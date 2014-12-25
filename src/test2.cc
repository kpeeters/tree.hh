
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

tree<std::string> test_move_out()
	{
	tree<std::string> mtree;
	tree<std::string>::iterator it = mtree.set_head("top");
	mtree.append_child(it, "one");
	auto it2 = mtree.append_child(it, "two");
	mtree.append_child(it, "three");
	mtree.append_child(it2, "four");
	mtree.append_child(it2, "five");

	return mtree.move_out(it2);
	}


int main(int argc, char **argv)
	{
	tree<std::string> res = test_move_constructor();

	std::cout << "res:" << std::endl;
	kptree::print_tree_bracketed(res);

	tree<std::string> res2 = test_move_out();
	std::cout << "\nres2:" << std::endl;
	kptree::print_tree_bracketed(res2);

	std::cout << std::endl;
	}
