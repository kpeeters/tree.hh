#include "tree.hh"
#include <iostream>

// This example shows how to iterate over the head nodes
// of a tree only. 

int main(int, char **)
   {
   tree<std::string> t;

   t.set_head("one");
   auto i2 = t.insert(t.end(), "two");
   auto i3 = t.insert(t.end(), "three");
   t.append_child(i2, "apple");
   t.append_child(i2, "pear");   
   t.append_child(i3, "banana");
   t.append_child(i3, "kiwi");   

   tree<std::string>::sibling_iterator it=t.begin();
   while(it!=t.end())
	   std::cerr << (*it++) << std::endl;
   }
