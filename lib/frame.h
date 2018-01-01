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
/** Frame class contains the frame relevant parameters */

#include <beam.h>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polygon_2.h>

enum class FrameType { FRAME, SHUTTER, MULLION, BEAD };
class Frame {
  using KCG = CGAL::Exact_predicates_inexact_constructions_kernel;
  using PointCG = KCG::Point_2;
  using Polygon_2CG = CGAL::Polygon_2<KCG>;

public:
  Frame(){};
  bool addNode(Eigen::Vector3d nodeT);
  bool checkBeams() const;
  bool checkIsSimple(const std::vector<std::shared_ptr<Node>> &nodes) const;
  bool calculated() const;
  void show() const;
  bool calculate();

  double widthA() const;
  double widthB() const;
  double widthC() const;
  double height() const;
  FrameType type() const;

  void setGeometry(double wA, double wB, double wC, double h);
  void setType(FrameType t);
  std::vector<std::shared_ptr<Node>> nodes();
  std::vector<std::shared_ptr<Node>> nodesInternA();
  void nodesIntern(Polygon_2CG &poly, const double W);

private:
  Polygon_2CG _FrameCG;  /**<  CGAL structure for the polygon */
  std::vector<std::shared_ptr<Node>> _nodes; /**<  vector of nodes */
  std::vector<std::shared_ptr<Beam>> _beams; /**<  vector of beams */
  bool _calculatedFrame = false;  /**<  is the frame calculated or not */
  double _height = 0;
  double _widthA = 58.0;
  double _widthB = 0.0;
  double _widthC = 0.0;
  FrameType _type = FrameType::FRAME;
};
