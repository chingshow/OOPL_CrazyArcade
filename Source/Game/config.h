/////////////////////////////////////////////////////////////////////////////
// 定義遊戲可設定的環境與條件
/////////////////////////////////////////////////////////////////////////////

#define GAME_TITLE           "CrazyArcade"
//! 設定遊戲畫面的解析度（寬度）
#define SIZE_X				 1065
//! 設定遊戲畫面的解析度（高度）
#define SIZE_Y				 931
//! 是否以全螢幕方式開啟遊戲
#define OPEN_AS_FULLSCREEN	 false		
//! 是否顯示loading(OnInit)的進度
#define SHOW_LOAD_PROGRESS   true		
// 遊戲畫面預設的背景顏色(黑色)
#define DEFAULT_BG_COLOR	 RGB(0, 0, 0)	
//! 每33ms跑一次Move及Show(每秒30次)
#define GAME_CYCLE_TIME		 15		    
//! 是否在debug mode顯示cycle time
#define SHOW_GAME_CYCLE_TIME false		
//! 是否允許以 Ctrl-Q 暫停遊戲
#define ENABLE_GAME_PAUSE	 true		
//! 啟動音效介面
#define ENABLE_AUDIO		 true		
 //! 是否關閉 toolbar
#define ENABLE_TOOLBAR       true     
//! 是否關閉 menu
#define ENABLE_MENU          true      
//! 是否關閉 statusbar
#define ENABLE_STATUSBAR     true      
//! 全螢幕用，請設定成目前視窗的解析度 (width)。
#define RESOLUTION_X     1920//     2880      
//! 全螢幕用，請設定成目前視窗的解析度 (height)。
#define RESOLUTION_Y     1080//     1620     
