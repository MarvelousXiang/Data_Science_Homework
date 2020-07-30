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
#include <iostream>
#include "glviewer.h"
#include <qfont.h>
#if defined(Q_CC_MSVC)
#pragma warning(disable:4305) // init: truncation from const double to float
#endif


///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
GLubyte rasters[][13] = {
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
{0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18},
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x36, 0x36, 0x36},
{0x00, 0x00, 0x00, 0x66, 0x66, 0xff, 0x66, 0x66, 0xff, 0x66, 0x66, 0x00, 0x00},
{0x00, 0x00, 0x18, 0x7e, 0xff, 0x1b, 0x1f, 0x7e, 0xf8, 0xd8, 0xff, 0x7e, 0x18},
{0x00, 0x00, 0x0e, 0x1b, 0xdb, 0x6e, 0x30, 0x18, 0x0c, 0x76, 0xdb, 0xd8, 0x70},
{0x00, 0x00, 0x7f, 0xc6, 0xcf, 0xd8, 0x70, 0x70, 0xd8, 0xcc, 0xcc, 0x6c, 0x38},
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x1c, 0x0c, 0x0e},
{0x00, 0x00, 0x0c, 0x18, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x18, 0x0c},
{0x00, 0x00, 0x30, 0x18, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x18, 0x30},
{0x00, 0x00, 0x00, 0x00, 0x99, 0x5a, 0x3c, 0xff, 0x3c, 0x5a, 0x99, 0x00, 0x00},
{0x00, 0x00, 0x00, 0x18, 0x18, 0x18, 0xff, 0xff, 0x18, 0x18, 0x18, 0x00, 0x00},
{0x00, 0x00, 0x30, 0x18, 0x1c, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00},
{0x00, 0x00, 0x00, 0x38, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
{0x00, 0x60, 0x60, 0x30, 0x30, 0x18, 0x18, 0x0c, 0x0c, 0x06, 0x06, 0x03, 0x03},
{0x00, 0x00, 0x3c, 0x66, 0xc3, 0xe3, 0xf3, 0xdb, 0xcf, 0xc7, 0xc3, 0x66, 0x3c},
{0x00, 0x00, 0x7e, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x78, 0x38, 0x18},
{0x00, 0x00, 0xff, 0xc0, 0xc0, 0x60, 0x30, 0x18, 0x0c, 0x06, 0x03, 0xe7, 0x7e},
{0x00, 0x00, 0x7e, 0xe7, 0x03, 0x03, 0x07, 0x7e, 0x07, 0x03, 0x03, 0xe7, 0x7e},
{0x00, 0x00, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0xff, 0xcc, 0x6c, 0x3c, 0x1c, 0x0c},
{0x00, 0x00, 0x7e, 0xe7, 0x03, 0x03, 0x07, 0xfe, 0xc0, 0xc0, 0xc0, 0xc0, 0xff},
{0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xc7, 0xfe, 0xc0, 0xc0, 0xc0, 0xe7, 0x7e},
{0x00, 0x00, 0x30, 0x30, 0x30, 0x30, 0x18, 0x0c, 0x06, 0x03, 0x03, 0x03, 0xff},
{0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xe7, 0x7e, 0xe7, 0xc3, 0xc3, 0xe7, 0x7e},
{0x00, 0x00, 0x7e, 0xe7, 0x03, 0x03, 0x03, 0x7f, 0xe7, 0xc3, 0xc3, 0xe7, 0x7e},
{0x00, 0x00, 0x00, 0x38, 0x38, 0x00, 0x00, 0x38, 0x38, 0x00, 0x00, 0x00, 0x00},
{0x00, 0x00, 0x30, 0x18, 0x1c, 0x1c, 0x00, 0x00, 0x1c, 0x1c, 0x00, 0x00, 0x00},
{0x00, 0x00, 0x06, 0x0c, 0x18, 0x30, 0x60, 0xc0, 0x60, 0x30, 0x18, 0x0c, 0x06},
{0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00},
{0x00, 0x00, 0x60, 0x30, 0x18, 0x0c, 0x06, 0x03, 0x06, 0x0c, 0x18, 0x30, 0x60},
{0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x18, 0x0c, 0x06, 0x03, 0xc3, 0xc3, 0x7e},
{0x00, 0x00, 0x3f, 0x60, 0xcf, 0xdb, 0xd3, 0xdd, 0xc3, 0x7e, 0x00, 0x00, 0x00},
{0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xc3, 0xc3, 0xc3, 0x66, 0x3c, 0x18},
{0x00, 0x00, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe},
{0x00, 0x00, 0x7e, 0xe7, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xe7, 0x7e},
{0x00, 0x00, 0xfc, 0xce, 0xc7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc7, 0xce, 0xfc},
{0x00, 0x00, 0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xfc, 0xc0, 0xc0, 0xc0, 0xc0, 0xff},
{0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xfc, 0xc0, 0xc0, 0xc0, 0xff},
{0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xcf, 0xc0, 0xc0, 0xc0, 0xc0, 0xe7, 0x7e},
{0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3},
{0x00, 0x00, 0x7e, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x7e},
{0x00, 0x00, 0x7c, 0xee, 0xc6, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06},
{0x00, 0x00, 0xc3, 0xc6, 0xcc, 0xd8, 0xf0, 0xe0, 0xf0, 0xd8, 0xcc, 0xc6, 0xc3},
{0x00, 0x00, 0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0},
{0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xdb, 0xff, 0xff, 0xe7, 0xc3},
{0x00, 0x00, 0xc7, 0xc7, 0xcf, 0xcf, 0xdf, 0xdb, 0xfb, 0xf3, 0xf3, 0xe3, 0xe3},
{0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xe7, 0x7e},
{0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe},
{0x00, 0x00, 0x3f, 0x6e, 0xdf, 0xdb, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x66, 0x3c},
{0x00, 0x00, 0xc3, 0xc6, 0xcc, 0xd8, 0xf0, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe},
{0x00, 0x00, 0x7e, 0xe7, 0x03, 0x03, 0x07, 0x7e, 0xe0, 0xc0, 0xc0, 0xe7, 0x7e},
{0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0xff},
{0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3},
{0x00, 0x00, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3},
{0x00, 0x00, 0xc3, 0xe7, 0xff, 0xff, 0xdb, 0xdb, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3},
{0x00, 0x00, 0xc3, 0x66, 0x66, 0x3c, 0x3c, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3},
{0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3},
{0x00, 0x00, 0xff, 0xc0, 0xc0, 0x60, 0x30, 0x7e, 0x0c, 0x06, 0x03, 0x03, 0xff},
{0x00, 0x00, 0x3c, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x3c},
{0x00, 0x03, 0x03, 0x06, 0x06, 0x0c, 0x0c, 0x18, 0x18, 0x30, 0x30, 0x60, 0x60},
{0x00, 0x00, 0x3c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x3c},
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc3, 0x66, 0x3c, 0x18},
{0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x38, 0x30, 0x70},
{0x00, 0x00, 0x7f, 0xc3, 0xc3, 0x7f, 0x03, 0xc3, 0x7e, 0x00, 0x00, 0x00, 0x00},
{0x00, 0x00, 0xfe, 0xc3, 0xc3, 0xc3, 0xc3, 0xfe, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0},
{0x00, 0x00, 0x7e, 0xc3, 0xc0, 0xc0, 0xc0, 0xc3, 0x7e, 0x00, 0x00, 0x00, 0x00},
{0x00, 0x00, 0x7f, 0xc3, 0xc3, 0xc3, 0xc3, 0x7f, 0x03, 0x03, 0x03, 0x03, 0x03},
{0x00, 0x00, 0x7f, 0xc0, 0xc0, 0xfe, 0xc3, 0xc3, 0x7e, 0x00, 0x00, 0x00, 0x00},
{0x00, 0x00, 0x30, 0x30, 0x30, 0x30, 0x30, 0xfc, 0x30, 0x30, 0x30, 0x33, 0x1e},
{0x7e, 0xc3, 0x03, 0x03, 0x7f, 0xc3, 0xc3, 0xc3, 0x7e, 0x00, 0x00, 0x00, 0x00},
{0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xfe, 0xc0, 0xc0, 0xc0, 0xc0},
{0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 0x18, 0x00},
{0x38, 0x6c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x00, 0x00, 0x0c, 0x00},
{0x00, 0x00, 0xc6, 0xcc, 0xf8, 0xf0, 0xd8, 0xcc, 0xc6, 0xc0, 0xc0, 0xc0, 0xc0},
{0x00, 0x00, 0x7e, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x78},
{0x00, 0x00, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0xfe, 0x00, 0x00, 0x00, 0x00},
{0x00, 0x00, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xfc, 0x00, 0x00, 0x00, 0x00},
{0x00, 0x00, 0x7c, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0x7c, 0x00, 0x00, 0x00, 0x00},
{0xc0, 0xc0, 0xc0, 0xfe, 0xc3, 0xc3, 0xc3, 0xc3, 0xfe, 0x00, 0x00, 0x00, 0x00},
{0x03, 0x03, 0x03, 0x7f, 0xc3, 0xc3, 0xc3, 0xc3, 0x7f, 0x00, 0x00, 0x00, 0x00},
{0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xe0, 0xfe, 0x00, 0x00, 0x00, 0x00},
{0x00, 0x00, 0xfe, 0x03, 0x03, 0x7e, 0xc0, 0xc0, 0x7f, 0x00, 0x00, 0x00, 0x00},
{0x00, 0x00, 0x1c, 0x36, 0x30, 0x30, 0x30, 0x30, 0xfc, 0x30, 0x30, 0x30, 0x00},
{0x00, 0x00, 0x7e, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0x00, 0x00, 0x00, 0x00},
{0x00, 0x00, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3, 0xc3, 0x00, 0x00, 0x00, 0x00},
{0x00, 0x00, 0xc3, 0xe7, 0xff, 0xdb, 0xc3, 0xc3, 0xc3, 0x00, 0x00, 0x00, 0x00},
{0x00, 0x00, 0xc3, 0x66, 0x3c, 0x18, 0x3c, 0x66, 0xc3, 0x00, 0x00, 0x00, 0x00},
{0xc0, 0x60, 0x60, 0x30, 0x18, 0x3c, 0x66, 0x66, 0xc3, 0x00, 0x00, 0x00, 0x00},
{0x00, 0x00, 0xff, 0x60, 0x30, 0x18, 0x0c, 0x06, 0xff, 0x00, 0x00, 0x00, 0x00},
{0x00, 0x00, 0x0f, 0x18, 0x18, 0x18, 0x38, 0xf0, 0x38, 0x18, 0x18, 0x18, 0x0f},
{0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18},
{0x00, 0x00, 0xf0, 0x18, 0x18, 0x18, 0x1c, 0x0f, 0x1c, 0x18, 0x18, 0x18, 0xf0},
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x8f, 0xf1, 0x60, 0x00, 0x00, 0x00}
};

static GLfloat redcol[4] = {1.0, 0.0, 0.0, 1.0};
static QString nbl="", nbc, nbd;
static int CornerH, CornerW;


void OpenGlWidget::cnd(){LocalScene.drawcnd *= -1;};
///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::cndmesh(){LocalScene.cndmesh *= -1;};
///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::drawborder(){LocalScene.border *= -1;};
///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::fog(){/*LocalScene.fog *= -1;*/};
///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::meshOk(){LocalScene.mesh *= -1;};
///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::backSurf(){ LocalScene.back *= -1;};
///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::clipOk(){ LocalScene.clip *= -1;};
///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::axeOk(){ LocalScene.axe *= -1;update();};
///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::normOk(){ LocalScene.norm *= -1;};
///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::infosOk(){ LocalScene.infos *= -1;};
///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::boxOk(){ LocalScene.box *= -1;update();};
///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::lineOk(){ LocalScene.line *= -1;};
///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::plan(){LocalScene.plan *= -1; update();};
///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::png(){png_ok*=-1;}
///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::jpg(){jpg_ok*=-1;}
///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::bmp(){bmp_ok*=-1;}
///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::quality(int c){quality_image = c;}
///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::conditionok(){LocalScene.condition *= -1;}
///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::screenshot(){
QImage image = grabFrameBuffer();
if(png_ok == 1) image.save("GLscreenshot.png", "PNG" , quality_image);
if(png_ok == 1) image.save("GLscreenshot.jpg", "JPEG" , quality_image);
if(png_ok == 1) image.save("GLscreenshot.bmp", "BMP" , quality_image);
}
///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::red(int cl)
{   switch(colortype) {
    case 0:  greencol[0] = (cl/255.);valueChanged();
             update();
             break;
    case 1:  goldcol[0]  = (cl/255.);valueChanged();
             update();
             break;
    case 2:  gridline[0] = (cl/255.);
             update();
             break;
    case 3:  background[0] = (cl/255.);
             glClearColor(background[0], background[1],background[2], 0.0);
             update();
             break;
     };
}
///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::green(int cl)
{   switch(colortype) {
    case 0:  greencol[1] = (cl/255.);valueChanged();
             update();
             break;
    case 1:  goldcol[1]  = (cl/255.);valueChanged();
             update();
             break;
    case 2:  gridline[1] = (cl/255.);
             update();
             break;
    case 3:  background[1] = (cl/255.);
             glClearColor(background[0], background[1],background[2], 0.0);
             update();
             break;
     };
}
///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::blue(int cl)
{   switch(colortype) {
    case 0:  greencol[2] = (cl/255.);valueChanged();
             update();
             break;
    case 1:  goldcol[2]  = (cl/255.);valueChanged();
             update();
             break;
    case 2:  gridline[2] = (cl/255.);
             update();
             break;
    case 3:  background[2] = (cl/255.);
             glClearColor(background[0], background[1],background[2], 0.0);
             update();
             break;
     };
}
///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::transparence()
{
      switch(colortype) {
    case 1:  LocalScene.front *= -1;
             update();break;
    case 0:  LocalScene.back  *= -1;
             update();break;
    case 2:  LocalScene.line  *= -1;
             update();break;
};
}
///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::valueChanged(){
    InitGlParameters();
     }

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
GLuint fontOffset;
void makeRasterFont(void)
{
    GLuint i;
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    fontOffset = glGenLists (128);
    for (i = 30; i < 127; i++) {
        glNewList(i+fontOffset, GL_COMPILE);
            glBitmap(8, 13, 0.0, 2.0, 10.0, 0.0, rasters[i-30]);
        glEndList();
    }
}
///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void InitFont(void)
{
    //glShadeModel (GL_FLAT);
    makeRasterFont();
}

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/*
static void printString(char *s)
{
    glPushAttrib (GL_LIST_BIT);
    glListBase(fontOffset);
    glCallLists(strlen(s), GL_UNSIGNED_BYTE, (GLubyte *) s);
    glPopAttrib ();
}
*/
///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::start(){
QThread::start();
}

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::run(){
}

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::anim(){
    LocalScene.anim *= -1;
if(LocalScene.anim == 1) timer->start( latence, FALSE );
else if(LocalScene.morph != 1) timer->stop();
}

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::morph(){
LocalScene.morph *= -1;
if(LocalScene.morph == 1) timer->start( latence, FALSE );
else if(LocalScene.anim != 1) timer->stop();
}

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
bool OpenGlWidget::timeractif(){
return(LocalScene.morph == 1 || LocalScene.anim == 1);
}

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::stoptimer(){
timer->stop();
}

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::starttimer(){
timer->start( latence, FALSE );
}
///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::restarttimer(int newlatence){
latence = newlatence;
if(LocalScene.morph == 1 || LocalScene.anim == 1) {
timer->stop();
timer->start( latence, FALSE );
}
}
///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
OpenGlWidget::OpenGlWidget( QWidget *parent, const char *name )
     : QGLWidget( parent, name, 0, WNoAutoErase )
{
    latence = 30;
    colortype = 0;
    view_rotx = view_roty = 0.0;
    view_rotz = 1.0; ScalCoeff =1.0; val1 = val2 = val3 = 0.0;
    nb_colone = nb_ligne = 25;
    coupure_col = coupure_ligne = 0;
    isoline = isocolumn = isodepth = 26;
    cpisoline = cpisocolumn = cpisodepth = 0;
    width = 650; height = 650;
    NbMorphFrame = 30; /// The maximum of morph sequences...
    timer = new QTimer( this );
    connect( timer, SIGNAL(timeout()), this, SLOT(updateGL()) );

    gridliner=0.1; gridlineg=0.4; gridlineb=0.1;
    pixmap = new QPixmap(650,650);
    png_ok = 1; jpg_ok = bmp_ok = -1; quality_image = 50;
    gridline[0] = 0.1;
    gridline[1] = 0.4;
    gridline[2] = 0.1;
    gridline[3] = 1.0;

    background[0] = 0.0;
    background[1] = 0.0;
    background[2] = 0.0;
    background[3] = 1.0;

    greencol[0] = 0.0;
    greencol[1] = 0.7;
    greencol[2] = 0.0;
    greencol[3] = 1.0;

    goldcol[0] = 249./255.;
    goldcol[1] = 170./255.;
    goldcol[2] = 0.0;
    goldcol[3] = 1.0;

    LocalScene.border  = 1;
    LocalScene.cndmesh =-1;
    LocalScene.drawcnd = 1;
    LocalScene.goldcol = goldcol;
    LocalScene.greencol= greencol;

    LocalScene.mesh  = 1;
    LocalScene.line  = 1;
    LocalScene.infos = 1;
    LocalScene.axe   = 1;
    LocalScene.box   = 1;
    LocalScene.typedrawing =-1;
    LocalScene.smoothpoly  = 1;
    LocalScene.smoothline  =-1;
    LocalScene.anim  =-1;
    LocalScene.morph =-1;
    LocalScene.norm  =-1;
    LocalScene.plan  = 1;
    LocalScene.front = 1;
    LocalScene.back  = 1;
    LocalScene.condition  = -1;
    LocalScene.ArrayNorVer_localPt = ArrayNorVer_local;
    LocalScene.PolyIndices_localPt = PolyIndices_local;
    LocalScene.morelistept[9] = NbPolygnNbVertex;
    IDGlWindow = NBGlWindow;
    PolyNumber        = 0;
    VertexNumber      = 0;

    NBGlWindow++;
    if(NBGlWindow == 1) {
    /*
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport( -width/2, -height/2, width/2, height/2);
    glFrustum(-400, 400, -400, 400, 400.0, 1000.0);
    //glOrtho( -400, 400, -400, 400, -400.0, 400.0 );
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef( 0.0, 0.0, -800.0 );
    */
   GLfloat ambient[] = { .0, .0, .0, 1.0 };
   GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
   //GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat lmodel_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
   GLfloat local_view[] = { 1.0 };
   static GLfloat position[4] = {0.0, 0.0,1000.0, 1.0};

   glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
   glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
   glLightfv(GL_LIGHT0, GL_POSITION, position);
   glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
   glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);


}

    InitFont();
}

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::CutLineIndex(int ctline){
   int i, j, k=0;
   coupure_ligne = ctline;
   PolyNumber = 4*(nb_ligne-coupure_ligne-1)*(nb_colone-coupure_col-1);
/// generation of the Index Array :
   k=0;
   for (i=0; i< nb_ligne - coupure_ligne -1; i++)
      for (j=0; j< nb_colone - coupure_col -1; j++) {
     PolyIndices_local[k  ] = i*nb_colone + j;
     PolyIndices_local[k+1] = (i+1)*nb_colone + j;
     PolyIndices_local[k+2] = (i+1)*nb_colone + (j+1);
     PolyIndices_local[k+3] = i*nb_colone + (j+1);
     k+=4;
    }
    // 1) Generate the Indices Tables for all Morph Frames :
  for(j =1; j < NbMorphFrame; j++)
    for(i =0; i < PolyNumber; i++){
    PolyIndices_local[j*PolyNumber + i] = PolyIndices_local[i] + j*nb_ligne*nb_colone;
    }
  /// 2) Nb Poly & Vertex :
 for(i =0; i < NbMorphFrame; i++) {
   NbPolygnNbVertex[2*i  ] = PolyNumber;
   NbPolygnNbVertex[2*i+1] = i*(nb_ligne-coupure_ligne)*(nb_colone-coupure_col);
   };
}

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::CutColIndex(int ctcol){
   int i, j, k=0;
   coupure_col = ctcol;
   PolyNumber = 4*(nb_ligne-coupure_ligne-1)*(nb_colone-coupure_col-1);
/// generation of the Index Array :
   k=0;
   for (i=0; i< nb_ligne - coupure_ligne -1; i++)
      for (j=0; j< nb_colone - coupure_col -1; j++) {
     PolyIndices_local[k  ] = i*nb_colone + j;
     PolyIndices_local[k+1] = (i+1)*nb_colone + j;
     PolyIndices_local[k+2] = (i+1)*nb_colone + (j+1);
     PolyIndices_local[k+3] = i*nb_colone + (j+1);
     k+=4;
    }
    // 1) Generate the Indices Tables for all Morph Frames :
  for(j =1; j < NbMorphFrame; j++)
    for(i =0; i < PolyNumber; i++){
    PolyIndices_local[j*PolyNumber + i] = PolyIndices_local[i] + j*nb_ligne*nb_colone;
    }
  /// 2) Nb Poly & Vertex :
 for(i =0; i < NbMorphFrame; i++) {
   NbPolygnNbVertex[2*i  ] = PolyNumber;
   NbPolygnNbVertex[2*i+1] = i*(nb_ligne-coupure_ligne)*(nb_colone-coupure_col);
   };
}

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::smoothpoly(){
    LocalScene.smoothpoly *= -1;
    if(LocalScene.smoothpoly == 1) glShadeModel (GL_SMOOTH);
    else glShadeModel (GL_FLAT);
    update();
}

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::smoothline(){ LocalScene.smoothline *= -1;
   /// For drawing Lines :
   if(LocalScene.smoothline == 1) {
   glEnable (GL_LINE_SMOOTH);
   glEnable (GL_BLEND);
   glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   glHint (GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
   }
   else {glDisable(GL_LINE_SMOOTH); glDisable(GL_BLEND);
   };
   update();
}

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::frontSurf(){
LocalScene.front *= -1;
    if(LocalScene.front == -1) glEnable(GL_CULL_FACE);
    else glDisable(GL_CULL_FACE);
    update();
}

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
static void makeallred(Scene *scene){
    static int redcl = 1;
    if( redcl == 1){
       /// For drawing Filled Polygones :
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glEnable(GL_NORMALIZE);
    glFrontFace (GL_CCW);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, redcol);
    glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, redcol);
    glMaterialf (GL_FRONT, GL_SHININESS, 35.0);
    glMaterialf (GL_BACK, GL_SHININESS, 35.0);
    }
   else {
      /// For drawing Filled Polygones :
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glEnable(GL_NORMALIZE);
    glFrontFace (GL_CCW);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, scene->goldcol);
    glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, scene->greencol);
    glMaterialf (GL_FRONT, GL_SHININESS, 35.0);
    glMaterialf (GL_BACK, GL_SHININESS, 35.0);
       }

   redcl *= -1;
}

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::InitGlParameters(){

    /// For drawing Filled Polygones :
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glEnable(GL_NORMALIZE);
    glFrontFace (GL_CCW);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, goldcol);
    glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, greencol);
    glMaterialf (GL_FRONT, GL_SHININESS, 35.0);
    glMaterialf (GL_BACK, GL_SHININESS, 35.0);

    glEnable(GL_DEPTH_TEST);
    glClearColor(background[0], background[1],background[2], 0.0);
    InitFont();
/*
    if(LocalScene.front == -1) glEnable(GL_CULL_FACE);
    else glDisable(GL_CULL_FACE);
*/

/*
    if(LocalScene.smoothpoly == 1) glShadeModel (GL_SMOOTH);
    else glShadeModel (GL_FLAT);
*/
/*
glFogi(GL_FOG_MODE, fogMode[fogfilter]);		// Fog Mode
glFogfv(GL_FOG_COLOR, fogColor);			// Set Fog Color
glFogf(GL_FOG_DENSITY, 0.85f);				// How Dense Will The Fog Be
glHint(GL_FOG_HINT, GL_DONT_CARE);			// Fog Hint Value
glFogf(GL_FOG_START, 1.0f);				// Fog Start Depth
glFogf(GL_FOG_END, 2400.0f);				// Fog End Depth
glEnable(GL_FOG);
*/

/*
   /// For drawing Lines :
   if(LocalScene.smoothline == 1) {
   glEnable (GL_LINE_SMOOTH);
   glEnable (GL_BLEND);
   glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   glHint (GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
   }
   else {glDisable(GL_LINE_SMOOTH); glDisable(GL_BLEND);
   }
*/
 LocalScene.axeliste = glGenLists(1);
 glNewList(LocalScene.axeliste, GL_COMPILE );
   glLineWidth(1);
   glBegin( GL_LINES );
  glColor3f (1., 0., 0.);
    glVertex3f( 400.0, 0.0, 0.0);
    glVertex3f(   0.0, 0.0, 0.0);
  glColor3f (0., 1., 0.);
    glVertex3f(0.0, 400.0, 0.0);
    glVertex3f(0.0,   0.0, 0.0);
  glColor3f (0., 0., 1.);
    glVertex3f(0.0, 0.0, 400.0);
    glVertex3f(0.0, 0.0,   0.0);
   glEnd();



   glBegin(GL_TRIANGLE_FAN);
   glColor3f (0.0, 0.0, 1.0);
   glVertex3f(0.0, 0.0, 400.0);
   glVertex3f(10.0, 0.0, 380.0);
   glVertex3f(0.0, 10.0, 380.0);
   glColor3f (0.0, 0.0, 0.3);
   glVertex3f(-10.0, 0.0, 380.0);
   glColor3f (0.0, 0.0, 1.0);
   glVertex3f(0.0, -10.0, 380.0);
   glColor3f (0.0, 0.0, 0.3);
   glVertex3f(10.0, 0.0, 380.0);
   glEnd();



   glBegin(GL_TRIANGLE_FAN);
   glColor3f (0.0, 1., 0.);
   glVertex3f(0.0, 400.0, 0.0);
   glVertex3f(10.0, 380.0, 0.0);
   glVertex3f(0.0, 380.0, 10.0);
   glColor3f (0.0, 0.3, 0.0);
   glVertex3f(-10.0, 380.0, 0.0);
   glColor3f (0.0, 1.0, 0.0);
   glVertex3f(.0, 380.0, -10.0);
   glColor3f (0.0, 0.3, 0.0);
   glVertex3f(10.0, 380.0, 0.0);
   glEnd();

/// Axe X :

   glBegin(GL_TRIANGLE_FAN);
   glColor3f (1.0, 0.0, 0.0);
   glVertex3f(400.0, 0.0, 0.0);
   glVertex3f(380.0, 10.0, 0.0);
   glVertex3f(380.0, 0.0, 10.0);
   glColor3f (0.3, 0.0, 0.0);
   glVertex3f(380.0, -10.0, 0.0);
   glColor3f (1.0, 0.0, 0.0);
   glVertex3f(380.0, 0.0, -10.0);
   glColor3f (0.3, 0.0, 0.0);
   glVertex3f(380.0, 10.0, 0.0);
   glEnd();

   glColor3f (1.0, 0.0, 0.0);
   glBegin(GL_LINE_LOOP);
   glVertex3f(400.0, 0.0, 0.0);
   glVertex3f(380.0, 10.0, 0.0);
   glVertex3f(380.0, 0.0, 10.0);
   glVertex3f(380.0, -10.0, 0.0);
   glVertex3f(380.0, 0.0, -10.0);
   glVertex3f(380.0, 10.0, 0.0);
   glEnd();

   glColor3f (1., 0., 0.);
    glRasterPos3i(410, 10, 10);
    //printString("X");
glCallLists(strlen("X"),
GL_UNSIGNED_BYTE,
"X");

   glColor3f (0., 1., 0.);
    glRasterPos3i(10, 410, 10);
    //printString("Y");
glCallLists(strlen("Y"),
GL_UNSIGNED_BYTE,
"Y");

   glColor3f (0., 0., 1.);
    glRasterPos3i(10, 10, 410);
    //printString("Z");
glCallLists(strlen("Z"),
GL_UNSIGNED_BYTE,
"Z");

   glLineWidth(0.9);
 glEndList();

LocalScene.planliste = glGenLists(1);
 glNewList(LocalScene.planliste, GL_COMPILE );
  glLineWidth(1);
   glColor3f (0.8, 0., 0.7);
   glBegin( GL_LINES );
glVertex3f(-150.0, 600.0, zminim);
glVertex3f(-150.0,-600.0, zminim);
glVertex3f(0.0, 600.0, zminim);
glVertex3f(0.0,-600.0, zminim);

glVertex3f(150.0, 600.0, zminim);
glVertex3f(150.0,-600.0, zminim);
glVertex3f(600.0, -150.0, zminim);
glVertex3f(-600.0,-150.0, zminim);

glVertex3f(600.0, 0.0, zminim);
glVertex3f(-600.0, 0.0, zminim);
glVertex3f(600.0, 150.0, zminim);
glVertex3f(-600.0, 150.0, zminim);

glVertex3f(-75.0, 600.0, zminim);
glVertex3f(-75.0,-600.0, zminim);
glVertex3f(-225.0, 600.0, zminim);
glVertex3f(-225.0,-600.0, zminim);
glVertex3f(-300.0, 600.0, zminim);
glVertex3f(-300.0,-600.0, zminim);
glVertex3f(-375.0, 600.0, zminim);
glVertex3f(-375.0,-600.0, zminim);
glVertex3f(-450.0, 600.0, zminim);
glVertex3f(-450.0,-600.0, zminim);
glVertex3f(-525.0, 600.0, zminim);
glVertex3f(-525.0,-600.0, zminim);

glVertex3f(75.0, 600.0, zminim);
glVertex3f(75.0,-600.0, zminim);
glVertex3f(225.0, 600.0, zminim);
glVertex3f(225.0,-600.0, zminim);
glVertex3f(300.0, 600.0, zminim);
glVertex3f(300.0,-600.0, zminim);
glVertex3f(375.0, 600.0, zminim);
glVertex3f(375.0,-600.0, zminim);
glVertex3f(450.0, 600.0, zminim);
glVertex3f(450.0,-600.0, zminim);
glVertex3f(525.0, 600.0, zminim);
glVertex3f(525.0,-600.0, zminim);

glVertex3f(600.0,-75.0, zminim);
glVertex3f(-600.0,-75.0, zminim);
glVertex3f(600.0,-225.0, zminim);
glVertex3f(-600.0,-225.0, zminim);
glVertex3f(600.0,-300.0, zminim);
glVertex3f(-600.0,-300.0, zminim);
glVertex3f(600.0,-375.0, zminim);
glVertex3f(-600.0,-375.0, zminim);
glVertex3f(600.0,-450.0, zminim);
glVertex3f(-600.0,-450.0, zminim);
glVertex3f(600.0,-525.0, zminim);
glVertex3f(-600.0,-525.0, zminim);



glVertex3f(600.0,75.0, zminim);
glVertex3f(-600.0,75.0, zminim);
glVertex3f(600.0,225.0, zminim);
glVertex3f(-600.0,225.0, zminim);
glVertex3f(600.0,300.0, zminim);
glVertex3f(-600.0,300.0, zminim);
glVertex3f(600.0,375.0, zminim);
glVertex3f(-600.0,375.0, zminim);
glVertex3f(600.0,450.0, zminim);
glVertex3f(-600.0,450.0, zminim);
glVertex3f(600.0,525.0, zminim);
glVertex3f(-600.0,525.0, zminim);
  glEnd();
   glLineWidth(0.9);
 glEndList();

}

///++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::InitGlMorph() {
    boxok();
    glInterleavedArrays (GL_N3F_V3F, 0, ArrayNorVer_local);
    //glEnable(GL_DEPTH_TEST);
    //glClearColor(backgroundr, backgroundg,backgroundb, 0.0);

    InitGlParameters();
}

///++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::initializeGL()
{ int i, j, k, l, mn, nbpl;

    boxok();
    glInterleavedArrays (GL_N3F_V3F, 0, ArrayNorVer_local);
   //object_id = makeObject();     // Generate an OpenGL display list
   //grid_id   = makeGrid();       // Generate an OpenGL display list
    if(LocalScene.condition == 1){
    j = k = l = 0;
    LocalScene.PolyIndices_localBorderCND    = &PolyIndices_local[20*48000];
    LocalScene.PolyIndices_localVerifyCND    = &PolyIndices_local[30*48000];
    LocalScene.PolyIndices_localNotVerifyCND = &PolyIndices_local[40*48000];

    nbpl = (int)(NbPolygnNbVertex[0]/3);
    for(i = 0; i < nbpl; i++){
    mn = TypeIsoSurfaceTriangleListeCND[i];
    if(mn == 1) {
    LocalScene.PolyIndices_localNotVerifyCND[j  ] = LocalScene.PolyIndices_localPt[3*i  ];
    LocalScene.PolyIndices_localNotVerifyCND[j+1] = LocalScene.PolyIndices_localPt[3*i+1];
    LocalScene.PolyIndices_localNotVerifyCND[j+2] = LocalScene.PolyIndices_localPt[3*i+2];
    j+=3;}
    else if(mn == 0) {
    LocalScene.PolyIndices_localVerifyCND[k  ] = LocalScene.PolyIndices_localPt[3*i  ];
    LocalScene.PolyIndices_localVerifyCND[k+1] = LocalScene.PolyIndices_localPt[3*i+1];
    LocalScene.PolyIndices_localVerifyCND[k+2] = LocalScene.PolyIndices_localPt[3*i+2];
    k+=3;}
    else if(mn == 4) {
    LocalScene.PolyIndices_localBorderCND[l  ] = LocalScene.PolyIndices_localPt[3*i  ];
    LocalScene.PolyIndices_localBorderCND[l+1] = LocalScene.PolyIndices_localPt[3*i+1];
    LocalScene.PolyIndices_localBorderCND[l+2] = LocalScene.PolyIndices_localPt[3*i+2];
    l+=3;}
    }

    LocalScene.PolyNumberVerifyCND = k;
    LocalScene.PolyNumberBorderCND = l;
    LocalScene.PolyNumberNotVerifyCND = j;
    }
    InitGlParameters();
    IndiceMorphFrame =0; /// To Initialise the morph effect

/*
///Listes Construction :
/// 1) The Object Definition :
 PolyIndices_local[47998] = glGenLists(1);
 glNewList(PolyIndices_local[47998], GL_COMPILE );
 glDrawElements(GL_QUADS, PolyNumber , GL_UNSIGNED_INT, PolyIndices_local);
 glEndList();

/// 2) The Object Complete Description :
 PolyIndices_local[47999] = glGenLists(1);
 glNewList(PolyIndices_local[47999], GL_COMPILE );
 if(MieshOk == 1){
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(polyfactor, polyunits);
    //glDrawElements(GL_QUADS, PolyNumber , GL_UNSIGNED_INT, PolyIndices_local);
    glCallList(PolyIndices_local[47998]);
    glDisable(GL_POLYGON_OFFSET_FILL);

    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
 }
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //glDrawElements(GL_QUADS, PolyNumber , GL_UNSIGNED_INT, PolyIndices_local);
    glCallList(PolyIndices_local[47998]);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

 glEndList();
*/
}

///++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::scalcoeff(double ){
//ScalCoeff = coeff;
}
/*
void OpenGlWidget::writetest(QString str){
    QFont ft;
    renderText(0, 0, str, ft, 2000);
    };
*/
/*
# include <string>
using std::string;
///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
static string itos(int i)	// convert int to string
	{
		stringstream s;
		s << i;
		return s.str();
	}
	*/

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::infosok()
{ LocalScene.infos *= -1;
 //nblg = QString::number(LocalScene.PolyNumber);
     }

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::PrintInfos()
{
(LocalScene.typedrawing == 1) ? 
nbl = QString::number(isoline-cpisoline)+"x"+QString::number(isocolumn-cpisocolumn)+"x"+QString::number(isodepth-cpisodepth) :
nbl = QString::number(nb_ligne-coupure_ligne)+"x"+QString::number(nb_colone-coupure_col)+" = "+QString::number((nb_ligne-coupure_ligne)*(nb_colone-coupure_col));

glDisable(GL_DEPTH_TEST);
glMatrixMode(GL_PROJECTION);
glPushMatrix();
glLoadIdentity();

glOrtho(-320,320,-320,320,-1,1);
glMatrixMode(GL_MODELVIEW);
glPushMatrix();
glLoadIdentity();
    //glRasterPos2i(-CornerW+20,CornerH);
glColor3f (0., 1.0, 0.);
glRasterPos2i(-310,300);
glCallLists(strlen("Grid = "),
GL_UNSIGNED_BYTE,
(GLubyte *)"Grid = ");
glColor3f (1., 0.0, 0.);
glRasterPos2i(-250,300);
glCallLists(strlen(nbl),GL_UNSIGNED_BYTE,nbl);

glColor3f (0., 1.0, 0.);
glRasterPos2i(-310,280);
glCallLists(strlen("Poly = "),
GL_UNSIGNED_BYTE,
(GLubyte *)"Poly = ");
glColor3f (1., 0.0, 0.);
glRasterPos2i(-250,280);
(LocalScene.typedrawing == 1) ? 
glCallLists(strlen(QString::number(NbPolygnNbVertex[0]/3)),
GL_UNSIGNED_BYTE,
QString::number(NbPolygnNbVertex[0]/3)) :
glCallLists(strlen(QString::number(NbPolygnNbVertex[0]/3)),
GL_UNSIGNED_BYTE,
QString::number(NbPolygnNbVertex[0]/4)) ;

if (LocalScene.typedrawing == 1)  {
glColor3f (0., 1.0, 0.);
glRasterPos2i(-310,260);
glCallLists(strlen("Vertx= "),
GL_UNSIGNED_BYTE,
(GLubyte *)"Vertx= ");
glColor3f (1., 0.0, 0.);
glRasterPos2i(-250,260);

glCallLists(strlen(QString::number(VertexNumber)),
GL_UNSIGNED_BYTE,
QString::number(VertexNumber)) ;
}



glMatrixMode(GL_PROJECTION);
glPopMatrix();
glMatrixMode(GL_MODELVIEW);
glPopMatrix();
glEnable(GL_DEPTH_TEST);
}

///++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
static void draw(/*GLuint *Poly_pt, int NB_Poly,*/ Scene *scene){
 glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
 
    if(scene->anim == 1) glRotatef(RotStrength,axe_x,axe_y,axe_z);

/// Axe Drawing :
    if(scene->axe == 1)  glCallList(scene->axeliste);

/// Plan drawing :
    if(scene->plan == 1) glCallList(scene->planliste);

/// Box Drawing:
    if(scene->box == 1) glCallList(scene->boxliste);

/// Object Drawing :

    /// No condition here :
    if(scene->condition != 1) {
      if(scene->mesh == 1){
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(polyfactor, polyunits);
    (scene->typedrawing == 1) ?
      glDrawElements(GL_TRIANGLES, scene->PolyNumber, GL_UNSIGNED_INT, scene->PolyIndices_localPt) :
      glDrawElements(GL_QUADS, scene->PolyNumber, GL_UNSIGNED_INT, scene->PolyIndices_localPt);
    glDisable(GL_POLYGON_OFFSET_FILL);
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
 }


 if(scene->line == 1) {
    glColor3f (gridline[0], gridline[1], gridline[2]);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    (scene->typedrawing == 1) ? glDrawElements(GL_TRIANGLES, scene->PolyNumber, GL_UNSIGNED_INT, scene->PolyIndices_localPt) : glDrawElements(GL_QUADS, scene->PolyNumber, GL_UNSIGNED_INT, scene->PolyIndices_localPt);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
 }
    }

 ///There is a condition :
    else  {

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_POLYGON_OFFSET_FILL);

    if(scene->mesh == 1){    
    glPolygonOffset(polyfactor, polyunits);
    glDrawElements(GL_TRIANGLES, scene->PolyNumberNotVerifyCND, GL_UNSIGNED_INT, scene->PolyIndices_localNotVerifyCND);
    }
    if(scene->cndmesh !=1 && scene->drawcnd == 1){
    makeallred(scene);
    glDrawElements(GL_TRIANGLES, scene->PolyNumberVerifyCND, GL_UNSIGNED_INT, scene->PolyIndices_localVerifyCND);
    makeallred(scene);
    }

    glDisable(GL_POLYGON_OFFSET_FILL);
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);

 /// Draw the Mesh:

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    if(scene->line == 1) {
    glColor3f (gridline[0], gridline[1], gridline[2]);
    //glDrawElements(GL_TRIANGLES, scene->PolyNumber, GL_UNSIGNED_INT, scene->PolyIndices_localPt);
    glDrawElements(GL_TRIANGLES, scene->PolyNumberNotVerifyCND, GL_UNSIGNED_INT, scene->PolyIndices_localNotVerifyCND);
    }
    if(scene->cndmesh == 1 && scene->drawcnd == 1){
    glColor3f (1.0, 0.0, 0.0);
    glDrawElements(GL_TRIANGLES, scene->PolyNumberVerifyCND, GL_UNSIGNED_INT, scene->PolyIndices_localVerifyCND);
    }

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    

 /// Draw the Border line:
    if(scene->border == 1){
    glLineWidth(4);
    glColor3f (1.0, 1.0, 1.0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawElements(GL_TRIANGLES, scene->PolyNumberBorderCND, GL_UNSIGNED_INT, scene->PolyIndices_localBorderCND);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glLineWidth(1);
    }
     } /// End of There is a condition


if(scene->norm == 1)
for(IndiceI=0; IndiceI< scene->PolyNumber; IndiceI+=4) {
IndiceJ = 6*scene->PolyIndices_localPt[IndiceI];
       glBegin( GL_LINES );
glVertex3f(scene->ArrayNorVer_localPt[IndiceJ+3],
           scene->ArrayNorVer_localPt[IndiceJ+4],
           scene->ArrayNorVer_localPt[IndiceJ+5]);
glVertex3f(scene->ArrayNorVer_localPt[IndiceJ+3]+30*scene->ArrayNorVer_localPt[IndiceJ  ],
           scene->ArrayNorVer_localPt[IndiceJ+4]+30*scene->ArrayNorVer_localPt[IndiceJ+1],
           scene->ArrayNorVer_localPt[IndiceJ+5]+30*scene->ArrayNorVer_localPt[IndiceJ+2]);
       glEnd();
 }


    glFlush();
};

///++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::paintGL()
{ int i;
  static int increase =1;

  LocalScene.PolyNumber = NbPolygnNbVertex[2*IndiceMorphFrame];
  i          = NbPolygnNbVertex[2*IndiceMorphFrame+1];
  LocalScene.PolyIndices_localPt = &(PolyIndices_local[i]);

  if(LocalScene.morph  != 1 ) draw(&LocalScene);
  else {
  draw(&LocalScene);
  IndiceMorphFrame +=increase;
  if(IndiceMorphFrame == NbMorphFrame) {
   increase *= -1; IndiceMorphFrame +=increase;};
  if(IndiceMorphFrame < 0) {
   increase *= -1; IndiceMorphFrame +=increase;};
}
//if(LocalScene.infos == 1)  PrintInfos2(&LocalScene);
if(LocalScene.infos == 1)  PrintInfos();
}
///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::boxok(){
GLfloat minx= 999999999, miny= 999999999, minz= 999999999,
        maxx=-999999999, maxy=-999999999, maxz=-999999999;
int i, nbvertex;
(LocalScene.typedrawing ==1) ? nbvertex = (int)NbPolygnNbVertex[0]/3 :
                               nbvertex = (int)NbPolygnNbVertex[0]/4 ;

for(i=0; i< nbvertex; i++) {
if(minx >ArrayNorVer_local[6*i+3]) minx = ArrayNorVer_local[6*i+3];
if(miny >ArrayNorVer_local[6*i+4]) miny = ArrayNorVer_local[6*i+4];
if(minz >ArrayNorVer_local[6*i+5]) minz = ArrayNorVer_local[6*i+5];

if(maxx <ArrayNorVer_local[6*i+3]) maxx = ArrayNorVer_local[6*i+3];
if(maxy <ArrayNorVer_local[6*i+4]) maxy = ArrayNorVer_local[6*i+4];
if(maxz <ArrayNorVer_local[6*i+5]) maxz = ArrayNorVer_local[6*i+5];
}

BoxLimits[0][0] = minx;
BoxLimits[1][0] = miny;
BoxLimits[2][0] = minz;

BoxLimits[0][5] = maxx;
BoxLimits[1][5] = maxy;
BoxLimits[2][5] = maxz;



glDeleteLists(LocalScene.boxliste, 1);
LocalScene.boxliste = glGenLists(1);
 glNewList(LocalScene.boxliste, GL_COMPILE );

  glLineWidth(2);
   glColor3f (1., 0.0, 0.0);
   glBegin( GL_LINES );

glVertex3f(BoxLimits[0][0], BoxLimits[1][0], BoxLimits[2][0]);
glVertex3f(BoxLimits[0][5], BoxLimits[1][0], BoxLimits[2][0]);
glVertex3f(BoxLimits[0][5], BoxLimits[1][0], BoxLimits[2][0]);
glVertex3f(BoxLimits[0][5], BoxLimits[1][5], BoxLimits[2][0]);
glVertex3f(BoxLimits[0][5], BoxLimits[1][5], BoxLimits[2][0]);
glVertex3f(BoxLimits[0][0], BoxLimits[1][5], BoxLimits[2][0]);
glVertex3f(BoxLimits[0][0], BoxLimits[1][5], BoxLimits[2][0]);
glVertex3f(BoxLimits[0][0], BoxLimits[1][0], BoxLimits[2][0]);


glVertex3f(BoxLimits[0][0], BoxLimits[1][0], BoxLimits[2][5]);
glVertex3f(BoxLimits[0][5], BoxLimits[1][0], BoxLimits[2][5]);
glVertex3f(BoxLimits[0][5], BoxLimits[1][0], BoxLimits[2][5]);
glVertex3f(BoxLimits[0][5], BoxLimits[1][5], BoxLimits[2][5]);
glVertex3f(BoxLimits[0][5], BoxLimits[1][5], BoxLimits[2][5]);
glVertex3f(BoxLimits[0][0], BoxLimits[1][5], BoxLimits[2][5]);
glVertex3f(BoxLimits[0][0], BoxLimits[1][5], BoxLimits[2][5]);
glVertex3f(BoxLimits[0][0], BoxLimits[1][0], BoxLimits[2][5]);

glColor3f (0.0, 0.0, 1.0);
glVertex3f(BoxLimits[0][0], BoxLimits[1][0], BoxLimits[2][0]);
glVertex3f(BoxLimits[0][0], BoxLimits[1][0], BoxLimits[2][5]);

glVertex3f(BoxLimits[0][5], BoxLimits[1][0], BoxLimits[2][0]);
glVertex3f(BoxLimits[0][5], BoxLimits[1][0], BoxLimits[2][5]);

glVertex3f(BoxLimits[0][5], BoxLimits[1][5], BoxLimits[2][0]);
glVertex3f(BoxLimits[0][5], BoxLimits[1][5], BoxLimits[2][5]);

glVertex3f(BoxLimits[0][0], BoxLimits[1][5], BoxLimits[2][0]);
glVertex3f(BoxLimits[0][0], BoxLimits[1][5], BoxLimits[2][5]);

 glEnd();

    glLineWidth(0.9);
   glColor3f (gridliner, gridlineg, gridlineb);
 glEndList();

}
///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::mouseReleaseEvent( QMouseEvent *){
     };

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::mousePressEvent( QMouseEvent * e)
{
    if ( e->button() == QMouseEvent::LeftButton ) btgauche = 1;
    else btgauche = 0;
    if ( e->button() == QMouseEvent::RightButton ) btdroit = 1;
    else btdroit = 0;
    if ( e->button() == QMouseEvent::MidButton ) btmilieu = 1;
    else btmilieu = 0;

    old_y = oldRoty = e->y();
    old_x = oldRotx = e->x();

}

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::mouseMoveEvent( QMouseEvent *e )
{
   RotStrength = sqrt((oldRotx-e->x())*(oldRotx-e->x()) +
                       (oldRoty-e->y())*(oldRoty-e->y()))/2.;
   oldRoty = e->y();
   oldRotx = e->x();

// Scale function :
 if(btdroit ==1)  {
   if(old_y - e->y() > 0 ) ScalCoeff = 1.02f;
   else if( ScalCoeff > 0.1f ) ScalCoeff = 0.98f;
   glScalef(ScalCoeff, ScalCoeff, ScalCoeff);
   view_rotx = view_roty = 0.0;
 }
// Rotational function :
 if(btgauche ==1) {
 view_roty = -(old_y - e->y());
 view_rotx = -(old_x - e->x());
 ScalCoeff = 1.0;

  glGetIntegerv(GL_VIEWPORT,viewport);
  glGetDoublev(GL_MODELVIEW_MATRIX,matrix);

   memcpy(m, matrix, 16*sizeof(GLdouble));

  ///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++///
   GLdouble det;
   GLdouble d12, d13, d23, d24, d34, d41;
   GLdouble tmp[16]; /* Allow out == in. */

   /* Inverse = adjoint / det. (See linear algebra texts.)*/
   /* pre-compute 2x2 dets for last two rows when computing */
   /* cofactors of first two rows. */
   d12 = (m31*m42-m41*m32);
   d13 = (m31*m43-m41*m33);
   d23 = (m32*m43-m42*m33);
   d24 = (m32*m44-m42*m34);
   d34 = (m33*m44-m43*m34);
   d41 = (m34*m41-m44*m31);

   tmp[0] =  (m22 * d34 - m23 * d24 + m24 * d23);
   tmp[1] = -(m21 * d34 + m23 * d41 + m24 * d13);
   tmp[2] =  (m21 * d24 + m22 * d41 + m24 * d12);
   tmp[3] = -(m21 * d23 - m22 * d13 + m23 * d12);

   /* Compute determinant as early as possible using these cofactors. */
   det = m11 * tmp[0] + m12 * tmp[1] + m13 * tmp[2] + m14 * tmp[3];

   /* Run singularity test. */
   if (det == 0.0) {
      printf("invert_matrix: Warning: Singular matrix.\n");
/*    memcpy(out,_identity,16*sizeof(double)); */
   }
   else {
      GLdouble invDet = 1.0 / det;
      /* Compute rest of inverse. */
      tmp[0] *= invDet;
      tmp[1] *= invDet;
      tmp[2] *= invDet;
      tmp[3] *= invDet;

      tmp[4] = -(m12 * d34 - m13 * d24 + m14 * d23) * invDet;
      tmp[5] =  (m11 * d34 + m13 * d41 + m14 * d13) * invDet;
      tmp[6] = -(m11 * d24 + m12 * d41 + m14 * d12) * invDet;
      tmp[7] =  (m11 * d23 - m12 * d13 + m13 * d12) * invDet;

      /* Pre-compute 2x2 dets for first two rows when computing */
      /* cofactors of last two rows. */
      d12 = m11*m22-m21*m12;
      d13 = m11*m23-m21*m13;
      d23 = m12*m23-m22*m13;
      d24 = m12*m24-m22*m14;
      d34 = m13*m24-m23*m14;
      d41 = m14*m21-m24*m11;

      tmp[8] =  (m42 * d34 - m43 * d24 + m44 * d23) * invDet;
      tmp[9] = -(m41 * d34 + m43 * d41 + m44 * d13) * invDet;
      tmp[10] =  (m41 * d24 + m42 * d41 + m44 * d12) * invDet;
      tmp[11] = -(m41 * d23 - m42 * d13 + m43 * d12) * invDet;
      tmp[12] = -(m32 * d34 - m33 * d24 + m34 * d23) * invDet;
      tmp[13] =  (m31 * d34 + m33 * d41 + m34 * d13) * invDet;
      tmp[14] = -(m31 * d24 + m32 * d41 + m34 * d12) * invDet;
      tmp[15] =  (m31 * d23 - m32 * d13 + m33 * d12) * invDet;

      memcpy(matrixInverse, tmp, 16*sizeof(GLdouble));
   }

            double ax,ay,az;

            ax = view_roty;
            ay = view_rotx;
            az = 0.0;
            angle = sqrt(ax*ax + ay*ay)/(double)(viewport[2]+1)*360.0;

            /* Use inverse matrix to determine local axis of rotation */

            axe_x = Axe_x = matrixInverse[0]*ax + matrixInverse[4]*ay;
            axe_y = Axe_y = matrixInverse[1]*ax + matrixInverse[5]*ay;
            axe_z = Axe_z = matrixInverse[2]*ax + matrixInverse[6]*ay;
  ///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++///

     glRotatef(angle,Axe_x,Axe_y,Axe_z);
 }

 old_y = e->y();
 old_x = e->x();
 updateGL();
}

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::resizeGL( int newwidth, int newheight)
{ int tmp, starth, startw;
    CornerH = (int)(newheight/2);
    CornerW = (int)(newwidth/2);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(newwidth > newheight) {tmp = newwidth;
     starth=(newwidth-newheight)/4;startw=0;
     }
    else {tmp = newheight;
    startw = (newheight-newwidth)/4;starth=0;
    }
    glViewport(0, 0, tmp, tmp);
    glFrustum(-250+startw, 250+startw, -250+starth, 250+starth, 350.0, 3000.0 );

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef( 0.0, 0.0, -800.0 );
}

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::DrawPlan(){
   GLuint list;

 list = glGenLists(1);
 glNewList( list, GL_COMPILE );

glBegin( GL_LINE );
glVertex3f(-400.0, 0.0, -400.0);
glNormal3f(0.0, 0.0, 1.0);

glVertex3f(-400.0, 0.0, 400.0);
glNormal3f(0.0, 0.0, 1.0);

glVertex3f(400.0, 0.0, 400.0);
glNormal3f(0.0, 0.0, 1.0);

glVertex3f(400.0, 0.0, -400.0);
glNormal3f(0.0, 0.0, 1.0);
glEnd();

 glEndList();
//    return list;
}

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/*
static void draw()
{
   glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);

   if(GlLneSmooth == 1) {
   glEnable (GL_LINE_SMOOTH);
   glEnable (GL_BLEND);
   glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   glHint (GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
   }

    //glRotatef(angle,bx,by,bz);
    //glScalef(ScalCoeff, ScalCoeff, ScalCoeff);

    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(polyfactor, polyunits);
    glDrawElements(GL_QUADS, NB_Poly , GL_UNSIGNED_INT, PolyIndices_pt);
    glDisable(GL_POLYGON_OFFSET_FILL);

    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    glLineWidth(0.5);
    glColor3f (0.2, 0.4, 0.2);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawElements(GL_QUADS, NB_Poly , GL_UNSIGNED_INT, PolyIndices_pt);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glFlush();
}

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
GLuint OpenGlWidget::makeObject()
{
   int i, j;
   GLuint list;

 list = glGenLists(1);
 glNewList( list, GL_COMPILE );

    for (i=0; i< nb_ligne - coupure_ligne ; i++)
      for (j=0; j< nb_colone - coupure_col ; j++) {

glBegin( GL_QUADS );
glVertex3f(M3dObjet[i*3][j], M3dObjet[i*3+1][j],M3dObjet[i*3+2][j]);
glNormal3f(NorObjet[i*3][j], NorObjet[i*3+1][j], -NorObjet[i*3+2][j]);

glVertex3f(M3dObjet[(i+1)*3][j], M3dObjet[(i+1)*3 +1][j],M3dObjet[(i+1)*3+2][j]);
glNormal3f(NorObjet[(i+1)*3][j], NorObjet[(i+1)*3 +1][j], -NorObjet[(i+1)*3+2][j]);

glVertex3f(M3dObjet[(i+1)*3][j+1], M3dObjet[(i+1)*3+1][j+1],M3dObjet[(i+1)*3 +2][j+1]);
glNormal3f(NorObjet[(i+1)*3][j+1], NorObjet[(i+1)*3+1][j+1], -NorObjet[(i+1)*3 +2][j+1]);

glVertex3f(M3dObjet[i*3][j+1], M3dObjet[i*3 +1][j+1],M3dObjet[i*3+2][j+1]);
glNormal3f(NorObjet[i*3][j+1], NorObjet[i*3 +1][j+1], -NorObjet[i*3+2][j+1]);
glEnd();

}
    glEndList();
    return list;
}

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
GLuint OpenGlWidget::makeGrid()
{
   int i, j;
   static GLfloat ared[4] = {1.0, 0.0, 0.0, 1.0 };
   GLuint list;

    list = glGenLists( 1 );
    glNewList( list, GL_COMPILE );
    //glLineWidth( 3.0 );
    //glColor3f(255.0, 255.0, 255.0);

 for (i=0;i<nb_ligne - coupure_ligne ;i++)
    for (j=0; j<nb_colone - coupure_col ; j++)

{
glBegin(GL_LINE_LOOP);
glVertex3f(M3dObjet[i*3][j], M3dObjet[i*3+1][j],M3dObjet[i*3+2][j]);
glVertex3f(M3dObjet[(i+1)*3][j], M3dObjet[(i+1)*3 +1][j],M3dObjet[(i+1)*3+2][j]);
glVertex3f(M3dObjet[(i+1)*3][j+1], M3dObjet[(i+1)*3+1][j+1],M3dObjet[(i+1)*3 +2][j+1]);
glVertex3f(M3dObjet[i*3][j+1], M3dObjet[i*3 +1][j+1],M3dObjet[i*3+2][j+1]);
glEnd();
}
    glEndList();
    return list;
}

*/
///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::timerEvent(QTimerEvent*)
{
    updateGL();
}

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::update()
{
    updateGL();
}

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::cutline(int){
}

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::step_morph(int){
}

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::latence_change(int){
}

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::linecolumn(int){
}

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::cutcolumn(int){
}

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::newFile()
{}

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::clipok()
{}

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::setFunction(int)
{}

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void OpenGlWidget::newGear()
{}

///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
OpenGlWidget::~OpenGlWidget()
{  delete(timer);
}
