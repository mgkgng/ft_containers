#pragma once

#include "RBTree.hpp"
#include "Iterator.hpp"

namespace ft {

template<
    class Key,
    class T,
    class Compare = std::less<Key>,
    class Allocator = std::allocator<ft::pair<const Key, T> >
>
class map {



		map() {
			compK = Compare();
			compV = value_compare(compK);
			allocator = Allocator();
			tree = tree_type();
		}
		
		explicit map(const Compare& comp, const Allocator& alloc = Allocator()) { // cppreference(2)
			compK = comp;
			compV = value_compare(compK);
			allocator = alloc;
			tree = tree_type();
		}

		template<class InputIt>
		map(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator()) { // cppreference(4)
			// Constructs the container with the contents of the range [first, last).
			// If multiple elements in the range have keys that compare equivalent, it is unspecified which element is inserted.
			compK = comp;
			compV = value_compare(compK);
			allocator = alloc;
			tree = tree_type();
			while (first != last)
				this->tree.add(*first++);
		}

		map(const map& other) { *this = other; }
		~map() {}

		map& operator=(const map& other) {
			tree = other.tree;
			compK = other.compK;
			allocator = other.allocator;
			compV = value_compare(other.compV);
			return (*this);
		}

		allocator_type get_allocator() const {
			return (allocator);
		}

		//////////////////////////
		// ** Element access ** //
		//////////////////////////

		T& at(const Key& key) { return ((this->find(key))->second); }
		const T& at(const Key& key) const { return ((this->find(key))->second); }

		T& operator[](const Key& key) {
			iterator it = this->find(key); // DES FOIS CA MARCHE PAS
			if (it != this->end())
				return (it->second);
			node* newNode = tree.add(ft::make_pair(key, T()));
			return (newNode->value.second);

		}

		/////////////////////
		// ** Iterators ** //
		/////////////////////

		iterator begin() { return iterator(this->tree.min()); }
		const_iterator begin() const { return const_iterator(this->tree.min()); }
		iterator end() { return iterator(); }
		const_iterator end() const { return const_iterator(); }
		reverse_iterator rbegin() { return reverse_iterator(this->tree.end()); }
		const_reverse_iterator rbegin() const { return reverse_iterator(this->tree.end()); }
		reverse_iterator rend() { return reverse_iterator(this->tree.begin()); }
		const_reverse_iterator rend() const { return reverse_iterator(this->tree.begin()); }

		////////////////////
		// ** Capacity ** //
		////////////////////

		bool empty() const { return ((tree.getSize()) ? false : true); }
		size_type size() const { return (tree.getSize()); }
		size_type max_size() const { return (tree.max_size()); }

		////////////////////
		// ** Modifier ** //
		////////////////////

		void clear() { tree.clear(); }

		ft::pair<iterator, bool> insert(const value_type& value) {
			node *pos = tree.search(value, tree.getRoot());
			if (pos)
				return (ft::make_pair<iterator, bool>(iterator(pos), false));
			node *where = tree.add(value);
			return (ft::make_pair<iterator, bool>(iterator(where), true));
		}

		iterator insert(iterator hint, const value_type& value) {
			node *pos = tree.search(value, hint.getNode());
			if (pos)
				return (iterator(pos)); //TODO LET'S CHECK IT LATER
			node *where = tree.add(value);
			return (iterator(where));
		}

		template<class InputIt>
		void insert(InputIt first, InputIt last) {
			while (first != last)
				tree.add(*first++);
		}

		void erase(iterator pos) {
			tree.remove(pos.getNode());
			tree.size--;
		}

		void erase(iterator first, iterator last) {
			while (first != last) {
				tree.erase(first++.getNode());
				tree.size--;
			}
		}

		size_type erase(const Key& key) {
			node *where = tree.root;
			while (1) {
				if (!where || where->value.first == key)
					break;
				where = (!compK(where->value.first, key)) ? where->left : where->right;
			}
			bool res = tree.erase(where);
			if (res)
				tree.size--;
			return (res);
		}

		void swap(map &other) {
			tree.swap(other.tree);
			
			key_compare tmp = compK;
			compK = other.compK;
			other.compK = tmp;
			allocator_type tmp2 = allocator;
			allocator = other.allocator;
			other.allocator = tmp2;
			value_compare tmp3 = compV;
			compV = other.compV;
			other.compV = tmp3;
		}

		//////////////////
		// ** Lookup ** //
		//////////////////

		size_type count(const Key& key) const {
			node *where = tree.root;
			while (1) {
				if (!where)
					return (0);
				if (where->value.first == key)
					return (1);
				where = (!compK(where->value.first, key)) ? where->left : where->right;
			}
		}

		iterator find(const Key& key) {
			node *where = tree.getRoot();
			while (1) {
				if (!where || where->value.first == key)
					return (iterator(where));
				where = (!compK(where->value.first, key)) ? where->left : where->right;
			}
		}

		const_iterator find(const Key& key) const {
			node *where = tree.root;
			while (1) {
				if (!where || where->value.first == key)
					return (const_iterator(where));
				where = (!compK(where->value.first, key)) ? where->left : where->right;
			}
		}

		

		/////////////////////
		// ** Observers ** //
		/////////////////////

		key_compare key_comp() const { return (compK); }
		value_compare value_comp() const { return (compV); }


		// friend bool operator==(const map& lhs, const map& rhs) {
		// 	if (lhs.tree.getSize() != rhs.tree.getSize())
		// 		return (false);
		// 	iterator lbegin = lhs.begin();
		// 	iterator rbegin = rhs.begin();
		// 	while (lbegin)
		// 		if ((lbegin++)->key != (rbegin++)->key || (lbegin++)->value != (rbegin++)->value)
		// 			return (false);
		// 	return (true);
		// }
		
		// friend bool operator!=(const map& lhs, const map& rhs) {
		// 	return (!(lhs == rhs));
		// }

		// friend bool operator<(const map& lhs, const map& rhs) {
		// 	return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
		// }

		// friend bool operator<=(const map& lhs, const map& rhs) {
		// 	return (!(lhs > rhs));
		// }

		// friend bool operator>(const map& lhs, const map& rhs) {
		// 	return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));

		// }

		// friend bool operator>=(const map& lhs, const map& rhs) {
		// 	return (!(lhs < rhs));
		// }

		void swap(map& lhs, map& rhs) {
			lhs.swap(rhs);
		}


};

	template <typename Key, typename T, typename Comp, typename Alloc>
	inline bool operator==(const ft::map<Key, T, Comp, Alloc>& lhs, const ft::map<Key, T, Comp, Alloc>& rhs) { return (lhs.tree == rhs.tree); }

	template <typename Key, typename T, typename Comp, typename Alloc>
	inline bool operator!=(const ft::map<Key, T, Comp, Alloc>& lhs, const ft::map<Key, T, Comp, Alloc>& rhs) { return (!(lhs == rhs)); }

	template <typename Key, typename T, typename Comp, typename Alloc>
	inline bool operator<(const ft::map<Key, T, Comp, Alloc>& lhs, const ft::map<Key, T, Comp, Alloc>& rhs) { return (lhs.tree < rhs.tree); }

	template <typename Key, typename T, typename Comp, typename Alloc>
	inline bool operator<=(const ft::map<Key, T, Comp, Alloc>& lhs, const ft::map<Key, T, Comp, Alloc>& rhs) { return (!(rhs < lhs)); }

	template <typename Key, typename T, typename Comp, typename Alloc>
	inline bool operator>(const ft::map<Key, T, Comp, Alloc>& lhs, const ft::map<Key, T, Comp, Alloc>& rhs) { return (rhs < lhs); }

	template <typename Key, typename T, typename Comp, typename Alloc>
	inline bool operator>=(const ft::map<Key, T, Comp, Alloc>& lhs, const ft::map<Key, T, Comp, Alloc>& rhs) { return !(lhs < rhs); }

};