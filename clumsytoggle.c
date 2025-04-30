#include <windows.h>
#include <stdio.h>

#define HOTKEY_ID 1
#define MAX_WINDOW_TEXT 256

static HWND g_hwndClumsy = NULL;
static HWND g_hwndButton = NULL;
static int isRunning = 0;

void PrintHeader() {
    printf("\nClumsy Toggle - made by kryo\n");
    printf("Press Alt to toggle, Ctrl+C to exit\n\n");
}

BOOL CALLBACK EnumChildProc(HWND hwndChild, LPARAM lParam) {
    static char className[MAX_WINDOW_TEXT];
    static char windowText[MAX_WINDOW_TEXT];
    
    if (GetClassNameA(hwndChild, className, MAX_WINDOW_TEXT) && 
        GetWindowTextA(hwndChild, windowText, MAX_WINDOW_TEXT)) {
        if (strcmp(className, "Button") == 0 && 
            (strcmp(windowText, "Start") == 0 || strcmp(windowText, "Stop") == 0)) {
            *(HWND*)lParam = hwndChild;
            return FALSE;
        }
    }
    return TRUE;
}

void FindClumsyWindow() {
    if (g_hwndClumsy && IsWindow(g_hwndClumsy)) return;

    HWND hwndDesktop = GetDesktopWindow();
    HWND hwndChild = GetWindow(hwndDesktop, GW_CHILD);
    char windowText[MAX_WINDOW_TEXT];

    while (hwndChild) {
        if (GetWindowTextA(hwndChild, windowText, MAX_WINDOW_TEXT)) {
            if (strcmp(windowText, "clumsy 0.2") == 0 || strcmp(windowText, "clumsy 0.3") == 0) {
                g_hwndClumsy = hwndChild;
                break;
            }
        }
        hwndChild = GetWindow(hwndChild, GW_HWNDNEXT);
    }
}

void FindClumsyButton() {
    if (g_hwndButton && IsWindow(g_hwndButton)) return;
    if (!g_hwndClumsy) return;

    g_hwndButton = NULL;
    EnumChildWindows(g_hwndClumsy, EnumChildProc, (LPARAM)&g_hwndButton);
}

void ToggleClumsyButton() {
    FindClumsyWindow();
    if (!g_hwndClumsy) return;

    FindClumsyButton();
    if (!g_hwndButton) return;

    isRunning = !isRunning;
    SendMessage(g_hwndButton, BM_CLICK, 0, 0);
}

int main() {
    PrintHeader();
    
    if (!RegisterHotKey(NULL, HOTKEY_ID, MOD_ALT, 0)) {
        MessageBoxA(NULL, "Failed to register hotkey", "Error", MB_ICONERROR);
        return 1;
    }

    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        if (msg.message == WM_HOTKEY && msg.wParam == HOTKEY_ID) {
            ToggleClumsyButton();
        }
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UnregisterHotKey(NULL, HOTKEY_ID);
    return 0;
}