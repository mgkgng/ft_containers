#include <memory>

namespace ft {

template<typename T>
struct treeNode {
	typedef T value_type;

	node *parent;
	node *left;
	node *right
	bool red;
	T	value;

	node(T val = T(), bool col = true) : parent(NULL), left(NULL), right(NULL), red(col), value(val) {};
};

template <typename Node>
class IterTree {
	public:
		typedef Node node_type;
		typedef typename Node::value_type value_type;
		typedef value_type& reference;
		typedef value_type*	pointer;

		
		
		IterTree(): ptr(NULL) {}
		IterTree(Node *where): ptr(where) {}

		operator IterTree<Node<const value_type> >() const { return (this->ptr); }

		reference operator*() const { return (ptr->value); }
};

template<typename Value, typename Compare>
class tree {
	public:
		typedef Value	value_type;
		typedef treeNode<value_type>	node_type;
		typedef treeNode<const value_type> const_node_type;
		typedef std::allocator<node_type> allocator_type;
		typedef Compare	value_compare;
		typedef ptrdiff_t 		difference_type;
		typedef unsigned long	size_type;
		typedef NULL			nil;

		typedef IterTree<node_type>			iterator;
		typedef IterTree<const_node_type>	const_iterator;
		typedef ReverseIter<iterator> 				reverse_iterator;
		typedef ReverseIter<const_iterator> 		const_reverse_iterator;

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

		node_type *createNode(value_type v) {
			node_type *n = nodeAlloc.allocate(1);
			nodeAlloc.construct(n, v);
			return (n);
		}

		node_type *deleteNode(node *n) {
			nodeAlloc.deallocate(n, 1);
		}

		bool isEqual(value_type v1, value_type v2) {
			return ((this->comp(v1, v2) && this->comp(v2, v1)) ? true : false);
		}

		node_type *add(value_type v) {
			if (this->search(v, this->root))
				return (nil);
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
			node *p = n->parent;
			if (!p) {
				n->red = false;
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
				adjustInsert(gp);
				return;
			}
			if (p == gp->left) {
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

		void remove(node_type *n){
			node *x, *y, *tmp;
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
				fix(x);
			
			if (tmp) {
				transplant(tmp, NULL);
				deleteNode(tmp);
			}
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

};
};