#include <iostream>
#include <cstdio>
#include <cstring>
#include <bitset>
#include <vector>
#include <cassert> 
#include <boost/dynamic_bitset.hpp> 
#define dbset boost::dynamic_bitset
using std::vector;
using std::bitset;
using boost::dynamic_bitset;
vector< dynamic_bitset<> > links;
int vert,edge;
int max_click;
//template<std::size_t SIZE>
//int B_K(bitset<SIZE> P,bitset<SIZE> R,bitset<SIZE> X){}
void B_K(dbset<> P,int R, dbset<> X){
	if( P.none() && X.none() ){
		max_click = (R > max_click )? R:max_click;  
		return;
	}
	int pot;
	if(( pot = (P.count() + R)) < max_click){
		return;
	}
	dbset<> a = (P | X);
	int piv = a.find_first();
	int tmp;
	dbset<> Q = P-links[piv];
	while( Q.any() && pot > max_click){
		tmp = Q.find_first();
		if( (Q|links[tmp]).any() || (tmp == piv) )
			B_K( (P & links[tmp]),R+1, (X & links[tmp]));
		--pot;
		P.reset(tmp);
		X.set(tmp);
		Q.reset(tmp);
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
			links[i].resize(vert);
			links[i].set();
			links[i][i].flip();
		}
		for (int i = 0; i < edge; ++i){// reads in the complementary graph
			scanf("%d%d", &f, &t);
			links[f][t].flip();
			links[t][f].flip();
		}
		dbset<> p(vert), x(vert); 
		p.set();
		max_click = 0;
		B_K(p,r,x);
		printf("%d\n", max_click);
	}
	return 0;
}
