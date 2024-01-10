/* File Name: Queue.h
 * Name: Kenny Sun
 * Date: 11/10/2023
 * Purpose: Header file for Queue.cpp
 */

#ifndef QUEUE_H //Header files
#define QUEUE_H

using namespace std; //Needed to not type out std:: for every standard library function

class Queue
{
protected:
  //QueueNode structure
  struct QueueNode
  {
    //char value contains an arbitrary key that the node stores
    char key;
    //*next is a pointer to the next list node
    QueueNode *next;
    //Default constructor, saves a value as well as sets what the next pointer is, it's by default nullptr unless otherwise
    QueueNode(char key1, QueueNode *next1 = nullptr)
    {
      key = key1;
      next = next1;
    }
  };
  //List head pointer
  QueueNode *front;
  QueueNode *rear;
public:
  //Constructors and destructors
  Queue();
  ~Queue();

  //Member functions
  void enqueue(char);
  void dequeue(char &);
  bool isFull() const;
  bool isEmpty() const;
  void printQueue();
  void clear();
};

#endif
