#include <iostream>
using namespace std;

int price[5000000];
int out[5000000];

int main()
{
  	int lenght = 0;
  	int now;

  	while( cin >> price[++lenght] );
  	lenght--;

  	for(int i = 1; i <= lenght; i++)
    {
      	now = i - 1;
      	while(price[i] <= price[now] && now > 0)
        {
          	out[i] += out[now];
          	now -= out[now];
        }
        out[i]++;

    	cout << out[i] << ' ';

    }
  	cout << endl;

  	return 0;
}
