#include "constrGui.h"
#include <boost/foreach.hpp>
#include <iostream>

constrGui::constrGui(std::shared_ptr<Constr> c) {
  _frameGui = std::shared_ptr<QPolygonF>(new QPolygonF());
  _frameInternAGui = std::shared_ptr<QPolygonF>(new QPolygonF());

  std::vector<std::shared_ptr<Node>> nodesV = c->mainFrameNodes();
  std::vector<std::shared_ptr<Node>> nodesVInternA =
      c->mainFrameNodesInternA();

  unsigned int i = 0;
  BOOST_FOREACH (const auto &nd, nodesV) {
    const QPointF p1 = QPointF(nd->c()[0], -nd->c()[1]);
    const QPointF p2 =
        QPointF(nodesVInternA[i]->c()[0], -nodesVInternA[i]->c()[1]);
    *_frameGui << p1;
    *_frameInternAGui << p2;
    _frameInternASeal.push_back(QLineF(p1, p2));
    i++;
  }
}

void constrGui::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                      QWidget *widget) {
  painter->setBrush(Qt::white);

  QPen *penFrame = new QPen();
  penFrame->setWidth(10.0);
  painter->setPen(*penFrame);

  painter->drawConvexPolygon(*_frameGui);
  painter->drawConvexPolygon(*_frameInternAGui);
  painter->drawLines(_frameInternASeal);
}

QRectF constrGui::boundingRect() const { return _frameGui->boundingRect(); }
