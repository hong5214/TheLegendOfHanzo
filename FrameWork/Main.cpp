//#include <windows.h>
//#include <mmsystem.h>
#include "Include.h"

#define ID_EDIT_ID 501
#define ID_EDIT_PW 502
HWND hIDinput;
HWND hPWinput;
TCHAR strID[128]; // 에디터 상자 입력 값(ID)
TCHAR strPW[128]; // 에디터 상자 입력 값(PW)

const int TICKS_PER_SECOND = 60;
const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
const int MAX_FRAMESKIP = 5;
int loops;
float interpolation;
// 버퍼 추가
char buffer[128] = {0,0,0,0};
char ch[3] = {0,0,0}; //D  strcat 사용법 틀림 최소 널이 들어갈수 있도록 해줘야함
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
	int W = rt.right - rt.left; // 프로그램의 너비
	int H = rt.bottom - rt.top; // 프로그램의 높이
	int X = (GetSystemMetrics(SM_CXSCREEN)/2) - SCREEN_WITH/2; // 프로그램이 출력되는 X좌표
	int Y = ( (GetSystemMetrics(SM_CYSCREEN)/2) - SCREEN_HEIGHT/2 ); // 프로그램이 출력되는 y좌표
	/*---------------------요-기-까-지-------------------*/

	/*
		int WINAPI GetSystemMetrics(
			int nIndex
		);

		<인자값>
		SM_CXSCREEN : 화면의 넓이를 구할 수 있다.
		SM_CYSCREEN : 화면의 높이를 구할 수 있다.

		현재 화면의 해상도를 구할 수 있다. 이 외에도 인자값에따라 다양한 값을 구할 수 있다.
		자세한 사항은 MSDN 의 GetSystemMetrics 를 참고하길 바람
		단, 다중 모니터에서 값을 구할 경우 메인 모니터에 대해서만 값을 구하기때문에 이 함수를 사용하면 안된다.
		다중 모니터에서 전체 해상도를 구하길 원할경우 GetMonitorInfo 함수를 이용하자
	*/

	// WS_POPUP 빼면 테투리가 생긴다~
	g_hWnd = CreateWindowEx( NULL, wc.lpszClassName, 
		"Archero", // 타이틀
		WS_EX_TOPMOST, // 상단 바 추가
		X, Y, W, H,
		NULL, NULL, wc.hInstance, NULL ) ;


	dv_font.Create(g_hWnd) ;	
	
	//g_SoundManager.Initialize(g_hWnd, DSSCL_PRIORITY);
	//g_SoundManager.SetPrimaryBufferFormat(2,22050,16);

	ShowWindow( g_hWnd, SW_SHOW ) ;
	UpdateWindow( g_hWnd ) ;
	// 마우스 안보이게~	
	ShowCursor(true);

	///////////////////////////////////////////////////////////////////
	ZeroMemory(&msg, sizeof(MSG));
	//TRACE("REV ====== %s ========= \n\n", buffer);
	/////////// 챕터 초기화 /////////////////
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

			if (!BGPlayCheck()) // 음악 실행중이 아니면 실행
				BGPlay(sound.BG);
			// 로딩화면에서 메뉴화면일 때 에디터 상자를 띄운다.
			if (Gmanager.LoadingState && g_Mng.n_Chap == MENU)
			{
				if (!Gmanager.m_Pause)
				{
					hIDinput = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOVSCROLL, SCREEN_WITH / 2 - 100, SCREEN_HEIGHT / 2 - 20, 200, 32, g_hWnd, (HMENU)ID_EDIT_ID, NULL, NULL);
					hPWinput = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOVSCROLL, SCREEN_WITH / 2 - 100, SCREEN_HEIGHT / 2 + 20, 200, 32, g_hWnd, (HMENU)ID_EDIT_PW, NULL, NULL);
					SendMessage(hPWinput, EM_SETPASSWORDCHAR, '*', 0);
					Gmanager.m_Pause = !Gmanager.m_Pause; // 에디트상자 생성 후 일시정지
					SetFocus(hIDinput); // 커서를 id창으로 이동					
				}
				if (KeyDown(VK_UP)) // 로딩화면에서 위를 누르면
					SetFocus(hIDinput);
				else if (KeyDown(VK_DOWN)) // 로딩화면에서 아래를 누르면
					SetFocus(hPWinput);
				else if (KeyDown(VK_RETURN)) // 로딩화면에서 엔터를 누르면
				{
					// id와 pw를 입력받는다.
					GetWindowText(hIDinput, strID, 128);
					GetWindowText(hPWinput, strPW, 128);

					Gmanager.NewId = true; // 새로운 아이디 생성 준비
					// sql에 있는 로그인정보와 비교한다.
					for (int i = 0; i < sql.count; i++)
					{
						// 맞다면 그 정보로 로그인 한다.
						if (!strcmp(sql.name[i], strID)) // 아이디가 맞으면
						{
							Gmanager.NewId = false; // 새로운 아이디가 아님
							if (!strcmp(sql.password[i], strPW)) // 패스워드가 맞으면
							{
								sound.BGChange("./resource/Sound/BGM_Menu.mp3");
								sql.index = i; // 로그인한 인덱스							
								Gmanager.LoadingState = !Gmanager.LoadingState; // 로딩창 해제
								Gmanager.m_Pause = !Gmanager.m_Pause; // 일시정지 해제
								// 에디터상자를 제거한다.
								sql.getItem(); // 아이템 정보 불러오기
								player.Init(); // 플레이어 정보 초기화
								DestroyWindow(hIDinput);
								DestroyWindow(hPWinput);
								ShowCursor(false);
								Sleep(500); // 엔터키를 한번만 먹게 딜레이를 준다.
							}							
						}						
					}
					if (Gmanager.NewId) { // 같은 아이디가 없을 때
						if (strlen(strID) <= 10 && strlen(strPW) <= 10 && sql.count < ID_MAX) { // ID/PW가 10자리 이하, 아이디가 최대 개수 이하일때 생성
							GetWindowText(hIDinput, sql.name[sql.count], 12);
							GetWindowText(hPWinput, sql.password[sql.count], 12);
							sql.CreateID();
						}
					}
				}
				else if (KeyDown(VK_ESCAPE))
					PostQuitMessage(0);
				continue; // 로그인 정보가 맞을 때까지 다른 화면으로 넘어가지 못하도록 한다.
			}

			g_Mng.chap[g_Mng.n_Chap]->Draw();

			dv_font.Device9->EndScene();
						
			dv_font.Device9->Present(NULL, NULL, NULL, NULL);
		}
	}

	return msg.wParam;

}

// 키 한번만 먹을거는 여기가 안전...아니면 귀찮다.(key.cpp 에서 연속키 안먹게 하기 위해 로직이 더러워짐)
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
		 // 문자열 위치 가져옴...
		 if (GetTickCount64() - key.KeyTime > 200)
		 {
			 if (strstr(buffer, "s") != NULL) // s를 누르면
			 {
				 // 스탯 창 활성/비활성
			 }
			 else if (strstr(buffer, "h") != NULL) // h를 누르면
			 {
				 // 도움말 활성/비활성
			 }
			 key.KeyTime = GetTickCount64();
		 }
		 ZeroMemory( &buffer, sizeof(buffer) );
		 break;	
	}
	return DefWindowProc( g_hWnd, uMsg, wParam, lParam ) ;
}