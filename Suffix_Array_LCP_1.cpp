#include<iostream>
#include<algorithm>
#include<string>
#include<climits>
#include<vector>

using namespace std;

struct indexs
{
    long long int first;
    long long int second;
};
struct entry
{
    indexs indx;
    long long int position;
};

struct suffix_array_rank
{
    vector<entry> entries;
    vector<long long int> ranks;
};
bool cmp(struct entry a, struct entry b)
{
    if (a.indx.first == b.indx.first)
        return a.indx.second < b.indx.second;
    return a.indx.first < b.indx.first;
}

suffix_array_rank build_suffix_array(string s){
	long long int N=s.length();
	vector<entry> entries(N);
	vector<long long int> temp(N);
	
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
    struct suffix_array_rank sfr;
	sfr.entries=entries;
    sfr.ranks=temp;
    return sfr;
} 

vector<long long int> find_LCP(suffix_array_rank sfr,string s){
    vector<entry> entries=sfr.entries;
    vector<long long int> ranks=sfr.ranks;
    vector<long long int> lcp(entries.size(),0);
    long long int prev=0;    
    for(int i=0;i<entries.size();i++){
        if(ranks[i]==entries.size()-1){
            prev=0;
            continue;
        }
        int next_pos=entries[ranks[i]+1].position;
        while(i+prev<entries.size() && next_pos+prev<entries.size()&&s[i+prev]==s[next_pos+prev]){
            prev++;
        }
        lcp[ranks[i]]=prev;
        if(prev>0){
            prev--;
        }
    }
    return lcp;
}
int main(int argc, char const *argv[])
{
	string s;
    int k;
	cin>>s;
	cin>>k;
	suffix_array_rank sfr=build_suffix_array(s);
    vector<long long int> lcp = find_LCP(sfr,s);
    
    long long int max_size=INT_MIN;
    for(int i=0;i<=lcp.size()-k+1;i++){
        long long int min_size=INT_MAX;
        for(int j=0;j<k-1;j++){
            min_size=min(lcp[i+j],min_size);
        }
        max_size=max(max_size,min_size);
    }
    cout<<max_size<<endl;
	return 0;
}
