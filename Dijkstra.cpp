#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
using namespace std;
struct index_pair
{
    long long first;
    long long second;
    index_pair()
    {
    }
    index_pair(long long int f, long long int s)
    {
        this->first = f;
        this->second = s;
    }
};
class Heap
{

public:
    vector<index_pair> arr;
    int n = 0;
    int size;
    Heap(int size)
    {
        this->size = size;
        arr.resize(size);
    }
    void insert_value(long long int first, long long int second)
    {
        index_pair p(first, second);
        n++;
        int i = n - 1;
        arr[i] = p;

        while (i != 0 && arr[parent(i)].first > arr[i].first)
        {
            swap(arr[parent(i)], arr[i]);
            i = parent(i);
        }
    }
    index_pair get_min_adjust()
    {
        index_pair p = arr[0];
        swap(arr[0], arr[n - 1]);
        n--;
        heapify(0);
        return p;
    }
    void heapify(int i)
    {
        int l = left(i);
        int r = right(i);
        int smallest = i;
        if (l < n && arr[l].first < arr[i].first)
            smallest = l;
        if (r < n && arr[r].first < arr[smallest].first)
            smallest = r;
        if (smallest == i)
            return;
        swap(arr[smallest], arr[i]);
        heapify(smallest);
    }
    void buildHeap(vector<index_pair> &arr, int n)
    {
        for (int i = n / 2; i >= 0; i--)
        {
            heapify(i);
        }
    }

    int parent(int i)
    {
        return (i - 1) / 2;
    }
    int right(int i)
    {
        return 2 * i + 2;
    }
    int left(int i)
    {
        return 2 * i + 1;
    }
    bool isEmpty()
    {
        if (n)
            return false;
        return true;
    }
};
void dijkstra(int V, vector<vector<index_pair>> graph, int S,vector<int>& distance)
{
    vector<bool> visited(V, false);
    distance[S] = 0;
    Heap h(V);
    h.insert_value(distance[S],S);
    while (!h.isEmpty())
    {
        index_pair ind = h.get_min_adjust();
        for (int i = 0; i < graph[ind.second].size(); i++)
        {
            if (distance[graph[ind.second][i].first] > distance[ind.second] + graph[ind.second][i].second)
            {
                h.insert_value(distance[ind.second] + graph[ind.second][i].second, graph[ind.second][i].first);
                distance[graph[ind.second][i].first] = distance[ind.second] + graph[ind.second][i].second;
            }
        }
    }
}
int main(int argc, char const *argv[])
{
    int N, M, K;
    cin >> N >> M >> K;
    vector<vector<index_pair>> graph(N + 1);
    for (int i = 0; i < M; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        index_pair index_i(v, w);
        index_pair index_j(u, w);
        graph[u].push_back(index_i);
        graph[v].push_back(index_j);
    }
    vector<int> distance(N+1, INT_MAX);
    for (int i = 0; i <K;i++){
        int k;
        cin>>k;
        dijkstra(N,graph,k,distance);
    }
    cout<<endl;
    for (int i = 1; i <=N;i++){
        if(distance[i]==INT_MAX)
            distance[i]=-1;
        cout<<distance[i]<<" ";
    }
    cout<<endl;
    return 0;
}
