#include "Plants&Zombies.h"
#include <cstdlib>	//for random
#include <ctime>	//time for random


void Plants::new_plant(char cata, char* nam, int cos, int hp, int cd, int rew)	//coin plants
{
	catagory= cata;
	name= nam;
	cost= cos;
	maxlife= hp;
	nowlife= hp;
	recharge= cd;
	needtime= recharge;
	reward= rew;
}

void Plants::new_plant(char cata, char* nam, int cos, int hp, int amount)			//shoot & heal plants
{
	catagory= cata;
	name= nam;
	cost= cos;
	maxlife= hp;
	nowlife= hp;
	if (cata=='S')
	{
		damage= amount;
	}
	else if(cata=='H')
	{
		heal= amount;
	}
}

void Plants::new_plant(char cata, char* nam, int cos, int hp)				//bomb plants
{
	catagory= cata;
	name= nam;
	cost= cos;
	maxlife= hp;
	nowlife= hp;
}

void Plants::player_react()
{
	switch (catagory)
	{
		case 'C':
			getcoin();
			break;
		case 'S':			
			break;
		case 'B':			
			break;
		case 'H':
			healing();
			break;
		default:
			break;
	}
}

void Plants::zombie_react(Zombies* zombie)
{
	switch (catagory)
	{
		case 'C':			
			break;
		case 'S':
			shoot(zombie);		
			break;
		case 'B':
			sacrifice(zombie);		
			break;
		case 'H':			
			break;
		default:
			break;
	}
}

void Plants::getcoin()		//coin plant
{
	needtime-=1;
	if (needtime==0)	//recharge is over
	{
		//player_money+= reward		//undone
		needtime= recharge;
	}
}
void Plants::shoot(Zombies* zombie)		//shooter plant
{
	zombie->hp-= damage;
	
}

void Plants::sacrifice(Zombies* zombie)	//bomb plant
{
	zombie->hp-= maxlife;
	if (zombie->hp<=0)
	{
		zombie->death();
	}
	death();
}

void Plants::healing()		//heal plant
{
	/*
	for (int i=0; i<land; i++)
	{
		land[i].plant.nowlife+= heal;
		if (land[i].plant.nowlife>maxlife)
		{
			nowlife= maxlife;
		}
	}
	*/
}

void Plants::death()
{
	delete this;
	//remove this from the map too
}

void Zombies::attack(Plants* plant)
{
	plant->nowlife-= atk;
	if (plant->nowlife<=0)
	{
		plant->death();
	}
}

void Zombies::death()
{
	delete this;
}

void Zombies::move()
{
	std::srand(std::time(NULL));
	
	int step= minstep+ std::rand()%(maxstep-minstep+1);
	
	//zombie->place+= step;
	//if (zomebie->place>=lands)
	//{	zombie->place-= lands; } 
}
