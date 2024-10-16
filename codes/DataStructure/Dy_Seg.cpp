#include <bits/stdc++.h>
using namespace std;

struct Node {
    unordered_map<int, int> mp; // 記錄頻率
    int tag = 0;
    int l, r;
    Node* left = nullptr;
    Node* right = nullptr;
};

Node* build(int l, int r) {
    Node* node = new Node();
    node->l = l;
    node->r = r;
    return node;
}

void pushdown(Node* node) { // push tags
    if (node->tag) {
        if (!node->left) node->left = build(node->l, (node->l + node->r) / 2);
        if (!node->right) node->right = build((node->l + node->r) / 2 + 1, node->r);
        // Update child
        node->left->mp.clear();
        node->right->mp.clear();
        int mid = (node->l + node->r) / 2;
        int left_len = mid - node->l + 1;
        int right_len = node->r - mid;
        node->left->mp[node->tag] = left_len;
        node->right->mp[node->tag] = right_len;
        node->left->tag = node->tag;
        node->right->tag = node->tag;

        node->tag = 0;
    }
}

// 將 [l, r] 區間內的數字設為 val
void range_update(Node* node, int l, int r, int val) {
    if (l <= node->l && node->r <= r) {
        node->mp.clear();
        node->mp[val] = node->r - node->l + 1;
        node->tag = val; // tag!
        return;
    }

    pushdown(node);
    int mid = (node->l + node->r) / 2;

    if (l <= mid) {
        if (!node->left) node->left = build(node->l, mid);
        range_update(node->left, l, r, val);
    }
    if (r > mid) {
        if (!node->right) node->right = build(mid + 1, node->r);
        range_update(node->right, l, r, val);
    }

    // push_up
    node->mp.clear();
    if (node->left) {
        for (auto& [key, val] : node->left->mp) {
            node->mp[key] += val;
        }
    }
    if (node->right) {
        for (auto& [key, val] : node->right->mp) {
            node->mp[key] += val;
        }
    }
}

unordered_map<int, int> query(Node* node, int l, int r) {
    if (l <= node->l && node->r <= r) return node->mp;
    
    pushdown(node);
    int mid = (node->l + node->r) / 2;
    unordered_map<int, int> result;

    if (l <= mid && node->left) {
        auto left_result = query(node->left, l, r);
        for (auto& [key, val] : left_result) {
            result[key] += val;
        }
    }

    if (r > mid && node->right) {
        auto right_result = query(node->right, l, r);
        for (auto& [key, val] : right_result) {
            result[key] += val;
        }
    }

    return result;
}

void recycle(Node* &node) {
    if (node == nullptr) return;
    if (node->left) recycle(node->left);
    if (node->right) recycle(node->right);
    delete node; 
    node = nullptr; 
}

void delete_range(Node* node, int l, int r) {
    // delete range [l,r]
    if (l <= node->l && node->r <= r) {
        node->mp.clear();
        node->tag = 0;
        recycle(node->left);
        recycle(node->right);
        return;
    }
    pushdown(node);
    int mid = (node->l + node->r) / 2;
    if (node->left && l <= mid) {
        delete_range(node->left, l, r);
    }
    if (node->right && r > mid) {
        delete_range(node->right, l, r);
    }
    // push_up
    node->mp.clear();
    if (node->left) {
        for (auto& [key, val] : node->left->mp) {
            node->mp[key] += val;
        }
    }
    if (node->right) {
        for (auto& [key, val] : node->right->mp) {
            node->mp[key] += val;
        }
    }
}


int main() {
    int n, q;
    cin >> n >> q;
    Node* root = build(1, n);

    while (q--) {
        int op, l, r, x;
        cin >> op;
        if (op == 1) {
            cin >> l >> r >> x; // set [l,r] to x
            range_update(root, l, r, x);
        } else {
            cin >> l >> r; // query [l,r] every number's frequency
            unordered_map<int, int> freq = query(root, l, r);
            for (auto& [key, val] : freq) {
                cout<<key<<" "<<val<<endl;
            }
            delete_range(root, l, r);
        }
    }
}
