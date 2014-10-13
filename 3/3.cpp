#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;
using std::vector;
using std::sort;
struct Event{
	double left,right;
	long long int goldvol;		
};

struct Player{
	int num;
	unsigned long long int goal,curr;
	vector<int> mine_field;
};

struct Nodes{
	float loc;
	int val;
};

bool myfunc(Nodes a,Nodes b){			
	return(a.loc < b.loc);
}

Event events[100001];
int worker[100001],res[100001],crosscheck[100001];
int n,m,q;

void decision(vector<Player> &v, int left,int right){
	if (v.size() == 0)// base case
		return;
	if (left == right && left != q){ // player succeeded before the last event
		for (int i = 0; i < v.size(); ++i)
			res[v[i].num] = left;
		return;
	}
	int mid = (left+right)/2;
	Nodes tnode;
	vector<Nodes> linked;
	for(int j=left;j<=mid;j++){
		tnode.loc = events[j].left-0.5; //left bound of gold 
		tnode.val = events[j].goldvol;//volume of gained gold indicated as (+)
		linked.push_back(tnode);
		tnode.loc = events[j].right+0.5;//right bound of gold
		tnode.val = -events[j].goldvol;//volume of gained gold indicated as (-)
		linked.push_back(tnode);
	}
	tnode.val=0;
	for(int i=0;i<v.size();i++)
		for (int j = 0; j < v[i].mine_field.size(); ++j)
		{
			tnode.loc = v[i].mine_field[j];
			linked.push_back(tnode);
			crosscheck[v[i].mine_field[j]]=i;// build a crosscheck table to relate the location to indexes of players
		}
	sort(linked.begin(), linked.end(),myfunc);
	int summation = 0;
	std::vector<Player> pre = v;
	for(int k=0; k<linked.size();k++){
		if(linked[k].val == 0)// is a mine field
			v[crosscheck[(int)linked[k].loc]].curr += summation;
		else // is a indicator of range of dropping golds
			summation += linked[k].val;
	}
	if(left == right && left == q){// at the last event 
		for (int i = 0; i < v.size(); ++i){
			if (v[i].curr < v[i].goal){ // goal not yet achieved
				res[v[i].num] = -1;
			}
			else //goal achieved
				res[v[i].num] = q;
		}
		return;
	}
	std::vector<Player> win ,lose;
	
	for(int i=0;i<v.size();i++){
		if(v[i].curr < v[i].goal)
			lose.push_back(v[i]);
		else{
			v[i].curr = pre[i].curr; // restore the previous condition to make sure the very event the player wins  
			win.push_back(v[i]);
		}
	}
	decision(win,left,mid);
	decision(lose,mid+1,right);
}
int main(){
	int test;
	scanf("%d", &test);
	for (int i = 0; i < test; ++i){
		std::vector<Player> play;
		scanf("%d %d %d", &n, &m, &q);
		for (int j = 1; j <= n; ++j){
			Player p;
			long long int a;
			scanf("%llu", &a);
			p.goal=a;
			p.curr =0;
			p.num= j;
			play.push_back(p);
		}
		for (int j = 1; j <= m; ++j){
			scanf("%d", &worker[j]);
			play[worker[j]-1].mine_field.push_back(j);
		}
		for (int j = 1; j <= q; ++j){
			Event a;
			int l,r;
			long long int v;
			scanf("%d %d %lld", &l, &r, &v);
			a.left=l;
			a.right=r;
			a.goldvol=v;
			events[j] = a;
		}
		decision(play,1,q);
		for(int i=1;i<=n;i++){//print out result 
			if(i==1)
				printf("%d", res[i]);
			else
				printf(" %d", res[i]);
		}
		printf("\n");
	}
	return 0;
}