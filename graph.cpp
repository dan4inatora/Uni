#include<iostream>
#include<vector>
#include<queue>

using namespace std;

template <typename T>
struct Vertex{
	T data;
	vector<Vertex<T> > neighbours;
	bool marked;
	
	Vertex(){
	}
	
	Vertex(const T& dt, vector<Vertex<T> > nb){
		data = dt;
		neighbours = nb;
		marked = false;
	}
	
	void setMarked(){
		marked = true;
	}
};

template <typename T>
struct Edge{
	Vertex<T> first;
	Vertex<T> second;
	
	Edge(){
	}
	
	Edge(Vertex<T> ft, Vertex<T> snd){
		first = ft;
		second = snd;
	}
};


template <typename T>
class Graph
{
private:
    vector< Vertex<T> > vertices;
    vector < Edge<T> > edges;
    size_t vertices_count;
    size_t edges_count;

    void copy(const Graph<T>&);
    void empty();
  //  void addEdge(const Vertex<T>&,const Vertex<T>&);
public:
    Graph();
    Graph(const Graph&);
    Graph& operator=(const Graph&);

    void addVertex(Vertex<T>);
    void addNeighborVertex(int vertexIndex,Vertex<T>);
    int getVertexIndex(const Vertex<T>&) const;
    int getEdgeIndex(const Edge<T>&) const;
    Vertex<T> getVertex(int index) const;
    Edge<T> getEdge(int index) const;
    vector< Edge<T> > findEdgeByVertex(const Vertex<T>&);
    void removeVertex(int index);
    void removeEdge(int index);
    void addEdge(Vertex<T>&,Vertex<T>&);
    bool areConnected(Vertex<T>,Vertex<T>) const;

    
    vector< Vertex<T> > getVertices() const;
    vector< Edge<T> > getEdges() const;
    size_t get_vertices_count() const;
    size_t get_edges_count() const;

    
    void BFS();

};

template <typename T>
vector <Vertex<T> > Graph<T> :: getVertices()const{
	return this->vertices;
}

template <typename T>
vector < Edge<T> > Graph<T>::getEdges() const
{
    return this->edges;
}

template <typename T>
size_t Graph<T>::get_vertices_count() const
{
    return this->vertices_count;
}

template <typename T>
size_t Graph<T>::get_edges_count() const
{
    return this->edges_count;
}

template <typename T>
void Graph<T>::copy(const Graph<T>& graph)
{
    this->vertices = graph.getVertices();
    this->edges = graph.getEdges();
    this->vertices_count = graph.get_vertices_count();
    this->edges_count = graph.get_edges_count();
}

template <typename T>
void Graph<T>::empty()
{

    for(size_t i = 0; i < this->vertices_count; i++)
        this->vertices.pop_front();

    for(size_t i = 0; i < this->edges_count; i++)
        this->edges.pop_front();

    this->vertices_count = 0;
    this->edges_count = 0;
}

template <typename T>
Graph<T>::Graph()
{
    this->vertices_count = 0;
    this->edges_count = 0;
}

template <typename T>
Graph<T> :: Graph(const Graph& graph){
	this->copy(graph);
}

template <typename T>
Graph<T>& Graph<T>::operator=(const Graph& graph)
{
	if(*this != &graph){
		this->empty();
		this->copy(graph);
	}	
	
	return *this;
}

template <typename T>
void Graph<T>::addVertex(Vertex<T> vertex)
{
    this->vertices.push_back(vertex);
    this->vertices_count++;
}


template <typename T>
void Graph<T>::addNeighborVertex(int vertexIndex,Vertex<T> vertex){
	
	this->vertices.push_back(vertex);
	this->vertices[vertexIndex].neighbours.push_back(vertex);
	vertex.neighbours.push_back(this->vertices[vertexIndex]);
	Edge<T> newEdge = Edge<T>(this->vertices[vertexIndex],vertex);
	this->edges.push_back(newEdge);
	this->vertices_count++;
    this->edges_count++;
}

template <typename T>
void Graph<T>::addEdge(Vertex<T>& first,Vertex<T>& second){
	
	Edge<T> edge = Edge<T>(first,second);
	this->vertices[first].neighbours.push_back(second);
	this->vertices[second].neighbours.push_back(first);
	this->edges.push_back(edge);
	this->edges_count++;
	
}

template <typename T>
int Graph<T>::getVertexIndex(const Vertex<T>& vertex) const
{
    for(int i = 0; i < this->vertices_count; i++)
    {
        if(this->vertices[i] == vertex)
            return i;
    }

    return -1;
}

template <typename T>
int Graph<T>::getEdgeIndex(const Edge<T>& edge) const
{
    for(int i = 0; i < this->edges_count; i++)
    {
        if(this->edges[i] == edge)
            return i;
    }

    return -1;
}

template <typename T>
Vertex<T> Graph<T>::getVertex(int index) const
{
    return this->vertices[index];
}

template <typename T>
Edge<T> Graph<T>::getEdge(int index) const
{
    return this->edges[index];
}

template <typename T>
void Graph<T>::removeVertex(int index)
{
    
    this->vertices.erase(vertices.begin() + index);
    this->vertices_count--;
}

template <typename T>
void Graph<T>::removeEdge(int index)
{
    this->edges.erase(edges.begin() + index);
    this->edges_count--;
}

template <typename T>
vector < Edge<T> > Graph<T>::findEdgeByVertex(const Vertex<T>& vertex)
{
    vector < Edge<T> > all;
    for(int i = 0; i < this->edges_count; i++)
    {
        if(vertex == this->edges[i].first || vertex == this->edges[i].second)
        {
            all.push_back(edges[i]);
        }
    }

    return all;
}

template <typename T>
bool Graph<T>::areConnected(Vertex<T> first,Vertex<T> second) const
{
    for(size_t i = 0; i < this->edges_count; i++)
    {
        if(edges[i].first == first && edges[i].second == second)
            return true;
    }

    return false;
}

template <typename T>
void Graph<T>::BFS()
{
    if(this->vertices.size() == 0)
        return;
    queue<Vertex<T> > q;
    this->vertices[0].setMarked();
    q.push(this->vertices[0]);

    while(q.size() > 0)
    {
        cout<<"In the while"<<endl;

        Vertex<T> front = q.front();
		cout << front.data << " ";
        q.pop();

        for(size_t i = 0; i < front.neighbors.size(); i++)
        {
            cout<<"In the for"<<endl;
            if(front.neighbors[i].marked == false)
            {
                cout<<"In the if"<<endl;
                q.push(front.neighbors[i]);
                front.neighbors[i].setMarked();
            }
        }

    }
}
int main(){
	
	
	Vertex<int> c;
	Vertex<int> b;
	vector<Vertex<int> > vect1;
	vect1.push_back(b);
	vect1.push_back(c);
	Vertex<int>* v = new Vertex<int>(15,vect1);
	
	Edge<int>* ed = new Edge<int>(c,b);
	
return 0;
}
