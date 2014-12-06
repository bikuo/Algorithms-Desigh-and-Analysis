#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
using std::queue;
typedef struct cell{
	char type = {'#'};
	int dist = -1;
	int drink = 0;
}CELL;
typedef struct coor{
	int x,y,z;
}COOR;
void check(int ,int ,int ,int ,int, CELL [][102][102] );
queue<COOR> que;
int main(int argc, char const *argv[]){
	int t,size;
	scanf("%d", &t);
	int curr_dist,curr_drink;;
	int corrx,corry,corrz;
	while(t--){
		scanf("%d", &size);
		COOR start,end;
		CELL grid[size+2][100+2][100+2];
		for(int i = 1; i <= size; ++i)
			for(int j = 1; j<= size; ++j)
				for(int k = 1; k<= size; k++){
					scanf(" %c", &grid[i][j][k].type);
					if(grid[i][j][k].type == 'S'){
						grid[i][j][k].dist = 0;
						start.x = i;
						start.y = j;
						start.z = k;
						que.push(start);
					}
					else if(grid[i][j][k].type == 'E'){
						end.x = i;
						end.y = j;
						end.z = k;
					}
				}
		while(!que.empty()){
			COOR top = que.front();
			corrx = top.x;
			corry = top.y;
			corrz = top.z;
			curr_dist = grid[corrx][corry][corrz].dist;
			curr_drink = grid[corrx][corry][corrz].drink;
			check(corrx+1,corry,corrz,curr_dist, curr_drink, grid);
			check(corrx-1,corry,corrz,curr_dist, curr_drink, grid);	
			check(corrx,corry+1,corrz,curr_dist, curr_drink, grid);
			check(corrx,corry-1,corrz,curr_dist, curr_drink, grid);	
			check(corrx,corry,corrz+1,curr_dist, curr_drink, grid);
			check(corrx,corry,corrz-1,curr_dist, curr_drink, grid);		
			que.pop();
		}
		(grid[end.x][end.y][end.z].dist == -1)? printf("Fail OAQ\n") : printf("%d %d\n", grid[end.x][end.y][end.z].dist, grid[end.x][end.y][end.z].drink);
	}
	return 0;
}
void check(int i,int j,int k,int dis,int bottle, CELL grid[][102][102] ){
	if(grid[i][j][k].dist == -1 && grid[i][j][k].type != '#'){
		COOR tmp;
		tmp.x = i;
		tmp.y = j;
		tmp.z = k;
		que.push(tmp);
		grid[i][j][k].dist = dis+1;
		grid[i][j][k].drink = (grid[i][j][k].type == 'B')? bottle+1 : bottle;
	}
	else if(grid[i][j][k].dist == dis + 1){
		if(grid[i][j][k].type == 'B')
			grid[i][j][k].drink = (bottle+1 > grid[i][j][k].drink)? bottle+1 : grid[i][j][k].drink;
		else
			grid[i][j][k].drink = (bottle > grid[i][j][k].drink)? bottle : grid[i][j][k].drink;
	}
	return;
}