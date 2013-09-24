#include "skiplist.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>

void* SuperMalloc(size_t size)
{
  void* tmp = malloc(size);
  if (tmp == NULL)
    abort();
  return tmp;
}

// Done ? Undone, no end point created
Node* SK_createList(int height) /* Header node creation */
{
  Node* tmp = SuperMalloc(sizeof(Node));
  tmp->height = height;
  tmp->value = 0; //This will be treated as length, used only in printing
  tmp->list = SuperMalloc(sizeof(Node*) * height);

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
  int tmp = 1; //always have atleast 1 level
  while((float)rand()/(float)(RAND_MAX) > 0.5) {tmp++;}
  if (tmp>value)
    tmp=value;
  return tmp;
}

// Undone
Node** SK_innerfind(Node* list, int value)
{
  int max_height = list->height;
  Node** update = SuperMalloc(sizeof(Node*)*max_height);

  Node* current = list;
  int i = max_height-1;
  /* Skip all the nils */
  // Houston, we had a problem... REWRITING
  while(i >= 0)
  {
    if (current->list[i] == NULL || current->list[i]->value >= value)
    {
      update[i--] = current;
    }
    else
    {
      current = current->list[i];
    }
  }
  return update;
}

int SK_innerfind2(Node** result, int value)
{
  if (result[0]->list[0] == NULL)
    return 0;
  if (result[0]->list[0]->value == value)
    return 1;
  return 0;
}

// ... wtf is this function for...
// atleast I can find nodes now >_>
// Untested also :D
// Ill just write a proper find
Node* SK_find(Node* list, int value) /* either find the node or returns null */
{
  int max_height = list->height;

  Node* current = list;
  if (current == NULL)
    return NULL;
  int i = max_height-1;
  while(i >= 0)
  {
    if (current->value == value) break;
    if (current->list[i] == NULL || current->list[i]->value > value)
    {
      i--;
      continue;
    }
    current = current->list[i];
  }
  if (current->value == value)
    return current;
  return NULL;
}

// havent broken so far
int SK_insert(Node* list, int value) /* insertion doh */
{
  Node** result = SK_innerfind(list, value);
  if (SK_innerfind2(result, value))
  {
    free(result);
    return 0;
  }

  // So now we can insert new value :)
  Node* tmp = SuperMalloc(sizeof(Node));
  tmp->value = value;
  int addheight = randomHeight(list->height);
  tmp->height = addheight;
  tmp->list = SuperMalloc(sizeof(Node*) * addheight);

  // Lets put this node into the right place
  for (int i=0;i<addheight;i++)
  {
    tmp->list[i] = result[i]->list[i];
    result[i]->list[i] = tmp;
  }
  // wtf this cannot work
  // It does :D
  list->value++;
  free(result);
  return 1;
}

int SK_delete(Node* list, int value)
{
  //actually we need a list of nodes that all point to the node
  Node** result = SK_innerfind(list, value);
  Node* tmp = NULL;
  if (SK_innerfind2(result,value))
    tmp = result[0]->list[0];
  if (tmp == NULL)
  {
    free(result);
    return 0;
  }
  int resultHeight = list->height;
  //printf("resultHeight: %d", resultHeight);
  for (int i=0;i<resultHeight;i++)
  {
    if (result[i]->list[i] == NULL || result[i]->list[i]->value != value)
      break;
    result[i]->list[i] = tmp->list[i];
  }
  free(tmp->list);
  free(tmp);
  free(result);
  list->value--;
  return 1;
}

// :D
void SK_print(Node* list) /* beautiful presentation of the skiplist */
{
  Node* current = list->list[0];
  printf("SkipList contents: \n");

  int length = list->value;
  int height = list->height;
  int** table = SuperMalloc(sizeof(int*)*length);
  for (int i=0;i<length;i++)
  {
    table[i] = SuperMalloc(sizeof(int)*height);
  }

  current = list->list[0]; //I know this is confusing, it's not even important
  int x=0;
  while(current != NULL || x < length) {
    // Add the elements from bottom to table
    for (unsigned int k=0;k<current->height;k++)
    {
      //printf("%d, ",current->value);
      table[x][k] = current->value;
    }
    for (unsigned int k=current->height;k<list->height;k++)
    {
      table[x][k] = INT_MIN;
    }
    current = current->list[0];
    x++;
  }

  // Lets Print what we have
  // Line at a time of course :F
  for (int i=height-1;i>=0;i--)
  {
    printf("[START]");
    for (int k=0;k<length;k++) {
      if (table[k][i] == INT_MIN) {
        printf("-------");
      }
      else {
        printf("->[%03d]",table[k][i]);
      }
    }
    printf("->[NULL]\n");
  }

  //Lol lets free shit
  for (int k=0;k<length;k++)
  {
    free(table[k]);
  }
  free(table);
}

// YOU ARE ALL FREE NOW!
void SK_free(Node* skiplist)
{
  if (skiplist->value == 0)
  {
    free(skiplist->list);
    free(skiplist);
  }
  //First we need pointers to all nodes... lol
  Node** nodes = SuperMalloc(sizeof(Node*)*skiplist->value);
  Node* tmp = skiplist->list[0];
  int i = 0;
  while (tmp != NULL)
  {
    nodes[i++] = tmp;
    tmp = tmp->list[0];
  }
  // So we can reverse free them :D
  // because I Dont have links to the earlier nodes
  i--;
  for (i=i;i>=0;i--)
  {
    free(nodes[i]->list);
    free(nodes[i]);
  }
  free(skiplist->list);
  free(skiplist);
  free(nodes);
}


// experimental print
void SK_print2(Node* list) /* beautiful presentation of the skiplist */
{
  Node* current = list->list[0];
  printf("SkipList contents: \n");

  int length = list->value;
  int height = list->height;
  int** table = SuperMalloc(sizeof(int*)*length);
  for (int i=0;i<length;i++)
  {
    table[i] = SuperMalloc(sizeof(int)*height);
  }

  current = list->list[0]; //I know this is confusing, it's not even important
  int x=0;
  while(current != NULL || x < length) {
    // Add the elements from bottom to table
    for (unsigned int k=0;k<current->height;k++)
    {
      //printf("%d, ",current->value);
      table[x][k] = current->value;
    }
    for (unsigned int k=current->height;k<list->height;k++)
    {
      table[x][k] = INT_MIN;
    }
    current = current->list[0];
    x++;
  }

  // Lets Print what we have
  // Line at a time of course :F
  int done = 0;
  for (int i=height-1;i>=0;i--)
  {
    printf("[START]");
    for (int k=0;k<length;k++) {
      if (table[k][i] == INT_MIN) {
        int asd = 1;
        if (!done)
        {
          asd = 0;
          for (int x = k; x<length;x++)
          {
            if (table[x][i] != INT_MIN)
            {
              asd = 1;
              break;
            }
          }
          done = 1;
          // asd = 1 jos halutaan printtaa ------
        }
        if (!asd && done)
        {
          done = 0;
          break;
        }
        printf("-------");
      }
      else {
        printf("->[%03d]",table[k][i]);
        done = 0;
      }
    }
    printf("->\n");
  }

  //Lol lets free shit
  for (int k=0;k<length;k++)
  {
    free(table[k]);
  }
  free(table);
}

