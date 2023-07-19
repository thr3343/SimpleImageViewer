#include "Win.hpp"
#include "defs.tpp"
#include <bit>
#include <cstdint>
#include <cstdio>



#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>


  
enum {
IMAGE_DOS_SIGNATURE = 0x5A4D
};




auto Win::nInit() -> HWND
{
  return glfwGetWin32Window(window);
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

auto monitor = glfwGetPrimaryMonitor();
const GLFWvidmode* mode = glfwGetVideoMode(monitor);

 
  this->width=mode->width;
  this->height=mode->height;
glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
    
    GLFWwindow* window = glfwCreateWindow(width, height, "My Title", monitor, NULL);



    glfwSetWindowMonitor(window, monitor, 0, 0, width, height, mode->refreshRate);
    
    // HMODULE hm;
    // GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, std::bit_cast<LPCTSTR>( GetModuleHandle(NULL)), &hm), 
   
   
  //  printf("__ImageBase.e_magic{} %hx\n", (__ImageBase.e_magic));
  //  printf("__ImageBase.e_cblp{} %hx\n", (__ImageBase.e_cblp));
  //  printf("__ImageBase.e_minalloc{} %hx\n", (__ImageBase.e_minalloc));
  //  printf("__ImageBase.e_maxalloc{} %hx\n", (__ImageBase.e_maxalloc));
  //  printf("__ImageBase.e_lfanew{} %hx\n", (__ImageBase.e_lfanew));
   
   if(__ImageBase.e_magic!=IMAGE_DOS_SIGNATURE)
  {
      printf("\nError: Invalid executable image.\n");

      // VirtualFree(_hInst,0,MEM_RELEASE);
      exit(-1);
  }
   

 
  printf("OK!\n");
  return window;
};

  [[nodiscard]] auto Win::show(bool a) const -> bool
  {
    printf("%s", a?"SHOW":"HIDE");
      return 1;//ShowWindow(window, a?6:5);
  }