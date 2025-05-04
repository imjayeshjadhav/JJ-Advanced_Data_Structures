/*
Name: Jayesh Jadhav
Roll Number: 17
Batch: A1
PRN Number: 202301040019
*/

#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;
    bool lth,rth;

    Node(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
        lth=true;
        rth=true;
    }
};

Node* insert (Node* root, int data)
{
    if (root==nullptr)
    {
        root= new Node(data);
        return root;
    }
    
    Node* temp=root;
    while (true)
    {
        if (data<temp->data)
        {
            if (temp->lth)
            {
                Node* newNode= new Node(data);
                newNode->left=temp->left;
                newNode->right=temp;
                temp->left=newNode;
                temp->lth=false;
                break;
            }
            else{
                temp=temp->left;
            }    
        }
        else{
            if(temp->rth)
            {
                Node* newNode= new Node(data);
                newNode->right=temp->right;
                newNode->left=temp;
                temp->right=newNode;
                temp->rth=false;
                break;
            }
            else{
                temp=temp->right;
            }
        }
    }
    return root;
}

Node* search(Node* root, int data )
{
    if(root==nullptr)
    return 0;

    Node* temp=root;
    while (temp!=nullptr)
    {
        if(temp->data==data)
        return temp;

        if(data<temp->data)
        {
            if(!temp->lth)
            {
                temp=temp->left;
            }
            else break;
        }
        else
        {
            if(!temp->rth)
            {
                temp=temp->right;
            }
            else break;
        }
    }
    cout<<"Node not found "<<data<<endl;
    return nullptr;
}

void preorder(Node* root)
{
    if(root==NULL)
    return;

    cout<<root->data<<" ";
    if(!root->lth)
    preorder(root->left);
    if(!root->rth)
    preorder(root->right);
}

void inorder(Node* root)
{
    if(root==NULL)
    return;

    if(!root->lth)
    inorder(root->left);
    cout<<root->data<<" ";
    if(!root->rth)
    inorder(root->right);
}

void postorder(Node* root)
{
    if(root==NULL)
    return;

    if(!root->lth)
    postorder(root->left);
    if(!root->rth)
    postorder(root->right);
    cout<<root->data<<" ";
}

void NonRecursivePreOrder(Node* root) {
    if (root==nullptr){
        return;
    }
    Node* current = root;

    while (current != nullptr) {
        cout<<current->data<<" ";

        if (!current->lth) {
            current = current->left;
        } else if (!current->rth) {
            current = current->right;
        } else {
            while (current != nullptr && current->rth) {
                current = current->right;
            }
            if (current != nullptr)
                current = current->right;
        }
    }
    cout << endl;
}

void NonRecursiveInOrder(Node* root) {
    if (root == nullptr)
        return;

    Node* temp = root;
    while (!temp->lth)
        temp = temp->left;

    while (temp != nullptr) {
        cout << temp->data << " ";
        if (temp->rth)
            temp = temp->right;
        else {
            temp = temp->right;
            while (temp != nullptr && !temp->lth)
                temp = temp->left;
        }
    }
    cout << endl;
}

void NonRecursivePostOrder(Node* root) {
    if (!root) return;

    Node* stack1[100];
    Node* stack2[100];
    int top1 = -1, top2 = -1;

    stack1[++top1] = root;

    while (top1 >= 0) {
        Node* current = stack1[top1--];
        stack2[++top2] = current;

        if (!current->lth && current->left) 
            stack1[++top1] = current->left;

        if (!current->rth && current->right) 
            stack1[++top1] = current->right;
    }

    while (top2 >= 0) {
        cout << stack2[top2--]->data << " ";
    }

    cout << endl;
}


// void display(Node* root)
// {
//     if (root==nullptr)
//     cout<<"No value to display";

//     if (root!=NULL)
//     {
//         if(root->lth == false)
//         display(root->left);
        
//         cout<<root->data<<" ";
//         if(root->rth==false)
//         display(root->right);
//     } 
// }

int main()
{
    int n,ch;
    Node* root=nullptr;
    cout<<"How Many nodes do you want to insert "<<endl;
    cin>>n;

    if(n<=0)
    cout<<"Enter a valid number"<<endl;

    cout<<"Enter the nodes"<<endl;
    for(int i=0; i<n; i++)
    {
        int value;
        cin>>value;
        root=insert(root,value);
    }

    do
    {
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
        switch (ch)
        {
        case 1:
            int value;
            cout<<"Enter the value you want to search"<<endl;
            cin>>value;
            search(root,value);
            break;

        case 2:
            int data;
            cout<<"Enter the value you want to insert"<<endl;
            cin>>data;
            insert(root,data);
            break;

        case 3:
            preorder(root);
            break;

        case 4:
            inorder(root);
            break;

        case 5:
            postorder(root);
            break;

        case 6:
            NonRecursivePreOrder(root);
            break;

        case 7:
            NonRecursiveInOrder(root);
            break;

        case 8:
            NonRecursivePostOrder(root);
            break;

        default:
            cout<<"Enter a valid choice"<<endl;
            break;
        }
    } while (ch!=9);
      
}