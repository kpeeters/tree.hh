#include "tree.hh"
#include "tree_util.hh"
#include <iostream>
#include <map>

int main()
	{
	tree<int> tt;
	tree<int>::iterator i = tt.insert(tt.begin(), 1);
	tt.insert(i, 2);
	
	std::cout << "==" << std::endl;
	kptree::print_tree_bracketed(tt);
	std::cout << std::endl << "==" << std::endl;
	
	std::map<unsigned, tree<int>> trees;
	std::map<unsigned, tree<int>>::iterator t = trees.find(1);
	if(t == trees.end()) {
		tree<int> tti;
		std::cout << "--" << std::endl;
		t = trees.insert(std::map<unsigned, tree<int>>::value_type(1, tti)).first;
		std::cout << "--" << std::endl;

		tree<int>::iterator j = t->second.insert(t->second.begin(), 1);
		t->second.insert(j, 2);
		std::cout << t->second.size() << std::endl;

		std::cout << "==" << std::endl;
		kptree::print_tree_bracketed(t->second);
		std::cout << std::endl << "==" << std::endl;

		}
	if(t != trees.end())
		std::cout << t->second.size() << std::endl;
	}

