/*
    This file is part of fensterkalk.
    Copyright (C) 2013, 2014 Anton Gladky <gladky.anton@gmail.com>

    Author: 2013, 2014 Anton Gladky <gladky.anton@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Gapart is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with fensterkalk.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "constr.h"
#include <iostream>
#include <boost/foreach.hpp>

constr::constr() {
  _calculatedConstr=false;
};

bool constr::addNode(Eigen::Vector3d const nodeT) {
  auto nodeTMP = boost::shared_ptr<node> (new node(nodeT));
  
  // Create temporarly _nodeVector to check, whether polygon is simple
  if (_nodes.size()>1) {
    auto nodesTMP = _nodes;
    nodesTMP.push_back(nodeTMP);
    if (not(this->checkIsSimple(nodesTMP))) {
      std::cerr<<"Polygon is not simple!"<<std::endl;
      return false;
    }
  }
  
  _nodes.push_back(nodeTMP);
  if (_nodes.size()==3) {
    boost::shared_ptr<frame> frameTMP1, frameTMP2, frameTMP3;
    frameTMP1 = boost::shared_ptr<frame> (new frame(_nodes[0],_nodes[1]));
    frameTMP2 = boost::shared_ptr<frame> (new frame(_nodes[1],_nodes[2]));
    frameTMP3 = boost::shared_ptr<frame> (new frame(_nodes[2],_nodes[0]));
    _frames.push_back(frameTMP1);
    _frames.push_back(frameTMP2);
    _frames.push_back(frameTMP3);
  } else if (_nodes.size() > 3) {
    _frames[_frames.size()-1]->changeNode2(nodeTMP);
    auto frameTMP(boost::shared_ptr<frame> (new frame(_nodes[_nodes.size()-1],_nodes[0])));
    _frames.push_back(frameTMP);
  }
  _calculatedConstr=false;
  return true;
};

void constr::show() const {
  unsigned int i=1;
  BOOST_FOREACH(boost::shared_ptr<frame> frameTMP, _frames) {
    std::cout<<"Frame "<<i<<": ";
    frameTMP->show();
    i++;
  }
};

bool constr::checkFrames() const {
  for (int i = 1; i < _frames.size(); i++) {
    if (_frames[i-1]->node2() != _frames[i]->node1()) {
      std::cerr<<i;
      return false;
    }
  }
  if (_frames[0]->node1() != _frames[_frames.size()-1]->node2()) {
    return false;
  }
  
  return true;
};

bool constr::calculated() const{
  return _calculatedConstr;
};

bool constr::calculate() {
  for (int i = 0; i < _frames.size()-1; i++) {
    _frames[i]->node2()->angle(_frames[i]->calculateAngle(_frames[i+1]));
  }
  _frames[_frames.size()-1]->node2()->angle(_frames[_frames.size()-1]->calculateAngle(_frames[0]));
  
  if (this->checkIsSimple(_nodes)) {
    _calculatedConstr=true;
    return true;
  } else {
    _calculatedConstr=false;
    return false;
  }
};

bool constr::checkIsSimple(const std::vector<boost::shared_ptr<node> >  & nodes) const {
  Polygon_2CG _frameCG;
  for (int i = 0; i < nodes.size(); i++) {
    _frameCG.push_back(PointCG(nodes[i]->c()[0],nodes[i]->c()[1]));
  }
  
  if (not(_frameCG.is_simple())) {
    return false;
  }
  return true;
}

unsigned int constr::nodeSize() const {
  return _nodes.size();
}

boost::shared_ptr<node> constr::nodeGet(unsigned int i) {
  if (i<_nodes.size() and i>=0) {
    return _nodes[i];
  } else {
    return NULL;
  }
}
