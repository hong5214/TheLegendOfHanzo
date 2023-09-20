//#include <windows.h>
//#include <mmsystem.h>
#include "Include.h"

#define ID_EDIT_ID 501
#define ID_EDIT_PW 502
HWND hIDinput;
HWND hPWinput;
TCHAR strID[128]; // ������ ���� �Է� ��(ID)
TCHAR strPW[128]; // ������ ���� �Է� ��(PW)

const int TICKS_PER_SECOND = 60;
const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
const int MAX_FRAMESKIP = 5;
int loops;
float interpolation;
// ���� �߰�
char buffer[128] = {0,0,0,0};
char ch[3] = {0,0,0}; //D  strcat ���� Ʋ�� �ּ� ���� ���� �ֵ��� �������
////////////////////////////////////
LRESULT CALLBACK WndProc( HWND g_hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wc;
	MSG msg;
	HWND g_hWnd ;
	wc.hInstance = GetModuleHandle( NULL ) ;
	wc.cbSize = sizeof( wc ) ;
	wc.style = CS_CLASSDC ;
	wc.cbClsExtra = NULL ;
	wc.cbWndExtra = NULL ;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH) ;
	wc.hCursor = LoadCursor( wc.hInstance, IDC_ARROW ) ;
	wc.hIcon = LoadIcon( wc.hInstance, IDI_APPLICATION ) ;
	wc.hIconSm = LoadIcon( wc.hInstance, IDI_APPLICATION ) ;
	wc.lpfnWndProc = WndProc ;
	wc.lpszClassName ="Game" ;
	wc.lpszMenuName = NULL ;

	RegisterClassEx( &wc ) ;

	RECT rt = {0, 0, SCREEN_WITH, SCREEN_HEIGHT};
	int W = rt.right - rt.left; // ���α׷��� �ʺ�
	int H = rt.bottom - rt.top; // ���α׷��� ����
	int X = (GetSystemMetrics(SM_CXSCREEN)/2) - SCREEN_WITH/2; // ���α׷��� ��µǴ� X��ǥ
	int Y = ( (GetSystemMetrics(SM_CYSCREEN)/2) - SCREEN_HEIGHT/2 ); // ���α׷��� ��µǴ� y��ǥ
	/*---------------------��-��-��-��-------------------*/

	/*
		int WINAPI GetSystemMetrics(
			int nIndex
		);

		<���ڰ�>
		SM_CXSCREEN : ȭ���� ���̸� ���� �� �ִ�.
		SM_CYSCREEN : ȭ���� ���̸� ���� �� �ִ�.

		���� ȭ���� �ػ󵵸� ���� �� �ִ�. �� �ܿ��� ���ڰ������� �پ��� ���� ���� �� �ִ�.
		�ڼ��� ������ MSDN �� GetSystemMetrics �� �����ϱ� �ٶ�
		��, ���� ����Ϳ��� ���� ���� ��� ���� ����Ϳ� ���ؼ��� ���� ���ϱ⶧���� �� �Լ��� ����ϸ� �ȵȴ�.
		���� ����Ϳ��� ��ü �ػ󵵸� ���ϱ� ���Ұ�� GetMonitorInfo �Լ��� �̿�����
	*/

	// WS_POPUP ���� �������� �����~
	g_hWnd = CreateWindowEx( NULL, wc.lpszClassName, 
		"Archero", // Ÿ��Ʋ
		WS_EX_TOPMOST, // ��� �� �߰�
		X, Y, W, H,
		NULL, NULL, wc.hInstance, NULL ) ;


	dv_font.Create(g_hWnd) ;	
	
	//g_SoundManager.Initialize(g_hWnd, DSSCL_PRIORITY);
	//g_SoundManager.SetPrimaryBufferFormat(2,22050,16);

	ShowWindow( g_hWnd, SW_SHOW ) ;
	UpdateWindow( g_hWnd ) ;
	// ���콺 �Ⱥ��̰�~	
	ShowCursor(true);

	///////////////////////////////////////////////////////////////////
	ZeroMemory(&msg, sizeof(MSG));
	//TRACE("REV ====== %s ========= \n\n", buffer);
	/////////// é�� �ʱ�ȭ /////////////////
	g_Mng.chap[LOGO] = new Logo;
	g_Mng.chap[MENU] = new Menu;
	g_Mng.chap[GAME] = new Game;
	g_Mng.chap[OVER] = new Over;
	/////////////////////////////////////////

	for(int i=0; i<TOTALCHAP; i++)
		g_Mng.chap[i]->Init();

	while( msg.message != WM_QUIT )
	{
		if(PeekMessage(&msg,NULL,0,0,PM_NOREMOVE))
		{
			if(GetMessage(&msg, NULL, 0, 0))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			
			static DWORD next_game_tick = GetTickCount();
			//static DWORD next_game_tick1 = GetTickCount();


			
			loops = 0;
		
			//static int aa;
			//bool b = false;

			while( GetTickCount64() > next_game_tick && loops < MAX_FRAMESKIP) 
			{				
				interpolation = float(GetTickCount64() + SKIP_TICKS - next_game_tick ) / float( SKIP_TICKS );
				g_Mng.chap[g_Mng.n_Chap]->Update(interpolation);
				//if(b == false)
				//{
				//	aa = interpolation;
				//	b = true;
				//}
				g_Mng.chap[g_Mng.n_Chap]->OnMessage(&msg);
				next_game_tick += SKIP_TICKS;
				loops++;
			}				

			dv_font.Device9->BeginScene();
			dv_font.Device9->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255, 255, 255), 0, 0);

			if (!BGPlayCheck()) // ���� �������� �ƴϸ� ����
				BGPlay(sound.BG);
			// �ε�ȭ�鿡�� �޴�ȭ���� �� ������ ���ڸ� ����.
			if (Gmanager.LoadingState && g_Mng.n_Chap == MENU)
			{
				if (!Gmanager.m_Pause)
				{
					hIDinput = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOVSCROLL, SCREEN_WITH / 2 - 100, SCREEN_HEIGHT / 2 - 20, 200, 32, g_hWnd, (HMENU)ID_EDIT_ID, NULL, NULL);
					hPWinput = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOVSCROLL, SCREEN_WITH / 2 - 100, SCREEN_HEIGHT / 2 + 20, 200, 32, g_hWnd, (HMENU)ID_EDIT_PW, NULL, NULL);
					SendMessage(hPWinput, EM_SETPASSWORDCHAR, '*', 0);
					Gmanager.m_Pause = !Gmanager.m_Pause; // ����Ʈ���� ���� �� �Ͻ�����
					SetFocus(hIDinput); // Ŀ���� idâ���� �̵�					
				}
				if (KeyDown(VK_UP)) // �ε�ȭ�鿡�� ���� ������
					SetFocus(hIDinput);
				else if (KeyDown(VK_DOWN)) // �ε�ȭ�鿡�� �Ʒ��� ������
					SetFocus(hPWinput);
				else if (KeyDown(VK_RETURN)) // �ε�ȭ�鿡�� ���͸� ������
				{
					// id�� pw�� �Է¹޴´�.
					GetWindowText(hIDinput, strID, 128);
					GetWindowText(hPWinput, strPW, 128);

					Gmanager.NewId = true; // ���ο� ���̵� ���� �غ�
					// sql�� �ִ� �α��������� ���Ѵ�.
					for (int i = 0; i < sql.count; i++)
					{
						// �´ٸ� �� ������ �α��� �Ѵ�.
						if (!strcmp(sql.name[i], strID)) // ���̵� ������
						{
							Gmanager.NewId = false; // ���ο� ���̵� �ƴ�
							if (!strcmp(sql.password[i], strPW)) // �н����尡 ������
							{
								sound.BGChange("./resource/Sound/BGM_Menu.mp3");
								sql.index = i; // �α����� �ε���							
								Gmanager.LoadingState = !Gmanager.LoadingState; // �ε�â ����
								Gmanager.m_Pause = !Gmanager.m_Pause; // �Ͻ����� ����
								// �����ͻ��ڸ� �����Ѵ�.
								sql.getItem(); // ������ ���� �ҷ�����
								player.Init(); // �÷��̾� ���� �ʱ�ȭ
								DestroyWindow(hIDinput);
								DestroyWindow(hPWinput);
								ShowCursor(false);
								Sleep(500); // ����Ű�� �ѹ��� �԰� �����̸� �ش�.
							}							
						}						
					}
					if (Gmanager.NewId) { // ���� ���̵� ���� ��
						if (strlen(strID) <= 10 && strlen(strPW) <= 10 && sql.count < ID_MAX) { // ID/PW�� 10�ڸ� ����, ���̵� �ִ� ���� �����϶� ����
							GetWindowText(hIDinput, sql.name[sql.count], 12);
							GetWindowText(hPWinput, sql.password[sql.count], 12);
							sql.CreateID();
						}
					}
				}
				else if (KeyDown(VK_ESCAPE))
					PostQuitMessage(0);
				continue; // �α��� ������ ���� ������ �ٸ� ȭ������ �Ѿ�� ���ϵ��� �Ѵ�.
			}

			g_Mng.chap[g_Mng.n_Chap]->Draw();

			dv_font.Device9->EndScene();
						
			dv_font.Device9->Present(NULL, NULL, NULL, NULL);
		}
	}

	return msg.wParam;

}

// Ű �ѹ��� �����Ŵ� ���Ⱑ ����...�ƴϸ� ������.(key.cpp ���� ����Ű �ȸ԰� �ϱ� ���� ������ ��������)
LRESULT CALLBACK WndProc( HWND g_hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch( uMsg )
	{
	case WM_DESTROY:
         PostQuitMessage(0);
         return 0;
	case WM_CHAR:
		 ch[0] = wParam;
		 strcat(buffer, ch);
		 // ���ڿ� ��ġ ������...
		 if (GetTickCount64() - key.KeyTime > 200)
		 {
			 if (strstr(buffer, "s") != NULL) // s�� ������
			 {
				 // ���� â Ȱ��/��Ȱ��
			 }
			 else if (strstr(buffer, "h") != NULL) // h�� ������
			 {
				 // ���� Ȱ��/��Ȱ��
			 }
			 key.KeyTime = GetTickCount64();
		 }
		 ZeroMemory( &buffer, sizeof(buffer) );
		 break;	
	}
	return DefWindowProc( g_hWnd, uMsg, wParam, lParam ) ;
}