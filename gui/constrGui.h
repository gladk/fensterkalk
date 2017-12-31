#pragma once

#include <QApplication>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QLineF>
#include <QWidget>
#include <QtGui>

#include <constr.h>

class constrGui : public QGraphicsItem {
public:
  // constrGui(QGraphicsItem* parent=NULL) {};
  constrGui(std::shared_ptr<Constr> c);

protected:
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget = 0);
  QRectF boundingRect() const;
  std::shared_ptr<QPolygonF> _frameGui;
  std::shared_ptr<QPolygonF> _frameInternAGui;
  QVector<QLineF> _frameInternASeal;
};
