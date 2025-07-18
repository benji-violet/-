#ifndef BULLET_H
#define BULLET_H
/*
源代码分析戳这里：http://blog.csdn.net/qq_26046771/article/details/72636320

  */
#include"wanwu.h"
#include "tank.h"
#include "enemytank.h"
class Bullet : public Wanwu
{
    friend Tank;
public:
    Bullet(const Tank &tank);
    // 绘图
    void Display(QPainter &paint) ;

    // 移动
    void Move() ;
    //
protected:
    void CalculateSphere();
private:
    int style;
    int group;//子弹所在组

};

#endif // BULLET_H
