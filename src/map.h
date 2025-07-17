#ifndef MAP_H
#define MAP_H

#include <QObject>
#include <QVector>
#include <QRandomGenerator>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <iostream>
#include "gameobject.h"

class Map : public QObject
{
    Q_OBJECT
public:
    explicit Map(QObject* parent = nullptr);
    ~Map();
    int getCell(int x, int y) const { return map[x][y]; }
    int getRows() const { return ROWS; }
    int getCols() const { return COLS; }
    void generateRandomMap();
    void debug() const;

private:
    void update();

    // 地图参数
    const int ROWS = 18;    // 行数（1080/60）
    const int COLS = 32;    // 列数（1920/60）
    const int OBSTACLE_DENSITY = 30;  // 障碍物总占比（%）
    const int BREAKABLE_RATIO = 60;   // 可破坏墙体占障碍物的比例（%）
    //地图
    QVector<QVector<int>> map;  //地图存储
};

#endif // MAP_H
