#include <iostream>
#include <set>
#include <vector>
using namespace std;

struct node {
    node() {
        lucky = new set<int>;
    }
    set<int> *lucky;
};

int n_node, tmp, a, b;
int *record;
vector<int> *ch;
vector<int> *edge;
vector<node*> tree;

void DFS(int now, int pa)
{
    for(int i : edge[now])
    {
        if(i == pa)
            continue;
        ch[now].emplace_back(i);
        DFS(i, now);
    }

    for(int i : ch[now])
    {
        if ( tree[i]->lucky->size() > tree[now]->lucky->size() )
        {
            tree[i]->lucky->insert(tree[now]->lucky->begin(), tree[now]->lucky->end());
            tree[now]->lucky = tree[i]->lucky;
        }
        else
            tree[now]->lucky->insert(tree[i]->lucky->begin(), tree[i]->lucky->end());

    }

    record[now] = tree[now]->lucky->size();

    return;
}


int main()
{
    cin >> n_node;
    edge = new vector<int>[n_node + 1];
    ch = new vector<int>[n_node + 1];
    record = new int[n_node + 1];

    node *headEmptyNode = new node;
    tree.emplace_back(headEmptyNode);
    for(int i = 1; i <= n_node; i++)
    {
        node *newNode = new node;
        cin >> tmp;
        newNode->lucky->insert(tmp);
        tree.emplace_back(newNode);
    }

    for(int i = 1; i < n_node; i++)
    {
        cin >> a >> b;
        edge[a].emplace_back(b);
        edge[b].emplace_back(a);
    }

    DFS(1, 0);

    for(int i = 1; i <= n_node; i++)
        cout << record[i] << " ";

    cout << "\n";
}
