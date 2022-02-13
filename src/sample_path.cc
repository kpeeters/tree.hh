
#include "tree.hh"
#include <iostream>

// Sample to demonstrate how to turn a tree iterator into a
// path_t, which is a vector of integers indicating which
// child is taken at any depth.

int main(int argc, char **argv)
   {
   tree<std::string> tr;

   tr.set_head("head");
   auto i1 = tr.append_child(tr.begin(), "one");
   auto i2 = tr.append_child(tr.begin(), "two");
   auto i3 = tr.append_child(tr.begin(), "three");
   auto i4 = tr.append_child(i2, "four");
   auto i5 = tr.append_child(i2, "five"); 

   auto path = tr.path_from_iterator(i5, tr.begin());
   for(auto& p: path)
      std::cerr << p << "/";
   std::cerr << std::endl;          // prints '0/1/1/'

   auto fnd = tr.iterator_from_path(path, tr.begin());
   std::cerr << *fnd << std::endl;  // prints 'five'
   }
