#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class Node{
public:
    int data;
    Node* right = nullptr;
    Node* left = nullptr;

    Node(int x){
        data = x;
    }
};

class BTree{
    Node* root = nullptr;

public:

    void insert(int x){
        insert(root,x);
    }

    void showByPreorder(){
        if(root == nullptr){
            cout<<"empty! ";
            return;
        }
        showByPreorder(root);
    }

    void showByInorder(){
        if(root == nullptr){
            cout<<"empty! ";
            return;
        }
        showByInorder(root);
    }

    void showByPostorder(){
        if(root == nullptr){
            cout<<"empty! ";
            return;
        }
        showByPostorder(root);
    }

    void showByLevelorder(){
        if(root == nullptr){
            cout<<"empty! ";
            return;
        }
        showByLevelorder(root);
    }

    Node* search(int x){
        return search(root,x);
    }

    bool deleteNode(int x){
        return deleteNode(root,x);
    }

    void showDecreasing(){
        if(root == nullptr){
            cout<<"empty! ";
            return;
        }
        int result;
        int nextTarget = INT_MAX;
        while(true){
            result = inorderBefore(root,nextTarget);
            if(result != INT_MIN){
                cout<<result<<" ";
                nextTarget = result;
            }
            else break;
        }
    }

private:

    void insert(Node*& node,int x){
        if (node == nullptr) {
            node = new Node(x);
            return;
        }
        if(node->data < x){ 
            insert(node->right, x);
        }else{
            insert(node->left, x);
        }
    }

    void showByPreorder(Node* node){
        if(node == nullptr)return;
        cout<<node->data<<" ";
        showByPreorder(node->left);
        showByPreorder(node->right);
    }

    void showByInorder(Node* node){
        if(node == nullptr)return;
        showByInorder(node->left);
        cout<<node->data<<" ";
        showByInorder(node->right);
    }

    void showByPostorder(Node* node){
        if(node == nullptr)return;
        showByPostorder(node->left);
        showByPostorder(node->right);
        cout<<node->data<<" ";
    }

    void showByLevelorder(Node* node){
        int rootHeight = height(root);
        for(int i=1;i<=rootHeight;i++){
            showLevel(root,i);
        }
    }

    void showLevel(Node* node,int level){
        if(node == nullptr)return;

        if(level == 1){
            cout<<node->data<<" ";
        }
        else if(level > 1){
            showLevel(node->left,level-1);
            showLevel(node->right,level-1);
        }
    }

    int height(Node* node){
        if (node == nullptr)return 0;
        else return max(
            height(node->left),
            height(node->right)
        )+1;
    }

    Node* search(Node* node,int x){
        if(node == nullptr || node->data == x){
            return node;
        }
        if(node->data < x){
            return search(node->right,x);
        }else{
            return search(node->left,x);
        }
    }

    Node* minNode(Node* node){
        while(
            (node!= nullptr)&&
            (node->left != nullptr)
        ){
            node = node->left;
        }
        return node;
    }

    bool deleteNode(Node*& node,int x){
        if(node == nullptr)return node;

        if(node->data > x){
            return deleteNode(node->left, x);
        }
        else if(node->data < x){
            return deleteNode(node->right, x);
        }
        else{
            if(node->left == nullptr){
                Node* temp = node;
                node = node->right;
                free(temp);
                return true;
            }
            else if(node->right == nullptr){
                Node *temp = node;
                node = node->left;
                free(temp);
                return true;
            }
            Node* temp = node;
            Node* insteadNode = minNode(node->right);
            node->data = insteadNode->data;
            deleteNode(node->right,insteadNode->data);
            return true;
        }
    }

    int inorderBefore(Node* node,int x){
        int rightInorderBefore;
        int leftInorderBefore;
        if(node->right != nullptr){
            rightInorderBefore = inorderBefore(node->right,x);
            if(rightInorderBefore != INT_MIN){
                return rightInorderBefore;
            }
        }
        if(node->data < x){
            return node->data;
        }
        if(node->left != nullptr){
            leftInorderBefore = inorderBefore(node->left,x);
            if(leftInorderBefore != INT_MIN){
                return leftInorderBefore;
            }
        }
        return INT_MIN;
    }
};

void menu(BTree& bTree){
    char choose;
    cout<<"Choose one of the options :"<<endl;
    cout<<"[1] insert"<<endl;
    cout<<"[2] show by preorder"<<endl;
    cout<<"[3] show by inorder"<<endl;
    cout<<"[4] show by postorder"<<endl;
    cout<<"[5] show by level"<<endl;
    cout<<"[6] show Decreasing"<<endl;
    cout<<"[7] search"<<endl;
    cout<<"[8] delete"<<endl;
    cout<<"[0] exit"<<endl;
    cin>>choose;
    switch(choose){
        case '1':{
            int x;
            cout<<"enter a number for insert : ";
            cin>>x;
            bTree.insert(x);
            cout<<"inserted!"<<endl;
            break;
        }
        case '2':{
            cout<<"[ ";
            bTree.showByPreorder();
            cout<<"]"<<endl;
            break;
        }
        case '3':{
            cout<<"[ ";
            bTree.showByInorder();
            cout<<"]"<<endl;
            break;
        }
        case '4':{
            cout<<"[ ";
            bTree.showByPostorder();
            cout<<"]"<<endl;
            break;
        }
        case '5':{
            cout<<"[ ";
            bTree.showByLevelorder();
            cout<<"]"<<endl;
            break;
        }
        case '6':{
            cout<<"[ ";
            bTree.showDecreasing();
            cout<<"]"<<endl;
            break;
        }
        case '7':{
            int x;
            Node* result = nullptr;
            cout<<"enter a number for search : ";
            cin>>x;
            result = bTree.search(x);
            if(result == nullptr){
                cout<<"the "<<x<<" not found!"<<endl;
            }else{
                cout<<"the "<<x<<" found"<<endl;
            }
            break;
        }
        case '8':{
            int x;
            bool deleted;
            cout<<"enter a number for delete : ";
            cin>>x;
            deleted = bTree.deleteNode(x);
            if(deleted){
                cout<<"the "<<x<<" deleted"<<endl;
            }else{
                cout<<"the "<<x<<" not found!"<<endl;
            }
            break;
        }
        case '0':{
            exit(0);
        }
        default:{
            cout<<"choose a valid number [0-6]"<<endl;
        }
    }
}

int main(){
    BTree bTree = BTree();
    while(true){
        menu(bTree);
        cout<<"##################################"<<endl;
    }
    return 0; 
}