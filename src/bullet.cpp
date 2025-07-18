#include "bullet.h"
/*
源代码分析戳这里：http://blog.csdn.net/qq_26046771/article/details/72636320

  */
Bullet::Bullet(const Tank &tank)
{
    m_dir=tank.m_dir;
    m_pos=tank.m_pos;
    style=tank.style/2;
    m_step=tank.m_step+10;
    wuli=tank.wuli;
    fashu=tank.fashu;
    group=tank.group;
    m_bDisappear=false;
    CalculateSphere();
}

void Bullet::Display(QPainter &paint){
   if(m_bDisappear==true)return;
QImage img(":/images/bullet/bullet.png");
   if (!img.isNull()) {
       paint.drawImage(m_rectSphere, img);
   } else {
       // 图片加载失败时用红色矩形代替
       paint.setBrush(Qt::red);
       paint.drawRect(m_rectSphere);
   }
      }






void Bullet::Move(){


     switch(m_dir){
         case UP:
             m_pos.setY(m_pos.y()-m_step);
             break;
         case DOWN:
             m_pos.setY(m_pos.y()+m_step);
             break;
         case LEFT:
             m_pos.setX(m_pos.x()-m_step);
             break;
         case RIGHT:
             m_pos.setX(m_pos.x()+m_step);
             break;
       }
     CalculateSphere();

//子弹是否与地图块碰撞
     for(int i=0;i<19;i++)
         for(int j=0;j<15;j++)
          if(glo.gamemap->getcell(i,j))
          if(!glo.gamemap->getcell(i,j)->ischuantou1())
          if(IsBoom(*glo.gamemap->getcell(i,j)))
          {glo.gamemap->getcell(i,j)->downlife(wuli,0);m_bDisappear=true;
         }


     for(int i=0;i<glo.badtanks.count();i++)
         if(glo.badtanks[i] && glo.badtanks[i]->group != this->group && IsBoom(*(glo.badtanks[i])))
    {
       m_bDisappear=true;//子弹消失
       glo.badtanks[i]->downlife(wuli);
     }

     if(glo.player->group!=this->group&&IsBoom(*glo.player))
     {

         m_bDisappear=true;
         glo.player->downlife(wuli);
     }


//子弹出界
     if(m_pos.x()<0||m_pos.x()>950||m_pos.y()>750||m_pos.y()<0)
         m_bDisappear=true;//子弹消失


}




void Bullet::CalculateSphere(){


this->m_rectSphere.setRect(m_pos.x()-4/2,m_pos.y()-2/2,4,2);

}
