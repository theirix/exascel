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
		table->put(CellPtr(new Cell("b1")));
		table->put(CellPtr(new Cell("b2", "Foobar")));
		table->put(CellPtr(new Cell("b3", 42)));

		table->get("a2")->expr().terms.push_back(table->get("a1"));
		table->get("a2")->expr().terms.push_back(table->get("a3"));
		table->get("a2")->expr().operations.push_back(Operation::add);
		return table;
	}
};

int main(int argc, char *argv[])
{
	TablePtr table = read_table(std::cin);
	//table = test::create_test_table();
	return 0;
}
