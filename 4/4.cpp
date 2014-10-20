#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;
// function to reverse the order of a given string reference from the NET
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
       		//initializing steps on border(when indices i or j equals zero) 
       		//of 3maps M(max length), D(direction for backtracing), 
       		//I(initial character of current lcs)
       		if (i == 0 || j == 0){
         		M[i][j] = 0;
         		D[i][j] = '.';
         		I[i][j] = '.';
         	}
  			//doing real work 
       		else{
       			// two stings matches at a<i-1> b<j-1>
       			if (a[i-1] == b[j-1]){
         			M[i][j] = M[i-1][j-1] + 1;
         			D[i][j] = '\\';
         			I[i][j] = a[i-1];
       			}
       			//does not match, we compare first the maximum length (choose the longer one)
       			// then the lexicograghical order (the preceeding one) of entries adjacent
       			// to the current entry either (i-1) or (j-1)
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
         					D[i][j] = '<'
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
	int index = M[m][n];//length of lcs
	char lcs1[index+1];
	lcs1[index] = '\0';
	int i=m,j=n;
	//tracing back and get lcs
	while(i>0 && j>0){
		if(D[i][j] == '\\')
		{//if a<i-1> and b<j-1> is a character of lcs, add that character to result string
			lcs1[index-1] = I[i][j];
			i--;
			j--;
			index--;
		}
		else
		{ //if not, check if the initial character of the current
			if(I[i][j] == a[i-1])
				j--;
			else if(I[i][j] == b[j-1])
				i--;
			else if(I[i][j] != a[i-1] && I[i][j] != b[j-1])
				i--;
		}
			
	}
	reverse(lcs1);
	printf("%s\n", lcs1);
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
		reverse(str2);
		lcs(str1,str2);
	}
	return 0;
}