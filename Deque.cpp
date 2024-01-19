#include<iostream>
using namespace std;
class Queue{

};
template<class T>
class Deque:public Queue{
    T* arr;
    int head;
    int tail;
    int count;
    int total;
public:
    Deque(){
        this->arr=new T[0];
        this->head=-1;
        this->tail=-1;
        this->count=0;
        this->total=0;
    }
    Deque(int n,T x){
        this->arr=new T[n];
        this->head=0;
        this->tail=n-1;
        this->count=n;
        this->total=n;
        for(int i=0;i<n;i++){
            arr[i]=x;
        }
    }
    int getHead(){
        return this->head;
    }
    int getTail(){
        return this->tail;
    }
    T& operator [](int );
    void push_front(T);
    void push_back(T);
    void pop_front();
    void pop_back();
    T front();
    T back();
    bool empty();
    int size();
    int capacity();
    void resize(int,T);
    void clear();
    
    ~Deque(){
		delete [] arr;
	}
};
template<class T>
void Deque<T>::push_front(T n){
    int newCapacity;
    if(this->count>=this->total){
        T* newarr;
        if(this->total==0){
            newCapacity=1;
            newarr=new T[newCapacity];
            this->head=-1;
            this->tail=-1;
        }else{
            newCapacity=2*this->total;
            newarr=new T[newCapacity];
            int i=0;
            int h=head;
            while((h%total)!=tail){
                newarr[i]=arr[h%total];
                i++;h++;
            }
            newarr[i]=arr[tail];
            this->head=0;
            this->tail=i; 
        }
        delete[] arr;
        arr=newarr;
        this->total=newCapacity;  
    }
    if(head==-1){
        head=0;
        tail=0;
    }else if(head==0){
        head=total-1;
    }else{
        head=head-1;
    }
    arr[head]=n;
    this->count++;

}

template<class T>
void Deque<T>::push_back(T n){
    int newCapacity;
    if(this->count>=this->total){
        T* newarr;
        if(this->total==0){
            newCapacity=1;
            newarr=new T[newCapacity];
            this->head=-1;
            this->tail=-1;
        }else{
            newCapacity=2*this->total;
            newarr=new T[newCapacity];
            int i=0;
            int h=head;
            while((h%total)!=tail){
                newarr[i]=arr[h%total];
                i++;h++;
            }
            newarr[i]=arr[tail];
            this->head=0;
            this->tail=i; 
        }
        delete[] arr;
        arr=newarr;
        this->total=newCapacity;
         
    }
    if(tail==-1){
        head=0;
        tail=0;
    }else{
        tail=(tail%total)+1;
    }
    arr[tail]=n;
    this->count++;
}
template<class T>
void Deque<T>::pop_front(){
    if(this->empty())
        return;
    if(this->count==this->total/2){
        int newCapacity=this->total/2;
        
        T* newarr=new T[newCapacity];
        int i=0;
        int h=head;
        while((h%total)!=tail){
            newarr[i]=arr[h%total];
            i++;h++;
        }
        newarr[i]=arr[tail];
        delete[] arr;
        arr=newarr;
        this->total=newCapacity;
        this->head=0;
        this->tail=i;  
    }
    
    if(head==tail){
        head=-1;
        tail=-1;
    }else{
        head=((head+1)%total);
    }
    count--;
}
template<class T>
void Deque<T>::pop_back(){
    if(this->empty())
        return;
    if(this->count==this->total/2){
        int newCapacity=this->total/2;
        
        T* newarr=new T[newCapacity];
        int i=0;
        int h=head;
        while((h%total)!=tail){
            newarr[i]=arr[h%total];
            i++;h++;
        }
        newarr[i]=arr[tail];
        delete[] arr;
        arr=newarr;
        this->total=newCapacity;
        this->head=0;
        this->tail=i;   
    }
    
    if(head==tail){
        head=-1;
        tail=-1;
    }else if(tail==0){
        tail=total-1;
    }else{
        tail--;
    }
    count--;
}
template<class T>
T Deque<T>::front(){
    if(this->empty())
        return T();
    return this->arr[head];
}
template<class T>
T Deque<T>::back(){
    if(this->empty())
        return T();
    return this->arr[tail];
}
template<class T>
bool Deque<T>::empty(){
    return this->count==0;
}
template<class T>
int Deque<T>::size(){
    return this->count;
}
template<class T>
int Deque<T>::capacity(){
    return this->total;
}
template<typename T>
T& Deque<T>::operator [](int index){
	return this->arr[(head+index)%total];
}
template<class T>
void Deque<T>::resize(int n,T d){
    T* newarr=new T[n];
    int h=head;
    for(int i=0;i<n;i++){
        if(i>this->count){
            newarr[i]=d;
        }else{
            newarr[i]=arr[h%total];
            h++;
        }
    }
    this->head=0;
    this->tail=n-1;
    this->count=n;
    this->total=n;
    delete[] arr;
    arr=newarr;
}
template<class T>
void Deque<T>::clear(){
    T* newarr=new T[0];
    delete[] arr;
    this->arr=newarr;
        this->head=-1;
        this->tail=-1;
        this->count=0;
        this->total=0;
}
template<class T>
std::ostream& operator << (std::ostream& sout,Deque<T>& dq){
    if(dq.size()>0){
	sout<<"[";
	for(int i=0;i<dq.size()-1;i++){
        sout<<dq[i]<<",";
        
    }
    sout<<dq[dq.size()-1];
	sout<<"]";
    }else{
        sout<<"[ ]";
    }
	return sout;
}
void print_menu(){
    Deque<int>* dq=NULL;
    while(true){
        cout << "\n1.Deque()\n2.Deque(n,x)\n3.push_back(x)\n4.pop_back()\n5.push_front(x)\n6.pop_front()\n7.front()\n8.back()\n9.D[n]\n10.empty()\n11.size()\n12.resize(x, d)\n13 clear()\n0.Exit\nEnter choice: ";
        int k;
        cin>>k;
        if(k==1){
            dq=new Deque<int>();
        }else if(k==2){
            cout<<"Enter n:";
            int n,x;
            cin>>n;
            cout<<"Enter x:";
            cin>>x;
            dq=new Deque<int>(n,x);
        }else if(k==3){
            if(dq==NULL)
                cout<<"INITIALISE DEQUE.\n";
            else{
                int x;
                cin>>x;
                dq->push_back(x);
                cout<<*dq<<"\n";
            }
        }else if(k==4){
            if(dq==NULL)
                cout<<"INITIALISE DEQUE.\n";
            else{
                dq->pop_back();
                cout<<*dq<<"\n";
            }
        }else if(k==5){
            if(dq==NULL)
                cout<<"INITIALISE DEQUE.\n";
            else{
                int x;
                cin>>x;
                dq->push_front(x);
                cout<<*dq<<"\n";
            }
        }else if(k==6){
            if(dq==NULL)
                cout<<"INITIALISE DEQUE.\n";
            else{
                dq->pop_front();
                cout<<*dq<<"\n";
            }
        }else if(k==7){
            if(dq==NULL)
                cout<<"INITIALISE DEQUE.\n";
            else{
                cout<<dq->front();
                
            }
        }else if(k==8){
            if(dq==NULL)
                cout<<"INITIALISE DEQUE.\n";
            else{
                cout<<dq->back();
            }
        }else if(k==9){
            if(dq==NULL)
                cout<<"INITIALISE DEQUE.\n";
            else{
                int x;
                cout<<"Enter index:";
                cin>>x;
                cout<<dq[x];

            }
        }
        else if(k==10){
            if(dq==NULL)
                cout<<"INITIALISE DEQUE.\n";
            else{
                dq->empty();
            }
        }
        else if(k==11){
            if(dq==NULL)
                cout<<"INITIALISE DEQUE.\n";
            else{
                cout<<dq->size();
            }
        }else if(k==12){
            if(dq==NULL)
                cout<<"INITIALISE DEQUE.\n";
            else{
                cout<<"Enter new Size";
                int x,d;
                cin>>x;
                cout<<"Enter pad";
                cin>>d;
                dq->resize(x,d);
                cout<<*dq<<"\n";
                
            }
        }else if(k==13){
            if(dq==NULL)
                cout<<"INITIALISE DEQUE.\n";
            else{
               dq->clear();
            }
        }else if(k==0){
            delete dq;
            cout<<"Exiting....\n";
            break;
        }else{
            cout<<"Wrong Choice";
        }
    }
    
    
}
int main()
{
    /* code */
    print_menu();
    
    return 0;
}
