#include <cstdio>
#include <cstring>
int main(int argc, char const *argv[]){
	int t,p;
	scanf("%d", &t);
	while(t--){
		scanf("%d", &p);
		int intel[p+1],ask[p+1],max=-1;
		memset(intel,0,sizeof(intel));
		memset(ask,-1,sizeof(ask));
		for (int i = 1; i <= p; ++i){
			scanf("%d", &intel[i]);
			if(intel[i] > max)
				max = intel[i];
			if(i > 1 && intel[i] < intel[i-1])
				ask[i] = i-1;
		}
		if(ask[1] == -1){
			if(intel[1] == max)
				ask[1] = 0;
			else{
				int check = p;
				while(1){
					if(intel[check] > intel[1]){
						ask[1] = check;
						break;
					}
					--check;
				}
			}
		}
		for (int i = 2; i <= p; ++i){
			if(ask[i] == -1){
				if(intel[i] == max)
					ask[i] = 0;
				else if(intel[i] == intel[i-1])
					ask[i] = ask[i-1];
				else if(intel[i] > intel[i-1]){
					int check = ask[i-1];
					while(1){
						if(intel[check] > intel[i]){
							ask[i] = check;
							break;
						}
						check = ask[check];
					}
				}
			}
		}
		for (int i = 1; i <= p; ++i)
			(i==p)? printf("%d\n",ask[i]):printf("%d ",ask[i]);
	}
	return 0;
}