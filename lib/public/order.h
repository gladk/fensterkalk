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

#include "constr.h"

class order {
private:
  std::vector<std::shared_ptr<Constr>> _constr;

public:
  order();
  std::shared_ptr<Constr> addConstr();
  bool addConstr(std::shared_ptr<Constr> constrTMP);
  bool calculate();
  void show();
  std::shared_ptr<Constr> constrGet(unsigned int i);
};
