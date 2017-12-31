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

#include <beam.h>
#include <iostream>

beam::beam(std::shared_ptr<node> nodeL, std::shared_ptr<node> nodeR) {
  _nodeL = nodeL;
  _nodeR = nodeR;
  this->calculateLength();
};

void beam::calculateLength() { _length = (_nodeL->c() - _nodeR->c()).norm(); };

void beam::replaceNode(std::shared_ptr<node> nodeT, Side side) {
  if (side == Side::LEFT) {
    _nodeL = nodeT;
  } else {
    _nodeR = nodeT;
  }
  this->calculateLength();
};

void beam::show() {
  std::cout << _nodeL->c()(0) << " " << _nodeL->c()(1) << " " << _nodeL->c()(2)
            << "; ";
  std::cout << _nodeR->c()(0) << " " << _nodeR->c()(1) << " " << _nodeR->c()(2)
            << "; ";
  std::cout << _length << "[mm]; angles ";
  std::cout << _nodeL->angle() * 180.0 / M_PI / 2.0 << " ";
  std::cout << _nodeR->angle() * 180.0 / M_PI / 2.0 << std::endl;
}

std::shared_ptr<node> beam::nodeL() { return _nodeL; }

std::shared_ptr<node> beam::nodeR() { return _nodeR; }

double beam::calculateAngle(std::shared_ptr<beam> f) {
  const Eigen::Vector3d a1 = (_nodeR->c() - _nodeL->c()).normalized();
  const Eigen::Vector3d a2 =
      ((f->nodeR())->c() - (f->nodeL())->c()).normalized();
  return acos(a1.dot(-a2));
}
