#include "SFML\Graphics.hpp"

#include<iostream>
#include<fstream>
#include<math.h>

#include<stdlib.h>
using namespace std;
using namespace sf;
int mat[100][100], exterior[100][100];
int i, j, coloane, linii, nr_bombe, ok,flag_set,square;
void initializare_exterior(int exterior[100][100], int linii, int coloane)
{
	for (int i = 0; i < linii; i++)
		for (int j = 0; j < coloane; j++)
			exterior[i][j] = 0;
	cout << "Succesiful initialization-Exterior-"<<endl;
}
void intitializare_interior(int mat[100][100], int linii, int coloane)
{
	for (int i = 0; i < linii; i++)
		for (int j = 0; j < coloane; j++)
			mat[i][j] = 0;
	cout << "Succesiful initialization -Interior-"<<endl;
}
void afisare(int mat[100][100])
{
	for (int i = 0; i < linii; i++)
	{
		for (int j = 0; j < coloane; j++)
			cout << mat[i][j] << '\t';
		cout << endl << endl;
	}
	cout << endl;
}
void generare(int mat[100][100], int coloane, int linii, int nr_bombe)
{
	int nr = 0;
	while (nr < nr_bombe)
	{
		i = rand() % linii + 0;
		j = rand() % coloane + 0;
		if (mat[i][j] != -1)
		{
			mat[i][j] = -1;
			nr++;
		}
	}
	cout << endl;
	for(int linie=0;linie<linii;linie++)
		for (int coloana= 0; coloana < coloane; coloana++)
		{
			nr = 0;
			if (mat[linie][coloana] == -1)
				nr = -1;
			else
			{
				if (mat[linie - 1][coloana - 1] == -1)
					nr++;
				if (mat[linie - 1][coloana] == -1)
					nr++;
				if (mat[linie - 1][coloana + 1] == -1)
					nr++;
				if (mat[linie][coloana - 1] == -1)
					nr++;
				if (mat[linie][coloana + 1] == -1)
					nr++;
				if (mat[linie + 1][coloana - 1] == -1)
					nr++;
				if (mat[linie + 1][coloana] == -1)
					nr++;
				if (mat[linie + 1][coloana + 1] == -1)
					nr++;
			}
			mat[linie][coloana] = nr;
		}
	for (int i = 0; i < linii; i++)
		for (int j = 0; j < coloane; j++)
			mat[i][j] = mat[i][j] + 4;
}
void afisare_exterior()
{
	for (int i = 0; i < linii; i++)
	{
		for (int j = 0; j < coloane; j++)
			cout << exterior[i][j] << '\t';
		cout << endl << endl;
	}
	cout << endl;
}
void cautare(int linie, int coloana, int exterior[100][100])
{
	if (linie >= 0 && coloana >= 0 && linie < linii && coloana < coloane)
	{
		if (exterior[linie][coloana] == 0)
		{
			exterior[linie][coloana] =mat[linie][coloana];
			square--;
			cout << endl << "Square modif in Cautare";
			if (exterior[linie][coloana] == 4)
			{
				cautare(linie - 1, coloana - 1, exterior);
				cautare(linie - 1, coloana, exterior);
				cautare(linie - 1, coloana + 1, exterior);
				cautare(linie, coloana - 1, exterior);
				cautare(linie, coloana + 1, exterior);
				cautare(linie + 1, coloana - 1, exterior);
				cautare(linie + 1, coloana, exterior);
				cautare(linie + 1, coloana + 1, exterior);
			}
		}
	}
}
void copiere()
{
	for (int i = 0; i < linii; i++)
		for (int j = 0; j < coloane; j++)
			exterior[i][j] = mat[i][j];
}
void restart_game()
{
	initializare_exterior(exterior, linii, coloane);
	intitializare_interior(mat, linii, coloane);
	generare(mat, coloane, linii, nr_bombe);
	square = linii*coloane;
	flag_set = nr_bombe;
	ok = 0;
}
int main(int argc, char **args)
{
	int pozitie = 64;
	coloane = 10;
	linii = 10;
	nr_bombe = 10;
	ok = 0;
	square = linii*coloane;
	flag_set = nr_bombe;
	initializare_exterior(exterior, linii, coloane);
	intitializare_interior(mat, linii, coloane);
	generare(mat,coloane, linii, nr_bombe);
	RenderWindow window(VideoMode(640, 680), "Game",Style::Close | Style::Titlebar);
	Texture t;
	Clock timeClock;
	if (!t.loadFromFile("t/tileset.png"))
	{
		window.close();
	}
	else
	{
		cout << "Load images succes" << endl;
	}
	Sprite s;
	s.setTexture(t);
	Font font;
	font.loadFromFile("fontGame.ttf");
	String timeString = "Time: ";
	String flagString= "Steaguri: ";
	String restart = "Restart";
	String overg = "Game over!";
	String game_win1 = "Congratulations!";
	String game_win2 = "You win!";
	float currentTime = 0;
	Text time(timeString,font);
	time.setPosition(50, 640);
	time.setCharacterSize(30);
	time.setFillColor(Color::Black);
	Text flag(flagString, font);
	flag.setPosition(440, 640);
	flag.setCharacterSize(30);
	flag.setFillColor(Color::Black);
	RectangleShape rectangle2(Vector2f(140, 40));
	rectangle2.setFillColor(Color(255, 200, 200));
	rectangle2.setPosition(245, 640);
	RectangleShape rectangle(Vector2f(130, 30));
	rectangle.setFillColor(Color(255, 128, 192));
	rectangle.setPosition(250, 645);
	Text reset(restart, font);
	reset.setPosition(270, 640);
	reset.setCharacterSize(30);
	reset.setFillColor(Color::Black);
	Text over(overg, font);
	over.setPosition(90, 250);
	over.setCharacterSize(100);
	over.setFillColor(Color::Red);
	Text win1(game_win1, font);
	win1.setPosition(20, 250);
	win1.setCharacterSize(80);
	win1.setFillColor(Color::Red);
	Text win2(game_win2, font);
	win2.setPosition(150, 320);
	win2.setCharacterSize(80);
	win2.setFillColor(Color::Red);
	while (window.isOpen())
	{ 
		Vector2i pos = Mouse::getPosition(window);
		int x = pos.x / pozitie;
		int y = pos.y / pozitie;
		Event event;
		Time seconds = timeClock.getElapsedTime();
		float deltaTime = seconds.asSeconds();
		timeClock.restart().asSeconds();
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
			if (event.type == Event::MouseButtonPressed)
			{
				cout << "x: " <<x<< "y: "<<y;
				if (event.key.code == Mouse::Left)
				{
					if (mat[x][y] == 3)
					{
						cout << "Game Over" << endl;
						ok = 1;
						copiere();
					}
					else
						if (mat[x][y] == 4)
						{
							cout << "Cautare called successful" << endl;
							cautare(x, y, exterior);
						}
						else
							if (x >= 3 && x <= 5 && y == 10)
							{
								currentTime = 0;
								restart_game();
							}
							else
							{

							exterior[x][y] = mat[x][y];
							square--;
							//cout << "Square modificated" << endl;
							}
						
				}
				else
					if (event.key.code == Mouse::Right)
					{

						if (exterior[x][y] == 0 && flag_set > 0)
						{
							exterior[x][y] = 2;
							cout << "Flag set" << endl;
							flag_set--;
							cout << "bomb left: " << flag_set << endl;
						}
						else
							if (exterior[x][y] == 2)
							{
								exterior[x][y] = 0;
								cout << "Flag removed" << endl;
								flag_set++;
								cout << "bomb left: " << flag_set << endl;
							}
							else
								cout << "Error! Check the numbers of flags!" << endl;
					}
				if (square == nr_bombe && flag_set == 0)
				{
					cout << "You win!";
					ok = 2;
				}
			}
		}
		window.clear(Color(255,175,175,0));
		for (int i = 0; i < linii; i++)
			for (int j = 0; j < coloane; j++)
			{
				if(exterior[i][j]==4)
					exterior[i][j]=mat[i][j];
				s.setTextureRect(IntRect(exterior[i][j]*pozitie, 0, pozitie, pozitie));
				s.setPosition(i*pozitie, j*pozitie);
				window.draw(s);
			}
		currentTime += deltaTime;
		if (ok == 0)
		{
			timeString = "Time : " + to_string((int)currentTime);
			flagString = "Steaguri: " + to_string(flag_set);
		}
		else
		{
			if (ok == 2)
			{
				window.draw(win1);
					window.draw(win2);
			}
			else
				window.draw(over);
			
		}
		time.setString(timeString);
		window.draw(time);
		flag.setString(flagString);
		window.draw(flag);
		window.draw(rectangle2);
		window.draw(rectangle);
		window.draw(reset);
		window.display();
	}
	return 0;

}
