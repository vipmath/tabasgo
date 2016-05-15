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

#ifndef TABASGO_BOARD_H
#define TABASGO_BOARD_H

#include <cstdint>

#define MAX_BOARD_SIZE 19

class Board {

private:
    uint8_t board[(MAX_BOARD_SIZE+1)*(MAX_BOARD_SIZE+2)];
};


#endif //TABASGO_BOARD_H
