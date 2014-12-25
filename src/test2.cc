
#include <iostream>
#include "tree.hh"
#include "tree_util.hh"

tree<std::string> test_move_constructor()
	{
	tree<std::string> mtree;
	tree<std::string>::iterator it = mtree.set_head("top");
	mtree.append_child(it, "one");
	mtree.append_child(it, "two");
	mtree.append_child(it, "three");

	tree<std::string> ctree(std::move(mtree));

	std::cout << "ctree:" << std::endl;
	kptree::print_tree_bracketed(ctree);
	std::cout << "\nmtree:" << std::endl;
	kptree::print_tree_bracketed(mtree);

	return ctree;
	}


int main(int argc, char **argv)
	{
	tree<std::string> res = test_move_constructor();

	std::cout << "res:" << std::endl;
	kptree::print_tree_bracketed(res);
	}
