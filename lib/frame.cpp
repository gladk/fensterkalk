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

#include <CGAL/create_offset_polygons_2.h>

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
  calculate();
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

bool frame::checkIsSimple(const std::vector<boost::shared_ptr<node> >  & nodes) const {
  if (not(_frameCG.is_simple())) {
    return false;
  }
  return true;
}

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
  calculate();
}

void frame::setType(frameType t) {_type=t;}

std::vector<boost::shared_ptr<node> > frame::nodes() {
  std::vector<boost::shared_ptr<node> > nodesRet = _nodes;
  return nodesRet;
}

std::vector<boost::shared_ptr<node> > frame::nodesInternA() {
  Polygon_2CG polyA;
  nodesIntern(polyA, _widthA);
  std::vector<boost::shared_ptr<node> > nodesRet;
  
  for( auto vi = polyA.vertices_begin() ; vi != polyA.vertices_end() ; ++ vi ) {
    auto nodeTMP = boost::shared_ptr<node> (new node(Eigen::Vector3d((*vi).x(),(*vi).y(),0)));
    nodesRet.push_back(nodeTMP);
  }
  return nodesRet;
}

void frame::nodesIntern(Polygon_2CG & poly, const double W) {
  const KCG::FT offset = W;
  auto inner_offset_polygons = CGAL::create_interior_skeleton_and_offset_polygons_2(offset,_frameCG)[0];
  poly = *inner_offset_polygons;
}

bool frame::calculate() {
  _frameCG.clear();
  for (int i = 0; i < _nodes.size(); i++) {
    _frameCG.push_back(PointCG(_nodes[i]->c()[0],_nodes[i]->c()[1]));
  }
  _calculatedFrame=true;
  return true;
}
