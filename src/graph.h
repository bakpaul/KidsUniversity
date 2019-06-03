#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include <memory>
#include <QPoint>
#include <map>

class Graph
{
public:
    typedef std::pair<int,int> Id;
    Graph(){}
    virtual ~Graph(){}

    enum GraphType
    {
        Branch,
        Node,
        Leaf
    };

    virtual GraphType getType(){ return m_type;}
    virtual Id getId(){return m_id;}
    virtual void addLink(std::shared_ptr<Graph> _link)
    {
        m_links.push_back(_link);
    };

protected:
    std::vector<std::shared_ptr<Graph> > m_links;
    GraphType m_type;
    Graph::Id m_id;

};

class Leaf : public Graph
{
public:
    Leaf();
    Leaf(std::shared_ptr<Graph> _parent, Id _id);

};

class Seed : public Leaf
{
public:
    Seed();
    Seed(Graph::Id);
    std::shared_ptr<Graph> addElem(std::shared_ptr<Graph>, Graph *_caller);
    void setId(Graph::Id);
protected:
    std::map<Graph::Id,std::shared_ptr<Graph>> m_graph;
};

class Node : public Graph
{
public:
    Node(int _n, std::shared_ptr<Graph> _parent, Graph::Id _id);

};

class Branch : public Graph
{
public:
    typedef std::pair<Graph::Id,Graph::Id> Id;

    Branch(std::shared_ptr<Graph>);
    friend Branch& operator++(Branch& _branch);
    void addLink(std::shared_ptr<Graph>, std::shared_ptr<Seed> _seed);

private:
    int m_length;
    Id m_bid;
};

#endif // GRAPH_H
