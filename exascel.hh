#ifndef HEADER_EXASCEL
#define HEADER_EXASCEL

namespace domain
{
	struct Operation
	{
		typedef enum { add, sub, mul, div } type;
	};


	class Cell;
	typedef std::shared_ptr<Cell> CellPtr;

	class Term
	{
	public:
		struct Kind
		{
			typedef enum { cell, num } type;
		};

		Term(CellPtr acell)
			:kind(Kind::cell), cell(acell)
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

	class Expression
	{
		public:
			std::list<Term> terms;
			std::list<Operation::type> operations;
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

	};
	
	typedef std::vector<CellPtr> CellVec;
	
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

		CellPtr get(std::string id)
		{
			if (!m_cells[id])
				throw std::runtime_error("Cannot extract empty cell");
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

		void print() {}
	};

	typedef std::shared_ptr<Table> TablePtr;

};


#endif
