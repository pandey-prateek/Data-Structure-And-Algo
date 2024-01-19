#include <iostream>
#include <algorithm>
#include <string>
#include <climits>
#include <vector>

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

suffix_array_rank build_suffix_array(string s)
{
    long long int N = s.length();
    vector<entry> entries(N);
    vector<long long int> temp(N);

    for (int i = 0; i < N; i++)
    {
        temp[i] = s[i] - 'a';
    }
    int step = 0;
    for (int i = 1; (i >> 1) <= N; i = i << 1)
    {
        for (int j = 0; j < N; j++)
        {
            entries[j].indx.first = temp[j];
            if (i + j < N)
            {
                entries[j].indx.second = temp[i + j];
            }
            else
            {
                entries[j].indx.second = -1;
            }
            entries[j].position = j;
        }
        sort(entries.begin(), entries.end(), cmp);
        for (int j = 0; j < N; j++)
        {
            if (j != 0 && entries[j].indx.first == entries[j - 1].indx.first && entries[j].indx.second == entries[j - 1].indx.second)
            {
                temp[entries[j].position] = temp[entries[j - 1].position];
            }
            else
            {
                temp[entries[j].position] = j;
            }
        }
    }
    struct suffix_array_rank sfr;
    sfr.entries = entries;
    sfr.ranks = temp;
    return sfr;
}

string find_LCP(suffix_array_rank sfr, string s, long long int dilimiter)
{
    vector<entry> entries = sfr.entries;
    vector<long long int> ranks = sfr.ranks;
    long long int prev = 0;
    long long int max_l = INT_MIN;
    string ret;
    for (int i = 0; i < entries.size(); i++)
    {
        if (ranks[i] == entries.size() - 1)
        {
            prev = 0;
            continue;
        }
        int next_pos = entries[ranks[i] + 1].position;
        while (i + prev < entries.size() && next_pos + prev < entries.size() && s[i + prev] == s[next_pos + prev] && !((i + prev < dilimiter && next_pos + prev < dilimiter) || (i + prev > dilimiter && next_pos + prev > dilimiter)))
        {
            prev++;
        }
        if (prev > max_l)
        {
            string n = s.substr(i, prev);
            string ss = n;
            reverse(ss.begin(), ss.end());
            if (n == ss)
            {
                max_l = prev;
                ret = n;
            }
        }
        if (prev > 0)
        {
            prev--;
        }
    }
    return ret;
}
int main(int argc, char const *argv[])
{
    string s;
    int k;
    cin >> s;
    string ss = s;
    reverse(ss.begin(), ss.end());
    suffix_array_rank sfr = build_suffix_array(s + "$" + ss);
    cout << find_LCP(sfr, s + "$" + ss, s.length()) << endl;

    return 0;
}
