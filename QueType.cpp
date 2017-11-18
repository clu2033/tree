#include <cstddef>                 // For NULL
#include <new>                     // For bad_alloc
#include "QueType.h"

struct NodeType
{
  ItemType info;
  NodeType* next;
};

// template<class ItemType>
// QueType<ItemType>::QueType()
QueType::QueType()
// Post:  front and rear are set to NULL.
{
  front = NULL;
  rear = NULL;
}

// template<class ItemType>
// void QueType<ItemType>::MakeEmpty()
void QueType::MakeEmpty()
// Post: Queue is empty; all elements have been deallocated.
{
  NodeType* tempPtr;

    while (front != NULL)
  {
    tempPtr = front;
    front = front->next;
    delete tempPtr;
  }
  rear = NULL;
}

// template<class ItemType>
// QueType<ItemType>::~QueType()
QueType::~QueType()
{
  MakeEmpty();
}

// template<class ItemType>
// bool QueType<ItemType>::IsFull() const
bool QueType::IsFull() const
// Returns true if there is no room for another ItemType 
//  on the free store; false otherwise.
{
  NodeType* location;
  try
  {
    location = new NodeType;
    delete location;
    return false;
  }
  catch(std::bad_alloc)
  {
    return true;
  }
}

// template<class ItemType>
// bool QueType<ItemType>::IsEmpty() const
bool QueType::IsEmpty() const
{
  return (front == NULL);
}

// template<class ItemType>
// void QueType<ItemType>::Enqueue(ItemType newItem)
void QueType::Enqueue(ItemType newItem)
// Adds newItem to the rear of the queue.
// Pre:  Queue has been initialized.
// Post: If (queue is not full) newItem is at the rear of the queue;
//       otherwise a FullQueue exception is thrown.  
{
  if (IsFull())
    throw FullQueue();
  else
  {
    NodeType* newNode;
    newNode = new NodeType;
    newNode->info = newItem;
    newNode->next = NULL;
    if (rear == NULL)
      front = newNode;
    else
      rear->next = newNode;
    rear = newNode;
  }
}

// template<class ItemType>
// void QueType<ItemType>::Dequeue(ItemType& item)
void QueType::Dequeue(ItemType& item)
// Removes front item from the queue and returns it in item.
// Pre:  Queue has been initialized and is not empty.
// Post: If (queue is not empty) the front of the queue has been 
//       removed and a copy returned in item; 
//       othersiwe a EmptyQueue exception has been thrown.
{
  if (IsEmpty())
    throw EmptyQueue();
  else
  {
    NodeType* tempPtr;

    tempPtr = front;
    item = front->info;
    front = front->next;
    if (front == NULL)
      rear = NULL;
    delete tempPtr;
  }
}

// template<class ItemType>
// QueType<ItemType>::QueType(const QueType& anotherQue) 
QueType::QueType(const QueType& anotherQue) 
{
  NodeType* ptr1;
  NodeType* ptr2;
  
  if (anotherQue.front == NULL)
    front = NULL;
  else
  {
    front = new NodeType;
    front->info = anotherQue.front->info;
    ptr1 = anotherQue.front->next;
    ptr2 = front;
    while (ptr1 != NULL)
    {
      ptr2->next = new NodeType;
      ptr2 = ptr2->next;
      ptr2->info = ptr1->info;
      ptr1 = ptr1->next;
    }
    ptr2->next = NULL;
    rear = ptr2;
  }    
}

// template class QueType<int>;
// template class QueType<string>;
// template class QueType<char>;
