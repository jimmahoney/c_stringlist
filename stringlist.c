/* stringlist.c
 * 
 * implementation of methods in stringlist.h
 *
 * Jim Mahoney |  cs.marlboro.edu | MIT License | summer 2017
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stringlist.h"

// The largest single string that can be read from stdin
// (The sherlock holmes big_file.txt has a 2541 "line" (paragraph) in it.)
#define STRING_IO_BUFFER_SIZE 4096

// --- stringlisit.h methods ------------------------------------------

// return new node with copy of data
stringnode new_stringnode(char* string){
  stringnode node = (stringnode) malloc(sizeof(struct _stringnode));
  size_t size = strlen(string); 
  node->data = (char*) malloc(size + 1); // +1 for string termination null
  strcpy(node->data, string);
  node->next = NULL;
  return node;
}

// free memory for node & its data  
void free_stringnode(stringnode node){
  free(node->data);
  free(node);
}

// return new empty list
stringlist new_stringlist(){
  stringlist list = (stringlist) malloc(sizeof(struct _stringlist));
  list->size = 0;
  list->first = NULL;
  return list;
}

// free list & its nodes
void free_stringlist(stringlist list){
  stringnode node = list->first;
  stringnode next = NULL;
  while (node != NULL){
    next = node->next;
    free_stringnode(node);
    node = next;
  }
  free(list);
}

// Write stringlist to file or stdout, one string per line with newline added.
// If filename is NULL, write to stdout
void write_stringlist_to_file(stringlist list, char* filename){
  FILE *filepointer;
  stringnode node;
  size_t size;
  char output_buffer[STRING_IO_BUFFER_SIZE];  
  if (filename == NULL){
    filepointer = stdout;
  }
  else {
    filepointer = fopen(filename, "w");
  }
  node = list->first;
  while (node != NULL){
    strcpy(output_buffer, node->data);
    size = strlen(output_buffer);
    output_buffer[size] = '\n';
    output_buffer[size+1] = (char)0;
    fputs(output_buffer, filepointer);
    node = node->next;
  }
  fclose(filepointer); // flush output buffers
}

// Create & return stringlist from file or stdin one string per line 'til EOF.
// That means if you're typing strings, end with control-d.
// To read from stdin, pass NULL for filename.
stringlist new_stringlist_from_file(char* filename){
  char input_buffer[STRING_IO_BUFFER_SIZE];
  char* status;
  size_t length;
  stringlist list;
  FILE *filepointer;
  // printf(" DEBUG: input filename = '%s'\n", filename);
  list = new_stringlist();
  if (filename == NULL){
    filepointer = stdin;
  }
  else {
    // printf(" DEBUG: opening '%s' \n", filename);
    filepointer = fopen(filename, "r");
  }
  if (filepointer != NULL){
    while (1){ // loop over lines in stdin until EndOfFile
      status = fgets(input_buffer, STRING_IO_BUFFER_SIZE, filepointer);
      length = strlen(input_buffer);
      // printf(" DEBUG: input length=%zu, line = '%s' \n", length, status);
      if (status == NULL || length == 0){
        break;
      }
      if (input_buffer[length - 1] == '\n'){  // remove trailing newline
        input_buffer[length - 1] = (char) 0;
        length--;
      }
      if (length > 0){ // ignore empty lines
        push_onto_stringlist(list, new_stringnode(input_buffer));
      }
    }
  }
  return list;
}

// push onto start
// (Note that this means the list will be in reverse order of what's pushed.)
void push_onto_stringlist(stringlist list, stringnode node){
    if (list->size == 0){
    list->first = node;
    list->size = 1;
  }
  else {
    node->next = list->first;
    list->first = node;
    list->size++;
  }
}

// pop from start
stringnode pop_from_stringlist(stringlist list){
  stringnode node = list->first;
  if (node != NULL){
    list->first = node->next;
    node->next = NULL;
    list->size--;
  }
  return node;
}

// "['s1', 's2', ...]" to stdout
void print_stringlist(stringlist list){
  stringnode node = list->first;
  printf("[");
  while (node != NULL){
    printf("'%s'", node->data);
    if (node->next != NULL) printf(", ");
    node = node->next;
  }
  printf("]\n");
}

// Split a list into two pieces, modifiying the original and returning another.
// If the original has 0 or 1 elements, return NULL.
stringlist split_stringlist(stringlist list){
  size_t i, split_size;
  stringlist list2;
  stringnode node, last_node;
  if (list->size < 2){
    return NULL;
  }
  list2 = new_stringlist();
  node = list->first;
  split_size = list->size / 2;
  for (i=0; i < split_size; i++){
    last_node = node;      // last in list at end of loop
    node = node->next;     // first in list2 at end of loop
  }
  // cleanup list2
  list2->first = node;
  list2->size = list->size - split_size;
  // cleanup list
  last_node->next = NULL;
  list->size = split_size;
  return list2;
}

void merge_stringlists(stringlist list, stringlist list2){
  // Put all the stringnodes in list and list2 into list, in sorted order.
  stringnode node, node_before, node2, node2_after;
  node_before = NULL;
  node = list->first;
  node2 = list2->first;
  //printf("\n  debug --- start merge --- \n");
  //printf("  debug merge setup: list= "); print_stringlist(list);
  //printf("  debug merge setup: list2= "); print_stringlist(list2);
  //printf("  debug merge setup: node='%s', node2='%s'\n",
  //	 node->data, node2->data);
  // --------
  // Walk through both lists, looking for small node2's to put before
  // one of the node's, inserting that node2 between node_before and node.
  // (And use node_before==Null to indicate that list->first gets changed.)
  while (node != NULL && node2 != NULL){
    //printf("  debug loop: node='%s', node2='%s'\n",
    //	 node->data, node2->data);
    if (strcmp(node->data, node2->data) > 0){ // node2 < node ?
      // Yes, so move node2 into list, and advance to next node2.
      //printf("  debug loop: node2 < node ; next node2 \n");
      node2_after = node2->next;
      node2->next = node;
      if (node_before == NULL){
	list->first = node2;
      }
      else {
	node_before->next = node2;
      }
      node_before = node2;
      node2 = node2_after;
    }
    else {
      // No, so advance node and node_before.
      //printf("  debug merge loop: node < node2 ; next node \n");
      node_before = node;
      node = node->next;
    }
  }
  // We've finished moving through one of the two lists.
  // If node2 is null, then list2 is empty and we're done.
  // Otherwise, if we are past the end of the original list,
  // then what's left of list2 goes at the end of list.
  if (node == NULL){
    //printf("  debug merge cleanup: * node is null, node_before='%s'\n",
    //	   node_before->data);
    node_before->next = node2;
  }
  // cleanup sizes etc now that all of list2 nodes are in list.
  list->size = list->size + list2->size;
  list2->first = NULL;
  list2->size = 0;
  //printf("  debug merge cleanup: list->size=%zu , list2->size=%zu \n",
  //	 list->size, list2->size);
  //printf("  debug merge cleanup: list= "); print_stringlist(list);
  //printf("  debug merge cleanup: list2= "); print_stringlist(list2);
  //printf("  debug --- end merge --- \n\n");
}

// sort a list of stringnodes, in place.
void sort_stringlist(stringlist list){
  // Merge sort is an O(n log(n)) method that works well for linked lists,
  // without needing extra storage for the string data (i.e. same stringnodes).
  // It's a divide and conquer approach:
  //    0) If the list has 0 or 1 element, it is sorted, so do nothing.
  //    1) Otherwise, split the list into two parts.
  //       (Since the stringlist datastructure has its length
  //       we can walk down it to the length/2 node and use
  //       that as the start of a second list.)
  //    2) Recursively sort both of those two length/2 lists.
  //    3) Merge the two sorted lists together.
  // Nontrivial calls to sort_stringlist() create a temporary list2,
  // and the same sort_stringlist are called on the two smaller pieces.
  // Then (list, list2) are merged back into list, and list2 is freed
  // once all the stringnodes are back in the original list.
  // ---
  //printf(" DEBUG: sort start list->size=%zu: list=", list->size);
  //print_stringlist(list);
  stringlist list2;
  list2 = split_stringlist(list);
  if (list2 == NULL){ // list is tiny and therefore already sorted.
    //printf("DEBUG: sort after split, list2==null, list->size=%zu : ",
    //	   list->size);
    //print_stringlist(list);
    return;
  }
  //printf(" DEBUG: sort after split list : "); print_stringlist(list);
  //printf(" DEBUG: sort after split list2 : "); print_stringlist(list2);
  // Sort each of these two now smaller lists.
  sort_stringlist(list);
  sort_stringlist(list2);
  // Merge (list, list2) back into (list).
  merge_stringlists(list, list2);
  // Free the memory for the (now empty) list2.
  free_stringlist(list2);
}

// reverse a list of stringnodes, in place 
void reverse_stringlist(stringlist list){
  //  a -> b -> c     orignal
  //  a <- b <- c     reversed
  stringnode a, b, c;
  a = list->first;
  if (a == NULL){   // empty list, so do nohting.
    return;
  }
  b = a->next;      // (a,b) now 1st two in list
  a->next = NULL;   //  ... and a will be the end.
  while (b != NULL){
    c = b->next;    // save what's coming next
    b->next = a;    // reverse a-b link
    a = b;          // slide (a,b) down chain
    b = c;
  }
  list->first = a;
}

 
