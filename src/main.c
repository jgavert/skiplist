#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "skiplist.h"


int main()
{
  Node* skiplist = SK_createList(10);
  srand(time(0));
  for (int i=0;i<15;i++) {
    int luku = rand()%1000;
    printf("Adding %d. node, value %d\n", i, luku);
    if (!SK_insert(skiplist, luku))
      printf("Already added\n");
    //SK_print(skiplist);
  }
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
  return 1;
}
