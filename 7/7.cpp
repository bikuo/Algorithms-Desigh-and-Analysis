#include <cstdio>
#include <iostream>
using namespace std;
int main(int argc, char const *argv[]){
	int d[10] = {1,5,10,20,50,100,200,500,1000,2000};
	int test;
	scanf("%d", &test);
	for (int i = 0; i < test; ++i){
		int price,m;
		bool affordable = false;
		scanf("%d", &price);
	 	//get amount for each denomination
		int cash[10];
		for(m=0;m<10;m++)
			scanf("%d", &cash[m]);
	 	//missing one dollars
		if(cash[0] < (price % 10)){
			printf("-1\n");
			continue;
		}

		for(m=0;m<10;m++){
			price -= (d[m]*cash[m]);
			if(price < 0){
				affordable = !affordable;
				break;
			}
		}
		// too pricy
		if(affordable == false){
			printf("-1\n");
			continue;
		}
		price *= (-1);
		int res=0;
		for(int j = m;j>=0;j--){
			//price -= (price/d[j])*d[j];
			cash[j] -= price/d[j];
			price %= d[j];
			/*for(int n=0;n<10;n++)
				cout<<cash[n]<<" ";*/
			cout<<endl;
			res += cash[j];
		}
		if(price != 0)
			printf("WTF\n");
		else
			printf("%d\n", res);
	}	
	return 0;
}
