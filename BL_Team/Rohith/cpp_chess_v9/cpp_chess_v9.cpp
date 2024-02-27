//////////// Horse movement //////////////

#include<iostream>
#include<string>
#include<cstring>

#include"cpp_chess_v9.hpp"

using namespace std;

const int boardSize = 3;                    //board size

static int xIndex = 0, yIndex = 0;          // current state;

static int ghostPositions[8];               //future possible

static int preIndex=0;

int board[boardSize][boardSize] = {0};

int moveRecord[boardSize*boardSize];

int rIndex = 0;

void display()
{
    for(int i = 0;i<boardSize;i++)
    {
        for (int j = 0; j < boardSize; j++)
        {
            cout << board[i][j];
        }
        cout << endl;
    }
}

GAMESTATUS stopper()
{
    int stopperID = 8;
    for (int l = 0; l < 8; l++)
    {
        for (int m = 0; m < boardSize*boardSize; m++)
        {
            if(ghostPositions[l]==moveRecord[m] || ghostPositions[l] == -9 || ghostPositions[l] < 0)
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
    
    if(stopperID > 0)
        return PLAY;
    else
        return LOSS;
}

class prediction
{
    private:
        int t1 = 0, t2 = 0, t3 = 0, t4 = 0,   t5 = 0, t6 = 0, t7 = 0, t8 = 0;

    public:
        void ghostDead()
        {
            if((ghostPositions[0]/10 < 0 || ghostPositions[0]/10 > boardSize-1) ||
                (ghostPositions[0]%10 < 0 || ghostPositions[0]%10 > boardSize-1))
            {
                ghostPositions[0] = -9;
            }
            if((ghostPositions[1]/10 < 0 || ghostPositions[1]/10 > boardSize-1) ||
                (ghostPositions[1]%10 < 0 || ghostPositions[1]%10 > boardSize-1))
            {
                ghostPositions[1] = -9;
            }
            if((ghostPositions[2]/10 < 0 || ghostPositions[2]/10 > boardSize-1) ||
                (ghostPositions[2]%10 < 0 || ghostPositions[2]%10 > boardSize-1))
            {
                ghostPositions[2] = -9;
            }
            if((ghostPositions[3]/10 < 0 || ghostPositions[3]/10 > boardSize-1) ||
                (ghostPositions[3]%10 < 0 || ghostPositions[3]%10 > boardSize-1))
            {
                ghostPositions[3] = -9;
            }

            if((ghostPositions[4]/10 < 0 || ghostPositions[4]/10 > boardSize-1) ||
                (ghostPositions[4]%10 < 0 || ghostPositions[4]%10 > boardSize-1))
            {
                ghostPositions[4] = -9;
            }
            if((ghostPositions[5]/10 < 0 || ghostPositions[5]/10 > boardSize-1) ||
                (ghostPositions[5]%10 < 0 || ghostPositions[5]%10 > boardSize-1))
            {
                ghostPositions[5] = -9;
            }
            if((ghostPositions[6]/10 < 0 || ghostPositions[6]/10 > boardSize-1) ||
                (ghostPositions[6]%10 < 0 || ghostPositions[6]%10 > boardSize-1))
            {
                ghostPositions[6] = -9;
            }
            if((ghostPositions[7]/10 < 0 || ghostPositions[7]/10 > boardSize-1) ||
                (ghostPositions[7]%10 < 0 || ghostPositions[7]%10 > boardSize-1))
            {
                ghostPositions[7] = -9;
            }
        }

        void ghostMoves()
        {
            t1 = xIndex - 1;
            t2 = yIndex - 1;

            t3 = xIndex - 1;
            t4 = yIndex + 1;

            t5 = xIndex + 1;
            t6 = yIndex - 1;

            t7 = xIndex + 1;
            t8 = yIndex + 1;


            ghostPositions[0] = (((t1-1)*10)+t2);
            ghostPositions[1] = ((t1*10)+(t2-1));

            ghostPositions[2] = (((t3-1)*10)+t4);
            ghostPositions[3] = ((t3*10)+(t4+1));

            ghostPositions[4] = (((t5)*10)+(t6-1));
            ghostPositions[5] = (((t5+1)*10)+(t6));

            ghostPositions[6] = (((t7)*10)+(t8+1));
            ghostPositions[7] = (((t7+1)*10)+(t8));

            ghostDead();            
        }

        RET_STATUS ghostChecker(int uip)
        {
            if((ghostPositions[0] == uip) || (ghostPositions[1] == uip) || (ghostPositions[2] == uip) || (ghostPositions[3] == uip) 
            || (ghostPositions[4] == uip) || (ghostPositions[5] == uip) || (ghostPositions[6] == uip) || (ghostPositions[7] == uip))
            {
                return STATUS_OK;
            }
            else
                return STATUS_ERR;
        }
};

class positions
{
    public:
        GAMESTATUS setIndexData(int iVal, prediction Tobj)
        {
            if(STATUS_OK == Tobj.ghostChecker(iVal))
            {
                if(boardSize*boardSize >= rIndex)
                {
                    xIndex = (iVal/10);
                    yIndex = (iVal%10);
                    moveRecord[rIndex] = (xIndex*10)+yIndex;
                    rIndex++;   
                    board[xIndex][yIndex]=1;
                    board[preIndex/10][preIndex%10]=0;
                    display();
                    preIndex=((xIndex*10)+yIndex);
                    Tobj.ghostMoves();
                    return PLAY;
                }
                else
                    return WON;
            }
            else
            {
                display();
                cout << "End of board\n";
                Tobj.ghostMoves();
                return PLAY;
            }

            return PLAY;
        }

        void defaultIndex()
        {
            xIndex=yIndex=(boardSize-1);

            xIndex = boardSize-1;
            yIndex = 0;
            moveRecord[rIndex] = (xIndex*10)+yIndex;
            rIndex++;
            board[xIndex][yIndex]=1;
            board[preIndex/10][preIndex%10]=0;
            preIndex=((xIndex*10)+yIndex);
            display();
        }
};

RET_STATUS checker(int cVal)
{
    if(boardSize > cVal/10 && boardSize > cVal%10)
        return STATUS_OK;
    else
        return STATUS_ERR;
}

RET_STATUS repeaterChecker(int uip)
{
    for (int k = 0; k < (boardSize*boardSize); k++)
    {
        if(uip == moveRecord[k])
            return STATUS_ERR;
        else
            {//Do Nothing;
            }
    }
    return STATUS_OK;
}

void moveDefaulter()
{
    for(int i = 0; i<(boardSize *boardSize);i++) 
    {
        moveRecord[i]=-9;
    }
}



int readUVal()
{
    int getUserIP = 0;
    cout << "Enter index\n";
    cin >> getUserIP;
    return getUserIP;
}

GAMESTATUS runApp(int Uip, positions Iobj1, prediction Gobj2)
{
        GAMESTATUS endStatus = PLAY;

    if(STATUS_OK == checker(Uip) && STATUS_OK == repeaterChecker(Uip) && STATUS_OK == Gobj2.ghostChecker(Uip))
        {
            if(Uip == (xIndex*10 + yIndex))              //for repeating entry after another;
                display();
            else if(STATUS_OK == checker(Uip))           //checks if user input is with board limit or not;
                endStatus = Iobj1.setIndexData(Uip, Gobj2);
            else
                cout << "Invalid index\n";

            if(LOSS == stopper())       //before this need to use ghostdead;
            {
                cout << "Lost!";
                return WON;
            }
            else if(WON == stopper())
            {
                cout << "Won!";
                return LOSS;
            }
            else
            {  //do nothing;
            }
        }
        else if(STATUS_ERR == repeaterChecker(Uip))      //checks if user input is valid or not!;
            cout << "Repeatation NOT ALLOWED"<<endl;
        else
            cout << "Invalid Move!!!!\n";

    return PLAY;
}

int main()
{
    int UserIP = 0;
    GAMESTATUS status = PLAY;

    positions obj1;
    prediction obj2;        //ghostChecker();
    
    moveDefaulter();
    obj1.defaultIndex();
    obj2.ghostMoves();

    while (1)
    {
        UserIP = readUVal();
        status = runApp(UserIP, obj1, obj2);
        if(status == LOSS || status == WON)
            break;
        else
        {//do nothing
        }
    }
    return 0;
}