#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdio> 
#include <array>
using namespace std;
using std::vector;
std::array<int ,100000>temp;
int counter = 0;

struct Box{	
	long long len,wid;
} box;

bool myfunc(Box a,Box b){
	return (a.len < b.len);
}

void mergee(vector<Box>& vv,int start,int mid,int end){
	//cout<<"mergee";
	int i = start;
	int j = mid + 1;
	int curr = 0;
	int pin;
	while(i<= mid && j<=end){
		if(vv[i].wid <= vv[j].wid){
			if(vv[i].wid < vv[j].wid){
				counter += end- j + 1;
				//cout<<"counter="<<counter<<"\n";
			}
			
			else if(vv[i].wid == vv[j].wid){
				pin=j;
				while(vv[i].wid == vv[pin].wid && pin<=end){
					if(vv[i].len < vv[pin].len)
						break;
					pin++;
				}
				/*if(vv[i].len < vv[j].len)
					counter += 1;*/
				counter += end-pin+1;
				//cout<<"counter="<<counter<<"\n";
			}
			temp[curr] = vv[i].wid;
			curr++;
			i++;
		}
		else if(vv[i].wid > vv[j].wid){
			temp[curr] = vv[j].wid;
			curr++;
			j++;
			counter += (mid - i + 1)*2;
			//cout<<"counter="<<counter<<"\n";
		}	
	}
	while(i<=mid){
		temp[curr] = vv[i].wid;
		curr++;
		i++;
	}
	while(j<=end){
		temp[curr] = vv[j].wid;
		curr++;
		j++;
	}
	for(int k=0;k<curr;k++){
		vv[start].wid = temp[k];
		start++;
	}
}

void mergesort(vector<Box>& vv,int start,int end){
	//cout<<"mergesort";
	if(start == end)
		return;
	int mid  = start + (end-start)/2;
	mergesort(vv,start,mid);
	mergesort(vv,mid+1,end);
	mergee(vv,start,mid,end);
}



int main()
{
	int test,num;
	long long ww, ll;
	long long int ans;
	std::vector<Box> vb;
	std::vector<Box>::iterator it;
	scanf("%d", &test);
	for (int i = 0; i < test; ++i)
	{
		scanf("%d", &num);
		for (int j = 0; j < num; ++j)
		{
			scanf("%lld %lld", &ll , &ww);
			box.len = (ll > ww )? ll:ww;
			box.wid = (ww < ll )? ww:ll;
			vb.push_back(box);	
			
		}
		//cout<<"boxes : "<<vb.size()<<"\n";	
		std::sort(vb.begin(),vb.end(),myfunc);
		/*for(it = vb.begin();it!=vb.end();it++)
		{
			cout<<" "<<it->len;
		}*/
		//cout<<"\n";
		mergesort(vb,0,num-1);
		//"counter" got
		//printf("counter: %d\n",counter);
		ans = num*(num-1)-counter;
		printf("%lld\n",ans);
		vb.clear();
		counter = 0;
		temp = {0};
	}
	return 0;
}