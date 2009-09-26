/* 

	Cadabra: a field-theory motivated computer algebra system.
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
