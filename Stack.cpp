
template <typename U>
struct Node2
{
    U data;
    Node2<U>* next;

    Node2(const U& dt,Node2<U>* nxt = NULL)
    {
        data = dt;
        next = nxt;
    }
};

template <typename U>
class stack
{
private:
    Node2<U>* first;
    size_t counter;
public:
    stack();
    stack(const stack&);
    stack& operator=(const stack&);
    size_t size() const;
    U& top() const;
    void push(const U& element);
    void pop();
    void print()const;
    bool isEmpty() const;
    ~stack();


private:
    void copy(const stack<U>&);
    void copyReverse(const stack<U>& st);
    void empty();
    void init();


};
template <typename U>
stack<U>::stack()
{
    this->first = NULL;
    this->counter = 0;
}
template <typename U>
stack<U>::stack(const stack& st)
{
    this->init();
    this->copy(st);
}
template <typename U>
stack<U>& stack<U>::operator=(const stack& st)
{
    if(this != &st)
    {
        this->empty();
        this->init();
        this->copy(st);
    }

    return *this;
}

template <typename U>
U& stack<U>::top() const
{
    return this->first->data;
}
template <typename U>
void stack<U>::push(const U& element)
{
    Node2<U>* add = new Node2<U>(element,this->first);
    if(add)
    {
        this->first = add;
        this->counter++;
    }
}
template <typename U>
void stack<U>::pop()
{
    if(!this->isEmpty())
    {
        Node2<U>* remove = this->first;
        this->first = this->first->next;
        delete remove;
        this->counter--;
    }
}

template <typename U>
size_t stack<U>::size() const
{
    return this->counter;
}

template <typename U>
bool stack<U>::isEmpty() const
{
    return this->first == NULL;
}
template <typename U>
void stack<U>::init()
{
    this->first = NULL;
    this->counter = 0;
}
template <typename U>
void stack<U>::copyReverse(const stack<U>& st)
{

    Node2<U>* node = st.first;
    for(size_t i = 0; i < st.size(); i++)
    {
        this->push(node->data);
        node = node->next;
    }
}
template <typename U>
void stack<U>::copy(const stack<U>& st)
{

    stack<U> reverse;
    reverse.copyReverse(st);

    this->copyReverse(reverse);
}
template <typename U>
void stack<U>::empty()
{
    for(size_t i = 0; i <= this->counter; i++)
        this->pop();
}

template <typename U>
stack<U>::~stack()
{
    this->empty();
}

template <typename U>
void stack<U>:: print()const{
    Node2<U> * temp = this->first;
    for(size_t i = 0; i < this->counter; i++){
        std::cout <<temp->data;
        std::cout<<std::endl;
        temp = temp->next;
    }
}
