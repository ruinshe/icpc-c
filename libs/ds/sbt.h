#ifndef SBT_T
#define SBT_T

#ifndef MaxM
#define MaxM 1005
#endif

template<typename K , typename V>
struct sbt_t {
  struct node_t {
    K key;
    V value;
    int size;
    node_t* c[2];
  } memo[MaxM], *cur, *nil;

  void update(node_t* t) {
    if (t == nil) return;
    t->size = t->c[0]->size + t->c[1]->size + 1;
    t->value = t->value + t->c[0]->value + t->c[1]->value;
  }

  node_t* new_node(K key, V value) {
    cur->key = key;
    cur->value = value;
    cur->size = 1;
    cur->c[0] = cur->c[1] = nil;
    return cur++;
  }

 void init() {
    nil = cur = memo;
    nil = new_node(K(), V());
    nil->size = 0;
  }

  void rotate(node_t*& t, int f) {
    node_t* k = t->c[f ^ 1];
    t->c[f ^ 1] = k->c[f];
    k->c[f] = t;
    update(t);
    update(k);
    t = k;
  }

  void keep (node_t*& t, int f) {
    if (t == nil) return ;
    else if (t->c[f]->c[f]->size > t->c[f ^ 1]->size) rotate(t, f ^ 1);
    else if (t->c[f]->c[f ^ 1]->size > t->c[f ^ 1]->size) rotate(t->c[f], f), rotate(t, f ^ 1);
    else return;
    for (int i = 0; i < 2; i++) keep(t->c[i], i);
    for (int i = 0; i < 2; i++) keep(t, i);
  }

  void insert(node_t*& t, K key, V value) {
    if (t == nil) t = new_node(key, value);
    else {
      insert(t->c[key >= t->key], key, value);
      update(t);
      keep(t, key >= t->key);
    }
  }

  node_t* del(node_t*& t, K key) {
    node_t* p;
    if (t == nil) return nil;
    if (key == t->key || t->c[key > t->key] == nil) {
      if (t->c[0] != nil && t->c[1] != nil) {
        p = del(t->c[0], key + 1);
        t->key = p->key;
        t->value = p->value;
      } else {
        p = t;
        t = t->c[t->c[0] == nil];
      }
    } else {
      p = del(t->c[key > t->key], key);
    }
    update(t);
    return p;
  }
};

#endif
