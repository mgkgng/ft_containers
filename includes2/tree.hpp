#pragma once

#include <memory>

#include "Iterator.hpp"

namespace ft {

template<typename T>
struct treeNode {
	treeNode	*parent;
	treeNode	*left;
	treeNode	*right;
	bool 		red;
	T			value;

	treeNode(T val = T(), bool col = true) : parent(NULL), left(NULL), right(NULL), red(col), value(val) {};

	treeNode *min() { return ((!this->left) ? this : this->left->min()); }
	treeNode *max() { return ((!this->right) ? this : this->right->max()); }

	treeNode *next() {
		if (this->right)
			return (this->right->min());
		if (this->parent && this == this->parent->left)
			return (this->parent);
		treeNode *where;
		for (where = this->parent; where && where->parent && where == where->parent->right; where = where->parent);
		return ((where) ? where->parent : NULL);
	}

	treeNode *prev() {
		if (this->left)
			return (this->left->max());
		if (this == this->parent->right)
			return (parent);

		treeNode *where;
		for (where = this->parent; where && where == where->parent->left; where = where->parent);
		return ((where) ? where->parent : NULL);
	}
};

template <typename T>
class IterTree {
	public:
		typedef T	value_type;
		typedef T&	reference;
		typedef T*	pointer;

		typedef ft::treeNode<T> 		node_type;
		typedef ft::treeNode<const T>	const_node_type;

		node_type	*nodePtr;
		node_type	*maxPtr;

		IterTree(): nodePtr(NULL), maxPtr(NULL) {}
		explicit IterTree(node_type *where, node_type *max): nodePtr(where), maxPtr(max) {}
		// IterTree(const_node_type *where, node_type *max): nodePtr(where), maxPtr(max) {}
		
		reference operator*() const { return (nodePtr->value); }
		pointer operator->() const { return (&(operator*())); }

    	operator IterTree<const_node_type>() const { return (this->nodePtr); }

		IterTree& operator=(IterTree const & other) {
			nodePtr = other.nodePtr;
			return (*this);
		}

		IterTree& operator++() {
			nodePtr = nodePtr->next();
			return (*this);
		}

		IterTree operator++(int) {
			IterTree tmp = *this;
			nodePtr = nodePtr->next();
			return (tmp);
		}

		IterTree& operator--() {
			nodePtr = ((!nodePtr) ? this->maxPtr : nodePtr->prev());
			return (*this);
		}

		IterTree operator--(int) {
			IterTree tmp = *this;
			nodePtr = nodePtr->prev();
			return (tmp);
		}

		bool operator==(const IterTree& s) { return (nodePtr == s.nodePtr); }
		bool operator!=(const IterTree& s) { return (nodePtr != s.nodePtr); }

		node_type *getNode() { return (nodePtr); }
};

template<typename Value, typename Compare>
class tree {
	public:
		typedef Value			value_type;
		typedef Compare			value_compare;
		typedef ptrdiff_t 		difference_type;
		typedef unsigned long	size_type;

		typedef treeNode<value_type>		node_type;
		typedef treeNode<const value_type>	const_node_type;
		typedef std::allocator<node_type>	allocator_type;

		typedef IterTree<value_type>		iterator;
		typedef IterTree<const value_type>	const_iterator;
		typedef ReverseIter<iterator> 		reverse_iterator;
		typedef ReverseIter<const_iterator> const_reverse_iterator;

		node_type		*root;
		size_type		size;
		allocator_type	nodeAlloc;
		value_compare	comp;

		explicit tree() {
			this->root = NULL;
			this->size = 0;
			this->nodeAlloc = allocator_type();
			this->comp = Compare();
		}

		tree(tree const & other) {
			this->root = other.root;
			this->size = other.size;
			this->nodeAlloc = other.nodeAlloc;
			this->comp = other.comp;
		}

		tree& operator=(const tree & other) {
			if (this->root)
				this->clearTree();
			this->nodeAlloc = other.nodeAlloc;
			this->comp = other.comp;
			this->root = NULL;
			if (!other.root)
				return (*this);
			for (iterator it = iterator((node_type *) other.min(), (node_type *) other.max()); it != iterator(NULL, (node_type *) other.max()); it++)
				this->add(*it);
			return (*this);
		}

		node_type *createNode(value_type v) {
			node_type *n = nodeAlloc.allocate(1);
			nodeAlloc.construct(n, v);
			return (n);
		}

		void deleteNode(node_type *n) {
			nodeAlloc.deallocate(n, 1);
		}

		bool isEqual(value_type v1, value_type v2) {
			return ((this->comp(v1, v2) && this->comp(v2, v1)) ? true : false);
		}

		node_type *add(value_type v) {
			if (this->search(v, this->root))
				return (NULL);
			node_type *n = createNode(v);
			insert(n);
			return (n);
		}

		void erase(node_type *n) {
			remove(n);
			deleteNode(n);
		}

		node_type *search(value_type v, node_type *where) {
			if (!where || isEqual(v, where->value))
				return (where);
			return ((!this->comp(where->value, v)) ? this->search(v, where->left) : this->search(v, where->right));
		}

		void clearTree() {
			destroyTree(this->root);
			this->root = NULL;
			this->size = 0;
		}

		void swapTree(tree &other) {
			node_type *tmpRoot = root;
			root = other.root;
			other.root = tmpRoot;

			size_type tmpSize = size;
			tmpSize = other.size;
			other.size = tmpSize;

			allocator_type tmpAlloc = nodeAlloc;
			nodeAlloc = other.nodeAlloc;
			other.nodeAlloc = tmpAlloc;

			value_compare tmpComp = comp;
			comp = other.comp;
			other.comp = tmpComp;
		}

		void printTree(node_type *n, bool left = false) {
			if (!n)
				return;

        	std::cout << ((left) ? "├──" : "└──" );
			std::cout << (!n->red ? "\033[1;90m" : "\033[1;31m") << n->value << "\033[0m" << std::endl;

        	printTree(((left) ? "│   " : "    "), n->left, true);
        	printTree(((left) ? "│   " : "    "), n->right, false);
		}

		node_type *max() { return ((!this->root) ? NULL : this->root->max()); }
		const_node_type *max() const { return ((!this->root) ? NULL : (const_node_type *) this->root->max()); }		
		node_type *min() { return ((!this->root) ? NULL : this->root->min()); }
		const_node_type *min() const { return ((!this->root) ? NULL : (const_node_type *) this->root->min()); }

		/* detailed implementation */
		void insert(node_type* n) {
			if (!this->root) {
				this->root = n;
				size++;
				return;
			}

			node_type *curr= this->root;
			while (1) {
				if (this->comp(curr->value, n->value)) {
					if (!curr->right) {
						n->parent= curr;
						curr->right= n;
						break;
					} else
						curr = curr->right;
				} else {
					if (!curr->left) {
						n->parent = curr;
						curr->left= n;
						break;
					} else
						curr = curr->left;
				}
			}
			adjustInsert(n);
			this->size++;
		}

		void adjustInsert(node_type *n) {
			node_type *p = n->parent;
			if (!p) {
				n->red = false;
				return ;
			}
			if (!p->red)
				return;
		
			node_type *u = getU(n);
			node_type *gp = getGP(n);
			if (p->red && (u && u->red)) {
				p->red = false;
				u->red = false;
				gp->red = true;
				adjustInsert(gp);
				return;
			}

			if (gp && p == gp->left) {
				if (n == p->right) {
					n = p;

					rotateL(p);
				}
				p->red = false;
				if (gp) {
					gp->red = true;
					rotateR(gp);
				}
				return;
			} else {
				if (n == p->left) {
					n = p;
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

		void rotateL(node_type *n)
		{
			if (!n || !n->right)
				return;

			node_type *rc = n->right ;
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

		void rotateR(node_type *n)
		{
			if (!n || !n->left)
				return;
			node_type *lc = n->left ;
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

		void remove(node_type *n){
			node_type *x, *y, *tmp;
			int yRed;

			y = n;
			yRed = n->red;
			tmp = NULL;

			if (!n->left && !n->right) {
				tmp = createNode(n->value);
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
					tmp = createNode(n->value);
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
				adjustRemove(x);
			
			if (tmp) {
				transplant(tmp, NULL);
				deleteNode(tmp);
			}
		}

		void adjustRemove(node_type *n){
			while (n != this->root && !n->red) {
				if (n == n->parent->left) {
					node_type *x = n->parent->right;
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
					node_type *x = n->parent->left;
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

		void transplant(node_type *n, node_type *child)
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

		void destroyTree(node_type *n) {
			if (!n)
				return ;
			destroyTree(n->left);
			destroyTree(n->right);
			deleteNode(n);
		}

		node_type *getGP(node_type *n) { return (n && n->parent) ? n->parent->parent : 0; }
		node_type *getS(node_type *n) { return (n == n->parent->left) ? n->parent->right : n->parent->left; }
		node_type *getU(node_type *n) {
			node_type *gp = getGP(n);
			if (!gp)
				return (NULL);
			return (n->parent == gp->left) ? gp->right : gp->left;
		}

};

// template <typename Value, typename Comp> 
// inline bool operator==(const tree<Value, Comp>& lhs, const tree<Value, Comp>& rhs) { return lhs.size == rhs.size && ft::equal(lhs.begin(), lhs.end(), rhs.begin()); }

// template <typename Value, typename Comp>
// inline bool operator!=(const tree<Value, Comp>& lhs, const tree<Value, Comp>& rhs) { return !(lhs == rhs); }

// template <typename Value, typename Comp>
// inline bool operator<(const tree<Value, Comp>& lhs, const tree<Value, Comp>& rhs) { return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); }

// template <typename Value, typename Comp>
// inline bool operator<=(const tree<Value, Comp>& lhs, const tree<Value, Comp>& rhs) { return !(rhs < lhs); }

// template <typename Value, typename Comp>
// inline bool operator>(const tree<Value, Comp>& lhs, const tree<Value, Comp>& rhs) { return rhs < lhs; }

// template <typename Value, typename Comp>
// inline bool operator>=(const tree<Value, Comp>& lhs, const tree<Value, Comp>& rhs) { return !(lhs < rhs); }

};