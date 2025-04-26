/*
Name: Jayesh Jadhav
Roll Number: 17
Batch: A1
PRN Number: 202301040019
*/

#include<iostream>
#include<stack>
#include<queue>
using namespace std;

class Node{
    public:
    int data;
    Node* left;
    Node* right;

    Node(int value)
    {
        data=value;
        left=nullptr;
        right=nullptr;
    }
};

int height(Node* root)
{
    if(root==NULL)
    return 0;

    int lh= height (root->left);
    int rh = height(root->right);

    return 1+max(lh,rh);
}

int balanceFactor(Node* root)
{
    if(root==NULL)
    return 0;

    int lh= height (root->left);
    int rh = height(root->right);

    return lh-rh;
}

Node* rightRotate(Node* y)
{
    Node* x= y->left;
    Node* t2= x->right;
    x->right=y;
    y->left=t2;
    return x;
}

Node* leftRotate(Node* x)
{
    Node* y=x->right;
    Node* t2= y->left;
    y->left=x;
    x->right=t2;
    return y;
}

Node* insert(Node* root, int value)
{

    if (!root)
        return new Node(value);

    if (value < root->data)
        root->left = insert(root->left, value);
    else if (value > root->data)
        root->right = insert(root->right, value);
    else
        return root;

    int balance = balanceFactor(root);
    if (balance > 1  && value < root->left->data){
        return rightRotate(root);
    }

    if(balance < -1 && value >root->right->data){
        return leftRotate(root);
    }

    if(balance >1 && value > root->left->data ){
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance <-1 && value < root->right->data){
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

int search(Node* root, int data) {
    if (root == nullptr) {
        return 0; 
    }

    if (root->data == data) {
        return 1; 
    } else if (data < root->data) {
        return search(root->left, data); 
    } else {
        return search(root->right, data); 
    }
}

void preorder(Node* root)
{
    if (root == NULL)
        return;

    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

void inorder(Node* root)
{
    if (root == NULL)
        return;

    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

void postorder(Node* root)
{
    if (root == NULL)
        return;

    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}

void NonRecursivePreorder(Node* root)
{
    if(root==NULL)
    {
        return ;
    }

    stack<Node*> s;
    s.push(root);
    while(!s.empty())
    {
        Node* curr=s.top(); //to get the top node
        s.pop();
        cout<<curr->data<<" ";
        if(curr->right != NULL)
        {
            s.push(curr->right);
        } 
        if(curr ->left != NULL)
        {
            s.push(curr->left);
        }
    }
}

void NonRecursiveInorder(Node* root)
{
    if (root == NULL) return;  
    stack<Node*> s;
    Node* curr = root;
    while (curr != NULL || !s.empty())  
    {
        while (curr != NULL)  
        {
            s.push(curr);
            curr = curr->left;  
        }
        curr = s.top();
        s.pop();
        cout << curr->data << " ";
        curr = curr->right;  
    }
}


void NonRecursivePostorder(Node* root)
{
    if(root==NULL) return;

    stack<Node*> s1;
    stack<Node*> s2;
    s1.push(root);
    while(!s1.empty())
    {
        Node* temp=s1.top();
        s1.pop();
        s2.push(temp);

        if(temp->left)
        s1.push(temp->left);
        if(temp->right)
        s1.push(temp->right);
    }
    while(!s2.empty())
    {
        cout<<s2.top()->data<<" ";
        s2.pop();
    }
}

int main()
{
    Node* root=nullptr;
    int n,ch;
    cout<<"How many values do you want to insert"<<endl;
    cin>>n;

    if(n<=0){
        cout<<"Please enter a valid value"<<endl;
        return 0;
    }

    for(int i=0; i<n;i++ ){
        int data;
        cin>>data;
        root= insert(root,data);
    }

    do{
        cout<<endl<<"Which action do you want to perform "<<endl;
        cout<<"1. Search the data" << endl;
        cout<<"2. Insert the data" << endl;
        cout<<"3. PreOrder Traversal (Recursive)" << endl;
        cout<<"4. InOrder Traversal (Recursive)" << endl;
        cout<<"5. PostOrder Traversal (Recursive)" << endl;
        cout<<"6. PreOrder Traversal (Non-Recursive)" << endl;
        cout<<"7. InOrder Traversal (Non-Recursive)" << endl;
        cout<<"8. PostOrder Traversal (Non-Recursive)" << endl<<endl;
        cin>>ch;
        switch(ch)
        {
            case 1:
                int num;
                cout << "Enter a number to search: ";
                cin >> num;
                if (search(root, num))
                    cout << "Data is found "<<num<< endl;
                else
                    cout << "Data not found" << endl;
                break;
            
            case 2:
                cout<<"Enter the value you want to insert"<<endl;
                int data;
                cin>>data;
                root = insert(root,data);
                cout<<"PreOrder Traversal after insertion is "<<endl;
                preorder(root);
                break;
            
            case 3:
                preorder(root);
                cout << endl;
                break;

            case 4:
                inorder(root);
                cout << endl;
                break;

            case 5:
                postorder(root);
                cout << endl;
                break;

            case 6:
                NonRecursivePreorder(root);
                cout<<endl;
                break;

            case 7:
                NonRecursiveInorder(root);
                cout<<endl;
                break;

            case 8:
                NonRecursivePostorder(root);
                cout<<endl;
                break;

        }
    }while(ch!=8);
}