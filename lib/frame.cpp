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

#include <CGAL/create_offset_polygons_2.h>
#include <frame.h>
#include <iostream>

bool Frame::addNode(Eigen::Vector3d &&nodeT) {
  const auto nodeTMP = std::make_shared<Node>(Node(nodeT));
  // Create temporarly _nodeVector to check, whether polygon is simple
  if (_nodes.size() > 1) {
    auto nodesTMP = _nodes;
    nodesTMP.push_back(nodeTMP);
    if (not(this->checkIsSimple(nodesTMP))) {
      std::cerr << "Polygon is not simple!" << std::endl;
      return false;
    }
  }

  _nodes.push_back(nodeTMP);
  if (_nodes.size() == 3) {
    _beams.emplace_back(std::make_shared<Beam>(Beam(_nodes[0], _nodes[1])));
    _beams.emplace_back(std::make_shared<Beam>(Beam(_nodes[1], _nodes[2])));
    _beams.emplace_back(std::make_shared<Beam>(Beam(_nodes[2], _nodes[0])));
  } else if (_beams.size() > 3) {
    _beams[_beams.size() - 1]->replaceNode(nodeTMP, Side::RIGHT);
    _beams.emplace_back(
        std::make_shared<Beam>(Beam(_nodes[_nodes.size() - 1], _nodes[0])));
  }
  _calculatedFrame = false;
  calculate();
  return true;
};

void Frame::show() const {
  unsigned int i = 1;
  for (const auto &beamTMP : _beams) {
    std::cout << "Beam " << i << ": ";
    beamTMP->show();
    i++;
  }
};

bool Frame::checkBeams() const {
  for (int i = 1; i < _beams.size(); i++) {
    if (_beams[i - 1]->node(Side::RIGHT) != _beams[i]->node(Side::LEFT)) {
      return false;
    }
  }
  if (_beams[0]->node(Side::LEFT) !=
      _beams[_beams.size() - 1]->node(Side::RIGHT)) {
    return false;
  }

  return true;
};

bool Frame::checkIsSimple(
    const std::vector<std::shared_ptr<Node>> &nodes) const {
  if (not(_FrameCG.is_simple()))
    return false;
  else
    return true;
}

double Frame::widthA() const { return _widthA; }
double Frame::widthB() const { return _widthB; }
double Frame::widthC() const { return _widthC; }
double Frame::height() const { return _height; }
FrameType Frame::type() const { return _type; }

void Frame::setGeometry(double wA, double wB, double wC, double h) {
  _widthA = wA;
  _widthB = wB;
  _widthC = wC;
  _height = h;
  calculate();
}

void Frame::setType(FrameType t) { _type = t; }

std::vector<std::shared_ptr<Node>> Frame::nodes() {
  std::vector<std::shared_ptr<Node>> nodesRet = _nodes;
  return nodesRet;
}

std::vector<std::shared_ptr<Node>> Frame::nodesInternA() {
  Polygon_2CG polyA;
  nodesIntern(polyA, _widthA);
  std::vector<std::shared_ptr<Node>> nodesRet;

  for (auto vi = polyA.vertices_begin(); vi != polyA.vertices_end(); ++vi) {
    auto nodeTMP = std::shared_ptr<Node>(
        new Node(Eigen::Vector3d((*vi).x(), (*vi).y(), 0)));
    nodesRet.push_back(nodeTMP);
  }
  return nodesRet;
}

void Frame::nodesIntern(Polygon_2CG &poly, const double W) {
  const KCG::FT offset = W;
  auto inner_offset_polygons =
      CGAL::create_interior_skeleton_and_offset_polygons_2(offset, _FrameCG)[0];
  poly = *inner_offset_polygons;
}

bool Frame::calculate() {
  _FrameCG.clear();
  for (int i = 0; i < _nodes.size(); i++) {
    _FrameCG.push_back(PointCG(_nodes[i]->c()[0], _nodes[i]->c()[1]));
  }
  _calculatedFrame = true;
  return true;
}
