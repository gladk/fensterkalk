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

#include <order.h>
#include <boost/foreach.hpp>

Order::Order(){};

std::shared_ptr<Constr> Order::addConstr() {
  std::shared_ptr<Constr> constrTMP = std::shared_ptr<Constr>(new Constr());
  _constr.push_back(constrTMP);
  return constrTMP;
};

bool Order::addConstr(std::shared_ptr<Constr> constrTMP) {
  _constr.push_back(constrTMP);
  return true;
};

bool Order::calculate() {
  BOOST_FOREACH (std::shared_ptr<Constr> constrTmp, _constr) {
    if (not(constrTmp->calculated())) {
      if (not(constrTmp->calculate())) {
        return false;
      }
    }
  }
  return true;
};

void Order::show() {
  unsigned int i = 1;
  BOOST_FOREACH (std::shared_ptr<Constr> constrTmp, _constr) {
    std::cout << "===================" << std::endl
              << "Construction " << i << std::endl;
    constrTmp->show();
    i++;
  }
};

std::shared_ptr<Constr> Order::constrGet(unsigned int i) {
  if (i < _constr.size() and i >= 0) {
    return _constr[i];
  } else {
    return NULL;
  }
};
