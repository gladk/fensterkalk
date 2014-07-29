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

#include "frame.h"
#include <iostream>
#include <boost/foreach.hpp>

bool frame::addNode(Eigen::Vector3d const nodeT) {
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
    auto beamTMP1 = boost::shared_ptr<beam> (new beam(_nodes[0],_nodes[1]));
    auto beamTMP2 = boost::shared_ptr<beam> (new beam(_nodes[1],_nodes[2]));
    auto beamTMP3 = boost::shared_ptr<beam> (new beam(_nodes[2],_nodes[0]));
    _beams.push_back(beamTMP1);
    _beams.push_back(beamTMP2);
    _beams.push_back(beamTMP3);
  } else if (_beams.size() > 3) {
    _beams[_beams.size()-1]->changeNode2(nodeTMP);
    auto beamTMP(boost::shared_ptr<beam> (new beam(_nodes[_nodes.size()-1],_nodes[0])));
    _beams.push_back(beamTMP);
  }
  _calculatedFrame=false;
  return true;
};

void frame::show() const {
  unsigned int i=1;
  BOOST_FOREACH(auto beamTMP, _beams) {
    std::cout<<"Beam "<<i<<": ";
    beamTMP->show();
    i++;
  }
};

bool frame::checkBeams() const {
  for (int i = 1; i < _beams.size(); i++) {
    if (_beams[i-1]->node2() != _beams[i]->node1()) {
      return false;
    }
  }
  if (_beams[0]->node1() != _beams[_beams.size()-1]->node2()) {
    return false;
  }
  
  return true;
};


double frame::widthA() const{return _widthA;}
double frame::widthB() const{return _widthB;}
double frame::widthC() const{return _widthC;}
double frame::height() const{return _height;}
frameType frame::type() const{return _type;}

void frame::setGeometry(double wA, double wB, double wC, double h) {
  _widthA = wA;
  _widthB = wB;
  _widthC = wC;
  _height = h;
}
void frame::setType(frameType t) {_type=t;}
