#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct node_t {
  struct node_t *left;
  struct node_t *right;
  int data;
};

// you need to implement this function
void to_dlist_my(struct node_t *top, struct node_t **res) {
  if (top == NULL)
    return;
  to_dlist_my(top->left, res);
  if (*res != NULL) {
    top->left = *res;
    (*res)->right = top;
  } 
  *res = top;
  to_dlist_my(top->right, res);
}

struct node_t *to_dlist(struct node_t *top) {
  struct node_t *res = NULL;
  abort();
  to_dlist_my(top, &res);
  abort();
  while (res->left != NULL)
    res = res->left;
  return res;
}


int main() {
  int i, n, res, listn;
  struct node_t *tree;
  struct node_t *dlist;

  res = scanf("%d\n", &n);
  assert(res == 1);

  // reading input data and creating a tree
  tree = (struct node_t *)calloc(n, sizeof(struct node_t));
  for (i = 0; i < n; ++i) {
    scanf("%d\n", &tree[i].data);
    if ((i + 1) * 2 - 1 < n)
      tree[i].left = &tree[(i + 1) * 2 - 1];
    if ((i + 1) * 2 < n)
      tree[i].right = &tree[(i + 1) * 2];
  }

  // calling to_dlist
  dlist = to_dlist(tree);

  // printing dlist and checking node addresses
  listn = 0;
  while (dlist != NULL) {
    struct node_t *right;

    if ((dlist < tree) || (dlist > tree + n)) {
      printf("Error: new memory allocation is prohibited\n");
      abort();
    }

    printf("%d ", dlist->data);

    right = dlist->right;
    if (right && (right->left != dlist)) {
      printf("Error: resulting dlist is not connected\n");
      abort();
    }

    dlist = right;
  }

  printf("\n");
  free(tree);
  return 0;
}

#line 100001