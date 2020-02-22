# include<iostream>
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
    return 0;
}