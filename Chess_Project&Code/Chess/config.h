#ifndef CONFIG_H
#define CONFIG_H





//游戏参数
#define GameWidth 1000
#define GameHeight 1000
#define ColWidth 500
#define GameTitle "国际象棋 v1.0"
#define GameResPath "./chess.rcc"
#define GameRate 10
#define TimeRate 1000
#define GameIconPath ":/res/GameIcon.png"
//#define plusTurnTime 10
//define StepTime 180
//#define iniTime 600
#define maxTurn 1024

//开始游戏按钮
#define PlaygameX 300
#define PlaygameY 301
#define PlaygameH 75
#define PlaygameW 400
#define BtlPlaygameText "开始游戏"

//设置按钮
#define BtlSettingsX 300
#define BtlSettingsY 426
#define BtlSettingsH 75
#define BtlSettingsW 400
#define BtlSettingsText "设      置"

//关于作者按钮
#define BtlAboutAuthorX 300
#define BtlAboutAuthorY 551
#define BtlAboutAuthorH 75
#define BtlAboutAuthorW 400
#define BtlAboutAuthorText "关于作者"

//设置界面
#define WidSettingsH 425
#define WidSettingsW 635

#define LabSetGameTimeX 35
#define LabSetGameTimeY 25
#define LabSetGameTimeH 50
#define LabSetGameTimeW 150
#define LabSetGameTimePX 370
#define LabSetGameTimePY 25
#define LabSetGameTimePH 50
#define LabSetGameTimePW 250
#define LEditGameTimeX 260
#define LEditGameTimeY 25
#define LEditGameTimeH 50
#define LEditGameTimeW 105

#define LabSetStepTimeX 35
#define LabSetStepTimeY 125
#define LabSetStepTimeH 50
#define LabSetStepTimeW 150
#define LabSetStepTimePX 370
#define LabSetStepTimePY 125
#define LabSetStepTimePH 50
#define LabSetStepTimePW 250
#define LEditStepTimeX 260
#define LEditStepTimeY 125
#define LEditStepTimeH 50
#define LEditStepTimeW 105

#define LabSetplusStepTimeX 35
#define LabSetplusStepTimeY 225
#define LabSetplusStepTimeH 50
#define LabSetplusStepTimeW 210
#define LabSetplusStepTimePX 370
#define LabSetplusStepTimePY 225
#define LabSetplusStepTimePH 50
#define LabSetplusStepTimePW 250
#define LEditplusStepTimeX 260
#define LEditplusStepTimeY 225
#define LEditplusStepTimeH 50
#define LEditplusStepTimeW 105

#define BtlBtlSaveSettingsX 237
#define BtlBtlSaveSettingsY 325
#define BtlBtlSaveSettingsH 60
#define BtlBtlSaveSettingsW 150

//关于作者界面
#define LabAboutAuthorH 350
#define LabAboutAuthorW 600
#define AboutAuthorText "    本程序为清华大学2021-2022春季学期计算机程序设计（20740073）大作业，作者为未央水木-12翁正洋，指导老师为黄维通老师。\n    若在使用程序的过程中有任何疑问，请查阅程序使用说明书。如仍有疑问，请与作者联系：wengzy21@mails.tsinghua.edu.cn\n\n\n翁正洋\n2022年5月20日"

//Player1
#define Player1X 1225
#define Player1Y 10
#define Player1H 100
#define Player1W 250
#define Player1Text "Player2"
#define Player1ImagePath ":/res/Player1.png"
#define Player1ImageX 1025
#define Player1ImageY 13

//Player2
#define Player2X 1225
#define Player2Y 750
#define Player2H 100
#define Player2W 250
#define Player2Text "Player1"
#define Player2ImagePath ":/res/Player2.png"
#define Player2ImageX 1025
#define Player2ImageY 750

//记谱
#define LabHistoryX 1025
#define LabHistoryY 325
#define LabHistoryH 225
#define LabHistoryW 450

//回放
#define BtlReplayX 1025
#define BtlReplayY 570
#define BtlReplayH 75
#define BtlReplayW 215
#define BtlReplayText "回   放"
#define replayTime 1500
#define slideTime 1000

//求和按钮
#define BtltoDrawX 1025
#define BtltoDrawY 665
#define BtltoDrawH 75
#define BtltoDrawW 215
#define BtltoDrawText "求   和"

//投降按钮
#define BtlConcedeX 1260
#define BtlConcedeY 665
#define BtlConcedeH 75
#define BtlConcedeW 215
#define BtlConcedeText "认   输"

//悔棋按钮
#define BtlRetractX 1260
#define BtlRetractY 570
#define BtlRetractH 75
#define BtlRetractW 215
#define BtlRetractText "悔   棋"

//求和&投降&悔棋弹窗
#define WidtoDrawH 250
#define WidtoDrawW 500
#define LabtoDrawX 35
#define LabtoDrawY 45
#define LabtoDrawH 50
#define LabtoDrawW 448
#define WhitetoDrawText "白棋请求和棋，黑棋是否同意？"
#define BlacktoDrawText "黑棋请求和棋，白棋是否同意？"
#define WhiteConcedeText "白棋是否确认投降？"
#define BlackConcedeText "黑棋是否确认投降？"
#define WhiteRetractText "白棋请求悔棋，黑棋是否同意？"
#define BlackRetractText "黑棋请求悔棋，白棋是否同意？"
#define BtltoDrawYesX 35
#define BtltoDrawYesY 140
#define BtltoDrawYesH 75
#define BtltoDrawYesW 175
#define BtltoDrawNoX 290
#define BtltoDrawNoY 140
#define BtltoDrawNoH 75
#define BtltoDrawNoW 175

//升变弹窗
#define WidPromotionH 320
#define WidPromotionW 384
#define LabPromotionX 32
#define LabPromotionY 32
#define LabPromotionH 64
#define LabPromotionW 320
#define LabPromotionText "请选择将兵升变为："
#define BtlPromotionQueenX 32
#define BtlPromotionQueenY 128
#define BtlPromotionKnightX 224
#define BtlPromotionKnightY 128
#define BtlPromotionBishopX 32
#define BtlPromotionBishopY 224
#define BtlPromotionRookX 224
#define BtlPromotionRookY 224
#define BtlPromotionH 64
#define BtlPromotionW 128

//总游戏时间
#define GameTimeX 1025
#define GameTimeY 265
#define GameTimeH 64
#define GameTimeW 450
#define GameTimeText "游戏时长："

//当前回合数
#define TurnX 1280
#define TurnY 0
#define TurnH 64
#define TurnW 200

//用时
#define BlackTurnTimeX 1295
#define BlackTurnTimeY 157
#define BlackTurnTimeH 50
#define BlackTurnTimeW 250
#define BlackTurnTimeText "步时:"

#define BlackTurnMaxTimeX 1295
#define BlackTurnMaxTimeY 207
#define BlackTurnMaxTimeH 50
#define BlackTurnMaxTimeW 250
#define BlackTurnMaxTimeText "步长:"

#define WhiteTurnTimeX 1295
#define WhiteTurnTimeY 897
#define WhiteTurnTimeH 50
#define WhiteTurnTimeW 250
#define WhiteTurnTimeText "步时:"

#define WhiteTurnMaxTimeX 1295
#define WhiteTurnMaxTimeY 947
#define WhiteTurnMaxTimeH 50
#define WhiteTurnMaxTimeW 250
#define WhiteTurnMaxTimeText "步长:"

#define BlackTimeX 1295
#define BlackTimeY 107
#define BlackTimeH 50
#define BlackTimeW 250
#define BlackTimeText "局时:"

#define WhiteTimeX 1295
#define WhiteTimeY 847
#define WhiteTimeH 50
#define WhiteTimeW 250
#define WhiteTimeText "局时:"

//游戏提示
#define LabGameX 250
#define LabGameY 375
#define LabGameH 250
#define LabGameW 500
#define WhiteWinText "  白棋胜利！"
#define BlackWinText "  黑棋胜利！"
#define CheckText "将    军"
#define giveCheckMateText "不能送将"
#define DrawText "平    局"


//棋盘资源
#define ChessBoardPath ":/res/ChessBoard.png"
#define SelectPath ":/res/SelectPiece.png"

//棋子资源
#define BlackKingPath ":/res/BlackKing.png"
#define BlackQueenPath ":/res/BlackQueen.png"
#define BlackRookPath ":/res/BlackRook.png"
#define BlackKnightPath ":/res/BlackKnight.png"
#define BlackBishopPath ":/res/BlackBishop.png"
#define BlackPawnPath ":/res/BlackPawn.png"
#define WhiteKingPath ":/res/WhiteKing.png"
#define WhiteQueenPath ":/res/WhiteQueen.png"
#define WhiteRookPath ":/res/WhiteRook.png"
#define WhiteKnightPath ":/res/WhiteKnight.png"
#define WhiteBishopPath ":/res/WhiteBishop.png"
#define WhitePawnPath ":/res/WhitePawn.png"
#define BlackKingNum 4
#define WhiteKingNum 20
#define BlackLeftRookNum 0
#define BlackRightRookNum 7
#define WhiteLeftRookNum 16
#define WhiteRightRookNum 23

#endif // CONFIG_H
