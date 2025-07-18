#include "map.h"

Map::Map(QObject* parent) : QObject(parent) {
    generateRandomMap();
}

Map::~Map() {}

// 随机地图生成
void Map::generateRandomMap() {
    map = QVector<QVector<MapCell*>>(ROWS, QVector<MapCell*>(COLS, nullptr));
    QRandomGenerator* rand = QRandomGenerator::global();

    // 初始化所有MapCell
    for(int i=0;i<ROWS;++i) {
        for(int j=0;j<COLS;++j) {
            map[i][j] = new MapCell(j, i, Ground, nullptr);
        }
    }

    // 1. 边界全部为地面（0）
    for (int i = 0; i < ROWS; ++i) {
        map[i][0]->setType(Ground);
        map[i][COLS-1]->setType(Ground);
    }
    for (int j = 0; j < COLS; ++j) {
        map[0][j]->setType(Ground);
        map[ROWS-1][j]->setType(Ground);
    }

    // 2. 司令部位置
    QPoint base(ROWS-2, COLS/2);
    map[base.x()][base.y()]->setType(HQ);
    // 司令部周围空地
    for(int dx=-1;dx<=1;++dx) for(int dy=-1;dy<=1;++dy) {
        int nx=base.x()+dx, ny=base.y()+dy;
        if(nx>0&&nx<ROWS-1&&ny>0&&ny<COLS-1) map[nx][ny]->setType(Ground);
    }

    // 3. 敌人出生点
    int mid = COLS / 2;
    QVector<QPoint> enemySpawns = {
        QPoint(1, mid - 5),        // 中上偏左
        QPoint(1, mid + 5),        // 中上偏右
        QPoint(8, 2),              // 左边缘下移3格
        QPoint(8, COLS - 3)        // 右边缘下移3格
    };
    for(const auto& p:enemySpawns) map[p.x()][p.y()]->setType(Ground);

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
            map[cur.x()][cur.y()]->setType(Ground);
            cur=prev[cur.x()][cur.y()];
        }
        map[from.x()][from.y()]->setType(Ground);
    };
    for(const auto& spawn:enemySpawns) carvePath(spawn, base);

    // 5. 分支生成（主干道上随机分叉，分支末端放道具）
    int branchCount = 4;
    for(int b=0;b<branchCount;++b) {
        // 随机选主干道上的点
        int ex = rand->bounded(2, ROWS-3);
        int ey = rand->bounded(2, COLS-3);
        if(map[ex][ey]->getType()==Ground && !(QPoint(ex,ey)==base)) {
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
                if(map[nx][ny]->getType()!=Ground) break;
                bx=nx; by=ny;
                map[bx][by]->setType(Ground);
            }
            // 分支末端放道具
            map[bx][by]->setType(Prop);
        }
    }
    
    // 随机生成3个额外的道具生成点
    int extraPropCount = 3;
    for(int p=0;p<extraPropCount;++p) {
        int attempts = 0;
        bool placed = false;
        while(attempts < 50 && !placed) { // 最多尝试50次
            int x = rand->bounded(2, ROWS-2);
            int y = rand->bounded(2, COLS-2);
            
            // 检查是否为空地且不是司令部
            if(map[x][y]->getType() == Ground && !(QPoint(x,y) == base)) {
                // 检查是否与分支末端重叠（分支末端已经是Prop类型）
                bool isBranchEnd = false;
                for(int b=0;b<branchCount;++b) {
                    // 这里需要记录分支末端位置，暂时用简单检查
                    // 由于分支末端已经设置为Prop，我们检查周围是否有其他Prop
                    int propCount = 0;
                    for(int dx=-1;dx<=1;++dx) {
                        for(int dy=-1;dy<=1;++dy) {
                            int nx = x + dx, ny = y + dy;
                            if(nx >= 0 && nx < ROWS && ny >= 0 && ny < COLS) {
                                if(map[nx][ny]->getType() == Prop) propCount++;
                            }
                        }
                    }
                    if(propCount > 0) {
                        isBranchEnd = true;
                        break;
                    }
                }
                
                if(!isBranchEnd) {
                    map[x][y]->setType(Prop);
                    placed = true;
                }
            }
            attempts++;
        }
    }
    
    // 6. 其余空地随机填充障碍、丛林、河流
    // 先生成河流块
    int riverBlockCount = 5; // 河流块数量
    for(int b=0;b<riverBlockCount;++b) {
        int blockSize = rand->bounded(2, 4); // 河流块大小
        int startX = rand->bounded(2, ROWS-blockSize-2);
        int startY = rand->bounded(2, COLS-blockSize-2);
        
        // 检查区域是否为空地
        bool canPlace = true;
        for(int dx=0;dx<blockSize;++dx) {
            for(int dy=0;dy<blockSize;++dy) {
                if(map[startX+dx][startY+dy]->getType() != Ground) {
                    canPlace = false;
                    break;
                }
            }
            if(!canPlace) break;
        }
        
        // 如果可以放置，生成河流块
        if(canPlace) {
            for(int dx=0;dx<blockSize;++dx) {
                for(int dy=0;dy<blockSize;++dy) {
                    if(rand->bounded(100) < 70) { // 70%概率生成河流
                        map[startX+dx][startY+dy]->setType(Water);
                    }
                }
            }
        }
    }
    
    // 再填充其他元素
    for(int i=1;i<ROWS-1;++i) for(int j=1;j<COLS-1;++j) {
        if(map[i][j]->getType()!=Ground) continue;
        int r = rand->bounded(100);
        if(r<15) map[i][j]->setType(Brick); // 砖墙
        else if(r<25) map[i][j]->setType(Steel); // 铁墙
        else if(r<45) map[i][j]->setType(Forest); // 丛林
        // 其余为地面
    }

    // 7. 敌人出生点再清空
    for(const auto& p:enemySpawns) map[p.x()][p.y()]->setType(Ground);
    // 司令部周围再清空
    for(int dx=-1;dx<=1;++dx) for(int dy=-1;dy<=1;++dy) {
        int nx=base.x()+dx, ny=base.y()+dy;
        if(nx>0&&nx<ROWS-1&&ny>0&&ny<COLS-1) map[nx][ny]->setType(Ground);
    }
    map[base.x()][base.y()]->setType(HQ);
}

// 测试随机地图生成是否正常
void Map::debug() const {
    for (const auto& row : map) {
        for (auto cell : row) {
            std::cout << static_cast<int>(cell->getType());
        }
        std::cout << std::endl;
    }
}

void Map::update() {}

