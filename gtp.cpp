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

#include <algorithm>
#include <iostream>
#include <string>
#include "gtp.h"

using namespace std;

void GTP::loop(int argc, char* argv[]) {
    string cmd, token;

    for (int i = 1; i < argc; ++i)
        cmd += std::string(argv[i]) + " ";

    do {
        if (argc == 1 && !getline(cin, cmd)) // Block here waiting for input or EOF
            cmd = "quit";

        //Remove all occurences of CR and other control characters except for HT and LF.
        auto filter = [] (char cc) { return (cc<32 && cc!=9 && cc!=10) || cc==127; };
        cmd.erase(std::remove_if(cmd.begin(), cmd.end(), filter), cmd.end());

        //For each line with a hash sign (#), remove all text following and including this character.
        cmd=cmd.substr(0, cmd.find("#"));
        replace(cmd.begin(), cmd.end(), (char)9, ' '); //Convert all occurences of HT to SPACE.

        //Discard any empty or white-space only lines.
        if(cmd.find_first_not_of(' ') != std::string::npos)
        {
            // There's a non-space.
            cout<<"non space"<<cmd<<endl;
        }
    } while (token != "quit" && argc == 1); // Passed args have one-shot behaviour
}
