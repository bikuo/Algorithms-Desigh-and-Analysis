#include <iostream>
#include <cstdio>
#include <bitset>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>
#include <list> 
using namespace std;
using std::pair; 
using std::size_t;
using std::vector;
using std::bitset;
using std::string;
using std::sort;
using std::list;
int vert,edge;
int max_click;
int recur=0;
vector<string> links(100);
pair<int,int> deg[100];
list<int> List[100];
void B_K(bitset<100> P,int R, bitset<100> X){
	if( P.none() ){
		if(X.none())
			max_click = (R > max_click )? R:max_click;  
		return;
	}
	int pot;
	if(( pot = (P.count() + R)) < max_click){
		return;
	}	
	int piv=0;
	//while(!(P|X).test(piv))
	//	++piv;
	int tmp=0;
	bitset<100> pivset(links[piv]);
	bitset<100> Q = P&(~pivset);
	while( pot > max_click && Q.any()){
		//while(!Q.test(tmp))
		//	++tmp;
		bitset<100> tmpset(links[tmp]);
		bitset<100> check = (Q&tmpset);
		P.reset(tmp);
		X.set(tmp);
		Q.reset(tmp);
		if( (tmp == piv) || (Q&tmpset).any())
			B_K( (P & tmpset),R+1, (X & tmpset));
		--pot;
	}
	return;
}
int main(int argc, char const *argv[])
{
	int tst;
	scanf("%d", &tst);
	while(tst--){
		vert=0,edge=0;
		scanf("%d%d", &vert, &edge);
		links.resize(vert);
		int f,t,r=0;
		for (int i = 0; i < vert; ++i){
			links[i].replace(0,1,100,'1');
			links[i].replace(0,(100-vert),(100-vert),'0');
			links[i][99-i] = '0';
			deg[i].first = 0;
			deg[i].second = i; 
		}
		for(int i=0;i<edge;i++){
			scanf("%d%d", &f, &t);
			++deg[f].first;
			++deg[t].first;
			List[f].push_back(t);
			List[t].push_back(f);
		}
		sort(deg,deg+vert);
		int rebuild[vert];
		for (int i = 0; i < vert; ++i)
			rebuild[deg[i].second] = i;
		for (int i = 0; i < vert; ++i){
			int j = deg[i].second;
			while(List[j].size()){
				links[i][ 99 - rebuild[List[j].front()]] = '0';
				List[j].pop_front(); 
			}
		}
		string  p(vert,'1'), x(vert,'0'); 
		bitset<100>P(p),X(x);
		max_click = 0;
		B_K(P,r,X);
		printf("%d\n", max_click);
		recur = 0;
		links.clear();
	}
	return 0;
}
