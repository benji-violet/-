#include "gameoverscene.h"

GameOverScene::GameOverScene(QObject *parent)
    : BaseScene{parent}
{
    this->setSceneRect(0, 0, 950, 750);
    setBackgroundBrush(QBrush(Qt::black));
    // 新建按钮
    back_to_menu_btn = new SceneButton("返回主菜单");
    restart_btn = new SceneButton("重新开始");
    // 按钮设置
    buttonSetting(back_to_menu_btn, 0);
    buttonSetting(restart_btn, 1);
    // 添加按钮
    this->addItem(back_to_menu_btn);
    this->addItem(restart_btn);
    // 按钮信号
    totalConnect(back_to_menu_btn, Start);
    totalConnect(restart_btn, Game);
}

void GameOverScene::enter() {
    setFocus();
}

void GameOverScene::totalConnect(SceneButton* button, int type) {
    connect(button, &SceneButton::clicked, this, [=](){
        emit switchToScene(type);
    });
}

void GameOverScene::buttonSetting(SceneButton* button, int index) {
    button->setPosition(this->width()/2-50, this->height()/2-20 + 60*index);
    button->setSize(100, 40);
}
