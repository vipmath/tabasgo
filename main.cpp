/*
  TabasGo, a GTP compatible Go playing engine.
  Copyright (C) 2016 Jean-Francois Romang

  TabasGo is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  TabasGo is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with TabasGo.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <iostream>
#include <fstream>
#include <iterator>
#include <boost/program_options.hpp>
#include "gtp.h"

using namespace std;
namespace po = boost::program_options;

int main(int ac, char* av[]) {

    typedef vector<string> string_vector;
    string gtp_command;

    try {
        // Declare a group of options that will be
        // allowed only on command line
        po::options_description generic("Generic options");
        generic.add_options()
                ("help", "produce help message")
                ("version", "display version number")
                ("gtp,G",  po::value<string>(),  "GTP command to parse")
                //("compression", po::value<int>(), "set compression level")
                ;

        // Declare a group of options that will be
        // allowed both on command line and in
        // config file
        po::options_description config("Configuration");
        config.add_options()
                ("threads,T", po::value<int>(), "number of threads to use")
                ("include-path,I",
                 po::value< vector<string_vector> >()->composing(),
                 "include path")
                ;

        po::options_description cmdline_options;
        cmdline_options.add(generic).add(config);

        po::options_description config_file_options;
        config_file_options.add(config);

        po::variables_map vm;
        po::store(po::parse_command_line(ac, av, cmdline_options), vm);
        po::notify(vm);

        if (vm.count("help")) {
            cout << cmdline_options << "\n";
            return 1;
        }

        if (vm.count("version")) {
            cout << "TabasGo " <<  GTP::version();
            return 1;
        }

        if (vm.count("gtp")) {
            gtp_command=vm["gtp"].as<string>();
            gtp_command+=" ";
        }

        if (vm.count("threads")) {
            cout << "Using "<< vm["threads"].as<int>() << " threads." << endl;
        }
    }
    catch (const po::error &ex)
    {
        std::cerr << ex.what() << std::endl;
    }

    GTP::loop(gtp_command);
    return 0;
}