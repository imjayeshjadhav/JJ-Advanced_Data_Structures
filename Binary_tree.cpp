/*
Name: Jayesh Jadhav
Roll Number: 17
Batch: A1
PRN Number: 202301040019
*/
#include <iostream>
#include<stack>
#include<queue>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

Node* insert(Node* root, int data) {
    if (root == nullptr) {
        return new Node(data);
    }

    if (data <= root->data) {
        root->left = insert(root->left, data);
    } else {
        root->right = insert(root->right, data);
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

void display(Node* root)
{
    if (root == nullptr) {
        return;
    }

    display(root->left);
    cout << root->data<<" ";
    display(root->right);
}

int maxDepth(Node* root)
{
    if (root == NULL) {
        return 0;
    }
    int lh = maxDepth(root->left);
    int rh = maxDepth(root->right);
    return 1 + (lh > rh ? lh : rh);
}

Node* del(Node* root,int value)
{
    if (root==nullptr){
        cout<<"No node to delete"<<endl;
        return  NULL;
    } 

    //case 1: if node is a leaf node
    if(value<root->data)
    {
        root->left = del(root->left,value);
    }
    else if(value>root->data)
    {
        root->right= del(root->right,value);
    }
    else
    {
        if (root->left==nullptr && root->right==nullptr)
        {
            delete root;
            return nullptr;
        }
        // case 2: if node has only one child
        else if(root->left==nullptr)
        {
            Node* temp=root->right;
            delete root;
            return temp;
        }
        else if(root->right==nullptr)
        {
            Node* temp=root->left;
            delete root;
            return temp;
        }
        // case 3: If node has two childrens
        Node* temp=root->right;
        while(temp->left != nullptr)
        {
            temp=temp->left;
        }
        root->data=temp->data;
        root->right=del(root->right,temp->data);
    }
    return root;
}

int maxHeight(Node* root)
{
    if(root== NULL)
    return 0 ;

    int lh = maxHeight(root->left);
    int rh = maxHeight(root->right);

    return 1+ (lh<rh ? rh :lh);
}

void BFS (Node* root)
{
    if(root==NULL)
    cout<<"Tree is empty"<<endl;

    queue <Node*> q;
    q.push(root);
    while(!q.empty())
    {
        Node* temp=q.front();
        q.pop();

        cout<<temp->data<<" ";
        if (temp->left != NULL)
        q.push(temp->left);

        if(temp->right != NULL)
        q.push(temp->right);
    }
}

int main() {
    int n, ch;
    Node* root=nullptr;
     cout << "How many nodes do you want to insert: ";
     cin >> n;
    
     if (n <= 0) {
         cout << "Node inserted is invalid" << endl;
         return 0;
     }

     cout<<"Enter the nodes"<<endl;
     for (int i = 0; i < n; i++) {
         int value;      
         cin >> value;
         root = insert(root, value);
    }

    // Node* root = new Node(1);
    // root->left = new Node(2);
    // root->right = new Node(3);
    // root->left->left = new Node(4);
    // root->left->right = new Node(5);
    // root->right->left=new Node(6);
    // root->right->right=new Node(7);
    
    do {
        cout<<"Enter which action do you want to perform:" << endl;
        cout<<"1. Search the data" << endl;
        cout<<"2. Insert the data" << endl;
        cout<<"3. PreOrder Traversal (Recursive)" << endl;
        cout<<"4. InOrder Traversal (Recursive)" << endl;
        cout<<"5. PostOrder Traversal (Recursive)" << endl;
        cout<<"6. PreOrder Traversal (Non-recursive)" << endl;
        cout<<"7. InOrder Traversal (Non-Recursive)"<< endl;
        cout<<"8. PostOrder Traversal (Non-Recursive)" << endl;
        cout<<"9. Breadth First Search/ Level Order Printing"<<endl;
        cout<<"10. Height/Depth of the binary tree" << endl;
        cout<<"11. Delete the particular node"<<endl;
        cout<<"12. Exit" << endl;
        cin >> ch;
        switch (ch)
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
                int data;
                cout<<"Enter the data you want to insert ";
                cin>>data;
                root=insert(root,data);
                cout<<"Data is insertd "<<endl;
                display(root);
                cout<<endl;
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

            case 9:
                cout<<"Breadth First Search/ Level Order Printing of the tree is "<<endl;
                BFS(root);
                cout<<endl;
                break;

            case 10:
                cout << "The Depth or Height of the binary tree is " << maxDepth(root) << endl;
                break;

            case 11:
                int value;
                cout<<"Enter the value you want to delete "<<endl;
                cin>>value;
                root=del(root,value);
                cout<<"Data is deleted "<<endl;
                display(root);
                break;

            case 12:
                cout << "Exiting..." << endl;
                break;

            default:
                cout << "Invalid choice, please try again" << endl;
                break;
        }
    } while (ch != 12);
    
    return 0;
}
