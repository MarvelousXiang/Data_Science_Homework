/***************************************************************************
 *   Copyright (C) 2005 by Abderrahman Taha                                *
 *   taha_ab@yahoo.fr                                                      *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor,Boston, MA 02110-1301 USA             *
 ***************************************************************************/
#include "videoplayer.h"



 
 videoplayer::videoplayer()
     : QMainWindow( 0, "player", WDestructiveClose )
{
   m = new QMovie("movie.png");    l = new QLabel("test", 0);
   l->resize(400, 400);
   l->setMovie(*m);
  
}
videoplayer::~videoplayer() {
delete m;
delete l;
}
