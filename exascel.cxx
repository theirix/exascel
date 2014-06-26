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
		table->put(CellPtr(new Cell("A1", 12)));
		table->put(CellPtr(new Cell("A2")));
		table->put(CellPtr(new Cell("A3", "Test")));
		table->put(CellPtr(new Cell("B1")));
		table->put(CellPtr(new Cell("B2")));
		table->put(CellPtr(new Cell("B3")));
		table->put(CellPtr(new Cell("C1", 3)));
		table->put(CellPtr(new Cell("C2")));
		table->put(CellPtr(new Cell("C3", 5)));
		table->put(CellPtr(new Cell("D1", "Sample")));
		table->put(CellPtr(new Cell("D2", "Spread")));
		table->put(CellPtr(new Cell("D3", "Sheet")));

		table->get("B1")->expr().terms.push_back(Term(table->get("C2")));
		
		table->get("A2")->expr().terms.push_back(Term(table->get("A1")));
		table->get("A2")->expr().terms.push_back(Term(table->get("B1")));
		table->get("A2")->expr().terms.push_back(Term(table->get("C1")));
		table->get("A2")->expr().terms.push_back(Term(5));

		table->get("A2")->expr().operations.push_back(Operation::add);
		table->get("A2")->expr().operations.push_back(Operation::mul);
		table->get("A2")->expr().operations.push_back(Operation::div);

		table->get("B2")->expr().terms.push_back(Term(table->get("A2")));
		table->get("B2")->expr().terms.push_back(Term(table->get("B1")));
		table->get("B2")->expr().operations.push_back(Operation::mul);
		
		table->get("C2")->expr().terms.push_back(Term(table->get("B3")));
		table->get("C2")->expr().terms.push_back(Term(table->get("C3")));
		table->get("C2")->expr().operations.push_back(Operation::sub);
		
		table->get("B3")->expr().terms.push_back(Term(4));
		table->get("B3")->expr().terms.push_back(Term(3));
		table->get("B3")->expr().operations.push_back(Operation::sub);

		return table;
	}
};

int main(int argc, char *argv[])
{
	const bool debug = argc == 2 && !strcmp(argv[1], "test");
	const bool verbose = true;

	TablePtr table;
	if (debug)
		table = test::create_test_table();
	else
		table = read_table(std::cin);

	Graph *graph = new Graph();
	graph->build(table);

	if (verbose)
	{
		std::ofstream file("foo.dot");
		table->print_dot(file);
		file.close();
		graph->print_tiers();
	}

	graph->evaluate();
	
	if (verbose)
	{
		table->print_dot(std::cerr);
	}

	table->print(std::cout);

	return 0;
}

std::string domain::next_column_name (std::string prev_column_name)
{
	for (int i = prev_column_name.size() - 1; i >= 0; --i)
	{
		if (prev_column_name[i] == 'Z')
		{
			prev_column_name[i] = 'A'; 
		}
		else {
			prev_column_name[i] += 1;
			return prev_column_name;
		} 
	}

	return std::string("A") + prev_column_name;
}
		
void Table::print_dot(std::ostream& output)
{
	output << "\ndigraph D {\n";
	for (auto& kv: cells())
	{
		CellPtr cell = kv.second;
		if (cell->kind() == Cell::Kind::expr)
		{
			for (auto t: cell->expr().terms)
				if (t.kind == Term::Kind::ref)
					output << "\t" << t.cell->id()  << " -> " 
						<< cell->id() << std::endl;
		}
		else if (cell->kind() == Cell::Kind::num)
		{
			output << "\t" << cell->id() << " [ style=filled ];\n";
		}
	}
	output << "}\n\n";
}
	
void Table::print(std::ostream& output)
{
	output << '\t';
	std::string cur_column_name = "A";

	for (int i = 0; i < w; ++i)
	{
		output << cur_column_name << '\t';
		cur_column_name = next_column_name(cur_column_name);
	}


	for (int i = 0; i < h; ++i)
	{
		output << std::endl << (i + 1) << '\t';
		cur_column_name = "A";

		for (int j = 0; j < w; ++j)
		{
			CellPtr cell = get(cur_column_name + std::to_string(i + 1));
			switch (cell->kind())
			{
				case Cell::Kind::text:	output << cell->text(); break;
				case Cell::Kind::num:		output << cell->num(); break;
				case Cell::Kind::expr:	output << "[expr]"; break;
				default:								output << "[UNKNOWN]"; break;
			}
			output << "\t";
			// cur_column_name + std::to_string(i + 1) << '\t';
			// get("A1")->text() << '\t';
			cur_column_name = next_column_name(cur_column_name);
		}
	}

	output << std::endl;
}
