#pragma once

typedef enum
{
    STATUS_OK = 0,
    STATUS_ERR
}RET_STATUS;


typedef enum
{
    BOARD_IN = 0,
    BOARD_END
}BOARD_STATUS;

typedef enum
{
    VIRGIN = 0,
    REPEAT
}REPEATER;

typedef enum
{
    LOSS = 0,
    WON,
    PLAY,
//    REPEAT,
    INVALID
}GAMESTATUS;

/*
typedef enum
{
    LOSS = 0,
    WON,
    PLAY
}GAMESTATUS;
*/

typedef enum
{
    DEAD = 0,
    ALIVE,
}MOVE_STATUS;


RET_STATUS checker(int cVal, int b_Size);

RET_STATUS ghostChecker(int x, int y);

void ghostDead(int boardSz);

void ghostMoves(int xIndex, int yIndex, int bSize);

RET_STATUS blCode(int x, int y, int boardSize);        //checking from current position to ghost moves;

void recoder(int data);

RET_STATUS repeaterChecker(int uip, int bo_size);

void moveDefaulter();

int readRecoder();




