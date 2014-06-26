#include "common.hh"
#include "exascel.hh"
#include "reader.hh"

using namespace domain;

CellPtr create_cell(std::string id, std::string text)
{
	if (text[0] == '\'')
		return CellPtr(new Cell(id,text));
	// if (text[0] == '=')
		// return CellPtr(new Cell(id,text));

	// TO DO: return different cells for different text types 
	return CellPtr(new Cell(id,text));
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

	Table *table = new Table(height, width);

	for (int i = 0; i < height; ++i)
	{
		cur_column_name = "A";
		for (int j = 0; j < width - 1; ++j)
		{
			std::getline(input, buf, delim);
			// TO DO: Check for bad input
			table->put(create_cell(cur_column_name + std::to_string((long long)(i + 1)),buf));
			cur_column_name = next_column_name(cur_column_name);
		}
		std::getline(input, buf);
		// TO DO: Check for bad input
		table->put(create_cell(cur_column_name + std::to_string((long long)(i + 1)),buf));
	}

	return TablePtr(table);
}
