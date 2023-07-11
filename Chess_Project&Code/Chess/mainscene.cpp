#include "mainscene.h"
#include "config.h"
#include "piece.h"
#include <QPainter>
#include <QString>
#include <QVBoxLayout>
#include <QScrollBar>
#include <QIntValidator>


MainScene::MainScene(QWidget *parent)
    : QWidget(parent)
{
    //初始化场景
    initScene();
}

MainScene::~MainScene()
{

}

void MainScene::initScene(){

    //设置窗口尺寸
    setFixedSize(GameWidth + ColWidth,GameHeight);

    //设置窗口标题
    setWindowTitle(GameTitle);

    //加载图标
    this->setWindowIcon(QIcon(GameIconPath));

    //定时器初始化
    //freTimer.setInterval(GameRate);
    //TimeTimer.setInterval(TimeRate);
    GameTime = 0;
    TurnTime = 0;
    blackTime = iniTime;
    whiteTime = iniTime;
    showLG = new QTimer(this);
    connect(showLG, SIGNAL(timeout()), this, SLOT(killLabGame()));

    numTurn = 0;

    //设置ui
    initUI();

    //初始化棋子
    initpieces();

    //禁用棋盘
    end = true;

    //初始化拖拽
    dragChess = -1;

    //开始游戏按钮
    connect(BtlPlaygame, SIGNAL(clicked()),this,SLOT(playGame()));
    //设置按钮
    connect(BtlSettings, SIGNAL(clicked()),this,SLOT(settings()));
    //关于作者按钮
    connect(BtlAboutAuthor, SIGNAL(clicked()),this,SLOT(aboutauthor()));
}

void MainScene::initUI()                                                                //初始化ui
{
    GameFont = new QFont;
    GameFont->setFamily("华文行楷");
    GameFont->setPointSize(72);

    TimeFont = new QFont;
    TimeFont->setFamily("微软雅黑");
    TimeFont->setPointSize(22);

    TotalTimeFont = new QFont;
    TotalTimeFont->setFamily("微软雅黑");
    TotalTimeFont->setPointSize(28);

    TextFont = new QFont;
    TextFont->setFamily("微软雅黑");
    TextFont->setPointSize(24);

    HisFont = new QFont;
    HisFont->setFamily("Consolas");
    HisFont->setPointSize(24);

    PlayerFont = new QFont;
    PlayerFont->setFamily("微软雅黑");
    PlayerFont->setPointSize(52);

    PlayFont = new QFont;
    PlayFont->setFamily("华文新魏");
    PlayFont->setPointSize(40);

    BtlPlaygame = new QPushButton(BtlPlaygameText,this);                                            //开始按钮
    BtlPlaygame->setGeometry(PlaygameX,PlaygameY,PlaygameW,PlaygameH);
    BtlPlaygame->setStyleSheet("background-color:#ffd17b;border-radius:10px;border:2px solid #000000;");
    BtlPlaygame->setFont(*PlayFont);
    BtlPlaygame->show();

    BtlSettings = new QPushButton(BtlSettingsText,this);                                            //设置按钮
    BtlSettings->setGeometry(BtlSettingsX,BtlSettingsY,BtlSettingsW,BtlSettingsH);
    BtlSettings->setStyleSheet("background-color:#ffd17b;border-radius:10px;border:2px solid #000000;");
    BtlSettings->setFont(*PlayFont);
    BtlSettings->show();

    BtlAboutAuthor = new QPushButton(BtlAboutAuthorText,this);                                      //关于作者按钮
    BtlAboutAuthor->setGeometry(BtlAboutAuthorX,BtlAboutAuthorY,BtlAboutAuthorW,BtlAboutAuthorH);
    BtlAboutAuthor->setStyleSheet("background-color:#ffd17b;border-radius:10px;border:2px solid #000000;");
    BtlAboutAuthor->setFont(*PlayFont);
    BtlAboutAuthor->show();

    BtltoDraw = new QPushButton(BtltoDrawText,this);                                                //求和按钮
    BtltoDraw->setGeometry(BtltoDrawX,BtltoDrawY,BtltoDrawW,BtltoDrawH);
    BtltoDraw->setFont(*TotalTimeFont);
    BtltoDraw->setStyleSheet("background-color:#ffd17b;border-radius:10px;border:1px solid #000000;");
    BtltoDraw->show();
    BtltoDraw->setEnabled(false);

    BtlConcede = new QPushButton(BtlConcedeText,this);                                              //认输按钮
    BtlConcede->setGeometry(BtlConcedeX,BtlConcedeY,BtlConcedeW,BtlConcedeH);
    BtlConcede->setFont(*TotalTimeFont);
    BtlConcede->setStyleSheet("background-color:#ffd17b;border-radius:10px;border:1px solid #000000;");
    BtlConcede->show();
    BtlConcede->setEnabled(false);

    BtlRetract = new QPushButton(BtlRetractText,this);                                              //悔棋按钮
    BtlRetract->setGeometry(BtlRetractX,BtlRetractY,BtlRetractW,BtlRetractH);
    BtlRetract->setFont(*TotalTimeFont);
    BtlRetract->setStyleSheet("background-color:#ffd17b;border-radius:10px;border:1px solid #000000;");
    BtlRetract->show();
    BtlRetract->setEnabled(false);

    BtlReplay = new QPushButton(BtlReplayText,this);                                                //回放按钮
    BtlReplay->setGeometry(BtlReplayX,BtlReplayY,BtlReplayW,BtlReplayH);
    BtlReplay->setFont(*TotalTimeFont);
    BtlReplay->setStyleSheet("background-color:#ffd17b;border-radius:10px;border:1px solid #000000;");
    BtlReplay->show();
    BtlReplay->setEnabled(false);

    Player1 = new QLabel;                                                                           //玩家1
    Player1->setParent(this);
    Player1->setAlignment(Qt::AlignTop);
    Player1->setGeometry(Player1X,Player1Y,Player1W,Player1H);
    Player1->setText(Player1Text);
    Player1->setFont(*PlayerFont);
    Player1->show();
    Player1Image.load(Player1ImagePath);

    Player2 = new QLabel;                                                                           //玩家2
    Player2->setParent(this);
    Player2->setAlignment(Qt::AlignTop);
    Player2->setGeometry(Player2X,Player2Y,Player2W,Player2H);
    Player2->setText(Player2Text);
    Player2->setFont(*PlayerFont);
    Player2->show();
    Player2Image.load(Player2ImagePath);

    LabGameTime = new QLabel;                                                                       //总用时
    LabGameTime->setParent(this);
    LabGameTime->setAlignment(Qt::AlignHCenter);
    LabGameTime->setGeometry(GameTimeX,GameTimeY,GameTimeW,GameTimeH);
    LabGameTime->setText(GameTimeText + calGameTime(GameTime));
    LabGameTime->setFont(*TotalTimeFont);
    LabGameTime->show();

    LabBlackTurnTime = new QLabel;                                                                  //黑色步时
    LabBlackTurnTime->setParent(this);
    LabBlackTurnTime->setGeometry(BlackTurnTimeX,BlackTurnTimeY,BlackTurnTimeW,BlackTurnTimeH);
    LabBlackTurnTime->setText(BlackTurnTimeText + calGameTime(TurnTime));
    LabBlackTurnTime->setFont(*TimeFont);
    LabBlackTurnTime->show();

    LabBlackTurnMaxTime = new QLabel;                                                               //黑色步长
    LabBlackTurnMaxTime->setParent(this);
    LabBlackTurnMaxTime->setGeometry(BlackTurnMaxTimeX,BlackTurnMaxTimeY,BlackTurnMaxTimeW,BlackTurnMaxTimeH);
    LabBlackTurnMaxTime->setText(BlackTurnMaxTimeText + calGameTime(StepTime));
    LabBlackTurnMaxTime->setFont(*TimeFont);
    LabBlackTurnMaxTime->show();

    LabWhiteTurnTime = new QLabel;                                                                  //白色步时
    LabWhiteTurnTime->setParent(this);
    LabWhiteTurnTime->setGeometry(WhiteTurnTimeX,WhiteTurnTimeY,WhiteTurnTimeW,WhiteTurnTimeH);
    LabWhiteTurnTime->setText(WhiteTurnTimeText + calGameTime(TurnTime));
    LabWhiteTurnTime->setFont(*TimeFont);
    LabWhiteTurnTime->show();

    LabWhiteTurnMaxTime = new QLabel;                                                               //白色步长
    LabWhiteTurnMaxTime->setParent(this);
    LabWhiteTurnMaxTime->setGeometry(WhiteTurnMaxTimeX,WhiteTurnMaxTimeY,WhiteTurnMaxTimeW,WhiteTurnMaxTimeH);
    LabWhiteTurnMaxTime->setText(WhiteTurnMaxTimeText + calGameTime(StepTime));
    LabWhiteTurnMaxTime->setFont(*TimeFont);
    LabWhiteTurnMaxTime->show();

    LabBlackTime = new QLabel;                                                                      //黑色局时
    LabBlackTime->setParent(this);
    LabBlackTime->setGeometry(BlackTimeX,BlackTimeY,BlackTimeW,BlackTimeH);
    LabBlackTime->setText(BlackTimeText + calGameTime(blackTime));
    LabBlackTime->setFont(*TimeFont);
    LabBlackTime->show();

    LabWhiteTime = new QLabel;                                                                      //白色局时
    LabWhiteTime->setParent(this);
    LabWhiteTime->setGeometry(WhiteTimeX,WhiteTimeY,WhiteTimeW,WhiteTimeH);
    LabWhiteTime->setText(WhiteTimeText + calGameTime(whiteTime));
    LabWhiteTime->setFont(*TimeFont);
    LabWhiteTime->show();

    LabGame = new QLabel;                                                                           //游戏显示
    LabGame->setParent(this);
    LabGame->setGeometry(LabGameX,LabGameY,LabGameW,LabGameH);
    LabGame->setFont(*GameFont);
    LabGame->setAlignment(Qt::AlignCenter);
    LabGame->setStyleSheet("color:#ffd17b;");
    LabGame->setVisible(0);

    Test = new QLabel;
    Test->setParent(this);
    Test->setGeometry(1450,950,50,50);
    Test->setFont(*TextFont);
    Test->show();
    Test->setVisible(false);

    ScrollAreaHistory = new QScrollArea(this);
    ScrollAreaHistory->setWidgetResizable(true);
    ScrollAreaHistory->setGeometry(LabHistoryX,LabHistoryY,LabHistoryW,LabHistoryH);
    scrbar = new QScrollBar;
    scrbar = ScrollAreaHistory->verticalScrollBar();
    LabHistory = new QLabel();
    LabHistory->setFont(*HisFont);
    LabHistory->setStyleSheet("background:white;");
    LabHistory->setWordWrap(true);
    LabHistory->setAlignment(Qt::AlignTop);
    ScrollAreaHistory->setWidget(LabHistory);
}

void MainScene::settings()                                                              //设置界面
{
    WidSettings = new QWidget;
    WidSettings->setFixedHeight(WidSettingsH);
    WidSettings->setFixedWidth(WidSettingsW);
    WidSettings->show();

    BtlSaveSettings = new QPushButton("保 存",WidSettings);
    BtlSaveSettings->setFont(*TextFont);
    BtlSaveSettings->setGeometry(BtlBtlSaveSettingsX,BtlBtlSaveSettingsY,BtlBtlSaveSettingsW,BtlBtlSaveSettingsH);
    BtlSaveSettings->show();
    connect(BtlSaveSettings, SIGNAL(clicked()),this,SLOT(savesettings()));

    //局时
    LabSetGameTime = new QLabel(WidSettings);
    LabSetGameTime->setFont(*TextFont);
    LabSetGameTime->setGeometry(LabSetGameTimeX,LabSetGameTimeY,LabSetGameTimeW,LabSetGameTimeH);
    LabSetGameTime->setText("局时：");
    LabSetGameTime->show();

    LabSetGameTimeP = new QLabel(WidSettings);
    LabSetGameTimeP->setFont(*TextFont);
    LabSetGameTimeP->setGeometry(LabSetGameTimePX,LabSetGameTimePY,LabSetGameTimePW,LabSetGameTimePH);
    LabSetGameTimeP->setText("秒 (1~28800秒)");
    LabSetGameTimeP->show();

    LEditGameTime = new QLineEdit(WidSettings);
    LEditGameTime->setFont(*TextFont);
    LEditGameTime->setGeometry(LEditGameTimeX,LEditGameTimeY,LEditGameTimeW,LEditGameTimeH);
    LEditGameTime->setValidator(new QIntValidator(1,28800,this));
    LEditGameTime->setText(QString::number(iniTime));
    LEditGameTime->show();

    //步时
    LabSetStepTime = new QLabel(WidSettings);
    LabSetStepTime->setFont(*TextFont);
    LabSetStepTime->setGeometry(LabSetStepTimeX,LabSetStepTimeY,LabSetStepTimeW,LabSetStepTimeH);
    LabSetStepTime->setText("步长：");
    LabSetStepTime->show();

    LabSetStepTimeP = new QLabel(WidSettings);
    LabSetStepTimeP->setFont(*TextFont);
    LabSetStepTimeP->setGeometry(LabSetStepTimePX,LabSetStepTimePY,LabSetStepTimePW,LabSetStepTimePH);
    LabSetStepTimeP->setText("秒 (1~28800秒)");
    LabSetStepTimeP->show();

    LEditStepTime = new QLineEdit(WidSettings);
    LEditStepTime->setFont(*TextFont);
    LEditStepTime->setGeometry(LEditStepTimeX,LEditStepTimeY,LEditStepTimeW,LEditStepTimeH);
    LEditStepTime->setValidator(new QIntValidator(1,28800,this));
    LEditStepTime->setText(QString::number(StepTime));
    LEditStepTime->show();

    //每步加时
    LabSetplusStepTime = new QLabel(WidSettings);
    LabSetplusStepTime->setFont(*TextFont);
    LabSetplusStepTime->setGeometry(LabSetplusStepTimeX,LabSetplusStepTimeY,LabSetplusStepTimeW,LabSetplusStepTimeH);
    LabSetplusStepTime->setText("每步增加局时：");
    LabSetplusStepTime->show();

    LabSetplusStepTimeP = new QLabel(WidSettings);
    LabSetplusStepTimeP->setFont(*TextFont);
    LabSetplusStepTimeP->setGeometry(LabSetplusStepTimePX,LabSetplusStepTimePY,LabSetplusStepTimePW,LabSetplusStepTimePH);
    LabSetplusStepTimeP->setText("秒 (0~600秒)");
    LabSetplusStepTimeP->show();

    LEditplusStepTime = new QLineEdit(WidSettings);
    LEditplusStepTime->setFont(*TextFont);
    LEditplusStepTime->setGeometry(LEditplusStepTimeX,LEditplusStepTimeY,LEditplusStepTimeW,LEditplusStepTimeH);
    LEditplusStepTime->setValidator(new QIntValidator(0,600,this));
    LEditplusStepTime->setText(QString::number(plusTurnTime));
    LEditplusStepTime->show();
}

void MainScene::savesettings()                                                          //保存设置
{
    iniTime = LEditGameTime->text().toInt();
    blackTime = iniTime;
    whiteTime = iniTime;
    LabBlackTime->setText(BlackTimeText + calGameTime(blackTime));
    LabWhiteTime->setText(WhiteTimeText + calGameTime(whiteTime));

    StepTime = LEditStepTime->text().toInt();
    LabBlackTurnMaxTime->setText(BlackTurnMaxTimeText + calGameTime(StepTime));
    LabWhiteTurnMaxTime->setText(WhiteTurnMaxTimeText + calGameTime(StepTime));

    plusTurnTime = LEditplusStepTime->text().toInt();
}

void MainScene::aboutauthor()                                                           //关于作者界面
{
    AuthorFont = new QFont;
    AuthorFont->setFamily("宋体");
    AuthorFont->setPointSize(18);

    LabAboutAuthor = new QLabel;
    LabAboutAuthor->setFont(*AuthorFont);
    LabAboutAuthor->setFixedHeight(LabAboutAuthorH);
    LabAboutAuthor->setFixedWidth(LabAboutAuthorW);
    LabAboutAuthor->setStyleSheet("background-color:#ffd17b;padding:3px");
    LabAboutAuthor->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    LabAboutAuthor->setWordWrap(true);
    LabAboutAuthor->setText(AboutAuthorText);
    LabAboutAuthor->show();
}

void MainScene::freshHistory(QString newText)                                           //更新记谱
{
    HistoryText[numTurn] = newText;
    QString output = "";
    for(int i=0; i<=numTurn; i++)
        output += HistoryText[i];
    LabHistory->setText(output);
    ScrollAreaHistory->setWidget(LabHistory);
    //默认页面最下方
    scrbar->setValue(scrbar->maximum());
}

QString MainScene::rowtoHistory(int row)                                                //转换row与记谱标记
{
    QString str[8] = {"8","7","6","5","4","3","2","1"};
    return str[row-1];
}

QString MainScene::coltoHistory(int col)                                                //转换col与记谱标记
{
    QString str[8] = {"a","b","c","d","e","f","g","h"};
    return str[col-1];
}

void MainScene::playGame()                                                              //游戏开始
{
    //隐藏开始按钮
    BtlPlaygame->setVisible(false);
    BtlSettings->setVisible(false);
    BtlAboutAuthor->setVisible(false);

    //启动定时器
    freTimer.start(GameRate);
    TimeTimer.start(TimeRate);

    //初始化回合
    Turn = false;
    newTurn();

    //启用棋盘
    end = false;


    //开始显示
    connect(&freTimer, &QTimer::timeout, [=](){
        update();
    });

    //计时器
    connect(&TimeTimer, &QTimer::timeout, [=](){
        GameTime ++;
        LabGameTime->setText(GameTimeText + calGameTime(GameTime));
        TurnTime ++;
        Test->setText(QString::number(selectPiece));
        if(Turn == true){
            LabWhiteTurnTime->setText(WhiteTurnTimeText + calGameTime(TurnTime));
            whiteTime --;
            LabWhiteTime->setText(WhiteTimeText + calGameTime(whiteTime));
        }else{
            LabBlackTurnTime->setText(BlackTurnTimeText + calGameTime(TurnTime));
            blackTime --;
            LabBlackTime->setText(BlackTimeText + calGameTime(blackTime));
        }
        if(whiteTime == 0){
            whiteTime = 0;
            win(false);
        }
        if(blackTime == 0){
            blackTime = 0;
            win(true);
        }
        if(TurnTime >= StepTime)
            win(!Turn);
    });

    //求和按钮
    BtltoDraw->setEnabled(true);
    connect(BtltoDraw, SIGNAL(clicked()),this,SLOT(toDraw()));

    //认输按钮
    BtlConcede->setEnabled(true);
    connect(BtlConcede, SIGNAL(clicked()),this,SLOT(concede()));

    //悔棋按钮
    connect(BtlRetract, SIGNAL(clicked()),this,SLOT(retract()));

    //回放按钮
    connect(BtlReplay, SIGNAL(clicked()),this,SLOT(replay()));

}

void MainScene::paintEvent(QPaintEvent *)                                               //绘制棋盘
{
    QPainter painter(this);
    QPixmap selectPix;
    selectPix.load(SelectPath);

    //绘制棋盘
    painter.drawPixmap(0,0,m_board.m_board_1);

    //绘制头像
    painter.drawPixmap(Player1ImageX,Player1ImageY,Player1Image);
    painter.drawPixmap(Player2ImageX,Player2ImageY,Player2Image);

    //绘制格间线
    for(int i=1; i<9; i++)
        painter.drawLine(QPoint(GameWidth/8*i,0),QPoint(GameWidth/8*i,GameHeight));
    for(int i=1; i<9; i++)
        painter.drawLine(QPoint(0,GameHeight/8*i),QPoint(GameWidth,GameHeight/8*i));

    //绘制可行区域
    if(selectPiece != -1){
        painter.drawPixmap(m_piece[selectPiece].Xcor + 4, m_piece[selectPiece].Ycor + 4, selectPix);
        Route r;
        r = findRoute(selectPiece);
        for(int i=1; i<=r.num; i++)
        {
            painter.drawPixmap(GameWidth / 8 * (r.r_col[i] - 1) + 4, GameHeight / 8 * (r.r_row[i] - 1) + 4, selectPix);
        }
    }

    //绘制棋子
    for(int i=0; i<32; i++){
        if(m_piece[i].dead == false && dragChess != i)
            painter.drawPixmap(m_piece[i].Xcor,m_piece[i].Ycor,m_piece[i].Pix);
    }

    //绘制被拖拽的棋子
    if(dragChess > -1){
        painter.drawPixmap(m_piece[dragChess].Xcor + dragNowXcor - dragStartXcor, m_piece[dragChess].Ycor + dragNowYcor - dragStartYcor, m_piece[dragChess].Pix);
    }

}

void MainScene::initpieces()                                                            //初始化棋子
{
    //初始化棋子颜色
    for(int i=0; i<16; i++)
        m_piece[i].color = false;//false代表黑棋
    for(int i=16; i<32; i++)
        m_piece[i].color = true;


    //初始棋子位置与种类
    for(int i=0; i<8; i++){
        m_piece[i].col = i+1;
        m_piece[i+8].col = i+1;
        m_piece[i+16].col = i+1;
        m_piece[i+24].col = i+1;
    }
    m_piece[0].type = Piece::ROOK;      m_piece[0].row = 1;
    m_piece[1].type = Piece::KNIGHT;    m_piece[1].row = 1;
    m_piece[2].type = Piece::BISHOP;    m_piece[2].row = 1;
    m_piece[3].type = Piece::QUEEN;     m_piece[3].row = 1;
    m_piece[4].type = Piece::KING;      m_piece[4].row = 1;
    m_piece[5].type = Piece::BISHOP;    m_piece[5].row = 1;
    m_piece[6].type = Piece::KNIGHT;    m_piece[6].row = 1;
    m_piece[7].type = Piece::ROOK;      m_piece[7].row = 1;
    m_piece[8].type = Piece::PAWN;      m_piece[8].row = 2;
    m_piece[9].type = Piece::PAWN;      m_piece[9].row = 2;
    m_piece[10].type = Piece::PAWN;     m_piece[10].row = 2;
    m_piece[11].type = Piece::PAWN;     m_piece[11].row = 2;
    m_piece[12].type = Piece::PAWN;     m_piece[12].row = 2;
    m_piece[13].type = Piece::PAWN;     m_piece[13].row = 2;
    m_piece[14].type = Piece::PAWN;     m_piece[14].row = 2;
    m_piece[15].type = Piece::PAWN;     m_piece[15].row = 2;
    m_piece[16].type = Piece::ROOK;     m_piece[16].row = 8;
    m_piece[17].type = Piece::KNIGHT;   m_piece[17].row = 8;
    m_piece[18].type = Piece::BISHOP;   m_piece[18].row = 8;
    m_piece[19].type = Piece::QUEEN;    m_piece[19].row = 8;
    m_piece[20].type = Piece::KING;     m_piece[20].row = 8;
    m_piece[21].type = Piece::BISHOP;   m_piece[21].row = 8;
    m_piece[22].type = Piece::KNIGHT;   m_piece[22].row = 8;
    m_piece[23].type = Piece::ROOK;     m_piece[23].row = 8;
    m_piece[24].type = Piece::PAWN;     m_piece[24].row = 7;
    m_piece[25].type = Piece::PAWN;     m_piece[25].row = 7;
    m_piece[26].type = Piece::PAWN;     m_piece[26].row = 7;
    m_piece[27].type = Piece::PAWN;     m_piece[27].row = 7;
    m_piece[28].type = Piece::PAWN;     m_piece[28].row = 7;
    m_piece[29].type = Piece::PAWN;     m_piece[29].row = 7;
    m_piece[30].type = Piece::PAWN;     m_piece[30].row = 7;
    m_piece[31].type = Piece::PAWN;     m_piece[31].row = 7;

    //得到棋子坐标
    for(int i=0; i<32; i++)
        m_piece[i].piecePosition();

    //加载棋子图片
    for(int i=0; i<32; i++)
        m_piece[i].piecePix();

    //初始化棋子存活情况、行走步数
    for(int i=0; i<32; i++){
        m_piece[i].dead = false;
        m_piece[i].moves = 0;
        m_piece[i].lastmove = 0;
        m_piece[i].lastrow = m_piece[i].row;
        m_piece[i].lastcol = m_piece[i].col;
        m_piece[i].last_lastmove = 0;
        m_piece[i].lasttype = m_piece[i].type;
    }

    //初始未选中任意棋子
    selectPiece = -1;

}

void MainScene::mouseReleaseEvent(QMouseEvent *ev)                                      //鼠标释放
{
    if(end)
        return;

    //结束拖拽
    dragChess = -1;

    //得到鼠标位置
    QPoint pt = ev->pos();
    int row, col, flag;

    //判断选择棋盘上一格
    flag = false;                                                                       //flag表示是否选到棋盘内合法的一格
    for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(getRowCol(pt,i,j)){
                row = i;
                col = j;
                flag = true;
            }

        }
    }
    if(!flag){
        ifdrag = false;
        return;
    }

    //检查选中的一格中是否有棋子
    flag = false;                                                                       //flag表示是否选到有本回合棋子的一格
    for(int i=0; i<32; i++){
        if(m_piece[i].col == col && m_piece[i].row == row && m_piece[i].dead == false){ //选中了棋子i
            flag = true;
            if(selectPiece == -1){                                                      //之前未选中棋子，选择失败
                ifdrag = false;
                return;
            }else if(selectPiece == i){                                                 //之前选中的是自己，仍继续选中自己
                ifdrag = false;
                return;
            }else{
                if(m_piece[i].color == m_piece[selectPiece].color){                     //之前选中的是别的本回合棋子，现在选中的也是本回合棋子，则保持选中之前的棋子
                    ifdrag = false;
                    return;
                }else{                                                                  //之前选中的是别的本回合棋子，现在选中的不是本回合棋子，判断能否能吃
                    if(checkRoute(row,col,selectPiece)){                                //能吃则吃
                        moveChess(row,col,selectPiece);
                        newTurn();
                        selectPiece = -1;
                    }else{                                                              //若不能吃，重置选择状态
                        selectPiece = -1;
                    }
                }
            }
            break;
        }
    }
    if(!flag){                                                                          //选择没棋子的一格，判断能否走到该格
        if(selectPiece != -1){
            if(checkRoute(row,col,selectPiece)){                                        //能走则走
                moveChess(row,col,selectPiece);
                newTurn();
                selectPiece = -1;
            }else{                                                                      //若不能走，重置选择状态
                selectPiece = -1;
            }
        }
    }
    ifdrag = false;
}

void MainScene::mousePressEvent(QMouseEvent *ev)                                        //鼠标按下
{
    if(end)
        return;

    QPoint pt = ev->pos();
    int row, col, flag;

    //选择棋盘上一格
    flag = false;                                                                       //flag表示是否选到棋盘内合法的一格
    for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            if(getRowCol(pt,i,j)){
                row = i;
                col = j;
                flag = true;
            }

        }
    }
    if(!flag)
        return;

    //检查选中的一格中是否有棋子
    flag = false;                                                                       //flag表示是否选到有该回合棋子的一格
    for(int i=0; i<32; i++){
        if(m_piece[i].col == col && m_piece[i].row == row && m_piece[i].dead == false){ //选中了棋子i
            flag = true;
            if(selectPiece == -1 && m_piece[i].color == Turn){                          //之前未选中棋子且选到的是本回合行动的棋子，则选中它
                selectPiece = i;
                //开始拖拽
                ifdrag = true;
                dragChess = i;
                dragStartXcor = pt.x();
                dragStartYcor = pt.y();
                dragNowXcor = pt.x();
                dragNowYcor = pt.y();
            }else if(selectPiece == i){                                                 //之前选中的是自己，继续选中它
                //开始拖拽
                ifdrag = true;
                dragChess = i;
                dragStartXcor = pt.x();
                dragStartYcor = pt.y();
                dragNowXcor = pt.x();
                dragNowYcor = pt.y();
            }else if(selectPiece != -1 && m_piece[i].color == m_piece[selectPiece].color){//之前选中的是别的本回合棋子，现在选择的也是本回合棋子，则改为选中当前棋子
                selectPiece = i;
                //开始拖拽
                ifdrag = true;
                dragChess = i;
                dragStartXcor = pt.x();
                dragStartYcor = pt.y();
                dragNowXcor = pt.x();
                dragNowYcor = pt.y();
            }
            break;
        }
    }

}

void MainScene::mouseMoveEvent(QMouseEvent *ev)                                         //拖拽
{
    if(end)
        return;

    QPoint pt = ev->pos();                                                              //拖拽过程中得到鼠标位置
    dragNowXcor = pt.x();
    dragNowYcor = pt.y();
}

void MainScene::slide()                                                                 //棋子滑动
{
    end = true;
    selectPiece = -1;
    int num;
    int live[2] = {-1,-1}, livenum = 0, dead = -1;
    int liveX[2], liveY[2], livelastX[2], livelastY[2];
    replaytime = 0;
    replayTimer.start(GameRate);
    for(num=0; num<32; num++){
        if(m_piece[num].lastmove == numTurn && m_piece[num].dead == false){
            livenum ++;
            live[livenum-1] = num;
            liveX[livenum-1] = m_piece[num].Xcor;
            liveY[livenum-1] = m_piece[num].Ycor;
            livelastX[livenum-1] = GameWidth / 8 * (m_piece[num].lastcol - 1);
            livelastY[livenum-1] = GameWidth / 8 * (m_piece[num].lastrow - 1);
            m_piece[num].Xcor = livelastX[livenum-1];
            m_piece[num].Ycor = livelastY[livenum-1];
        }
        if(m_piece[num].lastmove == numTurn && m_piece[num].dead == true){
            dead = num;
            m_piece[num].dead = false;
        }
    }

    connect(&replayTimer, &QTimer::timeout, [=](){
        replaytime = replaytime + GameRate;

        if(replaytime <= slideTime / 2.0){
            m_piece[live[0]].Xcor = livelastX[0] + (liveX[0] - livelastX[0]) * (replaytime / slideTime) * (replaytime / slideTime) * 2.0;
            m_piece[live[0]].Ycor = livelastY[0] + (liveY[0] - livelastY[0]) * (replaytime / slideTime) * (replaytime / slideTime) * 2.0;
        }else{
            m_piece[live[0]].Xcor = livelastX[0] + (liveX[0] - livelastX[0]) * ( - (replaytime / slideTime) * (replaytime / slideTime) * 2.0 + (replaytime / slideTime) * 4.0 - 1.0);
            m_piece[live[0]].Ycor = livelastY[0] + (liveY[0] - livelastY[0]) * ( - (replaytime / slideTime) * (replaytime / slideTime) * 2.0 + (replaytime / slideTime) * 4.0 - 1.0);
        }

        if(livenum == 2){
            if(replaytime <= slideTime / 2.0){
                m_piece[live[1]].Xcor = livelastX[1] + (liveX[1] - livelastX[1]) * (replaytime / slideTime) * (replaytime / slideTime) * 2.0;
                m_piece[live[1]].Ycor = livelastY[1] + (liveY[1] - livelastY[1]) * (replaytime / slideTime) * (replaytime / slideTime) * 2.0;
            }else{
                m_piece[live[1]].Xcor = livelastX[1] + (liveX[1] - livelastX[1]) * ( - (replaytime / slideTime) * (replaytime / slideTime) * 2.0 + (replaytime / slideTime) * 4.0 - 1.0);
                m_piece[live[1]].Ycor = livelastY[1] + (liveY[1] - livelastY[1]) * ( - (replaytime / slideTime) * (replaytime / slideTime) * 2.0 + (replaytime / slideTime) * 4.0 - 1.0);
            }
        }

        if(dead != -1){
            if((- GameWidth / 8 <= m_piece[live[0]].Xcor - liveX[0] && m_piece[live[0]].Xcor - liveX[0] <= GameWidth / 8)  && (- GameHeight / 8 <= m_piece[live[0]].Ycor - liveY[0] && m_piece[live[0]].Ycor - liveY[0] <= GameHeight / 8) && replaytime >= slideTime / 2.0)
                m_piece[dead].dead = true;
        }

        //结束动画
        if(replaytime >= slideTime){

            if(dead != -1){
                m_piece[dead].dead = true;
            }


            m_piece[live[0]].Xcor = GameWidth / 8 * (m_piece[live[0]].col - 1);
            m_piece[live[0]].Ycor = GameWidth / 8 * (m_piece[live[0]].row - 1);
            if(livenum == 2){
                m_piece[live[1]].Xcor = GameWidth / 8 * (m_piece[live[1]].col - 1);
                m_piece[live[1]].Ycor = GameWidth / 8 * (m_piece[live[1]].row - 1);
            }

            end = false;

            replayTimer.stop();
            disconnect(&replayTimer,0,0,0);
            return;
        }
    });
}

bool MainScene::getRowCol(QPoint pt, int &row, int &col)                                //判断鼠标是否选中有效单元格
{
    int Xcor = GameWidth / 8 * (col - 1);
    int Ycor = GameHeight / 8 *(row - 1);
    if(                                                                                 //判断是否选在了对应格内
    0 < (pt.x() - Xcor) && (GameWidth / 8) > (pt.x()-Xcor) &&
    0 < (pt.y() - Ycor) && (GameHeight / 8) > (pt.y() - Ycor)
    ){
        return true;
    }
    return false;
}

bool MainScene::checkRoute(const int row, const int col, const int sel)                 //判断sel棋子能否去到(row,col)。如果能，若该走法特殊，执行特殊部分。常规部分在moveChess函数中执行
{
    Route r = findRoute(sel);    //得到sel棋子所有可能的走法
    if(r.num > 0){
        for(int i=1; i<=r.num; i++){
            if(row == r.r_row[i] && col == r.r_col[i]){                                 //目标点存在合法走法
                //记谱
                if(m_piece[sel].type == Piece::KING)
                    MoveText = "K";
                if(m_piece[sel].type == Piece::QUEEN)
                    MoveText = "Q";
                if(m_piece[sel].type == Piece::KNIGHT)
                    MoveText = "N";
                if(m_piece[sel].type == Piece::ROOK)
                    MoveText = "R";
                if(m_piece[sel].type == Piece::BISHOP)
                    MoveText = "B";
                if(m_piece[sel].type == Piece::PAWN)
                    MoveText = "";

                if(checkPiece(row,col) != -1){
                    if(m_piece[sel].type == Piece::PAWN){
                        MoveText += coltoHistory(m_piece[sel].col);
                    }
                    MoveText += "x";
                }

                if(r.spe[i] == 1){                                                      //吃过路兵
                    //吃过路兵记谱
                    MoveText += coltoHistory(m_piece[sel].col) + "x";
                    for(int j=0; j<32; j++){
                        if(m_piece[sel].color == false){                                //黑棋
                            if(m_piece[j].row == row - 1 && m_piece[j].col == col && m_piece[j].dead == false && m_piece[j].color == true){
                                m_piece[j].last_lastmove = m_piece[j].lastmove;
                                m_piece[j].dead = true;
                                m_piece[j].lastmove = numTurn;
                            }
                        }else{                                                          //白棋
                            if(m_piece[j].row == row + 1 && m_piece[j].col == col && m_piece[j].dead == false && m_piece[j].color == false){
                                m_piece[j].last_lastmove = m_piece[j].lastmove;
                                m_piece[j].dead = true;
                                m_piece[j].lastmove = numTurn;
                            }
                        }
                    }
                }

                MoveText += coltoHistory(col) + rowtoHistory(row);

                if(r.spe[i] == 1)
                    MoveText += " e.p.";

                if(r.spe[i] == 2){                                                       //4种王车易位，完成车的走法
                    moveChess(1,4,BlackLeftRookNum);
                    MoveText = "0-0-0";
                }
                if(r.spe[i] == 3){
                    moveChess(1,6,BlackRightRookNum);
                    MoveText = "0-0";
                }
                if(r.spe[i] == 4){
                    moveChess(8,4,WhiteLeftRookNum);
                    MoveText = "0-0-0";
                }
                if(r.spe[i] == 5){
                    moveChess(8,6,WhiteRightRookNum);
                    MoveText = "0-0";
                }
                return true;
            }
        }
    }
    return false;
}

MainScene::Route MainScene::findRoute(const int sel)                                    //按输入的棋子分类查找可行区域
{
    if(m_piece[sel].type == Piece::KING)
        return findRouteKing(sel);
    else if(m_piece[sel].type == Piece::QUEEN)
        return findRouteQueen(sel);
    else if(m_piece[sel].type == Piece::ROOK)
        return findRouteRook(sel);
    else if(m_piece[sel].type == Piece::KNIGHT)
        return findRouteKnight(sel);
    else if(m_piece[sel].type == Piece::BISHOP)
        return findRouteBishop(sel);
    else
        return findRoutePawn(sel);
}

MainScene::Route MainScene::findRouteKing(const int sel)                                //王的可行区域，包含王车易位
{
    Route r;
    r.num = 0;
    for(int i=0; i<30; i++)
        r.spe[i] = 0;

    //正常走法
    for(int i=1; i<9; i++){//行
        for(int j=1; j<9; j++){//列
            //判断是否在王可走的范围内
            if(-1 <= m_piece[sel].row - i && m_piece[sel].row - i <= 1 &&
               -1 <= m_piece[sel].col - j && m_piece[sel].col - j <= 1 ){
                bool flag = true;
                if(m_piece[sel].color == true){
                    for(int num = 16; num<32; num++){
                        //判断是否有友方棋子
                        if(m_piece[num].row == i && m_piece[num].col == j && m_piece[num].dead == false){
                            flag = false;
                        }
                    }
                    if(flag){
                        r.num++;
                        r.r_row[r.num] = i;
                        r.r_col[r.num] = j;
                    }
                }else{
                    for(int num = 0; num<16; num++){
                        if(m_piece[num].row == i && m_piece[num].col == j && m_piece[num].dead == false){
                            flag = false;
                        }
                    }
                    if(flag){
                        r.num++;
                        r.r_row[r.num] = i;
                        r.r_col[r.num] = j;
                    }
                }
            }
        }
    }

    //王车易位
    //黑棋
    if(m_piece[sel].color == false && m_piece[sel].moves == 0 && (!whiteControl[m_piece[sel].row][m_piece[sel].col])){
        //左车
        if(m_piece[BlackLeftRookNum].moves == 0 && (!whiteControl[m_piece[sel].row][m_piece[sel].col - 1]) && (!whiteControl[m_piece[sel].row][m_piece[sel].col - 2]) && (!whiteControl[m_piece[sel].row][m_piece[sel].col - 3])){
            bool flag = true;
            for(int col=2; col<5; col++){
                for(int num=0; num<32; num++){
                    if(m_piece[num].row == 1 && m_piece[num].col == col && m_piece[num].dead == false)
                        flag = false;
                }
            }
            if(flag){
                r.num++;
                r.r_row[r.num] = 1;
                r.r_col[r.num] = 3;
                r.spe[r.num] = 2;
            }
        }
        //右车
        if(m_piece[BlackRightRookNum].moves == 0 && (!whiteControl[m_piece[sel].row][m_piece[sel].col + 1]) && (!whiteControl[m_piece[sel].row][m_piece[sel].col + 2])){
            bool flag = true;
            for(int col=6; col<8; col++){
                for(int num=0; num<32; num++){
                    if(m_piece[num].row == 1 && m_piece[num].col == col && m_piece[num].dead == false)
                        flag = false;
                }
            }
            if(flag){
                r.num++;
                r.r_row[r.num] = 1;
                r.r_col[r.num] = 7;
                r.spe[r.num] = 3;
            }
        }
    }
    //白棋
    else if(m_piece[sel].color == true && m_piece[sel].moves == 0 && (!blackControl[m_piece[sel].row][m_piece[sel].col])){
        //左车
        if(m_piece[WhiteLeftRookNum].moves == 0 && (!blackControl[m_piece[sel].row][m_piece[sel].col - 1]) && (!blackControl[m_piece[sel].row][m_piece[sel].col - 2]) && (!blackControl[m_piece[sel].row][m_piece[sel].col - 3])){
            bool flag = true;
            for(int col=2; col<5; col++){
                for(int num=0; num<32; num++){
                    if(m_piece[num].row == 8 && m_piece[num].col == col && m_piece[num].dead == false)
                        flag = false;
                }
            }
            if(flag){
                r.num++;
                r.r_row[r.num] = 8;
                r.r_col[r.num] = 3;
                r.spe[r.num] = 4;
            }
        }
        //右车
        if(m_piece[WhiteRightRookNum].moves == 0 && (!blackControl[m_piece[sel].row][m_piece[sel].col + 1]) && (!blackControl[m_piece[sel].row][m_piece[sel].col + 2])){
            bool flag = true;
            for(int col=6; col<8; col++){
                for(int num=0; num<32; num++){
                    if(m_piece[num].row == 8 && m_piece[num].col == col && m_piece[num].dead == false)
                        flag = false;
                }
            }
            if(flag){
                r.num++;
                r.r_row[r.num] = 8;
                r.r_col[r.num] = 7;
                r.spe[r.num] = 5;
            }
        }
    }



    return r;
}

MainScene::Route MainScene::findRouteQueen(const int sel)                               //后的可行区域
{
    Route r;
    int step;
    int num;
    r.num = 0;
    for(int i=0; i<30; i++)
        r.spe[i] = 0;
    for(step=m_piece[sel].row + 1; step<9; step++){//向下
        bool flag = true;
        for(num=0; num<32; num++){
            if(m_piece[num].col == m_piece[sel].col && m_piece[num].row == step && m_piece[num].dead == false){
                flag = false;
                break;
            }
        }
        if(flag){
            r.num++;
            r.r_row[r.num] = step;
            r.r_col[r.num] = m_piece[sel].col;
        }else if(m_piece[num].color != m_piece[sel].color){
            r.num++;
            r.r_row[r.num] = step;
            r.r_col[r.num] = m_piece[sel].col;
            break;
        }else
            break;
    }
    for(step=m_piece[sel].row - 1; step>0; step--){//向上
        bool flag = true;
        for(num=0; num<32; num++){
            if(m_piece[num].col == m_piece[sel].col && m_piece[num].row == step && m_piece[num].dead == false){
                flag = false;
                break;
            }
        }
        if(flag){
            r.num++;
            r.r_row[r.num] = step;
            r.r_col[r.num] = m_piece[sel].col;
        }else if(m_piece[num].color != m_piece[sel].color){
            r.num++;
            r.r_row[r.num] = step;
            r.r_col[r.num] = m_piece[sel].col;
            break;
        }else
            break;
    }
    for(step=m_piece[sel].col + 1; step<9; step++){//向右
        bool flag = true;
        for(num=0; num<32; num++){
            if(m_piece[num].row == m_piece[sel].row && m_piece[num].col == step && m_piece[num].dead == false){
                flag = false;
                break;
            }
        }
        if(flag){
            r.num++;
            r.r_col[r.num] = step;
            r.r_row[r.num] = m_piece[sel].row;
        }else if(m_piece[num].color != m_piece[sel].color){
            r.num++;
            r.r_col[r.num] = step;
            r.r_row[r.num] = m_piece[sel].row;
            break;
        }
        else
            break;
    }
    for(step=m_piece[sel].col - 1; step>0; step--){//向左
        bool flag = true;
        for(num=0; num<32; num++){
            if(m_piece[num].row == m_piece[sel].row && m_piece[num].col == step && m_piece[num].dead == false){
                flag = false;
                break;
            }
        }
        if(flag){
            r.num++;
            r.r_col[r.num] = step;
            r.r_row[r.num] = m_piece[sel].row;
        }else if(m_piece[num].color != m_piece[sel].color){
            r.num++;
            r.r_col[r.num] = step;
            r.r_row[r.num] = m_piece[sel].row;
            break;
        }
        else
            break;
    }

    step = 1;//向右下
    while(m_piece[sel].row + step < 9 && m_piece[sel].col + step < 9){
        bool flag = true;
        for(num=0; num<32; num++){
            if(m_piece[num].row == m_piece[sel].row + step && m_piece[num].col == m_piece[sel].col + step  && m_piece[num].dead == false){
                flag = false;
                break;
            }
        }
        if(flag){
            r.num++;
            r.r_col[r.num] = m_piece[sel].col + step;
            r.r_row[r.num] = m_piece[sel].row + step;
        }else if(m_piece[num].color != m_piece[sel].color){
            r.num++;
            r.r_col[r.num] = m_piece[sel].col + step;
            r.r_row[r.num] = m_piece[sel].row + step;
            break;
        }else
            break;
        step++;
    }

    step = 1;//向右上
    while(m_piece[sel].row - step > 0 && m_piece[sel].col + step < 9){
        bool flag = true;
        for(num=0; num<32; num++){
            if(m_piece[num].row == m_piece[sel].row - step && m_piece[num].col == m_piece[sel].col + step && m_piece[num].dead == false){
                flag = false;
                break;
            }
        }
        if(flag){
            r.num++;
            r.r_col[r.num] = m_piece[sel].col + step;
            r.r_row[r.num] = m_piece[sel].row - step;
        }else if(m_piece[num].color != m_piece[sel].color){
            r.num++;
            r.r_col[r.num] = m_piece[sel].col + step;
            r.r_row[r.num] = m_piece[sel].row - step;
            break;
        }else
            break;
        step++;
    }

    step = 1;//向左上
    while(m_piece[sel].row - step > 0 && m_piece[sel].col - step > 0){
        bool flag = true;
        for(num=0; num<32; num++){
            if(m_piece[num].row == m_piece[sel].row - step && m_piece[num].col == m_piece[sel].col - step && m_piece[num].dead == false){
                flag = false;
                break;
            }
        }
        if(flag){
            r.num++;
            r.r_col[r.num] = m_piece[sel].col - step;
            r.r_row[r.num] = m_piece[sel].row - step;
        }else if(m_piece[num].color != m_piece[sel].color){
            r.num++;
            r.r_col[r.num] = m_piece[sel].col - step;
            r.r_row[r.num] = m_piece[sel].row - step;
            break;
        }else
            break;
        step++;
    }

    step = 1;//向左下
    while(m_piece[sel].row + step < 9 && m_piece[sel].col - step > 0){
        bool flag = true;
        for(num=0; num<32; num++){
            if(m_piece[num].row == m_piece[sel].row + step && m_piece[num].col == m_piece[sel].col - step && m_piece[num].dead == false){
                flag = false;
                break;
            }
        }
        if(flag){
            r.num++;
            r.r_col[r.num] = m_piece[sel].col - step;
            r.r_row[r.num] = m_piece[sel].row + step;
        }else if(m_piece[num].color != m_piece[sel].color){
            r.num++;
            r.r_col[r.num] = m_piece[sel].col - step;
            r.r_row[r.num] = m_piece[sel].row + step;
            break;
        }else
            break;
        step++;
    }

    return r;
}

MainScene::Route MainScene::findRouteRook(const int sel)                                //车的可行区域
{
    Route r;
    int step;
    int num;
    r.num = 0;
    for(int i=0; i<30; i++)
        r.spe[i] = 0;
    for(step=m_piece[sel].row + 1; step<9; step++){//向下
        bool flag = true;
        for(num=0; num<32; num++){
            if(m_piece[num].col == m_piece[sel].col && m_piece[num].row == step && m_piece[num].dead == false){
                flag = false;
                break;
            }
        }
        if(flag){
            r.num++;
            r.r_row[r.num] = step;
            r.r_col[r.num] = m_piece[sel].col;
        }else if(m_piece[num].color != m_piece[sel].color){
            r.num++;
            r.r_row[r.num] = step;
            r.r_col[r.num] = m_piece[sel].col;
            break;
        }else
            break;
    }
    for(step=m_piece[sel].row - 1; step>0; step--){//向上
        bool flag = true;
        for(num=0; num<32; num++){
            if(m_piece[num].col == m_piece[sel].col && m_piece[num].row == step && m_piece[num].dead == false){
                flag = false;
                break;
            }
        }
        if(flag){
            r.num++;
            r.r_row[r.num] = step;
            r.r_col[r.num] = m_piece[sel].col;
        }else if(m_piece[num].color != m_piece[sel].color){
            r.num++;
            r.r_row[r.num] = step;
            r.r_col[r.num] = m_piece[sel].col;
            break;
        }else
            break;
    }
    for(step=m_piece[sel].col + 1; step<9; step++){//向右
        bool flag = true;
        for(num=0; num<32; num++){
            if(m_piece[num].row == m_piece[sel].row && m_piece[num].col == step && m_piece[num].dead == false){
                flag = false;
                break;
            }
        }
        if(flag){
            r.num++;
            r.r_col[r.num] = step;
            r.r_row[r.num] = m_piece[sel].row;
        }else if(m_piece[num].color != m_piece[sel].color){
            r.num++;
            r.r_col[r.num] = step;
            r.r_row[r.num] = m_piece[sel].row;
            break;
        }
        else
            break;
    }
    for(step=m_piece[sel].col - 1; step>0; step--){//向左
        bool flag = true;
        for(num=0; num<32; num++){
            if(m_piece[num].row == m_piece[sel].row && m_piece[num].col == step && m_piece[num].dead == false){
                flag = false;
                break;
            }
        }
        if(flag){
            r.num++;
            r.r_col[r.num] = step;
            r.r_row[r.num] = m_piece[sel].row;
        }else if(m_piece[num].color != m_piece[sel].color){
            r.num++;
            r.r_col[r.num] = step;
            r.r_row[r.num] = m_piece[sel].row;
            break;
        }
        else
            break;
    }

    return r;
}

MainScene::Route MainScene::findRouteKnight(const int sel)                              //马的可行区域
{
    Route r;
    r.num = 0;
    for(int i=0; i<30; i++)
        r.spe[i] = 0;
    int num;
    bool flag;

    if(m_piece[sel].row + 2 < 9 && m_piece[sel].col + 1 < 9){//五点钟方向
        flag = true;
        for(num=0; num<32; num++){
            if(m_piece[num].row == m_piece[sel].row + 2 && m_piece[num].col == m_piece[sel].col + 1 && m_piece[num].dead == false && m_piece[num].color == m_piece[sel].color){
                flag = false;
                break;
            }
        }
        if(flag){
            r.num++;
            r.r_row[r.num] = m_piece[sel].row + 2;
            r.r_col[r.num] = m_piece[sel].col + 1;
        }
    }

    if(m_piece[sel].row + 1 < 9 && m_piece[sel].col + 2 < 9){//四点钟方向
        flag = true;
        for(num=0; num<32; num++){
            if(m_piece[num].row == m_piece[sel].row + 1 && m_piece[num].col == m_piece[sel].col + 2 && m_piece[num].dead == false && m_piece[num].color == m_piece[sel].color){
                flag = false;
                break;
            }
        }
        if(flag){
            r.num++;
            r.r_row[r.num] = m_piece[sel].row + 1;
            r.r_col[r.num] = m_piece[sel].col + 2;
        }
    }

    if(m_piece[sel].row - 1 > 0 && m_piece[sel].col + 2 < 9){//二点钟方向
        flag = true;
        for(num=0; num<32; num++){
            if(m_piece[num].row == m_piece[sel].row - 1 && m_piece[num].col == m_piece[sel].col + 2 && m_piece[num].dead == false && m_piece[num].color == m_piece[sel].color){
                flag = false;
                break;
            }
        }
        if(flag){
            r.num++;
            r.r_row[r.num] = m_piece[sel].row - 1;
            r.r_col[r.num] = m_piece[sel].col + 2;
        }
    }

    if(m_piece[sel].row - 2 > 0 && m_piece[sel].col + 1 < 9){//一点钟方向
        flag = true;
        for(num=0; num<32; num++){
            if(m_piece[num].row == m_piece[sel].row - 2 && m_piece[num].col == m_piece[sel].col + 1 && m_piece[num].dead == false && m_piece[num].color == m_piece[sel].color){
                flag = false;
                break;
            }
        }
        if(flag){
            r.num++;
            r.r_row[r.num] = m_piece[sel].row - 2;
            r.r_col[r.num] = m_piece[sel].col + 1;
        }
    }

    if(m_piece[sel].row - 2 > 0 && m_piece[sel].col - 1 > 0){//十一点钟方向
        flag = true;
        for(num=0; num<32; num++){
            if(m_piece[num].row == m_piece[sel].row - 2 && m_piece[num].col == m_piece[sel].col - 1 && m_piece[num].dead == false && m_piece[num].color == m_piece[sel].color){
                flag = false;
                break;
            }
        }
        if(flag){
            r.num++;
            r.r_row[r.num] = m_piece[sel].row - 2;
            r.r_col[r.num] = m_piece[sel].col - 1;
        }
    }

    if(m_piece[sel].row - 1 > 0 && m_piece[sel].col - 2 > 0){//十点钟方向
        flag = true;
        for(num=0; num<32; num++){
            if(m_piece[num].row == m_piece[sel].row - 1 && m_piece[num].col == m_piece[sel].col - 2 && m_piece[num].dead == false && m_piece[num].color == m_piece[sel].color){
                flag = false;
                break;
            }
        }
        if(flag){
            r.num++;
            r.r_row[r.num] = m_piece[sel].row - 1;
            r.r_col[r.num] = m_piece[sel].col - 2;
        }
    }

    if(m_piece[sel].row + 1 < 9 && m_piece[sel].col - 2 > 0){//八点钟方向
        flag = true;
        for(num=0; num<32; num++){
            if(m_piece[num].row == m_piece[sel].row + 1 && m_piece[num].col == m_piece[sel].col - 2 && m_piece[num].dead == false && m_piece[num].color == m_piece[sel].color){
                flag = false;
                break;
            }
        }
        if(flag){
            r.num++;
            r.r_row[r.num] = m_piece[sel].row + 1;
            r.r_col[r.num] = m_piece[sel].col - 2;
        }
    }

    if(m_piece[sel].row + 2 < 9 && m_piece[sel].col - 1 > 0){//七点钟方向
        flag = true;
        for(num=0; num<32; num++){
            if(m_piece[num].row == m_piece[sel].row + 2 && m_piece[num].col == m_piece[sel].col - 1 && m_piece[num].dead == false && m_piece[num].color == m_piece[sel].color){
                flag = false;
                break;
            }
        }
        if(flag){
            r.num++;
            r.r_row[r.num] = m_piece[sel].row + 2;
            r.r_col[r.num] = m_piece[sel].col - 1;
        }
    }

    return r;
}

MainScene::Route MainScene::findRouteBishop(const int sel)                              //象的可行区域
{
    Route r;
    r.num = 0;
    for(int i=0; i<30; i++)
        r.spe[i] = 0;
    int num;
    int step = 1;//向右上
    while(m_piece[sel].row - step > 0 && m_piece[sel].col + step < 9){
        bool flag = true;
        for(num=0; num<32; num++){
            if(m_piece[num].row == m_piece[sel].row - step && m_piece[num].col == m_piece[sel].col + step && m_piece[num].dead == false){
                flag = false;
                break;
            }
        }
        if(flag){
            r.num++;
            r.r_col[r.num] = m_piece[sel].col + step;
            r.r_row[r.num] = m_piece[sel].row - step;
        }else if(m_piece[num].color != m_piece[sel].color){
            r.num++;
            r.r_col[r.num] = m_piece[sel].col + step;
            r.r_row[r.num] = m_piece[sel].row - step;
            break;
        }else
            break;
        step++;
    }

    step = 1;//向左上
    while(m_piece[sel].row - step > 0 && m_piece[sel].col - step > 0){
        bool flag = true;
        for(num=0; num<32; num++){
            if(m_piece[num].row == m_piece[sel].row - step && m_piece[num].col == m_piece[sel].col - step && m_piece[num].dead == false){
                flag = false;
                break;
            }
        }
        if(flag){
            r.num++;
            r.r_col[r.num] = m_piece[sel].col - step;
            r.r_row[r.num] = m_piece[sel].row - step;
        }else if(m_piece[num].color != m_piece[sel].color){
            r.num++;
            r.r_col[r.num] = m_piece[sel].col - step;
            r.r_row[r.num] = m_piece[sel].row - step;
            break;
        }else
            break;
        step++;
    }

    step = 1;//向左下
    while(m_piece[sel].row + step < 9 && m_piece[sel].col - step > 0){
        bool flag = true;
        for(num=0; num<32; num++){
            if(m_piece[num].row == m_piece[sel].row + step && m_piece[num].col == m_piece[sel].col - step && m_piece[num].dead == false){
                flag = false;
                break;
            }
        }
        if(flag){
            r.num++;
            r.r_col[r.num] = m_piece[sel].col - step;
            r.r_row[r.num] = m_piece[sel].row + step;
        }else if(m_piece[num].color != m_piece[sel].color){
            r.num++;
            r.r_col[r.num] = m_piece[sel].col - step;
            r.r_row[r.num] = m_piece[sel].row + step;
            break;
        }else
            break;
        step++;
    }

    step = 1;//向右下
    while(m_piece[sel].row + step < 9 && m_piece[sel].col + step < 9){
        bool flag = true;
        for(num=0; num<32; num++){
            if(m_piece[num].row == m_piece[sel].row + step && m_piece[num].col == m_piece[sel].col + step  && m_piece[num].dead == false){
                flag = false;
                break;
            }
        }
        if(flag){
            r.num++;
            r.r_col[r.num] = m_piece[sel].col + step;
            r.r_row[r.num] = m_piece[sel].row + step;
        }else if(m_piece[num].color != m_piece[sel].color){
            r.num++;
            r.r_col[r.num] = m_piece[sel].col + step;
            r.r_row[r.num] = m_piece[sel].row + step;
            break;
        }else
            break;
        step++;
    }

    return r;;
}

MainScene::Route MainScene::findRoutePawn(const int sel)                                //兵的可行区域，包含吃过路兵与兵升变
{
    Route r;
    r.num = 0;
    for(int i=0; i<30; i++)
        r.spe[i] = 0;
    int step;
    int num;
    if(m_piece[sel].color == false){//黑棋兵
        if(m_piece[sel].moves == 0){//前进
            for(step=1; step<3; step++){
                bool flag = true;
                for(num=0; num<32; num++){
                    if(m_piece[num].col == m_piece[sel].col && m_piece[num].row == m_piece[sel].row + step && m_piece[num].dead == false){
                        flag = false;
                        break;
                    }
                }
                if(flag){
                    r.num++;
                    r.r_row[r.num] = m_piece[sel].row + step;
                    r.r_col[r.num] = m_piece[sel].col;
                }else
                    break;
            }
        }else{
            bool flag = true;
            for(num=0; num<32; num++){
                if(m_piece[num].col == m_piece[sel].col && m_piece[num].row ==  m_piece[sel].row + 1 && m_piece[num].dead == false){
                    flag = false;
                    break;
                }
            }
            if(flag){
                r.num++;
                r.r_row[r.num] = m_piece[sel].row + 1;
                r.r_col[r.num] = m_piece[sel].col;
            }
        }
        if(1 < m_piece[sel].col && m_piece[sel].col < 8){//吃子，非靠边列
            for(step=-1; step<=1; step+=2){
                bool flag = false;
                for(num=0; num<32; num++){
                    if(m_piece[num].col == m_piece[sel].col + step && m_piece[num].row == m_piece[sel].row + 1 && m_piece[num].dead == false && m_piece[sel].color != m_piece[num].color){
                        flag = true;
                        break;
                    }
                }
                if(flag){
                    r.num++;
                    r.r_row[r.num] = m_piece[sel].row + 1;
                    r.r_col[r.num] = m_piece[sel].col + step;
                }
            }
        }else if(m_piece[sel].col == 1){//最左列
            step = 1;
            bool flag = false;
            for(num=0; num<32; num++){
                if(m_piece[num].col == m_piece[sel].col + step && m_piece[num].row == m_piece[sel].row + 1 && m_piece[num].dead == false && m_piece[sel].color != m_piece[num].color){
                    flag = true;
                    break;
                }
            }
            if(flag){
                r.num++;
                r.r_row[r.num] = m_piece[sel].row + 1;
                r.r_col[r.num] = m_piece[sel].col + step;
            }
        }else if(m_piece[sel].col == 8){//最右列
            step = -1;
            bool flag = false;
            for(num=0; num<32; num++){
                if(m_piece[num].col == m_piece[sel].col + step && m_piece[num].row == m_piece[sel].row + 1 && m_piece[num].dead == false && m_piece[sel].color != m_piece[num].color){
                    flag = true;
                    break;
                }
            }
            if(flag){
                r.num++;
                r.r_row[r.num] = m_piece[sel].row + 1;
                r.r_col[r.num] = m_piece[sel].col + step;
            }
        }
        if(m_piece[sel].row == 5){//吃过路兵
            if(1 < m_piece[sel].col && m_piece[sel].col < 8){//非靠边列
                for(step=-1; step<=1; step+=2){
                    for(num=0; num<32; num++){
                        if(m_piece[num].col == m_piece[sel].col + step && m_piece[num].row == m_piece[sel].row && m_piece[num].dead == false && m_piece[sel].color != m_piece[num].color && m_piece[num].lastmove == numTurn - 1 && m_piece[num].moves == 1){
                            r.num++;
                            r.r_row[r.num] = m_piece[sel].row + 1;
                            r.r_col[r.num] = m_piece[sel].col + step;
                            r.spe[r.num] = 1;
                        }
                    }
                }
            }else if(m_piece[sel].col == 1){//最左列
                step = 1;
                for(num=0; num<32; num++){
                    if(m_piece[num].col == m_piece[sel].col + step && m_piece[num].row == m_piece[sel].row && m_piece[num].dead == false && m_piece[sel].color != m_piece[num].color && m_piece[num].lastmove == numTurn - 1 && m_piece[num].moves == 1){
                        r.num++;
                        r.r_row[r.num] = m_piece[sel].row + 1;
                        r.r_col[r.num] = m_piece[sel].col + step;
                        r.spe[r.num] = 1;
                    }
                }
            }else if(m_piece[sel].col == 8){//最右列
                step = -1;
                for(num=0; num<32; num++){
                    if(m_piece[num].col == m_piece[sel].col + step && m_piece[num].row == m_piece[sel].row && m_piece[num].dead == false && m_piece[sel].color != m_piece[num].color && m_piece[num].lastmove == numTurn - 1 && m_piece[num].moves == 1){
                        r.num++;
                        r.r_row[r.num] = m_piece[sel].row + 1;
                        r.r_col[r.num] = m_piece[sel].col + step;
                        r.spe[r.num] = 1;
                    }
                }
            }
        }
    }else{//白棋兵
        if(m_piece[sel].moves == 0){//移动
            for(step=1; step<3; step++){
                bool flag = true;
                for(num=0; num<32; num++){
                    if(m_piece[num].col == m_piece[sel].col && m_piece[num].row == m_piece[sel].row - step && m_piece[num].dead == false){
                        flag = false;
                        break;
                    }
                }
                if(flag){
                    r.num++;
                    r.r_row[r.num] = m_piece[sel].row - step;
                    r.r_col[r.num] = m_piece[sel].col;
                }else
                    break;
            }
        }else{
            bool flag = true;
            for(num=0; num<32; num++){
                if(m_piece[num].col == m_piece[sel].col && m_piece[num].row ==  m_piece[sel].row - 1 && m_piece[num].dead == false){
                    flag = false;
                    break;
                }
            }
            if(flag){
                r.num++;
                r.r_row[r.num] = m_piece[sel].row - 1;
                r.r_col[r.num] = m_piece[sel].col;
            }
        }
        if(1 < m_piece[sel].col && m_piece[sel].col < 8){//吃子，非靠边列
            for(step=-1; step<=1; step+=2){
                bool flag = false;
                for(num=0; num<32; num++){
                    if(m_piece[num].col == m_piece[sel].col + step && m_piece[num].row == m_piece[sel].row - 1 && m_piece[num].dead == false && m_piece[sel].color != m_piece[num].color){
                        flag = true;
                        break;
                    }
                }
                if(flag){
                    r.num++;
                    r.r_row[r.num] = m_piece[sel].row - 1;
                    r.r_col[r.num] = m_piece[sel].col + step;
                }
            }
        }else if(m_piece[sel].col == 1){//最左列
            step = 1;
            bool flag = false;
            for(num=0; num<32; num++){
                if(m_piece[num].col == m_piece[sel].col + step && m_piece[num].row == m_piece[sel].row - 1 && m_piece[num].dead == false && m_piece[sel].color != m_piece[num].color){
                    flag = true;
                    break;
                }
            }
            if(flag){
                r.num++;
                r.r_row[r.num] = m_piece[sel].row - 1;
                r.r_col[r.num] = m_piece[sel].col + step;
            }
        }else if(m_piece[sel].col == 8){//最右列
            step = -1;
            bool flag = false;
            for(num=0; num<32; num++){
                if(m_piece[num].col == m_piece[sel].col + step && m_piece[num].row == m_piece[sel].row - 1 && m_piece[num].dead == false && m_piece[sel].color != m_piece[num].color){
                    flag = true;
                    break;
                }
            }
            if(flag){
                r.num++;
                r.r_row[r.num] = m_piece[sel].row - 1;
                r.r_col[r.num] = m_piece[sel].col + step;
            }
        }
        if(m_piece[sel].row == 4){//吃过路兵
            if(1 < m_piece[sel].col && m_piece[sel].col < 8){//非靠边列
                for(step=-1; step<=1; step+=2){
                    for(num=0; num<32; num++){
                        if(m_piece[num].col == m_piece[sel].col + step && m_piece[num].row == m_piece[sel].row && m_piece[num].dead == false && m_piece[sel].color != m_piece[num].color && m_piece[num].lastmove == numTurn - 1 && m_piece[num].moves == 1){
                            r.num++;
                            r.r_row[r.num] = m_piece[sel].row - 1;
                            r.r_col[r.num] = m_piece[sel].col + step;
                            r.spe[r.num] = 1;
                        }
                    }
                }
            }else if(m_piece[sel].col == 1){//最左列
                step = 1;
                for(num=0; num<32; num++){
                    if(m_piece[num].col == m_piece[sel].col + step && m_piece[num].row == m_piece[sel].row && m_piece[num].dead == false && m_piece[sel].color != m_piece[num].color && m_piece[num].lastmove == numTurn - 1 && m_piece[num].moves == 1){
                        r.num++;
                        r.r_row[r.num] = m_piece[sel].row - 1;
                        r.r_col[r.num] = m_piece[sel].col + step;
                        r.spe[r.num] = 1;
                    }
                }
            }else if(m_piece[sel].col == 8){//最右列
                step = -1;
                for(num=0; num<32; num++){
                    if(m_piece[num].col == m_piece[sel].col + step && m_piece[num].row == m_piece[sel].row && m_piece[num].dead == false && m_piece[sel].color != m_piece[num].color && m_piece[num].lastmove == numTurn - 1 && m_piece[num].moves == 1){
                        r.num++;
                        r.r_row[r.num] = m_piece[sel].row - 1;
                        r.r_col[r.num] = m_piece[sel].col + step;
                        r.spe[r.num] = 1;
                    }
                }
            }
        }
    }
    return r;
}

int MainScene::checkPiece(int row, int col)                                             //判断单元格上是否有棋子
{
    for(int num=0; num<32; num++){
        if(m_piece[num].row == row && m_piece[num].col == col)
            return num;
    }
    return -1;
}

void MainScene::moveChess(const int row, const int col, int sel)                        //棋子移动、吃子
{
    //吃子
    for(int num=0; num<32; num++){
        if(m_piece[num].row == row && m_piece[num].col == col && m_piece[num].dead == false){
            m_piece[num].last_lastmove = m_piece[num].lastmove;
            m_piece[num].dead = true;
            m_piece[num].lastmove = numTurn;
            break;
        }
    }

    //记录上一步，防止移动不合法
    m_piece[sel].lastrow = m_piece[sel].row;
    m_piece[sel].lastcol = m_piece[sel].col;
    m_piece[sel].last_lastmove = m_piece[sel].lastmove;

    //移动
    m_piece[sel].row = row;
    m_piece[sel].col = col;
    m_piece[sel].piecePosition();
    m_piece[sel].moves ++;
    m_piece[sel].lastmove = numTurn;


}

void MainScene::newTurn()                                                               //检查是否送将、将军、将死、兵升变，一切正常则下一回合
{

    int num;
    bool ifpro = false;
    //计算控制区
    calControl();

    //判断是否送将
    if(Turn == false){
        if(whiteControl[m_piece[BlackKingNum].row][m_piece[BlackKingNum].col]){
            LabGame->setText(giveCheckMateText);
            LabGame->show();
            showLG->start(1000);
            giveCheckMate();
            return;
        }
    }else{
        if(blackControl[m_piece[WhiteKingNum].row][m_piece[WhiteKingNum].col]){
            LabGame->setText(giveCheckMateText);
            LabGame->show();
            showLG->start(1000);
            giveCheckMate();
            return;
        }
    }

    if(numTurn > 0 && !ifdrag)
        slide();

    //如果未送将，则不会回退，判断兵升变
    for(num=0; num<32; num++){
        if(m_piece[num].type == Piece::PAWN){
            if(m_piece[num].color == false && m_piece[num].row == 8){
                promotion();
                ifpro = true;
            }
            if(m_piece[num].color == true && m_piece[num].row == 1){
                promotion();
                ifpro = true;
            }
        }
    }
    //如果兵升变，则回合会在promotion函数里结束
    if(ifpro)
        return;

    //如果将军，判断是否将死；如果未将军，判断是否逼和
    if(Turn == false){
        if(blackControl[m_piece[WhiteKingNum].row][m_piece[WhiteKingNum].col]){
            if(ifCheckMate(true)){
                win(false);
                MoveText += "#";
                while(MoveText.length()<=8){
                    MoveText += " ";
                }
                freshHistory(MoveText);
                return;
            }
            else
                Check();
        }else
            if(ifCheckMate(true)){
                draw();
                return;
            }
    }

    if(Turn == true){
        if(whiteControl[m_piece[BlackKingNum].row][m_piece[BlackKingNum].col]){
            if(ifCheckMate(false)){
                win(true);
                MoveText += "#";
                freshHistory(MoveText);
                return;
            }
           else
                Check();
        }else
            if(ifCheckMate(false)){
                draw();
                return;
            }
    }




    //如果新一回合能正常开始，记谱，交换回合，计算时间

    //记谱
    if(Turn == true){
        while(MoveText.length()<=9){
            MoveText += " ";
        }
        freshHistory(MoveText);
    }else{
        if(numTurn != 0){
            if(numTurn/2+1 < 10)
                freshHistory(MoveText + "\n" + QString::number(numTurn/2+1) + ". ");
            else
                freshHistory(MoveText + "\n" + QString::number(numTurn/2+1) + ".");
        }else{
            freshHistory(QString::number(numTurn/2+1) + ". ");
        }
    }


    if(Turn == false){
        Turn = true;
        whiteTime += plusTurnTime;
    }
    else{
        Turn = false;
        blackTime += plusTurnTime;
    }
    numTurn++;
    if(numTurn>1){
        BtlRetract->setEnabled(true);
        BtlReplay->setEnabled(true);
    }

    TurnTime = 0;
    LabBlackTurnTime->setText(BlackTurnTimeText + calGameTime(TurnTime));
    LabWhiteTurnTime->setText(BlackTurnTimeText + calGameTime(TurnTime));
}

void MainScene::giveCheckMate()                                                         //若送将，回退至上一回合
{

    for(int num=0; num<32; num++){
        if(m_piece[num].lastmove == numTurn){
            if(m_piece[num].dead == false){
                m_piece[num].row = m_piece[num].lastrow;
                m_piece[num].col = m_piece[num].lastcol;
                m_piece[num].lastmove = m_piece[num].last_lastmove;
                if(m_piece[num].type != m_piece[num].lasttype){
                    m_piece[num].type = m_piece[num].lasttype;
                    if(m_piece[num].color == true)
                        m_piece[num].Pix.load(WhitePawnPath);
                    else
                        m_piece[num].Pix.load(BlackQueenPath);
                }
                m_piece[num].piecePosition();
                m_piece[num].moves --;
            }else{
                m_piece[num].dead = false;
                m_piece[num].lastmove = m_piece[num].last_lastmove;
            }
        }
    }
}

void MainScene::calVirControl()                                                         //计算用于检查是否将死的虚拟控制区
{
    int num;
    for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            blackVirControl[i][j] = false;
            whiteVirControl[i][j] = false;
        }
    }
    for(num=0; num<16; num++){
        if(m_piece[num].dead == false){
            Route r;
            r = findRoute(num);
            for(int i=1; i<=r.num; i++){
                blackVirControl[r.r_row[i]][r.r_col[i]] = true;
            }
        }
    }
    for(num=16; num<32; num++){
        if(m_piece[num].dead == false){
            Route r;
            r = findRoute(num);
            for(int i=1; i<=r.num; i++){
                whiteVirControl[r.r_row[i]][r.r_col[i]] = true;
            }
        }
    }
}

void MainScene::calControl()                                                            //计算用于计算是否送将、将军的控制区
{
    int num;
    for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            blackControl[i][j] = false;
            whiteControl[i][j] = false;
        }
    }
    for(num=0; num<16; num++){
        if(m_piece[num].dead == false){
            Route r;
            r = findRoute(num);
            for(int i=1; i<=r.num; i++){
                blackControl[r.r_row[i]][r.r_col[i]] = true;
            }
        }
    }
    for(num=16; num<32; num++){
        if(m_piece[num].dead == false){
            Route r;
            r = findRoute(num);
            for(int i=1; i<=r.num; i++){
                whiteControl[r.r_row[i]][r.r_col[i]] = true;
            }
        }
    }
}

void MainScene::Check()                                                                 //将军事件
{
    MoveText += "+";

    LabGame->setText(CheckText);
    LabGame->show();
    showLG->start(1000);
}

bool MainScene::ifCheckMate(bool color)                                                 //判断是否将死
{
    Route r[16];
    int num0,KingNum;
    if(color == false){
        num0 = 0;
        KingNum = BlackKingNum;
    }
    else{
        num0 = 16;
        KingNum = WhiteKingNum;
    }

    for(int i=0; i<16; i++){
        if(m_piece[i+num0].dead == true)
            r[i].num = 0;
        else
            r[i] = findRoute(i+num0);
    }

    for(int i=0; i<16; i++){
        for(int j=1; j<=r[i].num; j++){
            numTurn++;
            moveChess(r[i].r_row[j],r[i].r_col[j],i+num0);
            calVirControl();
            if(color == false){
                if(whiteVirControl[m_piece[KingNum].row][m_piece[KingNum].col]){
                    giveCheckMate();
                }else{
                    giveCheckMate();
                    numTurn--;
                    return false;
                }
            }else{
                if(blackVirControl[m_piece[KingNum].row][m_piece[KingNum].col]){
                    giveCheckMate();
                }else{
                    giveCheckMate();
                    numTurn--;
                    return false;
                }
            }
            numTurn--;
        }
    }
    return true;
}

void MainScene::promotion()                                                             //兵升变事件
{
    WidPromotion = new QWidget;

    //设置弹出窗口为模态
    WidPromotion->setWindowModality(Qt::ApplicationModal);
    //不允许右上角退出
    WidPromotion->setWindowFlags(Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);
    WidPromotion->show();
    WidPromotion->setFixedHeight(WidPromotionH);
    WidPromotion->setFixedWidth(WidPromotionW);

    LabPromotion = new QLabel(WidPromotion);
    LabPromotion->setGeometry(LabPromotionX,LabPromotionY,LabPromotionW,LabPromotionH);
    LabPromotion->setFont(*TextFont);
    LabPromotion->setText(LabPromotionText);
    LabPromotion->show();

    BtlPromotionQueen = new QPushButton("后",WidPromotion);
    BtlPromotionQueen->setGeometry(BtlPromotionQueenX,BtlPromotionQueenY,BtlPromotionW,BtlPromotionH);
    BtlPromotionQueen->setFont(*TextFont);
    BtlPromotionQueen->show();
    connect(BtlPromotionQueen, SIGNAL(clicked()),this,SLOT(promotionQueen()));

    BtlPromotionKnight = new QPushButton("马",WidPromotion);
    BtlPromotionKnight->setGeometry(BtlPromotionKnightX,BtlPromotionKnightY,BtlPromotionW,BtlPromotionH);
    BtlPromotionKnight->setFont(*TextFont);
    BtlPromotionKnight->show();
    connect(BtlPromotionKnight, SIGNAL(clicked()),this,SLOT(promotionKnight()));

    BtlPromotionBishop = new QPushButton("象",WidPromotion);
    BtlPromotionBishop->setGeometry(BtlPromotionBishopX,BtlPromotionBishopY,BtlPromotionW,BtlPromotionH);
    BtlPromotionBishop->setFont(*TextFont);
    BtlPromotionBishop->show();
    connect(BtlPromotionBishop, SIGNAL(clicked()),this,SLOT(promotionBishop()));

    BtlPromotionRook = new QPushButton("车",WidPromotion);
    BtlPromotionRook->setGeometry(BtlPromotionRookX,BtlPromotionRookY,BtlPromotionW,BtlPromotionH);
    BtlPromotionRook->setFont(*TextFont);
    BtlPromotionRook->show();
    connect(BtlPromotionRook, SIGNAL(clicked()),this,SLOT(promotionRook()));

}

void MainScene::endpromotion()                                                          //结束兵升变，完成回合
{
    int num;
    //计算控制区
    for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            blackControl[i][j] = false;
            whiteControl[i][j] = false;
        }
    }
    for(num=0; num<16; num++){
        if(m_piece[num].dead == false){
            Route r;
            r = findRoute(num);
            for(int i=1; i<=r.num; i++){
                blackControl[r.r_row[i]][r.r_col[i]] = true;
            }
        }
    }
    for(num=16; num<32; num++){
        if(m_piece[num].dead == false){
            Route r;
            r = findRoute(num);
            for(int i=1; i<=r.num; i++){
                whiteControl[r.r_row[i]][r.r_col[i]] = true;
            }
        }
    }

    //如果将军，判断是否将死；如果未将军，判断是否逼和
    if(Turn == false){
        if(blackControl[m_piece[WhiteKingNum].row][m_piece[WhiteKingNum].col]){
            if(ifCheckMate(true)){
                win(false);
                MoveText += "#";
                freshHistory("\t " + MoveText);
                return;
            }
            else
                Check();
        }else
            if(ifCheckMate(true)){
                draw();
                return;
            }
    }

    if(Turn == true){
        if(whiteControl[m_piece[BlackKingNum].row][m_piece[BlackKingNum].col]){
            if(ifCheckMate(false)){
                win(true);
                MoveText += "#";
                freshHistory(MoveText);
                return;
            }
           else
                Check();
        }else
            if(ifCheckMate(false)){
                draw();
                return;
            }
    }




    //如果新一回合能正常开始，记谱，交换回合，计算时间
    //记谱
    if(Turn == true){
        while(MoveText.length()<=9){
            MoveText += " ";
        }
        freshHistory(MoveText);
    }else{
        if(numTurn != 0){
            freshHistory(MoveText + "\n" + QString::number(numTurn/2+1) + ". ");
        }else
            freshHistory(QString::number(numTurn/2+1) + ". ");
    }


    if(Turn == false){
        Turn = true;
        whiteTime += plusTurnTime;
    }
    else{
        Turn = false;
        blackTime += plusTurnTime;
    }
    numTurn++;
    TurnTime = 0;
    LabBlackTurnTime->setText(BlackTurnTimeText + calGameTime(TurnTime));
    LabWhiteTurnTime->setText(BlackTurnTimeText + calGameTime(TurnTime));
}

void MainScene::promotionQueen()                                                        //兵升变为后
{
    for(int num=0; num<32; num++){
        if(m_piece[num].type == Piece::PAWN){
            if(m_piece[num].color == false && m_piece[num].row == 8){
                m_piece[num].type = Piece::QUEEN;
                m_piece[num].Pix.load(BlackQueenPath);
            }
            if(m_piece[num].color == true && m_piece[num].row == 1){
                m_piece[num].type = Piece::QUEEN;
                m_piece[num].Pix.load(WhiteQueenPath);
            }
        }
    }
    MoveText += "=Q";
    WidPromotion->setVisible(false);
    endpromotion();
}

void MainScene::promotionKnight()                                                       //兵升变为马
{
    for(int num=0; num<32; num++){
        if(m_piece[num].type == Piece::PAWN){
            if(m_piece[num].color == false && m_piece[num].row == 8){
                m_piece[num].type = Piece::KNIGHT;
                m_piece[num].Pix.load(BlackKnightPath);
            }
            if(m_piece[num].color == true && m_piece[num].row == 1){
                m_piece[num].type = Piece::KNIGHT;
                m_piece[num].Pix.load(WhiteKnightPath);
            }
        }
    }
    MoveText += "=N";
    WidPromotion->setVisible(false);
    endpromotion();
}

void MainScene::promotionBishop()                                                       //兵升变为象
{
    for(int num=0; num<32; num++){
        if(m_piece[num].type == Piece::PAWN){
            if(m_piece[num].color == false && m_piece[num].row == 8){
                m_piece[num].type = Piece::BISHOP;
                m_piece[num].Pix.load(BlackBishopPath);
            }
            if(m_piece[num].color == true && m_piece[num].row == 1){
                m_piece[num].type = Piece::BISHOP;
                m_piece[num].Pix.load(WhiteBishopPath);
            }
        }
    }
    MoveText += "=B";
    WidPromotion->setVisible(false);
    endpromotion();
}

void MainScene::promotionRook()                                                         //兵升变为车
{
    for(int num=0; num<32; num++){
        if(m_piece[num].type == Piece::PAWN){
            if(m_piece[num].color == false && m_piece[num].row == 8){
                m_piece[num].type = Piece::ROOK;
                m_piece[num].Pix.load(BlackRookPath);
            }
            if(m_piece[num].color == true && m_piece[num].row == 1){
                m_piece[num].type = Piece::ROOK;
                m_piece[num].Pix.load(WhiteRookPath);
            }
        }
    }
    MoveText += "=R";
    WidPromotion->setVisible(false);
    endpromotion();
}

void MainScene::toDraw()                                                                //求和事件
{
    selectPiece = -1;
    WidtoDraw = new QWidget;
    //设置弹出窗口为模态，使得用户必须先决定是否和棋
    WidtoDraw->setWindowModality(Qt::ApplicationModal);
    WidtoDraw->show();
    WidtoDraw->setFixedHeight(WidtoDrawH);
    WidtoDraw->setFixedWidth(WidtoDrawW);

    LabtoDraw = new QLabel(WidtoDraw);
    LabtoDraw->setGeometry(LabtoDrawX,LabtoDrawY,LabtoDrawW,LabtoDrawH);
    LabtoDraw->setFont(*TextFont);
    LabtoDraw->setAlignment(Qt::AlignLeft);
    if(Turn == true)
        LabtoDraw->setText(WhitetoDrawText);
    else
        LabtoDraw->setText(BlacktoDrawText);
    LabtoDraw->show();

    BtltoDrawYes = new QPushButton("是",WidtoDraw);
    BtltoDrawYes->setGeometry(BtltoDrawYesX,BtltoDrawYesY,BtltoDrawYesW,BtltoDrawYesH);
    BtltoDrawYes->setFont(*TextFont);
    BtltoDrawYes->show();

    BtltoDrawNo = new QPushButton("否",WidtoDraw);
    BtltoDrawNo->setGeometry(BtltoDrawNoX,BtltoDrawNoY,BtltoDrawNoW,BtltoDrawNoH);
    BtltoDrawNo->setFont(*TextFont);
    BtltoDrawNo->show();

    connect(BtltoDrawYes, SIGNAL(clicked()),this,SLOT(toDrawYes()));
    connect(BtltoDrawNo, SIGNAL(clicked()),this,SLOT(toDrawNo()));

}

void MainScene::toDrawYes()                                                             //同意求和
{
    draw();
    WidtoDraw->setVisible(false);
}

void MainScene::toDrawNo()                                                              //不同意求和
{
    WidtoDraw->setVisible(false);
}

void MainScene::concede()                                                               //投降事件
{
    selectPiece = -1;
    WidConcede = new QWidget;
    //设置弹出窗口为模态
    WidConcede->setWindowModality(Qt::ApplicationModal);
    WidConcede->show();
    WidConcede->setFixedHeight(WidtoDrawH);
    WidConcede->setFixedWidth(WidtoDrawW);

    LabConcede = new QLabel(WidConcede);
    LabConcede->setGeometry(LabtoDrawX,LabtoDrawY,LabtoDrawW,LabtoDrawH);
    LabConcede->setFont(*TextFont);
    LabConcede->setAlignment(Qt::AlignLeft);
    if(Turn == true)
        LabConcede->setText(WhiteConcedeText);
    else
        LabConcede->setText(BlackConcedeText);
    LabConcede->show();

    BtlConcedeYes = new QPushButton("是",WidConcede);
    BtlConcedeYes->setGeometry(BtltoDrawYesX,BtltoDrawYesY,BtltoDrawYesW,BtltoDrawYesH);
    BtlConcedeYes->setFont(*TextFont);
    BtlConcedeYes->show();

    BtlConcedeNo = new QPushButton("否",WidConcede);
    BtlConcedeNo->setGeometry(BtltoDrawNoX,BtltoDrawNoY,BtltoDrawNoW,BtltoDrawNoH);
    BtlConcedeNo->setFont(*TextFont);
    BtlConcedeNo->show();

    connect(BtlConcedeYes, SIGNAL(clicked()),this,SLOT(concedeYes()));
    connect(BtlConcedeNo, SIGNAL(clicked()),this,SLOT(concedeNo()));
}

void MainScene::concedeYes()                                                            //确认投降
{
    win(!Turn);
    WidConcede->setVisible(false);
}

void MainScene::concedeNo()                                                             //放弃投降
{
    WidConcede->setVisible(false);
}

void MainScene::retract()                                                               //悔棋事件
{
    selectPiece = -1;
    WidRetract = new QWidget;
    //设置弹出窗口为模态
    WidRetract->setWindowModality(Qt::ApplicationModal);
    WidRetract->show();
    WidRetract->setFixedHeight(WidtoDrawH);
    WidRetract->setFixedWidth(WidtoDrawW);

    LabRetract = new QLabel(WidRetract);
    LabRetract->setGeometry(LabtoDrawX,LabtoDrawY,LabtoDrawW,LabtoDrawH);
    LabRetract->setFont(*TextFont);
    LabRetract->setAlignment(Qt::AlignLeft);
    if(Turn == true)
        LabRetract->setText(BlackRetractText);
    else
        LabRetract->setText(WhiteRetractText);
    LabRetract->show();

    BtlRetractYes = new QPushButton("是",WidRetract);
    BtlRetractYes->setGeometry(BtltoDrawYesX,BtltoDrawYesY,BtltoDrawYesW,BtltoDrawYesH);
    BtlRetractYes->setFont(*TextFont);
    BtlRetractYes->show();

    BtlRetractNo = new QPushButton("否",WidRetract);
    BtlRetractNo->setGeometry(BtltoDrawNoX,BtltoDrawNoY,BtltoDrawNoW,BtltoDrawNoH);
    BtlRetractNo->setFont(*TextFont);
    BtlRetractNo->show();

    connect(BtlRetractYes, SIGNAL(clicked()),this,SLOT(retractYes()));
    connect(BtlRetractNo, SIGNAL(clicked()),this,SLOT(retractNo()));
}

void MainScene::retractYes()                                                            //同意悔棋
{
    int num;
    numTurn --;
    freshHistory("");

    for(num=0; num<32; num++){
        if(m_piece[num].lastmove == numTurn){
            if(m_piece[num].dead == false){
                m_piece[num].row = m_piece[num].lastrow;
                m_piece[num].col = m_piece[num].lastcol;
                m_piece[num].lastmove = m_piece[num].last_lastmove;
                if(m_piece[num].type != m_piece[num].lasttype){
                    m_piece[num].type = m_piece[num].lasttype;
                    if(m_piece[num].color == true)
                        m_piece[num].Pix.load(WhitePawnPath);
                    else
                        m_piece[num].Pix.load(BlackQueenPath);
                }
                m_piece[num].piecePosition();
                m_piece[num].moves --;
            }else{
                m_piece[num].dead = false;
                m_piece[num].lastmove = m_piece[num].last_lastmove;
            }
        }
    }


    //计算控制区
    calControl();

    //判断将军
    if(Turn == false){
        if(blackControl[m_piece[WhiteKingNum].row][m_piece[WhiteKingNum].col]){
            if(ifCheckMate(true)){
                win(false);
                MoveText += "#";
                freshHistory("\t " + MoveText);
                return;
            }
            else
                Check();
        }else
            if(ifCheckMate(true)){
                draw();
                return;
            }
    }
    if(Turn == true){
        if(whiteControl[m_piece[BlackKingNum].row][m_piece[BlackKingNum].col]){
            if(ifCheckMate(false)){
                win(true);
                MoveText += "#";
                freshHistory(MoveText);
                return;
            }
           else
                Check();
        }else
            if(ifCheckMate(false)){
                draw();
                return;
            }
    }

    //交换回合，悔棋不给额外步时
    if(Turn == false){
        Turn = true;
    }
    else{
        Turn = false;
    }
    //不能连续悔棋
    BtlRetract->setEnabled(false);
    TurnTime = 0;
    LabBlackTurnTime->setText(BlackTurnTimeText + calGameTime(TurnTime));
    LabWhiteTurnTime->setText(WhiteTurnTimeText + calGameTime(TurnTime));


    WidRetract->setVisible(false);
    if(numTurn == 1)
        BtlRetract->setEnabled(false);
}

void MainScene::retractNo()                                                             //不同意悔棋
{
    WidRetract->setVisible(false);
}

void MainScene::replay()                                                                //回放事件
{
    end = true;
    BtlReplay->setEnabled(false);
    selectPiece = -1;
    int num;
    int live[2] = {-1,-1}, livenum = 0, dead = -1;
    int liveX[2], liveY[2], livelastX[2], livelastY[2];
    Piece::TYPE nowtype = Piece::PAWN;
    int pro = -1;
    replaytime = 0;
    replayTimer.start(GameRate);
    for(num=0; num<32; num++){
        if(m_piece[num].lastmove == numTurn - 1 && m_piece[num].dead == false){
            livenum ++;
            live[livenum-1] = num;
            liveX[livenum-1] = m_piece[num].Xcor;
            liveY[livenum-1] = m_piece[num].Ycor;
            livelastX[livenum-1] = GameWidth / 8 * (m_piece[num].lastcol - 1);
            livelastY[livenum-1] = GameWidth / 8 * (m_piece[num].lastrow - 1);
            m_piece[num].Xcor = livelastX[livenum-1];
            m_piece[num].Ycor = livelastY[livenum-1];
            if(m_piece[num].type != m_piece[num].lasttype){
                nowtype = m_piece[num].type;
                m_piece[num].type = m_piece[num].lasttype;
                m_piece[num].piecePix();
                pro = num;
            }
        }
        if(m_piece[num].lastmove == numTurn - 1 && m_piece[num].dead == true){
            dead = num;
            m_piece[num].dead = false;
        }
    }

    connect(&replayTimer, &QTimer::timeout, [=](){
        replaytime = replaytime + GameRate;

        if(replaytime <= replayTime / 2.0){
            m_piece[live[0]].Xcor = livelastX[0] + (liveX[0] - livelastX[0]) * (replaytime / replayTime) * (replaytime / replayTime) * 2.0;
            m_piece[live[0]].Ycor = livelastY[0] + (liveY[0] - livelastY[0]) * (replaytime / replayTime) * (replaytime / replayTime) * 2.0;
        }else{
            m_piece[live[0]].Xcor = livelastX[0] + (liveX[0] - livelastX[0]) * ( - (replaytime / replayTime) * (replaytime / replayTime) * 2.0 + (replaytime / replayTime) * 4.0 - 1.0);
            m_piece[live[0]].Ycor = livelastY[0] + (liveY[0] - livelastY[0]) * ( - (replaytime / replayTime) * (replaytime / replayTime) * 2.0 + (replaytime / replayTime) * 4.0 - 1.0);
        }

        if(livenum == 2){
            if(replaytime <= replayTime / 2.0){
                m_piece[live[1]].Xcor = livelastX[1] + (liveX[1] - livelastX[1]) * (replaytime / replayTime) * (replaytime / replayTime) * 2.0;
                m_piece[live[1]].Ycor = livelastY[1] + (liveY[1] - livelastY[1]) * (replaytime / replayTime) * (replaytime / replayTime) * 2.0;
            }else{
                m_piece[live[1]].Xcor = livelastX[1] + (liveX[1] - livelastX[1]) * ( - (replaytime / replayTime) * (replaytime / replayTime) * 2.0 + (replaytime / replayTime) * 4.0 - 1.0);
                m_piece[live[1]].Ycor = livelastY[1] + (liveY[1] - livelastY[1]) * ( - (replaytime / replayTime) * (replaytime / replayTime) * 2.0 + (replaytime / replayTime) * 4.0 - 1.0);
            }
        }

        if(dead != -1){
            if((- GameWidth / 8 <= m_piece[live[0]].Xcor - liveX[0] && m_piece[live[0]].Xcor - liveX[0] <= GameWidth / 8)  && (- GameHeight / 8 <= m_piece[live[0]].Ycor - liveY[0] && m_piece[live[0]].Ycor - liveY[0] <= GameHeight / 8) && replaytime >= replayTime / 2.0)
                m_piece[dead].dead = true;
        }

        //结束动画
        if(replaytime >= replayTime){

            if(pro != -1){
                m_piece[pro].type = nowtype;
                m_piece[pro].piecePix();
            }

            if(dead != -1){
                m_piece[dead].dead = true;
            }


            m_piece[live[0]].Xcor = GameWidth / 8 * (m_piece[live[0]].col - 1);
            m_piece[live[0]].Ycor = GameWidth / 8 * (m_piece[live[0]].row - 1);
            if(livenum == 2){
                m_piece[live[1]].Xcor = GameWidth / 8 * (m_piece[live[1]].col - 1);
                m_piece[live[1]].Ycor = GameWidth / 8 * (m_piece[live[1]].row - 1);
            }

            BtlReplay->setEnabled(true);
            end = false;

            replayTimer.stop();
            disconnect(&replayTimer,0,0,0);
            return;
        }
    });

}

void MainScene::win(bool color)                                                         //一方胜利
{
    QString Text;
    if(color){
        Text = WhiteWinText;
    }else{
        Text = BlackWinText;
    }

    LabGame->setText(Text);
    LabGame->show();
    endGame();
}

void MainScene::killLabGame()                                                           //关闭游戏显示
{
    LabGame->setVisible(0);
}

void MainScene::draw()                                                                  //平局
{
    LabGame->setText(DrawText);
    LabGame->show();
    endGame();
}

void MainScene::endGame()                                                               //结束游戏
{
    TimeTimer.stop();
    BtltoDraw->setEnabled(false);
    BtlConcede->setEnabled(false);
    BtlRetract->setEnabled(false);
    BtlReplay->setEnabled(false);
    end = true;
}

QString MainScene::calGameTime(int t)                                                   //游戏时间
{
    QString str;
    QString ti[60] = {"00","01","02","03","04","05","06","07","08","09","10","11","12","13","14","15","16","17","18","19",
                      "20","21","22","23","24","25","26","27","28","29","30","31","32","33","34","35","36","37","38","39",
                      "40","41","42","43","44","45","46","47","48","49","50","51","52","53","54","55","56","57","58","59"};
    int time, hour, min, sec;
    time = t;
    sec = time % 60;
    time = time / 60;
    min = time % 60;
    hour = time / 60;
    str = ti[hour] + ":" + ti[min] + ":" + ti[sec];
    if(hour >= 60)
        return "enough!";
    return str;
}

