tree.hh: an STL-like C++ tree class
===================================

by Kasper Peeters <kasper.peeters@phi-sci.com>

The ``tree.hh`` library for C++ provides an STL-like container class for
n-ary trees, templated over the data stored at the nodes. Various
types of iterators are provided (post-order, pre-order, and
others). Where possible the access methods are compatible with the STL
or alternative algorithms are available.

The library should work with any C++11 compiler, and has been used and
tested on all major platforms (Linux, Windows, macOS, Android, iOS). 

The library is available under the terms of the GNU General Public
License version 2 or 3.


What you need
-------------

The tree.hh is header-only; you only need to copy the `src/tree.hh
<https://raw.githubusercontent.com/kpeeters/tree.hh/master/src/tree.hh>`_
header file into your project and you are good to go.

Then scan the example below and consult the `documentation <doc/main.md>`_.


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

.. image:: https://raw.githubusercontent.com/kpeeters/tree.hh/master/doc/structure.png


Projects using tree.hh
----------------------

The ``tree.hh`` library is used in various projects:

- Cadabra (https://cadabra.science/), a field-theory motivated
  approach to symbolic computer algebra.

- Taxator-tk (https://github.com/fungs/taxator-tk/), a set of programs
  for the taxonomic analysis of nucleotide sequence data.

- Gnash (http://www.gnu.org/software/gnash/), a GNU Flash movie
  player. Previously, it was only possible to play flash movies with
  proprietary software. While there are some other free flash players,
  none support anything beyond SWF v4. Gnash is based on GameSWF, and
  supports many SWF v7 features.

- htmlcxx (http://htmlcxx.sourceforge.net/), a simple non-validating
  css1 and html parser for C++.

- Principles of Compiler Design
  (http://www.cs.sfu.ca/~anoop/courses/CMPT-379-Fall-2007/index.html),
  a course in compiler design at the Simon Fraser University, Canada.

- liborigin (http://sourceforge.net/projects/liborigin/), a library
  for reading OriginLab OPJ project files, which is used by QtiPlot
  (http://soft.proindependent.com/qtiplot.html) and LabPlot
  (http://labplot.sourceforge.net/), two applications for data
  analysis and visualisation.

- EChem++
  (http://www.echem.uni-tuebingen.de/~bs/echem/software/EChem++/echem++.shtml),
  a project realizing the idea of a Problem Solving Environment (PSE)
  in the field of computational electrochemistry.  Computer controlled
  experimental measurements, numerical simulation and analysis of
  electrochemical processes will be combined under a common user
  interface.

- LZCS (http://www.infor.uva.es/~jadiego/), a semistructured document
  transformation tool. LZCS compresses structured documents taking
  advantage of the redundant information that can appear in the
  structure. The main idea is that frequently repeated subtrees may
  exist and these can be replaced by a backward reference to their
  first occurance. See the paper
  (http://www.dcc.uchile.cl/~gnavarro/ps/dcc04.1.ps.gz).

- libOFX (http://libofx.sourceforge.net/), a parser and an API
  designed to allow applications to very easily support OFX command
  responses, usually provided by financial institutions for statement
  downloads.

- A genetic programming project
  (http://www.cs.adfa.edu.au/~shanyin/publications/peel.pdf).

- FreeLing (http://nlp.lsi.upc.edu/freeling/) a library providing
  language analysis services (such as morfological analysis, date
  recognition, PoS tagging, and so on.

Let me know about your project when you are using ``tree.hh``, so that
I can add it to the list.


License
-------

In principle, the tree.hh code is available under the terms of the GNU
General Public License 2 or 3. However, if you would like to use
tree.hh under different conditions, contact me and we will work
something out.
