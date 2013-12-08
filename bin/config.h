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
#define BOOST_FILESYSTEM_NO_DEPRECATED
#include <boost/filesystem.hpp> 
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

#include <iostream>
#include <string>
#include <Eigen/Dense>


class configopt {
  private:
    Eigen::Vector3d _c;                          // Center point
    std::string _FNameI;                         // Output file name of particles
    
  public:
    configopt(std::string FNameI);
    std::string FNameI() {return _FNameI;}
    void FNameI(std::string FNameI) {_FNameI=FNameI;}    
};
