#include "skiplist.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// Done ? Undone, no end point created
Node* SK_createList(int height) /* Header node creation */
{
  srand(time(0));
  Node* tmp = malloc(sizeof(Node));
  if (tmp == NULL)
    abort();
  tmp->MAX_HEIGHT = height;
  tmp->height = height;
  tmp->value = 123456;
  tmp->list = malloc(sizeof(Node*) * height);
  if (tmp->list == NULL)
    abort();

  //create endpoint, that is NULL
  for (int i=0;i<height;i++)
  {
    tmp->list[i] = NULL;
  }

  return tmp;
}

/* returns integer between [1, value] */
// Done ?
int randomHeight(int value)
{
  return (rand() % value)+1;
}

// Undone
Node** SK_innerfind(Node* list, int value)
{
  int max_height = list->MAX_HEIGHT;
  Node** update = malloc(sizeof(Node*)*max_height);

  Node* current = list;
  int i = max_height-1;
  /* Skip all the nils */
  // Houston, we had a problem... REWRITING
  while(i >= 0)
  {
    if (current->list[i] == NULL || current->list[i]->value > value)
    {
      update[i--] = current;
      continue;
    }
    else if (current->list[i]->value <= value)
    {
      current = current->list[i];
    }
  }
  return update;
}


// ... wtf is this function for...
// atleast I can find nodes now >_>
Node* SK_find(Node* list, int value) /* either find the node or returns null */
{
  Node** result = SK_innerfind(list, value);
  //
  for (int i=0;i<list->MAX_HEIGHT;i++)
  {
    if (result[i]->value == value)
      return result[i];
  }
  return NULL;
}

// Maybe?
int SK_insert(Node* list, int value) /* insertion doh */
{
  Node** result = SK_innerfind(list, value);
  for (int i=0;i<list->MAX_HEIGHT;i++)
  {
    if (result[i]->value == value)
      return -1;
  }

  // So now we can insert new value :)
  Node* tmp = malloc(sizeof(Node));
  if (tmp == NULL)
    abort();
  tmp->value = value;
  tmp->MAX_HEIGHT = list->MAX_HEIGHT;
  int addheight = randomHeight(list->MAX_HEIGHT);
  tmp->height = addheight;
  tmp->list = malloc(sizeof(Node*) * addheight);
  if (tmp->list == NULL)
    abort();

  // Lets put this node into the right place
  for (int i=0;i<addheight;i++)
  {
    tmp->list[i] = result[i]->list[i];
    result[i]->list[i] = tmp;
  }
  // wtf this cannot work
  return 1;
}

// Simple version
void SK_print(Node* list) /* beautiful presentation of the skiplist */
{
  Node* current = list->list[0];
  printf("skiplist contents: ");
  while(current != NULL) {
    printf("%d ", current->value);
    if (current->list[0] != NULL)
    {
      printf("-> ");
    }
    current = current->list[0];
  }
  printf("\n");
}
