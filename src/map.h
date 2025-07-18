#ifndef MAP_H
#define MAP_H

#include <QObject>
#include <QVector>
#include <QRandomGenerator>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <iostream>
#include "mapcell.h"

class Map : public QObject
{
    Q_OBJECT
public:
    explicit Map(QObject* parent = nullptr);
    ~Map();
    CellType getCell(int x, int y) const { return map[x][y]->getType(); }
    int getRows() const { return ROWS; }
    int getCols() const { return COLS; }
    MapCell* getMapCell(int x, int y) const { return map[x][y]; }
    void generateRandomMap();
    void debug() const;

private:
    void update();

    // 地图参数
    const int ROWS = 30;    // 行数
    const int COLS = 40;    // 列数
    const int OBSTACLE_DENSITY = 30;  // 障碍物总占比（%）
    const int BREAKABLE_RATIO = 60;   // 可破坏墙体占障碍物的比例（%）
    //地图
    QVector<QVector<MapCell*>> map;  //地图存储
};

#endif // MAP_H
