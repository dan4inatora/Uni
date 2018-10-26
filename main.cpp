#include <iostream>
#include <cassert>
template<typename T>
struct Node{
    T data;
    Node * next;
    Node * prev;
    Node(const T& data, Node* next, Node* prev):
        data(data),
        next(next),
        prev(prev){
    }
};
template<typename T>
class DoubleLinkedList;

template<typename T>
class DLLIterator{
private:

    Node<T> * currel;

public:
    DLLIterator(Node<T> * currel);
    T& operator * ();
    DLLIterator& operator ++ (int);
    DLLIterator& operator -- (int);
    bool operator != (const DLLIterator& other);



};

template<typename T>
class DoubleLinkedList{
public:
    DoubleLinkedList();
    DoubleLinkedList(const DoubleLinkedList& other);
    DoubleLinkedList& operator = (const DoubleLinkedList& other);
    ~DoubleLinkedList();
    void push_back(const T& elem);
    void push_front(const T& elem);
    void pop_back();
    void pop_front();
    size_t getSize()const;
    bool isEmpty()const;
    T& top()const;
    T& bottom()const;
    T& operator [](int index);
    void pushAt(const T& el, size_t index);
    void popAt(size_t index);
    void print()const;
    DLLIterator<T> begin();
    DLLIterator<T> end();
    void reverse();
    friend class DLLIterator<T>;
    void map(void(*func)(T&));




private:
    Node<T>* first;
    Node<T>* last;
    size_t size;
    void copy(const DoubleLinkedList& other);
    void erase();

};

template<typename T>
DLLIterator<T>::DLLIterator(Node<T> * currel):
    currel(currel){
}

template<typename T>
T& DLLIterator<T>:: operator * (){
    assert (currel != nullptr);
    return this->currel->data;
}

template<typename T>
DLLIterator<T>& DLLIterator<T>::operator ++ (int){
    assert (currel != nullptr);
    this->currel = this->currel->next;
    return *this;
}

template<typename T>
DLLIterator<T>& DLLIterator<T>::operator -- (int){
    if (currel != nullptr){
          this->currel = this->currel->prev;

    }

    return *this;

}

template<typename T>
bool DLLIterator<T> :: operator != (const DLLIterator& other){
    return this->currel != other.currel;
}



template<typename T>
DoubleLinkedList<T> :: DoubleLinkedList(){
    this->first = nullptr;
    this->last = nullptr;
    this->size = 0;
}

template<typename T>
void DoubleLinkedList<T> :: push_back(const T& elem){
    Node<T>* temp = new Node<T>(elem, nullptr, nullptr);
    if(this->size == 0){
        this->first = temp;
        this->last = temp;
    }
    else{
        this->last->next = temp;
        temp->prev = this->last;
        this->last = temp;
    }
    this->size++;
}

template<typename T>
void DoubleLinkedList<T> :: push_front(const T& elem){
    Node<T>* temp = new Node<T>(elem, nullptr, nullptr);
    if(this->size == 0){
        this->first = temp;
        this->last = temp;
    }
    else{
        this->first->prev = temp;
        temp->next = first;
        this->first = temp;
    }
    this->size++;
}

template<typename T>
void DoubleLinkedList<T> :: pop_back(){
    Node<T> * temp = this->last;
    delete[]this->last;
    this->last = temp->prev;
    this->last->next = nullptr;
    this->size--;
    if(this->last == nullptr){
        first = nullptr;
    }
}

template<typename T>
void DoubleLinkedList<T> :: pop_front(){
    Node<T> * temp = this->first->next;
    delete[]this->first;
    this->first = temp;
    this->size--;
    if(this->first == nullptr){
        this->last = nullptr;
    }

}

template<typename T>
void DoubleLinkedList<T> :: print()const{
    Node<T> * temp = this->first;
    while(temp != nullptr){
        std::cout<<temp->data<<std::endl;
        temp = temp->next;
    }
}

template<typename T>
void DoubleLinkedList<T> :: erase(){
  Node<T> *next;
  while (first != nullptr)
  {
    next = first->next;
    delete first;
    first = next;
  }

  size = 0;
  last = nullptr;
}


template<typename T>
DoubleLinkedList<T> :: ~DoubleLinkedList(){
    this->erase();
}


template<typename T>
size_t DoubleLinkedList<T> :: getSize()const{
    return this->size;
}

template<typename T>
T& DoubleLinkedList<T> :: top()const{
    return this->last->data;
}

template<typename T>
T& DoubleLinkedList<T> :: bottom()const{
    return this->first->data;
}

template<typename T>
bool DoubleLinkedList<T> :: isEmpty()const{
    return this->size == 0;
}

template<typename T>
void DoubleLinkedList<T> :: copy(const DoubleLinkedList& other){
  if (other.first == nullptr)
  {
    first = nullptr;
    last = nullptr;
    return;
  }
  this->first = new Node<T> (other.first->data,nullptr,nullptr);

  Node<T> *lastcreated = first;
  Node<T> *nexttocopy = other.first->next;

  while (nexttocopy != nullptr)
  {
    lastcreated->next = new Node<T> (nexttocopy->data,nullptr,lastcreated);
    lastcreated = lastcreated->next;
    nexttocopy = nexttocopy->next;
  }

  this->size = other.size;
  last = lastcreated;
}

template<typename T>
DoubleLinkedList<T> :: DoubleLinkedList(const DoubleLinkedList& other){
    this->copy(other);
}

template<typename T>
DoubleLinkedList<T>& DoubleLinkedList<T> :: operator = (const DoubleLinkedList& other){
    if(this != &other){
        this->erase();
        this->copy(other);
    }
    return *this;
}

template<typename T>
T& DoubleLinkedList<T> :: operator [](int index){
    Node<T> * temp = this->first;
    while(index > 0){
        temp = temp->next;
        index--;
    }
    return temp->data;
}

template<typename T>
DLLIterator<T> DoubleLinkedList<T> :: begin(){
    return DLLIterator<T>(this->first);
}

template<typename T>
DLLIterator<T> DoubleLinkedList<T> :: end(){
    return DLLIterator<T>(this->last->next);
}

template<typename T>
void DoubleLinkedList<T> :: pushAt(const T& el, size_t index){
    Node<T> * temp = this->first;
    if(index == 0){
        this->push_front(el);
    }
    else if(index == this->size){
        this->push_back(el);
    }
    else{
        for(size_t i = 1; i < index; i++){
            temp = temp->next;

        }
        Node<T> * temp2 = new Node<T>(el,temp->next,temp);
        temp->next->prev = temp2;
        temp->next = temp2;
        this->size++;
    }


}

template<typename T>
void DoubleLinkedList<T> :: popAt(size_t index){
    Node<T> * temp = this->first;
    if(index == 0){
        this->pop_front();
    }
    else if(index == this->size - 1){
        this->pop_back();
    }
    else{
        for(size_t i = 0; i < index; i++){
            temp = temp->next;

        }
        Node<T> * temp2 = temp->prev;
        Node<T> * temp3 = temp->next;
        delete[]temp;
        temp2->next = temp3;
        temp3->prev = temp2;
        size--;
    }

}


template<typename T>
void DoubleLinkedList<T> :: reverse(){
        Node<T> *ptr = this->first;
        while (ptr != NULL) {
        Node<T> *tmp = ptr->next;
        ptr->next = ptr->prev;
        ptr->prev = tmp;
        if (tmp == NULL) {
            this->last = this->first;
            this->first = ptr;
        }
        ptr = tmp;
    }

}
//OTTUKA NADOLU

template<typename T>
void DoubleLinkedList<T> :: map(void(*func)(T&)){
    Node<T> * temp = this->first;
    for(size_t i = 0; i < this->size; i++){
        func(temp->data);
        temp = temp->next;
    }
}


template<typename T>
void functionadd(T& sth){
    sth = sth + 1;
}
int main()
{
    DoubleLinkedList<int> l;
    l.push_front(2);
    l.push_back(3);
    l.push_front(4);
    l.push_back(6);
    l.pop_front();
    l.pop_front();
    l.push_back(8);
    l.push_front(9);
    l.pushAt(908,4);
    l.pushAt(901,4);
    l.pushAt(902,4);
    l.popAt(6);
    //l.popAt(0);
//    l.pushAt(901,4);
//    l.pushAt(903,4);
//    l.pushAt(9099,4);
//    l.popAt(2);
    l.map(functionadd);
    l.print();

    //l.reverse();
    //std::cout<<std::endl;
   // l.print();

//    std::cout<<std::endl;
//    DoubleLinkedList<int> l2(l);
//    l2.print();
//    std::cout<<std::endl;
//    DoubleLinkedList<int> l3;
//    l3 = l2;
//    l3.print();
//
//    std::cout<<std::endl;
//    std::cout<<l[1];
//    std::cout<<std::endl;
//    std::cout<<std::endl;
//
//    DLLIterator<int> i = l.begin();
//    std::cout << *i;
//    i++;
//    std::cout << *i;
//    i--;
//    std::cout << *i;
//
//    std::cout<<std::endl;
//    std::cout<<std::endl;
//
//    for(DLLIterator<int> i = l.begin(); i != l.end(); i++){
//        std::cout<<*i<<std::endl;
//    }




    return 0;
}
