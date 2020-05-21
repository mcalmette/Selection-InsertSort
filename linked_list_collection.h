//----------------------------------------------------------------------
// Author: Michael Calmette
//
// File:   linked_list_collection.h
//
// INFO: Selection and Insertion Sort with a linked list
//----------------------------------------------------------------------


#ifndef LINKED_LIST_COLLECTION_H
#define LINKED_LIST_COLLECTION_H

#include <vector>
#include <algorithm>
#include "collection.h"


template<typename K, typename V>
class LinkedListCollection : public Collection<K,V>
{
public:

  // constructor to initialize empty linked list
  LinkedListCollection();

  // copy constructor
  LinkedListCollection(const LinkedListCollection<K,V>& rhs);

  // assignment operator
  LinkedListCollection<K,V>& operator=(const LinkedListCollection<K,V>& rhs);
  
  // destructor to delete a linked list
  ~LinkedListCollection();
  
  // add a new key-value pair into the collection 
  void add(const K& a_key, const V& a_val);

  // remove a key-value pair from the collectiona
  void remove(const K& a_key);

  // find and return the value associated with the key
  bool find(const K& search_key, V& the_val) const;

  // find and return the values with keys >= to k1 and <= to k2 
  void find(const K& k1, const K& k2, std::vector<V>& vals) const;
  
  // return all of the keys in the collection 
  void keys(std::vector<K>& all_keys) const;

  // return all of the keys in ascending (sorted) order
  void sort(std::vector<K>& all_keys_sorted) const;

  // return the number of key-value pairs in the collection
  int size() const;

  // in place sorting 
  void selection_sort();
  void insertion_sort();
  
private:
  
  // linked list node structure
  struct Node {
    K key;
    V value;
    Node* next;
  };
  Node* head;
  Node* tail;
  int length;

  // helper to delete linked list (optional)
  void make_empty();

};


// TODO: Add Linked List Implementation here (from HW4)
// ... 


template<typename K, typename V>
LinkedListCollection<K,V>::LinkedListCollection() //constructor
{
   head = nullptr;
   tail = nullptr;
   length = 0;
}

//copy constructor
template<typename K, typename V>
LinkedListCollection<K,V>::LinkedListCollection(const LinkedListCollection<K,V>& rhs) 
{
    *this = rhs; //copy constructor
}

//assignment operator
template<typename K, typename V>
LinkedListCollection<K,V>& LinkedListCollection<K,V>::operator=(const LinkedListCollection<K,V>& rhs)
{
   //assign into existing object
   //delete lhs nodes
   //copy rhs to lhs
   if(this!= &rhs)
   {
	make_empty();
        head = nullptr;
	tail = nullptr;
 	length = 0;
	Node* tmp = rhs.head;
	while(tmp != nullptr)
	{
		add(tmp->key,tmp->value);
		tmp = tmp->next;
	}
	return *this;

   }
   return *this;
}


//Destructor
template<typename K, typename V>
LinkedListCollection<K,V>::~LinkedListCollection()
{
   make_empty(); //destructor
   head = nullptr;
   tail = nullptr;
}


template<typename K, typename V>
void LinkedListCollection<K,V>::add(const K& a_key, const V& v_val)
{
    Node* tmp = new Node;
    tmp->key = a_key;
    tmp-> value = v_val;
    if(length == 0) //empty list
    {
        head = tmp;
        tail = tmp;
        tmp -> next = nullptr;
    }
    else
    {
       tail-> next = tmp; //add to back
       tail = tmp;
       tail -> next = nullptr;   
    }
    length++;
}

template<typename K, typename V>
void LinkedListCollection<K,V>::remove(const K& a_key)
{
   Node* tmp1 = head;
   if((tmp1->key) == a_key) //if key is equal to the head
   {
	  head = head-> next;
 	  delete tmp1;
	  length--;
	  tmp1 = nullptr;
 	  return;
  }
    tmp1 = nullptr;

  Node* tmp = head;
  if(tmp->key == a_key)
  { 	
	if(length == 1) //get rid of list and make h/t null
	{
		head = nullptr;
		tail = nullptr;
	 	make_empty();
		length = 0;
		return;
	}
	else
	{
		head = tmp->next;
	}
	delete tmp;
	tmp = nullptr;
	length--;
	return;
  }

  while(tmp->next != nullptr) //anywhere else in list
  {
	if(tmp->next->key == a_key)
	{
		Node* ptr = tmp->next;
		tmp->next=ptr->next;
		delete ptr;
		ptr = nullptr;
		length=length-1;
		return;
	}
	tmp = tmp->next;
  }
}



template<typename K, typename V>
bool LinkedListCollection<K,V>::find(const K& search_key, V& the_val) const
{
  Node* tmp = head;
  while((tmp) != nullptr)
  {
      if(tmp->key == search_key)
   	{
		   the_val = tmp-> value; //set val
         tmp = nullptr;
	 	   return true; 
	   }
      tmp=tmp->next;
  }
   tmp = nullptr;
   return false;
}


template<typename K, typename V>
void LinkedListCollection<K,V>::find(const K& k1, const K& k2, std::vector<V>& vals) const
{
     Node* tmp = head;
     while(tmp != nullptr)
     {
	    if(tmp->key >= k1 && tmp->key <= k2) //compare
	     	vals.push_back(tmp->value); //add it to vector

	    tmp = tmp->next;
     }
     tmp = nullptr;
}


template<typename K, typename V>
void LinkedListCollection<K,V>::keys(std::vector<K>& all_keys) const
{
    Node* tmp = head;
    while(tmp != nullptr) //return all keys
    {
        all_keys.push_back(tmp->key);
	     tmp = tmp->next;
    }
   
}


template<typename K, typename V>
void LinkedListCollection<K,V>::sort(std::vector<K>& all_keys_sorted) const
{
   keys(all_keys_sorted); //use built in sort function
   std::sort(all_keys_sorted.begin(), all_keys_sorted.end());

}

template<typename K, typename V>
int LinkedListCollection<K,V>::size() const
{
    return length; //returns size
}


template<typename K, typename V>
void LinkedListCollection<K,V>::make_empty()
{
   while(head!= nullptr) //deletes all nodes
   {
	  Node* ptr = head;
	  head = head->next;
	  delete ptr;
	  length--;
   }

}


// TODO: Implement the two "in place" sorting algorithms below

template<typename K, typename V>
void LinkedListCollection<K,V>::selection_sort()
{
  if(size() <= 1)
   return;
  
   Node* cur = head;
   Node* tmp;
   Node* prevCur = nullptr;

   //increment sorted region
   while(cur -> next != nullptr)
   {
      Node* min = cur;
      tmp = cur -> next;
      //find smallest node from end of sorted region  ***
      while(tmp != nullptr)
      {
         if((tmp -> key) <= (min -> key))
            min = tmp;
         tmp = tmp -> next;
      }
      if(min == cur) //nothing smaller
         cur = cur -> next;
      
      Node* prevTmp = head;
      while(prevTmp -> next != min)
         prevTmp = prevTmp -> next;

      if((head -> key) > (min -> key)) //if min is smaller than head
      {
         //if smallest is at end
         if(min -> next == nullptr)
         {
            tail = prevTmp;
            tail -> next = nullptr;
         }
         else
         {
            prevTmp -> next = min -> next;
         }
         min -> next = cur;
         head = min;
         prevCur = head;
      } 
      else if ((head -> key) <= (min -> key)) //if smallest is at end
      {
         if(min -> next == nullptr)
         {
            tail = prevTmp;
            tail -> next = nullptr;
         }
         else
         {
            prevTmp -> next = min -> next;
         }
         min -> next = cur;
         prevCur -> next = min;
         prevCur = prevCur -> next;
      }
      
   }
  
}


template<typename K, typename V>
void LinkedListCollection<K,V>::insertion_sort()
{
  if(size() <= 1)
    return;
  
  Node* cur = head -> next;
  Node* prev = head;

  while(cur != nullptr)
  {
     if((prev -> key) >= (cur -> key))
     {
        //if cur next is at the end of list, need to
        //move the tail pointer
        if(cur -> next == nullptr)
        {
           tail = prev;
           tail -> next = nullptr;
        }
        //if the head prev is larger than the current index 
        prev -> next = cur -> next;
        if((head -> key) > (cur -> key))
        {
           //prev -> next = cur -> next;
           cur -> next = head;
           head = cur;
        } 
        //otherwise, find next node to insert
        else
        {
           Node* tmp = head;
           while((tmp -> next) -> key < cur -> key && tmp -> next != nullptr )
           {
               tmp = tmp -> next;
           }
           //prev -> next = cur -> next;
           cur -> next = tmp -> next;
           tmp -> next = cur; 
        }
     }
     else
     {
        cur = cur -> next;
        prev = prev -> next;
     }
   cur = prev -> next; //move index one over
  
  }

  cur = nullptr;
  prev = nullptr;
}


#endif
