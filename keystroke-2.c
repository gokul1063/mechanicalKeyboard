#include <windows.h>
// #include <stdio.h>
LRESULT CALLBACK KeyshortcutProc(int nCode , WPARAM Wparam , LPARAM Lparam ){
  if (nCode == HC_ACTION && Wparam == WM_KEYDOWN){
    KBDLLHOOKSTRUCT* kbddlhook = (KBDLLHOOKSTRUCT*) Lparam;
    if ((GetAsyncKeyState(VK_LWIN) & 0x8000) && kbddlhook->vkCode == VK_RETURN) {
      system("start cmd");
      return 1;
    }
  }
  return CallNextHookEx(NULL , nCode , Wparam , Lparam);
}


int main(){

  HHOOK hook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyshortcutProc , NULL , 0);
  MSG msg;
  while (GetMessage(&msg , NULL , 0 , 0 )){
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  UnhookWindowsHookEx(hook);
  return 0;
}
