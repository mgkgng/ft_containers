#define NIL   NULL
#define LEFT  0
#define RIGHT 1
#define _left  _child[LEFT]
#define _right _child[RIGHT]

enum Color {BLACK, RED};

namespace ft {

class RBnode {
	private:
		RBnode	*_parent;
		RBnode	*_child[2]
		Color	_color;

	public:
		RBnode();

		//////////////////
		// ** getter ** //
		//////////////////

		RBnode	*getGP() {
			if (_parent)
				return (_parent->_parent);
			return (NULL);
		}

		RBnode	*getU() {
			RBnode	*gp = getGP();
			if (!gp)
				return (NULL);
			if (_parent == gp->_left)
				return (gp->_right);
			return (gp->_left);
		}

		RBnode *getS()
		{
			if (this == _parent->_left)
				return (_parent->_right);
			return (_parent->_left);
		}

		//////////////////
		// ** insert ** //
		//////////////////

		void insert1()
		{
			(!_parent) ? _color = BLACK : insert2();
		}

		void insert2()
		{
    		(_parent->_color == BLACK) ? return ; : insert3();
		}

		void insert3()
		{
			RBnode *u = getU(n);

			if (u && (u->_color == RED)) {
				_parent->_color = BLACK;
				u->_color = BLACK;
				RBnode *gp = getGP();
				gp->_color = RED;
				gp.insert1();
			} else
				insert4();
		}

		void insert4()
		{
			RBnode	*gp = getGP();

			if ((this == _parent->_right) && (_parent == gp->_left)) {
				_parent->rotateL();
				this = _left;
			} else if ((this == _parent->_left) && (_parent == gp->_right)) {
				_parent->rotateR();
				this = _right;
			}
			insert5();
		}

		void insert5()
		{
			RBnode *gp = getGP;

			_parent->color = BLACK;
			gp->color = RED;
			(this == _parent->left) ? gp.rotateR() : gp.rotateL();
		}

		//////////////////
		// ** rotate ** //
		//////////////////

		void rotateL()
		{
			RBnode	*c = _right;
			RBnode	*p = _parent;

			if (c->_left != NULL)
				c->_left->_parent = this;

			_right = c->left;
			_parent = c;
			c->_left = this;
			c->_parent = p;

			if (p)
				(p->left == this) ? p->left = c : p->right = c;
		}

		void rotateR()
		{
			RBnode	*c = _left;
			RBnode	*p = _parent;

			if (c->_right != NULL)
				c->_right->_parent = this;

			_left = c->_right;
			_parent = c;
			c->_right = this;
			c->_parent = p;

			if (p)
				(p->right == this) ? p->right = c : p->left = c;
		}

		//////////////////
		// ** delete ** //
		//////////////////

		void delete_one_child()
		{
			RBnode *child = (_right == LEAF) ? _left: _right;

			replace_node(child);
			if (_color == BLACK)
				(child->color == RED) ? child->color = BLACK : delete_case1(child);
			free(this);
		}

		void delete1()
		{
			if (_parent)
				delete2();
		}

		void delete2()
		{
			RBnode *s = getS();

			if (s->_color == RED) {
				_parent->_color = RED;
				s->_color = BLACK;
				if (this == _parent->left)
					_parent->rotateL();
				else
					_parent->rotateR();
			}
			delete3();
		}

		void delete3()
		{
			RBnode *s = getS();

			if (_parent->_color == BLACK && s->_color == BLACK
				&& s->_left->_color == BLACK && s->_right->_color == BLACK) {
				s->_color = RED;
				_parent->delete1();
			} else
				delete4();
		}

		void delete4(struct node *n)
		{
			RBnode *s = getS(n);

			if (_parent->_color == RED && s->_color == BLACK
				&& s->_left->_color == BLACK && s->_right->_color == BLACK) {
				s->_color = RED;
				_parent->_color = BLACK;
			} else
				delete5();
		}

		void delete5()
		{
			RBnode *s = getS();

			if  (s->_color == BLACK) {
				if (this == _parent->_left && s->_right->_color == BLACK
					&& s->_left->_color == RED) { /* this last test is trivial too due to cases 2-4. */
					s->_color = RED;
					s->_left->_color = BLACK;
					s->rotateR();
				} else if (this == _parent->_right && s->_left->_color == BLACK
					&& s->_right->_color == RED) {/* this last test is trivial too due to cases 2-4. */
					s->_color = RED;
					s->_right->+color = BLACK;
					s->rotateL();
				}
			}
			delete6();
		}

		void delete6()
		{
			RBnode *s = getS();

			s->_color = _parent->_color;
			_parent->_color = BLACK;

			if (this == _parent->_left) {
				s->_right->_color = BLACK;
				rotateL(_parent);
			} else {
				s->_left->_color = BLACK;
				rotateR(_parent);
			}
		}

		//////////////////
		// ** utils ** //
		//////////////////

		void replace(RBnode *n, RBnode *child)
		{
			child->_parent = n->_parent;
			if (n->_parent->_left == n)
				n->_parent->_left = child;
			else if (n->_parent->_right == n)
				n->_parent->_right = child;
		}
};

class RBtree {

	private:
		RBnode	*root;

	public:
		RBtree() {
			
		}
}

}