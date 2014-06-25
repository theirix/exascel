#include "common.hh"
#include "exascel.hh"
#include "reader.hh"

using namespace domain;

TablePtr read_table(std::istream& input)
{
	return TablePtr(new Table());
}
