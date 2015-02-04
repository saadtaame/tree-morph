#include <cstdio>
#include <vector>

using namespace std;

const int N = 1000; /* max nodes - adjust */
const int LEFT = 0;
const int RIGHT = 1;
int n;

struct Node
{   int k, id; /* key, label */
    Node *p, *l, *r; /* parent, left, right pointers */
    Node() { p = l = r = 0; }
};

Node pool[2 * N];
int id_of[N];
int label_of[N];

/* right rotation */
void rotr(Node *x, vector< pair<int, int> > &v, bool rev = false)
{   if(rev)
    {   v.push_back(make_pair(LEFT, x->p->id));
    }
    else
    {   v.push_back(make_pair(RIGHT, x->id));
    }

    Node *y, *z;
    y = x->p, z = y->p;
    if((y->l = x->r)) y->l->p = y;
    x->r = y, y->p = x;
    if((x->p = z))
    {   if(y == z->l) z->l = x;
        else z->r = x;
    }
}

/* left rotation */
void rotl(Node *x, vector< pair<int, int> > &v, bool rev = false)
{   if(rev)
    {   v.push_back(make_pair(RIGHT, x->p->id));
    }
    else
    {   v.push_back(make_pair(LEFT, x->id));
    }

    Node *y, *z;
    y = x->p, z = y->p;
    if((y->r = x->l)) y->r->p = y;
    x->l = y, y->p = x;
    if((x->p = z))
    {   if(y == z->l) z->l = x;
        else z->r = x;
    }
}

vector< pair<int, int> > splay(Node *x, bool rev = false)
{   vector< pair<int, int> > v;
    Node *y, *z;
    while(x->p)
    {   y = x->p;
        if(y->p == 0)
        {   if(x == y->l) rotr(x, v, rev);
            else rotl(x, v, rev);
        }
        else
        {   z = y->p;
            if(y == z->l)
            {   if(x == y->l) rotr(y, v, rev), rotr(x, v, rev);
                else rotl(x, v, rev), rotr(x, v, rev);
            }
            else
            {   if(x == y->r) rotl(y, v, rev), rotl(x, v, rev);
                else rotr(x, v, rev), rotl(x, v, rev);
            }
        }
    }
    return v;
}

/* return node with key k */
Node * get_node(Node *s, int k)
{   if(s == 0) return 0;
    if(s->k == k) return s;
    Node *x = get_node(s->l, k);
    Node *y = get_node(s->r, k);
    return x ? x : y;
}

/* transform tree to canonical form */
vector< pair<int, int> > morph(Node *s, int l, int r, bool rev = false)
{   vector< pair<int, int> > v;
    if(s == 0)
    {   return v;
    }
    Node *x = get_node(s, (l + r) / 2);
    v = splay(x, rev);
    if(rev == false)
    {   id_of[(l + r) / 2] = x->id;
    }
    else
    {   label_of[x->id] = (l + r) / 2;
    }
    if(x->l) x->l->p = 0;
    if(x->r) x->r->p = 0;
    vector< pair<int, int> > vv = morph(x->l, l, (l + r) / 2 - 1, rev);
    v.insert(v.end(), vv.begin(), vv.end());
    vector< pair<int, int> > ww = morph(x->r, (l + r) / 2 + 1, r, rev);
    v.insert(v.end(), ww.begin(), ww.end());
    return v;
}

/* assign labels to nodes */
int next_k;
void dfs(Node *x)
{   if(x)
    {   dfs(x->l);
        x->k = next_k++;
        dfs(x->r);
    }
}

Node *read_tree(bool rev = false)
{   int m = 0;
    if(rev)
    {   m += n;
    }
    for(int i = 0; i < n; i++)
    {   int a, b;
        Node *x, *y, *z;
        scanf("%d %d", &a, &b);
        x = &pool[i + m];
        y = z = 0;
        if(a != -1)
        {   y = &pool[a + m];
        }
        if(b != -1)
        {   z = &pool[b + m];
        }
        x->id = i;
        if(y) y->id = a;
        if(z) z->id = b;
        x->l = y;
        x->r = z;
        if(y) y->p = x;
        if(z) z->p = x;
    }
    Node *root = 0;
    for(int i = 0; i < n && root == 0; i++)
    {   if(pool[i + m].p == 0)
        {   root = &pool[i + m];
        }
    }
    next_k = 0;
    dfs(root);
    return root;
}

int main(void)
{   scanf("%d", &n);

    Node *s = read_tree();
    Node *t = read_tree(true);

    vector< pair<int, int> > v = morph(s, 0, n - 1);
    vector< pair<int, int> > w = morph(t, 0, n - 1, true);

    for(int i = 0; i < w.size(); i++)
    {   w[i].second = id_of[ label_of[ w[i].second ] ];
    }

    v.insert(v.end(), w.rbegin(), w.rend());
    for(int i = 0; i < v.size(); i++)
    {   printf("rotate-%s(%d)\n", v[i].first == LEFT ? "left" : "right",
            v[i].second);
    }

    return 0;
}
