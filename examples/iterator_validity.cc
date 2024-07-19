#include "../src/tree.hh"
#include "../src/tree_util.hh"

int main()
   {
   // Initialize the tree
   tree<int> tr = tree<int>(1);
   
   // Loop for the depth of the tree
   int node_counter = 1;
   for (int depth = 1; depth <= 3; ++depth) {
      // Iterate over the leaf nodes
      tree<int>::leaf_iterator leaf_node = tr.begin_leaf();
      while(leaf_node != tr.end_leaf()) {
         auto next_leaf=leaf_node;
         ++next_leaf;
         // Add children to the leaf node
         for (int k = 1; k <= 3; ++k) {
            tr.append_child(leaf_node, node_counter);
            ++node_counter;
            }
         // Go to the next leaf node
         leaf_node = next_leaf;
         }
      }

   
   kptree::print_tree_bracketed(tr);
   
   return 0;
   }
