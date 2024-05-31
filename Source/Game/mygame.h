#include "CGameMap.h"
#include "player.h"
namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////

	enum AUDIO_ID {				// 
		AUDIO_START,			// 0
		AUDIO_MUSIC,			// 1
		AUDIO_BOBO,				// 2
		AUDIO_BANG,				// 3
		AUDIO_DING,				// 4
		AUDIO_DIE,				// 5
		AUDIO_OVER				// 6
	};

	/////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////

	class CGameStateInit : public CGameState {
	public:
		CGameStateInit(CGame *g);
		void OnInit(); 
		void OnBeginState();
		void OnKeyUp(UINT, UINT, UINT); 
		void OnLButtonDown(UINT nFlags, CPoint point);
	protected:
		void OnShow();
	private:
		CMovingBitmap logo;	
		CMovingBitmap background;
	};

	/////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateRun : public CGameState {
	public:
		CGameStateRun(CGame *g);
		~CGameStateRun();
		void OnBeginState();
		void OnInit(); 
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		
	protected:
		void OnMove();
		void OnShow();
		int timer;
		int select_mode;
		
		int play_mode;
		int player1_Win, player2_Win;
	private:
		CMovingBitmap select_map, background;
		CMovingBitmap player1Win,player2Win;
		CGameMap gamemap;
		Player player1;
		Player player2;
		
	};

	/////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateOver : public CGameState {
	public:
		CGameStateOver(CGame *g);
		void OnBeginState();
		void OnInit();
	protected:
		void OnMove();
		void OnShow();
		int over_mode;
	private:
		int counter;
		CMovingBitmap gameover;
	};

}
