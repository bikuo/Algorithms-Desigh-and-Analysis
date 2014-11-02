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
	 	//amount for each denomination
		int cash[10];
		for(m=0;m<10;m++)
			scanf("%d", &cash[m]);
		if(price == 0){
			printf("1\n");
			continue;
		}
		// =================================
		// algorithm starts here
		for(m=0;m<10;m++){
			price -= (d[m]*cash[m]);
		}
		
		// too pricy
		if(price > 0){
			printf("-1\n");
			continue;
		}
		// affordable,take back excessive payment using greedy 
		else{
			price *= (-1);
			int res=0;
			for(int j = 9;j>=0;j--){
				if(price >= d[j]){
					//price -= (price/d[j])*d[j];
					if(cash[j] >= price/d[j]){
						cash[j] -= price/d[j];
						price %= d[j];
					}
					else{
						price -= cash[j]*d[j];
						cash[j] = 0;
					}
					// for(int n=0;n<10;n++)
					// 	cout<<cash[n]<<" ";
					// cout<<endl;
				}
				res += cash[j];
			}
			/*if(price > 0)
				printf("-1\n");
			else*/
				printf("%d\n", res);
		}
	}	
	return 0;
}
