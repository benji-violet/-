#ifndef GAMEOVERSCENE_H
#define GAMEOVERSCENE_H

#include "basescene.h"

class GameOverScene : public BaseScene
{
    Q_OBJECT
public:
    explicit GameOverScene(QObject *parent = nullptr);
    ~GameOverScene() = default;
    void enter() override;
    void totalConnect();

private:
    SceneButton* back_to_menu_btn;
    SceneButton* restart_btn;
    void buttonSetting(SceneButton* button, int index);
    void totalConnect(SceneButton* button, int type);
};

#endif // GAMEOVERSCENE_H
