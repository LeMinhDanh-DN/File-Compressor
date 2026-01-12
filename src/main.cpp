#include <iostream>
#include <map>
#include <queue>
#include <fstream>

class Node{
    public:
        char c;
        int fre;
        int isInterval;
        Node* r;
        Node* l;
        Node(){
            isInterval  = 0;
            fre = 0;
            r = l = nullptr;
        }

};

struct cmp{
    bool operator()(Node*a, Node*b){
        return a->fre > b->fre;
    }
};
std::map<char,std::string> mp;

void get(Node* cur, std::string s){
    if(cur == nullptr) return;
    if(!cur->isInterval){
        mp[cur->c] = s;
    }
    get(cur->l, s + '0');
    get(cur->r, s + '1');
    
    return;
}
void freetree(Node* cur){
    if(cur == nullptr) return;
    freetree(cur->l);
    freetree(cur->r);
    delete cur;
}

signed main(){
    std::ifstream inp("../data/INP.txt");
    std::ofstream out("../data/OUT.txt");

    if(!inp.is_open()){
        std::cerr << "cant open";
        return 0;
    }

    std::string s, tmp;
    while(getline(inp,tmp)){
        s += tmp;
        s += '\n';
    }
    inp.close();

    std::map<char,int> cnt;
    std::priority_queue<Node*, std::vector<Node*>, cmp> pq;

    for(char c : s){
        cnt[c] ++;
    }
    for(auto x : cnt){
        // cout << char('a' + i )<< " " << cnt[i] << "\n";
        Node* tmp = new Node;
        tmp->c = x.first;
        tmp->fre = x.second;
        pq.push(tmp);
    }
    while(pq.size() != 1){
        Node* a = pq.top(); pq.pop();
        Node* b = pq.top(); pq.pop();
        Node* tmp = new Node;

        tmp->isInterval = 1;
        tmp->l = a;
        tmp->r = b;
        tmp->fre = a->fre + b->fre;

        pq.push(tmp);
    }
    Node* root = pq.top();
    // cout << root->fre << " " << root->inv;
    get(root, "");
    if(!root ->isInterval) mp[root->c] = "0";
    for(char c : s){
        out << mp[c];
    }

    freetree(root);
    out.close();
    
}