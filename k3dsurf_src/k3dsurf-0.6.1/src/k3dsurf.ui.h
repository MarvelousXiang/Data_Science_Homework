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
#include <qevent.h>
#include <iostream>
#include <qmessagebox.h>
#include <qscrollbar.h>
#include <qfile.h>
#include <qstatusbar.h>
#include <qcheckbox.h>
#include <qmovie.h>
#include "GlWindow.h"
#include "newwindow2.h"
#include "IsoWindow.h"
#include "drawingoptions.h"



int  smooth_triangle =1, mesh_parametric =1, pausewhendone = 1, verbose = -1,
     continu = -1, testabort = 1, drawvista = -1, ImageSize_Field_changed =-1,
     continuecheckbox = -1, outputfile = -1, inputfile = -1, outputbuffer = -1,
     implicite_fct = -1, parametrique_ok = 1,
     fourdimshapes = -1, fivedimshapes = -1, sixdimshapes = -1,
     separatecheckogjects = -1, tria_nas = -1, inverse_condition = -1,
     activate_cd = -1, activate_isocd = -1, activate_supershape = -1, add_condition = -1 , condition_mesh = 1,
     draw_poly_normals = -1, activate_tools = -1, axechoice = 1, objfile_triangle = -1, isomesh =-1, activateiso = -1, inverse_isocondition = -1;

int spheric_fct = -1, cylindric_fct = -1;
int implicit_param = 1, implicit_spheric = -1, implicit_cylindric = -1;
int NbStep =30;
int paramwidgetstack = 1, isowidgetstack =1;
QString     xterm="", 
            Width="+W400", Height="+H400", 
            Start_RowEdit="", End_RowEdit="", 
            Start_ColumnEdit="", End_ColumnEdit="", 
            Test_Abort_CountEdit="X50",
            Pause_When_Done = "+P",
            Continue ="", 
            Output_File_NameEdit="+Oscene", FileExtension=".tga  +FT ",
            Input_File_NameEdit="+Itest.pov",
            OutPutBuffer="", IncludeHeaderFile="", LibraryPath="";

///+++++++++++++++++++++++++++++///
void k3dsurface::Axes_center() {
//if(activateiso == 1) isoWidget->Axes_center();
    if(tabsurf->currentPageIndex() == 1) isoWidget->Axes_center();
    else connectWidget2->Axes_center();
}
///+++++++++++++++++++++++++++++///
void k3dsurface::Axes_draw() {
//if(activateiso == 1) isoWidget->Axes_draw();

 if(tabsurf->currentPageIndex() == 1)  isoWidget->Axes_draw();
else connectWidget2->Axes_draw();
}

///+++++++++++++++++++++++++++++///
void k3dsurface::Axes_width (int cl) {
//if(activateiso == 1) isoWidget->Axes_width(cl);
    if(tabsurf->currentPageIndex() == 1)  isoWidget->Axes_width(cl);
    else connectWidget2->Axes_width(cl);
}

///+++++++++++++++++++++++++++++///
void k3dsurface::Axes_size (int cl) {
    if(tabsurf->currentPageIndex() == 1) isoWidget->Axes_size(cl);
    else connectWidget2->Axes_size(cl);
}

///+++++++++++++++++++++++++++++///
void k3dsurface::bluecl(int cl) {
    if(tabsurf->currentPageIndex() == 1) {
     isoWidget->blue(cl);
     IsoGlWidget->blue(cl);}
    else {
    connectWidget2->blue(cl);
    ParamGlWidget->blue(cl);}
}
///+++++++++++++++++++++++++++++///
void k3dsurface::redcl(int cl) {
    if(tabsurf->currentPageIndex() == 1)  {
    isoWidget->red(cl);
    IsoGlWidget->red(cl);}
    else {
    connectWidget2->red(cl);
    ParamGlWidget->red(cl);}
}

///+++++++++++++++++++++++++++++///
void k3dsurface::greencl(int cl) {
    if(tabsurf->currentPageIndex() == 1)  {
 isoWidget->green(cl);
 IsoGlWidget->green(cl);}
    else {
 connectWidget2->green(cl);
 ParamGlWidget->green(cl);}
}

///+++++++++++++++++++++++++++++///
void k3dsurface::transparencecl() {
    if(tabsurf->currentPageIndex() == 1)  {
              isoWidget->transparence();
              IsoGlWidget->transparence();}
    else {  connectWidget2->transparence();
              ParamGlWidget->transparence();}
}

///+++++++++++++++++++++++++++++///

void k3dsurface::iso_Fct_activated(){

activateiso *= -1;
/*
if(activateiso == 1) {
IsoBox->setEnabled(TRUE);
isotoolBox->setEnabled(TRUE);
tabsurf->setCurrentPage(1);
//widgetStack->raiseWidget(WStackPage1);
    }
else {
IsoBox->setEnabled(FALSE);
isotoolBox->setEnabled(FALSE);
tabsurf->setCurrentPage(0);
//widgetStack->raiseWidget(WStackPage2);
}
*/
//update();
}
//====================================

void k3dsurface::iso_mesh()
{
 isomesh *=-1; ///To use for deactivating some components in the interface
 isoWidget->IsoObjet->IsoMesh*= -1;
 IsoGlWidget->meshOk();
    
/// Update Iso page :
    IsoPageUpdate(); 
}
//====================================

void k3dsurface::iso_infos()
{
 isoWidget->IsoObjet->IsoInfos*= -1;
 IsoGlWidget->infosOk();
/// Update Iso page :
    IsoPageUpdate(); 
 
}
//====================================

void k3dsurface::trianglemesh_clicked()
{
objfile_triangle *= -1;
}
//====================================
void k3dsurface::axex_choice(){
 axechoice = 0;
}
//====================================
void k3dsurface::axey_choice(){
 axechoice = 1;
}
//====================================
void k3dsurface::axez_choice(){
 axechoice = 2;
}
//====================================
/*
void k3dsurface::Draw_Normals(){

    draw_poly_normals *= -1;
     connectWidget2->objet->draw_poly_normals = draw_poly_normals;
    connectWidget2->update();

}
*/
//====================================

void k3dsurface::addcondt(){
     add_condition*= -1;
     connectWidget2->objet->draw_hidden_poly_and_nonhidden = add_condition;
    connectWidget2->update();
}

//====================================

void k3dsurface::meshcondt(){
    condition_mesh *= -1;
    connectWidget2->objet->draw_cond_mesh = condition_mesh;
}

//====================================

void k3dsurface::inverse_cond(){

    inverse_condition  *= -1;
    if(inverse_condition  == 1) 
 connectWidget2->objet->condition_expression = QString("("+condition->text()+") = 0");
    else  connectWidget2->objet->condition_expression  = condition->text();

    perform();
   //connectWidget2->update();
}
//====================================

void k3dsurface::inverse_isocond(){

    inverse_isocondition  *= -1;
    if(inverse_isocondition  == 1) 
    isoWidget->IsoObjet->IsoCondition = QString("("+Isocondition->text()+") = 0");
    else  isoWidget->IsoObjet->IsoCondition  = Isocondition->text();

    PerformNewImplicitFunct();
}
//====================================
void k3dsurface::activate_cond(){
QMessageBox     message;
        if( paramwidgetstack == 1)
    { 
    message.setText(tr(QString("Not yet supported by the OpenGL viewer\n Turn OFF OpenGL to see the result")));
    message.adjustSize () ;
    message.exec();
    activ_cond->toggle();
    return ;
    }

    activate_cd *= -1;
    if(activate_cd == 1) {
      groupBox25_2->setEnabled(TRUE);
      condition->setEnabled(TRUE);
      inverse_condt->setEnabled(TRUE);
       connectWidget2->objet->there_is_condition *= -1;
           if(inverse_condition  == 1) 
 connectWidget2->objet->condition_expression = QString("("+condition->text()+") = 0");
    else  connectWidget2->objet->condition_expression  = condition->text();
    }
    else {
       groupBox25_2->setEnabled(FALSE);
       //condition->setEnabled(FALSE);
       //inverse_condt->setEnabled(FALSE);
       connectWidget2->objet->there_is_condition *= -1; 
    }
    perform();
    //connectWidget2->update();
}
//====================================
void k3dsurface::activate_isocond(){
   /*  QMessageBox     message;

        if( isowidgetstack == 1)
    {
    message.setText(tr(QString("Not yet supported by the OpenGL viewer\n Turn OFF OpenGL to see the result")));
    message.adjustSize () ;
    message.exec();
    Isoactiv_cond->toggle();
    return ;
    }
   */
    activate_isocd *= -1;
    if(activate_isocd == 1) {
       IsogroupBox->setEnabled(TRUE);
       Isocondition->setEnabled(TRUE); /// TO FORCE ENABLE!!!
       cndmesh_2->setEnabled(TRUE); /// TO FORCE ENABLE!!!
       isoWidget->IsoObjet->IsoConditionRequired *= -1;
       IsoGlWidget->conditionok();
       isoWidget->IsoObjet->IsoCondition = Isocondition->text();
    }
    else {
       //Isocondition->setEnabled(FALSE);
       IsogroupBox->setEnabled(FALSE);
       isoWidget->IsoObjet->IsoConditionRequired *= -1;
       IsoGlWidget->conditionok();
    }
    PerformNewImplicitFunct();
}
//========================================
void k3dsurface::activate_frame(){
/*
QMessageBox message ;
QDir dir(Input_Dir_NameEdit->text());
if( !dir.exists()) { 
    message.setText(tr(QString(Input_Dir_NameEdit->text()+" Directory doesn't exists. \
    Create it or chose another one. ")));
    message.adjustSize () ;
    message.exec(); 
    return;
}

connectWidget2->frames_ok *= -1;
connectWidget2->counter = 0;
if(connectWidget2->frames_ok == 1) {
frames->setText("Frames :\n Stop");
}
else frames->setText("Frames :\n Start");
*/
}
//====================================
void k3dsurface::sixdimshape_activate()
{
sixdimshapes *= -1;
if(sixdimshapes == 1) {
scft_5->setEnabled(TRUE);
sfct_5->setEnabled(TRUE);
rotational6d->setEnabled(TRUE);
connectWidget2->objet->sixdimshapes = 1;
}
else {
scft_5->setEnabled(FALSE);
sfct_5->setEnabled(FALSE);
rotational6d->setEnabled(FALSE);
connectWidget2->objet->sixdimshapes = -1;
}
perform_fivedim();
}

//========================================//
//
// Handles mouse move events for the connect widget.
//

void k3dsurface::keyPressEvent ( QKeyEvent * e ) {

///std::cout << e->text();
connectWidget2->objet->keyboard = e->text();
connectWidget2->update();
}


//====================================

void k3dsurface::videorecord(){
/*
    connectWidget2->video_ok *= -1;
    if(connectWidget2->video_ok == 1) video->setText("Video: \n Stop");
    else  video->setText("Video: \n Start");
    connectWidget2->videorecord();
*/
}
//======================================
void k3dsurface::videoplay(){
/*
 videoplayer *player = new videoplayer();
        player->show();
*/
/*
   QMovie *movie = new QMovie("movie.png");
   movie->setSpeed(50);
   QLabel *label = new QLabel("test", 0);
   label->setBackgroundColor(Qt::black) ;
   label->(500, 500);
   label->setMovie(*movie);
   label->show();
*/
}

//====================================
void k3dsurface::loadPov()
{
        editeur *ed = new editeur();
        ed->load("test.pov");
        ed->show();
}
//====================================

void k3dsurface::separateCheckBoxtoggled(){

    separatecheckogjects *= -1;
   if(separatecheckogjects == 1) {
   groupobjects->setEnabled(TRUE);
   firstobj->setEnabled(TRUE) ; //don't know whay it doesn't enable automaticly...
   secondobj->setEnabled(TRUE); //don't know whay it doesn't enable automaticly...


   if(activate_cd == 1) {
      activ_cond->toggle();
      condition->setEnabled(FALSE);
      inverse_condt->setEnabled(FALSE);
       connectWidget2->objet->there_is_condition *= -1;
       activate_cd = -1;
   }

   }
   else groupobjects->setEnabled(FALSE);

   connectWidget2->objet->two_separate_objects *= -1;
   connectWidget2->valueChanged(); 
}
//====================================
void k3dsurface::firstobjtoggled(){

    connectWidget2->objet->change_first_object *= -1;
    if(connectWidget2->objet->change_first_object == 1) {
    connectWidget2->objet->mat = connectWidget2->objet->mat_first_obj;
    connectWidget2->objet->mat_rotation_save = connectWidget2->objet->mat_rotation_first_save;
    }
    else {
    connectWidget2->objet->mat_first_obj           = connectWidget2->objet->mat;
    connectWidget2->objet->mat_rotation_first_save = connectWidget2->objet->mat_rotation_save;
    }
}
//====================================
void k3dsurface::secondobjtoggled(){

    connectWidget2->objet->change_second_object *= -1;
    if(connectWidget2->objet->change_second_object == 1) {
    connectWidget2->objet->mat               = connectWidget2->objet->mat_second_obj;
    connectWidget2->objet->mat_rotation_save = connectWidget2->objet->mat_rotation_second_save;
    }
    else {
    connectWidget2->objet->mat_second_obj           = connectWidget2->objet->mat;
    connectWidget2->objet->mat_rotation_second_save = connectWidget2->objet->mat_rotation_save;
    }

};
//====================================

void k3dsurface::resizeEvent( QResizeEvent  *e ) {
 //For Windows

 if (connectWidget2->anim5_ok != 1 && connectWidget2->anim4_ok != 1 && 
 connectWidget2->anim_ok != 1 && connectWidget2->morph_ok != 1) {
  QSize qs = e->size();QSize qsold = e->oldSize();
  double ancien_hauteur = (double)connectWidget2->objet->demi_hauteur;
  double ancien_largeur = (double)connectWidget2->objet->demi_largeur;
  if(qs.width() > 350) {
   connectWidget2->width  = isoWidget->width  = (qs.width() - 340);
   connectWidget2->height = isoWidget->height  = qs.height(); 

   connectWidget2->setFixedSize (qs.width() - 340, qs.height());
   isoWidget->setFixedSize (qs.width() - 340, qs.height());

   ParamGlWidget->setFixedSize (qs.width() - 340, qs.height());
   IsoGlWidget->setFixedSize (qs.width() - 340, qs.height());

   ParaWidgetStack->setFixedSize (qs.width() - 340, qs.height());
   IsoWidgetStack->setFixedSize (qs.width() - 340, qs.height());
   
   
   delete connectWidget2->pixmap;
   delete isoWidget->pixmap;

   connectWidget2->pixmap = new QPixmap(qs.width()- 340, qs.height());
   isoWidget->pixmap = new QPixmap(qs.width()- 340, qs.height());

   connectWidget2->objet->demi_hauteur = (qs.width() -340)/2;
   connectWidget2->objet->demi_largeur = (qs.height())/2;
   isoWidget->IsoObjet->demi_hauteur = (qs.width() -340)/2;
   isoWidget->IsoObjet->demi_largeur = (qs.height())/2;



/// Parametric Window
   if(connectWidget2->objet->demi_hauteur < connectWidget2->objet->demi_largeur)
     connectWidget2->objet->coefficient = connectWidget2->objet->demi_hauteur/(double)ancien_hauteur;
   else connectWidget2->objet->coefficient = connectWidget2->objet->demi_largeur/(double)ancien_largeur;
   connectWidget2->objet->fct_bouton_droit3();
    
/// Iso Window
   if(isoWidget->IsoObjet->demi_hauteur < isoWidget->IsoObjet->demi_largeur)
     isoWidget->IsoObjet->ScalCoeff = isoWidget->IsoObjet->demi_hauteur/(double)ancien_hauteur;
   else isoWidget->IsoObjet->ScalCoeff = isoWidget->IsoObjet->demi_largeur/(double)ancien_largeur;
   isoWidget->IsoObjet->ScaleIsoMap();

/// OpenGL Window
   if(isoWidget->IsoObjet->demi_hauteur < isoWidget->IsoObjet->demi_largeur)
     ParamGlWidget->scalcoeff(isoWidget->IsoObjet->demi_hauteur/(double)ancien_hauteur);
   else ParamGlWidget->scalcoeff(isoWidget->IsoObjet->demi_largeur/(double)ancien_largeur);
   
   if(isoWidget->IsoObjet->demi_hauteur < isoWidget->IsoObjet->demi_largeur)
     IsoGlWidget->scalcoeff(isoWidget->IsoObjet->demi_hauteur/(double)ancien_hauteur);
   else IsoGlWidget->scalcoeff(isoWidget->IsoObjet->demi_largeur/(double)ancien_largeur);   
   }

 }
else {
    QMessageBox message ;
    message.setText(tr(QString("Please Stop Anim/Morph before Resizing")));
    message.adjustSize () ;
    message.exec();
        return ;
    update();
     }



};

//====================================
/*
void k3dsurface::perform4(){
    FunctionParser fp,f1;
    QMessageBox message ;

    fp.AddConstant("pi", 3.14159265);
    int ret;

        if(connectWidget2->objet->DefineNewFct ==1)
    {
    ret = fp.Parse(fctdef->text(), "u,v,t,x,y");
    if(ret >= 0)
    {


    message.setText(tr(QString("k(u,v,t,x,y)--> At col:")+
         QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec(); 
        return ; 
    }      
          
     f1.Parse(fctdef->text(), "u,v,t,x,y");
     fp.AddFunction("k", f1);
    }
    
    ret = fp.Parse(xcft_2->text(), "u,v,t,x,y"); 
    if(ret >= 0) 
    { 

    message.setText(tr(QString("X=g(u,v)--> At col:")+
         QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();  
  
  
   
        return ; 
    } 
    
    ret = fp.Parse(ycft_2->text(), "u,v,t,x,y");
    if(ret >= 0) 
    { 

    message.setText(tr(QString("Y=g(u,v)--> At col:")+
 QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec(); 
        return ; 
    } 


    
     ret = fp.Parse(zcft_2->text(), "u,v,t,x,y");
    if(ret >= 0) 
    {message.setText(tr(QString("Z=h(u,v)--> At col:")+
        QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();  
    return ; 
    }     


    
     ret = fp.Parse(wcft_2->text(), "u,v,t,x,y");
    if(ret >= 0) 
    {message.setText(tr(QString("W=l(u,v)--> At col:")+
        QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();  
    return ; 
    }




 
  connectWidget2->objet->expression_X = xcft_2->text();
  connectWidget2->objet->expression_Y = ycft_2->text();    
  connectWidget2->objet->expression_Z = zcft_2->text();   
  connectWidget2->objet->expression_W = wcft_2->text();

  connectWidget2->objet->inf_u = umin_2->text();
  connectWidget2->objet->sup_u = umax_2->text();
  connectWidget2->objet->inf_v = vmin_2->text();
  connectWidget2->objet->sup_v = vmax_2->text();
  
     
  // process the new surface
  connectWidget2->valueChanged();     
     
   
}     
*/
//====================================

void k3dsurface::File_Extension_Changed(int choice){
switch(choice) {
case 0 : FileExtension = ".tga  +FC"; break;
case 1 : FileExtension = ".png  +FN8"; break;
case 2 : FileExtension = ".ppm  +FP"; break;
case 3 : FileExtension = ".ss  +FS"; break;
case 4 : FileExtension = ".tga  +FT"; break;
}
}

//====================================
void k3dsurface::Pause_when_Donetoggled(){
    pausewhendone *= -1;
}

//====================================
void k3dsurface::AnimIso(){
  int current_pag = tabsurf->currentPageIndex();

  if(current_pag != 1) tabsurf->setCurrentPage(1);

  if( isowidgetstack != 1)   ParaWidgetStack->raiseWidget ( 0 );     
      IsoGlWidget->anim();
}
//====================================
void k3dsurface::anim_verify_rot4d(){
int current_pag = tabsurf->currentPageIndex();
  if(connectWidget2->anim4_ok == 1)  anim->toggle();

  if(current_pag != 0) tabsurf->setCurrentPage(0);

  if( paramwidgetstack == 1)   ParamGlWidget->anim();
  else  connectWidget2->anim();
}

//====================================
void k3dsurface::morph_verify_rot4d(){
int current_pag = tabsurf->currentPageIndex();
  if(connectWidget2->anim4_ok == 1)  morph->toggle();

  if(current_pag != 0) tabsurf->setCurrentPage(0);

  if(paramwidgetstack == 1) {
connectWidget2->objet->SpecialMorph_2(ParamGlWidget->ArrayNorVer_local, ParamGlWidget->PolyIndices_local, ParamGlWidget->NbPolygnNbVertex, NbStep);
ParamGlWidget->PolyNumber = connectWidget2->objet->NbPolygn;
ParamGlWidget->InitGlMorph();
ParamGlWidget->morph();
}
  else  connectWidget2->morph();
}

//====================================
void k3dsurface::IsoMorph(){
 int current_pag = tabsurf->currentPageIndex();
  if(current_pag != 1) tabsurf->setCurrentPage(1);
  if( isowidgetstack != 1) IsoWidgetStack->raiseWidget ( 0 );

isoWidget->IsoObjet->SpecialMorph_2(
               IsoGlWidget->ArrayNorVer_local,
               IsoGlWidget->PolyIndices_local,
               IsoGlWidget->NbPolygnNbVertex,
               IsoGlWidget->TypeIsoSurfaceTriangleListeCND,
               &(IsoGlWidget->VertexNumber),
               NbStep);
   IsoGlWidget->PolyNumber = connectWidget2->objet->NbPolygn;
   IsoGlWidget->InitGlMorph();  
   IsoGlWidget->morph();

}
//====================================
void k3dsurface::animxy_verify_rot3d(){
if(connectWidget2->anim_ok == 1 || connectWidget2->morph_ok == 1)  xybox->toggle();
}

//====================================
void k3dsurface::animxz_verify_rot3d(){
if(connectWidget2->anim_ok == 1 || connectWidget2->morph_ok == 1)  xzbox->toggle();
}

//====================================
void k3dsurface::animyz_verify_rot3d(){
if(connectWidget2->anim_ok == 1 || connectWidget2->morph_ok == 1)  yzbox->toggle();
}

//====================================
void k3dsurface::animxw_verify_rot3d(){
if(connectWidget2->anim_ok == 1 || connectWidget2->morph_ok == 1)  xwbox->toggle();
}

//====================================
void k3dsurface::animyw_verify_rot3d(){
if(connectWidget2->anim_ok == 1 || connectWidget2->morph_ok == 1)  ywbox->toggle();
}

//====================================
void k3dsurface::animzw_verify_rot3d(){
if(connectWidget2->anim_ok == 1 || connectWidget2->morph_ok == 1)  zwbox->toggle();
}

//====================================
void k3dsurface::newdrawwindow(){

    if(paramwidgetstack == -1) {

newwindow2 * nouvellefenetre = new newwindow2();
*(nouvellefenetre->newwindow->objet) = *(connectWidget2->objet);
nouvellefenetre->newwindow->objet->independantwindow = 1; // to show message h= help
nouvellefenetre->show();

if(connectWidget2->anim_ok == 1 || connectWidget2->morph_ok == 1){
nouvellefenetre->newwindow->anim_ok = connectWidget2->anim_ok ;
nouvellefenetre->newwindow->morph_ok = connectWidget2->morph_ok ;
nouvellefenetre->newwindow->start();
}
else if(connectWidget2->anim4_ok == 1 ) {
         nouvellefenetre->newwindow->anim4_ok = 1;
         nouvellefenetre->newwindow->start();
                                        }
     else if(connectWidget2->anim5_ok == 1 ) {
         nouvellefenetre->newwindow->anim5_ok = 1;
         nouvellefenetre->newwindow->start();
                                        };
 }  /// End of if(current_pag == 0)
    else  {
GlWindow *NewGlWindow = new GlWindow();

NewGlWindow->glWidget->PolyNumber = ParamGlWidget->PolyNumber ;
NewGlWindow->glWidget->LocalScene = ParamGlWidget->LocalScene;
/// Copy in one pass :
memcpy(NewGlWindow->glWidget->ArrayNorVer_local ,
             ParamGlWidget->ArrayNorVer_local ,
             50*66000*sizeof(GLfloat));
memcpy(NewGlWindow->glWidget->PolyIndices_local,
             ParamGlWidget->PolyIndices_local,
             50*48000*sizeof(GLuint));
memcpy(NewGlWindow->glWidget->NbPolygnNbVertex,
             ParamGlWidget->NbPolygnNbVertex,
             100*sizeof(GLuint));

NewGlWindow->show();
    }
}
//====================================
void k3dsurface::isodrawwindow(){

    if(isowidgetstack == 1) {
GlWindow *NewGlWindow = new GlWindow();

NewGlWindow->glWidget->PolyNumber = IsoGlWidget->PolyNumber ;
NewGlWindow->glWidget->LocalScene = IsoGlWidget->LocalScene;
NewGlWindow->glWidget->LocalScene.infos = -1;
/// Copy in one pass :
memcpy(NewGlWindow->glWidget->ArrayNorVer_local ,
             IsoGlWidget->ArrayNorVer_local ,
             50*66000*sizeof(GLfloat));
memcpy(NewGlWindow->glWidget->PolyIndices_local,
             IsoGlWidget->PolyIndices_local,
             50*48000*sizeof(GLuint));
memcpy(NewGlWindow->glWidget->NbPolygnNbVertex,
             IsoGlWidget->NbPolygnNbVertex,
             100*sizeof(GLuint));

NewGlWindow->show();
    }
    else { 
 IsoWindow * newisowin = new IsoWindow();
*(newisowin->isoWidget->IsoObjet) = *(isoWidget->IsoObjet);
newisowin->show();
    }
}

///====================================
void k3dsurface::NewIsoDrawWindow(){

IsoWindow * newisowin = new IsoWindow();
*(newisowin->isoWidget->IsoObjet) = *(isoWidget->IsoObjet);
newisowin->show();
/*
if(connectWidget2->anim_ok == 1 || connectWidget2->morph_ok == 1){
nouvellefenetre->newwindow->anim_ok = connectWidget2->anim_ok ;
nouvellefenetre->newwindow->morph_ok = connectWidget2->morph_ok ;
nouvellefenetre->newwindow->start();
}
else if(connectWidget2->anim4_ok == 1 ) {
         nouvellefenetre->newwindow->anim4_ok = 1;
         nouvellefenetre->newwindow->start();
                                        } 
     else if(connectWidget2->anim5_ok == 1 ) {
         nouvellefenetre->newwindow->anim5_ok = 1;
         nouvellefenetre->newwindow->start();
                                        };
*/
}

//====================================

void k3dsurface::newgldrawwindow(){
//newglwindow::newglwindow * glfenetre = new newglwindow::newglwindow();
//glfenetre->gldrawWidget->objet = new Model3D();//connectWidget2->objet;
//glfenetre->show();
}

//====================================

void k3dsurface::OutPutBuffer_toggled(){
    outputbuffer *= -1;
}

//====================================

void k3dsurface::ContinueCheckBoxtoggled(){

    continuecheckbox *= -1;
}
//====================================

void k3dsurface::Test_AbortCheckboxtoggled(){

    testabort *= -1;
}

//====================================

void k3dsurface::param_toggled(){
/*
    parametrique_ok *= -1;
    if(parametrique_ok == 1) toolBox2->setItemEnabled(0,TRUE);
    else toolBox2->setItemEnabled(0,FALSE);
*/
}

 //====================================
void k3dsurface::cylindric_Fct_activated(){
  QMessageBox message ;

    if(activate_tools == 1) {
    message.setText(tr(QString("Deactivate Tools")));
    message.adjustSize () ;
    message.exec();
    sfactivate->toggle();
        return ;
    }

    if(fourdimshapes == 1 )
    {
    message.setText(tr(QString("Deactivate 4D shapes")));
    message.adjustSize () ;
    message.exec();
    cylindrical->toggle();
        return ; 
    }

    if(implicite_fct  == 1 )
    {
    message.setText(tr(QString("Deactivate Implicit Function")));
    message.adjustSize () ;
    message.exec();
    cylindrical->toggle();
        return ;
    }

    if(spheric_fct  == 1 )
    {
    message.setText(tr(QString("Deactivate Spheric Function")));
    message.adjustSize () ;
    message.exec();
    cylindrical->toggle();
        return ;
    }

    // Deactivate condition
   if(activate_cd == 1) {
      activ_cond->toggle();
      condition->setEnabled(FALSE);
      inverse_condt->setEnabled(FALSE);
       connectWidget2->objet->there_is_condition *= -1;
       activate_cd = -1;
   }
    cylindric_fct *= -1;

    if(cylindric_fct == 1) {
    connectWidget2->objet->cylindricaldef = 1;
    cylindreBox->setEnabled(TRUE);
    inverse_condt->setEnabled(FALSE);
    page1->setEnabled(FALSE);
    page2->setEnabled(FALSE);
    perform_cylindre();
    }
    else {
    connectWidget2->objet->cylindricaldef = -1;
    cylindreBox->setEnabled(FALSE);
    inverse_condt->setEnabled(TRUE);
    page1->setEnabled(TRUE);
    page2->setEnabled(TRUE);
    }
}

 //====================================
void k3dsurface::perform_cylindre()
{  double vals=0;//[1] = {0};
   QMessageBox message ;
   FunctionParser f1, fp, fp2; 

    fp.AddConstant("pi", 3.14159265);
    int ret;

    ret = fp2.Parse(puissance_c_val->text(), "youpi");
    if(fmod(fp2.Eval(&vals), 2) == 0) {

    message.setText(tr("n mod 2 = 0 !!!!"));
    message.adjustSize () ;
    message.exec();
        return ;
    };

    ret = fp.Parse(fctdefc->text(), "u,z,t");
    if(ret >= 0) 
    {

    message.setText(tr(QString("Implicit equation : F(u,z,t)--> At col:")+
        QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();
        return ;
    }

  connectWidget2->objet->cylindricaldef = 1;
  connectWidget2->objet->cylindrical_expression = fctdefc->text();
  connectWidget2->objet->coefficient_n = puissance_c_val->text();

  connectWidget2->objet->inf_u = umin_3_2_2_2->text();
  connectWidget2->objet->sup_u = umax_3_2_2_2->text();
  connectWidget2->objet->inf_v = vmin_3_2_2_2->text();
  connectWidget2->objet->sup_v = vmax_3_2_2_2->text();

  //Process the new surface :
ParametricSurfaceProcess();
}
//====================================
void k3dsurface::cylindre_fct_changed( const QString & choix )
{
      if(choix == QString("Star_1")) {
  puissance_c_val->setText("1") ;
  fctdefc->setText("(1-0.25*z*z)*(1+0.5*sin(1.5*pi*z) +0.3*cos(5*u))") ;
  umin_3_2_2_2->setText("-pi") ;
  umax_3_2_2_2->setText("pi") ;
  vmin_3_2_2_2->setText("-2") ;
  vmax_3_2_2_2->setText("2") ;
  perform_cylindre();   // process the new surface  
  return;
    }

      if(choix == QString("Cup")) {
  puissance_c_val->setText("1") ;
  fctdefc->setText("sin(z*pi)*sin(z*pi) +cos(z*pi+0.9)");
  umin_3_2_2_2->setText("-pi") ;
  umax_3_2_2_2->setText("pi") ;
  vmin_3_2_2_2->setText("0.08") ;
  vmax_3_2_2_2->setText("0.71") ;
  perform_cylindre();   // process the new surface
  return;
    }

      if(choix == QString("Star_2")) {
  puissance_c_val->setText("1") ;
  fctdefc->setText("sin(z^2)*(1+0.5*sin(1.5*pi*z) +0.3*cos(5*u))") ;
  umin_3_2_2_2->setText("-pi") ;
  umax_3_2_2_2->setText("pi") ;
  vmin_3_2_2_2->setText("0") ;
  vmax_3_2_2_2->setText("1.773") ;
  perform_cylindre();   // process the new surface  
  return;
    }
       if(choix == QString("Height")) {
  puissance_c_val->setText("1") ;
  fctdefc->setText("sin(sin(z*pi))") ;
  umin_3_2_2_2->setText("-pi") ;
  umax_3_2_2_2->setText("pi") ;
  vmin_3_2_2_2->setText("-1") ;
  vmax_3_2_2_2->setText("1") ;
  perform_cylindre();   // process the new surface  
  return;
    }
  }
 //====================================


void k3dsurface::spheric_Fct_activated(){
   QMessageBox message ;
if(activate_tools == 1) {
    message.setText(tr(QString("Deactivate Tools")));
    message.adjustSize () ;
    message.exec();
    sfactivate->toggle();
        return ;
    }
    if(fourdimshapes == 1 )
    {
    message.setText(tr(QString("Deactivate 4D shapes")));
    message.adjustSize () ;
    message.exec();
    fct_spherical->toggle();
        return ;
    }

    if(implicite_fct  == 1 )
    {
    message.setText(tr(QString("Deactivate Implicit Function")));
    message.adjustSize () ;
    message.exec();
    fct_spherical->toggle();
        return ;
    }

    if(cylindric_fct  == 1 )
    {
    message.setText(tr(QString("Deactivate Cylindric Function")));
    message.adjustSize () ;
    message.exec();
    fct_spherical->toggle();
        return ;
    }

           // Deactivate condition
   if(activate_cd == 1) {
      activ_cond->toggle();
      condition->setEnabled(FALSE);
      inverse_condt->setEnabled(FALSE);
       connectWidget2->objet->there_is_condition *= -1;
       activate_cd = -1;
   }

    spheric_fct *= -1;
    if(spheric_fct == 1) {
    connectWidget2->objet->sphericaldef = 1;
    groupBox22->setEnabled(TRUE);
    groupBox22->setEnabled(TRUE);
    inverse_condt->setEnabled(FALSE);
    page1->setEnabled(FALSE);
    page2->setEnabled(FALSE);
    /*
    umin_3_2_2->setText("-pi/2");
    umax_3_2_2->setText("pi/2");
    vmin_3_2_2->setText("-pi");
    vmax_3_2_2->setText("pi");
    */
    perform_sphere(); 
    }
    else {
    connectWidget2->objet->sphericaldef = -1;
    groupBox22->setEnabled(FALSE);
   inverse_condt->setEnabled(TRUE);
    page1->setEnabled(TRUE);
    page2->setEnabled(TRUE);
    }
}

 //====================================
void k3dsurface::perform_sphere()
{  double vals=0;//[1] = {0};
   QMessageBox message ;
   FunctionParser f1, fp, fp2;
    fp.AddConstant("pi", 3.14159265);
    int ret;

    ret = fp2.Parse(puissance_r_val->text(), "youpi");
    if(fmod(fp2.Eval(&vals), 2) == 0) {
    message.setText(tr("n mod 2 = 0 !!!!"));
    message.adjustSize () ;
    message.exec();
        return ;
    };

    ret = fp.Parse(fctdefr->text(), "u,v,t");
    if(ret >= 0) 
    {
    message.setText(tr(QString("Implicit equation : f(u,v,t)--> At col:")+
    QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();
        return ;
    }

  connectWidget2->objet->sphericaldef = 1;
  connectWidget2->objet->spherical_expression = fctdefr->text();
  connectWidget2->objet->coefficient_n = puissance_r_val->text();

  connectWidget2->objet->inf_u = umin_3_2_2->text();
  connectWidget2->objet->sup_u = umax_3_2_2->text();
  connectWidget2->objet->inf_v = vmin_3_2_2->text();
  connectWidget2->objet->sup_v = vmax_3_2_2->text();

  //Process the new surface :
ParametricSurfaceProcess();
}
 //====================================

void k3dsurface::explicit_Fct_activated(){
   QMessageBox message ;
  if(activate_tools == 1) {
    message.setText(tr(QString("Deactivate Tools")));
    message.adjustSize () ;
    message.exec();
    sfactivate->toggle();
        return ;
    }

    if(fourdimshapes == 1 )
    {
    message.setText(tr(QString("Deactivate 4D shapes")));
    message.adjustSize () ;
    message.exec();
    fct_explicit->toggle();
        return ;
    }

    if(cylindric_fct  == 1 )
    {
    message.setText(tr(QString("Deactivate Cylindric Function")));
    message.adjustSize () ;
    message.exec();
    fct_explicit->toggle();
        return ;
    }

    if(spheric_fct  == 1 )
    {
    message.setText(tr(QString("Deactivate Spheric Function")));
    message.adjustSize () ;
    message.exec();
    fct_explicit->toggle();
        return ;
    }

           // Deactivate condition
   if(activate_cd == 1) {
      activ_cond->toggle();
      condition->setEnabled(FALSE);
      inverse_condt->setEnabled(FALSE);
       connectWidget2->objet->there_is_condition *= -1;
       activate_cd = -1;
   }

    implicite_fct *= -1;
    if(implicite_fct == 1) {
    connectWidget2->objet->implicitdef = 1;
    parametric_box->setEnabled(TRUE);
    inverse_condt->setEnabled(FALSE);
    //fourdims_box->setEnabled(FALSE);
    page1->setEnabled(FALSE);
    page2->setEnabled(FALSE);
    umin_3_2->setText("-pi");
    umax_3_2->setText("pi");
    vmin_3_2->setText("-pi");
    vmax_3_2->setText("pi");
    perform2();
    }
    else {
    connectWidget2->objet->implicitdef = -1;
    parametric_box->setEnabled(FALSE);
    inverse_condt->setEnabled(TRUE);
    //fourdims_box->setEnabled(TRUE);
    page1->setEnabled(TRUE);
    page2->setEnabled(TRUE);
    }
}

 //====================================

void k3dsurface::supershape_Fct_activated(){
   QMessageBox message ;

if(activate_tools == 1) {
    message.setText(tr(QString("Deactivate Tools")));
    message.adjustSize () ;
    message.exec();
    sfactivate->toggle();
        return ;
    }

       if(fivedimshapes == 1 )
    {
    message.setText(tr(QString("Deactivate ND shapes")));
    message.adjustSize () ;
    message.exec();
    sfactivate->toggle();
        return ; 
    }
    if(fourdimshapes == 1 )
    {
    message.setText(tr(QString("Deactivate 4D shapes")));
    message.adjustSize () ;
    message.exec();
    sfactivate->toggle();
        return ; 
    }

    if(cylindric_fct  == 1 )
    {
    message.setText(tr(QString("Deactivate Cylindric Function")));
    message.adjustSize () ;
    message.exec();
    sfactivate->toggle();
        return ;
    }

    if(spheric_fct  == 1 )
    {
    message.setText(tr(QString("Deactivate Spheric Function")));
    message.adjustSize () ;
    message.exec();
    sfactivate->toggle();
        return ;
    }

    if(implicite_fct  == 1 )
    {
    message.setText(tr(QString("Deactivate Implicit Function")));
    message.adjustSize () ;
    message.exec();
    sfactivate->toggle();
        return ;
    }

   /// Set the right Window for drawing :
    tabsurf->setCurrentPage(0);

 
    activate_supershape *= -1;
    if(activate_supershape == 1) {
    connectWidget2->objet->supershape = 1;
    //sftoolpage->setEnabled(TRUE);
    sfgroupBox->setEnabled(TRUE);
    toolBox2->setEnabled(FALSE);
    inverse_condt->setEnabled(FALSE);
    perform_supershape();
    }
    else {
    connectWidget2->objet->supershape = -1;
    //sftoolpage->setEnabled(FALSE);
    sfgroupBox->setEnabled(FALSE);
    toolBox2->setEnabled(TRUE);
    inverse_condt->setEnabled(TRUE);
    }

}

//====================================
void k3dsurface::Fourdim_Shapes(){
   QMessageBox message ;
  if(activate_tools == 1) {
    message.setText(tr(QString("Deactivate Tools")));
    message.adjustSize () ;
    message.exec();
    sfactivate->toggle();
        return ;
    }

    if(implicite_fct == 1 )
    {
    message.setText(tr(QString("Deactivate Implicite function Z^n = F(x,y,t)")));
    message.adjustSize () ;
    message.exec();
    activate_fourdim->toggle();
        return ;
    }

    if(spheric_fct == 1 )
    {
    message.setText(tr(QString("Deactivate Spheric function ")));
    message.adjustSize () ;
    message.exec();
    activate_fourdim->toggle();
        return ;
    }

    if(cylindric_fct == 1 ) 
    {
    message.setText(tr(QString("Deactivate Cylindric function ")));
    message.adjustSize () ;
    message.exec();
    activate_fourdim->toggle();
        return ;
    }


       // Deactivate condition
   if(activate_cd == 1) {
      activ_cond->toggle();
      condition->setEnabled(FALSE);
      inverse_condt->setEnabled(FALSE);
       connectWidget2->objet->there_is_condition *= -1;
       activate_cd = -1;
   }


    fourdimshapes *= -1;
   if( fourdimshapes == 1) {
    connectWidget2->objet->fourdimshapes = 1;
    fourdims_box->setEnabled(TRUE);
    rotational4d->setEnabled(TRUE);
    inverse_condt->setEnabled(FALSE);
    //parametric_box->setEnabled(FALSE);
    page1->setEnabled(FALSE);
    page2->setEnabled(FALSE);
    perform2();
    }
    else {
    connectWidget2->objet->fourdimshapes = -1;
    fourdims_box->setEnabled(FALSE);
    rotational4d->setEnabled(FALSE);
    inverse_condt->setEnabled(TRUE);
    //parametric_box->setEnabled(TRUE);
    page1->setEnabled(TRUE);
    page2->setEnabled(TRUE);

    }

}

//====================================
void k3dsurface::Fivedim_Shapes(){
  QMessageBox message;

  if(activate_tools == 1) {
    message.setText(tr(QString("Deactivate Tools")));
    message.adjustSize () ;
    message.exec();
    sfactivate->toggle();
        return ;
    }


if(connectWidget2->anim_ok  == 1 ||
   connectWidget2->morph_ok == 1 ||
   connectWidget2->anim4_ok == 1) {
    message.setText(tr(QString("Deactivate 3D/4D  Rotation/Morph")));
    message.adjustSize () ;
    message.exec();
    activate5d->toggle();
        return ;
}
if( connectWidget2->anim5_ok == 1) {
    message.setText(tr(QString("Deactivate 5D  Rotation")));
    message.adjustSize () ;
    message.exec();
    activate5d->toggle();
        return ;
}


     if(activate_supershape  == 1 )
    {
    message.setText(tr(QString("Deactivate Hall")));
    message.adjustSize () ;
    message.exec();
    activate5d->toggle();
        return ;
    }

    if(fourdimshapes == 1 ) 
    {
    message.setText(tr(QString("Deactivate 4D shapes")));
    message.adjustSize () ;
    message.exec();
    activate5d->toggle();
        return ;
    }

    if(implicite_fct  == 1 ) 
    {
    message.setText(tr(QString("Deactivate Implicit Function")));
    message.adjustSize () ;
    message.exec();
    activate5d->toggle();
        return ;
    }

    if(spheric_fct  == 1 ) 
    {
    message.setText(tr(QString("Deactivate Spheric Function")));
    message.adjustSize () ;
    message.exec();
    activate5d->toggle();
        return ;
    }

    if(cylindric_fct  == 1 )
    {
    message.setText(tr(QString("Deactivate Cylindric Function")));
    message.adjustSize () ;
    message.exec();
    activate5d->toggle();
        return ;
    } 
    // Set the right window for drawing:   
 tabsurf->setCurrentPage(0);
 if(paramwidgetstack == 1) glboxclicked();
    
         // Deactivate condition
   if(activate_cd == 1) {
      activ_cond->toggle();
      condition->setEnabled(FALSE);
      inverse_condt->setEnabled(FALSE);
       connectWidget2->objet->there_is_condition *= -1;
       activate_cd = -1;
   }

    fivedimshapes *= -1;
   if( fivedimshapes == 1) {
    connectWidget2->objet->fivedimshapes = 1;
    //sometimes I'm stuck with 4D!!! Must be changed
    connectWidget2->objet->fourdimshapes = fourdimshapes;
    fivedim_frame->setEnabled(TRUE);
    rotational5d->setEnabled(TRUE);
    toolBox2->setEnabled(FALSE);
    groupBox15->setEnabled(FALSE);
    inverse_condt->setEnabled(FALSE);
    perform_fivedim(); 
    }
    else {
    connectWidget2->objet->fivedimshapes = -1;
    //sometimes I'm stuck with 4D!!! Must be changed
    if(connectWidget2->objet->sixdimshapes == 1) {
    //connectWidget2->objet->fivedimshapes = -1;
    sixdimactivate->toggle();
    sixdimshape_activate();
    inverse_condt->setEnabled(TRUE);
    };
    connectWidget2->objet->fourdimshapes = fourdimshapes;
    fivedim_frame->setEnabled(FALSE);
    rotational5d->setEnabled(FALSE);
    toolBox2->setEnabled(TRUE);
    groupBox15->setEnabled(TRUE);
    }
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++//
//++++++++++++++++++++++++++++++++++++++++++++++++++++//
//++++++++++++++++++++++++++++++++++++++++++++++++++++//
//++++++++++++++++++++++++++++++++++++++++++++++++++++//
//++++++++++++++++++++++++++++++++++++++++++++++++++++//
//====================================
//static int ToolActivatedpage = 1; //Parametric == 1

void k3dsurface::activatetools(){
  QMessageBox message;

if(connectWidget2->anim_ok  == 1 ||
   connectWidget2->morph_ok == 1 ||
   connectWidget2->anim4_ok == 1) {
    message.setText(tr(QString("Deactivate 3D/4D  Rotation/Morph")));
    message.adjustSize () ;
    message.exec();
    toolcheckBox->toggle();
        return ;
}
if( connectWidget2->anim5_ok == 1) {
    message.setText(tr(QString("Deactivate 5D  Rotation")));
    message.adjustSize () ;
    message.exec();
    toolcheckBox->toggle();
        return ;
}

     if(activate_supershape  == 1 )
    {
    message.setText(tr(QString("Deactivate Hall")));
    message.adjustSize () ;
    message.exec();
    toolcheckBox->toggle();
        return ;
    }

    if(fourdimshapes == 1 )
    {
    message.setText(tr(QString("Deactivate 4D shapes")));
    message.adjustSize () ;
    message.exec();
    toolcheckBox->toggle();
        return ;
    }

    if(implicite_fct  == 1 )
    {
    message.setText(tr(QString("Deactivate Implicit Function")));
    message.adjustSize () ;
    message.exec();
    toolcheckBox->toggle();
        return ;
    }

    if(spheric_fct  == 1 )
    {
    message.setText(tr(QString("Deactivate Spheric Function")));
    message.adjustSize () ;
    message.exec();
    toolcheckBox->toggle();
        return ;
    }

    if(cylindric_fct  == 1 )
    {
    message.setText(tr(QString("Deactivate Cylindric Function")));
    message.adjustSize () ;
    message.exec();
    toolcheckBox->toggle();
        return ;
    }

    if( fivedimshapes  == 1 )
    {
    message.setText(tr(QString("Deactivate ND")));
    message.adjustSize () ;
    message.exec();
    toolcheckBox->toggle();
        return ; 
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
int current_pag = tabWidget7->currentPageIndex();    

if(current_pag == 0) {   tabsurf->setCurrentPage(0);
// if(paramwidgetstack == 1) glboxclicked();
    }
else { tabsurf->setCurrentPage(1);
// if(isowidgetstack == 1) isogl_clicked();
    }

    
    
         // Deactivate condition
   if(activate_cd == 1) {
      activ_cond->toggle();
      condition->setEnabled(FALSE);
      inverse_condt->setEnabled(FALSE);
       connectWidget2->objet->there_is_condition *= -1;
       activate_cd = -1;
   }

    activate_tools *= -1;

if(activate_tools == 1) {
    grouptools->setEnabled(TRUE);
    groupBox41->setEnabled(TRUE);
   // deformerstab->setEnabled(TRUE);
    //toolBox4->setEnabled(TRUE);
    toolBox2->setEnabled(FALSE);
    //groupBox15->setEnabled(FALSE);
    inverse_condt->setEnabled(FALSE);
       connectWidget2->objet->two_system = -1;     //just in case...
    perform_tools(); 
     //(connectWidget2->objet->Tre2_save) * = (connectWidget2->objet->Tre2) *
    }
else {
    grouptools->setEnabled(FALSE);
    groupBox41->setEnabled(FALSE);
    inverse_condt->setEnabled(TRUE);
    toolBox2->setEnabled(TRUE);
    //groupBox15->setEnabled(TRUE);
   // deformerstab->setEnabled(FALSE);
// toolBox4->setEnabled(FALSE);
}
}

//====================================
void k3dsurface::perform_tools()
{
    FunctionParser fp,f1;
    QMessageBox message ;

    fp.AddConstant("pi", 3.14159265);
    int ret;

        if(connectWidget2->objet->DefineNewFct ==1)
    {
    ret = fp.Parse(fctdef->text(), "u,v,t,x,y");
    if(ret >= 0)
    {
   message.setText(tr(QString("k(u,v,t,x,y)--> At col:")+
         QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();

        return ;
    }

     f1.Parse(fctdef->text(), "u,v,t");
     fp.AddFunction("k", f1);
    }

    ret = fp.Parse(xtool->text(), "u,v,t");
    if(ret >= 0)
    {

    message.setText(tr(QString("X=g(u,v)--> At col:")+
         QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();

        return ;
    }

    ret = fp.Parse(ytool->text(), "u,v,t");
    if(ret >= 0)
    {

    message.setText(tr(QString("Y=g(u,v)--> At col:")+
 QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();

        return ;
    }

     ret = fp.Parse(ztool->text(), "u,v,t");
    if(ret >= 0) 
    {

    message.setText(tr(QString("Z=h(u,v)--> At col:")+
        QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();

        return ;
    }



  connectWidget2->objet->expression_X =
  connectWidget2->objet->expression_X_save =
  xtool->text();

  connectWidget2->objet->expression_Y =
  connectWidget2->objet->expression_Y_save =
  ytool->text();

  connectWidget2->objet->expression_Z =
  connectWidget2->objet->expression_Z_save =
  ztool->text();


  connectWidget2->objet->inf_u = umin_tools->text();
  connectWidget2->objet->sup_u = umax_tools->text();
  connectWidget2->objet->inf_v = vmin_tools->text();
  connectWidget2->objet->sup_v = vmax_tools->text();
/*
  // process the new surface
  connectWidget2->valueChanged();
*/
    // process the new surface
ParametricSurfaceProcess();













  connectWidget2->objet->MINX_save =   connectWidget2->objet->MINX_tmp;
  connectWidget2->objet->DIFX_save =   connectWidget2->objet->DIFX_tmp;

  connectWidget2->objet->MINY_save =   connectWidget2->objet->MINY_tmp;
  connectWidget2->objet->DIFY_save =   connectWidget2->objet->DIFY_tmp;

  connectWidget2->objet->MINZ_save =   connectWidget2->objet->MINZ_tmp;
  connectWidget2->objet->DIFZ_save =   connectWidget2->objet->DIFZ_tmp;

//initialise the controls widgets 
scalexvalue->setValue(10) ;
scaleyvalue->setValue(10) ;
scalezvalue->setValue(10) ;
scrollBar81->setValue(0) ;
scrollBar20->setValue(10) ;
scrollBar81_2->setValue(0) ;
scrollBar20_2->setValue(10) ;
scrollBar81_3->setValue(0) ;
scrollBar20_3->setValue(10) ;

 connectWidget2->oldcoeff_rayonz = 10; 
 connectWidget2->oldnb_twistez = 0;   
 connectWidget2->oldcoeff_rayony = 10; 
 connectWidget2->oldnb_twistey = 0;
 connectWidget2->oldcoeff_rayonx = 10; 
 connectWidget2->oldnb_twistex = 0; 

 connectWidget2->objet->initialisecoeffscale();
}
//========================================//
void k3dsurface::reset_changes()
{
perform_tools();
perform_tools(); //!!!!  Must be change
}
//========================================//
void k3dsurface::save_changes()
{
 /*
connectWidget2->objet->expression_X_save = connectWidget2->objet->expression_X;
connectWidget2->objet->expression_Y_save = connectWidget2->objet->expression_Y;
connectWidget2->objet->expression_Z_save = connectWidget2->objet->expression_Z;

xtool->setText(connectWidget2->objet->expression_X_save);
ytool->setText(connectWidget2->objet->expression_Y_save);
ztool->setText(connectWidget2->objet->expression_Z_save);

//initialise the controls widgets 
scalexvalue->setValue(10) ;
scaleyvalue->setValue(10) ;
scalezvalue->setValue(10) ;
scrollBar81->setValue(0) ;
scrollBar20->setValue(10) ;
  // process the new surface
  connectWidget2->valueChanged(); 

connectWidget2->objet->MINX_save = connectWidget2->objet->MINX_tmp;
connectWidget2->objet->DIFX_save = connectWidget2->objet->DIFX_tmp;

connectWidget2->objet->MINY_save = connectWidget2->objet->MINY_tmp;
connectWidget2->objet->DIFY_save = connectWidget2->objet->DIFY_tmp;

connectWidget2->objet->MINZ_save = connectWidget2->objet->MINZ_tmp;
connectWidget2->objet->DIFZ_save = connectWidget2->objet->DIFZ_tmp;

 connectWidget2->objet->initialisecoeffscale();
 */

xtool->setText(connectWidget2->objet->expression_X);
ytool->setText(connectWidget2->objet->expression_Y);
ztool->setText(connectWidget2->objet->expression_Z);

perform_tools();
perform_tools(); //!!!!  Must be change

}

//========================================//
void k3dsurface::save_isochanges()
{ 
implicitfunct_2->setText(isoWidget->IsoObjet->ImplicitFunction);

minxlimit_2->setText(isoWidget->IsoObjet->XlimitInf);
minylimit_2->setText(isoWidget->IsoObjet->YlimitInf);
minzlimit_2->setText(isoWidget->IsoObjet->ZlimitInf);

maxxlimit_2->setText(isoWidget->IsoObjet->XlimitSup);
maxylimit_2->setText(isoWidget->IsoObjet->YlimitSup);
maxzlimit_2->setText(isoWidget->IsoObjet->ZlimitSup);

///
isoWidget->IsoObjet->ImplicitFunction_save = isoWidget->IsoObjet->ImplicitFunction;

isoWidget->IsoObjet->XlimitInf_save = isoWidget->IsoObjet->XlimitInf;
isoWidget->IsoObjet->YlimitInf_save = isoWidget->IsoObjet->YlimitInf;
isoWidget->IsoObjet->ZlimitInf_save = isoWidget->IsoObjet->ZlimitInf;

isoWidget->IsoObjet->XlimitSup_save = isoWidget->IsoObjet->XlimitSup;
isoWidget->IsoObjet->YlimitSup_save = isoWidget->IsoObjet->YlimitSup;
isoWidget->IsoObjet->ZlimitSup_save = isoWidget->IsoObjet->ZlimitSup;



/// Scale Controls :
scalexvalue_2->setValue(10) ;
scaleyvalue_2->setValue(10) ;
scalezvalue_2->setValue(10) ;
/// Twist controls :

//scrollBar20_3_2->setValue(10) ;
//scrollBar20_2_2->setValue(10) ;
//scrollBar20_4->setValue(10) ;
scrollBar81_3_2->setValue(0) ;
scrollBar81_2_2->setValue(0) ;
scrollBar81_4->setValue(0) ;

isoWidget->initcontrols();

}
//==========================================
void k3dsurface::reset_isochanges()
{

isoWidget->IsoObjet->ImplicitFunction = isoWidget->IsoObjet->ImplicitFunction_save;
isoWidget->IsoObjet->XlimitInf = isoWidget->IsoObjet->XlimitInf_save;
isoWidget->IsoObjet->YlimitInf = isoWidget->IsoObjet->YlimitInf_save;
isoWidget->IsoObjet->ZlimitInf = isoWidget->IsoObjet->ZlimitInf_save;
isoWidget->IsoObjet->XlimitSup = isoWidget->IsoObjet->XlimitSup_save;
isoWidget->IsoObjet->YlimitSup = isoWidget->IsoObjet->YlimitSup_save;
isoWidget->IsoObjet->ZlimitSup = isoWidget->IsoObjet->ZlimitSup_save;

/// Scale Controls :
scalexvalue_2->setValue(10) ;
scaleyvalue_2->setValue(10) ;
scalezvalue_2->setValue(10) ;
/// Twist controls :

//scrollBar20_3_2->setValue(10) ;
//scrollBar20_2_2->setValue(10) ;
//scrollBar20_4->setValue(10) ;

scrollBar81_3_2->setValue(0) ;
scrollBar81_2_2->setValue(0) ;
scrollBar81_4->setValue(0) ;

//isoWidget->IsoMorphCompute();
   ProcessNewIsoSurface( );
}
//====================================
void k3dsurface::ImplicitFunChanged( const QString & choix )
{

if(choix == QString("pseudo_Duplin")) {
  implicitfunct->setText("(2^2 - 0^2 - (2 + 2.1)^2) * (2^2 - 0^2 - (2 - 2.1)^2)*(((x/0.6)/3.9)^4+(y*cos(0.575383*(x/0.6)) - z*sin(0.575383*(x/0.6)))^4+(y*sin(0.575383*(x/0.6)) + z*cos(0.575383*(x/0.6)))^4)+ 2*((2^2 - 0^2 - (2 + 2.1)^2 )*(2^2 - 0^2 - (2 - 2.1)^2)* (((x/0.6)/3.9)^2 * (y*cos(0.575383*(x/0.6)) - z*sin(0.575383*(x/0.6)))^2+((x/0.6)/3.9)^2 * (y*sin(0.575383*(x/0.6)) + z*cos(0.575383*(x/0.6)))^2+(y*cos(0.575383*(x/0.6)) - z*sin(0.575383*(x/0.6)))^2 * (y*sin(0.575383*(x/0.6)) + z*cos(0.575383*(x/0.6)))^2))+2* 2^2 *((-0^2-2^2+2^2+2.1^2)* (2 *((x/0.6)/3.9) *2+2* (y*cos(0.575383*(x/0.6)) - z*sin(0.575383*(x/0.6)))* 0-2^2)-4*0 *2.1^2 *(y*cos(0.575383*(x/0.6)) - z*sin(0.575383*(x/0.6))))*(((x/0.6)/3.9)^2+(y*cos(0.575383*(x/0.6)) - z*sin(0.575383*(x/0.6)))^2+(y*sin(0.575383*(x/0.6)) + z*cos(0.575383*(x/0.6)))^2)+ 4 * 2^4 * (2 *((x/0.6)/3.9)+0 *(y*cos(0.575383*(x/0.6)) - z*sin(0.575383*(x/0.6))))* (-2^2+0 * (y*cos(0.575383*(x/0.6)) - z*sin(0.575383*(x/0.6)))+2 * ((x/0.6)/3.9))+4* 2^4 * 2.1^2 * (y*cos(0.575383*(x/0.6)) - z*sin(0.575383*(x/0.6)))^2+2^8") ;
  minxlimit->setText("-2*3.9*0.6") ;
  minylimit->setText("-2") ;
  minzlimit->setText("-2") ;
  maxxlimit->setText("2.2*3.9*0.6") ;
  maxylimit->setText("2") ;
  maxzlimit->setText("2") ;
    }
  else if(choix == QString("pseudo_Torus")) {
  implicitfunct->setText("(sqrt((x/2.7)*(x/2.7)+(y*sin(0.436332*x) + z*cos(0.436332*x))*(y*sin(0.436332*x) + z*cos(0.436332*x)))-3)^2 + (y*cos(0.436332*x) - z*sin(0.436332*x))*(y*cos(0.436332*x) - z*sin(0.436332*x)) - 1") ;
  minxlimit->setText("-4*2.7") ;
  minylimit->setText("-4") ;
  minzlimit->setText("-4") ;
  maxxlimit->setText("4*2.7") ;
  maxylimit->setText("4") ;
  maxzlimit->setText("4") ;
    }
  else    if(choix == QString("Bugs")) {
  implicitfunct->setText("min( ((x*cos(0.866646*y) - z*sin(0.866646*y))-0.7)*((x*cos(0.866646*y) - z*sin(0.866646*y))-0.7) + (y/2.9)*(y/2.9) + (x*sin(0.866646*y) + z*cos(0.866646*y))*(x*sin(0.866646*y) + z*cos(0.866646*y)) - 1,  ((x*cos(0.866646*y) - z*sin(0.866646*y))+0.5)*((x*cos(0.866646*y) - z*sin(0.866646*y))+0.5) + (y/2.9)*(y/2.9) + (x*sin(0.866646*y) + z*cos(0.866646*y))*(x*sin(0.866646*y) + z*cos(0.866646*y)) - 1)") ;
  minxlimit->setText("-2") ;
  minylimit->setText("-2*2.9*1") ;
  minzlimit->setText("-2") ;
  maxxlimit->setText("2") ;
  maxylimit->setText("2*2.9*1") ;
  maxzlimit->setText("2") ;
    }
  else
if(choix == QString("DifferenceSpheres")) {
  implicitfunct->setText("((x-0.7)*(x-0.7) + y*y + z*z - 1)*min( (x-0.7)*(x-0.7) + y*y + z*z - 1,  (x+0.3)*(x+0.3) + y*y + z*z - 1) +0.02") ;
  minxlimit->setText("-2") ;
  minylimit->setText("-1") ;
  minzlimit->setText("-1") ;
  maxxlimit->setText("0.1") ;
  maxylimit->setText("1") ;
  maxzlimit->setText("1") ;
    }
  else   if(choix == QString("Holes")) {
  implicitfunct->setText("3*(cos(x) + cos(y) + cos(z)) + 4* cos(x) * cos(y) * cos(z)") ;
  minxlimit->setText("-3") ;
  minylimit->setText("-3") ;
  minzlimit->setText("-3") ;
  maxxlimit->setText("3") ;
  maxylimit->setText("3") ;
  maxzlimit->setText("3") ;
    }
  else   if(choix == QString("Gyroid")) {
  implicitfunct->setText("cos(x) * sin(y) + cos(y) * sin(z) + cos(z) * sin(x)") ;
  minxlimit->setText("-4") ;
  minylimit->setText("-4") ;
  minzlimit->setText("-4") ;
  maxxlimit->setText("4") ;
  maxylimit->setText("4") ;
  maxzlimit->setText("4") ;
    }
  else   if(choix == QString("Diamand")) {
  implicitfunct->setText("sin(x) *sin(y) *sin(z) +sin(x) * cos(y) * cos(z) +cos(x) * sin(y) * cos(z) + cos(x) * cos(y) * sin(z)") ;
  minxlimit->setText("-4") ;
  minylimit->setText("-4") ;
  minzlimit->setText("-4") ;
  maxxlimit->setText("4") ;
  maxylimit->setText("4") ;
  maxzlimit->setText("4") ;
    }
  else if(choix == QString("Tetrahedral")) {
  implicitfunct->setText("(x^2 + y^2 + z^2)^2 + 8*x*y*z - 10*(x^2 + y^2 + z^2) + 25") ;
  minxlimit->setText("-4") ;
  minylimit->setText("-4") ;
  minzlimit->setText("-4") ;
  maxxlimit->setText("4") ;
  maxylimit->setText("4") ;
  maxzlimit->setText("4") ;
    }
  else if(choix == QString("DuplinCyclides")) {
  implicitfunct->setText("(2^2 - 0^2 - (2 + 2.1)^2) * (2^2 - 0^2 - (2 - 2.1)^2)*(x^4+y^4+z^4)+ 2*((2^2 - 0^2 - (2 + 2.1)^2 )*(2^2 - 0^2 - (2 - 2.1)^2)* (x^2 * y^2+x^2 * z^2+y^2 * z^2))+2* 2^2 *((-0^2-2^2+2^2+2.1^2)* (2 *x *2+2* y* 0-2^2)-4*0 *2.1^2 *y)*(x^2+y^2+z^2)+ 4 * 2^4 * (2 *x+0 *y)* (-2^2+0 * y+2 * x)+4* 2^4 * 2.1^2 * y^2+2^8") ;
  minxlimit->setText("-2") ;
  minylimit->setText("-2") ;
  minzlimit->setText("-1.3") ;
  maxxlimit->setText("2.2") ;
  maxylimit->setText("2") ;
  maxzlimit->setText("1.3") ;
    }
  else 
  if(choix == QString("Hyperboloid")) {
  implicitfunct->setText("x^2 - y^2 - z^2 +0.3") ;
  minxlimit->setText("-1.8") ;
  minylimit->setText("-2") ;
  minzlimit->setText("-2") ;
  maxxlimit->setText("1.8") ;
  maxylimit->setText("2") ;
  maxzlimit->setText("2") ;
    }
  else if(choix == QString("Hyperbolic")) {
  implicitfunct->setText("x*x + y - z*z") ;
  minxlimit->setText("-1") ;
  minylimit->setText("-1") ;
  minzlimit->setText("-1") ;
  maxxlimit->setText("1") ;
  maxylimit->setText("1") ;
  maxzlimit->setText("1") ;
}
  else if(choix == QString("Sinus")) {
  implicitfunct->setText("sin(pi*((x)^2+(y)^2))/2 -z") ;
  minxlimit->setText("-1") ;
  minylimit->setText("-1") ;
  minzlimit->setText("-1") ;
  maxxlimit->setText("1") ;
  maxylimit->setText("1") ;
  maxzlimit->setText("1") ;
    }
  else  if(choix == QString("Octahedron")) {
  implicitfunct->setText("abs(x)+abs(y)+abs(z) - 1") ;
  minxlimit->setText("-1") ;
  minylimit->setText("-1") ;
  minzlimit->setText("-1") ;
  maxxlimit->setText("1") ;
  maxylimit->setText("1") ;
  maxzlimit->setText("1") ;
    }
  else  if(choix == QString("UnionSpheres")) {
  implicitfunct->setText("min( (x-0.7)*(x-0.7) + y*y + z*z - 1,  (x+0.5)*(x+0.5) + y*y + z*z - 1)") ;
  minxlimit->setText("-2") ;
  minylimit->setText("-2") ;
  minzlimit->setText("-2") ;
  maxxlimit->setText("2") ;
  maxylimit->setText("2") ;
  maxzlimit->setText("2") ;
    }
  else  if(choix == QString("IntersectSpheres")) {
  implicitfunct->setText("max( (x-0.7)*(x-0.7) + y*y + z*z - 1,  (x+0.5)*(x+0.5) + y*y + z*z - 1)") ;
  minxlimit->setText("-2") ;
  minylimit->setText("-2") ;
  minzlimit->setText("-2") ;
  maxxlimit->setText("2") ;
  maxylimit->setText("2") ;
  maxzlimit->setText("2") ;
    }
/*
  else  if(choix == QString("InterSphOct")) {
  implicitfunct->setText("max( abs(x)+abs(y)+abs(z) - 1 ,  (x+0.9)*(x+0.9) + y*y + z*z - 0.7)") ;
  minxlimit->setText("-1") ;
  minylimit->setText("-1") ;
  minzlimit->setText("-1") ;
  maxxlimit->setText("0") ;
  maxylimit->setText("1") ;
  maxzlimit->setText("1") ;
    }
*/
  else   if(choix == QString("Blobs")) {
  implicitfunct->setText("x^2 + y ^2 + z^2 +cos(4*x)+cos(4*y)+cos(4*z)-0.2") ;
  minxlimit->setText("-2") ;
  minylimit->setText("-2") ;
  minzlimit->setText("-2") ;
  maxxlimit->setText("2") ;
  maxylimit->setText("2") ;
  maxzlimit->setText("2") ;
    }
  else   if(choix == QString("Blobs_2")) {
  implicitfunct->setText("x^2 + y ^2 + z^2 +sin(4*x) + sin(4*y) + sin(4*z) -1") ;
  minxlimit->setText("-2") ;
  minylimit->setText("-2") ;
  minzlimit->setText("-2") ;
  maxxlimit->setText("2") ;
  maxylimit->setText("2") ;
  maxzlimit->setText("2") ;
    }
/*
  else  if(choix == QString("Cylindre")) {
  implicitfunct->setText("(x^2 + (y^2)/4 - 1) * ( (x^2)/4 + z^2 - 1) ") ;
  minxlimit->setText("-2") ;
  minylimit->setText("-2") ;
  minzlimit->setText("-2") ;
  maxxlimit->setText("2") ;
  maxylimit->setText("2") ;
  maxzlimit->setText("2") ;
    }
*/
  else   if(choix == QString("OrthoCircle")) {
  implicitfunct->setText("((x^2 + y^2 - 1)^2 + z^2)* ((y^2 + z^2 - 1)^2 + x^2)* ((z^2 + x^2 - 1)^2 + y^2) - 0.075^2 *(1 + 3* (x^2 + y^2 + z^2))") ;
  minxlimit->setText("-1.5") ;
  minylimit->setText("-1.5") ;
  minzlimit->setText("-1.5") ;
  maxxlimit->setText("1.5") ;
  maxylimit->setText("1.5") ;
  maxzlimit->setText("1.5") ;
    }
  else   if(choix == QString("CubeSphere")) {
  implicitfunct->setText("1 - ((1/2.3)^2 *(x^2 + y^2 + z^2))^-6 - ( (1/2)^8 * (x^8 + y^8 + z^8) )^6") ;
  minxlimit->setText("-2") ;
  minylimit->setText("-2") ;
  minzlimit->setText("-2") ;
  maxxlimit->setText("2") ;
  maxylimit->setText("2") ;
  maxzlimit->setText("2") ;
    }
  else   if(choix == QString("CubeSphere_2")) {
  implicitfunct->setText("12 - ((1/2.3)^2 *(x^2 + y^2 + z^2))^-6 - ( (1/2)^8 * (x^8 + y^8 + z^8) )^6") ;
  minxlimit->setText("-2") ;
  minylimit->setText("-2") ;
  minzlimit->setText("-2") ;
  maxxlimit->setText("2") ;
  maxylimit->setText("2") ;
  maxzlimit->setText("2") ;
    }


  else   if(choix == QString("Holes_2")) {
  implicitfunct->setText("sin(4*x) + sin(4*y) + sin(4*z)  + 4*x*y*z") ;
  minxlimit->setText("-2") ;
  minylimit->setText("-2") ;
  minzlimit->setText("-2") ;
  maxxlimit->setText("2") ;
  maxylimit->setText("2") ;
  maxzlimit->setText("2") ;
    }

  else   if(choix == QString("Virus")) {
  implicitfunct->setText("cos(x) + cos(y) + cos(z) - 1") ;
  minxlimit->setText("-4") ;
  minylimit->setText("-4") ;
  minzlimit->setText("-4") ;
  maxxlimit->setText("4") ;
  maxylimit->setText("4") ;
  maxzlimit->setText("4") ;
    }

  else   if(choix == QString("Schwartz")) {
  implicitfunct->setText("cos(x) + cos(y) + cos(z)") ;
  minxlimit->setText("-4") ;
  minylimit->setText("-4") ;
  minzlimit->setText("-4") ;
  maxxlimit->setText("4") ;
  maxylimit->setText("4") ;
  maxzlimit->setText("4") ;
    }

  else   if(choix == QString("Schwartz_Morph")) {
  implicitfunct->setText("cos(x) + cos(y) + cos(z) - t") ;
  minxlimit->setText("-4") ;
  minylimit->setText("-4") ;
  minzlimit->setText("-4") ;
  maxxlimit->setText("4") ;
  maxylimit->setText("4") ;
  maxzlimit->setText("4") ;
    }

  else   if(choix == QString("Blob_Morph")) {
  implicitfunct->setText("((x-0.9*2*t)*(x-0.9*2*t)+y*y+z*z-1)*((x+0.9*2*t)*(x+0.9*2*t)+y*y+z*z -1)-0.3") ;
  minxlimit->setText("-3") ;
  minylimit->setText("-2") ;
  minzlimit->setText("-2") ;
  maxxlimit->setText("3") ;
  maxylimit->setText("2") ;
  maxzlimit->setText("2") ;
    }

  else   if(choix == QString("Torus")) {
  implicitfunct->setText("(sqrt(x*x+z*z)-3)^2 + y*y - 1") ;
  minxlimit->setText("-10") ;
  minylimit->setText("-10") ;
  minzlimit->setText("-4") ;
  maxxlimit->setText("4") ;
  maxylimit->setText("4") ;
  maxzlimit->setText("4") ;
    }
   else   if(choix == QString("TwoCylinderBlend")) {
  implicitfunct->setText("(x^2 + y^2 - 1) * ( x^2 + z^2 - 1) - 1") ;
  minxlimit->setText("-3") ;
  minylimit->setText("-3") ;
  minzlimit->setText("-3") ;
  maxxlimit->setText("3") ;
  maxylimit->setText("3") ;
  maxzlimit->setText("3") ;
    }
  else   if(choix == QString("BlendThreeCylinder")) {
  implicitfunct->setText("(x^2 + y^2 - 1) * ( x^2 + z^2 - 1)* ( y^2 + z^2 - 1) - 1") ;
  minxlimit->setText("-3") ;
  minylimit->setText("-3") ;
  minzlimit->setText("-3") ;
  maxxlimit->setText("3") ;
  maxylimit->setText("3") ;
  maxzlimit->setText("3") ;
    }
  else   if(choix == QString("Sphere")) {
  implicitfunct->setText("x*x + y*y + z*z - 1") ;
  minxlimit->setText("-1") ;
  minylimit->setText("-1") ;
  minzlimit->setText("-1") ;
  maxxlimit->setText("1") ;
  maxylimit->setText("1") ;
  maxzlimit->setText("1") ;
    }
  else   if(choix == QString("RoundCube")) {
  implicitfunct->setText("x^4 + y^4 + z^4 - (x^2 + y^2 + z^2)") ;
  minxlimit->setText("-2") ;
  minylimit->setText("-2") ;
  minzlimit->setText("-2") ;
  maxxlimit->setText("2") ;
  maxylimit->setText("2") ;
  maxzlimit->setText("2") ;
    }
  else   if(choix == QString("Toupie")) {
  implicitfunct->setText("(sqrt(x*x+z*z)-3)^3 + y*y - 1") ;
  minxlimit->setText("-4") ;
  minylimit->setText("-6") ;
  minzlimit->setText("-4") ;
  maxxlimit->setText("4") ;
  maxylimit->setText("6") ;
  maxzlimit->setText("4") ;
    }
  else   if(choix == QString("Chmutov")) {
  implicitfunct->setText("x^4 + y^4 + z^4 - (x^2 + y^2 + z^2-0.3)") ;
  minxlimit->setText("-1.5") ;
  minylimit->setText("-1.5") ;
  minzlimit->setText("-1.5") ;
  maxxlimit->setText("1.5") ;
  maxylimit->setText("1.5") ;
  maxzlimit->setText("1.5") ;
    }
      else   if(choix == QString("Chmutov_2")) {
  implicitfunct->setText("2*(x^2*(3-4*x^2)^2+y^2*(3-4*y^2)^2+z^2*(3-4*z^2)^2) -3") ;
  minxlimit->setText("-1.3") ;
  minylimit->setText("-1.3") ;
  minzlimit->setText("-1.3") ;
  maxxlimit->setText("1.3") ;
  maxylimit->setText("1.3") ;
  maxzlimit->setText("1.3") ;
    }
      else   if(choix == QString("Clebsch")) {
  implicitfunct->setText("81*(x^3+y^3+z^3)-189*(x^2*y+x^2*z+y^2*x+y^2*z+z^2*x+z^2*y) +54*x*y*z+126*(x*y+x*z+y*z)-9*(x^2+y^2+z^2)-9*(x+y+z)+1") ;
  minxlimit->setText("-1") ;
  minylimit->setText("-1") ;
  minzlimit->setText("-1") ;
  maxxlimit->setText("1") ;
  maxylimit->setText("1") ;
  maxzlimit->setText("1") ;
    }
   else   if(choix == QString("DingDong")) {
  implicitfunct->setText("x^2 +y^2 -(1-z)*z^2") ;
  minxlimit->setText("-1.5") ;
  minylimit->setText("-1.5") ;
  minzlimit->setText("-1") ;
  maxxlimit->setText("1.5") ;
  maxylimit->setText("1.5") ;
  maxzlimit->setText("1") ;
    } 
  else   if(choix == QString("Trap")) {
  implicitfunct->setText("(x^8 + y^30 + z^8 - (x^4 + y^50 + z^4 -0.3))*(x^2 + y^2 + z^2 -0.5)") ;
  minxlimit->setText("-1.2") ;
  minylimit->setText("-1.5") ;
  minzlimit->setText("-1.3") ;
  maxxlimit->setText("1.2") ;
  maxylimit->setText("1.5") ;
  maxzlimit->setText("1.3") ;
    }
 else   if(choix == QString("Cube")) {
  implicitfunct->setText("x^100 + y^100 + z^100 -1") ;
  minxlimit->setText("-2") ;
  minylimit->setText("-2") ;
  minzlimit->setText("-2") ;
  maxxlimit->setText("2") ;
  maxylimit->setText("2") ;
  maxzlimit->setText("2") ;
    }

  else   if(choix == QString("Drope")) {
  implicitfunct->setText("4*x*exp(-x^2-y^2) -z") ;
  minxlimit->setText("-2") ;
  minylimit->setText("-2") ;
  minzlimit->setText("-1.7") ;
  maxxlimit->setText("2") ;
  maxylimit->setText("2") ;
  maxzlimit->setText("1.7") ;
    }

  else   if(choix == QString("Leminescape")) {
  implicitfunct->setText("4*x^2*(x^2+y^2+z^2+z)+y^2*(y^2+z^2-1)") ;
  minxlimit->setText("-0.5") ;
  minylimit->setText("-1") ;
  minzlimit->setText("-1") ;
  maxxlimit->setText("0.5") ;
  maxylimit->setText("1") ;
  maxzlimit->setText("1") ;
    }

  else   if(choix == QString("Klein")) {
  implicitfunct->setText("(x^2+y^2+z^2+2*y-1)*((x^2+y^2+z^2-2*y-1)^2-8*z^2)+16*x*z*(x^2+y^2+z^2-2*y-1)") ;
  minxlimit->setText("-3") ;
  minylimit->setText("-3.1") ;
  minzlimit->setText("-4") ;
  maxxlimit->setText("3") ;
  maxylimit->setText("3.1") ;
  maxzlimit->setText("4") ;
    }


  ///Process New Surface :
 PerformNewImplicitFunct();
}
//====================================

//====================================
void k3dsurface::ToolsImplicitFunChanged( const QString & choix )
{

  if(choix == QString("BlendSpheres")) {
  implicitfunct_2->setText("((x-0.9)*(x-0.9) + y*y + z*z - 1)*((x+0.9)*(x+0.9) + y*y + z*z - 1) -0.3") ;
  minxlimit_2->setText("-2") ;
  minylimit_2->setText("-2") ;
  minzlimit_2->setText("-2") ;
  maxxlimit_2->setText("2") ;
  maxylimit_2->setText("2") ;
  maxzlimit_2->setText("2") ;
    }
  else     if(choix == QString("DifferenceSpheres")) {
  implicitfunct_2->setText("((x-0.7)*(x-0.7) + y*y + z*z - 1)*min( (x-0.7)*(x-0.7) + y*y + z*z - 1,  (x+0.3)*(x+0.3) + y*y + z*z - 1) +0.02") ;
  minxlimit_2->setText("-2") ;
  minylimit_2->setText("-1") ;
  minzlimit_2->setText("-1") ;
  maxxlimit_2->setText("0.1") ;
  maxylimit_2->setText("1") ;
  maxzlimit_2->setText("1") ;
    }
  else   if(choix == QString("Holes_2")) {
  implicitfunct_2->setText("3*(cos(x) + cos(y) + cos(z)) + 4* cos(x) * cos(y) * cos(z)") ;
  minxlimit_2->setText("-3") ;
  minylimit_2->setText("-3") ;
  minzlimit_2->setText("-3") ;
  maxxlimit_2->setText("3") ;
  maxylimit_2->setText("3") ;
  maxzlimit_2->setText("3") ;
    }
  else   if(choix == QString("Gyroid")) {
  implicitfunct_2->setText("cos(x) * sin(y) + cos(y) * sin(z) + cos(z) * sin(x)") ;
  minxlimit_2->setText("-4") ;
  minylimit_2->setText("-4") ;
  minzlimit_2->setText("-4") ;
  maxxlimit_2->setText("4") ;
  maxylimit_2->setText("4") ;
  maxzlimit_2->setText("4") ;
    }
  else   if(choix == QString("Diamand")) {
  implicitfunct_2->setText("sin(x) *sin(y) *sin(z) +sin(x) * cos(y) * cos(z) +cos(x) * sin(y) * cos(z) + cos(x) * cos(y) * sin(z)") ;
  minxlimit_2->setText("-4") ;
  minylimit_2->setText("-4") ;
  minzlimit_2->setText("-4") ;
  maxxlimit_2->setText("4") ;
  maxylimit_2->setText("4") ;
  maxzlimit_2->setText("4") ;
    }
  else if(choix == QString("Tetrahedral")) {
  implicitfunct_2->setText("(x^2 + y^2 + z^2)^2 + 8*x*y*z - 10*(x^2 + y^2 + z^2) + 25") ;
  minxlimit_2->setText("-4") ;
  minylimit_2->setText("-4") ;
  minzlimit_2->setText("-4") ;
  maxxlimit_2->setText("4") ;
  maxylimit_2->setText("4") ;
  maxzlimit_2->setText("4") ;
    }
  else if(choix == QString("DuplinCyclides")) {
  implicitfunct_2->setText("(2^2 - 0^2 - (2 + 2.1)^2) * (2^2 - 0^2 - (2 - 2.1)^2)*(x^4+y^4+z^4)+ 2*((2^2 - 0^2 - (2 + 2.1)^2 )*(2^2 - 0^2 - (2 - 2.1)^2)* (x^2 * y^2+x^2 * z^2+y^2 * z^2))+2* 2^2 *((-0^2-2^2+2^2+2.1^2)* (2 *x *2+2* y* 0-2^2)-4*0 *2.1^2 *y)*(x^2+y^2+z^2)+ 4 * 2^4 * (2 *x+0 *y)* (-2^2+0 * y+2 * x)+4* 2^4 * 2.1^2 * y^2+2^8") ;
  minxlimit_2->setText("-2") ;
  minylimit_2->setText("-2") ;
  minzlimit_2->setText("-1.3") ;
  maxxlimit_2->setText("2.2") ;
  maxylimit_2->setText("2") ;
  maxzlimit_2->setText("1.3") ;
    }
  else 
  if(choix == QString("Hyperboloid")) {
  implicitfunct_2->setText("x^2 - y^2 - z^2 +0.3") ;
  minxlimit_2->setText("-1.8") ;
  minylimit_2->setText("-2") ;
  minzlimit_2->setText("-2") ;
  maxxlimit_2->setText("1.8") ;
  maxylimit_2->setText("2") ;
  maxzlimit_2->setText("2") ;
    }
  else if(choix == QString("Hyperbolic")) {
  implicitfunct_2->setText("x*x + y - z*z") ;
  minxlimit_2->setText("-1") ;
  minylimit_2->setText("-1") ;
  minzlimit_2->setText("-1") ;
  maxxlimit_2->setText("1") ;
  maxylimit_2->setText("1") ;
  maxzlimit_2->setText("1") ;
}
  else if(choix == QString("Sinus")) {
  implicitfunct_2->setText("sin(pi*((x)^2+(y)^2))/2 -z") ;
  minxlimit_2->setText("-1") ;
  minylimit_2->setText("-1") ;
  minzlimit_2->setText("-1") ;
  maxxlimit_2->setText("1") ;
  maxylimit_2->setText("1") ;
  maxzlimit_2->setText("1") ;
    }
  else  if(choix == QString("Octahedron")) {
  implicitfunct_2->setText("abs(x)+abs(y)+abs(z) - 1") ;
  minxlimit_2->setText("-1") ;
  minylimit_2->setText("-1") ;
  minzlimit_2->setText("-1") ;
  maxxlimit_2->setText("1") ;
  maxylimit_2->setText("1") ;
  maxzlimit_2->setText("1") ;
    }
  else  if(choix == QString("UnionSpheres")) {
  implicitfunct_2->setText("min( (x-0.7)*(x-0.7) + y*y + z*z - 1,  (x+0.5)*(x+0.5) + y*y + z*z - 1)") ;
  minxlimit_2->setText("-2") ;
  minylimit_2->setText("-2") ;
  minzlimit_2->setText("-2") ;
  maxxlimit_2->setText("2") ;
  maxylimit_2->setText("2") ;
  maxzlimit_2->setText("2") ;
    }
  else  if(choix == QString("IntersectSpheres")) {
  implicitfunct_2->setText("max( (x-0.7)*(x-0.7) + y*y + z*z - 1,  (x+0.5)*(x+0.5) + y*y + z*z - 1)") ;
  minxlimit_2->setText("-2") ;
  minylimit_2->setText("-2") ;
  minzlimit_2->setText("-2") ;
  maxxlimit_2->setText("2") ;
  maxylimit_2->setText("2") ;
  maxzlimit_2->setText("2") ;
    }

  else   if(choix == QString("Blobs")) {
  implicitfunct_2->setText("x^2 + y ^2 + z^2 +cos(4*x)+cos(4*y)+cos(4*z)-0.2") ;
  minxlimit_2->setText("-2") ;
  minylimit_2->setText("-2") ;
  minzlimit_2->setText("-2") ;
  maxxlimit_2->setText("2") ;
  maxylimit_2->setText("2") ;
  maxzlimit_2->setText("2") ;
    }
  else   if(choix == QString("Blobs_2")) {
  implicitfunct_2->setText("x^2 + y ^2 + z^2 +sin(4*x) + sin(4*y) + sin(4*z) -1") ;
  minxlimit_2->setText("-2") ;
  minylimit_2->setText("-2") ;
  minzlimit_2->setText("-2") ;
  maxxlimit_2->setText("2") ;
  maxylimit_2->setText("2") ;
  maxzlimit_2->setText("2") ;
    }
/*
  else  if(choix == QString("Cylindre")) {
  implicitfunct->setText("(x^2 + (y^2)/4 - 1) * ( (x^2)/4 + z^2 - 1) ") ;
  minxlimit->setText("-2") ;
  minylimit->setText("-2") ;
  minzlimit->setText("-2") ;
  maxxlimit->setText("2") ;
  maxylimit->setText("2") ;
  maxzlimit->setText("2") ;
    }
*/
  else   if(choix == QString("OrthoCircle")) {
  implicitfunct_2->setText("((x^2 + y^2 - 1)^2 + z^2)* ((y^2 + z^2 - 1)^2 + x^2)* ((z^2 + x^2 - 1)^2 + y^2) - 0.075^2 *(1 + 3* (x^2 + y^2 + z^2))") ;
  minxlimit_2->setText("-1.5") ;
  minylimit_2->setText("-1.5") ;
  minzlimit_2->setText("-1.5") ;
  maxxlimit_2->setText("1.5") ;
  maxylimit_2->setText("1.5") ;
  maxzlimit_2->setText("1.5") ;
    }
  else   if(choix == QString("CubeSphere")) {
  implicitfunct_2->setText("1 - ((1/2.3)^2 *(x^2 + y^2 + z^2))^-6 - ( (1/2)^8 * (x^8 + y^8 + z^8) )^6") ;
  minxlimit_2->setText("-2") ;
  minylimit_2->setText("-2") ;
  minzlimit_2->setText("-2") ;
  maxxlimit_2->setText("2") ;
  maxylimit_2->setText("2") ;
  maxzlimit_2->setText("2") ;
    }
  else   if(choix == QString("CubeSphere_2")) {
  implicitfunct_2->setText("12 - ((1/2.3)^2 *(x^2 + y^2 + z^2))^-6 - ( (1/2)^8 * (x^8 + y^8 + z^8) )^6") ;
  minxlimit_2->setText("-2") ;
  minylimit_2->setText("-2") ;
  minzlimit_2->setText("-2") ;
  maxxlimit_2->setText("2") ;
  maxylimit_2->setText("2") ;
  maxzlimit_2->setText("2") ;
    }


  else   if(choix == QString("Holes")) {
  implicitfunct_2->setText("sin(4*x) + sin(4*y) + sin(4*z)  + 4*x*y*z") ;
  minxlimit_2->setText("-2") ;
  minylimit_2->setText("-2") ;
  minzlimit_2->setText("-2") ;
  maxxlimit_2->setText("2") ;
  maxylimit_2->setText("2") ;
  maxzlimit_2->setText("2") ;
    }

  else   if(choix == QString("Virus")) {
  implicitfunct_2->setText("cos(x) + cos(y) + cos(z) - 1") ;
  minxlimit_2->setText("-4") ;
  minylimit_2->setText("-4") ;
  minzlimit_2->setText("-4") ;
  maxxlimit_2->setText("4") ;
  maxylimit_2->setText("4") ;
  maxzlimit_2->setText("4") ;
    }

  else   if(choix == QString("Schwartz")) {
  implicitfunct_2->setText("cos(x) + cos(y) + cos(z)") ;
  minxlimit_2->setText("-4") ;
  minylimit_2->setText("-4") ;
  minzlimit_2->setText("-4") ;
  maxxlimit_2->setText("4") ;
  maxylimit_2->setText("4") ;
  maxzlimit_2->setText("4") ;
    }

  else   if(choix == QString("Torus")) {
  implicitfunct_2->setText("(sqrt(x*x+z*z)-3)^2 + y*y - 1") ;
  minxlimit_2->setText("-4") ;
  minylimit_2->setText("-4") ;
  minzlimit_2->setText("-4") ;
  maxxlimit_2->setText("4") ;
  maxylimit_2->setText("4") ;
  maxzlimit_2->setText("4") ;
    }
   else   if(choix == QString("TwoCylinderBlend")) {
  implicitfunct_2->setText("(x^2 + y^2 - 1) * ( x^2 + z^2 - 1) - 1") ;
  minxlimit_2->setText("-3") ;
  minylimit_2->setText("-3") ;
  minzlimit_2->setText("-3") ;
  maxxlimit_2->setText("3") ;
  maxylimit_2->setText("3") ;
  maxzlimit_2->setText("3") ;
    }
  else   if(choix == QString("BlendThreeCylinder")) {
  implicitfunct_2->setText("(x^2 + y^2 - 1) * ( x^2 + z^2 - 1)* ( y^2 + z^2 - 1) - 1") ;
  minxlimit_2->setText("-3") ;
  minylimit_2->setText("-3") ;
  minzlimit_2->setText("-3") ;
  maxxlimit_2->setText("3") ;
  maxylimit_2->setText("3") ;
  maxzlimit_2->setText("3") ;
    }
  else   if(choix == QString("Sphere")) {
  implicitfunct_2->setText("x*x + y*y + z*z - 1") ;
  minxlimit_2->setText("-1") ;
  minylimit_2->setText("-1") ;
  minzlimit_2->setText("-1") ;
  maxxlimit_2->setText("1") ;
  maxylimit_2->setText("1") ;
  maxzlimit_2->setText("1") ;
    }
  else   if(choix == QString("Cube")) {
  implicitfunct_2->setText("x^4 + y^4 + z^4 - (x^2 + y^2 + z^2)") ;
  minxlimit_2->setText("-2") ;
  minylimit_2->setText("-2") ;
  minzlimit_2->setText("-2") ;
  maxxlimit_2->setText("2") ;
  maxylimit_2->setText("2") ;
  maxzlimit_2->setText("2") ;
    }
    
  else   if(choix == QString("RoundCube")) {
  implicitfunct_2->setText("x^4 + y^4 + z^4 -1") ;
  minxlimit_2->setText("-2") ;
  minylimit_2->setText("-2") ;
  minzlimit_2->setText("-2") ;
  maxxlimit_2->setText("2") ;
  maxylimit_2->setText("2") ;
  maxzlimit_2->setText("2") ;
    }

  else   if(choix == QString("Drope")) {
  implicitfunct_2->setText("4*x*exp(-x^2-y^2) -z") ;
  minxlimit_2->setText("-2") ;
  minylimit_2->setText("-2") ;
  minzlimit_2->setText("-1.7") ;
  maxxlimit_2->setText("2") ;
  maxylimit_2->setText("2") ;
  maxzlimit_2->setText("1.7") ;
    }

  else   if(choix == QString("Leminescape")) {
  implicitfunct_2->setText("4*x^2*(x^2+y^2+z^2+z)+y^2*(y^2+z^2-1)") ;
  minxlimit_2->setText("-0.5") ;
  minylimit_2->setText("-1") ;
  minzlimit_2->setText("-1") ;
  maxxlimit_2->setText("0.5") ;
  maxylimit_2->setText("1") ;
  maxzlimit_2->setText("1") ;
    }

  else   if(choix == QString("Klein")) {
  implicitfunct_2->setText("(x^2+y^2+z^2+2*y-1)*((x^2+y^2+z^2-2*y-1)^2-8*z^2)+16*x*z*(x^2+y^2+z^2-2*y-1)") ;
  minxlimit_2->setText("-3") ;
  minylimit_2->setText("-3.1") ;
  minzlimit_2->setText("-4") ;
  maxxlimit_2->setText("3") ;
  maxylimit_2->setText("3.1") ;
  maxzlimit_2->setText("4") ;
    }



 PerformNewToolsImplicitFunct_2();
}
//====================================
void k3dsurface::PerformNewToolsImplicitFunct()
{
    FunctionParser fp,f1;
    QMessageBox message ;

    fp.AddConstant("pi", 3.14159265);
    int ret;


    ret = fp.Parse(implicitfunct->text(), "x,y,z,t");
    if(ret >= 0)
    {

    message.setText(tr(QString("F(x,y,z) = --> At col:")+
    QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();

        return ;
    }

    
    ///Activaste IsoDrawing Area...
    tabsurf->setCurrentPage(1);
    
  isoWidget->IsoObjet->ImplicitFunction = implicitfunct->text();

  isoWidget->IsoObjet->XlimitSup = maxxlimit->text();
  isoWidget->IsoObjet->YlimitSup = maxylimit->text();
  isoWidget->IsoObjet->ZlimitSup = maxzlimit->text();

  isoWidget->IsoObjet->XlimitInf = minxlimit->text();
  isoWidget->IsoObjet->YlimitInf = minylimit->text();
  isoWidget->IsoObjet->ZlimitInf = minzlimit->text();
 
/*
  // process the new curve
  isoWidget->IsoMorphCompute();
*/
  ///Process New Surface :
 PerformNewImplicitFunct();  
  
  
}
//====================================
void k3dsurface::PerformNewToolsImplicitFunct_2()
{
    FunctionParser fp,f1;
    QMessageBox message ;

    fp.AddConstant("pi", 3.14159265);
    int ret;


    ret = fp.Parse(implicitfunct_2->text(), "x,y,z,t");
    if(ret >= 0)
    {

    message.setText(tr(QString("F(x,y,z) = --> At col:")+
    QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();

        return ;
    }

    
    ///Activaste IsoDrawing Area...
    tabsurf->setCurrentPage(1);
    
  isoWidget->IsoObjet->ImplicitFunction = implicitfunct_2->text();

  isoWidget->IsoObjet->XlimitSup = maxxlimit_2->text();
  isoWidget->IsoObjet->YlimitSup = maxylimit_2->text();
  isoWidget->IsoObjet->ZlimitSup = maxzlimit_2->text();

  isoWidget->IsoObjet->XlimitInf = minxlimit_2->text();
  isoWidget->IsoObjet->YlimitInf = minylimit_2->text();
  isoWidget->IsoObjet->ZlimitInf = minzlimit_2->text();
  
  ///Save theses equations :
    isoWidget->IsoObjet->ImplicitFunction_save = implicitfunct_2->text();

  isoWidget->IsoObjet->XlimitSup_save = maxxlimit_2->text();
  isoWidget->IsoObjet->YlimitSup_save = maxylimit_2->text();
  isoWidget->IsoObjet->ZlimitSup_save = maxzlimit_2->text();

  isoWidget->IsoObjet->XlimitInf_save = minxlimit_2->text();
  isoWidget->IsoObjet->YlimitInf_save = minylimit_2->text();
  isoWidget->IsoObjet->ZlimitInf_save = minzlimit_2->text(); 
  
  ///Update the Tools controls
  /// Scale Controls :
scalexvalue_2->setValue(10) ;
scaleyvalue_2->setValue(10) ;
scalezvalue_2->setValue(10) ;
/// Twist controls :

//scrollBar20_3_2->setValue(10) ;
//scrollBar20_2_2->setValue(10) ;
//scrollBar20_4->setValue(10) ;

scrollBar81_3_2->setValue(0) ;
scrollBar81_2_2->setValue(0) ;
scrollBar81_4->setValue(0) ;
/*  
  // process the new curve
  isoWidget->IsoMorphCompute();
*/
     // process the new surface
   ProcessNewIsoSurface( );
}


//====================================
void k3dsurface::PerformNewImplicitFunct()
{
    FunctionParser fp,f1;
    QMessageBox message ;
    QString resultequation;
    fp.AddConstant("pi", 3.14159265);
    int ret;

    resultequation = implicitfunct->text();
    
 if(implicit_param == 1) {
    ret = fp.Parse(implicitfunct->text(), "x,y,z,t");
    if(ret >= 0)
    {

    message.setText(tr(QString("F(x,y,z) = --> At col:")+
    QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();

        return ;
    }
}
 else if(implicit_spheric == 1 ) {
 
     ret = fp.Parse(implicitfunct->text(), "R,u,v,t");
    if(ret >= 0)
    {

    message.setText(tr(QString("F(R,u,v,t) = --> At col:")+
    QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();

        return ;
    }
    
    /// If all is Ok, make coordinate changes : R= sqrt(x^2+y^2+z^2), u= z/sqrt(x^2+y^2+z^2), v= abs(atan(y/x))
  resultequation.replace(QChar('u'), "(asin(z/sqrt(x^2+y^2+z^2)))");
  resultequation.replace(QChar('v'), "(abs(atan(y/x)))"); 
  resultequation.replace(QChar('R'), "(sqrt(x^2+y^2+z^2))");   
  
  
    
 }   
 else if(implicit_cylindric == 1 ) {
 
     ret = fp.Parse(implicitfunct->text(), "R,Z,u,t");
    if(ret >= 0)
    {

    message.setText(tr(QString("F(R,Z,u,t) = --> At col:")+
    QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();

        return ;
    }
    
  resultequation.replace(QChar('u'), "(abs(atan(y/x)))");
  resultequation.replace(QChar('Z'), "z");  
  resultequation.replace(QChar('R'), "(sqrt(x^2+y^2))");     
    
 }      
    
 
 
 
 
if(activate_isocd ==1 ) {
        ret = fp.Parse(Isocondition->text(), "x,y,z,t");
    if(ret >= 0)
    {

    message.setText(tr(QString("CND(x,y,z,t) = --> At col:")+
    QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();

        return ;
    }

    else {
    if(inverse_isocondition  == 1) 
    isoWidget->IsoObjet->IsoCondition = QString("("+Isocondition->text()+") = 0");
    else  isoWidget->IsoObjet->IsoCondition  = Isocondition->text(); 
    }
}
    /// Acivate the Iso Drawing Area...
   //  tabsurf->setCurrentPage(1);

  isoWidget->IsoObjet->ImplicitFunction = resultequation;

  isoWidget->IsoObjet->XlimitSup = maxxlimit->text();
  isoWidget->IsoObjet->YlimitSup = maxylimit->text();
  isoWidget->IsoObjet->ZlimitSup = maxzlimit->text();

  isoWidget->IsoObjet->XlimitInf = minxlimit->text();
  isoWidget->IsoObjet->YlimitInf = minylimit->text();
  isoWidget->IsoObjet->ZlimitInf = minzlimit->text();
  
  
    // process the new surface
   ProcessNewIsoSurface( );
}


//====================================
void k3dsurface::ProcessNewIsoSurface( )
{
    // process the new surface
int current_pag = tabsurf->currentPageIndex();
if(current_pag != 1) tabsurf->setCurrentPage(1);

if(isowidgetstack == 1)  {
isoWidget->IsoObjet->SpecialMorph_2(
         IsoGlWidget->ArrayNorVer_local,
         IsoGlWidget->PolyIndices_local,
         IsoGlWidget->NbPolygnNbVertex,
         IsoGlWidget->TypeIsoSurfaceTriangleListeCND,
         &(IsoGlWidget->VertexNumber),
         1);
IsoGlWidget->initializeGL();
IsoGlWidget->PolyNumber  = 3*isoWidget->IsoObjet->NbTriangleIsoSurface;
IsoGlWidget->LocalScene.typedrawing = 1;
IsoGlWidget->updateGL();
}
 else  isoWidget->IsoMorphCompute();
}

//====================================
void k3dsurface::tools_extrude1_changed( const QString & choix )
{

  if(choix == QString("Cosinus")) {  
  xtool_2_2->setText("cos(u)"); 
  ytool_2_2->setText("u");
  ztool_2_2->setText("1");
  umin_2_2->setText("0") ;
  umax_2_2->setText("2*pi") ;
    } 

  if(choix == QString("Sinus")) {
  xtool_2_2->setText("sin(u)");
  ytool_2_2->setText("u");
  ztool_2_2->setText("1");
  umin_2_2->setText("0") ;
  umax_2_2->setText("2*pi") ;
    }

  if(choix == QString("Helix")) {
  xtool_2_2->setText("u*sin(u)");
  ytool_2_2->setText("u*cos(u)");
  ztool_2_2->setText("1");
  umin_2_2->setText("0") ;
  umax_2_2->setText("4*pi") ;
    }

 perform_extrude1_tools();

}


//====================================
void k3dsurface::perform_extrude1_tools()
{
    FunctionParser fp,f1;
    QMessageBox message ;

    fp.AddConstant("pi", 3.14159265);
    int ret;


    ret = fp.Parse(xtool_2_2->text(), "u,t"); 
    if(ret >= 0)
    {

    message.setText(tr(QString("X=f(u)--> At col:")+
         QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();
        return ;
    }

    ret = fp.Parse(ytool_2_2->text(), "u,t");
    if(ret >= 0) 
    {

    message.setText(tr(QString("Y=g(u)--> At col:")+
    QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();
        return ;
    }

    ret = fp.Parse(ztool_2_2->text(), "u,t");
    if(ret >= 0)
    {
    message.setText(tr(QString("Z=h(u)--> At col:")+
    QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();
    return ;
    }

  connectWidget2->objet->expression_X = xtool_2_2->text();
  connectWidget2->objet->expression_Y = ytool_2_2->text();
  connectWidget2->objet->expression_Z = ztool_2_2->text();
  connectWidget2->objet->inf_u = umin_2_2->text();
  connectWidget2->objet->sup_u = umax_2_2->text();
  connectWidget2->objet->inf_v = "0";
  connectWidget2->objet->sup_v = "2*pi";
/*
  // process the new curve
  connectWidget2->valueChanged();
*/
    // process the new surface
ParametricSurfaceProcess();
  
}


//====================================
void k3dsurface::tools_extrude2_changed( const QString & choix )
{

  if(choix == QString("Cosinus")) {  
  xtool_2_3->setText("cos(v)"); 
  ytool_2_3->setText("1");
  ztool_2_3->setText("v"); 
  umin_2_3->setText("0") ; 
  umax_2_3->setText("2*pi") ; 
    } 

  if(choix == QString("Sinus")) {  
  xtool_2_3->setText("sin(v)"); 
  ytool_2_3->setText("1");
  ztool_2_3->setText("v");
  umin_2_3->setText("0") ; 
  umax_2_3->setText("2*pi") ; 
    }

  if(choix == QString("Helix")) {  
  xtool_2_3->setText("v*sin(v)"); 
  ytool_2_3->setText("1");
  ztool_2_3->setText("v*cos(v)"); 
  umin_2_3->setText("0") ; 
  umax_2_3->setText("4*pi") ; 
    }
 
 perform_extrude2_tools();
 
}

//====================================
void k3dsurface::perform_extrude2_tools()
{    
    FunctionParser fp,f1;
    QMessageBox message ;
     
    fp.AddConstant("pi", 3.14159265);
    int ret;
    
    

    
    ret = fp.Parse(xtool_2_3->text(), "v,t"); 
    if(ret >= 0) 
    { 

    message.setText(tr(QString("X=f(v)--> At col:")+
         QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();  
 
        return ; 
    } 
    
    ret = fp.Parse(ytool_2_3->text(), "v,t");
    if(ret >= 0) 
    { 

    message.setText(tr(QString("Y=g(v)--> At col:")+
 QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec(); 

        return ; 
    } 

    ret = fp.Parse(ztool_2_3->text(), "v,t");
    if(ret >= 0) 
    { 

    message.setText(tr(QString("Z=h(v)--> At col:")+
 QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec(); 

        return ; 
    } 

  connectWidget2->objet->expression_X = xtool_2_3->text();
  connectWidget2->objet->expression_Y = ytool_2_3->text();    
  connectWidget2->objet->expression_Z = ztool_2_3->text(); 
  connectWidget2->objet->inf_u = "0";
  connectWidget2->objet->sup_u = "2*pi";
  connectWidget2->objet->inf_v = umin_2_3->text();
  connectWidget2->objet->sup_v = umax_2_3->text();
/*
  // process the new curve
  connectWidget2->valueChanged(); 
*/
    // process the new surface
ParametricSurfaceProcess();
  
}

//====================================
void k3dsurface::perform_3Dextrude_tools()
{    
    FunctionParser fp,f1;
    QMessageBox message ;
     
    fp.AddConstant("pi", 3.14159265);
    int ret;
    
    

    
    ret = fp.Parse(xtool_2_2->text(), "u,t"); 
    if(ret >= 0) 
    {message.setText(tr(QString("X=f(u)--> At col:")+
         QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();  
 
        return ; 
    } 
    
    ret = fp.Parse(ytool_2_2->text(), "u,t");
    if(ret >= 0) 
    {message.setText(tr(QString("Y=g(u)--> At col:")+
 QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec(); 

        return ; 
    } 

    
    ret = fp.Parse(ztool_2_2->text(), "u,t");
    if(ret >= 0) 
    {message.setText(tr(QString("Z=h(u)--> At col:")+
 QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec(); 

        return ; 
    } 


    ret = fp.Parse(xtool_2_3->text(), "v,t"); 
    if(ret >= 0) 
    {message.setText(tr(QString("X=f(v)--> At col:")+
         QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();  
 
        return ; 
    } 
    
    ret = fp.Parse(ytool_2_3->text(), "v,t");
    if(ret >= 0) 
    {message.setText(tr(QString("Y=g(v)--> At col:")+
 QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec(); 

        return ; 
    } 

    
    ret = fp.Parse(ztool_2_3->text(), "v,t");
    if(ret >= 0) 
    {message.setText(tr(QString("Z=h(v)--> At col:")+
 QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec(); 

        return ; 
    } 



  connectWidget2->objet->expression_X = xtool_2_2->text()+" + "+xtool_2_3->text();
  connectWidget2->objet->expression_Y = ytool_2_2->text()+" + "+ytool_2_3->text();    
  connectWidget2->objet->expression_Z = ztool_2_2->text()+" + "+ztool_2_3->text();
  
   
  connectWidget2->objet->inf_u = umin_2_2->text();
  connectWidget2->objet->sup_u = umax_2_2->text();
  connectWidget2->objet->inf_v = umin_2_3->text();
  connectWidget2->objet->sup_v = umax_2_3->text();
  
  // Show equations
  connectWidget2->objet->two_system = -1;
  xtool->setText(connectWidget2->objet->expression_X);
  ytool->setText(connectWidget2->objet->expression_Y);
  ztool->setText(connectWidget2->objet->expression_Z);
  
  umin_tools->setText(connectWidget2->objet->inf_u);
  umax_tools->setText(connectWidget2->objet->sup_u);
  vmin_tools->setText(connectWidget2->objet->inf_v);
  vmax_tools->setText(connectWidget2->objet->sup_v);
  
  perform_tools();
}


//====================================
void k3dsurface::tools_loft1_changed( const QString & choix )
{

  if(choix == QString("Cosinus")) {  
  xtool_2_4->setText("cos(u)"); 
  ytool_2_4->setText("u");
  ztool_2_4->setText("1"); 
  umin_2_4->setText("0") ; 
  umax_2_4->setText("2*pi") ; 
    } 

  if(choix == QString("Sinus")) {  
  xtool_2_4->setText("sin(u)"); 
  ytool_2_4->setText("u");
  ztool_2_4->setText("1");
  umin_2_4->setText("0") ; 
  umax_2_4->setText("2*pi") ; 
    }

  if(choix == QString("Helix")) {  
  xtool_2_4->setText("u*sin(u)"); 
  ytool_2_4->setText("u*cos(u)");
  ztool_2_4->setText("1"); 
  umin_2_4->setText("0") ; 
  umax_2_4->setText("4*pi") ; 
    }
 
 perform_loft1_tools();
 
}
//====================================
void k3dsurface::perform_loft1_tools()
{    
    FunctionParser fp,f1;
    QMessageBox message ;
     
    fp.AddConstant("pi", 3.14159265);
    int ret;
    
    

    
    ret = fp.Parse(xtool_2_4->text(), "u,t"); 
    if(ret >= 0) 
    { 

    message.setText(tr(QString("X=f(u)--> At col:")+
         QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();  
 
        return ; 
    } 
    
    ret = fp.Parse(ytool_2_4->text(), "u,t");
    if(ret >= 0) 
    { 

    message.setText(tr(QString("Y=g(u)--> At col:")+
 QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec(); 

        return ; 
    } 

    ret = fp.Parse(ztool_2_4->text(), "u,t");
    if(ret >= 0) 
    { 

    message.setText(tr(QString("Z=h(u)--> At col:")+
 QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec(); 

        return ; 
    } 

  connectWidget2->objet->expression_X = xtool_2_4->text();
  connectWidget2->objet->expression_Y = ytool_2_4->text();    
  connectWidget2->objet->expression_Z = ztool_2_4->text(); 
  connectWidget2->objet->inf_u = umin_2_4->text();
  connectWidget2->objet->sup_u = umax_2_4->text();
  connectWidget2->objet->inf_v = "0";
  connectWidget2->objet->sup_v = "2*pi";
/*
  // process the new curve
  connectWidget2->valueChanged(); 
*/

  // process the new surface
ParametricSurfaceProcess();
}

//====================================
void k3dsurface::tools_loft2_changed( const QString & choix )
{

  if(choix == QString("Cosinus")) {  
  xtool_2_5->setText("cos(v)"); 
  ytool_2_5->setText("1");
  ztool_2_5->setText("v"); 
  umin_2_5->setText("0") ; 
  umax_2_5->setText("2*pi") ; 
    } 

  if(choix == QString("Sinus")) {  
  xtool_2_5->setText("sin(v)"); 
  ytool_2_5->setText("1");
  ztool_2_5->setText("v");
  umin_2_5->setText("0") ; 
  umax_2_5->setText("2*pi") ; 
    }

  if(choix == QString("Helix")) {  
  xtool_2_5->setText("v*sin(v)"); 
  ytool_2_5->setText("1");
  ztool_2_5->setText("v*cos(v)"); 
  umin_2_5->setText("0") ; 
  umax_2_5->setText("4*pi") ; 
    }
 
 perform_loft2_tools();
 
}
//====================================
void k3dsurface::perform_loft2_tools()
{    
    FunctionParser fp,f1;
    QMessageBox message ;
     
    fp.AddConstant("pi", 3.14159265);
    int ret;
    
    

    
    ret = fp.Parse(xtool_2_5->text(), "v,t"); 
    if(ret >= 0) 
    { 

    message.setText(tr(QString("X=f(v)--> At col:")+
         QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();  
 
        return ; 
    } 
    
    ret = fp.Parse(ytool_2_5->text(), "v,t");
    if(ret >= 0) 
    { 

    message.setText(tr(QString("Y=g(v)--> At col:")+
 QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec(); 

        return ; 
    } 

    ret = fp.Parse(ztool_2_5->text(), "v,t");
    if(ret >= 0) 
    { 

    message.setText(tr(QString("Z=h(v)--> At col:")+
 QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec(); 

        return ; 
    } 

  connectWidget2->objet->expression_X = xtool_2_5->text();
  connectWidget2->objet->expression_Y = ytool_2_5->text();    
  connectWidget2->objet->expression_Z = ztool_2_5->text(); 
  connectWidget2->objet->inf_u = "0";
  connectWidget2->objet->sup_u = "2*pi";
  connectWidget2->objet->inf_v = umin_2_5->text();
  connectWidget2->objet->sup_v = umax_2_5->text();
/*
  // process the new curve
  connectWidget2->valueChanged(); 
*/

  // process the new surface
ParametricSurfaceProcess();
}

//====================================
void k3dsurface::perform_3Dloft_tools()
{    
    FunctionParser fp,f1;
    QMessageBox message ;
     
    fp.AddConstant("pi", 3.14159265);
    int ret;
    
    ret = fp.Parse(xtool_2_4->text(), "u,t"); 
    if(ret >= 0) 
    {message.setText(tr(QString("X=f(u)--> At col:")+
         QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();  
 
        return ; 
    } 

    ret = fp.Parse(ytool_2_4->text(), "u,t");
    if(ret >= 0) 
    {message.setText(tr(QString("Y=g(u)--> At col:")+
 QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec(); 

        return ; 
    } 

    ret = fp.Parse(ztool_2_4->text(), "u,t");
    if(ret >= 0) 
    {message.setText(tr(QString("Z=h(u)--> At col:")+
 QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec(); 

        return ; 
    } 


    ret = fp.Parse(xtool_2_5->text(), "v,t"); 
    if(ret >= 0) 
    {message.setText(tr(QString("X=f(v)--> At col:")+
         QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();  
 
        return ; 
    } 
    
    ret = fp.Parse(ytool_2_5->text(), "v,t");
    if(ret >= 0) 
    {message.setText(tr(QString("Y=g(v)--> At col:")+
 QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec(); 

        return ; 
    } 

    
    ret = fp.Parse(ztool_2_5->text(), "v,t");
    if(ret >= 0) 
    {message.setText(tr(QString("Z=h(v)--> At col:")+
 QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec(); 

        return ; 
    } 

QString alfa1 = "("+umax_2_5->text()+" - v)/("+
                umax_2_5->text()+" - "+umin_2_5->text()+") * ";

QString alfa2 = "(u - "+umin_2_4->text()+")/("+
                umax_2_4->text()+" - "+umin_2_4->text()+") * ";
                
  connectWidget2->objet->expression_X = 
  alfa1+xtool_2_4->text()+" + "+alfa2+xtool_2_5->text();
  
  connectWidget2->objet->expression_Y = 
  alfa1+ytool_2_4->text()+" + "+alfa2+ytool_2_5->text();
     
  connectWidget2->objet->expression_Z = 
  alfa1+ztool_2_4->text()+" + "+alfa2+ztool_2_5->text();
  
   
  connectWidget2->objet->inf_u = umin_2_4->text();
  connectWidget2->objet->sup_u = umax_2_4->text();
  connectWidget2->objet->inf_v = umin_2_5->text();
  connectWidget2->objet->sup_v = umax_2_5->text();
  
  // Show equations
  connectWidget2->objet->two_system = -1;
  xtool->setText(connectWidget2->objet->expression_X);
  ytool->setText(connectWidget2->objet->expression_Y);
  ztool->setText(connectWidget2->objet->expression_Z);
  
  umin_tools->setText(connectWidget2->objet->inf_u);
  umax_tools->setText(connectWidget2->objet->sup_u);
  vmin_tools->setText(connectWidget2->objet->inf_v);
  vmax_tools->setText(connectWidget2->objet->sup_v);
  
  perform_tools();
}

//====================================
void k3dsurface::tools_curve_changed( const QString & choix )
{

  if(choix == QString("Cosinus")) {  
  rotcurvex->setText("cos(u)"); 
  rotcurvey->setText("u");
  rotcurvez->setText("1"); 
  umin_tools_2->setText("0") ; 
  umax_tools_2->setText("2*pi") ; 
    } 

  if(choix == QString("Sinus")) {  
  rotcurvex->setText("sin(u)"); 
  rotcurvey->setText("u");
  rotcurvez->setText("1");
  umin_tools_2->setText("0") ; 
  umax_tools_2->setText("2*pi") ; 
    }

  if(choix == QString("Helix")) {  
  rotcurvex->setText("u*sin(u)"); 
  rotcurvey->setText("u*cos(u)");
  rotcurvez->setText("1"); 
  umin_tools_2->setText("0") ; 
  umax_tools_2->setText("4*pi") ; 
    }
 
 perform_curve_tools();
 
}
//====================================
void k3dsurface::perform_curve_tools()
{    
    FunctionParser fp,f1;
    QMessageBox message ;
     
    fp.AddConstant("pi", 3.14159265);
    int ret;
    
    

    
    ret = fp.Parse(rotcurvex->text(), "u,t"); 
    if(ret >= 0) 
    { 

    message.setText(tr(QString("X=f(u)--> At col:")+
         QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();  
 
        return ; 
    } 
    
    ret = fp.Parse(rotcurvey->text(), "u,t");
    if(ret >= 0) 
    { 

    message.setText(tr(QString("Y=g(u)--> At col:")+
 QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec(); 

        return ; 
    } 

    ret = fp.Parse(rotcurvez->text(), "u,t");
    if(ret >= 0) 
    { 

    message.setText(tr(QString("Z=h(u)--> At col:")+
 QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec(); 

        return ; 
    } 

  connectWidget2->objet->expression_X = rotcurvex->text();
  connectWidget2->objet->expression_Y = rotcurvey->text();    
  connectWidget2->objet->expression_Z = rotcurvez->text(); 
  connectWidget2->objet->inf_u = umin_tools_2->text();
  connectWidget2->objet->sup_u = umax_tools_2->text();
  connectWidget2->objet->inf_v = "0";
  connectWidget2->objet->sup_v = "2*pi";
/*
  // process the new curve
  connectWidget2->valueChanged(); 
*/
    // process the new surface
ParametricSurfaceProcess();
  
}

//====================================
void k3dsurface::perform_3Dcurve_tools()
{    
    FunctionParser fp,f1;
    QMessageBox message ;
     
    fp.AddConstant("pi", 3.14159265);
    int ret;
    
    

    
    ret = fp.Parse(rotcurvex->text(), "u,t"); 
    if(ret >= 0) 
    {message.setText(tr(QString("X=f(u)--> At col:")+
         QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();  
 
        return ; 
    } 
    
    ret = fp.Parse(rotcurvey->text(), "u,t");
    if(ret >= 0) 
    {message.setText(tr(QString("Y=g(u)--> At col:")+
 QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec(); 

        return ; 
    } 

    
    ret = fp.Parse(rotcurvez->text(), "u,t");
    if(ret >= 0) 
    {message.setText(tr(QString("Z=h(u)--> At col:")+
 QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec(); 

        return ; 
    } 
  
    
        if(axechoice == 0) {
  QString Axe_distance = "sqrt(("+rotcurvey->text()+
                         ")^2 + ("+rotcurvez->text()+")^2)";

  connectWidget2->objet->expression_X = rotcurvex->text();
  connectWidget2->objet->expression_Y = Axe_distance+"*sin(v)";
  connectWidget2->objet->expression_Z = Axe_distance+"*cos(v)";
}
else if(axechoice == 1) {
  QString Axe_distance = "sqrt(("+rotcurvex->text()+
                         ")^2 + ("+rotcurvez->text()+")^2)";

  connectWidget2->objet->expression_X = Axe_distance+"*sin(v)";
  connectWidget2->objet->expression_Y = rotcurvey->text();    
  connectWidget2->objet->expression_Z = Axe_distance+"*cos(v)";
}

else {
  QString Axe_distance = "sqrt(("+rotcurvex->text()+
                         ")^2 + ("+rotcurvey->text()+")^2)";

  connectWidget2->objet->expression_X = Axe_distance+"*sin(v)";
  connectWidget2->objet->expression_Y =  Axe_distance+"*cos(v)";
  connectWidget2->objet->expression_Z =  rotcurvez->text(); 
}



  connectWidget2->objet->inf_u = umin_tools_2->text();
  connectWidget2->objet->sup_u = umax_tools_2->text();
  connectWidget2->objet->inf_v = "0";
  connectWidget2->objet->sup_v = "2*pi";

  // process the new curve
  //connectWidget2->valueChanged();  // was replaced by "perform_tools()"
  
  // Show equations
  connectWidget2->objet->two_system = -1;
  xtool->setText(connectWidget2->objet->expression_X);
  ytool->setText(connectWidget2->objet->expression_Y);
  ztool->setText(connectWidget2->objet->expression_Z);
  
  umin_tools->setText(connectWidget2->objet->inf_u);
  umax_tools->setText(connectWidget2->objet->sup_u);
  vmin_tools->setText(connectWidget2->objet->inf_v);
  vmax_tools->setText(connectWidget2->objet->sup_v);
  
  perform_tools();
}
//====================================
void k3dsurface::tools_changed( const QString & choix )
{

  if(choix == QString("Prism")) {
   
   connectWidget2->objet->two_system = -1;
  
  xtool->setText("cos(u)*cos(v)*(abs(cos(3*v/4))^500 + abs(sin(3*v/4))^500)^(-1/260)*(abs(cos(4*u/4))^200 + abs(sin(4*u/4))^200)^(-1/200)");
  
  ytool->setText("cos(u)*sin(v)*(abs(cos(3*v/4))^500 + abs(sin(3*v/4))^500)^(-1/260)*(abs(cos(4*u/4))^200 + abs(sin(4*u/4))^200)^(-1/200)");
  
  ztool->setText("sin(u)*(abs(cos(4*u/4))^200 + abs(sin(4*u/4))^200)^(-1/200)") ;
  umin_tools->setText("-pi/2") ; 
  umax_tools->setText("pi/2") ; 
  vmin_tools->setText("0") ; 
  vmax_tools->setText("2*pi") ; 

    } 
    

                        if(choix == QString("Cube")) {
   
   connectWidget2->objet->two_system = -1;
  
  xtool->setText("cos(u)*cos(v)*(abs(cos(4*u/4))^100 + abs(sin(4*u/4))^100)^(-1/100)*(abs(cos(4*v/4))^100 + abs(sin(4*v/4))^100)^(-1/100)");
  
  ytool->setText("cos(u)*sin(v)*(abs(cos(4*u/4))^100 + abs(sin(4*u/4))^100)^(-1/100)*(abs(cos(4*v/4))^100 + abs(sin(4*v/4))^100)^(-1/100)");
  
  ztool->setText("sin(u)*(abs(cos(4*u/4))^100 + abs(sin(4*u/4))^100)^(-1/100)") ;
  umin_tools->setText("-pi/2") ; 
  umax_tools->setText("pi/2") ; 
  vmin_tools->setText("0") ; 
  vmax_tools->setText("2*pi") ; 

    } 

                        if(choix == QString("Hexagon")) {
   connectWidget2->objet->two_system = -1;
  xtool->setText("cos(u)*cos(v)*(abs(cos(4*u/4))^300 + abs(sin(4*u/4))^300)^(-1/300)*(abs(cos(6*v/4))^400 + abs(sin(6*v/4))^400)^(-1/1000)");
  
  ytool->setText("cos(u)*sin(v)*(abs(cos(4*u/4))^300 + abs(sin(4*u/4))^300)^(-1/300)*(abs(cos(6*v/4))^400 + abs(sin(6*v/4))^400)^(-1/1000)");
  
  ztool->setText("sin(u)*(abs(cos(4*u/4))^300 + abs(sin(4*u/4))^300)^(-1/300)") ;
  umin_tools->setText("-pi/2") ; 
  umax_tools->setText("pi/2") ; 
  vmin_tools->setText("0") ; 
  vmax_tools->setText("2*pi") ; 
 
    } 
        
    
                        if(choix == QString("Cone")) {
   connectWidget2->objet->two_system = -1;
  xtool->setText("cos(u)*cos(v)*(abs(cos(4*u/4))^1 + abs(sin(4*u/4))^1)^(-1/1)*(abs(cos(4*v/4))^1 + abs(sin(4*v/4))^1)^(-1/100)");
  
  ytool->setText("cos(u)*sin(v)*(abs(cos(4*u/4))^1 + abs(sin(4*u/4))^1)^(-1/1)*(abs(cos(4*v/4))^1 + abs(sin(4*v/4))^1)^(-1/100)");
  
  ztool->setText("sin(u)*(abs(cos(4*u/4))^1 + abs(sin(4*u/4))^1)^(-1/1)") ;
  umin_tools->setText("-pi/2") ; 
  umax_tools->setText("pi/2") ; 
  vmin_tools->setText("0") ; 
  vmax_tools->setText("2*pi") ; 
  
    } 
        
    
                         if(choix == QString("Diamond")) {
    connectWidget2->objet->two_system = -1;
  xtool->setText("cos(u)*cos(v)*(abs(cos(4*u/4))^1 + abs(sin(4*u/4))^1)^(-1/1)*(abs(cos(4*v/4))^1 + abs(sin(4*v/4))^1)^(-1/1)");
  
  ytool->setText("cos(u)*sin(v)*(abs(cos(4*u/4))^1 + abs(sin(4*u/4))^1)^(-1/1)*(abs(cos(4*v/4))^1 + abs(sin(4*v/4))^1)^(-1/1)");
  
  ztool->setText("sin(u)*(abs(cos(4*u/4))^1 + abs(sin(4*u/4))^1)^(-1/1)") ;
  umin_tools->setText("-pi/2") ; 
  umax_tools->setText("pi/2") ; 
  vmin_tools->setText("0") ; 
  vmax_tools->setText("2*pi") ; 
 
    }

       
                         if(choix == QString("Shape_10")) {
     connectWidget2->objet->two_system = -1;
  xtool->setText("cos(u)*cos(v)*(abs(cos(3*u/4))^1 + abs(sin(3*u/4))^1)^(-1/1)*(abs(cos(6*v/4))^1 + abs(sin(6*v/4))^1)^(-1/1)");
  
  ytool->setText("cos(u)*sin(v)*(abs(cos(3*u/4))^1 + abs(sin(3*u/4))^1)^(-1/1)*(abs(cos(6*v/4))^1 + abs(sin(6*v/4))^1)^(-1/1)");
  
  ztool->setText("sin(u)*(abs(cos(3*u/4))^1 + abs(sin(3*u/4))^1)^(-1/1)") ;
  umin_tools->setText("-pi/2") ; 
  umax_tools->setText("pi/2") ; 
  vmin_tools->setText("0") ; 
  vmax_tools->setText("2*pi") ; 
 
    }
       
                         if(choix == QString("Star_7")) {

   connectWidget2->objet->two_system = -1;

  xtool->setText("cos(u)*cos(v)*(abs(cos(7*v/4))^1.7 + abs(sin(7*v/4))^1.7)^(-1/0.2)*(abs(cos(7*u/4))^1.7 + abs(sin(7*u/4))^1.7)^(-1/0.2)");
  
  ytool->setText("cos(u)*sin(v)*(abs(cos(7*v/4))^1.7 + abs(sin(7*v/4))^1.7)^(-1/0.2)*(abs(cos(7*u/4))^1.7 + abs(sin(7*u/4))^1.7)^(-1/0.2)");
  
  ztool->setText("sin(u)*(abs(cos(7*u/4))^1.7 + abs(sin(7*u/4))^1.7)^(-1/0.2)") ;
  umin_tools->setText("-pi/2") ; 
  umax_tools->setText("pi/2") ; 
  vmin_tools->setText("0") ; 
  vmax_tools->setText("2*pi") ; 

    } 
      
                         if(choix == QString("Shape_8")) {
   connectWidget2->objet->two_system = -1;

  xtool->setText("cos(u)*cos(v)*(abs(cos(3*u/4))^100 + abs(sin(3*u/4))^100)^(-1/100)*(abs(cos(2*v/4))^0.3 + abs(sin(2*v/4))^0.2)^(-1/0.7)"); 
  ytool->setText("cos(u)*sin(v)*(abs(cos(3*u/4))^100 + abs(sin(3*u/4))^100)^(-1/100)*(abs(cos(2*v/4))^0.3 + abs(sin(2*v/4))^0.2)^(-1/0.7)"); 
  ztool->setText("sin(u)*(abs(cos(3*u/4))^100 + abs(sin(3*u/4))^100)^(-1/100)"); 

  umin_tools->setText("-pi/2") ; 
  umax_tools->setText("pi/2") ; 
  vmin_tools->setText("0") ; 
  vmax_tools->setText("2*pi") ; 

    } 
       
                         if(choix == QString("Shape_9")) {
   connectWidget2->objet->two_system = -1;
  xtool->setText("cos(u)*cos(v)*(abs(cos(2*u/4))^10 + abs(sin(2*u/4))^10)^(-1/10)*(abs(cos(8*v/4))^100 + abs(sin(8*v/4))^30)^(-1/60)");  
  ytool->setText("cos(u)*sin(v)*(abs(cos(2*u/4))^10 + abs(sin(2*u/4))^10)^(-1/10)*(abs(cos(8*v/4))^100 + abs(sin(8*v/4))^30)^(-1/60)"); 
  ztool->setText("sin(u)*(abs(cos(2*u/4))^10 + abs(sin(2*u/4))^10)^(-1/10)") ;
  umin_tools->setText("-pi/2") ; 
  umax_tools->setText("pi/2") ; 
  vmin_tools->setText("0") ; 
  vmax_tools->setText("2*pi") ; 

    } 
       
                          if(choix == QString("Star")) {

   connectWidget2->objet->two_system = -1;
  xtool->setText("cos(u)*cos(v)*(abs(cos(1*u/4))^0.5 + abs(sin(1*u/4))^0.5)^(-1/0.3)*(abs(cos(5*v/4))^1.7 + abs(sin(5*v/4))^1.7)^(-1/0.1)");
  
  ytool->setText("cos(u)*sin(v)*(abs(cos(1*u/4))^0.5 + abs(sin(1*u/4))^0.5)^(-1/0.3)*(abs(cos(5*v/4))^1.7 + abs(sin(5*v/4))^1.7)^(-1/0.1)");
  
  ztool->setText("sin(u)*(abs(cos(1*u/4))^0.5 + abs(sin(1*u/4))^0.5)^(-1/0.3)") ;
  umin_tools->setText("-pi/2") ; 
  umax_tools->setText("pi/2") ; 
  vmin_tools->setText("0") ; 
  vmax_tools->setText("2*pi") ; 

    }    
            


                        if(choix == QString("Implicit_Lemniscape")) {
   connectWidget2->objet->two_system = -1;
  xtool->setText("cos(v)*sqrt(abs(sin(2*u)))*cos(u)");
  ytool->setText("cos(v)*sqrt(abs(sin(2*u)))*sin(u)");
  ztool->setText("(cos(v)*sqrt(abs(sin(2*u)))*cos(u))^2 - (cos(v)*sqrt(abs(sin(2*u)))*sin(u))^2 + 2*(cos(v)*sqrt(abs(sin(2*u)))*cos(u))*(cos(v)*sqrt(abs(sin(2*u)))*sin(u))*(tan(v)^2)") ;
  umin_tools->setText("0") ; 
  umax_tools->setText("pi") ; 
  vmin_tools->setText("0") ; 
  vmax_tools->setText("pi") ; 

    } 
    

                        if(choix == QString("Twisted_heart")) {
   connectWidget2->objet->two_system = -1;
  xtool->setText("( abs(v) - abs(u) - abs(tanh((1/sqrt(2))*u)/(1/sqrt(2))) + abs(tanh((1/sqrt(2))*v)/(1/sqrt(2))) )*sin(v)");
  ytool->setText("( abs(v) - abs(u) - abs(tanh((1/sqrt(2))*u)/(1/sqrt(2))) - abs(tanh((1/sqrt(2))*v)/(1/sqrt(2))) )*cos(v)");
  ztool->setText("(1/sqrt(2))*( u^2 + v^2 ) / ( cosh((1/sqrt(2))*u)*cosh((1/sqrt(2))*v) )") ;
  umin_tools->setText("0") ; 
  umax_tools->setText("pi") ; 
  vmin_tools->setText("-pi") ; 
  vmax_tools->setText("pi") ;

    } 
  
    
                        if(choix == QString("Folium")) {
   connectWidget2->objet->two_system = -1;
  xtool->setText("cos(u) *(2*v/pi - tanh(v))");
  ytool->setText("cos(u + 2*pi / 3) / cosh(v)");
  ztool->setText("cos(u - 2*pi / 3) / cosh(v)") ;
  umin_tools->setText("-pi") ; 
  umax_tools->setText("pi") ; 
  vmin_tools->setText("-pi") ; 
  vmax_tools->setText("pi") ;  
 
    }   

    
                        if(choix == QString("Heart")) {
   connectWidget2->objet->two_system = -1;
  xtool->setText("cos(u)*(4*sqrt(1-v^2)*sin(abs(u))^abs(u))");
  ytool->setText("sin(u) *(4*sqrt(1-v^2)*sin(abs(u))^abs(u))");
  ztool->setText("v") ;
  umin_tools->setText("-pi") ; 
  umax_tools->setText("pi") ; 
  vmin_tools->setText("-1") ; 
  vmax_tools->setText("1") ;  
 
    }
                        
   
   
   
   if(choix == QString("Bow_Tie")) {
   connectWidget2->objet->two_system = -1;
  xtool->setText("sin(u) / (sqrt(2) + sin(v))");
  ytool->setText("sin(u) / (sqrt(2) + sin(v))");
  ztool->setText("cos(u) / (1 + sqrt(2))") ;
  umin_tools->setText("-pi") ; 
  umax_tools->setText("pi") ; 
  vmin_tools->setText("-pi") ; 
  vmax_tools->setText("pi") ;  

    } 
    

                        if(choix == QString("Triaxial_Hexatorus")) {
   connectWidget2->objet->two_system = -1;
  xtool->setText("sin(u) / (sqrt(2) + cos(v))");
  ytool->setText("sin(u+2*pi/3) / (sqrt(2) + cos(v+2*pi/3))");
  ztool->setText("cos(u-2*pi/3) / (sqrt(2) + cos(v-2*pi/3))") ;
  umin_tools->setText("-pi") ; 
  umax_tools->setText("pi") ; 
  vmin_tools->setText("-pi") ; 
  vmax_tools->setText("pi") ;

    }


                        if(choix == QString("Ghost_Plane")) {
   connectWidget2->objet->two_system = -1;
  xtool->setText("cos(u)*sinh(v) / (cosh(v) - cos(u))");
  ytool->setText("cos(u)*sin(u) / (cosh(v) - cos(u))");
  ztool->setText("sin(u)") ;
  umin_tools->setText("-pi") ; 
  umax_tools->setText("pi") ; 
  vmin_tools->setText("-pi") ; 
  vmax_tools->setText("pi") ; 
 
    }


                        if(choix == QString("Bent_Horns")) {
   connectWidget2->objet->two_system = -1;
  xtool->setText("(2 + cos(u))*(v/3 - sin(v))");
  ytool->setText("(2 + cos(u - 2*pi / 3)) *(cos(v) - 1) ");
  ztool->setText("(2 + cos(u + 2*pi / 3))*(cos(v) - 1) ") ;
  umin_tools->setText("-pi") ; 
  umax_tools->setText("pi") ; 
  vmin_tools->setText("-2*pi") ; 
  vmax_tools->setText("2*pi") ; 
 
    }


                        if(choix == QString("Richmond")) {
   connectWidget2->objet->two_system = -1;
  xtool->setText("(-3* u - u*5 + 2*u^3*v^2 + 3*u*v^4) / (6*(u*u + v*v))");
  ytool->setText("(-3*v - 3*u^4*v - 2*u^2*v^3 + v^5) / (6*(u*u + v*v))");
  ztool->setText("u") ;
  umin_tools->setText("-pi") ; 
  umax_tools->setText("pi") ; 
  vmin_tools->setText("-pi") ; 
  vmax_tools->setText("pi") ; 
 
    } 


                        if(choix == QString("Kidney")) {
   connectWidget2->objet->two_system = -1;
  xtool->setText("cos(u) *(3  *cos(v) - cos(3  *v))");
  ytool->setText("sin(u)  *(3  *cos(v) - cos(3 * v))");
  ztool->setText("3  *sin(v) - sin(3 * v)") ;
  umin_tools->setText("0") ; 
  umax_tools->setText("2*pi") ; 
  vmin_tools->setText("-pi/2") ; 
  vmax_tools->setText("pi/2") ; 
 
    } 


                        if(choix == QString("Kinky_Torus")) {
   connectWidget2->objet->two_system = -1;
  xtool->setText("1/cosh(u) - cos(v)");
  ytool->setText("sin(v)");
  ztool->setText("u / pi - tanh(v)") ;
  umin_tools->setText("-2*pi") ; 
  umax_tools->setText("2*pi") ; 
  vmin_tools->setText("-pi") ; 
  vmax_tools->setText("pi") ; 
 
    } 


                        if(choix == QString("Snail")) {
   connectWidget2->objet->two_system = -1;
  xtool->setText("u*cos(v)*sin(u)");
  ytool->setText("u*cos(u)*cos(v)");
  ztool->setText("-u*sin(v)") ;
  umin_tools->setText("0") ; 
  umax_tools->setText("2") ; 
  vmin_tools->setText("-pi/2") ; 
  vmax_tools->setText("pi/2") ;

    } 


                        if(choix == QString("Limpet_Torus")) {
   connectWidget2->objet->two_system = -1;
  xtool->setText("cos(u) / (sqrt(2) + sin(v))");
  ytool->setText("sin(u) / (sqrt(2) + sin(v))");
  ztool->setText("1 / (sqrt(2) + cos(v))") ;
  umin_tools->setText("-pi") ; 
  umax_tools->setText("pi") ; 
  vmin_tools->setText("-pi") ; 
  vmax_tools->setText("pi") ; 
 
    } 


      if(choix == QString("Twisted_Triaxial")) {
   connectWidget2->objet->two_system = -1;
  xtool->setText("(1-sqrt(u*u + v*v) / sqrt(2*pi*pi))*cos(u)*cos(v)+sqrt(u*u + v*v) / sqrt(2*pi*pi)*sin(u)*sin(v)");
  ytool->setText("(1-sqrt(u*u + v*v) / sqrt(2*pi*pi))*cos(u+2*pi/3)*cos(v+2*pi/3)+sqrt(u*u + v*v) / sqrt(2*pi*pi)*sin(u+2*pi/3)*sin(v+2*pi/3)") ;
  ztool->setText(" (1-sqrt(u*u + v*v) / sqrt(2*pi*pi))*cos(u+4*pi/3)*cos(v+4*pi/3)+sqrt(u*u + v*v) / sqrt(2*pi*pi)*sin(u+4*pi/3)*sin(v+4*pi/3)") ;
  umin_tools->setText("-pi") ; 
  umax_tools->setText("pi") ; 
  vmin_tools->setText("-pi") ; 
  vmax_tools->setText("pi") ; 
 
    } 

                        if(choix == QString("Apple")) {
   connectWidget2->objet->two_system = -1;
  xtool->setText("cos(u) *(4 + 3.8* cos(v))");
  ytool->setText("sin(u) *(4 + 3.8* cos(v))");
  ztool->setText("(cos(v) + sin(v) - 1)* (1 + sin(v)) *log(1 - pi *v / 10) + 7.5 *sin(v)") ;
  umin_tools->setText("0") ; 
  umax_tools->setText("2*pi") ; 
  vmin_tools->setText("-pi") ; 
  vmax_tools->setText("pi") ; 
  
    } 

                        if(choix == QString("Boy")) {
   connectWidget2->objet->two_system = -1;
  xtool->setText("2/3* (cos(u)* cos(2*v) + sqrt(2)* sin(u)* cos(v))* cos(u) / (sqrt(2) - sin(2*u)* sin(3*v))");
  ytool->setText("2/3* (cos(u)* sin(2*v) - sqrt(2)* sin(u)* sin(v))* cos(u) / (sqrt(2) - sin(2*u)* sin(3*v))");
  ztool->setText("sqrt(2)* cos(u)* cos(u) / (sqrt(2) - sin(2*u)* sin(3*v))") ;
  umin_tools->setText("0") ; 
  umax_tools->setText("pi") ; 
  vmin_tools->setText("0") ; 
  vmax_tools->setText("pi") ; 
 
    } 



                        if(choix == QString("Maeder's_Owl")) {
   connectWidget2->objet->two_system = -1;
  xtool->setText("v *cos(u) - 0.5* v^2 * cos(2* u)");
  ytool->setText("-v *sin(u) - 0.5* v^2 * sin(2* u)");
  ztool->setText("4 *v^1.5 * cos(3 *u / 2) / 3") ;
  umin_tools->setText("0") ; 
  umax_tools->setText("4*pi") ; 
  vmin_tools->setText("0") ; 
  vmax_tools->setText("1") ; 
   
    }     
    

                        if(choix == QString("Cone")) {
   connectWidget2->objet->two_system = -1;
  xtool->setText("u*cos(v)");
  ytool->setText("u*sin(v)");
  ztool->setText("u") ;
  umin_tools->setText("-1") ; 
  umax_tools->setText("1") ; 
  vmin_tools->setText("0") ; 
  vmax_tools->setText("2*pi") ; 

    } 

 
                        if(choix == QString("Eight")) {
   connectWidget2->objet->two_system = -1;
  xtool->setText("(2 + 0.2*sin(2*pi*u))*sin(pi*v)");
  ytool->setText("0.2*cos(2*pi*u) *3*cos(2*pi*v)");
  ztool->setText("(2 + 0.2*sin(2*pi*u))*cos(pi*v)") ;
  umin_tools->setText("0") ; 
  umax_tools->setText("pi/2") ; 
  vmin_tools->setText("0") ; 
  vmax_tools->setText("3*pi/4") ; 
    }



                        if(choix == QString("Drop")) {
   connectWidget2->objet->two_system = -1;
  xtool->setText("u*cos(v)");
  ytool->setText("u*sin(v)");
  ztool->setText("exp(-u*u)*(sin(2*pi*u) - u*cos(3*v))") ;
  umin_tools->setText("0") ; 
  umax_tools->setText("2") ; 
  vmin_tools->setText("0") ; 
  vmax_tools->setText("2*pi") ; 

    }



                        if(choix == QString("Plan")) {
   connectWidget2->objet->two_system = -1;
  xtool->setText("u");
  ytool->setText("0");
  ztool->setText("v") ;
  umin_tools->setText("-1") ; 
  umax_tools->setText("1") ; 
  vmin_tools->setText("-1") ; 
  vmax_tools->setText("1") ; 
    }

                        if(choix == QString("Ellipsoide")) {
   connectWidget2->objet->two_system = -1;
  xtool->setText("cos(u)*cos(v)");
  ytool->setText("sin(u)*cos(v)");
  ztool->setText("sin(v)") ;
  umin_tools->setText("0") ; 
  umax_tools->setText("6.2831") ; 
  vmin_tools->setText("-1.57") ; 
  vmax_tools->setText("1.5708") ; 
  
    }
 
                        if(choix == QString("EightSurface")) {
   connectWidget2->objet->two_system = -1;
  xtool->setText("cos(u)*sin(2*v)");
  ytool->setText("sin(u)*sin(2*v)");
  ztool->setText("sin(v)") ;
  umin_tools->setText("0") ; 
  umax_tools->setText("2*pi") ; 
  vmin_tools->setText("-pi/2") ; 
  vmax_tools->setText("pi/2") ; 
  
    }




 
                        if(choix == QString("Dini")) {
   connectWidget2->objet->two_system = -1;
  xtool->setText("cos(u)*sin(v)");
  ytool->setText("sin(u)*sin(v)");
  ztool->setText("(cos(v)+log(tan(v/2))) + 0.2*u") ;
  umin_tools->setText("0") ; 
  umax_tools->setText("12.4") ; 
  vmin_tools->setText("0.1") ; 
  vmax_tools->setText("2") ; 
  
    }    
  
    
                        if(choix == QString("Flower")) {
   connectWidget2->objet->two_system = -1;
  xtool->setText("v *cos(u) -0.5*v^2*cos(2*u)");
  ytool->setText("-v*sin(u) -0.5*v^2*sin(2*u)");
  ztool->setText("4* v^1.5 *cos(3* u / 2) / 3") ;
  umin_tools->setText("0") ; 
  umax_tools->setText("4*pi") ; 
  vmin_tools->setText("0") ; 
  vmax_tools->setText("1") ; 
  

    } 
  
  
  
    if(choix == QString("Cosinus")) {
   connectWidget2->objet->two_system = -1;
  xtool->setText("u");
  ytool->setText("v");
  ztool->setText("sin(pi*((u)^2+(v)^2))/2") ; 
  umin_tools->setText("-1") ; 
  umax_tools->setText("1") ; 
  vmin_tools->setText("-1") ; 
  vmax_tools->setText("1") ;
  
    }
    
      if(choix == QString("Shell")) {
   connectWidget2->objet->two_system = -1;
  xtool->setText("1.2^v*(sin(u)^2 *sin(v))");
  ytool->setText("1.2^v*(sin(u)^2 *cos(v))");
  ztool->setText("1.2^v*(sin(u)*cos(u))") ;
  umin_tools->setText("0") ; 
  umax_tools->setText("pi") ; 
  vmin_tools->setText("-pi/4") ; 
  vmax_tools->setText("5*pi/2") ; 

    }

       
           if(choix == QString("Sphere")) {
   connectWidget2->objet->two_system = -1;
  xtool->setText("cos(u)*cos(v)");
  ytool->setText("cos(u)*sin(v)");
  ztool->setText("sin(u)") ;
  umin_tools->setText("-pi/2") ; 
  umax_tools->setText("pi/2") ; 
  vmin_tools->setText("0") ; 
  vmax_tools->setText("2*pi") ; 
  
    }    
      
              if(choix == QString("Steiner")) {
   connectWidget2->objet->two_system = -1;
  xtool->setText("(sin(2 * u) * cos(v) * cos(v))");
  ytool->setText("(sin(u) * sin(2 * v))");
  ztool->setText("(cos(u) * sin(2 * v))") ;
  umin_tools->setText("-pi/2") ; 
  umax_tools->setText("pi/2") ; 
  vmin_tools->setText("-pi/2") ; 
  vmax_tools->setText("pi/2") ; 

    }     
              if(choix == QString("Cross_cap")) {
   connectWidget2->objet->two_system = -1;
  xtool->setText("(sin(u) * sin(2 * v) / 2)");
  ytool->setText("(sin(2 * u) * cos(v) * cos(v))");
  ztool->setText("(cos(2 * u) * cos(v) * cos(v))") ;
  umin_tools->setText("-pi/2") ; 
  umax_tools->setText("pi/2") ; 
  vmin_tools->setText("-pi/2") ; 
  vmax_tools->setText("pi/2") ; 

    } 
               if(choix == QString("Boys")) {
   connectWidget2->objet->two_system = -1;
  xtool->setText("(2/3)*(cos(u)*cos(2*v)+sqrt(2)*sin(u)*cos(v))*cos(u) /(sqrt(2) - sin(2*u)*sin(3*v))");
  ytool->setText("(2/3)*(cos(u)*sin(2*v)-sqrt(2)*sin(u)*sin(v))*cos(u) /(sqrt(2)-sin(2*u)*sin(3*v))");
  ztool->setText("sqrt(2)*cos(u)^2 / (sqrt(2) - sin(2*u)*sin(2*v))") ;
  umin_tools->setText("-pi/2") ; 
  umax_tools->setText("pi/2") ; 
  vmin_tools->setText("-pi/2") ; 
  vmax_tools->setText("pi/2") ; 
  
    }     
      
      if(choix == QString("Torus")) {
   connectWidget2->objet->two_system = -1;
  xtool->setText("(1+ 0.5*cos(u))*cos(v)");
  ytool->setText("(1+ 0.5*cos(u))*sin(v)");
  ztool->setText("0.5*sin(u)") ;
  umin_tools->setText("0") ; 
  umax_tools->setText("2*pi") ; 
  vmin_tools->setText("0") ; 
  vmax_tools->setText("2*pi") ; 

    }

      if(choix == QString("Klein")) {
   connectWidget2->objet->two_system = -1;   
  xtool->setText("(3*(1+sin(v)) + 2*(1-cos(v)/2)*cos(u))*cos(v)") ;      
  ytool->setText("(4+2*(1-cos(v)/2)*cos(u))*sin(v)");
  ztool->setText("-2*(1-cos(v)/2) * sin(u)"); 
  umin_tools->setText("0") ; 
  umax_tools->setText("2*pi") ; 
  vmin_tools->setText("0") ; 
  vmax_tools->setText("2*pi") ;
  
    }

       if(choix == QString("Moebius")) {
   connectWidget2->objet->two_system = -1;
  xtool->setText("cos(v)+u*cos(v/2)*cos(v)");
  ytool->setText("sin(v)+u*cos(v/2)*sin(v)");
  ztool->setText("u*sin(v/2)") ;
  umin_tools->setText("-0.4") ; 
  umax_tools->setText("0.4") ; 
  vmin_tools->setText("0") ; 
  vmax_tools->setText("2*pi") ; 
  
    }

          if(choix == QString("Riemann")) {
   connectWidget2->objet->two_system = -1;
  xtool->setText("u*v");
  ytool->setText("v^2 - u^2");
  ztool->setText("30*u") ;
  umin_tools->setText("-6") ; 
  umax_tools->setText("6") ; 
  vmin_tools->setText("-25") ; 
  vmax_tools->setText("25") ; 

    }
   

          if(choix == QString("Klein_2")) {
   connectWidget2->objet->two_system = -1;
  xtool->setText("(2 + cos(v/2)* sin(u) - sin(v/2)* sin(2 *u))* cos(v)");
  ytool->setText("(2 + cos(v/2)* sin(u) - sin(v/2)* sin(2 *u))* sin(v)");
  ztool->setText("sin(v/2)* sin(u) + cos(v/2) *sin(2* u)") ;
  umin_tools->setText("0") ; 
  umax_tools->setText("2*pi") ; 
  vmin_tools->setText("0") ; 
  vmax_tools->setText("2*pi") ;

    }

           if(choix == QString("Henneberg")) {
   connectWidget2->objet->two_system = -1;
  xtool->setText("2*sinh(u)*cos(v) -(2/3)*sinh(3*u)*cos(3*v)");
  ytool->setText("2*sinh(u)*sin(v) +(2/3)*sinh(3*u)*sin(3*v)");
  ztool->setText("2*cosh(2*u)*cos(2*v)") ;
  umin_tools->setText("-1") ; 
  umax_tools->setText("1") ; 
  vmin_tools->setText("-pi/2") ; 
  vmax_tools->setText("pi/2") ;
    }

          if(choix == QString("Enneper")) {
   connectWidget2->objet->two_system = -1;
  xtool->setText("u -u^3/3  + u*v^2");
  ytool->setText("v -v^3/3  + v*u^2");
  ztool->setText("u^2 - v^2") ;
  umin_tools->setText("-2") ; 
  umax_tools->setText("2") ; 
  vmin_tools->setText("-2") ; 
  vmax_tools->setText("2") ; 
    }  

            if(choix == QString("Helix")) {
   connectWidget2->objet->two_system = -1;
  xtool->setText("(1-0.1*cos(v))*cos(u)");
  ytool->setText("(1-0.1*cos(v))*sin(u)");
  ztool->setText("0.1*(sin(v) + u/1.7 -10)") ;
  umin_tools->setText("0") ; 
  umax_tools->setText("4*pi") ; 
  vmin_tools->setText("0") ; 
  vmax_tools->setText("2*pi") ; 
    }  

           if(choix == QString("Hexaedron")) {
   connectWidget2->objet->two_system = -1;
  xtool->setText("cos(v)^3*cos(u)^3");
  ytool->setText("sin(v)^3*cos(u)^3");
  ztool->setText("sin(u)^3") ;
  umin_tools->setText("-1.3") ; 
  umax_tools->setText("1.3") ; 
  vmin_tools->setText("0") ; 
  vmax_tools->setText("2*pi") ; 
    }       

           if(choix == QString("Sphere_1")) {
   connectWidget2->objet->two_system = -1;
  xtool->setText("cos(u)*cos(v)");
  ytool->setText("cos(u)*sin(v)");
  ztool->setText("sin(u)") ;
  umin_tools->setText("-pi/2") ; 
  umax_tools->setText("pi/2") ; 
  vmin_tools->setText("0") ; 
  vmax_tools->setText("2*pi") ; 
    }

             if(choix == QString("Sphere_2")) {
   connectWidget2->objet->two_system = -1;
  xtool->setText("cos(u)*cos(v)");
  ytool->setText("cos(u)*sin(v)");
  ztool->setText("sin(u)*sin(v)") ;
  umin_tools->setText("-pi/2") ; 
  umax_tools->setText("pi/2") ; 
  vmin_tools->setText("0") ; 
  vmax_tools->setText("2*pi") ; 
    }  

              if(choix == QString("Sphere_3")) {
   connectWidget2->objet->two_system = -1;
  xtool->setText("cos(u)*cos(v)");
  ytool->setText("cos(u)*sin(v)");
  ztool->setText("sin(u)*sin(v)*cos(v)") ;
  umin_tools->setText("-pi/2") ;
  umax_tools->setText("pi/2") ;
  vmin_tools->setText("0") ;
  vmax_tools->setText("2*pi") ;
    }    
    
    
               if(choix == QString("Sphere_4")) {
   connectWidget2->objet->two_system = -1;
  xtool->setText("cos(u)*cos(v)");
  ytool->setText("cos(u)*sin(v)*sin(v)");
  ztool->setText("sin(u)*sin(v)") ;
  umin_tools->setText("-pi/2") ; 
  umax_tools->setText("0") ; 
  vmin_tools->setText("0") ; 
  vmax_tools->setText("2*pi") ; 

    }

                 if(choix == QString("Sphere_5")) {
   connectWidget2->objet->two_system = -1;
  xtool->setText("cos(u)*cos(v)*sin(v)");
  ytool->setText("cos(u)*sin(v)*sin(v)");
  ztool->setText("sin(u)*sin(v)") ;
  umin_tools->setText("-pi/2") ; 
  umax_tools->setText("0") ; 
  vmin_tools->setText("0") ; 
  vmax_tools->setText("2*pi") ; 

    }

                 if(choix == QString("Sphere_6")) {
   connectWidget2->objet->two_system = -1;
  xtool->setText("cos(u)*cos(v)*sin(u)");
  ytool->setText("sin(u)");
  ztool->setText("sin(u)*sin(v)*sin(u)") ;
  umin_tools->setText("-pi/2") ; 
  umax_tools->setText("0") ; 
  vmin_tools->setText("0") ; 
  vmax_tools->setText("2*pi") ; 

    }

                 if(choix == QString("Sphere_7")) {
   connectWidget2->objet->two_system = -1;
  xtool->setText("cos(u)*cos(v)*sin(u)");
  ytool->setText("sin(u)*sin(v)*cos(u)");
  ztool->setText("sin(u)*sin(v)*sin(u)") ;
  umin_tools->setText("-pi/2") ; 
  umax_tools->setText("0") ; 
  vmin_tools->setText("0") ; 
  vmax_tools->setText("2*pi") ; 

    }

                 if(choix == QString("Sphere_8")) {
   connectWidget2->objet->two_system = -1;
  xtool->setText("cos(u)*cos(v)*sin(u)");
  ytool->setText("cos(u)*sin(v)*cos(u)");
  ztool->setText("sin(u)*sin(v)*sin(u)") ;
  umin_tools->setText("-pi/2") ; 
  umax_tools->setText("0") ; 
  vmin_tools->setText("0") ; 
  vmax_tools->setText("2*pi") ; 

    }
                 if(choix == QString("Sphere_9")) {
   connectWidget2->objet->two_system = -1;
  xtool->setText("cos(u)*cos(v)*sin(u)");
  ytool->setText("cos(u)*sin(v)*cos(u)*sin(v)");
  ztool->setText("sin(u)*sin(v)*sin(u)*sin(v)");
  umin_tools->setText("-pi/2") ;
  umax_tools->setText("0") ;
  vmin_tools->setText("0") ;
  vmax_tools->setText("pi") ;
    }

                 if(choix == QString("Sphere_10")) {
   connectWidget2->objet->two_system = -1;
  xtool->setText("cos(u)*cos(v)*sin(u)*sin(v)*sin(v)*sin(v)");
  ytool->setText("cos(u)*sin(v)*cos(u)*sin(v)");
  ztool->setText("sin(u)*sin(v)*sin(u)*sin(v)*cos(u)") ;
  umin_tools->setText("-pi/2") ;
  umax_tools->setText("0") ;
  vmin_tools->setText("0") ;
  vmax_tools->setText("pi") ;
    }

             if(choix == QString("Catalan")) {
   connectWidget2->objet->two_system = -1;
  xtool->setText("u-sin(u)*cosh(v)");
  ytool->setText("1-cos(u)*cosh(v)");
  ztool->setText("4*sin(1/2*u)*sinh(v/2)") ;
  umin_tools->setText("-pi") ;
  umax_tools->setText("3*pi") ;
  vmin_tools->setText("-2") ;
  vmax_tools->setText("2") ;
    }

             if(choix == QString("Toupie")) {
   connectWidget2->objet->two_system = -1;
  xtool->setText("(abs(u)-1)^2 * cos(v)");
  ytool->setText("(abs(u)-1)^2 * sin(v)");
  ztool->setText("u") ;
  umin_tools->setText("-1") ;
  umax_tools->setText("1") ;
  vmin_tools->setText("0") ;
  vmax_tools->setText("2*pi") ;
    }

              if(choix == QString("Bonbon")) {
   connectWidget2->objet->two_system = -1;
  xtool->setText("u");
  ytool->setText("cos (u)*cos (v)");
  ztool->setText("cos (u)*sin (v)") ;
  umin_tools->setText("0") ;
  umax_tools->setText("2*pi") ;
  vmin_tools->setText("0") ;
  vmax_tools->setText("2*pi") ;
    }

              if(choix == QString("Curve")) {
   connectWidget2->objet->two_system = -1;
  xtool->setText("cos(2*u)");
  ytool->setText("sin(3*u)");
  ztool->setText("cos(u)") ;
  umin_tools->setText("0") ;
  umax_tools->setText("2*pi") ;
  vmin_tools->setText("0") ;
  vmax_tools->setText("0") ;
    }

                 if(choix == QString("Trumpet")) {
   connectWidget2->objet->two_system = -1;
  xtool->setText("cos(u)*sin(v)");
  ytool->setText("sin(u)*sin(v)");
  ztool->setText("(cos(v)+log(tan(1/2*v)))") ;
  umin_tools->setText("0") ;
  umax_tools->setText("2*pi") ;
  vmin_tools->setText("0.03") ;
  vmax_tools->setText("2") ;
    }

                 if(choix == QString("Helice_Curve")) {
   connectWidget2->objet->two_system = -1;
  xtool->setText("sin(u)");
  ytool->setText("cos(u)");
  ztool->setText("(u^2)/100") ;
  umin_tools->setText("0") ;
  umax_tools->setText("6*pi") ;
  vmin_tools->setText("0") ;
  vmax_tools->setText("0") ;
    }

                 if(choix == QString("Cresent")) {
   connectWidget2->objet->two_system = -1;
  xtool->setText("(2 + sin(2* pi* u) *sin(2 *pi* v)) *sin(3* pi *v)");
  ytool->setText("(2 + sin(2* pi *u) *sin(2 *pi *v)) *cos(3* pi *v)");
  ztool->setText("cos(2* pi *u) *sin(2* pi* v) + 4 *v - 2") ;
  umin_tools->setText("0") ;
  umax_tools->setText("1") ;
  vmin_tools->setText("0") ;
  vmax_tools->setText("1") ;
    }

                  if(choix == QString("Shoe")) {
   connectWidget2->objet->two_system = -1;
  xtool->setText("u");
  ytool->setText("v");
  ztool->setText("1/3*u^3  - 1/2*v^2") ;
  umin_tools->setText("-2") ;
  umax_tools->setText("2") ;
  vmin_tools->setText("-2") ;
  vmax_tools->setText("2") ;
    }
                 if(choix == QString("Snake")) {
   connectWidget2->objet->two_system = -1;
  xtool->setText("1.2*(1 -v/(2*pi))*cos(3*v)*(1 + cos(u)) + 3*cos(3*v)");
  ytool->setText("1.2*(1 -v/(2*pi))*sin(3*v)*(1 + cos(u)) + 3*sin(3*v)");
  ztool->setText("9*v/(2*pi) + 1.2*(1 - v/(2*pi))*sin(u)") ;
  umin_tools->setText("0") ;
  umax_tools->setText("2*pi") ;
  vmin_tools->setText("0") ;
  vmax_tools->setText("2*pi") ;
    }

                  if(choix == QString("Roman")) {
   connectWidget2->objet->two_system = -1;
  xtool->setText("1/2*sin(2*u)*sin(v)^2");
  ytool->setText("1/2*sin(u)*cos(2*v)");
  ztool->setText("1/2*cos(u)*sin(2*v)") ;
  umin_tools->setText("0") ;
  umax_tools->setText("pi") ;
  vmin_tools->setText("-pi/2") ;
  vmax_tools->setText("pi/2") ;
    }

                    if(choix == QString("Hyperhelicoidal")) {
   connectWidget2->objet->two_system = -1;
  xtool->setText("(sinh(v)*cos(3*u))/(1+cosh(u)*cosh(v))");
  ytool->setText("(sinh(v)*sin(3*u))/(1+cosh(u)*cosh(v))");
  ztool->setText("(cosh(v)*sinh(u))/(1+cosh(u)*cosh(v))") ;
  umin_tools->setText("-pi") ;
  umax_tools->setText("pi") ;
  vmin_tools->setText("-pi") ;
  vmax_tools->setText("pi") ;
    }

                    if(choix == QString("Horn")) {
   connectWidget2->objet->two_system = -1;
  xtool->setText("(2 + u*cos(v))*sin(2*pi*u)");
  ytool->setText("(2 + u*cos(v))*cos(2*pi*u) + 2*u");
  ztool->setText("u *sin(v)") ;
  umin_tools->setText("0") ;
  umax_tools->setText("1") ;
  vmin_tools->setText("0") ;
  vmax_tools->setText("2*pi") ;
    }

                   if(choix == QString("Helicoidal")) {
   connectWidget2->objet->two_system = -1;
  xtool->setText("sinh(v)*sin(u)");
  ytool->setText("-sinh(v)*cos(u)");
  ztool->setText("3*u") ;
  umin_tools->setText("-pi") ;
  umax_tools->setText("pi") ;
  vmin_tools->setText("-pi") ;
  vmax_tools->setText("pi") ;
    }

                    if(choix == QString("Catenoid")) {
   connectWidget2->objet->two_system = -1;
  xtool->setText("2*cosh(v/2)*cos(u)");
  ytool->setText("2*cosh(v/2)*sin(u)");
  ztool->setText("v") ;
  umin_tools->setText("-pi") ;
  umax_tools->setText("pi") ;
  vmin_tools->setText("-pi") ;
  vmax_tools->setText("pi") ;
    }

                   if(choix == QString("Kuen")) {
   connectWidget2->objet->two_system = -1;
  xtool->setText("(2*(cos(u) + u*sin(u))*sin(v))/(1+ u^2*sin(v)^2)");
  ytool->setText("(2*(sin(u) - u*cos(u))*sin(v))/(1+ u^2*sin(v)^2)");
  ztool->setText("log(tan(1/2 *v)) + (2*cos(v))/(1+ u^2*sin(v)^2)") ;
  umin_tools->setText("0") ;
  umax_tools->setText("2*pi") ;
  vmin_tools->setText("0.01") ;
  vmax_tools->setText("pi-0.01") ;
    }

                    if(choix == QString("Hellipticparaboloid")) {
   connectWidget2->objet->two_system = -1;
  xtool->setText("v*2*cos(u)");
  ytool->setText("v*sin(u)");
  ztool->setText("v^2") ;
  umin_tools->setText("0") ;
  umax_tools->setText("2*pi") ;
  vmin_tools->setText("0") ;
  vmax_tools->setText("2") ;
    }


                    if(choix == QString("Enneper_2")) {
   connectWidget2->objet->two_system = -1;
  xtool->setText("u*cos(v)-u^3/3*cos(3*v)");
  ytool->setText("-u*sin(v)-u^(3)/3*sin(3*v)");
  ztool->setText("u^2*cos(2*v)") ;
  umin_tools->setText("0") ;
  umax_tools->setText("1.2") ;
  vmin_tools->setText("-pi") ;
  vmax_tools->setText("pi") ;
    }

                    if(choix == QString("Stereosphere")) {
   connectWidget2->objet->two_system = -1;
  xtool->setText("2.*u/(u*u+v*v+1.)");
  ytool->setText("2.*v/(u*u+v*v+1.)");
  ztool->setText("(u*u+v*v-1.)/(u*u+v*v+1.)") ;
  umin_tools->setText("-2") ;
  umax_tools->setText("2") ;
  vmin_tools->setText("-2") ;
  vmax_tools->setText("2") ;
    }

                    if(choix == QString("Cliffordtorus")) {
   connectWidget2->objet->two_system = -1;
  xtool->setText("cos(u+v)/(sqrt(2.)+cos(v-u))");
  ytool->setText("sin(u+v)/(sqrt(2.)+cos(v-u))");
  ztool->setText("sin(v-u)/(sqrt(2.)+cos(v-u))") ;
  umin_tools->setText("0") ;
  umax_tools->setText("pi") ;
  vmin_tools->setText("0") ;
  vmax_tools->setText("2*pi") ;
  }

                    if(choix == QString("Fresnel_1")) {
   connectWidget2->objet->two_system = -1;
  xtool->setText("cos(u)*cos(v)/(-2.*sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))*cos((acos(-(-0.941/6.+0.374*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4)-1.309/6.*((cos(u)^6+sin(u)^6)*cos(v)^6+sin(v)^6)-1.221*cos(u)^2*cos(v)^4*sin(u)^2*sin(v)^2)/sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))^3)+pi)/3.)+0.8)");
  ytool->setText("sin(u)*cos(v)/(-2.*sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))*cos((acos(-(-0.941/6.+0.374*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4)-1.309/6.*((cos(u)^6+sin(u)^6)*cos(v)^6+sin(v)^6)-1.221*cos(u)^2*cos(v)^4*sin(u)^2*sin(v)^2)/sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))^3)+pi)/3.)+0.8)");
  ztool->setText("sin(v)/(-2.*sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))*cos((acos(-(-0.941/6.+0.374*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4)-1.309/6.*((cos(u)^6+sin(u)^6)*cos(v)^6+sin(v)^6)-1.221*cos(u)^2*cos(v)^4*sin(u)^2*sin(v)^2)/sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))^3)+pi)/3.)+0.8)") ;
  umin_tools->setText("0") ;
  umax_tools->setText("2*pi") ;
  vmin_tools->setText("-pi/2") ;
  vmax_tools->setText("pi/2") ;
    }

                    if(choix == QString("Fresnel_2")) {
   connectWidget2->objet->two_system = -1;
  xtool->setText("cos(u)*cos(v)/(-2.*sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))*cos((acos(-(-0.941/6.+0.374*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4)-1.309/6.*((cos(u)^6+sin(u)^6)*cos(v)^6+sin(v)^6)-1.221*cos(u)^2*cos(v)^4*sin(u)^2*sin(v)^2)/sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))^3)-pi)/3.)+0.8)");
  ytool->setText("sin(u)*cos(v)/(-2.*sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))*cos((acos(-(-0.941/6.+0.374*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4)-1.309/6.*((cos(u)^6+sin(u)^6)*cos(v)^6+sin(v)^6)-1.221*cos(u)^2*cos(v)^4*sin(u)^2*sin(v)^2)/sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))^3)-pi)/3.)+0.8)");
  ztool->setText("sin(v)/(-2.*sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))*cos((acos(-(-0.941/6.+0.374*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4)-1.309/6.*((cos(u)^6+sin(u)^6)*cos(v)^6+sin(v)^6)-1.221*cos(u)^2*cos(v)^4*sin(u)^2*sin(v)^2)/sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))^3)-pi)/3.)+0.8)") ;
  umin_tools->setText("0") ;
  umax_tools->setText("2*pi") ;
  vmin_tools->setText("-pi/2") ;
  vmax_tools->setText("pi/2") ;
    }

/*
// copy the first system
  connectWidget2->objet->expression_X = xtool->text();
  connectWidget2->objet->expression_Y = ytool->text();
  connectWidget2->objet->expression_Z = ztool->text();
  connectWidget2->objet->inf_u = umin_tools->text();
  connectWidget2->objet->sup_u = umax_tools->text();
  connectWidget2->objet->inf_v = vmin_tools->text();
  connectWidget2->objet->sup_v = vmax_tools->text();
*/
// process the new surface
//  connectWidget2->valueChanged();
  perform_tools() ;
}

//====================================
void k3dsurface::perform_fivedim()
{
    FunctionParser fp,f1;
    QMessageBox message ;

    fp.AddConstant("pi", 3.14159265);
    int ret;

        if(connectWidget2->objet->DefineNewFct ==1)
    {
    ret = fp.Parse(fctdef->text(), "u,v,t,x,y");
    if(ret >= 0)
    { 
   message.setText(tr(QString("k(u,v,t,x,y)--> At col:")+
         QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();
        return ;
    }

     f1.Parse(fctdef->text(), "u,v,t");
     fp.AddFunction("k", f1);
    }

    ret = fp.Parse(xcft_5->text(), "u,v,t");
    if(ret >= 0)
    {
    message.setText(tr(QString("X=g(u,v)--> At col:")+
    QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize();
    message.exec();
        return ;
    }

    ret = fp.Parse(ycft_5->text(), "u,v,t");
    if(ret >= 0)
    {
    message.setText(tr(QString("Y=g(u,v)--> At col:")+
    QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();
        return ;
    }

     ret = fp.Parse(zcft_5->text(), "u,v,t");
    if(ret >= 0)
    {
    message.setText(tr(QString("Z=h(u,v)--> At col:")+
    QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();
        return ;
    }

     ret = fp.Parse(wcft_5->text(), "u,v,t");
    if(ret >= 0)
    {
    message.setText(tr(QString("W=h(u,v)--> At col:")+
    QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();
        return ;
    }

      ret = fp.Parse(tcft_5->text(), "u,v,t");
    if(ret >= 0)
    {
    message.setText(tr(QString("T=h(u,v)--> At col:")+
    QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();
        return ;
    }


  //connectWidget2->objet->fivedimshapes = 1;
  connectWidget2->objet->expression_X = ycft_5->text(); ///ToReverse Axes
  connectWidget2->objet->expression_Y = xcft_5->text(); ///ToReverse Axes
  connectWidget2->objet->expression_Z = zcft_5->text();
  connectWidget2->objet->expression_W = wcft_5->text();
  connectWidget2->objet->expression_T = tcft_5->text();

  connectWidget2->objet->inf_u = umin_5->text();
  connectWidget2->objet->sup_u = umax_5->text();
  connectWidget2->objet->inf_v = vmin_5->text();
  connectWidget2->objet->sup_v = vmax_5->text();

  if(sixdimshapes == 1 ) connectWidget2->objet->expression_S = scft_5->text();

   /// Set the right Window for drawing :
 tabsurf->setCurrentPage(0);
 if(paramwidgetstack == 1) glboxclicked();
  //Process the new surface :
ParametricSurfaceProcess();
   }

//====================================
void k3dsurface::FivedimShapes(){

}
//====================================
void k3dsurface::Butto_OK_Clicked(){
Width             = "+W"+WidthEdit_2->text();
Height            = "+H"+HeightEdit_2 ->text();
Start_RowEdit     = "+SR"+Start_RowEdit_2->text();
End_RowEdit       = "+ER"+End_RowEdit_2->text();
Start_ColumnEdit  = "+SC"+Start_ColumnEdit_2->text();
End_ColumnEdit    = "+EC"+End_ColumnEdit_2->text();

}
//====================================

void k3dsurface::InputFile_toggled(){

    inputfile *= -1;
}
//====================================

void k3dsurface::OutputFile_toggled(){

    outputfile *= -1;
}

//====================================
void k3dsurface::verbose_ok()
{
verbose  *= -1;
}
//====================================
void k3dsurface::ImageSizeChanged()
{ ImageSize_Field_changed =1;
}

//====================================
void k3dsurface::runpovray()
{   QString execute_commande;
    int result;

    if(ImageSize_Field_changed == 1)  {
    Butto_OK_Clicked() ; ImageSize_Field_changed =-1;}

    if(verbose ==1) xterm ="xterm -e ";
    else  xterm = "";

    if(testabort == 1) { Test_Abort_CountEdit ="+X"+Test_Abort_CountEdit_2->text();} 
    else Test_Abort_CountEdit = "" ;

    if(pausewhendone ==1) { Pause_When_Done = "+P"; }
    else  Pause_When_Done = "";

    if( continuecheckbox ==1) {  Continue= "+C"; }
    else  Continue = "";

    if(outputfile==1) Output_File_NameEdit="+O"+Output_File_NameEdit_2->text()+FileExtension+" ";
   // else { Output_File_NameEdit="";
   //        FileExtension = "";}

    if(inputfile==1) Input_File_NameEdit="+I"+Input_File_NameEdit_2->text();
    //else Input_File_NameEdit="";

    if(outputbuffer==1) OutPutBuffer="+B["+Buffer_SizeEdit_2->text()+"]";
    else OutPutBuffer="";

    execute_commande = xterm+" povray "+Input_File_NameEdit+" "+Output_File_NameEdit+" "\
     +Width+" "+Height+" \
     "+Start_RowEdit+" "+End_RowEdit+" \
     "+Start_ColumnEdit+" "+End_ColumnEdit+" \
     "+Pause_When_Done+" "+Test_Abort_CountEdit+"\
     "+OutPutBuffer+" "+IncludeHeaderFile+" "+Continue+"  &";


    result = system(execute_commande);
   if(result != 1) std::cout << "Ok \n";
    //std::cout <<execute_commande <<"\n";}
}
//====================================
void k3dsurface::whatsButton_clicked()
{
    QWhatsThis::enterWhatsThisMode();
}
//====================================
void k3dsurface::povPreference()
{


}
//====================================

void k3dsurface::IconBox()
{

    QMessageBox message ;
    //message.setIconPixmap(QPixmap("agoujime.jpg"));
    message.setText(tr("                              K3DSurf 0.6 \
         \nOpenGL integrated viewer \
         \n\
         \n Java version available at :\
         \n http://www.wintonet.com/java (3/3)."));
    message.adjustSize () ;
    message.exec();

}

//====================================
void k3dsurface::loadMesh()
{
        editeur *ed = new editeur();
 ed->load("Mesh.inc");
        ed->show();
}
//====================================
void k3dsurface::loadVrml()
{

    int i,cl, nb1,nb2,nb3,nb4;
    Model3D  * lien_objet;
    Iso3D  *iso_objet;
    int nb_ligne, nb_colone, coupure_ligne, coupure_colone,
        nbisopt, nbisotriangle, index;
    QString text1;


if(tabsurf->currentPageIndex() == 1)  {
     iso_objet = isoWidget->IsoObjet;
     nbisopt       = iso_objet->NbPointIsoMap;
     nbisotriangle = iso_objet->NbTriangleIsoSurface;

 text1 = "#VRML V2.0 utf8\n\
\n\
DEF Home Viewpoint {\n\
    position 0 0 800\n\
    description \"Home\"\n\
}\n\
NavigationInfo {\n\
    type [ \"EXAMINE\", \"ANY\" ]\n\
}\n\
Collision {\n\
    collide FALSE\n\
    children [\n\
 Group {\n\
     children [\n\
  DEF Cameras Switch {\n\
      whichChoice -1\n\
  },\n\
  Shape {\n\
      appearance\n\
   Appearance {\n\
       material\n\
    Material {\n\
    diffuseColor "+QString::number(iso_objet->backsurfr/256.0)+"  "+QString::number(iso_objet->backsurfg/256.0)+" "+QString::number(iso_objet->backsurfb/256.0)+"\n\
    }\n\
   }\n\
      geometry\n\
   IndexedFaceSet {\n\
       coord\n\
    Coordinate {\n\
        point ["  ;








for(i=0;i<nbisopt; i++) {
index = 3*i;
text1   +=  QString::number(iso_objet->IsoPointMapTransfrm[index  ])+" \
          "+QString::number(iso_objet->IsoPointMapTransfrm[index+1])+" \
          "+QString::number(iso_objet->IsoPointMapTransfrm[index+2]);
if( i != (nbisopt -1)) text1   +=  ",\n" ;
else    text1 +="]\n   } \n\
                 solid FALSE \n\
                 coordIndex [ " ;

}

for ( i=0; i < nbisotriangle; ++i) {
index = 3*i;
nb1 = iso_objet->IsoSurfaceTriangleListe[index  ];
nb2 = iso_objet->IsoSurfaceTriangleListe[index+1];
nb3 = iso_objet->IsoSurfaceTriangleListe[index+2];

text1 += QString::number(nb1)+", "+QString::number(nb2)+", "+QString::number(nb3)+", -1";

if( i != (nbisotriangle -1)) text1   +=", \n";
else text1   +="] \n";
}
/// OUUUUUUUUUF the end!
text1 +="   }\n\
  }\n\
     ]\n\
 }\n\
    ]\n\
}\n" ;
}




else {



         nb_ligne = connectWidget2->objet->nb_ligne ,
         nb_colone = connectWidget2->objet->nb_colone,
         coupure_ligne = connectWidget2->objet->coupure_ligne,
         coupure_colone = connectWidget2->objet->coupure_col;
         lien_objet = connectWidget2->objet;

 text1 = "#VRML V2.0 utf8\n\
\n\
DEF Home Viewpoint {\n\
    position 0 0 800\n\
    description \"Home\"\n\
}\n\
NavigationInfo {\n\
    type [ \"EXAMINE\", \"ANY\" ]\n\
}\n\
Collision {\n\
    collide FALSE\n\
    children [\n\
 Group {\n\
     children [\n\
  DEF Cameras Switch {\n\
      whichChoice -1\n\
  },\n\
  Shape {\n\
      appearance\n\
   Appearance {\n\
       material\n\
    Material {\n\
    diffuseColor "+QString::number(lien_objet->backsurfr/256.0)+"  "+QString::number(lien_objet->backsurfg/256.0)+" "+QString::number(lien_objet->backsurfb/256.0)+"\n\
    }\n\
   }\n\
      geometry\n\
   IndexedFaceSet {\n\
       coord\n\
    Coordinate {\n\
        point ["  ;

     for(i=0;i<nb_ligne - coupure_ligne; i++)
          for(cl=0; cl<nb_colone - coupure_colone; cl++) {

 if( i== nb_ligne-1-coupure_ligne && cl == nb_colone-1- coupure_colone) {
      text1 += QString::number(lien_objet->Tre[i*3][cl])+" \
              "+QString::number(lien_objet->Tre[i*3+1][cl])+" \
              "+QString::number(lien_objet->Tre[i*3+2][cl])+" ]\n" ;


   text1 +="   } \n\
       solid FALSE \n\
       coordIndex [ " ;
     }
 else {
      text1 += QString::number(lien_objet->Tre[i*3][cl])+" \
              "+QString::number(lien_objet->Tre[i*3+1][cl])+" \
              "+QString::number(lien_objet->Tre[i*3+2][cl])+", \n" ;
      }
    } // End of For...

// Begining to define triangles
for(i=0;i<nb_ligne -1 -coupure_ligne; i++)
  for(cl=0; cl<nb_colone -1 -coupure_colone; cl++) {
          nb1 = i*(nb_colone- coupure_colone)+ cl;
          nb2 = (i+1)*(nb_colone- coupure_colone)+ cl;
          nb3 = (i+1)*(nb_colone- coupure_colone)+ (cl+1);
          nb4 = i*(nb_colone- coupure_colone)+ (cl+1);
 if( i== nb_ligne-2-coupure_ligne && cl == nb_colone-2- coupure_colone) {
text1 += QString::number(nb1)+", "+QString::number(nb2)+", "+QString::number(nb3)+", -1, ";
text1 += QString::number(nb3)+", "+QString::number(nb4)+", "+QString::number(nb1)+", -1] \n";

     }
else {
text1 += QString::number(nb1)+", "+QString::number(nb2)+", "+QString::number(nb3)+", -1, ";
text1 += QString::number(nb3)+", "+QString::number(nb4)+", "+QString::number(nb1)+", -1, \n";
}
                    }
// Ending to define triangles

text1 +="   }\n\
  }\n\
     ]\n\
 }\n\
    ]\n\
}\n" ;


 }
     saveScript(text1, "test.vrml");

       editeur *ed = new editeur();
       ed->load("test.vrml");
        ed->show();
}
//====================================
//====================================
void k3dsurface::loadObj()
{
    int i,cl, nb1,nb2,nb3,nb4;
    Model3D  * lien_objet;
    Iso3D  *iso_objet;
    int nb_ligne, nb_colone, coupure_ligne, coupure_colone,
        nbisopt, nbisotriangle, index;
    QString text1;
    isoWidget->IsoMorphCompute();
/// First case : Isosurface activated
if(tabsurf->currentPageIndex() == 1)  {
     iso_objet = isoWidget->IsoObjet;
     nbisopt       = iso_objet->NbPointIsoMap;
     nbisotriangle = iso_objet->NbTriangleIsoSurface;
     
     isoWidget->IsoMorphCompute();  // Not always necessery but for we don't generate .obj file all the time...
   
for(i=0;i<nbisopt; i++) {
index = 3*i;
text1   += "v "+QString::number(iso_objet->IsoPointMapTransfrm[index  ])+" \
              "+QString::number(iso_objet->IsoPointMapTransfrm[index+1])+" \
              "+QString::number(iso_objet->IsoPointMapTransfrm[index+2])+"\n" ;
}

for ( i=0; i < nbisotriangle; ++i) {
index = 3*i;
nb1 = iso_objet->IsoSurfaceTriangleListe[index  ]+1;
nb2 = iso_objet->IsoSurfaceTriangleListe[index+1]+1;
nb3 = iso_objet->IsoSurfaceTriangleListe[index+2]+1;

text1 += "f "+QString::number(nb1)+" "+QString::number(nb2)+" "+QString::number(nb3)+"\n";
}
    }
    else {

         nb_ligne = connectWidget2->objet->nb_ligne ,
         nb_colone = connectWidget2->objet->nb_colone,
         coupure_ligne = connectWidget2->objet->coupure_ligne,
         coupure_colone = connectWidget2->objet->coupure_col;
         lien_objet = connectWidget2->objet;

      
        connectWidget2->valueChanged();  // Not always necessery but for we don't generate .obj file all the time...

     for(i=0;i<nb_ligne - coupure_ligne; i++)
          for(cl=0; cl<nb_colone - coupure_colone; cl++)
      text1 += "v "+QString::number(lien_objet->Tre[i*3][cl])+" \
              "+QString::number(lien_objet->Tre[i*3+1][cl])+" \
              "+QString::number(lien_objet->Tre[i*3+2][cl])+"\n" ;


// Begining to define faces:

for(i=0;i<nb_ligne -1 -coupure_ligne; i++)
  for(cl=0; cl<nb_colone -1 -coupure_colone; cl++) {
          nb1 = i*(nb_colone- coupure_colone)+ cl +1;
          nb2 = (i+1)*(nb_colone- coupure_colone)+ cl +1;
          nb3 = (i+1)*(nb_colone- coupure_colone)+ (cl+1) +1;
          nb4 = i*(nb_colone- coupure_colone)+ (cl+1) +1;
if( objfile_triangle == 1){
text1 += "f "+QString::number(nb1)+" "+QString::number(nb2)+" "+QString::number(nb3)+"\n";        text1 += "f "+QString::number(nb3)+" "+QString::number(nb4)+" "+QString::number(nb1)+"\n";
}
else text1 += "f "+QString::number(nb1)+" "+QString::number(nb2)+" "+QString::number(nb3)+" "+QString::number(nb4)+"\n";
                                                    }
}

        saveScript(text1, "test.obj");
        editeur *ed = new editeur();
        ed->load("test.obj");
        ed->show();


}
//====================================
void k3dsurface::activate_tria_nas(){
 tria_nas *= -1 ;
}
//====================================
void k3dsurface::loadNas()
{
    int i,cl;
    Model3D  * lien_objet;
    int nb_ligne = connectWidget2->objet->nb_ligne , 
         nb_colone = connectWidget2->objet->nb_colone,
         coupure_ligne = connectWidget2->objet->coupure_ligne,
         coupure_colone = connectWidget2->objet->coupure_col;
     lien_objet = connectWidget2->objet; 

    QString text1;
    QString val, val1, val2, val3, val4, X, Y, Z;
    int number, n1, n2, n3, n4;


     for(i=0;i<nb_ligne - coupure_ligne; i++)
          for(cl=0; cl<nb_colone - coupure_colone; cl++)  { 
       X = QString::number(lien_objet->Tre[i*3  ][cl], 'f', 8);
       Y = QString::number(lien_objet->Tre[i*3+1][cl], 'f', 8);
       Z = QString::number(lien_objet->Tre[i*3+2][cl], 'f', 8);
/*
 (lien_objet->Tre[i*3  ][cl] > 0) ? 
        X = QString::number(lien_objet->Tre[i*3  ][cl], 'f', 8) :
               X = QString::number(lien_objet->Tre[i*3  ][cl], 'f', 8);

 (lien_objet->Tre[i*3+1][cl] > 0) ? 
        Y = QString::number(lien_objet->Tre[i*3+1][cl], 'f', 8) :
               Y = QString::number(lien_objet->Tre[i*3+1][cl], 'f', 8);

 (lien_objet->Tre[i*3+2][cl] > 0) ? 
        Z = QString::number(lien_objet->Tre[i*3+2][cl], 'f', 8) :
               Z = QString::number(lien_objet->Tre[i*3+2][cl], 'f', 8);
*/

      X.truncate( 8 );
      Y.truncate( 8 );
      Z.truncate( 8 );
      number = (nb_ligne - coupure_ligne)*i + cl +1;
      if(number < 10) val = "       "+QString::number(number);
      else if(number < 100) val = "      "+QString::number(number);
           else if(number < 1000) val = "     "+QString::number(number);
                else if(number < 10000) val = "    "+QString::number(number);
                     else val = "   "+QString::number(number); //val < 100000

      text1 += "GRID    "+val+"        "+X+Y+Z+"\n";

}

if( tria_nas == 1){ 

number = 0;
// Begining to define triangles
for(i=0;i<nb_ligne -1 -coupure_ligne; i++)
  for(cl=0; cl<nb_colone -1 -coupure_colone; cl++) {

      number += 1;
      if(number < 10) val = "       "+QString::number(number);
      else if(number < 100) val = "      "+QString::number(number);
           else if(number < 1000) val = "     "+QString::number(number);
                else if(number < 10000) val = "    "+QString::number(number);
                     else val = "   "+QString::number(number); //val < 100000


      n1 = (nb_ligne - coupure_ligne)*i + cl +1;
      if(n1 < 10) val1 = "       "+QString::number(n1);
      else if(n1 < 100) val1 = "      "+QString::number(n1);
           else if(n1 < 1000) val1 = "     "+QString::number(n1);
                else if(n1 < 10000) val1 = "    "+QString::number(n1);
                     else val1 = "   "+QString::number(n1); //val < 100000

      n2 = (nb_ligne - coupure_ligne)*(i+1) + cl +1;
      if(n2 < 10) val2 = "       "+QString::number(n2);
      else if(n2 < 100) val2 = "      "+QString::number(n2);
           else if(n2 < 1000) val2 = "     "+QString::number(n2);
                else if(n2 < 10000) val2 = "    "+QString::number(n2);
                     else val2 = "   "+QString::number(n2); //val < 100000

      n3 = (nb_ligne - coupure_ligne)*(i+1) + cl +2;
      if(n3 < 10) val3 = "       "+QString::number(n3);
      else if(n3 < 100) val3 = "      "+QString::number(n3);
           else if(n3 < 1000) val3 = "     "+QString::number(n3);
                else if(n3 < 10000) val3 = "    "+QString::number(n3);
                     else val3 = "   "+QString::number(n3); //val < 100000


text1 +="CTRIA3  "+val+"       1"+val1+val2+val3+"\n";

      number += 1;
      if(number < 10) val = "       "+QString::number(number);
      else if(number < 100) val = "      "+QString::number(number);
           else if(number < 1000) val = "     "+QString::number(number);
                else if(number < 10000) val = "    "+QString::number(number);
                     else val = "   "+QString::number(number); //val < 100000

      n2 = (nb_ligne - coupure_ligne)*i + cl +2;
      if(n2 < 10) val2 = "       "+QString::number(n2);
      else if(n2 < 100) val2 = "      "+QString::number(n2);
           else if(n2 < 1000) val2 = "     "+QString::number(n2);
                else if(n2 < 10000) val2 = "    "+QString::number(n2);
                     else val2 = "   "+QString::number(n2); //val < 100000

text1 +="CTRIA3  "+val+"       1"+val3+val2+val1+"\n";
                                                    }

        saveScript(text1, "test_tria.nas");
        editeur *ed = new editeur();
        ed->load("test_tria.nas");
        ed->show(); 

}
//Nas QUAD
else {

number = 0;
// Begining to define triangles
for(i=0;i<nb_ligne -1 -coupure_ligne; i++)
  for(cl=0; cl<nb_colone -1 -coupure_colone; cl++) {

      number += 1;
      if(number < 10) val = "       "+QString::number(number);
      else if(number < 100) val = "      "+QString::number(number);
           else if(number < 1000) val = "     "+QString::number(number);
                else if(number < 10000) val = "    "+QString::number(number);
                     else val = "   "+QString::number(number); //val < 100000


      n1 = (nb_ligne - coupure_ligne)*i + cl +1;
      if(n1 < 10) val1 = "       "+QString::number(n1);
      else if(n1 < 100) val1 = "      "+QString::number(n1);
           else if(n1 < 1000) val1 = "     "+QString::number(n1);
                else if(n1 < 10000) val1 = "    "+QString::number(n1);
                     else val1 = "   "+QString::number(n1); //val < 100000

      n2 = (nb_ligne - coupure_ligne)*(i+1) + cl +1;
      if(n2 < 10) val2 = "       "+QString::number(n2);
      else if(n2 < 100) val2 = "      "+QString::number(n2);
           else if(n2 < 1000) val2 = "     "+QString::number(n2);
                else if(n2 < 10000) val2 = "    "+QString::number(n2);
                     else val2 = "   "+QString::number(n2); //val < 100000

      n3 = (nb_ligne - coupure_ligne)*(i+1) + cl +2;
      if(n3 < 10) val3 = "       "+QString::number(n3);
      else if(n3 < 100) val3 = "      "+QString::number(n3);
           else if(n3 < 1000) val3 = "     "+QString::number(n3);
                else if(n3 < 10000) val3 = "    "+QString::number(n3);
                     else val3 = "   "+QString::number(n3); //val < 100000

      n4 = (nb_ligne - coupure_ligne)*i + cl +2;
      if(n4 < 10) val4 = "       "+QString::number(n4);
      else if(n4 < 100) val4 = "      "+QString::number(n4);
           else if(n4 < 1000) val4 = "     "+QString::number(n4);
                else if(n4 < 10000) val4 = "    "+QString::number(n4);
                     else val4 = "   "+QString::number(n4); //val < 100000

text1 +="CQUAD4  "+val+"       1"+val1+val2+val3+val4+"\n";

}

        saveScript(text1, "test_quad.nas");
        editeur *ed = new editeur();
        ed->load("test_quad.nas");
        ed->show(); 

}

}
//====================================
void k3dsurface::saveScript(QString &text, QString name)
{
      QFile f( name );
    if ( !f.open( IO_WriteOnly ) ) {
 statusBar()->message( tr("Could not write to %1").arg(name),
         2000 );
 return;
    }

    QTextStream t( &f );
    t << text;
    f.close();
}
//====================================
void k3dsurface::smooth_ok()
{
smooth_triangle=1;
}
//====================================
void k3dsurface::triangle_ok()
{
smooth_triangle=-1;
}
//====================================
void k3dsurface::mesh_ok()
{
mesh_parametric = 1;
}
//====================================
void k3dsurface::parameter_ok()
{
mesh_parametric = -1;
}



//====================================
void k3dsurface::NewIsoScript()
{

    int i, ValIndex;
    Iso3D  * lien_objet;
    int NbTriangleUsed;


    QString text1, text2;

/// The only two infos needed to generate the FileOutPut
     lien_objet = isoWidget->IsoObjet;

/// Lunch the function to sabve the IsoSurface:
     lien_objet->SaveIsoMap();

/// Now that all is Ok, we can write theses values to the file :
     NbTriangleUsed = lien_objet->NbTriangleUsed;

        text1 = "#include \"shapes.inc\"\n\
#include \"colors.inc\"\n\
#include \"textures.inc\"\n\n\
#declare BACK_TEXTURE = texture {\n\
\n\
    pigment {\n\
        //checker color Blue color Red\n\
        //scale 10\n\
        //color Blue\n\
        color red  "+QString::number(lien_objet->frontsurfr/256.0)+" green  "+QString::number(lien_objet->frontsurfg/256.0)+" blue  "+QString::number(lien_objet->frontsurfb/256.0)+"\n\
    }\n\
    finish {\n\
        ambient 0.5\n\
        diffuse 0.4\n\
    }\n\
}\n\
#declare FRONT_TEXTURE = texture {  \n\
 pigment { \n\
        color red  "+QString::number(lien_objet->backsurfr/256.0)+" green  "+QString::number(lien_objet->backsurfg/256.0)+" blue  "+QString::number(lien_objet->backsurfb/256.0)+"\n }\n\
    finish {\n\
        ambient 0.5\n\
        diffuse 0.4\n\
    }\n\
}  \n\
\n\
#include \"Mesh.inc\"\n\
\n\
//camera\n\
 camera {\n\
  location  <0.0, 0.0, 800.0>\n\
     right     <-1, 0.0,  0.0>\n\
   //right     <0.0, 0.0,  0.0>\n\
   //up        <0.0, 0.0,  0.0>\n\
  direction <0.0, 0.0,  -1.0>\n\
 }\n\
 // Light source\n\
 light_source { <0, 0, 1000> colour White }    \n\
    \n";
    saveScript(text1, "test.pov");

/////////////////////////////////////////////////////////////////

    text2 = "mesh { \n";
  if(smooth_triangle ==1) 
    for(i=0;i<NbTriangleUsed; i++) {
ValIndex = 18*i;
text2 += "smooth_triangle {<"+QString::number(lien_objet->FileOutput[ValIndex  ])+", "+QString::number(lien_objet->FileOutput[ValIndex+1])+", "+QString::number(lien_objet->FileOutput[ValIndex+2])+">, ";
text2 += "<"+QString::number(lien_objet->FileOutput[ValIndex+9])+", "+QString::number(lien_objet->FileOutput[ValIndex+10])+", "+QString::number(lien_objet->FileOutput[ValIndex+11])+">, ";

text2 += "<"+QString::number(lien_objet->FileOutput[ValIndex+3])+", "+QString::number(lien_objet->FileOutput[ValIndex+4])+", "+QString::number(lien_objet->FileOutput[ValIndex+5])+">, ";
text2 += "<"+QString::number(lien_objet->FileOutput[ValIndex+12])+", "+QString::number(lien_objet->FileOutput[ValIndex+13])+", "+QString::number(lien_objet->FileOutput[ValIndex+14])+">, ";

text2 += "<"+QString::number(lien_objet->FileOutput[ValIndex+6])+", "+QString::number(lien_objet->FileOutput[ValIndex+7])+", "+QString::number(lien_objet->FileOutput[ValIndex+8])+">,";
text2 += "<"+QString::number(lien_objet->FileOutput[ValIndex+15])+", "+QString::number(lien_objet->FileOutput[ValIndex+16])+", "+QString::number(lien_objet->FileOutput[ValIndex+17])+">} \n";

}

else
    for(i=0;i<NbTriangleUsed; i++){
ValIndex = 18*i;
    text2 += "triangle {<"+QString::number(lien_objet->FileOutput[ValIndex  ])+", "+QString::number(lien_objet->FileOutput[ValIndex+1])+", "+QString::number(lien_objet->FileOutput[ValIndex+2])+">, ";

    text2 += "<"+QString::number(lien_objet->FileOutput[ValIndex+3])+", "+QString::number(lien_objet->FileOutput[ValIndex+4])+", "+QString::number(lien_objet->FileOutput[ValIndex+5])+">, ";

    text2 += "<"+QString::number(lien_objet->FileOutput[ValIndex+6])+", "+QString::number(lien_objet->FileOutput[ValIndex+7])+", "+QString::number(lien_objet->FileOutput[ValIndex+8])+">}\n";

}

    text2 += " texture { FRONT_TEXTURE }  \n\
       interior_texture { BACK_TEXTURE }\
       }\n\
       /*************End of 'file.inc'************/ ";

    saveScript(text2, "Mesh.inc");

 }


//====================================
void k3dsurface::newScriptRun()
{
    int i,cl;
    Model3D  * lien_objet;
    int nb_ligne = connectWidget2->objet->nb_ligne ,
         nb_colone = connectWidget2->objet->nb_colone,
         coupure_ligne = connectWidget2->objet->coupure_ligne,
         coupure_colone = connectWidget2->objet->coupure_col;
     lien_objet = connectWidget2->objet;

    QString text1, text2;


/// If IsoSurface is activated
//if(activateiso == 1) NewIsoScript();

    if(tabsurf->currentPageIndex() == 1) {
 isoWidget->IsoMorphCompute(); // Not always necessery but for we don't generate .obj file all the time...
 NewIsoScript();
    }
else    /// We do like before...
    if( mesh_parametric ==1){

     connectWidget2->valueChanged();  // Not always necessery but for we don't generate .obj file all the time...
    
        text1 = "#include \"shapes.inc\"\n\
#include \"colors.inc\"\n\
#include \"textures.inc\"\n\n\
#declare FRONT_TEXTURE = texture {\n\
\n\
    pigment {\n\
        //checker color Blue color Red\n\
        //scale 10\n\
        //color Blue\n\
        color red  "+QString::number(lien_objet->frontsurfr/256.0)+" green  "+QString::number(lien_objet->frontsurfg/256.0)+" blue  "+QString::number(lien_objet->frontsurfb/256.0)+"\n\
    }\n\
    finish {\n\
        ambient 0.5\n\
        diffuse 0.4\n\
    }\n\
}\n\
#declare BACK_TEXTURE = texture {  \n\
 pigment { \n\
        color red  "+QString::number(lien_objet->backsurfr/256.0)+" green  "+QString::number(lien_objet->backsurfg/256.0)+" blue  "+QString::number(lien_objet->backsurfb/256.0)+"\n }\n\
    finish {\n\
        ambient 0.5\n\
        diffuse 0.4\n\
    }\n\
}  \n\
\n\
#include \"Mesh.inc\"\n\
\n\
//Plan\n\
 plane { y, -1800\n\
     pigment {\n\
        checker color Green color Yellow\n\
        scale 100\n\
    }\n\
     finish {\n\
        ambient 0.6\n\
        diffuse 0.6\n\
    }\n\
 }\n\
//camera\n\
 camera {\n\
  location  <0.0, 0.0, 800.0>\n\
     right     <-1, 0.0,  0.0>\n\
   //right     <0.0, 0.0,  0.0>\n\
   //up        <0.0, 0.0,  0.0>\n\
  direction <0.0, 0.0,  -1.0>\n\
 }\n\
 // Light source\n\
 light_source { <0, 0, 1000> colour White }    \n\
    \n";
    saveScript(text1, "test.pov");

/////////////////////////////////////////////////////////////////

    text2 = "mesh { \n";
  if(smooth_triangle ==1) 
    for(i=0;i<nb_ligne-1- coupure_ligne; i++)
 for(cl=0; cl<nb_colone-1- coupure_colone; cl++) {

    text2 += "smooth_triangle {<"+QString::number(lien_objet->Tre[i*3][cl])+", "+QString::number(lien_objet->Tre[i*3+1][cl])+", "+QString::number(lien_objet->Tre[i*3+2][cl])+">, ";
      text2 += "<"+QString::number(-lien_objet->Nor[i*3][cl])+", "+QString::number(-lien_objet->Nor[i*3+1][cl])+", "+QString::number(-lien_objet->Nor[i*3+2][cl])+">, ";

    text2 += "<"+QString::number(lien_objet->Tre[(i+1)*3][cl])+", "+QString::number(lien_objet->Tre[(i+1)*3+1][cl])+", "+QString::number(lien_objet->Tre[(i+1)*3+2][cl])+">, ";
     text2 += "<"+QString::number(-lien_objet->Nor[(i+1)*3][cl])+", "+QString::number(-lien_objet->Nor[(i+1)*3+1][cl])+", "+QString::number(-lien_objet->Nor[(i+1)*3+2][cl])+">, ";

    text2 += "<"+QString::number(lien_objet->Tre[(i+1)*3][cl+1])+", "+QString::number(lien_objet->Tre[(i+1)*3+1][cl+1])+", "+QString::number(lien_objet->Tre[(i+1)*3+2][cl+1])+">,";
      text2 += "<"+QString::number(-lien_objet->Nor[(i+1)*3][cl+1])+", "+QString::number(-lien_objet->Nor[(i+1)*3+1][cl+1])+", "+QString::number(-lien_objet->Nor[(i+1)*3+2][cl+1])+">} \n";

    text2 += "smooth_triangle {<"+QString::number(lien_objet->Tre[(i+1)*3][cl+1])+", "+QString::number(lien_objet->Tre[(i+1)*3+1][cl+1])+", "+QString::number(lien_objet->Tre[(i+1)*3+2][cl+1])+">, ";
      text2 += "<"+QString::number(-lien_objet->Nor[(i+1)*3][cl+1])+", "+QString::number(-lien_objet->Nor[(i+1)*3+1][cl+1])+", "+QString::number(-lien_objet->Nor[(i+1)*3+2][cl+1])+">, ";

    text2 += "<"+QString::number(lien_objet->Tre[i*3][cl+1])+", "+QString::number(lien_objet->Tre[i*3+1][cl+1])+", "+QString::number(lien_objet->Tre[i*3+2][cl+1])+">, ";
    text2 += "<"+QString::number(-lien_objet->Nor[i*3][cl+1])+", "+QString::number(-lien_objet->Nor[i*3+1][cl+1])+", "+QString::number(-lien_objet->Nor[i*3+2][cl+1])+">, ";


text2 += "<"+QString::number(lien_objet->Tre[i*3][cl])+", "+QString::number(lien_objet->Tre[i*3+1][cl])+", "+QString::number(lien_objet->Tre[i*3+2][cl])+">,";
text2 += "<"+QString::number(-lien_objet->Nor[i*3][cl])+", "+QString::number(-lien_objet->Nor[i*3+1][cl])+", "+QString::number(-lien_objet->Nor[i*3+2][cl])+"> \n\
} \n";
}

else
     for(i=0;i<nb_ligne-1-coupure_ligne; i++)
 for(cl=0; cl<nb_colone-1-coupure_colone; cl++) {

    text2 += "triangle {<"+QString::number(lien_objet->Tre[i*3][cl])+", "+QString::number(lien_objet->Tre[i*3+1][cl])+", "+QString::number(lien_objet->Tre[i*3+2][cl])+">, ";
    text2 += "<"+QString::number(lien_objet->Tre[(i+1)*3][cl])+", "+QString::number(lien_objet->Tre[(i+1)*3+1][cl])+", "+QString::number(lien_objet->Tre[(i+1)*3+2][cl])+">, ";
    text2 += "<"+QString::number(lien_objet->Tre[(i+1)*3][cl+1])+", "+QString::number(lien_objet->Tre[(i+1)*3+1][cl+1])+", "+QString::number(lien_objet->Tre[(i+1)*3+2][cl+1])+">} \n";

    text2 += "triangle {<"+QString::number(lien_objet->Tre[(i+1)*3][cl+1])+", "+QString::number(lien_objet->Tre[(i+1)*3+1][cl+1])+", "+QString::number(lien_objet->Tre[(i+1)*3+2][cl+1])+">, ";
    text2 += "<"+QString::number(lien_objet->Tre[i*3][cl+1])+", "+QString::number(lien_objet->Tre[i*3+1][cl+1])+", "+QString::number(lien_objet->Tre[i*3+2][cl+1])+">, ";
     text2 += "<"+QString::number(lien_objet->Tre[i*3][cl])+", "+QString::number(lien_objet->Tre[i*3+1][cl])+", "+QString::number(lien_objet->Tre[i*3+2][cl])+">} \n";

}

    text2 += " texture { FRONT_TEXTURE }  \n\
       interior_texture { BACK_TEXTURE }\
       }\n\
       /*************End of 'file.inc'************/ ";

    saveScript(text2, "Mesh.inc");
}
else {
     QString text;

    text = "#include \"shapes.inc\"\n\
#include \"colors.inc\"\n\
#include \"textures.inc\"\n\n\
parametric {\n \tfunction  {   ";
    text +=   xcft->text();
    text += "   } \n  \tfunction  {   "; 
    text +=   ycft->text();    
    text += "   } \n  \tfunction  {   ";
    text +=   zcft->text();
    text += "   } \n  \t<";
    text +=   umin->text();
    text += ",  ";
    text +=   vmin->text();
    text += "> ,  <  ";
    text +=   umax->text();
    text += ",  ";
    text +=   vmax->text();
    text += "> \n  \tcontained_by { sphere{0, 4} } \n \
\taccuracy 0.01  \n \
\tprecompute 10 x,y,z \n \
pigment { \n\
        color red  "+QString::number(lien_objet->backsurfr/256.0)+" green  "+QString::number(lien_objet->backsurfg/256.0)+" blue  "+QString::number(lien_objet->backsurfb/256.0)+"\n }\n\
    finish {\n\
        ambient 0.5\n\
        diffuse 0.4\n\
    }\n\
 }  \n\
//camera\n\
 camera {\n\
  location  <0.0, 0.0, 4.0>\n\
     right     <-1, 0.0,  0.0>\n\
   //right     <0.0, 0.0,  0.0>\n\
   //up        <0.0, 0.0,  0.0>\n\
  direction <0.0, 0.0,  -1.0>\n\
 }\n\
 // Light source\n\
 light_source { <0, 0, 1000> colour White }    \n\
    \n";


    saveScript(text, "test.pov");

}

    runpovray();

}
//====================================
void k3dsurface::newDocIso()
{
    editeur *ed = new editeur();
    ed->setCaption(tr("Qt Example - Application"));
    QString text;


    text = "F(x, y, z, t) = ";
    text +=   implicitfunct->text();
    text += " = 0 \n x [ ";
    text +=   minxlimit->text();
    text += ",  ";
    text +=   maxxlimit->text();
    text += "] ;\n y [  ";
    text +=  minylimit->text();
    text += ",  ";
    text +=   maxylimit->text();
    text += "] ;\n z [  ";
    text +=  minzlimit->text();
    text += ",  ";
    text +=   maxzlimit->text();
    text += "] ;\n";

   
    ed->settext(text);
    ed->show();
}
//====================================
void k3dsurface::newDocToolsIso()
{
    editeur *ed = new editeur();
    ed->setCaption(tr("Qt Example - Application"));
    QString text;

    text = "F(x, y, z, t) = ";
    text +=   implicitfunct_2->text();
    text += " = 0 \n x [ ";
    text +=   minxlimit_2->text();
    text += ",  ";
    text +=   maxxlimit_2->text();
    text += "] ;\n y [  ";
    text +=  minylimit_2->text();
    text += ",  ";
    text +=   maxylimit_2->text();
    text += "] ;\n z [  ";
    text +=  minzlimit_2->text();
    text += ",  ";
    text +=   maxzlimit_2->text();
    text += "] ;\n";
    
    ed->settext(text);
    ed->show();
    
    
}
//==============================
void k3dsurface::newDoc()
{
    editeur *ed = new editeur();
    ed->setCaption(tr("Qt Example - Application"));
    QString text;
/*
    if(activateiso == 1){

    text = "F(x, y, z, t) = ";
    text +=   implicitfunct->text();
    text += " = 0 \n x [ ";
    text +=   minxlimit->text();
    text += ",  ";
    text +=   maxxlimit->text();
    text += "] ;\n y [  ";
    text +=  minylimit->text();
    text += ",  ";
    text +=   maxylimit->text();
    text += "] ;\n z [  ";
    text +=  minzlimit->text();
    text += ",  ";
    text +=   maxzlimit->text();
    text += "] ;\n";

    }
    else 
*/
    if(activate_tools == 1)  {
    text = "X = ";
    text +=   xtool->text();
    text += "\nY = ";
    text +=   ytool->text();
    text += "\nZ = ";
    text +=   ztool->text();
    text += "\n With   U[ ";
    text +=   umin_tools->text();
    text += ",  ";
    text +=   umax_tools->text();
    text += "] And V[  ";
    text +=   vmin_tools->text();
    text += ",  ";
    text +=   vmax_tools->text();
    text += "] \n\n";

  }
  else
  if(cylindric_fct == 1) {
    text = "R^";
    text += puissance_c_val->text();
    text += " = ";
    text += fctdefc->text();
    text += "\n With   U[ ";
    text +=   umin_3_2_2_2->text();
    text += ",  ";
    text +=   umax_3_2_2_2->text();
    text += "] And V[  ";
    text +=   vmin_3_2_2_2->text();
    text += ",  ";
    text +=   vmax_3_2_2_2->text();
    text += "] \n";
 }

 else  if(spheric_fct == 1) {
    text = "R^";
    text += puissance_r_val->text();
    text += " = ";
    text += fctdefr->text();
    text += "\n With   U[ ";
    text +=   umin_3_2_2->text();
    text += ",  ";
    text +=   umax_3_2_2->text();
    text += "] And V[  ";
    text +=   vmin_3_2_2->text();
    text += ",  ";
    text +=   vmax_3_2_2->text();
    text += "] \n";
 }
else
if(sixdimshapes == 1) {
    text = "X = ";
    text +=   xcft_5->text();
    text += "\nY = ";
    text +=   ycft_5->text();
    text += "\nZ = ";
    text +=   zcft_5->text();
    text += "\nW = ";
    text +=   wcft_5->text();
    text += "\nT = ";
    text +=   tcft_5->text();
    text += "\nS = ";
    text +=   scft_5->text();

    text += "\n With   U[ "; 
    text +=   umin_5->text();
    text += ",  ";
    text +=   umax_5->text();
    text += "] And V[  ";
    text +=   vmin_5->text();
    text += ",  ";
    text +=   vmax_5->text();
    text += "] \n\n";

}
else

if(fivedimshapes == 1) {
    text = "X = ";
    text +=   xcft_5->text();
    text += "\nY = ";
    text +=   ycft_5->text();
    text += "\nZ = ";
    text +=   zcft_5->text();
    text += "\nW = ";
    text +=   wcft_5->text();
    text += "\nT = ";
    text +=   tcft_5->text();

    text += "\n With   U[ ";
    text +=   umin_5->text();
    text += ",  ";
    text +=   umax_5->text();
    text += "] And V[  ";
    text +=   vmin_5->text();
    text += ",  ";
    text +=   vmax_5->text();
    text += "] \n\n";

}
else
if(fourdimshapes == 1) {
    text = "X = ";
    text +=   xcft_2->text();
    text += "\nY = ";
    text +=   ycft_2->text();
    text += "\nZ = ";
    text +=   zcft_2->text();
    text += "\nW = ";
    text +=   wcft_2->text();
    text += "\n With   U[ ";
    text +=   umin_2->text();
    text += ",  ";
    text +=   umax_2->text();
    text += "] And V[  ";
    text +=   vmin_2->text();
    text += ",  ";
    text +=   vmax_2->text();
    text += "] \n\n";

}
else
if( connectWidget2->objet->implicitdef == -1) {
    text = "X = ";
    text +=   xcft->text();
    text += "\nY = ";
    text +=   ycft->text();
    text += "\nZ = ";
    text +=   zcft->text();
    text += "\n With   U[ ";
    text +=   umin->text();
    text += ",  ";
    text +=   umax->text();
    text += "] And V[  ";
    text +=   vmin->text();
    text += ",  ";
    text +=   vmax->text();
    text += "] \n\n";
  if(connectWidget2->objet->two_system == 1) {
    text += "X_2 = ";
    text +=   xcft_3->text();
    text += "\nY_2 = ";
    text +=   ycft_3->text();
    text += "\nZ_2 = ";
    text +=   zcft_3->text();
    text += "\n With   U[ ";
    text +=   umin_3->text();
    text += ",  ";
    text +=   umax_3->text();
    text += "] And V[  ";
    text +=   vmin_3->text();
    text += ",  ";
    text +=   vmax_3->text();
    text += "] \n\n";
   }
 }
 else {
     text = "Z^";
    text +=   puissance_val_2->text();
    text += " = ";
    text += fctdefz_val_2->text();
    text += "\n With   U[ ";
    text +=   umin_3_2->text();
    text += ",  ";
    text +=   umax_3_2->text();
    text += "] And V[  ";
    text +=   vmin_3_2->text();
    text += ",  ";
    text +=   vmax_3_2->text();
    text += "] \n";
 }
    ed->settext(text);
    ed->show();

}
//====================================

void k3dsurface::povfile()
{
    editeur *ed = new editeur();
    ed->setCaption(tr("Qt Example - Application"));
    QString text;

    text = "#include \"shapes.inc\"\n\
#include \"colors.inc\"\n\
#include \"textures.inc\"\n\n\
parametric {\n \tfunction  {   ";
    text +=   xcft->text();
    text += "   } \n  \tfunction  {   ";
    text +=   ycft->text();
    text += "   } \n  \tfunction  {   ";
    text +=   zcft->text();
    text += "   } \n  \t<";
    text +=   umin->text();
    text += ",  ";
    text +=   vmin->text();
    text += "> ,  <  ";
    text +=   umax->text();
    text += ",  ";
    text +=   vmax->text();
    text += "> \n  \tcontained_by { sphere{0, 4} } \n \
\taccuracy 0.01  \n \
\tprecompute 10 x,y,z \n \
   pigment {\n \
\t      checker color Yellow color Red\n \
\t      scale 0.3\n \
   }\n \
   finish {\n \
\t      ambient 0.7\n \
\t      diffuse 0.8\n \
   }\n \
}\n \
plane { -z, -20\n \
\t   pigment {\n \
\t      checker color Green color Yellow\n \
\t      scale 4\n \
   }\n \
\t   finish {\n \
\t      ambient 0.2\n \
\t      diffuse 0.8\n \
   }\n \
}\n \
camera {\n \
\tlocation  <0.0, 0.0, -6.0>\n \
\t //right     <0.0, 0.0,  0.0>\n \
\t //up        <0.0, 0.0,  0.0>\n \
\tdirection <0.0, 0.0,  1.0>\n \
}\n \
\n \
// Light source\n \
light_source { <0, 0, -5> colour White }\n ";

    ed->settext(text);
    ed->show();

}
//====================================
void k3dsurface::typecolor(int cl)
{
///    if(activateiso == 1) { isoWidget->colortype = cl;
    isoWidget->colortype = cl;
    IsoGlWidget->colortype = cl;
    connectWidget2->colortype = cl;
    ParamGlWidget->colortype = cl;

if(tabsurf->currentPageIndex() == 1)  {
     switch(cl) {

    case 0:
              red->setValue(isoWidget->IsoObjet->frontsurfr) ;
              green->setValue(isoWidget->IsoObjet->frontsurfg) ;
              blue->setValue(isoWidget->IsoObjet->frontsurfb );
              transparence->setEnabled(TRUE);
       if (isoWidget->IsoObjet->fronttrans == 1 && !transparence->isOn() )
                   transparence->toggle();
       if(isoWidget->IsoObjet->fronttrans == -1 && transparence->isOn())   transparence->toggle();

 break;
    case 1:
              red->setValue(isoWidget->IsoObjet->backsurfr) ;
              green->setValue(isoWidget->IsoObjet->backsurfg);
              blue->setValue(isoWidget->IsoObjet->backsurfb );
              transparence->setEnabled(TRUE);
       if (isoWidget->IsoObjet->backtrans == 1 && !transparence->isOn() )
                   transparence->toggle();
       if(isoWidget->IsoObjet->backtrans == -1 && transparence->isOn())   transparence->toggle();


 break;
    case 2:
              red->setValue(isoWidget->IsoObjet->gridr) ;
              green->setValue(isoWidget->IsoObjet->gridg);
              blue->setValue(isoWidget->IsoObjet->gridb);
              transparence->setEnabled(TRUE);

       if (isoWidget->IsoObjet->gridtransparent == 1 && !transparence->isOn() )
                   transparence->toggle();
       if(isoWidget->IsoObjet->gridtransparent == -1 && transparence->isOn())   transparence->toggle();


 break;
    case 3:
              red->setValue(isoWidget->redbackground) ;
              green->setValue(isoWidget->greenbackground);
              blue->setValue(isoWidget->bluebackground);
              transparence->setEnabled(FALSE);
 break;

     case 4:
              red->setValue(isoWidget->IsoObjet->CNDsurfr) ;
              green->setValue(isoWidget->IsoObjet->CNDsurfg);
              blue->setValue(isoWidget->IsoObjet->CNDsurfb );
              transparence->setEnabled(TRUE);
       if (isoWidget->IsoObjet->CNDtrans == 1 && !transparence->isOn() )
                   transparence->toggle();
       if(isoWidget->IsoObjet->CNDtrans == -1 && transparence->isOn())   transparence->toggle();

 break;

}
}
    else {

    switch(cl) {

    case 0:
              red->setValue(connectWidget2->objet->frontsurfr) ;
              green->setValue(connectWidget2->objet->frontsurfg) ;
              blue->setValue(connectWidget2->objet->frontsurfb );
       transparence->setEnabled(TRUE);
       if (connectWidget2->objet->fronttrans == 1 && !transparence->isOn() )
                   transparence->toggle();
       if(connectWidget2->objet->fronttrans == -1 && transparence->isOn())   transparence->toggle();

 break;
    case 1:
              red->setValue(connectWidget2->objet->backsurfr) ;
              green->setValue(connectWidget2->objet->backsurfg);
              blue->setValue(connectWidget2->objet->backsurfb );
       transparence->setEnabled(TRUE);
       if (connectWidget2->objet->backtrans == 1 && !transparence->isOn() )
                   transparence->toggle();
       if(connectWidget2->objet->backtrans == -1 && transparence->isOn())   transparence->toggle();

 break;
    case 2:
              red->setValue(connectWidget2->objet->gridliner) ;
              green->setValue(connectWidget2->objet->gridlineg);
              blue->setValue(connectWidget2->objet->gridlineb);
       transparence->setEnabled(FALSE);
 break;

    case 3:
              red->setValue(connectWidget2->redbackground) ;
              green->setValue(connectWidget2->greenbackground);
              blue->setValue(connectWidget2->bluebackground);
       transparence->setEnabled(FALSE);
 break;

};

} /// End else...
}

//====================================

void k3dsurface::newfct_ok(  )
{
  ////+++++++++++++++++++++
  QString Intermediate;/// To reverse the Axes
  Intermediate = fctdef->text();/// To reverse the Axes
  Intermediate.replace(QChar('x'), "W");/// To reverse the Axes
  Intermediate.replace(QChar('y'), "x");/// To reverse the Axes
  Intermediate.replace(QChar('W'), "y");  /// To reverse the Axes 
       ////+++++++++++++++++++++    
    // connectWidget2->objet->newfct = fctdef->text();
     connectWidget2->objet->newfct = Intermediate;
     connectWidget2->objet->DefineNewFct *=-1;
}
//====================================
void k3dsurface::spheric_fct_changed( const QString & choix )
{

  
      if(choix == QString("Blob_1")) {
  puissance_r_val->setText("1") ;
  fctdefr->setText("3*cos(u)*cos(v)*sin(u)*sin(u+v)+0.8") ;
  umin_3_2_2->setText("-pi/2") ; 
  umax_3_2_2->setText("pi/2") ; 
  vmin_3_2_2->setText("-pi") ; 
  vmax_3_2_2->setText("pi") ;
  perform_sphere();   // process the new surface  
  return;
    }
      else
       if(choix == QString("Blob_2")) {
  puissance_r_val->setText("1") ;
  fctdefr->setText("3*sin(u)*sin(u)+0.8") ;
  umin_3_2_2->setText("-pi/2") ; 
  umax_3_2_2->setText("pi/2") ; 
  vmin_3_2_2->setText("-pi") ; 
  vmax_3_2_2->setText("pi") ;
  perform_sphere();  // process the new surface   
  return;
    }    
        if(choix == QString("Blob_3")) {
  puissance_r_val->setText("1") ;
  fctdefr->setText("3*cos(u)*cos(v)*sin(u)+0.8") ;
  umin_3_2_2->setText("-pi/2") ; 
  umax_3_2_2->setText("pi/2") ; 
  vmin_3_2_2->setText("-pi") ; 
  vmax_3_2_2->setText("pi") ; 
  perform_sphere();   // process the new surface 
  return;
    }       
       
       
          if(choix == QString("Blob_4")) {
  puissance_r_val->setText("1") ;
  fctdefr->setText("3*sin(u)*cos(u)+0.8") ;
  umin_3_2_2->setText("-pi/2") ; 
  umax_3_2_2->setText("pi/2") ; 
  vmin_3_2_2->setText("-pi") ; 
  vmax_3_2_2->setText("pi") ;
  perform_sphere();  // process the new surface   
  return;
    }      
       
            if(choix == QString("Blob_5")) {
  puissance_r_val->setText("1") ;
  fctdefr->setText("3*cos(u)*sin(v)*sin(v)+0.8") ;
  umin_3_2_2->setText("-pi/2") ; 
  umax_3_2_2->setText("pi/2") ; 
  vmin_3_2_2->setText("-pi") ; 
  vmax_3_2_2->setText("pi") ; 
  perform_sphere();   // process the new surface 
  return;
    }       
       
             if(choix == QString("Blob_6")) {
  puissance_r_val->setText("1") ;
  fctdefr->setText("sin(v)*cos(v)") ;
  umin_3_2_2->setText("-pi/2") ; 
  umax_3_2_2->setText("pi/2") ; 
  vmin_3_2_2->setText("-pi") ; 
  vmax_3_2_2->setText("pi") ; 
  perform_sphere();   // process the new surface 
  return;
    }      
       
             if(choix == QString("Blob_7")) {
  puissance_r_val->setText("1") ;
  fctdefr->setText("cos(u)*cos(u)") ;
  umin_3_2_2->setText("-pi/2") ; 
  umax_3_2_2->setText("pi/2") ; 
  vmin_3_2_2->setText("-pi") ; 
  vmax_3_2_2->setText("pi") ;  
  perform_sphere();  // process the new surface 
  return;
    }      
              if(choix == QString("Blob_8")) {
  puissance_r_val->setText("1") ;
  fctdefr->setText("cos(u)+cos(u)*cos(v) +0.8") ;
  umin_3_2_2->setText("-pi/2") ; 
  umax_3_2_2->setText("pi/2") ; 
  vmin_3_2_2->setText("-pi") ; 
  vmax_3_2_2->setText("pi") ; 
  perform_sphere();   // process the new surface 
  return;
    }  
              if(choix == QString("Blob_9")) {
  puissance_r_val->setText("1") ;
  fctdefr->setText("(abs(cos(7*u/4))^1.7 + abs(sin(7*u/4))^1.7)^(-1/0.2)") ;
  umin_3_2_2->setText("-pi/2") ; 
  umax_3_2_2->setText("pi/2") ; 
  vmin_3_2_2->setText("-pi") ; 
  vmax_3_2_2->setText("pi") ; 
  perform_sphere();   // process the new surface 
  return;
    }       
       
               if(choix == QString("Blob_10")) {
  puissance_r_val->setText("1") ;
  fctdefr->setText("abs(3*x)*cos(u)*sin(v)*sin(u)*sin(u+v)+0.8") ;
  umin_3_2_2->setText("-pi/2") ; 
  umax_3_2_2->setText("pi/2") ; 
  vmin_3_2_2->setText("-pi") ; 
  vmax_3_2_2->setText("pi") ;   
  perform_sphere(); // process the new surface 
  return;
    }     
  }
//====================================
void k3dsurface::implicit_fct_changed( const QString & choix )
{

  
      if(choix == QString("Wave")) {
  puissance_val_2->setText("1") ;
  fctdefz_val_2->setText("2*cos(x)*sin(y)") ;
  umin_3_2->setText("-pi") ; 
  umax_3_2->setText("pi") ; 
  vmin_3_2->setText("-pi") ; 
  vmax_3_2->setText("pi") ;   
   // return;
    }
  
      if(choix == QString("Selle")) {
  puissance_val_2->setText("1") ;
  fctdefz_val_2->setText("cos(x)*y") ;
  umin_3_2->setText("-pi") ; 
  umax_3_2->setText("pi") ; 
  vmin_3_2->setText("-pi") ; 
  vmax_3_2->setText("pi") ;   
   // return;
    }
       if(choix == QString("Cone")) {
  puissance_val_2->setText("1") ;
  fctdefz_val_2->setText("1 - (x^2 + y^2)") ;
  umin_3_2->setText("-1") ; 
  umax_3_2->setText("1") ; 
  vmin_3_2->setText("-1") ; 
  vmax_3_2->setText("1") ;   
   // return;
    } 
    
        if(choix == QString("x*exp(-x^2-y^2)")) {
  puissance_val_2->setText("1") ;
  fctdefz_val_2->setText("4*x*exp(-x^2-y^2)") ;
  umin_3_2->setText("-2") ; 
  umax_3_2->setText("2") ; 
  vmin_3_2->setText("-2") ; 
  vmax_3_2->setText("2") ;   
   // return;
    }

      if(choix == QString("cos(x*y)")) {
  puissance_val_2->setText("1") ;
  fctdefz_val_2->setText("cos(x*y)") ;
  umin_3_2->setText("-pi") ; 
  umax_3_2->setText("pi") ; 
  vmin_3_2->setText("-pi") ; 
  vmax_3_2->setText("pi") ;   
   // return;
    }

      if(choix == QString("cos(x*x-y*y)")) {
  puissance_val_2->setText("1") ;
  fctdefz_val_2->setText("cos(x*x - y*y)/2") ;
  umin_3_2->setText("-pi") ; 
  umax_3_2->setText("pi") ; 
  vmin_3_2->setText("-pi") ; 
  vmax_3_2->setText("pi") ;   
   // return;
    }  
    
    
    
  // process the new surface        
 perform2();   
 
    
    
    
  }
  
  
//====================================
void k3dsurface::choice4D_changed( const QString & choix )
{

    
                        if(choix == QString("shell4D")) {
   connectWidget2->objet->two_system = -1;
   connectWidget2->objet->fourdimshapes = 1;
  xcft_2->setText("1.2^v*(sin(u)^2 *sin(v))");
  ycft_2->setText("1.2^v*(sin(u)^2 *cos(v))");
  zcft_2->setText("1.2^v*(sin(u)*cos(u))") ;
  wcft_2->setText("cos(u)*sinh(u)") ;
  umin_2->setText("0") ; 
  umax_2->setText("pi") ; 
  vmin_2->setText("-pi/4") ; 
  vmax_2->setText("5*pi/2") ; 

    } 

                       if(choix == QString("Curve4D")) {
   connectWidget2->objet->two_system = -1;
   connectWidget2->objet->fourdimshapes = 1;
  xcft_2->setText("sin(pi*u)");
  ycft_2->setText("cos(pi*u)");
  zcft_2->setText("sin(3*pi*u)") ;
  wcft_2->setText("cos(3*pi*u)") ;
  umin_2->setText("0") ; 
  umax_2->setText("2") ; 
  vmin_2->setText("1") ; 
  vmax_2->setText("1") ; 

    } 


                       if(choix == QString("Klein4D")) {
   connectWidget2->objet->two_system = -1;
   connectWidget2->objet->fourdimshapes = 1;
  xcft_2->setText("(1 +0.3*cos(2*pi*u))*cos(2*pi*v)");
  ycft_2->setText("(1+0.3*cos(2*pi*u))*cos(pi*u)*sin(2*pi*v)");
  zcft_2->setText("(1+0.3*cos(2*pi*u))*sin(pi*u)*sin(2*pi*v)") ;
  wcft_2->setText("cos(2*pi*u)") ;
  umin_2->setText("0") ; 
  umax_2->setText("1") ; 
  vmin_2->setText("0") ; 
  vmax_2->setText("1") ; 

    } 



                       if(choix == QString("FlatTorus4D")) {
   connectWidget2->objet->two_system = -1;
   connectWidget2->objet->fourdimshapes = 1;
  xcft_2->setText("sin(2*pi*u)");
  ycft_2->setText("cos(2*pi*u)");
  zcft_2->setText("sin(2*pi*v)") ;
  wcft_2->setText("cos(2*pi*v)") ;
  umin_2->setText("0") ; 
  umax_2->setText("1") ; 
  vmin_2->setText("0") ; 
  vmax_2->setText("1") ; 

    } 


                       if(choix == QString("LawsonHelicoidal")) {
   connectWidget2->objet->two_system = -1;
   connectWidget2->objet->fourdimshapes = 1;
  xcft_2->setText("cos(u)*cos(v)");
  ycft_2->setText("cos(0.7*pi/4)*cos(u)*sin(v)-sin(1.2*pi/4)*sin(u)*cos(0.5*v)");
  zcft_2->setText("sin(u)*sin(0.5*v)") ;
  wcft_2->setText("sin(0.7*pi/4)*cos(u)*sin(v)+cos(1.2*pi/4)*sin(u)*cos(0.5*v)") ;
  umin_2->setText("0") ; 
  umax_2->setText("2*pi") ; 
  vmin_2->setText("0") ; 
  vmax_2->setText("2*pi") ; 

    } 



                       if(choix == QString("Hyperbolichelicoidal_2")) {
   connectWidget2->objet->two_system = -1;
   connectWidget2->objet->fourdimshapes = 1;
  xcft_2->setText("sinh(v)*cos(4*u)");
  ycft_2->setText("sinh(v)*sin(4*u)");
  zcft_2->setText("cosh(v)*sinh(u)") ;
  wcft_2->setText("cosh(u)*cosh(v)") ;
  umin_2->setText("-2.5") ; 
  umax_2->setText("2.5") ; 
  vmin_2->setText("-4") ; 
  vmax_2->setText("4") ; 

    } 

                       if(choix == QString("Hopftorus4D")) {
   connectWidget2->objet->two_system = -1;
   connectWidget2->objet->fourdimshapes = 1;
  xcft_2->setText("cos(0.46)*cos(u+v)");
  ycft_2->setText("cos(0.46)*sin(u+v)");
  zcft_2->setText("sin(0.46)*sin(v)") ;
  wcft_2->setText("sin(0.46)*cos(v)") ;
  umin_2->setText("0") ; 
  umax_2->setText("2*pi") ; 
  vmin_2->setText("0") ; 
  vmax_2->setText("2*pi") ; 

    }   















    
                        if(choix == QString("Flower")) {
   connectWidget2->objet->two_system = -1;
   connectWidget2->objet->fourdimshapes = 1;
  xcft_2->setText("v *cos(u) -0.5*v^2*cos(2*u)");
  ycft_2->setText("-v*sin(u) -0.5*v^2*sin(2*u)");
  zcft_2->setText("4* v^1.5 *cos(3* u / 2) / 3") ;
  wcft_2->setText("cos(u)") ;
  umin_2->setText("0") ; 
  umax_2->setText("4*pi") ; 
  vmin_2->setText("0") ; 
  vmax_2->setText("1") ; 

    } 
  
  
  
    if(choix == QString("Cosinus")) {
   connectWidget2->objet->two_system = -1;
   connectWidget2->objet->fourdimshapes = 1;
  xcft_2->setText("u");
  ycft_2->setText("v");
  zcft_2->setText("sin(t*pi*((u)^2+(v)^2))/2") ;
  wcft_2->setText("cos(u)") ; 
  umin_2->setText("-1") ; 
  umax_2->setText("1") ; 
  vmin_2->setText("-1") ; 
  vmax_2->setText("1") ;

    }
    
      if(choix == QString("Shell")) {
   connectWidget2->objet->two_system = -1;
   connectWidget2->objet->fourdimshapes = 1;
  xcft_2->setText("1.2^v*(sin(u)^2 *sin(v))");
  ycft_2->setText("1.2^v*(sin(u)^2 *cos(v))");
  zcft_2->setText("1.2^v*(sin(u)*cos(u))") ;
  wcft_2->setText("cos(u)") ;
  umin_2->setText("0") ; 
  umax_2->setText("pi") ; 
  vmin_2->setText("-pi/4") ; 
  vmax_2->setText("5*pi/2") ; 

    }

       
           if(choix == QString("Sphere")) {
   connectWidget2->objet->two_system = -1;
   connectWidget2->objet->fourdimshapes = 1;
  xcft_2->setText("cos(u)*cos(v)");
  ycft_2->setText("cos(u)*sin(v)");
  zcft_2->setText("sin(u)") ;
  wcft_2->setText("cos(u)") ;
  umin_2->setText("-pi/2") ; 
  umax_2->setText("pi/2") ; 
  vmin_2->setText("0") ; 
  vmax_2->setText("2*pi") ; 

    }    
      
              if(choix == QString("Steiner")) {
   connectWidget2->objet->two_system = -1;
   connectWidget2->objet->fourdimshapes = 1;
  xcft_2->setText("(sin(2 * u) * cos(v) * cos(v))");
  ycft_2->setText("(sin(u) * sin(2 * v))");
  zcft_2->setText("(cos(u) * sin(2 * v))") ;
  wcft_2->setText("cos(u)") ;
  umin_2->setText("-pi/2") ; 
  umax_2->setText("pi/2") ; 
  vmin_2->setText("-pi/2") ; 
  vmax_2->setText("pi/2") ; 
  
    }     
              if(choix == QString("Cross_cap")) {
   connectWidget2->objet->two_system = -1;
   connectWidget2->objet->fourdimshapes = 1;
  xcft_2->setText("(sin(u) * sin(2 * v) / 2)");
  ycft_2->setText("(sin(2 * u) * cos(v) * cos(v))");
  zcft_2->setText("(cos(2 * u) * cos(v) * cos(v))") ;
  wcft_2->setText("cos(u)") ;
  umin_2->setText("-pi/2") ; 
  umax_2->setText("pi/2") ; 
  vmin_2->setText("-pi/2") ; 
  vmax_2->setText("pi/2") ; 

    } 
               if(choix == QString("Boys")) {
   connectWidget2->objet->two_system = -1;
   connectWidget2->objet->fourdimshapes = 1;
  xcft_2->setText("(2/3)*(cos(u)*cos(2*v)+sqrt(2)*sin(u)*cos(v))*cos(u) /(sqrt(2) - sin(2*u)*sin(3*v))");
  ycft_2->setText("(2/3)*(cos(u)*sin(2*v)-sqrt(2)*sin(u)*sin(v))*cos(u) /(sqrt(2)-sin(2*u)*sin(3*v))");
  zcft_2->setText("sqrt(2)*cos(u)^2 / (sqrt(2) - sin(2*u)*sin(2*v))") ;
  wcft_2->setText("cos(u)") ;
  umin_2->setText("-pi/2") ; 
  umax_2->setText("pi/2") ; 
  vmin_2->setText("-pi/2") ; 
  vmax_2->setText("pi/2") ; 

    }     
      
      if(choix == QString("Torus")) {
   connectWidget2->objet->two_system = -1;
   connectWidget2->objet->fourdimshapes = 1;
  xcft_2->setText("(1+ 0.5*cos(u))*cos(v)");
  ycft_2->setText("(1+ 0.5*cos(u))*sin(v)");
  zcft_2->setText("0.5*sin(u)") ;
  wcft_2->setText("cos(u)") ;
  umin_2->setText("0") ; 
  umax_2->setText("2*pi") ; 
  vmin_2->setText("0") ; 
  vmax_2->setText("2*pi") ; 

    }
      
      if(choix == QString("Klein")) {
   connectWidget2->objet->two_system = -1;   
   connectWidget2->objet->fourdimshapes = 1;
  xcft_2->setText("(3*(1+sin(v)) + 2*(1-cos(v)/2)*cos(u))*cos(v)") ;      
  ycft_2->setText("(4+2*(1-cos(v)/2)*cos(u))*sin(v)");
  zcft_2->setText("-2*(1-cos(v)/2) * sin(u)");
  wcft_2->setText("cos(u)") ; 
  umin_2->setText("0") ; 
  umax_2->setText("2*pi") ; 
  vmin_2->setText("0") ; 
  vmax_2->setText("2*pi") ;
  
    }
    

       
       if(choix == QString("Moebius")) {
   connectWidget2->objet->two_system = -1;
   connectWidget2->objet->fourdimshapes = 1;
  xcft_2->setText("cos(v)+u*cos(v/2)*cos(v)");
  ycft_2->setText("sin(v)+u*cos(v/2)*sin(v)");
  zcft_2->setText("u*sin(v/2)") ;
  wcft_2->setText("cos(u)") ;
  umin_2->setText("-0.4") ; 
  umax_2->setText("0.4") ; 
  vmin_2->setText("0") ; 
  vmax_2->setText("2*pi") ; 

    }
     
          if(choix == QString("Riemann")) {
   connectWidget2->objet->two_system = -1;
   connectWidget2->objet->fourdimshapes = 1;
  xcft_2->setText("u*v");
  ycft_2->setText("v^2 - u^2");
  zcft_2->setText("30*u") ;
  wcft_2->setText("cos(u)") ;
  umin_2->setText("-6") ; 
  umax_2->setText("6") ; 
  vmin_2->setText("-25") ; 
  vmax_2->setText("25") ; 

    }
   

   
          if(choix == QString("Klein_2")) {
   connectWidget2->objet->two_system = -1;
   connectWidget2->objet->fourdimshapes = 1;
  xcft_2->setText("(2 + cos(v/2)* sin(u) - sin(v/2)* sin(2 *u))* cos(v)");
  ycft_2->setText("(2 + cos(v/2)* sin(u) - sin(v/2)* sin(2 *u))* sin(v)");
  zcft_2->setText("sin(v/2)* sin(u) + cos(v/2) *sin(2* u)") ;
  wcft_2->setText("cos(u)") ;
  umin_2->setText("0") ; 
  umax_2->setText("2*pi") ; 
  vmin_2->setText("0") ; 
  vmax_2->setText("2*pi") ;

    }

           if(choix == QString("Henneberg")) {
   connectWidget2->objet->two_system = -1;
   connectWidget2->objet->fourdimshapes = 1;
  xcft_2->setText("2*sinh(u)*cos(v) -(2/3)*sinh(3*u)*cos(3*v)");
  ycft_2->setText("2*sinh(u)*sin(v) +(2/3)*sinh(3*u)*sin(3*v)");
  zcft_2->setText("2*cosh(2*u)*cos(2*v)") ;
  wcft_2->setText("cos(u)") ;
  umin_2->setText("-1") ; 
  umax_2->setText("1") ; 
  vmin_2->setText("-pi/2") ; 
  vmax_2->setText("pi/2") ;
  
    }

          if(choix == QString("Enneper")) {
   connectWidget2->objet->two_system = -1;
   connectWidget2->objet->fourdimshapes = 1;
  xcft_2->setText("u -u^3/3  + u*v^2");
  ycft_2->setText("v -v^3/3  + v*u^2");
  zcft_2->setText("u^2 - v^2") ;
  wcft_2->setText("cos(u)") ;
  umin_2->setText("-2") ; 
  umax_2->setText("2") ; 
  vmin_2->setText("-2") ; 
  vmax_2->setText("2") ; 
  

    }  
 
            if(choix == QString("Helix")) {
   connectWidget2->objet->two_system = -1;
   connectWidget2->objet->fourdimshapes = 1;
  xcft_2->setText("(1-0.1*cos(v))*cos(u)");
  ycft_2->setText("(1-0.1*cos(v))*sin(u)");
  zcft_2->setText("0.1*(sin(v) + u/1.7 -10)") ;
  wcft_2->setText("cos(u)") ;
  umin_2->setText("0") ; 
  umax_2->setText("4*pi") ; 
  vmin_2->setText("0") ; 
  vmax_2->setText("2*pi") ; 
  

    }  
  
           if(choix == QString("Hexaedron")) {
   connectWidget2->objet->two_system = -1;
   connectWidget2->objet->fourdimshapes = 1;
  xcft_2->setText("cos(v)^3*cos(u)^3");
  ycft_2->setText("sin(v)^3*cos(u)^3");
  zcft_2->setText("sin(u)^3") ;
  wcft_2->setText("cos(u)") ;
  umin_2->setText("-1.3") ; 
  umax_2->setText("1.3") ; 
  vmin_2->setText("0") ; 
  vmax_2->setText("2*pi") ; 
  
    }       

     
           if(choix == QString("Sphere_1")) {
   connectWidget2->objet->two_system = -1;
   connectWidget2->objet->fourdimshapes = 1;
  xcft_2->setText("cos(u)*cos(v)");
  ycft_2->setText("cos(u)*sin(v)");
  zcft_2->setText("sin(u)") ;
  wcft_2->setText("cos(u)") ;
  umin_2->setText("-pi/2") ; 
  umax_2->setText("pi/2") ; 
  vmin_2->setText("0") ; 
  vmax_2->setText("2*pi") ; 
  

    }
  
            
             if(choix == QString("Catalan")) {
   connectWidget2->objet->two_system = -1;
   connectWidget2->objet->fourdimshapes = 1;
  xcft_2->setText("u-sin(u)*cosh(v)");
  ycft_2->setText("1-cos(u)*cosh(v)");
  zcft_2->setText("4*sin(1/2*u)*sinh(v/2)") ;
  wcft_2->setText("cos(u)") ;
  umin_2->setText("-pi") ; 
  umax_2->setText("3*pi") ; 
  vmin_2->setText("-2") ; 
  vmax_2->setText("2") ; 
  
    }   
   
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
             if(choix == QString("Toupie")) {
   connectWidget2->objet->two_system = -1;
   connectWidget2->objet->fourdimshapes = 1;
  xcft_2->setText("(abs(u)-1)^2 * cos(v)");
  ycft_2->setText("(abs(u)-1)^2 * sin(v)");
  zcft_2->setText("u") ;
  wcft_2->setText("cos(u)") ;
  umin_2->setText("-1") ; 
  umax_2->setText("1") ; 
  vmin_2->setText("0") ; 
  vmax_2->setText("2*pi") ; 

    }
  
              if(choix == QString("Bonbon")) {
   connectWidget2->objet->two_system = -1;
   connectWidget2->objet->fourdimshapes = 1;
  xcft_2->setText("u");
  ycft_2->setText("cos (u)*cos (v)");
  zcft_2->setText("cos (u)*sin (v)") ;
  wcft_2->setText("cos(u)") ;
  umin_2->setText("0") ; 
  umax_2->setText("2*pi") ; 
  vmin_2->setText("0") ; 
  vmax_2->setText("2*pi") ; 

    }   
  
              if(choix == QString("Curve")) {
   connectWidget2->objet->two_system = -1;
   connectWidget2->objet->fourdimshapes = 1;
  xcft_2->setText("cos(2*u)");
  ycft_2->setText("sin(3*u)");
  zcft_2->setText("cos(u)") ;
  wcft_2->setText("cos(u)") ;
  umin_2->setText("0") ; 
  umax_2->setText("2*pi") ; 
  vmin_2->setText("0") ; 
  vmax_2->setText("0") ; 
  
    }   
    
    
    
                 if(choix == QString("Trumpet")) {
   connectWidget2->objet->two_system = -1;
   connectWidget2->objet->fourdimshapes = 1;
  xcft_2->setText("cos(u)*sin(v)");
  ycft_2->setText("sin(u)*sin(v)");
  zcft_2->setText("(cos(v)+log(tan(1/2*v)))") ;
  wcft_2->setText("cos(u)") ;
  umin_2->setText("0") ; 
  umax_2->setText("2*pi") ; 
  vmin_2->setText("0.03") ; 
  vmax_2->setText("2") ; 
  
    } 
    
 
     
                 if(choix == QString("Helice_Curve")) {
   connectWidget2->objet->two_system = -1;
   connectWidget2->objet->fourdimshapes = 1;
  xcft_2->setText("sin(u)");
  ycft_2->setText("cos(u)");
  zcft_2->setText("(u^2)/100") ;
  wcft_2->setText("cos(u)") ;
  umin_2->setText("0") ; 
  umax_2->setText("6*pi") ; 
  vmin_2->setText("0") ; 
  vmax_2->setText("0") ; 
  
    }    
    



                   if(choix == QString("Cresent")) {
   connectWidget2->objet->two_system = -1;
   connectWidget2->objet->fourdimshapes = 1;
  xcft_2->setText("(2 + sin(2* pi* u) *sin(2 *pi* v)) *sin(3* pi *v)");
  ycft_2->setText("(2 + sin(2* pi *u) *sin(2 *pi *v)) *cos(3* pi *v)");
  zcft_2->setText("cos(2* pi *u) *sin(2* pi* v) + 4 *v - 2") ;
  wcft_2->setText("cos(u)") ;
  umin_2->setText("0") ; 
  umax_2->setText("1") ; 
  vmin_2->setText("0") ; 
  vmax_2->setText("1") ; 

    } 
    
    

 
 
 
                  if(choix == QString("Shoe")) {
   connectWidget2->objet->two_system = -1;
   connectWidget2->objet->fourdimshapes = 1;
  xcft_2->setText("u");
  ycft_2->setText("v");
  zcft_2->setText("1/3*u^3  - 1/2*v^2") ;
  wcft_2->setText("cos(u)") ;
  umin_2->setText("-2") ; 
  umax_2->setText("2") ; 
  vmin_2->setText("-2") ; 
  vmax_2->setText("2") ; 
  
    } 
                 if(choix == QString("Snake")) {
   connectWidget2->objet->two_system = -1;
   connectWidget2->objet->fourdimshapes = 1;
  xcft_2->setText("1.2*(1 -v/(2*pi))*cos(3*v)*(1 + cos(u)) + 3*cos(3*v)");
  ycft_2->setText("1.2*(1 -v/(2*pi))*sin(3*v)*(1 + cos(u)) + 3*sin(3*v)");
  zcft_2->setText("9*v/(2*pi) + 1.2*(1 - v/(2*pi))*sin(u)") ;
  wcft_2->setText("cos(u)") ;
  umin_2->setText("0") ; 
  umax_2->setText("2*pi") ; 
  vmin_2->setText("0") ; 
  vmax_2->setText("2*pi") ; 
  
    }     
    
    
                  if(choix == QString("Roman")) {
   connectWidget2->objet->two_system = -1;
   connectWidget2->objet->fourdimshapes = 1;
  xcft_2->setText("1/2*sin(2*u)*sin(v)^2");
  ycft_2->setText("1/2*sin(u)*cos(2*v)");
  zcft_2->setText("1/2*cos(u)*sin(2*v)") ;
  wcft_2->setText("cos(u)") ;
  umin_2->setText("0") ; 
  umax_2->setText("pi") ; 
  vmin_2->setText("-pi/2") ; 
  vmax_2->setText("pi/2") ; 

    } 
    
                    if(choix == QString("Hyperhelicoidal")) {
   connectWidget2->objet->two_system = -1;
   connectWidget2->objet->fourdimshapes = 1;
  xcft_2->setText("(sinh(v)*cos(3*u))/(1+cosh(u)*cosh(v))");
  ycft_2->setText("(sinh(v)*sin(3*u))/(1+cosh(u)*cosh(v))");
  zcft_2->setText("(cosh(v)*sinh(u))/(1+cosh(u)*cosh(v))") ;
  wcft_2->setText("cos(u)") ;
  umin_2->setText("-pi") ; 
  umax_2->setText("pi") ; 
  vmin_2->setText("-pi") ; 
  vmax_2->setText("pi") ; 
  
    }
    

  
                    if(choix == QString("Horn")) {
   connectWidget2->objet->two_system = -1;
   connectWidget2->objet->fourdimshapes = 1;
  xcft_2->setText("(2 + u*cos(v))*sin(2*pi*u)");
  ycft_2->setText("(2 + u*cos(v))*cos(2*pi*u) + 2*u");
  zcft_2->setText("u *sin(v)") ;
  wcft_2->setText("cos(u)") ;
  umin_2->setText("0") ; 
  umax_2->setText("1") ; 
  vmin_2->setText("0") ; 
  vmax_2->setText("2*pi") ; 

    }
  
  
    
                   if(choix == QString("Helicoidal")) {
   connectWidget2->objet->two_system = -1;
   connectWidget2->objet->fourdimshapes = 1;
  xcft_2->setText("sinh(v)*sin(u)");
  ycft_2->setText("-sinh(v)*cos(u)");
  zcft_2->setText("3*u") ;
  wcft_2->setText("cos(u)") ;
  umin_2->setText("-pi") ; 
  umax_2->setText("pi") ; 
  vmin_2->setText("-pi") ; 
  vmax_2->setText("pi") ; 
  
    }   
                    if(choix == QString("Catenoid")) {
   connectWidget2->objet->two_system = -1;
   connectWidget2->objet->fourdimshapes = 1;
  xcft_2->setText("2*cosh(v/2)*cos(u)");
  ycft_2->setText("2*cosh(v/2)*sin(u)");
  zcft_2->setText("v") ;
  wcft_2->setText("cos(u)") ;
  umin_2->setText("-pi") ; 
  umax_2->setText("pi") ; 
  vmin_2->setText("-pi") ; 
  vmax_2->setText("pi") ; 
  
    }  
                   if(choix == QString("Kuen")) {
   connectWidget2->objet->two_system = -1;
   connectWidget2->objet->fourdimshapes = 1;
  xcft_2->setText("(2*(cos(u) + u*sin(u))*sin(v))/(1+ u^2*sin(v)^2)");
  ycft_2->setText("(2*(sin(u) - u*cos(u))*sin(v))/(1+ u^2*sin(v)^2)");
  zcft_2->setText("log(tan(1/2 *v)) + (2*cos(v))/(1+ u^2*sin(v)^2)") ;
  wcft_2->setText("cos(u)") ;
  umin_2->setText("0") ; 
  umax_2->setText("2*pi") ; 
  vmin_2->setText("0.01") ; 
  vmax_2->setText("pi-0.01") ; 
    }   


                    if(choix == QString("Hellipticparaboloid")) {
   connectWidget2->objet->two_system = -1;
   connectWidget2->objet->fourdimshapes = 1;
  xcft_2->setText("v*2*cos(u)");
  ycft_2->setText("v*sin(u)");
  zcft_2->setText("v^2") ;
  wcft_2->setText("cos(u)") ;
  umin_2->setText("0") ; 
  umax_2->setText("2*pi") ; 
  vmin_2->setText("0") ; 
  vmax_2->setText("2") ; 
    }


                    if(choix == QString("Enneper_2")) {
   connectWidget2->objet->two_system = -1;
   connectWidget2->objet->fourdimshapes = 1;
  xcft_2->setText("u*cos(v)-u^3/3*cos(3*v)");
  ycft_2->setText("-u*sin(v)-u^(3)/3*sin(3*v)");
  zcft_2->setText("u^2*cos(2*v)") ;
  wcft_2->setText("cos(u)") ;
  umin_2->setText("0") ; 
  umax_2->setText("1.2") ; 
  vmin_2->setText("-pi") ; 
  vmax_2->setText("pi") ; 
    } 
   
                    if(choix == QString("Stereosphere")) {
   connectWidget2->objet->two_system = -1;
   connectWidget2->objet->fourdimshapes = 1;
  xcft_2->setText("2.*u/(u*u+v*v+1.)");
  ycft_2->setText("2.*v/(u*u+v*v+1.)");
  zcft_2->setText("(u*u+v*v-1.)/(u*u+v*v+1.)") ;
  wcft_2->setText("cos(u)") ;
  umin_2->setText("-2") ; 
  umax_2->setText("2") ; 
  vmin_2->setText("-2") ; 
  vmax_2->setText("2") ; 

    }

                    if(choix == QString("Cliffordtorus")) {
   connectWidget2->objet->two_system = -1;
   connectWidget2->objet->fourdimshapes = 1;
  xcft_2->setText("cos(u+v)/(sqrt(2.)+cos(v-u))");
  ycft_2->setText("sin(u+v)/(sqrt(2.)+cos(v-u))");
  zcft_2->setText("sin(v-u)/(sqrt(2.)+cos(v-u))");
  wcft_2->setText("cos(u)") ;
  umin_2->setText("0") ; 
  umax_2->setText("pi") ; 
  vmin_2->setText("0") ; 
  vmax_2->setText("2*pi") ; 

    }   

  
 
                    if(choix == QString("Fresnel_1")) {
   connectWidget2->objet->two_system = -1;
   connectWidget2->objet->fourdimshapes = 1;
  xcft_2->setText("cos(u)*cos(v)/(-2.*sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))*cos((acos(-(-0.941/6.+0.374*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4)-1.309/6.*((cos(u)^6+sin(u)^6)*cos(v)^6+sin(v)^6)-1.221*cos(u)^2*cos(v)^4*sin(u)^2*sin(v)^2)/sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))^3)+pi)/3.)+0.8)");
  ycft_2->setText("sin(u)*cos(v)/(-2.*sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))*cos((acos(-(-0.941/6.+0.374*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4)-1.309/6.*((cos(u)^6+sin(u)^6)*cos(v)^6+sin(v)^6)-1.221*cos(u)^2*cos(v)^4*sin(u)^2*sin(v)^2)/sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))^3)+pi)/3.)+0.8)");
  zcft_2->setText("sin(v)/(-2.*sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))*cos((acos(-(-0.941/6.+0.374*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4)-1.309/6.*((cos(u)^6+sin(u)^6)*cos(v)^6+sin(v)^6)-1.221*cos(u)^2*cos(v)^4*sin(u)^2*sin(v)^2)/sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))^3)+pi)/3.)+0.8)") ;
  wcft_2->setText("cos(u)") ;
  umin_2->setText("0") ; 
  umax_2->setText("2*pi") ; 
  vmin_2->setText("-pi/2") ; 
  vmax_2->setText("pi/2") ; 

    }   
    
  
                    if(choix == QString("Fresnel_2")) {
   connectWidget2->objet->two_system = -1;
   connectWidget2->objet->fourdimshapes = 1;
  xcft_2->setText("cos(u)*cos(v)/(-2.*sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))*cos((acos(-(-0.941/6.+0.374*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4)-1.309/6.*((cos(u)^6+sin(u)^6)*cos(v)^6+sin(v)^6)-1.221*cos(u)^2*cos(v)^4*sin(u)^2*sin(v)^2)/sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))^3)-pi)/3.)+0.8)");
  ycft_2->setText("sin(u)*cos(v)/(-2.*sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))*cos((acos(-(-0.941/6.+0.374*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4)-1.309/6.*((cos(u)^6+sin(u)^6)*cos(v)^6+sin(v)^6)-1.221*cos(u)^2*cos(v)^4*sin(u)^2*sin(v)^2)/sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))^3)-pi)/3.)+0.8)");
  zcft_2->setText("sin(v)/(-2.*sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))*cos((acos(-(-0.941/6.+0.374*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4)-1.309/6.*((cos(u)^6+sin(u)^6)*cos(v)^6+sin(v)^6)-1.221*cos(u)^2*cos(v)^4*sin(u)^2*sin(v)^2)/sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))^3)-pi)/3.)+0.8)") ;
  wcft_2->setText("cos(u)") ;
  umin_2->setText("0") ; 
  umax_2->setText("2*pi") ; 
  vmin_2->setText("-pi/2") ; 
  vmax_2->setText("pi/2") ; 

    }

// copy the first system
  connectWidget2->objet->expression_X = xcft_2->text();
  connectWidget2->objet->expression_Y = ycft_2->text();
  connectWidget2->objet->expression_Z = zcft_2->text();
  connectWidget2->objet->expression_W = wcft_2->text();

  connectWidget2->objet->inf_u = umin_2->text();
  connectWidget2->objet->sup_u = umax_2->text();
  connectWidget2->objet->inf_v = vmin_2->text();
  connectWidget2->objet->sup_v = vmax_2->text();

  //Process the new surface :
ParametricSurfaceProcess();

}

//====================================
void k3dsurface::choice_changed( const QString & choix )
{
                        if(choix == QString("Hurricane")) {
   connectWidget2->objet->two_system = -1;
  
  xcft->setText("1 * (2*cosh(v/2)*cos(u) * cos((2.1 * (2*cosh(v/2)*sin(u) * sin((2*cosh(v/2)*cos(u) - -5.01836)*2*pi*0/10.0367) + 2*(v) * cos((2*cosh(v/2)*cos(u) - -5.01836)*2*pi*0/10.0367))   - -13.1947)*2*pi*1.5/26.3894) - 2.1 * (2*cosh(v/2)*sin(u) * cos((2*cosh(v/2)*cos(u) - -5.01836)*2*pi*0/10.0367) - 2*(v) * sin((2*cosh(v/2)*cos(u) - -5.01836)*2*pi*0/10.0367))   * sin((2.1 * (2*cosh(v/2)*sin(u) * sin((2*cosh(v/2)*cos(u) - -5.01836)*2*pi*0/10.0367) + 2*(v) * cos((2*cosh(v/2)*cos(u) - -5.01836)*2*pi*0/10.0367))   - -13.1947)*2*pi*1.5/26.3894))");
  
  ycft->setText("1 * (2*cosh(v/2)*cos(u) * sin((2.1 * (2*cosh(v/2)*sin(u) * sin((2*cosh(v/2)*cos(u) - -5.01836)*2*pi*0/10.0367) + 2*(v) * cos((2*cosh(v/2)*cos(u) - -5.01836)*2*pi*0/10.0367))   - -13.1947)*2*pi*1.5/26.3894) + 2.1 * (2*cosh(v/2)*sin(u) * cos((2*cosh(v/2)*cos(u) - -5.01836)*2*pi*0/10.0367) - 2*(v) * sin((2*cosh(v/2)*cos(u) - -5.01836)*2*pi*0/10.0367))   * cos((2.1 * (2*cosh(v/2)*sin(u) * sin((2*cosh(v/2)*cos(u) - -5.01836)*2*pi*0/10.0367) + 2*(v) * cos((2*cosh(v/2)*cos(u) - -5.01836)*2*pi*0/10.0367))   - -13.1947)*2*pi*1.5/26.3894)) ");
  
  zcft->setText("2.1 * (2*cosh(v/2)*sin(u) * sin((2*cosh(v/2)*cos(u) - -5.01836)*2*pi*0/10.0367) + 2*(v) * cos((2*cosh(v/2)*cos(u) - -5.01836)*2*pi*0/10.0367))  ") ;
  
  umin->setText("-pi") ; 
  umax->setText("pi") ; 
  vmin->setText("-pi") ; 
  vmax->setText("pi") ; 
  
  xcft_3->setText("") ;  
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ; 
  umax_3->setText("") ; 
  vmin_3->setText("") ; 
  vmax_3->setText("") ;  
    } 
               else         if(choix == QString("Pseudo_Torus")) {
   connectWidget2->objet->two_system = -1;
  
  xcft->setText("(1+ 0.5*cos(u))*cos(v)");
  
  ycft->setText("0.632456 * ((1+ 0.5*cos(u))*sin(v) * cos(((1+ 0.5*cos(u))*cos(v) - -1.5)*2*pi*0.9/3) - 0.5*sin(u) * sin(((1+ 0.5*cos(u))*cos(v) - -1.5)*2*pi*0.9/3))  ");
  
  zcft->setText(" 0.632456 * ((1+ 0.5*cos(u))*sin(v) * sin(((1+ 0.5*cos(u))*cos(v) - -1.5)*2*pi*0.9/3) + 0.5*sin(u) * cos(((1+ 0.5*cos(u))*cos(v) - -1.5)*2*pi*0.9/3))") ;
  
  umin->setText("0") ; 
  umax->setText("2*pi") ; 
  vmin->setText("0") ; 
  vmax->setText("2*pi") ; 
  
  xcft_3->setText("") ;  
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ; 
  umax_3->setText("") ; 
  vmin_3->setText("") ; 
  vmax_3->setText("") ;  
    } 

                        if(choix == QString("Pseudo_Cube")) {
   connectWidget2->objet->two_system = -1;
  
  xcft->setText("0.848528 * (cos(u)*cos(v)*(abs(cos(4*u/4))^100 + abs(sin(4*u/4))^100)^(-1/100)*(abs(cos(4*v/4))^100 + abs(sin(4*v/4))^100)^(-1/100) * cos((1.6*(sin(u)*(abs(cos(4*u/4))^100 + abs(sin(4*u/4))^100)^(-1/100)) - -1.6)*2*pi*0.3/3.2) - cos(u)*sin(v)*(abs(cos(4*u/4))^100 + abs(sin(4*u/4))^100)^(-1/100)*(abs(cos(4*v/4))^100 + abs(sin(4*v/4))^100)^(-1/100) * sin((1.6*(sin(u)*(abs(cos(4*u/4))^100 + abs(sin(4*u/4))^100)^(-1/100)) - -1.6)*2*pi*0.3/3.2))  ");
  
  ycft->setText("0.848528 * (cos(u)*cos(v)*(abs(cos(4*u/4))^100 + abs(sin(4*u/4))^100)^(-1/100)*(abs(cos(4*v/4))^100 + abs(sin(4*v/4))^100)^(-1/100) * sin((1.6*(sin(u)*(abs(cos(4*u/4))^100 + abs(sin(4*u/4))^100)^(-1/100)) - -1.6)*2*pi*0.3/3.2) + cos(u)*sin(v)*(abs(cos(4*u/4))^100 + abs(sin(4*u/4))^100)^(-1/100)*(abs(cos(4*v/4))^100 + abs(sin(4*v/4))^100)^(-1/100) * cos((1.6*(sin(u)*(abs(cos(4*u/4))^100 + abs(sin(4*u/4))^100)^(-1/100)) - -1.6)*2*pi*0.3/3.2))  ");
  
  zcft->setText("1.6*(sin(u)*(abs(cos(4*u/4))^100 + abs(sin(4*u/4))^100)^(-1/100))") ;
  
  umin->setText("-pi/2") ; 
  umax->setText("pi/2") ; 
  vmin->setText("0") ; 
  vmax->setText("2*pi") ; 
  
  xcft_3->setText("") ;  
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ; 
  umax_3->setText("") ; 
  vmin_3->setText("") ; 
  vmax_3->setText("") ;  
    } 

                        if(choix == QString("Pseudo_Hexagon")) {
   connectWidget2->objet->two_system = -1;
  
  xcft->setText("1.7*(cos(u)*cos(v)*(abs(cos(4*u/4))^300 + abs(sin(4*u/4))^300)^(-1/300)*(abs(cos(6*v/4))^400 + abs(sin(6*v/4))^400)^(-1/1000))");
  
  ycft->setText("0.743482 * (1.5*(cos(u)*sin(v)*(abs(cos(4*u/4))^300 + abs(sin(4*u/4))^300)^(-1/300)*(abs(cos(6*v/4))^400 + abs(sin(6*v/4))^400)^(-1/1000)) * cos((1.7*(cos(u)*cos(v)*(abs(cos(4*u/4))^300 + abs(sin(4*u/4))^300)^(-1/300)*(abs(cos(6*v/4))^400 + abs(sin(6*v/4))^400)^(-1/1000)) - -1.7)*2*pi*0.3/3.4) - 0.7*(sin(u)*(abs(cos(4*u/4))^300 + abs(sin(4*u/4))^300)^(-1/300)) * sin((1.7*(cos(u)*cos(v)*(abs(cos(4*u/4))^300 + abs(sin(4*u/4))^300)^(-1/300)*(abs(cos(6*v/4))^400 + abs(sin(6*v/4))^400)^(-1/1000)) - -1.7)*2*pi*0.3/3.4))  ");
  
  zcft->setText("0.743482 * (1.5*(cos(u)*sin(v)*(abs(cos(4*u/4))^300 + abs(sin(4*u/4))^300)^(-1/300)*(abs(cos(6*v/4))^400 + abs(sin(6*v/4))^400)^(-1/1000)) * sin((1.7*(cos(u)*cos(v)*(abs(cos(4*u/4))^300 + abs(sin(4*u/4))^300)^(-1/300)*(abs(cos(6*v/4))^400 + abs(sin(6*v/4))^400)^(-1/1000)) - -1.7)*2*pi*0.3/3.4) + 0.7*(sin(u)*(abs(cos(4*u/4))^300 + abs(sin(4*u/4))^300)^(-1/300)) * cos((1.7*(cos(u)*cos(v)*(abs(cos(4*u/4))^300 + abs(sin(4*u/4))^300)^(-1/300)*(abs(cos(6*v/4))^400 + abs(sin(6*v/4))^400)^(-1/1000)) - -1.7)*2*pi*0.3/3.4))") ;
  
  umin->setText("-pi/2") ; 
  umax->setText("pi/2") ; 
  vmin->setText("0") ; 
  vmax->setText("2*pi") ; 
  
  xcft_3->setText("") ;  
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ; 
  umax_3->setText("") ; 
  vmin_3->setText("") ; 
  vmax_3->setText("") ;  
    } 


                        if(choix == QString("Pseudo_Cone")) {
   connectWidget2->objet->two_system = -1;
  
  xcft->setText("u*cos(v)");
  
  ycft->setText("0.848528 * (u*sin(v) * cos((u*cos(v) - -1)*2*pi*1/2) - u * sin((u*cos(v) - -1)*2*pi*1/2)) ");
  
  zcft->setText("0.848528 * (u*sin(v) * sin((u*cos(v) - -1)*2*pi*1/2) + u * cos((u*cos(v) - -1)*2*pi*1/2))") ;
  
  umin->setText("-1") ; 
  umax->setText("1") ; 
  vmin->setText("0") ; 
  vmax->setText("2*pi") ; 
  
  xcft_3->setText("") ;  
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ; 
  umax_3->setText("") ; 
  vmin_3->setText("") ; 
  vmax_3->setText("") ;  
    } 


                        if(choix == QString("Pseudo_Helix")) {
   connectWidget2->objet->two_system = -1;
  
  xcft->setText("0.717627 * ((1-0.1*cos(v))*cos(u) * cos(((1-0.1*cos(v))*sin(u) - -1.1)*2*pi*0.2/2.2) - 0.1*(sin(v) + u/1.7 -10) * sin(((1-0.1*cos(v))*sin(u) - -1.1)*2*pi*0.2/2.2))  ");
  
  ycft->setText("(1-0.1*cos(v))*sin(u)");
  
  zcft->setText(" 0.717627 * ((1-0.1*cos(v))*cos(u) * sin(((1-0.1*cos(v))*sin(u) - -1.1)*2*pi*0.2/2.2) + 0.1*(sin(v) + u/1.7 -10) * cos(((1-0.1*cos(v))*sin(u) - -1.1)*2*pi*0.2/2.2))  ") ;
  
  umin->setText("0") ; 
  umax->setText("4*pi") ; 
  vmin->setText("0") ; 
  vmax->setText("2*pi") ; 
  
  xcft_3->setText("") ;  
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ; 
  umax_3->setText("") ; 
  vmin_3->setText("") ; 
  vmax_3->setText("") ;  
    } 


                        if(choix == QString("Pseudo_Sphere")) {
   connectWidget2->objet->two_system = -1;
  
  xcft->setText(" cos(u)*cos(v)+sin((sin(u)+1)*2*pi) ");
  
  ycft->setText("cos(u)*sin(v)+cos((sin(u)+1)*2*pi) ");
  
  zcft->setText(" 4*sin(u) ") ;
  
  umin->setText("-pi/2") ; 
  umax->setText("pi/2") ; 
  vmin->setText("0") ; 
  vmax->setText("2*pi") ; 
  
  xcft_3->setText("") ;  
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ; 
  umax_3->setText("") ; 
  vmin_3->setText("") ; 
  vmax_3->setText("") ;  
    } 
   
   
                        if(choix == QString("Pseudo_Catenoid")) {
   connectWidget2->objet->two_system = -1;
  
  xcft->setText(" 2.2*(2*cosh(v/2)*cos(u)) ");
  
  ycft->setText(" 1.51166 * (2*cosh(v/2)*sin(u) * cos((2.2*(2*cosh(v/2)*cos(u)) - -11.0404)*2*pi*1/22.0513) - 1.8*(v) * sin((2.2*(2*cosh(v/2)*cos(u)) - -11.0404)*2*pi*1/22.0513)) ");
  
  zcft->setText(" 1.51166 * (2*cosh(v/2)*sin(u) * sin((2.2*(2*cosh(v/2)*cos(u)) - -11.0404)*2*pi*1/22.0513) + 1.8*(v) * cos((2.2*(2*cosh(v/2)*cos(u)) - -11.0404)*2*pi*1/22.0513)) ") ;
  
  umin->setText("-pi") ; 
  umax->setText("pi") ; 
  vmin->setText("-pi") ; 
  vmax->setText("pi") ; 
  
  xcft_3->setText("") ;  
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ; 
  umax_3->setText("") ; 
  vmin_3->setText("") ; 
  vmax_3->setText("") ;  
    } 
   
                        if(choix == QString("Prism")) {
   //fctdef->setText("(abs(cos(x*y/4))^v + abs(sin(x*y/4))^t)^(-1/u)");
   connectWidget2->objet->two_system = -1;
  
  xcft->setText("cos(u)*cos(v)*(abs(cos(3*v/4))^500 + abs(sin(3*v/4))^500)^(-1/260)*(abs(cos(4*u/4))^200 + abs(sin(4*u/4))^200)^(-1/200)");
  
  ycft->setText("cos(u)*sin(v)*(abs(cos(3*v/4))^500 + abs(sin(3*v/4))^500)^(-1/260)*(abs(cos(4*u/4))^200 + abs(sin(4*u/4))^200)^(-1/200)");
  
  zcft->setText("sin(u)*(abs(cos(4*u/4))^200 + abs(sin(4*u/4))^200)^(-1/200)") ;
  umin->setText("-pi/2") ; 
  umax->setText("pi/2") ; 
  vmin->setText("0") ; 
  vmax->setText("2*pi") ; 
  
  xcft_3->setText("") ;  
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ; 
  umax_3->setText("") ; 
  vmin_3->setText("") ; 
  vmax_3->setText("") ;  
    } 
    

                        if(choix == QString("Cube")) {
   
   connectWidget2->objet->two_system = -1;
  
  xcft->setText("cos(u)*cos(v)*(abs(cos(4*u/4))^100 + abs(sin(4*u/4))^100)^(-1/100)*(abs(cos(4*v/4))^100 + abs(sin(4*v/4))^100)^(-1/100)");
  
  ycft->setText("cos(u)*sin(v)*(abs(cos(4*u/4))^100 + abs(sin(4*u/4))^100)^(-1/100)*(abs(cos(4*v/4))^100 + abs(sin(4*v/4))^100)^(-1/100)");
  
  zcft->setText("sin(u)*(abs(cos(4*u/4))^100 + abs(sin(4*u/4))^100)^(-1/100)") ;
  umin->setText("-pi/2") ; 
  umax->setText("pi/2") ; 
  vmin->setText("0") ; 
  vmax->setText("2*pi") ; 
  
  xcft_3->setText("") ;  
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ; 
  umax_3->setText("") ; 
  vmin_3->setText("") ; 
  vmax_3->setText("") ;  
    } 

                        if(choix == QString("Hexagon")) {
   connectWidget2->objet->two_system = -1;
  xcft->setText("cos(u)*cos(v)*(abs(cos(4*u/4))^300 + abs(sin(4*u/4))^300)^(-1/300)*(abs(cos(6*v/4))^400 + abs(sin(6*v/4))^400)^(-1/1000)");
  
  ycft->setText("cos(u)*sin(v)*(abs(cos(4*u/4))^300 + abs(sin(4*u/4))^300)^(-1/300)*(abs(cos(6*v/4))^400 + abs(sin(6*v/4))^400)^(-1/1000)");
  
  zcft->setText("sin(u)*(abs(cos(4*u/4))^300 + abs(sin(4*u/4))^300)^(-1/300)") ;
  umin->setText("-pi/2") ; 
  umax->setText("pi/2") ; 
  vmin->setText("0") ; 
  vmax->setText("2*pi") ; 
  
  xcft_3->setText("") ;  
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ; 
  umax_3->setText("") ; 
  vmin_3->setText("") ; 
  vmax_3->setText("") ;  
    } 
        
    
                        if(choix == QString("Cone")) {
   connectWidget2->objet->two_system = -1;
  xcft->setText("cos(u)*cos(v)*(abs(cos(4*u/4))^1 + abs(sin(4*u/4))^1)^(-1/1)*(abs(cos(4*v/4))^1 + abs(sin(4*v/4))^1)^(-1/100)");
  
  ycft->setText("cos(u)*sin(v)*(abs(cos(4*u/4))^1 + abs(sin(4*u/4))^1)^(-1/1)*(abs(cos(4*v/4))^1 + abs(sin(4*v/4))^1)^(-1/100)");
  
  zcft->setText("sin(u)*(abs(cos(4*u/4))^1 + abs(sin(4*u/4))^1)^(-1/1)") ;
  umin->setText("-pi/2") ; 
  umax->setText("pi/2") ; 
  vmin->setText("0") ; 
  vmax->setText("2*pi") ; 
  
  xcft_3->setText("") ;  
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ; 
  umax_3->setText("") ; 
  vmin_3->setText("") ; 
  vmax_3->setText("") ;  
    } 
        
    
                         if(choix == QString("Diamond")) {
    connectWidget2->objet->two_system = -1;
  xcft->setText("cos(u)*cos(v)*(abs(cos(4*u/4))^1 + abs(sin(4*u/4))^1)^(-1/1)*(abs(cos(4*v/4))^1 + abs(sin(4*v/4))^1)^(-1/1)");
  
  ycft->setText("cos(u)*sin(v)*(abs(cos(4*u/4))^1 + abs(sin(4*u/4))^1)^(-1/1)*(abs(cos(4*v/4))^1 + abs(sin(4*v/4))^1)^(-1/1)");
  
  zcft->setText("sin(u)*(abs(cos(4*u/4))^1 + abs(sin(4*u/4))^1)^(-1/1)") ;
  umin->setText("-pi/2") ; 
  umax->setText("pi/2") ; 
  vmin->setText("0") ; 
  vmax->setText("2*pi") ; 
  
  xcft_3->setText("") ;  
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ; 
  umax_3->setText("") ; 
  vmin_3->setText("") ; 
  vmax_3->setText("") ;  
    }

       
                         if(choix == QString("Shape_10")) {
     connectWidget2->objet->two_system = -1;
  xcft->setText("cos(u)*cos(v)*(abs(cos(3*u/4))^1 + abs(sin(3*u/4))^1)^(-1/1)*(abs(cos(6*v/4))^1 + abs(sin(6*v/4))^1)^(-1/1)");
  
  ycft->setText("cos(u)*sin(v)*(abs(cos(3*u/4))^1 + abs(sin(3*u/4))^1)^(-1/1)*(abs(cos(6*v/4))^1 + abs(sin(6*v/4))^1)^(-1/1)");
  
  zcft->setText("sin(u)*(abs(cos(3*u/4))^1 + abs(sin(3*u/4))^1)^(-1/1)") ;
  umin->setText("-pi/2") ; 
  umax->setText("pi/2") ; 
  vmin->setText("0") ; 
  vmax->setText("2*pi") ; 
  
  xcft_3->setText("") ;  
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ; 
  umax_3->setText("") ; 
  vmin_3->setText("") ; 
  vmax_3->setText("") ;  
    }
       
                         if(choix == QString("Star_7")) {

   connectWidget2->objet->two_system = -1;

  xcft->setText("cos(u)*cos(v)*(abs(cos(7*v/4))^1.7 + abs(sin(7*v/4))^1.7)^(-1/0.2)*(abs(cos(7*u/4))^1.7 + abs(sin(7*u/4))^1.7)^(-1/0.2)");
  
  ycft->setText("cos(u)*sin(v)*(abs(cos(7*v/4))^1.7 + abs(sin(7*v/4))^1.7)^(-1/0.2)*(abs(cos(7*u/4))^1.7 + abs(sin(7*u/4))^1.7)^(-1/0.2)");
  
  zcft->setText("sin(u)*(abs(cos(7*u/4))^1.7 + abs(sin(7*u/4))^1.7)^(-1/0.2)") ;
  umin->setText("-pi/2") ; 
  umax->setText("pi/2") ; 
  vmin->setText("0") ; 
  vmax->setText("2*pi") ; 
  
  xcft_3->setText("") ;  
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ; 
  umax_3->setText("") ; 
  vmin_3->setText("") ; 
  vmax_3->setText("") ;  
    } 
      
                         if(choix == QString("Shape_8")) {
   connectWidget2->objet->two_system = -1;

  xcft->setText("cos(u)*cos(v)*(abs(cos(3*u/4))^100 + abs(sin(3*u/4))^100)^(-1/100)*(abs(cos(2*v/4))^0.3 + abs(sin(2*v/4))^0.2)^(-1/0.7)"); 
  ycft->setText("cos(u)*sin(v)*(abs(cos(3*u/4))^100 + abs(sin(3*u/4))^100)^(-1/100)*(abs(cos(2*v/4))^0.3 + abs(sin(2*v/4))^0.2)^(-1/0.7)"); 
  zcft->setText("sin(u)*(abs(cos(3*u/4))^100 + abs(sin(3*u/4))^100)^(-1/100)"); 

  umin->setText("-pi/2") ; 
  umax->setText("pi/2") ; 
  vmin->setText("0") ; 
  vmax->setText("2*pi") ; 
  
  xcft_3->setText("") ;  
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ; 
  umax_3->setText("") ; 
  vmin_3->setText("") ; 
  vmax_3->setText("") ;  
    } 
       
                         if(choix == QString("Shape_9")) {
   connectWidget2->objet->two_system = -1;
  xcft->setText("cos(u)*cos(v)*(abs(cos(2*u/4))^10 + abs(sin(2*u/4))^10)^(-1/10)*(abs(cos(8*v/4))^100 + abs(sin(8*v/4))^30)^(-1/60)");  
  ycft->setText("cos(u)*sin(v)*(abs(cos(2*u/4))^10 + abs(sin(2*u/4))^10)^(-1/10)*(abs(cos(8*v/4))^100 + abs(sin(8*v/4))^30)^(-1/60)"); 
  zcft->setText("sin(u)*(abs(cos(2*u/4))^10 + abs(sin(2*u/4))^10)^(-1/10)") ;
  umin->setText("-pi/2") ; 
  umax->setText("pi/2") ; 
  vmin->setText("0") ; 
  vmax->setText("2*pi") ; 
  
  xcft_3->setText("") ;  
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ; 
  umax_3->setText("") ; 
  vmin_3->setText("") ; 
  vmax_3->setText("") ;  
    } 
       
                          if(choix == QString("Star")) {

   connectWidget2->objet->two_system = -1;
  xcft->setText("cos(u)*cos(v)*(abs(cos(1*u/4))^0.5 + abs(sin(1*u/4))^0.5)^(-1/0.3)*(abs(cos(5*v/4))^1.7 + abs(sin(5*v/4))^1.7)^(-1/0.1)");
  
  ycft->setText("cos(u)*sin(v)*(abs(cos(1*u/4))^0.5 + abs(sin(1*u/4))^0.5)^(-1/0.3)*(abs(cos(5*v/4))^1.7 + abs(sin(5*v/4))^1.7)^(-1/0.1)");
  
  zcft->setText("sin(u)*(abs(cos(1*u/4))^0.5 + abs(sin(1*u/4))^0.5)^(-1/0.3)") ;
  umin->setText("-pi/2") ; 
  umax->setText("pi/2") ; 
  vmin->setText("0") ; 
  vmax->setText("2*pi") ; 
  
  xcft_3->setText("") ;  
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ; 
  umax_3->setText("") ; 
  vmin_3->setText("") ; 
  vmax_3->setText("") ;  
    }    
            


                        if(choix == QString("Implicit_Lemniscape")) {
   connectWidget2->objet->two_system = -1;
  xcft->setText("cos(v)*sqrt(abs(sin(2*u)))*cos(u)");
  ycft->setText("cos(v)*sqrt(abs(sin(2*u)))*sin(u)");
  zcft->setText("x^2 - y^2 + 2*x*y*(tan(v)^2)") ;
  umin->setText("0") ; 
  umax->setText("pi") ; 
  vmin->setText("0") ; 
  vmax->setText("pi") ; 
  
  xcft_3->setText("") ;  
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ; 
  umax_3->setText("") ; 
  vmin_3->setText("") ; 
  vmax_3->setText("") ;  
    } 
    

                        if(choix == QString("Twisted_heart")) {
   connectWidget2->objet->two_system = -1;
  xcft->setText("( abs(v) - abs(u) - abs(tanh((1/sqrt(2))*u)/(1/sqrt(2))) + abs(tanh((1/sqrt(2))*v)/(1/sqrt(2))) )*sin(v)");
  ycft->setText("( abs(v) - abs(u) - abs(tanh((1/sqrt(2))*u)/(1/sqrt(2))) - abs(tanh((1/sqrt(2))*v)/(1/sqrt(2))) )*cos(v)");
  zcft->setText("(1/sqrt(2))*( u^2 + v^2 ) / ( cosh((1/sqrt(2))*u)*cosh((1/sqrt(2))*v) )") ;
  umin->setText("0") ; 
  umax->setText("pi") ; 
  vmin->setText("-pi") ; 
  vmax->setText("pi") ;
  
  xcft_3->setText("") ;  
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ; 
  umax_3->setText("") ; 
  vmin_3->setText("") ; 
  vmax_3->setText("") ;  
    } 
  
    
                        if(choix == QString("Folium")) {
   connectWidget2->objet->two_system = -1;
  xcft->setText("cos(u) *(2*v/pi - tanh(v))");
  ycft->setText("cos(u + 2*pi / 3) / cosh(v)");
  zcft->setText("cos(u - 2*pi / 3) / cosh(v)") ;
  umin->setText("-pi") ; 
  umax->setText("pi") ; 
  vmin->setText("-pi") ; 
  vmax->setText("pi") ;  
  
  xcft_3->setText("") ;  
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ; 
  umax_3->setText("") ; 
  vmin_3->setText("") ; 
  vmax_3->setText("") ;  
    }   

    
                        if(choix == QString("Heart")) {
   connectWidget2->objet->two_system = -1;
  xcft->setText("cos(u)*(4*sqrt(1-v^2)*sin(abs(u))^abs(u))");
  ycft->setText("sin(u) *(4*sqrt(1-v^2)*sin(abs(u))^abs(u))");
  zcft->setText("v") ;
  umin->setText("-pi") ; 
  umax->setText("pi") ; 
  vmin->setText("-1") ; 
  vmax->setText("1") ;  
  
  xcft_3->setText("") ;  
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ; 
  umax_3->setText("") ; 
  vmin_3->setText("") ; 
  vmax_3->setText("") ;  
    }
                        
   
   
   
   if(choix == QString("Bow_Tie")) {
   connectWidget2->objet->two_system = -1;
  xcft->setText("sin(u) / (sqrt(2) + sin(v))");
  ycft->setText("sin(u) / (sqrt(2) + sin(v))");
  zcft->setText("cos(u) / (1 + sqrt(2))") ;
  umin->setText("-pi") ; 
  umax->setText("pi") ; 
  vmin->setText("-pi") ; 
  vmax->setText("pi") ;  
  
  xcft_3->setText("") ;  
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ; 
  umax_3->setText("") ; 
  vmin_3->setText("") ; 
  vmax_3->setText("") ;  
    } 
    

                        if(choix == QString("Triaxial_Hexatorus")) {
   connectWidget2->objet->two_system = -1;
  xcft->setText("sin(u) / (sqrt(2) + cos(v))");
  ycft->setText("sin(u+2*pi/3) / (sqrt(2) + cos(v+2*pi/3))");
  zcft->setText("cos(u-2*pi/3) / (sqrt(2) + cos(v-2*pi/3))") ;
  umin->setText("-pi") ; 
  umax->setText("pi") ; 
  vmin->setText("-pi") ; 
  vmax->setText("pi") ;
    
  xcft_3->setText("") ;  
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ; 
  umax_3->setText("") ; 
  vmin_3->setText("") ; 
  vmax_3->setText("") ;  
    }


                        if(choix == QString("Ghost_Plane")) {
   connectWidget2->objet->two_system = -1;
  xcft->setText("cos(u)*sinh(v) / (cosh(v) - cos(u))");
  ycft->setText("cos(u)*sin(u) / (cosh(v) - cos(u))");
  zcft->setText("sin(u)") ;
  umin->setText("-pi") ; 
  umax->setText("pi") ; 
  vmin->setText("-pi") ; 
  vmax->setText("pi") ; 
  
  xcft_3->setText("") ;  
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("-pi") ; 
  umax_3->setText("pi") ; 
  vmin_3->setText("-pi") ; 
  vmax_3->setText("pi") ;  
    }


                        if(choix == QString("Bent_Horns")) {
   connectWidget2->objet->two_system = -1;
  xcft->setText("(2 + cos(u))*(v/3 - sin(v))");
  ycft->setText("(2 + cos(u - 2*pi / 3)) *(cos(v) - 1) ");
  zcft->setText("(2 + cos(u + 2*pi / 3))*(cos(v) - 1) ") ;
  umin->setText("-pi") ; 
  umax->setText("pi") ; 
  vmin->setText("-2*pi") ; 
  vmax->setText("2*pi") ; 
  
  xcft_3->setText("") ;  
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("-pi") ; 
  umax_3->setText("pi") ; 
  vmin_3->setText("-2*pi") ; 
  vmax_3->setText("2*pi") ;  
    }


                        if(choix == QString("Richmond")) {
   connectWidget2->objet->two_system = -1;
  xcft->setText("(-3* u - u*5 + 2*u^3*v^2 + 3*u*v^4) / (6*(u*u + v*v))");
  ycft->setText("(-3*v - 3*u^4*v - 2*u^2*v^3 + v^5) / (6*(u*u + v*v))");
  zcft->setText("u") ;
  umin->setText("-pi") ; 
  umax->setText("pi") ; 
  vmin->setText("-pi") ; 
  vmax->setText("pi") ; 
  
  xcft_3->setText("") ;  
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("-pi") ; 
  umax_3->setText("pi") ; 
  vmin_3->setText("-pi") ; 
  vmax_3->setText("pi") ;  
    } 


                        if(choix == QString("Kidney")) {
   connectWidget2->objet->two_system = -1;
  xcft->setText("cos(u) *(3  *cos(v) - cos(3  *v))");
  ycft->setText("sin(u)  *(3  *cos(v) - cos(3 * v))");
  zcft->setText("3  *sin(v) - sin(3 * v)") ;
  umin->setText("0") ; 
  umax->setText("2*pi") ; 
  vmin->setText("-pi/2") ; 
  vmax->setText("pi/2") ; 
  
  xcft_3->setText("") ;  
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("0") ; 
  umax_3->setText("2*pi") ; 
  vmin_3->setText("-pi/2") ; 
  vmax_3->setText("pi/2") ;  
    } 


                        if(choix == QString("Kinky_Torus")) {
   connectWidget2->objet->two_system = -1;
  xcft->setText("1/cosh(u) - cos(v)");
  ycft->setText("sin(v)");
  zcft->setText("u / pi - tanh(v)") ;
  umin->setText("-2*pi") ;
  umax->setText("2*pi") ;
  vmin->setText("-pi") ;
  vmax->setText("pi") ;

  xcft_3->setText("") ;
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ;
  umax_3->setText("") ;
  vmin_3->setText("") ;
  vmax_3->setText("") ;
    }


                        if(choix == QString("Snail")) {
   connectWidget2->objet->two_system = -1;
  xcft->setText("u*cos(v)*sin(u)");
  ycft->setText("u*cos(u)*cos(v)");
  zcft->setText("-u*sin(v)") ;
  umin->setText("0") ;
  umax->setText("2") ;
  vmin->setText("-pi/2") ;
  vmax->setText("pi/2") ;

  xcft_3->setText("") ;
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("0") ;
  umax_3->setText("2") ;
  vmin_3->setText("-pi/2") ;
  vmax_3->setText("pi/2") ;
    }

                        if(choix == QString("Limpet_Torus")) {
   connectWidget2->objet->two_system = -1;
  xcft->setText("cos(u) / (sqrt(2) + sin(v))");
  ycft->setText("sin(u) / (sqrt(2) + sin(v))");
  zcft->setText("1 / (sqrt(2) + cos(v))") ;
  umin->setText("-pi") ;
  umax->setText("pi") ;
  vmin->setText("-pi") ;
  vmax->setText("pi") ;

  xcft_3->setText("") ;
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("-pi") ;
  umax_3->setText("pi") ;
  vmin_3->setText("-pi") ;
  vmax_3->setText("pi") ;
    }

      if(choix == QString("Twisted_Triaxial")) {
   connectWidget2->objet->two_system = -1;
  xcft->setText("(1-sqrt(u*u + v*v) / sqrt(2*pi*pi))*cos(u)*cos(v)+sqrt(u*u + v*v) / sqrt(2*pi*pi)*sin(u)*sin(v)");
  ycft->setText("(1-sqrt(u*u + v*v) / sqrt(2*pi*pi))*cos(u+2*pi/3)*cos(v+2*pi/3)+sqrt(u*u + v*v) / sqrt(2*pi*pi)*sin(u+2*pi/3)*sin(v+2*pi/3)") ;
  zcft->setText(" (1-sqrt(u*u + v*v) / sqrt(2*pi*pi))*cos(u+4*pi/3)*cos(v+4*pi/3)+sqrt(u*u + v*v) / sqrt(2*pi*pi)*sin(u+4*pi/3)*sin(v+4*pi/3)") ;
  umin->setText("-pi") ;
  umax->setText("pi") ;
  vmin->setText("-pi") ;
  vmax->setText("pi") ;

  xcft_3->setText("") ;
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("-pi") ;
  umax_3->setText("pi") ;
  vmin_3->setText("-pi") ;
  vmax_3->setText("pi") ;
    }

                        if(choix == QString("Apple")) {
   connectWidget2->objet->two_system = -1;
  xcft->setText("cos(u) *(4 + 3.8* cos(v))");
  ycft->setText("sin(u) *(4 + 3.8* cos(v))");
  zcft->setText("(cos(v) + sin(v) - 1)* (1 + sin(v)) *log(1 - pi *v / 10) + 7.5 *sin(v)") ;
  umin->setText("0") ;
  umax->setText("2*pi") ;
  vmin->setText("-pi") ;
  vmax->setText("pi") ;

  xcft_3->setText("") ;
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("0") ;
  umax_3->setText("2*pi") ;
  vmin_3->setText("-pi") ;
  vmax_3->setText("pi") ;
    }

                        if(choix == QString("Boy")) {
   connectWidget2->objet->two_system = -1;
  xcft->setText("2/3* (cos(u)* cos(2*v) + sqrt(2)* sin(u)* cos(v))* cos(u) / (sqrt(2) - sin(2*u)* sin(3*v))");
  ycft->setText("2/3* (cos(u)* sin(2*v) - sqrt(2)* sin(u)* sin(v))* cos(u) / (sqrt(2) - sin(2*u)* sin(3*v))");
  zcft->setText("sqrt(2)* cos(u)* cos(u) / (sqrt(2) - sin(2*u)* sin(3*v))") ;
  umin->setText("0") ;
  umax->setText("pi") ;
  vmin->setText("0") ;
  vmax->setText("pi") ;

  xcft_3->setText("") ;
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("0") ;
  umax_3->setText("pi") ;
  vmin_3->setText("0") ;
  vmax_3->setText("pi") ;
    }


                        if(choix == QString("Maeder's_Owl")) {
   connectWidget2->objet->two_system = -1;
  xcft->setText("v *cos(u) - 0.5* v^2 * cos(2* u)");
  ycft->setText("-v *sin(u) - 0.5* v^2 * sin(2* u)");
  zcft->setText("4 *v^1.5 * cos(3 *u / 2) / 3") ;
  umin->setText("0") ;
  umax->setText("4*pi") ;
  vmin->setText("0") ;
  vmax->setText("1") ;

  xcft_3->setText("") ;
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("0") ;
  umax_3->setText("4*pi") ;
  vmin_3->setText("0") ;
  vmax_3->setText("1") ;
    }


                        if(choix == QString("Cone")) {
   connectWidget2->objet->two_system = -1;
  xcft->setText("u*cos(v)");
  ycft->setText("u*sin(v)");
  zcft->setText("u") ;
  umin->setText("-1") ;
  umax->setText("1") ;
  vmin->setText("0") ;
  vmax->setText("2*pi") ;

  xcft_3->setText("") ;
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ;
  umax_3->setText("") ;
  vmin_3->setText("") ;
  vmax_3->setText("") ;
 // return;
    }

                        if(choix == QString("Eight")) {
   connectWidget2->objet->two_system = -1;
  xcft->setText("(2 + 0.2*sin(2*pi*u))*sin(pi*v)");
  ycft->setText("0.2*cos(2*pi*u) *3*cos(2*pi*v)");
  zcft->setText("(2 + 0.2*sin(2*pi*u))*cos(pi*v)") ;
  umin->setText("0") ;
  umax->setText("pi/2") ;
  vmin->setText("0") ;
  vmax->setText("3*pi/4") ;

  xcft_3->setText("") ;
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ;
  umax_3->setText("") ;
  vmin_3->setText("") ;
  vmax_3->setText("") ;
 // return;
    }

                        if(choix == QString("Drop")) {
   connectWidget2->objet->two_system = -1;
  xcft->setText("u*cos(v)");
  ycft->setText("u*sin(v)");
  zcft->setText("exp(-u*u)*(sin(2*pi*u) - u*cos(3*v))") ;
  umin->setText("0") ;
  umax->setText("2") ;
  vmin->setText("0") ;
  vmax->setText("2*pi") ;

  xcft_3->setText("") ;
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ;
  umax_3->setText("") ;
  vmin_3->setText("") ;
  vmax_3->setText("") ;
 // return;
    }

                        if(choix == QString("Plan")) {
   connectWidget2->objet->two_system = -1;
  xcft->setText("u");
  ycft->setText("0");
  zcft->setText("v") ;
  umin->setText("-1") ;
  umax->setText("1") ;
  vmin->setText("-1") ;
  vmax->setText("1") ;

  xcft_3->setText("") ;
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ;
  umax_3->setText("") ;
  vmin_3->setText("") ;
  vmax_3->setText("") ;
 // return;
    }

                        if(choix == QString("Ellipsoide")) {
   connectWidget2->objet->two_system = -1;
  xcft->setText("cos(u)*cos(v)");
  ycft->setText("sin(u)*cos(v)");
  zcft->setText("sin(v)") ;
  umin->setText("0") ;
  umax->setText("6.2831") ;
  vmin->setText("-1.57") ;
  vmax->setText("1.5708") ;

  xcft_3->setText("") ;
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ;
  umax_3->setText("") ;
  vmin_3->setText("") ;
  vmax_3->setText("") ;
 // return;
    }
                        if(choix == QString("EightSurface")) {
   connectWidget2->objet->two_system = -1;
  xcft->setText("cos(u)*sin(2*v)");
  ycft->setText("sin(u)*sin(2*v)");
  zcft->setText("sin(v)") ;
  umin->setText("0") ;
  umax->setText("2*pi") ;
  vmin->setText("-pi/2") ;
  vmax->setText("pi/2") ;

  xcft_3->setText("") ;
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ;
  umax_3->setText("") ;
  vmin_3->setText("") ;
  vmax_3->setText("") ;
 // return;
    }

                        if(choix == QString("Dini")) {
   connectWidget2->objet->two_system = -1;
  xcft->setText("cos(u)*sin(v)");
  ycft->setText("sin(u)*sin(v)");
  zcft->setText("(cos(v)+log(tan(v/2))) + 0.2*u") ;
  umin->setText("0") ;
  umax->setText("12.4") ;
  vmin->setText("0.1") ;
  vmax->setText("2") ;

  xcft_3->setText("") ;
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ;
  umax_3->setText("") ;
  vmin_3->setText("") ;
  vmax_3->setText("") ;
 // return;
    }

                        if(choix == QString("Flower")) {
   connectWidget2->objet->two_system = -1;
  xcft->setText("v *cos(u) -0.5*v^2*cos(2*u)");
  ycft->setText("-v*sin(u) -0.5*v^2*sin(2*u)");
  zcft->setText("4* v^1.5 *cos(3* u / 2) / 3") ;
  umin->setText("0") ;
  umax->setText("4*pi") ;
  vmin->setText("0") ;
  vmax->setText("1") ;

  xcft_3->setText("") ;
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ;
  umax_3->setText("") ;
  vmin_3->setText("") ;
  vmax_3->setText("") ;
 // return;
    }

    if(choix == QString("Cosinus")) {
   connectWidget2->objet->two_system = -1;
  xcft->setText("u");
  ycft->setText("v");
  zcft->setText("sin(pi*((u)^2+(v)^2))/2") ;
  umin->setText("-1") ;
  umax->setText("1") ;
  vmin->setText("-1") ;
  vmax->setText("1") ;

  xcft_3->setText("") ;
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ;
  umax_3->setText("") ;
  vmin_3->setText("") ;
  vmax_3->setText("") ;
   // return;
    }

      if(choix == QString("Shell")) {
   connectWidget2->objet->two_system = -1;
  xcft->setText("1.2^v*(sin(u)^2 *sin(v))");
  ycft->setText("1.2^v*(sin(u)^2 *cos(v))");
  zcft->setText("1.2^v*(sin(u)*cos(u))") ;
  umin->setText("0") ;
  umax->setText("pi") ;
  vmin->setText("-pi/4") ;
  vmax->setText("5*pi/2") ;

  xcft_3->setText("") ;
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ;
  umax_3->setText("") ;
  vmin_3->setText("") ;
  vmax_3->setText("") ;
   // return;
    }

           if(choix == QString("Sphere")) {
   connectWidget2->objet->two_system = -1;
  xcft->setText("cos(u)*cos(v)");
  ycft->setText("cos(u)*sin(v)");
  zcft->setText("sin(u)") ;
  umin->setText("-pi/2") ;
  umax->setText("pi/2") ;
  vmin->setText("0") ;
  vmax->setText("2*pi") ;

  xcft_3->setText("") ;
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ;
  umax_3->setText("") ;
  vmin_3->setText("") ;
  vmax_3->setText("") ;
 // return;
    }

              if(choix == QString("Steiner")) {
   connectWidget2->objet->two_system = -1;
  xcft->setText("(sin(2 * u) * cos(v) * cos(v))");
  ycft->setText("(sin(u) * sin(2 * v))");
  zcft->setText("(cos(u) * sin(2 * v))") ;
  umin->setText("-pi/2") ;
  umax->setText("pi/2") ;
  vmin->setText("-pi/2") ;
  vmax->setText("pi/2") ;

  xcft_3->setText("") ;
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ;
  umax_3->setText("") ;
  vmin_3->setText("") ;
  vmax_3->setText("") ;
 // return;
    }
              if(choix == QString("Cross_cap")) {
   connectWidget2->objet->two_system = -1;
  xcft->setText("(sin(u) * sin(2 * v) / 2)");
  ycft->setText("(sin(2 * u) * cos(v) * cos(v))");
  zcft->setText("(cos(2 * u) * cos(v) * cos(v))") ;
  umin->setText("-pi/2") ;
  umax->setText("pi/2") ;
  vmin->setText("-pi/2") ;
  vmax->setText("pi/2") ;

  xcft_3->setText("") ;
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ;
  umax_3->setText("") ;
  vmin_3->setText("") ;
  vmax_3->setText("") ;
 // return;
    }
               if(choix == QString("Boys")) {
   connectWidget2->objet->two_system = -1;
  xcft->setText("(2/3)*(cos(u)*cos(2*v)+sqrt(2)*sin(u)*cos(v))*cos(u) /(sqrt(2) - sin(2*u)*sin(3*v))");
  ycft->setText("(2/3)*(cos(u)*sin(2*v)-sqrt(2)*sin(u)*sin(v))*cos(u) /(sqrt(2)-sin(2*u)*sin(3*v))");
  zcft->setText("sqrt(2)*cos(u)^2 / (sqrt(2) - sin(2*u)*sin(2*v))") ;
  umin->setText("-pi/2") ;
  umax->setText("pi/2") ;
  vmin->setText("-pi/2") ;
  vmax->setText("pi/2") ;

  xcft_3->setText("") ;
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ;
  umax_3->setText("") ;
  vmin_3->setText("") ;
  vmax_3->setText("") ;
 // return;
    }

      if(choix == QString("Torus")) {
   connectWidget2->objet->two_system = -1;
  xcft->setText("(1+ 0.5*cos(u))*cos(v)");
  ycft->setText("(1+ 0.5*cos(u))*sin(v)");
  zcft->setText("0.5*sin(u)") ;
  umin->setText("0") ;
  umax->setText("2*pi") ;
  vmin->setText("0") ;
  vmax->setText("2*pi") ;

  xcft_3->setText("") ;
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ;
  umax_3->setText("") ;
  vmin_3->setText("") ;
  vmax_3->setText("") ;
   // return;
    }

      if(choix == QString("Klein")) {
   connectWidget2->objet->two_system = -1;
  xcft->setText("(3*(1+sin(v)) + 2*(1-cos(v)/2)*cos(u))*cos(v)") ;
  ycft->setText("(4+2*(1-cos(v)/2)*cos(u))*sin(v)");
  zcft->setText("-2*(1-cos(v)/2) * sin(u)");
  umin->setText("0") ;
  umax->setText("2*pi") ;
  vmin->setText("0") ;
  vmax->setText("2*pi") ;

/*
  xcft_3->setText("3*(1+sin(v))*cos(v) - 2*(1-cos(v)/2)*cos(u)") ;
  ycft_3->setText("4*sin(v)");
  zcft_3->setText("-2*(1-cos(v)/2)* sin(u)");
  umin_3->setText("0") ;
  umax_3->setText("2*pi") ;
  vmin_3->setText("pi") ;
  vmax_3->setText("2*pi") ;
*/
   // return;
    }

       if(choix == QString("Moebius")) {
   connectWidget2->objet->two_system = -1;
  xcft->setText("cos(v)+u*cos(v/2)*cos(v)");
  ycft->setText("sin(v)+u*cos(v/2)*sin(v)");
  zcft->setText("u*sin(v/2)") ;
  umin->setText("-0.4") ;
  umax->setText("0.4") ;
  vmin->setText("0") ;
  vmax->setText("2*pi") ;

  xcft_3->setText("") ;
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ;
  umax_3->setText("") ;
  vmin_3->setText("") ;
  vmax_3->setText("") ;
   // return;
    }

          if(choix == QString("Riemann")) {
   connectWidget2->objet->two_system = -1;
  xcft->setText("u*v");
  ycft->setText("v^2 - u^2");
  zcft->setText("30*u") ;
  umin->setText("-6") ;
  umax->setText("6") ;
  vmin->setText("-25") ;
  vmax->setText("25") ;

  xcft_3->setText("") ;
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ;
  umax_3->setText("") ;
  vmin_3->setText("") ;
  vmax_3->setText("") ;
   // return;
    }

          if(choix == QString("Klein_2")) {
   connectWidget2->objet->two_system = -1;
  xcft->setText("(2 + cos(v/2)* sin(u) - sin(v/2)* sin(2 *u))* cos(v)");
  ycft->setText("(2 + cos(v/2)* sin(u) - sin(v/2)* sin(2 *u))* sin(v)");
  zcft->setText("sin(v/2)* sin(u) + cos(v/2) *sin(2* u)") ;
  umin->setText("0") ;
  umax->setText("2*pi") ;
  vmin->setText("0") ;
  vmax->setText("2*pi") ;

  xcft_3->setText("") ;
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ;
  umax_3->setText("") ;
  vmin_3->setText("") ;
  vmax_3->setText("") ;
  //  return;
    }

           if(choix == QString("Henneberg")) {
   connectWidget2->objet->two_system = -1;
  xcft->setText("2*sinh(u)*cos(v) -(2/3)*sinh(3*u)*cos(3*v)");
  ycft->setText("2*sinh(u)*sin(v) +(2/3)*sinh(3*u)*sin(3*v)");
  zcft->setText("2*cosh(2*u)*cos(2*v)") ;
  umin->setText("-1") ;
  umax->setText("1") ;
  vmin->setText("-pi/2") ;
  vmax->setText("pi/2") ;

  xcft_3->setText("") ;
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ;
  umax_3->setText("") ;
  vmin_3->setText("") ;
  vmax_3->setText("") ;
  //  return;
    }

          if(choix == QString("Enneper")) {
   connectWidget2->objet->two_system = -1;
  xcft->setText("u -u^3/3  + u*v^2");
  ycft->setText("v -v^3/3  + v*u^2");
  zcft->setText("u^2 - v^2") ;
  umin->setText("-2") ;
  umax->setText("2") ;
  vmin->setText("-2") ;
  vmax->setText("2") ;

  xcft_3->setText("") ;
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ;
  umax_3->setText("") ;
  vmin_3->setText("") ;
  vmax_3->setText("") ;
 // return;
    }

            if(choix == QString("Helix")) {
   connectWidget2->objet->two_system = -1;
  xcft->setText("(1-0.1*cos(v))*cos(u)");
  ycft->setText("(1-0.1*cos(v))*sin(u)");
  zcft->setText("0.1*(sin(v) + u/1.7 -10)") ;
  umin->setText("0") ;
  umax->setText("4*pi") ;
  vmin->setText("0") ;
  vmax->setText("2*pi") ;

  xcft_3->setText("") ;
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ;
  umax_3->setText("") ;
  vmin_3->setText("") ;
  vmax_3->setText("") ;
 // return;
    }

           if(choix == QString("Hexaedron")) {
   connectWidget2->objet->two_system = -1;
  xcft->setText("cos(v)^3*cos(u)^3");
  ycft->setText("sin(v)^3*cos(u)^3");
  zcft->setText("sin(u)^3") ;
  umin->setText("-1.3") ;
  umax->setText("1.3") ;
  vmin->setText("0") ;
  vmax->setText("2*pi") ;

  xcft_3->setText("") ;
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ;
  umax_3->setText("") ;
  vmin_3->setText("") ;
  vmax_3->setText("") ;
 // return;
    }

           if(choix == QString("Sphere_1")) {
   connectWidget2->objet->two_system = -1;
  xcft->setText("cos(u)*cos(v)");
  ycft->setText("cos(u)*sin(v)");
  zcft->setText("sin(u)") ;
  umin->setText("-pi/2") ;
  umax->setText("pi/2") ;
  vmin->setText("0") ;
  vmax->setText("2*pi") ;

  xcft_3->setText("") ;
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ;
  umax_3->setText("") ;
  vmin_3->setText("") ;
  vmax_3->setText("") ;
 // return;
    }
             if(choix == QString("Sphere_2")) {
   connectWidget2->objet->two_system = -1;
  xcft->setText("cos(u)*cos(v)");
  ycft->setText("cos(u)*sin(v)");
  zcft->setText("sin(u)*sin(v)") ;
  umin->setText("-pi/2") ;
  umax->setText("pi/2") ;
  vmin->setText("0") ;
  vmax->setText("2*pi") ;

  xcft_3->setText("") ;
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ;
  umax_3->setText("") ;
  vmin_3->setText("") ;
  vmax_3->setText("") ;
 // return;
    }

              if(choix == QString("Sphere_3")) {
   connectWidget2->objet->two_system = -1;
  xcft->setText("cos(u)*cos(v)");
  ycft->setText("cos(u)*sin(v)");
  zcft->setText("sin(u)*sin(v)*cos(v)") ;
  umin->setText("-pi/2") ;
  umax->setText("pi/2") ;
  vmin->setText("0") ;
  vmax->setText("2*pi") ;

  xcft_3->setText("") ;
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ;
  umax_3->setText("") ;
  vmin_3->setText("") ;
  vmax_3->setText("") ;
 // return;
    }

               if(choix == QString("Sphere_4")) {
   connectWidget2->objet->two_system = -1;
  xcft->setText("cos(u)*cos(v)");
  ycft->setText("cos(u)*sin(v)*sin(v)");
  zcft->setText("sin(u)*sin(v)") ;
  umin->setText("-pi/2") ;
  umax->setText("0") ;
  vmin->setText("0") ;
  vmax->setText("2*pi") ;

  xcft_3->setText("") ;
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ;
  umax_3->setText("") ;
  vmin_3->setText("") ;
  vmax_3->setText("") ;
 // return;
    }

                 if(choix == QString("Sphere_5")) {
   connectWidget2->objet->two_system = -1;
  xcft->setText("cos(u)*cos(v)*sin(v)");
  ycft->setText("cos(u)*sin(v)*sin(v)");
  zcft->setText("sin(u)*sin(v)") ;
  umin->setText("-pi/2") ;
  umax->setText("0") ;
  vmin->setText("0") ;
  vmax->setText("2*pi") ;

  xcft_3->setText("") ;
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ;
  umax_3->setText("") ;
  vmin_3->setText("") ;
  vmax_3->setText("") ;
 // return;
    }

                 if(choix == QString("Sphere_6")) {
   connectWidget2->objet->two_system = -1;
  xcft->setText("cos(u)*cos(v)*sin(u)");
  ycft->setText("sin(u)");
  zcft->setText("sin(u)*sin(v)*sin(u)") ;
  umin->setText("-pi/2") ;
  umax->setText("0") ;
  vmin->setText("0") ;
  vmax->setText("2*pi") ;

  xcft_3->setText("") ;
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ;
  umax_3->setText("") ;
  vmin_3->setText("") ;
  vmax_3->setText("") ;
 // return;
    }

                 if(choix == QString("Sphere_7")) {
   connectWidget2->objet->two_system = -1;
  xcft->setText("cos(u)*cos(v)*sin(u)");
  ycft->setText("sin(u)*sin(v)*cos(u)");
  zcft->setText("sin(u)*sin(v)*sin(u)") ;
  umin->setText("-pi/2") ;
  umax->setText("0") ;
  vmin->setText("0") ;
  vmax->setText("2*pi") ;

  xcft_3->setText("") ;
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ;
  umax_3->setText("") ;
  vmin_3->setText("") ;
  vmax_3->setText("") ;
 // return;
    }

                 if(choix == QString("Sphere_8")) {
   connectWidget2->objet->two_system = -1;
  xcft->setText("cos(u)*cos(v)*sin(u)");
  ycft->setText("cos(u)*sin(v)*cos(u)");
  zcft->setText("sin(u)*sin(v)*sin(u)") ;
  umin->setText("-pi/2") ;
  umax->setText("0") ;
  vmin->setText("0") ;
  vmax->setText("2*pi") ;

  xcft_3->setText("") ;
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ;
  umax_3->setText("") ;
  vmin_3->setText("") ;
  vmax_3->setText("") ;
 // return;
    }

                 if(choix == QString("Sphere_9")) {
   connectWidget2->objet->two_system = -1;
  xcft->setText("cos(u)*cos(v)*sin(u)");
  ycft->setText("cos(u)*sin(v)*cos(u)*sin(v)");
  zcft->setText("sin(u)*sin(v)*sin(u)*sin(v)") ;
  umin->setText("-pi/2") ;
  umax->setText("0") ;
  vmin->setText("0") ;
  vmax->setText("pi") ;

  xcft_3->setText("") ;
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ;
  umax_3->setText("") ;
  vmin_3->setText("") ;
  vmax_3->setText("") ;
 // return;
    }

                 if(choix == QString("Sphere_10")) {
   connectWidget2->objet->two_system = -1;
  xcft->setText("cos(u)*cos(v)*sin(u)*sin(v)*sin(v)*sin(v)");
  ycft->setText("cos(u)*sin(v)*cos(u)*sin(v)");
  zcft->setText("sin(u)*sin(v)*sin(u)*sin(v)*cos(u)") ;
  umin->setText("-pi/2") ;
  umax->setText("0") ;
  vmin->setText("0") ;
  vmax->setText("pi") ;

  xcft_3->setText("") ;
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ;
  umax_3->setText("") ;
  vmin_3->setText("") ;
  vmax_3->setText("") ;
 // return;
    }

             if(choix == QString("Catalan")) {
   connectWidget2->objet->two_system = -1;
  xcft->setText("u-sin(u)*cosh(v)");
  ycft->setText("1-cos(u)*cosh(v)");
  zcft->setText("4*sin(1/2*u)*sinh(v/2)") ;
  umin->setText("-pi") ;
  umax->setText("3*pi") ;
  vmin->setText("-2") ;
  vmax->setText("2") ;

  xcft_3->setText("") ;
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ;
  umax_3->setText("") ;
  vmin_3->setText("") ;
  vmax_3->setText("") ;
 // return;
    }

             if(choix == QString("Toupie")) {
   connectWidget2->objet->two_system = -1;
  xcft->setText("(abs(u)-1)^2 * cos(v)");
  ycft->setText("(abs(u)-1)^2 * sin(v)");
  zcft->setText("u") ;
  umin->setText("-1") ;
  umax->setText("1") ;
  vmin->setText("0") ;
  vmax->setText("2*pi") ;

  xcft_3->setText("") ;
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ;
  umax_3->setText("") ;
  vmin_3->setText("") ;
  vmax_3->setText("") ;
 // return;
    }

             if(choix == QString("Bonbon")) {
   connectWidget2->objet->two_system = -1;
  xcft->setText("u");
  ycft->setText("cos (u)*cos (v)");
  zcft->setText("cos (u)*sin (v)") ;
  umin->setText("0") ;
  umax->setText("2*pi") ;
  vmin->setText("0") ;
  vmax->setText("2*pi") ;

  xcft_3->setText("") ;
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ;
  umax_3->setText("") ;
  vmin_3->setText("") ;
  vmax_3->setText("") ;
 // return;
    }

              if(choix == QString("Curve")) {
   connectWidget2->objet->two_system = -1;
  xcft->setText("cos(2*u)");
  ycft->setText("sin(3*u)");
  zcft->setText("cos(u)") ;
  umin->setText("0") ;
  umax->setText("2*pi") ;
  vmin->setText("0") ;
  vmax->setText("0") ;

  xcft_3->setText("") ;
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ;
  umax_3->setText("") ;
  vmin_3->setText("") ;
  vmax_3->setText("") ;
 // return;
    }

                 if(choix == QString("Trumpet")) {
   connectWidget2->objet->two_system = -1;
  xcft->setText("cos(u)*sin(v)");
  ycft->setText("sin(u)*sin(v)");
  zcft->setText("(cos(v)+log(tan(1/2*v)))") ;
  umin->setText("0") ;
  umax->setText("2*pi") ;
  vmin->setText("0.03") ;
  vmax->setText("2") ;

  xcft_3->setText("") ;
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ;
  umax_3->setText("") ;
  vmin_3->setText("") ;
  vmax_3->setText("") ;
 // return;
    }


                 if(choix == QString("Helice_Curve")) {
   connectWidget2->objet->two_system = -1;
  xcft->setText("sin(u)");
  ycft->setText("cos(u)");
  zcft->setText("(u^2)/100") ;
  umin->setText("0") ;
  umax->setText("6*pi") ;
  vmin->setText("0") ;
  vmax->setText("0") ;

  xcft_3->setText("") ;
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ;
  umax_3->setText("") ;
  vmin_3->setText("") ;
  vmax_3->setText("") ;
 // return;
    }

/*
boy
(2/3)*(cos(u)*cos(2*v) + 2^(1/2)*sin(u)*cos(v))*cos(u)/(2^(1/2)-sin(2*u)*sin(3*v))
(2/3)*(cos(u)*cos(2*v) - 2^(1/2)*sin(u)*sin(v))*cos(u)/(2^(1/2)-sin(2*u)*sin(3*v))
2^(1/2)*sin(2*u)*sin(2*v)/(2^(1/2)-sin(2*u)*sin(2*v))
 u  0  pi
 v  0  pi
 */



                   if(choix == QString("Cresent")) {
   connectWidget2->objet->two_system = -1;
  xcft->setText("(2 + sin(2* pi* u) *sin(2 *pi* v)) *sin(3* pi *v)");
  ycft->setText("(2 + sin(2* pi *u) *sin(2 *pi *v)) *cos(3* pi *v)");
  zcft->setText("cos(2* pi *u) *sin(2* pi* v) + 4 *v - 2") ;
  umin->setText("0") ;
  umax->setText("1") ;
  vmin->setText("0") ;
  vmax->setText("1") ;

  xcft_3->setText("") ;
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ;
  umax_3->setText("") ;
  vmin_3->setText("") ;
  vmax_3->setText("") ;
 // return;
    }

                  if(choix == QString("Shoe")) {
   connectWidget2->objet->two_system = -1;
  xcft->setText("u");
  ycft->setText("v");
  zcft->setText("1/3*u^3  - 1/2*v^2") ;
  umin->setText("-2") ; 
  umax->setText("2") ; 
  vmin->setText("-2") ; 
  vmax->setText("2") ; 
  
  xcft_3->setText("") ;  
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ; 
  umax_3->setText("") ; 
  vmin_3->setText("") ; 
  vmax_3->setText("") ;  
 // return;
    } 
                 if(choix == QString("Snake")) {
   connectWidget2->objet->two_system = -1;
  xcft->setText("1.2*(1 -v/(2*pi))*cos(3*v)*(1 + cos(u)) + 3*cos(3*v)");
  ycft->setText("1.2*(1 -v/(2*pi))*sin(3*v)*(1 + cos(u)) + 3*sin(3*v)");
  zcft->setText("9*v/(2*pi) + 1.2*(1 - v/(2*pi))*sin(u)") ;
  umin->setText("0") ; 
  umax->setText("2*pi") ; 
  vmin->setText("0") ; 
  vmax->setText("2*pi") ; 
  
  xcft_3->setText("") ;  
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ; 
  umax_3->setText("") ; 
  vmin_3->setText("") ; 
  vmax_3->setText("") ;  
 // return;
    }     
    
    
                  if(choix == QString("Roman")) {
   connectWidget2->objet->two_system = -1;
  xcft->setText("1/2*sin(2*u)*sin(v)^2");
  ycft->setText("1/2*sin(u)*cos(2*v)");
  zcft->setText("1/2*cos(u)*sin(2*v)") ;
  umin->setText("0") ; 
  umax->setText("pi") ; 
  vmin->setText("-pi/2") ; 
  vmax->setText("pi/2") ; 

  xcft_3->setText("") ;  
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ; 
  umax_3->setText("") ; 
  vmin_3->setText("") ; 
  vmax_3->setText("") ;  
 // return;
    } 
    
                    if(choix == QString("Hyperhelicoidal")) {
   connectWidget2->objet->two_system = -1;
  xcft->setText("(sinh(v)*cos(3*u))/(1+cosh(u)*cosh(v))");
  ycft->setText("(sinh(v)*sin(3*u))/(1+cosh(u)*cosh(v))");
  zcft->setText("(cosh(v)*sinh(u))/(1+cosh(u)*cosh(v))") ;
  umin->setText("-pi") ; 
  umax->setText("pi") ; 
  vmin->setText("-pi") ; 
  vmax->setText("pi") ; 
  
  xcft_3->setText("") ;  
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ; 
  umax_3->setText("") ; 
  vmin_3->setText("") ; 
  vmax_3->setText("") ;  
 // return;
    }
    
 /*   
                   if(choix == QString("Horn")) {
   connectWidget2->objet->two_system = -1;
  xcft->setText("(2 + u *cos(v)) *sin(2* pi* u)
");
  ycft->setText("(2 + u *cos(v)) *cos(2* pi* u) + 2* u");
  zcft->setText("u *sin(v)") ;
  umin->setText("0") ; 
  umax->setText("1") ; 
  vmin->setText("0") ; 
  vmax->setText("2*pi") ; 
  
  xcft_3->setText("") ;  
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ; 
  umax_3->setText("") ; 
  vmin_3->setText("") ; 
  vmax_3->setText("") ;  
 // return;
    }
    
  */
  
  
                    if(choix == QString("Horn")) {
   connectWidget2->objet->two_system = -1;
  xcft->setText("(2 + u*cos(v))*sin(2*pi*u)");
  ycft->setText("(2 + u*cos(v))*cos(2*pi*u) + 2*u");
  zcft->setText("u *sin(v)") ;
  umin->setText("0") ; 
  umax->setText("1") ; 
  vmin->setText("0") ; 
  vmax->setText("2*pi") ; 
  
  xcft_3->setText("") ;  
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ; 
  umax_3->setText("") ; 
  vmin_3->setText("") ; 
  vmax_3->setText("") ;  
 // return;
    }
  
  
    
                   if(choix == QString("Helicoidal")) {
   connectWidget2->objet->two_system = -1;
  xcft->setText("sinh(v)*sin(u)");
  ycft->setText("-sinh(v)*cos(u)");
  zcft->setText("3*u") ;
  umin->setText("-pi") ; 
  umax->setText("pi") ; 
  vmin->setText("-pi") ; 
  vmax->setText("pi") ; 
  
  xcft_3->setText("") ;  
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ; 
  umax_3->setText("") ; 
  vmin_3->setText("") ; 
  vmax_3->setText("") ;  
 // return;
    }   
                    if(choix == QString("Catenoid")) {
   connectWidget2->objet->two_system = -1;
  xcft->setText("2*cosh(v/2)*cos(u)");
  ycft->setText("2*cosh(v/2)*sin(u)");
  zcft->setText("v") ;
  umin->setText("-pi") ; 
  umax->setText("pi") ; 
  vmin->setText("-pi") ; 
  vmax->setText("pi") ; 
  
  xcft_3->setText("") ;  
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ; 
  umax_3->setText("") ; 
  vmin_3->setText("") ; 
  vmax_3->setText("") ;  
 // return;
    }  
                   if(choix == QString("Kuen")) {
   connectWidget2->objet->two_system = -1;
  xcft->setText("(2*(cos(u) + u*sin(u))*sin(v))/(1+ u^2*sin(v)^2)");
  ycft->setText("(2*(sin(u) - u*cos(u))*sin(v))/(1+ u^2*sin(v)^2)");
  zcft->setText("log(tan(1/2 *v)) + (2*cos(v))/(1+ u^2*sin(v)^2)") ;
  umin->setText("0") ; 
  umax->setText("2*pi") ; 
  vmin->setText("0.01") ; 
  vmax->setText("pi-0.01") ; 
  
  xcft_3->setText("") ;  
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ; 
  umax_3->setText("") ; 
  vmin_3->setText("") ; 
  vmax_3->setText("") ;  
 // return;
    }   


                    if(choix == QString("Hellipticparaboloid")) {
   connectWidget2->objet->two_system = -1;
  xcft->setText("v*2*cos(u)");
  ycft->setText("v*sin(u)");
  zcft->setText("v^2") ;
  umin->setText("0") ; 
  umax->setText("2*pi") ; 
  vmin->setText("0") ; 
  vmax->setText("2") ; 
  
  xcft_3->setText("") ;  
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ; 
  umax_3->setText("") ; 
  vmin_3->setText("") ; 
  vmax_3->setText("") ;  
 // return;
    }


                    if(choix == QString("Enneper_2")) {
   connectWidget2->objet->two_system = -1;
  xcft->setText("u*cos(v)-u^3/3*cos(3*v)");
  ycft->setText("-u*sin(v)-u^(3)/3*sin(3*v)");
  zcft->setText("u^2*cos(2*v)") ;
  umin->setText("0") ; 
  umax->setText("1.2") ; 
  vmin->setText("-pi") ; 
  vmax->setText("pi") ; 
  
  xcft_3->setText("") ;  
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ; 
  umax_3->setText("") ; 
  vmin_3->setText("") ; 
  vmax_3->setText("") ;  
 // return;
    } 
    /*
                     if(choix == QString("Hyperbolichelicoid")) {
   connectWidget2->objet->two_system = -1;
  xcft->setText("sinh(v)*cos(cosh(u)*cosh(v)*u)");
  ycft->setText("sinh(v)*sin(cosh(u)*cosh(v)*u");
  zcft->setText("cosh(v)*sinh(u)") ;
  umin->setText("0") ; 
  umax->setText("pi") ; 
  vmin->setText("0") ; 
  vmax->setText("pi") ; 
  
  xcft_3->setText("") ;  
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ; 
  umax_3->setText("") ; 
  vmin_3->setText("") ; 
  vmax_3->setText("") ;  
 // return;
    } 
 
 */
 
                    if(choix == QString("Stereosphere")) {
   connectWidget2->objet->two_system = -1;
  xcft->setText("2.*u/(u*u+v*v+1.)");
  ycft->setText("2.*v/(u*u+v*v+1.)");
  zcft->setText("(u*u+v*v-1.)/(u*u+v*v+1.)") ;
  umin->setText("-2") ; 
  umax->setText("2") ; 
  vmin->setText("-2") ; 
  vmax->setText("2") ; 
  
  xcft_3->setText("") ;  
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ; 
  umax_3->setText("") ; 
  vmin_3->setText("") ; 
  vmax_3->setText("") ;  
 // return;
    }

                    if(choix == QString("Cliffordtorus")) {
   connectWidget2->objet->two_system = -1;
  xcft->setText("cos(u+v)/(sqrt(2.)+cos(v-u))");
  ycft->setText("sin(u+v)/(sqrt(2.)+cos(v-u))");
  zcft->setText("sin(v-u)/(sqrt(2.)+cos(v-u))") ;
  umin->setText("0") ; 
  umax->setText("pi") ; 
  vmin->setText("0") ; 
  vmax->setText("2*pi") ; 
  
  xcft_3->setText("") ;  
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ; 
  umax_3->setText("") ; 
  vmin_3->setText("") ; 
  vmax_3->setText("") ;  
 // return;
    }   

  
 
                    if(choix == QString("Fresnel_1")) {
   connectWidget2->objet->two_system = -1;
  xcft->setText("cos(u)*cos(v)/(-2.*sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))*cos((acos(-(-0.941/6.+0.374*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4)-1.309/6.*((cos(u)^6+sin(u)^6)*cos(v)^6+sin(v)^6)-1.221*cos(u)^2*cos(v)^4*sin(u)^2*sin(v)^2)/sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))^3)+pi)/3.)+0.8)");
  ycft->setText("sin(u)*cos(v)/(-2.*sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))*cos((acos(-(-0.941/6.+0.374*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4)-1.309/6.*((cos(u)^6+sin(u)^6)*cos(v)^6+sin(v)^6)-1.221*cos(u)^2*cos(v)^4*sin(u)^2*sin(v)^2)/sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))^3)+pi)/3.)+0.8)");
  zcft->setText("sin(v)/(-2.*sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))*cos((acos(-(-0.941/6.+0.374*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4)-1.309/6.*((cos(u)^6+sin(u)^6)*cos(v)^6+sin(v)^6)-1.221*cos(u)^2*cos(v)^4*sin(u)^2*sin(v)^2)/sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))^3)+pi)/3.)+0.8)") ;
  umin->setText("0") ; 
  umax->setText("2*pi") ; 
  vmin->setText("-pi/2") ; 
  vmax->setText("pi/2") ; 
  
  xcft_3->setText("") ;  
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ; 
  umax_3->setText("") ; 
  vmin_3->setText("") ; 
  vmax_3->setText("") ;  
 // return;
    }   
    
  
                    if(choix == QString("Fresnel_2")) {
   connectWidget2->objet->two_system = -1;
  xcft->setText("cos(u)*cos(v)/(-2.*sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))*cos((acos(-(-0.941/6.+0.374*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4)-1.309/6.*((cos(u)^6+sin(u)^6)*cos(v)^6+sin(v)^6)-1.221*cos(u)^2*cos(v)^4*sin(u)^2*sin(v)^2)/sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))^3)-pi)/3.)+0.8)");
  ycft->setText("sin(u)*cos(v)/(-2.*sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))*cos((acos(-(-0.941/6.+0.374*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4)-1.309/6.*((cos(u)^6+sin(u)^6)*cos(v)^6+sin(v)^6)-1.221*cos(u)^2*cos(v)^4*sin(u)^2*sin(v)^2)/sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))^3)-pi)/3.)+0.8)");
  zcft->setText("sin(v)/(-2.*sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))*cos((acos(-(-0.941/6.+0.374*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4)-1.309/6.*((cos(u)^6+sin(u)^6)*cos(v)^6+sin(v)^6)-1.221*cos(u)^2*cos(v)^4*sin(u)^2*sin(v)^2)/sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))^3)-pi)/3.)+0.8)") ;
  umin->setText("0") ;
  umax->setText("2*pi") ;
  vmin->setText("-pi/2");
  vmax->setText("pi/2");

  xcft_3->setText("") ;
  zcft_3->setText("") ;
  ycft_3->setText("") ;
  umin_3->setText("") ;
  umax_3->setText("") ;
  vmin_3->setText("") ;
  vmax_3->setText("") ;
 // return;
    }

// copy the first system
  connectWidget2->objet->expression_X = xcft->text();
  connectWidget2->objet->expression_Y = ycft->text();
  connectWidget2->objet->expression_Z = zcft->text();

  connectWidget2->objet->inf_u = umin->text();
  connectWidget2->objet->sup_u = umax->text();
  connectWidget2->objet->inf_v = vmin->text();
  connectWidget2->objet->sup_v = vmax->text();

// copy the second system
if(connectWidget2->objet->two_system == 1) {

  connectWidget2->objet->expression_X_2 = xcft_3->text();
  connectWidget2->objet->expression_Y_2 = ycft_3->text();
  connectWidget2->objet->expression_Z_2 = zcft_3->text();

  connectWidget2->objet->inf_u_2 = umin_3->text();
  connectWidget2->objet->sup_u_2 = umax_3->text();
  connectWidget2->objet->inf_v_2 = vmin_3->text();
  connectWidget2->objet->sup_v_2 = vmax_3->text();
   }
else {
  // for more security...
  connectWidget2->objet->expression_X_2 = "";
  connectWidget2->objet->expression_Y_2 = "";
  connectWidget2->objet->expression_Z_2 = "";
  connectWidget2->objet->inf_u_2 = "";
  connectWidget2->objet->sup_u_2 = "";
  connectWidget2->objet->inf_v_2 = "";
  connectWidget2->objet->sup_v_2 = "";
  }

  // process the new surface
 ParametricSurfaceProcess();

}


//====================================
void k3dsurface::deffct_desactiver() {
//if( deffct->isChecked())   deffct->toggle();
   if(connectWidget2->objet->DefineNewFct ==1)     deffct->toggle(); 
    connectWidget2->objet->DefineNewFct = -1;
}
//====================================
void k3dsurface::secondsys_desactiver() {
 //  if(connectWidget2->objet->two_system ==1)     secondsystem->toggle(); 
 //   connectWidget2->objet->two_system = -1;
}

//====================================
void k3dsurface::perform_supershape()
{
    FunctionParser fp;
    QMessageBox message ;
     
    fp.AddConstant("pi", 3.14159265);
    int ret;

    ret = fp.Parse(m1->text(), "t"); 
    if(ret >= 0) 
    { 
    message.setText(tr(QString("M(u)--> At col:")+
         QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec(); 
      return ; 
    }

    ret = fp.Parse(m2->text(), "t"); 
    if(ret >= 0) 
    { 
    message.setText(tr(QString("M(v)--> At col:")+
         QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec(); 
      return ; 
    }

    ret = fp.Parse(a_1->text(), "t"); 
    if(ret >= 0) 
    { 
    message.setText(tr(QString("a(u)--> At col:")+
         QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec(); 
      return ; 
    }

    ret = fp.Parse(a_2->text(), "t"); 
    if(ret >= 0) 
    { 
    message.setText(tr(QString("a(v)--> At col:")+
         QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec(); 
      return ; 
    }

    ret = fp.Parse(b_1->text(), "t"); 
    if(ret >= 0) 
    { 
    message.setText(tr(QString("b(u)--> At col:")+
         QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec(); 
      return ; 
    }

    ret = fp.Parse(b_2->text(), "t"); 
    if(ret >= 0) 
    { 
    message.setText(tr(QString("b(v)--> At col:")+
         QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec(); 
      return ; 
    }

    ret = fp.Parse(n1_1->text(), "t"); 
    if(ret >= 0) 
    { 
    message.setText(tr(QString("N1(u)--> At col:")+
         QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec(); 
      return ; 
    }

    ret = fp.Parse(n1_2->text(), "t"); 
    if(ret >= 0) 
    { 
    message.setText(tr(QString("N1(v)--> At col:")+
         QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec(); 
      return ; 
    }

    ret = fp.Parse(n2_1->text(), "t"); 
    if(ret >= 0) 
    { 
    message.setText(tr(QString("N2(u)--> At col:")+
         QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec(); 
      return ; 
    }

    ret = fp.Parse(n2_2->text(), "t"); 
    if(ret >= 0) 
    { 
    message.setText(tr(QString("N2(v)--> At col:")+
         QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec(); 
      return ; 
    }

    ret = fp.Parse(n3_1->text(), "t"); 
    if(ret >= 0) 
    { 
    message.setText(tr(QString("N3(u)--> At col:")+
         QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec(); 
      return ; 
    }

    ret = fp.Parse(n3_2->text(), "t"); 
    if(ret >= 0) 
    { 
    message.setText(tr(QString("N3(v)--> At col:")+
         QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec(); 
      return ; 
    }

    ret = fp.Parse(sfumin->text(), "t"); 
    if(ret >= 0) 
    { 
    message.setText(tr(QString("Umin--> At col:")+
         QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec(); 
      return ; 
    }

    ret = fp.Parse(sfumax->text(), "t"); 
    if(ret >= 0) 
    { 
    message.setText(tr(QString("Umax--> At col:")+
         QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec(); 
      return ; 
    }

    ret = fp.Parse(sfvmin->text(), "t"); 
    if(ret >= 0) 
    { 
    message.setText(tr(QString("Vmin--> At col:")+
         QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec(); 
      return ; 
    }

    ret = fp.Parse(sfvmax->text(), "t"); 
    if(ret >= 0) 
    { 
    message.setText(tr(QString("Vmax--> At col:")+
         QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec(); 
      return ; 
    }



    connectWidget2->objet->sm1   = m1->text();
    connectWidget2->objet->sa_1  = a_1->text();
    connectWidget2->objet->sb_1  = b_1->text();
    connectWidget2->objet->sn1_1 = n1_1->text();
    connectWidget2->objet->sn2_1 = n2_1->text();
    connectWidget2->objet->sn3_1 = n3_1->text();

    connectWidget2->objet->sm2   = m2->text();
    connectWidget2->objet->sa_2  = a_2->text();
    connectWidget2->objet->sb_2  = b_2->text();
    connectWidget2->objet->sn1_2 = n1_2->text();
    connectWidget2->objet->sn2_2 = n2_2->text();
    connectWidget2->objet->sn3_2 = n3_2->text();


    connectWidget2->objet->inf_u = sfumin->text();
    connectWidget2->objet->sup_u = sfumax->text();
    connectWidget2->objet->inf_v = sfvmin->text();
    connectWidget2->objet->sup_v = sfvmax->text();

   /// Set the right Window for drawing :
    tabsurf->setCurrentPage(0);
    
  //Process the new surface :
    ParametricSurfaceProcess();
}
//====================================
void k3dsurface::choicesf_changed( const QString & choix )
{        
 if(choix == QString("SuperShape_1")) { 
  m1->setText("0"); a_1->setText("1"); b_1->setText("1"); 
  n1_1->setText("0.48"); n2_1->setText("30.25"); n3_1->setText("0.35");
  
  m2->setText("5"); a_2->setText("1"); b_2->setText("1"); 
  n1_2->setText("15.44"); n2_2->setText("-0.45"); n3_2->setText("87");  
  
  sfumin->setText("-pi"); sfumax->setText("pi");
  sfvmin->setText("-pi/2"); sfvmax->setText("pi/2");
}

 if(choix == QString("SuperShape_2")) { 
  m1->setText("0.2"); a_1->setText("1"); b_1->setText("1"); 
  n1_1->setText("0.1"); n2_1->setText("1.7"); n3_1->setText("1.7");
  
  m2->setText("0.2"); a_2->setText("1"); b_2->setText("1"); 
  n1_2->setText("0.5"); n2_2->setText("0.2"); n3_2->setText("0.2");    
  
   sfumin->setText("-pi"); sfumax->setText("pi");
  sfvmin->setText("-pi/2"); sfvmax->setText("pi/2");
}

 if(choix == QString("SuperShape_3")) { 
  m1->setText("2"); a_1->setText("1"); b_1->setText("1"); 
  n1_1->setText("1"); n2_1->setText("1"); n3_1->setText("1");
  
  m2->setText("4"); a_2->setText("1"); b_2->setText("1"); 
  n1_2->setText("1"); n2_2->setText("1"); n3_2->setText("1");  
  
  sfumin->setText("-pi"); sfumax->setText("pi");
  sfvmin->setText("-pi/2"); sfvmax->setText("pi/2");  
}

 if(choix == QString("SuperShape_4")) { 
  m1->setText("5.7"); a_1->setText("1"); b_1->setText("1"); 
  n1_1->setText("0.5"); n2_1->setText("1"); n3_1->setText("2.5");
  
  m2->setText("10"); a_2->setText("1"); b_2->setText("1"); 
  n1_2->setText("3"); n2_2->setText("0.2"); n3_2->setText("1");  
  
  sfumin->setText("-pi"); sfumax->setText("pi");
  sfvmin->setText("-pi/2"); sfvmax->setText("pi/2");  
} 
 
 if(choix == QString("SuperShape_5")) { 
  m1->setText("6"); a_1->setText("1"); b_1->setText("1"); 
  n1_1->setText("60"); n2_1->setText("55"); n3_1->setText("1000");
  
  m2->setText("6"); a_2->setText("1"); b_2->setText("1"); 
  n1_2->setText("250"); n2_2->setText("100"); n3_2->setText("100");
  
  sfumin->setText("-pi"); sfumax->setText("pi");
  sfvmin->setText("-pi/2"); sfvmax->setText("pi/2");  
} 

 if(choix == QString("SuperShape_6")) { 
  m1->setText("2"); a_1->setText("1"); b_1->setText("1"); 
  n1_1->setText("0.99"); n2_1->setText("97.67"); n3_1->setText("-0.439");
  
  m2->setText("7"); a_2->setText("1"); b_2->setText("1"); 
  n1_2->setText("-8.11"); n2_2->setText("-0.0807"); n3_2->setText("93");  
  
  sfumin->setText("-pi"); sfumax->setText("pi");
  sfvmin->setText("-pi/2"); sfvmax->setText("pi/2");  
} 

 if(choix == QString("SuperShape_7")) { 
  m1->setText("6"); a_1->setText("1"); b_1->setText("1"); 
  n1_1->setText("0.709889"); n2_1->setText("46.82"); n3_1->setText("-0.80");
  
  m2->setText("7"); a_2->setText("1"); b_2->setText("1"); 
  n1_2->setText("-31.9083"); n2_2->setText("-0.19"); n3_2->setText("97"); 
  
  sfumin->setText("-pi"); sfumax->setText("pi");
  sfvmin->setText("-pi/2"); sfvmax->setText("pi/2");  
}
 if(choix == QString("SuperShape_8")) { 
  m1->setText("7"); a_1->setText("1"); b_1->setText("1"); 
  n1_1->setText("0.2"); n2_1->setText("1.7"); n3_1->setText("1.7");
  
  m2->setText("7"); a_2->setText("1"); b_2->setText("1"); 
  n1_2->setText("0.2"); n2_2->setText("1.7"); n3_2->setText("1.7");  
  
  sfumin->setText("-pi"); sfumax->setText("pi");
  sfvmin->setText("-pi/2"); sfvmax->setText("pi/2");  
}
 if(choix == QString("SuperShape_9")) { 
  m1->setText("3"); a_1->setText("1"); b_1->setText("1"); 
  n1_1->setText("1"); n2_1->setText("1"); n3_1->setText("1");
  
  m2->setText("6"); a_2->setText("2"); b_2->setText("1"); 
  n1_2->setText("2"); n2_2->setText("1"); n3_2->setText("1"); 
  
  sfumin->setText("-pi"); sfumax->setText("pi");
  sfvmin->setText("-pi/2"); sfvmax->setText("pi/2");  
}
 if(choix == QString("SuperShape_10")) { 
  m1->setText("6"); a_1->setText("1"); b_1->setText("1"); 
  n1_1->setText("3000"); n2_1->setText("1000"); n3_1->setText("1000");
  
  m2->setText("6"); a_2->setText("1"); b_2->setText("1"); 
  n1_2->setText("250"); n2_2->setText("100"); n3_2->setText("100");  
  
  sfumin->setText("-pi"); sfumax->setText("pi");
  sfvmin->setText("-pi/2"); sfvmax->setText("pi/2");  
}

  // process the new surface
    connectWidget2->objet->sm1   = m1->text();
    connectWidget2->objet->sa_1  = a_1->text();
    connectWidget2->objet->sb_1  = b_1->text();
    connectWidget2->objet->sn1_1 = n1_1->text();
    connectWidget2->objet->sn2_1 = n2_1->text();
    connectWidget2->objet->sn3_1 = n3_1->text();

    connectWidget2->objet->sm2   = m2->text();
    connectWidget2->objet->sa_2  = a_2->text();
    connectWidget2->objet->sb_2  = b_2->text();
    connectWidget2->objet->sn1_2 = n1_2->text();
    connectWidget2->objet->sn2_2 = n2_2->text();
    connectWidget2->objet->sn3_2 = n3_2->text();


    connectWidget2->objet->inf_u = sfumin->text();
    connectWidget2->objet->sup_u = sfumax->text();
    connectWidget2->objet->inf_v = sfvmin->text();
    connectWidget2->objet->sup_v = sfvmax->text();

   /// Set the right Window for drawing :
    tabsurf->setCurrentPage(0);
    
  //Process the new surface :
ParametricSurfaceProcess();
}
//====================================
void k3dsurface::perform()
{
    FunctionParser fp,f1;
    QMessageBox message ;
     
    fp.AddConstant("pi", 3.14159265);
    int ret;
    
    
        if(connectWidget2->objet->DefineNewFct ==1) 
    {          
    ret = fp.Parse(fctdef->text(), "u,v,t,x,y"); 
    if(ret >= 0) 
    { 


    message.setText(tr(QString("k(u,v,t,x,y)--> At col:")+
         QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec(); 
 
 
 
 
        return ; 
    }      
          
     f1.Parse(fctdef->text(), "u,v,t,x,y");
     fp.AddFunction("k", f1);
    }
    
    ret = fp.Parse(xcft->text(), "u,v,t"); 
    if(ret >= 0) 
    { 

    message.setText(tr(QString("X=g(u,v)--> At col:")+
         QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();  
  
  
   
        return ; 
    } 
    
    ret = fp.Parse(ycft->text(), "u,v,t,x");
    if(ret >= 0) 
    { 

    message.setText(tr(QString("Y=g(u,v)--> At col:")+
 QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec(); 
 
 
 
 
        return ; 
    } 
    
     ret = fp.Parse(zcft->text(), "u,v,t,x,y");
    if(ret >= 0) 
    { 
    message.setText(tr(QString("Z=h(u,v)--> At col:")+
        QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec(); 
        return ; 
    }

// verifiy that a condition exists  

 if(activate_cd == 1) {
     ret = fp.Parse(condition->text(), "u,v,t,x,y,z");
    if(ret >= 0)
    {
    message.setText(tr(QString("CND --> At col:")+
        QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();
        return ;
    }

  if(inverse_condition  == 1) 
     connectWidget2->objet->condition_expression = QString("("+condition->text()+") = 0");
  else connectWidget2->objet->condition_expression  = condition->text();

} // End if(activate_cd == 1)

  connectWidget2->objet->expression_X = xcft->text(); ///Reverse the Axes
  connectWidget2->objet->expression_Y = ycft->text(); ///Reverse the Axes
  connectWidget2->objet->expression_Z = zcft->text();

  connectWidget2->objet->inf_u = umin->text();
  connectWidget2->objet->sup_u = umax->text();
  connectWidget2->objet->inf_v = vmin->text();
  connectWidget2->objet->sup_v = vmax->text();

// Now we look in the second system if something wrong with it...

if (
(xcft_3->text() != "") && 
(ycft_3->text() != "") &&
(zcft_3->text() != "") &&
(umin_3->text() != "") &&
(umax_3->text() != "") &&
(vmin_3->text() != "") &&
(vmax_3->text() != "")  ) 

{
  connectWidget2->objet->expression_X_2 = xcft_3->text(); ///Reverse the Axes
  connectWidget2->objet->expression_Y_2 = ycft_3->text(); ///Reverse the Axes
  connectWidget2->objet->expression_Z_2 = zcft_3->text();
  connectWidget2->objet->inf_u_2 = umin_3->text();
  connectWidget2->objet->sup_u_2 = umax_3->text();
  connectWidget2->objet->sup_v_2 = vmax_3->text();
  connectWidget2->objet->inf_v_2 = vmin_3->text();

    ret = fp.Parse(xcft_3->text(), "u,v,t");
    if(ret >= 0)
    {
    message.setText(tr(QString("Second System : X=l(u,v)--> At col:")+
         QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();
   connectWidget2->objet->two_system = -1 ;
        return ;
    }

    ret = fp.Parse(ycft_3->text(), "u,v,t");
    if(ret >= 0) 
    {

    message.setText(tr(QString("Second System : Y=r(u,v)--> At col:")+
 QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();

 connectWidget2->objet->two_system = -1;
        return ;
    }
     ret = fp.Parse(zcft_3->text(), "u,v,t");
    if(ret >= 0) 
    {
    message.setText(tr(QString("Second System : Z=s(u,v)--> At col:")+
        QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();

 connectWidget2->objet->two_system = -1 ;
        return ;
    }

   // Now we give the authorisation to use two systems...
   connectWidget2->objet->two_system = 1 ; 

}

  // process the new surface
ParametricSurfaceProcess();
}

//====================================
void k3dsurface::ParametricSurfaceProcess()
{
  // process the new surface
int current_pag = tabsurf->currentPageIndex();


if( paramwidgetstack == 1)  {
connectWidget2->objet->SpecialMorph_2(ParamGlWidget->ArrayNorVer_local, ParamGlWidget->PolyIndices_local, ParamGlWidget->NbPolygnNbVertex, 1);
ParamGlWidget->PolyNumber = connectWidget2->objet->NbPolygn;
      ParamGlWidget->initializeGL();
      ParamGlWidget->updateGL();
}
 else  connectWidget2->valueChanged();

if(current_pag != 0) tabsurf->setCurrentPage(0);
}
//====================================
void k3dsurface::Initparametricpage(){
      ParamGlWidget->LocalScene.typedrawing = -1;
      ParamGlWidget->LocalScene.line = 1;
}
//====================================
void k3dsurface::Initisopage(){
      IsoGlWidget->LocalScene.typedrawing = 1;
      IsoGlWidget->LocalScene.line = -1;
      IsoGlWidget->LocalScene.box = -1;
}


//====================================
void k3dsurface::perform2()
{  //double vals=0;//[1] = {0};
   QMessageBox message ;
   FunctionParser f1, fp, fp2; 
  
  
  if(fourdimshapes == -1) {
   
    fp.AddConstant("pi", 3.14159265);
    int ret;
/*    
    ret = fp2.Parse(puissance_val_2->text(), "youpi");
    if(fmod(fp2.Eval(&vals), 2) == 0) {
    
    message.setText(tr("n mod 2 = 0 !!!!"));
    message.adjustSize () ;
    message.exec(); 
        return ;        
    };
*/
    ret = fp.Parse(fctdefz_val_2->text(), "x,y,t"); 
    if(ret >= 0) 
    { 

    message.setText(tr(QString("Implicit equation : f(x,y,t)--> At col:")+
        QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec(); 
 
        return ; 
    } 
    
    
      connectWidget2->objet->implicitdef = 1;
      connectWidget2->objet->expression_implicite = fctdefz_val_2->text();


  connectWidget2->objet->coefficient_n = puissance_val_2->text();

  connectWidget2->objet->inf_u = umin_3_2->text();
  connectWidget2->objet->sup_u = umax_3_2->text();
  connectWidget2->objet->inf_v = vmin_3_2->text();
  connectWidget2->objet->sup_v = vmax_3_2->text();

  // process the new surface
ParametricSurfaceProcess();

}
else {

    fp.AddConstant("pi", 3.14159265);
    int ret;

        if(connectWidget2->objet->DefineNewFct ==1)
    {
    ret = fp.Parse(fctdef->text(), "u,v,t,x,y");
    if(ret >= 0) 
    {

    message.setText(tr(QString("k(u,v,t,x,y)--> At col:")+
         QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();
        return ;
    }

     f1.Parse(fctdef->text(), "u,v,t,x,y");
     fp.AddFunction("k", f1);
    }

    ret = fp.Parse(xcft_2->text(), "u,v,t"); 
    if(ret >= 0) 
    {
    message.setText(tr(QString("X=g(u,v)--> At col:")+
         QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();
        return ;
    }

    ret = fp.Parse(ycft_2->text(), "u,v,t");
    if(ret >= 0) 
    {
    message.setText(tr(QString("Y=g(u,v)--> At col:")+
 QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();
        return ;
    }


     ret = fp.Parse(zcft_2->text(), "u,v,t");
    if(ret >= 0) 
    {message.setText(tr(QString("Z=h(u,v)--> At col:")+
        QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();
    return ;
    }


     ret = fp.Parse(wcft_2->text(), "u,v,t");
    if(ret >= 0) 
    {message.setText(tr(QString("W=l(u,v)--> At col:")+
        QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();
    return ;
    }



  connectWidget2->objet->fourdimshapes = 1;

  connectWidget2->objet->expression_X = xcft_2->text(); /// To reverse the Axes
  connectWidget2->objet->expression_Y = ycft_2->text(); /// To reverse the Axes
  connectWidget2->objet->expression_Z = zcft_2->text();
  connectWidget2->objet->expression_W = wcft_2->text();

  connectWidget2->objet->inf_u = umin_2->text();
  connectWidget2->objet->sup_u = umax_2->text();
  connectWidget2->objet->inf_v = vmin_2->text();
  connectWidget2->objet->sup_v = vmax_2->text();

   // process the new surface
ParametricSurfaceProcess();
     }

}
/*
//====================================
void k3dsurface::perform3()
{
    FunctionParser fp,f1;
    QMessageBox message ;

    fp.AddConstant("pi", 3.14159265);
    int ret;

        if(connectWidget2->objet->DefineNewFct ==1)
    {
    ret = fp.Parse(fctdef->text(), "u,v,t,x,y");
    if(ret >= 0)
    {


    message.setText(tr(QString("k(u,v,t,x,y)--> At col:")+
         QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();


        return ;
    }

     f1.Parse(fctdef->text(), "u,v,t,x,y");
     fp.AddFunction("k", f1);
    }

    ret = fp.Parse(xcft_tools->text(), "u,v,t"); 
    if(ret >= 0)
    {
    message.setText(tr(QString("X=g(u,v)--> At col:")+
         QString::number(ret)+QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();

        return ;
    }

    ret = fp.Parse(ycft_tools->text(), "u,v,t,x");
    if(ret >= 0)
    {

    message.setText(tr(QString("Y=g(u,v)--> At col:")+
 QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();

        return ;
    }

     ret = fp.Parse(zcft_tools->text(), "u,v,t,x,y");
    if(ret >= 0)
    {
    message.setText(tr(QString("Z=h(u,v)--> At col:")+
        QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();
        return ;
    }

// verifiy that a condition exists  

 if(activate_cd == 1) {
     ret = fp.Parse(condition->text(), "u,v,t,x,y,z");
    if(ret >= 0)
    {
    message.setText(tr(QString("CND --> At col:")+
        QString::number(ret)+ QString("--> \n")+ fp.ErrorMsg()));
    message.adjustSize () ;
    message.exec();
        return ;
    }

  if(inverse_condition  == 1) 
        connectWidget2->objet->condition_expression = QString("("+condition->text()+") = 0");
  else  connectWidget2->objet->condition_expression  = condition->text();

} // End if(activate_cd == 1)

  connectWidget2->objet->expression_X = xcft_tools->text();
  connectWidget2->objet->expression_Y = ycft_tools->text();
  connectWidget2->objet->expression_Z = zcft_tools->text();

  connectWidget2->objet->inf_u = umin_tools->text();
  connectWidget2->objet->sup_u = umax_tools->text();
  connectWidget2->objet->inf_v = vmin_tools->text();
  connectWidget2->objet->sup_v = vmax_tools->text();

   connectWidget2->objet->two_system = -1 ;

  // process the new surface
  connectWidget2->valueChanged();
}
//=====================//======================
*/
#include <qfiledialog.h>
#include <qlistview.h>


void k3dsurface::Include_Ini_AddButton_clicked()
{
       QString   include_ini = QFileDialog::getOpenFileName(
            "",
            tr("Povray ini files (*.ini);;All files (* *.*)"),
            this,
            "open file dialog",
            tr("Please choose the include ini") );
    if (include_ini.length() && !Include_IniListview_2->findItem(include_ini,0))
    {
        new QListViewItem(Include_IniListview_2,include_ini);
    }
}
//====================================

void k3dsurface::Include_Ini_RemoveButton_clicked()
{
    if (Include_IniListview_2->currentItem())
    {
        delete Include_IniListview_2->currentItem();
    }
}
//====================================
void k3dsurface::InputFileNameButton_clicked()
{

    QString filename = QFileDialog::getSaveFileName(
            "",
            tr("Povray scripts (*.pov)"),
            this,
            "save file dialog",
            tr("Please choose the output file") );
    if (filename.length())
    {
        Input_File_NameEdit_2->setText(filename);
    }
}

//====================================
void k3dsurface::Include_Header_AddButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(
            "",
            tr("Povray files (*.inc *.pov)"),
            this,
            "open file dialog",
            tr("Please choose the include header") );
    if (filename.length() && !Include_HeaderListview_2->findItem(filename,0))
    {
        new QListViewItem(Include_HeaderListview_2,filename);
    }

   IncludeHeaderFile += " +HI"+filename;
}
//====================================
void k3dsurface::Include_Header_RemoveButton_clicked()
{
    if (Include_HeaderListview_2->currentItem())
    {
        delete Include_HeaderListview_2->currentItem();
    }
}

//====================================

void k3dsurface::Library_Path_RemoveButton_clicked()
{
    if (Library_PathListview_2->currentItem())
    {
        delete Library_PathListview_2->currentItem();
    }
}
//====================================
void k3dsurface::Declare_AddButton_clicked()
{/*
    DeclareDialog dd;
    if (dd.exec() == QDialog::Accepted)
    {
        if (dd.DeclareEdit_2->text().find('=') != -1)
        {
            new QListViewItem(DeclareListview,dd.DeclareEdit_2->text());
        }
        else
            QMessageBox::warning(this,tr("format error"),tr("the declare format is\nIDENTIFIER=VALUE"),QMessageBox::Ok,QMessageBox::NoButton,QMessageBox::NoButton);
    }*/
}
//====================================
void k3dsurface::Declare_RemoveButton_clicked()
{
    /*
    if (DeclareListview_2->currentItem())
    {
        delete DeclareListview_2->currentItem();
    }
    */
}
//====================================
void k3dsurface::Test_AbortCheckbox_toggled( bool )
{
    Test_Abort_CountLabel_2->setEnabled(Test_AbortCheckbox_2->isChecked());
    Test_Abort_CountEdit_2->setEnabled(Test_AbortCheckbox_2->isChecked());
}

//====================================

void k3dsurface::Create_IniCheckbox_toggled( bool )
{/*
    Create_IniEdit_2->setEnabled(Create_IniCheckbox_2->isChecked());
*/}
//====================================
void k3dsurface::OutputFileNameButton_clicked()
{
    QString filename = QFileDialog::getSaveFileName(
            "",
            tr("Images (*.png *.jpg *.jpeg *.tif *.tiff *.ppm *.tga *.pgm)"),
            this,
            "save file dialog",
            tr("Please choose the output file") );
    if (filename.length())
    {
        Output_File_NameEdit_2->setText(filename);
    }
}

//====================================
void k3dsurface::Buffer_OutputCheckbox_toggled( bool )
{
    Buffer_SizeEdit_2->setEnabled(Output_To_FileCheckbox_2->isChecked() && Buffer_OutputCheckbox_2->isChecked());
}
/*
void k3dsurface::Create_HistogramCheckbox_toggled( bool )
{
    Histogram_NameLabel_2->setEnabled(Create_HistogramCheckbox_2->isChecked());
    Histogram_NameEdit_2->setEnabled(Create_HistogramCheckbox_2->isChecked());
    Histogram_TypeLabel_2->setEnabled(Create_HistogramCheckbox_2->isChecked());
    Histogram_TypeCombobox_2->setEnabled(Create_HistogramCheckbox_2->isChecked());
    Histogram_Grid_SizeLabel_2->setEnabled(Create_HistogramCheckbox_2->isChecked());
    Histogram_Grid_SizeEdit_2->setEnabled(Create_HistogramCheckbox_2->isChecked());
}
*/

//====================================
void k3dsurface::Output_To_FileCheckbox_toggled( bool )
{
//    Output_AlphaCheckbox_2->setEnabled(Output_To_FileCheckbox_2->isChecked());
    Output_File_NameLabel_2->setEnabled(Output_To_FileCheckbox_2->isChecked());
    Output_File_NameEdit_2->setEnabled(Output_To_FileCheckbox_2->isChecked());
    Output_File_TypeLabel_2->setEnabled(Output_To_FileCheckbox_2->isChecked());
    Output_File_TypeCombobox_2->setEnabled(Output_To_FileCheckbox_2->isChecked());
    Bits_Per_ColorLabel_2->setEnabled(Output_To_FileCheckbox_2->isChecked());
    Bits_Per_ColorSpinbox_2->setEnabled(Output_To_FileCheckbox_2->isChecked());
    Buffer_OutputCheckbox_2->setEnabled(Output_To_FileCheckbox_2->isChecked());
    Buffer_SizeEdit_2->setEnabled(Output_To_FileCheckbox_2->isChecked() && Buffer_OutputCheckbox_2->isChecked());
}
//====================================
void k3dsurface::Output_File_TypeCombobox_highlighted( const QString & item)
{
    Bits_Per_ColorLabel_2->setEnabled((item == "PNG") || (item == "Unix PPM"));
    Bits_Per_ColorSpinbox_2->setEnabled((item == "PNG") || (item == "Unix PPM"));
}

//====================================

void k3dsurface::whatsThisButton_clicked()
{
    QWhatsThis::enterWhatsThisMode();
}


//====================================
void k3dsurface::choice5D_changed( const QString & choix )
{

                        if(choix == QString("Flower")) {

  xcft_5->setText("v *cos(u) -0.5*v^2*cos(2*u)");
  ycft_5->setText("-v*sin(u) -0.5*v^2*sin(2*u)");
  zcft_5->setText("4* v^1.5 *cos(3* u / 2) / 3") ;
  wcft_5->setText("cos(u)") ;
  tcft_5->setText("cos(u)") ;

  umin_5->setText("0") ;
  umax_5->setText("4*pi") ;
  vmin_5->setText("0") ;
  vmax_5->setText("1") ;

    }
    if(choix == QString("Cosinus")) {

  xcft_5->setText("u");
  ycft_5->setText("v");
  zcft_5->setText("sin(pi*((u)^2+(v)^2))/2") ;
  wcft_5->setText("cos(u)") ;
  tcft_5->setText("cos(u)") ; 
  umin_5->setText("-1") ; 
  umax_5->setText("1") ; 
  vmin_5->setText("-1") ;
  vmax_5->setText("1") ;

    }
      if(choix == QString("Shell")) {

  xcft_5->setText("1.2^v*(sin(u)^2 *sin(v))");
  ycft_5->setText("1.2^v*(sin(u)^2 *cos(v))");
  zcft_5->setText("1.2^v*(sin(u)*cos(u))") ;
  wcft_5->setText("cos(u)") ;
  tcft_5->setText("cos(u)") ;
  umin_5->setText("0") ;
  umax_5->setText("pi") ;
  vmin_5->setText("-pi/4") ;
  vmax_5->setText("5*pi/2") ;

    }
           if(choix == QString("Sphere")) {

  xcft_5->setText("cos(u)*cos(v)");
  ycft_5->setText("cos(u)*sin(v)");
  zcft_5->setText("sin(u)") ;
  wcft_5->setText("cos(u)") ;
  tcft_5->setText("cos(u)") ;
  umin_5->setText("-pi/2") ;
  umax_5->setText("pi/2") ;
  vmin_5->setText("0") ;
  vmax_5->setText("2*pi") ;

    }
              if(choix == QString("Steiner")) {

  xcft_5->setText("(sin(2 * u) * cos(v) * cos(v))");
  ycft_5->setText("(sin(u) * sin(2 * v))");
  zcft_5->setText("(cos(u) * sin(2 * v))") ;
  wcft_5->setText("cos(u)") ;
  tcft_5->setText("cos(u)") ;
  umin_5->setText("-pi/2") ;
  umax_5->setText("pi/2") ;
  vmin_5->setText("-pi/2") ;
  vmax_5->setText("pi/2") ;
    }
              if(choix == QString("Cross_cap")) {

  xcft_5->setText("(sin(u) * sin(2 * v) / 2)");
  ycft_5->setText("(sin(2 * u) * cos(v) * cos(v))");
  zcft_5->setText("(cos(2 * u) * cos(v) * cos(v))") ;
  wcft_5->setText("cos(u)") ;
  tcft_5->setText("cos(u)") ;
  umin_5->setText("-pi/2") ;
  umax_5->setText("pi/2") ;
  vmin_5->setText("-pi/2") ;
  vmax_5->setText("pi/2") ;

    }
               if(choix == QString("Boys")) {

  xcft_5->setText("(2/3)*(cos(u)*cos(2*v)+sqrt(2)*sin(u)*cos(v))*cos(u) /(sqrt(2) - sin(2*u)*sin(3*v))");
  ycft_5->setText("(2/3)*(cos(u)*sin(2*v)-sqrt(2)*sin(u)*sin(v))*cos(u) /(sqrt(2)-sin(2*u)*sin(3*v))");
  zcft_5->setText("sqrt(2)*cos(u)^2 / (sqrt(2) - sin(2*u)*sin(2*v))") ;
  wcft_5->setText("cos(u)") ;
  tcft_5->setText("cos(u)") ;
  umin_5->setText("-pi/2") ;
  umax_5->setText("pi/2") ;
  vmin_5->setText("-pi/2") ;
  vmax_5->setText("pi/2") ;

    }
      if(choix == QString("Torus")) {

  xcft_5->setText("(1+ 0.5*cos(u))*cos(v)");
  ycft_5->setText("(1+ 0.5*cos(u))*sin(v)");
  zcft_5->setText("0.5*sin(u)") ;
  wcft_5->setText("cos(u)") ;
  tcft_5->setText("cos(u)") ;
  umin_5->setText("0") ;
  umax_5->setText("2*pi");
  vmin_5->setText("0") ;
  vmax_5->setText("2*pi") ;
    }
      if(choix == QString("Klein")) {
   connectWidget2->objet->two_system = -1;   
   connectWidget2->objet->fourdimshapes = 1;
  xcft_5->setText("(3*(1+sin(v)) + 2*(1-cos(v)/2)*cos(u))*cos(v)") ;
  ycft_5->setText("(4+2*(1-cos(v)/2)*cos(u))*sin(v)");
  zcft_5->setText("-2*(1-cos(v)/2) * sin(u)");
  wcft_5->setText("cos(u)") ;
  tcft_5->setText("cos(u)") ;
  umin_5->setText("0") ;
  umax_5->setText("2*pi") ;
  vmin_5->setText("0") ;
  vmax_5->setText("2*pi") ;
    }
       if(choix == QString("Moebius")) {

  xcft_5->setText("cos(v)+u*cos(v/2)*cos(v)");
  ycft_5->setText("sin(v)+u*cos(v/2)*sin(v)");
  zcft_5->setText("u*sin(v/2)") ;
  wcft_5->setText("cos(u)") ;
  tcft_5->setText("cos(u)") ;
  umin_5->setText("-0.4") ;
  umax_5->setText("0.4") ;
  vmin_5->setText("0") ;
  vmax_5->setText("2*pi") ;

    }
          if(choix == QString("Riemann")) {

  xcft_5->setText("u*v");
  ycft_5->setText("v^2 - u^2");
  zcft_5->setText("30*u") ;
  wcft_5->setText("cos(u)") ;
  tcft_5->setText("cos(u)") ;
  umin_5->setText("-6") ;
  umax_5->setText("6") ;
  vmin_5->setText("-25") ;
  vmax_5->setText("25") ;

    }

          if(choix == QString("Klein_2")) {

  xcft_5->setText("(2 + cos(v/2)* sin(u) - sin(v/2)* sin(2 *u))* cos(v)");
  ycft_5->setText("(2 + cos(v/2)* sin(u) - sin(v/2)* sin(2 *u))* sin(v)");
  zcft_5->setText("sin(v/2)* sin(u) + cos(v/2) *sin(2* u)") ;
  wcft_5->setText("cos(u)") ;
  tcft_5->setText("cos(u)") ;
  umin_5->setText("0") ;
  umax_5->setText("2*pi") ;
  vmin_5->setText("0") ;
  vmax_5->setText("2*pi") ;

    }
           if(choix == QString("Henneberg")) {

  xcft_5->setText("2*sinh(u)*cos(v) -(2/3)*sinh(3*u)*cos(3*v)");
  ycft_5->setText("2*sinh(u)*sin(v) +(2/3)*sinh(3*u)*sin(3*v)");
  zcft_5->setText("2*cosh(2*u)*cos(2*v)") ;
  wcft_5->setText("cos(u)") ;
  tcft_5->setText("cos(u)") ;
  umin_5->setText("-1") ;
  umax_5->setText("1") ;
  vmin_5->setText("-pi/2") ;
  vmax_5->setText("pi/2") ;
    }

          if(choix == QString("Enneper")) {

  xcft_5->setText("u -u^3/3  + u*v^2");
  ycft_5->setText("v -v^3/3  + v*u^2");
  zcft_5->setText("u^2 - v^2") ;
  wcft_5->setText("cos(u)") ;
  tcft_5->setText("cos(u)") ;
  umin_5->setText("-2") ;
  umax_5->setText("2") ;
  vmin_5->setText("-2") ;
  vmax_5->setText("2") ;
    }
            if(choix == QString("Helix")) {

  xcft_5->setText("(1-0.1*cos(v))*cos(u)");
  ycft_5->setText("(1-0.1*cos(v))*sin(u)");
  zcft_5->setText("0.1*(sin(v) + u/1.7 -10)");
  wcft_5->setText("cos(u)") ;
  tcft_5->setText("cos(u)") ;
  umin_5->setText("0") ;
  umax_5->setText("4*pi") ;
  vmin_5->setText("0") ;
  vmax_5->setText("2*pi") ;

    }
           if(choix == QString("Hexaedron")) {

  xcft_5->setText("cos(v)^3*cos(u)^3");
  ycft_5->setText("sin(v)^3*cos(u)^3");
  zcft_5->setText("sin(u)^3") ;
  wcft_5->setText("cos(u)") ;
  tcft_5->setText("cos(u)") ;
  umin_5->setText("-1.3") ;
  umax_5->setText("1.3") ;
  vmin_5->setText("0") ;
  vmax_5->setText("2*pi") ;
    }

           if(choix == QString("Sphere_1")) {

  xcft_5->setText("cos(u)*cos(v)");
  ycft_5->setText("cos(u)*sin(v)");
  zcft_5->setText("sin(u)") ;
  wcft_5->setText("cos(u)") ;
  tcft_5->setText("cos(u)") ;
  umin_5->setText("-pi/2") ;
  umax_5->setText("pi/2") ;
  vmin_5->setText("0") ;
  vmax_5->setText("2*pi") ;

    }

             if(choix == QString("Catalan")) {

  xcft_5->setText("u-sin(u)*cosh(v)");
  ycft_5->setText("1-cos(u)*cosh(v)");
  zcft_5->setText("4*sin(1/2*u)*sinh(v/2)") ;
  wcft_5->setText("cos(u)") ;
  tcft_5->setText("cos(u)") ;
  umin_5->setText("-pi") ;
  umax_5->setText("3*pi") ;
  vmin_5->setText("-2") ;
  vmax_5->setText("2") ;
    }

             if(choix == QString("Toupie")) {

  xcft_5->setText("(abs(u)-1)^2 * cos(v)");
  ycft_5->setText("(abs(u)-1)^2 * sin(v)");
  zcft_5->setText("u") ;
  wcft_5->setText("cos(u)") ;
  tcft_5->setText("cos(u)") ;
  umin_5->setText("-1") ;
  umax_5->setText("1") ;
  vmin_5->setText("0") ;
  vmax_5->setText("2*pi") ;

    }
              if(choix == QString("Bonbon")) {

  xcft_5->setText("u");
  ycft_5->setText("cos (u)*cos (v)");
  zcft_5->setText("cos (u)*sin (v)") ;
  wcft_5->setText("cos(u)") ;
  tcft_5->setText("cos(u)") ;
  umin_5->setText("0") ;
  umax_5->setText("2*pi") ;
  vmin_5->setText("0") ;
  vmax_5->setText("2*pi") ;

    }
              if(choix == QString("Curve")) {

  xcft_5->setText("cos(2*u)");
  ycft_5->setText("sin(3*u)");
  zcft_5->setText("cos(u)") ;
  wcft_5->setText("cos(u)") ;
  tcft_5->setText("cos(u)") ;
  umin_5->setText("0") ;
  umax_5->setText("2*pi") ;
  vmin_5->setText("0") ;
  vmax_5->setText("0") ;
    }
                 if(choix == QString("Trumpet")) {

  xcft_5->setText("cos(u)*sin(v)");
  ycft_5->setText("sin(u)*sin(v)");
  zcft_5->setText("(cos(v)+log(tan(1/2*v)))") ;
  wcft_5->setText("cos(u)") ;
  tcft_5->setText("cos(u)") ;
  umin_5->setText("0") ; 
  umax_5->setText("2*pi") ;
  vmin_5->setText("0.03") ;
  vmax_5->setText("2") ;

    }

                 if(choix == QString("Helice_Curve")) {

  xcft_5->setText("sin(u)");
  ycft_5->setText("cos(u)");
  zcft_5->setText("(u^2)/100") ;
  wcft_5->setText("cos(u)") ;
  tcft_5->setText("cos(u)") ;
  umin_5->setText("0") ;
  umax_5->setText("6*pi") ;
  vmin_5->setText("0") ;
  vmax_5->setText("0") ;

    }
                   if(choix == QString("Cresent")) {

  xcft_5->setText("(2 + sin(2* pi* u) *sin(2 *pi* v)) *sin(3* pi *v)");
  ycft_5->setText("(2 + sin(2* pi *u) *sin(2 *pi *v)) *cos(3* pi *v)");
  zcft_5->setText("cos(2* pi *u) *sin(2* pi* v) + 4 *v - 2") ;
  wcft_5->setText("cos(u)") ;
  tcft_5->setText("cos(u)") ;
  umin_5->setText("0") ; 
  umax_5->setText("1") ; 
  vmin_5->setText("0") ; 
  vmax_5->setText("1") ; 

    }

                  if(choix == QString("Shoe")) {

  xcft_5->setText("u");
  ycft_5->setText("v");
  zcft_5->setText("1/3*u^3  - 1/2*v^2") ;
  wcft_5->setText("cos(u)") ;
  tcft_5->setText("cos(u)") ;
  umin_5->setText("-2") ;
  umax_5->setText("2") ;
  vmin_5->setText("-2") ;
  vmax_5->setText("2") ;

    }
                if(choix == QString("Snake")) {

  xcft_5->setText("1.2*(1 -v/(2*pi))*cos(3*v)*(1 + cos(u)) + 3*cos(3*v)");
  ycft_5->setText("1.2*(1 -v/(2*pi))*sin(3*v)*(1 + cos(u)) + 3*sin(3*v)");
  zcft_5->setText("9*v/(2*pi) + 1.2*(1 - v/(2*pi))*sin(u)") ;
  wcft_5->setText("cos(u)") ;
  tcft_5->setText("cos(u)") ;
  umin_5->setText("0") ;
  umax_5->setText("2*pi") ;
  vmin_5->setText("0") ;
  vmax_5->setText("2*pi") ;

    }

                  if(choix == QString("Roman")) {

  xcft_5->setText("1/2*sin(2*u)*sin(v)^2");
  ycft_5->setText("1/2*sin(u)*cos(2*v)");
  zcft_5->setText("1/2*cos(u)*sin(2*v)") ;
  wcft_5->setText("cos(u)") ;
  tcft_5->setText("cos(u)") ;
  umin_5->setText("0") ; 
  umax_5->setText("pi") ; 
  vmin_5->setText("-pi/2") ; 
  vmax_5->setText("pi/2") ; 

    } 
    
                    if(choix == QString("Hyperhelicoidal")) {

  xcft_5->setText("(sinh(v)*cos(3*u))/(1+cosh(u)*cosh(v))");
  ycft_5->setText("(sinh(v)*sin(3*u))/(1+cosh(u)*cosh(v))");
  zcft_5->setText("(cosh(v)*sinh(u))/(1+cosh(u)*cosh(v))") ;
  wcft_5->setText("cos(u)") ;
  tcft_5->setText("cos(u)") ;
  umin_5->setText("-pi") ; 
  umax_5->setText("pi") ; 
  vmin_5->setText("-pi") ; 
  vmax_5->setText("pi") ; 
  
    }
    

  
                    if(choix == QString("Horn")) {

  xcft_5->setText("(2 + u*cos(v))*sin(2*pi*u)");
  ycft_5->setText("(2 + u*cos(v))*cos(2*pi*u) + 2*u");
  zcft_5->setText("u *sin(v)") ;
  wcft_5->setText("cos(u)") ;
  tcft_5->setText("cos(u)") ;
  umin_5->setText("0") ; 
  umax_5->setText("1") ; 
  vmin_5->setText("0") ; 
  vmax_5->setText("2*pi") ; 

    }
  
  
    
                   if(choix == QString("Helicoidal")) {

  xcft_5->setText("sinh(v)*sin(u)");
  ycft_5->setText("-sinh(v)*cos(u)");
  zcft_5->setText("3*u") ;
  wcft_5->setText("cos(u)") ;
  tcft_5->setText("cos(u)") ;
  umin_5->setText("-pi") ; 
  umax_5->setText("pi") ; 
  vmin_5->setText("-pi") ; 
  vmax_5->setText("pi") ; 
  
    }   
                    if(choix == QString("Catenoid")) {

  xcft_5->setText("2*cosh(v/2)*cos(u)");
  ycft_5->setText("2*cosh(v/2)*sin(u)");
  zcft_5->setText("v") ;
  wcft_5->setText("cos(u)") ;
  tcft_5->setText("cos(u)") ;
  umin_5->setText("-pi") ; 
  umax_5->setText("pi") ; 
  vmin_5->setText("-pi") ; 
  vmax_5->setText("pi") ; 
  
    }  
                   if(choix == QString("Kuen")) {

  xcft_5->setText("(2*(cos(u) + u*sin(u))*sin(v))/(1+ u^2*sin(v)^2)");
  ycft_5->setText("(2*(sin(u) - u*cos(u))*sin(v))/(1+ u^2*sin(v)^2)");
  zcft_5->setText("log(tan(1/2 *v)) + (2*cos(v))/(1+ u^2*sin(v)^2)") ;
  wcft_5->setText("cos(u)") ;
  tcft_5->setText("cos(u)") ;
  umin_5->setText("0") ; 
  umax_5->setText("2*pi") ; 
  vmin_5->setText("0.01") ; 
  vmax_5->setText("pi-0.01") ; 
    }   


                    if(choix == QString("Hellipticparaboloid")) {

  xcft_5->setText("v*2*cos(u)");
  ycft_5->setText("v*sin(u)");
  zcft_5->setText("v^2") ;
  wcft_5->setText("cos(u)") ;
  tcft_5->setText("cos(u)") ;
  umin_5->setText("0") ; 
  umax_5->setText("2*pi") ; 
  vmin_5->setText("0") ; 
  vmax_5->setText("2") ; 
    }


                    if(choix == QString("Enneper_2")) {

  xcft_5->setText("u*cos(v)-u^3/3*cos(3*v)");
  ycft_5->setText("-u*sin(v)-u^(3)/3*sin(3*v)");
  zcft_5->setText("u^2*cos(2*v)") ;
  wcft_5->setText("cos(u)") ;
  tcft_5->setText("cos(u)") ;
  umin_5->setText("0") ; 
  umax_5->setText("1.2") ; 
  vmin_5->setText("-pi") ; 
  vmax_5->setText("pi") ; 
    } 
   
                    if(choix == QString("Stereosphere")) {

  xcft_5->setText("2.*u/(u*u+v*v+1.)");
  ycft_5->setText("2.*v/(u*u+v*v+1.)");
  zcft_5->setText("(u*u+v*v-1.)/(u*u+v*v+1.)") ;
  wcft_5->setText("cos(u)") ;
  tcft_5->setText("cos(u)") ;
  umin_5->setText("-2") ; 
  umax_5->setText("2") ; 
  vmin_5->setText("-2") ; 
  vmax_5->setText("2") ; 

    }

                    if(choix == QString("Cliffordtorus")) {

  xcft_5->setText("cos(u+v)/(sqrt(2.)+cos(v-u))");
  ycft_5->setText("sin(u+v)/(sqrt(2.)+cos(v-u))");
  zcft_5->setText("sin(v-u)/(sqrt(2.)+cos(v-u))");
  wcft_5->setText("cos(u)") ;
  tcft_5->setText("cos(u)") ;
  umin_5->setText("0") ; 
  umax_5->setText("pi") ; 
  vmin_5->setText("0") ; 
  vmax_5->setText("2*pi") ; 

    }   

  
 
                    if(choix == QString("Fresnel_1")) {

  xcft_5->setText("cos(u)*cos(v)/(-2.*sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))*cos((acos(-(-0.941/6.+0.374*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4)-1.309/6.*((cos(u)^6+sin(u)^6)*cos(v)^6+sin(v)^6)-1.221*cos(u)^2*cos(v)^4*sin(u)^2*sin(v)^2)/sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))^3)+pi)/3.)+0.8)");
  ycft_5->setText("sin(u)*cos(v)/(-2.*sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))*cos((acos(-(-0.941/6.+0.374*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4)-1.309/6.*((cos(u)^6+sin(u)^6)*cos(v)^6+sin(v)^6)-1.221*cos(u)^2*cos(v)^4*sin(u)^2*sin(v)^2)/sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))^3)+pi)/3.)+0.8)");
  zcft_5->setText("sin(v)/(-2.*sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))*cos((acos(-(-0.941/6.+0.374*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4)-1.309/6.*((cos(u)^6+sin(u)^6)*cos(v)^6+sin(v)^6)-1.221*cos(u)^2*cos(v)^4*sin(u)^2*sin(v)^2)/sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))^3)+pi)/3.)+0.8)") ;
  wcft_5->setText("cos(u)") ;
  tcft_5->setText("cos(u)") ;
  umin_5->setText("0") ;
  umax_5->setText("2*pi") ;
  vmin_5->setText("-pi/2") ;
  vmax_5->setText("pi/2") ;

    }

                    if(choix == QString("Fresnel_2")) {

  xcft_5->setText("cos(u)*cos(v)/(-2.*sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))*cos((acos(-(-0.941/6.+0.374*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4)-1.309/6.*((cos(u)^6+sin(u)^6)*cos(v)^6+sin(v)^6)-1.221*cos(u)^2*cos(v)^4*sin(u)^2*sin(v)^2)/sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))^3)-pi)/3.)+0.8)");
  ycft_5->setText("sin(u)*cos(v)/(-2.*sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))*cos((acos(-(-0.941/6.+0.374*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4)-1.309/6.*((cos(u)^6+sin(u)^6)*cos(v)^6+sin(v)^6)-1.221*cos(u)^2*cos(v)^4*sin(u)^2*sin(v)^2)/sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))^3)-pi)/3.)+0.8)");
  zcft_5->setText("sin(v)/(-2.*sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))*cos((acos(-(-0.941/6.+0.374*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4)-1.309/6.*((cos(u)^6+sin(u)^6)*cos(v)^6+sin(v)^6)-1.221*cos(u)^2*cos(v)^4*sin(u)^2*sin(v)^2)/sqrt(0.965/3.-0.935/3.*((cos(u)^4+sin(u)^4)*cos(v)^4+sin(v)^4))^3)-pi)/3.)+0.8)") ;
  wcft_5->setText("cos(u)") ;
  tcft_5->setText("cos(u)") ;
  umin_5->setText("0") ;
  umax_5->setText("2*pi") ;
  vmin_5->setText("-pi/2") ;
  vmax_5->setText("pi/2") ;

    }

  connectWidget2->objet->fivedimshapes = 1;

  connectWidget2->objet->expression_X = xcft_5->text();
  connectWidget2->objet->expression_Y = ycft_5->text();
  connectWidget2->objet->expression_Z = zcft_5->text();
  connectWidget2->objet->expression_W = wcft_5->text();
  connectWidget2->objet->expression_T = tcft_5->text();

  connectWidget2->objet->inf_u = umin_5->text();
  connectWidget2->objet->sup_u = umax_5->text();
  connectWidget2->objet->inf_v = vmin_5->text();
  connectWidget2->objet->sup_v = vmax_5->text();
 
  /// Set the right Window for drawing :
 tabsurf->setCurrentPage(0);
 if(paramwidgetstack == 1) glboxclicked();
 
  //Process the new surface :
ParametricSurfaceProcess();

}


//====================================
void k3dsurface::Library_Path_AddButton_clicked()
{
    QString dirname = QFileDialog::getExistingDirectory(
            "",
            this,
            "open directory dialog",
            tr("Please choose the directory containing the libs") );
    if (dirname.length() && !Library_PathListview_2->findItem(dirname,0))
    {
        new QListViewItem(Library_PathListview_2,dirname);
    }
    
    LibraryPath += " +L"+dirname;
}


//====================================
void k3dsurface::Frames_Path_clicked()
{
/*
    QString dirname = QFileDialog::getExistingDirectory(
            "",
            this,
            "open directory dialog",
            tr("Please choose the directory containing the libs") );

    Input_Dir_NameEdit->setText(dirname);
    connectWidget2->directory = dirname;
    
*/
}

//====================================

void k3dsurface::isopage_selected( const QString & choice )
{ 
int current_pag = tabsurf->currentPageIndex();
if (choice =="Parametric")  { ParametricSurfaceProcess();
                                          ParametricSurfaceProcess(); }   //that's a bug...
else if (choice =="IsoSurface") {ProcessNewIsoSurface( ); 
                                              ProcessNewIsoSurface( ); }  //that's a bug...
else  if(choice =="Pov") {
 if(current_pag == 0)  {
   tabsurf->setCurrentPage(0);
                if(paramwidgetstack == 1) glboxclicked();
               }
              else if(current_pag == 1) {
               tabsurf->setCurrentPage(1);
               if(isowidgetstack == 1) isogl_clicked();
              }
    }
else if(choice =="ND") {
      if(current_pag != 0)    tabsurf->setCurrentPage(0);
      if(paramwidgetstack == 1) glboxclicked();
    }
}
//====================================
void k3dsurface::tabWidget7_selected( const QString & )
{ int current_pag = tabWidget7->currentPageIndex();

if(current_pag == 0) {   tabsurf->setCurrentPage(0);
 if(paramwidgetstack != 1) glboxclicked();
    }
else { tabsurf->setCurrentPage(1);
 if(isowidgetstack != 1) isogl_clicked();
    }
}

//====================================
void k3dsurface::add_condt_clicked()
{
 isoWidget->IsoObjet->CNDDraw*= -1;
 IsoGlWidget->cnd();
 IsoPageUpdate();
}

//====================================
void k3dsurface::cndmesh_clicked()
{
 isoWidget->IsoObjet->CNDMesh*= -1;
 IsoGlWidget->cndmesh();
 IsoPageUpdate();
}

//====================================
void k3dsurface::border_clicked()
{
 isoWidget->IsoObjet->BorderDraw*= -1;
 IsoGlWidget->drawborder();
 IsoPageUpdate();
}

//====================================
void k3dsurface::parametrics_clicked()
{
implicit_param = 1; implicit_spheric = -1; implicit_cylindric = -1;
implicit->setText("F(x,y,z,t) =");
}

//====================================
void k3dsurface::spherics_clicked()
{
implicit_param = -1; implicit_spheric = 1; implicit_cylindric = -1;
implicit->setText("F(R,u,v,t) =");
}

///====================================///
void k3dsurface::sylindrics_clicked()
{
implicit_param = -1; implicit_spheric = -1; implicit_cylindric = 1;
implicit->setText("F(R,Z,u,t) =");
}

///====================================///
void k3dsurface::tabsurf_selected( const QString &  )
{
}

///====================================///

int nb_lig=24, nb_col=24, old_nb_lig=0,
    old_nb_col=0, coupure_lig=0, coupure_col=0,
    old_coupure_lig=0, old_coupure_col=0;
///====================================///
void k3dsurface::MakeACopy() {
    int i, j, k, l;

    nb_lig = ParamGlWidget->nb_ligne = connectWidget2->objet->nb_ligne;
    nb_col = ParamGlWidget->nb_colone = connectWidget2->objet->nb_colone;
    coupure_col = ParamGlWidget->coupure_col = connectWidget2->objet->coupure_col;
    coupure_lig = ParamGlWidget->coupure_ligne = connectWidget2->objet->coupure_ligne;
   ParamGlWidget->PolyNumber    = 4*(nb_lig - coupure_lig -1)*(nb_col -coupure_col -1);
   ParamGlWidget->VertexNumber = 6*nb_col*nb_lig;
/// generation of the Normals-Vertex Array :
    l=0;
    for (i=0; i< nb_lig; i++)
      for (j=0; j< nb_col; j++) {
     ParamGlWidget->ArrayNorVer_local[l  ] = connectWidget2->objet->Nor2[3*i  ][j];
     ParamGlWidget->ArrayNorVer_local[l+1] = connectWidget2->objet->Nor2[3*i+1][j];
     ParamGlWidget->ArrayNorVer_local[l+2] = connectWidget2->objet->Nor2[3*i+2][j];
     ParamGlWidget->ArrayNorVer_local[l+3] = connectWidget2->objet->Tre2[3*i  ][j];
     ParamGlWidget->ArrayNorVer_local[l+4] = connectWidget2->objet->Tre2[3*i+1][j];
     ParamGlWidget->ArrayNorVer_local[l+5] = connectWidget2->objet->Tre2[3*i+2][j];
     l+=6;
    }
/// generation of the Index Array :
   k=0;
   for (i=0; i< nb_lig - coupure_lig -1; i++)
      for (j=0; j< nb_col - coupure_col -1; j++) {
     ParamGlWidget->PolyIndices_local[k  ] = i*nb_col+ j;
     ParamGlWidget->PolyIndices_local[k+1] = (i+1)*nb_col + j;
     ParamGlWidget->PolyIndices_local[k+2] = (i+1)*nb_col + (j+1);
     ParamGlWidget->PolyIndices_local[k+3] = i*nb_col + (j+1);
     k+=4;
    }
}

///====================================///
void k3dsurface::tabsurf_currentChanged( QWidget * /*glw*/ )
{/*
static int previousWindow = 0; //Parametric Window

    QString name = glw->name();
    if(name == QString("GLPage")) {
 if(previousWindow == 0){
connectWidget2->objet->SpecialMorph_2(ParamGlWidget->ArrayNorVer_local, ParamGlWidget->PolyIndices_local, ParamGlWidget->NbPolygnNbVertex, 1);
ParamGlWidget->PolyNumber = connectWidget2->objet->NbPolygn;
      ParamGlWidget->initializeGL();
      ParamGlWidget->TypeTriangle = -1;
 }
 else if(previousWindow ==1){
isoWidget->IsoObjet->SpecialMorph_2(ParamGlWidget->ArrayNorVer_local, ParamGlWidget->PolyIndices_local, ParamGlWidget->NbPolygnNbVertex, 1);
ParamGlWidget->initializeGL();
ParamGlWidget->PolyNumber  = 3*isoWidget->IsoObjet->NbTriangleIsoSurface;
ParamGlWidget->TypeTriangle = 1;
 }

ParamGlWidget->updateGL();}
    else if(name == QString("IsoPage")) {previousWindow =1; isoWidget->IsoMorphCompute();}
    else if(name == QString("ParaPage")) {previousWindow =0; connectWidget2->valueChanged();}*/
}

///====================================///
void k3dsurface::DrawInOpenGlArea() {
      MakeACopy();
      ParamGlWidget->initializeGL();
      ParamGlWidget->updateGL();
}

///++++++++++++++++++++++++++++++++++++++++///
void k3dsurface::UpdateActivatedWin()
{
if( paramwidgetstack == 1) ParamGlWidget->updateGL();
 else connectWidget2->update();
}

///++++++++++++++++++++++++++++++++++++++++///
void k3dsurface::cutline_valueChanged(int ctline )
{
  connectWidget2->objet->coupure_ligne = ParamGlWidget->coupure_ligne = ctline;
  ParamGlWidget->CutLineIndex(ctline);
  UpdateActivatedWin();
}

///++++++++++++++++++++++++++++++++++++++++///
void k3dsurface::cutcolumn_valueChanged( int ctcl)
{
  connectWidget2->objet->coupure_col = ParamGlWidget->coupure_col = ctcl;
  ParamGlWidget->CutColIndex(ctcl);
  UpdateActivatedWin();
}

///++++++++++++++++++++++++++++++++++++++++///
void k3dsurface::mesh_clicked()
{
  connectWidget2->objet->mesh *= -1;
  ParamGlWidget->meshOk();
  UpdateActivatedWin();
}

///++++++++++++++++++++++++++++++++++++++++///
void k3dsurface::box_clicked()
{
  connectWidget2->objet->box *= -1;
  ParamGlWidget->boxOk();
  UpdateActivatedWin();
}

///++++++++++++++++++++++++++++++++++++++++///
void k3dsurface::infos_clicked()
{
  connectWidget2->objet->infos  *= -1;
  ParamGlWidget->infosOk();
  UpdateActivatedWin();
}

///++++++++++++++++++++++++++++++++++++++++///
void k3dsurface::inter_clicked()
{
  connectWidget2->objet->interior_surface  *= -1;
  ParamGlWidget->backSurf();
  UpdateActivatedWin();  
}

///++++++++++++++++++++++++++++++++++++++++///
void k3dsurface::exter_clicked()
{
  connectWidget2->objet->exterior_surface  *= -1;
  ParamGlWidget->frontSurf();
  UpdateActivatedWin();
}

///++++++++++++++++++++++++++++++++++++++++///
void k3dsurface::Axes_ok_clicked()
{
  connectWidget2->objet->drawaxes_ok  *= -1;
  ParamGlWidget->axeOk();
    //UpdateActivatedWin();
int current_pag = tabsurf->currentPageIndex();
if(current_pag != 0) tabsurf->setCurrentPage(0);
if( paramwidgetstack == 1) ParamGlWidget->updateGL();
 else   connectWidget2->valueChanged();
}

///++++++++++++++++++++++++++++++++++++++++///
void k3dsurface::draw_norm_clicked()
{
  connectWidget2->objet->draw_poly_normals  *= -1;
  ParamGlWidget->normOk();
  UpdateActivatedWin();
}

///++++++++++++++++++++++++++++++++++++++++///
void k3dsurface::linecolumn_valueChanged( int cl)
{
    connectWidget2->objet->nb_licol = cl;
    connectWidget2->objet->nb_colone  = ParamGlWidget->nb_colone = cl;
    connectWidget2->objet->nb_ligne  = ParamGlWidget->nb_ligne = cl;

    /// process the new surface only if Gl window is active
    ParametricSurfaceProcess();
/*    
     if(current_pag ==2){
connectWidget2->objet->SpecialMorph_2(ParamGlWidget->ArrayNorVer_local, ParamGlWidget->PolyIndices_local, ParamGlWidget->NbPolygnNbVertex, 1);
      ParamGlWidget->initializeGL();
      ParamGlWidget->TypeTriangle = -1;
      ParamGlWidget->updateGL();
      }
      else if(current_pag == 0) {
      connectWidget2->objet->fct_bouton_Morph3();
      connectWidget2->update();
      }
*/
}

///++++++++++++++++++++++++++++++++++++++++///
void k3dsurface::latency2_valueChanged( int lat)
{
 connectWidget2->objet->latence = connectWidget2->latence = lat;
 ParamGlWidget->restarttimer(lat);
 IsoGlWidget->restarttimer(lat);
}

///++++++++++++++++++++++++++++++++++++++++///
void k3dsurface::xg_valueChanged( int cl)
{
isoWidget->IsoObjet->nb_ligne  = cl;
IsoGlWidget->isoline = cl;
    // process the new surface
   ProcessNewIsoSurface( );
}

///++++++++++++++++++++++++++++++++++++++++///
void k3dsurface::yg_valueChanged( int cl)
{
isoWidget->IsoObjet->nb_colon  = cl;
IsoGlWidget->isocolumn = cl;
    // process the new surface
   ProcessNewIsoSurface( );
}
///++++++++++++++++++++++++++++++++++++++++///
void k3dsurface::zg_valueChanged( int cl)
{
isoWidget->IsoObjet->nb_depth  = cl;
IsoGlWidget->isodepth = cl;
    // process the new surface
   ProcessNewIsoSurface( );
}

///++++++++++++++++++++++++++++++++++++++++///
void k3dsurface::DrawIso( )
{  int current_pag = tabsurf->currentPageIndex();

if(current_pag == 2)  {
isoWidget->IsoObjet->SpecialMorph_2(
         IsoGlWidget->ArrayNorVer_local,
         IsoGlWidget->PolyIndices_local,
         IsoGlWidget->NbPolygnNbVertex,
         IsoGlWidget->TypeIsoSurfaceTriangleListeCND,
         &(IsoGlWidget->VertexNumber),
         1);
ParamGlWidget->initializeGL();
ParamGlWidget->PolyNumber  = 3*isoWidget->IsoObjet->NbTriangleIsoSurface;
ParamGlWidget->updateGL();
}
else  if(current_pag == 1) {
    isoWidget->IsoMorphCompute();
    isoWidget->update();
}
}

///++++++++++++++++++++++++++++++++++++++++///
void k3dsurface::isogl_clicked(){
   isowidgetstack *=-1;
isowidgetstack   == 1 ? IsoWidgetStack->raiseWidget ( 0 ) : IsoWidgetStack->raiseWidget ( 1 );
if(isowidgetstack   == 1 ) {
  glisobutton->setText("OpenGL \n (ON)") ;
  tabsurf->setTabLabel (IsoPage, "IsoSurface (OpenGL ON)");
  morphanimgroupBox->setEnabled(TRUE); }
else {
 glisobutton->setText("OpenGL \n (OFF)");
 tabsurf->setTabLabel (IsoPage, "IsoSurface (OpenGL OFF)");
 morphanimgroupBox->setEnabled(FALSE); 
if (isoWidget->IsoObjet->nb_depth >29 ||
    isoWidget->IsoObjet->nb_colon >29 ||
    isoWidget->IsoObjet->nb_ligne >29 )
isoWidget->IsoObjet->nb_depth = isoWidget->IsoObjet->nb_colon = isoWidget->IsoObjet->nb_ligne = 26;
xyzg->setValue(26);
}
   // process the new surface:
   ProcessNewIsoSurface( );
   ProcessNewIsoSurface( ); // That's a bug...
}

///++++++++++++++++++++++++++++++++++++++++///
void k3dsurface::IsoPageUpdate()
{   int current_pag = tabsurf->currentPageIndex();
    if(current_pag !=1) tabsurf->setCurrentPage(1);

    if(isowidgetstack == 1) IsoGlWidget->updateGL();
    else  isoWidget->update();
}

///++++++++++++++++++++++++++++++++++++++++///
void k3dsurface::IsoLine_clicked()
{
    IsoGlWidget->lineOk();
    isoWidget->lineOk();
/// Update Iso page :
    IsoPageUpdate();
}

///++++++++++++++++++++++++++++++++++++++++///
void k3dsurface::isoaxe_clicked()
{
IsoGlWidget->axeOk();
isoWidget->Axes_draw(); 
/// Update Iso page :
    IsoPageUpdate();
}

///++++++++++++++++++++++++++++++++++++++++///
void k3dsurface::glboxclicked()
{  paramwidgetstack *= -1;
    paramwidgetstack == 1 ? ParaWidgetStack->raiseWidget ( 0 ) : ParaWidgetStack->raiseWidget ( 1 );
    if(paramwidgetstack   == 1) {
     glparbutton->setText("OpenGL\n(ON)") ;
     ParaPage->setCaption("Parametric (OpenGL ON)") ;
     tabsurf->setTabLabel (ParaPage, "Parametric (OpenGL ON)");
    }
    else {
      glparbutton->setText("OpenGL\n(OFF)");
      tabsurf->setTabLabel (ParaPage, "Parametric (OpenGL OFF)");
    }
     // process the new surface
ParametricSurfaceProcess();
ParametricSurfaceProcess();  // That's a bug...
}

//========================================//
void k3dsurface::step_morph(int cl)
{
 /*   
QMessageBox message ;

if(ParamGlWidget->timeractif()) {
    message.setText("Stop Parametric OpenGl Animation");
    message.adjustSize () ;
    message.exec();
    tstep->setValue(NbStep);
    return;
}

if(IsoGlWidget->timeractif()) {
    message.setText("Stop Isosurface OpenGl Animation");
    message.adjustSize () ;
    message.exec();
    tstep->setValue(NbStep);
    return;
}
*/
NbStep =cl;
connectWidget2->step_morph(cl);

}

//========================================/
void k3dsurface::secondsystativation_clicked()
{
connectWidget2->objet->two_system *= -1;
}

//========================================/
void k3dsurface::checkBox240_clicked()
{
 int current_pag = tabsurf->currentPageIndex();
    if(current_pag == 0) ParamGlWidget->smoothpoly();
    else if (current_pag == 1) IsoGlWidget->smoothpoly();
}

//========================================/
void k3dsurface::checkBox241_clicked()
{
 int current_pag = tabsurf->currentPageIndex();
    if(current_pag == 0) ParamGlWidget->smoothline();
    else if (current_pag == 1) IsoGlWidget->smoothline();
    
}

//========================================/
void k3dsurface::FogBox_clicked()
{
 int current_pag = tabsurf->currentPageIndex();
    if(current_pag == 0) ParamGlWidget->fog();
    else if (current_pag == 1) IsoGlWidget->fog();
}
//========================================/
void k3dsurface::PlanBox_clicked()
{
 int current_pag = tabsurf->currentPageIndex();
    if(current_pag == 0) ParamGlWidget->plan();
    else if (current_pag == 1) IsoGlWidget->plan();
}
//========================================/
void k3dsurface::comboBox18_activated( int ch )
{
           if ( ch ==0) checkBox240_clicked();
    else if (ch == 1) checkBox241_clicked();
    else if (ch == 2) PlanBox_clicked();
    else if (ch == 3) FogBox_clicked();
}




//========================================/
void k3dsurface::screenshot_clicked()
{ int current_pag = tabsurf->currentPageIndex();
  if(current_pag == 0) 
 paramwidgetstack == 1 ? ParamGlWidget->screenshot() : connectWidget2->screenshot();
  else if(current_pag == 1) 
  isowidgetstack == 1 ? IsoGlWidget->screenshot() : isoWidget->screenshot(); 
}

//========================================/
void k3dsurface::quality_valueChanged( int cl)
{
    IsoGlWidget->quality(cl);
    ParamGlWidget->quality(cl);
    isoWidget->quality(cl);
     connectWidget2->quality(cl);
}

//========================================/
void k3dsurface::png_clicked()
{
    IsoGlWidget->png();
    ParamGlWidget->png();
    isoWidget->png();
    connectWidget2->png();
}

//========================================/
void k3dsurface::bmp_clicked()
{
    IsoGlWidget->bmp();
    ParamGlWidget->bmp();
    isoWidget->bmp();
    connectWidget2->bmp();
}

//========================================/
void k3dsurface::jpg_clicked()
{
    IsoGlWidget->jpg();
    ParamGlWidget->jpg();
    isoWidget->jpg();
    connectWidget2->jpg();
}

//========================================/
void k3dsurface::xyzg_valueChanged( int cl)
{
if(isowidgetstack == -1) {
    if( cl < 30) {
isoWidget->IsoObjet->nb_depth = isoWidget->IsoObjet->nb_colon = isoWidget->IsoObjet->nb_ligne = cl;
IsoGlWidget->isoline = IsoGlWidget->isocolumn = IsoGlWidget->isodepth = cl;
    // process the new surface
   ProcessNewIsoSurface( );
    }

}
else {
isoWidget->IsoObjet->nb_depth = isoWidget->IsoObjet->nb_colon = isoWidget->IsoObjet->nb_ligne = cl;
IsoGlWidget->isoline = IsoGlWidget->isocolumn = IsoGlWidget->isodepth = cl;
    // process the new surface
   ProcessNewIsoSurface( );  
}
}
//========================================/
void k3dsurface::xyzg_2_valueChanged( int cl)
{
    isoWidget->IsoObjet->CutDepth = isoWidget->IsoObjet->CutColon = isoWidget->IsoObjet->CutLigne = cl;
    IsoGlWidget->cpisoline = IsoGlWidget->cpisocolumn = IsoGlWidget->cpisodepth = cl;
    // process the new surface
   ProcessNewIsoSurface( );
}

//========================================/
void k3dsurface::xg_2_valueChanged( int cl)
{
     isoWidget->IsoObjet->CutLigne = cl;
     IsoGlWidget->cpisoline = cl;
    // process the new surface
   ProcessNewIsoSurface( );
}

//========================================/
void k3dsurface::yg_2_valueChanged( int cl)
{
    isoWidget->IsoObjet->CutColon = cl;
    IsoGlWidget->cpisocolumn = cl;
    // process the new surface
   ProcessNewIsoSurface( );
}

//========================================/
void k3dsurface::zg_2_valueChanged( int cl)
{
    isoWidget->IsoObjet->CutDepth = cl;
    IsoGlWidget->cpisodepth = cl;
    // process the new surface
   ProcessNewIsoSurface( );
}

//========================================/
void k3dsurface::scalexvalue_valueChanged( int n)
{
connectWidget2->objet->scalex(n);
//UpdateActivatedWin();
ParametricSurfaceProcess();
}

//========================================/
void k3dsurface::scaleyvalue_valueChanged( int n)
{
connectWidget2->objet->scaley(n);
//UpdateActivatedWin();
ParametricSurfaceProcess();
}

//========================================/
void k3dsurface::scalezvalue_valueChanged( int n)
{
connectWidget2->objet->scalez(n);
//UpdateActivatedWin();
ParametricSurfaceProcess();
}


//========================================/
void k3dsurface::scrollBar81_3_valueChanged( int n)
{
    connectWidget2->nbtwistex_changed(n);
   //UpdateActivatedWin();
   ParametricSurfaceProcess();
}

//========================================/
void k3dsurface::scrollBar20_3_valueChanged( int n)
{
    connectWidget2->coeffrayonx_changed(n);
   //UpdateActivatedWin();
   ParametricSurfaceProcess();
}


//========================================/
void k3dsurface::scrollBar81_2_valueChanged( int n)
{
    connectWidget2->nbtwistey_changed(n);
   //UpdateActivatedWin();
   ParametricSurfaceProcess();
}

//========================================/
void k3dsurface::scrollBar20_2_valueChanged( int n)
{
    connectWidget2->coeffrayony_changed(n);
   //UpdateActivatedWin();
   ParametricSurfaceProcess();
}

//========================================/
void k3dsurface::scrollBar81_valueChanged( int n)
{
    connectWidget2->nbtwistez_changed(n);
   //UpdateActivatedWin();
   ParametricSurfaceProcess();
}

//========================================/
void k3dsurface::scrollBar20_valueChanged( int n)
{
    connectWidget2->coeffrayonz_changed(n);
   //UpdateActivatedWin();
   ParametricSurfaceProcess();
}

//========================================/
void k3dsurface::scalexvalue_2_valueChanged( int  n)
{
   isoWidget->IsoObjet->scalex(n);
   //IsoPageUpdate();
   ProcessNewIsoSurface( );
}

//========================================/
void k3dsurface::scaleyvalue_2_valueChanged( int  n)
{
   isoWidget->IsoObjet->scaley(n);
   //IsoPageUpdate();
   ProcessNewIsoSurface( );
}

//========================================/
void k3dsurface::scalezvalue_2_valueChanged( int  n)
{
   isoWidget->IsoObjet->scalez(n);
   //IsoPageUpdate();
   ProcessNewIsoSurface( );
}

//========================================/
void k3dsurface::scrollBar81_3_2_valueChanged( int n)
{
   isoWidget->nbtwistex_changed(n);
   ProcessNewIsoSurface( );
}

//========================================/
void k3dsurface::scrollBar81_2_2_valueChanged( int n)
{
   isoWidget->nbtwistey_changed(n);
   ProcessNewIsoSurface( );
}

//========================================/
void k3dsurface::scrollBar81_4_valueChanged( int n)
{
   isoWidget->nbtwistez_changed(n);
   ProcessNewIsoSurface( );
}
//========================================/
void k3dsurface::scrollBar81_4_valueChanged2( )
{
   ProcessNewIsoSurface( );
}
//========================================/
void k3dsurface::anim_2_toggle()
{ 
anim_2->toggle();
}

void k3dsurface::morph_2_toggle(){morph_2->toggle();};
void k3dsurface::Isomesh_toggle(){Isomesh->toggle();};
void k3dsurface::IsoLine_toggle(){IsoLine->toggle();};
void k3dsurface::isoinfos_toggle(){isoinfos->toggle();};
void k3dsurface::isoaxe_toggle(){isoaxe->toggle();};
void k3dsurface::mesh_toggle(){mesh->toggle();};
void k3dsurface::Axes_ok_toggle(){Axes_ok->toggle();};
void k3dsurface::box_toggle(){box->toggle();};
void k3dsurface::infos_toggle(){infos->toggle();};
void k3dsurface::draw_norm_toggle(){draw_norm->toggle();};
void k3dsurface::anim_toggle(){anim->toggle();};
void k3dsurface::morph_toggle(){morph->toggle();};
void k3dsurface::exter_toggle(){exter->toggle();};
//void k3dsurface::morph_toggle(){morph->toggle();};
///++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++///
void k3dsurface::pushButton69_clicked()
{
/// IsoSurface Page :
drawingoptions *newpanl = new drawingoptions();
connect( newpanl->xyzg, SIGNAL( valueChanged(int) ), this, SLOT(xyzg_valueChanged(int)));
connect( newpanl->xg, SIGNAL( valueChanged(int) ), this, SLOT(xg_valueChanged(int)));
connect( newpanl->yg, SIGNAL( valueChanged(int) ), this, SLOT(yg_valueChanged(int)));
connect( newpanl->zg, SIGNAL( valueChanged(int) ), this, SLOT(zg_valueChanged(int)));

connect( newpanl->xyzg_2, SIGNAL( valueChanged(int) ), this, SLOT(xyzg_2_valueChanged(int)));
connect( newpanl->xg_2, SIGNAL( valueChanged(int) ), this, SLOT(xg_2_valueChanged(int)));
connect( newpanl->yg_2, SIGNAL( valueChanged(int) ), this, SLOT(yg_2_valueChanged(int)));
connect( newpanl->zg_2, SIGNAL( valueChanged(int) ), this, SLOT(zg_2_valueChanged(int)));
/*
connect( newpanl->anim_2_2, SIGNAL( clicked() ), this, SLOT(AnimIso()));
connect( newpanl->anim_2_2, SIGNAL( clicked() ), this, SLOT(anim_2_toggle()));
connect( newpanl->morph_2_2, SIGNAL( clicked() ), this, SLOT(IsoMorph()));
connect( newpanl->morph_2_2, SIGNAL( clicked() ), this, SLOT(morph_2_toggle()));
connect( newpanl->Isomesh, SIGNAL( clicked() ), this, SLOT(iso_mesh()));
connect( newpanl->Isomesh, SIGNAL( clicked() ), this, SLOT(Isomesh_toggle()));
connect( newpanl->IsoLine, SIGNAL( clicked() ), this, SLOT(IsoLine_clicked()));
connect( newpanl->IsoLine, SIGNAL( clicked() ), this, SLOT(IsoLine_toggle()));
connect( newpanl->isoinfos, SIGNAL( clicked() ), this, SLOT(iso_infos()));
connect( newpanl->isoinfos, SIGNAL( clicked() ), this, SLOT(isoinfos_toggle()));
connect( newpanl->isoaxe, SIGNAL( clicked() ), this, SLOT(isoaxe_clicked()));
connect( newpanl->isoaxe, SIGNAL( clicked() ), this, SLOT(isoaxe_toggle()));
*/
connect( newpanl->comboBox18_3, SIGNAL(activated(int) ), this, SLOT(comboBox18_3_activated(int)));

/// Parametric Page :

connect( newpanl->cutline, SIGNAL( valueChanged(int) ), this, SLOT(cutline_valueChanged(int)));
connect( newpanl->cutcolumn, SIGNAL( valueChanged(int) ), this, SLOT(cutcolumn_valueChanged(int)));
connect( newpanl->linecolumn, SIGNAL( valueChanged(int) ), this, SLOT(linecolumn_valueChanged(int)));
/*
connect( newpanl->mesh, SIGNAL( clicked() ), this, SLOT(mesh_clicked()));
connect( newpanl->mesh, SIGNAL( clicked() ), this, SLOT(mesh_toggle()));
connect( newpanl->Axes_ok, SIGNAL( clicked() ), this, SLOT(Axes_ok_clicked()));
connect( newpanl->Axes_ok, SIGNAL( clicked() ), this, SLOT(Axes_ok_toggle()));
connect( newpanl->box, SIGNAL( clicked() ), this, SLOT(box_clicked()));
connect( newpanl->box, SIGNAL( clicked() ), this, SLOT(box_toggle()));
connect( newpanl->infos, SIGNAL( clicked() ), this, SLOT(infos_clicked()));
connect( newpanl->infos, SIGNAL( clicked() ), this, SLOT(infos_toggle()));
connect( newpanl->draw_norm, SIGNAL( clicked() ), this, SLOT(draw_norm_clicked()));
connect( newpanl->draw_norm, SIGNAL( clicked() ), this, SLOT(draw_norm_toggle()));
connect( newpanl->exter, SIGNAL( clicked() ), this, SLOT(exter_clicked()));
connect( newpanl->exter, SIGNAL( clicked() ), this, SLOT(exter_toggle()));
connect( newpanl->anim,  SIGNAL( clicked() ), this, SLOT(anim_verify_rot4d()));
connect( newpanl->anim,  SIGNAL( clicked() ), this, SLOT(anim_toggle()));
connect( newpanl->morph, SIGNAL( clicked() ), this, SLOT(morph_verify_rot4d()));
connect( newpanl->morph, SIGNAL( clicked() ), this, SLOT(morph_toggle()));
*/
connect( newpanl->comboBox18_2, SIGNAL(activated(int) ), this, SLOT(comboBox18_2_activated(int)));

/// Color/OpenGL :

connect( newpanl->color, SIGNAL( activated(int) ), this, SLOT(typecolor(int)));
connect( newpanl->red, SIGNAL( valueChanged(int) ), this, SLOT(redcl(int)));
connect( newpanl->green, SIGNAL( valueChanged(int) ), this, SLOT(greencl(int)));
connect( newpanl->blue, SIGNAL( valueChanged(int) ), this, SLOT(bluecl(int)));
connect( newpanl->transparence, SIGNAL( clicked() ), this, SLOT(transparencecl()));
connect( newpanl->transparence, SIGNAL( clicked() ), this, SLOT(transparence->toggle()));
connect( newpanl->comboBox18, SIGNAL( activated(int) ), this, SLOT(comboBox18_activated(int)));

/// Lunch the Panel :
newpanl->show();
}

//==================================================/
void k3dsurface::comboBox18_2_activated( int ch )
{
         if (ch == 0)  {mesh_clicked(); mesh->toggle();}
    else if (ch == 1) {Axes_ok_clicked(); Axes_ok->toggle();}
    else if (ch == 2) {box_clicked(); box->toggle();}
    else if (ch == 3) {infos_clicked(); infos->toggle();}
    else if (ch == 4) {draw_norm_clicked(); draw_norm->toggle();}
    else if (ch == 5) {exter_clicked(); exter->toggle();}
    else if (ch == 6) {anim_verify_rot4d(); anim->toggle();}
    else if (ch == 7) {morph_verify_rot4d(); morph->toggle();}
}

//==================================================/
void k3dsurface::comboBox18_3_activated( int ch )
{
         if (ch == 0) {iso_mesh(); Isomesh->toggle();}
    else if (ch == 1) {IsoLine_clicked(); IsoLine->toggle();}
    else if (ch == 2) {iso_infos(); isoinfos->toggle();}
    else if (ch == 3) {isoaxe_clicked(); isoaxe->toggle();}
    else if (ch == 4) {AnimIso(); anim_2->toggle();}
    else if (ch == 5) {IsoMorph(); morph_2->toggle();}
}
