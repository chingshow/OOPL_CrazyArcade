#include "StdAfx.h"
#include "resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "CGameMap.h"

#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>
int map_init[13][15], map1_init[13][15], map2_init[13][15], map3_init[13][15], map4_init[13][15], map5_init[13][15],
map_bomb[13][15], map_id[13][15], map_explosion[13][15];
namespace game_framework
{
	
	void map_read()
	{
		ifstream map1, map2, map3, map4, map5;
		map1.open("Resources/map_txt/map1.txt");
		map2.open("Resources/map_txt/map2.txt");
		map3.open("Resources/map_txt/map3.txt");
		map4.open("Resources/map_txt/map4.txt");
		map5.open("Resources/map_txt/map5.txt");
		int value1, value2, value3, value4, value5 = 0;
		for(int i = 0; i < 13; i++){
			for(int j = 0; j < 15; j++){
				map_init[i][j] = 0;
				map_bomb[i][j] = 0;
				map_id[i][j] = 0;
				map_explosion[i][j] = 0;
				map1 >> value1;
				map1_init[i][j] = value1;
				map2 >> value2;
				map2_init[i][j] = value2;
				map3 >> value3;
				map3_init[i][j] = value3;
				map4 >> value4;
				map4_init[i][j] = value4;
				map5 >> value5;
				map5_init[i][j] = value5;
			}
		}
		map1.close();map2.close();map3.close();map4.close();map5.close();
	}
    CGameMap::CGameMap()
    :X(0), Y(0), MapWidth(70), MapHeight(70)
    {
		srand((unsigned)time(NULL));
		map_read();
        for (int i = 0; i < 13; i++) {
            for (int j = 0; j < 15; j++) {
                map[i][j] = map_init[i][j];
                mapCopy[i][j] = map_init[i][j];
				bombMap[i][j] = map_bomb[i][j];
				idMap[i][j] = map_id[i][j];
				exp_Map[i][j] = map_explosion[i][j];
            }
        }

        timer = 6, timerS = 30 ,timerb = 50;
		p1_Distance = 1, p1_Quantity = 1, p1_Speed = 7, p1_Status = 5, p1_Life = 1, p1_Hit = false, p1_Jump = 1;
		p2_Distance = 1, p2_Quantity = 1, p2_Speed = 7, p2_Status = 5, p2_Life = 1, p2_Hit = false, p2_Jump = 1;
        X1_1 = 0, Y1_1 = 0;
		X1_2 = 0, Y1_2 = 0;
		audio[0] = 0, audio[1] = 0, audio[2] = 0, audio[3] = 0;
    }

	int (*CGameMap::getMap())[15]
	{
		return map;
	}

    void CGameMap::OnKeyDown(UINT nChar, int Xtest, int Ytest, int id)
	{
		const char KEY_SPACE = 0x20;
		const char KEY_V = 0x56;
        const char KEY_ENTER = 0x0D;
		const char KEY_M = 0x4D;

		const char KEY_R = 0x52;
		const char KEY_T = 0x54;		
		const char KEY_Y = 0x59;
		const char KEY_U = 0x55;		
		const char KEY_I = 0x49;
		
		if (nChar == KEY_ENTER)
		{
			if (map[Ytest][Xtest] == 0 && bombMap[Ytest][Xtest] == 0 && p2_Quantity > 0 && id == 2 && p2_Status == 5)
			{
				p2_Quantity -= 1;
				bombMap[Ytest][Xtest] = 11;
				idMap[Ytest][Xtest] = 2;
				audio[0] = 1;
				mapCopy[Ytest][Xtest] = 100;
			}
		}
		if (nChar == KEY_SPACE)
		{
			if (map[Ytest][Xtest] == 0 && bombMap[Ytest][Xtest] == 0 && p1_Quantity > 0 && id == 1 && p1_Status == 5)
			{
				p1_Quantity -= 1;
				bombMap[Ytest][Xtest] = 11;
				idMap[Ytest][Xtest] = 1;
				audio[0] = 1;
				mapCopy[Ytest][Xtest] = 100;
			}
		}
		if (nChar == KEY_V && id == 1)
		{
			if (map[Ytest - 1][Xtest] == 0 && Ytest > 0) {
				bombMap[Ytest - 1][Xtest] = 11;
				mapCopy[Ytest - 1][Xtest] = 100;
			}
			if (map[Ytest + 1][Xtest] == 0 && Ytest < 12) {
				bombMap[Ytest + 1][Xtest] = 11;
				mapCopy[Ytest + 1][Xtest] = 100;
			}
			if (map[Ytest][Xtest - 1] == 0 && Xtest > 0) {
				bombMap[Ytest][Xtest - 1] = 11;
				mapCopy[Ytest][Xtest - 1] = 100;
			}
			if (map[Ytest][Xtest + 1] == 0 && Xtest < 14) {
				bombMap[Ytest][Xtest + 1] = 11;
				mapCopy[Ytest][Xtest + 1] = 100;
			}
			audio[0] = 1;
			p2_Jump = 1;
		}
		if (nChar == KEY_M && id == 2)
		{
			if (map[Ytest - 1][Xtest] == 0 && Ytest > 0) {
				bombMap[Ytest - 1][Xtest] = 11;
				mapCopy[Ytest - 1][Xtest] = 100;
			}
			if (map[Ytest + 1][Xtest] == 0 && Ytest < 12) {
				bombMap[Ytest + 1][Xtest] = 11;
				mapCopy[Ytest + 1][Xtest] = 100;
			}
			if (map[Ytest][Xtest - 1] == 0 && Xtest > 0) {
				bombMap[Ytest][Xtest - 1] = 11;
				mapCopy[Ytest][Xtest - 1] = 100;
			}
			if (map[Ytest][Xtest + 1] == 0 && Xtest < 14) {
				bombMap[Ytest][Xtest + 1] = 11;
				mapCopy[Ytest][Xtest + 1] = 100;
			}
			audio[0] = 1;
			p1_Jump = 1;
		}
		//-------------------------------------------------------//
		if (nChar == KEY_R)
		{
			// quantity
			if(p1_Quantity < 5)
			{
				p1_Quantity ++;
			}
			if(p2_Quantity < 5)
			{
				p2_Quantity ++;
			}
		}
		if(nChar == KEY_T)
		{
			// distance
			if(p1_Distance < 5)
			{
				p1_Distance++;
			}
			if(p2_Distance < 5)
			{
				p2_Distance++;
			}
		}
		if(nChar == KEY_Y)
		{
			// speed
			if(p1_Speed < 15)
			{
				p1_Speed++;
			}
			if(p2_Speed < 15)
			{
				p2_Speed++;
			}
		}
		if(nChar == KEY_U)
		{
			// jump
			if(p1_Jump == 1)
			{
				p1_Jump = 2;
			}
			else
			{
				p1_Jump = 1;
			}
			
			if(p2_Jump == 1)
			{
				p2_Jump = 2;
			}
			else
			{
				p2_Jump = 1;
			}
		}
		if(nChar == KEY_I)
		{
			// life
			p1_Life = 2;
			p2_Life = 2;
		}
		
	}
    void CGameMap::setBombInfo()
	{
		if (timer % 7 == 0)
		{
			for (int i = 0; i < 13; i++)
				for (int j = 0; j < 15; j++)
				{
					if (bombMap[i][j] > 2)
					{
						bombMap[i][j]--;
					}
					else if (bombMap[i][j] == 2)
					{
						bombMap[i][j]--;
						audio[1] = 1;
						
					}
					else if (bombMap[i][j] == 1)
					{
						bombMap[i][j]--;
						mapCopy[i][j] = 0;
						if (idMap[i][j] == 1)
							p1_Quantity += 1;
						if (idMap[i][j] == 2)
							p2_Quantity += 1;
					}
				}
		}
	}

    void CGameMap::set_expMap()
	{
		int k = 0;
        //down
		for (int i = 0; i < 13; i++)
		{
			for (int j = 0; j < 15; j++)
			{
				if (bombMap[i][j] == 1 && timer % 7 == 6)
				{
					int temp = 0;
					if (idMap[i][j] == 1)
					{
						temp = p1_Distance;
					}
					else
					{
						temp = p2_Distance;
					}
					for (k = 1; k <= temp; k++)
					{
						if (i + k < 13) {
							if (map[i + k][j] == 0)
							{
								if (k != temp) 
								{
									exp_Map[i + k][j] = 3;
								}
								else
								{
									exp_Map[i + k][j] = 4;
									break;
								}
							}
							else
							{
								exp_Map[i + k - 1][j] = 4;
								break;
							}
						}
						else
						{
							break;
						}
					}
					for (k = 0; k <= temp; k++)
					{
						if (exp_Map[i + k][j] == 4 && (i + k + 1) < 13 && k != temp)
						{
							int random_num = (rand() % 15);
								if (isBreakable(map[i + k + 1][j]))
								{
									if (random_num <= 6 || map[i - k - 1][j] >= 101)
										mapCopy[i + k + 1][j] = 0;
									else if (random_num == 7 || random_num == 8)
										mapCopy[i + k + 1][j] = 101;
									else if (random_num == 9 || random_num == 10)
										mapCopy[i + k + 1][j] = 102;
									else if (random_num == 11 || random_num == 12)
										mapCopy[i + k + 1][j] = 103;
									else if (random_num == 13)
										mapCopy[i + k + 1][j] = 104;
									else if (random_num == 14)
										mapCopy[i + k + 1][j] = 105;
							}
							break;
						}
					}
					//up
					for (k = 1; k <= temp; k++)
					{
						if (i - k >= 0) {
							if (map[i - k][j] == 0)
							{
								if (k != temp)
								{
									exp_Map[i - k][j] = 1;
								}
								else
								{
									exp_Map[i - k][j] = 2;
									break;
								}
							}
							else
							{
								exp_Map[i - k + 1][j] = 2;
								break;
							}
						}
						else
						{
							break;
						}
					}
					for (k = 0; k <= temp; k++)
					{
						if (exp_Map[i - k][j] == 2 && (i - k - 1) >= 0 && k != temp)
						{
							int random_num = (rand() % 15);
							if (isBreakable(map[i - k - 1][j]))
							{
								if (random_num <= 6 || map[i - k - 1][j] >= 101)
									mapCopy[i - k - 1][j] = 0;
								else if (random_num == 7 || random_num == 8)
									mapCopy[i - k - 1][j] = 101;
								else if (random_num == 9 || random_num == 10)
									mapCopy[i - k - 1][j] = 102;
								else if (random_num == 11 || random_num == 12)
									mapCopy[i - k - 1][j] = 103;
                                else if (random_num == 13)
									mapCopy[i - k - 1][j] = 104;
								else if (random_num == 14)
									mapCopy[i - k - 1][j] = 105;
							}
						}
					}
					//right
					for (k = 1; k <= temp; k++)
					{
						if (j + k < 15)
						{
							if (map[i][j + k] == 0)
							{
								if (k != temp)
								{
									exp_Map[i][j + k] = 7;
								}
								else
								{
									exp_Map[i][j + k] = 8;
									break;
								}
							}
							else
							{
								exp_Map[i][j + k - 1] = 8;
								break;
							}
						}
						else
						{
							break;
						}
					}
					for (k = 0; k <= temp; k++)
					{
						if (exp_Map[i][j + k] == 8 && (j + k) < 15 && k != temp)
						{
							int random_num = (rand() % 15);
							if (isBreakable(map[i][j + k + 1]))
							{
								if (random_num <= 6 || map[i][j + k + 1] >= 101)
									mapCopy[i][j + k + 1] = 0;
								else if (random_num == 7 || random_num == 8)
									mapCopy[i][j + k + 1]= 101;
								else if (random_num == 9 || random_num == 10)
									mapCopy[i][j + k + 1] = 102;
								else if (random_num == 11 || random_num == 12)
									mapCopy[i][j + k + 1]= 103;
                                else if (random_num == 13)
									mapCopy[i][j + k + 1] = 104;
								else if (random_num == 14)
									mapCopy[i][j + k + 1] = 105;
							}
						}
					}
					//left
					for (k = 1; k <= temp; k++)
					{
						if (j - k >= 0)
						{
							if (map[i][j - k] == 0)
							{
								if (k != temp)
								{
									exp_Map[i][j - k] = 5;
								}
								else
								{
									exp_Map[i][j - k] = 6;
									break;
								}
							}
							else
							{
								exp_Map[i][j - k + 1] = 6;
								break;
							}
						}
						else
						{
							break;
						}
					}
					for (k = 0; k <= temp; k++)
					{

						if (exp_Map[i][j - k] == 6 && (j - k) >= 0 && k != temp)
						{
							int random_num = (rand() % 15);
							if (isBreakable(map[i][j - k - 1]))
							{
								if (random_num <= 6 || map[i][j - k - 1] >= 101 )
									mapCopy[i][j - k - 1] = 0;
								else if (random_num == 7 || random_num == 8)
									mapCopy[i][j - k - 1] = 101;
								else if (random_num == 9 || random_num == 10)
									mapCopy[i][j - k - 1] = 102;
								else if (random_num == 11 || random_num == 12)
									mapCopy[i][j - k - 1] = 103;
                                else if (random_num == 13)
									mapCopy[i][j - k - 1] = 104;
								else if (random_num == 14)
									mapCopy[i][j - k - 1] = 105;
							}
						}
					}
				}
			}
		}
	}


    void CGameMap::setLinkBomb()
	{
		for (int i = 0; i < 13; i++)
			for (int j = 0; j < 15; j++)
			{
				int id = idMap[i][j];
				if (bombMap[i][j] > 0 && id == 1)
				{
					for (int k = 1; k <= p1_Distance; k++)
					{
						if (map[i + k][j] == 0)
						{
							if (bombMap[i + k][j] > bombMap[i][j] && idMap[i + k][j] == 1)
							{
								bombMap[i + k][j] = bombMap[i][j];
							}
						}
						else
						{
							break;
						}
					}

					for (int k = 1; k <= p1_Distance; k++)
					{
						if (map[i - k][j] == 0)
						{
							if (bombMap[i - k][j] > bombMap[i][j] && idMap[i - k][j] == 1)
							{
								bombMap[i - k][j] = bombMap[i][j];
							}
						}
						else
						{
							break;
						}
					}
					for (int k = 1; k <= p1_Distance; k++)
					{
						if (map[i][j + k] == 0)
						{
							if (bombMap[i][j + k] > bombMap[i][j] && idMap[i][j + k] == 1)
							{
								bombMap[i][j + k] = bombMap[i][j];
							}
						}
						else
						{
							break;
						}
					}
					for (int k = 1; k <= p1_Distance; k++)
					{
						if (map[i][j - k] == 0)
						{
							if (bombMap[i][j - k] > bombMap[i][j] && idMap[i][j - k] == 1)
							{
								bombMap[i][j - k] = bombMap[i][j];
							}
						}
						else
						{
							break;
						}
					}
				}

				else if (bombMap[i][j] > 0 && id == 2)
				{
					for (int k = 1; k <= p2_Distance; k++)
					{
						if (bombMap[i + k][j] > bombMap[i][j] && idMap[i + k][j] == 2)
						{
							bombMap[i + k][j] = bombMap[i][j];
						}
					}

					for (int k = 1; k <= p2_Distance; k++)
					{
						if (bombMap[i - k][j] > bombMap[i][j] && idMap[i - k][j] == 2)
						{
							bombMap[i - k][j] = bombMap[i][j];
						}
					}
					for (int k = 1; k <= p2_Distance; k++)
					{
						if (bombMap[i][j + k] > bombMap[i][j] && idMap[i][j + k] == 2)
						{
							bombMap[i][j + k] = bombMap[i][j];
						}
					}
					for (int k = 1; k <= p2_Distance; k++)
					{
						if (bombMap[i][j - k] > bombMap[i][j] && idMap[i][j - k] == 2)
						{
							bombMap[i][j - k] = bombMap[i][j];
						}
					}
				}

			}
	}


    void CGameMap::OnProps(int X1, int Y1, int id)
	{
    	int row = (Y1 + 35) / 70;
    	int col = (X1 + 35) / 70;
    	int position = mapCopy[row][col];
		if (position == 101 && id == 1) {
			mapCopy[row][col] = 0;
			if (p1_Quantity < 5)
				p1_Quantity += 1;
			audio[2] = 1;
		}
		else if (position == 102 && id == 1) {
			mapCopy[row][col] = 0;
			if (p1_Distance < 5)
				p1_Distance += 1;
			audio[2] = 1;
		}
		else if (position == 103 && id == 1) {
			mapCopy[row][col] = 0;
			if (p1_Speed < 15)
				p1_Speed += 1;
			audio[2] = 1;
		}
        else if (position == 104 && id == 1) {
        	mapCopy[row][col] = 0;
			if (p1_Jump == 1)
				p1_Jump = 2;
			audio[2] = 1;
		}
        else if (position == 105 && id == 1) {
    		mapCopy[row][col] = 0;
			if (p1_Life < 2)
				p1_Life += 1;
			audio[2] = 1;
		}
		//-----------------------------------------------------------//
		if (position == 101 && id == 2) {
			mapCopy[row][col] = 0;
			if (p2_Quantity < 5)
				p2_Quantity += 1;
			audio[2] = 1;
		}
		else if (position == 102 && id == 2) {
			mapCopy[row][col] = 0;
			if (p2_Distance < 5)
				p2_Distance += 1;
			audio[2] = 1;
		}
		else if (position == 103 && id == 2) {
			mapCopy[row][col] = 0;
			if (p2_Speed < 15)
				p2_Speed += 1;
			audio[2] = 1;
		}
        else if (position == 104 && id == 2) {
        	mapCopy[row][col] = 0;
			if (p2_Jump == 1)
				p2_Jump = 2;
			audio[2] = 1;
		}
        else if (position == 105 && id == 2) {
    		mapCopy[row][col] = 0;
			if (p2_Life < 2)
				p2_Life += 1;
			audio[2] = 1;
		}
	}
    void CGameMap::setP1Range(int x1, int y1)
	{
		X1_1 = x1, Y1_1 = y1;
	}

	void CGameMap::setP2Range(int x1, int y1)
	{
		X1_2 = x1, Y1_2 = y1;
	}

    void CGameMap::hitWater()
	{
		if ((exp_Map[(Y1_1 + 35) / 70][(X1_1 + 35) / 70] != 0) && (timer%7==6)) {
			if (p1_Life == 1) {
			    p1_Hit = true;
		    }
             else if(p1_Life == 2)
            {
                p1_Hit = false;
                p1_Status = 5;
             	p1_Distance = 1;
             	p1_Quantity = 0;
             	p1_Jump = 1;
             	p1_Speed = 7;
                p1_Life = 1;
            }
		}
        else if ((bombMap[Y1_1 / 70][X1_1/ 70] ==1) && (timer%7==6))
        {
			if (p1_Life == 1) {
			    p1_Hit = true;
		    }
			else if(p1_Life == 2)
            {
                p1_Hit = false;
                p1_Status = 5;
				p1_Distance = 1;
				p1_Quantity = 0;
				p1_Jump = 1;
				p1_Speed = 7;
                p1_Life = 1;
            } 
        }
		if ((exp_Map[(Y1_2 + 35) / 70][(X1_2 + 35) / 70] != 0) && (timer%7==6)) {
			if (p2_Life == 1) {
			    p2_Hit = true;
		    }
             else if(p2_Life == 2)
            {
                p2_Hit = false;
                p2_Status = 5;
             	p2_Distance = 1;
             	p2_Quantity = 0;
             	p2_Jump = 1;
             	p2_Speed = 7;
                p2_Life = 1;
            }
		}
        else if ((bombMap[(Y1_2 + 35) / 70][(X1_2 + 35) / 70] == 1) && (timer%7==6))
        {
			if (p2_Life == 1) {
			    p2_Hit = true;
		    }
             else if(p2_Life == 2)
            {
                p2_Hit = false;
                p2_Status = 5;
             	p2_Distance = 1;
             	p2_Quantity = 0;
             	p2_Jump = 1;
             	p2_Speed = 7;
                p2_Life = 1;
            }
        }
	}
    void CGameMap::getHitP1AndDecrease()
	{
		if (p1_Hit == true)
		{
			if (timerS % 31 == 0)
			{
				p1_Status--;
			}
		}
	}
    void CGameMap::getHitP2AndDecrease()
	{
		if (p2_Hit == true)
		{
			if (timerS % 31 == 0)
			{
				p2_Status--;
			}
		}
	}


    void CGameMap::updateMap()
	{
		if (timer % 7 == 0)
		{
			for (int i = 0; i < 13; i++)
				for (int j = 0; j < 15; j++)
				{
					map[i][j] = mapCopy[i][j];
				}
		}
	}
	//aaaaaaaaaa
	bool CGameMap::isBreakable(int position)
    {
    	switch (mode)
    	{
    	case 1:
    		if(position == 1 || position == 2  || position == 3 || position == 8)
    		{
    			return true;
    		}
    		return false;
    	case 2:
    		if(position == 2 || position == 3 || position == 4)
    		{
    			return true;
    		}
    		return false;
    	case 3:
		case 4:
			if(position == 1 || position == 2 || position == 3)
			{
				return true;
			}
    		return false;
    	case 5:
    		if(position == 4 || position == 5 || position == 6)
    		{
    			return true;
    		}
    		return false;
    	default:
    		return false;
    	}
    }

    
    int CGameMap::getP1Status()
	{
		return p1_Status;
	}
	int CGameMap::getP2Status()
	{
		return p2_Status;
	}

    int CGameMap::getP1Life()
	{
		return p1_Life;
	}
	int CGameMap::getP2Life()
	{
		return p2_Life;
	}
    int CGameMap::getP1Speed()
	{
		return p1_Speed;
	}
	int CGameMap::getP2Speed()
	{
		return p2_Speed;
	}
    int CGameMap::getP1Jump()
	{
		return p1_Jump;
	}
    int CGameMap::getP2Jump()
	{
		return p2_Jump;
	}



    void CGameMap::OnMove()
	{
		timer--;
		timerS--;
        timerb--;


		if (timer == -1)
			timer = 6;
		if (timerS == -1)
			timerS = 30;
        if (timerb == -1)
			timerb = 50;

		setBombInfo();
    	set_expMap();
    	
    	
        setLinkBomb();
		updateMap();
        
		
		hitWater();
		getHitP1AndDecrease();
		getHitP2AndDecrease();


	}

    void CGameMap::setMode(int m)
    {
        mode = m;
    }

    void CGameMap::select_map()
    {   
        timer = 6, timerS = 30,timerb = 50 ;
		p1_Distance = 1, p1_Quantity = 1, p1_Speed = 7, p1_Status = 5, p1_Life = 1, p1_Hit = false, p1_Jump = 1;
		p2_Distance = 1, p2_Quantity = 1, p2_Speed = 7, p2_Status = 5, p2_Life = 1, p2_Hit = false, p2_Jump = 1;
        X1_1 = 0, Y1_1 = 0;
		X1_2 = 0, Y1_2 = 0;
		audio[0] = 0, audio[1] = 0, audio[2] = 0, audio[3] = 0;
        for (int i = 0; i < 13; i++) {
            for (int j = 0; j < 15; j++) {
                switch(mode)
                {
                case 1:
                	map[i][j] = map1_init[i][j];
                	mapCopy[i][j] = map1_init[i][j];
                	bombMap[i][j] = map_bomb[i][j];
                	idMap[i][j] = map_id[i][j];
                	exp_Map[i][j] = map_explosion[i][j];
                	break;
                case 2:
                	map[i][j] = map2_init[i][j];
                	mapCopy[i][j] = map2_init[i][j];
                	bombMap[i][j] = map_bomb[i][j];
                	idMap[i][j] = map_id[i][j];
                	exp_Map[i][j] = map_explosion[i][j];
                	break;
                case 3:
                	map[i][j] = map3_init[i][j];
                	mapCopy[i][j] = map3_init[i][j];
                	bombMap[i][j] = map_bomb[i][j];
                	idMap[i][j] = map_id[i][j];
                	exp_Map[i][j] = map_explosion[i][j];
                	break;
                case 4:
                	map[i][j] = map4_init[i][j];
                	mapCopy[i][j] = map4_init[i][j];
                	bombMap[i][j] = map_bomb[i][j];
                	idMap[i][j] = map_id[i][j];
                	exp_Map[i][j] = map_explosion[i][j];
                	break;
                case 5:
                	map[i][j] = map5_init[i][j];
                	mapCopy[i][j] = map5_init[i][j];
                	bombMap[i][j] = map_bomb[i][j];
                	idMap[i][j] = map_id[i][j];
                	exp_Map[i][j] = map_explosion[i][j];
                	break;
                }
            }
        }
    }
	
    void CGameMap::LoadBitmap()
    {
        //map1
        blocks_r.LoadBitmap("Resources/map1/bmp/blocks_r.bmp", RGB(255, 255, 255));
        blocks_y.LoadBitmap("Resources/map1/bmp/blocks_y.bmp", RGB(255, 255, 255));
        grass.LoadBitmap("Resources/map1/bmp/grass.bmp", RGB(255, 255, 255));
        house_b.LoadBitmap("Resources/map1/bmp/house_b.bmp", RGB(255, 255, 255));
        house_r.LoadBitmap("Resources/map1/bmp/house_r.bmp", RGB(255, 255, 255));
        house_y.LoadBitmap("Resources/map1/bmp/house_y.bmp", RGB(255, 255, 255));
        tree.LoadBitmap("Resources/map1/bmp/tree.bmp", RGB(255, 255, 255));
        wooden_box.LoadBitmap("Resources/map1/bmp/wooden_box.bmp", RGB(255, 255, 255));

        //map2
        cactus.LoadBitmap("Resources/map2/bmp/cactus.bmp", RGB(255, 255, 255));
        earth.LoadBitmap("Resources/map2/bmp/earth.bmp", RGB(255, 255, 255));
        green_box.LoadBitmap("Resources/map2/bmp/green_box.bmp", RGB(255, 255, 255));
        green_box2.LoadBitmap("Resources/map2/bmp/green_box2.bmp", RGB(255, 255, 255));
        rock.LoadBitmap("Resources/map2/bmp/rock.bmp", RGB(255, 255, 255));
        tent_b.LoadBitmap("Resources/map2/bmp/tent_b.bmp", RGB(255, 255, 255));
        tent_r.LoadBitmap("Resources/map2/bmp/tent_r.bmp", RGB(255, 255, 255));
        tent_y.LoadBitmap("Resources/map2/bmp/tent_y.bmp", RGB(255, 255, 255));
        
        //map3
        basket_trans.LoadBitmap("Resources/map3/bmp/basket_trans.bmp", RGB(255, 255, 255));
        flower_trans.LoadBitmap("Resources/map3/bmp/flower_trans.bmp", RGB(255, 255, 255));
        grassBlock_trans.LoadBitmap("Resources/map3/bmp/grassBlock_trans.bmp", RGB(255, 255, 255));
        tree_trans.LoadBitmap("Resources/map3/bmp/tree_trans.bmp", RGB(255, 255, 255));
        pool_LB_trans.LoadBitmap("Resources/map3/bmp/pool_LB_trans.bmp", RGB(255, 255, 255));
        pool_LU_trans.LoadBitmap("Resources/map3/bmp/pool_LU_trans.bmp", RGB(255, 255, 255));
        pool_MB_trans.LoadBitmap("Resources/map3/bmp/pool_MB_trans.bmp", RGB(255, 255, 255));
        pool_MU_trans.LoadBitmap("Resources/map3/bmp/pool_MU_trans.bmp", RGB(255, 255, 255));
        pool_RB_trans.LoadBitmap("Resources/map3/bmp/pool_RB_trans.bmp", RGB(255, 255, 255));
        pool_RU_trans.LoadBitmap("Resources/map3/bmp/pool_RU_trans.bmp", RGB(255, 255, 255));

        //map4
        box.LoadBitmap("Resources/map4/bmp/box.bmp", RGB(255, 255, 255));
        rock1.LoadBitmap("Resources/map4/bmp/rock1.bmp", RGB(255, 255, 255));
        rock2.LoadBitmap("Resources/map4/bmp/rock2.bmp", RGB(255, 255, 255));
        stone.LoadBitmap("Resources/map4/bmp/stone.bmp", RGB(255, 255, 255));
        cross_trans_L.LoadBitmap("Resources/map4/bmp/cross_trans_L.bmp", RGB(255, 255, 255));
        cross_trans_R.LoadBitmap("Resources/map4/bmp/cross_trans_R.bmp", RGB(255, 255, 255));
        iron1_trans_B.LoadBitmap("Resources/map4/bmp/iron1_trans_B.bmp", RGB(255, 255, 255));
        iron2_trans_B.LoadBitmap("Resources/map4/bmp/iron2_trans_B.bmp", RGB(255, 255, 255));
        lamb_trans_B.LoadBitmap("Resources/map4/bmp/lamb_trans_B.bmp", RGB(255, 255, 255));

        //map5
        block.LoadBitmap("Resources/map5/bmp/block.bmp", RGB(255, 255, 255));
        block2_trans.LoadBitmap("Resources/map5/bmp/block2_trans.bmp", RGB(255, 255, 255));
        bottle_B.LoadBitmap("Resources/map5/bmp/bottle_B.bmp", RGB(255, 255, 255));
        box_b.LoadBitmap("Resources/map5/bmp/box_b.bmp", RGB(255, 255, 255));
        box_d.LoadBitmap("Resources/map5/bmp/box_d.bmp", RGB(255, 255, 255));
        triangle_trans.LoadBitmap("Resources/map5/bmp/triangle_trans.bmp", RGB(255, 255, 255));

        //bomb
        bomb1.LoadBitmap("Resources/item/bmp/bomb.bmp", RGB(255, 255, 255));
        bomb2.LoadBitmap("Resources/item/bmp/bomb2.bmp", RGB(255, 255, 255));
        bomb3.LoadBitmap("Resources/item/bmp/bomb3.bmp", RGB(255, 255, 255));
        explode.LoadBitmap("Resources/item/bmp/explode.bmp", RGB(255, 255, 255));
        //Nullnull
        NullS.LoadBitmap("Resources/item/bmp/null.bmp", RGB(255, 255, 255));


        //water
        w_R.LoadBitmap("Resources/player/bmp/water_right.bmp", RGB(255, 255, 255));
		w_R_E.LoadBitmap("Resources/player/bmp/water_right_end.bmp", RGB(255, 255, 255));

		w_L.LoadBitmap("Resources/player/bmp/water_left.bmp", RGB(255, 255, 255));
		w_L_E.LoadBitmap("Resources/player/bmp/water_left_end.bmp", RGB(255, 255, 255));

		w_U.LoadBitmap("Resources/player/bmp/water_up.bmp", RGB(255, 255, 255));
		w_U_E.LoadBitmap("Resources/player/bmp/water_up_end.bmp", RGB(255, 255, 255));

		w_D.LoadBitmap("Resources/player/bmp/water_down.bmp", RGB(255, 255, 255));
		w_D_E.LoadBitmap("Resources/player/bmp/water_down_end.bmp", RGB(255, 255, 255));


        //Props
        Props_1.LoadBitmap("Resources/item/bmp/props_1.bmp", RGB(255, 255, 255));
        Props_2.LoadBitmap("Resources/item/bmp/props_2.bmp", RGB(255, 255, 255));
        Props_3.LoadBitmap("Resources/item/bmp/props_3.bmp", RGB(255, 255, 255));
        Props_4.LoadBitmap("Resources/item/bmp/prop_4_trans.bmp", RGB(255, 255, 255));
        Props_5.LoadBitmap("Resources/item/bmp/prop_5.bmp", RGB(255, 255, 255));



    }

    void CGameMap::selectShow()
    {
        for (int i = 0; i < 15; i++){
            for (int j = 0; j < 13; j++) {
                switch (map[j][i]) {
                case 0:
                    break;
                case 1:
                    if(mode == 1)
                    {
                        blocks_r.SetTopLeft(X + (MapWidth * i), Y + (MapHeight *( j+1)) - blocks_r.GetHeight());
                        blocks_r.ShowBitmap();
                    }
                    else if(mode == 2)
                    {
                        cactus.SetTopLeft(X + (MapWidth * i), Y + (MapHeight *( j+1)) - cactus.GetHeight());
                        cactus.ShowBitmap();
                    }
                    else if(mode == 3){
                        basket_trans.SetTopLeft(X + (MapWidth * i), Y + (MapHeight *( j+1)) - basket_trans.GetHeight());
                        basket_trans.ShowBitmap();
                    }
                    else if(mode == 4){
                        box.SetTopLeft(X + (MapWidth * i), Y + (MapHeight *( j+1)) - box.GetHeight());
                        box.ShowBitmap();
                    }
                    else if(mode == 5)
                    {
                        block.SetTopLeft(X + (MapWidth * i), Y + (MapHeight *( j+1)) - block.GetHeight());
                        block.ShowBitmap();
                    }
                    break;
                case 2:
                    if(mode == 1)
                    {
                        blocks_y.SetTopLeft(X + (MapWidth * i), Y + (MapHeight * (j+1)) - blocks_y.GetHeight());
                        blocks_y.ShowBitmap();
                    }
                    else if(mode == 2)
                    {
                        earth.SetTopLeft(X + (MapWidth * i), Y + (MapHeight * (j+1)) - earth.GetHeight());
                        earth.ShowBitmap();
                    }
                    else if(mode == 3){
                        flower_trans.SetTopLeft(X + (MapWidth * i), Y + (MapHeight * (j+1)) - flower_trans.GetHeight());
                        flower_trans.ShowBitmap();
                    }
                    else if(mode == 4){
                        rock1.SetTopLeft(X + (MapWidth * i), Y + (MapHeight *(j+1)) - rock1.GetHeight());
                        rock1.ShowBitmap();
                    }
                    else if(mode == 5)
                    {
                        block2_trans.SetTopLeft(X + (MapWidth * i), Y + (MapHeight *( j+1)) - block2_trans.GetHeight());
                        block2_trans.ShowBitmap();
                    }
                    break;
                case 3:
                    if(mode == 1)
                    {
                        grass.SetTopLeft(X + (MapWidth * i), Y + (MapHeight *( j+1)) - grass.GetHeight());
                        grass.ShowBitmap();
                    }
                    else if(mode == 2)
                    {
                        green_box.SetTopLeft(X + (MapWidth * i), Y + (MapHeight *( j+1)) - green_box.GetHeight());
                        green_box.ShowBitmap();
                    }
                    else if(mode == 3){
                        grassBlock_trans.SetTopLeft(X + (MapWidth * i), Y + (MapHeight *( j+1)) - grassBlock_trans.GetHeight());
                        grassBlock_trans.ShowBitmap();
                    }
                    else if(mode == 4){
                        rock2.SetTopLeft(X + (MapWidth * i), Y + (MapHeight *( j+1)) - rock2.GetHeight());
                        rock2.ShowBitmap();
                    }
                    else if(mode == 5)
                    {
                        bottle_B.SetTopLeft(X + (MapWidth * i), Y + (MapHeight *( j+1)) - bottle_B.GetHeight());
                        bottle_B.ShowBitmap();
                    }
                    break;
                case 4:
                    if(mode == 1)
                    {
                        house_b.SetTopLeft(X + (MapWidth * i), Y + (MapHeight * (j+1)) - house_b.GetHeight());
                        house_b.ShowBitmap();
                    }
                    else if(mode == 2)
                    {
                        green_box2.SetTopLeft(X + (MapWidth * i), Y + (MapHeight * (j+1)) - green_box2.GetHeight());
                        green_box2.ShowBitmap();
                    }
                    else if(mode == 3){
                        tree_trans.SetTopLeft(X + (MapWidth * i), Y + (MapHeight * (j+1)) - tree_trans.GetHeight());
                        tree_trans.ShowBitmap();
                    }
                    else if(mode == 4)
                    {
                        stone.SetTopLeft(X + (MapWidth * i), Y + (MapHeight *( j+1)) - stone.GetHeight());
                        stone.ShowBitmap();
                    }
                    else if(mode == 5)
                    {
                        box_b.SetTopLeft(X + (MapWidth * i), Y + (MapHeight *( j+1)) - box_b.GetHeight());
                        box_b.ShowBitmap();
                    }
                    break;
                case 5:
                    if(mode == 1)
                    {
                        house_r.SetTopLeft(X + (MapWidth * i), Y + (MapHeight *( j+1)) - house_r.GetHeight());
                        house_r.ShowBitmap();
                    }
                    else if(mode == 2)
                    {
                        rock.SetTopLeft(X + (MapWidth * i), Y + (MapHeight *( j+1)) - rock.GetHeight());
                        rock.ShowBitmap();
                    }
                    else if(mode == 5)
                    {
                        box_d.SetTopLeft(X + (MapWidth * i), Y + (MapHeight *( j+1)) - box_d.GetHeight());
                        box_d.ShowBitmap();
                    }
                    break;
                case 6:
                    if(mode == 1)
                    {
                        house_y.SetTopLeft(X + (MapWidth * i), Y + (MapHeight *( j+1)) - house_y.GetHeight());
                        house_y.ShowBitmap();
                    }
                    else if(mode == 2)
                    {
                        tent_b.SetTopLeft(X + (MapWidth * i), Y + (MapHeight *( j+1)) - tent_b.GetHeight());
                        tent_b.ShowBitmap();
                    }
                    else if(mode == 4)
                    {
                        cross_trans_L.SetTopLeft(X + (MapWidth * i), Y + (MapHeight *( j+1)) - cross_trans_L.GetHeight());
                        cross_trans_L.ShowBitmap();
                    }
                    else if(mode == 5)
                    {
                        triangle_trans.SetTopLeft(X + (MapWidth * i), Y + (MapHeight *( j+1)) - triangle_trans.GetHeight());
                        triangle_trans.ShowBitmap();
                    }
                    break;
                case 7:
                    if(mode == 1)
                    {
                        tree.SetTopLeft(X + (MapWidth * i), Y + (MapHeight *( j+1)) - tree.GetHeight());
                        tree.ShowBitmap();
                    }
                    else if(mode == 2)
                    {
                        tent_r.SetTopLeft(X + (MapWidth * i), Y + (MapHeight *( j+1)) - tent_r.GetHeight());
                        tent_r.ShowBitmap();
                    }
                    else if(mode == 4)
                    {
                        cross_trans_R.SetTopLeft(X + (MapWidth * i), Y + (MapHeight *( j+1)) - cross_trans_R.GetHeight());
                        cross_trans_R.ShowBitmap();
                    }
                    break;
                case 8:
                    if(mode == 1)
                    {
                        wooden_box.SetTopLeft(X + (MapWidth * i), Y + (MapHeight *( j+1)) - wooden_box.GetHeight());
                        wooden_box.ShowBitmap();
                    }
                    else if(mode == 2)
                    {
                        tent_y.SetTopLeft(X + (MapWidth * i), Y + (MapHeight *( j+1)) - tent_y.GetHeight());
                        tent_y.ShowBitmap();
                    }
                    else if(mode == 4)
                    {
                        iron1_trans_B.SetTopLeft(X + (MapWidth * i), Y + (MapHeight *( j+1)) - iron1_trans_B.GetHeight());
                        iron1_trans_B.ShowBitmap();
                    }
                    break;
                case 9:
                    if(mode == 4)
                    {
                        iron2_trans_B.SetTopLeft(X + (MapWidth * i), Y + (MapHeight *( j+1)) - iron2_trans_B.GetHeight());
                        iron2_trans_B.ShowBitmap();
                    }
                    break;
                case 10:
                    if(mode == 3)
                    {
                        pool_LB_trans.SetTopLeft(X + (MapWidth * i), Y + (MapHeight *( j+1)) - pool_LB_trans.GetHeight());
                        pool_LB_trans.ShowBitmap();
                    }
                    else if(mode == 4)
                    {
                        lamb_trans_B.SetTopLeft(X + (MapWidth * i), Y + (MapHeight *( j+1)) - lamb_trans_B.GetHeight());
                        lamb_trans_B.ShowBitmap();
                    }
                    break;
                case 11:
                    pool_LU_trans.SetTopLeft(X + (MapWidth * i), Y + (MapHeight *( j+1)) - pool_LU_trans.GetHeight());
                    pool_LU_trans.ShowBitmap();
                    break;
                case 12:
                    pool_MB_trans.SetTopLeft(X + (MapWidth * i), Y + (MapHeight * (j+1)) - pool_MB_trans.GetHeight());
                    pool_MB_trans.ShowBitmap();
                    break;
                case 13:
                    pool_MU_trans.SetTopLeft(X + (MapWidth * i), Y + (MapHeight * (j+1)) - pool_MU_trans.GetHeight());
                    pool_MU_trans.ShowBitmap();
                    break;
                case 14:
                    pool_RB_trans.SetTopLeft(X + (MapWidth * i), Y + (MapHeight * (j+1)) - pool_RB_trans.GetHeight());
                    pool_RB_trans.ShowBitmap();
                    break;
                case 15:
                    pool_RU_trans.SetTopLeft(X + (MapWidth * i), Y + (MapHeight * (j+1)) - pool_RU_trans.GetHeight());
                    pool_RU_trans.ShowBitmap();
                    break;
                case 100:
                    NullS.SetTopLeft(X + (MapWidth * i), Y + (MapHeight * (j+1)) - NullS.GetHeight());
                    //NullS.ShowBitmap();
                    break;
                case 101:
                    Props_1.SetTopLeft(X + (MapWidth * i), Y + (MapHeight * (j+1)) - Props_1.GetHeight());
                    Props_1.ShowBitmap();
                    break;
                case 102:
                    Props_2.SetTopLeft(X + (MapWidth * i), Y + (MapHeight * (j+1)) - Props_2.GetHeight());
                    Props_2.ShowBitmap();
                    break;
                case 103:
                    Props_3.SetTopLeft(X + (MapWidth * i), Y + (MapHeight * (j+1)) - Props_3.GetHeight());
                    Props_3.ShowBitmap();
                    break;
                case 104:
                    Props_4.SetTopLeft(X + (MapWidth * i), Y + (MapHeight * (j+1)) - Props_4.GetHeight());
                    Props_4.ShowBitmap();
                    break;
                case 105:
                    Props_5.SetTopLeft(X + (MapWidth * i), Y + (MapHeight * (j+1)) - Props_5.GetHeight());
                    Props_5.ShowBitmap();
                    break;
				default:
					ASSERT(0);
                

                }
            }
        }
    }

    void CGameMap::bombShow()
    {
        for (int i = 0; i < 15; i++){
            for (int j = 0; j < 13; j++) {
				switch (bombMap[j][i]) {
				case 0:
					break;
				case 11:
					bomb3.SetTopLeft(X + (MapWidth * i), Y + (MapHeight * j));
					bomb3.ShowBitmap();
					break;
				case 10:
					bomb1.SetTopLeft(X + (MapWidth * i), Y + (MapHeight * j));
					bomb1.ShowBitmap();
					break;
				case 9:
					bomb2.SetTopLeft(X + (MapWidth * i), Y + (MapHeight * j));
					bomb2.ShowBitmap();
					break;
				case 8:
					bomb1.SetTopLeft(X + (MapWidth * i), Y + (MapHeight * j));
					bomb1.ShowBitmap();
					break;
				case 7:
					bomb3.SetTopLeft(X + (MapWidth * i), Y + (MapHeight * j));
					bomb3.ShowBitmap();
					break;
				case 6:
					bomb1.SetTopLeft(X + (MapWidth * i), Y + (MapHeight * j));
					bomb1.ShowBitmap();
					break;
				case 5:
					bomb2.SetTopLeft(X + (MapWidth * i), Y + (MapHeight * j));
					bomb2.ShowBitmap();
					break;
				case 4:
					bomb1.SetTopLeft(X + (MapWidth * i), Y + (MapHeight * j));
					bomb1.ShowBitmap();
					break;
				case 3:
					bomb3.SetTopLeft(X + (MapWidth * i), Y + (MapHeight * j));
					bomb3.ShowBitmap();
					break;
				case 2:
					bomb1.SetTopLeft(X + (MapWidth * i), Y + (MapHeight * j));
					bomb1.ShowBitmap();
					break;
				case 1:
					explode.SetTopLeft(X + (MapWidth * i), Y + (MapHeight * j));
					explode.ShowBitmap();
					break;
				default:
					ASSERT(0);
				}
            }
        }
    }
	
    void CGameMap::explodeShow()
    {
        for (int i = 0; i < 15; i++)
			for (int j = 0; j < 13; j++) {
				switch (exp_Map[j][i]) {
				case 0:
					break;
				case 1:
					w_U.SetTopLeft(X + (MapWidth * i), Y + (MapHeight * j));
					w_U.ShowBitmap();
					if (timer % 7 == 0)
					{
						exp_Map[j][i] = 0;
					}

					break;
				case 2:
					w_U_E.SetTopLeft(X + (MapWidth * i), Y + (MapHeight * j));
					w_U_E.ShowBitmap();
					if (timer % 7 == 0)
					{
						exp_Map[j][i] = 0;
					}
					break;
				case 3:
					w_D.SetTopLeft(X + (MapWidth * i), Y + (MapHeight * j));
					w_D.ShowBitmap();
					if (timer % 7 == 0)
					{
						exp_Map[j][i] = 0;
					}
					break;
				case 4:
					w_D_E.SetTopLeft(X + (MapWidth * i), Y + (MapHeight * j));
					w_D_E.ShowBitmap();
					if (timer % 7 == 0)
					{
						exp_Map[j][i] = 0;
					}
					break;
				case 5:
					w_L.SetTopLeft(X + (MapWidth * i), Y + (MapHeight * j));
					w_L.ShowBitmap();
					if (timer % 7 == 0)
					{
						exp_Map[j][i] = 0;
					}
					break;
				case 6:
					w_L_E.SetTopLeft(X + (MapWidth * i), Y + (MapHeight * j));
					w_L_E.ShowBitmap();
					if (timer % 7 == 0)
					{
						exp_Map[j][i] = 0;
					}
					break;
				case 7:
					w_R.SetTopLeft(X + (MapWidth * i), Y + (MapHeight * j));
					w_R.ShowBitmap();
					if (timer % 7 == 0)
					{
						exp_Map[j][i] = 0;
					}
					break;
				case 8:
					w_R_E.SetTopLeft(X + (MapWidth * i), Y + (MapHeight * j));
					w_R_E.ShowBitmap();
					if (timer % 7 == 0)
					{
						exp_Map[j][i] = 0;
					}
					break;
				default:
					ASSERT(0);
				}
			}

    }
    

    void CGameMap::OnShow()
    {
        //bombShow();
        //explodeShow();
		selectShow();
    }

	bool CGameMap::OnAudio(int mode)
	{
		if (mode == 0)
			return audio[0];
		else if (mode == 1)
			return audio[1];
		else if (mode == 2)
			return audio[2];
		else if (mode == 3)
			return audio[3];
		else
			return 0;
	}

	void CGameMap::ResetAudio(int mode)
	{
		for (int i = 0; i < 4; i++)
		{
			if (mode == i)
				audio[i] = 0;
		}
	}

    CGameMap::~CGameMap(){}
}
