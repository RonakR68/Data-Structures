#include<iostream>
#include<vector>
using namespace std;

//define Trie node structure
struct TrieNode{
    struct TrieNode *nodes [26];
    bool isLast;
    TrieNode(){
        int i=0;
        while(i<26){
            nodes[i] = nullptr;
            i++;
        }
        isLast = false;
    }
};

//function to insert string in trie
void insert(TrieNode *root, string s){
    int n = s.size();
    TrieNode *ptr = root;
    for(int i=0; i<n; i++){
        if(!ptr->nodes[s[i]-'a']){
            ptr->nodes[s[i]-'a'] = new TrieNode();
        }
        ptr = ptr->nodes[s[i]-'a'];
    }
    ptr->isLast = true;
}

//1.spellcheck
bool spellCheck(TrieNode *root, string s){
    int n = s.size();
    TrieNode *ptr = root;
    for(int i=0; i<n; i++){
        char c = s[i];
        int ind = c-'a';
        if(!ptr->nodes[ind])
            return false;
        ptr = ptr->nodes[ind];
    }
    return ptr && ptr->isLast;
}

void solve_autoComplete(TrieNode *node, string s, vector<string> &v){
    if(node->isLast){
        v.push_back(s);
    }
    for(int i=0; i<26; i++){
        if(!node->nodes[i])
            continue;
        char c = 'a'+i;
        solve_autoComplete(node->nodes[i], s+c, v);
    } 
}

//2.autocomplete
void autoComplete(TrieNode *root, string s){
    int n = s.size();
    TrieNode *ptr = root;
    for(int i=0; i<n; i++){
        int ind = s[i]-'a';
        if(!ptr->nodes[ind]){
            cout<<0<<endl;
            return;
        }
        ptr = ptr->nodes[ind];
    }
    vector<string> words;
    solve_autoComplete(ptr, s, words);
    cout<<words.size()<<endl;
    for(int i=0; i<words.size(); i++){
        cout<<words[i]<<endl;
    }
}

int getMin(int a, int b, int c){
    return a<b ? (a<c ? a : c) : (b<c ? b : c);
}

bool checkDistance(string s1, string s2){
    int m = s1.size();
    int n = s2.size();
    if(abs(m-n)>3)
        return false;
    vector<int> prev(n + 1), curr(n + 1);
    for (int j = 0; j <= n; j++){
        prev[j] = j;
    }
    int minDist = 4;
    for (int i = 1; i <= m; i++){
        curr[0] = i;
        for(int j = 1; j <= n; j++){
            curr[j] = getMin(prev[j] + 1,curr[j - 1] + 1,prev[j - 1] + (s1[i - 1] != s2[j - 1] ? 1 : 0));
            minDist=minDist<curr[j]?minDist:curr[j];
        }
        if(minDist>3)
            return false;
        swap(prev, curr);
    }
    return prev[n]<=3;
}

void solve_autoCorrect(TrieNode *node, string s1, string s2, vector<string> &v){
    if(!node)
        return;
    //if(s1.size()+3<s2.size() || s2.size()+6<s1.size())
    //  return;
    if(node->isLast && checkDistance(s1, s2))
        v.push_back(s2);
    for(int i=0; i<26; i++){
        if(!node->nodes[i])
            continue;
        char c = 'a'+i;
        solve_autoCorrect(node->nodes[i], s1, s2+c, v);
    }
}

//3.autocorrect
void autoCorrect(TrieNode *root, string s){
    vector<string> words;
    solve_autoCorrect(root,s,"",words);
    cout<<words.size()<<endl;
    for(int i=0; i<words.size(); i++){
        cout<<words[i]<<endl;
    }
}

int main(){
    int n,q;
    cin >> n >> q;
    TrieNode* root = new TrieNode();
    for (int i = 0; i < n; i++){
        string s;
        cin>>s;
        insert(root, s);
    }
    while (q--){
        int choice;
        string s;
        cin >> choice >> s;
        if (choice == 1){
            cout << spellCheck(root, s)<<endl;
        } 
        else if(choice == 2){
            autoComplete(root, s);
        } 
        else if(choice == 3){
            autoCorrect(root, s);
        }
    }
    return 0;
}