#include <cstdio>
#include <vector>
#include <stack>
#include <iostream> 
using std::stack;
using std::vector;
typedef struct path 
{
	int end;
	int weight;	
}PATH;
int node,edge;
const int twos[31]={1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,
				131072,262144,524288,1048576,2097152,4194304,8388608,16777216,33554432
					,67108864,134217728,268435456,536870912,1073741824};
std::vector< vector<PATH> > v;
stack<int> steak;
int search(int bits,int sum){
	int vertex = 1;
	int pathcount[10001]={0};
	short pushed[10001] = {0};
	steak.push(1);
	pushed[1] = 1;
	if(bits == 0)
		return 0;
	while(!steak.empty()){
		int cur = steak.top();
		if(pathcount[cur] < v[cur].size() ){
			if( ((v[cur][pathcount[cur]].weight >> (bits-1) ) |  sum >> (bits-1)) ==  (sum >> (bits-1)) ){
				if( ! pushed[v[cur][pathcount[cur]].end] ){
					steak.push(v[cur][pathcount[cur]].end);
					vertex++;
					pushed[cur] = 1;
				}	
			}
			pathcount[cur]++;
		}
		else
			steak.pop();
	}
	if(vertex != node)// unsuccess
		return (twos[bits-1] + search(bits-1, sum + twos[bits-1]));
	else				// success
		return search(bits-1, sum);
}
int main(int argc, char const *argv[])
{
	PATH tmp;
	int t,end1,end2,wt;
	int max=0,count;
	scanf("%d",&t);
	while(t--){
		scanf("%d%d", &node, &edge);
		count = 0;
		v.resize(node+1);
		for(int i = 0;i<edge;i++){
			scanf("%d %d %d", &end1, &end2, &wt);
			tmp.weight = wt;
			tmp.end = end1;
			v[end2].push_back(tmp);
			tmp.end = end2;
			v[end1].push_back(tmp);
			max = (wt > max)? wt:max;
		}
		while(max > 0){
			max >>= 1;
			count++;
		}
	printf("%d\n",search(count,0)); // (bits, initial cost=0)
	//v.clear();
	v.resize(0);
	}
	return 0;
}