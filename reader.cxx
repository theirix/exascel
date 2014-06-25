#include "common.hh"
#include "exascel.hh"
#include "reader.hh"

using namespace domain;

TablePtr read_table(std::istream& input)
{
	int height, width;
	std::string buf;
	char delim = '\t';

	input >> height >> width;

	// std::getline(input,buf);

	Table *table = new Table(height,width);

	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width - 1; ++j)
		{
			std::getline(input,buf,delim);
			table->put(CellPtr(new Cell("a1", 12)));
			std::cout << buf << '\t';
		}
		std::getline(input,buf);
		std::cout << buf << std::endl;
	}

	return TablePtr(table);
}
