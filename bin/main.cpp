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

#include "main.h"
#include "log.h"
#include "config.h"
#include "order.h"
#include "loadjson.h"

namespace po = boost::program_options;
namespace fs = boost::filesystem;


int main(int ac, char* av[])
{ 
  boost::shared_ptr<logs> log (new logs());
  std::string configFileName;
  
  std::cout<<"\n\
Fensterkalk \n\
Copyright (C) 2013, 2014 Anton Gladky <gladky.anton@gmail.com> \n\
This program comes with ABSOLUTELY NO WARRANTY.\n\
"<<std::endl;
  
  try {
    po::options_description desc("Allowed options");
    desc.add_options()
      ("help", "produce help message")
      ("input,i", po::value<std::string>(), "input file name")
    ;
    
    po::positional_options_description p;
    p.add("input", -1);
    po::variables_map vm;        
    po::store(po::command_line_parser(ac, av).
    options(desc).positional(p).run(), vm);
    po::notify(vm);  
    
    if (vm.count("help")) {
      std::cout << desc << std::endl;
      return 0;
    }
    
    if (vm.count("input")) {
      std::string ss = "input file is: " + vm["input"].as<std::string>();
      configFileName = vm["input"].as<std::string>();
      log->info(ss);
    } else {
      std::string ss = "input file is required, use `-i` option for that or `--help`.\n";
      log->info(ss);
      exit (EXIT_FAILURE);
    }
  }
   catch(std::exception& e) {
      std::string ss =  "error: " + std::string(e.what());
      log->info(ss);
      exit (EXIT_FAILURE);
  }
  catch(...) {
      std::cerr << "Exception of unknown type!\n";
      exit (EXIT_FAILURE);
  }
  boost::shared_ptr<configopt> cfgPrm;
  cfgPrm = boost::shared_ptr<configopt> (new configopt(configFileName));

  boost::shared_ptr<order> orderCur = boost::shared_ptr<order> (new order());
  
  if (not(loadJson(cfgPrm->FNameI(), orderCur))) {
    std::cerr<<"Loaded construction is wrong!"<<std::endl;
    exit (EXIT_FAILURE);
  }
  
  if (not(orderCur->calculate())) {
    std::cerr<<"Loaded construction is wrong!"<<std::endl;
    exit (EXIT_FAILURE);
  }
  orderCur->show();
}
