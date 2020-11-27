#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;
class TowerOfHanoiInterface
{
	int* a;
	int* b;
	int* c;
	int size;
	int nextIndexA;
	int nextIndexB;
	int nextIndexC;
public:
	static int moves;
	int& getSize()
	{
		return size;
	}
	int* getArrayA()
	{
		return a;
	}
	int* getArrayB()
	{
		return b;
	}
	int* getArrayC()
	{
		return c;
	}
	int* getIndexA()
	{
		return &nextIndexA;
	}
	int* getIndexB()
	{
		return &nextIndexB;
	}
	int* getIndexC()
	{
		return &nextIndexC;
	}
	TowerOfHanoiInterface(int n)
	{
		if (n > 0)
		{
			size = n;
		}
		else
		{
			size = 1;
		}
		a = NULL;
		b = NULL;
		c = NULL;
	}
	int swap(char source, char dest)
	{
		int* s;
		int* q;
		int* sourceIndex;
		int* destIndex;
		if (source == 'A')
		{
			sourceIndex = getIndexA();
			s = getArrayA();
		}
		else if (source == 'B')
		{
			sourceIndex = getIndexB();
			s = getArrayB();
		}
		else
		{
			sourceIndex = getIndexC();
			s = getArrayC();
		}
		if (dest == 'A')
		{
			q = getArrayA();
			destIndex = getIndexA();
		}
		else if (dest == 'B')
		{
			q = getArrayB();
			destIndex = getIndexB();
		}
		else
		{
			q = getArrayC();
			destIndex = getIndexC();
		}
		if (*destIndex >= 0 && *destIndex < size && (*sourceIndex - 1) >= 0 && (*sourceIndex - 1) < size)
		{
			if (*sourceIndex == 0)
			{
				return -1;
			}
			else if ((*destIndex - 1 >= 0) && q[*destIndex - 1] <= s[*sourceIndex - 1])
			{
				return 0;
			}
			else
			{
				int temp = q[*destIndex];
				q[*destIndex] = s[*sourceIndex - 1];
				s[*sourceIndex - 1] = temp;
				*sourceIndex = *sourceIndex - 1;
				*destIndex = *destIndex + 1;
				return true;
			}
		}
	}
	void display()
	{
		cout << "\n---------------Towers_Of_Hanoi_Game--------------\n";
		cout << '\n';
		for (int i = size; i >= 0; i--)
		{
			cout << "\t\t";
			for (int j = 0; j < 3; j++)
			{
				if (i == size)
				{
					cout << ".\t";
				}
				else
				{
					if (j == 0)
					{
						if (a[i] == 0)
						{
							cout << ".\t";
						}
						else
						{
							cout << a[i] << '\t';
						}
					}
					else if (j == 1)
					{
						if (b[i] == 0)
						{
							cout << ".\t";
						}
						else
						{
							cout << b[i] << '\t';
						}
					}
					else if (j == 2)
					{
						if (c[i] == 0)
						{
							cout << ".\t";
						}
						else
						{
							cout << c[i] << '\t';
						}
					}
				}
			}
			cout << '\n';
		}
		cout << "\t ----- ----- -----";
		cout << "\n\t\tA\tB\tC\n";
		cout << "\n------------------------------------------------\n";
	}
	void resetGame()
	{
		if (a && b && c)
		{
			delete a;
			delete b;
			delete c;
			a = NULL;
			b = NULL;
			c = NULL;
		}
		a = new int[size];
		b = new int[size];
		c = new int[size];
		nextIndexA = size;
		nextIndexB = 0;
		nextIndexC = 0;
		int count = size;
		for (int i = 0; i < size; i++)
		{
			a[i] = count;
			count = count - 1;
		}
		for (int i = 0; i < size; i++)
		{
			b[i] = 0;
			c[i] = 0;
		}
		moves = 0;
	}
	virtual void playGame() = 0;
};
class TowerOfHanoiGame :private TowerOfHanoiInterface
{
	bool isGameWin()
	{
		int size = getSize();
		int* c = getArrayC();
		for (int i = 0; i < size; i++)
		{
			if (c[i] == 0)
			{
				return false;
			}
		}
		return true;
	}
public:
	using TowerOfHanoiInterface::getSize;
	TowerOfHanoiGame(int n) :TowerOfHanoiInterface(n)
	{
	}
	void playGame()
	{
		resetGame();
		bool flag = false;
		char source;
		char dest;
		int invalidCheck;
		while (flag == false)
		{
			system("CLS");
			display();
			cout << "\nTotal Moves:\t" << moves;
			cout << '\n';
			cout << "\nEnter Src (A,B,C):\t";
			cin >> source;
			while (source != 'A' && source != 'B' && source != 'C')
			{
				cout << "invalid input";
				cout << "\nEnter Src (A,B,C):\t";
				cin >> source;
			}
			cout << "Enter Dst (A,B,C):\t";
			cin >> dest;
			while (source == dest || (dest != 'A' && dest != 'B' && dest != 'C'))
			{
				cout << "invalid input";
				cout << "\nEnter Dst (A,B,C):\t";
				cin >> dest;
			}
			invalidCheck = swap(source, dest);
			if (invalidCheck != 1)
			{
				if (invalidCheck == 0)
				{
					cout << "\nWarning!, a bigger number can't be place above on small number\n";
				}
				else
				{
					cout << "\nInvalid Move from " << source << " to " << dest << "\n";
				}
				system("pause");
			}
			else
			{
				moves = moves + 1;
			}
			flag = isGameWin();
		}
		system("CLS");
		display();
		cout << "Total Moves:\t" << moves;
		cout << "\nCongrats! You Solve The Tower of Hanoi Puzzle in " << moves << " moves\n";
		system("pause");
	}
};
int TowerOfHanoiInterface::moves = 0;
class TowerOfHanoiApp
{
public:
	static void TowerOfHanoiGameApp()
	{
		int size = 3;
		int option;
		TowerOfHanoiGame p(size);
		do
		{
			system("CLS");
			cout << "------------------------------------------------";
			cout << "\n\tWelcome To Tower Of Hanoi Game App\n";
			cout << "\nEnter 1 to Select No of Disks";
			cout << "\nEnter 2 to Start Game";
			cout << "\nEnter 3 to play Random No of Disk (3-7)";
			cout << "\nEnter 0 to exit the App";
			cout << "\nChoose Option:\t";
			cin >> option;
			if (option == 1)
			{
				cout << "Enter No. Of Disk for Tower Of Hanoi Game: ";
				cin >> size;
				while (size <= 0)
				{
					cout << "Invalid Input Size Must Be Greater Than Zero\n";
					cout << "Enter No. Of Disk for Tower Of Hanoi Game: ";
					cin >> size;
				}
				p.getSize() = size;
			}
			else if (option == 2)
			{
				cout << "\nGame is Starting Now";
				cout << "\nNo of Disks Are:\t" << size << '\n';
				system("pause");
				p.playGame();
			}
			else if (option == 3)
			{
				cout << "\nYour are playing Random Puzzle Game";
				size = 3 + rand() % (7 - 3 + 1);
				p.getSize() = size;
				cout << "\nGame is Starting Now";
				cout << "\nNo of Disks Are:\t" << size << '\n';
				system("pause");
				p.playGame();
			}
			else if (option == 0)
			{
				cout << "\nTowers of Hanoi Game App is Exit Now";
			}
			else
			{
				cout << "\nInvalid Option From User";
			}
		} while (option != 0);
	}
};
int main()
{
	srand(time(0));
	TowerOfHanoiApp::TowerOfHanoiGameApp();
	return 0;
}
