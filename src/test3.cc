
#include <string>
#include <iostream>
#include "tree.hh"

tree<std::string> fun() 
	{
	tree<std::string> one;
	
	one.set_head("head");
	one.append_child(one.begin(), "child");

	tree<std::string> two(one);
	
	// change the 'one' tree
	(*one.begin())="new head";
	(*one.begin(one.begin()))="new child";

	// 'one' has changed, 'two' is still the original 'one'.
	std::cout << (*one.begin()) << std::endl;
	std::cout << (*two.begin()) << std::endl;

	return two;
	}

main()
	{
	tree<std::string> test=fun();

	// this outputs the original 'one' tree.
	std::cout << *test.begin() << std::endl;
	std::cout << (*test.begin(test.begin())) << std::endl;
	}
