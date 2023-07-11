#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QWidget>
#include <QTimer>
#include <QPainter>
#include "board.h"
#include <QMouseEvent>
#include <QPushButton>
#include <QFont>
#include <QLabel>
#include <QString>
#include <QCloseEvent>
#include <QScrollArea>
#include <QScrollBar>
#include <QPropertyAnimation>
#include <QLineEdit>

class MainScene : public QWidget
{
    Q_OBJECT

public:
    MainScene(QWidget *parent = 0);

    ~MainScene();

    //初始化场景
    void initScene();

    //启动游戏
public slots:
    void playGame();
    void settings();
    void killLabGame();
    void savesettings();
    void aboutauthor();


public:
    QLabel *Test;

    //ui
    void initUI();
    QFont *GameFont;
    QFont *TimeFont;
    QFont *TotalTimeFont;
    QFont *TextFont;
    QFont *HisFont;
    QFont *PlayerFont;
    QFont *PlayFont;
    QFont *AuthorFont;
    QPushButton *BtltoDraw;
    QPushButton *BtlConcede;
    QPushButton *BtlRetract;
    QPushButton *BtlPlaygame;
    QPushButton *BtlSettings;
    QPushButton *BtlAboutAuthor;
    QPushButton *BtlReplay;
    QLabel *Player1;
    QLabel *Player2;
    QPixmap Player1Image;
    QPixmap Player2Image;
    QLabel *LabGameTime;
    QLabel *LabBlackTurnTime;
    QLabel *LabWhiteTurnTime;
    QLabel *LabBlackTurnMaxTime;
    QLabel *LabWhiteTurnMaxTime;
    QLabel *LabBlackTime;
    QLabel *LabWhiteTime;
    QLabel *LabGame;
    QLabel *LabHistory;
    QLabel *LabAboutAuthor;

    //设置界面
    int iniTime = 600;
    int StepTime = 180;
    int plusTurnTime = 10;
    QWidget *WidSettings;
    QPushButton *BtlSaveSettings;
    QLineEdit *LEditGameTime;
    QLabel *LabSetGameTime;
    QLabel *LabSetGameTimeP;
    QLineEdit *LEditStepTime;
    QLabel *LabSetStepTime;
    QLabel *LabSetStepTimeP;
    QLineEdit *LEditplusStepTime;
    QLabel *LabSetplusStepTime;
    QLabel *LabSetplusStepTimeP;

    //记谱
    QScrollArea *ScrollAreaHistory;
    QScrollBar *scrbar;
    QString HistoryText[1024];
    void freshHistory(QString newText);
    QString MoveText;
    QString rowtoHistory(int row);
    QString coltoHistory(int col);


    //绘制到屏幕中
    void paintEvent(QPaintEvent *);

    //地图对象
    Board m_board;

    //棋子对象
    Piece m_piece[32];
    void initpieces();

    //计时
    QTimer freTimer;
    QTimer TimeTimer;
    QTimer replayTimer;
    QTimer *showLG;
    int GameTime;
    QString calGameTime(int t);

    //点击、拖拽操作
    void mouseReleaseEvent(QMouseEvent *ev);
    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    int dragChess;
    int dragStartXcor;
    int dragStartYcor;
    int dragNowXcor;
    int dragNowYcor;
    bool ifdrag;
    void slide();

    //得到鼠标点击位置
    bool getRowCol(QPoint pt, int &row, int &col);

    //当前选中的棋子
    int selectPiece;

    //检查走法合法性
    struct Route {int num; int r_row[30]; int r_col[30]; int spe[30];};  //行列数组均从1开始
    bool checkRoute(const int row, const int col, const int sel);
    Route findRoute(const int sel);
    Route findRouteKing(const int sel);
    Route findRouteQueen(const int sel);
    Route findRouteRook(const int sel);
    Route findRouteKnight(const int sel);
    Route findRouteBishop(const int sel);
    Route findRoutePawn(const int sel);
    int checkPiece(int row, int col);

    //控制区
    bool blackControl[10][10];
    bool whiteControl[10][10];
    bool blackVirControl[10][10];
    bool whiteVirControl[10][10];
    void calVirControl();
    void calControl();

    //回合
    bool Turn;
    void newTurn();
    int numTurn;
    int blackTime;
    int whiteTime;
    int TurnTime;


    //棋子行为
    void moveChess(const int row, const int col, int sel);


    //游戏内特殊事件
    void giveCheckMate();
    void Check();
    bool ifCheckMate(bool color);
    void promotion();
    void endpromotion();
    QWidget *WidPromotion;
    QLabel *LabPromotion;
    QPushButton *BtlPromotionQueen;
    QPushButton *BtlPromotionKnight;
    QPushButton *BtlPromotionBishop;
    QPushButton *BtlPromotionRook;

    //游戏外特殊事件
    //求和
    QWidget *WidtoDraw;
    QLabel *LabtoDraw;
    QPushButton *BtltoDrawYes;
    QPushButton *BtltoDrawNo;

    //投降
    QWidget *WidConcede;
    QLabel *LabConcede;
    QPushButton *BtlConcedeYes;
    QPushButton *BtlConcedeNo;

    //悔棋
    QWidget *WidRetract;
    QLabel *LabRetract;
    QPushButton *BtlRetractYes;
    QPushButton *BtlRetractNo;

    //回放
    double replaytime;


public slots:
    void promotionQueen();
    void promotionKnight();
    void promotionBishop();
    void promotionRook();

    void toDraw();
    void toDrawYes();
    void toDrawNo();
    void concede();
    void concedeYes();
    void concedeNo();
    void retract();
    void retractYes();
    void retractNo();
    void replay();


public:

    //游戏结束
    void win(bool color);
    void draw();
    void endGame();
    bool end;




};

#endif // MAINSCENE_H
