/*
    This file is part of fensterkalk.
    Copyright (C) 2013 Anton Gladky <gladky.anton@gmail.com>

    Author: 2013, Anton Gladky <gladky.anton@gmail.com>

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

#include "node.h"
#include <boost/shared_ptr.hpp>

class frame {
  private:
    boost::shared_ptr<node> _node1;
    boost::shared_ptr<node> _node2;
    double _length;
    
  public:
    frame (boost::shared_ptr<node> node1, boost::shared_ptr<node> node2);
    void changeNode1 (boost::shared_ptr<node> nodeT);
    void changeNode2 (boost::shared_ptr<node> nodeT);
    void calculateLength();
    void show();
};
