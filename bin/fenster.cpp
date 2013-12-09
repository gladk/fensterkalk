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
  _fenster.push_back(constrTMP);
  return constrTMP;
};

bool fenster::loadFile() {
  using boost::property_tree::ptree;
  using boost::property_tree::read_json;
  ptree pt;
  std::vector <boost::shared_ptr<node> > nodes;

  read_json(_cfg->FNameI(), pt);
  int nodes_number = pt.get<int>("nodes_number", -1);
  if (nodes_number>0) {
    for (unsigned i=0; i < nodes_number; i++){
      boost::shared_ptr<node> nodeTMP = 
        boost::shared_ptr<node> (new node(Eigen::Vector3d((Eigen::Vector3d(
        pt.get<double>("nodes.node_"+boost::lexical_cast<std::string>(i)+".x"), 
        pt.get<double>("nodes.node_"+boost::lexical_cast<std::string>(i)+".y"), 
        pt.get<double>("nodes.node_"+boost::lexical_cast<std::string>(i)+".z"))))));
      nodes.push_back(nodeTMP);
    }
  }
  
  std::vector<boost::shared_ptr<frame> > frames;
  for (int i=0; i<nodes_number; i++) {
    boost::shared_ptr<frame> frameTMP;
    if (i!=(nodes_number-1)) {
      frameTMP = boost::shared_ptr<frame> (new frame(nodes[i],nodes[i+1]));
    } else {
      frameTMP = boost::shared_ptr<frame> (new frame(nodes[i],nodes[0]));
    }
    frames.push_back(frameTMP);
  }
  
  boost::shared_ptr <constr> constrTMP = addFenster();
  BOOST_FOREACH(boost::shared_ptr<frame> i, frames) {
    constrTMP->addFrame(i);
  }
  
  return true;
};
