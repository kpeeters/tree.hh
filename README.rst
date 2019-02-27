tree.hh: an STL-like C++ tree class
===================================

by Kasper Peeters <kasper.peeters@phi-sci.com>

The tree.hh library for C++ provides an STL-like container class for
n-ary trees, templated over the data stored at the nodes. Various
types of iterators are provided (post-order, pre-order, and
others). Where possible the access methods are compatible with the STL
or alternative algorithms are available. The library is available
under the terms of the GNU General Public License version 2 or 3.

What you need
-------------

The tree.hh is header-only; you only need to copy the `src/tree.hh`
header file into your project and you are good to go.


Sample use
----------

The following is a small sample program to illustrate how `tree.hh` is used::

    #include <algorithm>
    #include <string>
    #include <iostream>
    #include "tree.hh"
    
    using namespace std;
    
    int main(int, char **)
       {
       tree<string> tr;
       tree<string>::iterator top, one, two, loc, banana;
       
       top=tr.begin();
       one=tr.insert(top, "one");
       two=tr.append_child(one, "two");
       tr.append_child(two, "apple");
       banana=tr.append_child(two, "banana");
       tr.append_child(banana,"cherry");
       tr.append_child(two, "peach");
       tr.append_child(one,"three");
       
       loc=find(tr.begin(), tr.end(), "two");
       if(loc!=tr.end()) {
       tree<string>::sibling_iterator sib=tr.begin(loc);
       while(sib!=tr.end(loc)) {
         cout << (*sib) << endl;
         ++sib;
         }
       cout << endl;
       tree<string>::iterator sib2=tr.begin(loc);
       tree<string>::iterator end2=tr.end(loc);
       while(sib2!=end2) {
         for(int i=0; i<tr.depth(sib2)-2; ++i) 
            cout << " ";
         cout << (*sib2) << endl;
         ++sib2;
         }
       }
    }

The output of this program is::

    apple
    banana
    peach
    
    apple
    banana
     cherry
    peach

Note that this example only has one element at the top of the tree (in
this case that is the node containing `one`) but it is possible to
have an arbitary number of such elements (then the tree is more like a
"bush"). Observe the way in which the two types of iterators work. The
first block of output, obtained using the sibling_iterator, only
displays the children directly below `two`. The second block iterates
over all children at any depth below `two`. In the second output
block, the depth member has been used to determine the distance of a
given node to the root of the tree.

Structure
---------

<img src="https://cdn.rawgit.com/kpeeters/tree.hh/master/doc/structure.png" />


License
-------

In principle, the tree.hh code is available under the terms of the GNU
General Public License 2 or 3. However, if you would like to use
tree.hh under different conditions, contact me and we will work
something out.
