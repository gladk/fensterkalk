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
  bool addNode(Eigen::Vector3d && nodeT); /**< @brief Add node to the frame */
  bool checkBeams() const; /**< @brief Check frame on its integrity */
  bool calculated() const; /**< @brief  Check whether the frame is calculated*/
  void show() const; /**< @brief  Output the main geometrical info into the
                        standard output*/
  bool calculate();  /**< @brief Calculate the frame */

  double widthA() const;  /**< @brief Return the width A*/
  double widthB() const;  /**< @brief Return the width B*/
  double widthC() const;  /**< @brief Return the width C*/
  double height() const;  /**< @brief Return the height*/
  FrameType type() const; /**< @brief Return the type of the frame*/

  void setGeometry(double wA, double wB, double wC,
                   double h); /**< @brief Set the main profile geometry*/
  void setType(FrameType t);  /**< @brief Set the frame type*/
  std::vector<std::shared_ptr<Node>>
  nodes(); /**< @brief Return the vector of nodes*/
  std::
      vector<std::shared_ptr<Node>>
      nodesInternA(); /**< @brief Return the vector of internal nodes (nodes,
                         which are creating the internal contour of the frame.
                         It should be soon replaced by the generic function.*/
  void nodesIntern(Polygon_2CG &poly,
                   const double W); /**< @brief Set the intefnal nodes*/

private:
  bool checkIsSimple(const std::vector<std::shared_ptr<Node>> &nodes)
      const;            /**< @brief  Check whether the frame is simple*/
  Polygon_2CG _FrameCG; /**< @brief CGAL structure for the polygon */
  std::vector<std::shared_ptr<Node>> _nodes; /**< @brief vector of nodes */
  std::vector<std::shared_ptr<Beam>> _beams; /**< @brief vector of beams */
  bool _calculatedFrame = false; /**< @brief is the frame calculated or not */
  double _height = 0;            /**< @brief height of the profile */
  double _widthA = 58.0;         /**< @brief width A of the profile */
  double _widthB = 0.0;          /**< @brief width B of the profile*/
  double _widthC = 0.0;          /**< @brief width C of the profile*/
  FrameType _type = FrameType::FRAME; /**< @brief Type of the frame*/
};
