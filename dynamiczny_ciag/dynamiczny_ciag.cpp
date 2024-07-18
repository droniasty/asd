
// C++ code for the above approach:
//#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
 
struct node {
    int key;
    uint32_t subtree_size;
    uint32_t count;
    node *left, *right;
};

uint32_t get_size(node* root) {
    if (root == NULL) return 0;
    return root->subtree_size;
}
 
node* newNode(int key, uint32_t count)
{
    node* temp = new node;
    temp->key = key;
    temp->left = temp->right = NULL;
    temp->subtree_size = count;
    temp->count = count;
    return temp;
}
 
node* rightRotate(node* x)
{
    node* y = x->left;
    uint32_t node_count = x->subtree_size;
    uint32_t left_count = y ? y->subtree_size : 0;
    uint32_t right_count = x->right ? x->right->subtree_size : 0;
    uint32_t left_right_count = y ? (y->right ? y->right->subtree_size : 0) : 0;
    uint32_t left_left_count = y ? (y->left ? y->left->subtree_size : 0) : 0;
    //uint32_t right_left_count = x->right->left ? x->right->left->subtree_size : 0;

    x->left = y->right;
    x->subtree_size = left_right_count + right_count + x->count;
    y->right = x;
    y->subtree_size = x->subtree_size + left_left_count + y->count;
    return y;
}
 
node* leftRotate(node* x)
{
    node* y = x->right;
    uint32_t node_count = x->subtree_size;
    //printf("node_count:%d\n", node_count);
    uint32_t right_count = y ? y->subtree_size : 0;
    //printf("right_count:%d\n", right_count);
    uint32_t left_count = x->left ? x->left->subtree_size : 0;
    //printf("left_count:%d\n", left_count);
    uint32_t right_left_count = y ? (y->left ? y->left->subtree_size : 0) : 0;
    //printf("right_left_count:%d\n", right_left_count);
    uint32_t right_right_count = y ? (y->right ? y->right->subtree_size : 0) : 0;
    //printf("right_right_count:%d\n", right_right_count);


    x->right = y->left;
    x->subtree_size = left_count + right_left_count + x->count;
    y->left = x;
    y->subtree_size = x->subtree_size + right_right_count + y->count;
    return y;
}

void print_tree(node* root) {
    if (root == NULL) return;
    cout << "key:" << root->key << " ";
    cout << "subtree_size:" << root->subtree_size << " ";
    if (root->left) cout << "left:" << root->left->key << " ";
    if (root->right) cout << "right:" << root->right->key << " ";
    cout << endl;
    print_tree(root->left);
    print_tree(root->right);

}
 
node* splay(node* root, int poz)
{
    if (root == NULL || (get_size(root->left) < poz && poz <= get_size(root->left) + root->count)) {
        return root;
    }
    if (get_size(root->left) >= poz) {
        if (root->left == NULL) return root;
        if (get_size(root->left->left) >= poz) {
            root->left->left = splay(root->left->left, poz);
            root = rightRotate(root);
        }
        else if (get_size(root->left->left) + root->left->count < poz) {
            root->left->right = splay(root->left->right, poz - get_size(root->left->left) - root->left->count);
            if (root->left->right != NULL)
                root->left = leftRotate(root->left);
        }
        return rightRotate(root);
    }
    else {
        poz -= get_size(root->left) + root->count;
        //printf("poz: %d\n", poz);
        if (root->right == NULL) return root;
        if (get_size(root->right->left) >= poz) {
            root->right->left = splay(root->right->left, poz);
            if (root->right->left != NULL)
                root->right = rightRotate(root->right);
        }
        else if (get_size(root->right->left) + root->right->count < poz) {
            root->right->right = splay(root->right->right, poz - get_size(root->right->left) - root->right->count);
            root = leftRotate(root);
        }
        //print_tree(root);
        return leftRotate(root);
        
    }
 
    
}


 
node* insert(node* root, int key, int count, int poz)
{ //printf("key:%d count:%d poz:%d\n", key, count, poz);
    if (root == NULL)
        return newNode(key, count);

    if (poz == 0) {
        node* temp = newNode(key, count);
        temp->right = root;
        temp->subtree_size = get_size(temp->left) + get_size(temp->right) + temp->count;
        //printf("temp->subtree_size:%d\n", temp->subtree_size);
        return temp;
    }

    //poz++;

    if (poz >= root->subtree_size) {
        node* temp = newNode(key, count);
        temp->left = root;
        temp->subtree_size = get_size(temp->left) + get_size(temp->right) + temp->count;
        return temp;
    }
 
    root = splay(root, poz);
    //print_tree(root);

    if (root->key == key) {
        root->count += count;
        return root;
    }
 
    int in_leftson = poz - get_size(root->left);
    int in_rightson = root->count - in_leftson;

    root->count -= in_rightson;

    node* rightson = newNode(root->key, in_rightson);
    rightson->right = root->right;
    rightson->subtree_size = in_rightson + get_size(rightson->right);
    root->subtree_size -= in_rightson;
    root->subtree_size -= get_size(root->right);
    root->right = NULL;

    node* temp = newNode(key, count);
    temp->left = root;
    temp->right = rightson;
    temp->subtree_size = get_size(temp->left) + get_size(temp->right) + temp->count;
    return temp;
}

void print_sequence(node* root) {
    if (root == NULL) return;
    print_sequence(root->left);
    for (int i = 0; i < root->count; i++) {
        cout << root->key << " ";
    }
    print_sequence(root->right);
    
}

node* get(node* root, int poz) {
    return splay(root, poz+1);
}
 
// Drivers code
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    node* root = NULL;
    /*while (true) {
        char c;
        cin >> c;
        if (c == 'i') {
            int key, count, poz;
            cin >> key >> count >> poz;
            root = insert(root, key, count, poz);
            
        } else if (c == 'g') {
            int val;
            cin >> val;
            root = get(root, val);
            cout << "splay:" << root->key << endl;
        }
        print_tree(root);
        cout << "----------------" << endl;
        
        print_sequence(root);
        cout << "\n----------------" << endl;
    }*/

    int m; 
    cin >> m;
    int n = 0;
    int w = 0;
    for (int i = 0; i < m; i++) {
        char c;
        cin >> c;
        if (c == 'i') {
            int key, count, poz;
            cin >> poz >> key >> count;
            root = insert(root, key, count, (poz + w) % (n + 1));
            n += count;
        } else if (c == 'g') {
            // print w 
            //printf("w:%d\n", w);
            int val;
            cin >> val;
            root = get(root, (val + w) % n);
            cout << root->key << endl;
            w = root->key;
        }
        //print_sequence(root);
        //cout << "\n----------------" << endl;
    }
    return 0;
}
