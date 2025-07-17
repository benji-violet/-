#include "startscene.h"

StartScene::StartScene(QObject* parent)
    : BaseScene{parent}
{
    this->setSceneRect(0, 0, 950, 750);
    setBackgroundBrush(QBrush(Qt::black));
    //新建
    start_btn = new SceneButton("START");
    exit_btn = new SceneButton("EXIT");
    help_btn = new SceneButton("HELP");
    //按钮设置
    buttonSetting(start_btn, 0);
    buttonSetting(exit_btn, 1);
    buttonSetting(help_btn, 2);


    //添加按钮
    this->addItem(start_btn);
    this->addItem(exit_btn);
    this->addItem(help_btn);

    //按钮信号
    totalConnect(start_btn, Game);
    totalConnect(exit_btn, Close);
    totalConnect(help_btn, Help);
}

void StartScene::enter() {
    setFocus();
}

// 按钮点击后的处理逻辑
void StartScene::totalConnect(SceneButton* button, int type) {
    connect(button, &SceneButton::clicked, this, [=](){
        qDebug() << "点击按钮";
        if(type == Help) {
            QMessageBox::information(nullptr, "帮助", "欢迎来到游戏！\n操作说明：\n- WASD移动\n- J键攻击\n- CapsLock+Esc退出\n祝你游戏愉快！");
            return;
        }
        emit switchToScene(type);   //跳转到game界面
    });
}

//按钮设置
void StartScene::buttonSetting(SceneButton* button, int index) {
    button->setPosition(this->width()/2-75, this->height()/2 - 70 + 70*index);
    button->setSize(150, 60);
}


