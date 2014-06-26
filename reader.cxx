#include "common.hh"
#include "exascel.hh"
#include "reader.hh"

using namespace domain;

CellPtr create_cell(TablePtr table,std::string id, std::string text)
{
	Cell::Kind::type new_type;
	Cell *cell;
	if (text[0] == '\'')
	{
		cell = new Cell(id,text.substr(1));
		new_type = Cell::Kind::text;
		// std::cout << text.substr(1);
		// std::cout.flush();
	}
	else if (text[0] == '=')
	{
		cell = new Cell(id);
		new_type = Cell::Kind::expr;
		std::string term;
		Cell::Kind::type old_type;
		bool isnumber = true;
		bool isdiv = false;

		char c;
		Operation::type oper;

		for (int i = 1; i < text.size(); ++i)
		{
			c = text[i];
			// std::cout << c;
			// std::cout.flush();

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
				{
					old_type = table->get(id)->get_type();
					table->get(id)->morph(Cell::Kind::expr);
					table->get(id)->expr().terms.push_back(Term(atoi(term.c_str())));
					table->get(id)->morph(old_type);
				}
				else 
				{
					old_type = table->get(id)->get_type();
					table->get(id)->morph(Cell::Kind::expr);
					table->put(CellPtr(new Cell(term, Cell::Tag())));
					// table->put(create_cell(table,id,buf));
					table->get(id)->expr().terms.push_back(Term(table->get(term)));
					table->get(id)->morph(old_type);
				}
				
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
				
				old_type = table->get(id)->get_type();
				table->get(id)->morph(Cell::Kind::expr);
				table->get(id)->expr().operations.push_back(oper);
				table->get(id)->morph(old_type);
				
				isnumber = true;
			}
		}
		// last operand
		// TODO: check for zero if (isdiv)
		if (isnumber)
		{
			old_type = table->get(id)->get_type();
			table->get(id)->morph(Cell::Kind::expr);
			table->get(id)->expr().terms.push_back(Term(atoi(term.c_str())));
			table->get(id)->morph(old_type);
		}
		else 
		{
			old_type = table->get(id)->get_type();
			table->get(id)->morph(Cell::Kind::expr);
			table->put(CellPtr(new Cell(term, Cell::Tag())));
			table->get(id)->expr().terms.push_back(Term(table->get(term)));	
			table->get(id)->morph(old_type);
		}			
	}
	else
	{
		cell = new Cell(id,atoi(text.c_str()));
		new_type = Cell::Kind::num;
	}

	table->get(id)->morph(new_type);
	cell->morph(new_type);
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

	std::string cur_id;

	for (int i = 0; i < height; ++i)
	{
		cur_column_name = "A";
		for (int j = 0; j < width - 1; ++j)
		{
			cur_id = cur_column_name + std::to_string((long long)(i + 1));

			table->put(CellPtr(new Cell(cur_id, Cell::Tag())));

			std::getline(input, buf, delim);
			// TO DO: Check for bad input
			table->put(create_cell(table,cur_id,buf));
			cur_column_name = next_column_name(cur_column_name);
		}
		std::getline(input, buf);
		// TO DO: Check for bad input
		table->put(create_cell(table,cur_id,buf));
	}

	return TablePtr(table);
}
