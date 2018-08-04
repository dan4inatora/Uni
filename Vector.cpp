#include <iostream>

using namespace std;

template <typename T>

class Vector{
private:
    T * data;
    size_t size;
    size_t capacity;

    void copy(const Vector& other){
        this->size = other.size;
        this->capacity = other.capacity;
        this->data = new T[this->capacity];
        for(size_t i = 0; i < this->size; i++){
            this->data[i] = other.data[i];
        }

    }

    void erase(){
        delete this->data;
    }

    void resize(){
        if(this->size >= this->capacity){
            this->capacity *= 2;
            T* temp = new T[this->capacity];
            for(size_t i = 0; i < this->size; i++){
                temp[i] = this->data[i];
            }
            this->erase();
            this->data = temp;
        }

    }

public:
    Vector();
    ~Vector();
    Vector(const Vector& other);
    Vector& operator=(const Vector& other);
    void print()const;
    int getsize()const;
    int getcapacity()const;
    bool isEmpty()const;
    T operator[](size_t index);
    bool operator == (const Vector& other);
    void clear();
    void push_back(T data);
    void pop_back();
    void insertAtPos(size_t index, T value);
    void eraseAtPos(size_t index);


};

template <typename T>
Vector<T> :: Vector(){
    this->size = 0;
    this->capacity = 4;
    this->data = new T[this->capacity];
}

template <typename T>
Vector<T> :: ~Vector(){
    this->erase();
}

template <typename T>
Vector<T> :: Vector(const Vector& other){
    this->copy(other);
}

template <typename T>
Vector<T>& Vector<T> :: operator=(const Vector& other){
    if(this != &other){
        this->erase();
        this->copy(other);
    }

    return *this;

}
template <typename T>
void Vector<T> :: print()const{
    for(size_t i = 0; i < this->size; i++){
        cout<<"at pos "<< i + 1 << " : "<< this->data[i] <<endl;
    }
}

template <typename T>
int Vector<T> :: getsize()const{
    return this ->size;
}

template <typename T>
int Vector<T> :: getcapacity()const{
    return this ->capacity;
}

template <typename T>
bool Vector<T> :: isEmpty()const{
    return this->size == 0;
}

template <typename T>
T Vector<T> :: operator[](size_t index){
    if(index >  this->size){
        cout<<"index outta bounds"<<endl;
    }
    else{
        return this->data[index - 1];
    }

}

template <typename T>
bool Vector<T> :: operator == (const Vector& other){
    bool flag = true;
    if(this->size != other.size){
        return false;
    }
    else{
        for(int i = 0; i < this->size; i++){
            if(this->data[i] != other.data[i])
                flag = false;
        }
    }
    return flag;
}
template <typename T>
void Vector<T> :: push_back(T data){
    if(this->size == capacity){this->resize();}
    this->data[this->size++] = data;
}

template <typename T>
void Vector<T> :: pop_back(){
    this->size--;
}

template <typename T>
void Vector<T> :: clear(){
    while(this->size > 0){
        this->pop_back();
    }
}

template <typename T>
void Vector<T> :: insertAtPos(size_t index, T value){
    if(index >  this->size){
        cout<<"index outta bounds"<<endl;
    }
    else{
        if(this->size == capacity){this->resize();}
        for(size_t i = (this->size - 1); i >= index - 1; i--){
            this->data[i + 1] = this->data[i];
        }
        this->data[index - 1] = value;
        this->size++;

    }
}

template <typename T>
void Vector<T> :: eraseAtPos(size_t index){
    if(index >  this->size){
        cout<<"index outta bounds"<<endl;
    }
    else{
        for(size_t i = index - 1; i < this->size; i++){
            this->data[i] = this->data[i + 1];
        }
        this->size--;
    }
}

int main()
{
    Vector<int> v;
    v.print();
    v.push_back(12);
    v.push_back(122);
    v.push_back(121);
    v.push_back(1221);
    v.push_back(123);
    v.push_back(1223);
    v.print();

    cout<<endl;

    Vector<int> v2(v);
    Vector<int> v3;
    v3 = v;
    v2.print();
    cout<<endl;
    v3.print();
    v3.pop_back();
    cout<<endl;
    v3.print();
    v3.clear();
    cout<<endl;
    v3.print();

    cout<<v2[3]<<endl;
    v2.insertAtPos(3,1111);
    //v2.eraseAtPos(3);
    cout<<endl;
    v2.print();
    return 0;
}
