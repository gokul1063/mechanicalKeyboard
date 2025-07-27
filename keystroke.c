#include <windows.h>
// #include <mmsystem.h>
#include <stdio.h>
#pragma comment(lib,"winmm.lib")

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION && wParam == WM_KEYDOWN) {
        KBDLLHOOKSTRUCT *kbddlStruct = (KBDLLHOOKSTRUCT *)lParam;
        const char *filename;
        if (kbddlStruct->vkCode == 8){
          filename = "key-1.wav";
        }
        else {
          filename = "key-3.wav";
        }
        char filepath[100];
        sprintf(filepath , ".\\sounds\\%s" , filename);
        PlaySound(filepath,NULL , SND_FILENAME | SND_ASYNC);

        printf("Key: %d\n", kbddlStruct->vkCode);
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

int main() {
    HHOOK hook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    UnhookWindowsHookEx(hook);
    return 0;
}
