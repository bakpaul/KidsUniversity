#include "graph.h"

/**************************
 * SEED
 * ***********************/

Seed::Seed()
{

}

Seed::Seed(Graph::Id _pos)
{

}

void Seed::setId(Graph::Id _id)
{
    m_id = _id;
}

std::shared_ptr<Graph>  Seed::addElem(std::shared_ptr<Graph> _elem,Graph* _caller)
{
    if(!m_graph.count(_elem->getId()))
    {
        m_graph.emplace(std::pair<Graph::Id,std::shared_ptr<Graph>>(_elem->getId(),_elem));
        return _elem;
    }
    else
    {
        if(_caller->getType() == Graph::GraphType::Branch)
            //m_graph[_elem->getId()]->addLink(_caller->getLink[0])); //TO DO create a instance of shared pointer, not good
        return m_graph[_elem->getId()];
    }
}

/**************************
 * LEAF
 * ***********************/

Leaf::Leaf()
{
    m_type = Graph::GraphType::Leaf;
    m_links.push_back(std::shared_ptr<Graph>(new class Branch(std::shared_ptr<Graph>(this))));
}
Leaf::Leaf(std::shared_ptr<Graph> _parent,Graph::Id _id)
{
    m_type = Graph::GraphType::Leaf;
    m_links.push_back(_parent);
    m_id =_id;
}


/**************************
 * NODE
 * ***********************/

Node::Node(int _n, std::shared_ptr<Graph> _parent, Id _id)
{
    m_type = Graph::GraphType::Node;
    m_links.reserve(_n);
    m_links.push_back(_parent);
    for(int i=0;i<(_n-1);i++)
        m_links.push_back(std::shared_ptr<Graph>(new class Branch(std::shared_ptr<Graph>(this))));
    m_id =_id;
}


/**************************
 * BRANCH
 * ***********************/

Branch::Branch(std::shared_ptr<Graph> _parent)
{
    m_type = Graph::GraphType::Branch;
    m_length = 0;
    m_links.push_back(_parent);
    m_bid = Id(Graph::Id(-1,-1),_parent->getId());
}
Branch& operator++(Branch& _branch)
{
    _branch.m_length++;
    return _branch;
}
void Branch::addLink(std::shared_ptr<Graph> _graph, std::shared_ptr<Seed> _seed)
{
    m_links.push_back(_seed->addElem(_graph,this));
}
