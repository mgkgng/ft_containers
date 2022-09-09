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
		typedef Value value_type;

		RBnode() : red(true), left(0), right(0), parent(0), value(Value()), empty(true) {}
		RBnode(Value v) : red(true), left(0), right(0), parent(0), value(v), empty(false) {}

		RBnode *min() {
			// else
			// 	// std::cout << "no left!" << std::endl;
			// if (this->right)
			// 	std::cout << this->right->value.first << std::endl;

			RBnode* test = (!this->left) ? this : this->left->min();
			return ((!this->left) ? this : this->left->min());
		}

		RBnode *max() {
			return ((!this->right) ? this : this->right->max());
		}

		RBnode *next() {
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

		RBnode *prev() {
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

		typedef typename Node::value_type& reference;			

		explicit RBiter() : ptr(NULL) {} 
		RBiter(Node *where) : ptr(where) {}

		reference operator*() { return (ptr->value); }
		Node* operator->() { return (ptr); }

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
		Node	*ptr;
};

template<
    class Key,
    class T,
    class Compare = std::less<Key>
>
class RBtree {

	public:

		///////////////////////////
		// ** type definition ** //
		///////////////////////////ß
		typedef ft::pair<const Key, T>	value_type;
		typedef RBnode<value_type>		node;
		typedef RBiter<node>			iterator;
		typedef std::allocator<node>	node_allocator;
		typedef unsigned int			size_type;

		////////////////////////
		// ** Constructors ** //
		////////////////////////

		RBtree() : root(NULL), size(0) {
			nodeAlloc = node_allocator();
			comp = Compare();
		}

		///////////////////////////////
		// ** principal functions ** //
		///////////////////////////////

		node *add(value_type v) {
			node	*newNode = nodeAlloc.allocate(1);
			nodeAlloc.construct(newNode, RBnode<value_type>(v));

			insert(newNode);
			adjust(newNode);
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

		void insert(node* newNode) {
			if (!this->root) {
				this->root = newNode;
				size++;
				return;
			}

			node *curr= this->root;
			while (1) {
				if (this->comp(curr->value.first, newNode->value.first)) {
					if (!curr->right) {
						newNode->parent= curr;
						curr->right= newNode;
						break;
					} else
						curr = curr->right;
				} else {
					if (!curr->left) {
						newNode->parent = curr;
						curr->left= newNode;
						break;
					} else
						curr = curr->left;
				}
			}
			size++;
		}

		void adjust(node *newNode) {
			node *p = newNode->parent;

			//Case 1: Root node
			if (!p) {
				// std::cout << "111111" << std::endl;
				newNode->red = false;
				return ;
			}

			//Case 2: Parent is BLACK
			if (!p->red) {
				// std::cout << "222222" << std::endl;
				return;
			}
			
			node *u = getU(newNode);
			node *gp = getGP(newNode);

			//Case 3: Parent and Uncle are RED
			if (p->red && (u && u->red)) {
				p->red = false;
				u->red = false;
				gp->red = true;
				adjust(gp);
				// std::cout << "3333333" << std::endl;
				return;
			}

			//Case 4: Parent is Red and Uncle is Black(Or NULL)
			//If parent is left son
			if (p == gp->left) {
				if (newNode == p->right) {
					newNode = p;
					rotateL(p);
				}
				p->red = false;
				if (gp) {
					gp->red = true;
					rotateR(gp);
				}
				// std::cout << "4444444" << std::endl;
				return;
			} else {
				if (newNode == p->left) {
					newNode = p;
					rotateR(p);
				}
				p->red = false;
				if (gp) {
					gp->red = true;
					rotateL(gp);
				}
				// std::cout << "555555" << std::endl;
				return;
			}
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
			std::cout << "what?" << where << std::endl;
			n->parent = where->parent;
			std::cout << "why?" << std::endl;
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

		iterator max()  { return (this->root->empty) ? end() : iterator(this->root->max()); }
		iterator min()  { return (this->root->empty) ? end() : iterator(this->root->min());	}
		iterator begin() { return this->min(); }
		iterator end() 	{ return iterator(); }


	protected:
		node			*root;
		size_type		size;
		node_allocator	nodeAlloc;
		Compare			comp;

};