/**
 * @file StringList.hpp
 * @author sizilium
 * @date 01.06.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef STRING_LIST_H
#define STRING_LIST_H

// includes
#include <vs/Build.hpp>
#include <string>
#include <iostream>
#include <assert.h>
#include <stdio.h>
#include <iterator>
#include <vs/base/cont/JavaStyleIterator.hpp>
#include <vs/base/cont/JavaStyleContainer.hpp>
#include <vs/base/cont/NullIterator.hpp>
#include <vs/base/cont/SmartIterator.hpp>

namespace vs
{
namespace base
{
namespace cont
{
// predeclarations
//template <class T> class SmartIterator;
template <class T> class StringListNode;
template <class T> class StringList;

using namespace std;

/**
 * Global function wich swappes two StringList's.
 * @code // Example
 * StringList<MyClass *> list_1, list_2;
 * ...
 * swap(list_1, list_2);	// swapping by global function
 * list_1.swap(list_2);			// swapping by StringList method
 * 
 * @endcode
 * @param list_1 Pass the first list (reference).
 * @param list_2 Pass the second list (reference).
 */
template<class T>
VS_EXPORT void swap(StringList<T> &list_1, StringList<T> &list_2)
{
	StringListNode<T> *tmp;

	tmp = list_1.head;
	list_1.head = list_2.head;
	list_2.head = tmp;

	tmp = list_1.tail;
	list_1.tail = list_2.tail;
	list_2.tail = tmp;
}


/** @class StringList
 * A vision-synthesis template container like the stl list pattern. But StringList can
 * contain pointers (it's safe) and the members can searched by a string name (optional). \n
 * StringList supports an iterator who can both: Java and STL styled access. \n
 * It is a double linked list. There are many assertions to catch some errors. If you want
 * to disable it (for more performance) write \#define NDEBUG in this header. \n
 * The container is tested regularly with several CppUnit "http://sourceforge.net/projects/cppunit" 
 * test but notice that no warranty is given.
 */
template <class T> 
class VS_EXPORT StringList : public JavaStyleContainer<T>
{
public:
	/**
	 * After initialization the container is empty. 
	 */
	StringList()
	{
		head = new StringListNode<T>();
		tail = new StringListNode<T>();
		head->next = tail;
		head->previous = NULL;
		tail->next = NULL;
		tail->previous = head;
	}
	
	StringList(const StringList<T> &list)
	{
		this->addAll(&list);
	}

	/**
	 * All entrys will be cleared.
	 * @see clear
	 */
	virtual ~StringList()	
	{
		clear();
		delete head;
		head = NULL;
		delete tail;
		tail = NULL;
	}
	
	/**
	 * Copies the list.
	 */
	StringList<T>& operator=(const StringList<T> &op2)
	{
		if (this != &op2)
		{
			this->addAll(&op2);
		}
		return *this;
	}
	
	/**
	 * Checks if two list pointers are directed to the same list. Complexity is only O(1).
	 * @return True if it != op2
	 */
	bool operator== (const StringList<T> &op2) const
	{
		if (head == op2.head)
			return true;
		else
			return false;
	}
	
	/**
	 * The opposite of '==' operator. Checks if two list pointers are directed to
	 * different lists.
	 * @return True if it != op2
	 */
	bool operator!= (const StringList<T> &op2) const
	{
		return !(*this == op2);
	}

	/**
	 * This is the iterator for StringList. It implements JavaStyleIterator, means that
	 * the common methods hasNext, next and remove available. STL style operation are
	 * possible too, like ++, --, = and * operations.\n
	 * A special feature of the StringList::iterator is the name() method, who returns the
	 * name of an entry.\n
	 * If you try to use an uninitialized iterator an assert will occure.\n
	 * Note: EasyFramework use strictly name conventions: Classes are all upper case
	 * and also the Iterator class.
	 * 
	 * @code // Usage-Exampe:
	 * StringList<short> stringList;
	 * stringList.push_front(15, "fifteen");
	 * stringList.push_front(10, "ten");
	 * stringList.push_front(5, "five");
	 * 
	 * //Java style:
	 * StringList<short>::Iterator it(stringList);
	 * while (it.hasNext())
	 *     cout << it.next() << " ";				// output is: 5 10 15
	 * // {cout << it.name() << " "; it.next();}	// output: five ten fifteen
	 * 
	 * // STL style:
	 * StringList<short>::Iterator itc = stringList.begin();
	 * while (itc != stringList.end())
	 * {
	 *     cout << *itc << " ";					// output is: 5 10 15
 	 *     itc++;
	 * }
	 * @endcode
	 */
	class VS_EXPORT Iterator : public JavaStyleIterator<T>, public std::iterator<std::bidirectional_iterator_tag, T>
	{
	public:	
		// typedefs
		typedef T value_type;
		typedef T& reference;
		typedef T* pointer;
		typedef int difference_type;
		typedef std::bidirectional_iterator_tag iterator_category;
		friend class StringList<T>;
		
		/**
		 * You need no parameters for an iterator, but before the first use the iterator
		 * must be initialized (with '=' operator for example).
		 * @param node Optional parameter to direct the iterator to an ListNode. 
		 * Only for internal use. 
		 */
		Iterator(StringListNode<T> *node = NULL) :currentNode(node) {}

		/**
		 * A useful iterator initialization. Pass a list to the constructor parameter to
		 * direct the iterator to the first entry of the list.
		 * @param list The target list for the iterator
		 */
		Iterator(StringList<T> &list)
		{
			*this = list.begin();
		}
		
		/**
		 * Copyconstructor.
		 * @param it Iterator to copy.
		 */
		Iterator(const Iterator &it) :currentNode(it.currentNode) {}

		/**
		 * Java style method. Checks if the list has a next entry, dependent of the
		 * iterator position.
		 * @return True if the list still has a next entry from the iterator position. 
		 */
		bool hasNext() const
		{
			assert("first you must inizialize the iterator!" && currentNode != NULL);
			if (currentNode->next != NULL)
				return true;
			return false;
		}

		/**
		 * Returns the current entry without iterater shifting (additional vs method, no java
		 * style but useful).
		 * @return The current entry.
		 */
		T current() const
		{
			assert ("first you must inizialize the iterator!" && currentNode != NULL);
			return currentNode->value;
		}
		
		/**
		 * Java style method. Returns the current entry and set the iterator to the next.\n
		 * First check if the list has a next entry with hasNext()! Otherwise an assert
		 * will occure.
		 * @return The current entry.
		 */
		T next()
		{
			assert ("first you must inizialize the iterator!" && currentNode != NULL);
			T tmp = currentNode->value;
			assert ("there are no more entrys in the StringList, call hasNext() first!" && currentNode->next != NULL);
			currentNode = currentNode->next;
			return tmp;
		}

		/**
		 * Removes the current entry and push the iterator to the next entry. 
		 */
		void remove()
		{
			assert ("first you must inizialize the iterator!" && currentNode != NULL);
			StringListNode<T> *tmp = currentNode->next;
			currentNode->previous->next = currentNode->next;
			currentNode->next->previous = currentNode->previous;
			delete currentNode;
			currentNode = tmp;
		}

		/** 
		 * Special feature of StringList: The entries are named.\n
		 * Returns the name of the entry dependent of the actual iterator position.
		 * @return The entries name.
		 */
		string& name() const
		{
			assert ("first you must inizialize the iterator!" && currentNode != NULL);
			return currentNode->name;
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
			assert ("first you must inizialize the iterator!" && currentNode != NULL);
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
			assert ("first you must inizialize the iterator!" && currentNode != NULL);
			assert ("there are no more entrys in the StringList, call  if (it==list.end())  first!" && currentNode->next != NULL);
			currentNode = currentNode->next;
			return *this;
		}
		
		/**
		 * The --it prefix operator shifts the iterator to the previous entry and returns
		 * it then.
		 * @return Iterator to the new position.
		 */
		Iterator& operator--()
		{
			assert ("first you must inizialize the iterator!" && currentNode != NULL);
			assert ("there are no more entrys in the StringList, call  if (it==list.begin())  first!" && currentNode->previous != NULL);
			currentNode = currentNode->previous;
			return *this;
		}
		
		/**
		 * The it++ postfix operator returns the iterator first and then shifts it
		 * to the next entry.
		 * @return Iterator to the new position.
		 */
		Iterator operator++(int)
		{
			assert ("first you must inizialize the iterator!" && currentNode != NULL);
			assert ("there are no more entrys in the StringList, call  if (it==list.end())  first!" && currentNode->next != NULL);
			Iterator tmp = *this;
			currentNode = currentNode->next;
			return tmp;
		}
		
		/**
		 * The it-- postfix operator first returns the iterator and then shifts it
		 * to the previous entry.
		 * @return Iterator to the new position.
		 */
		Iterator operator--(int)
		{
			assert ("first you must inizialize the iterator!" && currentNode != NULL);
			assert ("there are no more entrys in the StringList, call  if (it==list.begin())  first!" && currentNode->previous != NULL);
			Iterator tmp = *this;
			currentNode = currentNode->previous;
			return tmp;
		}
		
		/**
		 * The '==' operator checks if two iterators are directed to the same
		 * StringListNode, say to the same entry of a list. 
		 * @return True if it == op2
		 */
		bool operator== (const Iterator& op2) const
		{
			if (currentNode == op2.currentNode)
				return true;
			else
				return false;
		}

		/**
		 * The opposite of '==' operator. Checks if two iterators not directed to the
		 * same entry of a list.
		 * @return True if it != op2
		 */
		bool operator!= (const Iterator &op2) const
		{
			return !(*this == op2);
		}
			
	private:
		StringListNode<T> *currentNode;
	};
	
	
	/**
	 * This is the Const_Iterator for StringList. It implements JavaStyleIterator, means that
	 * the common methods hasNext, next and remove available. STL style operation are
	 * possible too, like ++, --, = and * operations. STL algorithm are also possible
	 * (this is an STL bidirectional_iterator).\n
	 * If you try to use an uninitialized Const_Iterator an assert will occure.\n
	 * Note: EasyFramework use strictly name conventions: Classes are all upper case
	 * and also the iterator class.\n
	 * The const iterator can not change the container!
	 */
	class VS_EXPORT Const_Iterator : public JavaStyleIterator<T>, public std::iterator<std::bidirectional_iterator_tag, const T>
	{
	public:
		// typedefs
		typedef const T value_type;
		typedef const T& reference;
		typedef const T* pointer;
		typedef int difference_type;
		typedef std::bidirectional_iterator_tag iterator_category;
		friend class StringList<T>;
		
		/**
		 * You need no parameters for an iterator, but before the first use the iterator
		 * must be initialized (with '=' operator for example).
		 * @param node Optional parameter to direct the iterator to an ListNode. 
		 * Only for internal use. 
		 */
		Const_Iterator(const StringListNode<T> *node = NULL) :currentNode(node) {}

		/**
		 * Overloaded constructor for more const compability (Const_Iterator must be able
		 * to direct to an const StringListNode and a StringListNode).
		 */
		Const_Iterator(StringListNode<T> *node)
		:currentNode(const_cast<const StringListNode<T>*> (node) ) 
		{}
		
		/**
		 * A useful iterator initialization. Pass a list to the constructor parameter to
		 * direct the iterator to the first entry of the list.
		 * @param list The target list for the iterator
		 */
		Const_Iterator(const StringList<T> &list)
		{
			*this = list.begin();
		}
		
		/**
		 * Copyconstructor.
		 * @param it iterator to copy.
		 */
		Const_Iterator(const Const_Iterator &it) :currentNode(it.currentNode) {}

		/**
		 * Java style method. Checks if the list has a next entry, dependent of the
		 * iterator position.
		 * @return True if the list still has a next entry from the iterator position. 
		 */
		bool hasNext() const
		{
			assert("first you must inizialize the Const_Iterator!" && currentNode != NULL);
			if (currentNode->next != NULL)
				return true;
			return false;
		}

		/**
		 * Returns the current entry without iterater shifting (additional vs method, no java
		 * style but useful).
		 * @return The current entry.
		 */
		T current() const
		{
			assert ("first you must inizialize the iterator!" && currentNode != NULL);
			return currentNode->value;
		}
		
		/**
		 * Java style method. Returns the current entry and set the iterator to the next.\n
		 * First check if the list has a next entry with hasNext()! Otherwise an assert
		 * will occure.
		 * @return The current entry.
		 */
		T next()
		{
			assert ("first you must inizialize the Const_Iterator!" && currentNode != NULL);
			T tmp = currentNode->value;
			assert ("there are no more entrys in the StringList, call hasNext() first!" && currentNode->next != NULL);
			currentNode = currentNode->next;
			return tmp;
		}

		/**
		 * Removes the current entry and push the iterator to the next entry. 
		 */
		void remove()
		{
			assert ("first you must inizialize the Const_Iterator!" && currentNode != NULL);
			StringListNode<T> *tmp = currentNode->next;
			currentNode->previous->next = currentNode->next;
			currentNode->next->previous = currentNode->previous;
			delete currentNode;
			currentNode = tmp;
		}

		/**
		 * Returns the value of the entry dependent of the actual iterator position.
		 * @return The entries value.
		 */
		reference operator*() const
		{
			assert ("first you must inizialize the Const_Iterator!" && currentNode != NULL);
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
		 * @return iterator to the new position.
		 */
		Const_Iterator& operator++()
		{
			assert ("first you must inizialize the Const_Iterator!" && currentNode != NULL);
			assert ("there are no more entrys in the StringList, call  if (it==list.end())  first!" && currentNode->next != NULL);
			currentNode = currentNode->next;
			return *this;
		}
		
		/**
		 * The --it prefix operator shifts the iterator to the previous entry and returns
		 * it then.
		 * @return iterator to the new position.
		 */
		Const_Iterator& operator--()
		{
			assert ("first you must inizialize the Const_Iterator!" && currentNode != NULL);
			assert ("there are no more entrys in the StringList, call  if (it==list.begin())  first!" && currentNode->previous != NULL);
			currentNode = currentNode->previous;
			return *this;
		}
		
		/**
		 * The it++ postfix operator returns the iterator first and then shifts it
		 * to the next entry.
		 * @return Const_Iterator to the new position.
		 */
		Const_Iterator operator++(int)
		{
			assert ("first you must inizialize the Const_Iterator!" && currentNode != NULL);
			assert ("there are no more entrys in the StringList, call  if (it==list.end())  first!" && currentNode->next != NULL);
			Const_Iterator tmp = *this;
			currentNode = currentNode->next;
			return tmp;
		}
		
		/**
		 * The it-- postfix operator first returns the iterator and then shifts it
		 * to the previous entry.
		 * @return iterator to the new position.
		 */
		Const_Iterator operator--(int)
		{
			assert ("first you must inizialize the Const_Iterator!" && currentNode != NULL);
			assert ("there are no more entrys in the StringList, call  if (it==list.begin())  first!" && currentNode->previous != NULL);
			Const_Iterator tmp = *this;
			currentNode = currentNode->previous;
			return tmp;
		}
		
		/**
		 * The '==' operator checks if two iterators are directed to the same
		 * StringListNode, say to the same entry of a list. 
		 * @return True if it == op2
		 */
		bool operator== (const Const_Iterator& op2) const
		{
			if (currentNode == op2.currentNode)
				return true;
			else
				return false;
		}

		/**
		 * The opposite of '==' operator. Checks if two iterators not directed to the
		 * same entry of a list.
		 * @return True if it != op2
		 */
		bool operator!= (const Const_Iterator &op2) const
		{
			return !(*this == op2);
		}
		
	private:
		// this is const!
		const StringListNode<T> *currentNode;
	};
	
	
	// -------------- Java section ------------------
	
	/**
	 * This method implements the JavaStyleContainer interfaces an returns an iterator
	 * pointer with JavaStyleIterator type.
	 * @return Look out for Iterator pattern for further informations.
	 * @see JavaStyleContainer, JavaStyleIterator
	 */
	SmartIterator<T> iterator() const
	{
		if (empty())
			return SmartIterator<T> (new NullIterator<T>);
		else
			return SmartIterator<T> (new Iterator(head->next));
	}
	
	void add(const T element)
	{
		push_back(element);
	}
	
	void add(const T element, string name)
	{
		push_back(element, name);
	}
	
	/**
	 * Removes all entries by a given name. If there is no entry with this name, 
	 * nothing happens.
	 * @param name All entries with this values will be removed
	 */
	bool remove(const string &name)
	{
		bool changed = false;
		Iterator it = this->begin();
		while (it != this->end())
		{
			if (it.name() == name)
			{
				erase(it);
				changed = true;
			}
			else
				++it;
		}
		return changed;
	}

	/**
	 * Removes all entries by a given value. If there is no entry whis this value,
	 * nothing happens.
	 * @param value All entries with this value will be removed.
	 */
	bool remove(const T value)
	{
		bool changed = false;
		Iterator it = this->begin();
		while (it != this->end())
		{
			if (*it == value)
			{
				erase(it);
				changed = true;
			}
			else
				++it;
		}
		return changed;
	}
	
	// ----------- Java section end ----------------
	
	
	/**
	 * Returns an iterator wich is directed to the beginning of the StringList (head->next). If the list
	 * is empty, the iterator will directed to the tail of the list (no error).\n
	 * Note: Check with empty() if there is an entry first!
	 * @return An iterator to the first entry.
	 */
	Iterator begin()
	{
		return Iterator(head->next);
	}
	
	/**
	 * Returns an iterator wich is directed the end of the StringList (tail).
	 */
	Iterator end()
	{
		return Iterator(tail);
	}
	
	/**
	 * Returns an const iterator wich is directed to the beginning of the List (head->next). If the list
	 * is empty, the iterator will directed to the tail of the list (no error).\n
	 * Note: Check with empty() if there is an entry first!\n
	 * The const iterator can not change the container.
	 * @return An iterator to the first entry.
	 */
	Const_Iterator begin() const
	{
		return Const_Iterator(head->next);
	}
	
	/**
	 * Returns an const iterator wich is directed the end of the List (tail).
	 */
	Const_Iterator end() const
	{
		return Const_Iterator(tail);
	}
	
	/**
	 * Pushes an (named) entry at the front of the list.
	 * @param value Pass the value you have determined at the template specifier \<T\>.
	 * @param name A special feature of StringList: You can name the entrys (optional).
	 * The default name is "".
	 */
	void push_front(T value, string name = "")
	{
		StringListNode<T> *tmp = new StringListNode<T>(value, name);
		
		tmp->next = head->next;
		tmp->previous = head;
		head->next->previous = tmp;
		head->next = tmp;
	}
	
	/**
	 * The front entry of the list will removed, if the list isn't empty.
	 * If the list is empty nothing happens.
	 */
	void pop_front()
	{
		if (!empty())
		{
			StringListNode<T> *tmp = head->next->next;
			
			delete head->next;
			head->next = tmp;
			tmp->previous = head;
		}
	}
	
	/**
	 * Getter for the front entry of the list. Note: If there is no entry, an assert
	 * will occure! First check with isEmpty() if there is an entry at all.
	 * @return The front entry value of the list.
	 */
	T front() const
	{
		if (!empty())
			return head->next->value;
		else
		{
			assert("StringList is empty! front() is forbidden!");
			return 0;
		}
	}
	
	
	/**
	 * Special feature of StringList: Returns the front entrys name of the list.
	 * Note: If there is no entry, an assert will occure! First check with isEmpty() if
	 * there is an entry at all.
	 * @return The name of the front entry as std::string.
	 */
	string frontName() const
	{
		if (!empty())
			return head->next->name;
		else
		{
			assert("StringList is empty! frontName() is forbidden!");
			return 0;
		}
	}
	
	
	/**
	 * Pushes an (named) entry at back of the list.
	 * @param value Pass the value you have determined at the template specifier \<T\>.
	 * @param name A special feature of StringList: You can name the entrys (optional).
	 * The default name is "".
	 */
	void push_back(T value, string name = "")
	{
		StringListNode<T> *tmp = new StringListNode<T>(value, name);

		tmp->next = tail;
		tmp->previous = tail->previous;
		tail->previous->next = tmp;
		tail->previous = tmp;
	}
	
	
	/**
	 * The back entry of the list will removed, if the list isn't empty.
	 * If the list is empty nothing happens.
	 */
	void pop_back()
	{
		if (!empty())
		{
			StringListNode<T> *tmp = tail->previous->previous;
			
			delete tail->previous;
			tail->previous = tmp;
			tmp->next = tail;
		}
	}
	
	
	/**
	 * Getter for the back entry of the list. Note: If there is no entry, an assert
	 * will occure! First check with isEmpty() if there is an entry at all.
	 * @return The back entry value of the list.
	 */
	T back() const
	{
		if(!empty())
			return tail->previous->value;
		else
		{
			assert("StringList is empty! back() is forbidden!");
			return 0;
		}
	}
	
	
	/**
	 * Special feature of StringList: Returns the back entrys name of the list.
	 * Note: If there is no entry, an assert will occure! First check with isEmpty() if
	 * there is an entry at all.
	 * @return The name of the back entry as std::string.
	 */
	string backName() const
	{
		if(!empty())
			return tail->previous->name;
		else
		{
			assert("StringList is empty! backName() is forbidden!");
			return 0;
		}
	}
	
	
	/**
	 * Transferes the complete sourceStringList to an appointed place in this list (one
	 * entry before the iterator position). After this operation the sourceStringList will be empty.
 	 * It's a efficiently operation: O(1).
	 * @param position Specifies the position in this list the copy will paste. After the
	 * insertion the iterator shows the next entry after insertion.
	 * @param sourceStringList The source list wich entrys will completely shifted to this list.
	 */
	void splice(Iterator &position, StringList<T> &sourceStringList)
	{
		assert("source list should not be the list itself" && sourceStringList != *this);
		
		StringListNode<T> *insert = position.currentNode;
		insert->previous->next = sourceStringList.head->next;
		sourceStringList.head->next->previous = insert->previous;
		
		sourceStringList.tail->previous->next = insert;
		insert->previous = sourceStringList.tail->previous;
		
		sourceStringList.head->next = sourceStringList.tail;
		sourceStringList.tail->previous = sourceStringList.head;
	}
	
	
	/**
	 * Transferes a single entry from sourceStringList to an appointed place in this list
	 * (one entry before the iterator position).\n
	 * The entry will removed from sourceStringList and added in sourceStringList.
 	 * It's a efficiently operation: O(1).
	 * @param position Specifies the position in this list the copy will paste. After the
	 * insertion the iterator shows the next entry after insertion.
	 * @param sourceStringList The source list wich entry will shifted to this list.
	 * @param sourceElement The place of the entry in source list who will be moved.
	 * After the operation the iterator shows the entry after the removed.
	 */
	void splice(Iterator &position, StringList<T> &sourceStringList, Iterator &sourceElement)
	{
		assert("source list should not be the list itself" && sourceStringList != *this);
	
		StringListNode<T> *insert = position.currentNode;
		StringListNode<T> *element = sourceElement.currentNode;
		++sourceElement;
		
		element->previous->next = element->next;
		element->next->previous = element->previous;
		
		insert->previous->next = element;
		element->previous = insert->previous;
		
		element->next = insert;
		insert->previous = element;
	}
	
	
	/**
	 * Transferes a range (start to end iterator) of entries from sourceStringList to
	 * an appointed place in this list (one entry before the iterator position).\n
	 * The entries will removed from sourceStringList and added in sourceStringList.\n
	 * Note: The start and end iterators must directed to sourceStringList.\n
	 * If the end iterator isn't linked to sourceStringList, the transfer stops on the 
	 * end of sourceStringList. 
 	 * It's a efficiently operation: O(1).
	 * @param position Specifies the position in this list the copy will paste. After the
	 * insertion the iterator shows the next entry after insertion.
	 * @param sourceStringList The source list wich entries will shifted to this list.
	 * @param start The start marker (iterator) of the range in source list. After the
	 * operation the iterator shows the entry in source list after the end iterator.
	 * @param end The end marker (iterator) of the range in source list.
	 */
	void splice(Iterator &position, StringList<T> &sourceStringList, Iterator &start, Iterator &end)
	{
		assert("source list should not be the list itself" && sourceStringList != *this);

		StringListNode<T> *insert = position.currentNode;
		StringListNode<T> *s = start.currentNode;
		StringListNode<T> *e = end.currentNode;
		
		s->previous->next = e->next;
		e->next->previous = s->previous;
		
		insert->previous->next = s;
		s->previous = insert->previous;
		
		e->next = insert;
		insert->previous = e;
	}
	
	
	/**
	 * Swaps another list with this one in constant time.
	 * @param list The other list, this list will swapped with.
	 */
	void swap(StringList<T> &list)
	{
		vs::base::cont::swap(*this, list);
	}
	
	/**
	 * Deletes an entry in the StringList with an iterator.
	 * @param position An iterator shows the position in StringList to delete an entry.\n
	 * Note: After a deletion the iterator shows to the next entry!
	 * @return Iterator to the new position (after deletion).
	 */
	Iterator erase(Iterator &position)
	{
		assert ("first you must inizialize the iterator!" && position.currentNode != NULL);
		assert ("iterator is directed to a wrong entry. Can't erase this!" && position.currentNode != head && position.currentNode != tail);
		
		StringListNode<T> *tmp = position.currentNode->next;
		position.currentNode->previous->next = position.currentNode->next;
		position.currentNode->next->previous = position.currentNode->previous;
		delete position.currentNode;
		
		position.currentNode = tmp;
		return position;
	}

	
	/**
	 * Deletes several entries in the StringList with two iterators.
	 * @param first The start position in StringList of the entries to delete.
	 * @param last The last position in StringList of the entries to delete.
	 * @return Iterator to the new position (after deletion).
	 */
	Iterator erase(Iterator &first, Iterator &last)
	{
		assert ("first you must inizialize the two iterators!" && first.currentNode != NULL && last.currentNode != NULL);
		assert ("first iterator is directed to a wrong entry. Can't erase this!" && first.currentNode != head && first.currentNode != tail);
		assert ("last iterator is directed to a wrong entry. Can't erase this!" && last.currentNode != head && last.currentNode != tail);
		
		StringListNode<T> *tmp = first.currentNode;
		first.currentNode = first.currentNode->previous;
		last.currentNode = last.currentNode->next;

		while(tmp != last.currentNode)
		{
			tmp = tmp->next;
			delete tmp->previous;
		}
		
		first.currentNode->next = last.currentNode;
		last.currentNode->previous = first.currentNode;
		
		first.currentNode = last.currentNode;
		return first;
	}
	
	/**
	 * Inserts an entry in the StringList with an iterator. The entry will be added before
	 * the iteratiors indication.
	 * @param position An entry will be added before this position.
	 * @param value The entry value who will insert before the position.
	 * @param name The name of the new entry value (optional). The default name is "".
	 * @return Iterator to the new entry.
	 */
	Iterator insert(Iterator &position, const T value, string name = "")
	{
		assert ("first you must inizialize the iterator!" && position.currentNode != NULL);
		assert("iterator is directed to a wrong entry. Can't insert entry there!" && position.currentNode != head);
		
		StringListNode<T> *tmp = new StringListNode<T>(value, name);
		
		position.currentNode->previous->next = tmp;
		tmp->previous = position.currentNode->previous;
		
		position.currentNode->previous = tmp;
		tmp->next = position.currentNode;
		
		position.currentNode = tmp;
		return tmp;
	}
	
	/**
	 * Search an entry by name and checks if the entry exist.\n
	 * Note: If there are several entrys with the same name, the first match will
	 * returned! The items must be names useful.
	 * @code // Usage example
	 * StringList<int> ids;
	 * ids.push_front(55, "glHouse");
	 * ids.push_front(46, "glTree");
	 * ...
	 * int id;
	 * if (ids.byName("glTree", id))
	 *     cout << "the glTree id is: " << id << endl;
	 * else
	 *     cout << "there is no glTree id!" << endl;
	 * @endcode
	 * 
	 * @param name The name of the searched entry.
	 * @param value If the entry was found, it will returned by the value reference.
	 * If the entry was not found, the value will be -1.
	 * @return Check if the entry was found (true) or not exist (false).
	 */
	bool byName(const string &name, T &value) const
	{
		// todo: optimierungen, z.b. cache ...
		
		StringListNode<T> *tmp = head;
		while (tmp->next != tail)
		{
			if (tmp->next->name == name)
			{
				value = tmp->next->value;
				return true;
			}
			tmp = tmp->next;
		}
		return false;
	}
	
	/**
	 * Search an entry by name and checks if the entry exist.\n
	 * Note: If there are several entrys with the same name, the first match will
	 * returned! The items must be names useful.
	 * @param name The name of the searched entry.
	 * @param it If the entry was found, an iterator wich is directed to it will returned.
	 * @return Check if the entry was found (true) or not exist (false).
	 */
	bool byName(const string &name, Iterator &it) const
	{
		// todo: optimierungen, z.b. cache ...		

		StringListNode<T> *tmp = head;
		while (tmp->next != tail)
		{
			if (tmp->next->name == name)
			{
				it = Iterator(tmp->next);
				return true;
			}
			tmp = tmp->next;
		}
		return false;
	}

	/**
	 * Search an entry by name and checks if the entry exist.\n
	 * Note: If there are several entrys with the same name, the first match will
	 * returned! The items must be names useful.\n
	 * The advantage of using JavaStryleIterator is thas you can programming with an
	 * abstract iterator and its save! When the entry is not found, a NullIterarot will
	 * returned.
	 * @param name The name of the searched entry.
	 * @param it If the entry was found, an iterator wich is directed to it will returned.
	 * @return Check if the entry was found (true) or not exist (false).
	 * @see JavaStyleIterator, NullIterator
	 */
	bool byName(const string &name, SmartIterator<T> &it) const
	{
		// todo: speicherleiche entfernen
		
		StringListNode<T> *tmp = head;
		while (tmp->next != tail)
		{
			if (tmp->next->name == name)
			{
				it = SmartIterator<T>(new Iterator(tmp->next));
				return true;
			}
			
			tmp = tmp->next;
		}
		it = SmartIterator<T>(new NullIterator<T>());
		return false;
	}
	
	/**
	 * Special feature of StringList.\n
	 * Search an entry by name and returns an iterator on it. If the searched name does
	 * not exist, the iterator on the end of the list will be returned. Check this with
	 * @code // Example
	 * StringList<char *>::iterator it;
	 * it = myList.findByName("Adress");
	 * if (it != myList.end())
	 *     printf("%s\n", *it);		// output: 78357 Stockach (for example)
	 * @endcode
	 * 
	 * @param name The name of the searched entry.
	 * @return Iterator to the first found found entry (if exists) or to the end of the list.
	 */
	Iterator findByName(const string name)
	{
		StringListNode<T> *tmp = head;
		while (tmp->next != tail)
		{
			if (tmp->next->name == name)
			{
				return Iterator(tmp->next);
			}
			tmp = tmp->next;
		}
		return Iterator(tail);
	}
	
	/**
	 * A search method in STL style.\n
	 * Search an entry by value and returns an iterator on it. If the searched name does
	 * not exist, the iterator on the end of the list will be returned. Check this with
	 * @code // Example
	 * StringList<char *>::iterator it;
	 * it = myList.find(55);
	 * if (it != myList.end())
	 *     printf("%d\n", *it);		// output: 55
	 * @endcode
	 * 
	 * @return Iterator to the first found entry (if exists) or to the end of the list.
	 */
	Iterator find(const T value)
	{
		StringListNode<T> *tmp = head;
		while (tmp->next != tail)
		{
			if (tmp->next->value == value)
			{
				return Iterator(tmp->next);
			}
			tmp = tmp->next;
		}
		return Iterator(tail);
	}
	
	/**
	 * All entrys will be cleared. After this operation the container is empty.
	 * Of course you can refill it.
	 */
	void clear()
	{
		StringListNode<T> *tmp;
		while (head->next != tail)
		{
			tmp = head->next->next;
			delete head->next;
			head->next = tmp;
		}
		tail->previous = head;
	}
	
	/**
	 * Count the number of all entrys in the list and returns it. Optional you can count the
	 * entries by name.
	 * @param name Count the number of entries named with "name". If you don't pass an
	 * argument, all entries will count (like size()).
	 * @return The number of entries.
	 */
	int count(const string &name = "") const
	{
		if (name == "")
			return size();
		else
		{
			int num = 0;
			if (empty())
				return 0;
			
			StringListNode<T> *tmp = head->next;
			while(tmp->next != tail)
			{
				if (name == tmp->name)
					++num;
				tmp = tmp->next;
			}
			if (name == tmp->name)
				++num;
			
			return num;
		}
	}
	
	/**
	 * Count the number of values in the list and return it. Overloaded method.
	 * @param value The value the method will searched with.
	 * @return The number of entries.
	 */
	int count(const T value) const
	{
		if (empty())
			return 0;
		
		int num = 0;
		StringListNode<T> *tmp = head->next;
		while (tmp->next != tail)
		{
			if (value == tmp->value)
				++num;
			tmp = tmp->next;
		}
		if (value == tmp->value)
			++num;
		
		return num;
	}

	/**
	 * Count the number of all entrys in the list and returns it. 
	 * @return The number of entrys.
	 */
	int size() const
	{
		if (empty())
			return 0;
		else
		{
			int num = 1;
			StringListNode<T> *tmp = head->next;
			while(tmp->next != tail)
			{
				++num;
				tmp = tmp->next;
			}
			return num;
		}
	}

	/**
	 * Check if there is a entry or not.
	 * @return If there is no entry it returns true.
	 */
	bool empty() const
	{
		if (head->next == tail)
			return true;
		else
			return false;
	}
	
	/**
	 * Cout all entries names to the std console. Useful for debugging. Note that
	 * only the name will be printed!
	 */
	void coutNames() const
	{
		StringListNode<T> *tmp = head;
		while (tmp->next != tail)
		{
			tmp = tmp->next;
			cout << tmp->name << endl;
		}
	}
	
	// global swap for StringList
	friend void vs::base::cont::swap<T>(StringList<T> &list_1, StringList<T> &list_2);

private:
	StringListNode<T> *head;
	StringListNode<T> *tail;
};


/**
 * An entry node used by the StringList class. It contains a name and a template value.\n
 * Note: You don't must touch this!
 * @see StringList
 */
template <class T>
class VS_EXPORT StringListNode
{
public:
	StringListNode(T value, string name = "")
	:name(name), value(value)
	{
		this->next = NULL;
		this->previous = NULL;
	}
	StringListNode(string name = "")
	:name(name)
	{
		this->next = NULL;
		this->previous = NULL;
	}

	friend class StringList<T>;
	friend class StringList<T>::Iterator;
	friend class StringList<T>::Const_Iterator;

private:
	string name;
	StringListNode<T> *next;
	StringListNode<T> *previous;
	T value;
};


} // cont
} // base
} // vs

#endif	// STRING_LIST_H
