#include <iostream>
using namespace std;

//define priority_queue class
class priority_queue{
    private:
    int sz, cap, isMax;
    int* arr = nullptr;

    //swap values
    void swap(int* a, int*b){
        int temp = 0;
        temp = *a;
        *a = *b;
        *b = temp;
    }

    //create a new array with double capacity
    void changeCap(){
        int oldCap = cap, newCap;
        if(oldCap == 0)
            newCap = 1;
        else
            newCap = 2*oldCap;
        int *temp = new int[newCap];
        for(int i=0; i<cap; i++){
            temp[i] = arr[i];
        }
        cap = newCap;
        if(arr){
            delete[] arr;
        }
        arr = temp;
    }

    //Heapify heap from parent of last pushed node till root
    void Push_Heapify(int node){
        while(node > 0){
            int p = (node-1)/2;
            if((isMax && arr[node] > arr[p]) || !isMax && -1*arr[node] < -1*arr[p]){
                swap(&arr[p], &arr[node]);
                node = p;
            }
            else
                break;
        }
    }

    // Heapify heap from root and below for pop operation
    void Pop_Heapify(int node){
        int index = node;
        int lc = 2*node+1;
        int rc = 2*node+2;
        if((lc < sz) && ((!isMax && (-1*arr[lc] < -1*arr[index])) || (isMax && (arr[lc] > arr[index])))){
            index = lc;
        }
        if((rc < sz) && ((!isMax && (-1*arr[rc] < -1*arr[index])) || (isMax && (arr[rc] > arr[index])))){
            index = rc;
        }
        if(index!=node){
            swap(&arr[index],&arr[node]);
            Pop_Heapify(index);
        }
    }

    public:

    // 1. priority_queue
    priority_queue(int isMaxHeap){
        isMax = isMaxHeap;
        sz = 0;
        cap = 0;
    }

    // 2. size
    int size(){
        return sz;
    }

    // 6. empty
    bool empty(){
        return sz == 0;
    }

    // 3. push
    void push(int el){
        if(sz == cap){
            changeCap();
            //cout<<"change cap called"<<endl;
        }
        if(isMax){
            arr[sz] = el;
            sz++;
            Push_Heapify(sz-1);
        }
        else{
            arr[sz] = -1*el;
            sz++;
            Push_Heapify(sz-1);
        }
    }

    // 4. top
    int top(){
        if(!empty()){
            if(isMax)
                return arr[0];
            return -1*arr[0];
        }
        return -1;
    }

    // 5. pop
    void pop(){
        if(!empty()){
            arr[0] = arr[sz-1];
            sz--;
            Pop_Heapify(0);
        }
    }

    // 7. print heap for testing
    // void show(){
    //     for(int i=0; i<sz; i++)
    //         cout<<arr[i]<<" ";
    //     cout<<endl;
    // }
};

int main(){
    int choice = -1;
    priority_queue pq(1);

    while(choice != 0){
        cin>>choice;
        switch (choice)
        {
            case 0:
            {
                break;
            }

            //create empty pq
            // max:1
            // min:0
            case 1:
            {   int max;
                cin>>max;
                pq = priority_queue(max);
                break;
            }

            //size
            case 2:
            {   
                cout<<pq.size()<<endl;
                break;
            }

            //push
            case 3:
            {   int n;
                cin>>n;
                pq.push(n);
                break;
            }

            //top
            case 4:
            {
                cout<<pq.top()<<endl;
                break;
            }

            //pop
            case 5:
            {
                pq.pop();
                break;
            }

            //empty
            case 6:
            {
                cout<<boolalpha<<pq.empty()<<endl;
                break;
            }

            //print pq for testing
            // case 7:
            // {
            //     pq.show();
            //     break;
            // }

            default:
            {   //cout<<"Invalid Choice"<<endl;
                break;
            }
        }
    }
    return 0;
}
