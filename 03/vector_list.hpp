#pragma once
#include <vector>
#include <list>

template<class T>
class VectorList
{
	private:
		using VectT  = std::vector<T>;
		using ListT = std::list<VectT>;

	public:
		using value_type = T;

		VectorList() = default;
		VectorList(VectorList const &) = default;
		VectorList(VectorList &&) = default;

		VectorList & operator=(VectorList &&)     = default;
		VectorList & operator=(VectorList const &) = default;

		// метод, который будет использоваться для заполнения VectorList
		// гарантирует, что в списке не будет пустых массивов
		template<class It>
			void append(It p, It q); // определена снаружи
		/*  {
		    if (p != q)
		    data_.push_back(VectT(p,q));
		    } 
		 */

		bool empty() const { return size() == 0; } 

		// определите метод size
		size_t size() const 
		{
			size_t ret_val = 0;
			for (auto &&vec : data_)
				ret_val += vec.size();

			return ret_val;
		}

		// определите const_iterator
		class const_iterator : public std::iterator<std::bidirectional_iterator_tag, const T>
	{
		public:
			const_iterator() : data(), lit(), vit() {}

			const_iterator(const const_iterator &it) : data(it.data), lit(it.lit), vit(it.vit) {}

			const_iterator(const ListT *dat, typename ListT::const_iterator it) : data(dat)
		{
			if (dat && dat->size())
			{
				if (it == dat->begin())
				{
					lit = dat->begin();
					vit = lit->begin();
				}
				else
				{
					lit = std::prev(dat->end());
					vit = lit->end();
				}
			}
		}

			const_iterator& operator++()
			{
				if (vit != lit->end())
				{
					vit++;
				}

				if (vit == lit->end())
				{
					auto _tlit = std::next(lit);
					if (_tlit != data->end())
					{
						lit = _tlit;
						vit = lit->begin();
					}
				}

				return *this;
			}

			const_iterator operator++(int)
			{
				const_iterator it = *this;
				this->operator++();

				return it;
			}

			const_iterator& operator--()
			{
				if (vit != lit->begin())
				{
					vit--;
				}
				else if (lit != data->begin())
				{
					lit--;
					vit = std::prev(lit->end());
				}

				return *this;
			}

			const_iterator operator--(int)
			{
				const_iterator it = *this;
				this->operator--();

				return it;
			}

			const T& operator*() const
			{
				return *vit;
			}

			const T* operator->() const
			{
				return &(*vit);
			}

			bool operator==(const const_iterator& rhs) const
			{
				return (lit == rhs.lit) && (vit == rhs.vit);
			}

			bool operator!=(const const_iterator& rhs) const
			{
				return (lit != rhs.lit) || (vit != rhs.vit);
			}

		private:
			const ListT *data;
			typename ListT::const_iterator lit;
			typename VectT::const_iterator vit;
	};

		// определите методы begin / end
		const_iterator begin() const
		{
			return const_iterator(&data_, data_.cbegin());
		}
		const_iterator end()   const
		{
			return const_iterator(&data_, data_.cend());
		}

		// определите const_reverse_iterator
		class const_reverse_iterator : public std::reverse_iterator<const_iterator>
	{
		public:
			const_reverse_iterator() : cit() {};

			explicit const_reverse_iterator(const_iterator _it) : cit(_it) { }

			const_reverse_iterator(const const_reverse_iterator &crit) : cit(crit.cit) {}

			const_iterator base() const { return cit; }

			const_reverse_iterator& operator++()
			{
				--cit;
				return *this;
			}

			const_reverse_iterator operator++(int)
			{
				const_reverse_iterator it = *this;
				--cit;
				return it;
			}

			const_reverse_iterator& operator--()
			{
				++cit;
				return *this;
			}

			const_reverse_iterator operator--(int)
			{
				const_reverse_iterator it = *this;
				++cit;
				return it;
			}

			const T& operator*() const
			{
				return *(std::prev(cit));
			}

			const T* operator->() const
			{
				return &(operator*()); 
			}

			bool operator==(const const_reverse_iterator& rhs) const
			{
				return cit == rhs.cit;
			}

			bool operator!=(const const_reverse_iterator& rhs) const
			{
				return cit != rhs.cit;
			}

		private:
			const_iterator cit;
	};

		// определите методы rbegin / rend
		const_reverse_iterator rbegin() const 
		{
			return const_reverse_iterator(const_iterator(&data_, data_.cend()));
		}

		const_reverse_iterator rend()   const {
			return const_reverse_iterator(const_iterator(&data_, data_.cbegin()));
		}

	private:
		ListT data_;
};
