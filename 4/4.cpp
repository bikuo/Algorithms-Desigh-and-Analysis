#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

void lcs(char* a, char* b){
	int m = strlen(a);
	int n = strlen(b);
	//printf("length: %d %d", m,n);
	//printf("\n");
	int M[m+1][n+1];
	for (int i = 0; i <= m; ++i)
	{
		for (int j = 0; j <= n; ++j)
		{
			if(i==0 || j==0)
				M[i][j] = 0;
			else if(a[i-1] == b[j-1])
				M[i][j] = M[i-1][j-1] + 1;
			else
				M[i][j] = max(M[i-1][j], M[i][j-1]);
		}
	}
	// printf out the map constructed above to check for correctness 
	/*for(int i= 0;i<=m;i++){
		for(int j=0;j <= n;j++){
			printf("%d ", M[i][j]);
		}
	cout<<"\n";
	}
	cout<<"\n";*/
	int index = M[m][n];
	if (index ==0)
		printf("\n");
	else{
	char lcs1[index+1];
	lcs1[index] = '\0';
	int i=m,j=n;
	while(i>0 && j>0){
		if(a[i-1] == b[j-1]){
			lcs1[index-1] = a[i-1];
			i--;
			j--;
			index--;
		}
		else if(M[i-1][j] > M[i][j-1])
			i--;
		else 
			j--;
	}
	printf("%s", lcs1);}
	/*int L[m+1][n+1];
	for (int i = 0; i <= m; ++i)
		L[i][n] = 0;
	
	for (int j = 0; j <= n; ++j)
		L[m][j] = 0;
	
	for(int i= m-1;i>=0;i--)
		for(int j = n-1;j>=0;j--){
			L[i][j] = L[i+1][j+1];
			if(a[i] == b[j]) 
				L[i][j]++;
			if(L[i][j+1] > L[i][j]) 
				L[i][j] = L[i][j+1];
			if(L[i+1][j] > L[i][j]) 
				L[i][j] = L[i+1][j];
			}
		
	/*for(int i= 0;i<=m;i++){
		for(int j=0;j <= n;j++){
			printf("%d ", L[i][j]);
		}
		cout<<"\n";
	}
	if(L[0][0] == 0)
		printf("\n");
	else{
		int i=0,j =0;
		int length = L[0][0];
		int index = 0;
		char lcs[length+1];
		lcs[length] = '\0';
		while(i<m && j<n){
			if(a[i] == b[j]){
				lcs[index] = a[i];
				i++;
				j++;
				index++;
			}
			else if(L[i+1][j] > L[i][j+1])
				i++;
			else if(L[i][j+1] > L[i+1][j+1])
				j++;
			else if(L[i+1][j] == L[i][j+1])
				j++;
			
		
		}
	printf("%s\n",lcs);
	}*/
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
		//cout<<"ready for function\n";
		
			lcs(str1,str2);
		printf("\n");
	}
	return 0;
}