#include "common.hh"
#include "exascel.hh"
#include "graph.hh"

using namespace domain;

void Graph::print_tiers()
{
	for (auto tier: m_tiers)
	{
		std::cerr << "tier:\t";
		for (auto cell: tier)
			std::cerr << cell->id() << " ";
		std::cerr << "\n";
	}
}

void Graph::build(TablePtr table)
{
	m_table = table;
	m_tiers.clear();

	std::list<CellPtr> all_cells;

	for (auto& kv: table->cells())
		if (kv.second->kind() == Cell::Kind::expr ||
				kv.second->kind() == Cell::Kind::num)
			all_cells.push_back(kv.second);
		
	while (!all_cells.empty())
	{
		CellVec current_tier;

		for (auto cell: all_cells)
		{
			bool save = true;
			if (cell->kind() == Cell::Kind::expr)
			{
				for (auto t: cell->expr().terms)
				{
					if (t.kind == Term::Kind::cell &&
							std::find(all_cells.begin(), all_cells.end(), 
								t.cell) != all_cells.end())
						save = false;
				}
			}
			else if (cell->kind() == Cell::Kind::num)
			{
				save = true;
			}
			if (save)
				current_tier.push_back(cell);
		}

#if 0
		std::cerr << "In current tier: " << current_tier.size() << ", " << all_cells.size() << ":\n";
		for (auto cell: current_tier)
			std::cerr << "\t" << cell->id() << "\n";
#endif

		for (auto cell: current_tier)
			all_cells.remove(cell);
		if (!current_tier.empty())
			m_tiers.push_back(current_tier);
	}

}
		
void Graph::evaluate()
{
	for (auto tier: m_tiers)
	{
		std::cerr << "Calculating tier\n";
		for (auto cell: tier)
		{
			if (cell->kind() == Cell::Kind::expr)
			{
				for (auto term: cell->expr().terms)
				{
					if (!(term.kind == Term::Kind::num ||
								term.cell->kind() == Cell::Kind::num))
					{
						std::cerr << "Dependency error for cell "
							<< cell->id() << ", term " << term.cell->id()
							<< std::endl;
						throw std::runtime_error("Dependency error");
					}
				}

				int value = (int)evaluate_expression(cell->expr());
				cell->set_evaluated(value);
				std::cerr << "For cell " << cell->id() << " val=" << value << "\n";
			}
		}

	}

	for (auto kv: m_table->cells())
	{
		if (kv.second->kind() == Cell::Kind::expr)
			throw std::runtime_error("Wrong type " + kv.second->id());
		if (kv.second->kind() == Cell::Kind::num)
			std::cerr << kv.second->id() << " = " << kv.second->num() << "\n";
	}
}

int read_num(Term term)
{
	if (term.kind == Term::Kind::cell)
	{
		if (term.cell->kind() != Cell::Kind::num)
			throw std::runtime_error("Wrong type");
		return term.cell->num();
	}
	return term.num;
}

double Graph::evaluate_expression (Expression expression)
{
	double value;
	std::list<Term>::const_iterator 
		left = expression.terms.begin(), right = left;
	std::list<Operation::type>::const_iterator
		op = expression.operations.begin();
	value = read_num(*left);
	for (++right; right != expression.terms.end(); ++left, ++right, ++op)
	{
		double rhs = read_num(*right);
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
