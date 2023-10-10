#include <stdio.h>
#include <string.h>

typedef struct _node {
	int data;
    struct _node* lp;
    struct _node* rp;
} Node;

Node tree[540001];
int check[270001];

int cur;
void inorder(Node* root)
{
    if(root)
    {
        inorder(root->lp);
        if(!root->lp)
            check[cur++] = root->data;

        inorder(root->rp);
    }
    return;
}

void rotate(Node* root)
{
    if(root)
    {
        Node* tmp = root->lp;
        root->lp = root->rp;
        root->rp = tmp;
    }
    return;
}

int main()
{
    int t, n;
    scanf("%d", &t);
    while(t--)
    {
        int times = 0;
        int ok = 1;
        cur = 1;

        scanf("%d", &n);
    	for(int i = n; i < 2 * n; i++)
        {
        	scanf("%d", &tree[i].data);
            tree[i].lp = NULL;
        	tree[i].rp = NULL;
        }

        // 建樹
    	for(int i = 1; i <= n - 1; i++)
    	{
        	tree[i].lp = &tree[2 * i];
        	tree[i].rp = &tree[2 * i + 1];
            tree[i].data = 0;
    	}

        // 旋轉
        for(int i = n - 1; i >= 1; i--)
    	{
        	if(tree[i].lp->data > tree[i].rp->data)
            {
                rotate(&tree[i]);
                times++;
            }

            tree[i].data = tree[i].lp->data;
    	}

        inorder(&tree[1]);
        for(int i = 1; i <= n; i++)
        {
        	if(check[i] != i)
            {
                ok = 0;
                break;
            }
        }

        if(ok)
        	printf("%d\n", times);
        else
            printf("-1\n");

    }
    return 0;
}
