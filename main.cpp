#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <deque>
#include <iomanip>

using namespace std;
enum direction { LEFT = 0, RIGHT = 1 };

class projectile
{
	private:
		int x, y;
		direction dir;
	public:
		projectile(int xCoor, int yCoor, int player)
		{
			x = xCoor;
			y = yCoor;
			(player == 1) ? dir = RIGHT : dir = LEFT;
		}
	inline int getX() {
		return x;
	}
	inline int getY() {
		return y;
	}
	void Move()
	{
		if(dir == LEFT)
            x--;
        else
            x++;
	}
};

class player
{
	private:
		int x, y;
	public:
		player()
		{
			x = y = 0;
		}
		player(int xCoor, int yCoor)
		{
			x = xCoor;
			y = yCoor;
		}
		inline int getX()
		{
			return x;
		}
		inline int getY()
		{
			return y;
		}
		inline void moveUp()
		{
			y--;
		}
		inline void moveDown()
		{
			y++;
		}
};

class game
{
	private:
		int height, width;
		int player1HP;
		int player2HP;
		char up1, down1, up2, down2;
		bool quit;
		projectile *newProj;
		deque<projectile*> p1Projectiles;
		deque<projectile*> p2Projectiles;
		deque<projectile*>::iterator it;
		player *p1;
		player *p2;
	public:
		game(int h, int w)
		{
			quit = false;
			up1 = 'w';
			down1 = 's';
			up2 = 'o';
			down2 = 'l';
			player1HP = player2HP = 4;
			height = h;
			width = w;
			p1 = new player(0, h/2 - 2);
			p2 = new player(w-2, h/2 - 2);
			newProj = new projectile(p1->getX()+1, p1->getY()+1, 1);
			p1Projectiles.push_back(newProj);
			newProj = new projectile(p2->getX()-1, p2->getY()+1, 2);
			p2Projectiles.push_back(newProj);
		}
		~game()
		{
			for(it = p1Projectiles.begin(); it != p1Projectiles.end(); it++)
                delete *it;
            for(it = p2Projectiles.begin(); it != p2Projectiles.end(); it++)
                delete *it;

            delete p1, p2;
		}
		/*!!!!!!!!!!*/
		void hitUpdate(player * p)
		{
			if (p == p1)
				player1HP--;
			else if (p == p2)
					player2HP--;
		}
		void drawGame()
		{
			system("cls");
			cout << endl << endl;
			for(int i = 0; i < width+1; i++)
				cout << "-";
			cout << endl;

			int p1LeadProjX = p1Projectiles.back()->getX();
            int p1LeadProjY = p1Projectiles.back()->getY();
            int p2LeadProjX = p2Projectiles.back()->getX();
            int p2LeadProjY = p2Projectiles.back()->getY();

            int p1X = p1->getX();
            int p1Y = p1->getY();
            int p2X = p2->getX();
            int p2Y = p2->getY();

            if(p1LeadProjX > width/3)
            {
                newProj = new projectile(p1X+1, p1Y+1, 1);
                p1Projectiles.push_back(newProj);
            }
            if(p2LeadProjX < width*2/3)
            {
                newProj = new projectile(p2X, p2Y+1, 2);
                p2Projectiles.push_back(newProj);
            }

			for(int i = 0; i < height; i++)
            {
                for(int j = 0; j < width; j++)
                {
                    bool drewProj = false;
                    if(j == 0 || j == width-1)
                        cout << "\xB3";

                    for (it = p1Projectiles.begin(); it != p1Projectiles.end(); it++)
                    {
                        int p1ProjX = (*it)->getX();
                        int p1ProjY = (*it)->getY();
                        if(p1ProjX == j && p1ProjY == i)
                        {
                            cout << "\xFE";
                            drewProj = true;
                        }
                    }

                    for (it = p2Projectiles.begin(); it != p2Projectiles.end(); it++)
                    {
                        int p2ProjX = (*it)->getX();
                        int p2ProjY = (*it)->getY();
                        if(p2ProjX == j && p2ProjY == i)
                        {
                            cout << "O";
                            drewProj = true;
                        }
                    }

                    if (drewProj == false)
                    {if(p1X == j && p1Y == i)
                        cout << "\xDB";
                    else if(p1X == j && p1Y+1 == i)
                        cout << "\xDB";
                    else if(p1X == j && p1Y+2 == i)
                        cout << "\xDB";
                    else if(p1X+1 == j && p1Y+1 == i)
                        cout << "\xC3";
                    else if(p2X == j && p2Y == i)
                        cout << "\xDB";
                    else if(p2X == j && p2Y+1 == i)
                        cout << "\xDB";
                    else if(p2X == j && p2Y+2 == i)
                        cout << "\xDB";
                    else if(p2X-1 == j && p2Y+1 == i)
                        cout << "\xB4";
                    else
                        cout << " ";
                    }
                }
                cout << endl;
            }

			for(int i = 0; i < width+1; i++)
				cout << "-";

            cout << endl << endl << left << setw(14) << "Player 1 HP: "
                 << player1HP << right << setw(width-16) << "Player 2 HP: " << player2HP << endl;

            if(player1HP <= 0 && player2HP <= 0)
            {
                cout << endl << "DRAW!";
                quit = true;
            }
            else if(player2HP <= 0)
            {
                cout << endl << "Player 1 wins!";
                quit = true;
            }
            else if(player1HP <= 0)
            {
                cout << endl << "Player 2 wins!";
                quit = true;
            }
        }
		void getInput()
		{
		    for(it = p1Projectiles.begin(); it != p1Projectiles.end(); it++)
                (*it)->Move();
            for(it = p2Projectiles.begin(); it != p2Projectiles.end(); it++)
                (*it)->Move();


            int p1X = p1->getX();
            int p1Y = p1->getY();
            int p2X = p2->getX();
            int p2Y = p2->getY();

            if(_kbhit())
            {
                char input = _getch();
                if(input == up1)
                    if(p1Y > 0)
                        p1->moveUp();
                if(input == down1)
                    if(p1Y < height - 3)
                        p1->moveDown();
                if(input == up2)
                    if(p2Y > 0)
                        p2->moveUp();
                if(input == down2)
                    if(p2Y < height - 3)
                        p2->moveDown();
                if(input == 'q')
                    quit = true;
            }
		}
		void checkCollision()
		{
		    int p1ProjX = p1Projectiles.front()->getX();
            int p1ProjY = p1Projectiles.front()->getY();
            int p2ProjX = p2Projectiles.front()->getX();
            int p2ProjY = p2Projectiles.front()->getY();

            int p1X = p1->getX();
            int p1Y = p1->getY();
            int p2X = p2->getX();
            int p2Y = p2->getY();

            for(int i = 0; i < 3; i++)
                if(p2ProjX == p1X +1)
                    if(p2ProjY == p1Y+i)
                    {
                        hitUpdate(p1);
                        delete p2Projectiles.front();
                        p2Projectiles.pop_front();
                    }

            for(int i = 0; i < 3; i++)
                if(p1ProjX == p2X - 1)
                    if(p1ProjY == p2Y+i)
                    {
                        hitUpdate(p2);
                        delete p1Projectiles.front();
                        p1Projectiles.pop_front();
                    }
            if((p1Projectiles.front()->getX()) == width-2)
            {
                delete p1Projectiles.front();
                p1Projectiles.pop_front();
            }

            if((p2Projectiles.front()->getX()) == 0)
            {
                delete p2Projectiles.front();
                p2Projectiles.pop_front();
            }
		}
        void run()
        {
            while (!quit)
            {
                drawGame();
                getInput();
                checkCollision();
            }
        }
};

int main()
{
	game fight(14, 40);
	fight.run();
    cout << endl << "press q to quit";
    char input;
    while(input != 'q')
    {
        input = getch();
    }

    return 0;
}
