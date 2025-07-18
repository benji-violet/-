#ifndef ENEMYSPAWNER_H
#define ENEMYSPAWNER_H

#include <QObject>
#include <QTimer>
#include <QVector>
#include <QPoint>
#include "enemy.h"
#include "map.h"

class EnemySpawner : public QObject
{
    Q_OBJECT
public:
    EnemySpawner(Map* map, QGraphicsScene* scene, QObject* parent = nullptr);
    void setSpawnPoints(const QVector<QPoint>& points); //设置生成位置
    void setMaxEnemyCount(int count);   //敌人的最大数量
    void setSpawnInterval(int ms);  //敌人生成间隔
    void start();   //开始生成敌人
    void stop();    //终止生成敌人
    QVector<Enemy*> getEnemies() const; //获取敌人数组

signals:
    void enemySpawned(Enemy* enemy);    //生成敌人的信号

private slots:
    void trySpawnEnemy();   //生成敌人

private:
    Map* map_;  //目标地图
    QGraphicsScene* scene_; //目标界面
    QTimer* timer_; //计时器
    QVector<QPoint> spawn_points_;  //生成点
    QVector<Enemy*> enemies_;   //敌人数组
    int max_enemy_count_ = 10;   //最大敌人数量
    int spawn_interval_ = 1000; //生成间隔
};

#endif // ENEMYSPAWNER_H
