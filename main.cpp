#include <graphics.h> //EasyX

char board_data[3][3];

char current_piece = 'O';

bool CheckWin(char c)
{
	for (size_t i = 0; i < 3; i++)
	{
		if (board_data[i][0] == c && board_data[i][1] == c && board_data[i][2] == c)
			return true;
		if(board_data[0][i] == c && board_data[1][i] == c && board_data[2][i] == c)
			return true;
	}

	if (board_data[0][0] == c && board_data[1][1] == c && board_data[2][2] == c)
		return true;
	if (board_data[0][2] == c && board_data[1][1] == c && board_data[2][0] == c)
		return true;

	return false;
}

bool CheckDraw()
{
	for (size_t i = 0; i < 3; i++)
		for (size_t j = 0; j < 3; j++)
		{
			if (board_data[i][j] == '-')
				return false;
		}
	return true;

}

void DrawBoard()
{
	line(0, 200, 600, 200);
	line(0, 400, 600, 400);
	line(200, 0, 200, 600);
	line(400, 0, 400, 600);
}

void DrawPiece()
{
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			switch (board_data[i][j])
			{
			case 'O':
				circle(200 * j + 100, 200 * i + 100, 100); //Get Circle
				break;
			case 'X':
				line(200 * j, 200 * i, 200 * (j + 1), 200 * (i + 1)); //Get X
				line(200 * (j + 1), 200 * i, 200 * j, 200 * (i + 1));
				break;
			case '-':
				break;


			}
		}
	}

}

void DrawTipText()
{
	static TCHAR str[64];
	_stprintf_s(str, _T("当前棋子类型: %c"), current_piece); 

	settextcolor(RGB(225, 175, 45));
	outtextxy(0, 0, str);

}

int main()
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
		{
			board_data[i][j] = '-';
		}

	initgraph(600, 600);

	bool n = true; // Flag to control whether the loop continues

	ExMessage msg;

	BeginBatchDraw();

	while (n)
	{
		DWORD start_time = GetTickCount();


		while (peekmessage(&msg)) 
		{
			if (msg.message == WM_LBUTTONDOWN)
			{
				int x = msg.x;
				int y = msg.y;

				int index_x = msg.x / 200;
				int index_y = msg.y / 200;

				if (board_data[index_y][index_x] == '-')
				{
					board_data[index_y][index_x] = current_piece;

					if (current_piece == 'O')
						current_piece = 'X';

					else
						current_piece = 'O';
				}
			}
		}

		cleardevice();

		DrawBoard();
		DrawPiece();
		DrawTipText();

		FlushBatchDraw();

		if (CheckWin('X'))
		{
			MessageBox(GetHWnd(), _T("X PlayerWin"), _T("GameOver"), MB_OK);
			n = false;
		}
		if (CheckWin('O'))
		{
			MessageBox(GetHWnd(), _T("O PlayerWin"), _T("GameOver"), MB_OK);
			n = false;
		}
		if (CheckDraw())
		{
			MessageBox(GetHWnd(), _T("Draw!"), _T("GameOver"), MB_OK);
			n = false;
		}
		DWORD end_time = GetTickCount();
		DWORD delta_time = end_time - start_time;

		if (delta_time < 1000 / 60)
		{
			Sleep(1000 / 60 - delta_time);
		}

	}

	EndBatchDraw();

	return 0;
}