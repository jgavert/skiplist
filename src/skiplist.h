#ifndef SKIPLIST_H
#define SKIPLIST_H
#include "node.h"

Node* SK_createList(int); /* Header node creation */
int randomHeight(int);
Node** SK_innerfind(Node*,int); /* either find the node or returns null */
Node* SK_find(Node*,int); /* either find the node or returns null */
int SK_insert(Node*,int); /* insertion doh */
void SK_print(Node*); /* beautiful presentation of the skiplist */


#endif /* SKIPLIST_H */
