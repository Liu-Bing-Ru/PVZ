#ifndef PLANTSANDZOMBIES_
#define PLANTSANDZOMBIES_

#include <string>
class Zombies;

class Plants
{
	friend class Zombies;
	protected:
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
	private:
		int maxcd= 0, cd= 0, reward= 0;
	public:
		Sunflower(const std::string&);
		virtual void show() const override;
		virtual void player_react() override;
};

class Shooter : public Plants
{
	friend class Zombies;
	private:
		int damage= 0;
	public:
		Shooter(const std::string&);
		virtual void show() const override;
		virtual void zombie_react(Zombies*) override;
};

class Bomber : public Plants
{
	friend class Zombies;
	public:
		Bomber(const std::string&);
		virtual void show() const override;
		virtual void zombie_react(Zombies*) override;
};

class Healer : public Plants
{
	friend class Zombies;
	private:
		int heal= 0;
	public:
		Healer(const std::string&);
		virtual void show() const override;
		virtual void player_react() override;
};


class Zombies
{
	friend class Plants;
	friend class Shooter;
	friend class Bomber;
	private:
		int hp= 40, atk= 15;
		int minstep= 1, maxstep= 3;
	public:
		void attack(Plants*);
		void death();
		void move();
};

#endif
