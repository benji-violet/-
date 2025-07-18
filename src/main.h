/*
源代码分析戳这里：http://blog.csdn.net/qq_26046771/article/details/72636320

  */
#ifndef MAIN
#define MAIN
#define JNUM 19
#define INUM 15
#define PICWIDTH 50//地图块图片宽度
#define PICHEIGHT 50
#define CELLWIDTH 50//地图块宽度
#define CELLHEIGHT 50
#define WIDTH 50*17//地图宽度
#define HEIGHT 50*11
#define PICTANKWIDTH 50//坦克图片宽度
#define PICTANKHEIGHT 50//坦克图片高度
#define TANKWIDTH 50//坦克宽度
#define TANKHEIGHT 50//坦克高度
#include <QVector>
class EnemyTank;
class Tank;
class GameMap;
class Bullet;
    struct Glo{
    Tank *player;
    GameMap *gamemap;
   QVector<EnemyTank*> badtanks;
    QVector<Bullet*> playerbullets;

};//实列化Glo类型变量，能实列化出来,所有的指针变量所占空间daxiao一样。
extern Glo glo;//声明变量
#endif // MAIN

