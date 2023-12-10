#pragma GCC optimize("O3")
#include <iostream>
#include <vector>
using namespace std;

template <typename T> class Treap{
    private:
    struct Node{
        T value;
        int priority;
        Node *left;
        Node *right;
        int sz;

        Node(T val){
            this->value = val;
            this->priority = rand();
            this->left = nullptr;
            this->right = nullptr;
            this->sz = 1;
        }
    };

    Node *root = nullptr;

    int getNodeSize(Node* node){
        if(!node)
            return 0;
        return node->sz;
    }

    void setNodeSize(Node* node){
        if(node){
            node->sz = 1 + getNodeSize(node->left) + getNodeSize(node->right);
        }
    }

    void clearTreap(Node *treapNode){
        if(!treapNode)
            return;
        if(treapNode->left)
            clearTreap(treapNode->left);
        if(treapNode->right)
            clearTreap(treapNode->right);
        delete treapNode;
    }

    void merge(Node* &node, Node* l, Node* r){
        int p;
        if(l == nullptr || r == nullptr){
            if(l){
                node = l;
            }
            else
                node = r;
        } 
        else if(l->priority <= r->priority){
            merge(r->left, l, r->left);
            node = r;
        } 
        else{
            merge(l->right, l->right, r);
            node = l;
        }
        setNodeSize(node);
    }

    void split(Node* node, Node* &l, Node* &r, int ind, int cnt){
        if(node == nullptr){
            l = nullptr;
            r = nullptr;
            return;
        }
        int currInd;
        currInd = cnt + getNodeSize(node->left);
        if(ind > currInd){
            int currCount = 0;
            cnt = cnt + getNodeSize(node->left) + 1;
            split(node->right, node->right, r, ind, cnt);
            l = node;
        } 
        else{
            int currCount = 0;
            split(node->left, l, node->left, ind, cnt);
            r = node;
        }
        setNodeSize(node);
    }

    int getLowerBound(Node* node, T val){
        if(node){
            if(node->value >= val) {
                return getLowerBound(node->left, val);
            }
            return getLowerBound(node->right, val) + getNodeSize(node->left) + 1;
        }
        else{
            return 0;
        }
    }

    int getUpperBound(Node* node, T val){
        if(node){
            if(node->value > val){
                return getUpperBound(node->left, val);
            }
            return getUpperBound(node->right, val) + getNodeSize(node->left) + 1;
        }
        else{
            return 0;
        }
    }

    int findIndexOf(Node* node, T val){
        if(!node){
            return -1;
        }
        if(val == node->value){
            int leftSubtreeIndex = findIndexOf(node->left, val);
            if(leftSubtreeIndex == -1){
                return getNodeSize(node->left);
            } 
            else{
                return leftSubtreeIndex;
            }
        } 
        else if(val >= node->value){
            int rightSubtreeIndex = findIndexOf(node->right, val);
            if(rightSubtreeIndex == -1){
                return -1;
            } 
            else{
                return getNodeSize(node->left) + 1 + rightSubtreeIndex;
            }
        } 
        else{
            return findIndexOf(node->left, val);
        }
    }

    void inorder(vector<T> &v, Node* node){
        if(!node) return;
        inorder(v, node->left);
        v.push_back(node->value);
        inorder(v, node->right);
    }

    public:

    Treap(){
        root = nullptr;
    }

    //1. empty
    bool empty(){
        return root == nullptr;
    }

    //2. size
    int size(){
        return getNodeSize(root);
    }

    //3. clear
    void clear(){
        clearTreap(root);
        root = nullptr;
    }

    //4. insert
    int insert(T val){
        Node* newNode = new Node(val);
        int indexToSplit = 0;
        indexToSplit = getLowerBound(root,val);
        Node *node1 = nullptr;
        Node *node2 = nullptr;
        //split treap with node1(<val) and node2(>=val) as roots based on lowerbound index
        //cout<<"splitIndex is: "<<indexToSplit<<"\n";
        split(root, node1, node2, indexToSplit, 0);
        //insert new node in treap 1
        merge(node1, node1, newNode);
        //merge treap 1 containing new node with treap 2
        merge(root, node1, node2);
        return indexToSplit;     
    }

    // 5. erase
    bool erase(int index){
        int currSize = getNodeSize(root);
        if(index >= currSize || index <= -1){
            return false;
        }
        Node *node1 = nullptr;
        Node* node2 = nullptr;
        Node* node3 = nullptr;
        split(root, node1, node2, index, 0);
        split(node2, node2, node3, 1, 0);
        delete node2;
        merge(root, node1, node3);
        return true;
    }

    // 6. IndexOf
    int indexOf(T val){
        int index = findIndexOf(root, val);
        return index;
    }

    // 7. atIndex
    T atIndex(int index){
        int currSize = getNodeSize(root);
        if(index <= -1 || index >= currSize){
            return T();
        }
        Node *node1 = nullptr;
        Node* node2 = nullptr;
        Node* node3 = nullptr;
        split(root, node1, node2, index, 0);
        split(node2, node2, node3, 1, 0);
        T valueAtIndex;
        valueAtIndex = node2->value;
        merge(node2, node2, node3);
        merge(root, node1, node2);
        return valueAtIndex;
    }

    // 8. merge
    Treap<T>* merge(Treap<T> *t2){
        Treap<T> *t1 = this;
        Node *first = t1->root;
        Node *second = t2->root;
        merge(first, first, second);
        second = nullptr;
        return t1;
    }

    //9. split
    pair<Treap<T>*, Treap<T>*> split(int index){
        int currSize = getNodeSize(root);
        if(index >= 0 && index < currSize){
            Treap<T> *t1 = new Treap<T>();
            Node *t1_root, *t2_root;
            Treap<T> *t2 = new Treap<T>();
            split(root, t1_root, t2_root, index, 0);
            t1->root = t1_root;
            t2->root = t2_root;
            root = nullptr;
            return {t1, t2};
        }
        else{
            return {nullptr, nullptr};
        }
    }

    // 10. erase (first,last)
    bool erase(int first, int last){
        int currSize = getNodeSize(root);
        if(first >= 0 && last < currSize && first <= last){
            Treap<T> *t1 = new Treap<T>();
            pair<Treap<T>*,Treap<T>*> split1;
            Treap<T> *t2 = new Treap<T>();
            pair<Treap<T>*,Treap<T>*> split2;
            Treap<T> *t3 = new Treap<T>();
            split1 = split(first);
            if(last == currSize - 1){
                t1->root = split1.first->root;
            } 
            else{
                int ind2 = 1 + last - first;
                split2 = split1.second->split(ind2);
                t1->root = split1.first->root;
                t2->root = split2.first->root;
                t3->root = split2.second->root;
            }
            merge(root, t1->root, t3->root);
            delete split1.first;
            delete split1.second;
            delete split2.first;
            delete split2.second;
            delete t2;
            return true;
        }
        else{
            return false;
        }
    }

    // 11. slice
    Treap<T>* slice(int first, int last){
        int currSize = getNodeSize(root);
        if (first >= 0 && last < currSize && first <= last) {
            // Split the original treap into two parts: [0, first - 1] and [first, last]
            Treap<T>* leftTreap = nullptr;
            Treap<T>* middleTreap = nullptr;
            pair<Treap<T>*, Treap<T>*> split1;
            split1 = split(first);
            leftTreap = split1.first;
            middleTreap = split1.second;
            if(last < currSize - 1){
                pair<Treap<T>*, Treap<T>*> split2;
                split2 = middleTreap->split(last - first + 1);
                middleTreap = split2.first;
                delete split2.second;
            }
            delete leftTreap;
            return middleTreap;
        } 
        else{
            return nullptr;
        }
    }

    // 12. lower bound
    int lower_bound(T val){
        int lb = getLowerBound(root,val);
        return lb;
    }

    // 13. upper bound
    int upper_bound(T val){
        int ub = getUpperBound(root, val);
        return ub;
    }

    // 14. count
    int count(T val){
        int lb = lower_bound(val);
        int ub = upper_bound(val);
        return ub - lb;
    }

    // 15. to_array
    vector<T> to_array(){
        vector<T> ans;
        inorder(ans,root);
        int n = ans.size();
        //cout<<n<<"\n";
        return ans;
    }
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    Treap<int> treap;
    int choice;
    int index, first, last;
    int val;
    Treap<int>* treap2 = nullptr;
    while(true){
        cin>>choice;
        if(choice == 1){
        // Empty
        if(treap.empty())
            cout << "true" << "\n";
        else
            cout << "false" << "\n";
        }
        else if(choice == 2){
            // Size
            cout << treap.size() << "\n";
        }
        else if(choice == 3){
            // Clear
            treap.clear();
        }
        else if(choice == 4){
            // Insert
            cin >> val;
            cout << treap.insert(val) << "\n";
        }
        else if(choice == 5){
            // Erase
            cin >> index;
            cout << (treap.erase(index) ? "true" : "false") << "\n";
        }
        else if(choice == 6){
            // IndexOf
            cin >> val;
            cout << treap.indexOf(val) << "\n";
        }
        else if(choice == 7){
            // AtIndex
            cin >> index;
            cout << treap.atIndex(index) << "\n";
        }
        else if(choice == 8){
            // Merge
            treap2 = new Treap<int>();
            treap.merge(treap2);
        }
        else if(choice == 9){
            // Split
            cin >> index;
            auto splitResult = treap.split(index);
            // Treap<int>* leftTreap = splitResult.first;
            // Treap<int>* rightTreap = splitResult.second;
            // delete leftTreap;
            // delete rightTreap;
        }
        else if (choice == 10){
            // Erase (Range)
            cin >> first >> last;
            cout << (treap.erase(first, last) ? "true" : "false") << "\n";
        }
        else if (choice == 11){
            // Slice
            int first, last;
            cin >> first >> last;
            Treap<int>* slicedTreap = treap.slice(first, last);
            if(slicedTreap){
                // Update the original treap with the sliced treap
                treap = *slicedTreap;
                delete slicedTreap;
            } 
        }
        else if(choice == 12){
            // Lower Bound
            cin >> val;
            cout << treap.lower_bound(val) << "\n";
        }
        else if(choice == 13){
            // Upper Bound
            cin >> val;
            cout << treap.upper_bound(val) << "\n";
        }
        else if(choice == 14){
            // Count
            cin >> val;
            cout << treap.count(val) << "\n";
        }
        else if(choice == 15){
            // To Array
            vector<int> arr = treap.to_array();
            for(int i = 0; i < arr.size(); i++){
                cout << arr[i];
                if(i < arr.size() - 1){
                    cout << ' ';
                }
            }
            cout << "\n";
        }
        else if(choice == 0){
            if(treap2 != nullptr){
                delete treap2;
            }
            break;
        }
    }
    
    return 0;
}
