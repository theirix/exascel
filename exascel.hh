#ifndef HEADER_EXASCEL
#define HEADER_EXASCEL

namespace domain
{
	struct Operation
	{
		typedef enum { add, sub, mul, div } type;
	};


	class Cell
	{
		public:
			struct Kind
			{
				typedef enum { none, error, expr, text, num } type;
			};
		private:

			std::string m_id;
			const Kind::type m_kind;
		public:

			Cell (std::string id, Kind::type kind)
				: m_id(id), m_kind(kind)
			{
			}

			std::string id() const
			{
				return m_id;
			}

	};
	typedef std::shared_ptr<Cell> CellPtr;

	class Expression
	{
		public:
			std::list<CellPtr> terms;
			std::list<Operation::type> operations;

	};
	
	class Table
	{

		typedef std::map<std::string, CellPtr> Cells;
		Cells m_cells;
	public:

		CellPtr get(std::string id)
		{
			return m_cells[id];
		}
		
		void put(CellPtr cell)
		{
			assert(cell);
			m_cells[cell->id()] = cell;
		}

		void print() {}
	};

	typedef std::shared_ptr<Table> TablePtr;

};


#endif
