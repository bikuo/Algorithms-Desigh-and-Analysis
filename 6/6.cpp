#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
using std::sort;
int coor[100000];
// calculating count of ports with given interval width
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
// binary search for a best interval width
void bin_search(int n, int p, int L, int R){
	int dis = R;
	while(L<=R){
		int mid=(L+R)/2;
		int calc = intervalcalc(n,p,mid);
		//too wide
		if (calc <= p){
			R = mid -1;
			dis = mid;
		}
		//too narrow
		else{
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
		memset(coor,0, city*sizeof(int));
		for(int j=0;j<city;j++)
			scanf("%d", &coor[j]);
		sort(coor,coor+city);
		bin_search(city, port, 0,coor[city-1] - coor[0]);
	}
	return 0;
}