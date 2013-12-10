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

#include "fenster.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/foreach.hpp>

fenster::fenster(boost::shared_ptr<configopt> config) {
  _cfg=config;
};

boost::shared_ptr<constr> fenster::addFenster() {
  boost::shared_ptr<constr> constrTMP = 
    boost::shared_ptr<constr> (new constr());
  _constr.push_back(constrTMP);
  return constrTMP;
};

bool fenster::calculate() {
  BOOST_FOREACH(boost::shared_ptr<constr> constrTmp, _constr) {
    if (not(constrTmp->calculated())){
      constrTmp->calculate();
    }
  }
};

bool fenster::loadFile() {
  using boost::property_tree::ptree;
  using boost::property_tree::read_json;
  ptree pt;
  std::vector <boost::shared_ptr<node> > nodes;
  boost::shared_ptr <constr> constrTMP = addFenster();
  
  read_json(_cfg->FNameI(), pt);
  int nodes_number = pt.get<int>("nodes_number", -1);
  if (nodes_number>0) {
    for (unsigned i=0; i < nodes_number; i++){
      Eigen::Vector3d nodeTMP = Eigen::Vector3d((Eigen::Vector3d(
        pt.get<double>("nodes.node_"+boost::lexical_cast<std::string>(i)+".x"), 
        pt.get<double>("nodes.node_"+boost::lexical_cast<std::string>(i)+".y"), 
        pt.get<double>("nodes.node_"+boost::lexical_cast<std::string>(i)+".z"))));
      constrTMP->addNode(nodeTMP);
    }
  }
  if (not(constrTMP->checkFrames())) {
    constrTMP->show();
    std::cerr<<"Constriction is wrong!";
    return false;
  }
  return true;
};
