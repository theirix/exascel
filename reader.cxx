#include "common.hh"
#include "exascel.hh"
#include "reader.hh"

using namespace domain;

void add_referenced_cell(TablePtr table,std::string id,bool isnumber,
		std::string term)
{
	if (isnumber)
	{
		table->get(id)->expr().terms.push_back(Term(atoi(term.c_str())));
	}
	else 
	{
		/* dumb cell if referenced forward */
		if (!table->is(term))
			table->put(CellPtr(new Cell(term, Cell::TagKindNone())));

		table->get(id)->expr().terms.push_back(Term(table->get(term)));
	}
}

void create_cell(TablePtr table,std::string id, std::string text)
{
	if (text[0] == '\'')
	{
		table->put(CellPtr(new Cell(id,text.substr(1))));
	}
	else if (text[0] >= '0' && text[0] <= '9')
	{
		/* forward-referenced numeric field is always of type None */
		if (table->is(id))
			table->get(id)->set_num(atoi(text.c_str()));
		else
			table->put(CellPtr(new Cell(id,atoi(text.c_str()))));
	}
	else if (text[0] == '=')
	{
		std::string term;
		bool isnumber = true;
		char c;
		Operation::type oper;

		if (table->is(id))
			table->get(id)->morph(Cell::Kind::expr);
		else
			table->put(CellPtr(new Cell(id)));

		for (int i = 1; i < text.size(); ++i)
		{
			c = text[i];

			if (c >= 'A' && c <= 'Z')
			{
				// cell name
				isnumber = false;
				term += c;
			}
			else if (c >= '0' && c <= '9')
			{
				// digit
				term += c;
			}
			else if (c == ' ')
			{
				continue;
			}
			else 
			{
				// operation
				switch (c)
				{
					case '*': oper = Operation::mul; break;
					case '-': oper = Operation::sub; break;
					case '+': oper = Operation::add; break;
					case '/': oper = Operation::div; break;
					default: throw std::runtime_error("Wrong op");
				}
				
				add_referenced_cell(table, id, isnumber, term);
				table->get(id)->expr().operations.push_back(oper);
				
				isnumber = true;
				term = "";
			}
		} // end for

		// last operand
		add_referenced_cell(table, id, isnumber, term);
	}
	else
	{
		throw std::runtime_error("Unknown input '" + text + "'");
	}
}

TablePtr read_table(std::istream& input)
{
	int height, width;
	std::string buf;
	const char delim = '\t';
	std::string column_name;

	input >> height >> width;

	//ignore endline symbol from first row
	std::getline(input, buf, '\n');

	TablePtr table(new Table(height, width));

	for (int i = 0; i < height; ++i)
	{
		column_name = "A";
		for (int j = 0; j < width - 1; ++j)
		{
			std::getline(input, buf, delim);
			// TO DO: Check for bad input
			create_cell(table, domain::cell_name(column_name, i), buf);
			column_name = next_column_name(column_name);
		}
		std::getline(input, buf);
		// TO DO: Check for bad input
		create_cell(table, domain::cell_name(column_name, i), buf);
	}

	return table;
}
