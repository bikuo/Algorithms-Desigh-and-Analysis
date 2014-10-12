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
void mergee(vector<Box>& vec,const int start,const int mid,const int end){
	int i = start;
	int j = mid + 1;
	int curr = 0;
	int pin;
    int tag;
    int index = start;
    while(i<= mid && j<=end){
        if(vec[i].wid < vec[j].wid){
            counter += end - j + 1;
            temp[curr]=vec[i];
            curr++;
            i++;
        }
        else if(vec[i].wid == vec[j].wid){
            pin=j;// clone the value of j
            tag=i;// clone the value of i
            if(vec[i].len < vec[j].len){
                counter += end-j+1;
                temp[curr] = vec[i];
                curr++;
                i++;
            }
            else if(vec[i].len == vec[j].len){
                while (pin<= end && vec[i].len == vec[pin].len && vec[i].wid == vec[pin].wid)//find boxes with same sizes on the right
                    pin++;
                while (tag<= mid && vec[tag].len == vec[j].len && vec[tag].wid == vec[j].wid)//search for boxes with same sizes on the left
                    tag++;
                counter += (end-pin+1)*(tag-i);
                while(i<tag){
                    temp[curr] = vec[i];
                    curr++;
                    i++;
                }
            }
        }
        else if(vec[i].wid > vec[j].wid){
			temp[curr] = vec[j];
			curr++;
			j++;
			counter += (mid - i + 1)*2;
		}
	}
	while(i<=mid){
		temp[curr] = vec[i];
		curr++;
		i++;
	}
	while(j<=end){
		temp[curr] = vec[j];
		curr++;
		j++;
	}
	for(int k=0;k<curr;k++){ //put elements sorted back to original vector
		vec[index] = temp[k];
		index++;
	}
}
void mergesort(vector<Box>& vec,const int start,const int end){
	if(start == end)
		return;
	int mid  = start + (end-start)/2;
	mergesort(vec,start,mid);
	mergesort(vec,mid+1,end);
	mergee(vec,start,mid,end);
}
int main()
{
	int test;
	long long wide, leng,num;
	long long int ans;
	std::vector<Box> boxes;
	
	scanf("%d", &test);
	for (int i = 0; i < test; ++i)
	{
		scanf("%lld", &num);
		for (int j = 0; j < num; ++j)
		{
			scanf("%lld %lld", &leng , &wide);
			box.len = (leng > wide )? leng:wide;
			box.wid = (wide < leng )? wide:leng;
			boxes.push_back(box);
		}
		std::sort(boxes.begin(),boxes.end(),myfunc);
        mergesort(boxes,0,num-1);
		ans = num*(num-1)-counter;
		printf("%lld\n",ans);
		boxes.clear();
		counter = 0;
	}
	return 0;
}