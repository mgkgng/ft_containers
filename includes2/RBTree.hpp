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

		node *max() { return (!this->root) ? NULL : this->root->max(); }
		node *max() const { return (!this->root) ? NULL : this->root->max(); }
		node *min() { return (!this->root) ? NULL : this->root->min(); }
		node *min() const { return (!this->root) ? NULL : this->root->min(); }

		size_t max_size() const { return (nodeAlloc.max_size()); }

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