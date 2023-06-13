#ifndef PLANTSANDZOMBIES_
#define PLANTSANDZOMBIES_

#include <string>
class Zombies;

class Plants
{
	friend class Zombies;
	public:
		char catagory= ' ';
		std::string name;
		int cost= 0, maxhp= 0, nowhp= 0;
	public:
		//void new_plant(char, char*, int, int, int, int);
		virtual void show() const {};
		virtual void player_react(){};
		virtual void zombie_react(Zombies*){};
		void death();
};

class Sunflower : public Plants
{
	friend class Zombies;
	public:
		int maxcd= 0, cd= 0, reward= 0;
	public:
		Sunflower();
		Sunflower(const std::string);
		virtual void show() const override;
		virtual void player_react() override;
};

class Shooter : public Plants
{
	friend class Zombies;
	public:
		int damage= 0;
	public:
		Shooter();
		Shooter(const std::string);
		virtual void show() const override;
		virtual void zombie_react(Zombies*) override;
};

class Bomber : public Plants
{
	friend class Zombies;
	public:
		Bomber(const std::string);
		virtual void show() const override;
		virtual void zombie_react(Zombies*) override;
		int life;
};

class Healer : public Plants
{
	friend class Zombies;
	public:
		int heal= 0;
	public:
		Healer(const std::string);
		virtual void show() const override;
		virtual void player_react() override;
};


class Zombies
{
	friend class Plants;
	friend class Shooter;
	friend class Bomber;
	private:
		int id;
		int hp= 40, atk= 15;
		int minstep= 1, maxstep= 3;
	public:
		void attack(Plants*);
		void death();
		void move();
		Zombies(int id) : id(id) {}
	    int getId() const {
	        return id;
	    }
};

#endif
