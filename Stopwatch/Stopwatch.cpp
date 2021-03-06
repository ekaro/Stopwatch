// Stopwatch.cpp : Defines the entry point for the application.
//

#include <windows.h>
#include <tchar.h>
#include <array>
#include <Windowsx.h>

// Forward declaration of functions included in this module:
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// Window properties
int WindowWidth = 300;
int WindowHeight = 300;

// location properties
int xPos;
int yPos;

static bool State = false;
std::array<int, 3> Timer = {0, 0, 0};

// Button properties
HWND StartButton;
HWND StopButton;
HWND ResetButton;
int FontHeight;
HFONT ButtonFont;
LOGFONT logFont;

// Button functions

void Start()
{
	State = true;
}

void Stop()
{

}

void Reset()
{

}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	const wchar_t szWindowClass[] = L"WinApp";
	static TCHAR szTitle[] = _T("Stopwatch");

	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));  // wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			_T("Call to RegisterClassEx failed!"),
			_T("Windows Desktop Guided Tour"),
			NULL);

		return 1;
	}

	HWND hWnd = CreateWindow(
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		WindowWidth, WindowHeight,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (IsWindow(hWnd))
	{
		DWORD dwStyle = GetWindowLongPtr(hWnd, GWL_STYLE);
		DWORD dwExStyle = GetWindowLongPtr(hWnd, GWL_EXSTYLE);
		HMENU menu = GetMenu(hWnd);

		RECT rc = { 0, 0, WindowWidth, WindowHeight };

		AdjustWindowRectEx(&rc, dwStyle, menu ? TRUE : FALSE, dwExStyle);

		SetWindowPos(hWnd, NULL, 0, 0, rc.right - rc.left, rc.bottom - rc.top, SWP_NOZORDER | SWP_NOMOVE);
	}

	if (!hWnd)
	{
		MessageBox(NULL,
			_T("Call to CreateWindow failed!"),
			_T("Windows Desktop Guided Tour"),
			NULL);

		return 1;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

#define START_BUTTON 1
#define STOP_BUTTON 1
#define RESET_BUTTON 1

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR display_msg[] = _T("Message in window");

	switch (message)
	{
	case WM_CREATE:

		StartButton = CreateWindow(
			L"BUTTON",
			L"New Game",
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
			0,
			0,
			WindowWidth / 3,
			WindowHeight / 3,
			hWnd,
			(HMENU)START_BUTTON,
			NULL,
			NULL
		);

		StopButton = CreateWindow(
			L"BUTTON",
			L"Stop",
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
			WindowWidth / 3,
			0,
			WindowWidth / 3,
			WindowHeight / 3,
			hWnd,
			(HMENU)STOP_BUTTON,
			NULL,
			NULL
		);

		ResetButton = CreateWindow(
			L"BUTTON",
			L"Reset",
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
			WindowWidth / 3 * 2,
			0,
			WindowWidth / 3,
			WindowHeight / 3,
			hWnd,
			(HMENU)RESET_BUTTON,
			NULL,
			NULL
		);

	case WM_COMMAND:

		if (LOWORD(wParam) == START_BUTTON)
		{
			//NewDeck.NewGame();
			RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE);
		}
		break;

	case WM_PAINT:

		hdc = BeginPaint(hWnd, &ps);

		//NewDeck.DrawDeck(hdc, hWnd);

		EndPaint(hWnd, &ps);
		break;

	case WM_LBUTTONDOWN:

		xPos = GET_X_LPARAM(lParam);
		yPos = GET_Y_LPARAM(lParam);

		break;

	case WM_SIZE:

		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
	return 0;
}