/* 

	STL-like templated tree class; test program.
	Copyright (C) 2001-2009  Kasper Peeters <kasper.peeters@aei.mpg.de>

   This program is free software: you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation, either version 3 of the
   License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 
*/

#include "tree.hh"
#include "tree_util.hh"

#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <list>
#include <utility>
#include <stdexcept>

/*
  
    Simple test program for the tree.hh class library. Run it and see
    what happens. Or, if you want to see that it does not leak memory,
    run it like

      ./test_tree 10000 >/dev/null

    or some other large number and have 'top' running in a different
    shell. This will run the tests 10000 times, creating and destroying
    the trees for every iteration of the loop.

 */

bool truefunc(std::string& one, std::string& two) 
	{
//	std::cout << "comparing " << one << "==" << two << std::endl;
	return true;
	}

void print_tree(const tree<std::string>& tr, tree<std::string>::pre_order_iterator it, tree<std::string>::pre_order_iterator end)
	{
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

void print_tree_post(const tree<std::string>& tr, tree<std::string>::post_order_iterator it, tree<std::string>::post_order_iterator end)
	{
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

void print_tree_rev(const tree<std::string>& tr, tree<std::string>::pre_order_iterator it, tree<std::string>::pre_order_iterator end)
	{
	--it;
	int rootdepth=0;//tr.depth(it);
	std::cout << "-----" << std::endl;
	while(1==1) {
		for(int i=0; i<tr.depth(it)-rootdepth; ++i) 
			std::cout << "  ";
		std::cout << (*it) << std::endl;
		if(it==end) break;
		--it;
		}
	std::cout << "-----" << std::endl;
	}

void print_tree_rev_post(const tree<std::string>& tr, tree<std::string>::post_order_iterator it, tree<std::string>::post_order_iterator end)
	{
	--it;
	int rootdepth=0;//tr.depth(it);
	std::cout << "-----" << std::endl;
	while(1==1) {
		for(int i=0; i<tr.depth(it)-rootdepth; ++i) 
			std::cout << "  ";
		std::cout << (*it) << std::endl;
		if(it==end) break;
		--it;
		}
	std::cout << "-----" << std::endl;
	}

int main(int argc, char **argv)
	{
	unsigned int maxloop=1;
	if(argc>1)
		maxloop=atoi(argv[1]);

	for(unsigned int j=0; j<maxloop; ++j) {
		tree<std::string> tr9;
		tr9.set_head("hi");
		tr9.insert(tr9.begin().begin(), "0");
		tr9.insert(tr9.begin().begin(), "1");
		print_tree(tr9, tr9.begin(), tr9.end());


		tree<std::string> tr;
		tree<std::string>::pre_order_iterator html, body, h1, h3, bh1, mv1;
		
		std::cout << "empty tree to begin with:" << std::endl;
		print_tree(tr, tr.begin(), tr.end());

		html=tr.insert(tr.begin(), "html");
		tr.insert(html,"extra");
//		tr.insert(html,"zextra2");
		body=tr.append_child(html, "body");
		h1  =tr.append_child(body, "h1");
		std::cout << tr.index(h1) << std::endl;
		bh1 =tr.insert(h1,"before h1");
		tr.append_child(h1, "some text");
		tree<std::string>::sibling_iterator more_text=tr.append_child(body, "more text");

		std::cout << " 'more text' is sibling " << tr.index(more_text) << " in its sibling range" << std::endl;
		
		std::cout << "filled tree:" << std::endl;
		print_tree(tr, tr.begin(), tr.end());

		std::cout << "filled tree, post-order traversal:" << std::endl;
		print_tree_post(tr, tr.begin_post(), tr.end_post());

		tr.swap(bh1);
		std::cout << "swapped elements:" << std::endl;
		print_tree(tr, tr.begin(), tr.end());
		tr.swap(h1);
		std::cout << "swapped back:" << std::endl;
		print_tree(tr, tr.begin(), tr.end());

		tree<std::string> copytree(h1);
		std::cout << "copied tree:" << std::endl;
		print_tree(copytree, copytree.begin(), copytree.end());

		// Now test the STL algorithms
		std::cout << "result of search for h1 and kasper:" << std::endl;
		tree<std::string>::pre_order_iterator it;
		it=std::find(tr.begin(),tr.end(),std::string("h1"));
		if(it!=tr.end()) print_tree(tr, it, tr.next_sibling(it));
		else             std::cout << "h1 not found" << std::endl;
		it=std::find(tr.begin(),tr.end(), std::string("kasper"));
		if(it!=tr.end()) print_tree(tr, it, tr.next_sibling(it));
		else             std::cout << "kasper not found" << std::endl;
		std::cout << std::endl;

		// remove the h1, replace it with new subtree
		tree<std::string> replacement;
		h3  =replacement.insert(replacement.begin(), "h3");
		replacement.append_child(h3, "text in h3");
		std::cout << "replacement tree:" << std::endl;
		print_tree(replacement, replacement.begin(), replacement.end());
		print_tree(tr, tr.begin(), tr.end());
		h1=tr.replace(tree<std::string>::sibling_iterator(h1), tr.next_sibling(h1),
						  tree<std::string>::sibling_iterator(h3), tr.next_sibling(h3));
		std::cout << "filled tree with replacement done:" << std::endl;
		print_tree(tr, tr.begin(), tr.end());
		
		// replace h3 node while keeping children
		h1=tr.replace(h1, "<foobar>");
		print_tree(tr, tr.begin(), tr.end());

		// add a sibling to the head
		tr.insert_after(h1, "more");
					  
		// Copy object.
		tree<std::string> tr2=tr;
		print_tree(tr2, tr2.begin(), tr2.end());
		tree<std::string> tr3(tr);

		// reparent "before h1" to h3 node
		tr.reparent(h1, bh1, tr.next_sibling(bh1));
		std::cout << "moved content:" << std::endl;
		print_tree(tr, tr.begin(), tr.end());

		// iterate over children only
		tree<std::string>::sibling_iterator ch=tr.begin(h1);
		std::cout << "children of h1:" << std::endl;
		while(ch!=tr.end(h1)) {
			std::cout << (*ch) << std::endl;
			++ch;
			}
		std::cout << std::endl;

		// flatten the h3 node
		tr.flatten(h1);
		std::cout << "flattened (at h3) tree:" << std::endl;
		print_tree(tr, tr.begin(), tr.end());

		// Erase the subtree of tr below body.
		tr.erase_children(body);
		std::cout << "children of body erased:" << std::endl;
		print_tree(tr, tr.begin(), tr.end());
		it=std::find(tr.begin(),tr.end(),"h1");
		if(it!=tr.end()) print_tree(tr, it, tr.next_sibling(it));
		else             std::cout << "h1 not found" << std::endl;

		// Erase everything
		tr.erase(tr.begin());
		std::cout << "erased tree:" << std::endl;
		print_tree(tr, tr.begin(), tr.end());
		
		// The copies are deep, ie. all nodes have been copied.
		std::cout << "copies still exist:" << std::endl;
		print_tree(tr2, tr2.begin(), tr2.end());
		print_tree(tr3, tr3.begin(), tr3.end());
		
		// Test comparison
		std::cout << "testing comparison functions:" << std::endl;
		std::cout << std::equal(tr2.begin(), tr2.end(), tr3.begin(), std::equal_to<std::string>()) 
					 << " (should be 1)" << std::endl;
		// modify content but not structure
		tree<std::string>::pre_order_iterator fl3=tr3.begin();
		fl3+=4; // pointing to "<foobar>" node
		std::cout << (*fl3) << std::endl;
		std::string tmpfl3=(*fl3);
		(*fl3)="modified";
		std::cout << std::equal(tr2.begin(), tr2.end(), tr3.begin(), std::equal_to<std::string>()) 
					 << " (should be 0)" << std::endl;
		std::cout << tr2.equal(tr2.begin(), tr2.end(), tr3.begin(), std::equal_to<std::string>()) 
					 << " (should be 0)" << std::endl;		
		std::cout << tr2.equal(tr2.begin(), tr2.end(), tr3.begin(), truefunc)
					 << " (should be 1)" << std::endl;
		// modify tr3 structure (but not content)
		(*fl3)=tmpfl3;
		tr3.flatten(fl3);
		std::cout << "tree flattened, test again" << std::endl;
		print_tree(tr3, tr3.begin(), tr3.end());

		// Test comparison again
		std::cout << tr2.equal(tr2.begin(), tr2.end(), tr3.begin(), std::equal_to<std::string>()) 
					 << " (should be 0)" << std::endl;
		std::cout << std::equal(tr2.begin(), tr2.end(), tr3.begin(), std::equal_to<std::string>()) 
					 << " (should be 1)" << std::endl;
		// Change content
		(*fl3)="modified";
		// Test comparison again
		std::cout << std::equal(tr2.begin(), tr2.end(), tr3.begin(), std::equal_to<std::string>()) 
					 << " (should be 0)" << std::endl;
		std::cout << tr2.equal(tr2.begin(), tr2.end(), tr3.begin(), std::equal_to<std::string>()) 
					 << " (should be 0)" << std::endl;
		
		// Testing sort. First add a subtree to one leaf
		tree<std::string>::pre_order_iterator txx3=tr3.begin();
		txx3+=5;
		tr3.append_child(txx3,"ccc");
		tr3.append_child(txx3,"bbb");
		tr3.append_child(txx3,"bbb");
		tr3.append_child(txx3,"aaa");
		std::less<std::string> comp;
		tree<std::string>::pre_order_iterator bdy=tr3.begin();
		bdy+=2;
		assert(tr.is_valid(bdy));
		std::cout << "unsorted subtree:" << std::endl;
		print_tree(tr3, tr3.begin(), tr3.end());
		tree<std::string>::sibling_iterator sortit1=tr3.begin(bdy), sortit2=tr3.begin(bdy);
		sortit1+=2;
		sortit2+=4;
		assert(tr.is_valid(sortit1));
		assert(tr.is_valid(sortit2));
		std::cout << "partially sorted subtree: (" 
					 << "sorted from " << (*sortit1) << " to " 
					 << (*sortit2) << ", excluding the last element)" << std::endl;


		mv1=tr3.begin();
		++mv1;
		tr3.sort(sortit1, sortit2);
		print_tree(tr3, tr3.begin(), tr3.end());
		tr3.sort(tr3.begin(bdy), tr3.end(bdy), comp, true); // false: no sorting of subtrees
//    Sorting the entire tree, level by level, is much simpler:
//		tr3.sort(tr3.begin(), tr3.end(), true);
		std::cout << "sorted subtree:" << std::endl;
		print_tree(tr3, tr3.begin(), tr3.end());
		
		// Michael's problem
//		std::cout << mv1.node << ", " << tr3.feet << ", " << tr3.feet->prev_sibling << std::endl;
//		std::cout << mv1.node->next_sibling << ", " << tr3.feet->prev_sibling << ", " << tr3.end().node << std::endl;
//		tr3.sort(tr3.begin(), tr3.end(), true);		
//		std::cout << mv1.node << ", " << tr3.feet << ", " << tr3.feet->prev_sibling << std::endl;
//		std::cout << mv1.node->next_sibling << ", " << tr3.feet->prev_sibling << ", " << tr3.end().node << std::endl;
//		print_tree(tr3, tr3.begin(), tr3.end());
//		tr3.sort(tr3.begin(), tr3.end(), true);
//		std::cout << mv1.node << ", " << tr3.feet << ", " << tr3.feet->prev_sibling << std::endl;
//		std::cout << mv1.node->next_sibling << ", " << tr3.feet->prev_sibling << ", " << tr3.end().node << std::endl;
//		print_tree(tr3, tr3.begin(), tr3.end());
//		return 1;

		// Test merge algorithm.
		std::cout << "test merge" << std::endl;
		tree<std::string> mtree;
		tree<std::string>::pre_order_iterator mt1, mt2, mt3;
		mt1=mtree.insert(mtree.begin(),"html");
		mt2=mtree.append_child(mt1,"head");
		mt3=mtree.append_child(mt1,"body");
// Adding it without head having any children tests whether we can
// insert at the end of an empty list of children. 
		mtree.append_child(mt2,"title");
		mtree.append_child(mt3,"h1");
		mtree.append_child(mt3,"h1");
		
		tree<std::string> mtBree;
		tree<std::string>::pre_order_iterator mtB1, mtB2;
		mtB1=mtBree.insert(mtBree.begin(),"head");
		mtB2=mtBree.append_child(mtB1,"another title");
		print_tree(mtree, mtree.begin(), mtree.end());
		print_tree(mtBree, mtBree.begin(), mtBree.end());

		mtree.merge(mtree.begin(), mtree.end(), mtBree.begin(), mtBree.end(), true);
		print_tree(mtree, mtree.begin(), mtree.end());
		mtree.merge(mtree.begin(mtree.begin()), mtree.end(mtree.begin()), mtBree.begin(), mtBree.end(), true);
		print_tree(mtree, mtree.begin(), mtree.end());

		// Print tree in reverse (test operator--)
		print_tree_rev(mtree, mtree.end(), mtree.begin());
		print_tree_rev_post(mtree, mtree.end_post(), mtree.begin_post());

		// Breadth-first
		tree<std::string> bft;
		tree<std::string>::iterator bfB,bfC,bfD;
		bft.set_head("A");
		bfB=bft.append_child(bft.begin(), "B");
		bfC=bft.append_child(bft.begin(), "C");
		bfD=bft.append_child(bft.begin(), "D");
		bft.append_child(bfB, "E");
		bft.append_child(bfB, "F");
		bft.append_child(bfC, "G");
		bft.append_child(bfC, "H");
		bft.append_child(bfD, "I");
		tree<std::string>::breadth_first_queued_iterator bfq=bft.begin_breadth_first();
		while(bfq!=bft.end_breadth_first()) {
			std::cout << *bfq << std::endl;
			++bfq;
			}

		print_tree(bft, bft.begin(), bft.end());
		bft.wrap(bfD, "wrap");
		print_tree(bft, bft.begin(), bft.end());

		tree<std::string>::leaf_iterator li=tr.begin_leaf(bfC);
		while(li!=tr.end_leaf(bfC)) {
			 std::cout << *li << std::endl;
			 ++li;
			 }

//		  tree<std::string> testfixed;
//		  testfixed.insert(testfixed.begin(), "one");
//		  testfixed.insert(testfixed.begin(), "two");
//		  testfixed.insert(testfixed.begin(), "three");
//		  tree<std::string>::fixed_depth_iterator fit=testfixed.begin();
//		  while(testfixed.is_valid(fit)) {
//			  std::cout << *fit << std::endl;
//			  ++fit;
//			  }
		}
	}
