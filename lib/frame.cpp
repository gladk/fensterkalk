/*
    This file is part of fensterkalk.
    Copyright (C) 2013 Anton Gladky <gladky.anton@gmail.com>

    Author: 2013, Anton Gladky <gladky.anton@gmail.com>

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

frame::frame(boost::shared_ptr<node> node1, boost::shared_ptr<node> node2) {
  _node1 = node1;
  _node2 = node2;
  this->calculateLength();
};

void frame::calculateLength() {
  _length = (_node1->c() - _node2->c()).norm();
};

void frame::changeNode1 (boost::shared_ptr<node> nodeT) {
  _node1 = nodeT;
  this->calculateLength();
};

void frame::changeNode2 (boost::shared_ptr<node> nodeT) {
  _node2 = nodeT;
  this->calculateLength();
};

void frame::showFrame() {
  std::cout<<_node1->c()(0)<<" "<<_node1->c()(1)<<" "<<_node1->c()(2)<<"; ";
  std::cout<<_node2->c()(0)<<" "<<_node2->c()(1)<<" "<<_node2->c()(2)<<"; ";
  std::cout<<_length<<"[mm]; angles ";
  //std::cout<< _node1->angleGRAD()/2.0 << " ";
  //std::cout<< _node2->angleGRAD()/2.0 <<std::endl;
}
