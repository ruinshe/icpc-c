#ifndef TRIE_H
#define TRIE_H

#ifndef TRIE_DATA
#define TRIE_DATA
#endif

struct trie_t {
  struct node_t {
    TRIE_DATA;
    node_t* next[MaxC];
  } memo[MaxM], *root, *cur;

  void init() {
    cur = memo;
    root = new_node();
  }

  node_t* new_node() {
    memset(cur, 0, sizeof(node_t));
    return cur++;
  }
};

#endif
