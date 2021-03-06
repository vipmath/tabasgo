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
#include "board.h"

using namespace std;

Board position;

bool Board::setSize(unsigned int size)
{
    if(size>=3 && size<=MAX_BOARD_SIZE) { this->size=size; return true; }
    else return false;
}

void Board::clear()
{
    for(uint8_t &i : board) i=border;
    for(int raw=0; raw<size; raw++)
        for(int col=0; col<size; col++)
            board[vertice(col,raw)]=empty;
}

void Board::show()
{
    for(int i=0; i<MAX_ARRAY_SIZE; i++)
    {
        if(!(i%20)) cout<<"|"<<endl;
        cout<<(int)board[i]<<" ";

    }
}