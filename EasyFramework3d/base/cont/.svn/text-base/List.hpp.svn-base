/**
 * @file List.hpp
 * @author sizilium
 * @date 01.06.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef VS_UT_LIST_H
#define VS_UT_LIST_H

#include <vs/Build.hpp>
#include <string>
#include <assert.h>
#include <stdio.h>
#include <iterator>
#include <vs/base/cont/JavaStyleIterator.hpp>
#include <vs/base/cont/JavaStyleContainer.hpp>
#include <vs/base/cont/NullIterator.hpp>

namespace vs
{
namespace base
{
namespace cont
{
// predeclarations
template <class T> class SmartIterator;
template <class T> class ListNode;
template <class T> class List;

using namespace std;


/**
 * Global function wich swappes two List's.
 * @code // Example
 * List<MyClass *> list_1, list_2;
 * ...
 * swap(list_1, list_2);		// swapping by global function
 * list_1.swap(list_2);			// swapping by List method
 * 
 * @endcode
 * @param list_1 Pass the first list (reference).
 * @param list_2 Pass the second list (reference).
 */
template<class T>
VS_EXPORT void swap(List<T> &list_1, List<T> &list_2)
{
	ListNode<T> *tmp;

	tmp = list_1.head;
	list_1.head = list_2.head;
	list_2.head = tmp;

	tmp = list_1.tail;
	list_1.tail = list_2.tail;
	list_2.tail = tmp;
}


/** @class List
 * A vision-synthesis template container like the stl list pattern. But List can
 * contain pointers (it's safe) and the members can searched by a string name (optional).\n
 * List supports an iterator who can both: Java and STL styled access.\n
 * It is a double linked list. There are many assertions to catch some errors. If you want
 * to disable it (for more performance) write \#define NDEBUG in this header.\n
 * The container is tested regularly with several CppUnit "http://sourceforge.net/projects/cppunit" 
 * test but notice that no warranty is given.
 */
template <class T> 
class VS_EXPORT List : public JavaStyleContainer<T>
{
public:
	/**
	 * After initialization the container is empty. 
	 */
	List()
	{
		head = new ListNode<T>();
		tail = new ListNode<T>();
		head->next = tail;
		head->previous = NULL;
		tail->next = NULL;
		tail->previous = head;
	}

	List(const List<T> &list)
	{
		this->addAll(&list);
	}
	
	/**
	 * All entrys will be cleared.
	 * @see clear
	 */
	virtual ~List()	
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
	List<T>& operator=(const List<T>& op2)
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
	bool operator== (const List<T>& op2) const
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
	bool operator!= (const List<T> &op2) const
	{
		return !(*this == op2);
	}
	
	/**
	 * This is the iterator for List. It implements JavaStyleIterator, means that
	 * the common methods hasNext, next and remove available. STL style operation are
	 * possible too, like ++, --, = and * operations. STL algorithm are also possible
	 * (this is an STL bidirectional_iterator).\n
	 * If you try to use an uninitialized iterator an assert will occure.\n
	 * Note: EasyFramework use strictly name conventions: Classes are all upper case
	 * and also the Iterator class.
	 * 
	 * @code // Usage-Exampe:
	 * List<int> list;
	 * List.push_front(15);
	 * List.push_front(10);
	 * List.push_front(5);
	 * 
	 * //Java style:
	 * List<int>::Iterator it(list);
	 * while (it.hasNext())
	 *     cout << it.next() << " ";				// output is: 5 10 15
	 * 
	 * // STL style:
	 * List<int>::Iterator itc = list.begin();
	 * while (itc != list.end())
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
		friend class List<T>;
		
		/**
		 * You need no parameters for an iterator, but before the first use the iterator
		 * must be initialized (with '=' operator for example).
		 * @param node Optional parameter to direct the iterator to an ListNode. 
		 * Only for internal use. 
		 */
		Iterator(ListNode<T> *node = NULL) :currentNode(node) {}

		/**
		 * A useful iterator initialization. Pass a list to the constructor parameter to
		 * direct the iterator to the first entry of the list.
		 * @param list The target list for the iterator
		 */
		Iterator(List<T> &list)
		{
			*this = list.begin();
		}
		
		/**
		 * Copyconstructor.
		 * @param it Iterator to copy.
		 */
		Iterator(const Iterator &it)
		{
			currentNode = it.currentNode;
		}

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
		 * Returns the currentNode entry without iterater shifting (additional vs method, no java
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
			assert ("there are no more entrys in the List, call hasNext() first!" && currentNode->next != NULL);
			currentNode = currentNode->next;
			return tmp;
		}

		/**
		 * Removes the current entry and push the iterator to the next entry. 
		 */
		void remove()
		{
			assert ("first you must inizialize the iterator!" && currentNode != NULL);
			ListNode<T> *tmp = currentNode->next;
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
			assert ("there are no more entrys in the List, call  if (it==list.end())  first!" && currentNode->next != NULL);
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
			assert ("there are no more entrys in the List, call  if (it==list.begin())  first!" && currentNode->previous != NULL);
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
		 * ListNode, say to the same entry of a list. 
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
		ListNode<T> *currentNode;
	};
	
	
	/**
	 * This is the Const_Iterator for List. It implements JavaStyleIterator, means that
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
		friend class List<T>;
		
		/**
		 * You need no parameters for an iterator, but before the first use the iterator
		 * must be initialized (with '=' operator for example).
		 * @param node Optional parameter to direct the iterator to an ListNode. 
		 * Only for internal use. 
		 */
		Const_Iterator(const ListNode<T> *node = NULL) :currentNode(node) {}

		/**
		 * Overloaded constructor for more const compability (Const_Iterator must be able
		 * to direct to an const ListNode and a ListNode).
		 */
		Const_Iterator(ListNode<T> *node)
		:currentNode(const_cast<const ListNode<T>*>(node) )
		{}
		
		/**
		 * A useful iterator initialization. Pass a list to the constructor parameter to
		 * direct the iterator to the first entry of the list.
		 * @param list The target list for the iterator
		 */
		Const_Iterator(const List<T> &list)
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
		 * @return The iterator with new position. 
		 */
		T next()
		{
			assert ("first you must inizialize the Const_Iterator!" && currentNode != NULL);
			T tmp = currentNode->value;
			assert ("there are no more entrys in the List, call hasNext() first!" && currentNode->next != NULL);
			currentNode = currentNode->next;
			return tmp;
		}

		/**
		 * Removes the current entry and push the iterator to the next entry. 
		 */
		void remove()
		{
			// not in Const_Iterator
			// TODO throw Exception here?
			
			/*
			assert ("first you must inizialize the Const_Iterator!" && currentNode != NULL);
			ListNode<T> *tmp = currentNode->next;
			currentNode->previous->next = currentNode->next;
			currentNode->next->previous = currentNode->previous;
			delete currentNode;
			currentNode = tmp;
			*/
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
			assert ("there are no more entrys in the List, call  if (it==list.end())  first!" && currentNode->next != NULL);
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
			assert ("there are no more entrys in the List, call  if (it==list.begin())  first!" && currentNode->previous != NULL);
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
		 * ListNode, say to the same entry of a list. 
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
		const ListNode<T> *currentNode;
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
	 * Returns an iterator wich is directed to the beginning of the List (head->next). If the list
	 * is empty, the iterator will directed to the tail of the list (no error).\n
	 * Note: Check with empty() if there is an entry first!
	 * @return An iterator to the first entry.
	 */
	Iterator begin()
	{
		return Iterator(head->next);
	}
	
	/**
	 * Returns an iterator wich is directed the end of the List (tail).
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
	 * Pushes an entry at the front of the list.
	 * @param value Pass the value you have determined at the template specifier \<T\>.
	 * The default name is "".
	 */
	void push_front(T value)
	{
		ListNode<T> *tmp = new ListNode<T>(value);
		
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
			ListNode<T> *tmp = head->next->next;
			
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
			assert("List is empty! front() is forbidden!");
			return 0;
		}
	}
		
	/**
	 * Pushes an entry at back of the list.
	 * @param value Pass the value you have determined at the template specifier  \<T\>.
	 * The default name is "".
	 */
	void push_back(T value)
	{
		ListNode<T> *tmp = new ListNode<T>(value);

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
			ListNode<T> *tmp = tail->previous->previous;
			
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
			assert("List is empty! back() is forbidden!");
			return 0;
		}
	}

	/**
	 * Transferes the complete sourceList to an appointed place in this list (one
	 * entry before the iterator position). After this operation the sourceList will be empty.
	 * It's a efficiently operation: O(1).
	 * @param position Specifies the position in this list the copy will paste. After the
	 * insertion the iterator shows the next entry after insertion.
	 * @param sourceList The source list wich entrys will completely shifted to this list.
	 */
	void splice(Iterator &position, List<T> &sourceList)
	{
		assert("source list should not be the list itself" && sourceList != *this);
		
		ListNode<T> *insert = position.currentNode;
		insert->previous->next = sourceList.head->next;
		sourceList.head->next->previous = insert->previous;
		
		sourceList.tail->previous->next = insert;
		insert->previous = sourceList.tail->previous;
		
		sourceList.head->next = sourceList.tail;
		sourceList.tail->previous = sourceList.head;
	}
	
	/**
	 * Transferes a single entry from sourceList to an appointed place in this list
	 * (one entry before the iterator position).\n
	 * The entry will removed from sourceList and added in this List.
 	 * It's a efficiently operation: O(1).
	 * @param position Specifies the position in this list the copy will paste. After the
	 * insertion the iterator shows the next entry after insertion.
	 * @param sourceList The source list wich entry will shifted to this list.
	 * @param sourceElement The place of the entry in source list who will be moved.
	 * After the operation the iterator shows the entry after the removed.
	 */
	void splice(Iterator &position, List<T> &sourceList, Iterator &sourceElement)
	{
		assert("source list should not be the list itself" && sourceList != *this);
	
		ListNode<T> *insert = position.currentNode;
		ListNode<T> *element = sourceElement.currentNode;
		++sourceElement;
		
		element->previous->next = element->next;
		element->next->previous = element->previous;
		
		insert->previous->next = element;
		element->previous = insert->previous;
		
		element->next = insert;
		insert->previous = element;
	}
	
	/**
	 * Transferes a range (start to end iterator) of entries from sourceList to
	 * an appointed place in this list (one entry before the iterator position).\n
	 * The entries will removed from sourceList and added in sourceList.\n
	 * Note: The start and end iterators must directed to sourceList.\n
	 * If the end iterator isn't linked to sourceList, the transfer stops on the 
	 * end of sourceList. 
 	 * It's a efficiently operation: O(1).
	 * @param position Specifies the position in this list the copy will paste. After the
	 * insertion the iterator shows the next entry after insertion.
	 * @param sourceList The source list wich entries will shifted to this list.
	 * @param start The start marker (iterator) of the range in source list. After the
	 * operation the iterator shows the entry in source list after the end iterator.
	 * @param end The end marker (iterator) of the range in source list.
	 */
	void splice(Iterator &position, List<T> &sourceList, Iterator &start, Iterator &end)
	{
		assert("source list should not be the list itself" && sourceList != *this);

		ListNode<T> *insert = position.currentNode;
		ListNode<T> *s = start.currentNode;
		ListNode<T> *e = end.currentNode;
		
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
	void swap(List<T> &list)
	{
		base::cont::swap(*this, list);
	}

	/**
	 * Deletes an entry in the List with an iterator.
	 * @param position An iterator shows the position in List to delete an entry.\n
	 * Note: After a deletion the iterator shows to the next entry!
	 * @return Iterator to the new position (after deletion).
	 */
	Iterator erase(Iterator &position)
	{
		assert ("first you must inizialize the iterator!" && position.currentNode != NULL);
		assert ("iterator is directed to a wrong entry. Can't erase this!" && position.currentNode != head && position.currentNode != tail);
		
		ListNode<T> *tmp = position.currentNode->next;
		position.currentNode->previous->next = position.currentNode->next;
		position.currentNode->next->previous = position.currentNode->previous;
		delete position.currentNode;
		
		position.currentNode = tmp;
		return position;
	}

	/**
	 * Deletes several entries in the List with two iterators.
	 * @param first The start position in List of the entries to delete.
	 * @param last The last position in List of the entries to delete.
	 * @return Iterator to the new position (after deletion).
	 */
	Iterator erase(Iterator &first, Iterator &last)
	{
		assert ("first you must inizialize the two iterators!" && first.currentNode != NULL && last.currentNode != NULL);
		assert ("first iterator is directed to a wrong entry. Can't erase this!" && first.currentNode != head && first.currentNode != tail);
		assert ("last iterator is directed to a wrong entry. Can't erase this!" && last.currentNode != head && last.currentNode != tail);
		
		ListNode<T> *tmp = first.currentNode;
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
	 * Inserts an entry in the List with an iterator. The entry will be added before
	 * the iteratiors indication.
	 * @param position An entry will be added before this position.
	 * @param value The entry value who will insert before the position.
	 * @return Iterator to the new entry.
	 */
	Iterator insert(Iterator &position, const T value)
	{
		assert ("first you must inizialize the iterator!" && position.currentNode != NULL);
		assert("iterator is directed to a wrong entry. Can't insert entry there!" && position.currentNode != head);
		
		ListNode<T> *tmp = new ListNode<T>(value);
		
		position.currentNode->previous->next = tmp;
		tmp->previous = position.currentNode->previous;
		
		position.currentNode->previous = tmp;
		tmp->next = position.currentNode;
		
		position.currentNode = tmp;
		return tmp;
	}
	
	/**
	 * All entrys will be cleared. After this operation the container is empty.
	 * Of course you can refill it.
	 */
	void clear()
	{
		ListNode<T> *tmp;
		while (head->next != tail)
		{
			tmp = head->next->next;
			delete head->next;
			head->next = tmp;
		}
		tail->previous = head;
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
		ListNode<T> *tmp = head->next;
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
	 * Overloaded method. Count all elements (like size()).
	 * @return The number of entries.
	 */
	int count() const
	{
		return size();
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
		ListNode<T> *tmp = head;
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
			ListNode<T> *tmp = head->next;
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
	
	// global swap for List
	friend void vs::base::cont::swap<T>(List<T> &list_1, List<T> &list_2);

private:
	ListNode<T> *head;
	ListNode<T> *tail;
};


/**
 * An entry node used by the List class. It contains a name and a template value.\n
 * Note: You don't must touch this!
 * @see List
 */
template <class T>
class VS_EXPORT ListNode
{
public:
	ListNode(T value)
	:value(value)
	{
		this->next = NULL;
		this->previous = NULL;
	}
	ListNode()
	{
		this->next = NULL;
		this->previous = NULL;
	}

	friend class List<T>;
	friend class List<T>::Iterator;
	friend class List<T>::Const_Iterator;

private:
	ListNode<T> *next;
	ListNode<T> *previous;
	T value;
};


} // cont
} // base
} // vs

#endif	// VS_UT_LIST_H
