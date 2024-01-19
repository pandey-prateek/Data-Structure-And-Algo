#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <ctime>
#define file_size 1000000
using namespace std;
struct Node
{
    long long int val;
    int i;
    int j;
     Node()
    {
    }
    Node(long long int val, int i, int j)
    {
        this->val = val;
        this->i = i;
        this->j = j;
    }
};

class Heap
{

public:
    vector<Node> arr;
    int n = 0;
    int size;
    Heap(int size)
    {
        this->size = size;
        arr.resize(size);
    }
    void insert_value(long long int val, int index)
    {
        Node node(val, index, n);
        n++;
        int i = n - 1;
        arr[i] = node;

        while (i != 0 && arr[parent(i)].val > arr[i].val)
        {
            swap(arr[parent(i)], arr[i]);
            i = parent(i);
        }
    }
    Node get_min_adjust()
    {
        Node v = arr[0];
        swap(arr[0], arr[n - 1]);
        n--;
        heapify(0);
        return v;
    }
    void heapify(int i)
    {
        int l = left(i);
        int r = right(i);
        int smallest = i;
        if (l < n && arr[l].val < arr[i].val)
            smallest = l;
        if (r < n && arr[r].val < arr[smallest].val)
            smallest = r;
        if (smallest == i)
            return;
        swap(arr[smallest], arr[i]);
        heapify(smallest);
    }
    void buildHeap(vector<Node> &arr, int n)
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

int main(int argc, char const *argv[])
{   time_t start, end;
    time(&start);
    ifstream f(argv[1]);
    ofstream fout(argv[2]);
    long long int s;
    int count = 0;
    int k = 0;
    vector<long long int> file_int(file_size);

    while (f >> s)
    {

        if (count < file_size-1)
        {
            file_int[count++] = s;
        }
        else
        {   file_int[count++] = s;
            ofstream of("sorted_" + to_string(k) + ".txt");
            sort(file_int.begin(), file_int.end());
            for (int i = 0; i < count; i++)
            {
                of << file_int[i] << " ";
            }
            cout<<"sorted_"<<to_string(k)<<".txt"<<" File Size-"<<count<<endl;
            count = 0;
            //file_int.clear();
            //file_int.resize(file_size,0);
            of.close();
            k++;
        }
    }

    if (count!=0)
    {
        ofstream of("sorted_" + to_string(k) + ".txt");
        sort(file_int.begin(), file_int.end());
        for (int i = 0; i < count; i++)
        {
            of << file_int[i] << " ";
        }
        file_int.clear();
        cout<<"sorted_"<<to_string(k)<<".txt"<<" File Size-"<<count<<endl;
        count = 0;
        k++;
        of.close();
    }
    cout<<"No. of files created:"<<k<<endl;
    Heap h(k);
    ifstream files[k];
    
    for (int i = 0; i < k; i++)
    {   files[i].open("sorted_" + to_string(i) + ".txt");
        long long int val;
        files[i]>>val;
        h.insert_value(val,i);
        
    }

    while (!h.isEmpty())
    {   
        long long int next_val;
        Node node = h.get_min_adjust();
        fout << node.val << "\n";
        if (files[node.i] >> next_val)
        {
            h.insert_value(next_val, node.i);
        }else{
            files[node.i].close();
        }
        
    }
    fout.close();
    ifstream fi("output.txt");
    time(&end);
        double time_taken = double(end - start);
    cout << "Code runtime is : " << fixed
         << time_taken << setprecision(5);
    cout << " sec " << endl;

    return 0;
}
