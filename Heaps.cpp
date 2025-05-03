#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

void maxHeapify(vector<int>& arr, int n, int i){
    int largest=i; // Initializing largest as root
    int left = 2*i+1;
    int right = 2*i+2;

    // If the left child is larger than root
    if (left < n && arr[left]>arr[largest]){
        largest=left;
    }

    // If the right child is larger than root
    if(right<n && arr[right]>arr[largest]){
        largest=right;
    }

    // If largest is not root
    if(largest != i){
        swap(arr[i], arr[largest]);

        // Recursively Heapify the affected sub-tree
        maxHeapify(arr,n,largest);
    }
}

// Function to perform heap sort
void heapSortAsending(vector<int>& arr){
    int n= arr.size();

    // Build max heap (rearrange array)
    for(int i=n/2 -1; i>=0; i--)
    maxHeapify(arr,n,i);

    // One by one extract an element from heap
    for(int i=n-1; i>0; i--){
        // Move current root to end 
        swap(arr[0],arr[i]);
        // call maxHeapify on the reduced heap
        maxHeapify(arr,i,0);
    }
}

void minHeapify(vector<int>& arr,int n,int i){
    int smallest=i;
    int left= 2*i+1;
    int right= 2*i+2;

    if(left<n && arr[left]<arr[smallest]){
        smallest=left;
    }

    if (right<n && arr[right]<arr[smallest]){
        smallest=right;
    }

    if (smallest!= i){
        swap(arr[i],arr[smallest]);

        minHeapify(arr,n,smallest);
    }
}

void heapSortDescending(vector<int>& arr){
    int n= arr.size();
    for (int i=n/2-1; i>=0; i--){
        minHeapify(arr,n,i);
    }

    for (int i=n-1; i>0; i--){
        swap(arr[0],arr[i]);
        minHeapify(arr,i,0);
    }
}

int main(){
    vector<int> arr;
    int n;

    cout<<"Enter the number of elements: "<<endl;
    cin>>n;

    cout<<"Enter the elements: "<<endl;
    for(int i=0; i<n; i++){
        int element;
        cin>>element;
        arr.push_back(element);
    }

    cout<<"Original Array is: "<<endl;
    for (int element: arr){
        cout<<element<<" ";
    }
    cout<<endl;

    // Sort in asending order on a copy
    vector<int> arr_asc= arr;
    heapSortAsending(arr_asc);
    cout<<"Sorted Array in asending order is: ";
    for(int element: arr_asc){
        cout<<element<<" ";
    }
    cout<<endl;

    vector<int> arr_desc= arr;
    heapSortDescending(arr_desc);
    cout<<"Sorted Array in descending order is: ";
    for(int element: arr_desc){
        cout<<element<<" ";
    }
    cout<<endl;

}