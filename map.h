#ifndef MAP_H
#define MAP_H

#include <QObject>
#include <QPainter>
#include <QPixmap>
#include <QPaintEvent>
#include <QWidget>
#include <QKeyEvent>
#include <QTimer>
#include <QPushButton>
#include <QFile>
#include <QVector>
#include <QRandomGenerator>
#include <QDebug>

class Map : public QWidget
{
    Q_OBJECT
public:
    explicit Map(QWidget *parent = nullptr);
    ~Map();
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent * event);
    void keyRealeaseEent(QKeyEvent * event);
    void renderMap();
    QVector<QVector<int>> generateRandomMap();

private slots:
    void checkKeyCombinations();

signals:
    void switchToMainwindow();

private:
    //检测组合按键部分
    QSet<int> pressed_keys;
    QTimer *timer;
    // 地图参数
    const int ROWS = 15;    // 行数
    const int COLS = 19;    // 列数
    const int OBSTACLE_DENSITY = 30;  // 障碍物总占比（%）
    const int BREAKABLE_RATIO = 60;   // 可破坏墙体占障碍物的比例（%）
};

#endif // MAP_H
