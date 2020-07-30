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
#ifndef gear_H
#define gear_H

#include <qthread.h>
#include <qgl.h>
#include <qapplication.h>
#include <math.h>
#include <qthread.h>
#include <qmutex.h>
#include <qpixmap.h>
#include <qwidget.h>
#include <qpainter.h>
#include <qmessagebox.h>
#include <qfile.h>
#include <qdir.h>
#include <qpngio.h>
#include <stdlib.h>
#include <string>
#include <qtimer.h>







/* NB. OpenGL Matrices are COLUMN major. */
#define MAT(m,r,c) (m)[(c)*4+(r)]

/* Here's some shorthand converting standard (row,column) to index. */
#define m11 MAT(m,0,0)
#define m12 MAT(m,0,1)
#define m13 MAT(m,0,2)
#define m14 MAT(m,0,3)
#define m21 MAT(m,1,0)
#define m22 MAT(m,1,1)
#define m23 MAT(m,1,2)
#define m24 MAT(m,1,3)
#define m31 MAT(m,2,0)
#define m32 MAT(m,2,1)
#define m33 MAT(m,2,2)
#define m34 MAT(m,2,3)
#define m41 MAT(m,3,0)
#define m42 MAT(m,3,1)
#define m43 MAT(m,3,2)
#define m44 MAT(m,3,3)


   static GLfloat RotStrength=0, oldRotx, oldRoty;
   static GLfloat zminim = -400.0, BoxLimits[3][6];
   static GLfloat gridline[4], background[4];

   static GLint viewport[4];
   static GLdouble m[16];
   static GLfloat polyfactor = 1.0;
   static GLfloat polyunits = 1.0;
   static int NBGlWindow = 0;
   static double matrix[16];
   static double matrixInverse[16];

   static double axe_x, axe_y, axe_z, ScalCoeff, view_rotx, view_roty, view_rotz;
   static int IndiceI, IndiceJ;

///************* A new Structure the scene *********///
struct  Scene {
    GLfloat * ArrayNorVer_localPt;
    GLuint  * PolyIndices_localPt;
    GLuint  * NbPolygnNbVertexPt ;
    GLfloat * ArrayNorVer_localPtCND;

    GLuint   *PolyIndices_localVerifyCND;
    GLuint   *PolyIndices_localNotVerifyCND;
    GLuint   *PolyIndices_localBorderCND;

    GLint PolyNumber;
    GLint PolyNumberBorderCND;
    GLint PolyNumberVerifyCND;
    GLint PolyNumberNotVerifyCND;

    GLint border;
    GLint cndmesh;
    GLint drawcnd;

    GLfloat *greencol;
    GLfloat *goldcol;

    GLint anim;
    GLint morph;
    GLint typedrawing; /// Triangle or
    GLint mesh;
    GLint front;
    GLint back;
    GLint smoothline;
    GLint smoothpoly;
    GLint box;
    GLint interior;
    GLint exterior;
    GLint infos;
    GLint line; ///Draw line on top of filled polygons
    GLint axe;
    GLint clip;
    GLint norm;
    GLint plan;
    GLint condition;
    GLuint axeliste;
    GLuint boxliste;
    GLuint planliste;
    
    GLuint moreliste[10];
    GLuint *morelistept[10];
    GLfloat *morefloatpt[10];
    GLfloat morefloat[10];
              };

class OpenGlWidget : public QGLWidget, public QThread
{    Q_OBJECT
public :
    int colortype, btgauche, btdroit, btmilieu,
    width, height, latence,
    nb_ligne, nb_colone, coupure_col, coupure_ligne,
    IDGlWindow, PolyNumber, VertexNumber,
    IndiceMorphFrame, NbMorphFrame;
    int isoline, isocolumn, isodepth,
        cpisoline, cpisocolumn, cpisodepth;
    QTimer *timer;
    int       greenbackground,
              bluebackground, redbackground, TypeTriangle;

    GLfloat  ArrayNorVer_local[50*66000];
    GLuint   PolyIndices_local[50*48000];
    

    int TypeIsoSurfaceTriangleListeCND[100000];
    
    GLuint NbPolygnNbVertex[2*50];
    int  PolyNumberTab[50];
    double Axe_x, Axe_y, Axe_z, angle, val1, val2, val3, old_x, old_y, old_z;
    GLfloat gridliner, gridlineg, gridlineb;
    GLfloat greencol[4] ;
    GLfloat goldcol[4] ;

    Scene  LocalScene;
    int jpg_ok, png_ok, bmp_ok, quality_image;
    QPixmap * pixmap;
public:
    OpenGlWidget( QWidget *parent=0, const char *name=0 );
    ~OpenGlWidget();
    void initializeGL();
    void resizeGL( int, int );
    void paintGL();
    void update();
    void timerEvent( QTimerEvent * );
    //GLuint makeObject();
    //GLuint makeGrid();
    void mousePressEvent( QMouseEvent *);
    void mouseMoveEvent( QMouseEvent *);
    void mouseReleaseEvent( QMouseEvent *);
    virtual   void run();
    void valueChanged();
    void InitGlParameters();
    void InitGlMorph();
public slots:
    void newFile();
    void newGear();
    void setFunction(int);
    void cutline(int);
    void cutcolumn(int);
    void linecolumn(int);
    void boxok();
    void anim();
    void morph();
    void start();
    void starttimer();
    void stoptimer();
    bool timeractif();
    void restarttimer(int);
    void cnd();
    void cndmesh();
    void drawborder();
    void PrintInfos();
    void png();
    void jpg();
    void bmp();
    void quality(int);
    void screenshot();
    void conditionok();
    void clipok();
    void infosok();
    void latence_change(int);
    void step_morph(int);
    void red(int);
    void green(int);
    void blue(int);
    void transparence();
    void scalcoeff(double);
    void CutLineIndex(int );
    void CutColIndex(int );
    void plan();
    void fog();
    void meshOk();
    void smoothpoly();
    void smoothline();
    void frontSurf();
    void backSurf();
    void clipOk();
    void axeOk();
    void normOk();
    void infosOk();
    void boxOk();
    void lineOk();
    void DrawPlan();
};

#endif
