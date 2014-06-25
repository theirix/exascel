#ifndef HEADER_EXASCEL
#define HEADER_EXASCEL

namespace domain
{
	/*
	 * Helper functions
	 */
	std::string next_column_name (std::string prev_column_name);

	/*
	 * Generic operation
	 */
	struct Operation
	{
		typedef enum { add, sub, mul, div } type;
	};


	class Cell;
	typedef std::shared_ptr<Cell> CellPtr;

	/*
	 * Generic term - cell reference or value
	 */
	class Term
	{
	public:
		struct Kind
		{
			typedef enum { ref, num } type;
		};

		Term(CellPtr acell)
			:kind(Kind::ref), cell(acell)
		{
		}
		
		Term(int anum)
			: kind(Kind::num), num(anum)
		{
		}

		Kind::type kind;
		CellPtr cell;
		int num;
	};


	/*
	 * Represents a left-associative expression by given grammar
	 */
	class Expression
	{
		public:
			std::list<Term> terms;
			std::list<Operation::type> operations;
	};

	/*
	 * Represents a single typed cell of table 
	 */
	class Cell
	{
		public:
			struct Kind
			{
				typedef enum { none, error, expr, text, num } type;
			};
		private:

			std::string m_id;
			Kind::type m_kind;

			// for expression cells
			Expression m_expr;
			// for text cells
			std::string m_text;
			// for numeric cells
			int m_num;
		public:

			Cell (std::string id, std::string text)
				: m_id(id), m_kind(Kind::text), m_text(text)
			{
			}
			
			Cell (std::string id, int num)
				: m_id(id), m_kind(Kind::num), m_num(num)
			{
			}
			
			Cell (std::string id)
				: m_id(id), m_kind(Kind::expr)
			{
			}
			

			std::string id() const
			{
				return m_id;
			}
			
			Kind::type kind() const
			{
				return m_kind;
			}
			
			std::string text() const
			{
				if (m_kind != Kind::text)
					throw std::runtime_error("Wrong cell type");
				return m_text;
			}
			
			int num() const
			{
				if (m_kind != Kind::num)
					throw std::runtime_error("Wrong cell type");
				return m_num;
			}

			Expression& expr()
			{
				if (m_kind != Kind::expr)
					throw std::runtime_error("Wrong cell type");
				return m_expr;
			}

			void set_evaluated(int num)
			{
				if (m_kind != Kind::expr)
					throw std::runtime_error("Wrong cell type");
				m_expr = Expression();
				m_num = num;
				m_kind = Kind::num;
			}

	};
	
	typedef std::vector<CellPtr> CellVec;
	
	/*
	 * Table. Stores cells, provides associative access by their id
	 */
	class Table
	{
	public:
		typedef std::map<std::string, CellPtr> Cells;

	private:
		int w;
		int h;
		Cells m_cells;
	public:

		Table (int height, int width)
				: h(height), w(width)
		{
		}

		CellPtr get(std::string id) // why getting errors trying const?
		{
			if (!m_cells[id])
				throw std::runtime_error("Cannot extract empty cell by" + id);
			return m_cells[id];
		}
		
		void put(CellPtr cell)
		{
			assert(cell);
			if (!cell)
				throw std::runtime_error("Cannot add empty cell");
			m_cells[cell->id()] = cell;
		}

		const Cells& cells() const
		{
			return m_cells;
		}

		void print(std::ostream& output);

		void print_dot(std::ostream& output);
	};

	typedef std::shared_ptr<Table> TablePtr;

};


#endif
