#include "common.hh"
#include "exascel.hh"
#include "reader.hh"
#include "graph.hh"

using namespace domain;

namespace test
{
	TablePtr create_test_table()
	{
		TablePtr table(new Table(3,4));
		table->put(CellPtr(new Cell("a1", 12)));
		table->put(CellPtr(new Cell("a2")));
		table->put(CellPtr(new Cell("a3", 3)));
		table->put(CellPtr(new Cell("a4", "Sample")));
		table->put(CellPtr(new Cell("b1")));
		table->put(CellPtr(new Cell("b2")));
		table->put(CellPtr(new Cell("b3")));
		table->put(CellPtr(new Cell("b4", "Spread")));
		table->put(CellPtr(new Cell("c1", "Test")));
		table->put(CellPtr(new Cell("c2")));
		table->put(CellPtr(new Cell("c3", 5)));
		table->put(CellPtr(new Cell("b4", "Sheet")));

		table->get("b1")->expr().terms.push_back(Term(table->get("c2")));
		
		table->get("a2")->expr().terms.push_back(Term(table->get("a1")));
		table->get("a2")->expr().terms.push_back(Term(table->get("b1")));
		table->get("a2")->expr().terms.push_back(Term(table->get("c1")));
		table->get("a2")->expr().terms.push_back(Term(5));

		table->get("a2")->expr().operations.push_back(Operation::add);
		table->get("a2")->expr().operations.push_back(Operation::mul);
		table->get("a2")->expr().operations.push_back(Operation::div);

		table->get("b2")->expr().terms.push_back(Term(table->get("a2")));
		table->get("b2")->expr().terms.push_back(Term(table->get("b1")));
		table->get("b2")->expr().operations.push_back(Operation::mul);
		
		table->get("c2")->expr().terms.push_back(Term(table->get("b3")));
		table->get("c2")->expr().terms.push_back(Term(table->get("c3")));
		table->get("a2")->expr().operations.push_back(Operation::sub);

		return table;
	}
};

int main(int argc, char *argv[])
{
	TablePtr table;
	if (argc == 2 && !strcmp(argv[1], "test"))
		table = test::create_test_table();
	else
		table = read_table(std::cin);

	Graph *graph = new Graph();
	graph->build(table);

	return 0;
}
