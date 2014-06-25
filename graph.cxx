#include "common.hh"
#include "exascel.hh"
#include "graph.hh"

using namespace domain;

void dump(TablePtr table)
{
	std::cerr << "digraph D {\n";
	for (auto& kv: table->cells())
	{
		CellPtr cell = kv.second;
		if (cell->kind() == Cell::Kind::expr)
			for (auto t: cell->expr().terms)
				if (t.kind == Term::Kind::cell)
					std::cerr << t.cell->id()  << " -> " 
						<< cell->id() << std::endl;
	}
	std::cerr << "}\n";

}

void Graph::build(TablePtr table)
{
	std::list<CellPtr> all_cells;
	std::vector<CellVec> tiers;

	dump(table);

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
							std::find(all_cells.begin(), all_cells.end(), t.cell) != all_cells.end())
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
			tiers.push_back(current_tier);
	}

	for (auto tier: tiers)
	{
		std::cerr << "tier:\n\t";
		for (auto cell: tier)
			std::cerr << cell->id() << " ";
		std::cerr << "\n";
	}

}
