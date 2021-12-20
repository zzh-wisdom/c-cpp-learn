#include <iostream>
#include <stack>
#include <queue>
#include <unordered_map>
#include <algorithm>
using namespace std;

struct entry_key_t {
    uint64_t key;
    uint64_t hot;
    entry_key_t(uint64_t key_, uint64_t hot_ = 0) :key(key_), hot(hot_){}
};

void btree_insert(entry_key_t key) {
    cout<<"entry_key_t:"<<endl;
    cout<<key.key<<endl;
    cout<<key.hot<<endl;
}

int main() {
    unsigned long key = 50;
    btree_insert(key);
    stack<int> s;
    // cout << s.top() << endl;;

    std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
    pq.push(2);
    pq.push(3);
    while(!pq.empty()) {
        cout << pq.top() << " ";
        pq.pop();
    }
    cout << endl;

    std::unordered_map<int, int> m;
    m[1] = 1;
    m[2] = 2;
    m[3] = 3;
    m[7] = 7;
    m[4] = 4;
    // std::sort(m.begin(), m.end());
    auto it = ++m.begin();
    printf("%d %d\n", it->first, it->second);
    for(auto p: m) {
        cout << p.first << "," << p.second << " ";
    }
    cout << endl;
    return 0;
}