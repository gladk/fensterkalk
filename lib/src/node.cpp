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

#include <iostream>
#include <node.h>

node::node(Eigen::Vector3d c, double angle) : _c(c), _angle(angle){};

node::node(Eigen::Vector3d c) : _c(c), _angle(-1){};

Eigen::Vector3d node::c() { return _c; };

void node::c(Eigen::Vector3d c) { _c = c; };

void node::angle(double angle) { _angle = angle; };

double node::angle() { return _angle; };