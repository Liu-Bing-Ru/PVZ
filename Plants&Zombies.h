#ifndef PLANTSANDZOMBIES_
#define PLANTSANDZOMBIES_

class Zombies;

class Plants
{
	friend class Zombies;
	private:
		char catagory= ' ', *name= nullptr;
		int cost= 0, maxlife= 0, nowlife= 0;
		int recharge= 0, needtime= 0, reward= 0;	//for coin plants
		int damage= 0;		//for shooter plants
		int heal= 0;		//for heal plants
		
	public:
		void new_plant(char, char*, int, int, int, int);	//coin plants
		void new_plant(char, char*, int, int, int);			//shoot & heal plants
		void new_plant(char, char*, int, int);				//bomb plants
		void player_react();
		void zombie_react(Zombies*);
		void getcoin();		//coin plant
		void shoot(Zombies*);		//shooter plant
		void sacrifice(Zombies*);	//bomb plant
		void healing();		//heal plant
		void death();
};

class Zombies
{
	friend class Plants;
	private:
		int hp= 40, atk= 15;
		int minstep= 1, maxstep= 3;
	public:
		void attack(Plants*);
		void death();
		void move();
};

#endif
