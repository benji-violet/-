#include "gamemap.h"

GameMap::GameMap()
{
    map MAP(QWidget * parent);
    QVector<QVector<int>> MAP1 = MAP.generateRandomMap();
for(int i=0;i<19;i++)
    for(int j=0;j<15;j++)
        cells[i][j]=new Mapcell(i,j,MAP1[i][j]);
//for(int i=0;i<INUM;i++)
   // for(int j=0;j<JNUM;j++)
       //cells[i][j]=new Mapcell(i,j,0);
}
GameMap::~GameMap(){
    for (int i = 0;i < 19;i++) {
        for (int j = 0;j < 15;j++)
        {
            delete cells[i][j];cells[i][j] = NULL;
        }
    }
}

void GameMap::Display(QPainter &paint){

for(int i=0;i<19;i++)
    for(int j=0;j<15;j++)
    {
        if(cells[i][j]!=NULL)
            cells[i][j]->Display(paint);

    }

}


//void GameMap::setstyle(int i, int j, int style){
   // if(i>=INUM||j>=JNUM)
   // {qDebug("数组越界");return ;}
    // if(cells[i][j])
   //      cells[i][j]->setstyle(style);
   //  else{
   //      cells[i][j]=new Mapcell(i,j,style);

   //  }
//}


//void GameMap::deletecell(int i, int j){
  //  if(i>=INUM||j>=JNUM)
 //   {qDebug("数组越界");return;}
  //  delete cells[i][j];
 //  cells[i][j]=NULL;

//}


//void GameMap::savemap(const char *str){
//erjinzhi
  //  std::ofstream ou(str);
  //  for(int i=0;i<INUM;i++)
   //     for(int j=0;j<JNUM;j++)
    //         if(cells[i][j]&&!cells[i][j]->IsDisappear())
    //         ou.write((char*)cells[i][j],sizeof(Mapcell));
//ou.close();
//}

//void GameMap::loadmap(const char *str){
   // for(int i=0;i<INUM;i++)
    //   for(int j=0;j<JNUM;j++)
       //     if(cells[i][j])
      //   {delete cells[i][j] ;cells[i][j]=NULL;}
/// <summary>/
/// </summary>
//Mapcell cellst;
//std::ifstream in(str);
//int i=0,j=0;
 //  while(in.read((char*)&cellst,sizeof(Mapcell)))
  //    { j=cellst.getpos().x()/CELLWIDTH;
   //     i=cellst.getpos().y()/CELLHEIGHT;
   //     if(cells[i][j])
   //     *cells[i][j]=cellst;
    //        else
    //         {
   //          cells[i][j]=new Mapcell(i,j);
    //         *cells[i][j]=cellst;//moren de 赋值 gou zao hanshu
   //          }
//
   //    }
//in.close();
//}
