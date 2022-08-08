#pragma once

template<class T>
class RBtree;

namespace ft {

template <class T>
class RBiter {
	private:
		Ptr _node;

		void increment() {
			if (_node->right) {
				Ptr tmp = _node->right;
				while (tmp->left)
					tmp = tmp->left;
				_node = tmp;
			} else {
				Ptr tmp = _node->parent;
				if (tmp->right == _node) {
					while (_node == tmp->right) {
						_node = tmp;
						tmp = tmp->parent;
					}
				}
				if (_node->right != tmp)
					_node = tmp;
			}
		}

		void decrement() {
			if (_node->parent->parent = _node && _node->_red)
				_node = _node->left;
			else if (_node->left) {
				while (_node->right)
					_node = _node->right;
			} else {
				Ptr parent = _node->parent;
				while (parent->left == _node) {
					_node = parent;
					parent = parent->parent;
				}
				_node = parent;
			}
		}

	public:
		typedef RBtree<T>*	Ptr;
		typedef RBiter<T> 	Iter;

		RBiter(Ptr n = 0) : _node(n) {} 

		T& operator*() {
			return (_node->v);
		}

		T* operator->() {
			return (&_node->v);
		}

		Iter& operator++() {
			this->increment();
			return (*this);
		}

		Iter& operator++(int) {
			Iter tmp = this;
			this->increment();
			return (tmp);
		}

		Iter& operator--() {
			this->decrement();
			return (*this);
		}

		Iter& operator--(int) {
			Iter tmp = this;
			this->decrement();
			return (tmp);
		}

		bool operator==(const Iter& s) {
			return (_node == s._node);
		}

		bool operator!=(const Iter& s) {
			return (_node != s._node);
		}
};
};