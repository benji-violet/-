#include "enemyspawner.h"
#include <QRandomGenerator>

EnemySpawner::EnemySpawner(Map* map, QGraphicsScene* scene, QObject* parent)
    : QObject(parent), map_(map), scene_(scene)
{
    timer_ = new QTimer(this);
    connect(timer_, &QTimer::timeout, this, &EnemySpawner::trySpawnEnemy);
}

//设置生成点
void EnemySpawner::setSpawnPoints(const QVector<QPoint>& points)
{
    spawn_points_ = points;
}

//敌人最大数量
void EnemySpawner::setMaxEnemyCount(int count)
{
    max_enemy_count_ = count;
}

//生成间隔
void EnemySpawner::setSpawnInterval(int ms)
{
    spawn_interval_ = ms;
    if (timer_->isActive()) {
        timer_->start(spawn_interval_);
    }
}

//开始生成
void EnemySpawner::start()
{
    timer_->start(spawn_interval_);
}

//停止生成
void EnemySpawner::stop()
{
    timer_->stop();
}

//获取敌人数组
QVector<Enemy*> EnemySpawner::getEnemies() const
{
    return enemies_;
}

//生成敌人
void EnemySpawner::trySpawnEnemy()
{
    if (enemies_.size() >= max_enemy_count_ || spawn_points_.isEmpty()) return;
    int idx = QRandomGenerator::global()->bounded(spawn_points_.size());
    QPoint pt = spawn_points_[idx];
    // 检查该点是否为空地
    if (map_ && map_->getCell(pt.x(), pt.y()) != Ground
        && map_->getCell(pt.x(), pt.y()) != Forest)
        return;
    // 检查是否已有敌人在该点
    for (Enemy* e : enemies_) {
        if (e && e->getGraphicsItem()->scenePos() == QPointF(pt.x() * 60 + 10, pt.y() * 60 + 10))
            return;
    }
    // 生成敌人
    Enemy* enemy = new Enemy(pt.x() * 60 + 10, pt.y() * 60 + 10, Enemy::Normal, nullptr);
    scene_->addItem(enemy->getGraphicsItem());
    enemies_.append(enemy);
    emit enemySpawned(enemy);
    connect(enemy, &Enemy::destroyed, this, [=](Enemy* e){
        enemies_.removeOne(e);
        scene_->removeItem(e->getGraphicsItem());
        e->deleteLater();
    });
}
