#include<iostream>
#include<algorithm>
#include<string>
#include<vector>

using namespace std;

struct indexs
{
    int first;
    int second;
};
struct entry
{
    indexs indx;
    int position;
};
bool cmp(struct entry a, struct entry b)
{
    if (a.indx.first == b.indx.first)
        return a.indx.second < b.indx.second;
    return a.indx.first < b.indx.first;
}

vector<int> build_suffix_array(string s){
	int N=s.length();
	vector<entry> entries(N);
	vector<int> temp(N);
	
	for(int i=0;i<N;i++){
		temp[i]= s[i]-'a';
	}
	int step=0;
	for(int i=1;(i>>1)<=N;i=i<<1){
		for(int j=0;j<N;j++){
			entries[j].indx.first=temp[j];
			if(i+j<N){
				entries[j].indx.second=temp[i+j];
			}else{
				entries[j].indx.second=-1;
			}
			entries[j].position=j;
		}
		sort(entries.begin(),entries.end(),cmp);
		for(int j=0;j<N;j++){
			if(j!=0&&entries[j].indx.first==entries[j-1].indx.first&&entries[j].indx.second==entries[j-1].indx.second){
				temp[entries[j].position]=temp[entries[j-1].position];
			}else{
				temp[entries[j].position]=j;
			}
		}
	}
	return temp;
} 
int main(int argc, char const *argv[])
{
	string s;
	cin>>s;
	string new_str =s+s;
	
	vector<int> ranks=build_suffix_array(new_str);
	int min_rank=new_str.length()-1;
	int min_index=0;

    for (int i = 0; i < s.length(); i++)
    {
        if(ranks[i]< min_rank){
			min_rank=ranks[i];
			min_index=i;
		}
    }
	cout<<new_str.substr(min_index,s.length())<<endl;
	
	return 0;
}
