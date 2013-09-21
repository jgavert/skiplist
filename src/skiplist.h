#ifndef SKIPLIST_H
#define SKIPLIST_H
#include "node.h"

Node* SK_createList(int); /* Header node creation */
int randomHeight(int);
Node** SK_innerfind(Node*,int); /* either find the node or returns null */
int SK_innerfind2(Node**,int);
Node* SK_find(Node*,int); /* either find the node or returns null */
int SK_insert(Node*,int); /* insertion doh */
int SK_delete(Node*,int);
void SK_print(Node*); /* beautiful presentation of the skiplist */
void SK_free(Node*);

#endif /* SKIPLIST_H  */
