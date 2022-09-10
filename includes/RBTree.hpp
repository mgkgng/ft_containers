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

		RBnode *min() { return ((!this->left) ? this : this->left->min()); }
		RBnode *max() { return ((!this->right) ? this : this->right->max()); }

		RBnode *next() {
			if (this->empty)
				return (NULL);
			if (this->right)
				return (this->right->min());
			if (this == this->parent->left)
				return (this->parent);
			RBnode *where = this->parent;
			for (where = this->parent; where && where->parent && where == where->parent->right; where = where->parent);
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
		typedef typename Node::value_type* pointer;			
		

		explicit RBiter() : ptr(NULL) {} 
		RBiter(Node *where) : ptr(where) {}

		reference operator*() { return (ptr->value); }
		pointer operator->() { return (&ptr->value); }

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

		Node *getPtr() const {
			return (ptr);
		}
	
	protected:
		Node	*ptr;
};

template<
	class Key,
    class Value,
    class Compare = std::less<Key>
>
class RBtree {

	public:

		///////////////////////////
		// ** type definition ** //
		///////////////////////////
		typedef Key						key_type;
		typedef Value					value_type;
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

		void erase(key_type k) {
			node *n = search(k, this->root);
			if (!n)
				return ;
			remove(n);
		}

		node *search(const key_type &key, node *n) {
			if (!n || n->value.first == key)
				return (n);
			return (!comp(n->value.first, key)) ? (this->search(key, n->left)) : (this->search(key, n->right));
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

		void rotateL(node *n)
		{
			node *rc = n->right ;
			n->right = rc->left;

			if (n->right)
				n->right->parent = n;
			
			if (!n->parent)
				this->root = rc;
			else if (n == n->parent->left)
				n->parent->left = rc;
			else
				n->parent->right = rc;	

			rc->parent = n->parent ;
			n->parent = rc;
			rc->left = n;
		}

		node* getSuccessor(node *n) {
			if (n->right)
				return (n->right->min());

			node* x = n->parent;
			while (x && n == x->right) {
				n = x;
				x = x->parent;
			}
			return (x);
		}

		// void remove(node *n){
		// 	node *x, y;
	
		// 	if (!n->left || !n->right)
		// 		y = n;
		// 	else
		// 		y = getSuccessor(n);
	
		// 	if (y->left)
		// 		x = y->left;
		// 	else
		// 		x = y->right;
		// 	x->parent = y->parent;
		// 	if (!y->parent)
		// 		this->root = x;
		// 	else {
		// 		if (y == y->parent->left)
		// 			y->parent->left = x;
		// 		else
		// 			y->parent->right = x;
		// 	}
		// 	if (y != n)
		// 		n->key = y->key;
		// 	if (!y->red)
		// 		rbDeleteFixup(x);
		// 	delete y;
		// }

		void fix(node *n){
			while (n != this->root && !n->red){
				if (n == n->parent->left) {
					node *x = n->parent->right;
					if (x->red) {
						x->red = false;
						n->parent->red = true;
						rotateL(n->parent);
						x = n->parent->right;
					}
					if (!x->left->red && !x->right->red) {
						x->red = true;
						n = n->parent;
					} else {
						if(x->right->red == false) {
							x->left->red = false;
							x->red = true;
							rotateR(x);
							x = n->parent->right;
						}
						x->red = n->parent->red;
						n->parent->red = false;
						x->right->red = false;
						rotateL(n->parent);
						n = root;
					}
				} else {
					node *x = n->parent->left;
					if (x->red) {
						x->red = false;
						n->parent->red = true;
						rotateR(n->parent);
						x = n->parent->left;
					}
					if (!x->right->red && !x->left->red) {
						x->red = true;
						n = n->parent;
					} else {
						if(x->left->red == false) {
							x->right->red = false;
							x->red = true;
							rotateL(x);
							x = n->parent->left;
						}
						x->red = n->parent->red;
						n->parent->red = false;
						x->left->red = false;
						rotateR(n->parent);
						n = this->root;
					}
				}
			}
			n->red = false;
		}

		void remove(node *n){
			node *x, *y;
			int yRed;

			y = n;
			yRed = n->red;

			if (!n->left) {
				x = n->right;
				transplant(n, n->right);
			} else if(!n->right){
				x = n->left;
				transplant(n, n->left);
			} else {
				y = n->right->min();
				yRed = y->red;

				x = y->right;

				if (y->parent == n)
					x->parent = y;
				else {
					transplant(y, y->right);
					y->right = n->right;
					y->right->parent = y;
				}
				transplant(n, y);
				y->left = n->left;
				y->left->parent = y;
				y->red = n->red;
			}
			if (!yRed)
				fix(x);

			nodeAlloc.destroy(n);
			nodeAlloc.deallocate(n, 1);
		}

		// void fix(node *n){
		// 	node *x;	

		// 	while (n != this->root && !n->red) {
		// 		if (n == n->parent->left){
		// 			x = n->parent->right;
		// 			if (x->red) {
		// 				x->red = false;
		// 				n->parent->red = true;
		// 				rotateL(n->parent);
		// 				x = n->parent->right;
		// 			}

		// 			if(!x->left->red && !x->right->red){
		// 				x->red = true;
		// 				n->parent->red = false;
		// 				n = n->parent;
		// 			} else {
		// 				if (!x->right->red) {
		// 					x->red = true;
		// 					x->left->red = false;
		// 					rotateR(x);
		// 					x = n->parent->right;
		// 				}
		// 				x->red = n->parent->red;
		// 				n->parent->red = false;
		// 				n->right->red = false;
		// 				rotateL(n->parent);
		// 				n = this->root;		
		// 			}
		// 		} else {
		// 			x = n->parent->left;
		// 			if (x->red) {
		// 				x->red = false;
		// 				n->parent->red = false;
		// 				rotateR(n->parent);
		// 				x = n->parent->left;
		// 			}

		// 			if (!x->left->red && !x->right->red){
		// 				x->red = true;
		// 				n->parent->red = false;
		// 				n = n->parent;
		// 			} else {
		// 				if (!x->left->red) {
		// 					x->red = true;
		// 					x->right->red = false;
		// 					rotateL(x);
		// 					x = n->parent->left;
		// 				}
		// 				x->red = n->parent->red;
		// 				n->parent->red = false;
		// 				x->left->red = false;
		// 				rotateR(n->parent);
		// 				n = this->root;
		// 			}
		// 		}
		// 	}
		// 	n->red = false;
		// }

		void rotateR(node *n)
		{
			node *lc = n->left ;
			n->left = lc->right;

			if (n->left)
				n->left->parent = n;
			
			if (!n->parent)
				this->root = lc;
			else if (n == n->parent->left)
				n->parent->left = lc;
			else
				n->parent->right = lc;	

			lc->parent = n->parent ;
			n->parent = lc;
			lc->right = n;
		}

		void clear() {
			for (iterator it = begin(); it != end(); it++) {
				nodeAlloc.destroy(it.getPtr());
				//nodeAlloc.deallocate(it.getPtr(), 1);
			}
			this->root = NULL;
			this->size = 0;
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

		node *getRoot() {
			return (root);
		}

		void transplant(node *n, node *child)
		{
			if (!n->parent)
				this->root = child;
			else if (n == n->parent->left)
				n->parent->left = child;
			else
				n->parent->right = child;
			child->parent = n->parent;
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

		iterator max()  { return (!this->root) ? end() : iterator(this->root->max()); }
		iterator min()  { return (!this->root) ? end() : iterator(this->root->min()); }
		iterator begin() { return (this->min()); }
		iterator end() 	{ return iterator(); }
		size_t max_size() const {
			return (nodeAlloc.max_size());
		}

	protected:
		node			*root;
		size_type		size;
		node_allocator	nodeAlloc;
		Compare			comp;

		friend class map;

};