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
		double evaluate_expression (Expression expression);
	public:

		void build (TablePtr table);

		void evaluate();

		void print_tiers();
	};
};

#endif
