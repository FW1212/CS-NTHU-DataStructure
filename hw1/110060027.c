#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct _NODE
{
    int data;
    struct _NODE *next;
} Node;

int m, n, k, read;
Node *head;


void reverse(Node**, int, int);

int main()
{
  	Node *now;
  	Node *temp;
  	head = (Node*) malloc(sizeof(Node));
    head->data = 0;
    head->next = NULL;

  	scanf("%d", &m);
  	while(m--)
    {
    	scanf("%d %d", &n, &k);

        now = head;
        for(int i = 1; i <= n; i++)
        {
            Node *np;
            np = (Node*) malloc(sizeof(Node));
            scanf("%d", &read);
            np->data = read;
            np->next = NULL;
            now->next = np;
            now = now->next;
        }

        now = head;
        for(int i = 1; i + k - 1 <= n; i += k)
        {
            reverse(&now, 1, k);
            for(int j = 1; j <= k; j++)
                now = now->next;
        }

        now = head;
        for(int i = 1; i <= n; i++)
        {
            now = now->next;
            printf("%d ", now->data);
        }
        printf("\n");

        now = head;
        now = now->next;
        for(int i = 1; i <= n; i++)
        {
            temp = now;
            now = now->next;
            free(temp);
        }
        head->next = NULL;

    }

  	return 0;
}

void reverse(Node** head, int left, int right)
{
    Node* now = *head;
    Node *previous, *tempright, *templeft, *r;
    while (left != 0 && now->next != '\0') {
        previous = now;
        now = now->next;
        left--;
        right--;
    }
    templeft = previous;
    while (right != 0 && now->next != '\0') {
        previous = now;
        now = now->next;
        right--;
    }
    tempright = now->next;  //找到左右界(開區間)
    now = templeft->next;
    previous = tempright;
    while(now!=tempright){
        r = previous;
        previous = now;
        now = now ->next;
        previous -> next = r;
    }
    templeft -> next = previous;
}
