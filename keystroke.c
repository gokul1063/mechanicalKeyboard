#include <windows.h>
#include <mmsystem.h>
#include <process.h>
#include <stdio.h>
#pragma comment(lib,"winmm.lib")

char* soundTrack;
DWORD soundSize = 0;

void fileToMemeory(){
  HANDLE hfile = CreateFile(
    ".\\sounds\\key-4.wav",
    GENERIC_READ,
    FILE_SHARE_READ,
    NULL,
    OPEN_EXISTING,
    FILE_ATTRIBUTE_READONLY,
    NULL
  );
  soundSize = GetFileSize(hfile,NULL);
  if (soundSize <= 0 ){
    printf("soundSize : %d", soundSize);
    return ;
  }
  soundTrack = (char*)malloc(soundSize);
  DWORD readBytes;
  ReadFile(hfile , soundTrack , soundSize , &readBytes , NULL);
  CloseHandle(hfile);
}

void PlaySoundProc(void* arg){
  PlaySound(soundTrack , NULL , SND_ASYNC | SND_MEMORY | SND_NOSTOP);
  _endthread();

}

void PlaySoundProc1(void* arg){
  ULONGLONG start = GetTickCount();
  PlaySound(".\\sounds\\key-3.wav" , NULL , SND_ASYNC | SND_FILENAME | SND_NOSTOP);
  printf("thread - created .\n");
  ULONGLONG end = GetTickCount();
  printf("time taken : %f \n" , end - start);
  _endthread();

}

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION && wParam == WM_KEYDOWN) {
        KBDLLHOOKSTRUCT *kbddlStruct = (KBDLLHOOKSTRUCT *)lParam;
        const char *filename;
        _beginthread(PlaySoundProc , 0 , NULL);
        printf("Key: %d\n", kbddlStruct->vkCode);
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

int main() {
    fileToMemeory();
    HHOOK hook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    UnhookWindowsHookEx(hook);
    return 0;
}
