/**
 * @file Tree.hpp
 * @author sizilium
 * @date 10.06.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef COMPOSITE_CONTAINER_H
#define COMPOSITE_CONTAINER_H

// includes
#include <vs/Build.hpp>
#include <iterator>
#include <stack>
#include <queue>
#include <vs/base/cont/List.hpp>
#include <vs/base/cont/NullIterator.hpp>
#include <vs/base/cont/SmartIterator.hpp>
#include <vs/base/interfaces/Uncopyable.hpp>
#include <iostream>

namespace vs
{
namespace base
{
namespace cont
{
// predeclarations
template<class T> class TreeNode;

using namespace std;

/** @class Tree
 * A vision-synthesis template container in stl and java style. 
 * The most STL container hides the internal data structures. But sometimes you want to
 * use a tree structure transparently (for ordering xml entries for example). This
 * container simply arrange the data values in a tree structure. There is no binary
 * tree, b-tree etc. optimations. It serves simply as an container for ordering data
 * in tree structure.\n
 * The special tree iterator supports methods like nextSibling(), goParent(), goChild()
 * etc. so you can traverse the tree.\n
 * You can convert the contents to a normal container with the traversePostfix(), 
 * traversePrefix(), traverseHorizontal() methods().
 */
template<class T> class VS_EXPORT Tree : public JavaStyleContainer<T>
{
public:
	Tree()
	{
		root = new TreeNode<T> (NULL);
		tail = new TreeNode<T> (root);
		root->childs.push_back(tail);
	}
	
	Tree(T firstValue)
	{
		root = new TreeNode<T> (NULL);
		tail = new TreeNode<T> (root);
		TreeNode<T> *tmp = new TreeNode<T>(firstValue, root);
		root->childs.push_back(tmp);
		root->childs.push_back(tail);
	}
	
	virtual ~Tree()
	{
		clear();
		
		assert (root != NULL);
		delete root;

		root = NULL;
		tail = NULL;
	}

	bool operator==(const Tree<T> &tree) const
	{
		assert("operator== ist not implemented for class Tree yet" && false);
		// TODO implement operator== for Tree container
		return false;
	}
	
	class Const_Iterator;
	
	/** @class Iterator
	 * 
	 */
	class VS_EXPORT Iterator : public JavaStyleIterator<T>, public std::iterator<std::forward_iterator_tag, T>
	{
		
		// TODO: wenn ein iterator auf leeren baum angelegt wird muss eine assertion
		// geworfen werden, sonst absturz bei erster benutzung
		
	public:
		// typedefs
		typedef T value_type;
		typedef T& reference;
		typedef T* pointer;
		typedef int difference_type;
		typedef std::forward_iterator_tag iterator_category;
		friend class Tree<T>;
		friend class SmartIterator<T>;

		Iterator(TreeNode<T> *node = NULL) :
			currentNode(node)
		{
			if (node != NULL)
				root = node->parent;

			else
				root = NULL;
		}

		Iterator(Tree<T> *cont)
		{
			root = cont->root;
			
			if (root->childs.empty())
				currentNode = NULL;
			else
				currentNode = cont->root->childs.front();
		}
		
		Iterator(Tree<T> &cont)
		{
			root = cont.root;
			
			if (root->childs.empty())
				currentNode = NULL;
			else
				currentNode = cont.root->childs.front();
		}

		virtual ~Iterator()
		{
			root = NULL;
			currentNode = NULL;
		}

		bool hasNext() const
		{
			assert ("The iterator isn't initialized (or the container is empty)! First initialize it." && currentNode != NULL);

			if (!currentNode->childs.empty())
				return true;

			TreeNode<T> *tmp = currentNode->parent;
			TreeNode<T> *old = currentNode;
			SmartIterator<TreeNode<T>* > it;
			it = tmp->childs.iterator();
			
			while (it.hasNext())
			{
				if (it.current() == root)
					return false;
				// find right neigbour path
				if (it.next() == old)
					if (it.hasNext())
						return true;
					else
					{
						old = tmp;
						tmp = tmp->parent;
						if (tmp == NULL)
							return false;
						it = tmp->childs.iterator();
					}
			}
			
			return false;
		}

		T current() const
		{
			assert ("The iterator isn't initialized (or the container is empty)! First initialize it." && currentNode != NULL);
			return currentNode->value;
		}

		T next()
		{
			assert ("The iterator isn't initialized (or the container is empty)! First initialize it." && currentNode != NULL);
			T retVal = currentNode->value;

			if (!currentNode->childs.empty())
			{
				currentNode = currentNode->childs.front();
			}
			else
			{
				TreeNode<T> *old = currentNode;
				TreeNode<T> *parentNode = currentNode->parent;
				typename List<TreeNode<T>* >::Iterator it;
				it = parentNode->childs.begin();
				
				while (it.hasNext())
				{
					if (it.next() == old)
						if (it.hasNext())
						{
							currentNode = it.current();
							return retVal;
						}
						else
						{
							old = parentNode;
							parentNode = parentNode->parent;
							assert ("Invalid Tree<>::Iterator::next()! There is no next node. First check with hasNext()" && parentNode != NULL);
							it = parentNode->childs.begin();
						}
				}
				assert("The tree container has no next! First check with hasNextSibling().");
			}

			return retVal;
		}
		
		bool hasNextSibling() const
		{
			TreeNode<T> *parent = currentNode->parent;
			TreeNode<T> *last = NULL;
			TreeNode<T> *last2 = NULL;

			last = parent->childs.back();
			
			if (parent->parent == NULL)	// if there is a tail
			{
				typename List<TreeNode<T>* >::Iterator it;
				it = parent->childs.end();
				--it;
				--it;
				last2 = *it;
			}
			if(lastNode == last || lastNode == last2)
				return false;
			return true;
		}
		
		T nextSibling()
		{
			assert ("The iterator isn't initialized (or the container is empty)! First initialize it." && currentNode != NULL);
			T retVal = currentNode->value;
			
			lastNode = currentNode;
			TreeNode<T> *parent = currentNode->parent;
			typename List<TreeNode<T>* >::Iterator it (parent->childs);
			
			while (it.hasNext())
			{
				if (it.next() == lastNode)
					if (it.hasNext())
					{
						currentNode = it.current();
						return retVal;
					}
					//else
					//	assert("The tree container has no next sibling! First check with hasNextSibling().");
			}
			assert("The tree container has no next sibling! First check with hasNextSibling().");
	
			return retVal;
		}

		bool hasParent() const
		{
			assert ("The iterator isn't initialized (or the container is empty)! First initialize it." && currentNode != NULL);
			if (currentNode->parent != NULL)
				return true;
			else
				return false;
		}
		
		bool goParent()
		{
			assert ("The iterator isn't initialized (or the container is empty)! First initialize it." && currentNode != NULL);
			if (currentNode->parent == NULL)
				return false;
			
			currentNode = currentNode->parent;
			
			return true;
		}
		
		bool goParent(T value)
		{
			assert ("The iterator isn't initialized (or the container is empty)! First initialize it." && currentNode != NULL);

			while (currentNode->value != value)
			{
				if (currentNode->parent == NULL)
					return false;
				currentNode = currentNode->parent;
			}
			return true;
		}
		
		bool hasChildNr(int nr) const
		{
			assert ("The iterator isn't initialized (or the container is empty)! First initialize it." && currentNode != NULL);
			assert ("Invalid Tree child nr!" && nr >= 0);
			
			int numChilds = currentNode->childs.count();
			if (currentNode == root)
				--numChilds;
			
			if (numChilds > nr)
				return true;
			else
				return false;
		}
		
		T goChildNr(int nr)
		{
			assert ("The iterator isn't initialized (or the container is empty)! First initialize it." && currentNode != NULL);
			assert ("The current TreeNode has no childs! First check with hasChild()." && !currentNode->childs.empty());
			
			T retVal = currentNode->value;

			typename List<TreeNode<T>* >::Iterator it (currentNode->childs);
			for (int i = 0; i < nr ; i++)
			{
				++it;
				assert ("TreeNode children does not exist! First check with hasChilden(n)." && it.hasNext());
			}
			
			currentNode = *it;
			
			return retVal;
		}
		
		T goChild()
		{
			return goChildNr(0);
		}
		
		bool hasChild(T value) const
		{
			assert ("The iterator isn't initialized (or the container is empty)! First initialize it." && currentNode != NULL);
			typename List<TreeNode<T>* >::Iterator it (currentNode->childs);
			while(it.hasNext())
			{
				if (it.next()->value == value)
					return true;
			}
			return false;
		}
		
		bool hasChild() const
		{
			assert ("The iterator isn't initialized (or the container is empty)! First initialize it." && currentNode != NULL);
			if (currentNode->childs.empty())
				return false;
			else
				return true;
		}
		
		T goChild(T value)
		{
			assert ("The iterator isn't initialized (or the container is empty)! First initialize it." && currentNode != NULL);
			T retVal = currentNode->value;
			typename List<TreeNode<T>* >::Iterator it (currentNode->childs);
			while(it.hasNext())
			{
				if (it.current()->value == value)
					currentNode = it.current();
				it.next();
			}
			
			return retVal;
		}
		
		void remove()
		{
			// unsupported !!
			assert ("unsupported remove in Composite Iterator!" && false);
		}
		
		int depth() const
		{
			// find depth
			int itDepth;
			if (currentNode == NULL)
				itDepth = 0;
			else
				itDepth = 1;
			
			TreeNode<T> *tmp = currentNode;
			while (tmp->parent != NULL)
			{
				if (tmp->parent->parent != NULL)
					++itDepth;
				tmp = tmp->parent;
			}
			return itDepth;
		}
		
		operator bool() const
		{
			return bool (currentNode);
		}

		/**
		 * Returns the value of the entry dependent of the actual iterator position.
		 * @return The entries value.
		 */
		reference operator*() const
		{
			assert ("The iterator isn't initialized (or the container is empty)! First initialize it." && currentNode != NULL);
			return currentNode->value;
		}

		/**
		 * Returns the value of the entry dependent of the actual iterator position.
		 * return The entries value.
		 */
		pointer operator->() const
		{
			return &(operator*());
		}

		/**
		 * The ++it prefix operator shifts the iterator to the next entry and returns it
		 * then.
		 * @return Iterator to the new position.
		 */
		Iterator& operator++()
		{
			next();
			return *this;
		}

		/**
		 * The it++ postfix operator returns the iterator first and then shifts it
		 * to the next entry.
		 * @return Iterator to the new position.
		 */
		Iterator operator++(int)
		{
			Iterator it = *this;
			next();
			return it;
		}

		/**
		 * The '==' operator checks if two iterators are directed to the same
		 * TreeNode, say to the same entry of a list. 
		 * @return True if it == op2
		 */
		bool operator==(const Iterator &op2) const
		{
			if (this->currentNode == op2.currentNode)
				return true;
			else
				return false;
		}

		/**
		 * The opposite of '==' operator. Checks if two iterators not directed to the
		 * same TreeNode.
		 * @return True if it != op2
		 */
		bool operator!=(const Iterator &op2) const
		{
			return !(*this == op2);
		}

	private:
		Iterator(const Const_Iterator &it)
		{
			this->lastNode = const_cast<TreeNode<T>*> (it.lastNode);
			this->root = const_cast<TreeNode<T>*> (it.root);
			this->currentNode = const_cast<TreeNode<T>*> (it.currentNode);
		}
		
		mutable TreeNode<T> *lastNode;
		TreeNode<T> *root;
		TreeNode<T> *currentNode;
	};

	
	
	/** @class Const_Iterator
	 * 
	 */
	class VS_EXPORT Const_Iterator : public JavaStyleIterator<T>, public std::iterator<std::forward_iterator_tag, T>
	{
	public:
		// typedefs
		typedef const T value_type;
		typedef const T& reference;
		typedef const T* pointer;
		typedef int difference_type;
		typedef std::forward_iterator_tag iterator_category;
		friend class Tree<T>;
		friend class Iterator;

		Const_Iterator(const TreeNode<T> *node = NULL) :
			currentNode(node)
		{
			if (node != NULL)
				root = node->parent;

			else
				root = NULL;
		}

		Const_Iterator(const Tree<T> *cont)
		{
			root = cont->root;
			
			if (root->childs.empty())
				currentNode = NULL;
			else
				currentNode = cont->root->childs.front();
		}
		
		Const_Iterator(const Tree<T> &cont)
		{
			root = cont.root;
			
			if (root->childs.empty())
				currentNode = NULL;
			else
				currentNode = cont.root->childs.front();
		}

		virtual ~Const_Iterator()
		{
			root = NULL;
			currentNode = NULL;
		}

		bool hasNext() const
		{
			assert ("The iterator isn't initialized (or the container is empty)! First initialize it." && currentNode != NULL);

			if (!currentNode->childs.empty())
				return true;

			TreeNode<T> *tmp = currentNode->parent;
			const TreeNode<T> *old = currentNode;
			SmartIterator<TreeNode<T>* > it;
			it = tmp->childs.iterator();
			
			while (it.hasNext())
			{
				if (it.current() == root)
					return false;
				// find right neigbour path
				if (it.next() == old)
					if (it.hasNext())
						return true;
					else
					{
						old = tmp;
						tmp = tmp->parent;
						if (tmp == NULL)
							return false;
						it = tmp->childs.iterator();
					}
			}
			
			return false;
		}

		T current() const
		{
			assert ("The iterator isn't initialized (or the container is empty)! First initialize it." && currentNode != NULL);
			return currentNode->value;
		}

		T next()
		{
			assert ("The iterator isn't initialized (or the container is empty)! First initialize it." && currentNode != NULL);
			T retVal = currentNode->value;

			if (!currentNode->childs.empty())
			{
				currentNode = currentNode->childs.front();
			}
			else
			{
				const TreeNode<T> *old = currentNode;
				TreeNode<T> *parentNode = currentNode->parent;
				typename List<TreeNode<T>* >::Iterator it;
				it = parentNode->childs.begin();
				
				while (it.hasNext())
				{
					if (it.next() == old)
						if (it.hasNext())
						{
							currentNode = it.current();
							return retVal;
						}
						else
						{
							old = parentNode;
							parentNode = parentNode->parent;
							assert ("Invalid Tree<>::Const_Iterator::next()! There is no next node. First check with hasNext()" && parentNode != NULL);
							it = parentNode->childs.begin();
						}
				}
				assert("The tree container has no next! First check with hasNextSibling().");
			}

			return retVal;
		}
		
		bool hasNextSibling() const
		{
			TreeNode<T> *parent = currentNode->parent;
			TreeNode<T> *last, *last2 = NULL;

			last = parent->childs.back();
			
			if (parent->parent == NULL)	// if there is a tail
			{
				typename List<TreeNode<T>* >::Iterator it;
				it = parent->childs.end();
				--it;
				--it;
				last2 = *it;
			}
			if(lastNode == last || lastNode == last2)
				return false;
			return true;
		}
		
		T nextSibling()
		{
			assert ("The iterator isn't initialized (or the container is empty)! First initialize it." && currentNode != NULL);
			T retVal = currentNode->value;
			
			lastNode = currentNode;
			TreeNode<T> *parent = currentNode->parent;
			typename List<TreeNode<T>* >::Const_Iterator it (parent->childs);
			
			while (it.hasNext())
			{
				if (it.next() == lastNode)
					if (it.hasNext())
					{
						currentNode = it.current();
						return retVal;
					}
					//else
					//	assert("The tree container has no next sibling! First check with hasNextSibling().");
			}
			assert("The tree container has no next sibling! First check with hasNextSibling().");
	
			return retVal;
		}

		bool hasParent() const
		{
			assert ("The iterator isn't initialized (or the container is empty)! First initialize it." && currentNode != NULL);
			if (currentNode->parent != NULL)
				return true;
			else
				return false;
		}
		
		bool goParent()
		{
			assert ("The iterator isn't initialized (or the container is empty)! First initialize it." && currentNode != NULL);
			if (currentNode->parent == NULL)
				return false;
			
			currentNode = currentNode->parent;
			
			return true;
		}
		
		bool goParent(T value)
		{
			assert ("The iterator isn't initialized (or the container is empty)! First initialize it." && currentNode != NULL);

			while (currentNode->value != value)
			{
				if (currentNode->parent == NULL)
					return false;
				currentNode = currentNode->parent;
			}
			return true;
		}
		
		bool hasChildNr(int nr) const
		{
			assert ("The iterator isn't initialized (or the container is empty)! First initialize it." && currentNode != NULL);
			assert ("Invalid Tree child nr!" && nr >= 0);
			
			int numChilds = currentNode->childs.count();
			if (currentNode == root)
				--numChilds;
			
			if (numChilds > nr)
				return true;
			else
				return false;
		}
		
		T goChildNr(int nr)
		{
			assert ("The iterator isn't initialized (or the container is empty)! First initialize it." && currentNode != NULL);
			assert ("The current TreeNode has no childs! First check with hasChild()." && !currentNode->childs.empty());
			
			T retVal = currentNode->value;

			typename List<TreeNode<T>* >::Const_Iterator it (currentNode->childs);
			for (int i = 0; i < nr ; i++)
			{
				++it;
				assert ("TreeNode children does not exist! First check with hasChilden(n)." && it.hasNext());
			}
			
			currentNode = *it;
			
			return retVal;
		}
		
		T goChild()
		{
			return goChildNr(0);
		}
		
		bool hasChild(T value) const
		{
			assert ("The iterator isn't initialized (or the container is empty)! First initialize it." && currentNode != NULL);
			typename List<TreeNode<T>* >::Const_Iterator it (currentNode->childs);
			while(it.hasNext())
			{
				if (it.next()->value == value)
					return true;
			}
			return false;
		}
		
		bool hasChild() const
		{
			assert ("The iterator isn't initialized (or the container is empty)! First initialize it." && currentNode != NULL);
			if (currentNode->childs.empty())
				return false;
			else
				return true;
		}
		
		T goChild(T value)
		{
			assert ("The iterator isn't initialized (or the container is empty)! First initialize it." && currentNode != NULL);
			T retVal = currentNode->value;
			typename List<TreeNode<T>* >::Const_Iterator it (currentNode->childs);
			while(it.hasNext())
			{
				if (it.current()->value == value)
					currentNode = it.current();
				it.next();
			}
			
			return retVal;
		}
		
		void remove()
		{
			// unsupported !!
			assert ("unsupported remove in Composite Const_Iterator!" && false);
		}
		
		int depth() // TODO const
		{
			// find depth
			int itDepth;
			if (currentNode == NULL)
				itDepth = 0;
			else
				itDepth = 1;
			
			TreeNode<T> *tmp = const_cast<TreeNode<T> *> (currentNode);
			while (tmp->parent != NULL)
			{
				if (tmp->parent->parent != NULL)
					++itDepth;
				tmp = tmp->parent;
			}
			return itDepth;
		}
		
		operator bool() const
		{
			return bool (currentNode);
		}

		/**
		 * Returns the value of the entry dependent of the actual iterator position.
		 * @return The entries value.
		 */
		reference operator*() const
		{
			assert ("The iterator isn't initialized (or the container is empty)! First initialize it." && currentNode != NULL);
			return currentNode->value;
		}

		/**
		 * Returns the value of the entry dependent of the actual iterator position.
		 * return The entries value.
		 */
		pointer operator->() const
		{
			return &(operator*());
		}

		/**
		 * The ++it prefix operator shifts the iterator to the next entry and returns it
		 * then.
		 * @return Const_Iterator to the new position.
		 */
		Const_Iterator& operator++()
		{
			next();
			return *this;
		}

		/**
		 * The it++ postfix operator returns the iterator first and then shifts it
		 * to the next entry.
		 * @return Const_Iterator to the new position.
		 */
		Const_Iterator operator++(int)
		{
			Const_Iterator it = *this;
			next();
			return it;
		}

		/**
		 * The '==' operator checks if two iterators are directed to the same
		 * TreeNode, say to the same entry of a list. 
		 * @return True if it == op2
		 */
		bool operator==(const Const_Iterator& op2) const
		{
			if (this->currentNode == op2.currentNode)
				return true;
			else
				return false;
		}

		/**
		 * The opposite of '==' operator. Checks if two iterators not directed to the
		 * same TreeNode.
		 * @return True if it != op2
		 */
		bool operator!=(const Const_Iterator &op2) const
		{
			return !(*this == op2);
		}

	private:
		// this is const!
		mutable const TreeNode<T> *lastNode;
		const TreeNode<T> *root;
		const TreeNode<T> *currentNode;
	};
	
	// ----------------------------------------------------------

	SmartIterator<T> iterator() const
	{
		if (empty())
			return SmartIterator<T>(new NullIterator<T>);
		else
			// set iterator to first element
			return SmartIterator<T>( new Iterator(root->childs.front()) );
	}

	Iterator begin()
	{
		if (empty())
			return Iterator();
		else
		{
			// set iterator to first element
			Iterator it(root->childs.front());
			return it;
		}
	}

	Iterator end()
	{
		return Iterator(tail);
	}
	
	Const_Iterator begin() const
	{
		if (empty())
			return Const_Iterator();
		else
		{
			// set iterator to first element
			Const_Iterator it(root->childs.front());
			return it;
		}
	}

	Const_Iterator end() const
	{
		return Iterator(tail);
	}
	
	T front() const
	{
		assert("The Tree container is empty! First check with empty() or isEmtpy()." && !empty());
		return root->childs.front()->value;
	}

	void add(const T value)
	{
		TreeNode<T> *tmp = new TreeNode<T> (value, this->root);

		// remove tail
		delete root->childs.back();
		root->childs.pop_back();

		root->childs.push_back(tmp);

		// restore tail
		tail = new TreeNode<T> (root);
		root->childs.push_back(tail);
	}

	void add(const T value, const Iterator &it)
	{
		assert (it.currentNode != NULL);

		if (it.currentNode == this->root)
		{
			add (value);
			return;
		}

		TreeNode<T> *tmp = new TreeNode<T> (value, it.currentNode);
		it.currentNode->childs.push_back(tmp);
	}
	
	void add(const JavaStyleContainer<T> *values)
	{
		SmartIterator<T> it = values->iterator();
		while (it.hasNext())
			add(it.next());
	}
	
	void add(const JavaStyleContainer<T> *values, const Iterator &it)
	{
		SmartIterator<T> valIt = values->iterator();
		while (valIt.hasNext())
			add(valIt.next(), it);
	}

	bool remove(const T value)
	{
		bool retVal = false;
		
		Iterator it = find(value);
		

		if (it != end())
		{
			it.currentNode->parent->childs.remove(it.currentNode);
			delete it.currentNode;
			it.currentNode = NULL;
			retVal = true;
			remove(value);
		}
		
		return retVal;
	}

	Iterator find(const T value)
	{
		Iterator it = begin();
		while (it.hasNext())
		{
			if (it.current() == value)
				return it;
			it.next();
		}
		return end();
	}

	Iterator find(const T value, const Iterator &startSearchHere)
	{
		Iterator it;
		it.root = startSearchHere.currentNode;
		it.currentNode = startSearchHere.currentNode;
		
		while (it.hasNext())
		{
			if (it.current() == value)
				return it;
			it.next();
		}
		return end();
	}

	bool empty() const
	{
		// when empty only the tail is in list
		if (root->childs.count() == 1)
			return true;
		else
			return false;
	}

	/**
	 * Override (instead of JavaStyleContainer implementation).
	 */
	void clear()
	{
		SmartIterator<TreeNode<T>* > it = root->childs.iterator();
		while (it.hasNext())
		{
			delete it.next();
		}
		root->childs.clear();
		tail = new TreeNode<T> (root);
		root->childs.push_back(tail);
	}
	
	/**
	 *
	 */
	void splice(Iterator &toPosition, Tree<T> &sourceTree)
	{
		typename List<TreeNode<T>* >::Iterator itSource, itThis;
		
		// remove tail from source
		delete sourceTree.root->childs.back();
		sourceTree.root->childs.pop_back();
		
		itSource = sourceTree.root->childs.begin();
		itThis = toPosition.currentNode->childs.end();
		
		// transfer childrens
		while (itSource.hasNext())
			toPosition.currentNode->childs.splice(itThis, sourceTree.root->childs, itSource);

		// repair parents
		itThis = toPosition.currentNode->childs.begin();
		while (itThis.hasNext())
			itThis.next()->parent = toPosition.currentNode;
			
		sourceTree.clear();
	}
	
	/**
	 * 
	 */
	void splice(Iterator &toPosition, Tree<T> &sourceTree, Iterator &sourceTreePart)
	{
		// TODO splice for tree
	}
	
	/**
	 * 
	 */
	void copy(Iterator &sourcePosition)
	{
		// clear, new root
		if (root != NULL)
			delete root;
		root = NULL;
		root = new TreeNode<T>(NULL);
		
		// add first node
		TreeNode<T> *tmp = new TreeNode<T>(sourcePosition.currentNode->value, root);
		root->childs.push_front(tmp);
		
		// add tail
		tail = new TreeNode<T> (root);
		root->childs.push_back(tail);
		
		// copy subtree
		copyMeRecursive(sourcePosition.currentNode, sourcePosition.currentNode->parent, tmp);
	}
	
	/**
	 * 
	 */
	void copy(Const_Iterator &sourcePosition)
	{
		Iterator it(sourcePosition);
		copy(it);
	}
	
	/**
	 * Traverse the Tree by postfix and save the result in any container.
	 */
	void traversePostfix(JavaStyleContainer<T> *container)
	{
		recursiveTraversePostfix(this->root->childs.front(), this->tail, container);
	}
	
	void traversePrefix(JavaStyleContainer<T> *container)
	{
		recursiveTraversePrefix(this->root->childs.front(), this->tail, container);
	}
	
	void traverseInfix(JavaStyleContainer<T> *container)
	{
		
	}
	
	void traverseHorizontal(JavaStyleContainer<T> *container)
	{
		int tmpDepth = depth();
		for(int i = 1; i <= tmpDepth; i++)
		{
			traverseHorizontal(container, i);
		}
	}
	
	void traverseHorizontal(JavaStyleContainer<T> *container, int onLevel)
	{
		Iterator it = begin();
		while (it.hasNext())
		{
			if (it.depth() == onLevel)
				container->add(*it);
			it.next();
		}
	}
	
	float averageDepth() // TODO: const
	{
		int num = 0;
		int sum = 0;
		Iterator it = begin();
		while (it.hasNext())
		{
			++num;
			sum += (it++).depth();
		}
		return (float) sum / (float) num;
	}
	
	int depth() // TODO: const
	{
		int maxDepth = 0, tmp;
		Iterator it = begin();
		while (it.hasNext())
		{
			if ((tmp = it.depth()) > maxDepth)
				maxDepth = tmp;
			it.next();
		}
		return maxDepth;
	}
	
	void cout() const
	{
		// TODO implements cout for tree
	}

private:
	
	void copyMeRecursive(TreeNode<T> *otherNode, const TreeNode<T> *end, TreeNode<T> *myNode)
	{
		if (otherNode != NULL)
		{
			typename List<TreeNode<T>* >::Iterator it (otherNode->childs);
			while (it.hasNext() && it.current() != end)
			{
				// copy node
				T value = it.current()->value;
				TreeNode<T> *newNode = new TreeNode<T>(value, myNode);
				
				myNode->childs.push_back(newNode);
				
				copyMeRecursive(it.next(), end, newNode);
			}
		}
	}
	
	void recursiveTraversePostfix(TreeNode<T> *node, TreeNode<T> *tail, JavaStyleContainer<T> *container)
	{
		if (node != NULL)
		{
			container->add(node->value);
			typename List<TreeNode<T>* >::Iterator it (node->childs);
			while (it.hasNext() && it.current() != tail)
				recursiveTraversePostfix(it.next(), tail, container);
		}
	}
	
	void recursiveTraversePrefix(TreeNode<T> *node, TreeNode<T> *tail, JavaStyleContainer<T> *container)
	{
		if (node != NULL)
		{
			typename List<TreeNode<T>* >::Iterator it (node->childs);
			while (it.hasNext() && it.current() != tail)
				recursiveTraversePrefix(it.next(), tail, container);
			container->add(node->value);
		}
	}
	
	// start and end marker
	TreeNode<T> *root;
	TreeNode<T> *tail;

};

/** @class TreeNode
 * 
 */
template<class T> class VS_EXPORT TreeNode
{
public:
	TreeNode(T value, TreeNode<T> *parent) :
		value(value), parent(parent)
	{
	}

	TreeNode(TreeNode<T> *parent) :
		parent(parent)
	{
	}

	~TreeNode()
	{
		SmartIterator<TreeNode<T> *> it = childs.iterator();
		while (it.hasNext())
			delete it.next();

		childs.clear();
		parent = NULL;
	}

	friend class Tree<T>;
	friend class Tree<T>::Iterator;
	friend class Tree<T>::Const_Iterator;

private:
	T value;

	TreeNode<T> *parent;
	List<TreeNode<T>* > childs;
};


} // cont
} // base
} // vs

#endif /*TREE_HPP_*/
