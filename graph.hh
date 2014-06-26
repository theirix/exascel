#ifndef HEADER_GRAPH
#define HEADER_GRAPH

namespace domain
{
	/*
	 * Class allows to build tiered representation of evaluation
	 * algorithm, evaluate graph expression.
	 */
	class Graph
	{
		TablePtr m_table;
		std::vector<CellVec> m_tiers;
		size_t m_max_width;

		void evaluate_seq();
		void evaluate_openmp();
	public:

		void build (TablePtr table);

		void evaluate();

		void print_tiers();
	};
};

#endif
