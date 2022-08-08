#pragma once

#include "lib.hpp"
#include "pair.hpp"
#include "RBiter.hpp"

namespace ft {

template<class Value>
struct RBnode {
	RBnode*	parent;
	RBnode*	left;
	RBnode*	right;
	bool			red;
	Value			value;
};

template<class T, class Compare>
class RBtree {

	public:

		///////////////////////////
		// ** type definition ** //
		///////////////////////////

		typedef T						Value;
		typedef size_t					size_type;
		typedef ptrdiff_t				difference_type;
		typedef Compare					value_compare;

		typedef ft::RBnode<T>				node;
		typedef ft::RBnode<T>*				node_pointer;

		typedef typename ft::RBiter<Value>		iterator;

		///////////////////////////
		// ** Node structure ** //
		///////////////////////////



		////////////////////////
		// ** Constructors ** //
		////////////////////////

		explicit RBtree(const Compare &comp) {
			_root = 0;
			_size = 0;
			_nodeAlloc = std::allocator<RBnode>();
			_comp = comp;
		}

		///////////////////////////////
		// ** principal functions ** //
		///////////////////////////////

		void add(const Value &v, node_pointer where) {
			node_pointer n = _nodeAlloc.allocate(1);
			this->initNode(n, v);
			if (where)
				this->putNode(n, where);
			else // un truc comme ca
				this->_root = n;
			insert1(n);
			return (n);
		}

		template<class Key>
		void remove(Key &key) {
			node_pointer n = this->search(key);
			if (!n)
				return ;
			node_pointer child = (!n->right) ? n->left : n->right; // SUS
			this->replace(n, child);
			if (n && !n->red) { // SUS
				if (child->red)
					child->red = false;
				else
					delete1(child);
			}
			// _nodeAlloc.destroy(n); as i don't construct anything for now
			_nodeAlloc.deallocate(n, 1);
		}

		//////////////////
		// ** getter ** //
		//////////////////

		node_pointer getGP(node_pointer n) {
			return (n && n->parent) ? n->parent->parent : 0;
		}

		node_pointer getU(node_pointer n) {
			node_pointer gp = getGP(n);
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
		node_pointer search(node_pointer n, Key &key) {
			if (!n || n->v.first == key)
				return (n);
			return (n->v.first < key) ? (this->search(n->left, key)) : (this->search(n->right, key));
		}

		//////////////////
		// ** insert ** //
		//////////////////

		void insert1(node_pointer n)
		{
			if (!n->parent)
				n->_red = false;
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
			} else
				insert4(n);
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

		void initNode(node_pointer n, Value v) {
			n->red = true;
			n->left = 0;
			n->right = 0;
			n->parent = 0;
			n->value = v;
		}

		template<class Key>
		void putNode(node_pointer n, node_pointer where) {
			n->parent = where->parent;
			(n == n->parent->left) ? n->parent->left = n : n->parent->right = n;
		}
		
		void eraseAll() {
			node_pointer n = this->begin();
			while (n) {
				node_pointer next = n + 1;
				_nodeAlloc.deallocate(n, 1);
				n = next;
				//* or could it work like this too? -> _nodeAlloc.dealloc(n++, 1);
			}
		}

		void swap(RBtree &other) {
			node_pointer tmp = _root;
			_root = other._root;
			other._root = tmp;

			size_type tmp2 = _size;
			_size = other._size;
			other._size = tmp2;

			std::allocator<node> tmp3 = _nodeAlloc;
			_nodeAlloc = other._nodeAlloc;
			other._nodeAlloc = tmp3;

			value_compare tmp4 = _comp;
			_comp = other._comp;
			other._comp = tmp4;
		}

	private:
		node_pointer			_root;
		size_type				_size;
		std::allocator<node>	_nodeAlloc;
		value_compare			_comp;

};

};