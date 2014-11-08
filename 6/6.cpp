#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
using std::sort;
int coor[100000];

int intervalcalc(int n,int p,int width){
	int switchy=0,count =0,start = 0;
	for(int i=0;i<n;i++){
		if(coor[i]-coor[start] > width){
			if(switchy == 0){
				start  = i - 1;
				switchy = 1;
				i--;
			}
			else if(switchy == 1){
				start = i;
				count ++;
				switchy = 0;
			}
		}
		if ( coor[i]-coor[start] <= width &&  (coor[n-1] - coor[start]) <= width){
			count++;
			break;
		}
	}
	return count;
}
void bin_search(int n, int p, int L, int R){
	int dis = R;
	while(L<=R){
		int mid=(L+R)/2;
		//cout<<"#width:"<<mid<<"\n";
		int calc = intervalcalc(n,p,mid);
		//cout<<"calc"<<calc<<"\n";
		if (calc <= p){
			R = mid -1;
			dis = mid;
			//cout<<"dis:"<<dis<<"\n";
		}
		else{
			//cout<<"too narrow\n";
			L = mid + 1;
		}
	}
	printf("%d\n", dis);
}
int main(int argc, char const *argv[]){
	int tst;
	scanf("%d", &tst);
	for (int i = 0; i < tst; ++i){
		int city,port;
		scanf("%d %d", &city, &port);
		memset(coor,0,sizeof(coor));
		for(int j=0;j<city;j++)
			scanf("%d", &coor[j]);
		sort(coor,coor+city);
		bin_search(city, port, 0,coor[city-1] - coor[0]);
	}
	return 0;
}