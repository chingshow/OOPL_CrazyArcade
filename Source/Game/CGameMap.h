#pragma once
namespace game_framework
{    
    class CGameMap
    {
    public:
        CGameMap();
        void OnKeyDown(UINT nChar, int Xtest, int Ytest, int id);
        void setBombInfo();	
        void set_expMap();
        void setLinkBomb();
        void OnProps(int X1, int Y1, int id);
        void setP1Range(int x1, int y1);
		void setP2Range(int x1, int y1);
        void hitWater();
        void getHitP1AndDecrease();
		void getHitP2AndDecrease();
        void updateMap();
        bool isBreakable(int position);
        int getP1Status();
		int getP2Status();
        int getP1Life();
		int getP2Life();
        int getP1Speed();
		int getP2Speed();
        int getP1Jump();
		int getP2Jump();
        void OnMove();
        void setMode(int m);
        void select_map();
        void LoadBitmap();
        void selectShow();
        void bombShow();
        void explodeShow();
        void OnShow();
        bool OnAudio(int);
		void ResetAudio(int);
        int (*getMap())[15];
        
        ~CGameMap();
    private:
    	int map[13][15];
        //map1
        CMovingBitmap blocks_r, blocks_y, grass, house_b,
        house_r, house_y, tree, wooden_box;
        //map2
        CMovingBitmap cactus, earth, green_box, green_box2,
        rock, tent_b, tent_r, tent_y;
        //map3
        CMovingBitmap basket_trans, flower_trans, grassBlock_trans, tree_trans,
        pool_LB_trans, pool_LU_trans, pool_MB_trans, pool_MU_trans, pool_RB_trans, pool_RU_trans;
        //map4
        CMovingBitmap box, rock1, rock2, stone, cross_trans_L, cross_trans_R,
        iron1_trans_B, iron2_trans_B, lamb_trans_B;
        //map5
        CMovingBitmap block, block2_trans, bottle_B, box_b, box_d, triangle_trans;
        //bomp
        CMovingBitmap bomb1, bomb2, bomb3, explode;
        //Nullnull
        CMovingBitmap NullS;
        //water
        CMovingBitmap w_R, w_R_E, w_L, w_L_E, w_U, w_U_E, w_D, w_D_E;
        //Props
        CMovingBitmap Props_1, Props_2, Props_3, Props_4, Props_5;
        const int X, Y;
        const int MapWidth, MapHeight;
        int mode = 0;
        int mapCopy[13][15];
		int bombMap[13][15];
		int exp_Map[13][15];
        int idMap[13][15];
        int timer;
        int timerb;
        int timerS;
        int p1_Distance, p2_Distance;
		int p1_Quantity, p2_Quantity;
		int p1_Speed, p2_Speed;
		int p1_Status, p2_Status;	
        int p1_Life, p2_Life;
        int p1_Jump, p2_Jump;
        bool p1_Hit, p2_Hit;
        int X1_1, Y1_1;
		int X1_2, Y1_2;
        bool audio[4];
    };
}
