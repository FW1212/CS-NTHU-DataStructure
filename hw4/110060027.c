#include <stdio.h>

int adj[1000][1000];
int n, e, s, f, k, u, v, w, min = 2147483647;

void DFS(int now, int cur, int total)
{

    if(adj[now][s] && total + adj[now][s] < min)
        min = total + adj[now][s];

    if(cur < k)
    {
        for(int i = 0; i <= n; i++)
        {
            if(adj[now][i] && i != s && total + adj[now][i] < min)
                DFS(i, cur + 1, total + adj[now][i]);
        }
    }

    return;
}

int main()
{
    scanf("%d %d", &n, &e);
    scanf("%d %d %d", &s, &f, &k);

    while(e--)
    {
        scanf("%d %d %d", &u, &v, &w);
        adj[v][u] = w;
    }

    DFS(f, 0, 0);

    printf("%d\n", min);

    return 0;
}
