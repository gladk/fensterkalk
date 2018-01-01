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

#include <frame.h>

class Constr {
  friend class Frame;

public:
  Constr() = default;
  bool calculated() const;
  bool calculate();
  bool checkFrames();
  bool addNodeMainFrame(Eigen::Vector3d nodeTMP);
  void show();
  std::vector<std::shared_ptr<Node>> mainFrameNodes();
  std::vector<std::shared_ptr<Node>> mainFrameNodesInternA();

private:
  bool _calculatedConstr = false;
  Frame _mainFrame;
};
