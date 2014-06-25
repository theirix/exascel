#include "common.hh"
#include "exascel.hh"
#include "reader.hh"

using namespace domain;

TablePtr read_table(std::istream& input)
{
	int height, width;
	std::string buf;

	input >> height >> width;
	for (int i = 0; i < height; ++i)
	{
		getline(input,buf);
	}
	return TablePtr(new Table());
}
