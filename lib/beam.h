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
  void replaceNode(
      std::shared_ptr<Node> nodeT,
      Side s = Side::LEFT); /**<  @brief Replace one of nodes by another one*/
  void calculateLength();   /**<  @brief Calculate the distance between nodes*/
  void show() const;        /**<  @brief Output the information about the main
                               parameters of this beam*/
  std::shared_ptr<Node> node(Side s = Side::LEFT) const; /**<  @brief Get the
                                                            node of the side
                                                            (Side::LEFT - by
                                                            default or
                                                            Side::RIGHT)*/
  double calculateAngle(std::shared_ptr<Beam>)
      const; /**<  @brief Calculate the angle and return it*/

private:
  std::shared_ptr<Node> _nodeL; /**<  @brief ptr on left node */
  std::shared_ptr<Node> _nodeR; /**<  @brief ptr on right node */
  double _length; /**<  @brief Calculated length of the node (meter) */
};
