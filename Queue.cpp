#include <iostream>

template<typename T>
class Queue{
public:
    struct Node{
        T data;
        Node * next;
        Node(T data, Node * next):
            data(data),
            next(next){
        }
    };

    Queue();
    Queue(const Queue& other);
    Queue& operator = (const Queue& other);
    ~Queue();
    T& front()const;
    T& back()const;
    void push(const T& elem);
    void pop();
    size_t getSize()const;
    void clear();
    void print()const;

private:
    Node * first;
    Node * last;
    size_t size;
    void copy(const Queue& other);
    void erase();
    bool isEmpty()const;

};

template<typename T>
void Queue<T> :: push(const T& elem){
    Node * temp = new Node(elem, nullptr);
    if(isEmpty()){
        this->first = temp;
        this->last = temp;
    }
    else{
        this->last->next = temp;
        this->last = temp;
    }
    this->size++;
}

template<typename T>
bool Queue<T> :: isEmpty()const{
    return this->size == 0;
}

template<typename T>
size_t Queue<T> :: getSize()const{
    return this->size;
}

template<typename T>
Queue<T> :: Queue(){
    this->first = nullptr;
    this->last = nullptr;
    this->size=0;
}

template<typename T>
void Queue<T> :: copy(const Queue& other){

    Node * temp = other.first;
    for(size_t i = 0; i < other.getSize(); i++){
        this->push(temp->data);
        temp=temp->next;
    }
}

template<typename T>
Queue<T> :: Queue(const Queue& other){
    this->copy(other);
}

template<typename T>
Queue<T>& Queue<T> :: operator = (const Queue& other){
    if(this != &other){
        this->erase();
        this->copy(other);
    }
    return *this;
}

template<typename T>
Queue<T> ::~Queue(){
    this->erase();
}

template<typename T>
void Queue<T> :: pop(){
    if(!isEmpty()){
        Node*temp = this->first;
        this->first = this->first->next;
        delete[]temp;
        size--;
    }
}

template<typename T>
void Queue<T> :: erase(){
    while(!isEmpty()){
        this->pop();
    }
}

template<typename T>
T& Queue<T> :: front()const{
    if(this->first != nullptr){
        return this->first->data;
    }
}

template<typename T>
T& Queue<T> :: back()const{
    if(this->last != nullptr){
        return this->last->data;
    }
}

template<typename T>
void Queue<T> :: clear(){
    this->erase();
    this->first = nullptr;
    this->last = nullptr;
    this->size=0;
}

template<typename T>
void Queue<T> :: print()const{
    Node * temp = this->first;
    for(size_t i = 0; i < this->size; i++){
        std::cout<<temp->data<<std::endl;
        temp = temp->next;
    }
}
int main()
{
    Queue<int> q;
    q.push(3);
    q.push(2);
    q.push(1);
    q.push(4);
    q.print();
    std::cout<<q.back()<<std::endl;
    std::cout<<q.front()<<std::endl;
    return 0;
}
