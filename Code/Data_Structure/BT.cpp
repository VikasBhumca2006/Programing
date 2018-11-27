#include < iostream >
#include < stdio.h >
#include < limits.h >
#include < stack >
#include < queue >
#include < map >
#include < stdlib.h >

#define MAX 100

using namespace std;
int max(int a, int b)
{
    return a > b ? a : b;
}

int Min(int a, int b)
{
    return a < b ? a : b;
}

typedef struct node
{
    int data;
    struct node * left;
    struct node * right;
    struct node * nextRight;
}
Node;

struct node * newNode(int data)
{
    struct node * node = new Node;
    node - > data = data;
    node - > left = NULL;
    node - > right = NULL;
    return (node);
}

void printPreorderI1(Node * t)
{
    if (!t) 
		return;
	
    stack < Node * > s;
    s.push(t);

	while (!s.empty())
    {
        t = s.top();
        s.pop();
        cout << t - > data << " ";
        if (t - > right) s.push(t - > right);
        if (t - > left) s.push(t - > left);
    }
	
}

void printPostorderI1(Node * t)
{
    if (!t) return;
    stack < Node * > s;
	
label: while (t != NULL)
       {
           if (t - > right) 
		   	s.push(t - > right);
		   
           s.push(t);
           t = t - > left;
       }
       while (!s.empty())
       {
           t = s.top();

		   s.pop();
		   
           if (!s.empty() && t - > right == s.top())
           {
               s.pop();
               s.push(t);
               t = t - > right;
               goto label;
           } 
		   else 
		   	cout << t - > data << " ";
       }
}

void printPreorderI2(Node * t)
{
    if (!t) 
		return;

	while (t != NULL)
    {
        if (t - > left == NULL)
        {
            cout << t - > data << " ";
            t = t - > right;
        } 
		else
        {
            Node * p = t - > left;

			while (p - > right != NULL && p - > right != t) 
				p = p - > right;
			
            if (p - > right == t)
            {
                p - > right = NULL;
                t = t - > right;
            } 
			else
            {
                cout << t - > data << " ";
                p - > right = t;
                t = t - > left;
            }
        }
    }
}

void printInorderI2(Node * t)
{
    if (!t) return;
    while (t != NULL)
    {
        if (t - > left == NULL)
        {
            cout << t - > data << " ";
            t = t - > right;
        } 
		else
        {
            Node * p = t - > left;

			while (p - > right != NULL && p - > right != t) 
				p = p - > right;
			
            if (p - > right == t)
            {
                cout << t - > data << " ";
                p - > right = NULL;
                t = t - > right;
            } else
            {
                p - > right = t;
                t = t - > left;
            }
        }
    }
} // morrish traversal

void printPostorderI2(Node * t)
{
    if (!t) return;
    stack < Node * > s1, s2;
    s1.push(t);
    while (!s1.empty())
    {
        t = s1.top();
        s1.pop();
        if (t - > left) s1.push(t - > left);
        if (t - > right) s1.push(t - > right);
        s2.push(t);
    }
    while (!s2.empty())
    {
        cout << s2.top() - > data << " ";
        s2.pop();
    }
} // post order usinfg two stack

int sizeofBT(Node * t)
{
    if (!t) return 0;
    return 1 + sizeofBT(t - > left) + sizeofBT(t - > right);
}
int height(Node * t)
{
    if (!t) return 0;
    return (1 + max(height(t - > left), height(t - > right)));
}
Node * deleteBT(Node * t)
{
    if (!t) return t;
    deleteBT(t - > left);
    deleteBT(t - > right);
    cout << "deleting " << t - > data << " ";
    free(t);
    t = NULL;
    return t;
} // delete BT in post order way
Node * Mirror(Node * t)
{
    if (!t) return t;
    Mirror(t - > left);
    Mirror(t - > right);
    Node * p = t - > left;
    t - > left = t - > right;
    t - > right = p;
} // make mirror of a tree
void printPathUtil(int a[], Node * t, int l)
{
    if (!t) return;
    a[l++] = t - > data;
    if (t - > left == NULL && t - > right == NULL)
    {
        for (int i = 0; i < l; i++) cout << a[i] << " ";
        cout << endl;
    }
    printPathUtil(a, t - > left, l);
    printPathUtil(a, t - > right, l);
}
void printPath(Node * t)
{
    int a[MAX] =
    {
        0
    };
    printPathUtil(a, t, 0);
}
void printLevelorder(Node * t)
{
    if (!t) return;
    queue < Node * > q;
    q.push(t);
    while (!q.empty())
    {
        int l = q.size();
        while (l--)
        {
            t = q.front();
            q.pop();
            cout << t - > data << " ";
            if (t - > left) q.push(t - > left);
            if (t - > right) q.push(t - > right);
        }
        cout << endl;
    }
}
void printLevelorderZigZag(Node * t)
{
    if (!t) return;
    bool f = false;
    stack < Node * > s1, s2;
    s1.push(t);
    while (!s1.empty() || !s2.empty())
    {
        while (!s1.empty())
        {
            t = s1.top();
            s1.pop();
            cout << t - > data << " ";
            if (t - > right) s2.push(t - > right);
            if (t - > left) s2.push(t - > left);
        }
        cout << endl;
        while (!s2.empty())
        {
            t = s2.top();
            s2.pop();
            cout << t - > data << " ";
            if (t - > left) s1.push(t - > left);
            if (t - > right) s1.push(t - > right);
        }
        cout << endl;
    }
}
void printLevel(Node * t, int l)
{
    if (!t) return;
    if (l == 0)
    {
        cout << t - > data << " ";
        return;
    }
    printLevel(t - > left, l - 1);
    printLevel(t - > right, l - 1);
}
void printLevelorder1(Node * t)
{
    int h = height(t);
    for (int i = 0; i < h; i++, cout << endl) printLevel(t, i);
}
bool isSumProperty(Node * t)
{
    if (t == NULL || t - > left == NULL && t - > right == NULL) return true;
    int ls = 0, rs = 0;
    if (t - > left) ls = t - > left - > data;
    if (t - > right) rs = t - > right - > data;
    return (t - > data == ls + rs) && isSumProperty(t - > left) && isSumProperty(t - > right);
}
int diameterBT(Node * t)
{
    if (!t) return 0;
    int h1 = height(t - > left);
    int h2 = height(t - > right);
    int h = h1 + h2 + 1;
    int d1 = diameterBT(t - > left);
    int d2 = diameterBT(t - > right);
    return max(h, max(d1, d2));
}
int diameterutil(Node * t, int & h)
{
    if (!t) return 0;
    int lh = 0, rh = 0;
    int d1 = diameterutil(t - > left, lh);
    int d2 = diameterutil(t - > right, rh);
    h = 1 + max(lh, rh);
    return max(1 + lh + rh, max(d1, d2));
}
int diameterBT1(Node * t)
{
    int h = 0;
    return diameterutil(t, h);
}
bool heightBalance(Node * t)
{
    if (!t) return true;
    int lh = height(t - > left);
    int rh = height(t - > right);
    return (abs(rh - lh) < 2) && heightBalance(t - > left) && heightBalance(t - > right);
}
int maxHeight(Node * t)
{
    if (!t) return 0;
    return 1 + max(maxHeight(t - > left), maxHeight(t - > right));
}
int minHeight(Node * t)
{
    if (!t) return 0;
    return 1 + Min(minHeight(t - > left), minHeight(t - > right));
}
bool heightBalance1(Node * t)
{
    if (!t) return true;
    return (abs(maxHeight(t) - minHeight(t)) < 2);
}
bool heightBalanceUtil(Node * t, int & h)
{
    if (!t) return true;
    int lh = 0, rh = 0;
    bool l = heightBalanceUtil(t - > left, lh);
    if (!l) return l;
    bool r = heightBalanceUtil(t - > right, rh);
    h = 1 + max(lh, rh);
    return l && r && abs(lh - rh) < 2;
}
bool heightBalance2(Node * t)
{
    if (!t) return true;
    int h = 0;
    return heightBalanceUtil(t, h);
}
bool hasPathSum(Node * t, int s)
{
    if (!t) return s == 0;
    if (t - > left == NULL && t - > right == NULL && t - > data == s) return true;
    return hasPathSum(t - > left, s - t - > data) || hasPathSum(t - > right, s - t - > data);
}
Node * buildTree(int in [], int pre[], int l, int n, int & r)
{
    if (l > n) return NULL;
    Node * t = newNode(pre[r++]);
    if (l == n) return t;
    int i = 0;
    for (i = l; i <= n; i++)
        if (t - > data == in [i]) break;
    t - > left = buildTree( in , pre, l, i - 1, r);
    t - > right = buildTree( in , pre, i + 1, n, r);
    return t;
}
Node * buildTreeS(int a[], int l, int h)
{
    if (l > h) return NULL;
    int j = l;
    for (int i = l + 1; i <= h; i++)
        if (a[l] < a[i]) l = i;
    Node * t = newNode(a[j]);
    if (l == h) return t;
    t - > left = buildTreeS(a, l, j - 1);
    t - > right = buildTreeS(a, j + 1, h);
    return t;
}
Node * constructTree(int pre[], int preLN[], int & l, int h)
{
    if (l > h) return NULL;
    int k = l;
    Node * t = newNode(pre[l++]);
    if (preLN[k] == 'L') return t;
    t - > left = constructTree(pre, preLN, l, h);
    t - > right = constructTree(pre, preLN, l, h);
    return t;
}
void doubleBT(Node * t)
{
    if (!t) return;
    doubleBT(t - > left);
    doubleBT(t - > right);
    Node * p = t - > left;
    t - > left = newNode(t - > data);
    t - > left - > left = p;
}
int countNode(Node * t, int l)
{
    if (!t) return 0;
    if (l == 0) return 1;
    else return countNode(t - > left, l - 1) + countNode(t - > right, l - 1);
}
int maxWidth(Node * t)
{
    if (!t) return 0;
    int h = height(t);
    int w = INT_MIN;
    for (int i = 0; i < h; i++)
    {
        int a = countNode(t, i);
        if (w < a) w = a;
    }
    return w;
}
void maxWidthUtil(Node * t, int a[], int l)
{
    if (!t) return;
    a[l]++;
    maxWidthUtil(t - > left, a, l + 1);
    maxWidthUtil(t - > right, a, l + 1);
}
int maxWidth1(Node * t)
{
    int a[MAX] =
    {
        0
    };
    int w = INT_MIN;
    maxWidthUtil(t, a, 0);
    for (int i = 0; i < MAX; i++)
        if (w < a[i]) w = a[i];
    return w;
}
bool isMirror(Node * a, Node * b)
{
    if (a == NULL && b == NULL) return true;
    return a != NULL && b != NULL && isMirror(a - > left, b - > right) && isMirror(a - > left, b - > right);
}
bool isFoldable(Node * t)
{
    if (!t) return true;
    return isMirror(t - > left, t - > right);
}
void printKDistantDown(Node * t, int d)
{
    if (!t) return;
    if (d == 0) cout << t - > data;
    printKDistantDown(t - > left, d - 1);
    printKDistantDown(t - > right, d - 1);
}
void levelofNode(Node * t, int x, int & l, int n)
{
    if (!t) return;
    if (t - > data == x)
    {
        l = n;
        return;
    }
    levelofNode(t - > left, x, l, n + 1);
    levelofNode(t - > right, x, l, n + 1);
}
int levelofNode2(Node * t, int x, int l)
{
    if (!t) return 0;
    if (t - > data == x)
    {
        return l;
    }
    int a = levelofNode2(t - > left, x, l + 1);
    if (a != 0) return a;
    return levelofNode2(t - > right, x, l);
}
bool printAncestorsBT(Node * t, int x)
{
    if (!t) return false;
    if (t - > data == x) return true;
    if (printAncestorsBT(t - > left, x) || printAncestorsBT(t - > right, x))
    {
        cout << t - > data << " ";
        return true;
    }
}
void connect(Node * t)
{
    if (!t) return;
    if (t - > left) t - > left - > nextRight = t - > right;
    if (t - > right) t - > right - > nextRight = t - > nextRight ? t - > nextRight - > left : NULL;
    connect(t - > left);
    connect(t - > right);
} // will not work for not complete binary tree for that use level order
//void connectRecur(struct node* p)
{if(!p) return;if(p->nextRight != NULL) connectRecur(p->nextRight);if(p->left)
    {if (p->right)
        { p->left->nextRight = p->right; p->right->nextRight = getNextRight(p);   }    else      p->left->nextRight = getNextRight(p);    connectRecur(p->left);  }  else if (p->right)
        {    p->right->nextRight = getNextRight(p);    connectRecur(p->right);  }  else    connectRecur(getNextRight(p));}
        //struct node *getNextRight(struct node *p)
{    struct node *temp = p->nextRight;   while(temp != NULL)
    {        if(temp->left != NULL)            return temp->left;        if(temp->right != NULL)            return temp->right;        temp = temp->nextRight;    }   return NULL;}
    //void connect1(struct node* p)
{    struct node *temp;    if (!p)      return;    p->nextRight = NULL;    while (p != NULL)
    {        struct node *q = p;        while (q != NULL)
        {            if (q->left)
            {                if (q->right)                    q->left->nextRight = q->right;                else                    q->left->nextRight = getNextRight(q);            }            if (q->right)                q->right->nextRight = getNextRight(q);            q = q->nextRight;        }        if (p->left)           p = p->left;        else if (p->right)           p = p->right;        else           p = getNextRight(p);    }}
void vsumUtil(Node * t, map < int, int > & m, int l)
{
    if (!t) return;
    m[l] += t - > data;
    vsumUtil(t - > left, m, l - 1);
    vsumUtil(t - > right, m, l + 1);
}
void vsum(Node * t)
{
    if (!t) return;
    map < int, int > m;
    vsumUtil(t, m, 0);
    for (map < int, int > ::iterator it = m.begin(); it != m.end(); it++) cout << it - > first << " -> " << it - > second << endl;
}
void maxSum(Node * t, int & ms, Node * & p, int sum)
{
    if (!t) return;
    sum += t - > data;
    if (t - > left == NULL && t - > right == NULL)
    {
        if (ms < sum) ms = sum;
        p = t;
    }
    maxSum(t - > left, ms, p, sum);
    maxSum(t - > right, ms, p, sum);
}
bool printPath(Node * t, Node * p)
{
    if (!t) return false;
    if (t == p)
    {
        cout << t - > data << " ";
        return true;
    }
    if (printPath(t - > left, p) || printPath(t - > right, p))
    {
        cout << t - > data << " ";
        return true;
    }
}
int maxSumPath(Node * t)
{
    int msum = INT_MIN;
    Node * p = NULL;
    maxSum(t, msum, p, 0);
    printPath(t, p);
    return msum;
}
void printLeftV(Node * t)
{
    if (!t) return;
    if (t - > left == NULL && t - > right == NULL) return;
    cout << t - > data << " ";
    if (t - > left) printLeftV(t - > left);
    else if (t - > right) printLeftV(t - > right);
}
void printRightV(Node * t)
{
    if (!t) return;
    if (t - > left == NULL && t - > right == NULL) return;
    cout << t - > data << " ";
    if (t - > right) printLeftV(t - > right);
    else if (t - > left) printLeftV(t - > left);
}
void printBottomV(Node * t)
{
    if (!t) return;
    if (t - > left == NULL && t - > right == NULL) cout << t - > data << " ";
    printBottomV(t - > left);
    printBottomV(t - > right);
}
void printBoundary(Node * t)
{
    if (!t) return;
    printLeftV(t);
    printBottomV(t);
    printRightV(t - > right);
}
struct P
{
    Node * t;
    int d;
};
void BottomView(Node * t)
{
    if (!t) return;
    map < int, int > m;
    queue < struct P > q;
    P a;
    a.t = t;
    a.d = 0;
    q.push(a);
    while (!q.empty())
    {
        int l = q.size();
        while (l--)
        {
            a = q.front();
            q.pop();
            m[a.d] = a.t - > data;
            if (a.t - > left)
            {
                P b;
                b.t = a.t - > left;
                b.d = a.d - 1;
                q.push(b);
            }
            if (a.t - > right)
            {
                P b;
                b.t = a.t - > right;
                b.d = a.d + 1;
                q.push(b);
            }
        }
    }
    for (map < int, int > ::iterator it = m.begin(); it != m.end(); it++) cout << it - > second << " ";
    cout << endl;
}
void TopView(Node * t)
{
    if (!t) return;
    map < int, int > m;
    queue < struct P > q;
    P a;
    a.t = t;
    a.d = 0;
    q.push(a);
    while (!q.empty())
    {
        int l = q.size();
        while (l--)
        {
            a = q.front();
            q.pop();
            if (m.find(a.d) == m.end()) m[a.d] = a.t - > data;
            if (a.t - > left)
            {
                P b;
                b.t = a.t - > left;
                b.d = a.d - 1;
                q.push(b);
            }
            if (a.t - > right)
            {
                P b;
                b.t = a.t - > right;
                b.d = a.d + 1;
                q.push(b);
            }
        }
    }
    for (map < int, int > ::iterator it = m.begin(); it != m.end(); it++) cout << it - > second << " ";
    cout << endl;
}
void LeftView(Node * t, int & l, int m)
{
    if (!t) return;
    if (m > l)
    {
        cout << t - > data << " ";
        l = m;
    }
    LeftView(t - > left, l, m + 1);
    LeftView(t - > right, l, m + 1);
}
void RightView(Node * t, int & l, int m)
{
    if (!t) return;
    if (m > l)
    {
        cout << t - > data << " ";
        l = m;
    }
    RightView(t - > right, l, m + 1);
    RightView(t - > left, l, m + 1);
}
Node * buildTreePrePost(int pre[], int post[], int & i, int l, int h, int n)
{ /*if tree is full binary tree*/
    if (i == n || l > h) return NULL;
    Node * t = newNode(pre[i++]);
    int k;
    for (k = l; k <= h; k++)
        if (post[k] == t - > data) break;
    if (k <= h)
    {
        t - > left = buildTreePrePost(pre, post, i, l, k, n);
        t - > right = buildTreePrePost(pre, post, i, k + 1, h, n);
    }
    return t;
}
bool isIsomorphic(Node * t1, Node * t2)
{
    if (t1 == NULL && t2 == NULL) return true;
    if (t1 == NULL || t2 == NULL) return false;
    return t1 - > data == t2 - > data && (isIsomorphic(t1 - > left, t2 - > left) && isIsomorphic(t1 - > right, t2 - > right) || isIsomorphic(t1 - > left, t2 - > right) && isIsomorphic(t1 - > right, t2 - > left));
}
void deepestLeafNode(Node * t, int & n, int & l, int d)
{
    if (!t) return;
    if (t - > left == NULL && t - > right == NULL)
        if (l < d)
        {
            l = d;
            n = t - > data;
        }
    deepestLeafNode(t - > left, n, l, d + 1);
    deepestLeafNode(t - > right, n, l, d + 1);
}
Node * RemoveNodeNotSum(Node * t, int k)
{
    if (!t) return t;
    t - > left = RemoveNodeNotSum(t - > left, k - t - > data);
    t - > right = RemoveNodeNotSum(t - > right, k - t - > data);
    if (t - > left == NULL && t - > right == NULL && k - t - > data > 0) return NULL;
    return t;
}#
    if 1
int main()
{
    int k = 45;
    Node * root = newNode(1);
    root - > left = newNode(2);
    root - > right = newNode(3);
    root - > left - > left = newNode(4);
    root - > left - > right = newNode(5);
    root - > right - > left = newNode(6);
    root - > right - > right = newNode(7);
    root - > left - > left - > left = newNode(8);
    root - > left - > left - > right = newNode(9);
    root - > left - > right - > left = newNode(12);
    root - > right - > right - > left = newNode(10);
    root - > right - > right - > left - > right = newNode(11);
    root - > left - > left - > right - > left = newNode(13);
    root - > left - > left - > right - > right = newNode(14);
    root - > left - > left - > right - > right - > left = newNode(15);

    printf("Tree before truncation\n");
    printInorder(root);

    root = RemoveNodeNotSum(root, k); // k is 45

    printf("\n\nTree after truncation\n");
    printInorder(root);

    /*
       int pre[] =
       {1, 2, 4, 8, 9, 5, 3, 6, 7};
       int post[] =
       {8, 9, 4, 5, 2, 6, 7, 3, 1};
       int size = sizeof( pre ) / sizeof( pre[0] );
       int l=0;
       struct node *root = buildTreePrePost(pre, post,l,0,size-1, size);

       printf("Inorder traversal of the constructed tree: \n");
       printInorder(root);
       */
    return 1;
}#
endif
/*
   int main()

   {
   struct node *root = NULL;
   int pre[] =
   {10, 30, 20, 5, 15};
   int preLN[] =
   {'N', 'N', 'L', 'L', 'L'};
   int n = sizeof(pre)/sizeof(pre[0]);
   int l=0;
   root = constructTree (pre, preLN,l, n-1);
   printf("Following is Inorder Traversal of the Constructed Binary Tree: \n");
   printInorder (root);
   return 0;
   }
   */
/*
   int main()

   {
   int inorder[] =
   {1, 5, 10, 40, 30, 15, 28, 20};
   int len = sizeof(inorder)/sizeof(inorder[0]);
   struct node *root = buildTreeS(inorder, 0, len - 1);
   printf("\n Inorder traversal of the constructed tree is \n");
   printInorder(root);
   return 0;
   }
   */
/*
   int main()

   {
   int in[] =
   {'D', 'B', 'E', 'A', 'F', 'C'};
   int pre[] =
   {'A', 'B', 'D', 'E', 'C', 'F'};
   int k=0;
   int len = sizeof(in)/sizeof(in[0]);
   struct node *root = buildTree(in, pre, 0, len - 1,k);
   printf("\n Inorder traversal of the constructed tree is \n");
   printInorderc(root);
   return 0;
   }
   */
