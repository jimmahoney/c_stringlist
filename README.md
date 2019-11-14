# c_stringlist

A sample C program with malloc, struct, multiple files,
pointers, merge sort, and file I/O.

Jim Mahoney |  cs.marlboro.edu | MIT License | summer 2017

-------------------------------------------

    $ make clean
    $ ls
    Makefile      big.txt    stringlist.c   test
    README.txt    small.txt  stringlist.h   test.c
    $ make
    gcc -O2 -c test.c
    gcc -O2 -c stringlist.c
    gcc -O2 test.o stringlist.o -o test
    $ time ./test
    An empty stringlist : []
    A size=4 stringlist : ['four', 'three', 'two', 'one']
    Reversed : ['one', 'two', 'three', 'four']
    Sorted : ['four', 'one', 'three', 'two']
    A list from 'small.txt' : ['not', 'or', 'words', 'of', 'list', \
                               'a', 'is', 'this']
    Reversed : ['this', 'is', 'a', 'list', 'of', 'words', 'or', 'not']
    Sorted : ['a', 'is', 'list', 'not', 'of', 'or', 'this', 'words']
    Read a big list from 'big.txt' with 103600 lines. 
    Its last three lines are (first three in list) : 
    103600 :   print [ord(c) for c in s] 
    103599 :   print s 
    103598 :         s.add(c) 
    Its first three lines are (first in reversed list): 
    0 : The Project Gutenberg EBook of The Adventures of Sherlock Holmes 
    1 : by Sir Arthur Conan Doyle 
    2 : (#15 in our series by Sir Arthur Conan Doyle) 
    A sample of the sorted lines (20000 to 20020) are : 
    1000 : '=The Losses in American Commerce.=--This high-handed conduct on the part' 
    1001 : '=The Louisiana Purchase.=--Text of Treaty in Macdonald, _Documentary' 
    1002 : '=The Massachusetts Circular (1768).=--Massachusetts, under the' 
    1003 : '=The Methods of Travel into the West.=--Many stories giving exact' 
    1004 : '=The Mexican War.=--The inevitable war with Mexico, foretold by the' 
    1005 : '=The Migration to Oregon.=--Schafer, pp. 105-172. Coman, _Economic' 
    1006 : '=The Military Education of the Colonists.=--The same wars that showed' 
    1007 : '=The Missouri Compromise.=--Respecting one other important measure of' 
    1008 : '=The Monroe Doctrine Applied to Germany.=--Less spectacular than the' 
    1009 : '=The Monroe Doctrine.=--Even more effective in fashioning the national' 
    1010 : '=The Monroe Message.=--Macdonald, pp. 318-320.' 
    1011 : '=The Mormon Migration.=--Coman, Vol. II, pp. 167-206.' 
    1012 : '=The Mugwumps and Cleveland Democracy in 1884.=--Though aided by' 
    1013 : '=The Nation Aroused.=--With the spirit of criticism came also the spirit' 
    1014 : '=The National Road.=--To far-sighted men, like Albert Gallatin, "the' 
    1015 : '=The New Economic Age.=--The spirit of criticism and the measures of' 
    1016 : '=The New England Confederation.=--Analyze the document in Macdonald,' 
    1017 : '=The New England Confederation.=--It was in their efforts to deal with' 
    1018 : '=The New England View of the Tariff.=--Callender, pp. 503-514.' 
    1019 : '=The New York Assembly Suspended.=--In the very month that Townshend's' 
    Writing sorted lines to 'big_sorted.txt'.

    real	0m0.144s
    user	0m0.098s
    sys	0m0.031s
