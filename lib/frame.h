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

#include "beam.h"
#include <boost/shared_ptr.hpp>

enum frameType {FRAME, SHUTTER, MULLION, BEAD};
class frame {
  private:
    std::vector<boost::shared_ptr<node> > _nodes;
    std::vector<boost::shared_ptr<beam> > _beams;
    bool _calculatedFrame=false;
    double _height = 0;
    double _widthA=0.0, _widthB=0.0, _widthC=0.0;
    frameType _type=FRAME;
    
  public:
    frame () {};
    
    bool addNode(Eigen::Vector3d nodeT);
    bool checkBeams() const;
    bool checkIsSimple(const std::vector<boost::shared_ptr<node> >  & nodes) const;
    bool calculated() const;
    void show() const;
    bool calculate();
    
    double widthA() const;
    double widthB() const;
    double widthC() const;
    double height() const;
    frameType type() const;
    void setGeometry(double wA, double wB, double wC, double h);
    void setType(frameType t);
    std::vector<boost::shared_ptr<node> > nodes();
};
