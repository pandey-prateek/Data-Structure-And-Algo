#include<iostream>
#include<string>
using namespace std;
template <class T> class Node{
    
    
    public:
    T val;
    Node* next;
    Node(T s){
        this->val=s;
        this->next=NULL;
    }
    
};
template <class T> class Stack{
    Node<T>* tos=NULL;
    public:
        void push(T val){
            Node<T>* temp=new Node(val);
            if(tos==NULL){
                tos=temp;
            }else{
                temp->next=tos;
                tos=temp;  
            }  
        }
        void pop(){
            if(tos==NULL)
                return;
            Node<T>* temp=tos;
            tos=tos->next;
            temp->next=NULL;
            delete temp;
        }
        T top(){
            if(tos!=NULL)
                return tos->val;

        }
        bool isEmpty(){
            if(tos==NULL)
                return true;
            return false;
        }
};

int check_get_priority(char symbol){
    if(symbol=='X'||symbol=='x')
        return 2;
    else if(symbol=='+'||symbol=='-')
        return 1;
    else
        return 0;
    
}
class BigInteger{
    string s;
public:
    //static BigInteger ZERO("0");

    BigInteger(string val){
        this->s=val;
    }
    BigInteger(){
    }
    BigInteger add(BigInteger num2);
    BigInteger subtract(BigInteger num2);
    BigInteger cross(BigInteger num2);
    BigInteger mod(BigInteger num2);
    static BigInteger gcd(BigInteger b1,BigInteger b2){
        BigInteger k=b1;
        k.mod(b2);
        BigInteger zero("0");
        if(BigInteger::compare(zero,k)==0){
            return b2;
        }
        return BigInteger::gcd(b2,k);

    }
    BigInteger get_quotent(BigInteger a,BigInteger b){
        if(BigInteger::compare(b,a)>0)
            return b;
        BigInteger t;
        BigInteger z=b;
        while(BigInteger::compare(b,a)<=0){
            t=b;
            b.add(z);
        }
        return t;
    }
    static string remove_leading_zeros(string r){
        int j=0;
        while(r[j]=='0')
             j++;
              
        if(j==r.length())
            return "0";
        else
            return r.substr(j,r.length()-j);
        }


    static BigInteger exp(BigInteger base,unsigned long long int exp){
        if(exp==0){
            BigInteger b1("1");
            return b1;
        }
        if(exp%2==0){
            BigInteger b=BigInteger::exp(base,exp/2);
            return b.cross(b);
        }else{
            return BigInteger::exp(base,exp-1).cross(base);
        }
    };
    
    static BigInteger fact(BigInteger num1){
        long long int a=stoll(num1.get_val());
        BigInteger n1("1");
        for(long long int i=2;i<=a;i++){
            BigInteger x(to_string(i));
            n1.cross(x);
        }
        return n1;
    }
    static int compare(BigInteger num1,BigInteger num2){
        string a=remove_leading_zeros(num1.get_val());
        string b=remove_leading_zeros(num2.get_val());
        if(a.length()>b.length()){
            return 1;
        }else if(a.length()<b.length()){
            return -1;
        }
        for(int i=0;i<a.length();i++){
            int n1=a[i]-'0';
            int n2=b[i]-'0';
            if(n1>n2){
                return 1;
            }else if(n1<n2){
                return -1;
            }
        }
        return 0;
    }
    string get_val() const{
        return this->s;
    }
    void set_val(string s){
        this->s=s;
    }

};
BigInteger BigInteger::add(BigInteger s1){
        //add
        string min="0",max="0";
        string a=this->get_val();
        string b=s1.get_val();
        int lena=a.length();
        int lenb=b.length();
        
        if(lena>lenb){
            max.append(a);
            min.append(lena-lenb,'0');
            min.append(b);
        }else {
            max.append(b);
            min.append(lenb-lena,'0');
            min.append(a);
        }
        string r(min.length(),'0');
        
        int c=0, k=0,j=0;
        for(int i=min.length()-1;i>=0;i--){
            c=(k+j+c)/10;
            k=min[i]-'0';
            j=max[i]-'0';
            r[i]=(k+c+j)%10+'0';
        }
        r=BigInteger::remove_leading_zeros(r);
        this->set_val(r);
        return *this;
}

BigInteger BigInteger::mod(BigInteger s1){
        //add
        string divisor=remove_leading_zeros(s1.get_val());
        string divident=remove_leading_zeros(this->get_val());
        if(divisor.length()>divident.length()){
            this->set_val(divident);
        }else{
            string k;
            for(int i=0;i<divident.length();i++){
                k+=divident[i];
                if(BigInteger::compare(k,divisor)>=0){
                    BigInteger d(k);
                    BigInteger q=get_quotent(d,divisor) ;
                    k.erase();
                    k=d.subtract(q).get_val();      
                }
            }
            this->set_val(k);
        }
        return *this;
}
BigInteger BigInteger::subtract(BigInteger s1){
        //add
        string min="0",max="0";
        string a=this->get_val();
        string b=s1.get_val();
        int lena=a.length();
        int lenb=b.length();
        
        if(lena>lenb){
            max.append(a);
            min.append(lena-lenb,'0');
            min.append(b);
        }else if(lena<lenb){
            max.append(b);
            min.append(lenb-lena,'0');
            min.append(a);
        }else{
            max.append(a);
            min.append(b);
        }
        string r(max.length(),'0');
        
        int brw=0,k=0,j=0;
        for(int i=max.length()-1;i>=0;i--){
            k=min[i]-'0';
            j=max[i]-'0';
            if(brw){
                j--;  
                brw--; 
            }
            if(j>=k){
                r[i]=(j-k)+'0';
                
            }else{
                r[i]=(j+10-k)+'0';
                brw++;
            }
        }
        r=BigInteger::remove_leading_zeros(r);
        
        this->set_val(r);
        return *this;
}
BigInteger BigInteger::cross(BigInteger s1){
        //add
        string a=this->get_val();
        string b=s1.get_val();
        string min="0",max="0";

        
        
         int lena=a.length();
        int lenb=b.length();
        
         if(lena>lenb){
            max.append(a);
            min.append(lena-lenb,'0');
            min.append(b);
        }else {
            max.append(b);
            min.append(lenb-lena,'0');
            min.append(a);
        }
        string r(max.length()+min.length(),'0');
        int n1=0,n2=0,n3=0,c=0,V=0;
        for(int i=min.length()-1,i1=0;i>=0;i--,i1++){
            c=0;
            for(int j=max.length()-1,j1=0;j>=0;j--,j1++){
                n1=min[i]-'0';
                n2=max[j]-'0';
                n3=r[min.length()+max.length()-1-i1-j1]-'0';
                V=n1*n2+c+n3;
                
                r[min.length()+max.length()-1-i1-j1]=(V%10)+'0';
                c=V/10;
            }
        }
        r=BigInteger::remove_leading_zeros(r);
        this->set_val(r);
        return *this;
}

BigInteger performOperation(BigInteger num1,BigInteger num2,char ch){
    if(ch =='x'||ch=='X'){
        return num1.cross(num2);
    }else if(ch == '+'){
        return num1.add(num2);
    }else if(ch == '-'){
        return num1.subtract(num2);
    }
}

string evaluate(string s){
    Stack<BigInteger> big; 
    Stack<char> op;
    string k;
    for(int i=0;i<s.length();i++){
        if(isdigit(s[i])){
            k+=s[i];
        }else{

            BigInteger b1(k);
            big.push(b1);
            k.erase();
            int p=check_get_priority(s[i]);
            if(op.isEmpty()){
                op.push(s[i]);
            }else{
                while(!op.isEmpty()&&p<=check_get_priority(op.top())){
                    BigInteger op2=big.top();
                    big.pop();
                    BigInteger op1=big.top();
                    big.pop();
                    char ch=op.top();
                    op.pop();
                    big.push(performOperation(op1,op2,ch));
                }
                op.push(s[i]);
            }
                        
        }
        
    }
    BigInteger b1(k);
    big.push(b1);
    while(!op.isEmpty()){
            BigInteger op2=big.top();
                    big.pop();
                    BigInteger op1=big.top();
                    big.pop();
                    char ch=op.top();
                    op.pop();
                    big.push(performOperation(op1,op2,ch));
        }
    return big.top().get_val();
}

int main()
{
    /* code */
    int t;
     
    
    do{
        cin>>t;
        if(t==1)
        {   string s;
            cin>>s;
            cout<<evaluate(s);
        }else if(t==2){
            string b;
            string e;
            cin>>b>>e;
            BigInteger base(b);
            long long int exp=stoll(e);
            cout<<BigInteger::exp(base,exp).get_val();
        }else if(t==3){
            string n1;
            string n2;
            cin>>n1>>n2;
            BigInteger num1(n1);
            BigInteger num2(n2);
            cout<<BigInteger::gcd(num1,num2).get_val();
        }else if(t==4){
            string s;
            cin>>s;
            BigInteger f(s);
            cout<<BigInteger::fact(f).get_val();
        }
        cout<<endl;
        
    }while(t!=0&&t<4); 
    return 0;
}