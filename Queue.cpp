/* File Name: Queue.cpp
 * Name: Kenny Sun
 * Date: 11/10/2023
 * Purpose: Source code for Queue object
 * Implementation of the queue data type, a first in first out data type that is constructed by a linked list.
 * Used in Cipher.cpp to encode and decode messages
 */

#include "Queue.h" //Source file needs own header file
#include <iostream> //Needed to print when the queue was empty for certain functions like dequeuing

/* Default Constructor */
//Creates a queue and sets the front and rear QueueNode pointers to nullptr
Queue::Queue()
{
  front = nullptr;
  rear = nullptr;
}

/* Destructor */
//Iterates through each node and deletes it
Queue::~Queue()
{
  QueueNode * deleteNode = front;
  while(deleteNode != nullptr)
    {
      front = front->next;
      deleteNode->next = nullptr;
      delete deleteNode;
      deleteNode = front;
    }
}

/* enqueue */
//Adds a character key to the rear of the queue
void Queue::enqueue(char key)
{
  //If the queue is empty, the front pointer is allocated memory for a brand new node and rear points to it since the front and rear are the same w/ only 1 node
  if(isEmpty())
    {
      front = new QueueNode(key);
      rear = front;
    }
  //Otherwise, the nullptr that the rear is pointing at becomes a new node with a key and the rear pointer points at that new node
  else
    {
      rear->next = new QueueNode(key);
      rear = rear->next;
    }
}

/* dequeue */
//Removes a node from the front of the queue and passes the node's key value through reference
void Queue::dequeue(char &output)
{
  //Temp pointer is intialized
  QueueNode * temp = nullptr;
  if(isEmpty())
    {
      cout << "The queue is empty." << endl;
      exit(1);
    }
  //If the queue isn't empty
  else
    {
      //The key passed through reference gets the information from the front
      output = front->key;
      //Temp stores the information at the front so it isn't lost
      temp = front;
      //Front moves down the queue to the next one in line while the original front is deleted
      front = front->next;
      delete temp;
    }
}

/* isEmpty */
//Returns whether or not the queue is empty
bool Queue::isEmpty() const
{
  if(front == nullptr)
    {
      return true;
    }
  else
    {
      return false;
    }
}

/* isFull */
//Iterates through the queue and counts the number of iterations there are and returns true if there are at least 100
bool Queue::isFull() const
{
  QueueNode * temp = front;
  int count = 1;
  if(isEmpty())
    {
      return false;
    }
  while(temp->next != nullptr)
    {
      temp = temp->next;
      count++;
    }
  if(count >= 100)
    {
      return true;
    }
  else
    {
      return false;
    }
}

/* printQueue */
//Iterates through the queue and prints out each value
//Primarily used for testing functionality of queue
void Queue::printQueue()
{
  if(isEmpty())
    {
      cout << "The queue is empty." << endl;
    }
  else
    {
      QueueNode * temp = front;
      while(temp->next != nullptr)
	{
	  cout << temp->key << " ";
	  temp = temp->next;
	}
      cout << temp->key << endl;
    }
}

/* clear */
//While the queue isn't empty, it keeps dequeueing to empty the queue
void Queue::clear()
{
  char dummy;
  while(!isEmpty())
  {
    dequeue(dummy);
  }
}
