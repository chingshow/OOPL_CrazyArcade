#pragma once

namespace game_framework
{ 
    class Player
    {
    public:
        Player();
        int getX1();
        int getY1();
        int getX2();
        int getY2();
        void setXY(int x, int y);
		void setMap(int map[13][15]);
        void setdirection(int mode, bool flag);
        void setSpeed(int speed);
        int getSpeed();
        void setStatus(int status);
        int getStatus();
        void setId(int user_id);
		int getId();
        void setJump(int jump);
        int getJump();
        void init(int user_id);
        void LoadBitmap();
        void OnMove();
        void OnShow();
        ~Player();
        
    private:
        int x , y ;
        bool isMovingUp , isMovingDown , isMovingLeft , isMovingRight;
        int mode;
        int speed;
        int status;
        int id;
        int jump;
        int map_user[13][15];  
        CMovingBitmap P1_down, P1_up, P1_left, P1_right, p1die1, p1die2,
        P2_down, P2_up, P2_left, P2_right, p2die1, p2die2;
    };
    
    
}
