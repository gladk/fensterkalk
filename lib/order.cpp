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

#include "order.h"
#include <boost/foreach.hpp>

order::order() {
};

boost::shared_ptr<constr> order::addConstr() {
  boost::shared_ptr<constr> constrTMP = 
    boost::shared_ptr<constr> (new constr());
  _constr.push_back(constrTMP);
  return constrTMP;
};

bool order::addConstr(boost::shared_ptr<constr> constrTMP) {
  _constr.push_back(constrTMP);
  return true;
};

bool order::calculate() {
  BOOST_FOREACH(boost::shared_ptr<constr> constrTmp, _constr) {
    if (not(constrTmp->calculated())){
      constrTmp->calculate();
    }
  }
};

void order::show() {
  unsigned int i=1;
  BOOST_FOREACH(boost::shared_ptr<constr> constrTmp, _constr) {
    std::cout<<"==================="<<std::endl<<"Construction "<<i<<std::endl;
    constrTmp->show();
    i++;
  }
};
