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

		RBnode *getSibling()
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

}

class RBtree {

	private:
		RBnode	*root;

	public:
		RBtree() {
			
		}
}

}