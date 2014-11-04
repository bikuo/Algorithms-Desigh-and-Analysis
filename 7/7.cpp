#include <cstdio>
#include <iostream>
using namespace std;
int main(int argc, char const *argv[]){
	int d[10] = {1,5,10,20,50,100,200,500,1000,2000};
	int v[10] = {1,5,10,20,100,100,200,1000,1000,2000};// watch out for indexes 4(100') , 7(1000')
	int test;
	scanf("%d", &test);
	for (int i = 0; i < test; ++i){
		int m,n,price;
		int count = 0;
		scanf("%d", &price);
	 	//amount of each denomination
		int cash[10];
		for(m=0;m<10;m++){
			scanf("%d", &cash[m]);
			count += cash[m];
		}
		// =========================================//
		for(m=0;m<10;m++)
			price -= (d[m]*cash[m]);
		// too pricy
		if(price > 0){
			printf("-1\n");
			continue;
		}
		// exactly 
		else if(price == 0){
			printf("%d\n",count);
			continue;
		}
		// affordable take back excessive payment using greedy 
		else{
			int res[4] ;
			int prices[4];
			int check[4]={0};
			int amount[4][10];
			price *= (-1);
			int min=99999999;
			//n=0 50 odd 500 even
			for(m=0;m<4;m++){
				res[m] = 1e9;
				for(n=0;n<10;n++)
					amount[m][n] = cash[n];
			}
			if((price >= 50) && cash[4] > 0){
				prices[0] = price - 50;
				//cout<<"prices[0] = "<<prices[0]<<"\n";
				amount[0][4] = (cash[4]-1) / 2;
				amount[0][7] = cash[7] / 2;
				res[0] = 1;
				check[0] =1;
			}
			//n=1 50 even 500 odd 
			if((price >= 500) && cash[7] > 0){
				prices[1] = price - 500;
				amount[1][4] = cash[4] / 2;
				amount[1][7] = (cash[7]-1) / 2;
				res[1] = 1;
				check[1] = 1;
			}
			//n=2 50 odd 500 odd 
			if((price >= 550) && cash[4] > 0 && cash[7] > 0){
				prices[2] = price - 550;
				amount[2][4] = (cash[4]-1) / 2;
				amount[2][7] = (cash[7]-1) / 2;
				res[2] = 2;
				check[2] = 1; 
			}
			//n=3 50 even 500 even
			prices[3] = price;
			amount[3][4] = cash[4] / 2;
			amount[3][7] = cash[7] / 2;
			res[3] = 0;
			check[3] = 1;
			for(n=0;n<4;n++){
				if(check[n]){
					for(int j = 9;j>=0;j--){				
						if(prices[n] >= v[j]){
							if(amount[n][j] >= prices[n]/v[j]){
								res[n] += (j==4 || j==7)? (2*(prices[n]/v[j])) : (prices[n]/v[j]);
								prices[n] %= v[j];
								//cout<<"res."<<j<<"="<<res[n]<<endl;
							}
							else{
								prices[n] -=  amount[n][j]*v[j];
								res[n] += (j==4 || j==7)? (2*amount[n][j]): amount[n][j];
								//cout<<"res.."<<j<<"="<<res[n]<<endl;
							}
						}
					}
					if(prices[n])
						res[n] = 1e9;
				}
				//cout<<"res"<<n<<"="<<res[n]<<endl;
			}
			for(n = 0;n<4;n++){
				if(res[n] < min)
					min = res[n];
			}
			if(prices[0] && prices[1] && prices[2] && prices[3])
				printf("woohoo\n");
			else
				printf("%d\n",count-min);
		}
	}	
	return 0;
}
