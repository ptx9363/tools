#include <iostream>
#include <vector>

using namespace std;

class RBNode{
  public:
    RBNode* rchild;
    RBNode* lchild;
    RBNode* parent;
    int val;
    int color; // 0 for red, 1 for black
    
    // insert node
    RBNode(int v, int c = 0): rchild(NULL), lchild(NULL), parent(NULL){
      val = v;
      color = c;
    }
};

class RBTree{

  public:
    RBNode* root;

    RBTree(){
      root = NULL;
    }

    void rtleft(RBNode* p);
    void rtright(RBNode* p);
    RBNode* rb_get(int x);
    void rb_print();
    void rb_print_node(RBNode* p);
    void rb_insert(int x);
    void rb_insert_fixup(RBNode* p);
    void rb_remove(RBNode* p);
    void rb_delete(RBNode* p);
    void rb_delete(int x);
    void rb_delete_fixup(RBNode* p);
    RBNode* rb_tree_successor(RBNode* p);
};

RBNode* RBTree::rb_get(int x){
  auto pos = this->root;
  while (pos != NULL){
    if (pos->val == x)
      break;
    else{
      if(pos->val < x)
        pos = pos->rchild;
      else
        pos = pos->lchild;
    }
  }
  return pos;
}

void RBTree::rb_delete(int x){
  RBNode* pos = rb_get(x);
  if (pos != NULL){

    cout << "delete " << pos->val << endl;
    rb_delete(pos);
  }

}

RBNode* RBTree::rb_tree_successor(RBNode* p){
  if (p->lchild != NULL){
    RBNode* s = p->lchild;
    while (s->rchild != NULL)
      s = s->rchild;
    return s;
  }
  else
    return NULL;
}

void RBTree::rb_print_node(RBNode* p){
  int rval = -1;
  int lval = -1;

  if (p->rchild != NULL)
    rval = p->rchild->val;

  if (p->lchild != NULL)
    lval = p->lchild->val;

  cout << "[" << p->val <<  "]: left is " << lval << ", right is " << rval << ", color is " << p->color << endl;

  if (p->lchild != NULL)
    rb_print_node(p->lchild);

  if (p->rchild != NULL)
    rb_print_node(p->rchild);
}

void RBTree::rb_print(){
  rb_print_node(this->root);
}

void RBTree::rb_delete(RBNode* p){
  RBNode* y(NULL);
  RBNode* x(NULL);

  if (p->lchild == NULL || p->rchild == NULL)
    y = p;
  else
    y = rb_tree_successor(p);

  if (y->lchild != NULL)
    x = y->lchild;
  else
    x = y->rchild;

  if (x != NULL)
    x->parent = y->parent;

  if (y->parent == NULL)
    this->root = x;
  else{
    if (y == y->parent->lchild)
      y->parent->lchild = x;
    else
      y->parent->rchild = x;
  }

  if (y != p)
    p->val = y->val;

  if (x != NULL && y->color == 1)
    rb_delete_fixup(x);

  delete y;
}

void RBTree::rb_delete_fixup(RBNode* x){
  while(x != this->root && x->color == 1){
      if (x == x->parent->lchild){
        auto p = x->parent;
        auto u = p->rchild;

        if (u != NULL && u->color == 0){
          p->color = 0;
          u->color = 1;
          rtleft(p);
          u = p->rchild;
        }

        if ((u->rchild == NULL || u->rchild->color == 1) && (u->lchild == NULL || u->lchild->color == 1)){
          u->color = 0;
          x = p;
        }
        else{
          if (u->rchild == NULL || u->rchild->color == 1){
            u->lchild->color = 1;
            u->color = 0;
            rtright(u);
            u = p->rchild;
          }

          u->color = p->color;
          p->color = 1;
          if (u->rchild != NULL)
            u->rchild->color = 1;
          rtleft(p);
          x = this->root;
        }
      }

      else{
        auto p = x->parent;
        auto u = p->lchild;

        if (u != NULL && u->color == 0){
          p->color = 0;
          u->color = 1;
          rtright(p);
          u = p->lchild;
        }

        if ((u->rchild == NULL || u->rchild->color == 1) && (u->lchild == NULL || u->lchild->color == 1)){
          u->color = 0;
          x = p;
        }
        else{
          if (u->lchild == NULL || u->lchild->color == 1){
            u->rchild->color = 1;
            u->color = 0;
            rtleft(u);
            u = p->lchild;
          }

          u->color = p->color;
          p->color = 1;
          if (u->lchild != NULL)
            u->lchild->color = 1;
          rtright(p);
          x = this->root;
        }
      }
 }

  x->color = 1;
}

void RBTree::rb_insert(int x){
  auto pos = this->root;

  RBNode* node = new RBNode(x, 0);

  if (pos == NULL){
    this->root = node;
    this->root->color = 1; // root is black
  }
  else{
    auto fa = pos;
    while (pos != NULL){
      fa = pos;
      if (pos->val == x)
        return; // no need to insert
      else{
        if ( x > pos->val )
          pos = pos->rchild;
        else
          pos = pos->lchild;
      }
    }

    node->parent = fa;
    if (node->val < fa->val)
      fa->lchild = node;
    else
      fa->rchild = node;
  }
  pos = node;

  rb_insert_fixup(pos);
}

void RBTree::rb_insert_fixup(RBNode* n){
  while(n->parent != NULL && n->parent->color == 0){
    auto p = n->parent;
    if (p == p->parent->lchild){
      auto pp = p->parent;
      auto u = p->parent->rchild;

      if (u != NULL && u->color == 0){
        // uncle is red
        u->color = 1;
        p->color = 1;
        pp->color = 0;
        n = pp;
      }
      else{
        if (n == p->rchild){
          n = p;
          rtleft(n);
        }
        p = n->parent;
        pp->color = 0;
        p->color = 1;
        rtright(pp);
        n = p;
      }
    }
    else{
      auto pp = p->parent;
      auto u = p->parent->lchild;

      if (u != NULL && u->color == 0){
        // uncle is red
        u->color = 1;
        p->color = 1;
        pp->color = 0;
        n = pp;
      }
      else{
        if (n == p->lchild){
          n = p;
          rtright(n);
        }
        p = n->parent;
        pp->color = 0;
        p->color = 1;
        rtleft(pp);
        n = p;
      }
    }
  }

  this->root->color = 1; // set root to black
}


void RBTree::rtleft(RBNode* p){
  if (p != NULL){
    auto r = p->rchild;
    
    p->rchild = r->lchild;
    if (r->lchild != NULL)
      r->lchild->parent = p;

    r->parent = p->parent;
    if (r->parent != NULL){
      if (r->parent->lchild == p)
        r->parent->lchild = r;
      else
        r->parent->rchild = r;
    }
    else{
      this->root = r; // rotate root
    }

    r->lchild = p;
    p->parent = r;
  }
}

void RBTree::rtright(RBNode* p){
  if (p != NULL){
    auto l = p->lchild;
    
    p->lchild = l->rchild;
    if (l->rchild != NULL)
        p->rchild->parent = p;

    l->parent = p->parent;
    if (l->parent != NULL){
      if (l->parent->lchild == p)
        l->parent->lchild = l;
      else
        l->parent->rchild = l;
    }
    else{
      this->root = l; // rotate root
    }

    p->parent = l;
    l->rchild = p;
  }
}


int main(){
  auto rbtree = new RBTree();
  
  vector<int> insert_data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  for(auto i : insert_data){
    rbtree->rb_insert(i);
  }

  rbtree->rb_print();

  vector<int> delete_data = {3, 4, 7, 9, 1};
  for(auto i : delete_data){
    cout << "=========================" << endl;
    rbtree->rb_delete(i);
    rbtree->rb_print();
  }


  
  return 0;
}
