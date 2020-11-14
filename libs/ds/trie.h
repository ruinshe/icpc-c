#ifndef TRIE_H
#define TRIE_H

#ifndef TRIE_DATA
#define TRIE_DATA
#endif

#ifndef MaxM
#define MaxM 1005
#endif

#ifndef MaxC
#define MaxC 26
#endif

namespace trie {

struct node_t {
  TRIE_DATA;
  node_t *next[MaxC];

#ifdef TRIE_AC
  node_t *fail;
#endif // TRIE_AC
} memo[MaxM], *root, *cur;

node_t *new_node() {
  std::fill(cur->next, cur->next + MaxC, root);
#ifdef TRIE_AC
  cur->fail = root;
#endif
  return cur++;
}

void init() {
  cur = root = memo;
  root = new_node();
}

node_t *add(const char *s) {
  node_t *now = root;
  for (const char *p = s; *p; p++) {
    int c = *p - 'a';
    if (now->next[c] == root) {
      now->next[c] = new_node();
    }
    now = now->next[c];
  }
  return now;
}

#ifdef TRIE_AC
node_t *queue[MaxM];

int bfs() {
  int f = 0, b = 0;
  root->fail = root;

  queue[b++] = root;
  while (f < b) {
    node_t *u = queue[f++];

    for (int i = 0; i < MaxC; i++) {
      node_t *v = u->next[i];
      if (v != root) {
        if (u != root) {
          v->fail = u->fail->next[i];
        }
        queue[b++] = v;
      } else {
        u->next[i] = u->fail->next[i];
      }
    }
  }

  return b;
}
#endif // TRIE_AC
};     // namespace trie

#endif
