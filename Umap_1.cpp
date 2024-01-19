#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <climits>
#include <sstream>

using namespace std;
template <class K, class V>
struct key_value_pair
{
    K key;
    V val;
    key_value_pair()
    {
    }
    key_value_pair(K k, V v)
    {
        key = k;
        val = v;
    }
};
template <class K, class V>
struct node
{
    struct key_value_pair<K, V> key_val;
    node *next;
    node(struct key_value_pair<K, V> k_v)
    {
        next = NULL;
        key_val = k_v;
    }
};

template <class K, class V>
class unorderedmap
{
    int mod_key = 1690691;
    int s=0;
    vector<node<K, V> *> m;

public:
    unorderedmap()
    {
        m.resize(mod_key);
    }
    void insert(K key, V val)
    {
        int hash = gethash(key);
        node<K, V> *temp = m[hash];
        while (temp)
        {
            if (temp->key_val.key == key)
            {
                temp->key_val.val = val;
                return;
            }
            temp = temp->next;
        }
        key_value_pair<K, V> key_val(key, val);
        node<K, V> *newnode = new node(key_val);
        if (temp)
            temp->next = newnode;
        else
            m[hash] = newnode;
        s++;
    }
    void erase(K key)
    {
        int hash = gethash(key);
        node<K, V> *temp = m[hash];
        if (temp && temp->key_val.key == key)
        {
            node<K, V> *del_node = temp;
            m[hash] = temp->next;
            delete (del_node);
            s--;
            return;
        }
        while (temp && temp->next)
        {
            if (temp->next->key_val.key == key)
            {
                node<K, V> *del_node = temp->next;
                temp->next = temp->next->next;
                delete (del_node);
                s--;
                return;
            }
            temp = temp->next;
        }
    }
    bool find(K key)
    {
        node<K, V> *temp = m[gethash(key)];
        while (temp)
        {
            if (temp->key_val.key == key)
            {
                return true;
            }
        }
        return false;
    }
    V operator[](K key)
    {
        node<K, V> *temp = m[gethash(key)];
        while (temp)
        {
            if (temp->key_val.key == key)
            {
                return temp->key_val.val;
            }
            temp = temp->next;
        }
        return V();
    }
    int gethash(K key)
    {
        string hash_string;
        stringstream ss;
        ss << key;
        hash_string = ss.str();

        int l(hash_string.length());
        int length = min(l, 37);
        int hash = 0;
        for (int i = length; i >= 0; i--)
        {
            hash = (((hash + int(hash_string[i])) % mod_key) * 257) % mod_key;
        }
        return hash;
    }
    int size()
    {
        return s;
    }
};

int main(int argc, char const *argv[])
{
    /* code */
    int q;
    cin >> q;
    unorderedmap<int, int> m;
    while (q--)
    {
        int a;
        cin >> a;
        int key;
        int val;
        if (a == 1)
        {
            cin >> key >> val;
            m.insert(key, val);
        }
        else if (a == 2)
        {
            cin >> key;
            m.erase(key);
        }
        else if (a == 3)
        {
            cin >> key;
            cout << m.find(key)<<endl;
        }
        else if (a == 4)
        {
            cin >> key;
            cout << m[key]<<endl;
        }
    }
}
