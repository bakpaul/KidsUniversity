#include "parcours.h"
#include "stringException.h"

std::ostream& operator<<(std::ostream& _out,parcoursMap& _config)
{

    for(unsigned i=0;i<_config.size();i++)
    {
        for(unsigned j=0;j<_config[0].size();j++)
        {
            _out<<_config[i][j]<<"\t";
        }
        _out<<std::endl;
    }
    return _out;
}

parcours::~parcours()
{

}

parcours::parcours(std::string _fileName)
{
    configuration(_fileName);
    m_pen.push_back(QPen(Qt::black));
    m_pen.back().setWidth(3);
    m_pen.push_back(QPen(Qt::black));
    m_pen.back().setWidth(3);
    m_pen.push_back(QPen(Qt::black));
    m_pen.back().setWidth(3);
    m_pen.push_back(QPen(Qt::black));
    m_pen.back().setWidth(3);
    m_pen.push_back(QPen(Qt::black));
    m_pen.back().setWidth(3);
    m_brush.push_back(QBrush(Qt::white));
    m_brush.push_back(QBrush(QColor(20,100,150)));
    m_brush.push_back(QBrush(Qt::white));
    m_brush.push_back(QBrush(Qt::white));
    m_brush.push_back(QBrush(QColor(250,90,70)));
    m_scale = 0.95;
    m_offsetFromCenter = QPointF(0,0);
    std::cout<<"Parcours : "<<std::endl;
    std::cout<<m_map;

}


void parcours::draw(QPainter *_painter, QPaintEvent *_event, long long _elapsed)
{

    double ratio_factor_ratio = fmin(1,(((double)_event->rect().width())/(_event->rect().height()))/RATIO_FACTOR);
    double remaining_w  = _event->rect().width()-0.95*(1/3.0+1/9.0)*_event->rect().height()*ratio_factor_ratio;
    double remaining_h  = ratio_factor_ratio*0.95*_event->rect().height();
    int carreSize = std::min(remaining_w/m_map[0].size(),remaining_h/m_map.size());
    m_carreSize = carreSize;
    for(int i=0;i<m_map.size();i++)
    {
        for(int j=0;j<m_map[0].size();j++)
        {
            _painter->save();
            _painter->translate(remaining_w/2.0, _event->rect().height()/2.0);
            m_font.setPixelSize(carreSize);
            _painter->setFont(m_font);
            _painter->setPen(m_pen[m_map[i][j]]);
            _painter->setBrush(m_brush[m_map[i][j]]);
            _painter->translate((j-(m_map[0].size())/2.0)*carreSize,(i-(m_map.size())/2.0)*carreSize );
            if(!j&&!i)
            {
                m_origin.setX((j-(m_map[0].size())/2.0)*carreSize+remaining_w/2.0);
                m_origin.setY((i-(m_map.size())/2.0)*carreSize + _event->rect().height()/2.0);
            }
            _painter->drawRect(0,0,carreSize,carreSize);
            if(m_map[i][j]==2)
            {
                _painter->drawText(QRect(0,0,carreSize,carreSize), Qt::AlignCenter, "D");
            }
            else if(m_map[i][j]==3)
            {
                _painter->drawText(QRect(0,0,carreSize,carreSize), Qt::AlignCenter, "A");
            }
            _painter->restore();
        }
    }
}

void parcours::configuration(std::string _fileName)
{
    std::ifstream file;
    std::string fileName(_fileName);

    file.open(fileName);
    if(file.is_open())
    {
        file >> m_height;
        file >> m_width;
        for(unsigned i=0;i<m_height;i++)
        {
            std::vector<int> temp;
            temp.resize(m_width);
            for(unsigned j=0;j<m_width;j++)
            {
                file >> temp[j];
            }
            m_map.push_back(temp);
        }
    }
    else
    {
        throw(stringException("Parcours : Unable to open configuration file"));
    }
}
