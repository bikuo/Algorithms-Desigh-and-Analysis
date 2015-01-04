#include <cstdio>
#include <cstring>
int main(int argc, char const *argv[]){
	int t,p;
	scanf("%d", &t);
	while(t--){
		scanf("%d", &p);
		int intel[p+1],ask[p+1],max=-1,maxer;
		memset(intel,0,sizeof(intel));
		memset(ask,-1,sizeof(ask));
		for (int i = 1; i <= p; ++i){
			scanf("%d", &intel[i]);
			if(intel[i] > max){
				max = intel[i];
				maxer = i;
			}
			if(i > 1 && intel[i] < intel[i-1])
				ask[i] = i-1;
		}
		if(intel[1] < intel[p])
			ask[1] = p;
		int i=maxer;
		int rounds = p;
		while (rounds--){
			if(ask[i] == -1){
				int temp = (i==1)? p:i-1;
				if(intel[i] == max)
					ask[i] = 0;
				else if(intel[i] == intel[temp])
					ask[i] = ask[temp];
				else if(intel[i] > intel[temp]){
					int check = ask[temp];
					while(1){
						if(intel[check] > intel[i]){
							ask[i] = check;
							break;
						}
						check = ask[check];
					}
				} 
			}
			i = (i == p)? 1:i+1;
		}
		for (i = 1; i <= p; ++i){
			(i==p)? printf("%d\n",ask[i]):printf("%d ",ask[i]);
		}
	}
	return 0;
}