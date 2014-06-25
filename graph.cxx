#include "common.hh"
#include "exascel.hh"
#include "graph.hh"

using namespace domain;

void Graph::build(TablePtr table)
{
	const Table::Cells& cells = table->cells();

	typedef std::vector<CellPtr> CellVec;
	std::vector<CellVec> tiers;

	for (;;)
	{
		tiers.push_back(CellVec());

		for (auto& kv: cells)
		{
			CellPtr cell = kv.second;
			if (cell->kind() == Cell::Kind::expr &&
					cell->expr().terms.empty())
			{
				std::cerr << "That one: " << cell->id() << std::endl;
				tiers.back().push_back(cell);
			}
		
			//for (auto& kv_tier: tiers.)
			{

			}
		}
		break;
	}

}
