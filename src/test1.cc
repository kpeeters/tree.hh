#include "tree.hh"
#include "tree_util.hh"

int main(int, char **)
	{
	tree<int> tr;

	tr.insert(tr.begin(), 1);
	tree<int>::iterator i2 = tr.insert(tr.end(), 2);
	tree<int>::iterator i3 = tr.insert(tr.end(), 3);
	tr.append_child(i2, 21);
	tr.append_child(i3, 31);
	tree<int>::iterator i4 = tr.insert(tr.end(), 4);

	kptree::print_tree_bracketed(tr, std::cout);

	std::cout << std::endl;
	}
