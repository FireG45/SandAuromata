#include <iostream>
#include <algorithm>
#include <windows.h>
#include <list>

enum  Type
{
	SAND = '#',
	EMPTY = ' ',
	STONE = '@',
	SANDSPAWNER = 'S',
};

class Screen
{
private:
	int w, h;
	char* plane;

public:
	Screen(int _w, int _h)
	{
		w = _w;
		h = _h;
		plane = new char[w * h + 1];

		for (int i = 0; i < w; i++)
		{
			for (int j = 0; j < h; j++)
				plane[i + j * w] = ' ';
		}
		plane[w * h] = '\0';

	}

	~Screen()
	{
		delete[] plane;
	}

	char* get()
	{
		return plane;
	}

	void set_pixel(int x, int y, char c)
	{
		plane[x + y * w] = c;
	}

	int get_w() { return w; }

	int get_h() { return h; }

	void clear_screen()
	{
		for (int i = 0; i < w; i++)
		{
			for (int j = 0; j < h; j++)
				plane[i + j * w] = ' ';
		}
		plane[w * h] = '\0';
	}

};

class Powder
{
public:
	bool upd = false;
	Type type;

	Powder()
	{
		type = EMPTY;
	}

	Powder(Type type)
	{
		this->type = type;
	}

	bool operator==(Powder p)
	{
		return type == p.type;
	}

	bool operator==(Type t)
	{
		return type == t;
	}
	void operator=(Type t)
	{
		type = t;
	}
};

class Plane
{
	int w, h;
public:
	Powder** plane = new Powder * [h];

	Plane(int w, int h)
	{
		this->w = w;
		this->h = h;

		for (int i = 0; i < w; i++)
			plane[i] = new Powder[w];
	}

	~Plane()
	{
		for (int i = 0; i < w; i++)
			delete[] plane[i];
		delete[] plane;
	}

	void Draw(Screen* screen)
	{
		for (int i = 0; i < w; i++)
			for (int j = 0; j < h; j++)
				screen->set_pixel(i, j, plane[i, j]->type);

		printf(screen->get());
	}

	void set(int x, int y, Type type)
	{
		plane[x][y].type = type;
	}

	int get_w() { return w; }
	int get_h() { return h; }

	void update()
	{
		for (int i = 0; i < w; i++)
			for (int j = 0; j < h; j++)
				plane[i][j].upd = false;


		for (int i = 0; i < w; i++)
		{
			for (int j = h; j > 0; j--)
			{
				if (!plane[i][j].upd && plane[i][j] == SAND)
				{
					if (j + 1 < h)
						if (plane[i][j + 1] == EMPTY)
						{
							plane[i][j].upd = true;
							std::swap(plane[i][j], plane[i][j + 1]);
						}

					if (i - 1 > 0)
						if (plane[i - 1][j + 1] == EMPTY)
						{
							plane[i][j].upd = true;
							std::swap(plane[i][j], plane[i - 1][j + 1]);
						}
					if (i + 1 < w)
						if (plane[i + 1][j + 1] == EMPTY)
						{
							plane[i][j].upd = true;
							std::swap(plane[i][j], plane[i + 1][j + 1]);
						}
				}
				if (!plane[i][j].upd && plane[i][j] == SANDSPAWNER)
				{
					plane[i][j + 1] = SAND;
				}
			}
		}

	}

};



int main()
{
	Screen screen(120, 30);
	Plane plane(120, 30);

	/*for (int i = 1; i < 8; i++)
	{
		plane.set(60, i, SAND);
	}*/
	plane.set(60, 2, SANDSPAWNER);
	plane.set(15, 2, SANDSPAWNER);
	plane.set(45, 2, SANDSPAWNER);



	for (int i = 0; i < plane.get_w(); i++)
		plane.set(i, plane.get_h() - 1, STONE);

	while (true)
	{

		for (int i = 0; i < plane.get_w() - 1; i++)
			for (int j = 0; j < plane.get_h() - 1; j++)
			{
				screen.set_pixel(i, j, (char)(plane.plane[i][j].type));
			}
		printf(screen.get());
		Sleep(30);
		screen.clear_screen();
		plane.update();

	}

}

