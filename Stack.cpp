#include <iostream>



template <typename T>
class Stack{

public:
    struct Node{
    T data;
    Node * next;

    Node(T data, Node * next):
        data(data),
        next(next){
    }

};
    Stack();
    Stack(const Stack& other);
    Stack& operator = (const Stack& other);
    ~Stack();
    void pop();
    void push(const T& elem);
    T top()const;
    size_t getsize()const;
    void print()const;
    void clear();


private:
    Node * first;
    size_t size;
    void copy(const Stack& other);
    bool isEmpty()const;
    void empty();
    void copyReverse(const Stack& other);

};

template<typename T>
Stack<T>::Stack(){
    this->size = 0;
    this->first = nullptr;


}

template<typename T>
 void Stack <T>:: push(const T& elem){

    Node *temp = new Node(elem,this->first);
    this->first = temp;
    size++;
 }

template<typename T>
void Stack<T> :: copyReverse(const Stack& other){
    Node * temp = other.first;
    for(size_t i = 0; i < other.size; i++){
        this->push(temp->data);
        temp = temp->next;
    }
}


template<typename T>
Stack<T> :: ~Stack(){
    this->empty();
}

template<typename T>
void Stack<T> :: print()const{
    Node * temp = this->first;
    for(size_t i = 0; i < this->size; i++){
        std::cout <<temp->data;
        std::cout<<std::endl;
        temp = temp->next;
    }
}

template<typename T>
void Stack<T> :: copy(const Stack& other){
//    NOT OPTIMAL
//    Stack reversed;
//    reversed.copyReverse(other);
//    this->copyReverse(reversed);

    if(other.first == nullptr){
        this->first = nullptr;
        this->size = 0;
        return;
    }

    this->first = new Node(other.first->data, other.first->next);
    Node * temp1 = this->first;
    Node * temp2 = other.first;

    while(temp2){
        temp1->next = new Node(temp2->next->data, temp2->next->next);
        temp1 = temp1->next;
        temp2 = temp2->next;
    }

    this->size = other.size;
}

template<typename T>
Stack<T> :: Stack(const Stack& other){
    this->copy(other);
}

template<typename T>
Stack<T>& Stack<T> :: operator = (const Stack& other){
    if(this != &other){
        this->empty();
        this->copy(other);
    }
    return *this;
}

template<typename T>
bool Stack <T> :: isEmpty()const{
    return this->size == 0;
}

template<typename T>
void Stack<T> :: pop(){

    if(!this->isEmpty()){
        Node * temp = this->first;
        this->first = this->first->next;
        delete[]temp;
        size--;
    }
}

template<typename T>
void Stack<T> :: empty(){
    while(this->size > 0){
        this->pop();
    }
}

template<typename T>
void Stack<T> :: clear(){
    this->empty();
}

template<typename T>
size_t Stack<T> :: getsize()const{
    return this->size;
}

template<typename T>
T Stack<T> :: top()const{
    return this->first->data;
}

int main()
{
   Stack<int> a;
   a.push(3);
   a.push(1);
   a.push(3);
   a.push(2);
  // a.clear();
   a.print();

   Stack<int> b;
   b = a;
   b.push(8);
   b.print();

   Stack<int> c(a);
   //c.print();
    return 0;
}
