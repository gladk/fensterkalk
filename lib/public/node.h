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
/** This is the node class which has two main parameters: centtal point and
 * angle  */

#include <Eigen/Dense>

class node {
public:
  node(Eigen::Vector3d c, double angle);
  node(Eigen::Vector3d c);
  node() = delete;

  Eigen::Vector3d c();       /**<  @brief Get the center (in meter)*/
  void c(Eigen::Vector3d c); /**<  @brief Set the center (in meter)*/
  double angle();            /**<  @brief Get the angle (in radians)*/
  void angle(double angle);  /**<  @brief Set the angle (in radians)*/

private:
  Eigen::Vector3d _c; /**< Center of the node (in meter)*/
  double _angle;      /**< Angle of the node (in radians)*/
};
