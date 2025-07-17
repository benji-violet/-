#include "map.h"

Map::Map(QObject* parent) : QObject(parent) {
    generateRandomMap();
}

Map::~Map() {}

void Map::generateRandomMap() {
    map = QVector<QVector<int>>(ROWS, QVector<int>(COLS, 0));
    QRandomGenerator* rand = QRandomGenerator::global();

    // 1. 边界全部为地面（0）
    for (int i = 0; i < ROWS; ++i) {
        map[i][0] = 0;
        map[i][COLS-1] = 0;
    }
    for (int j = 0; j < COLS; ++j) {
        map[0][j] = 0;
        map[ROWS-1][j] = 0;
    }

    // 2. 司令部位置
    QPoint base(ROWS-2, COLS/2);
    map[base.x()][base.y()] = 5;
    // 司令部周围空地
    for(int dx=-1;dx<=1;++dx) for(int dy=-1;dy<=1;++dy) {
        int nx=base.x()+dx, ny=base.y()+dy;
        if(nx>0&&nx<ROWS-1&&ny>0&&ny<COLS-1) map[nx][ny]=0;
    }

    // 3. 敌人出生点
    int mid = COLS / 2;
    QVector<QPoint> enemySpawns = {
        QPoint(1, mid - 5),        // 中上偏左
        QPoint(1, mid + 5),        // 中上偏右
        QPoint(5, 2),              // 左边缘下移3格
        QPoint(5, COLS - 3)        // 右边缘下移3格
    };
    for(const auto& p:enemySpawns) map[p.x()][p.y()]=0;

    // 4. 主干道生成（BFS保证连通）
    auto carvePath = [&](QPoint from, QPoint to) {
        QVector<QVector<bool>> vis(ROWS, QVector<bool>(COLS,false));
        QVector<QVector<QPoint>> prev(ROWS, QVector<QPoint>(COLS,QPoint(-1,-1)));
        QVector<QPoint> q; q.push_back(from); vis[from.x()][from.y()]=true;
        int dx[4]={1,-1,0,0}, dy[4]={0,0,1,-1};
        while(!q.isEmpty()) {
            QPoint cur=q.front(); q.pop_front();
            if(cur==to) break;
            for(int d=0;d<4;++d) {
                int nx=cur.x()+dx[d], ny=cur.y()+dy[d];
                if(nx>0&&nx<ROWS-1&&ny>0&&ny<COLS-1&&!vis[nx][ny]) {
                    vis[nx][ny]=true; prev[nx][ny]=cur; q.push_back(QPoint(nx,ny));
                }
            }
        }
        // 回溯路径
        QPoint cur=to;
        while(cur!=from&&prev[cur.x()][cur.y()]!=QPoint(-1,-1)) {
            map[cur.x()][cur.y()]=0;
            cur=prev[cur.x()][cur.y()];
        }
        map[from.x()][from.y()]=0;
    };
    for(const auto& spawn:enemySpawns) carvePath(spawn, base);

    // 5. 分支生成（主干道上随机分叉，分支末端放道具）
    int branchCount = 4;
    for(int b=0;b<branchCount;++b) {
        // 随机选主干道上的点
        int ex = rand->bounded(2, ROWS-3);
        int ey = rand->bounded(2, COLS-3);
        if(map[ex][ey]==0 && !(QPoint(ex,ey)==base)) {
            int len = rand->bounded(3,6);
            int dir = rand->bounded(4); // 0上1下2左3右
            int bx=ex, by=ey;
            for(int l=0;l<len;++l) {
                int nx=bx, ny=by;
                if(dir==0) nx--;
                else if(dir==1) nx++;
                else if(dir==2) ny--;
                else ny++;
                if(nx<=1||nx>=ROWS-2||ny<=1||ny>=COLS-2) break;
                if(map[nx][ny]!=0) break;
                bx=nx; by=ny;
                map[bx][by]=0;
            }
            // 分支末端放道具
            map[bx][by]=3;
        }
    }

    // 6. 其余空地随机填充障碍、丛林、河流
    for(int i=1;i<ROWS-1;++i) for(int j=1;j<COLS-1;++j) {
        if(map[i][j]!=0) continue;
        int r = rand->bounded(100);
        if(r<15) map[i][j]=1; // 砖墙
        else if(r<25) map[i][j]=2; // 铁墙
        else if(r<31.67) map[i][j]=4; // 河流，概率减少1/3
        else if(r<45) map[i][j]=3; // 丛林
        // 其余为地面
    }

    // 7. 敌人出生点再清空
    for(const auto& p:enemySpawns) map[p.x()][p.y()]=0;
    // 司令部周围再清空
    for(int dx=-1;dx<=1;++dx) for(int dy=-1;dy<=1;++dy) {
        int nx=base.x()+dx, ny=base.y()+dy;
        if(nx>0&&nx<ROWS-1&&ny>0&&ny<COLS-1) map[nx][ny]=0;
    }
    map[base.x()][base.y()]=5;

    // nothing to return
}

void Map::debug() const {
    for (const auto& row : map) {
        for (auto ele : row) {
            std::cout << ele;
        }
        std::cout << std::endl;
    }
}

void Map::update() {}
























