/*  
 * test.c
 *
 * Tests of the stringlist methods.
 *
 * Jim Mahoney |  cs.marlboro.edu | MIT License | summer 2017
 */

#include "stringlist.h"
#include <stdio.h>

int main(){
  char* test_input_filename = "small.txt";
  char* big_input_filename = "big.txt";
  char* big_sorted_filename = "big_sorted.txt";
  size_t n_words = 4;
  char* words[] = {"one", "two", "three", "four"};
  char* sevenwords[] = {"a1", "b2", "c3", "d4", "e5", "f6", "h7"}; 
  stringlist list, list2;
  stringnode node;
  size_t i, j;

  // ----- debugging testing split_ and merge_
  // ----- ... which as it turns out wasn't enough,
  // ----- since a list->size's were wrong after split.
  // ----- I should have printed that here, too.
  //printf("- debug split & merge -\n\n");
  //for (j=2; j<7; j++){
  //  list = new_stringlist();
  //  for (i=0; i<j; i++){
  //    push_onto_stringlist(list, new_stringnode(sevenwords[i]));
  //  }
  //  printf(" before split :");
  //  print_stringlist(list);
  //  list2 = split_stringlist(list);
  //  printf(" after split 1 :");
  //  print_stringlist(list);
  //  printf(" after split 2 :");    
  //  print_stringlist(list2);
  //  merge_stringlists(list, list2);
  //  printf(" merged 1 :");
  //  print_stringlist(list);
  //  printf(" merged 2 :");    
  //  print_stringlist(list2);
  //  printf("\n");
  //  free_stringlist(list2);
  //  free_stringlist(list);
  // }
  
  printf("An empty stringlist : ");
  list = new_stringlist();
  print_stringlist(list);
  free_stringlist(list);
  
  printf("A size=%zu stringlist : ", list->size);
  list = new_stringlist();
  for (i=0; i<n_words; i++){
    push_onto_stringlist(list, new_stringnode(words[i]));
  }
  print_stringlist(list);
  reverse_stringlist(list);
  printf(" Reversed : ");
  print_stringlist(list);
  sort_stringlist(list);
  printf(" Sorted : ");
  print_stringlist(list);  
  free_stringlist(list);

  printf("A list from '%s' : ", test_input_filename);
  list = new_stringlist_from_file(test_input_filename);
  print_stringlist(list);
  reverse_stringlist(list);
  printf(" Reversed : ");
  print_stringlist(list);
  sort_stringlist(list);
  printf(" Sorted : ");
  print_stringlist(list);  
  free_stringlist(list);  

  printf("Read a big list from '%s' with %zu lines. \n",
	 big_input_filename, list->size);
  list = new_stringlist_from_file(big_input_filename);
  printf(" Its last three lines are (first three in list) : \n");
  node = list->first;
  for (i=0; i<3; i++){
    printf("  %zu : %s \n", list->size - i, node->data);
    node = node->next;
  }

  printf(" Its first three lines are (first in reversed list): \n");
  reverse_stringlist(list);
  node = list->first;
  for (i=0; i<3; i++){
    printf("  %zu : %s \n", i, node->data);
    node = node->next;
  }

  printf(" A sample of the sorted lines (20000 to 20020) are : \n");
  sort_stringlist(list);
  node = list->first;
  for (i=0; i<20000; i++) node = node->next; // Skip over 20000 lines
  for (i=0; i<20; i++){                      // ... and print the next 20.
    printf("  %zu : '%s' \n", i+1000, node->data);
    node = node->next;
  }
  
  printf(" Writing sorted lines to '%s'.\n", big_sorted_filename);
  write_stringlist_to_file(list, big_sorted_filename);
  free_stringlist(list);
  
  return 1;
}

// Are we having fun yet?

