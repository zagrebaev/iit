#include <iostream> 
using namespace std;

class Character {
protected:
	int damage;
	int coordinate;
	int range;

	virtual void atack(Character* ch) {};
	void stepRight() {
		cout << "Иду вправо\n";
		this->coordinate += 1;
	};
	void stepLeft() {
		cout << "Иду влево\n";
		this->coordinate -= 1;
	};
public:
	int health = 100;
	void getDamage(int dam) {
		health -= dam;
	}

	int giveCoord() {
		return coordinate;
	}

	virtual void chooseAction(int dis, Character* me, Character* enemy) {};

};


class Archer : public Character {
private:
	void atack(Character* ch) {
		cout << "Атакую!\n";
		ch->getDamage(damage);
	}

public:
	Archer(int dam, int ran) {
		damage = dam;
		range = ran;
		coordinate = 0;
	}

	void chooseAction(int dis, Character* me, Character* enemy) override {
		cout << "Мое здоровье: " << health << endl;
		if (dis > range)
			if (dis > 0) stepRight();
			else stepLeft();
		else if (me->health < enemy->health) {
			if (dis < 0) {
				atack(enemy);
				stepRight();
			}
			else { 
				atack(enemy);
				stepLeft(); 
			}
		}
		else atack(enemy);
	}

};

class Paladin : public Character {
private:
	void atack(Character* ch) {
		cout << "Атакую и лечусь!\n";
		ch->getDamage(damage);
		health += 3;
	}
	void heal() {
		cout << "Лечусь!\n";
		health += 5;
	}

public:
	Paladin(int dam, int ran) {
		damage = dam;
		range = ran;
		coordinate = 9;
	}
	void chooseAction(int dis, Character* me, Character* enemy) override {
		cout << "Мое здоровье: " << health << endl;
		if (dis > range)
			if (dis > 0) stepLeft();
			else stepRight();
		else if (enemy->health - me->health > 10 ) {
			heal();
		}
		else atack(enemy);
	}
};

int main()
{
	setlocale(LC_ALL, "russian");
	Character* arch = new Archer(7, 3);
	Character* pal = new Paladin(6, 1);
	int dis = 0;
	int iter = 1;
	while (arch->health > 0 && pal->health > 0) {
		cout << "Номер хода: " << iter++ << endl;
		dis = pal->giveCoord() - arch->giveCoord();
		cout << "Лучник:\n" << "dis" << dis << endl;
		arch->chooseAction(dis, arch, pal);
		dis = pal->giveCoord() - arch->giveCoord();
		cout << "Паладин:\n" << "Дистанция до цели: " << dis << endl;
		pal->chooseAction(dis, pal, arch);
		cout << endl << endl;
		
	}

}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки" 
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку" 

// Советы по началу работы 
// 1. В окне обозревателя решений можно добавлять файлы и управлять ими. 
// 2. В окне Team Explorer можно подключиться к системе управления версиями. 
// 3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения. 
// 4. В окне "Список ошибок" можно просматривать ошибки. 
// 5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода. 
// 6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.