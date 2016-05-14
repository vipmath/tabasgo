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
#include <regex>
#include <string>
#include "gtp.h"

using namespace std;

#define gtp_known_commands "boardsize|clear_board|genmove|known_command|komi|\
list_commands|name|play|protocol_version|quit|version"

namespace GTP{

    string version()
    {
        stringstream ss;
        ss<<"0.1"
            #ifdef __GNUC__
                            " "
                            __DATE__
                            " "
                            __TIME__
            #endif
            ;
        return ss.str();
    }

    string get_string_arg(string id, string args){
        regex r("([[:alnum:]]+)");
        smatch match;
        if(regex_match(args,match,r)) return match[1];
        else {
            cout<<"?"<<id<<"arguments error ["<<args<<"]"<<endl;
            return "";
        }
    }

    void process_command(string id, string name, string args){
        //cout<<"#processing command id["<<id<<"] name ["<<name<<"] args ["<<args<<"]"<<endl;
        //if(id.empty()) id=" ";

        if(name=="protocol_version") cout<<"="<<id<<" "<<"2"<<endl<<endl;
        if(name=="name") cout<<"="<<id<<" "<<"tabasgo"<<endl<<endl;
        if(name=="version") cout<<"="<<id<<" "<<version()<<endl<<endl;
        if(name=="known_command"){
            string command=get_string_arg(id, args), list=gtp_known_commands;
            if(!command.empty()) cout<<"="<<id<<" "<<string((list.find(command)!= std::string::npos)?"true":"false")<<endl<<endl;
        }
        if(name=="list_commands"){
            string list=gtp_known_commands;
            regex re("[|]+");
            sregex_token_iterator it(list.begin(), list.end(), re, -1), reg_end;
            cout<<"="<<id<<" ";
            for (; it != reg_end; ++it) {
                cout << it->str() << endl;
            }
            cout<<endl;
        }
        if(name=="quit") cout<<"="<<id<<endl<<endl;
        if(name=="boardsize") {
            //TODO update board size
            cout<<"="<<id<<endl<<endl;
        }
        if(name=="clear_board") {
            //TODO clear the board
            cout<<"="<<id<<endl<<endl;
        }
        if(name=="komi") {
            //TODO update komi
            cout<<"="<<id<<endl<<endl;
        }
    }

    void loop(int argc, char* argv[]) {
        string cmd;
        bool quit=false;

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
                regex r(
                        "([[:digit:]]+)? ?("
                        gtp_known_commands
                        ") ?(.*)?"
                );
                smatch match;
                if(regex_match(cmd,match,r)){
                    //cout<<"["<<match[1]<<"]"<<"["<<match[2]<<"]"<<"["<<match[3]<<"]"<<endl;
                    process_command(match[1], match[2], match[3]);
                    quit=(match[2]=="quit");
                }
                else
                {
                    regex r_error("([[:digit:]]+) .*");
                    smatch match_error;
                    cout<<"?";
                    if(regex_match(cmd,match_error,r_error))
                        cout<<match_error[1].str();
                    cout<<" error: invalid input ["<<cmd<<"]"<<endl;
                }
            }
        } while (!quit && argc == 1); // Passed args have one-shot behaviour
    }

} // namespace GTP