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

CGameStateInit::CGameStateInit(CGame *g) : CGameState(g)
{
}

void CGameStateInit::OnInit()
{
	
	ShowInitProgress(0, "Start Initialize...");
	logo.LoadBitmap("Resources/pages/Home_page_1.4.bmp", RGB(255, 255, 255));
	logo.SetTopLeft((SIZE_X - 15 - logo.GetWidth())/2, SIZE_Y/13);
}

void CGameStateInit::OnBeginState()
{
}

void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_ENTER = 0x0D;
	const char KEY_ESC = 0x1B;
	CAudio::Instance()->Stop(AUDIO_MUSIC);
	if (nChar == KEY_ENTER)
	{
		GotoGameState(GAME_STATE_RUN);	
	}
	else if (nChar == KEY_ESC)
	{
		PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0);
	}
}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
}

void CGameStateInit::OnShow()
{
	logo.ShowBitmap();
}
