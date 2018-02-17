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

#include "constr.h"
#include <gtest/gtest.h>

auto constrGLOB = std::make_shared<Constr>(Constr());

TEST(PrimitiveTest, CreateConstruction) {
  using namespace Eigen;
  auto constrTMP = std::make_shared<Constr>(Constr());
  // The empty construction should be not calculated
  EXPECT_FALSE(constrTMP->calculated());
  // Add nodes into the construction
  EXPECT_TRUE(constrTMP->addNodeMainFrame(std::move(Vector3d(0, 0, 0))));
  EXPECT_TRUE(constrTMP->addNodeMainFrame(std::move(Vector3d(2, 0, 0))));
  EXPECT_TRUE(constrTMP->addNodeMainFrame(std::move(Vector3d(2, 2, 0))));
  EXPECT_TRUE(constrTMP->checkFrames());
  // Three nodes should be available
  EXPECT_EQ(3, (constrTMP->mainFrameNodes()).size());
  constrGLOB = constrTMP;
}

TEST(PrimitiveTest, CopiedConstruction) {
  EXPECT_FALSE(constrGLOB->calculated());
  // Three nodes should be available in the copied construction
  EXPECT_EQ(3, (constrGLOB->mainFrameNodes()).size());
}
