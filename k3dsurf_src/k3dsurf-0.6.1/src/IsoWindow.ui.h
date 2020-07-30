/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you want to add, delete, or rename functions or slots, use
** Qt Designer to update this file, preserving your code.
**
** You should not define a constructor or destructor in this file.
** Instead, write your code in functions called init() and destroy().
** These will automatically be called by the form's constructor and
** destructor.
*****************************************************************************/
#include <qevent.h>

///++++++++++++++++++++++++++++++++++++++
void IsoWindow::keyPressEvent ( QKeyEvent * e ) {

int key = e->key();



switch(key) {
case Qt::Key_A : isoWidget->IsoAnim();break;
case Qt::Key_P : isoWidget->IsoMorph();break;
}

isoWidget->update();
};


void IsoWindow::resizeEvent( QResizeEvent  *e )
{

QSize qs = e->size();
QSize qsold = e->oldSize();

  double ancien_hauteur = (double)isoWidget->IsoObjet->demi_hauteur;
  double ancien_largeur = (double)isoWidget->IsoObjet->demi_largeur;

   isoWidget->width  = qs.width();
   isoWidget->height = qs.height();
   isoWidget->setFixedSize (qs.width() , qs.height());
   //isoWidget->taillechanged = 1;
   delete isoWidget->pixmap;
   isoWidget->pixmap = new QPixmap(qs.width(), qs.height());

   isoWidget->IsoObjet->demi_hauteur = (qs.width())/2;
   isoWidget->IsoObjet->demi_largeur = (qs.height())/2;

   if(isoWidget->IsoObjet->demi_hauteur < isoWidget->IsoObjet->demi_largeur)
     isoWidget->IsoObjet->ScalCoeff = isoWidget->IsoObjet->demi_hauteur/(double)ancien_hauteur;
   else isoWidget->IsoObjet->ScalCoeff = isoWidget->IsoObjet->demi_largeur/(double)ancien_largeur;
   isoWidget->IsoObjet->ScaleIsoMap();

   isoWidget->update();
   //update();

};
