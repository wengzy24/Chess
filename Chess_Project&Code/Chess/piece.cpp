#include "piece.h"
#include "config.h"


Piece::Piece()
{

}

void Piece::piecePosition()
{
    Xcor = GameWidth / 8 * (col - 1);
    Ycor = GameHeight / 8 *(row - 1);
}

void Piece::piecePix()
{
    if(type == Piece::KING && color == 0 )
        Pix.load(BlackKingPath);
    if(type == Piece::QUEEN && color == 0 )
        Pix.load(BlackQueenPath);
    if(type == Piece::ROOK && color == 0 )
        Pix.load(BlackRookPath);
    if(type == Piece::KNIGHT && color == 0 )
        Pix.load(BlackKnightPath);
    if(type == Piece::BISHOP && color == 0 )
        Pix.load(BlackBishopPath);
    if(type == Piece::PAWN && color == 0 )
        Pix.load(BlackPawnPath);
    if(type == Piece::KING && color == 1 )
        Pix.load(WhiteKingPath);
    if(type == Piece::QUEEN && color == 1 )
        Pix.load(WhiteQueenPath);
    if(type == Piece::ROOK && color == 1 )
        Pix.load(WhiteRookPath);
    if(type == Piece::KNIGHT && color == 1 )
        Pix.load(WhiteKnightPath);
    if(type == Piece::BISHOP && color == 1 )
        Pix.load(WhiteBishopPath);
    if(type == Piece::PAWN && color == 1 )
        Pix.load(WhitePawnPath);
}




