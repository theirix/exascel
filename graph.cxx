#include "common.hh"
#include "exascel.hh"
#include "graph.hh"

using namespace domain;

void Graph::build(TablePtr table)
{
	const Table::Cells& cells = table->cells();
	for (auto& kv: cells)
	{
		CellPtr cell = kv.second;
		if (cell->kind() == Cell::Kind::expr &&
				cell->expr().terms.empty())
		{
			std::cerr << "That one: " << cell->id() << std::endl;
		}
	}
}
