#include <iostream>

using namespace std;

bool fexists(const std::string& filename) {
  ifstream ifile(filename.c_str());
  return (bool)ifile;
}

template <typename T>
struct Node
{
    T data;
    Node<T>* next;

    Node(const T& dt,Node<T>* nxt = NULL)
    {
        data = dt;
        next = nxt;
    }

};
template <typename T>
class queue
{

private:
    Node<T>* first;
    Node<T>* last;
    size_t counter;

public:
    queue();
    queue(const queue&);
    queue& operator=(const queue&);
    void push(const T&);
    void pop();
    T front() const;
    T end() const;
    size_t size() const;
    void print()const;
    bool isEmpty() const;


private:
    void copy(const queue&);
    void init();
    void empty();

};

template <typename T>
void queue<T>:: print()const{
        Node<T> * temp = this->first;
    for(size_t i = 0; i < this->counter; i++){
        std::cout<<temp->data<<std::endl;
        temp = temp->next;
    }
}

template <typename T>
queue<T>::queue()
{
    this->init();
}
template <typename T>
queue<T>::queue(const queue& q)
{
    this->init();
    this->copy(q);
}

template <typename T>
queue<T>& queue<T>::operator=(const queue& q)
{
    if(this != &q)
    {
        this->empty();
        this->init();
        this->copy(q);
    }

    return *this;
}
template <typename T>
void queue<T>::push(const T& data)
{
    Node<T>* add = new Node<T>(data,NULL);
    if(add)
    {
        if(this->isEmpty())
        {
            this->first = add;
        }
        else
        {
            this->last->next = add;
        }

        this->last = add;
        this->counter++;
    }
}
template <typename T>
void queue<T>::pop()
{
    if(!this->isEmpty())
    {
        Node<T>* remove = this->first;
        if(remove)
        {
            if(this->size() == 1)
            {
                this->init();
            }
            else
            {
            this->first = this->first->next;
            delete remove;
            this->counter--;
            }
        }
    }else cout<<"Empty queue"<<endl;
}
template <typename T>
T queue<T>::front() const
{
    if(!this->isEmpty())
    return this->first->data;

    else return 0;
}
template <typename T>
T queue<T>::end() const
{
    if(!this->isEmpty())
    return this->last->data;

    else return 0;
}
template <typename T>
size_t queue<T>::size() const
{
    return this->counter;
}

template <typename T>
bool queue<T>::isEmpty() const
{
    return this->counter == 0;
}
template <typename T>
void queue<T>::copy(const queue& q)
{

    Node<T>* node = q.first;
    for(size_t i = 0; i < q.size(); i++)
    {
        this->push(node->data);
        node = node->next;
    }
}
template <typename T>
void queue<T>::init()
{
    this->first = NULL;
    this->last = NULL;
    this->counter = 0;
}
template <typename T>
void queue<T>::empty()
{
    for(size_t i = 0; i < this->size(); i++)
        this->pop();
}
