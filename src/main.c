#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "skiplist.h"


int main()
{
  Node* skiplist = SK_createList(10);
  srand(time(0));
  int luku;
  int max = 0;
  for (int i=0;i<15;i++) {
    luku = rand()%1000;
    if (luku > max)
      max = luku;
    printf("Adding %d. node, value %d\n", i, luku);
    if (!SK_insert(skiplist, luku))
      printf("Already added\n");
    //SK_print(skiplist);
  }
  SK_print(skiplist);
  Node* tmp = SK_find(skiplist, luku);
  if (tmp != NULL)
  {
    printf("Found: %d\n", tmp->value);
    int luku2 = tmp->value;
    printf("Deleting %d...\n", luku);
    SK_delete(skiplist, luku);
    printf("Inserting: %d\n", (int)(luku2/2.0));
    SK_insert(skiplist, (int)(luku2/2.0));
  }
  else
    printf("Didn't find\n");

  SK_print2(skiplist);
  Node** list = SK_innerfind(skiplist, max);
  printf("found %d by going from ", max);
  int last = 0;
  for (int i=skiplist->height-1;i>=0;i--)
  {
    if (list[i] != skiplist)
    {
      if (last == list[i]->value)
        continue;
      printf("%d", list[i]->value);
      last = list[i]->value;
      if (i>0)
        printf(" -> ", list[i]->value);
    }
    if (list[i]->list[i] != NULL && list[i]->list[i]->value == max)
      break;
  }
  printf("\n");

  SK_free(skiplist);
  return 1;
}
