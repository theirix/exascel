#include "common.hh"
#include "exascel.hh"
#include "reader.hh"

using namespace domain;

CellPtr create_cell(TablePtr table,std::string id, std::string text)
{
	Cell *cell;
	if (text[0] == '\'')
	{
		cell = new Cell(id,text.substr(1));
		// std::cout << text.substr(1);
	}
	else if (text[0] == '=')
	{
		cell = new Cell(id);
		std::string term;
		bool isnumber = true;
		bool isdiv = false;

		char c;
		Operation::type oper;

		for (int i = 1; i < text.size(); ++i)
		{
			c = text[i];
			std::cout << c;

			if (c == ' ')
				continue;

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
			else 
			{
				// operation
				if (isnumber && isdiv && atoi(term.c_str()) == 0)
				{
					// division by zero
				}

				if (isnumber)
					table->get(id)->expr().terms.push_back(Term(atoi(term.c_str())));
				else 
					table->get(id)->expr().terms.push_back(Term(table->get(term)));
				
				term = "";

				switch (c)
				{
					case '*': 
					{
						oper = Operation::mul; 
						isdiv = false;
					} break;
					case '-': 
					{
						oper = Operation::sub;
						isdiv = false;
					} break;
					case '+': 
					{
						oper = Operation::add; 
						isdiv = false;
					} break;
					case '/': 
					{
						oper = Operation::div; 
						isdiv = true;
					} break;
					default: ;// unknown symbol
				}
				
				table->get(id)->expr().operations.push_back(oper);
				
				isnumber = true;
			}
		}
		// last operand
		// TODO: check for zero if (isdiv)
		if (isnumber)
			table->get(id)->expr().terms.push_back(Term(atoi(term.c_str())));
		else 
			table->get(id)->expr().terms.push_back(Term(table->get(term)));				
	}
	else
	{
		cell = new Cell(id,atoi(text.c_str()));
	}

	// TO DO: return different cells for different text types 
	return CellPtr(cell);
}

TablePtr read_table(std::istream& input)
{
	int height, width;
	std::string buf;
	char delim = '\t';
	std::string cur_column_name;

	input >> height >> width;

	//ignore endline symbol from first row
	std::getline(input, buf, '\n');

	TablePtr table(new Table(height, width));


	for (int i = 0; i < height; ++i)
	{
		cur_column_name = "A";
		for (int j = 0; j < width - 1; ++j)
		{
			std::getline(input, buf, delim);
			// TO DO: Check for bad input
			table->put(create_cell(table,cur_column_name + std::to_string(i + 1),buf));
			cur_column_name = next_column_name(cur_column_name);
		}
		std::getline(input, buf);
		// TO DO: Check for bad input
		table->put(create_cell(table,cur_column_name + std::to_string(i + 1),buf));
	}

	return TablePtr(table);
}
