#pragma once

typedef enum
{
    STATUS_OK = 0,
    STATUS_ERR
}RET_STATUS;


typedef enum
{
    LOSS = 0,
    WON,
    PLAY,
    INVALID
}GAMESTATUS;


void moveDefaulter();

int* getter();


class checkerClass
{
public:
    RET_STATUS repeaterChecker(int uip, int bo_size, checkerClass ob);

    GAMESTATUS stopper(int b_si);
};

class recoderClass
{
public:
    void recoder(int data);

    int readRecoder();
};

class prediction
{
public:
    RET_STATUS ghostChecker(int x, int y); //check it

    void ghostDead(int boardSz);

    void ghostMoves(int xIndex, int yIndex, int bSize, prediction objGm, recoderClass objR);
};