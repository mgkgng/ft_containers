#include <memory>

namespace ft {

template<typename T>
struct node {
	node *parent;
	node *left;
	node *right
	bool red;
	T	value;

	node(T val = T(), bool col = true) : parent(NULL), left(NULL), right(NULL), red(col), value(val) {};
};

template<typename T, typename Compare, typename Alloc>
class tree {
	public:

		typedef T		value_type;
		typedef Alloc	allocator_type;
		typedef Compare	value_compare;
		typedef typename allocator_type::reference reference ;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::pointer const_pointer;
		typedef ptrdiff_t 		difference_type;
		typedef unsigned long	size_type;

		typedef node<T> node;

		typedef IterTree<value_type, Compare, Alloc, node<value_type> >			iterator;
		typedef ConstIterTree<value_type, Compare, Alloc, node<value_type> >	const_iterator;
		typedef ReverseIter<iterator> 											reverse_iterator;
		typedef ReverseIter<const_iterator> 									const_reverse_iterator;

		node *root;
		size_type size;
		allocator_type nodeAlloc;
		value_compare comp;
};
};