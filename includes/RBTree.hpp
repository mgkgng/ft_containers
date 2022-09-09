#pragma once

#include "lib.hpp"
#include "pair.hpp"

template<class Value>
struct RBnode {
	RBnode*	parent;
	RBnode*	left;
	RBnode*	right;
	bool	red;
	Value	value;
	bool	empty;

	public:
		RBnode() : empty(true) {}
		RBnode(Value v) : red(true), left(0), right(0), parent(0), value(v), empty(false) {}

		RBnode *next() const {
			if (this->empty)
				return (NULL);

			if (this->right)
				return (this->right->min());

			if (this == this->parent->left)
				return (this->parent);
			
			RBnode *where;
			for (where = this->parent; where && where == where->parent->right; where = where->parent);
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

template <typename Value>
class RBiter {
	public:
		typedef RBnode<Value> node;

		explicit RBiter() : ptr(NULL) {} 

		Value& operator*() { return (ptr->value); }
		node* operator->() { return (ptr); }

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

		bool operator==(const RBiter& s) {
			return (ptr == s.ptr);
		}

		bool operator!=(const RBiter& s) {
			return (ptr != s.ptr);
		}
	
	protected:
		node	*ptr;
};

template<
    class Key,
    class T,
    class Compare = std::less<Key>,
    class Allocator = std::allocator<ft::pair<const Key, T> >
>
class RBtree {

	public:

		///////////////////////////
		// ** type definition ** //
		///////////////////////////ß
		typedef ft::pair<const Key, T>			 value_type;
		typedef RBnode<value_type>  			 node;
		typedef std::allocator<node>			 node_allocator;
		typedef unsigned int					 size_type;

		////////////////////////
		// ** Constructors ** //
		////////////////////////

		RBtree() : size(0) {
			nodeAlloc = node_allocator();
			root = nodeAlloc.allocate(1);
		}

		///////////////////////////////
		// ** principal functions ** //
		///////////////////////////////

		node *add(value_type &v) {
			node	*newNode = nodeAlloc.allocate(1);
			nodeAlloc.construct(newNode, RBnode<value_type>(v));

			node *where = search(v.first, this->root);
			if (where == this->root)
				this->root = newNode;
			else
				this->putNodePos(newNode, where);
			insert1(newNode);
			return (newNode);
		}

		void remove(Key &key) {
			node *n = this->search(key, root);
			if (!n)
				return ;
			node *child = (!n->right) ? n->left : n->right; // SUS
			this->replace(n, child);
			if (n && !n->red) { // SUS
				if (child->red)
					child->red = false;
				else
					delete1(child);
			}
			// nodeAlloc.destroy(n); as i don't construct anything for now
			nodeAlloc.deallocate(n, 1);
		}

		//////////////////
		// ** getter ** //
		//////////////////

		node *getRoot() {
			return (root);
		}

		//////////////////
		// ** search ** //
		//////////////////

		node *search(const Key &key, node *n) {
			if (!n || n->value.first == key)
				return (n);
			return (n->value.first < key) ? (this->search(key, n->left)) : (this->search(key, n->right));
		}

		//////////////////
		// ** insert ** //
		//////////////////

		void insert1(node *n)
		{
			if (!n->parent)
				n->red = false;
			else
				this->insert2(n);
		}

		void insert2(node *n)
		{
    		if (!n->parent->red)
				return;
			else
				this->insert3(n);
		}

		void insert3(node *n)
		{
			node *u = getU(n);
			if (u && u->red) {
				n->parent->red = false;
				u->red = false;
				node *gp = getGP(n);
				gp->red = true;
				this->insert1(gp);
			} else
				this->insert4(n);
		}

		void insert4(node *n)
		{
			node *gp = getGP(n);

			if (n == n->parent->right && n->parent == gp->left) {
				this->rotateL(n->parent);
				n = n->left;
			} else if (n == n->parent->left && n->parent == gp->right) {
				this->rotateR(n->parent);
				n = n->right;
			}
			this->insert5(n);
		}

		void insert5(node *n)
		{
			node *gp = this->getGP(n);

			n->parent->red = false;
			gp->red = true;
			(n == n->parent->left) ? this->rotateR(gp) : this->rotateL(gp);
		}

		//////////////////
		// ** rotate ** //
		//////////////////

		void rotateL(node *n)
		{
			node *c = n->right;
			node *p = n->parent;

			if (c->left)
				c->left->parent = n;

			n->right = c->left;
			n->parent = c;
			c->left = n;
			c->parent = p;

			if (p)
				(p->left == n) ? p->left = c : p->right = c;
		}

		void rotateR(node *n)
		{
			node *c = n->left;
			node *p = n->parent;

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

		void delete1(node *n)
		{
			if (n->parent)
				this->delete2(n);
		}

		void delete2(node *n)
		{
			node *s = getS(n);

			if (s->red) {
				n->parent->red = true;
				s->red = false;
				(n == n->parent->left) ? rotateL(n->parent) : rotateR(n->parent);
			}
			delete3(n);
		}

		void delete3(node *n)
		{
			node *s = getS(n);

			if (!n->parent->red && !s->red
				&& !s->left->red && !s->right->red) {
				s->red = true;
				delete1(n->parent);
			} else
				delete4(n);
		}

		void delete4(node *n)
		{
			node *s = getS(n);

			if (n->parent->red && !s->red
				&& !s->left->red && !s->right->red) {
				s->red = true;
				n->parent->red = false;
			} else
				delete5(n);
		}

		void delete5(node *n)
		{
			node *s = getS(n);

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

		void delete6(node *n)
		{
			node *s = getS(n);

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

		void replace(node *n, node *child)
		{
			child->parent = n->parent;
			if (n->parent->left == n)
				n->parent->left = child;
			else if (n->parent->right == n)
				n->parent->right = child;
		}

		void putNodePos(node *n, node *where) {
			n->parent = where->parent;
			(n == n->parent->left) ? n->parent->left = n : n->parent->right = n;
		}
		
		node *beginPtr() {
			node *l = root;
	
			while (l && l->left)
				l = l->left;
			return (l);
		}

		void eraseAll() {
			node *n = this->beginPtr();
			while (n) {
				node *next = n + 1;
				nodeAlloc.deallocate(n, 1);
				n = next;
				//* or could it work like this too? -> nodeAlloc.dealloc(n++, 1);
			}
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

	protected:
		node			*root;
		size_type		size;
		node_allocator	nodeAlloc;
		Compare			comp;

};