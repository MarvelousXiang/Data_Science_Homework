/***************************************************************************
 *   Copyright (C) 2006 by Abderrahman Taha                                *
 *                                                                         *
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
#include <qsplashscreen.h>
#include <qapplication.h>
#include <qmainwindow.h>
#include "k3dsurf.h"


int main( int argc, char **argv )
{
    QApplication a( argc, argv );
    k3dsurface  connect;
#ifndef QT_NO_WIDGET_TOPEXTRA   // for Qt/Embedded minimal build
    //connect.setCaption( "K3DSurf v0.5.3: Math for fun");
    //connect.setWindowOpacity ( 0);
#endif
connect.setGeometry(6, 30, 1016, 672);
a.setMainWidget( &connect );

// Init Iso page:
connect.Initisopage();
//connect.ProcessNewIsoSurface();

// Init Parametric Page:
connect.ParametricSurfaceProcess(); /// To show the first model

// Now show the result of all this stuff:
connect.show();



return (a.exec());
}
