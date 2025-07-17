#ifndef STARTSCENE_H
#define STARTSCENE_H

#include <QTimer>
#include <QPushButton>
#include <QDebug>
#include <QMessageBox>

#include "basescene.h"
#include "scenebutton.h"

class StartScene : public BaseScene
{
    Q_OBJECT

public:
    explicit StartScene(QObject* parent = nullptr);
    ~StartScene() = default;
    void enter() override;

protected:
    void totalConnect(SceneButton* button, int type);
    void buttonSetting(SceneButton* button, int index);

private:
    SceneButton* start_btn;
    SceneButton* exit_btn;
    SceneButton* help_btn;
};

#endif // STARTSCENE_H
