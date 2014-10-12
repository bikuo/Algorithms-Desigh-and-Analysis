#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;
using std::vector;

struct Event{
	double left,right;
	long long int goldvol;		
};

struct Player{
	long long int goal,curr,succ=-1,status=-1;
};

struct Mine
{
	long long int belongs_to;
	long long int goldnum;

};

int main()
{
	int test;
	int n,m,q;
	std::vector<Mine> blocks;
	std::vector<Player> play;
	std::vector<Event> events;
	int count=0;
	scanf("%d", &test);
	for (int i = 0; i < test; ++i)
	{
		scanf("%d %d %d", &n, &m, &q);
		for (int j = 1; j <= n; ++j){
			Player p;
			int a;
			scanf("%d", &a);
			p.goal=a;
			play.push_back(p);
		}
		for (int j = 1; j <= m; ++j){
			Mine mine;
			int num;
			scanf("%d", &num);
			mine.belongs_to = num;
			blocks.push_back(mine);
		}
		for (int j = 1; j <= q; ++j){
			Event a;
			int l,r,v;
			scanf("%d %d %d", &l, &r, &v);
			a.left=l;
			a.right=r;
			a.goldvol=v;
			events.push_back(a);
		}
		for(vector<Event>::iterator it=events.begin();it!=events.end();it++){
			count++;
			for(int i=it->left;i<=it->right;i++){
				play[(blocks[i-1].belongs_to)-1].curr += it->goldvol;
			}
			for(std::vector<Player>::iterator point=play.begin();point != play.end();point ++){
				if(point->curr >= point->goal && point->status < 0){
					point->status =1;
					point->succ=count;
				}

			}

		}
		for(std::vector<Player>::iterator it=play.begin();it!=play.end();it++){
			if(it++ ==  play.end())
				printf("%lld", it->succ);
			else
				printf("%lld ",it->succ);

		}
		printf("\n");
		blocks.clear();
		events.clear();
		play.clear();
		count = 0;

	}
	return 0;
}