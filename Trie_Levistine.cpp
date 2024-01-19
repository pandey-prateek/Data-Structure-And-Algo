#include <iostream>
#include <string>
#include <vector>
using namespace std;
struct Node
{
    Node *next[26] = {NULL};
    bool end = false;
};
class Trie
{
    Node *root = NULL;

public:
    Trie()
    {
        this->root = new Node;
    }
    void insert(string s)
    {
        Node *temp = root;
        for (int i = 0; i < s.length(); i++)
        {
            if (!temp->next[s[i] - 'a'])
            {
                temp->next[s[i] - 'a'] = new Node();
            }
            temp = temp->next[s[i] - 'a'];
        }
        temp->end = true;
    }
    Node *find_end(string s)
    {
        Node *temp = root;
        for (int i = 0; i < s.length(); i++)
        {
            if (!temp->next[s[i] - 'a'])
            {
                return NULL;
            }
            temp = temp->next[s[i] - 'a'];
        }
        return temp;
    }
    bool search(string s)
    {
        Node *temp = find_end(s);
        if (temp)
            return temp->end;
        return false;
    }
    vector<string> autocomplete(string s)
    {
        Node *temp = find_end(s);
        vector<string> v;
        if (temp)
            find_rest(temp, v, s);
        return v;
    }
    void find_rest(Node *temp, vector<string> &v, string s)
    {
        if (temp->end)
        {
            v.push_back(s);
        }
        for (int i = 0; i < 26; i++)
        {
            if (temp->next[i])
            {
                char ch = 'a' + i;
                find_rest(temp->next[i], v, s + ch);
            }
        }
    }
    vector<string> autocorrect(string incorrect)
    {
        vector<string> v;
        autocorrect(root, v, "", incorrect);
        return v;
    }
    void autocorrect(Node *temp, vector<string> &v, string s, string incorrect)
    {
        if (temp->end)
        {
            if (get_levistien_dist(s, incorrect) <= 3)
            {
                v.push_back(s);
            }
        }
        for (int i = 0; i < 26; i++)
        {
            if (temp->next[i])
            {
                char ch = 'a' + i;
                autocorrect(temp->next[i], v, s + ch, incorrect);
            }
        }
    }
    int get_levistien_dist(string a, string b)
    {
        int dp[a.length() + 1][b.length() + 1];
        for (int i = 0; i <= a.length(); i++)
        {
            dp[i][0] = i;
        }
        for (int i = 0; i <= b.length(); i++)
        {

            dp[0][i] = i;
        }
        for (int i = 1; i <= a.length(); i++)
        {
            for (int j = 1; j <= b.length(); j++)
            {
                 if (a[i - 1] == b[j - 1])
                {   dp[i][j] = dp[i-1][j-1];
                }else{
                    dp[i][j] = 1+min(dp[i - 1][j - 1], min(dp[i - 1][j], dp[i][j - 1]));
                }
            }
        }
        return dp[a.length()][b.length()];
    }
};
int main(int argc, char const *argv[])
{
    int n, q;
    cin >> n>> q;;
    Trie t;
    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s;
        t.insert(s);
    }
    for (int i = 0; i < q; i++)
    {
        int choice;
        cin >> choice;
        if (choice == 1)
        {
            string s;
            cin >> s;
            cout << t.search(s) << endl;
        }
        else if (choice == 2)
        {
            string s;
            cin >> s;
            vector<string> v=t.autocomplete(s);
            cout<<v.size()<<'\n';
            for(auto i:v){
                cout<<i<<'\n';
            }
        }
        else if (choice == 3)
        {
            string s;
            cin >> s;
            vector<string> v=t.autocorrect(s);
            cout<<v.size()<<'\n';
            for(auto i:v){
                cout<<i<<'\n';
            }
        }
    }

    return 0;
}
