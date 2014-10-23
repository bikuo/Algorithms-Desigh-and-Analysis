#include <iostream>
#include <cstdio>
using namespace std;
char map[15][15];
int modder=1000000007;
void tetris(char map[15][15],int row,int col){
	int count = 1<<col;
	int mat[row+1][col+1][count];
	// initialize matrix with all zero 
	for(int i=0;i<=row;i++)
		for(int j=0;j<=col;j++)
			for(int k=0;k<count;k++)
				mat[i][j][k] = 0;
	mat[1][0][count-1] = 1;
	// two variables for later use
	int a=(1<<(col-1))+(1<<(col-2));
	int b=1<<(col-1);
	int des;
	for (int i = 1; i <= row; ++i){
		for(int j=0;j <col; j++){
			for(int k=0;k<count;k++){
					if(i > 1 && j==0)
						mat[i][j][k] = mat[i-1][col][k];
					if(((k>>(col-1)) & 1) ==1){// 1*1 block or a natural obstacle
						des = 2*(k-b)+1;
              			mat[i][j+1][des] += mat[i][j][k];
              			mat[i][j+1][des] %= modder;
					}
      				// not an obstacle
					if(map[i][j] != 'X'){
			  			if(((k>>(col-1)) & 1) ==1){ // leave a blank
          					des = (k-b)*2;
            				mat[i][j+1][des] += mat[i][j][k];
            				mat[i][j+1][des] %= modder;
						}
						if(((k>>(col-1)) % 2)==0){ // 2*1 vertical 
				  			des = 2*k+1;
				    		mat[i][j+1][des] += mat[i][j][k];
				    		mat[i][j+1][des] %= modder;
						}
						// cases with wider blocks 
						if(j < col-1 && map[i][j+1] !='X'){
						 	if(((k>>(col-2)) & 3) == 3){ // 1*2 horizontal 
				  			des = 4*(k-a)+3;
				  			mat[i][j+2][des] += mat[i][j][k];
				  			mat[i][j+2][des] %= modder;
							}
							if(((k>>(col-2)) % 2) == 0 && ((k>>(col-1)) % 2 == 0)){ // 2*2 square
							des = 4*k+3;
							mat[i][j+2][des] += mat[i][j][k];
							mat[i][j+2][des] %= modder;
						}
					}
				}
			}		
		}
	}
	printf("%d",mat[row][col][count-1]);
}
int main(){
	int test;
	scanf("%d", &test);
	for (int i = 0; i < test; ++i){
		int row,col;
		scanf("%d %d", &row, &col);
		for (int r = 1; r <= row; ++r){
			char str[20];
			scanf("%s", str);
			for(int c = 0;c < col; c++)
					map[r][c] = str[c];
		}
		tetris(map,row,col);
		printf("\n");
	}
	return 0;
}