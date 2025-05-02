#ifndef AEROASSAULT_H
#define AEROASSAULT_H

#include <SFML/Graphics.hpp>
#include "soundmanager.h"
using namespace sf;
using namespace std;

//a side quest in which player has to destroy enemy planes
//destroy all to gain maximum points

class Bullet {
public:
	Texture tex;
	Sprite sprite;
	float speed = 1;

	Bullet(std::string filePath) {
		tex.loadFromFile(filePath);
		sprite.setTexture(tex);
		sprite.setPosition(120, 233); //120,233
		sprite.setScale(0.09, 0.125);
	}

	void move(int tempX, int tempY) {
		float delta_x = 0, delta_y = 0;
		delta_x += 1;
		delta_x *= speed;
		if (sprite.getPosition().y < 0)
			sprite.setPosition(tempX + 80.0f, tempY + 40.0f);
		else if (sprite.getPosition().y > 720) {
			sprite.setPosition(tempX + 80.0f, tempY + 40.0f);
		}
		else if (sprite.getPosition().x > 1280)
			sprite.setPosition(tempX, tempY);
		else if (sprite.getPosition().x < 0)
			sprite.setPosition(tempX + 80.0f, tempY + 40.0f);
		sprite.move(delta_x, delta_y);
	}


};

class EnemyBullet {
public:
	Texture tex;
	Sprite sprite;
	int tempX;
	int tempY;
	float speed = 1;

	EnemyBullet(std::string filePath, double x, double y) {
		tex.loadFromFile(filePath);
		sprite.setTexture(tex);
		sprite.setPosition(x, y); //120,233
		sprite.setScale(1.5, 2);
		tempX = x;
		tempY = y;
	}

	void move(bool& out) {
		float delta_x = 0, delta_y = 0;
		delta_x -= 1;
		delta_x *= speed;
		if (sprite.getPosition().y < 0)
			sprite.setPosition(tempX, tempY);
		else if (sprite.getPosition().y > 720) {
			sprite.setPosition(tempX, tempY);
		}
		else if (sprite.getPosition().x > 1280)
			sprite.setPosition(tempX, tempY);
		else if (sprite.getPosition().x < 0) {
			sprite.setPosition(tempX, tempY);
			out = true;
		}
		sprite.move(delta_x, delta_y);
	}
};

class Enemy
{
public:
	Texture tex;
	Sprite sprite;
	float speed = 0.3;
	EnemyBullet* eB;

	Enemy(std::string png_path, double x, double y)
	{
		tex.loadFromFile(png_path);
		sprite.setTexture(tex);
		sprite.setPosition(x, y);
		sprite.setScale(1.5, 1.5);
		eB = new EnemyBullet("img/enemy-bullet.png", x + 20, y + 33);
	}

	void setEnemies(vector<Enemy*>& e) {
		Enemy* e1 = new Enemy("img/enemy.png", 1120, 0);
		e.push_back(e1);

		e1 = new Enemy("img/enemy.png", 960, 100);
		e.push_back(e1);

		e1 = new Enemy("img/enemy.png", 800, 200);
		e.push_back(e1);

		e1 = new Enemy("img/enemy.png", 1120, 200);
		e.push_back(e1);

		e1 = new Enemy("img/enemy.png", 640, 300);
		e.push_back(e1);

		e1 = new Enemy("img/enemy.png", 960, 300);
		e.push_back(e1);

		e1 = new Enemy("img/enemy.png", 800, 400);
		e.push_back(e1);

		e1 = new Enemy("img/enemy.png", 1120, 400);
		e.push_back(e1);

		e1 = new Enemy("img/enemy.png", 960, 500);
		e.push_back(e1);

		e1 = new Enemy("img/enemy.png", 1120, 600);

		e.push_back(e1);
	}
};

class Player {
public:
	Texture tex;
	Sprite sprite;
	float speed = 0.75;

	Player(std::string filePath) {
		tex.loadFromFile(filePath);
		sprite.setTexture(tex);
		sprite.setPosition(100, 200);
		sprite.setScale(0.25, 0.25);
	}

	void move(std::string s) {
		float delta_x = 0, delta_y = 0;
		if (s == "l")
			delta_x -= 1;
		//move the player left

		else if (s == "r")
			delta_x += 1;
		//move the player right
		else if (s == "u")
			delta_y = -1;
		else if (s == "d")
			delta_y += 1;

		delta_x *= speed;
		delta_y *= speed;

		if (sprite.getPosition().y < 0)
		{
			sprite.setPosition(sprite.getPosition().x, 720);
		}
		else if (sprite.getPosition().x < 0)
		{
			sprite.setPosition(1280, sprite.getPosition().y);
		}
		else if (sprite.getPosition().y > 720)
		{
			sprite.setPosition(sprite.getPosition().x, 0);
		}
		else if (sprite.getPosition().x > 1280)
		{
			sprite.setPosition(0, sprite.getPosition().y);
		}

		sprite.move(delta_x, delta_y);

	}
};

class AeroAssault{
public:
	Texture tex;
	Sprite background;
	Player* p;
	Bullet* b;
	vector<Enemy*> e;
	FloatRect playerBounds;
	FloatRect bulletBounds;
	FloatRect enemyBulletBounds;
	vector<FloatRect> enemyBounds;
	vector<bool> enemyBool;
	double x, y;
	int enemyCount;
	int score;
	bool enemyBulletOut;
	int deadEnemyCount;
	int deadIndex[10];
	bool deadIndexBool;
	bool gameOver;
	bool collision;
	Font font;
	Text scoring;

	AeroAssault() {
		tex.loadFromFile("img/aerobackground.jpg");
		background.setTexture(tex);
		p = new Player("img/player.png");
		b = new Bullet("img/bullet.png");
		x = 800;
		y = 0;
		enemyCount = 10;
		setEnemies(e);
		collision = false;
		enemyBulletOut = false;
		deadEnemyCount = 0;
		for (int i = 0; i < 10; i++) {
			deadIndex[i] = -1;
			bool a = true;
			enemyBool.push_back(a);
		}
		deadIndexBool = false;
		score = 0;
		gameOver = false;
		playerBounds = { -1.0f, -1.0f, 0.0f, 0.0f };
		bulletBounds = { -1.0f, -1.0f, 0.0f, 0.0f };
		enemyBulletBounds = { -1.0f, -1.0f, 0.0f, 0.0f };
		gameOver = false;
		font.loadFromFile("fonts/Squartiqa4F.ttf");
		scoring.setCharacterSize(20);
		scoring.setFont(font);
		scoring.setPosition(70, 683);
		scoring.setFillColor(Color::Yellow);
	}

	void gameRun(RenderWindow& window, int& points) {
		srand(100);
		int index = rand() % enemyCount;
		int prevIndex = -1;
		Event E;
		while (window.isOpen())
		{
			while (window.pollEvent(E))
			{
				if (E.type == Event::Closed)
					window.close();
			}

			checkEnemyBulletOut(index, prevIndex, deadIndexBool);

			if (Keyboard::isKeyPressed(Keyboard::Left)) //If left key is pressed
				p->move("l");    // Player will move to left
			if (Keyboard::isKeyPressed(Keyboard::Right)) // If right key is pressed
				p->move("r");  //player will move to right
			if (Keyboard::isKeyPressed(Keyboard::Up)) //If up key is pressed
				p->move("u");    //player will move upwards
			if (Keyboard::isKeyPressed(Keyboard::Down)) // If down key is pressed
				p->move("d");  //player will move downwards

			if (deadEnemyCount == 10) {
				gameOver = true;
			}

			b->move(p->sprite.getPosition().x + 20, p->sprite.getPosition().y + 33);
			if (e[index] != nullptr) {
				e[index]->eB->move(enemyBulletOut);
			}

			setBulletAndEnemyBounds();
			checkPlayerBulletEnemyCollision();
			checkEnemyBulletPlayerCollision(index);
			scoring.setString("Score: " + to_string(score));

			if (gameOver) {
				gameOverScreen(window, points);
				return;
			}
			drawEverything(window);
		}

	}

	void setEnemies(vector<Enemy*>& e) {
		Enemy* e1 = new Enemy("img/enemy.png", 1120, 0);
		e.push_back(e1);

		e1 = new Enemy("img/enemy.png", 960, 100);
		e.push_back(e1);

		e1 = new Enemy("img/enemy.png", 800, 200);
		e.push_back(e1);

		e1 = new Enemy("img/enemy.png", 1120, 200);
		e.push_back(e1);

		e1 = new Enemy("img/enemy.png", 640, 300);
		e.push_back(e1);

		e1 = new Enemy("img/enemy.png", 960, 300);
		e.push_back(e1);

		e1 = new Enemy("img/enemy.png", 800, 400);
		e.push_back(e1);

		e1 = new Enemy("img/enemy.png", 1120, 400);
		e.push_back(e1);

		e1 = new Enemy("img/enemy.png", 960, 500);
		e.push_back(e1);

		e1 = new Enemy("img/enemy.png", 1120, 600);

		e.push_back(e1);
	}

	void checkEnemyBulletOut(int& index, int& prevIndex, bool& deadIndexBool) {
		if (enemyBulletOut) {
			while (index == prevIndex || deadIndexBool) {
				index = rand() % enemyCount;
				for (int i = 0; i < enemyCount; i++) {
					if (index == deadIndex[i]) {
						deadIndexBool = true;
						break;
					}
					deadIndexBool = false;
				}

			}
			enemyBulletOut = false;
		}
		prevIndex = index;
	}

	void setBulletAndEnemyBounds() {
		bulletBounds = b->sprite.getGlobalBounds();
		for (int i = 0; i < enemyCount; i++) {
			if (e[i] != nullptr) {
				FloatRect bounds = e[i]->sprite.getGlobalBounds();
				enemyBounds.push_back(bounds);
			}
			else {
				enemyBounds[i] = { -1.0f, -1.0f, 0.0f, 0.0f };
			}
		}
	}

	void checkPlayerBulletEnemyCollision() {
		for (int i = 0; i < enemyCount; i++) {
			if (bulletBounds.intersects(enemyBounds[i])) {
				e[i] = nullptr;
				b->sprite.setPosition(p->sprite.getPosition().x + 20, p->sprite.getPosition().y + 33);
				enemyBounds[i] = { -1.0f, -1.0f, 0.0f, 0.0f };
				enemyBool[i] = false;
				deadEnemyCount += 1;
				deadIndex[i] = i;
				score += 10;
			}
		}
	}

	void checkEnemyBulletPlayerCollision(int index) {
		playerBounds = p->sprite.getGlobalBounds();
		if (e[index] != nullptr) {
			enemyBulletBounds = e[index]->eB->sprite.getGlobalBounds();
		}

		if (enemyBulletBounds.intersects(playerBounds)) {
			gameOver = true;
		}
	}

	void drawEverything(RenderWindow& window) {
		window.clear();
		window.draw(background);
		window.draw(b->sprite);
		window.draw(p->sprite);

		for (auto& enemy : e) {
			if (enemy != nullptr) {
				window.draw(enemy->eB->sprite);
				window.draw(enemy->sprite);
			}
		}
		window.draw(scoring);
		window.display();
	}

	void gameOverScreen(RenderWindow& window, int& points) {
		while (gameOver) {
			window.clear();
			window.draw(background);
			scoring.setCharacterSize(50);
			scoring.setPosition(500, 320);
			scoring.setString("Final Score: " + to_string(score));
			window.draw(scoring);
			window.display();
			if (Keyboard::isKeyPressed(Keyboard::R)) {
				points += score;
				return;
			}
		}
	}
};

#endif
