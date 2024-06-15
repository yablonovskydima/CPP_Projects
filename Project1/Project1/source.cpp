#include <iostream>
#include <vector>
#include <Windows.h>
using namespace std;

bool ENEMYHIT = false;
bool HIT = false;
int SHIPCOUNT = 10;
int ENEMY_SHIPCOUNT = 10;
bool ISGAME = true;
bool DIFFICULTY;


class Ship
{
public:
	int x, y;
	int deck;
	bool ishorizontal = true;
	vector<vector<int>> deck_coords;
	Ship()
	{
		deck = 1;
	}

	void set_decks(int decks)
	{
		deck = decks;
		deck_coords.resize(deck);
		for (size_t i = 0; i < deck; i++)
		{
			deck_coords[i].resize(2);
		}
	}

};

class Field
{
public:
	int arr[10][10];
	int dir = 0, x, y, step = 1;
	bool isthereship = false;

	Field()
	{
		for (size_t i = 0; i < 10; i++)
		{
			for (size_t j = 0; j < 10; j++)
			{
				arr[i][j] = 0;
			}
		}
	}

	void show_enemy()
	{
		char a = 'A';
		cout << "    ";
		for (size_t i = 0; i < 10; i++)
		{

			cout << a << " ";
			a++;
		}
		cout << endl << endl;
		for (size_t i = 0; i < 10; i++)
		{
			if (i == 9) { cout << i + 1 << "  "; }
			else { cout << i + 1 << "   "; }

			for (size_t j = 0; j < 10; j++)
			{
				if (i == 0 && j == 0 && arr[i][j] == 3) cout << "x ";
				else if (arr[i][j] == 3 && i != 0 && j != 0) { cout << "X "; }
				else if (arr[i][j] == 5) { cout << "x "; }
				else if (arr[i][j] == 4) { cout << "x "; }
				else { cout << "* "; }
			}
			cout << endl;
		}
	}

	void show()
	{
		char a = 'A';
		cout << "    ";
		for (size_t i = 0; i < 10; i++)
		{

			cout << a << " ";
			a++;
		}
		cout << "\n\n";

		for (size_t i = 0; i < 10; i++)
		{
			if (i == 9) { cout << i + 1 << "  "; }
			else { cout << i + 1 << "   "; }

			for (size_t j = 0; j < 10; j++)
			{
				cout << arr[i][j] << " ";
			}
			cout << endl;
		}
	}

	void show_ingame()
	{
		char a = 'A';
		cout << "    ";
		for (size_t i = 0; i < 10; i++)
		{

			cout << a << " ";
			a++;
		}
		cout << "\n\n";

		for (size_t i = 0; i < 10; i++)
		{
			if (i == 9) { cout << i + 1 << "  "; }
			else { cout << i + 1 << "   "; }

			for (size_t j = 0; j < 10; j++)
			{
				if (arr[i][j] == 0 || arr[i][j] == 2 || arr[i][j] == 5) { cout << "* "; }
				else if (arr[i][j] == 3) { cout << "X "; }
				else if (arr[i][j] == 4) { cout << "x "; }
				else { cout << "# "; }
			}
			cout << endl;
		}
	}

	void shoot()
	{
		system("cls");
		cout << "Enemy's field: " << endl;
		this->show_enemy();
		int _x = 0, _y;
		char input_x;
		bool k = true;
	InvalidCoords:
		do
		{
			cout << "\nShooting ,enter coordinates(row, column): ";
			cin >> _y >> input_x;

			if (_y < 0 || _y > 10)
			{
				cout << "Invalid coordinates! Try again!"; goto InvalidCoords;
			}
			if ((input_x >= 'a' && input_x <= 'j') || (input_x >= 'A' && input_x <= 'J'))
			{
				for (size_t i = 1, j = 65, z = 97; j < 75; j++, z++, i++)
				{
					if (input_x == char(j) || input_x == char(z))
					{
						_x = i;
					}
				}
				k = false;
			}
			else { cout << "Invalid coordinates! Try again!"; goto InvalidCoords; }
		} while (k);

		_x--;
		_y--;

		if (arr[_y][_x] == 1)
		{
			arr[_y][_x] = 5;
			cout << "Hit!" << endl;
			Sleep(1000);
			HIT = true;
		}
		else
		{
			cout << "Miss!" << endl;
			Sleep(1000);
			HIT = false;
			arr[_y][_x] = 5;
		}
	}

	void enemy_rand_shoot()
	{
		srand(time(NULL));
		int _x, _y;
		bool k = false;

		while (!k)
		{
			_x = rand() % 10;
			_y = rand() % 10;

			if (arr[_y][_x] == 1 || arr[_y][_x] == 2 || arr[_y][_x] == 0) { k = true; }
		}

		if (arr[_y][_x] == 1)
		{
			arr[_y][_x] = 5;
			ENEMYHIT = true;
		}
		else
		{
			ENEMYHIT = false;
			arr[_y][_x] = 5;
		}
	}

	void enemy_smart_shoot()
	{
		srand(time(NULL));
		int _x, _y;
		bool k = false;

		if (isthereship == false)
		{
			while (!k)
			{
				_x = rand() % 10;
				_y = rand() % 10;

				if (arr[_y][_x] == 1 || arr[_y][_x] == 2 || arr[_y][_x] == 0) { k = true; }
			}

			if (arr[_y][_x] == 1)
			{
				isthereship = true;
			}

			x = _x;
			y = _y;

			arr[_y][_x] = 5;
		}

		if (isthereship == true)
		{
			if (dir == 0) dir = 1;

			if (dir == 1)
			{
				if (arr[y][x + step] == 3 || arr[y][x + step] == 4)
				{
					dir = 2; step = 1;
					ENEMYHIT = false;
				}
				else
				{
					if (arr[y][x + step] != 1) { dir = 2; step = 1; }
					else
					{
						arr[y][x + step] = 5;
						step++;
						ENEMYHIT = true;
					}
				}
			}
			else if (dir == 2)
			{
				if (arr[y][x - step] == 3 || arr[y][x - step] == 4)
				{
					dir = 3; step = 1;
					ENEMYHIT = false;
				}
				else
				{
					if (arr[y][x - step] != 1) { dir = 3; step = 1; }
					else
					{
						arr[y][x - step] = 5;
						step++;
						ENEMYHIT = true;
					}
				}
			}
			else if (dir == 3)
			{
				if (arr[y + step][x] == 3 || arr[y + step][x] == 4)
				{
					dir = 4; step = 1;
					ENEMYHIT = false;
				}
				else
				{
					if (arr[y + step][x] != 1) { dir = 4; step = 1; }
					else
					{
						arr[y + step][x] = 5;
						step++;
						ENEMYHIT = true;
					}
				}
			}
			else if (dir == 4)
			{
				if (arr[y - step][x] == 3 || arr[y - step][x] == 4)
				{
					dir = 0; step = 1; isthereship = false;
					ENEMYHIT = false;
				}
				else
				{
					if (arr[y - step][x] != 1) { dir = 0; step = 1; isthereship = false; ENEMYHIT = false; }
					else
					{
						arr[y - step][x] = 5;
						step++;
						ENEMYHIT = true;
					}
				}
			}
		}


	}
};

void winner_check()
{
	if (SHIPCOUNT == 0) { cout << "You LOST!" << endl; ISGAME = false; }
	if (ENEMY_SHIPCOUNT == 0) { cout << "You WON!" << endl; ISGAME = false; }
}

void ship_check(Field& field, vector<Ship>& ships, bool isenemy)
{
	for (size_t i = 0; i < ships.size(); i++)
	{
		int decks_destroyed = 0;
		if (field.arr[ships[i].y][ships[i].x] == 5) { field.arr[ships[i].y][ships[i].x] = 3;  decks_destroyed++; }

		for (size_t j = 0; j < ships[i].deck; j++)
		{
			if (field.arr[ships[i].deck_coords[j][1]][ships[i].deck_coords[j][0]] == 5)
			{
				field.arr[ships[i].deck_coords[j][1]][ships[i].deck_coords[j][0]] = 3;
				decks_destroyed++;
			}
		}

		if (field.arr[ships[i].y][ships[i].x] == 3 && decks_destroyed == ships[i].deck)
		{
			int _x, _y;
			_x = ships[i].x;
			_y = ships[i].y;

			if (isenemy == true) {
				ENEMY_SHIPCOUNT--;
			}

			if (isenemy == false)
			{
				SHIPCOUNT--;
			}

			if (_y - 1 >= 0 && _y - 1 <= 9) field.arr[_y - 1][_x] = 4;
			if (_y - 1 >= 0 && _x - 1 >= 0 && _y - 1 <= 9 && _x - 1 <= 9) field.arr[_y - 1][_x - 1] = 4;
			if (_x - 1 >= 0 && _x - 1 <= 9) field.arr[_y][_x - 1] = 4;
			if (_y + 1 >= 0 && _x - 1 >= 0 && _y + 1 <= 9 && _x - 1 <= 9) field.arr[_y + 1][_x - 1] = 4;
			if (_y + 1 >= 0 && _y + 1 <= 9) field.arr[_y + 1][_x] = 4;
			if (_y + 1 >= 0 && _x + 1 >= 0 && _y + 1 <= 9 && _x + 1 <= 9) field.arr[_y + 1][_x + 1] = 4;
			if (_x + 1 >= 0 && _x + 1 <= 9) field.arr[_y][_x + 1] = 4;
			if (_y - 1 >= 0 && _x + 1 >= 0 && _y - 1 <= 9 && _x + 1 <= 9) field.arr[_y - 1][_x + 1] = 4;

			for (size_t j = 1; j < ships[i].deck; j++)
			{
				_x = ships[i].deck_coords[j][0];
				_y = ships[i].deck_coords[j][1];

				if (_y - 1 >= 0 && _y - 1 <= 9) field.arr[_y - 1][_x] = 4;
				if (_y - 1 >= 0 && _x - 1 >= 0 && _y - 1 <= 9 && _x - 1 <= 9) field.arr[_y - 1][_x - 1] = 4;
				if (_x - 1 >= 0 && _x - 1 <= 9) field.arr[_y][_x - 1] = 4;
				if (_y + 1 >= 0 && _x - 1 >= 0 && _y + 1 <= 9 && _x - 1 <= 9) field.arr[_y + 1][_x - 1] = 4;
				if (_y + 1 >= 0 && _y + 1 <= 9) field.arr[_y + 1][_x] = 4;
				if (_y + 1 >= 0 && _x + 1 >= 0 && _y + 1 <= 9 && _x + 1 <= 9) field.arr[_y + 1][_x + 1] = 4;
				if (_x + 1 >= 0 && _x + 1 <= 9) field.arr[_y][_x + 1] = 4;
				if (_y - 1 >= 0 && _x + 1 >= 0 && _y - 1 <= 9 && _x + 1 <= 9) field.arr[_y - 1][_x + 1] = 4;
			}
			field.arr[ships[i].y][ships[i].x] = 3;

			for (size_t j = 1; j < ships[i].deck; j++)
			{
				field.arr[ships[i].deck_coords[j][1]][ships[i].deck_coords[j][0]] = 3;
			}
		}
	}
}


void manual_erange(Field& field, vector<Ship>& ships)
{
	int _x, _y;
	char x_char;
	bool ish;
	for (size_t i = 0; i < ships.size(); i++)
	{
	OutOfRange:
		field.show_ingame();
		cout << endl;
	InvalidCoords:
		if (i == 0) { cout << "enter 4 deck ship coords(row, column): "; }
		else if (i > 0 && i < 3) { cout << "enter 3 deck ship coords(row, column): "; }
		else if (i >= 3 && i < 6) { cout << "enter 2 deck ship coords(row, column): "; }
		else if (i > 5) { cout << "enter 1 deck ship coords(row, column): "; }
		cin >> _y >> x_char;

		if (_y < 0 || _y > 10) { cout << "Invalid coordinates! Try again!\n"; goto InvalidCoords; }
		else
		{
			if ((x_char >= 'a' && x_char <= 'j') || (x_char >= 'A' && x_char <= 'J'))
			{
				for (size_t n = 1, j = 65, z = 97; j < 75; j++, z++, n++)
				{
					if (x_char == char(j) || x_char == char(z))
					{
						_x = n;
					}
				}
			}
			else { cout << "Invalid coordinates! Try again!\n"; goto InvalidCoords; }
		}



		do
		{
			cout << "Horizontal or vertical position?(0, 1): ";
			cin >> ish;

			if (ish != 0 && ish != 1)
			{
				cout << "\n\t\t\t\t\tThere's not such option. Try again!\n";
			}

		} while (ish != 0 && ish != 1);

		_x--, _y--;
		system("cls");

		if (_x < 0 || _x > 9 || _y < 0 || _y > 9)
		{
			cout << "Coordinates are out of range! Try again" << endl;
			goto OutOfRange;
		}
		else
		{
			if (field.arr[_y][_x] == 0)
			{
				ships[i].x = _x, ships[i].y = _y, ships[i].ishorizontal = ish;

				if (ish == false)
				{
					if (ships[i].x + ships[i].deck <= 10)
					{
						bool isthereship = false;
						for (size_t z = 0; z < ships[i].deck; z++)
						{
							if (field.arr[ships[i].y][ships[i].x + z] == 1 || field.arr[ships[i].y][ships[i].x + z] == 2)
							{
								isthereship = true;
							}
						}

						if (isthereship == false)
						{
							field.arr[_y][_x] = 1;

							if (_y - 1 >= 0 && _y - 1 <= 9) field.arr[_y - 1][_x] = 2;
							if (_y - 1 >= 0 && _x - 1 >= 0 && _y - 1 <= 9 && _x - 1 <= 9) field.arr[_y - 1][_x - 1] = 2;
							if (_x - 1 >= 0 && _x - 1 <= 9) field.arr[_y][_x - 1] = 2;
							if (_y + 1 >= 0 && _x - 1 >= 0 && _y + 1 <= 9 && _x - 1 <= 9) field.arr[_y + 1][_x - 1] = 2;
							if (_y + 1 >= 0 && _y + 1 <= 9) field.arr[_y + 1][_x] = 2;
							if (_y + 1 >= 0 && _x + 1 >= 0 && _y + 1 <= 9 && _x + 1 <= 9) field.arr[_y + 1][_x + 1] = 2;
							if (_x + 1 >= 0 && _x + 1 <= 9) field.arr[_y][_x + 1] = 2;
							if (_y - 1 >= 0 && _x + 1 >= 0 && _y - 1 <= 9 && _x + 1 <= 9) field.arr[_y - 1][_x + 1] = 2;

							for (size_t j = 1; j < ships[i].deck; j++)
							{
								field.arr[ships[i].y][ships[i].x + j] = 1;
								ships[i].deck_coords[j][0] = ships[i].x + j;
								ships[i].deck_coords[j][1] = ships[i].y;

								if (ships[i].y - 1 >= 0 && ships[i].y - 1 <= 9 && field.arr[ships[i].y - 1][ships[i].x + j] == 0)     field.arr[ships[i].y - 1][ships[i].x + j] = 2;
								if (ships[i].y - 1 >= 0 && ships[i].y - 1 <= 9 && ships[i].x + j - 1 >= 0 && ships[i].x + j - 1 <= 9 && field.arr[ships[i].y - 1][ships[i].x + j - 1] == 0)    field.arr[ships[i].y - 1][ships[i].x + j - 1] = 2;
								if (ships[i].x + j - 1 >= 0 && ships[i].x + j - 1 <= 9 && field.arr[ships[i].y][ships[i].x + j - 1] == 0)   field.arr[ships[i].y][ships[i].x + j - 1] = 2;
								if (ships[i].y + 1 >= 0 && ships[i].y + 1 <= 9 && ships[i].x + j - 1 >= 0 && ships[i].x + j - 1 <= 9 && field.arr[ships[i].y + 1][ships[i].x + j - 1] == 0)   field.arr[ships[i].y + 1][ships[i].x + j - 1] = 2;
								if (ships[i].y + 1 >= 0 && ships[i].y + 1 <= 9 && field.arr[ships[i].y + 1][ships[i].x + j] == 0)    field.arr[ships[i].y + 1][ships[i].x + j] = 2;
								if (ships[i].y + 1 >= 0 && ships[i].y + 1 <= 9 && ships[i].x + j + 1 >= 0 && ships[i].x + j + 1 <= 9 && field.arr[ships[i].y + 1][ships[i].x + j + 1] == 0)    field.arr[ships[i].y + 1][ships[i].x + j + 1] = 2;
								if (ships[i].x + j + 1 >= 0 && ships[i].x + j + 1 <= 9 && field.arr[ships[i].y][ships[i].x + j + 1] == 0)   field.arr[ships[i].y][ships[i].x + j + 1] = 2;
								if (ships[i].x + j + 1 >= 0 && ships[i].x + j + 1 <= 9 && ships[i].y - 1 >= 0 && ships[i].y - 1 <= 9 && field.arr[ships[i].y - 1][ships[i].x + j + 1] == 0) field.arr[ships[i].y - 1][ships[i].x + j + 1] = 2;
							}
						}
						else
						{
							goto ShipIsRight;
						}

					}
					else
					{
					ShipIsRight:
						if (ships[i].x - ships[i].deck >= 0)
						{
							bool isthereship = false;
							for (size_t z = 0; z < ships[i].deck; z++)
							{
								if (field.arr[ships[i].y][ships[i].x - z] == 1 || field.arr[ships[i].y][ships[i].x - z] == 2)
								{
									isthereship = true;
								}
							}

							if (isthereship == false)
							{
								field.arr[_y][_x] = 1;

								if (_y - 1 >= 0 && _y - 1 <= 9) field.arr[_y - 1][_x] = 2;
								if (_y - 1 >= 0 && _x - 1 >= 0 && _y - 1 <= 9 && _x - 1 <= 9) field.arr[_y - 1][_x - 1] = 2;
								if (_x - 1 >= 0 && _x - 1 <= 9) field.arr[_y][_x - 1] = 2;
								if (_y + 1 >= 0 && _x - 1 >= 0 && _y + 1 <= 9 && _x - 1 <= 9) field.arr[_y + 1][_x - 1] = 2;
								if (_y + 1 >= 0 && _y + 1 <= 9) field.arr[_y + 1][_x] = 2;
								if (_y + 1 >= 0 && _x + 1 >= 0 && _y + 1 <= 9 && _x + 1 <= 9) field.arr[_y + 1][_x + 1] = 2;
								if (_x + 1 >= 0 && _x + 1 <= 9) field.arr[_y][_x + 1] = 2;
								if (_y - 1 >= 0 && _x + 1 >= 0 && _y - 1 <= 9 && _x + 1 <= 9) field.arr[_y - 1][_x + 1] = 2;

								for (size_t j = 0; j < ships[j].deck; j++)
								{
									field.arr[ships[i].y][ships[i].x - j] = 1;
									ships[i].deck_coords[j][0] = ships[i].x - j;
									ships[i].deck_coords[j][1] = ships[i].y;

									if (ships[i].y - 1 >= 0 && ships[i].y - 1 <= 9 && field.arr[ships[i].y - 1][ships[i].x - j] == 0)     field.arr[ships[i].y - 1][ships[i].x - j] = 2;
									if (ships[i].y - 1 >= 0 && ships[i].y - 1 <= 9 && ships[i].x - j - 1 >= 0 && ships[i].x - j - 1 <= 9 && field.arr[ships[i].y - 1][ships[i].x - j - 1] == 0)    field.arr[ships[i].y - 1][ships[i].x - j - 1] = 2;
									if (ships[i].x - j - 1 >= 0 && ships[i].x - j - 1 <= 9 && field.arr[ships[i].y][ships[i].x - j - 1] == 0)   field.arr[ships[i].y][ships[i].x - j - 1] = 2;
									if (ships[i].y + 1 >= 0 && ships[i].y + 1 <= 9 && ships[i].x - j - 1 >= 0 && ships[i].x - j - 1 <= 9 && field.arr[ships[i].y + 1][ships[i].x - j - 1] == 0)   field.arr[ships[i].y + 1][ships[i].x - j - 1] = 2;
									if (ships[i].y + 1 >= 0 && ships[i].y + 1 <= 9 && field.arr[ships[i].y + 1][ships[i].x - j] == 0)    field.arr[ships[i].y + 1][ships[i].x - j] = 2;
									if (ships[i].y + 1 >= 0 && ships[i].y + 1 <= 9 && ships[i].x - j + 1 >= 0 && ships[i].x - j + 1 <= 9 && field.arr[ships[i].y + 1][ships[i].x - j + 1] == 0)    field.arr[ships[i].y + 1][ships[i].x - j + 1] = 2;
									if (ships[i].x - j + 1 >= 0 && ships[i].x - j + 1 <= 9 && field.arr[ships[i].y][ships[i].x - j + 1] == 0)   field.arr[ships[i].y][ships[i].x - j + 1] = 2;
									if (ships[i].y - 1 >= 0 && ships[i].y - 1 <= 9 && ships[i].x - j + 1 >= 0 && ships[i].x - j + 1 <= 9 && ships[i].x - j + 1 < +0 && field.arr[ships[i].y - 1][ships[i].x] == 0)   field.arr[ships[i].y - 1][ships[i].x - j + 1] = 2;
									if (ships[i].x + j + 1 >= 0 && ships[i].x - j + 1 <= 9 && ships[i].y - 1 >= 0 && ships[i].y - 1 <= 9 && field.arr[ships[i].y - 1][ships[i].x - j + 1] == 0) field.arr[ships[i].y - 1][ships[i].x - j + 1] = 2;
								}
							}
							else
							{
								cout << "Can't place ship there! Try again!" << endl;
								goto OutOfRange;
							}

						}
						else
						{
							cout << "Can't place ship there! Try again!" << endl;
							goto OutOfRange;
						}
					}

				}
				else if (ish == true)
				{
					if (ships[i].y + ships[i].deck <= 10)
					{
						bool isthereship = false;
						for (size_t z = 0; z < ships[i].deck; z++)
						{
							if (field.arr[ships[i].y + z][ships[i].x] == 1 || field.arr[ships[i].y + z][ships[i].x] == 2)
							{
								isthereship = true;
							}
						}

						if (isthereship == false)
						{
							field.arr[_y][_x] = 1;

							if (_y - 1 >= 0 && _y - 1 <= 9) field.arr[_y - 1][_x] = 2;
							if (_y - 1 >= 0 && _x - 1 >= 0 && _y - 1 <= 9 && _x - 1 <= 9) field.arr[_y - 1][_x - 1] = 2;
							if (_x - 1 >= 0 && _x - 1 <= 9) field.arr[_y][_x - 1] = 2;
							if (_y + 1 >= 0 && _x - 1 >= 0 && _y + 1 <= 9 && _x - 1 <= 9) field.arr[_y + 1][_x - 1] = 2;
							if (_y + 1 >= 0 && _y + 1 <= 9) field.arr[_y + 1][_x] = 2;
							if (_y + 1 >= 0 && _x + 1 >= 0 && _y + 1 <= 9 && _x + 1 <= 9) field.arr[_y + 1][_x + 1] = 2;
							if (_x + 1 >= 0 && _x + 1 <= 9) field.arr[_y][_x + 1] = 2;
							if (_y - 1 >= 0 && _x + 1 >= 0 && _y - 1 <= 9 && _x + 1 <= 9) field.arr[_y - 1][_x + 1] = 2;


							for (size_t j = 1; j < ships[i].deck; j++)
							{
								field.arr[ships[i].y + j][ships[i].x] = 1;
								ships[i].deck_coords[j][0] = ships[i].x;
								ships[i].deck_coords[j][1] = ships[i].y + j;

								if (ships[i].y + j - 1 >= 0 && ships[i].y + j - 1 <= 9 && field.arr[ships[i].y + j - 1][ships[i].x] == 0)     field.arr[ships[i].y + j - 1][ships[i].x] = 2;
								if (ships[i].y + j - 1 >= 0 && ships[i].y + j - 1 <= 9 && ships[i].x - 1 >= 0 && ships[i].x - 1 <= 9 && field.arr[ships[i].y + j - 1][ships[i].x - 1] == 0)    field.arr[ships[i].y + j - 1][ships[i].x - 1] = 2;
								if (ships[i].x - 1 >= 0 && ships[i].x - 1 <= 9 && field.arr[ships[i].y + j][ships[i].x - 1] == 0)   field.arr[ships[i].y + j][ships[i].x - 1] = 2;
								if (ships[i].y + j + 1 >= 0 && ships[i].y + j + 1 <= 9 && ships[i].x - 1 >= 0 && ships[i].x - 1 <= 9 && field.arr[ships[i].y + j + 1][ships[i].x - 1] == 0)   field.arr[ships[i].y + j + 1][ships[i].x - 1] = 2;
								if (ships[i].y + j + 1 >= 0 && ships[i].y + j + 1 <= 9 && field.arr[ships[i].y + j + 1][ships[i].x] == 0)    field.arr[ships[i].y + j + 1][ships[i].x] = 2;
								if (ships[i].y + j + 1 >= 0 && ships[i].y + j + 1 <= 9 && ships[i].x + 1 >= 0 && ships[i].x + 1 <= 9 && field.arr[ships[i].y + j + 1][ships[i].x + 1] == 0)    field.arr[ships[i].y + j + 1][ships[i].x + 1] = 2;
								if (ships[i].x + 1 >= 0 && ships[i].x + 1 <= 9 && field.arr[ships[i].y + j][ships[i].x + 1] == 0)   field.arr[ships[i].y + j][ships[i].x + 1] = 2;
								if (ships[i].y + j - 1 >= 0 && ships[i].y + j - 1 <= 9 && ships[i].x + 1 >= 0 && ships[i].x + 1 <= 9 && field.arr[ships[i].y + j - 1][ships[i].x + 1] == 0)   field.arr[ships[i].y + j - 1][ships[i].x + 1] = 2;
							}
						}
						else
						{
							goto ShipIsDown;
						}
					}
					else
					{
					ShipIsDown:
						if (ships[i].y - ships[i].deck >= 0)
						{
							bool isthereship = false;
							for (size_t z = 0; z < ships[i].deck; z++)
							{
								if (field.arr[ships[i].y - z][ships[i].x] == 1 || field.arr[ships[i].y - z][ships[i].x] == 2)
								{
									isthereship = true;
								}
							}

							if (isthereship == false)
							{

								field.arr[_y][_x] = 1;

								if (_y - 1 >= 0 && _y - 1 <= 9) field.arr[_y - 1][_x] = 2;
								if (_y - 1 >= 0 && _x - 1 >= 0 && _y - 1 <= 9 && _x - 1 <= 9) field.arr[_y - 1][_x - 1] = 2;
								if (_x - 1 >= 0 && _x - 1 <= 9) field.arr[_y][_x - 1] = 2;
								if (_y + 1 >= 0 && _x - 1 >= 0 && _y + 1 <= 9 && _x - 1 <= 9) field.arr[_y + 1][_x - 1] = 2;
								if (_y + 1 >= 0 && _y + 1 <= 9) field.arr[_y + 1][_x] = 2;
								if (_y + 1 >= 0 && _x + 1 >= 0 && _y + 1 <= 9 && _x + 1 <= 9) field.arr[_y + 1][_x + 1] = 2;
								if (_x + 1 >= 0 && _x + 1 <= 9) field.arr[_y][_x + 1] = 2;
								if (_y - 1 >= 0 && _x + 1 >= 0 && _y - 1 <= 9 && _x + 1 <= 9) field.arr[_y - 1][_x + 1] = 2;

								for (size_t j = 1; j < ships[i].deck; j++)
								{

									field.arr[ships[i].y - j][ships[i].x] = 1;
									ships[i].deck_coords[j][0] = ships[i].x;
									ships[i].deck_coords[j][1] = ships[i].y - j;

									if (ships[i].y - j - 1 >= 0 && ships[i].y - j - 1 <= 9 && field.arr[ships[i].y - j - 1][ships[i].x] == 0)     field.arr[ships[i].y - j - 1][ships[i].x] = 2;
									if (ships[i].y - j - 1 >= 0 && ships[i].y - j - 1 <= 9 && ships[i].x - 1 >= 0 && ships[i].x - 1 <= 9 && field.arr[ships[i].y - j - 1][ships[i].x - 1] == 0)    field.arr[ships[i].y - j - 1][ships[i].x - 1] = 2;
									if (ships[i].x - 1 >= 0 && ships[i].x - 1 <= 9 && field.arr[ships[i].y - j][ships[i].x - 1] == 0)   field.arr[ships[i].y - j][ships[i].x - 1] = 2;
									if (ships[i].y - j + 1 >= 0 && ships[i].y - j + 1 <= 9 && ships[i].x - 1 >= 0 && ships[i].x - 1 <= 9 && field.arr[ships[i].y - j + 1][ships[i].x - 1] == 0)   field.arr[ships[i].y - j + 1][ships[i].x - 1] = 2;
									if (ships[i].y - j + 1 >= 0 && ships[i].y - j + 1 <= 9 && field.arr[ships[i].y - j + 1][ships[i].x] == 0)    field.arr[ships[i].y - j + 1][ships[i].x] = 2;
									if (ships[i].y - j + 1 >= 0 && ships[i].y - j + 1 <= 9 && ships[i].x + 1 >= 0 && ships[i].x + 1 <= 9 && field.arr[ships[i].y - j + 1][ships[i].x + 1] == 0)    field.arr[ships[i].y - j + 1][ships[i].x + 1] = 2;
									if (ships[i].x + 1 >= 0 && ships[i].x + 1 <= 9 && field.arr[ships[i].y - j][ships[i].x + 1] == 0)   field.arr[ships[i].y + j][ships[i].x + 1] = 2;
									if (ships[i].y - j - 1 >= 0 && ships[i].y - j - 1 <= 9 && ships[i].x + 1 >= 0 && ships[i].x + 1 <= 9 && field.arr[ships[i].y - j - 1][ships[i].x + 1] == 0)   field.arr[ships[i].y - j - 1][ships[i].x + 1] = 2;
								}

							}
							else
							{
								cout << "Can't place ship there! Try again!" << endl;
								goto OutOfRange;
							}

						}
						else
						{
							cout << "Can't place ship there! Try again!" << endl;
							goto OutOfRange;
						}
					}
				}
			}
			else
			{
				cout << "Can't place ship there! Try again!" << endl;
				goto OutOfRange;
			}

		}
	}
}

void auto_erange(Field& field, vector<Ship>& ships)
{
	srand(time(NULL));
	int _x, _y;
	int dir;


	for (size_t i = 0; i < 10; i++)
	{
		bool correct_coords = false;

	InvalidCoords:
		while (!correct_coords)
		{
			_x = rand() % 10;
			_y = rand() % 10;
			int ishrznt = rand() % 21;

			if (_x == 0 || _y == 0) { goto InvalidCoords; }

			if (ishrznt % 2 == 0)
			{
				ships[i].ishorizontal = true;
			}
			else ships[i].ishorizontal = false;

			if (field.arr[_y][_x] == 0)
			{
				bool isthereship = false;

				if (ships[i].ishorizontal == true)
				{
					if (_x + ships[i].deck <= 10)
					{
						for (size_t z = 0; z < ships[i].deck; z++)
						{
							if (field.arr[_y][_x + z] == 1 || field.arr[_y][_x + z] == 2)
							{
								isthereship = true;
								break;
							}
						}
						if (isthereship == false)
						{
							correct_coords = true;
							dir = 1;
						}
					}
					else if (_x + ships[i].deck > 10 || isthereship == true)
					{
						for (size_t z = 0; z < ships[i].deck; z++)
						{
							if (field.arr[_y][_x - z] == 1 || field.arr[_y][_x - z] == 2)
							{
								isthereship = true;
								ships[i].ishorizontal = false;
								break;
							}
						}
						if (isthereship == false)
						{
							correct_coords = true;
							dir = 2;
						}
					}
				}

				if (ships[i].ishorizontal == false)
				{
					if (_y + ships[i].deck <= 10)
					{
						for (size_t z = 0; z < ships[i].deck; z++)
						{
							if (field.arr[_y + z][_x] == 1 || field.arr[_y + z][_x] == 2)
							{
								isthereship = true;
								break;
							}
						}
						if (isthereship == false)
						{
							correct_coords = true;
							dir = 3;
						}
					}
					else if (_y + ships[i].deck > 10 || isthereship == true)
					{
						for (size_t z = 0; z < ships[i].deck; z++)
						{
							if (field.arr[_y - z][_x] == 1 || field.arr[_y - z][_x] == 2)
							{
								isthereship = true;
								break;
							}
							if (isthereship == false)
							{
								correct_coords = true;
								dir = 4;
							}
						}
					}
				}
			}
		}

		if (correct_coords == true)
		{
			ships[i].x = _x;
			ships[i].y = _y;
			field.arr[ships[i].y][ships[i].x] = 1;

			if (_y - 1 >= 0 && _y - 1 <= 9) field.arr[_y - 1][_x] = 2;
			if (_y - 1 >= 0 && _x - 1 >= 0 && _y - 1 <= 9 && _x - 1 <= 9) field.arr[_y - 1][_x - 1] = 2;
			if (_x - 1 >= 0 && _x - 1 <= 9) field.arr[_y][_x - 1] = 2;
			if (_y + 1 >= 0 && _x - 1 >= 0 && _y + 1 <= 9 && _x - 1 <= 9) field.arr[_y + 1][_x - 1] = 2;
			if (_y + 1 >= 0 && _y + 1 <= 9) field.arr[_y + 1][_x] = 2;
			if (_y + 1 >= 0 && _x + 1 >= 0 && _y + 1 <= 9 && _x + 1 <= 9) field.arr[_y + 1][_x + 1] = 2;
			if (_x + 1 >= 0 && _x + 1 <= 9) field.arr[_y][_x + 1] = 2;
			if (_y - 1 >= 0 && _x + 1 >= 0 && _y - 1 <= 9 && _x + 1 <= 9) field.arr[_y - 1][_x + 1] = 2;

			if (dir == 1)
			{

				for (size_t j = 0; j < ships[i].deck; j++)
				{
					field.arr[ships[i].y][ships[i].x + j] = 1;
					ships[i].deck_coords[j][0] = ships[i].x + j;
					ships[i].deck_coords[j][1] = ships[i].y;

					if (ships[i].y - 1 >= 0 && ships[i].y - 1 <= 9 && field.arr[ships[i].y - 1][ships[i].x + j] == 0)     field.arr[ships[i].y - 1][ships[i].x + j] = 2;
					if (ships[i].y - 1 >= 0 && ships[i].y - 1 <= 9 && ships[i].x + j - 1 >= 0 && ships[i].x + j - 1 <= 9 && field.arr[ships[i].y - 1][ships[i].x + j - 1] == 0)    field.arr[ships[i].y - 1][ships[i].x + j - 1] = 2;
					if (ships[i].x + j - 1 >= 0 && ships[i].x + j - 1 <= 9 && field.arr[ships[i].y][ships[i].x + j - 1] == 0)   field.arr[ships[i].y][ships[i].x + j - 1] = 2;
					if (ships[i].y + 1 >= 0 && ships[i].y + 1 <= 9 && ships[i].x + j - 1 >= 0 && ships[i].x + j - 1 <= 9 && field.arr[ships[i].y + 1][ships[i].x + j - 1] == 0)   field.arr[ships[i].y + 1][ships[i].x + j - 1] = 2;
					if (ships[i].y + 1 >= 0 && ships[i].y + 1 <= 9 && field.arr[ships[i].y + 1][ships[i].x + j] == 0)    field.arr[ships[i].y + 1][ships[i].x + j] = 2;
					if (ships[i].y + 1 >= 0 && ships[i].y + 1 <= 9 && ships[i].x + j + 1 >= 0 && ships[i].x + j + 1 <= 9 && field.arr[ships[i].y + 1][ships[i].x + j + 1] == 0)    field.arr[ships[i].y + 1][ships[i].x + j + 1] = 2;
					if (ships[i].x + j + 1 >= 0 && ships[i].x + j + 1 <= 9 && field.arr[ships[i].y][ships[i].x + j + 1] == 0)   field.arr[ships[i].y][ships[i].x + j + 1] = 2;
					if (ships[i].x + j + 1 >= 0 && ships[i].x + j + 1 <= 9 && ships[i].y - 1 >= 0 && ships[i].y - 1 <= 9 && field.arr[ships[i].y - 1][ships[i].x + j + 1] == 0) field.arr[ships[i].y - 1][ships[i].x + j + 1] = 2;
				}
			}
			else if (dir == 2)
			{
				for (size_t j = 1; j < ships[i].deck; j++)
				{
					field.arr[ships[i].y][ships[i].x - j] = 1;
					ships[i].deck_coords[j][0] = ships[i].x - j;
					ships[i].deck_coords[j][1] = ships[i].y;

					if (ships[i].y - 1 >= 0 && ships[i].y - 1 <= 9 && field.arr[ships[i].y - 1][ships[i].x - j] == 0)     field.arr[ships[i].y - 1][ships[i].x - j] = 2;
					if (ships[i].y - 1 >= 0 && ships[i].y - 1 <= 9 && ships[i].x - j - 1 >= 0 && ships[i].x - j - 1 <= 9 && field.arr[ships[i].y - 1][ships[i].x - j - 1] == 0)    field.arr[ships[i].y - 1][ships[i].x - j - 1] = 2;
					if (ships[i].x - j - 1 >= 0 && ships[i].x - j - 1 <= 9 && field.arr[ships[i].y][ships[i].x - j - 1] == 0)   field.arr[ships[i].y][ships[i].x - j - 1] = 2;
					if (ships[i].y + 1 >= 0 && ships[i].y + 1 <= 9 && ships[i].x - j - 1 >= 0 && ships[i].x - j - 1 <= 9 && field.arr[ships[i].y + 1][ships[i].x - j - 1] == 0)   field.arr[ships[i].y + 1][ships[i].x - j - 1] = 2;
					if (ships[i].y + 1 >= 0 && ships[i].y + 1 <= 9 && field.arr[ships[i].y + 1][ships[i].x - j] == 0)    field.arr[ships[i].y + 1][ships[i].x - j] = 2;
					if (ships[i].y + 1 >= 0 && ships[i].y + 1 <= 9 && ships[i].x - j + 1 >= 0 && ships[i].x - j + 1 <= 9 && field.arr[ships[i].y + 1][ships[i].x - j + 1] == 0)    field.arr[ships[i].y + 1][ships[i].x - j + 1] = 2;
					if (ships[i].x - j + 1 >= 0 && ships[i].x - j + 1 <= 9 && field.arr[ships[i].y][ships[i].x - j + 1] == 0)   field.arr[ships[i].y][ships[i].x - j + 1] = 2;
					if (ships[i].y - 1 >= 0 && ships[i].y - 1 <= 9 && ships[i].x - j + 1 >= 0 && ships[i].x - j + 1 <= 9 && field.arr[ships[i].y - 1][ships[i].x - j + 1] == 0)   field.arr[ships[i].y - 1][ships[i].x - j + 1] = 2;

				}
			}
			else if (dir == 3)
			{
				for (size_t j = 1; j < ships[i].deck; j++)
				{
					field.arr[ships[i].y + j][ships[i].x] = 1;
					ships[i].deck_coords[j][0] = ships[i].x;
					ships[i].deck_coords[j][1] = ships[i].y + j;

					if (ships[i].y + j - 1 >= 0 && ships[i].y + j - 1 <= 9 && field.arr[ships[i].y + j - 1][ships[i].x] == 0)     field.arr[ships[i].y + j - 1][ships[i].x] = 2;
					if (ships[i].y + j - 1 >= 0 && ships[i].y + j - 1 <= 9 && ships[i].x - 1 >= 0 && ships[i].x - 1 <= 9 && field.arr[ships[i].y + j - 1][ships[i].x - 1] == 0)    field.arr[ships[i].y + j - 1][ships[i].x - 1] = 2;
					if (ships[i].x - 1 >= 0 && ships[i].x - 1 <= 9 && field.arr[ships[i].y + j][ships[i].x - 1] == 0)   field.arr[ships[i].y + j][ships[i].x - 1] = 2;
					if (ships[i].y + j + 1 >= 0 && ships[i].y + j + 1 <= 9 && ships[i].x - 1 >= 0 && ships[i].x - 1 <= 9 && field.arr[ships[i].y + j + 1][ships[i].x - 1] == 0)   field.arr[ships[i].y + j + 1][ships[i].x - 1] = 2;
					if (ships[i].y + j + 1 >= 0 && ships[i].y + j + 1 <= 9 && field.arr[ships[i].y + j + 1][ships[i].x] == 0)    field.arr[ships[i].y + j + 1][ships[i].x] = 2;
					if (ships[i].y + j + 1 >= 0 && ships[i].y + j + 1 <= 9 && ships[i].x + 1 >= 0 && ships[i].x + 1 <= 9 && field.arr[ships[i].y + j + 1][ships[i].x + 1] == 0)    field.arr[ships[i].y + j + 1][ships[i].x + 1] = 2;
					if (ships[i].x + 1 >= 0 && ships[i].x + 1 <= 9 && field.arr[ships[i].y + j][ships[i].x + 1] == 0)   field.arr[ships[i].y + j][ships[i].x + 1] = 2;
					if (ships[i].y + j - 1 >= 0 && ships[i].y + j - 1 <= 9 && ships[i].x + 1 >= 0 && ships[i].x + 1 <= 9 && field.arr[ships[i].y + j - 1][ships[i].x + 1] == 0)   field.arr[ships[i].y + j - 1][ships[i].x + 1] = 2;
				}
			}
			else if (dir == 4)
			{
				for (size_t j = 1; j < ships[i].deck; j++)
				{

					field.arr[ships[i].y - j][ships[i].x] = 1;
					ships[i].deck_coords[j][0] = ships[i].x;
					ships[i].deck_coords[j][1] = ships[i].y - j;

					if (ships[i].y - j - 1 >= 0 && ships[i].y - j - 1 <= 9 && field.arr[ships[i].y - j - 1][ships[i].x] == 0)     field.arr[ships[i].y - j - 1][ships[i].x] = 2;
					if (ships[i].y - j - 1 >= 0 && ships[i].y - j - 1 <= 9 && ships[i].x - 1 >= 0 && ships[i].x - 1 <= 9 && field.arr[ships[i].y - j - 1][ships[i].x - 1] == 0)    field.arr[ships[i].y - j - 1][ships[i].x - 1] = 2;
					if (ships[i].x - 1 >= 0 && ships[i].x - 1 <= 9 && field.arr[ships[i].y - j][ships[i].x - 1] == 0)   field.arr[ships[i].y - j][ships[i].x - 1] = 2;
					if (ships[i].y - j + 1 >= 0 && ships[i].y - j + 1 <= 9 && ships[i].x - 1 >= 0 && ships[i].x - 1 <= 9 && field.arr[ships[i].y - j + 1][ships[i].x - 1] == 0)   field.arr[ships[i].y - j + 1][ships[i].x - 1] = 2;
					if (ships[i].y - j + 1 >= 0 && ships[i].y - j + 1 <= 9 && field.arr[ships[i].y - j + 1][ships[i].x] == 0)    field.arr[ships[i].y - j + 1][ships[i].x] = 2;
					if (ships[i].y - j + 1 >= 0 && ships[i].y - j + 1 <= 9 && ships[i].x + 1 >= 0 && ships[i].x + 1 <= 9 && field.arr[ships[i].y - j + 1][ships[i].x + 1] == 0)    field.arr[ships[i].y - j + 1][ships[i].x + 1] = 2;
					if (ships[i].x + 1 >= 0 && ships[i].x + 1 <= 9 && field.arr[ships[i].y - j][ships[i].x + 1] == 0)   field.arr[ships[i].y + j][ships[i].x + 1] = 2;
					if (ships[i].y - j - 1 >= 0 && ships[i].y - j - 1 <= 9 && ships[i].x + 1 >= 0 && ships[i].x + 1 <= 9 && field.arr[ships[i].y - j - 1][ships[i].x + 1] == 0)   field.arr[ships[i].y - j - 1][ships[i].x + 1] = 2;
				}
			}
		}

	}
}


void menu(Field& field, Field& enemy_field, vector<Ship>& ships, vector<Ship>& enemy_ships)
{

	int choice;
	do
	{
		cout << "\n\n\t\t\t\t\t\tSEA BATTLE\t\n" << endl;
		cout << "\t\t\t\t\tPlay(1)" << endl << endl;
		cout << "\t\t\t\t\tExit(0)\n\n\t\t\t\t\t";
		cin >> choice;

		if (choice != 0 && choice != 1)
		{
			system("cls");
			cout << "\n\t\t\t\t\tThere's not such option. Try again!\n";
		}
	} while (choice != 0 && choice != 1);

	system("cls");

	if (choice == 1)
	{
		int dif;
		do
		{
			cout << "\n\t\t\t\t\tEnter difficulty: easy(0),  hard(1)\n\n\t\t\t\t\t";
			cin >> dif;
			if (dif != 0 && dif != 1)
			{
				system("cls");
				cout << "\n\t\t\t\t\tThere's not such option. Try again!\n";
			}
		} while (dif != 0 && dif != 1);

		DIFFICULTY = dif;

		int erng;

		do
		{
			cout << "\n\t\t\t\t\tHow do you whant to place your ships?  manualy(0),  auto(1)\n\n\t\t\t\t\t";
			cin >> erng;
			if (erng != 0 && erng != 1)
			{
				system("cls");
				cout << "\n\t\t\t\t\tThere's not such option. Try again!\n";
			}
		} while (erng != 0 && erng != 1);

		auto_erange(enemy_field, enemy_ships);

		if (erng == 0) { manual_erange(field, ships); }
		else { auto_erange(field, ships); }

		choice = 2;
		do
		{
			cout << "\n\t\t\t\t\tStarting? Yes(1),  Exit(0)\n\n\t\t\t\t\t";
			cin >> choice;
			if (choice != 0 && choice != 1)
			{
				system("cls");
				cout << "\n\t\t\t\t\tThere's not such option. Try again!\n";
			}
		} while (choice != 0 && choice != 1);

		if (choice == 0) { exit(0); }
	}
	else { exit(0); }
}

void game(Field& field, Field& enemy_field, vector<Ship>& ships, vector<Ship>& enemy_ships)
{
	int turn = 1;
	system("cls");
	while (ISGAME)
	{
		if (turn % 2 != 0)
		{
			system("cls");
			ship_check(field, ships, false);
			cout << "Your field:\n";
			cout << "You have " << SHIPCOUNT << " ships\n\n";
			field.show_ingame();
			cout << "\n\n";
			cout << "Enemy's field:\n";
			cout << "Enemy has " << ENEMY_SHIPCOUNT << " ships\n\n";
			enemy_field.show_enemy();
			system("pause");

			cout << endl << "Your turn!: " << endl;

			do
			{
				enemy_field.shoot();
				Sleep(1000);
			} while (HIT);
		}
		else
		{
			system("cls");
			ship_check(enemy_field, enemy_ships, true);
			cout << "Your field:\n\n";
			field.show_ingame();
			cout << "\n\n";
			cout << "Enemy's field:\n\n";
			enemy_field.show_enemy();

			cout << endl << "Enemy's turn!" << endl;
			Sleep(4000);

			if (DIFFICULTY == 0)
			{
				do
				{
					field.enemy_rand_shoot();

				} while (ENEMYHIT);
			}
			else
			{
				do
				{
					field.enemy_smart_shoot();
				} while (ENEMYHIT);
			}
		}
		winner_check();
		turn++;

	}
}

int main()
{
	Field field;
	Field enemy_field;

	vector<Ship> ships(SHIPCOUNT);
	vector<Ship> enemy_ships(ENEMY_SHIPCOUNT);

	for (size_t i = 0, j = 4; i < ships.size(); i++)
	{
		if (i > 0 && i < 3) { j = 3; }
		if (i > 2 && i < 6) { j = 2; }
		if (i > 5) { j = 1; }
		ships[i].set_decks(j);
		enemy_ships[i].set_decks(j);
	}

	menu(field, enemy_field, ships, enemy_ships);
	game(field, enemy_field, ships, enemy_ships);


	return 0;
}