// Versuch2.cpp : Definiert den Einstiegspunkt der Anwendung.
//

#include "stdafx.h"
#include "Versuch2.h"

#define MAX_LOADSTRING 256

// Globale Variablen:
HINSTANCE hInst;                                // Aktuelle Instanz
//char FENSTERTITEL[MAX_LOADSTRING];
WCHAR FENSTERTITEL[MAX_LOADSTRING];                  // Titelleistentext
WCHAR szWindowClass[MAX_LOADSTRING];				 // Klassenname des Hauptfensters
//CHAR szWindowClass[MAX_LOADSTRING];

// Vorwärtsdeklarationen der in diesem Codemodul enthaltenen Funktionen:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

HWND Hauptfenster;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Hier Code einfügen.

    // Globale Zeichenfolgen initialisieren
    LoadStringW(hInstance, IDS_APP_TITLE, FENSTERTITEL, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_VERSUCH2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Anwendungsinitialisierung ausführen:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_VERSUCH2));

    MSG msg;

    // Hauptnachrichtenschleife:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNKTION: MyRegisterClass()
//
//  ZWECK: Registriert die Fensterklasse.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_VERSUCH2));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_VERSUCH2);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNKTION: InitInstance(HINSTANCE, int)
//
//   ZWECK: Speichert das Instanzenhandle und erstellt das Hauptfenster.
//
//   KOMMENTARE:
//
//        In dieser Funktion wird das Instanzenhandle in einer globalen Variablen gespeichert, und das
//        Hauptprogrammfenster wird erstellt und angezeigt.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Instanzenhandle in der globalen Variablen speichern

   Hauptfenster = CreateWindowW(
	   szWindowClass, 
	   FENSTERTITEL,
	   WS_OVERLAPPEDWINDOW,
	   CW_USEDEFAULT,
	   0,
	   CW_USEDEFAULT,
	   0,
	   nullptr,
	   nullptr,
	   hInstance, 
	   nullptr);

   if (!Hauptfenster)
   {
      return FALSE;
   }

   ShowWindow(Hauptfenster, nCmdShow);
   UpdateWindow(Hauptfenster);

   return TRUE;
}

//
//  FUNKTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ZWECK:  Verarbeitet Meldungen vom Hauptfenster.
//
//  WM_COMMAND  - Verarbeiten des Anwendungsmenüs
//  WM_PAINT    - Darstellen des Hauptfensters
//  WM_DESTROY  - Ausgeben einer Beendenmeldung und zurückkehren
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HMENU static menu = GetMenu(hWnd);

	RECT rect;
	static RECT rectText;
	SIZE size;
	int x, y;
	WCHAR * newTitle = reinterpret_cast<WCHAR *>(lParam);

    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Menüauswahl bearbeiten:
            switch (wmId)
            {
			case ID_TITEL_CHANGE:
				DialogBox(
					GetModuleHandle(NULL),
					MAKEINTRESOURCE(IDD_ABOUTBOX),
					hWnd,
					About
				);
				break;
			case ID_MENU_WEG :
				SetMenu(hWnd, NULL);
				break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
			GetClientRect(hWnd, &rect);
			//GetWindowRect(hWnd,&rect);
			GetTextExtentPoint(hdc, LPCWSTR(FENSTERTITEL),sizeof(FENSTERTITEL),&size);
			//   mitte des Fensterinhaltes             -  mitte des Textes
			//x = (rect.left + ((rect.right  - rect.left) / 2)) - (size.cx / 2);
			//y = (rect.top  + ((rect.bottom - rect.top ) / 2)) - (size.cy / 2);

			x = ((rect.right + rect.left) /2)-(wcslen(FENSTERTITEL)*3);    // BOAH
			y = (rect.bottom + rect.top)/2;

			// setzen der Werte des Textrechtecks
			rectText.top = y;
			rectText.bottom = y + 30;
			rectText.left = x;
			rectText.right = x + (wcslen(FENSTERTITEL) * 10);

			TextOut(hdc, x, y, FENSTERTITEL, sizeof(FENSTERTITEL));
			
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
		
	case WM_RBUTTONDBLCLK:
	{
		
		int x, y;
		x = GET_X_LPARAM(lParam);
		y = GET_Y_LPARAM(lParam);

		if (x >= rectText.left && x <= rectText.right 
		 && y >= rectText.top  && y <= rectText.bottom) {
			SetMenu(hWnd, menu);
		}
	}	
	break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Meldungshandler für Infofeld.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	/*
	int len = GetWindowTextLength(GetDlgItem(hDlg, IDD_ABOUTBOX)) + 1;
	WCHAR * newTitle = new wchar_t[len];
	*/
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;
	case WM_CREATE:
		ShowWindow(hDlg, SW_SHOW);
		break;
    case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			if (LOWORD(wParam) == IDOK) {

				RECT rect;
				GetClientRect(GetParent(hDlg),&rect);
				// Holt den Text
				for (int i = 0; i < MAX_LOADSTRING;i++) {
					FENSTERTITEL[i] = '\0';
				}
				GetWindowText(GetDlgItem(hDlg, IDC_EDIT1), FENSTERTITEL, MAX_LOADSTRING);
				// Versendet den neuen Titel
				SetWindowTextW(GetParent(hDlg),FENSTERTITEL);
				InvalidateRect(0, &rect, false);
				//InvalidateRect(GetParent(hDlg), &rect, false);
				//PostMessageW(GetParent(hDlg), WM_PAINT, 0, 0);
				//SendNotifyMessage(GetParent(hDlg),WM_PAINT,0,0);
				//UpdateWindow(Hauptfenster);
				//RedrawWindow(GetParent(hDlg),NULL,NULL,0);
				//SendMessageW(GetParent(hDlg), WM_PAINT, 0, 0);
				//UpdateWindow(GetParent(hDlg));
				//UpdateWindow(hDlg);
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			break;
		}
    }
    return (INT_PTR)FALSE;
}
