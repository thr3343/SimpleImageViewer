#include "Win.hpp"
#include <cstdint>

#include <fmt/core.h>
#include <fmt/format.h>

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
static bool resizing=false;
static bool isActive=false;
void decodeWMMsg(UINT uMsg)
{
  switch(uMsg)
  {

    
  case WM_IME_SETCONTEXT: fmt::print("WM_IME_SETCONTEXT\n"); break;
  case WM_IME_NOTIFY: fmt::print("WM_IME_NOTIFY\n"); break;
  case WM_IME_CONTROL: fmt::print("WM_IME_CONTROL\n"); break;
  case WM_IME_COMPOSITIONFULL: fmt::print("WM_IME_COMPOSITIONFULL\n"); break;
  case WM_IME_SELECT: fmt::print("WM_IME_SELECT\n"); break;
  case WM_IME_CHAR: fmt::print("WM_IME_CHAR\n"); break;
  case WM_IME_REQUEST: fmt::print("WM_IME_REQUEST\n"); break;
  case WM_IME_KEYDOWN: fmt::print("WM_IME_KEYDOWN\n"); break;
  case WM_IME_KEYUP: fmt::print("WM_IME_KEYUP\n"); break;
  case WM_NULL: fmt::print("WM_NULL\n"); break;
  case WM_CREATE: fmt::print("WM_CREATE\n"); break;
  case WM_DESTROY: fmt::print("WM_DESTROY\n"); break;
  case WM_MOVE: fmt::print("WM_MOVE\n"); break;
  case WM_SIZE: fmt::print("WM_SIZE\n"); break;
  case WM_ACTIVATE: fmt::print("WM_ACTIVATE\n"); break;


  case WM_SETFOCUS: fmt::print("WM_SETFOCUS\n"); break;
  case WM_KILLFOCUS: fmt::print("WM_KILLFOCUS\n"); break;
  case WM_ENABLE: fmt::print("WM_ENABLE\n"); break;
  case WM_SETREDRAW: fmt::print("WM_SETREDRAW\n"); break;
  case WM_SETTEXT: fmt::print("WM_SETTEXT\n"); break;
  case WM_GETTEXT: fmt::print("WM_GETTEXT\n"); break;
  case WM_GETTEXTLENGTH: fmt::print("WM_GETTEXTLENGTH\n"); break;
  case WM_PAINT: fmt::print("WM_PAINT\n"); break;
  case WM_CLOSE: fmt::print("WM_CLOSE\n"); break;

  case WM_QUERYENDSESSION: fmt::print("WM_QUERYENDSESSION\n"); break;
  case WM_QUERYOPEN: fmt::print("WM_QUERYOPEN\n"); break;
  case WM_ENDSESSION: fmt::print("WM_ENDSESSION\n"); break;

  case WM_QUIT: fmt::print("WM_QUIT\n"); break;
  case WM_ERASEBKGND: fmt::print("WM_ERASEBKGND\n"); break;
  case WM_SYSCOLORCHANGE: fmt::print("WM_SYSCOLORCHANGE\n"); break;
  case WM_SHOWWINDOW: fmt::print("WM_SHOWWINDOW\n"); break;
  case WM_WININICHANGE: fmt::print("WM_WININICHANGE\n"); break;
  // case WM_SETTINGCHANGE: fmt::print("WM_WININ\n"); break;
  case WM_DEVMODECHANGE: fmt::print("WM_DEVMODECHANGE\n"); break;
  case WM_ACTIVATEAPP: fmt::print("WM_ACTIVATEAPP\n"); break;
  case WM_FONTCHANGE: fmt::print("WM_FONTCHANGE\n"); break;
  case WM_TIMECHANGE: fmt::print("WM_TIMECHANGE\n"); break;
  case WM_CANCELMODE: fmt::print("WM_CANCELMODE\n"); break;
  case WM_SETCURSOR: fmt::print("WM_SETCURSOR\n"); break;
  case WM_MOUSEACTIVATE: fmt::print("WM_MOUSEACTIVATE\n"); break;
  case WM_CHILDACTIVATE: fmt::print("WM_CHILDACTIVATE\n"); break;
  case WM_QUEUESYNC: fmt::print("WM_QUEUESYNC\n"); break;
  case WM_GETMINMAXINFO: fmt::print("WM_GETMINMAXINFO\n"); break;


  case WM_PAINTICON: fmt::print("WM_PAINTICON\n"); break;
  case WM_ICONERASEBKGND: fmt::print("WM_ICONERASEBKGND\n"); break;
  case WM_NEXTDLGCTL: fmt::print("WM_NEXTDLGCTL\n"); break;
  case WM_SPOOLERSTATUS: fmt::print("WM_SPOOLERSTATUS\n"); break;
  case WM_DRAWITEM: fmt::print("WM_DRAWITEM\n"); break;
  case WM_MEASUREITEM: fmt::print("WM_MEASUREITEM\n"); break;
  case WM_DELETEITEM: fmt::print("WM_DELETEITEM\n"); break;
  case WM_VKEYTOITEM: fmt::print("WM_VKEYTOITEM\n"); break;
  case WM_CHARTOITEM: fmt::print("WM_CHARTOITEM\n"); break;
  case WM_SETFONT: fmt::print("WM_SETFONT\n"); break;
  case WM_GETFONT: fmt::print("WM_GETFONT\n"); break;
  case WM_SETHOTKEY: fmt::print("WM_SETHOTKEY\n"); break;
  case WM_GETHOTKEY: fmt::print("WM_GETHOTKEY\n"); break;
  case WM_QUERYDRAGICON: fmt::print("WM_QUERYDRAGICON\n"); break;
  case WM_COMPAREITEM: fmt::print("WM_COMPAREITEM\n"); break;

  case WM_GETOBJECT: fmt::print("WM_GETOBJECT\n"); break;

  case WM_COMPACTING: fmt::print("WM_COMPACTING\n"); break;
  case WM_COMMNOTIFY: fmt::print("WM_COMMNOTIFY\n"); break;
  case WM_WINDOWPOSCHANGING: fmt::print("WM_WINDOWPOSCHANGING\n"); break;
  case WM_WINDOWPOSCHANGED: fmt::print("WM_WINDOWPOSCHANGED\n"); break;
  case WM_POWER: fmt::print("WM_POWER\n"); break;


  case WM_COPYDATA: fmt::print("WM_COPYDATA\n"); break;
  case WM_CANCELJOURNAL: fmt::print("WM_CANCELJOURNAL\n"); break;


  case WM_NOTIFY: fmt::print("WM_NOTIFY\n"); break;
  case WM_INPUTLANGCHANGEREQUEST: fmt::print("WM_INPUTLANGCHANGEREQUEST\n"); break;
  case WM_INPUTLANGCHANGE: fmt::print("WM_INPUTLANGCHANGE\n"); break;
  case WM_TCARD: fmt::print("WM_TCARD\n"); break;
  case WM_HELP: fmt::print("WM_HELP\n"); break;
  case WM_USERCHANGED: fmt::print("WM_USERCHANGED\n"); break;
  case WM_NOTIFYFORMAT: fmt::print("WM_NOTIFYFORMAT\n"); break;


  case WM_CONTEXTMENU: fmt::print("WM_CONTEXTMENU\n"); break;
  case WM_STYLECHANGING: fmt::print("WM_STYLECHANGING\n"); break;
  case WM_STYLECHANGED: fmt::print("WM_STYLECHANGED\n"); break;
  case WM_DISPLAYCHANGE: fmt::print("WM_DISPLAYCHANGE\n"); break;
  case WM_GETICON: fmt::print("WM_GETICON\n"); break;
  case WM_SETICON: fmt::print("WM_SETICON\n"); break;

  case WM_NCCREATE: fmt::print("WM_NCCREATE\n"); break;
  case WM_NCDESTROY: fmt::print("WM_NCDESTROY\n"); break;
  case WM_NCCALCSIZE: fmt::print("WM_NCCALCSIZE\n"); break;
  case WM_NCHITTEST: fmt::print("WM_NCHITTEST\n"); break;
  case WM_NCPAINT: fmt::print("WM_NCPAINT\n"); break;
  case WM_NCACTIVATE: fmt::print("WM_NCACTIVATE\n"); break;
  case WM_GETDLGCODE: fmt::print("WM_GETDLGCODE\n"); break;

  case WM_SYNCPAINT: fmt::print("WM_SYNCPAINT\n"); break;

  case WM_NCMOUSEMOVE: fmt::print("WM_NCMOUSEMOVE\n"); break;
  case WM_NCLBUTTONDOWN: fmt::print("WM_NCLBUTTONDOWN\n"); break;
  case WM_NCLBUTTONUP: fmt::print("WM_NCLBUTTONUP\n"); break;
  case WM_NCLBUTTONDBLCLK: fmt::print("WM_NCLBUTTONDBLCLK\n"); break;
  case WM_NCRBUTTONDOWN: fmt::print("WM_NCRBUTTONDOWN\n"); break;
  case WM_NCRBUTTONUP: fmt::print("WM_NCRBUTTONUP\n"); break;
  case WM_NCRBUTTONDBLCLK: fmt::print("WM_NCRBUTTONDBLCLK\n"); break;
  case WM_NCMBUTTONDOWN: fmt::print("WM_NCMBUTTONDOWN\n"); break;
  case WM_NCMBUTTONUP: fmt::print("WM_NCMBUTTONUP\n"); break;
  case WM_NCMBUTTONDBLCLK: fmt::print("WM_NCMBUTTONDBLCLK\n"); break;

  case WM_NCXBUTTONDOWN: fmt::print("WM_NCXBUTTONDOWN\n"); break;
  case WM_NCXBUTTONUP: fmt::print("WM_NCXBUTTONUP\n"); break;
  case WM_NCXBUTTONDBLCLK: fmt::print("WM_NCXBUTTONDBLCLK\n"); break;
  case WM_INPUT_DEVICE_CHANGE: fmt::print("WM_INPUT_DEVICE_CHANGE\n"); break;
  case WM_INPUT: fmt::print("WM_INPUT\n"); break;
  case WM_KEYDOWN: fmt::print("WM_KEYDOWN\n"); break;
  case WM_KEYUP: fmt::print("WM_KEYUP\n"); break;
  case WM_CHAR: fmt::print("WM_CHAR\n"); break;
  case WM_DEADCHAR: fmt::print("WM_DEADCHAR\n"); break;
  case WM_SYSKEYDOWN: fmt::print("WM_SYSKEYDOWN\n"); break;
  case WM_SYSKEYUP: fmt::print("WM_SYSKEYUP\n"); break;
  case WM_SYSCHAR: fmt::print("WM_SYSCHAR\n"); break;
  case WM_SYSDEADCHAR: fmt::print("WM_SYSDEADCHAR\n"); break;

  case WM_UNICHAR: fmt::print("WM_UNICHAR\n"); break;
  case UNICODE_NOCHAR: fmt::print("UNICODE_NOCHAR\n"); break;


  case WM_IME_STARTCOMPOSITION: fmt::print("WM_IME_STARTCOMPOSITION\n"); break;
  case WM_IME_ENDCOMPOSITION: fmt::print("WM_IME_ENDCOMPOSITION\n"); break;
  case WM_IME_COMPOSITION: fmt::print("WM_IME_COMPOSITION\n"); break;

  case WM_INITDIALOG: fmt::print("WM_INITDIALOG\n"); break;
  case WM_COMMAND: fmt::print("WM_COMMAND\n"); break;
  case WM_SYSCOMMAND: fmt::print("WM_SYSCOMMAND\n"); break;
  case WM_TIMER: fmt::print("WM_TIMER\n"); break;
  case WM_HSCROLL: fmt::print("WM_HSCROLL\n"); break;
  case WM_VSCROLL: fmt::print("WM_VSCROLL\n"); break;
  case WM_INITMENU: fmt::print("WM_INITMENU\n"); break;
  case WM_INITMENUPOPUP: fmt::print("WM_INITMENUPOPUP\n"); break;
  case WM_MENUSELECT: fmt::print("WM_MENUSELECT\n"); break;

  case WM_GESTURE: fmt::print("WM_GESTURE\n"); break;
  case WM_GESTURENOTIFY: fmt::print("WM_GESTURENOTIFY\n"); break;

  case WM_MENUCHAR: fmt::print("WM_MENUCHAR\n"); break;
  case WM_ENTERIDLE: fmt::print("WM_ENTERIDLE\n"); break;

  case WM_MENURBUTTONUP: fmt::print("WM_MENURBUTTONUP\n"); break;
  case WM_MENUDRAG: fmt::print("WM_MENUDRAG\n"); break;
  case WM_MENUGETOBJECT: fmt::print("WM_MENUGETOBJECT\n"); break;
  case WM_UNINITMENUPOPUP: fmt::print("WM_UNINITMENUPOPUP\n"); break;
  case WM_MENUCOMMAND: fmt::print("WM_MENUCOMMAND\n"); break;
  case WM_CHANGEUISTATE: fmt::print("WM_CHANGEUISTATE\n"); break;
  case WM_UPDATEUISTATE: fmt::print("WM_UPDATEUISTATE\n"); break;
  case WM_QUERYUISTATE: fmt::print("WM_QUERYUISTATE\n"); break;


  case WM_CTLCOLORMSGBOX: fmt::print("WM_CTLCOLORMSGBOX\n"); break;
  case WM_CTLCOLOREDIT: fmt::print("WM_CTLCOLOREDIT\n"); break;
  case WM_CTLCOLORLISTBOX: fmt::print("WM_CTLCOLORLISTBOX\n"); break;
  case WM_CTLCOLORBTN: fmt::print("WM_CTLCOLORBTN\n"); break;
  case WM_CTLCOLORDLG: fmt::print("WM_CTLCOLORDLG\n"); break;
  case WM_CTLCOLORSCROLLBAR: fmt::print("WM_CTLCOLORSCROLLBAR\n"); break;
  case WM_CTLCOLORSTATIC: fmt::print("WM_CTLCOLORSTATIC\n"); break;
  case MN_GETHMENU: fmt::print("MN_GETHMENU\n"); break;

  case WM_LBUTTONDOWN: fmt::print("WM_LBUTTONDOWN\n"); break;
  case WM_LBUTTONUP: fmt::print("WM_LBUTTONUP\n"); break;
  case WM_LBUTTONDBLCLK: fmt::print("WM_LBUTTONDBLCLK\n"); break;
  case WM_RBUTTONDOWN: fmt::print("WM_RBUTTONDOWN\n"); break;
  case WM_RBUTTONUP: fmt::print("WM_RBUTTONUP\n"); break;
  case WM_RBUTTONDBLCLK: fmt::print("WM_RBUTTONDBLCLK\n"); break;
  case WM_MBUTTONDOWN: fmt::print("WM_MBUTTONDOWN\n"); break;
  case WM_MBUTTONUP: fmt::print("WM_MBUTTONUP\n"); break;
  case WM_MBUTTONDBLCLK: fmt::print("WM_MBUTTONDBLCLK\n"); break;
  case WM_MOUSEWHEEL: fmt::print("WM_MOUSEWHEEL\n"); break;
  case WM_XBUTTONDOWN: fmt::print("WM_XBUTTONDOWN\n"); break;
  case WM_XBUTTONUP: fmt::print("WM_XBUTTONUP\n"); break;
  case WM_XBUTTONDBLCLK: fmt::print("WM_XBUTTONDBLCLK\n"); break;

  case WM_MOUSEHWHEEL: fmt::print("WM_MOUSEHWHEEL\n"); break;

  case WM_PARENTNOTIFY: fmt::print("WM_PARENTNOTIFY\n"); break;
  case WM_ENTERMENULOOP: fmt::print("WM_ENTERMENULOOP\n"); break;
  case WM_EXITMENULOOP: fmt::print("WM_EXITMENULOOP\n"); break;
  case WM_NEXTMENU: fmt::print("WM_NEXTMENU\n"); break;
  case WM_SIZING: fmt::print("WM_SIZING\n"); break;
  case WM_CAPTURECHANGED: fmt::print("WM_CAPTURECHANGED\n"); break;
  case WM_MOVING: fmt::print("WM_MOVING\n"); break;
  case WM_POWERBROADCAST: fmt::print("WM_POWERBROADCAST\n"); break;


  case WM_DEVICECHANGE: fmt::print("WM_DEVICECHANGE\n"); break;

  case WM_MDICREATE: fmt::print("WM_MDICREATE\n"); break;
  case WM_MDIDESTROY: fmt::print("WM_MDIDESTROY\n"); break;
  case WM_MDIACTIVATE: fmt::print("WM_MDIACTIVATE\n"); break;
  case WM_MDIRESTORE: fmt::print("WM_MDIRESTORE\n"); break;
  case WM_MDINEXT: fmt::print("WM_MDINEXT\n"); break;
  case WM_MDIMAXIMIZE: fmt::print("WM_MDIMAXIMIZE\n"); break;
  case WM_MDITILE: fmt::print("WM_MDITILE\n"); break;
  case WM_MDICASCADE: fmt::print("WM_MDICASCADE\n"); break;
  case WM_MDIICONARRANGE: fmt::print("WM_MDIICONARRANGE\n"); break;
  case WM_MDIGETACTIVE: fmt::print("WM_MDIGETACTIVE\n"); break;

  case WM_MDISETMENU: fmt::print("WM_MDISETMENU\n"); break;
  case WM_ENTERSIZEMOVE: fmt::print("WM_ENTERSIZEMOVE\n"); break;
  case WM_EXITSIZEMOVE: fmt::print("WM_EXITSIZEMOVE\n"); break;
  case WM_DROPFILES: fmt::print("WM_DROPFILES\n"); break;
  case WM_MDIREFRESHMENU: fmt::print("WM_MDIREFRESHMENU\n"); break;
  default: fmt::print("%s %x\n", "Unknown Message!: ", uMsg); break;
  }
}
// Heavily Based on https://github.com/SaschaWillems/Vulkan/blob/master/base/vulkanexamplebase.cpp#L1221
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
        fmt::print("Close Window!\n");
        // PostQuitMessage(0);
        CloseWindow(hwnd);
        DestroyWindow(hwnd);
        return 0;
    case WM_DESTROY:
        fmt::print("Destroy!\n");
        PostQuitMessage(0);
        return 0;
    case WM_ENABLE:
        fmt::print("{} {}\n", "ChangeState!", wParam);
        return 0;
    case WM_PAINT:
        return 0;
    case WM_NCCREATE:
    
          fmt::print("NCCreate Window!\n");
          return true;
    
    case WM_NCDESTROY:
    
      fmt::print("NCDestroy Window!\n");
      return 0;
    case WM_INPUT:
    {
      fmt::print("INPUT!\n");
      auto a =GET_RAWINPUT_CODE_WPARAM(wParam);
      fmt::print("\n");
      return 0;
    }
    case WM_CREATE:
      fmt::print("Create Window\n");
       return true;
    case WM_NCACTIVATE:
      fmt::print("CreateActivat Window\n");
      fmt::print("{} {}", "Enable", wParam);
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
      fmt::print("MOVE!\n");
      fmt::print("{} {}\n", LOWORD(lParam), HIWORD(lParam));
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
      fmt::print("FAIL!\n");
        return nullptr;
    }
   fmt::print("__ImageBase.ImageBase{}\n",fmt::ptr(&__ImageBase));
   fmt::print("__ImageBase.ImageBase{}\n", fmt::ptr(_hInst));
   fmt::print("__ImageBase.ImageBase{}\n", fmt::ptr(GetModuleHandle(NULL)));
   fmt::print("__ImageBase.ImageBase{}\n",fmt::ptr(inst));
   Win::min= ShowWindow(w, 10);

 
  fmt::print("OK!\n");
  return w;
};

  [[nodiscard]] auto Win::show(bool a) const -> bool
  {
    fmt::print("%z", a?"SHOW":"HIDE");
      return ShowWindow(window, a?6:5);
  }