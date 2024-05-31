#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"
#include "config.h"

using namespace game_framework;

CGameStateRun::CGameStateRun(CGame *g) : CGameState(g)
{
}

CGameStateRun::~CGameStateRun()
{
}

void CGameStateRun::OnBeginState()
{
	player1.init(1);
	player2.init(2);
	select_mode = 0;
	play_mode = 0;
	player1_Win = 0;
	player2_Win = 0;
	timer = 200;
}

void CGameStateRun::OnMove()
{	
	if (play_mode != 1)
	{
		CAudio::Instance()->Stop(AUDIO_MUSIC);
	}

	if (play_mode == 1)
	{	
		gamemap.OnMove();
		player1.OnMove();
		player2.OnMove();
		player1.setMap(gamemap.getMap()); 
		player2.setMap(gamemap.getMap());
		gamemap.OnProps(player1.getX1(), player1.getY1(), 1);
		gamemap.OnProps(player2.getX1(), player2.getY1(), 2);
		gamemap.setP1Range(player1.getX1(), player1.getY1());
		gamemap.setP2Range(player2.getX1(), player2.getY1());
		player1.setSpeed(gamemap.getP1Speed());
		player2.setSpeed(gamemap.getP2Speed());
		player1.setJump(gamemap.getP1Jump());
		player2.setJump(gamemap.getP2Jump());
		int p1s = gamemap.getP1Status();
		int p2s = gamemap.getP2Status();
		
		for (int i = 0; i < 4; i++)
		{
			if (gamemap.OnAudio(i) == 1)
			{
				CAudio::Instance()->Play(i+2, false);
				gamemap.ResetAudio(i);
			}
		}

		if (p1s != 5)
		{
			player1.setStatus(p1s);
			player1.setSpeed(1);
		}
		if (p2s != 5)
		{
			player2.setStatus(p2s);
			player2.setSpeed(1);
		}	
		if (p1s == 0)
		{	
			CAudio::Instance()->Play(AUDIO_DIE, false);
			CAudio::Instance()->Stop(AUDIO_MUSIC);
			player2_Win = 1;
			play_mode = 2;
		}
		if (p2s == 0)
		{	
			CAudio::Instance()->Play(AUDIO_DIE, false);
			CAudio::Instance()->Stop(AUDIO_MUSIC);
			player1_Win = 1;
			play_mode = 2;	
		}
	}
	
	if (play_mode == 2)
	{	
		timer--;
		
		if (timer == 120)
			CAudio::Instance()->Play(AUDIO_OVER, false);
		if (player2_Win == 1)
		{	
			if (timer == 0)
			{
				GotoGameState(GAME_STATE_OVER);
			}	
		}
		if (player1_Win == 1)
		{	
			if (timer  == 0)
			{
				GotoGameState(GAME_STATE_OVER);
			}	
		}

	}

	
}

void CGameStateRun::OnInit()  
{
	select_map.LoadBitmap("Resources/pages/map_select1.2.bmp", RGB(255, 255, 255));
	select_map.SetTopLeft((SIZE_X - 15 - select_map.GetWidth())/2, SIZE_Y/13);
	select_mode = 0;
	play_mode = 0;
	player1_Win = 0;
	player2_Win = 0;
	timer = 200;
	
	background.LoadBitmapByString({"resources/map1/bmp/map1.bmp",
			"resources/map2/bmp/map2.bmp",
			"resources/map3/bmp/map3.bmp",
			"resources/map4/bmp/map4.bmp",
			"resources/map5/bmp/map5.bmp"
		});
	player1Win.LoadBitmap("Resources/pages/game_end1.bmp", RGB(255, 255, 255));
	player2Win.LoadBitmap("Resources/pages/game_end2.bmp", RGB(255, 255, 255));
	player1Win.SetTopLeft((SIZE_X - 15 - player1Win.GetWidth())/2, SIZE_Y/13);
	player2Win.SetTopLeft((SIZE_X - 15 - player2Win.GetWidth())/2, SIZE_Y/13);
	background.SetTopLeft(0, 0);
	gamemap.LoadBitmap();
	player1.LoadBitmap();
	player2.LoadBitmap();

	CAudio::Instance()->Load(AUDIO_START,  "sounds\\start.wav");
	CAudio::Instance()->Load(AUDIO_MUSIC,  "sounds\\music.wav");
	CAudio::Instance()->Load(AUDIO_BOBO, "sounds\\bobo.wav");
	CAudio::Instance()->Load(AUDIO_BANG, "sounds\\bang.wav");
	CAudio::Instance()->Load(AUDIO_DING, "sounds\\ding.wav");
	CAudio::Instance()->Load(AUDIO_DIE, "sounds\\die.wav");	
	CAudio::Instance()->Load(AUDIO_OVER, "sounds\\over.wav");

}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{	
	const char KEY_A = 0x41;		
	const char KEY_W = 0x57;		
	const char KEY_D = 0x44;		
	const char KEY_S = 0x53;
	const char KEY_SPACE = 0x20;
	const char KEY_V = 0x56;

	const char KEY_LEFT  = 0x25; 
	const char KEY_UP    = 0x26;
	const char KEY_RIGHT = 0x27;
	const char KEY_DOWN  = 0x28;
	const char KEY_ENTER = 0x0D;
	const char KEY_M = 0x4D;

	const char KEY_E = 0x45;		
	const char KEY_R = 0x52;
	const char KEY_T = 0x54;		
	const char KEY_Y = 0x59;
	const char KEY_U = 0x55;		
	const char KEY_I = 0x49;
	const char KEY_O = 0x4F;		
	const char KEY_P = 0x50;
	
	if(play_mode == 1)
	{
		if (nChar == KEY_A)
		{
			player1.setdirection(3, true);
		}
		if (nChar == KEY_D)
		{
			player1.setdirection(4, true);
		}
		if (nChar == KEY_W)
		{
			player1.setdirection(1, true);
		}
		if (nChar == KEY_S)
		{
			player1.setdirection(2, true);
		}

		
		if (nChar == KEY_LEFT)
		{
			player2.setdirection(3, true);
		}
		if (nChar == KEY_RIGHT)
		{
			player2.setdirection(4, true);
		}
		if (nChar == KEY_UP)
		{
			player2.setdirection(1, true);
		}
		if (nChar == KEY_DOWN)
		{
			player2.setdirection(2, true);
		}
		

	}
	
		
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_ESC = 0x1B;
	const char KEY_S = 0x53;
	const char KEY_D = 0x44;
	const char KEY_F = 0x46;
	const char KEY_G = 0x47;
	const char KEY_H = 0x48;
	const char KEY_J = 0x4A;
	const char KEY_K = 0x4B;
	const char KEY_A = 0x41;		
	const char KEY_W = 0x57;
	
	const char KEY_R = 0x52;
	const char KEY_T = 0x54;		
	const char KEY_Y = 0x59;
	const char KEY_U = 0x55;		
	const char KEY_I = 0x49;
	
	const char KEY_SPACE = 0x20;
	const char KEY_V = 0x56;

	const char KEY_LEFT  = 0x25; 
	const char KEY_UP    = 0x26;
	const char KEY_RIGHT = 0x27;
	const char KEY_DOWN  = 0x28;
	const char KEY_ENTER = 0x0D;
	const char KEY_M = 0x4D;
	

	if(select_mode == 0)
		if(nChar == KEY_S || nChar == KEY_D || nChar == KEY_F || nChar == KEY_G || nChar == KEY_H)
		{	
			select_mode = 1;
			if(select_mode == 1)
			{
				player1.init(1);
				player2.init(2);
				CAudio::Instance()->Play(AUDIO_START, false);
				CAudio::Instance()->Play(AUDIO_MUSIC, true);
				if (nChar == KEY_S)
				{
					gamemap.setMode(1);
					gamemap.select_map();
					background.SetFrameIndexOfBitmap(0);
					play_mode = 1;
				}
				else if (nChar == KEY_D)
				{
					gamemap.setMode(2);
					gamemap.select_map();
					background.SetFrameIndexOfBitmap(1);
					play_mode = 1;
				}
				else if (nChar == KEY_F)
				{
					gamemap.setMode(3);
					gamemap.select_map();
					background.SetFrameIndexOfBitmap(2);
					play_mode = 1;
				}
				else if (nChar == KEY_G)
				{
					gamemap.setMode(4);
					gamemap.select_map();
					background.SetFrameIndexOfBitmap(3);
					play_mode = 1;
				}
				else if (nChar == KEY_H)
				{
					gamemap.setMode(5);
					gamemap.select_map();
					background.SetFrameIndexOfBitmap(4);
					play_mode = 1;
				}
			}
	}

	if(play_mode == 1)
	{
		if (nChar == KEY_A)
		{
			player1.setdirection(3, false);
		}
		if (nChar == KEY_D)
		{
			player1.setdirection(4, false);
		}
		if (nChar == KEY_W)
		{
			player1.setdirection(1, false);
		}
		if (nChar == KEY_S)
		{
			player1.setdirection(2, false);
		}
		if (nChar == KEY_LEFT)
		{
			player2.setdirection(3, false);
		}
		if (nChar == KEY_RIGHT)
		{
			player2.setdirection(4, false);
		}
		if (nChar == KEY_UP)
		{
			player2.setdirection(1, false);
		}
		if (nChar == KEY_DOWN)
		{
			player2.setdirection(2, false);
		}
		if (nChar == KEY_K)
		{
			select_mode = 0;
			play_mode = 0;
		}

		if (nChar == KEY_SPACE) {
			int Xtest = (player1.getX1() + 35) / 70;
			int Ytest = (player1.getY1() + 35) / 70;
			gamemap.OnKeyDown(nChar, Xtest, Ytest, 1);
			player1.setMap(gamemap.getMap());
			player2.setMap(gamemap.getMap());
		}
		if (nChar == KEY_V) {
			int Xtest = (player2.getX1() + 35) / 70;
			int Ytest = (player2.getY1() + 35) / 70;
			gamemap.OnKeyDown(nChar, Xtest, Ytest, 1);
			player1.setMap(gamemap.getMap());
			player2.setMap(gamemap.getMap());
		}

		if (nChar == KEY_ENTER) {
			int Xtest = (player2.getX1() + 35) / 70;
			int Ytest = (player2.getY1() + 35) / 70;
			gamemap.OnKeyDown(nChar, Xtest, Ytest, 2);
			player1.setMap(gamemap.getMap());
			player2.setMap(gamemap.getMap());
		}
		if (nChar == KEY_M) {
			int Xtest = (player1.getX1() + 35) / 70;
			int Ytest = (player1.getY1() + 35) / 70;
			gamemap.OnKeyDown(nChar, Xtest, Ytest, 2);
			player1.setMap(gamemap.getMap());
			player2.setMap(gamemap.getMap());
		}
		if(nChar == KEY_R)
		{
			// quantity
			int Xtest = (player1.getX1() + 35) / 70;
			int Ytest = (player1.getY1() + 35) / 70;
			gamemap.OnKeyDown(nChar, Xtest, Ytest, 1);
		}
		if(nChar == KEY_T)
		{
			// distance
			int Xtest = (player1.getX1() + 35) / 70;
			int Ytest = (player1.getY1() + 35) / 70;
			gamemap.OnKeyDown(nChar, Xtest, Ytest, 1);
		}
		if(nChar == KEY_Y)
		{
			// speed
			int Xtest = (player1.getX1() + 35) / 70;
			int Ytest = (player1.getY1() + 35) / 70;
			gamemap.OnKeyDown(nChar, Xtest, Ytest, 1);
			player1.setSpeed(gamemap.getP1Speed());
			player2.setSpeed(gamemap.getP2Speed());
		}
		if(nChar == KEY_U)
		{
			// jump
			int Xtest = (player1.getX1() + 35) / 70;
			int Ytest = (player1.getY1() + 35) / 70;
			gamemap.OnKeyDown(nChar, Xtest, Ytest, 1);
			player1.setJump(gamemap.getP1Jump());
			player2.setJump(gamemap.getP2Jump());
		}
		if(nChar == KEY_I)
		{
			// life
			int Xtest = (player1.getX1() + 35) / 70;
			int Ytest = (player1.getY1() + 35) / 70;
			gamemap.OnKeyDown(nChar, Xtest, Ytest, 1);
		}
	}
	if (nChar == KEY_ESC)
	{
		PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0);
	}
	if (nChar == KEY_J)
	{	
		CAudio::Instance()->Stop(AUDIO_MUSIC);
		select_mode = 0;
		play_mode = 0;
		GotoGameState(GAME_STATE_INIT);	
	}
}

void CGameStateRun::OnShow()
{
	if(select_mode == 0)
	{
		select_map.ShowBitmap();
	}
	else
	{	
		if (play_mode == 1)
		{
			background.ShowBitmap();
			gamemap.bombShow();
			gamemap.explodeShow();
			player1.OnShow();
			player2.OnShow();
			gamemap.OnShow();
			
			if(player1.getJump() == 2)
			{
				player1.OnShow();
			}
			if(player2.getJump() == 2)
			{
				player2.OnShow();
			}
		}	
		
	}
	if (play_mode == 1)
	{
		
		
	}
	if (player2_Win == 1 && play_mode == 2)
	{
		player2Win.ShowBitmap();
	}
	if (player1_Win == 1 && play_mode == 2)
	{	
		player1Win.ShowBitmap();	
	}
}
