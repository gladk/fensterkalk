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

#pragma once

#include <memory>
#include <node.h>

enum class Side { LEFT, RIGHT };

class beam {
public:
  beam(std::shared_ptr<node> nodeL, std::shared_ptr<node> nodeR);
  void replaceNode(std::shared_ptr<node> nodeT, Side s = Side::LEFT);
  void calculateLength();
  void show();
  std::shared_ptr<node> nodeL();
  std::shared_ptr<node> nodeR();
  double calculateAngle(std::shared_ptr<beam> b);

private:
  std::shared_ptr<node> _nodeL;
  std::shared_ptr<node> _nodeR;
  double _length;
};
