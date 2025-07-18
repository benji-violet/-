#include "mapcell.h"
//QImage Mapcell::blockimage=QImage(":/images/map_block.png"); linux
float Mapcell::lifes[BLOCKSNUM]={300,3,2000,1000,800,200};
float Mapcell::hujias[BLOCKSNUM]={1000,0,400,300,200,50};
float Mapcell::mokangs[BLOCKSNUM]={1000,0,400,300,200,0};
bool Mapcell::chuantous[BLOCKSNUM]={true,false,false,false,true,true};
bool Mapcell::chuantous1[BLOCKSNUM]={true,false,false,true,true,true};
Mapcell::Mapcell()
{
    this->m_pos.setX(8*50+50/2);
    this->m_pos.setY(8*50+50/2);
    this->CalculateSphere();
    this->m_bDisappear=false;
    this->style=0;
    this->life=lifes[style];
    this->hujia=hujias[style];
    this->mokang=mokangs[style];
    this->chuantou=chuantous[style];
    this->chuantou1=chuantous1[style];

}

Mapcell::Mapcell(int iIndex,int jIndex,int style1){
    this->m_pos.setX(jIndex*50+50/2);
    this->m_pos.setY(iIndex*50+50/2);
    this->CalculateSphere();
    this->m_bDisappear=false;
    this->style = style1;
    this->life=lifes[style];
    this->hujia=hujias[style];
    this->mokang=mokangs[style];
    this->chuantou=chuantous[style];
    this->chuantou1=chuantous1[style];
}


void Mapcell::Display(QPainter &paint){
    QRect xm_rectSphere = m_rectSphere;
    QImage img0("images/walls/0.png");
    QImage img1("images/walls/1.png");
    QImage img2("images/walls/2.png");
    QImage img3("images/walls/3.png");
    QImage img4("images/walls/4.png");
    QImage img5("images/walls/5.png");
    if (!this->IsDisappear())
    {
        switch (style) {
        case 0:
            paint.drawImage(xm_rectSphere, img0);
            break;
        case 1:

            paint.drawImage(xm_rectSphere, img1);
            break;
        case 2:

            paint.drawImage(xm_rectSphere, img2);
            break;
        case 3:

            paint.drawImage(xm_rectSphere, img3);
            break;
        case 4:

            paint.drawImage(xm_rectSphere, img4);
            break;
        case 5:

            paint.drawImage(xm_rectSphere, img5);
            break;

        }
    }
}
void Mapcell::Move(){

}
