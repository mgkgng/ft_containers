#pragma once

#include "lib.hpp"
#include "pair.hpp"

namespace ft {

template<class T, class Compare, class Allocator = std::allocator<T> >
class RBtree {

	private:
		node_pointer			_root;
		node_pointer			_start;
		node_pointer			_end;
		size_type				_size;
		allocator_type			_alloc;
		std::allocator<node>	_nodeAlloc;
		value_compare			_comp;

	public:

		///////////////////////////
		// ** type definition ** //
		///////////////////////////

		typedef T						Value;
		typedef size_t					size_type;
		typedef ptrdiff_t				difference_type;
		typedef Compare					value_compare;
		typedef Allocator				allocator_type;
		typedef value_type&				reference;
		typedef const value_type&		const_reference;
		typedef Allocator::pointer			pointer;
		typedef Allocator::const_pointer	const_pointer;

		typedef RBnode<T>				node;
		typedef RBnode<T>*				node_pointer;

		typedef ft::RBiter<Value>		iterator;

		///////////////////////////
		// ** Node structure ** //
		///////////////////////////

		struct RBnode {
			node_pointer parent;
			node_pointer left;
			node_pointer right;
			bool		red;
			Value		_v;

			RBnode(Value v) : _v(v), parent(0), left(0), right(0) {}
		};

		////////////////////////
		// ** Constructors ** //
		////////////////////////

		RBtree() {
			_root = 0;
			_start = _nodeAlloc.allocate(1);
			_end = _start;
		}

		///////////////////////////////
		// ** principal functions ** //
		///////////////////////////////

		void add(Value &v) {
			node_pointer n = _nodeAlloc.allocate(1);
			this->initNode(n, v);
			this->putNode(n, v);

			insert1(n);
		}

		void remove(node_pointer n) {
			node_pointer child = (this->isLeaf(n->right)) ? n->left : n->right;

			this->replace(n, child);
			if (!n->red) {
				if (child->red) child->red = false;
				else delete1(child);
			}
			_nodeAlloc.destroy(n);
			_nodeAlloc.deallocate(n, 1);
		}

		//////////////////
		// ** getter ** //
		//////////////////

		node_pointer getGP(node_pointer n) {
			return (n && n->parent) ? n->parent->parent : 0;
		}

		node_pointer getU(node_pointer n) {
			RBnode	*gp = getGP(n);
			if (!gp)
				return (0);
			return (n->parent == gp->left) ? gp->right : gp->left;
		}

		node_pointer getS(node_pointer n)
		{
			return (n == n->parent->left) ? n->parent->right : n->parent->left;
		}

		//////////////////
		// ** search ** //
		//////////////////

		template<typename Key>
		node_pointer recursiveTreeSearch(node_pointer n, Key &key) {
			if (!n || n->v.first == key)
				return (n);
			return (n->v.first < key) ? (recursiveTreeSearch(n->left, key)) : (recursiveTreeSearch(n->right, key));
		}

		template<typename Key>
		iterator searchKey(node_pointer n, Key &key) {
			if (!n)
				return (0);
			if (n->v.first == key)
				return (RBiter(n));
			if (_comp(n->key, key)) // less
				return (searchKey(n->right, key));
			else
				return (searchKey(n->left, key));
		}

		//////////////////
		// ** insert ** //
		//////////////////

		void insert(node_pointer n) {
			_alloc.
			n->parent = pos->parent;
			insert1(n);
		}

		void insert1(node_pointer n)
		{
			if (!n->parent)
				this->_root = n;
			else
				insert2(n);
		}

		void insert2(node_pointer n)
		{
    		if (!n->parent->red)
				return;
			else
				insert3(n);
		}

		void insert3(node_pointer n)
		{
			node_pointer u = getU(n);

			if (u && u->red) {
				n->parent->red = false;
				u->red = false;
				node_pointer gp = getGP(n);
				gp->red = true;
				insert1(gp);
			} else insert4(n);
		}

		void insert4(node_pointer n)
		{
			node_pointer gp = getGP(n);

			if (n == n->parent->right && n->parent == gp->left) {
				rotateL(n->parent);
				n = n->left;
			} else if (n == n->parent->left && n->parent == gp->right) {
				rotateR(n->parent);
				n = n->right;
			}
			insert5(n);
		}

		void insert5(node_pointer n)
		{
			node_pointer gp = getGP(n);

			n->parent->red = false;
			gp->red = true;
			(n == n->parent->left) ? rotateR(gp) : rotateL(gp);
		}

		//////////////////
		// ** rotate ** //
		//////////////////

		void rotateL(node_pointer n)
		{
			node_pointer c = n->right;
			node_pointer p = n->parent;

			if (c->left)
				c->left->parent = n;

			n->right = c->left;
			n->parent = c;
			c->left = n;
			c->parent = p;

			if (p)
				(p->left == n) ? p->left = c : p->right = c;
		}

		void rotateR(node_pointer n)
		{
			node_pointer c = n->left;
			node_pointer p = n->parent;

			if (c->right)
				c->right->parent = n;

			n->left = c->right;
			n->parent = c;
			c->right = n;
			c->parent = p;

			if (p)
				(p->right == n) ? p->right = c : p->left = c;
		}

		//////////////////
		// ** delete ** //
		//////////////////

		void delete1(node_pointer n)
		{
			if (n->parent)
				delete2(n);
		}

		void delete2(node_pointer n)
		{
			node_pointer s = getS(n);

			if (s->red) {
				n->parent->red = true;
				s->red = false;
				(n == n->parent->left) ? rotateL(n->parent) : rotateR(n->parent);
			}
			delete3(n);
		}

		void delete3(node_pointer n)
		{
			node_pointer s = getS(n);

			if (!n->parent->red && !s->red
				&& !s->left->red && !s->right->red) {
				s->red = true;
				delete1(n->parent);
			} else
				delete4(n);
		}

		void delete4(node_pointer n)
		{
			node_pointer s = getS(n);

			if (n->parent->red && !s->red
				&& !s->left->red && !s->right->red) {
				s->red = true;
				n->parent->red = false;
			} else
				delete5(n);
		}

		void delete5(node_pointer n)
		{
			node_pointer s = getS(n);

			if  (!s->red) {
				if (n == n->parent->left && !s->right->red
					&& s->left->red) {
					s->red = true;
					s->left->red = false;
					rotateR(s);
				} else if (n == n->parent->right && !s->left->red
					&& s->right->red) {
					s->red = true;
					s->right->red = false;
					rotateL(s);
				}
			}
			delete6(n);
		}

		void delete6(node_pointer n)
		{
			node_pointer s = getS(n);

			s->red = n->parent->red;
			n->parent->red = false;

			if (n == n->parent->left) {
				s->right->red = false;
				rotateL(n->parent);
			} else {
				s->left->red = false;
				rotateR(n->parent);
			}
		}

		//////////////////
		// ** utils ** //
		//////////////////

		void replace(node_pointer n, node_pointer child)
		{
			child->parent = n->parent;
			if (n->parent->left == n)
				n->parent->left = child;
			else if (n->parent->right == n)
				n->parent->right = child;
		}

		bool isLeaf(node_pointer n) {
			
		}

		void initNode(node_pointer n, Value v) {
			n->_red = true;
			n->_left = 0;
			n->_right = 0;
			n->_parent = 0;
			n->_v = v;
		}

		template<class Key>
		void putNode(node_point n, Key &key) {
						node_pointer pos = recursiveTreeSearch(this->_root, v.first);

		}
		
		
		void clear() {
			
		}

};

template <class T>
class RBiter {
	private:
		Ptr _node;

		void increment() {
			if (_node->right) {
				Ptr tmp = _node->right;
				while (tmp->left)
					tmp = tmp->left;
				_node = tmp;
			} else {
				Ptr tmp = _node->parent;
				if (tmp->right = _node) {
					while (_node == tmp->right) {
						_node = tmp;
						tmp = tmp->parent;
					}
				}
				if (_node->right != tmp)
					_node = tmp;
			}
		}

		void decrement() {
			if (_node->parent->parent = _node && _node->_red)
				_node = _node->left;
			else if (_node->left) {
				while (_node->right)
					_node = _node->right;
			} else {
				Ptr parent = _node->parent;
				while (parent->left == _node) {
					_node = parent;
					parent = parent->parent;
				}
				_node = parent;
			}
		}

	public:
		typedef RBtree<T>*	Ptr;
		typedef RBiter<T> 	Iter;

		RBiter(Ptr n = 0) : _node(n) {} 

		T& operator*() {
			return (_node->v);
		}

		T* operator->() {
			return (_node);
		}

		Iter& operator++() {
			this->increment();
			return (*this);
		}

		Iter& operator++(int) {
			Iter tmp = this;
			this->increment();
			return (tmp);
		}

		Iter& operator--() {
			this->decrement();
			return (*this);
		}

		Iter& operator--(int) {
			Iter tmp = this;
			this->decrement();
			return (tmp);
		}

		bool operator==(const Iter& s) {
			return (_node == s._node);
		}

		bool operator!=(const Iter& s) {
			return (_node != s._node);
		}
};

};