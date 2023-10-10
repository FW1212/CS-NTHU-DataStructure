#include <iostream>
using namespace std;

void merge(int *,int, int , int );
void merge_sort(int *arr, int low, int high)
{
    int mid;
    if (low < high){
        //divide the array at mid and sort independently using merge sort
        mid=(low+high)/2;
        merge_sort(arr,low,mid);
        merge_sort(arr,mid+1,high);
        //merge or conquer sorted arrays
        merge(arr,low,high,mid);
    }
}
// Merge sort
void merge(int *arr, int low, int high, int mid)
{
    int i, j, k, c[1000000];
    i = low;
    k = low;
    j = mid + 1;
    while (i <= mid && j <= high) {
        if (arr[i] < arr[j]) {
            c[k] = arr[i];
            k++;
            i++;
        }
        else  {
            c[k] = arr[j];
            k++;
            j++;
        }
    }
    while (i <= mid) {
        c[k] = arr[i];
        k++;
        i++;
    }
    while (j <= high) {
        c[k] = arr[j];
        k++;
        j++;
    }
    for (i = low; i < k; i++)  {
        arr[i] = c[i];
    }
}

int abs(int x)
{
    if(x >= 0)
        return x;
    return -x;
}

int main()
{
    int n_order, len;
    long long int ans = 0;
    cin >> n_order >> len;

    int st[n_order] = {0};
    int ed[n_order] = {0};

    for(int i = 0; i < n_order; i++)
    {
        cin >> st[i] >> ed[i];
        ans += abs(st[i] - ed[i]);
    }

    int pos = 0;
    merge_sort(st, 0, n_order-1);
    merge_sort(ed, 0, n_order-1);

    for(int i = 0; i < n_order; i++)
    {
        ans += abs(pos - st[i]);
        pos = ed[i];
    }
    ans += abs(len - pos);

    cout << ans << endl;
}
