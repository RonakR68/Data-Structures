#include <iostream>
#include <vector>
using namespace std;

template <class T1, class T2>
class ordered_map{
private:
    struct Node{
        T1 key;
        T2 value;
        Node* left;
        Node* right;
        int height;

        Node(T1& k, T2& v){
        key = k;
        value = v;
        left = nullptr;
        right = nullptr;
        height = 1;
        }
    };

    Node* root;
    int map_size = 0;

    int getHeight(Node* node){
        if (node == nullptr) return 0;
        return node->height;
    }

    void setHeight(Node* node){
        node->height = max(getHeight(node->left),getHeight(node->right))+1;
    }

    int getBalance(Node* node){
        if (node == nullptr) return 0;
        return getHeight(node->left) - getHeight(node->right);
    }

    Node* rotateLeft(Node* x){
        Node* y = x->right;
        if(!y) return y;
        Node* y_lc = y->left;
        y->left = x;
        x->right = y_lc;
        setHeight(x);
        setHeight(y);
        return y;
    }

    Node* rotateRight(Node* y){
        Node* x = y->left;
        if(!x) return x;
        Node* x_rc = x->right;
        x->right = y;
        y->left = x_rc;
        setHeight(y);
        setHeight(x);
        return x;
    }

    Node* insert(Node* node, T1 key, T2 value){
        if(node == nullptr){
            Node* newNode = new Node(key, value);
            map_size++;
            return newNode;
        }
        if(key < node->key)
            node->left = insert(node->left, key, value);
        else if(node->key == key){
            return node;
        }
        else{
            node->right = insert(node->right, key, value);
        }
        setHeight(node);
        int balance = getBalance(node);

        // Right subtree is heavy
        if(balance < -1){
            //RL
            if(key < node->right->key){
                node->right = rotateRight(node->right);
                return rotateLeft(node);
            }
                
            //RR
            else{
                return rotateLeft(node);
            }
        }
        else if(-1 <= balance && balance <= 1){
            //balanced
        }
        // Left subtree is heavy
        else{
            //LL
            if (key < node->left->key)
                return rotateRight(node);
            //LR
            else {
                node->left = rotateLeft(node->left);
                return rotateRight(node);
            }
        }        
        return node;
    }

    Node* getMinNode(Node* node){
        Node* current = node;
        while(current && current->left != nullptr)
            current = current->left;
        return current;
    }

    Node* erase(Node* node, T1 key){
        if (node == nullptr) return node;
        if (key < node->key)
            node->left = erase(node->left, key);
        else if (key == node->key){
            if(node->left == nullptr || node->right == nullptr){
                Node* temp = nullptr;
                if(node->left){
        		temp = node->left;
                }
                else{
                	temp = node->right;
                }
                if(temp == nullptr){
                    temp = node;
                    node = nullptr;
                } 
                else
                    *node = *temp;
                delete temp;
                map_size--;
            } 
            else{
                Node* temp = getMinNode(node->right);
                node->key = temp->key;
                node->value = temp->value;
                node->right = erase(node->right, temp->key);
            }
        }
        else{
            node->right = erase(node->right, key);
        }
        if (node == nullptr) return node;
        setHeight(node);
        int balance = getBalance(node);

        // Right Heavy
        if(balance < -1){
            if(getBalance(node->right) <= 0)
                return rotateLeft(node);
            else{
                node->right = rotateRight(node->right);
                return rotateLeft(node);
            }
        }
        else if(-1 <= balance && balance <= 1){
            //balanced
        }
        // Left Heavy
        else{
            if(getBalance(node->left) < 0){
                node->left = rotateLeft(node->left);
                return rotateRight(node);
            }  
            else{
                return rotateRight(node);
            }
        }
        return node;
    }

    void clear(Node* node){
        if(node != nullptr){
            clear(node->left);
            clear(node->right);
            delete node;
            map_size--;
        }
    }

    void keys(Node* node, vector<T1>& result){
        if(!node)
            return;
        keys(node->left, result);
        result.push_back(node->key);
        keys(node->right, result);
    }

public:
    ordered_map(){
        root = nullptr;
    }

    bool empty(){
        return (root == nullptr);
    }

    int size(){
        return map_size;
    }

    bool contains(T1 key){
        Node* current = root;
        while(current){
            if(key == current->key)
                return true;
            else if(key < current->key)
                current = current->left;
            else
                current = current->right;
        }
        return false;
    }

    bool insert(T1 key, T2 value){
        int prev_size = size();
        root = insert(root, key, value);
        return prev_size < size();
    }

    bool erase(T1 key){
        int prev_size = size();
        root = erase(root, key);
        return size() < prev_size;
    }

    T2& operator[](T1 key){
        Node* current = root;
        while (current != nullptr){
            if (key == current->key)
                return current->value;
            else if (key < current->key)
                current = current->left;
            else
                current = current->right;
        }
        //key not found insert default value
        insert(key, T2());
        return operator[](key);
    }

    void clear(){
        clear(root);
        root = nullptr;
    }

    vector<T1> keys(){
        vector<T1> result;
        keys(root, result);
        return result;
    }

    pair<bool, T1> lower_bound(T1 key){
    Node* current = root;
    Node* lb = nullptr;
    while(current != nullptr){
        if(key == current->key)
            return make_pair(true, current->key);
        else if(key < current->key){
            lb = current;
            current = current->left;
        } 
        else
            current = current->right;
    }
    if(lb != nullptr)
        return make_pair(true, lb->key);
    // else if (root != nullptr)
    //     return make_pair(true, root->key);
    else
        return make_pair(false, T1());
}

    pair<bool, T1> upper_bound(T1 key){
    Node* current = root;
    Node* ub = nullptr;
    while(current != nullptr){
        if(key == current->key){
            current = current->right; 
        } 
        else if(key < current->key){
            ub = current;
            current = current->left;
        } 
        else{
            current = current->right;
        }
    }
    if(ub != nullptr && key < ub->key){
        return make_pair(true, ub->key);
    } 
    else{
        return make_pair(false, T1());
    }
    }

};

int main(){
    ordered_map<int, int> ordered_map;
    int key;
    int val;

    while(true){
        int choice;
        cin >> choice;

        switch (choice){
            case 0:
            {
                return 0;
            }
            case 1:
            {
                cout << (ordered_map.empty() ? "true" : "false") << endl;
                break;
            }
            case 2:
            {
                cout << ordered_map.size() << endl;
                break;
            }
            case 3:
            {
                cin >> key;
                cout << (ordered_map.contains(key) ? "true" : "false") << endl;
                break;
            }
            case 4:
            {
                cin >> key >> val;
                cout << (ordered_map.insert(key, val) ? "true" : "false") << endl;
                break;
            }
            case 5:
            {
                cin >> key;
                cout << (ordered_map.erase(key) ? "true" : "false") << endl;
                break;
            }
            case 6:
            {
                cin >> key;
                cout << ordered_map[key] << endl;
                break;
            }
            case 7:
            {
                ordered_map.clear();
                break;
            }
            case 8:
            {
                vector<int> keyVector = ordered_map.keys();
                for (int k : keyVector) {
                    cout << k << endl;
                }
                break;
            }
            case 9:
            {
                cin >> key;
                pair<bool, int> result = ordered_map.lower_bound(key);
                bool first = result.first;
                if(first){
                    cout << "true" << endl;
                    cout << result.second << endl;
                } 
                else{
                    cout << "false" << endl;
                    //cout<< result.second <<endl;
                }
                break;
            }
            case 10:
            {
                cin >> key;
                pair<bool, int> result = ordered_map.upper_bound(key);
                bool first = result.first;
                if(first){
                    cout << "true" << endl;
                    cout << result.second << endl;
                } 
                else{
                    cout << "false" << endl;
                    //cout<< result.second <<endl;
                }
                break;
            }
            default:
            {
                // cout << "Invalid choice" << endl;
                break;
            }
        }
    }
    return 0;
}
