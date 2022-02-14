#include<iostream>
#include<Windows.h>
#include<vector>
#include<fstream>
using namespace std;
void color(int textColor, int backColor = 0)
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	int colorAttribute = backColor << 4 | textColor;
	SetConsoleTextAttribute(consoleHandle, colorAttribute);
}

void draw(vector<vector<int>> &graph, vector<vector<int>> &result, vector<vector<int>> &front, int length);

void floydWarshall(vector<vector<int>> &graph, vector<vector<int>> &result ,int length)
{
	int input[4];
	int output[4];
	for (int i = 0; i < length; i++)
	{
		int in = 0;
		for (int j = 0; j < length; j++)
		{
			if (graph[i][j] != 0) {
				input[in] = j;
				in++;
			}
		}
		int o = 0;
		for (int j = 0; j < length; j++)
		{
			if (graph[j][i] != 0) {
				output[o] = j;
				o++;
			}
		}
		vector<vector<int>> front(length, vector<int>(length, 0));
		for (int i = 0;i < in;i++)
		{
			for (int j = 0;j < o;j++)
			{
				if (graph[input[i]][output[j]] != 1)
				{
					front[input[i]][output[j]] = 1;
					result[input[i]][output[j]] = 1;
				}
				graph[input[i]][output[j]] = 1;


			}
		}
		Sleep(500);
		draw(graph, result, front, length);
	}
}
int cnt = 0;
void draw(vector<vector<int>> &graph, vector<vector<int>> &result, vector<vector<int>> &front, int length)
{
	cnt++;
	if (cnt <= length)
	{
		color(8, 0);
		cout << cnt << ":" << endl;
		for (int i = 0;i < length;i++)
		{
			for (int j = 0;j < length;j++)
			{
				if (i + 1 == cnt || j + 1 == cnt)
				{
					if (front[i][j] == 1)
					{
						color(12, 17);
						cout << graph[i][j] << " ";
					}
					else
					{
						color(6, 17);
						cout << graph[i][j] << " ";
					}
				}
				else
				{
					if (front[i][j] == 1)
					{
						color(12, 0);
						cout << graph[i][j] << " ";
					}
					else
					{
						color(6, 0);
						cout << graph[i][j] << " ";
					}
				}
			}
			cout << endl;
		}
	}
	else
	{
		color(3, 0);
		cout << "\nresult is:\n";
		for (int i = 0;i < length;i++)
		{
			cout << "           ";
			for (int j = 0;j < length;j++)
			{
				if (result[i][j] == 1)
				{
					color(5, 0);
					cout << graph[i][j] << " ";
				}
				else
				{
					color(2, 0);
					cout << graph[i][j] << " ";
				}
			}
			cout << "\n";
		}
	}
}
void input(vector<vector<int>> &graph,int length)
{
	cout << "Enter the adjacency of matrix\n";
	for (int i = 0; i <length; i++)
	{
		cout << "enter for " << i + 1 << " row" << endl;
		for (int j = 0; j < 4; j++)
			cin >> graph[i][j];
	}
}
int main()
{
	int length;
	cout << "Enter the row of your matrix: ";
	cin >> length;
	
	vector<vector<int>> result(length, vector<int>(length, 0));
	vector<vector<int>> graph(length, vector<int>(length));
	input(graph,length);
	floydWarshall(graph, result, length);
	Sleep(1000);
	draw(graph, result, result, length);
	system("pause>a");
}