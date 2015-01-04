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
		/*if(ask[1] == -1){
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
		}*/
		int i=maxer;
		int rounds = p;
		while (rounds--){
			if(ask[i] == -1){
				int temp = (i==1)? p:i-1;
				if(intel[i] == max)
					ask[i] = i;
				else if(intel[i] == intel[temp])
					ask[i] = ask[temp];
				else if(intel[i] > intel[temp]){
					int check = ask[temp];
					while(1){
						if(intel[check] > intel[i]){
							ask[i] = check;
							//printf("whatthe i = %d\n", i);
							break;
						}
						check = ask[check];
					}
				} 
			}
			i = i+1; 
			if (i > p) i = 1;
			//printf("!! i == %d\n", i);
		}
		for (i = 1; i <= p; ++i){
			if(ask[i] == i)ask[i] = 0;
			(i==p)? printf("%d\n",ask[i]):printf("%d ",ask[i]);
		}
	
	}
	return 0;
}