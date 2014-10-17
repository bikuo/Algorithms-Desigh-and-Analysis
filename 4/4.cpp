#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

void reverse(char str[]){
    int i,j;
    char temp[2020];
    for(i=strlen(str)-1,j=0; i+1!=0; --i,++j)
    {
        temp[j]=str[i];
    }
    temp[j]='\0';
    strcpy(str,temp);
}

void lcs(char* a, char* b){
	int m = strlen(a);
	int n = strlen(b);
	int M[m+1][n+1];
	char D[m+1][n+1];
	char I[m+1][n+1];
	for (int i=0; i<=m; i++)
    	for (int j=0; j<=n; j++){
       		//initializing steps on border of maps
       		if (i == 0 || j == 0){
         		M[i][j] = 0;
         		D[i][j] = '.';
         		I[i][j] = '.';
         	}
  			//doing real work 
       		else{
       			// two stings matches
       			if (a[i-1] == b[j-1]){
         			M[i][j] = M[i-1][j-1] + 1;
         			D[i][j] = '\\';
         			I[i][j] = a[i-1];
       			}
       			else if(a[i-1] != b[j-1]){
         			if(M[i-1][j] > M[i][j-1]){
         				M[i][j] = M[i-1][j];
         				D[i][j] = '^';
         				I[i][j] = I[i-1][j];
         			}
         			else if(M[i-1][j] < M[i][j-1]){
         				M[i][j] = M[i][j-1];
         				D[i][j] = '<';
         				I[i][j] = I[i][j-1];
         			}
         			else if(M[i-1][j] == M[i][j-1]){
         				if(I[i-1][j] > I[i][j-1]){
         					M[i][j] = M[i][j-1];
         					D[i][j] = '<';
         					I[i][j] = I[i][j-1];
         				}
         				else{
         					M[i][j] = M[i-1][j];
         					D[i][j] = '^';
         					I[i][j] = I[i-1][j];
         				}
         			}
       			}
         	
         	}
     	}
	// printf out the map constructed above to check for correctness 
	/*for(int i= 0;i<=m;i++){
		for(int j=0;j <= n;j++){
			printf("%d ", M[i][j]);
		}
	cout<<"\n";
	}
	cout<<"\n";
	for(int i= 0;i<=m;i++){
		for(int j=0;j <= n;j++){
			printf("%c ", D[i][j]);
		}
	cout<<"\n";
	}
	cout<<"\n";
	for(int i= 0;i<=m;i++){
		for(int j=0;j <= n;j++){
			printf("%c ", I[i][j]);
		}
	cout<<"\n";
	}
	cout<<"\n";*/
	//==================================
	int index = M[m][n];
	char lcs1[index+1];
	lcs1[index] = '\0';
	int i=m,j=n;
	//tracing back to get lcs
	while(i>0 && j>0){
		//cout<<i<<";"<<j<<endl;
		if(D[i][j] == '\\'){
			lcs1[index-1] = I[i][j];
			i--;
			j--;
			index--;
		}
		else if(M[i-1][j] > M[i][j-1])
			i--;
		else if(M[i-1][j] < M[i][j-1])
			j--;
		else if(M[i-1][j] == M[i][j-1]){
			if(I[i-1][j] == I[i][j])
				i--;
			else if(I[i][j-1] ==  I[i][j])
				j--;
			else if(I[i][j] == I[i][j-1] && I[i][j] == I[i-1][j])
				i--;
			else if(I[i][j] != I[i][j-1] && I[i][j] != I[i-1][j]){
				if(I[i-1][j] > I[i][j-1])
					j--;
				else
					i--;
			}
		}
			
	}
	//cout<<lcs1<<endl;
	reverse(lcs1);
	printf("%s", lcs1);
	return;
}	
int main(int argc, char const *argv[])
{
	int n;
	char str1[2020],str2[2020];
	scanf("%d", &n);
	for (int i = 0; i < n; ++i)
	{
		scanf("%s", str1);
		scanf("%s", str2);
		reverse(str1);
		//cout<<str1<<endl;
		reverse(str2);
		//cout<<str2<<endl;
		lcs(str1,str2);
		printf("\n");
	}
	return 0;
}