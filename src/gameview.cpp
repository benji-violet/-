#include "gameview.h"

GameView::GameView(QWidget *parent)
: QGraphicsView(parent)
{
    // 3. 游戏定时器（控制更新频率）
    game_timer = new QTimer(this);
    connect(game_timer, &QTimer::timeout, this, &GameView::run);
    game_timer->start(16); // 60FPS

    // 初始化定时器，每50ms检查一次按键组合
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GameView::checkKeyCombinations);
    timer->start(50);

    // 创建各个场景
    start_scene = new StartScene();
    game_scene = new GameScene();
    game_over_scene = new GameOverScene();

    // 设置视图属性
    setFixedSize(1600, 900);
    setAlignment(Qt::AlignLeft | Qt::AlignTop);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setRenderHint(QPainter::Antialiasing);

    // 连接场景切换信号
    connect(start_scene, &StartScene::switchToScene, this, &GameView::switchScene);
    connect(game_scene, &GameScene::switchToScene, this, &GameView::switchScene);
    connect(game_over_scene, &GameOverScene::switchToScene, this, &GameView::switchScene);

    // 初始显示菜单场景
    switchScene(Start);
}

GameView::~GameView() {}

// 切换场景
void GameView::switchScene(int sceneType)
{
    switch(sceneType)
    {
    case Start: // 菜单场景
        setScene(start_scene);
        start_scene->enter();
        game_scene->gameCease();
        break;
    case Game: // 游戏场景
        game_scene->gameStart();
        game_scene->debug();
        setScene(game_scene);
        game_scene->enter();
        break;
    case GameOver: // 结束场景
        setScene(game_over_scene);
        game_over_scene->enter();
        game_scene->gameCease();
        break;
    case Close: //退出场景（关闭窗口）
        if (QMessageBox::question(this, "退出", "确定退出游戏吗？", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
            close(); // 关闭主窗口
        }
        break;
    }
}

//处理按键输入
void GameView::checkKeyCombinations() {
    //按下CapsLock和escape退出
    if (pressed_keys.contains(Qt::Key_CapsLock) &&
        pressed_keys.contains(Qt::Key_Escape)) {
        window()->close();
    }
}

//按下按键
void GameView::keyPressEvent(QKeyEvent *event)
{
    // 添加按键到集合，但忽略自动重复的按键事件
    if (!event->isAutoRepeat()) {
        pressed_keys.insert(event->key());
        // 转发给GameScene的玩家
        if (game_scene) game_scene->handlePlayerKeyPress(event->key());
    }
    QGraphicsView::keyPressEvent(event);
}

//释放按键
void GameView::keyReleaseEvent(QKeyEvent *event)
{
    // 从集合中移除按键，忽略自动重复的按键事件
    if (!event->isAutoRepeat()) {
        pressed_keys.remove(event->key());
        // 转发给GameScene的玩家
        if (game_scene) game_scene->handlePlayerKeyRelease(event->key());
    }
    QGraphicsView::keyReleaseEvent(event);
}

//运行游戏
void GameView::run() {
    qDebug() << "gameview";
    this->setFixedSize(1400, 800);
    // 卷轴滚动：以玩家为中心
    if (game_scene && game_scene->player_) {
        QPointF player_center = game_scene->player_->getGraphicsItem()->sceneBoundingRect().center();
        centerOn(player_center);
    }
    game_scene->run();
}
