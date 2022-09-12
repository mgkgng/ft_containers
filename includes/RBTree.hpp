#pragma once

#include "lib.hpp"
#include "pair.hpp"
#include <unistd.h>

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

template <typename Node>
class const_RBiter {
	public:
		typedef typename Node::value_type value_type;
		typedef value_type const & reference;
		typedef value_type const * pointer;
		typedef ptrdiff_t difference_type;

		const_RBiter() : ptr(NULL) {} 
		explicit const_RBiter(Node *where) { this->ptr = where; }

		reference operator*() const { return (ptr->value); }
		pointer operator->() const { return (&(operator*())); }

		const_RBiter& operator++() {
			ptr = ptr->next();
			return (*this);
		}

		const_RBiter operator++(int) {
			const_RBiter tmp = *this;
			ptr = ptr->next();
			return (tmp);
		}

		const_RBiter& operator=(const_RBiter const & other) {
			ptr = other.ptr;
			return (*this);
		}

		const_RBiter& operator--() {
			ptr = ptr->prev();
			return (*this);
		}

		const_RBiter operator--(int) {
			const_RBiter tmp = *this;
			ptr = ptr->prev();
			return (tmp);
		}

		bool operator==(const const_RBiter& s) { return (ptr == s.ptr); }
		bool operator!=(const const_RBiter& s) { return (ptr != s.ptr); }

		Node *getNode() { return (ptr); }
	
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
		typedef const_RBiter<node>		const_iterator;
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

		void insert(node* newNode) {
			if (!this->root) {
				this->root = newNode;
				size++;
				return;
			}

			node *curr= this->root;
			while (1) {
				if (this->comp(curr->value, newNode->value)) {
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
			adjust(curr);
		}

		void adjust(node *newNode) {
			node *p = newNode->parent;

			if (!p) {
				newNode->red = false;
				return ;
			}

			if (!p->red)
				return;
			
			node *u = getU(newNode);
			node *gp = getGP(newNode);

			if (p->red && (u && u->red)) {
				p->red = false;
				u->red = false;
				gp->red = true;
				adjust(gp);
				return;
			}

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
				return;
			}
		}

		void rotateL(node *n)
		{
			if (!n || !n->right)
				return;

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

		bool remove(node *n){
			node *x, *y, *tmp;
			int yRed;

			y = n;
			yRed = n->red;
			tmp = NULL;

			if (!n->left && !n->right) {
				tmp = addNode(n->value);
				tmp->red = false;
				transplant(n, tmp);
				x = tmp;
			} else if (!n->left) {
				x = n->right;
				transplant(n, n->right);
			} else if (!n->right){
				x = n->left;
				transplant(n, n->left);
			} else {
				y = n->prev();
				x = y->left;
				if (!x) {
					tmp = addNode(n->value);
					tmp->red = false;
					tmp->parent = y;
					y->left = tmp;
					x = tmp;
				}
				yRed = y->red;
				if (y->parent != n) {
					transplant(y, x);
					y->left = n->left;
					if (y->left)
						y->left->parent = y;
				}
				transplant(n, y);
				y->red = n->red;
				y->right = n->right;
				if (y->right)
					y->right->parent = y;
			}

			if (!yRed)
				fix(x);
			
			if (tmp) {
				transplant(tmp, NULL);
				deleteNode(tmp);
			}

			deleteNode(n);
			return (true);
		}

		void fix(node *n){
			while (n != this->root && !n->red) {
				if (n == n->parent->left) {
					node *x = n->parent->right;
					if (x && x->red) {
						x->red = false;
						n->parent->red = true;
						rotateL(n->parent);
						x = n->parent->right;
					}
					if (x && (!x->left || !x->left->red) && (!x->right || !x->right->red)) {
						x->red = true;
						n = n->parent;
					} else {
						if (x && (!x->right || !x->right->red)) {
							if (x->left)
								x->left->red = false;
							x->red = true;
							rotateR(x);
							x = n->parent->right;
						}
						if (x) {
							x->red = n->parent->red;
							x->right->red = false;
						}
						n->parent->red = false;
						rotateL(n->parent);
						n = root;
					}
				} else {
					node *x = n->parent->left;
					if (x && x->red) {
						x->red = false;
						n->parent->red = true;
						rotateR(n->parent);
						x = n->parent->left;
					}
					if (x && (!x->right || !x->right->red) && (!x->left || !x->left->red)) {
						x->red = true;
						n = n->parent;
					} else {
						if (!x->left->red) {
							x->right->red = false;
							x->red = true;
							rotateL(x);
							x = n->parent->left;
						}
						if (x) {
							x->red = n->parent->red;
							x->left->red = false;
						}
						n->parent->red = false;
						rotateR(n->parent);
						n = this->root;
					}
				}
			}
			n->red = false;
		}

		void rotateR(node *n)
		{
			if (!n || !n->left)
				return;
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

		iterator begin() const { return this->min(); }
		iterator end() const { return iterator(); }
		size_t max_size() const { return (nodeAlloc.max_size()); }

		size_type		size;
		node			*root;

	protected:
		node_allocator	nodeAlloc;
		Compare			comp;

		friend class map;

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