#include <bits/stdc++.h>
using namespace std;

class Node
{
public:
  int key;
  int value;
  Node *prev;
  Node *next;
  Node(int key, int value)
  {
    this->key = key;
    this->value = value;
    this->prev = nullptr;
    this->next = nullptr;
  }
};
//          head      MRU               LRU      tail
// NULL <-{-1, -1}<->{3, 3}<->{2, 2}<->{1,1}<->{-1, -1} -> NULL

void printDLL(Node *head)
{
  Node *temp = head;
  cout << "null ";
  while (temp != NULL)
  {
    cout << "<-{" << temp->key << "," << temp->value << "}->" << "  ";
    temp = temp->next;
  }
  cout << " null" << endl;
}

class LRUCache
{
private:
  int capacity;
  Node *head;
  Node *tail;
  unordered_map<int, Node *> map;

  void addNode(Node *node)
  {
    // links for the newNode
    node->next = head->next;
    node->prev = head;

    // update left and right node's pointer
    head->next = node;
    node->next->prev = node;
  }

  void removeNode(Node *node)
  {
    Node *previousNode = node->prev;
    Node *nextNode = node->next;

    previousNode->next = nextNode;
    nextNode->prev = previousNode;
  }

public:
  LRUCache(int capacity)
  {
    this->capacity = capacity;
    head = new Node(-1, -1);
    tail = new Node(-1, -1);
    head->next = tail;
    tail->prev = head;
  }

  int get(int key)
  {
    if (map.find(key) != map.end())
    {
      Node *existingNode = map[key];
      removeNode(existingNode);
      addNode(existingNode);
      printDLL(head);
      return existingNode->value;
    }
    return -1;
  }

  void put(int key, int value)
  {
    if (map.find(key) != map.end())
    {
      // key exists
      // update the value
      // change the order
      Node *existingNode = map[key];
      existingNode->value = value;
      removeNode(existingNode);
      addNode(existingNode);
      printDLL(head);
      return;
    }
    if (map.size() == capacity)
    {
      cout << "max capacity reached\n";
      // remove the least recently used node
      // then add the new node
      Node *lruNode = tail->prev;
      removeNode(lruNode);
      map.erase(lruNode->key);
      delete lruNode;
    }

    // create and add the new node to the linkedlist
    Node *newNode = new Node(key, value);
    map[key] = newNode;
    addNode(newNode);
    printDLL(head);
  }
};

int main()
{

  LRUCache *cache = new LRUCache(3);
  cache->put(1, 1);
  cache->put(2, 2);
  cache->put(3, 3);
  cache->put(4, 4);
  cache->put(3, 5);
  cout << cache->get(2) << endl;
  return 0;
}