#include <iostream>
#include "BL.h"

using namespace std;

static int ghostPositions[8] = { 0 };

static int moveRecord[8 * 8];

static int rIndex = 0;

prediction obj1;        //ghostChecker();
prediction obj2;        //

recoderClass obj3;

checkerClass obj4;
checkerClass obj5;

/*void BL_App(int gY, int gX, int bSize, prediction b1, prediction b2, recoderClass b3, checkerClass b4, checkerClass b5);
{
    if (obj1.ghostChecker(gY, gridX) == STATUS_OK && obj4.repeaterChecker((gridY * 10) + gridX, BOARD_SIZE, obj5) == STATUS_OK)
    {
        obj1.ghostMoves(gY, gridX, BOARD_SIZE, obj2, obj3);
        sprite.setPosition(gY * SQUARE_SIZE, gridY * SQUARE_SIZE);
    }
    else
    {
        cout << "Invalid Move\n";
    }
    cout << "X: " << gridX << " Y:" << gridY << "\n";
}*/

GAMESTATUS checkerClass :: stopper(int b_si)
{
    int stopperID = 8;
    for (int l = 0; l < 8; l++)
    {
        for (int m = 0; m < b_si * b_si; m++)
        {
            if (ghostPositions[l] == moveRecord[m] || ghostPositions[l] == -9 || ghostPositions[l] < 0)
            {
                stopperID--;
                break;
            }
            else
            {
                //do nothing;
            }
        }
    }

    if (stopperID > 0)
        return PLAY;
    else if (rIndex >= (b_si * b_si))
        return WON;
    else
        return LOSS;
}


void moveDefaulter()
{
    for (int i = 0; i < (8*8); i++)
    {
        moveRecord[i] = -9;
    }
}


void recoderClass :: recoder(int data)
{
    cout << "data = " << data << endl;
    moveRecord[rIndex] = data;
    cout << "moveRecord[rIndex] = " << moveRecord[rIndex] << endl;
    rIndex++;
    cout << "rIndex = " << rIndex << endl;
}

int recoderClass :: readRecoder()
{
    return moveRecord[rIndex - 1];
}

RET_STATUS checkerClass :: repeaterChecker(int uip,int bo_size, checkerClass ob)
{
    //GAMESTATUS winStatus = ob.stopper(bo_size);
    
    //if (winStatus == PLAY)
    {
        for (int k = 0; k < (bo_size * bo_size); k++)
        {
            if (uip == moveRecord[k])
                return STATUS_ERR;
            else
            {//Do Nothing;
            }
        }
        return STATUS_OK;

    }
    /*else if (winStatus == LOSS)
    {
        cout << "YOU LOST!!!\n";

    }
    else
        cout << "You won\n";*/
}

/*
RET_STATUS checker(int cVal, int b_Size)
{
    if (b_Size > cVal / 10 && b_Size > cVal % 10)
    {
        //cout << "size ok" << endl;
        return STATUS_OK;
    }
    else
    {
        //cout << "size ok" << endl;
        return STATUS_ERR;
    }
}
*/


RET_STATUS prediction ::  ghostChecker(int x, int y) //check it
{
    int uip = (x * 10) + y;
    cout << "uip = " << uip << endl;

    /*
        cout << ghostPositions[0] << endl;
        cout << ghostPositions[1] << endl;
        cout << ghostPositions[2] << endl;
        cout << ghostPositions[3] << endl;
        cout << ghostPositions[4] << endl;
        cout << ghostPositions[5] << endl;
        cout << ghostPositions[6] << endl;
        cout << ghostPositions[7] << endl;
    */

    if ((ghostPositions[0] == uip) || (ghostPositions[1] == uip) || (ghostPositions[2] == uip) || (ghostPositions[3] == uip)
        || (ghostPositions[4] == uip) || (ghostPositions[5] == uip) || (ghostPositions[6] == uip) || (ghostPositions[7] == uip))
    {
        cout << "c ok" << endl;
        return STATUS_OK;
    }
    else
    {
        cout << "c err" << endl;
        return STATUS_ERR;
    }
}


void prediction :: ghostDead(int boardSz)
{
    if ((ghostPositions[0] / 10 < 0 || ghostPositions[0] / 10 > boardSz - 1) ||
        (ghostPositions[0] % 10 < 0 || ghostPositions[0] % 10 > boardSz - 1))
    {
        ghostPositions[0] = -9;
    }
    if ((ghostPositions[1] / 10 < 0 || ghostPositions[1] / 10 > boardSz - 1) ||
        (ghostPositions[1] % 10 < 0 || ghostPositions[1] % 10 > boardSz - 1))
    {
        ghostPositions[1] = -9;
    }
    if ((ghostPositions[2] / 10 < 0 || ghostPositions[2] / 10 > boardSz - 1) ||
        (ghostPositions[2] % 10 < 0 || ghostPositions[2] % 10 > boardSz - 1))
    {
        ghostPositions[2] = -9;
    }
    if ((ghostPositions[3] / 10 < 0 || ghostPositions[3] / 10 > boardSz - 1) ||
        (ghostPositions[3] % 10 < 0 || ghostPositions[3] % 10 > boardSz - 1))
    {
        ghostPositions[3] = -9;
    }

    if ((ghostPositions[4] / 10 < 0 || ghostPositions[4] / 10 > boardSz - 1) ||
        (ghostPositions[4] % 10 < 0 || ghostPositions[4] % 10 > boardSz - 1))
    {
        ghostPositions[4] = -9;
    }
    if ((ghostPositions[5] / 10 < 0 || ghostPositions[5] / 10 > boardSz - 1) ||
        (ghostPositions[5] % 10 < 0 || ghostPositions[5] % 10 > boardSz - 1))
    {
        ghostPositions[5] = -9;
    }
    if ((ghostPositions[6] / 10 < 0 || ghostPositions[6] / 10 > boardSz - 1) ||
        (ghostPositions[6] % 10 < 0 || ghostPositions[6] % 10 > boardSz - 1))
    {
        ghostPositions[6] = -9;
    }
    if ((ghostPositions[7] / 10 < 0 || ghostPositions[7] / 10 > boardSz - 1) ||
        (ghostPositions[7] % 10 < 0 || ghostPositions[7] % 10 > boardSz - 1))
    {
        ghostPositions[7] = -9;
    }
}

void prediction :: ghostMoves(int xIndex, int yIndex, int bSize, prediction objGm, recoderClass objR)
{
    int t1 = 0, t2 = 0, t3 = 0, t4 = 0, t5 = 0, t6 = 0, t7 = 0, t8 = 0;
    t1 = xIndex - 1;
    t2 = yIndex - 1;

    t3 = xIndex - 1;
    t4 = yIndex + 1;

    t5 = xIndex + 1;
    t6 = yIndex - 1;

    t7 = xIndex + 1;
    t8 = yIndex + 1;


    ghostPositions[0] = (((t1 - 1) * 10) + t2);
    ghostPositions[1] = ((t1 * 10) + (t2 - 1));

    ghostPositions[2] = (((t3 - 1) * 10) + t4);
    ghostPositions[3] = ((t3 * 10) + (t4 + 1));

    ghostPositions[4] = (((t5) * 10) + (t6 - 1));
    ghostPositions[5] = (((t5 + 1) * 10) + (t6));

    ghostPositions[6] = (((t7) * 10) + (t8 + 1));
    ghostPositions[7] = (((t7 + 1) * 10) + (t8));

    objGm.ghostDead(bSize);
    objR.recoder((xIndex * 10) + yIndex);
    /*
    cout << ghostPositions[0] << endl;
    cout << ghostPositions[1] << endl;
    cout << ghostPositions[2] << endl;
    cout << ghostPositions[3] << endl;
    cout << ghostPositions[4] << endl;
    cout << ghostPositions[5] << endl;
    cout << ghostPositions[6] << endl;
    cout << ghostPositions[7] << endl;
    */
}


int* getter()
{
    return ghostPositions;
}

