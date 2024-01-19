#include <iostream>
#include <string>

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
    int n, m;
    char **v;
    Trie()
    {
        this->root = new Node;
    }
    Trie(int n, int m)
    {
        this->n = n;
        this->m = m;
        this->root = new Node;
        v = new char *[n];
        for (int i = 0; i < n; i++)
        {
            v[i] = new char[m];
        }
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
    void search()
    {
        bool **visited = new bool *[n];
        for (int i = 0; i < n; i++)
        {
            visited[i] = new bool[m];
        }
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                visited[i][j] = false;
            }
        }
        Trie *t = new Trie;
        int count = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                find_word(root, visited, i, j, "", t, &count);
            }
        }
        string str[count];
        int cnt = 0;
        t->print_trie(t->root, "", str, &cnt);
        cout << cnt << endl;
        for (int i = 0; i < cnt; i++)
        {
            cout << str[i] << '\n';
        }
    }
    void print_trie(Node *root, string s, string *str, int *count)
    {
        if (root->end)
        {
            str[*count] = s;
            *count = *count + 1;
        }

        for (int i = 0; i < 26; i++)
        {
            if (root->next[i])
            {
                char ch = 'a' + i;
                print_trie(root->next[i], s + ch, str, count);
            }
        }
    }
    void find_word(Node *temp, bool **visited, int i, int j, string s, Trie *t, int *count)
    {
        if (i < 0 || j < 0 || i > n - 1 || j > m - 1 || visited[i][j])
        {
            return;
        }

        if (temp->next[v[i][j] - 'a'])
        {

            s.push_back(v[i][j]);
            if (temp->next[v[i][j] - 'a']->end)
            {
                t->insert(s);
                *count = *count + 1;
            }
            visited[i][j] = true;
            find_word(temp->next[v[i][j] - 'a'], visited, i + 1, j, s, t, count);
            find_word(temp->next[v[i][j] - 'a'], visited, i, j + 1, s, t, count);
            find_word(temp->next[v[i][j] - 'a'], visited, i - 1, j, s, t, count);
            find_word(temp->next[v[i][j] - 'a'], visited, i, j - 1, s, t, count);
            s.pop_back();
            visited[i][j] = false;
        }
    }
};

int main(int argc, char const *argv[])
{

    int n, m;
    cin >> n >> m;

    Trie t(n, m);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> t.v[i][j];
        }
    }
    int k;
    cin >> k;
    for (int i = 0; i < k; i++)
    {
        string s;
        cin >> s;
        t.insert(s);
    }
    t.search();
    return 0;
}
