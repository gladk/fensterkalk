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

/** Beam class which keeps to nodes to calculate distance between them  */

#include <memory>
#include <node.h>

enum class Side { LEFT, RIGHT };

class Beam {
public:
  Beam(std::shared_ptr<Node> nodeL, std::shared_ptr<Node> nodeR);
  /**
   * @brief Replace one of nodes by another one
   * */
  void replaceNode(std::shared_ptr<Node> nodeT, Side s = Side::LEFT);
  /**
   * @brief Calculate the distance between nodes
   * */
  void calculateLength();
  /**
   * @brief Output the information about this Beam
   * */
  void show() const;
  /**
   * @brief Get the node
   * */
  std::shared_ptr<Node> getNode(Side s = Side::LEFT) const;
  /**
   * @brief Calculate the angle and return it
   * */
  double calculateAngle(std::shared_ptr<Beam>) const;

private:
  std::shared_ptr<Node> _nodeL;
  std::shared_ptr<Node> _nodeR;
  double _length;
};
