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

#include <constr.h>

bool Constr::calculated() const { return _calculatedConstr; }
bool Constr::checkFrames() { return _mainFrame.checkBeams(); }

bool Constr::addNodeMainFrame(Eigen::Vector3d &&nodeTMP) {
  return _mainFrame.addNode(std::move(nodeTMP));
}

std::vector<std::shared_ptr<Node>> Constr::mainFrameNodes() {
  return _mainFrame.nodes();
}

std::vector<std::shared_ptr<Node>> Constr::mainFrameNodesInternA() {
  return _mainFrame.nodesInternA();
}
