#include<bits/stdc++.h>
using namespace std;

int loc_mutex=1,full=0,empty=5,x=0;  

int P(int s)
{    
    s--;
	return s;
}

int V(int s)
{
	s++;
	return s;
}

void producer()
{
	loc_mutex=P(loc_mutex);
	full=V(full);
	empty=P(empty);
	x++;
	printf("\nItem number %d produced by Producer",x);
	loc_mutex=V(loc_mutex);
}

void consumer()
{
	loc_mutex=P(loc_mutex);
	full=P(full);
	empty=V(empty);
	printf("\nItem number %d consumed by Consumer",x);
	x--;
	loc_mutex=V(loc_mutex);
}

signed main()
{
	int n;
	printf("Key:\n1.Producer\n2.Consumer\n3.Exit");
	while(1)
	{
		printf("\nEnter your choice:");
		scanf("%d",&n);
		switch(n)
		{
			case 1:	if((loc_mutex==1)&&(empty!=0))
						producer();
					else
						printf("Buffer is full.");
					break;
			case 2:	if((loc_mutex==1)&&(full!=0))
						consumer();
					else
						printf("Buffer is empty.");
					break;
			case 3:
					exit(0);
					break;
		}
	}

	return 0;
}
