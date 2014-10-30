#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
char map[16][16];
int modder=1000000007;
int pow_2[17] = { 1,2,4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536 };
void tetris(int row,int col){
	int count = pow_2[col];
	// initialize matrix with all zero 
	static int mat[16][16][32768];
	//int mat[row+1][col+1][count];
	memset(mat,0,sizeof(mat));
	mat[1][0][count-1] = 1;
	// two variables for later use
	int a=pow_2[col-1]+pow_2[col-2];
	int b=pow_2[col-1];
	int des;
	for (int i = 1; i <= row; ++i){
		for(int j=0;j <col; j++){
			for(int k=0;k<count;k++){
					if(i > 1 && j==0)
						mat[i][j][k] = mat[i-1][col][k];
					// 1*1 block or a natural obstacle
					if(((k>>(col-1)) & 1) ==1){
						des = 2*(k-b)+1;
              			mat[i][j+1][des] += mat[i][j][k];
              			if(mat[i][j+1][des] >= modder)
              				mat[i][j+1][des] -= modder;
					}
      				// not an obstacle
					if(map[i][j] != 'X'){
			  			if(((k>>(col-1)) & 1) ==1){ // leave a blank
          					des = (k-b)*2;
            				mat[i][j+1][des] += mat[i][j][k];
            				if(mat[i][j+1][des] >= modder)
            					mat[i][j+1][des] -= modder;
						}
						if(((k>>(col-1)) % 2)==0){ // 2*1 vertical 
				  			des = 2*k+1;
				    		mat[i][j+1][des] += mat[i][j][k];
				    		if(mat[i][j+1][des] >= modder)
				    			mat[i][j+1][des] -= modder;
						}
						// cases with wider blocks 
						if(j < col-1 && map[i][j+1] !='X'){
						 	if((k>>(col-2)) == 3){ // 1*2 horizontal 
				  				des = 4*(k-a)+3;
				  				mat[i][j+2][des] += mat[i][j][k];
				  				if(mat[i][j+2][des] >= modder)
				  					mat[i][j+2][des] -= modder;
							}
							if(((k>>(col-2)) == 0)){ // 2*2 square
								des = 4*k+3;
								mat[i][j+2][des] += mat[i][j][k];
								if(mat[i][j+2][des] >= modder)
									mat[i][j+2][des] -= modder;
							}
						}
					}
				}
			}
		}
	printf("%d",mat[row][col][count-1]);
}
int main(){
	int test,row,col;
	char str[20];
	scanf("%d", &test);
	for (int i = 0; i < test; ++i){
		scanf("%d %d", &row, &col);
		for (int r = 1; r <= row; ++r){
			scanf("%s", str);
			for(int c = 0;c < col; c++)
					map[r][c] = str[c];
		}
		tetris(row,col);
		printf("\n");
	}
	return 0;
}