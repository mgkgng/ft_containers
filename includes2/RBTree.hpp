#pragma once

#include "lib.hpp"
#include "pair.hpp"
#include <unistd.h>
#include "Iterator.hpp"

namespace ft {
template<typename Value>
struct RBnode {
	RBnode*	parent;
	RBnode*	left;
	RBnode*	right;
	bool	red;
	Value	value;
	bool	empty;

	public:
		typedef Value value_type;

		RBnode() : parent(0), left(0), right(0), red(false), empty(true) {
			value = Value();
		}
		RBnode(Value v) : parent(0), left(0), right(0), red(true), value(v), empty(false) {}

		RBnode *min() { return ((!this->left) ? this : this->left->min()); }
		RBnode *min() const { return ((!this->left) ? this : this->left->min()); }
		RBnode *max() { return ((!this->right) ? this : this->right->max()); }
		RBnode *max() const { return ((!this->right) ? this : this->right->max()); }

		RBnode *next() const {
			if (this->empty)
				return (NULL);
			if (this->right)
				return (this->right->min());
			if (this->parent && this == this->parent->left)
				return (this->parent);
			RBnode *where;
			for (where = this->parent; where && where->parent && where == where->parent->right; where = where->parent);
			return ((where) ? where->parent : NULL);
		}

		RBnode *prev() const {
			if (this->empty)
				return (NULL);
			if (this->left)
				return (this->left->max());
			if (this == this->parent->right)
				return (parent);

			RBnode *where;
			for (where = this->parent; where && where == where->parent->left; where = where->parent);
			return ((where) ? where->parent : NULL);
		}
};

template <typename Node>
class RBiter {
	public:
		typedef typename Node::value_type value_type;
		typedef value_type& reference;
		typedef value_type* pointer;
		typedef ptrdiff_t difference_type;

		explicit RBiter() : ptr(NULL) {} 
		RBiter(Node *where) : ptr(where) {}

    	operator RBiter<const Node>() const { return (this->ptr); }

		reference operator*() const { return (ptr->value); }
		const pointer operator->() const { return (&(operator*())); }

		RBiter& operator=(RBiter const & other) {
			ptr = other.ptr;
			return (*this);
		}

		RBiter& operator++() {
			ptr = ptr->next();
			return (*this);
		}

		RBiter operator++(int) {
			RBiter tmp = *this;
			ptr = ptr->next();
			return (tmp);
		}

		RBiter& operator--() {
			ptr = ptr->prev();
			return (*this);
		}

		RBiter operator--(int) {
			RBiter tmp = *this;
			ptr = ptr->prev();
			return (tmp);
		}

		bool operator==(const RBiter& s) { return (ptr == s.ptr); }
		bool operator!=(const RBiter& s) { return (ptr != s.ptr); }

		Node *getNode() const { return (ptr); }
	
	protected:
		Node	*ptr;
};

template<
	class Value,
    class Compare
>
class RBtree {

	public:
		///////////////////////////
		// ** type definition ** //
		///////////////////////////
		typedef Value					value_type;
		typedef RBnode<value_type>		node;
		typedef RBiter<node>			iterator;
		typedef RBiter<const node>		const_iterator;
		typedef ft::ReverseIter<iterator>		reverse_iterator;
		typedef ft::ReverseIter<const_iterator>	const_reverse_iterator;
		typedef std::allocator<node>	node_allocator;
		typedef unsigned int			size_type;

		////////////////////////
		// ** Constructors ** //
		////////////////////////

		RBtree() {
			this->size = 0;
			this->root = NULL;
			this->nodeAlloc = node_allocator();
			this->comp = Compare();
		}

		///////////////////////////////
		// ** principal functions ** //
		///////////////////////////////

		node *add(value_type v) {
			if (search(v, this->root))
				return (NULL);
			node *newNode = addNode(v);
			insert(newNode);
			return (newNode);
		}

		bool erase(value_type v) {
			node *n = search(v, this->root);
			usleep(1);
			return ((!n) ? false : remove(n));
		}

		bool erase(node *n) {
			usleep(10);
			return ((!n) ? false : remove(n));
		}

		node *search(const value_type &v, node *n) {
 			if (!n || (comp(n->value, v) && comp(v, n->value))) /*n->value == v)*/
				return (n);
			return (!comp(n->value, v)) ? (this->search(v, n->left)) : (this->search(v, n->right));
		}

		



		void clear() {
			destroy(this->root);
			this->root = NULL;
			this->size = 0;
		}

		void destroy(node *n) {
			if (!n)
				return;
			destroy(n->left);
			destroy(n->right);
			deleteNode(n);
		}

		//////////////////
		// ** utils ** //
		//////////////////
		node *getGP(node *n) {
			return (n && n->parent) ? n->parent->parent : 0;
		}

		node *getU(node *n) {
			node *gp = getGP(n);
			if (!gp)
				return (0);
			return (n->parent == gp->left) ? gp->right : gp->left;
		}

		node *getS(node *n) {
			return (n == n->parent->left) ? n->parent->right : n->parent->left;
		}

		node *getRoot() { return (root); }

		void transplant(node *n, node *child)
		{			
			if (!n->parent)
				this->root = child;
			else if (n == n->parent->left)
				n->parent->left = child;
			else
				n->parent->right = child;
			if (child)
				child->parent = n->parent;
		}

		void putNodePos(node *n, node *where) {
			n->parent = where->parent;
			(n == n->parent->left) ? n->parent->left = n : n->parent->right = n;
		}
		
		/* GETTER */
		size_type getSize() const { return size; }

		void swap(RBtree &other) {
			node *tmp = root;
			root = other.root;
			other.root = tmp;

			size_type tmp2 = size;
			size = other.size;
			other.size = tmp2;

			std::allocator<node> tmp3 = nodeAlloc;
			nodeAlloc = other.nodeAlloc;
			other.nodeAlloc = tmp3;

			Compare tmp4 = comp;
			comp = other.comp;
			other.comp = tmp4;
		}

		node *addNode(const value_type &v) {
			node* n = nodeAlloc.allocate(1);
			nodeAlloc.construct(n, v);
			return (n);
		}

		void deleteNode(node *n) {
			nodeAlloc.destroy(n);
			nodeAlloc.deallocate(n, 1);
		}

		void print(const std::string &prefix, node *n, bool isLeft = 0)
		{
			if (!n)
				return;

			std::cout << prefix;
        	std::cout << (isLeft ? "├──" : "└──" );

			std::cout << (!n->red ? "\033[1;90m" : "\033[1;31m") << n->value << "\033[0m" << std::endl;

        	print(prefix + (isLeft ? "│   " : "    "), n->left, true);
        	print(prefix + (isLeft ? "│   " : "    "), n->right, false);
		}

		node *max() { return (!this->root) ? NULL : this->root->max(); }
		node *max() const { return (!this->root) ? NULL : this->root->max(); }
		node *min() { return (!this->root) ? NULL : this->root->min(); }
		node *min() const { return (!this->root) ? NULL : this->root->min(); }


		size_t max_size() const { return (nodeAlloc.max_size()); }

		size_type		size;
		node			*root;


	protected:
		node_allocator	nodeAlloc;
		Compare			comp;

};

template <typename Value, typename CompV> 
inline bool operator==(const RBtree<Value, CompV>& lhs, const RBtree<Value, CompV>& rhs) { return lhs.size == rhs.size && ft::equal(lhs.begin(), lhs.end(), rhs.begin()); }

template <typename Value, typename CompV>
inline bool operator!=(const RBtree<Value, CompV>& lhs, const RBtree<Value, CompV>& rhs) { return !(lhs == rhs); }

template <typename Value, typename CompV>
inline bool operator<(const RBtree<Value, CompV>& lhs, const RBtree<Value, CompV>& rhs) { return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); }

template <typename Value, typename CompV>
inline bool operator<=(const RBtree<Value, CompV>& lhs, const RBtree<Value, CompV>& rhs) { return !(rhs < lhs); }

template <typename Value, typename CompV>
inline bool operator>(const RBtree<Value, CompV>& lhs, const RBtree<Value, CompV>& rhs) { return rhs < lhs; }

template <typename Value, typename CompV>
inline bool operator>=(const RBtree<Value, CompV>& lhs, const RBtree<Value, CompV>& rhs) { return !(lhs < rhs); }
};