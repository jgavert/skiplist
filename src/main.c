#include <stdlib.h>
#include <stdio.h>

#include "skiplist.h"


int main()
{
  Node* skiplist = SK_createList(10);
  for (int i=0;i<10;i++) {
    printf("Adding %d. node\n", i);
    if (SK_insert(skiplist, (i+1)*2) != 1)
      abort();
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
