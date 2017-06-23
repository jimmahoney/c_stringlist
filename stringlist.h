/* stringlist.h
 * 
 * data structures & methods for a linked list of strings 
 *
 * Note that since the push_onto_stringlist method adds strings
 * to the start of the list, the strings will be in the reverse
 * order of how they were pushed. In other words, the first 
 * string pushed will be the last in the list, unless it 
 * is reversed after being built.
 *
 * Jim Mahoney |  cs.marlboro.edu | MIT License | summer 2017
 */ 

#ifndef H_STRINGLIST
#define H_STRINGLIST

#include <stdlib.h>

// A node in a singely linked list of strings.
typedef struct _stringnode *stringnode;
struct _stringnode {
  char* data;
  stringnode next;
};

// A list of strings.
typedef struct _stringlist *stringlist;
struct _stringlist {
  stringnode first;
  size_t size;
};

stringnode new_stringnode(char* string); // return new node with copy of string
void free_stringnode(stringnode node);   // free memory for node & its data

stringlist new_stringlist();             // return new empty list
void free_stringlist(stringlist list);   // free list & its nodes
void write_stringlist_to_file(stringlist list, char* filename);
stringlist new_stringlist_from_file(char* filename); // one string per line.
                                                     // NULL => stdin/stdout.
void push_onto_stringlist(stringlist list, stringnode node); // push onto start
stringnode pop_from_stringlist(stringlist list);             // pop from start

void print_stringlist(stringlist list);   // "['s1', 's2', ...]" to stdout
void sort_stringlist(stringlist list);    // sort list of strings in place
void reverse_stringlist(stringlist list); // reverse list strings in place

// -- For debugging only, since these should only be used by sort_ .
stringlist split_stringlist(stringlist list);
void merge_stringlists(stringlist list, stringlist list2);

#endif
