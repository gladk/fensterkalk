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

#include "frame.h"
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polygon_2.h>

class constr {
  typedef CGAL::Exact_predicates_inexact_constructions_kernel KCG;
  typedef KCG::Point_2 PointCG;
  typedef CGAL::Polygon_2<KCG> Polygon_2CG;
  
  private:
    std::vector<boost::shared_ptr<frame> > _frames;
    std::vector<boost::shared_ptr<node> >  _nodes;
    bool _calculatedConstr;
    
  public:
    constr ();
    bool addNode(Eigen::Vector3d nodeT);
    bool checkFrames() const;
    bool checkIsSimple(const std::vector<boost::shared_ptr<node> >  & nodes) const;
    bool calculated() const;
    void show() const;
    bool calculate();
    unsigned int nodeSize() const;
    boost::shared_ptr<node> nodeGet(unsigned int i);
};
