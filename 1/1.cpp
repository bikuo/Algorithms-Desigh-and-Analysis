#include <stdio.h>
int main(int argc, char const *argv[])
{
	long long int a,b;
	int t;
	scanf("%d", &t);
	for (int i = 0; i < t; ++i)
	{		
		scanf("%lld %lld", &a, &b);
		printf("%lld\n", a+b);
		
	}
	return 0;
}