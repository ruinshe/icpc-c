#ifndef DYNAMIC_TREE_H
#define DYNAMIC_TREE_H

#ifndef MaxN
#define MaxN 1005
#endif

namespace lct {

struct node_t {
  node_t *c[2], *p;
  int key, s;
  bool rev;
} memo[MaxN], *nil, *pt[MaxN], *st[MaxN];

void init(node_t *x) {
  x->c[0] = x->c[1] = x->p = nil;
  x->key = x->s = -1;
  x->rev = false;
}

void init(int n) {
  pt[0] = nil = &memo[0];
  init(nil);
  for (int i = 1; i <= n; i++) {
    pt[i] = &memo[i];
    init(pt[i]);
  }
}

void update(node_t *x) {
  if (x == nil) {
    return;
  }
  x->s = std::max(std::max(x->c[0]->s, x->key), x->c[1]->s);
}

void rotate(node_t *x, int f) {
  node_t *y = x->p, *z = y->p;
  x->p = z, y->p = x;
  if (z != nil) { // can not conbine
    if (y == z->c[0]) {
      z->c[0] = x;
    } else if (y == z->c[1]) {
      z->c[1] = x;
    }
  }
  y->c[f ^ 1] = x->c[f];
  if (y->c[f ^ 1] != nil) {
    y->c[f ^ 1]->p = y;
  }
  x->c[f] = y;
  update(y);
  update(x);
}

bool isroot(node_t *x) {
  return x->p == nil || (x->p->c[0] != x && x->p->c[1] != x);
}

void reverse(node_t *x) {
  if (x != nil) {
    std::swap(x->c[0], x->c[1]);
    x->rev ^= 1;
  }
}

void pushdown(node_t *x) {
  if (x == nil) {
    return;
  }
  if (x->rev) {
    reverse(x->c[0]);
    reverse(x->c[1]);
    x->rev = false;
  }
}

void splay(node_t *x) {
  int top = 1;
  st[0] = x;
  for (node_t *q = x; !isroot(q);) {
    st[top++] = (q = q->p);
  }
  while (top) {
    pushdown(st[--top]);
  }
  while (!isroot(x)) {
    node_t *y = x->p;
    if (isroot(y)) {
      rotate(x, y->c[0] == x);
    } else {
      int t = (y == y->p->c[0]);
      if (x == y->c[t]) {
        rotate(x, t ^ 1);
        rotate(x, t);
      } else {
        rotate(y, t);
        rotate(x, t);
      }
    }
  }
}

node_t *expose(node_t *x) {
  // return the root
  node_t *y;
  for (y = nil; x != nil; x = x->p) {
    splay(x);
    x->c[1] = y;
    update(y = x);
  }
  return y;
}

void set(node_t *x, int v) {
  x->key = v;
  splay(x);
}

node_t *head(node_t *x) {
  if (x == nil) {
    return nil;
  }
  while (x->c[0] != nil) {
    pushdown(x);
    x = x->c[0];
  }
  splay(x);
  return x;
}

node_t *getRoot(node_t *x) { return head(expose(x)); }

// path from first -> second(only) -> second->c[1]
// all nodes in these three parts are included.
void tackle(node_t *first, node_t *second);

void query(node_t *x, node_t *y) {
  // path: v => u => u->c[1]
  // to calculate edge's weight, u can not be included
  node_t *ry = head(expose(y)), *rx = head(expose(x));
  if (rx != ry) {
    // puts("impossible");
  } else {
    for (node_t *u = y, *v = nil; u != nil; u = u->p) {
      splay(u);
      if (u->p == nil) {
        tackle(v, u);
        return;
      }
      u->c[1] = v;
      update(v = u);
    }
  }
}

void setRoot(node_t *x) { reverse(expose(x)); }

bool merge(node_t *x, node_t *y) {
  // y is x's father in a rooted tree
  node_t *ry = head(expose(y)), *rx = head(expose(x));
  if (rx == ry) {
    return false;
  } else {
    setRoot(x);
    splay(x), x->p = y;
    return true;
  }
}

void cut(node_t *x) {
  splay(x);
  if (x->c[0] != nil)
    x->c[0]->p = x->p, x->p = x->c[0] = nil;
  else
    x->p = nil;
}

node_t *lca(node_t *x, node_t *y) {
  node_t *rx = head(expose(x));
  node_t *ey = expose(y), *ry = head(ey);
  if (rx == ry)
    return ey;
  else
    return nil;
}
}; // namespace lct

#endif
