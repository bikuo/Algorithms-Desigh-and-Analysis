#include <cstdio>
#include <vector>
#include <cstring>
#include <stack>       
#include <iostream> 
using std::stack;
using std::vector;
typedef struct path {
	int end;
	int weight;	
}PATH;
int node,edge;
const int twos[31]={1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072,262144,524288,1048576,2097152,4194304,8388608,16777216,33554432,67108864,134217728,268435456,536870912,1073741824};
std::vector< vector<PATH> > v;
stack<int> steak;
int search(int bits,int sum){
	if(bits == 0)
		return 0;
	int vertex = 1;
	int pathcount[node+1];
	bool pushed[node+1];
	memset(pathcount,0,sizeof(pathcount));
	memset(pushed,0,sizeof(pushed));
	steak.push(1);
	pushed[1] = 1;
	while(!steak.empty()){
		int cur = steak.top();		
		if(pathcount[cur] < v[cur].size() ){
			if( ((v[cur][pathcount[cur]].weight >> (bits-1) ) | (sum >> (bits-1)) )  ==  (sum >> (bits-1)) ){
				if( (!pushed[v[cur][pathcount[cur]].end]) && (cur !=v[cur][pathcount[cur]].end) ){
					steak.push(v[cur][pathcount[cur]].end);
					vertex++;
					pushed[v[cur][pathcount[cur]].end] = true;
				}	
			}
			pathcount[cur]++;
		}
		else
			steak.pop();
	}
	if(vertex < node) // fail
		return ( twos[bits-1] + search(bits-1, sum + twos[bits-1]));
	else	// okay
		return search(bits-1, sum);
}
int main(int argc, char const *argv[]){
	PATH tmp;
	int t,end1,end2,wt;
	int max,count;
	scanf("%d",&t);
	while(t--){
		scanf("%d%d", &node, &edge);
		v.resize(node+1);
		count = 0;
		max = 0;
		for(int i = 0;i<edge;i++){
			scanf("%d %d %d", &end1, &end2, &wt);
			tmp.weight = wt;
			tmp.end = end1;
			v[end2].push_back(tmp);
			tmp.end = end2;
			v[end1].push_back(tmp);
			if(end1 != end2)
				max = (wt > max)? wt:max;
		}
		// the max weight of all paths has "count" digits
		while(max > 0){
			max >>= 1;
			count++;  
		}
	printf("%d\n",search(count,0)); // (bits, initial cost=0)
	for(int i = 0;i<=node;i++)
		v[i].clear();
	}
	return 0;
}