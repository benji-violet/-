#ifndef ENEMY_H
#define ENEMY_H

#include "tank.h"

class Enemy : public Tank
{
    Q_OBJECT
public:
    enum EnemyType {
        Normal,
        Fast,
        Heavy,
        Boss
    };

    explicit Enemy(int x, int y, EnemyType enemy_type = Normal, QObject *parent = nullptr);
    ~Enemy();

    int getHealth() const { return health_; }
    EnemyType getEnemyType() const { return enemy_type_; }
    bool isAlive() const { return health_ > 0; }

    void update() override;
    void moveAI();
    void shoot() override;
    void takeDamage(int damage = 1);

signals:
    void destroyed(Enemy* enemy);

private:
    EnemyType enemy_type_;
    int health_;
    int fire_rate_;
    int fire_counter_;

    void updateImage();
};

#endif // ENEMY_H
