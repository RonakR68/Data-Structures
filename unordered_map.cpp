#include <iostream>
#include <vector>
#include <string>
using namespace std;
   
//hash map node
template <typename T1, typename T2>
struct Node{
    T1 key;
    T2 value;
    Node* next;
    Node(T1 k, T2 v){
        key = k;
        value = v;
        next = nullptr;
    }
};

//define hash table
template <typename T1, typename T2>
class unordered_map{
private:
    const static int MAX_SIZE = 100000;
    Node<T1, T2>* map[MAX_SIZE];
    // Hash function
    template <typename T>
    size_t hash(const T& value){
    string strVal = to_string(value);
    size_t hashValue = 0;
    const size_t prime = 100000007;
    int n = strVal.size();
    for(int i=0; i<n; i++){
        char ch = strVal[i];
        hashValue = (hashValue * 31 + ch)%prime;
    }
    return hashValue%MAX_SIZE;
}

size_t hash(const string& value) {
    size_t hashValue = 0;
    const size_t prime = 100000007;
    int n = value.size();
    for (int i = 0; i < n; i++) {
        char ch = value[i];
        hashValue = (hashValue * 31 + ch) % prime;
    }
    return hashValue % MAX_SIZE;
}

public:
    int map_size;
    unordered_map(){
        for(int i = 0; i < MAX_SIZE; ++i){
            map[i] = nullptr;
        }
        map_size=0;
    }

    bool insert(T1 key, T2 value){
        int index = hash(key);
        //cout<<"index is: "<<index<<endl;
        Node<T1, T2>* newNode = new Node<T1, T2>(key, value);
        if(map[index] == nullptr){
            map[index] = newNode;
            map_size++;
        } 
        else{
            Node<T1, T2>* curr = map[index];
            if(curr && curr->key == key){
                delete newNode;
                return false; // Key already exists
            }
            while(curr->next){
                if(curr->key == key){
                    delete newNode;
                    return false; // Key already exists
                }
                curr = curr->next;
            }
            curr->next = newNode;
        }
        return true;
    }

    bool erase(T1 key){
        int index = hash(key);
        Node<T1, T2>* curr = map[index];
        Node<T1, T2>* prev = nullptr;
        while(curr){
            if(curr->key == key){
                if(prev){
                    prev->next = curr->next;
                }
                else{
                    map[index] = curr->next;
                }
                delete curr;
                map_size--;
                return true;
            }
            prev = curr;
            curr = curr->next;
        }
        return false; // Key not found
    }

    bool contains(T1 key){
        int index = hash(key);
        Node<T1, T2>* curr = map[index];
        while(curr){
            if(curr->key == key){
                return true;
            }
            curr = curr->next;
        }
        return false;
    }

    T2& operator[](T1 key){
        int index = hash(key);
        Node<T1, T2>* curr = map[index], *prev = nullptr;
        while(curr){
            if (curr->key == key){
                return curr->value;
            }
            prev = curr;
            curr = curr->next;
        }
        Node<T1, T2>* newNode = new Node<T1, T2>(key, T2());
        if(prev){
            prev->next = newNode;
            map_size++;
            return prev->next->value;
        }
        else{
            map[index] = newNode;
            map_size++;
            return map[index]->value;
        }
    }

    void clear(){
        for(int i = 0; i < MAX_SIZE; ++i){
            Node<T1, T2>* curr = map[i];
            while(curr){
                Node<T1, T2>* temp = curr;
                curr = curr->next;
                delete temp;
                map_size--;
            }
            map[i] = nullptr;
        }
        //map_size=0;
    }

    int size(){
        return map_size;
    }

    bool empty(){
        return size() == 0;
    }

    vector<T1> keys(){
        vector<T1> result;
        for (int i = 0; i < MAX_SIZE; ++i){
            Node<T1, T2>* curr = map[i];
            while(curr){
                result.push_back(curr->key);
                curr = curr->next;
            }
        }
        return result;
    }
};


int main(){
    int q;
    cin >> q;
    unordered_map<int,int> mp;
    int key;

    while(q--){
        int operation;
        cin >> operation;

        // Insert
        if(operation == 1){  
            int value;
            cin >> key >> value;
            cout<<(mp.insert(key, value) ? "true" : "false")<<endl;
        }
        // Erase
        else if(operation == 2){  
            cin >> key;
            cout<<(mp.erase(key) ? "true" : "false")<<endl;
        }
        // Contains
        else if(operation == 3){ 
            cin >> key;
            cout<<(mp.contains(key) ? "true" : "false")<<endl;
        }
        // Operator []
        else if(operation == 4){
            cin >> key;
            int &value = mp[key];
            cout<<value<<endl;
        }
        // Clear
        else if(operation == 5){  
            mp.clear();
        } 
        // Size
        else if (operation == 6){  
            cout<<mp.size()<<endl;
        }
        // Empty
        else if (operation == 7){  
            cout<<(mp.empty() ? "true" : "false")<<endl;
        }
        // Keys
        else if (operation == 8){  
            vector<int> keys = mp.keys();
            for(auto& key : keys){
                cout<<key<<endl;
            }
        }
    }
    return 0;
}
