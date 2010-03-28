#define WIN32_LEAN_AND_MEAN

#if defined (_MSC_VER)

#pragma warning( disable : 4244 )
#endif

#include "Base.h"
#include "Game.h"

Game g_game;


// NOTE: Leaving this here, in case someone wants to port from ZiiWakeBreaker->Windows in the future, but I don't have a Windows box

#ifdef WIN32_CODE
LONG WINAPI MainWndProc(HWND, UINT, WPARAM, LPARAM);

#define WINDOW_WIDTH     320
#define WINDOW_HEIGHT    240

const char g_appName[] = "Wake Breaker";
HWND ghWnd;

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,
				   LPSTR lpCmdLine,int nCmdShow)
{
    WNDCLASS wndclass =
	{
		0,
		(WNDPROC)MainWndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor (NULL,IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW+1),
		g_appName,
		g_appName
	};

    if(!RegisterClass(&wndclass))
        return FALSE;

    ghWnd = CreateWindow(g_appName,
                         g_appName,
                         WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
                         CW_USEDEFAULT,
                         CW_USEDEFAULT,
                         WINDOW_WIDTH,
                         WINDOW_HEIGHT,
                         NULL,
                         NULL,
                         hInstance,
                         NULL);

    if(!ghWnd)
        return FALSE;

    ShowWindow (ghWnd, nCmdShow);
    UpdateWindow (ghWnd);

	g_game.Create(WINDOW_WIDTH,WINDOW_HEIGHT,&ghWnd);



	MSG msg;

    while(1)
    {
        RECT rc;
        while(PeekMessage(&msg,NULL,0,0,PM_NOREMOVE) == TRUE)
        {
            if(GetMessage(&msg,NULL,0,0))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
            else
                return 0;
        }




		//calculate how long it takes to draw one frame
		float frameTime = GetTickCount();
		g_game.Menu();
		frameTime = GetTickCount() - frameTime;

		//this tick essentially has to happen 30 times a second
		//so that means it has 33 milliseconds to fill

		//therefore, we must wait
		float waitTime = 33 - frameTime;
		if(waitTime < 0)
			waitTime = 0;

		Sleep(waitTime);




    }

}


LONG WINAPI MainWndProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
    LONG lRet = 1;
    switch (uMsg)
    {
    case WM_CLOSE:
		{
			DestroyWindow (hWnd);
		} break;
    case WM_DESTROY:
		{

			/* Destroy all EGL resources */
			g_game.Destroy();
			PostQuitMessage (0);
        }break;
    case WM_KEYDOWN:
		{
			if(wParam == VK_ESCAPE)
				SendMessage(hWnd, WM_CLOSE, 0, 0);
			if(wParam == VK_LEFT)
				g_game.KeyDown(G_LEFT);

			if(wParam == VK_UP)
				g_game.KeyDown(G_UP);

			if(wParam == VK_RIGHT)
				g_game.KeyDown(G_RIGHT);

			if(wParam == VK_DOWN)
				g_game.KeyDown(G_DOWN);

			if(wParam == VK_RETURN)
				g_game.KeyDown(G_OK);

			if(wParam == VK_NUMPAD1)
				g_game.KeyDown(G_DEVICE1);

			if(wParam == VK_NUMPAD2)
				g_game.KeyDown(G_DEVICE2);
		} break;
	case WM_KEYUP:
		{
			if(wParam == VK_ESCAPE)
				SendMessage(hWnd, WM_CLOSE, 0, 0);
			if(wParam == VK_LEFT)
				g_game.KeyUp(G_LEFT);

			if(wParam == VK_UP)
				g_game.KeyUp(G_UP);

			if(wParam == VK_RIGHT)
				g_game.KeyUp(G_RIGHT);

			if(wParam == VK_DOWN)
				g_game.KeyUp(G_DOWN);
			if(wParam == VK_RETURN)
				g_game.KeyUp(G_OK);

			if(wParam == VK_NUMPAD1)
				g_game.KeyUp(G_DEVICE1);

			if(wParam == VK_NUMPAD2)
				g_game.KeyUp(G_DEVICE2);
		} break;
    default:
        lRet = DefWindowProc(hWnd, uMsg, wParam, lParam);
        break;
    }
    return lRet;
}

#endif
