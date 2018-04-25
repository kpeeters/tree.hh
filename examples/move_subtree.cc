#include <iostream>
#include "tree.hh"
#include "tree_util.hh"

void print_tree(const tree<std::string>& tr)
{
    tree<std::string>::pre_order_iterator it = tr.begin();
    tree<std::string>::pre_order_iterator end = tr.end();
    if(!tr.is_valid(it)) return;
    int rootdepth=tr.depth(it);
    std::cout << "-----" << std::endl;
    while(it!=end) {
        for(int i=0; i<tr.depth(it)-rootdepth; ++i)
            std::cout << "  ";
        std::cout << (*it) << std::endl << std::flush;
        ++it;
        }
    std::cout << "-----" << std::endl;
}

int main(int, char **)
{
    tree<std::string> my_tree;

    tree<std::string>::iterator iA = my_tree.insert(my_tree.end(), "A");
    tree<std::string>::iterator iB = my_tree.insert(my_tree.end(), "B");
    tree<std::string>::iterator iB1 = my_tree.append_child(iB, "B1");
    tree<std::string>::iterator iC = my_tree.insert(my_tree.end(), "C");        
    print_tree(my_tree);

    my_tree.move_after(iB1, iC);
    print_tree(my_tree);
}
