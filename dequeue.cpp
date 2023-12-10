#include <iostream>
using namespace std;

//define deque class
template <class T> class deque{
    private:
    int frontPtr, rearPtr, sz, cap;
    T* arr = nullptr;

     //function that returns true is deque is full
    bool isFull(){
        if(sz == cap)
            return true;
        return false;
    }

    //function which creates a new deque in memory as per new capacity and copy contents from old deque.
    //It takes input parameter which is uses to set as defailt value
    bool changecap(int oldCap, T d){
        T* temp = new T[cap]; // create new array
        if(temp == NULL) return false;
        //copy values to new array
        int i = frontPtr;
        int j = 0;
        while (i != rearPtr) {
            temp[j] = arr[i];
            i = (i + 1) % oldCap;
            j++;
        }
        if(i>=0)
        temp[j] = arr[i];
        frontPtr = 0;
        rearPtr = sz - 1;
        for(i = sz; i<cap; i++)
            temp[i] = d;
        delete[] arr; //delete old array
        arr = temp;
        return true;
    }



    public:
    // 1. empty deque constructor
    deque(){
        sz = 0;
        cap = 0;
        frontPtr = -1;
        rearPtr = -1;
    }

    // 2. deque(n) constructor
    deque(int n){
        sz = n;
        cap = n;
        frontPtr = 0;
        rearPtr = n-1;
        arr = new T[cap];
        //initialize with default values
        for(int i=0; i<n; i++)
            arr[i] = T();
    }

    // 3. deque(n,x) constructor
    deque(int n, T x){
        sz = n;
        cap = n;
        frontPtr = 0;
        rearPtr = n-1;
        arr = new T[cap];
        for(int i=0; i<n; i++){
            arr[i] = x;
        }
    }


    // 4. push_back(x)
    bool push_back(T x){
        if (sz == 0) {
            frontPtr = 0;
            rearPtr = 0;
            if(arr)
                delete[] arr;
            arr = new T[1];
            arr[frontPtr] = x;
            sz++;
            if(cap == 0) cap++;
            return true;
        }
        if(isFull()){
            int oCap = cap;
            cap = 2*cap;
            if(!changecap(oCap, T())) return false;
        }
        rearPtr = (rearPtr + 1) % cap;
        arr[rearPtr] = x;
        sz++;
        return true;
    }

    // 11. empty()
    bool empty(){
        if(sz == 0)
            return true;
        return false;
    }

    // 5. pop_back()
    bool pop_back(){
        if(empty()) return false;

        if(frontPtr == rearPtr){
            //only single element in deque
            frontPtr = -1;
            rearPtr = -1;
            sz = 0;
            return true;
        }

        rearPtr = (rearPtr - 1 + cap) % cap;
        sz--;
        return true;
    }

    // 6. push_front(x)
    bool push_front(T x){
        if(empty()){
            frontPtr = 0;
            rearPtr = 0;
            if(arr)
                delete[] arr;
            arr = new T[1];
            arr[frontPtr] = x;
            sz++;
            if(cap == 0) cap++;
            return true;
        }
        if(isFull()){
            int oCap = cap;
            cap = 2*cap;
            if(!changecap(oCap, T())) return false;
        }

        frontPtr = (frontPtr - 1 + cap) % cap;
        arr[frontPtr] = x;
        sz++;
        return true;
    }

    // 7 pop_front()
    bool pop_front(){
        if(empty()) return false;

        if(frontPtr == rearPtr){
            frontPtr = -1;
            rearPtr = -1;
            sz--;
            return true;
        }

        frontPtr = (frontPtr + 1) % cap;
        sz--;
        return true;
    }
    
    //8. front
    T front(){
        if(empty())
            return T();
        else
            return arr[frontPtr];
    }

    //9. back
    T back(){
        if(empty())
            return T();
        else
            return arr[rearPtr];
    }

    // 10. D[n]
    T operator [](int n){
        if(empty()) return T();
        if(n<0){
            int m = -1*n;
            if(m > sz) return T();
            int p = rearPtr;
            n++;
            p = (p + n + cap) % cap;
            return arr[p];
        }
        //if n is in valid range then return currently stored value else return default value 
        if(n < sz)
       {
            int p = frontPtr;
            //n--;
            p = (p + n) % cap;
            return arr[p];
       }
        return T();
    }

    // 12. size()
    int size(){
        return sz;
    }

    // 13. resize(n)
    void resize(int n){
        if(n == sz) return;
        //if n<0 throw error
        if(n==0){
            frontPtr = -1;
            rearPtr = -1;
            sz = 0;
            return;
        }
        if(n > sz){
            if(n <= cap){
                int diff = n-sz;
                sz = n;
                while(diff){
                    rearPtr = (rearPtr+1)%cap;
                    arr[rearPtr] = T();
                    diff--;
                }
                if(frontPtr == -1) frontPtr = 0;
                return;
            }
            else{
                //int count = (n-1)/cap;
                int oCap = cap;
                //cap = 2*count*cap;
                cap = n;
                changecap(oCap, T());
                sz = n;
                rearPtr = sz-1;
                if(frontPtr == -1) frontPtr = 0;
                return;
                }
        }
        int diff = sz-n;
        sz = n;
        while(diff){
            rearPtr = (rearPtr - 1 + cap) % cap;
            diff--;
        }
    }

    // 14. resize(n,d)
    void resize(int n, T d){
        if(n == sz) return;
        //if n<0 throw error
        if(n > sz){
            if(n <= cap){
                int diff = n-sz;
                sz = n;
                while(diff){
                    rearPtr = (rearPtr+1)%cap;
                    arr[rearPtr] = d;
                    diff--;
                }
                if(frontPtr == -1) frontPtr = 0;
                return;
            }
            else{
                //int count = (n-1)/cap;
                int oCap = cap;
                //cap = 2*count*cap;
                cap = n;
                changecap(oCap, d);
                sz = n;
                rearPtr = sz-1;
                if(frontPtr == -1) frontPtr = 0;
                return;
            }
        }
        int diff = sz-n;
        sz = n;
        while(diff){
            rearPtr = (rearPtr - 1 + cap) % cap;
            diff--;
        }
    }

    // 15. reserve(n)
    void reserve(int n){
        if(n > cap){
            int oCap = cap;
            cap = n;
            changecap(oCap, T());
        }
    }

    // 16. shrink_to_fit
    void shrink_to_fit(){
        int oCap = cap;
        cap = sz;
        changecap(oCap, T());
    }

    // 17. clear()
    void clear(){
        frontPtr = -1;
        rearPtr = -1;
        sz = 0;
    }

    // 18. capacity()
    int capacity(){
        return cap;
    }

};


int main(){
    
    int choice = -1;
    deque <int> dq;
    int s;

    while(choice != 0){
        //cout<<"Enter Choice [0-18]:";
        cin>>choice;
        //cout<<endl;
        switch (choice)
        {
        case 0:
        {
            break;
        }

        case 1:
        {
            dq = deque <int> ();
            break;
        }

        case 2:
        {   
            int n;
            cin>>n;
            dq = deque <int> (n);
            break;
        }

        case 3:
        {   int n;
            cin>>n;
            cin>>s;
            dq = deque <int> (n,s);
            break;
        }

        case 4:
        {
            cin>>s;
            cout<< boolalpha <<dq.push_back(s)<<endl;
            break;
        }

        case 5:
        {
            cout<< boolalpha <<dq.pop_back()<<endl;
            break;
        }

        case 6:
        {
            cin>>s;
            cout<<boolalpha<<dq.push_front(s)<<endl;
            break;
        }

        case 7:
        {
            cout<< boolalpha <<dq.pop_front()<<endl;
            break;
        }

        case 8:
        {
            cout<<dq.front()<<endl;
            break;
        }

        case 9:
        {
            cout<<dq.back()<<endl;
            break;
        }

        case 10:
        {
            int n;
            cin>>n;
            cout<<dq[n]<<endl;
            break;
        }

        case 11:
        {
            cout<< boolalpha <<dq.empty()<<endl;
            break;
        }

        case 12:
        {
            cout<<dq.size()<<endl;
            break;
        }

        case 13:
        {
            int n;
            cin>>n;
            dq.resize(n);
            break;
        }

        case 14:
        {
            int n;
            cin>>n;
            cin>>s;
            dq.resize(n,s);
            break;
        }

        case 15:
        {
            int n;
            cin>>n;
            dq.reserve(n);
            break;
        }

        case 16:
        {
            dq.shrink_to_fit();
            break;
        }

        case 17:
        {
            dq.clear();
            break;
        }

        case 18:
        {
            cout<<dq.capacity()<<endl;
            break;
        }
        
        default:
        {   //cout<<"Invalid Choice"<<endl;
            break;
        }
        }
    }
   
    return 0;
}
