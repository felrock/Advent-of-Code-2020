#include <algorithm>
#include <iostream>
#include <iterator>
#include <list>
#include <fstream>

class Node
{
public:
  Node(int v) : val(v) {}
  int val;
  Node* next;
};

int main(int argc, char** argv)
{
  std::fstream file(argv[1]);
  std::string s; // read single line input
  std::getline(file, s);

  Node* head;
  Node* prev;
  bool start = true;
  int width = 0;
  for(const auto& chr : s)
  {
    int num = chr - '0';
    if(start)
    {
      head = new Node(num);
      prev = head;
      start = false;
    }
    else
    {
      Node* next = new Node(num);
      prev->next = next;
      prev = next;
    }
    width++;
  }
  for(int i=s.size()+1; i < 10000001; ++i)
  {
    Node* next = new Node(i);
    prev->next = next;
    prev = next;
    width++;
  }
  int max   = 10000000;
  // wrap around
  prev->next = head;

  // iterate game
  int i=999990;
  const int iterations = 1000020;
  Node* current = head;
  int previus_dest = -1;
  while(i < iterations)
  {
    std::cout << "current " << current->val << std::endl;
    Node* first_node = current->next;
    Node* second_node = current->next->next;
    Node* third_node = current->next->next->next;

    current->next = current->next->next->next->next;

    // make sure that val is correct
    int val = current->val-1;
    while((val == first_node->val || val == second_node->val ||
           val == third_node->val || val == previus_dest) || val <= 0)
    {
      val--;
      if(val <= 0)
      {
        val = max;
      }
    }
    // walk until we find destination node
    std::cout << "val " << val << std::endl;
    Node* dest = current->next;
    while(dest->val != val)
    {
      if(dest->val == val)
      {
          break;
      }
      dest = dest->next;
    }
    std::cout << "dest " << dest->val << std::endl;
    previus_dest = dest->val;

    // attach the detached nodes to destination node
    Node* cont_nodes = dest->next;
    dest->next = first_node;
    dest->next->next = second_node;
    dest->next->next->next = third_node;
    dest->next->next->next->next = cont_nodes;
    std::cout << "first_node " << first_node->val << std::endl;
    std::cout << "second_node " << second_node->val << std::endl;
    std::cout << "third_node " << third_node->val << std::endl;
    std::cout << "current->next " << current->next->val << std::endl;

    // iterate
    i++;
    current = current->next;
  }
  std::cout << "done" << std::endl;
  Node* temp = head;
  for(int i=0; i < 100; ++i)
  {
    std::cout << temp->val << std::endl;
    temp = temp->next;
  }
  std::cout << temp->next->val << std::endl;

  return 0;
}
