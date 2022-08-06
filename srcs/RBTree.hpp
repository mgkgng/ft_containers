#pragma once

#define NIL 0
#define LEFT  0
#define RIGHT 1
#define left  child[LEFT]
#define right child[RIGHT]

namespace ft {

class RBnode {
	public: 
		RBnode	*parent;
		RBnode	*child[2];
		bool	red;
		int		key;

		RBnode(int key) {
			this->red = true;
			this->left = NIL;
			this->right = NIL;
			this->key = key;
		}
};

class RBtree {

	private:
		RBnode	*root;

	public:
		RBtree() : root(NIL) {}

		///////////////////////////////
		// ** principal functions ** //
		///////////////////////////////

		void add(RBnode* n) {
			// allocate...
			RBnode *pos = recursiveTreeSearch(_root, n->key);
			pos->insert1(n);
		}

		void remove(RBnode *n) {
			// deallocate...
		}

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
			if (!n || n->key == key)
				return (n);
			return (n->key < key) ? (recursiveTreeSearch(n->left, key)) : (recursiveTreeSearch(n->right, key));
		}

		//////////////////
		// ** insert ** //
		//////////////////

		void insert(RBnode *n) {
			RBnode *pos = recursiveTreeSearch(this->root, n->key);

			n->parent = pos->parent;
			insert1(n);
		}
		void insert1(RBnode *n)
		{
			if (!n->parent) this->root = n;
			else insert2(n);
		}

		void insert2(RBnode *n)
		{
    		if (!n->parent->red) return;
			else insert3(n);
		}

		void insert3(RBnode *n)
		{
			RBnode *u = getU(n);

			if (u && u->red) {
				n->parent->red = false;
				u->red = false;
				RBnode *gp = getGP(n);
				gp->red = true;
				insert1(gp);
			} else insert4(n);
		}

		void insert4(RBnode *n)
		{
			RBnode	*gp = getGP(n);

			if (n == n->parent->right && n->parent == gp->left) {
				rotateL(n->parent);
				n = n->left;
			} else if (n == n->parent->left && n->parent == gp->right) {
				rotateR(n->parent);
				n = n->right;
			}
			insert5(n);
		}

		void insert5(RBnode *n)
		{
			RBnode *gp = getGP(n);

			n->parent->red = false;
			gp->red = true;
			(n == n->parent->left) ? rotateR(gp) : rotateL(gp);
		}

		//////////////////
		// ** rotate ** //
		//////////////////

		void rotateL(RBnode *n)
		{
			RBnode	*c = n->right;
			RBnode	*p = n_>parent;

			if (c->left)
				c->left->parent = n;

			n->right = c->left;
			n->parent = c;
			c->left = n;
			c->parent = p;

			if (p)
				(p->left == this) ? p->left = c : p->right = c;
		}

		void rotateR()
		{
			RBnode	*c = n->left;
			RBnode	*p = n->parent;

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