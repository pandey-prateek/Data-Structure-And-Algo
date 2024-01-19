#include <iostream>
#include <cmath>
using namespace std;
struct values
{
    long long first;
    long long second;
    values(){
        
    }
    values(long long f,int s){
        this->first=f;
        this->second=s;
    }
};
class Heap
{
    
public:
    values *arr=new values[1];
    int n=0;
    int size = 1;
    void insert_value(values v)
    {
        if (size == n)
        {
            int newCapacity = 2 * size;
            values *newarr = new values[newCapacity];
            for (int i = 0; i < n; i++)
            {
                newarr[i] = arr[i];
            }
            delete[] arr;
            arr=newarr;
            size=newCapacity;
        }

        n++;
        int i = n - 1;
        arr[i] = v;

        while (i != 0 && arr[parent(i)].first < arr[i].first)
        {
            swap(arr[parent(i)], arr[i]);
            i = parent(i);
        }
    }
    void delete_value()
    {
            arr[0];
            swap(arr[0], arr[n - 1]);
            n--;
            heapify(0);
    }
    void heapify(int i)
    {
        int l = left(i);
        int r = right(i);
        int largest = i;
        if (l < n && arr[l].first > arr[i].first)
            largest = l;
        if (r < n && arr[r].first > arr[largest].first)
            largest = r;
        if (largest == i)
            return;
        swap(arr[largest], arr[i]);
        heapify(largest);
    }
    static void heapify(int *arr, int n, int i)
    {
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        int largest = i;
        if (l < n && arr[l] > arr[i])
            largest = l;
        if (r < n && arr[r] > arr[largest])
            largest = r;
        if (largest == i)
            return;
        swap(arr[largest], arr[i]);
        heapify(arr, n, largest);
    }
    void buildHeap(values *arr, int n)
    {
        for (int i = n/2; i >= 0; i--)
        {
            heapify(i);
        }
    }
    static void buildHeap(int *arr, int n)
    {
        for (int i = n/2; i >= 0; i--)
        {
            heapify(arr, n, i);
        }
    }
    void heapSort()
    {
        buildHeap(arr, n);
        int k = n;
        values ret[n];
        for (int i = 0; i < n; i++)
        {
            ret[i] = arr[0];
            swap(arr[0], arr[k - 1]);
            k--;
            heapify(0);
        }
        arr = ret;
    }
   
    static void heapSort(int *arr, int n)
    {
        buildHeap(arr, n);
        int k = n;
        
        for (int i = 0; i < n; i++)
        {
            
            swap(arr[0], arr[k - 1]);
            k--;
            heapify(arr, k, 0);
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
};
int main(int argc, char const *argv[])
{
    int n, k;
    cin >> n >> k;
    long long max_sum = 0;
    int a[n];
    long long ans[k];
    int abs_value[n];
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        abs_value[i] = abs(a[i]);
        if (a[i] > 0)
        {
            max_sum += a[i];
        }
    }
    Heap::heapSort(abs_value,n);
    int i=1;
    ans[0]=max_sum;
    Heap h;
    values v;   
    v.first=max_sum-abs_value[0];
    v.second=0;
    h.insert_value(v);
    
    while(i<k){
        
        values v=h.arr[0];
        h.delete_value();
        ans[i++]=v.first;
        if(v.second+1<n){
            values v1(v.first+abs_value[v.second]-abs_value[v.second+1],v.second+1);
            h.insert_value(v1);
            values v2(v.first-abs_value[v.second+1],v.second+1);
            h.insert_value(v2);
        }

    }
    for(int i=0;i<k;i++){
        cout<<ans[i]<<" ";
    }
    cout<<endl;
    return 0;
}
