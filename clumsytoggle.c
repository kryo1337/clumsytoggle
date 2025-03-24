#include <windows.h>

#define HOTKEY_ID 1

int isRunning = 0;

BOOL CALLBACK EnumChildProc(HWND hwndChild, LPARAM lParam) {
    char className[256];
    char windowText[256];
    GetClassName(hwndChild, className, sizeof(className));
    GetWindowText(hwndChild, windowText, sizeof(windowText));
    if (_stricmp(className, "Button") == 0 && 
        (_stricmp(windowText, "Start") == 0 || _stricmp(windowText, "Stop") == 0)) {
        *(HWND*)lParam = hwndChild;
        return FALSE;
    }
    return TRUE;
}

void ToggleClumsyButton() {
    HWND hwndClumsy = NULL;
    HWND hwndDesktop = GetDesktopWindow();
    HWND hwndChild = GetWindow(hwndDesktop, GW_CHILD);
    char windowText[256];

    while (hwndChild) {
        GetWindowText(hwndChild, windowText, sizeof(windowText));
        if (_stricmp(windowText, "clumsy 0.2") == 0 || _stricmp(windowText, "clumsy 0.3") == 0) {
            hwndClumsy = hwndChild;
            break;
        }
        hwndChild = GetWindow(hwndChild, GW_HWNDNEXT);
    }

    if (hwndClumsy == NULL) return;

    HWND hwndButton = NULL;
    EnumChildWindows(hwndClumsy, EnumChildProc, (LPARAM)&hwndButton);

    if (hwndButton == NULL) return;

    isRunning = !isRunning;
    SendMessage(hwndButton, BM_CLICK, 0, 0);
}

int main() {
    if (!RegisterHotKey(NULL, HOTKEY_ID, MOD_ALT, 0)) return 1;

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