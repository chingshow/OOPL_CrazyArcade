#include "StdAfx.h"
#include "resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "player.h"
#include <stdlib.h>

namespace game_framework
{
    Player::Player()
    {
       init(0);
    }
    int Player::getX1()
    {
        return x;
    }

    int Player::getY1()
    {
        return y;
    }
    int Player::getX2()
    {
        return x + 70;
    }

    int Player::getY2()
    {
        return y + 70;
    }
    void Player::setXY(int x, int y)
    {
        this -> x = x;
        this -> y = y;
    }

    void Player::setMap(int map[13][15])
	{
		for (int i = 0; i < 13; i++) {
			for (int j = 0; j < 15; j++) {
				map_user[i][j] = map[i][j];
			}
		}
	}

    void Player::setdirection(int mode, bool flag)
    {
        switch(mode)
        {
        case 1:
            isMovingUp = flag;
            break;
        case 2:
            isMovingDown = flag;
            break;
        case 3:
            isMovingLeft = flag;
            break;
        case 4:
            isMovingRight = flag;
            break;
        }
    }

    void Player::setSpeed(int speed)
    {
        this -> speed = speed;
    }
    int Player::getSpeed()
    {
        return speed;
    }


    void Player::setStatus(int status)
    {
        this -> status = status;
    }
    int Player::getStatus()
    {
        return status;
    }
    

    void Player::setId(int id)
    {
        this -> id = id;
    }
    int Player::getId()
    {
        return id;
    }

    void Player::setJump(int jump)
    {
        this -> jump = jump;
    }
    int Player::getJump()
    {
        return jump;
    }
    
    void Player::init(int user_id)
    {   
        setId(user_id);
        int X_POS = 5;
		int Y_POS = 5;
        if (user_id == 2)
		{
			X_POS = 975;
			Y_POS = 835;
		}

        speed = 7;
        status = 5;
        jump = 1;
        x = X_POS;
		y = Y_POS;
        isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
        mode = 2;
    }
    
    void Player::LoadBitmap()
    {
        P1_down.LoadBitmap("Resources/player/bmp/Player1_down.bmp", RGB(255, 255, 255));
        P1_up.LoadBitmap("Resources/player/bmp/Player1_up.bmp", RGB(255, 255, 255));
        P1_left.LoadBitmap("Resources/player/bmp/Player1_left.bmp", RGB(255, 255, 255));
        P1_right.LoadBitmap("Resources/player/bmp/Player1_right.bmp", RGB(255, 255, 255));
        p1die1.LoadBitmap("Resources/player/bmp/Player1_die1.bmp", RGB(255, 255, 255));
        p1die2.LoadBitmap("Resources/player/bmp/Player1_die2.bmp", RGB(255, 255, 255));

        P2_down.LoadBitmap("Resources/player/bmp/Player2_down.bmp", RGB(255, 255, 255));
        P2_up.LoadBitmap("Resources/player/bmp/Player2_up.bmp", RGB(255, 255, 255));
        P2_left.LoadBitmap("Resources/player/bmp/Player2_left.bmp", RGB(255, 255, 255));
        P2_right.LoadBitmap("Resources/player/bmp/Player2_right.bmp", RGB(255, 255, 255));
        p2die1.LoadBitmap("Resources/player/bmp/Player2_die1.bmp", RGB(255, 255, 255));
        p2die2.LoadBitmap("Resources/player/bmp/Player2_die2.bmp", RGB(255, 255, 255));
    }

    void Player::OnMove()
    {
        int x2 = getX2();
		int y2 = getY2();
        int row, col, row_u, row_d, col_l, col_r, placeNow_l, placeNow_r;
        if (isMovingUp) {
            mode = 1;
            if (jump == 1) 
            {
                row = (y - speed) / 70;
                col_l = (x + 5) / 70;
                col_r = (x + 60) / 70;
                placeNow_l = map_user[row][col_l];
                placeNow_r = map_user[row][col_r];
                if (y > 3 && ((placeNow_l == 0 || placeNow_l > 20)&& (placeNow_l !=100))
                    &&  ((placeNow_r == 0 || placeNow_r > 20)&& (placeNow_r !=100))) {
				    y -= speed;
				}
		        else
			    {
                    int temp = speed;
                    while (temp > 0)
                    {
                        temp--;
                        row = (y - speed) / 70;
                        placeNow_l = map_user[row][col_l];
                        placeNow_r = map_user[row][col_r];
                        if (y > 3 && ((placeNow_l == 0 || placeNow_l > 20) && (placeNow_l !=100))
                        &&  ((placeNow_r == 0 || placeNow_r > 20)&& (placeNow_r !=100)))
                        {
                                y--;
                        }
                    }
                }          
            }
            else
            {
                if (y > 3) 
                {
                    y -= speed;
                }
                else
                {
                    int temp = speed;
                    while (temp > 0)
                    {
                        temp--;
                        if (y > 3)
                        {
                            y--;
                        }
                    }
                }
            }
            
        }
        else if (isMovingDown) {
            mode = 2;
            if (jump == 1) 
            {
                row = (y2 + speed) / 70;
                col_l = (x + 5) / 70;
                col_r = (x + 60) / 70;
                placeNow_l = map_user[row][col_l];
                placeNow_r = map_user[row][col_r];
                if (y < 835 && ((placeNow_l == 0 || placeNow_l > 20) && (placeNow_l !=100))
                        &&  ((placeNow_r == 0 || placeNow_r > 20) && (placeNow_r !=100))) {
                    y += speed;
                }
                else
                {
                    int temp = speed;
                    while (temp > 0)
                    {
                        temp--;
                        row = (y2 + temp) / 70;
                        placeNow_l = map_user[row][col_l];
                        placeNow_r = map_user[row][col_r];
                        if (y  < 835 && ((placeNow_l == 0 || placeNow_l > 20) && (placeNow_l !=100))
                        &&  ((placeNow_r == 0 || placeNow_r > 20)&& (placeNow_r !=100)))
                        {
                            y++;
                        }
                    }
                }          
            }
            else
            {
                if (y < 835) {
                    y += speed;
                }
                else
                {
                    int temp = speed;
                    while (temp > 0)
                    {
                        temp--;
                        if (y  < 835)
                        {
                            y++;
                        }
                    }
                }
            }
        }
        else if (isMovingLeft) {
            mode = 3;
            if (jump == 1) 
            {
                col = (x - speed) / 70;
                row_u = (y + 5) / 70;
                row_d = (y + 60) / 70;
                placeNow_l = map_user[row_u][col];
                placeNow_r = map_user[row_d][col];
                if (x > 3 && ((placeNow_l == 0 || placeNow_l > 20) && (placeNow_l !=100))
                        &&  ((placeNow_r == 0 || placeNow_r > 20)&& (placeNow_r !=100))) {
                    x -= speed;
                }
                else
                {
                    int temp = speed;
                    while (temp > 0)
                    {
                        temp--;
                        col = (x - temp) / 70;
                        placeNow_l = map_user[row_u][col];
                        placeNow_r = map_user[row_d][col];
                        if (x > 3 && ((placeNow_l == 0 || placeNow_l > 20) && (placeNow_l !=100))
                        &&  ((placeNow_r == 0 || placeNow_r > 20)&& (placeNow_r !=100)))
                        {
                            x--;
                        }
                    }
                }          
            }
            else
            {
                if (x > 3) {
                    x -= speed;
                }
                else
                {
                    int temp = speed;
                    while (temp > 0)
                    {
                        temp--;
                        if (x > 3)
                        {
                            x--;
                        }
                    }
                }
            }
        }
        else if (isMovingRight) {
            mode = 4;
            if (jump == 1) 
            {
                row_u = (y + 5) / 70;
                row_d = (y + 60) / 70;
                col = (x2 + speed) / 70;
                
                placeNow_l = map_user[row_u][col];
                placeNow_r = map_user[row_d][col];
                if (x < 976 && ((placeNow_l == 0 || placeNow_l > 20) && (placeNow_l !=100))
                        &&  ((placeNow_r == 0 || placeNow_r > 20) && (placeNow_r !=100))) {
                    x += speed;
                }
                else
                {
                    int temp = speed;
                    while (temp > 0)
                    {
                        temp--;
                        col = (x2 + temp) / 70;
                        placeNow_l = map_user[row_u][col];
                        placeNow_r = map_user[row_d][col];
                        if (x < 976 && ((placeNow_l == 0 || placeNow_l > 20) && (placeNow_l !=100))
                        &&  ((placeNow_r == 0 || placeNow_r > 20)&& (placeNow_r !=100)))
                        {
                            x++;
                        }
                    }
                }          
            }
            else
            {
                if (x < 976) {
                    x += speed;
                }
                else
                {
                    int temp = speed;
                    while (temp > 0)
                    {
                        temp--;
                        if (x < 976)
                        {
                            x++;
                        }
                    }
                }
            }
        }
    }

    void Player::OnShow()
    {
        if (status == 5 && id == 1)
		{
            if (mode == 1) 
            {
                P1_up.SetTopLeft(x, y);
                P1_up.ShowBitmap();
            }
            if (mode == 2) 
            {
                P1_down.SetTopLeft(x, y);
                P1_down.ShowBitmap();
            }
            if (mode == 3) 
            {
                P1_left.SetTopLeft(x, y);
                P1_left.ShowBitmap();
            }
            if (mode == 4) 
            {
                P1_right.SetTopLeft(x, y);
                P1_right.ShowBitmap();
            }
		}
        else if(status != 5 && id == 1)
        {
            if (status == 4)
            {
                p1die1.SetTopLeft(x, y);
                p1die1.ShowBitmap();
            }
            else if (status == 3)
            {
                p1die2.SetTopLeft(x, y);
                p1die2.ShowBitmap();
            }
            else if (status == 2)
            {
                p1die1.SetTopLeft(x, y);
                p1die1.ShowBitmap();
            }
            else if (status == 1)
            {
                p1die2.SetTopLeft(x, y);
                p1die2.ShowBitmap();
            }
        }
        if (status == 5 && id == 2)
		{   
            if (mode == 1) 
            {
                P2_up.SetTopLeft(x, y);
                P2_up.ShowBitmap();
            }
            if (mode == 2) 
            {
                P2_down.SetTopLeft(x, y);
                P2_down.ShowBitmap();
            }
            if (mode == 3) 
            {
                P2_left.SetTopLeft(x, y);
                P2_left.ShowBitmap();
            }
            if (mode == 4) 
            {
                P2_right.SetTopLeft(x, y);
                P2_right.ShowBitmap();
            }
			
		}
        else if(status != 5 && id == 2)
        {
            if (status == 4)
            {
                p2die1.SetTopLeft(x, y);
                p2die1.ShowBitmap();
            }
            else if (status == 3)
            {
                p2die2.SetTopLeft(x, y);
                p2die2.ShowBitmap();
            }
            else if (status == 2)
            {
                p2die1.SetTopLeft(x, y);
                p2die1.ShowBitmap();
            }
            else if (status == 1)
            {
                p2die2.SetTopLeft(x, y);
                p2die2.ShowBitmap();
            }
        }
    }
    Player::~Player(){}
}
