#include "constrGui.h"
#include <iostream>
#include <boost/foreach.hpp>

constrGui::constrGui(boost::shared_ptr<constr> c) {
  _frameGui = boost::shared_ptr<QPolygonF> (new QPolygonF());
  _frameInternAGui = boost::shared_ptr<QPolygonF> (new QPolygonF());
  
  std::vector<boost::shared_ptr<node> > nodesV = c->mainFrameNodes();
  std::vector<boost::shared_ptr<node> > nodesVInternA = c->mainFrameNodesInternA();
  
  unsigned int i=0;
  BOOST_FOREACH(const auto &nd, nodesV) {
    *_frameGui << QPointF(nd->c()[0], -nd->c()[1]);
    *_frameInternAGui << QPointF(nodesVInternA[i]->c()[0], -nodesVInternA[i]->c()[1]);
    i++;
  }
}

void constrGui::paint(QPainter * painter, 
      const QStyleOptionGraphicsItem * option, 
      QWidget * widget) {
  painter->setBrush(Qt::white);
  
  QPen* penFrame = new QPen();
  penFrame->setWidth(15.0);
  painter->setPen(*penFrame);
  
  painter->drawConvexPolygon(*_frameGui);
  painter->drawConvexPolygon(*_frameInternAGui);
}

QRectF constrGui::boundingRect() const{
  return _frameGui->boundingRect();
}
