#include <iostream>
#include <cstring>
using namespace std;

class String{

private:
    char * data;
    size_t size;
    size_t capacity;

    void copy(const String& other){
        this->capacity = other.capacity;
        this->size = other.size;
        this->data = new char[this->capacity];
        for(size_t i = 0; i < this->size; i++){
            this->data[i] = other.data[i];
        }
    }

    void erase(){
        delete[] this->data;
    }

    void resize(){
        if(this->size >= this->capacity){
            this->capacity *= 2;
        }
    }

public:
    String();
    String(const String& other);
    String& operator = (const String& other);
    String& operator = (const char * ch);
    ~String();
    size_t length()const;
    size_t getcapacity()const;
    bool isEmpty()const;
    void clear();
    char operator[](size_t index);
    String& operator += (const String& other);
    String operator + (const String& other);
    String& operator += (const char * ch);
    String operator + (const char * ch);
    void push_back(const char  s);
    void pop_back();
    void insert(size_t index, const char s);
    void deleteAt(size_t index);
    void replace(const char chr, const char rep);
    bool compare(const String& other);
    String substr(size_t start, size_t length);
    void print()const;
};

String :: String(){
    this->size = 0;
    this->capacity = 4;
    this->data = new char[this->capacity];
}

String :: String(const String& other){
    this->copy(other);
}

String& String :: operator = (const String& other){
    if(this != &other){
        this->erase();
        this->copy(other);
    }
    return *this;
}

String& String :: operator = (const char * ch){
    this->capacity = strlen(ch) * 2;
    this->size = strlen(ch);
    this->data = new char[size];
    for(size_t i = 0; i < size; i++){
        this->data[i] = ch[i];
    }
    return *this;
}

String :: ~String(){
    this->erase();
}

size_t String :: length()const{
    return this->size;
}

size_t String :: getcapacity()const{
    return this->capacity;
}

bool String :: isEmpty()const{
    return this->size == 0;
}

void String :: push_back(const char s){
    if(this->size == this->capacity){
        this->resize();
    }
    this->data[this->size++] = s;
}

void String :: pop_back(){
    this->size--;
}

void String :: clear(){
    while(this->size > 0){
        this->pop_back();
    }
}

char String :: operator[](size_t index){
    if(index < 0 || index > this->size){
        cout<<"out of bounds"<<endl;
        return 0;
    }
    else{
        return this->data[index];
    }

}

String& String :: operator += (const String& other){
    this->capacity += other.capacity;
    char* temp = new char[this->capacity];
    for(size_t i = 0; i < this->size; i++){
        temp[i] = this->data[i];
    }
    for(size_t i = 0; i < other.size; i++){
        temp[this->size + i] = other.data[i];
    }
    this->size += other.size;
    delete[] this->data;
    this->data = temp;

    return *this;
}

String& String :: operator += (const char * ch){
    this->capacity += strlen(ch);
    char* temp = new char[this->capacity];
    for(size_t i = 0; i < this->size; i++){
        temp[i] = this->data[i];
    }
    for(size_t i = 0; i < strlen(ch); i++){
        temp[this->size + i] = ch[i];
    }
    this->size += strlen(ch);
    delete[] this->data;
    this->data = temp;

    return *this;
}

String String :: operator + (const String& other){
    String str;
    str.capacity = this->capacity + other.capacity;
    str.size = this->size + other.size;
    for(size_t i = 0; i < this->size; i++){
        str.data[i] = this->data[i];
    }
    for(size_t i = 0; i < other.size; i++){
        str.data[this->size + i] = other.data[i];
    }
    return str;
}

String String :: operator + (const char * ch){
    String str;
    str.capacity = this->capacity + strlen(ch);
    str.size = this->size + strlen(ch);
    for(size_t i = 0; i < this->size; i++){
        str.data[i] = this->data[i];
    }
    for(size_t i = 0; i < strlen(ch); i++){
        str.data[this->size + i] = ch[i];
    }
    return str;
}

void String :: insert(size_t index, const char s){
    if(this->size == this->capacity){
        this->resize();
    }
    if(index < 0 || index > this->size){
        cout<<"out of bounds"<<endl;
    }
    else{
        for(size_t i = this->size - 1; i >= index; i--){
            this->data[i + 1] = this->data[i];
        }
        this->data[index] = s;
        this->size++;
    }

}
void String :: deleteAt(size_t index){
    if(index < 0 || index > this->size){
        cout<<"out of bounds"<<endl;
    }
    else{
        for(size_t i = index; i < this->size; i++){
            this->data[i] = this->data[i + 1];
        }
        this->size--;

    }
}

void String :: replace(const char chr, const char rep){
    for(size_t i = 0; i < this->size; i++){
        if(this->data[i] == chr){
            this->data[i] = rep;
        }
    }
}

bool String :: compare(const String& other){
    if(this->size != other.size){
        return false;
    }

    bool flag = true;
    for(size_t i = 0; i < this->size; i++){
        if(this->data[i] != other.data[i]){
            flag = false;
        }
    }
    return flag;
}

String String :: substr(size_t start, size_t length){

    if(start < 0 || start > size){
        cout<<"outta bounds";
        return String();
    }
    else{
       String str;
            if(length > this->size){
                return *this;
            }
            else{

                str.capacity = length * 2;
                int i = 0;
                while(length > 0){
                    str.push_back(this->data[start + i]);
                    i++;
                    length--;
                }
                return str;

        }
    }


}

void String :: print()const{
    for(size_t i = 0; i < this->size; i++){
        cout<<this->data[i];
    }
}
int main()
{
    String s;
    s.print();
    s = "dasMan und me";
    s.print();
    cout<<endl;

    String s2(s);
    s2.print();
    cout<<endl;
    s+=s;
    s.print();
    cout<<endl;
    cout<<s.compare(s) << s.compare(s2)<<endl;

    s2 += "something";
    s2.print();
    s2.pop_back();
    s2.pop_back();
    cout<<endl;
    s2.print();
    cout<<endl;

   String v;
   v = s.substr(1,2);
    v.print();

    return 0;
}
