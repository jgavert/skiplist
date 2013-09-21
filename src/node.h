#ifndef NODE_H
#define NODE_H

typedef struct _node {
  int value;
  unsigned int height;
  struct _node** list;
} Node;

#endif  /* NODE_H */

