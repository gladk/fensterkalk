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

#include "beam.h"
#include <iostream>

beam::beam(boost::shared_ptr<node> node1, boost::shared_ptr<node> node2) {
  _node1 = node1;
  _node2 = node2;
  this->calculateLength();
};

void beam::calculateLength() {
  _length = (_node1->c() - _node2->c()).norm();
};

void beam::changeNode1 (boost::shared_ptr<node> nodeT) {
  _node1 = nodeT;
  this->calculateLength();
};

void beam::changeNode2 (boost::shared_ptr<node> nodeT) {
  _node2 = nodeT;
  this->calculateLength();
};

void beam::show() {
  std::cout<<_node1->c()(0)<<" "<<_node1->c()(1)<<" "<<_node1->c()(2)<<"; ";
  std::cout<<_node2->c()(0)<<" "<<_node2->c()(1)<<" "<<_node2->c()(2)<<"; ";
  std::cout<<_length<<"[mm]; angles ";
  std::cout<< _node1->angleGRAD()/2.0 << " ";
  std::cout<< _node2->angleGRAD()/2.0 <<std::endl;
}

boost::shared_ptr<node> beam::node1() {
  return _node1;
}

boost::shared_ptr<node> beam::node2() {
  return _node2;
}

double beam::calculateAngle(boost::shared_ptr<beam> f) {
  const Eigen::Vector3d a1 = (_node2->c() - _node1->c()).normalized();
  const Eigen::Vector3d a2 = ((f->node2())->c() - (f->node1())->c()).normalized();
  return acos(a1.dot(-a2));
}
