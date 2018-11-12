#include <iostream>

template <class T>
class LinkedList{
private:
    class Node{
        public:
        T data;
        Node * next;
        Node(T value, Node * next) :
            data(value),
            next(next){
        }
        Node(T value) :
            data(value),
            next(nullptr){
        }
    };
    Node * head;
    Node * tail;
    size_t size;
    Node * goToElement(size_t index){
        if(index < 0 || index >= this->size)
        {
            std::cout<<"Index can't be smaller than 0 or bigger than list length"<<std::endl;
            return nullptr;
        }
        else
        {
            Node* current = this->head;
            for(size_t i = 0; i < index - 1; i++)
            {
                current = current->next;
            }

            return current;
        }
    }

    void copy(const LinkedList& other){
        Node * temp = other.head;
        for(size_t i = 0; i < other.size; i++){
            this->push_back(temp->data);
            temp = temp->next;
        }
    }

    void erase(){
        for(size_t i = 0; i < this->size; i++){
            this->pop_back();
        }
        this->init();
    }
public:
    class Iterator{
        Node * current;
    public:
        Iterator(Node * start):
            current(start){
        }
        Iterator& operator++(int){
            this->current = this->current->next;
            return *this;
        }
        bool operator == (const Iterator& other){
            return this->current == other.current;
        }
        bool operator != (const Iterator& other){
            return this->current != other.current;
        }
        T& operator * (){
            return current->data;
        }
    };
    LinkedList();
    LinkedList(const LinkedList<T>& other);
    LinkedList& operator = (const LinkedList<T>& other);
    ~LinkedList();
    void push_back(T value);
    void push_front(T value);
    void pop_front();
    void pop_back();
    void print()const;
    size_t getSize()const;
    void init();
    bool isEmpty() const;
    void insert(size_t index, const T& data);
    void remove(size_t index);
    void changeValueAtIndex(size_t index ,const T& value);
    LinkedList& operator += (const LinkedList<T>& other);
    LinkedList& operator + (const LinkedList<T>& other);
    T& operator[](unsigned int index);
    void reverse();
    Iterator begin(){
        return Iterator(this->head);
    }
    Iterator end(){
        return Iterator(this->tail->next);
    }
};

template <class T>
LinkedList<T> :: LinkedList():
    head(nullptr),
    tail(nullptr),
    size(0){
}

template <class T>
void LinkedList<T> :: reverse(){
    Node * current = this->head;
    Node * prev = nullptr;
    Node * next = nullptr;

    while(current != nullptr){
        next = current->next;

        current->next = prev;

        prev = current;
        current = next;
    }
    head = prev;
}

template <class T>
void LinkedList<T> :: push_back(T value){
    Node * temp = new Node(value);
    if(this->size > 0){
        this->tail->next = temp;
        this->tail = temp;
    }
    else{
        this->head = temp;
        this->tail = temp;
    }
    this->size++;
}

template <class T>
void LinkedList<T> :: pop_back(){
    Node * temp = this->head;
    Node * temp2 = this->tail;
    while(temp -> next != this->tail){
        temp = temp -> next;
    }
    this->tail = temp;
    delete [] temp2;
    this->size--;
}

template <class T>
void LinkedList<T> :: print()const{
    Node * temp = this->head;
    for(size_t i = 0; i < this->size; i++){
        std::cout << temp->data << std::endl;
        temp = temp->next;
    }
}

template <class T>
size_t LinkedList<T> :: getSize()const{
    return this->size;
}

template<class T>
void LinkedList<T> :: init(){
	this->head = nullptr;
	this->tail = nullptr;
	this->size = 0;
}

template<class T>
LinkedList<T> :: LinkedList(const LinkedList& other){
    this->init();
    this->copy(other);
}

template<class T>
LinkedList<T>& LinkedList<T> :: operator = (const LinkedList& other){
    if(this != &other){
        this->erase();
        this->copy(other);
    }
    return *this;
}

template<class T>
LinkedList<T> :: ~LinkedList(){
    this->erase();
}

template<class T>
void LinkedList<T> :: push_front(T value){
    Node * newnode = new Node(value);
    if(this->size > 0){
        Node * temp = this->head;
        this->head = newnode;
        newnode -> next = temp;
       // IF U DO NOT ADD OR ERASE SIZE U WONT GET ACCURATE PRINT(PRint works with size)
    }
    else{
        this->head = newnode;
        this->tail = newnode;
    }
    this->size++;
}

template<class T>
void LinkedList<T> ::  pop_front(){
    if(!this->isEmpty())
    {
        Node* node = this->head;
        this->head = this->head->next;
        if(this->size == 1)
        {
            this->head = nullptr;
            this->tail = nullptr;
        }

        this->size--;

        delete node;
    }
    else std::cout<<"Empty List[There is nothing to delete]"<<std::endl;
}
template<class T>
bool LinkedList<T> :: isEmpty() const{
    return this->size == 0;
}

template<class T>
void LinkedList<T> :: insert(size_t index, const T& data){
    if(!this->isEmpty())
    {
        if(index < 0 || index >= this->size)
            std::cout<<"Index can't be smaller than 0 or bigger than list length"<<std::endl;
        else if(index == 0) push_front(data);
        else if(index == this->size-1) push_back(data);
        else
        {
            Node * node = new Node (data,this->goToElement(index)->next);
            this->goToElement(index)->next = node;
        }

        this->size++;
    }
}

template<class T>
void LinkedList<T> :: remove(size_t index){
        if(!this->isEmpty())
    {
        if(index < 0 || index >= this->size)
            std::cout<<"Index can't be smaller than 0 or bigger than list length"<<std::endl;
        else if(index == 0) pop_front();
        else if(index == this->size-1) pop_back();
        else
        {
            Node *  temp = this->goToElement(index);
            this->goToElement(index - 1)->next = this->goToElement(index)->next;
            delete[] temp;

        }

        this->size--;
    }
}

template<class T>
void LinkedList<T> ::changeValueAtIndex(size_t index ,const T& value){
    this->goToElement(index)->data = value;

}

template<class T>
LinkedList<T>& LinkedList<T> :: operator += (const LinkedList<T>& other){
	Node * temp = other.head;
	while(temp != nullptr){
		this->push_back(temp->data);
		temp = temp->next;

	}
	return *this;
}

template<class T>
LinkedList<T>& LinkedList<T> :: operator + (const LinkedList<T>& other){


	LinkedList<T> * newl = new LinkedList<T>(*this);
	Node * temp = other.head;
	for(int i = 0; i < other.getNumberOfElements(); i++){
		newl->push_back(temp->data);
		temp = temp->next;
	}


	return *newl;
}

template<class T>
T& LinkedList<T> :: operator[](unsigned int index){
   return this->goToElement(index)->data;
}
int main()
{
    LinkedList<int> l;
    l.push_back(2);
    l.push_back(5);
    l.push_back(5);
    l.push_back(6);
    l.push_back(8);
    l.push_front(122);
    l.push_front(122);
    l.push_front(43);
    l.pop_front();
    l.push_front(453);
    l.pop_back();
    l.pop_front();
    l.push_front(444);
    l.push_back(8);
    l.push_front(444);
    l.insert(3,1357);
    l.pop_front();
    l.pop_front();
    l.push_front(3456);
    l.remove(5);
    l.changeValueAtIndex(2, 123);
    l.print();
    std::cout<<"size : "<<l.getSize()<<std::endl;

    LinkedList<int> l2(l);
    l2.print();

    std::cout<<std::endl;

    LinkedList<int> l3;
    l3 = l;
    l3.print();

    std::cout<<std::endl;
    std::cout<<std::endl;

    l3.reverse();
    l3.print();

    std::cout<<std::endl;
//    LinkedList<int>::Iterator i = l.begin();
//    std::cout<<*i;
//
//    LinkedList<int>::Iterator i2 = l.end();
//    std::cout<<*i2;
    for(LinkedList<int>::Iterator i = l.begin(); i != l.end(); i++){
        std::cout << *i << " ";
    }

    return 0;
}
