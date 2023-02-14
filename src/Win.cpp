#include "Win.hpp"
#include <cstdint>

#include <cstdio>

#include <minwindef.h>
#include <windef.h>
#include <winuser.h>


// using QWORD = uint64_t;
#ifdef __WIN32
EXTERN_C  constinit const IMAGE_DOS_HEADER   __ImageBase;
const auto _hInst = (HINSTANCE)&__ImageBase;

#endif

void test()
{
  // init();
  // inst=_hInst;
}



LRESULT CALLBACK constexpr Win::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
      // std::cout <<std::hex <<"0x"<< uMsg << "OK!" << "\n";
      // std::cout <<std::dec <<"wParam"<<"0x"<< wParam << "OK!" << "\n";
      // std::cout <<std::left <<"lParam"<<"0x"<< lParam << "OK!" << "\n";
      // std::cout <<std::dec <<"W"<< (GET_X_LPARAM(lParam)) << "OK!" << "\n";
      // std::cout <<std::dec <<"H"<< (GET_Y_LPARAM(lParam)) << "OK!" << "\n";
    //   X=(GET_X_LPARAM(lParam));
    //   Y=(GET_Y_LPARAM(lParam));
    RAWINPUT_ALIGN(1);

  switch (uMsg)
    {
    case WM_CLOSE:
        printf("Close Window!\n");
        // PostQuitMessage(0);
        CloseWindow(hwnd);
        DestroyWindow(hwnd);
        return 0;
    case WM_DESTROY:
        printf("Destroy!\n");
        PostQuitMessage(0);
        return 0;
    case WM_ENABLE:
        printf("%s %llu\n", "ChangeState!", wParam);
        return 0;
    case WM_PAINT:
        return 0;
    case WM_NCCREATE:
    
          printf("NCCreate Window!\n");
          return true;
    
    case WM_NCDESTROY:
    
      printf("NCDestroy Window!\n");
      return 0;
    case WM_INPUT:
    {
      printf("INPUT!\n");
      auto a =GET_RAWINPUT_CODE_WPARAM(wParam);
      printf("\n");
      return 0;
    }
    case WM_CREATE:
      printf("Create Window\n");
       return true;
    case WM_NCACTIVATE:
      printf("CreateActivat Window\n");
      printf("%s %llu\n", "Enable", wParam);
      return(!wParam)?false: -1;
      return 1;
    case WM_SETCURSOR:
      return false;
    case WM_GETMINMAXINFO:
      return 0;
    case WM_NCCALCSIZE:
      if(wParam)
      {
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
      }
      else return true;
    
    case WM_MOVE:
      printf("MOVE!\n");
      return true;
    
   

    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
};

auto Win::hInst() -> HINSTANCE
{
  return (_hInst);
}

auto Win::init() -> HWND
{

 

  
  tagWNDCLASSA wc = { 
    .style=CS_HREDRAW | CS_VREDRAW,
    .lpfnWndProc   = WindowProc,
    .hInstance     = _hInst,
    // .hIcon = LoadIcon(NULL, IDI_APPLICATION),
    // .hCursor = LoadCursor(NULL, IDC_ARROW),
    // .hbrBackground = nullptr;//(HBRUSH)GetStockObject(BLACK_BRUSH),
    .lpszMenuName = nullptr,
    .lpszClassName = "Win"};
    RegisterClass(&wc);
    HWND w =CreateWindowEx(wc.style,
                                           "Win",
                                           nullptr,
                                           NULL,
                                           0, 0,
                                           width, height,
                                           nullptr, // No parent window
                                           NULL, // No window menu
                                           _hInst,
                                           (LPVOID) nullptr);

    if (w == nullptr)
    {
      printf("FAIL!\n");
        return nullptr;
    }
  //  printf("__ImageBase.ImageBase %llu\n",&__ImageBase.ImageBase);
   printf("__ImageBase.ImageBase %llx\n",_hInst);
   printf("__ImageBase.ImageBase %llx\n",GetModuleHandle(NULL));
   printf("__ImageBase.ImageBase %llx\n",inst);
   Win::min= ShowWindow(w, 10);

 
  printf("OK!\n");
  return w;
};

  [[nodiscard]] auto Win::show(bool a) const -> bool
  {
    printf(a?"SHOW":"HIDE");
      return ShowWindow(window, a?6:5);
  }