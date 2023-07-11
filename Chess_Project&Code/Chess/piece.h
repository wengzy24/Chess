#ifndef PIECE_H
#define PIECE_H

#include <QPainter>
#include <QPixmap>

class Piece
{
public:
    Piece();

    enum TYPE{KING,QUEEN,BISHOP,KNIGHT,ROOK,PAWN};

    int row;
    int col;
    int Xcor;
    int Ycor;
    bool dead;
    bool color;
    int moves;
    int lastmove;
    int lastrow;
    int lastcol;
    TYPE lasttype;
    int last_lastmove;
    TYPE type;
    QPixmap Pix;

    void piecePosition();
    void piecePix();


};

#endif // PIECE_H
