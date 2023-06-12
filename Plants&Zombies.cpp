#include "Plants&Zombies.h"
#include <iostream>
#include <cstdlib>	//for random
#include <ctime>	//time for random

/*
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
*/

void Plants::death()
{
	std::cout << "Plant " << name << "is dead!" << std::endl;
	delete this;
}

void Sunflower::show() const 
{
	std::cout << name << " $" << cost << " HP:" << maxhp << " - give $" << reward << " every " << maxcd << " rounds" << std::endl;
}

void Sunflower::player_react()
{
	if (cd>0)
	{
		std::cout << "You still need " << cd << " visit to earn money." << std::endl;
	}
	else
	{
		// player->money+= reward;
		std::cout << "You have earned $" << reward << "! Now you have $" << 100 << "." << std::endl;
		//																//	^this need to react to player's data->money
		cd= maxcd;
	}
	cd-=1;
}

void Shooter::show() const 
{
	std::cout << name << " $" << cost << " HP:" << maxhp << " - give " << damage << " damage points" << std::endl;
}

void Shooter::zombie_react(Zombies *zombie)
{
	std::cout << name << " gives " << damage << " damage to the zombie!" << std::endl;
	zombie->hp-= damage;
	if (zombie->hp<0)
	{
		zombie->death();
	}
}

void Bomber::show() const 
{
	std::cout << name << " $" << cost << " HP:" << maxhp << " - give " << maxhp << " damage points" << std::endl;
}

void Bomber::zombie_react(Zombies *zombie)
{
	std::cout << name << " gives " << maxhp << " damage to the zombie!" << std::endl;
	zombie->hp-= maxhp;
	if (zombie->hp<0)
	{
		zombie->death();
	}
	this->death();
}

void Healer::show() const 
{
	std::cout << name << " $" << cost << " HP:" << maxhp << " - give all your plants " << heal << " HP back." << std::endl;
}

void Healer::player_react()
{
	//need react to map
	/*
	for (int i=0; i<lands; i+=1)
	{
		land.plant.hp+= heal;
	}
	*/
}

void Zombies::attack(Plants* plant)
{
	std::cout << "Zombie eats plant " << plant->name << " and cause damage " << atk << "." << std::endl;
	plant->nowhp-= atk;
	if (plant->nowhp<=0)
	{
		plant->death();
	}
}

void Zombies::death()
{
	std::cout << "Zombie is killed!" << std::endl;
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
