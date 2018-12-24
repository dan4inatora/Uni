#include <iostream>

using namespace std;

template <typename T>
struct Node{
    T data;
    Node * left;
    Node * right;

    Node(const T& data, Node * left = nullptr, Node * right = nullptr):
        data(data),
        left(left),
        right(right){
    }

};

template<typename T>
class BinaryTree{

private:
    Node<T> * root;
    void Addleafprivate(T data, Node<T> * ptr);
    void Printprivate(Node<T> *ptr);
    Node<T> * ReturnNodePrivate(T data, Node<T> * ptr);
    T& findSmallestPrivate(Node<T> * ptr);
    void RemoveNodePrivate(const T& data, Node<T> *& ptr);
    void destroyTree(Node<T> * ptr);
    void NotOrderedPrintPrivate(Node<T> * ptr)const;
    Node<T> * copyNode(Node<T> * current);
    void copy(const BinaryTree& other);

public:
    BinaryTree();
    ~BinaryTree();
    BinaryTree(const BinaryTree& other);
    BinaryTree& operator = (const BinaryTree& other);
    Node<T>* createLeafe(T data);
    void Addleaf(T data);
    void Print();
    Node<T> * ReturnNode(T data);
    T returnRootKey();
    void PrintChildren(T data);
    T& findSmallest();
    void RemoveNode(const T& data);
    T max(Node<T> * val)const;
    void NotOrderedPrint()const;
};

template <typename T>
BinaryTree<T> :: BinaryTree(){
    root = nullptr;
}

template <typename T>
Node<T> * BinaryTree<T> ::createLeafe(T data){
    Node<T> * newnode = new Node<T> (data);
    return newnode;

}

template <typename T>
void BinaryTree<T> :: Addleafprivate(T data, Node<T> * ptr){
    if(this->root == nullptr){
        this->root = createLeafe(data);
    }
    else if(ptr->data > data){
        if(ptr->left != nullptr){
            Addleafprivate(data, ptr->left);
        }
        else{
            ptr->left = createLeafe(data);
        }
    }
    else if(ptr->data < data){
        if(ptr->right != nullptr){
            Addleafprivate(data, ptr->right);
        }
        else{
            ptr->right = createLeafe(data);
        }
    }
    else{
        cout<<"Data: "<< data << "has been already added"<<endl;
    }
}

template <typename T>
void BinaryTree<T> :: Addleaf(T data){
    Addleafprivate(data, this->root);
}

template <typename T>
void BinaryTree<T> :: Printprivate(Node<T> * ptr){
    if(root == nullptr){
        cout<<"The tree is empty"<<endl;
    }
    else{
        if(ptr->left != nullptr){
            Printprivate(ptr->left);
        }
        cout<<ptr->data<< " ";
        if(ptr->right != nullptr){
            Printprivate(ptr->right);
        }
    }
}

template <typename T>
void BinaryTree<T>::Print(){
    Printprivate(root);
}

template <typename T>
Node<T> * BinaryTree<T> :: ReturnNodePrivate(T data, Node<T> * ptr){
    if(ptr != nullptr){
        if(ptr->data == data){
            return ptr;
        }
        else if(ptr->data > data){
            ReturnNodePrivate(data, ptr->left);
        }
        else if(ptr->data < data){
            ReturnNodePrivate(data, ptr->right);
        }
    }
    else{
        return nullptr;
    }
}


template <typename T>
Node<T> * BinaryTree<T> :: ReturnNode(T data){
    return ReturnNodePrivate(data, root);
}

template <typename T>
T BinaryTree<T> :: returnRootKey(){
    if(root != nullptr){
        return root->data;
    }
}


template <typename T>
void BinaryTree<T> :: PrintChildren(T data){
    Node<T> * ptr = ReturnNode(data);
    if(ptr != nullptr){
        cout<< "Parent is : " << ptr->data <<endl;

        ptr->left == nullptr ? cout << "Left child is nullptr" <<endl : cout<<"Left child is: "<<ptr->left->data <<endl;
        ptr->right == nullptr ? cout << "right child is nullptr" <<endl : cout<<"right child is: "<<ptr->right->data <<endl;
    }
    else{
        cout<<"No such node in the tree Exists"<<endl;
    }
}

template <typename T>
T& BinaryTree<T> :: findSmallestPrivate(Node<T> * ptr){
    if(root != nullptr){
        if(ptr->left != nullptr){
            findSmallest(ptr->left);
        }
        else{
            return ptr->data;
        }
    }
}

template <typename T>
T& BinaryTree<T> :: findSmallest(){
    findSmallestPrivate(root);
}

template <typename T>
void BinaryTree<T> :: RemoveNode(const T& data){
    RemoveNodePrivate(data, root);
}

template <typename T>
void BinaryTree<T> :: RemoveNodePrivate(const T& data, Node<T> *& ptr){
    if(data < ptr->data){
        RemoveNodePrivate(data, ptr->left);
    }
    else if(data > ptr->data){
        RemoveNodePrivate(data, ptr->right);
    }
    else{
        if(ptr->left && ptr->right){
            ptr->data = max(ptr->left);
            RemoveNodePrivate(max(ptr->left), ptr->left);
        }
        else if(ptr->left){
            Node<T> * temp = ptr;
            ptr = ptr->left;
            delete temp;
        }
        else if(ptr->right){
            Node<T> * temp = ptr;
            ptr = ptr->right;
            delete temp;
        }
        else{
            delete ptr;
        }
    }
}

template <typename T>
T BinaryTree<T> :: max(Node<T> * val)const{

    Node<T> * temp = val;
    while(temp->right){
        temp = temp->right;
    }
    return temp->data;
}

template <typename T>
void BinaryTree<T> :: destroyTree(Node<T> * ptr){
    if(ptr){
        destroyTree(ptr->left);
        destroyTree(ptr->right);

        delete ptr;
    }
}

template <typename T>
BinaryTree<T> ::~BinaryTree(){
    destroyTree(root);
}

template <typename T>
void BinaryTree<T> :: NotOrderedPrintPrivate(Node<T> * ptr)const{
    if(ptr){
        cout<<ptr->data << " ";
        NotOrderedPrintPrivate(ptr->left);
        NotOrderedPrintPrivate(ptr->right);
    }
}

template <typename T>
void BinaryTree<T> :: NotOrderedPrint()const{
    NotOrderedPrintPrivate(root);
}


template <typename T>
Node<T> * BinaryTree<T> :: copyNode(Node<T> * current){

    if(current == nullptr) return nullptr;
    Node<T> * temp = new Node<T>(current->data, copyNode(current->left), copyNode(current->right));
    return temp;
}

template <typename T>
void BinaryTree<T> :: copy(const BinaryTree& other){
    this->root = copyNode(other.root);
}

template <typename T>
BinaryTree<T> :: BinaryTree(const BinaryTree& other){
    this->copy(other);
}

template <typename T>
BinaryTree<T>& BinaryTree<T> :: operator = (const BinaryTree& other){
    if(this != &other){
        this->destroyTree(this->root);
        this.copy(other.root);
    }
    return *this;
}
int main()
{
    int arr[13] = {50, 76, 21, 4 ,32,65,15, 52, 14, 100, 83, 2 ,3};
    BinaryTree<int> btree;
    for(int i = 0; i < 13; i++){
            btree.Addleaf(arr[i]);
    }

    btree.Print();
    cout<<endl;
    btree.PrintChildren(50);
    btree.NotOrderedPrint();
    cout<<endl;
    BinaryTree<int> copied(btree);
    copied.Print();

    return 0;
}
