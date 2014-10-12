#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdio> 
using namespace std;
using std::vector;
long long int counter = 0;
struct Box{
	long long len,wid;
} box;
bool myfunc(Box a,Box b){
    if (a.len == b.len)
        return (a.wid < b.wid);
    else
        return (a.len < b.len);
}
std::vector<Box>::iterator it;
vector<Box> temp(100000);
void mergee(vector<Box>& vv,const int start,const int mid,const int end){
	int i = start;
	int j = mid + 1;
	int curr = 0;
	int pin;
    int tag;
    int index = start;
        while(i<= mid && j<=end){
            if(vv[i].wid < vv[j].wid){
				counter += end - j + 1;
                temp[curr]=vv[i];
                curr++;
                i++;
			}
			else if(vv[i].wid == vv[j].wid){
                pin=j;
                tag=i;
                if(vv[i].len < vv[j].len){
                    counter += end-j+1;
                    temp[curr] = vv[i];
                    curr++;
                    i++;
                }
                else if(vv[i].len == vv[j].len){
                    while (pin<= end && vv[i].len == vv[pin].len && vv[i].wid == vv[pin].wid){
                        pin++;
                    }
                    while (tag<= mid && vv[tag].len == vv[j].len && vv[tag].wid == vv[j].wid){
                        tag++;
                    }
                    counter += (end-pin+1)*(tag-i);
                    while(i<tag){
                        temp[curr] = vv[i];
                        curr++;
                        i++;
                    }
                    
                }
            }
            else if(vv[i].wid > vv[j].wid){
			temp[curr] = vv[j];
			curr++;
			j++;
			counter += (mid - i + 1)*2;
		}
	}
	while(i<=mid){
		temp[curr] = vv[i];
		curr++;
		i++;
	}
	while(j<=end){
		temp[curr] = vv[j];
		curr++;
		j++;
	}
	for(int k=0;k<curr;k++){
		vv[index] = temp[k];
		index++;
	}
}
void mergesort(vector<Box>& vv,const int start,const int end){
	if(start == end)
		return;
	int mid  = start + (end-start)/2;
	mergesort(vv,start,mid);
	mergesort(vv,mid+1,end);
	mergee(vv,start,mid,end);
}
int main()
{
	int test;
	long long wide, leng,num;
	long long int ans;
	std::vector<Box> vb;
	
	scanf("%d", &test);
	for (int i = 0; i < test; ++i)
	{
		scanf("%lld", &num);
		for (int j = 0; j < num; ++j)
		{
			scanf("%lld %lld", &leng , &wide);
			box.len = (leng > wide )? leng:wide;
			box.wid = (wide < leng )? wide:leng;
			vb.push_back(box);
		}
		std::sort(vb.begin(),vb.end(),myfunc);
        mergesort(vb,0,num-1);
		ans = num*(num-1)-counter;
		printf("%lld\n",ans);
		vb.clear();
		counter = 0;
	}
	return 0;
}