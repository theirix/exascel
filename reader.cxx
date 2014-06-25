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

	//ignore endline symbol from first row
	std::getline(input,buf,'\n');

	Table *table = new Table(height,width);

	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width - 1; ++j)
		{
			std::getline(input, buf, delim);
			std::cout << buf << '\t';
		}
		std::getline(input,buf);
		std::cout << buf << std::endl;
	}

	return TablePtr(table);
}
