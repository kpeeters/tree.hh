
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

	auto ret = mtree.move_out(it2);
	ret.debug_verify_consistency();	
	return ret;
	}

void test_move_in(tree<std::string>& other)
	{
	tree<std::string> mtree;
	tree<std::string>::iterator it = mtree.set_head("top");
	mtree.append_child(it, "one");
	auto it3=mtree.append_child(it, "three");

	mtree.move_in(it3, other);
	mtree.debug_verify_consistency();
	kptree::print_tree_bracketed(mtree);
	std::cout << "\n";
	}

void test_move_in_as_nth_child(int n)
	{
	tree<std::string> mtree, other;
	tree<std::string>::iterator it = mtree.set_head("top");
	mtree.append_child(it, "one");
	mtree.append_child(it, "three");

	auto ot1 = other.set_head("hi");
	other.insert_after(ot1, "second");
	other.append_child(ot1, "1");
	other.append_child(ot1, "2");
	
	mtree.move_in_as_nth_child(it, n, other);
	mtree.debug_verify_consistency();
	kptree::print_tree_bracketed(mtree);
	std::cout << "\n";
	}

void test_move_below(tree<std::string>& other)
	{
	tree<std::string> mtree;
	tree<std::string>::iterator it = mtree.set_head("top");
	mtree.append_child(it, "one");
	auto it3=mtree.append_child(it, "three");

	mtree.move_in(it3, other);
	kptree::print_tree_bracketed(mtree);
	}


int main(int argc, char **argv)
	{
	// Move constructor.
	tree<std::string> res = test_move_constructor();
	std::cout << "res:" << std::endl;
	kptree::print_tree_bracketed(res);

	// Move out.
	tree<std::string> res2 = test_move_out();
	std::cout << "\nres2:" << std::endl;
	kptree::print_tree_bracketed(res2);
	std::cout << std::endl;

	// Move in.
	test_move_in(res2);
	std::cout << "\n";
	kptree::print_tree_bracketed(res2);
	std::cout << "\n";

	// Move in as nth child.
	test_move_in_as_nth_child(0);
	test_move_in_as_nth_child(1);
	test_move_in_as_nth_child(2);
	try {
		test_move_in_as_nth_child(3);
		}
	catch(const std::range_error& ex) {
		std::cout << ex.what() << std::endl;
		}
	}
