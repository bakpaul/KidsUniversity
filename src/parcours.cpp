#include "parcours.h"

parcours::~parcours()
{

}

parcours::parcours(std::string)
{

}

void parcours::draw(QPainter *painter, QPaintEvent *event, long long elapsed)
{
    std::cout<<"Hey I am the parcours and the time elapsed is : "<<elapsed<<std::endl;
}
