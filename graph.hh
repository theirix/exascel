#ifndef HEADER_GRAPH
#define HEADER_GRAPH

namespace domain
{
	class Node;

	class Node
	{
		std::vector<Node*> childs;
	};
	

	class Graph
	{
		Node *m_root;
	public:

		Graph()
			: m_root(NULL)
		{
		}

		void build (TablePtr table);
	};
};

#endif
