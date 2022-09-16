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


		allocator_type get_allocator() const {
			return (allocator);
		}

		//////////////////////////
		// ** Element access ** //
		//////////////////////////

		T& at(const Key& key) { return ((this->find(key))->second); }
		const T& at(const Key& key) const { return ((this->find(key))->second); }

		////////////////////
		// ** Modifier ** //
		////////////////////


		

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