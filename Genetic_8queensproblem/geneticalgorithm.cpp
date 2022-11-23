#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <fstream>
#include <ctime>
#include <windows.h>
#pragma comment (linker, "/subsystem:windows /entry:mainCRTStartup")

using namespace sf;
using namespace std;

#define MAX_LENGTH 1000
#define SIZE 8
#define height 100
#define width 100

typedef struct
{
	int data[SIZE];
	int f;
} Indidvidual;

typedef struct
{
	Indidvidual data[MAX_LENGTH];
	int size;
} Population;

typedef struct
{
	int data[SIZE][SIZE];
} Board;

void initIndividual(Population* P);
void addIndividual(Population* P, Indidvidual x);
void clearBoard(Board* B);
void clearConstrain(int constrain[SIZE][SIZE]);
void displayBoard(int B[SIZE][SIZE]);
void displayIndividual(Indidvidual x);
void individualtoBoard(Board* B, Indidvidual x);
void fitness(Indidvidual* x);
void randomdata(Population* P, int n);
void displayPopulation(Population P);
int random(int min, int max);
float random();
void crossover(Indidvidual c1, Indidvidual c2, Indidvidual* c3);
void mutate(Indidvidual* x);
int inspectIndividual(Indidvidual x);
int checkBoard(Population P, Indidvidual x);
void SA(Population P);

void initIndividual(Population* P)
{
	P->size = 0;
}

void addIndividual(Population* P, Indidvidual x)
{
	P->data[P->size] = x;
	P->size++;
}

void clearBoard(Board* B)
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			B->data[i][j] = 0;
		}
	}
}

void clearConstrain(int constrain[SIZE][SIZE])
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			constrain[i][j] = 0;
		}
	}
}

void displayBoard(int B[SIZE][SIZE])
{
	printf("Board:\n");
	int i, j;
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			if (B[i][j] != 0) {
				printf("%c ", 254);
			}
			else {
				printf("%d ", B[i][j]);
			}
		}
		printf("\n");
	}
}

void displayIndividual(Indidvidual x)
{
	for (int i = 0; i < SIZE; i++)
	{
		cout << x.data[i] << " ";
	}
	cout << " f=" << x.f << "\n";
}
void individualtoBoard(Board* B, Indidvidual x)
{
	for (int i = 0; i < SIZE; i++)
	{
		int num = x.data[i];
		int row = 8 - num;
		B->data[row][i] = 1;
	}
}

int random(int min, int max)
{
	return min + rand() % (max + 1 - min);
}

float random2()
{
	return (float(rand()) / float((RAND_MAX)));
}

void randomdata(Population* P)
{
	for (int i = 1; i <= 5; i++) {
		Indidvidual c1;
		for (int j = 0; j < SIZE; j++) {
			int value = random(1, 8);
			c1.data[j] = value;
		}
		fitness(&c1);
		//		displayIndividual(c1);
		addIndividual(P, c1);
	}
}

void fitness(Indidvidual* x)
{
	Board B;
	x->f = 0;
	clearBoard(&B);
	individualtoBoard(&B, *x);
	int pair = 7;


	for (int i = 0; i < SIZE - 1; i++)
	{
		int no_conflict = pair;
		int row = 8 - x->data[i];
		// kiem tra hang ngang
		for (int j = i + 1; j < SIZE; j++)
		{
			int col = j;
			if (B.data[row][col] == 1)
			{
				no_conflict--;
			}
		}
		// kiem tra xung dot cheo  phai tren 
		int k = row - 1;
		int j = i + 1;
		while (k >= 0 && j < SIZE)
		{
			if (B.data[k][j] == 1)
			{
				no_conflict--;
			}
			k--;
			j++;
		}
		// kiem tra xung dot cheo phai duoi
		k = row + 1;
		j = i + 1;
		while (k < SIZE && j < SIZE)
		{
			if (B.data[k][j] == 1)
			{
				no_conflict--;
			}
			k++;
			j++;
		}
		x->f += no_conflict;
		pair--;
	}
}

void displayPopulation(Population P)
{
	cout << "Quan the\n";
	for (int i = 0; i < P.size; i++)
	{
		Indidvidual x = P.data[i];
		displayIndividual(x);
	}
}

void crossover(Indidvidual c1, Indidvidual c2, Indidvidual* c3)
{
	for (int i = 0; i < SIZE; i++)
	{
		double pb = random2();
		if (pb < 0.5)
		{
			c3->data[i] = c1.data[i];
		}
		else
		{
			c3->data[i] = c2.data[i];
		}
	}
	fitness(c3);
}

void mutate(Indidvidual* x)
{
	int index = random(0, 7);
	int value = random(1, 8);
	x->data[index] = value;
	fitness(x);
}
int inspectIndividual(Indidvidual x)
{
	return x.f == 28;
}

int checkBoard(Population P, Indidvidual x)
{
	for (int i = 0; i < P.size; i++)
	{
		Indidvidual c1 = P.data[i];
		int check = 1;
		for (int j = 0; j < SIZE; j++)
		{
			if (c1.data[j] != x.data[j])
			{
				check = 0;
			}
		}
		if (check == 1)
		{
			return 1;
		}
	}
	return 0;
}

int daCoData = 0;
Indidvidual rs;
void hienthi() {

	RenderWindow window(VideoMode(width * 8, height * 8), "The Chess!");
	int rotation = 0;
	while (window.isOpen())
	{
		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
				window.close();
		}
		window.clear();
		if (daCoData == 0) {
			sf::Texture whiteBG;
			if (!whiteBG.loadFromFile("C:/Users/LENOVO/Desktop/images/white1.png"))
			{
				std::cerr << "load image white1 fail" << std::endl;
				exit(1);
			}
			sf::Texture loader1;
			if (!loader1.loadFromFile("C:/Users/LENOVO/Desktop/images/load1.png"))
			{
				std::cerr << "load image white1 fail" << std::endl;
				exit(1);
			}
			sf::Texture loader2;
			if (!loader2.loadFromFile("C:/Users/LENOVO/Desktop/images/load2.png"))
			{
				std::cerr << "load image loader fail" << std::endl;
				exit(1);
			}


			sf::RectangleShape backGround(sf::Vector2f(width * 8, height * 8));
			backGround.setPosition(0, 0);
			window.draw(backGround);

			sf::RectangleShape load1(sf::Vector2f(width, height));
			load1.setPosition((width * 4), (height * 4));
			load1.setTexture(&loader2);
			load1.setRotation(0 + rotation);
			window.draw(load1);

			sf::RectangleShape load2(sf::Vector2f(width, height));
			load2.setPosition((width * 4), (height * 4));
			load2.setTexture(&loader1);
			load2.setRotation(90 + rotation);
			window.draw(load2);

			load2.setTexture(&loader1);
			load2.setRotation(180 + rotation);
			window.draw(load2);

			load2.setTexture(&loader1);
			load2.setRotation(270 + rotation);
			window.draw(load2);

			rotation += 5;
		}
		else {
			Board B;
			clearBoard(&B);
			individualtoBoard(&B, rs);
			sf::Texture textureGreen;
			if (!textureGreen.loadFromFile("C:/Users/LENOVO/Desktop/images/green.png"))
			{
				std::cerr << "load image green fail" << std::endl;
				exit(1);
			}
			sf::Texture textureWhite;
			if (!textureWhite.loadFromFile("C:/Users/LENOVO/Desktop/images/white2.png"))
			{
				std::cerr << "load image white2 fail" << std::endl;
				exit(1);
			}
			sf::Texture textureQueeGreen;
			if (!textureQueeGreen.loadFromFile("C:/Users/LENOVO/Desktop/images/queen_green.png"))
			{
				std::cerr << "load image queen_green fail" << std::endl;
				exit(1);
			}
			sf::Texture textureQueenWhite;
			if (!textureQueenWhite.loadFromFile("C:/Users/LENOVO/Desktop/images/queen_white.png"))
			{
				std::cerr << "load image queen_white fail" << std::endl;
				exit(1);
			}

			for (int i = 0; i < SIZE; i++) {
				for (int j = 0; j < SIZE; j++) {
					int t = i + j;
					if (t % 2 == 0) {
						sf::RectangleShape greenBG(sf::Vector2f(100.f, 100.f));
						greenBG.setPosition(j * width, i * height);
						greenBG.setTexture(&textureGreen);
						window.draw(greenBG);

						if (B.data[i][j] == 1) {
							sf::RectangleShape queeGreen(sf::Vector2f(100.f, 100.f));
							queeGreen.setPosition(j * width, i * height);
							queeGreen.setTexture(&textureQueeGreen);
							window.draw(queeGreen);
						}

					}
					else {
						sf::RectangleShape whiteBG(sf::Vector2f(100.f, 100.f));
						whiteBG.setPosition(j * 100, i * 100);
						whiteBG.setTexture(&textureWhite);
						window.draw(whiteBG);

						if (B.data[i][j] == 1) {
							sf::RectangleShape queenWhite(sf::Vector2f(100.f, 100.f));
							queenWhite.setPosition(j * 100, i * 100);
							queenWhite.setTexture(&textureQueenWhite);
							window.draw(queenWhite);
						}
					}

				}
			}
		}
		window.display();
		Sleep(10);
	}
}

void SA(Population P)
{
	int index1;
	int index2;
	while (1)
	{
		index1 = random(0, P.size - 1);
		index2 = random(0, P.size - 1);
		if (index1 == index2)
		{
			continue;
		}
		Indidvidual c1 = P.data[index1];
		Indidvidual c2 = P.data[index2];
		Indidvidual c3;
		//lai c1,c2 ->c3
		crossover(c1, c2, &c3);
		//dot bien c3
		mutate(&c3);
		if (inspectIndividual(c3))
		{
			rs = c3;
			return;
		}
		if (checkBoard(P, c3) == 0)
		{
			addIndividual(&P, c3);
		}
	}
}

int main()
{

	srand((int)time(NULL));
	Population Q;
	initIndividual(&Q);
	randomdata(&Q);

	sf::Thread thread1(&SA, Q);
	sf::Thread thread2(&hienthi);

	thread1.launch();
	thread2.launch();

	thread1.wait();
	daCoData = 1;

	thread2.wait();

	return 0;
}