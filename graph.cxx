#include "common.hh"
#include "exascel.hh"
#include "graph.hh"

/*#include <omp.h>*/

using namespace domain;

/*
 * Print helper
 */
void Graph::print_tiers()
{
	for (auto tier: m_tiers)
	{
		std::cerr << "tier:\t";
		for (auto cell: tier)
			std::cerr << cell->id() << " ";
		std::cerr << "\n";
	}
	std::cerr << "maximum parallel width " << m_max_width << "\n";
}

/*
 * Build graph tiers
 */
void Graph::build(TablePtr table)
{
	m_table = table;
	m_tiers.clear();
	m_max_width = 0;

	std::list<CellPtr> all_cells;

	/* save all cells at first */
	for (auto& kv: table->cells())
		if (kv.second->kind() == Cell::Kind::expr ||
				kv.second->kind() == Cell::Kind::num)
			all_cells.push_back(kv.second);
	
	/* iterate while any cell found */
	while (!all_cells.empty())
	{
		CellVec current_tier;

		for (auto cell: all_cells)
		{
			bool save = true;
			if (cell->kind() == Cell::Kind::expr)
			{
				/* find only expr cells that lead to existing tiers */
				for (auto t: cell->expr().terms)
				{
					if (t.kind == Term::Kind::ref &&
							std::find(all_cells.begin(), all_cells.end(), 
								t.cell) != all_cells.end())
						save = false;
				}
			}
			else if (cell->kind() == Cell::Kind::num)
			{
				/* numeric cell is saved first */
				save = true;
			}
			if (save)
				current_tier.push_back(cell);
		}

		/* remove current tier from all cells */
		for (auto cell: current_tier)
			all_cells.remove(cell);
		/* add the tier */
		if (!current_tier.empty())
			m_tiers.push_back(current_tier);
		else
			throw std::runtime_error("Dependency detection stalled " + std::to_string((long long)m_tiers.size()) + 
					", first stalled item " + all_cells.front()->describe());

		m_max_width = std::max(m_max_width, current_tier.size());
	}

}

/*
 * Fetch int value from term (cell or scalar)
 */
int read_ref_or_value(Term term)
{
	std::cerr << term.kind << std::endl;
	if (term.kind == Term::Kind::ref)
	{
		if (term.cell->kind() != Cell::Kind::num)
			throw std::runtime_error("Wrong type");
		return term.cell->num();
	}
	return term.num;
}

/*
 * Evaluate an expression
 */
int evaluate_expression (Expression expression)
{
	std::list<Term>::const_iterator 
		left = expression.terms.begin(), right = left;
	std::list<Operation::type>::const_iterator
		op = expression.operations.begin();

	int value = read_ref_or_value(*left);
	for (++right; right != expression.terms.end(); ++left, ++right, ++op)
	{
		int rhs = read_ref_or_value(*right);
		switch (*op)
		{
			case Operation::add: value += rhs; break;
			case Operation::sub: value -= rhs; break;
			case Operation::mul: value *= rhs; break;
			case Operation::div: value /= rhs; break;
		}
	}
	return value;
}

void Graph::evaluate()
{
	evaluate_openmp();

	// dump
	for (auto kv: m_table->cells())
	{
		if (kv.second->kind() == Cell::Kind::expr)
			throw std::runtime_error("Wrong type " + kv.second->id());
		if (kv.second->kind() == Cell::Kind::num)
			std::cerr << kv.second->id() << " = " << kv.second->num() << "\n";
	}
}

/*
 * Sequential evaluation of all cells
 */
void Graph::evaluate_seq()
{
	for (auto tier: m_tiers)
	{
		std::cerr << "\nCalculating tier\n";
		for (auto cell: tier)
		{
			if (cell->kind() == Cell::Kind::expr)
			{
				for (auto term: cell->expr().terms)
				{
					if (!(term.kind == Term::Kind::num ||
							(term.cell->kind() == Cell::Kind::num)))
						throw std::runtime_error("Dependency error for " + cell->id());
				}

				int value = (int)evaluate_expression(cell->expr());
				cell->set_num(value);
				std::cerr << "For cell " << cell->id() << " val=" << value << "\n";
			}
		}

	}
}

/*
 * OpenMP evaluation of all cells
 */
void Graph::evaluate_openmp()
{
	std::cerr << "Parallel width " << m_max_width << std::endl;
	
	//num_threads(m_max_width)
#pragma omp parallel
	for (auto tier: m_tiers)
	{
		/*
#pragma omp critical
		{
		std::cerr << "thread " << omp_get_thread_num() << std::endl;
		}
		*/
#pragma omp for
		for (size_t i = 0; i < tier.size(); ++i)
		{
			CellPtr cell = tier[i];
			if (cell->kind() == Cell::Kind::expr)
			{
				for (auto term: cell->expr().terms)
				{
					if (!(term.kind == Term::Kind::num ||
								term.cell->kind() == Cell::Kind::num))
						throw std::runtime_error("Dependency error for " + cell->id());
				}

				int value = (int)evaluate_expression(cell->expr());
				cell->set_num(value);
			}
		}

	}

}

