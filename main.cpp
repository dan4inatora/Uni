#include <iostream>

using namespace std;

template<typename T>

class SmartArray{
private :
    T * data;
    size_t size;
    size_t capacity;

    void erase(){
        delete[]data;
    }

    void copy(const SmartArray& other){
        this->size = other.size;
        this->capacity = other.capacity;
        this->data = new T[this->capacity];
        for(size_t i = 0; i < this->size; i++){
            this->data[i] = other.data[i];
        }
    }

    void resize(){
        if(this->size >= this->capacity){
            this->capacity *= 2;
            T * temp = new T[this->capacity];
            for(size_t i = 0; i < this->size; i++){
                temp[i] = this->data[i];
            }
            this->erase();
            this->data = temp;
        }
    }

public:
    SmartArray();
    SmartArray(const SmartArray& other);
    SmartArray& operator = (const SmartArray& other);
    ~SmartArray();
    size_t getcap()const;
    size_t getsize()const;
    void print()const;
    bool isEmpty()const;
    void clear();
    void push_back(T value);
    void pop_back();
    bool operator == (const SmartArray& other);
    void eraseat(size_t index);
    void setat(size_t index, T value);
    SmartArray operator + (const SmartArray& other);
    SmartArray& operator += (const SmartArray& other);
    T& operator [](size_t index);

    class Iterator{
        T * current;
    public:
        Iterator(T * start):
            current(start){
        }
        Iterator& operator++(int){
            this->current++;
            return *this;
        }
        bool operator == (const Iterator& other){
            return this->current == other.current;
        }
        bool operator != (const Iterator& other){
            return this->current != other.current;
        }
        T& operator * (){
            return *current;
        }
    };

    Iterator begin(){
        return Iterator(data);
    }
    Iterator end(){
        return Iterator(data + size);
    }
};
template<typename T>
SmartArray<T> :: SmartArray()
{
    this->size = 0;
    this->capacity = 4;
    this->data = new T[this->capacity];
}

template<typename T>
SmartArray<T> :: SmartArray(const SmartArray& other){
    this->copy(other);
}

template<typename T>
SmartArray<T>& SmartArray<T> :: operator = (const SmartArray& other){
    if(this != &other){
        this->erase();
        this->copy(other);
    }
    return *this;
}

template<typename T>
SmartArray<T> :: ~SmartArray(){
    this->erase();
}

template<typename T>
size_t SmartArray<T> :: getcap()const{
    return this->capacity;
}

template<typename T>
size_t SmartArray<T> :: getsize()const{
    return this->size;
}

template<typename T>
void SmartArray<T> :: print()const{
    for(size_t i = 0; i < this->size; i++){
        cout<<data[i]<<" ";
    }
}

template<typename T>
void SmartArray<T> :: push_back(T value){
    this->resize();
    this->data[size++] = value;

}

template<typename T>
void SmartArray<T> :: pop_back(){
    this->size --;
}

template<typename T>
bool SmartArray<T> :: isEmpty()const{
    return this->size == 0;
}

template<typename T>
void SmartArray<T> :: clear(){
    while(size > 0){
        this->pop_back();
    }
}

template<typename T>
bool SmartArray<T> :: operator == (const SmartArray& other){
    bool flag = true;
    if(this->size != other.size){
        return false;
    }
    else{
        for(size_t i = 0; i < this->size; i++){
            this->data[i] != other.data[i];
            flag = false;
            break;
        }
    }
    return flag;
}

template<typename T>
void SmartArray<T> :: eraseat(size_t index){
    if(index >  this->size){
        cout<<"index outta bounds"<<endl;
    }
    else{
        for(size_t i = (index - 1); i < this->size; i++){
            this->data[i] = this->data[i + 1];
        }
        this->size--;
    }
}

template<typename T>
void SmartArray<T> :: setat(size_t index, T value){
    if(index >  this->size){
        cout<<"index outta bounds"<<endl;
    }
    else{
        for(size_t i = (this->size - 1); i > index; i--){
            this->data[i + 1] = this->data[i];
        }
        this->data[index - 1] = value;
        this->size++;
    }
}

template<typename T>
T& SmartArray<T> :: operator [](size_t index){
    if(index >  this->size){
        cout<<"index outta bounds"<<endl;
    }
    else{
        return this->data[index];
    }

}

template<typename T>
SmartArray<T>  SmartArray<T> :: operator + (const SmartArray& other){
    SmartArray s;
    s.size = this->size + other.size;
    s.capacity = this->capacity + other.capacity;
    for(size_t i = 0; i < this->size; i ++){
        s.data[i] = this->data[i];
    }
    for(size_t i = 0; i < other.size; i ++){
        s.data[this->size + i] = other.data[i];
    }
    return SmartArray(s);
}

template<typename T>
SmartArray<T>&  SmartArray<T> :: operator += (const SmartArray& other){

    size_t allsize = this->size + other.size;
    size_t allcapacity = this->capacity + other.capacity;
    T * temp = new T[this->capacity];
    for(size_t i = 0; i < this->size; i ++){
        temp[i] = this->data[i];
    }
    for(size_t i = 0; i < other.size; i ++){
        temp[this->size + i] = other.data[i];
    }
    this->erase();
    this->size = allsize;
    this->capacity = allcapacity;
    this->data = temp;
    return *this;
}
int main()
{

    SmartArray<int> s;
    cout<<s.getsize()<<endl;
    s.push_back(1);
    s.push_back(1);
    s.push_back(1);
    s.push_back(3);
    s.push_back(2);
    s.push_back(4);


//    SmartArray<int> s1;
//    s1.push_back(1);
//    s1.push_back(1);
//    s1.push_back(1);
//    s1.push_back(3);
//    s1.push_back(2);
//    s1.push_back(4);
//
//    s1 += s;
//    s1.print();

    for(SmartArray<int>::Iterator i = s.begin(); i != s.end(); i++){
    std::cout << *i << " ";
    }

    return 0;
}
