#include "Win.hpp"
#include <cstdint>
#include <cstdio>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>





// using QWORD = uint64_t;

extern  constinit const HINSTANCE   __ImageBase;


auto Win::nInit() -> HWND
{
  return glfwGetWin32Window(window);
}

auto Win::hInst() -> HINSTANCE
{
  return (__ImageBase);
}

auto Win::init() -> GLFWwindow*
{

 
if (!glfwInit())
{
    exit(1);
}
  
  /* tagWNDCLASSA wc = { 
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
                                           (LPVOID) nullptr); */

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_CONTEXT_CREATION_API , GLFW_NATIVE_CONTEXT_API);
    GLFWwindow* window = glfwCreateWindow(width, height, "My Title", NULL, NULL);
    
   printf("__ImageBase.ImageBase{} %llx\n", (&__ImageBase));
  //  printf("__ImageBase.ImageBase{} %llx\n", (_hInst));
   printf("__ImageBase.ImageBase{} %llx\n", (GetModuleHandle(NULL)));
   printf("__ImageBase.ImageBase{} %llx\n", (inst));
  //  Win::min= glfwGetWin32Window(window);

 
  printf("OK!\n");
  return window;
};

  [[nodiscard]] auto Win::show(bool a) const -> bool
  {
    printf("%s", a?"SHOW":"HIDE");
      return 1;//ShowWindow(window, a?6:5);
  }