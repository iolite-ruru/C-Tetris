#include<iostream> 
#include<stdlib.h> 
#include<time.h> 
#include<conio.h> 
#include<Windows.h> 
#include<string.h> 
#include<thread>
#include<fstream>
#include<istream>
#include<iomanip>
#include<mmsystem.h>
#pragma comment(lib, "winmm.lib")
using namespace std;
//현재 x 마지막 값 51, y 마지막 값 38 
//벽 x:3~34 / y:2~39
#define WIDTH  16 //게임판 가로 
#define HEIGHT 26 //게임판 세로
#define UP 72 
#define DOWN 80 
#define LEFT 75 
#define RIGHT 77 
#define UNIT_LENGTH 4
#define FULL 12
int tetris[HEIGHT][WIDTH];
int scoreUnit[] = { 0, 500, 1000, 1500,  2000 };
int speedUnit[] = { 350, 300, 200, 100, 80 };
int nextBlock; //미리 선언 해둬야 함 
int nextRotation;
int unit;
int score;
int speed;
bool exe;
struct User {
	string name = "";
	int score = -1;
};
// l, ㅗ, z, s, L, L반대, ㅁ, +, U, ㄴ, ㅏ, 긴 ㅗ
const int BLOCK[FULL][4][4][4] = {
	{
		{
			0, 1, 0, 0,
			0, 1, 0, 0,
			0, 1, 0, 0,
			0, 1, 0, 0
		},
		{
			0, 0, 0, 0,
			1, 1, 1, 1,
			0, 0, 0, 0,
			0, 0, 0, 0
		},
		{
			0, 1, 0, 0,
			0, 1, 0, 0,
			0, 1, 0, 0,
			0, 1, 0, 0
		},
		{
			0, 0, 0, 0,
			1, 1, 1, 1,
			0, 0, 0, 0,
			0, 0, 0, 0
		}
	},
	{
		{
			0, 1, 0, 0,
			1, 1, 1, 0,
			0, 0, 0, 0,
			0, 0, 0, 0
		},
		{
			0, 1, 0, 0,
			0, 1, 1, 0,
			0, 1, 0, 0,
			0, 0, 0, 0
		},
		{
			0, 0, 0, 0,
			1, 1, 1, 0,
			0, 1, 0, 0,
			0, 0, 0, 0
		},
		{
			0, 1, 0, 0,
			1, 1, 0, 0,
			0, 1, 0, 0,
			0, 0, 0, 0
		}
	},
	{
		{
			1, 1, 0, 0,
			0, 1, 1, 0,
			0, 0, 0, 0,
			0, 0, 0, 0
		},
		{
			0, 0, 1, 0,
			0, 1, 1, 0,
			0, 1, 0, 0,
			0, 0, 0, 0
		},
		{
			1, 1, 0, 0,
			0, 1, 1, 0,
			0, 0, 0, 0,
			0, 0, 0, 0
		},
		{
			0, 0, 1, 0,
			0, 1, 1, 0,
			0, 1, 0, 0,
			0, 0, 0, 0
		}
	},
	{
		{
			0, 1, 1, 0,
			1, 1, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0
		},
		{
			0, 1, 0, 0,
			0, 1, 1, 0,
			0, 0, 1, 0,
			0, 0, 0, 0
		},
		{
			0, 1, 1, 0,
			1, 1, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0
		},
		{
			0, 1, 0, 0,
			0, 1, 1, 0,
			0, 0, 1, 0,
			0, 0, 0, 0
		}
	},
	{
		{
			1, 0, 0, 0,
			1, 0, 0, 0,
			1, 1, 0, 0,
			0, 0, 0, 0
		},
		{
			0, 0, 0, 0,
			1, 1, 1, 0,
			1, 0, 0, 0,
			0, 0, 0, 0
		},
		{
			1, 1, 0, 0,
			0, 1, 0, 0,
			0, 1, 0, 0,
			0, 0, 0, 0
		},
		{
			0, 0, 1, 0,
			1, 1, 1, 0,
			0, 0, 0, 0,
			0, 0, 0, 0
		}
	},
	{
		{
			0, 1, 0, 0,
			0, 1, 0, 0,
			1, 1, 0, 0,
			0, 0, 0, 0
		},
		{
			1, 0, 0, 0,
			1, 1, 1, 0,
			0, 0, 0, 0,
			0, 0, 0, 0
		},
		{
			0, 1, 1, 0,
			0, 1, 0, 0,
			0, 1, 0, 0,
			0, 0, 0, 0
		},
		{
			0, 0, 0, 0,
			1, 1, 1, 0,
			0, 0, 1, 0,
			0, 0, 0, 0
		}
	},
	{
		{
			1, 1, 0, 0,
			1, 1, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0
		},
		{
			1, 1, 0, 0,
			1, 1, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0
		},
		{
			1, 1, 0, 0,
			1, 1, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0
		},
		{
			1, 1, 0, 0,
			1, 1, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0
		}
	},
	{
		{
			0, 1, 0, 0,
			1, 1, 1, 0,
			0, 1, 0, 0,
			0, 0, 0, 0
		},
		{
			0, 1, 0, 0,
			1, 1, 1, 0,
			0, 1, 0, 0,
			0, 0, 0, 0
		},
		{
			0, 1, 0, 0,
			1, 1, 1, 0,
			0, 1, 0, 0,
			0, 0, 0, 0
		},
		{
			0, 1, 0, 0,
			1, 1, 1, 0,
			0, 1, 0, 0,
			0, 0, 0, 0
		}
	},
	{
		{
			1, 0, 1, 0,
			1, 1, 1, 0,
			0, 0, 0, 0,
			0, 0, 0, 0
		},
		{
			0, 1, 1, 0,
			0, 1, 0, 0,
			0, 1, 1, 0,
			0, 0, 0, 0
		},
		{
			0, 0, 0, 0,
			1, 1, 1, 0,
			1, 0, 1, 0,
			0, 0, 0, 0
		},
		{
			1, 1, 0, 0,
			0, 1, 0, 0,
			1, 1, 0, 0,
			0, 0, 0, 0
		}
	},
	{
		{
			1, 0, 0, 0,
			1, 0, 0, 0,
			1, 1, 1, 0,
			0, 0, 0, 0
		},
		{
			1, 1, 1, 0,
			1, 0, 0, 0,
			1, 0, 0, 0,
			0, 0, 0, 0
		},
		{
			1, 1, 1, 0,
			0, 0, 1, 0,
			0, 0, 1, 0,
			0, 0, 0, 0
		},
		{
			0, 0, 1, 0,
			0, 0, 1, 0,
			1, 1, 1, 0,
			0, 0, 0, 0
		}
	},
	{
		{
			0, 1, 0, 0,
			1, 1, 0, 0,
			0, 1, 0, 0,
			0, 1, 0, 0
		},
		{
			0, 0, 1, 0,
			1, 1, 1, 1,
			0, 0, 0, 0,
			0, 0, 0, 0
		},
		{
			0, 1, 0, 0,
			0, 1, 0, 0,
			0, 1, 1, 0,
			0, 1, 0, 0
		},
		{
			0, 0, 0, 0,
			1, 1, 1, 1,
			0, 1, 0, 0,
			0, 0, 0, 0
		}
	},
	{
		{
			0, 1, 0, 0,
			0, 1, 0, 0,
			1, 1, 1, 0,
			0, 0, 0, 0
		},
		{
			1, 0, 0, 0,
			1, 1, 1, 0,
			1, 0, 0, 0,
			0, 0, 0, 0
		},
		{
			1, 1, 1, 0,
			0, 1, 0, 0,
			0, 1, 0, 0,
			0, 0, 0, 0
		},
		{
			0, 0, 1, 0,
			1, 1, 1, 0,
			0, 0, 1, 0,
			0, 0, 0, 0
		}
	}
};
void ShowCursor(bool b)
{
	CONSOLE_CURSOR_INFO cursor = { 0, };
	cursor.dwSize = 1;
	cursor.bVisible = b;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}
void GotoXY(int x, int y) {
	COORD coord; //COORD : x, y값을 가지는 구조체 타입 
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
POINT GetXY() {
	POINT p;
	GetCursorPos(&p);
	return p;
}
int KeyInput() {
	char key = _getch();
	switch (toupper(key)) {
	case 'W': return UP;
	case 'S': return DOWN;
	case 'A': return LEFT;
	case 'D': return RIGHT;
	case 13: return 13;
	default: return -1;
	}
}
class Block {
public:
	int x, y, block, cnt; //x, y는 tetris 배열 내의 좌표(벽 포함)
	Block(int block, int rotation) {
		x = WIDTH / 2 - 1; //tetris[0]은 벽
		y = 1;
		this->block = block;
		cnt = rotation;
		Draw();
	}
	void Draw() {
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (BLOCK[block][GetRotation()][i][j] == 1 && tetris[y + i][x + j] == 0) tetris[y + i][x + j] = 1;
			}
		}
	}
	void Remove() {
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (BLOCK[block][GetRotation()][i][j] == 1 && tetris[y + i][x + j] == 1)
					tetris[y + i][x + j] = 0;
			}
		}
	}
	void RemoveBlock() {
		for (int i = 0; i < 4; i++) {
			int x_temp = x, y_temp = y + i + 1; //T 내의 x, y좌표에 대해서
			for (int j = 0; j < 4; j++) {
				if (BLOCK[block][GetRotation()][i][j] == 1 && tetris[y + i][x + j] == 1) {
					GotoXY((x_temp + j) * 2 + 2, y_temp);
					cout << "　";
				}
			}
		}
	}
	void DrawBlock() {
		for (int i = 0; i < 4; i++) {
			int x_temp = x, y_temp = y + i + 1;
			for (int j = 0; j < 4; j++) {
				GotoXY((x_temp + j) * 2 + 2, y_temp);
				if (tetris[y + i][x + j] == 1 && BLOCK[block][GetRotation()][i][j] == 1) cout << "■";
			}
		}
	}
	void Down() {
		if ((this->CheckFloor()) == false) {
			RemoveBlock();
			Remove();
			y++;
			Draw();
			DrawBlock();
		}
	}
	bool CheckLeft(int x, int y, int cnt) {
		for (int i = 0; i < 4; i++) //행
		{
			for (int j = 0; j < 4; j++) //열
			{
				if (BLOCK[block][GetRotation()][i][j] == 1) {
					if (tetris[y + i][x + j - 1] > 0) return false;
					else break;
				}
			}
		}
		return true;
	}
	bool CheckRight(int x, int y, int cnt) {
		for (int i = 0; i < 4; i++) //행
		{
			for (int j = 3; j >= 0; j--) //열
			{
				if (BLOCK[block][GetRotation()][i][j] == 1) {
					if (tetris[y + i][x + j + 1] > 0) return false;
					else break;
				}
			}
		}
		return true;
	}
	bool CheckUp(int x, int y, int cnt) {
		bool check = true;
		int x_temp = 3, y_temp = 3;
		//현재 블럭 모양 지움
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				if (BLOCK[block][GetRotation()][i][j] == 1)
					if (tetris[y + i][x + j] == 1) tetris[y + i][x + j] = 0;
		//다음 블럭 모양 출력
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++)
				if (BLOCK[block][cnt % 4][i][j] == 1) {
					if (tetris[y + i][x + j] == 0) tetris[y + i][x + j] = 1;
					else { //블록 또는 벽과 충돌했을 경우
						check = false;
						x_temp = j;
						y_temp = i;
						goto label;
					}
				}
		}
	label:
		//다음 블럭 모양 지움
		for (int i = 0; i <= y_temp; i++) {
			int temp = 3;
			if (i == y_temp) temp = x_temp - 1;
			for (int j = 0; j <= temp; j++)
				if (BLOCK[block][cnt % 4][i][j] == 1)
					if (tetris[y + i][x + j] == 1) tetris[y + i][x + j] = 0;
		}
		//현재 블럭 모양 출력
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++)
				if (BLOCK[block][GetRotation()][i][j] == 1) tetris[y + i][x + j] = 1;
		}
		return check;
	}
	bool CheckFloor() {
		bool temp = true;
		for (int i = 3; i >= 0; i--)
		{
			for (int j = 0; j < 4; j++)
			{
				if (BLOCK[block][GetRotation()][i][j] == 1) {
					if (i != 3 && BLOCK[block][GetRotation()][i + 1][j] == 0) {
						if (tetris[y + i + 1][x + j] > 0) return true; //충돌 있다면 바로 종료
					}
					else if (i == 3) {
						if (tetris[y + i + 1][x + j] > 0) return true; //충돌 있다면 바로 종료
					}
				}
			}
		}
		return false;
	}
	void Move() {
		switch (KeyInput()) {
		case LEFT:
			if (CheckLeft(x, y, cnt)) {
				RemoveBlock(); Remove(); x--; Draw(); DrawBlock();
			} break;
		case RIGHT:
			if (CheckRight(x, y, cnt)) {
				RemoveBlock();  Remove(); x++; Draw(); DrawBlock();
			} break;
		case DOWN:
			if (CheckFloor() == false) {
				RemoveBlock(); Remove(); y++; Draw(); DrawBlock();
			} break;
		case UP:
			if (CheckUp(x, y, cnt + 1)) {
				RemoveBlock();  Remove(); cnt++; Draw(); DrawBlock();
			} break;
		}
	}
	int GetRotation() {
		return cnt % 4;
	}
};
Block* block; //미리 객체 생성
void DrawScore() {
	GotoXY(38, 1);
	cout << "┌───────────┐";
	GotoXY(38, 2);
	cout << "│   SCORE   │";
	GotoXY(38, 3);
	cout << "├───────────┤";
	GotoXY(38, 4);
	cout << "│           │";
	GotoXY(38, 5);
	cout << "└───────────┘";
}
void DrawNext() {
	GotoXY(38, 7);
	cout << "┌───────────┐";
	GotoXY(38, 8);
	cout << "│ NEXT BLOCK│";
	GotoXY(38, 9);
	cout << "├───────────┤";
	GotoXY(38, 10);
	cout << "│           │";
	GotoXY(38, 11);
	cout << "│           │";
	GotoXY(38, 12);
	cout << "│           │";
	GotoXY(38, 13);
	cout << "│           │";
	GotoXY(38, 14);
	cout << "└───────────┘";
}
void DrawNextBlock(int block, int rotation) {
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			GotoXY(42 + j * 2, 10 + i);
			if (BLOCK[block][rotation][i][j] == 1) cout << "■";
			else cout << "　";
		}
	}
}
void PrintScore() {
	GotoXY(40, 4);
	printf("%9d", score);
}
void DrawMap() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	PrintScore();
	int temp_x = 2;
	for (int i = 0; i < HEIGHT; i++) { //출력
		temp_x = 2;
		GotoXY(temp_x, i + 1); //여백 주기 위함 
		for (int j = 0; j < WIDTH; j++) {
			if (true) {
				switch (tetris[i][j]) {
				case 1: cout << "■"; break;
				case 2: cout << "▩"; break;
				default: cout << "　";
				}
			}
		}
		cout << endl;
	}
}
bool CheckOver() {
	for (int j = 1; j < WIDTH - 1; j++) {
		if (tetris[1][j] == 1) return false; //게임오버
	}
	return true; //게임 계속 진행
}
bool CheckRow() {
	int count;
	bool checkRow = false;
	for (int i = HEIGHT - 2; i > 0; i--) { //i : 행. 0보다 클 때까지.
		count = 0;
		for (int j = 1; j < WIDTH - 1; j++) //j : 열
			if (tetris[i][j] == 1) count++;
		//한 줄이 다 찼을 때의 실행
		if (count == WIDTH - 2) {
			Sleep(600); //첨에는 Sleep이 DrawMap() 밑에 있었음!!
			score += 100; //점수 증가
			PrintScore(); //점수 출력
			checkRow = true;
			for (int q = i; q > 0; q--) { //q : 행
				for (int p = 1; p < WIDTH - p; p++) //p : 열
					if (tetris[q - 1][p] != 2) tetris[q][p] = tetris[q - 1][p];
			}
			PlaySound(TEXT("success.wav"), NULL, SND_FILENAME | SND_ASYNC);
			DrawMap();
		}
	}
	if (checkRow && unit < UNIT_LENGTH) {
		if (score >= scoreUnit[unit + 1])
			speed = speedUnit[++unit];
	}
	return checkRow;
}
void BlockDownThread() {
	while (exe) {
		if ((block->CheckFloor()) == false) {
			Sleep(speed);
			block->Down();
		}
	}
}
void CreateBlock() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	srand((unsigned)time(0));
	int nowBlock = nextBlock;
	int nowRotation = nextRotation;
	nextBlock = rand() % FULL;
	nextRotation = rand() % 4;
	DrawNextBlock(nextBlock, nextRotation);
	block = new Block(nowBlock, nowRotation);
	block->DrawBlock();
	exe = true;
	thread threadTest(BlockDownThread);
	while (true) {
		if (block->CheckFloor()) break; //참==바닥 -> 중지
		block->Move();
	}
	exe = false;
	threadTest.join();
	block->~Block();
	PlaySound(TEXT("land.wav"), NULL, SND_FILENAME | SND_ASYNC);
	DrawMap();
}
void DrawUser() {
	string name;
	cout << " ※User 이름은 8글자 이내※" << endl;
	cout << " User 이름 입력: ";
	ShowCursor(true);
	cin >> name;
	ShowCursor(false);
	name.erase(remove(name.begin(), name.end(), ' '), name.end());
	if (name.length() > 16) name = name.substr(0, 16);

	User user[10];
	ifstream file("ranking.txt");
	int userScore;
	string userName;
	int _while = 0;

	while (file >> userScore >> userName) {
		user[_while].score = userScore;
		user[_while].name = userName;
		_while++;
		if (_while > 10)break;
	}
	if (score < user[9].score) return;
	for (int i = 0; i < 10; i++) {
		if (score > user[i].score) {
			for (int j = 8; j >= i; j--) {
				user[j + 1].score = user[j].score;
				user[j + 1].name = user[j].name;
			}
			user[i].score = score;
			user[i].name = name;
			break;
		}
	}
	ofstream file_o("ranking.txt");
	for (int i = 0; i < 10; i++) {
		file_o << user[i].score << "\t" << user[i].name << endl;
	}
}
void DrawPlay() {
	system("cls");
	for (int i = 0; i < HEIGHT; i++) { //할당 
		for (int j = 0; j < WIDTH; j++) {
			if (i == 0 || i == HEIGHT - 1 || j == 0 || j == WIDTH - 1)
				tetris[i][j] = 2; //벽 
			else tetris[i][j] = 0; //공백 
		}
	}
	DrawMap();
	DrawScore();
	DrawNext();
}
int ShowPlay() {
	DrawPlay();
	PrintScore();
	srand((unsigned)time(0));
	nextBlock = rand() % FULL;
	nextRotation = rand() % 4;
	unit = 0;
	score = 0;
	speed = speedUnit[unit];

	//실행 while문 
	bool _playing = true;
	while (_playing) {
		bool _block = true;
		bool _checkRow = true;
		while (_block) {
			Sleep(600);
			thread createBlock(CreateBlock);
			_block = false;
			createBlock.join();
		}
		while (_checkRow) {
			_checkRow = CheckRow();
		}
		_playing = CheckOver();
	} //While End
	PlaySound(TEXT("game_over.wav"), NULL, SND_FILENAME | SND_ASYNC);
	Sleep(1000);
	GotoXY(0, 27);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	cout << "=======================================================" << endl;
	cout << " 게임이 종료되었습니다." << endl;
	cout << " 점수 : " << score << endl;
	DrawUser();
	cout << "=======================================================" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cout << "※메인 화면으로 돌아가려면 Backspace를 누르세요" << endl;
	while (true) {
		if (_getch() == 8) break;
	}
	return 0;
}
int ShowRule() {
	system("cls");

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	cout << endl << "=======================================================" << endl;
	cout << "======================== RULES ========================" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cout << " 1. 7가지 모양의 블럭들을 쌓아갑니다." << endl;
	cout << " 2. 각 행이 블럭으로 채워질 때마다 해당 행은 사라지고\n    점수가 올라갑니다." << endl;
	cout << " 3. 블럭이 천장까지 쌓이는 순간 게임이 종료됩니다." << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	cout << endl << "=======================================================" << endl;
	cout << "========================= KEY =========================" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cout << " 모든 조작은 키보드 입력을 기준으로 합니다." << endl;
	cout << " W : Rotation 블럭 회전(시계방향)\n A : Left 블럭 왼쪽으로 이동\n D : Right 블럭 오른쪽으로 이동\n S : Down 블럭 아래로 이동" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	cout << endl << "=======================================================";
	cout << "======================== SOUND ========================" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cout << " free sound : grunz, myfox14, sharesynth" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	cout << endl << "=======================================================" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	GotoXY(1, 36);
	cout << "※메인 화면으로 돌아가려면 Backspace를 누르세요" << endl;
	while (true) {
		if (_getch() == 8) {
			PlaySound(TEXT("menu_select.wav"), NULL, SND_FILENAME | SND_ASYNC);
			return 0;
		}
	}
}
int ShowRank() {
	system("cls");
	//cout<<"\u25A0"<<endl;
	ifstream file("ranking.txt");
	int rank = 1;
	int score;
	string userName;
	int x = 4, y = 8;
	int j = 2;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	cout << endl;
	cout << "=======================================================" << endl;
	cout << ":::::::::::::::::::::::::::::::::::::::::::::::::::::::" << endl;
	cout << ":::::::::::::::::::::::::::::::::::::::::::::::::::::::" << endl;
	cout << "======================  RANKING  ======================" << endl;
	cout << ":::::::::::::::::::::::::::::::::::::::::::::::::::::::" << endl;
	cout << ":::::::::::::::::::::::::::::::::::::::::::::::::::::::" << endl;
	cout << "=======================================================" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	GotoXY(x, y);
	cout << "┌────────────┬──────────────────┬───────────┐";
	GotoXY(x, y + 1);
	cout << "│    순위    │       이름       │    점수   │" << endl;

	int i = y + 1;
	while (file >> score >> userName) {
		if (score == -1) break;
		GotoXY(x, y + j++);
		cout << "│────────────┼──────────────────┼───────────│";
		GotoXY(x, y + j++);
		cout << "│            │                  │           │";
		GotoXY(x + 5, i += 2);
		cout << setw(2) << rank++ << "위";
		GotoXY(x + 16, i);
		cout << setw(16) << userName;
		GotoXY(x + 34, i);
		printf("%8d점", score);
	}
	GotoXY(x, y + j);
	cout << "└────────────┴──────────────────┴───────────┘";
	GotoXY(23, 32);
	cout << "ㄴ(◑_◑)ㄱ";
	GotoXY(1, 36);
	cout << endl << "※메인 화면으로 돌아가려면 Backspace를 누르세요" << endl;
	while (true) {
		if (_getch() == 8) {
			PlaySound(TEXT("menu_select.wav"), NULL, SND_FILENAME | SND_ASYNC);
			return 0;
		}
	}
}
int ShowMain() {
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	GotoXY(26, 4);
	cout << ".-. " << endl;
	GotoXY(26, 5);
	cout << "|   ++" << endl;
	GotoXY(26, 6);
	cout << "`-' " << endl;
	GotoXY(0, 7);
	cout << "  _______  _______  _______  ______    ___   _______ " << endl;
	cout << " |       ||       ||       ||    _ |  |   | |       |" << endl;
	cout << " |_     _||    ___||_     _||   | ||  |   | |  _____|" << endl;
	cout << "   |   |  |   |___   |   |  |   |_||_ |   | | |_____ " << endl;
	cout << "   |   |  |    ___|  |   |  |    __  ||   | |_____  |" << endl;
	cout << "   |   |  |   |___   |   |  |   |  | ||   |  _____| |" << endl;
	cout << "   |___|  |_______|  |___|  |___|  |_||___| |_______|" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	//GotoXY(24, 15);
	//cout << "C++ Tetris" << endl << endl; //제목 크게 만들기 
	GotoXY(13, 17);
	cout << "UP : W | DOWN : S | SELECT : Enter";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	GotoXY(43, 31);
	cout << "2103 김소연";
	GotoXY(38, 32);
	cout << "Git: iolite-ruru";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	int x = 22, y = 22, _y = y;
	int selectKey = 0;
	GotoXY(x, y);
	while (true) {
		GotoXY(x, y);
		cout << "  게임 시작";
		GotoXY(x, y + 1);
		cout << "  게임 설명";
		GotoXY(x, y + 2);
		cout << "  랭킹 보기";
		GotoXY(x, y + 3);
		cout << "    종료";
		GotoXY(x, _y);
		cout << "> ";
		int key = KeyInput();
		switch (key) {
		case UP:
			if (_y != y) {
				GotoXY(x, --_y);
				PlaySound(TEXT("menu_select.wav"), NULL, SND_FILENAME | SND_ASYNC);
			}
			break;
		case DOWN:
			if (_y != y + 3) {
				GotoXY(x, ++_y);
				PlaySound(TEXT("menu_select.wav"), NULL, SND_FILENAME | SND_ASYNC);
			}
			break;
		case 13: //Enter키 아스키코드 값 
			switch (_y) {
			case 22: selectKey = 0; break;
			case 23: selectKey = 1; break;
			case 24: selectKey = 2; break;
			case 25: selectKey = 3; break;
			}
			goto skip;
		default: break;
		}
	}
skip:
	return selectKey;
}
int main() {
	system("mode con cols=55 lines=35");
	system("title C++ Tetris");
	//srand((unsigned)time(0));
	ShowCursor(false);
	bool _while = true;
	while (_while) {
		int key = ShowMain();
		switch (key) {
		case 0: ShowPlay(); break;
		case 1: ShowRule(); break;
		case 2: ShowRank(); break;
		case 3: _while = false; break;
		}
	}
	GotoXY(0, 35);
	system("pause");
	return 0;
}