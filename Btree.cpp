#include <iostream>

using namespace std;


template<typename T>
struct Node{
    T data;
    Node * left;
    Node * right;
    Node(const T& data, Node * left, Node * right):
        data(data),
        left(left),
        right(right){
    }
};

template<typename T>
class Btree{

private:
    Node<T> * root;
    void addLeafprivate(const T& data, Node<T> * prt);
    void printInOrderprivate(Node<T> * ptr);
    Node<T>* returnNodeprivate(const T& data, Node<T> * ptr);
    T& findSmallestPrivate(Node<T> * ptr)const;
    void deleteNodeprivate(const T& data, Node<T> * parent);
    void RemoveRootMatch();
    void RemoveMatch(Node<T> * parent, Node<T> * match, bool left);
    void normalPrint(Node<T> * ptr)const;
    void removeSubtree(Node<T> * ptr); // removes pointer and everything below it



public:
    Btree();
    ~Btree();
    Node<T> * createNode(const T& data);
    void addLeaf(const T& data);
    Node<T> * returnNode(const T& data);
    void printInOrder();
    T& returnRootData();
    void printChildren(const T& data);
    T& findSmallest()const;
    void deleteNode(const T& data);
    void print()const;


};

template<typename T>
void Btree<T> :: removeSubtree(Node<T> * ptr){
    if(ptr != nullptr){
        if(ptr->left){
            removeSubtree(ptr->left);
        }
        if(ptr->right){
            removeSubtree(ptr-> right);
        }
        cout<<"deleting: "<< ptr->data<<endl;
        delete[] ptr;
    }
}

template<typename T>
Btree<T> :: ~Btree(){
    removeSubtree(this->root);
}


template<typename T>
void Btree<T> :: print()const{
    normalPrint(this->root);
}

template<typename T>
void Btree<T> :: normalPrint(Node<T> * ptr)const{
    if(ptr){
        normalPrint(ptr->left);

        cout<<ptr->data<<" ";

        normalPrint(ptr->right);
    }
}

template<typename T>
Btree<T> :: Btree(){
    this->root = nullptr;
}

template<typename T>
Node<T> * Btree<T> :: createNode(const T& data){
    Node<T> * temp = new Node<T>(data,nullptr,nullptr);
    return temp;
}

template<typename T>
void Btree<T> :: addLeafprivate(const T& data, Node<T> * prt){

        if(root == nullptr){
            this->root = createNode(data);
        }
        else if(prt->data > data){
            if(prt->left != nullptr){
                addLeafprivate(data,prt->left);
            }
            else{
                prt->left = createNode(data);
            }
        }
        else if(prt->data < data){
            if(prt->right != nullptr){
                addLeafprivate(data,prt->right);
            }
            else{
                prt->right = createNode(data);
            }
        }
}

template<typename T>
void Btree<T> :: addLeaf(const T& data){
    addLeafprivate(data, this->root);
}


template<typename T>
void Btree<T> :: printInOrderprivate(Node<T> * ptr){
    if(this->root != nullptr){
        if(ptr->left != nullptr){
            printInOrderprivate(ptr->left);
        }
        cout<<ptr->data<<endl;
        if(ptr->right != nullptr)
        {
            printInOrderprivate(ptr->right);
        }
    }
    else{
        cout<<"Tree is empty"<<endl;
    }
}

template<typename T>
void Btree<T> :: printInOrder(){
    printInOrderprivate(this->root);
}


template<typename T>
Node<T>* Btree<T> :: returnNodeprivate(const T& data, Node<T> * ptr){
    if(ptr != nullptr ){
        if(ptr->data == data){
            return ptr;
        }
        else{
            if(data < ptr->data){
                return returnNodeprivate(data, ptr->left);
            }
            else{
                return returnNodeprivate(data, ptr->right);
            }
        }
    }
    else{
        return nullptr;
    }
}

template<typename T>
Node<T>* Btree<T> :: returnNode(const T& data){
    return returnNodeprivate(data, this->root);
}


template<typename T>
T& Btree<T> :: returnRootData(){
    if(root != nullptr){
        return root->data;
    }

}

template<typename T>
void Btree<T> :: printChildren(const T& data){
    Node<T>* temp = returnNode(data);

    if(temp != nullptr){
        cout<<"Parent node: "<<temp->data<<endl;
        if(temp->left != nullptr){
           cout<<"Left child: "<<temp->left->data<<endl;
        }
        else{
            cout<<"No left child"<<endl;
        }

        if(temp->right != nullptr){
           cout<<"right child: "<<temp->right->data<<endl;
        }
        else{
            cout<<"No right child"<<endl;
        }
    }
    else{
        cout<<"No Node with such data"<<endl;
    }
}

template<typename T>
T& Btree<T> :: findSmallestPrivate(Node<T> * ptr)const{
    if(this->root != nullptr){
        if(ptr->left != nullptr){
            return findSmallestPrivate(ptr->left);
        }
        else{
            return ptr->data;
        }
    }

}

template<typename T>
T& Btree<T> :: findSmallest()const{
    return findSmallestPrivate(this->root);
}

template<typename T>
void Btree<T> :: deleteNodeprivate(const T& data, Node<T> * parent){
    if(root != nullptr){
        if(root->data == data){
            RemoveRootMatch();
        }
        else{
            if(data < parent->data && parent->left != nullptr){
                parent->left->data == data ? RemoveMatch(parent, parent->left, true) : deleteNodeprivate(data, parent->left);

            }
            else if(data > parent->data && parent->right != nullptr){
                 parent->right->data == data ? RemoveMatch(parent, parent->right, false) : deleteNodeprivate(data, parent->right);
            }
            else{
                cout<<"Node key not found in tree"<<endl;
            }
        }
    }
    else{
        cout<<"Tree is empty"<<endl;
    }
}


template<typename T>
void Btree<T> :: RemoveRootMatch(){
    if(root != nullptr){
        Node<T> * temp = this->root;
        T rootkey = root->data;
        T smallestInRightSubtree;

        // 0 children
        if(root->right == nullptr && root->left ==nullptr){
            this->root = nullptr;
            delete[] temp;
        }
        // one child right
        else if(root->left == nullptr && root->right != nullptr){
            root = root->right;
            temp->right = nullptr;
            delete[] temp;
             cout<<"The rootkey: "<<rootkey<<" was deleted " <<"The new root contains" <<root->data<<endl;
        }
        //one child left
        else if(root->left != nullptr && root->right == nullptr){
            root = root->left;
            temp->left = nullptr;
            delete[] temp;
            cout<<"The rootkey: "<<rootkey<<" was deleted " <<"The new root contains" <<root->data<<endl;
        }
        else{
           smallestInRightSubtree = findSmallestPrivate(root->right);
           deleteNodeprivate(smallestInRightSubtree, root);
           root->data = smallestInRightSubtree;
           cout<<"The rootkey: "<<rootkey<<" was overwriten with" << root->data<<endl;
        }
    }
    else{
        cout<<"Three s empthy"<<endl;
    }
}


template<typename T>
void Btree<T> :: RemoveMatch(Node<T> * parent, Node<T> * match, bool left){

    if(root != nullptr){
        Node<T> * temp;
        T matchkey = match->data;
        T smallestInrightTree;

        if(match->left == nullptr && match->right == nullptr){
            temp = match;
            left == true ? parent->left = nullptr : parent->right = nullptr;
            cout<<"The Node conatining "<<matchkey<<" has been removed"<<endl;
        }
        else if(match->left == nullptr && match->right != nullptr){
            left == true ? parent->left = match->right : parent->right = match->right;
            match->right = nullptr;
            temp = match;
            delete[] temp;
            cout<<"The matching: "<<matchkey<<" was removeed"<<endl;
        }
        else if(match->left != nullptr && match->right == nullptr){
            left == true ? parent->left = match->left : parent->right = match->left;
            match->left = nullptr;
            temp = match;
            delete[] temp;
            cout<<"The matching: "<<matchkey<<" was removeed"<<endl;
        }
        else{
            smallestInrightTree = findSmallestPrivate(match->right);
            deleteNodeprivate(smallestInrightTree, match);
            match->data = smallestInrightTree;
        }
    }
    else{
        cout<<"Cannot remove match, tree empty"<<endl;
    }

}

template<typename T>
void Btree<T> :: deleteNode(const T& data){
    deleteNodeprivate(data, root);
}

int main()
{
    Btree<int> b;
    int keys[] = {4, 5, 3, 6, 44, 5, 2, 78, 2, 88, 9};
    for(int i = 0; i < 11; i++){
        b.addLeaf(keys[i]);
    }

        b.print();
//    b.printInOrder();
//    b.printChildren(5);
//    cout<<b.findSmallest()<<endl;
//    b.deleteNode(4);


    return 0;
}
