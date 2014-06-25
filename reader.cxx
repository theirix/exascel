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

	TablePtr table(height,width);

	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			std::getline(input,buf,delim);
			std::cout << buf << '\t';
		}
		std::cout << endl;
	}

	return table;
}
