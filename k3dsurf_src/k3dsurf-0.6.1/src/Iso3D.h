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
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA            *
 ***************************************************************************/
#include <qgl.h>
#include <qpointarray.h>
#include <qpainter.h>
#include <qbrush.h>
#include <qstring.h>
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <list>
#include "IsoMatrix3D.h"
#include "fparser/fparser.h"

using std::string;
using std::vector;
using std::list;
/*


                     4.-----------4----------------.5
                     /|                           /|
                    7 |                          5 |
                   /  |                         /  |
                 7.---|-----------6------------.6  |
                  |   |                        |   |
                  |   8                        |   9
                  |   |                        |   |
                  |   ^ j                      |   |
                 11   |                       10   |
                  |   |     i                  |   |
                  |  0.----->-----0------------|---.1
                  |  /                         |  /
                  | 3 k                        | 1
                  |/                           |/
                 3.---------------2------------.2
*/


///************* A new Structure that represents a Voxel *********///
struct  Voxel {
   double PositionX, PositionY, PositionZ;
    int Edge_Points [12]; //reference to the Edge Points
    int  Signature; // From 0 to 255
    int NbEdgePoint;
    int Index[4];
    double Value;   // The value of the implicit function.
                  };

///************* A new Structure that represents a Triangle *********///
struct  IsoTriangle {
   QPointArray * pl;
   double valeur_z;
   double valeur_cos;
   int TypeCND; /// Two types : 1 --> Draw like a normal triangle; 2 --> Draw in Red
                  };




class Iso3D {
public :


   double IsoPointMapOriginal[3*60000]; // Up to 40.000 Pts
   double IsoPointMapProjectd[3*10000]; // Up to 40.000 Pts
   double IsoPointMapTransfrm[3*60000]; // Up to 40.000 Points

/// Conditional data :
   int WichPointVeryCond[100000];
   int TypeIsoSurfaceTriangleListeCND[100000]; // From 1 to 7 Up to 100.000
   double IsoPointMapOriginalCD[3*10000]; // Up to 10.000 Pts
   double IsoPointMapProjectdCD[3*10000]; // Up to 10.000 Pts
   double IsoPointMapTransfrmCD[3*10000]; // Up to 10.000 Points

   double IsoNormMapOriginal[3*100000]; // Up to 100.000 Norm
   double IsoNormMapTransfrm[3*100000]; // Up to 100.000 Norm


   double AxeArrayOriginal[3][150];           // 3D Axes X, y and Z with 50 points
   double AxeArrayProjectd[3][150];           // 3D Axes X, y and Z with 50 points
   double AxeArrayTransfrm[3][150];           // 3D Axes X, y and Z with 50 points

   int IsoSurfaceTriangleListe[3*100000];// Up to 100.000 Triangles
   int IsoSurfaceTriangleListeCND[3*10000];// Up to 10.000 Triangles

   double NormTransfrm[3*100000];// Up to 100.000 Triangles
   double NormOriginal[3*100000];// Up to 100.000 Triangles
   double FileOutput[180000]; /// Up to 10.000 Triangles= (3 x 3 Points)

   int NbPointIsoMap; // Init to 0 ; Up to 10.000
   int NbPointIsoMapCND; // Init to 0 ; Up to 10.000
   int NbTriangleIsoSurface;
   int NbTriangleIsoSurfaceCND;
   int i,j,k,l;
   FunctionParser ImplicitFunctionParser,
                  XSupParser, XInfParser,
                  YSupParser, YInfParser,
                  ZSupParser, ZInfParser,
                  IsoConditionParser,
                  ExpressionEvaluator,
Iso;
   QString ImplicitFunction, IsoCondition,
           XlimitSup, XlimitInf,
           YlimitSup, YlimitInf,
           ZlimitSup, ZlimitInf,

           ImplicitFunction_save,
           XlimitSup_save, XlimitInf_save,
           YlimitSup_save, YlimitInf_save,
           ZlimitSup_save, ZlimitInf_save;

   double newcoeffx, newcoeffy, newcoeffz;
   double X_Start, X_End, X_Step,
          Y_Start, Y_End, Y_Step,
          Z_Start, Z_End, Z_Step;
    int nb_ligne, nb_colon, nb_depth, 
        clipping, CutLigne, CutColon, CutDepth,
        IsoConditionRequired;
    double D; // Distance observator
    double Oprime[3], Obser[3];
    double MINX,MINY,MINZ,MINW,MINT,MINS,
           MAXX,MAXY,MAXZ,MAXW,MAXT,MAXS,
           DIFX,DIFY,DIFZ,DIFW,DIFT,DIFS,
           DIFMAXIMUM, decalage_xo, decalage_yo, decalage_zo,
           IsoValue, anglex, angley, ancienx, ancieny, ScalCoeff,
           morph_param, step, axe_size,
           newscalex, newscaley, newscalez;
    int    demi_hauteur, demi_largeur, hauteur_fenetre;
    IsoMatrix3D MatGen, MatRot, MatRotSave, MatSca, MatInv;
    int  frontsurfr, frontsurfg, frontsurfb,
         backsurfr,  backsurfg,  backsurfb,
         CNDsurfr,  CNDsurfg,  CNDsurfb,
         gridr, gridg, gridb, gridtransparent,
         PovActivate, fronttrans, backtrans, CNDtrans;
    QPointArray *tableaureferences[10000];
    IsoTriangle * tableau;
    QPointArray  isotriangle;
    vector<IsoTriangle *> VectorIsoTriangle;
    QBrush palette_front_face[256], palette_back_face[256], palette_CND[256];
    QColor palette_grid[256];
    int IsoMesh, IsoInfos, NbTriangleUsed,
        axe_width, axe_center, DrawAxe_Ok, CNDMesh,
        CNDDraw, BorderDraw, Borderlimite;

int NbPolygonImposedLimit ;
GLfloat NormVertexTab[50*66000];
GLuint IndexPolyTab[50*48000];
int NbVertex;
GLuint NbPolygn;
GLuint NbPolygnNbVertex[2*50];
int CurrentStep; /// To hold the current step in the Morph process
public :
   Iso3D();
   ~Iso3D();
   void VoxelEvaluation ();
   void PointEdgeComputation();
   void DrawIsoSurface();
   void InitParser();
   void InitParameter();
   void SignatureComputation();
   void ConstructIsoSurface();
   void ConstructIsoNormale();
   void ProjectIsoMap();
   void RotateIsoMap();
   void TranslateIsoMap();
   void ScaleIsoMap();
   void BoxIsoMap();
   void ApplicateTransform();
   void ApplicateProjection();
   void DrawIsoMap(QPainter &);
   void Rotate();
   void AnimMorph();
   void Scale();
   void PaletteInit();
   void ComputeIsoMap();
   void ParseExpression();
   void CutIsoSurface();
   void SaveIsoMap();
   void SaveIsoMapUnifColor();

   void scalex(int);
   void scaley(int);
   void scalez(int);

  void twistex(double, double);
  void twistey(double, double);
  void twistez(double, double);

/// FOR GL Window :
 void SpecialAnim_1();
 void SpecialAnim_2(GLfloat *, GLuint *);
 void SpecialAnim_3(GLfloat *, GLuint *);

 void SpecialMorph_1();
 void SpecialMorph_2(GLfloat *, GLuint *, GLuint *, int *, int *, int);
 void SpecialMorph_3(GLfloat *, GLuint *);
 void SaveIsoGLMap();
};




