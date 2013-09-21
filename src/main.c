#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "skiplist.h"


int main()
{
  Node* skiplist = SK_createList(10);
  srand(time(0));
  int luku;
  for (int i=0;i<15;i++) {
    luku = rand()%1000;
    printf("Adding %d. node, value %d\n", i, luku);
    if (!SK_insert(skiplist, luku))
      printf("Already added\n");
    //SK_print(skiplist);
  }
  SK_print(skiplist);
  printf("\n\nDeleting %d...\n", luku);
  SK_delete(skiplist, luku);

  /*
  for (int i=0;i<10;i++)
  {
    if (skiplist->list[i] != NULL)
      printf("%d, ", skiplist->list[i]->value);
    else
      printf("NULL,");
  }
  */
  SK_print(skiplist);
  SK_free(skiplist);
  return 1;
}
