#pragma once

#define NIL 0
#define LEFT  0
#define RIGHT 1
#define left  child[LEFT]
#define right child[RIGHT]

namespace ft {

struct RBnode {
	RBnode	*parent;
	RBnode	*child[2];
	bool	red;
	int		key;
};

class RBtree {

	private:
		RBnode	*root;

	public:
		RBtree() : root(NIL) {}

		//////////////////
		// ** getter ** //
		//////////////////

		RBnode	*getGP(RBnode *n) {
			return (n && n->parent) ? n->parent->parent : 0;
		}

		RBnode	*getU(RBnode *n) {
			RBnode	*gp = getGP(n);
			if (!gp)
				return (0);
			return (n->parent == gp->left) ? gp->right : gp->left;
		}

		RBnode *getS(RBnode *n)
		{
			return (n == n->parent->left) ? n->parent->right : n->parent->left;
		}

		//////////////////
		// ** search ** //
		//////////////////
		RBnode *recursiveTreeSearch(RBnode *n, int key) {
			if (!root || root->key ==  key)
				return (root);
			if (root->key < key)
				return (recursiveTreeSearch(n->left, key));
			else
				return (recursiveTreeSearch(n->right,  key));
		}

		//////////////////
		// ** insert ** //
		//////////////////

		void insert(RBnode *n) {
			RBnode *pos = recursiveTreeSearch(this->root, n->key);
			n->red = true;
			n->left = NIL;
			n->right = NIL;
			n->parent = pos->p;
			insert1(n);
		}
		void insert1(RBnode *n)
		{
			if (!n->parent) this->root = n;
			else insert2();
		}

		void insert2(RBnode *n)
		{
    		if (!parent->red) return;
			else insert3();
		}

		void insert3(RBnode *n)
		{
			RBnode *u = getU();

			if (u && u->red) {
				parent->red = false;
				u->red = false;
				RBnode *gp = getGP();
				gp->red = true;
				gp->insert1();
			} else insert4();
		}

		void insert4(RBnode *n)
		{
			RBnode	*gp = getGP();

			if (this == parent->right && parent == gp->left) {
				parent->rotateL();
				this = left;
			} else if (this == parent->left && parent == gp->right) {
				parent->rotateR();
				this = right;
			}
			insert5();
		}

		void insert5(RBnode *n)
		{
			RBnode *gp = getGP();

			parent->red = false;
			gp->red = true;
			(this == parent->left) ? gp->rotateR() : gp->rotateL();
		}

		//////////////////
		// ** rotate ** //
		//////////////////

		void rotateL()
		{
			RBnode	*c = right;
			RBnode	*p = parent;

			if (c->left)
				c->left->parent = this;

			right = c->left;
			parent = c;
			c->left = this;
			c->parent = p;

			if (p)
				(p->left == this) ? p->left = c : p->right = c;
		}

		void rotateR()
		{
			RBnode	*c = left;
			RBnode	*p = parent;

			if (c->right)
				c->right->parent = this;

			left = c->right;
			parent = c;
			c->right = this;
			c->parent = p;

			if (p)
				(p->right == this) ? p->right = c : p->left = c;
		}

		//////////////////
		// ** delete ** //
		//////////////////

		void delete_one_child()
		{
			RBnode *child = (right->isNil()) ? left: right;

			replace(this, child);
			if (!red) {
				if (child->red) child->red = false;
				else child->delete1();
			}
			//free(this);
		}

		void delete1()
		{
			if (parent)
				delete2();
		}

		void delete2()
		{
			RBnode *s = getS();

			if (s->red) {
				parent->red = true;
				s->red = false;
				(this == parent->left) ? parent->rotateL() : parent->rotateR();
			}
			delete3();
		}

		void delete3()
		{
			RBnode *s = getS();

			if (!parent->red && !s->red
				&& !s->left->red && !s->right->red) {
				s->red = true;
				parent->delete1();
			} else
				delete4();
		}

		void delete4()
		{
			RBnode *s = getS();

			if (parent->red && !s->red
				&& !s->left->red && !s->right->red) {
				s->red = true;
				parent->red = false;
			} else
				delete5();
		}

		void delete5()
		{
			RBnode *s = getS();

			if  (!s->red) {
				if (this == parent->left && !s->right->red
					&& s->left->red) { /* this last test is trivial too due to cases 2-4. */
					s->red = true;
					s->left->red = false;
					s->rotateR();
				} else if (this == parent->right && !s->left->red
					&& s->right->red) {/* this last test is trivial too due to cases 2-4. */
					s->red = true;
					s->right->red = false;
					s->rotateL();
				}
			}
			delete6();
		}

		void delete6()
		{
			RBnode *s = getS();

			s->red = parent->red;
			parent->red = false;

			if (this == parent->left) {
				s->right->red = false;
				parent->rotateL();
			} else {
				s->left->red = false;
				parent->rotateR();
			}
		}

		//////////////////
		// ** utils ** //
		//////////////////

		void replace(RBnode *n, RBnode *child)
		{
			child->parent = n->parent;
			if (n->parent->left == n)
				n->parent->left = child;
			else if (n->parent->right == n)
				n->parent->right = child;
		}

		bool isLeaf(RBnode *n) {
			
		}
};

};