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
static bool resizing=false;
static bool isActive=false;
void decodeWMMsg(UINT uMsg)
{
  switch(uMsg)
  {

    
  case WM_IME_SETCONTEXT: printf("WM_IME_SETCONTEXT\n"); break;
  case WM_IME_NOTIFY: printf("WM_IME_NOTIFY\n"); break;
  case WM_IME_CONTROL: printf("WM_IME_CONTROL\n"); break;
  case WM_IME_COMPOSITIONFULL: printf("WM_IME_COMPOSITIONFULL\n"); break;
  case WM_IME_SELECT: printf("WM_IME_SELECT\n"); break;
  case WM_IME_CHAR: printf("WM_IME_CHAR\n"); break;
  case WM_IME_REQUEST: printf("WM_IME_REQUEST\n"); break;
  case WM_IME_KEYDOWN: printf("WM_IME_KEYDOWN\n"); break;
  case WM_IME_KEYUP: printf("WM_IME_KEYUP\n"); break;
  case WM_NULL: printf("WM_NULL\n"); break;
  case WM_CREATE: printf("WM_CREATE\n"); break;
  case WM_DESTROY: printf("WM_DESTROY\n"); break;
  case WM_MOVE: printf("WM_MOVE\n"); break;
  case WM_SIZE: printf("WM_SIZE\n"); break;

  case WM_ACTIVATE: printf("WM_ACTIVATE\n"); break;


  case WM_SETFOCUS: printf("WM_SETFOCUS\n"); break;
  case WM_KILLFOCUS: printf("WM_KILLFOCUS\n"); break;
  case WM_ENABLE: printf("WM_ENABLE\n"); break;
  case WM_SETREDRAW: printf("WM_SETREDRAW\n"); break;
  case WM_SETTEXT: printf("WM_SETTEXT\n"); break;
  case WM_GETTEXT: printf("WM_GETTEXT\n"); break;
  case WM_GETTEXTLENGTH: printf("WM_GETTEXTLENGTH\n"); break;
  case WM_PAINT: printf("WM_PAINT\n"); break;
  case WM_CLOSE: printf("WM_CLOSE\n"); break;

  case WM_QUERYENDSESSION: printf("WM_QUERYENDSESSION\n"); break;
  case WM_QUERYOPEN: printf("WM_QUERYOPEN\n"); break;
  case WM_ENDSESSION: printf("WM_ENDSESSION\n"); break;

  case WM_QUIT: printf("WM_QUIT\n"); break;
  case WM_ERASEBKGND: printf("WM_ERASEBKGND\n"); break;
  case WM_SYSCOLORCHANGE: printf("WM_SYSCOLORCHANGE\n"); break;
  case WM_SHOWWINDOW: printf("WM_SHOWWINDOW\n"); break;
  case WM_WININICHANGE: printf("WM_WININICHANGE\n"); break;
  // case WM_SETTINGCHANGE: printf("WM_WININ\n"); break;
  case WM_DEVMODECHANGE: printf("WM_DEVMODECHANGE\n"); break;
  case WM_ACTIVATEAPP: printf("WM_ACTIVATEAPP\n"); break;
  case WM_FONTCHANGE: printf("WM_FONTCHANGE\n"); break;
  case WM_TIMECHANGE: printf("WM_TIMECHANGE\n"); break;
  case WM_CANCELMODE: printf("WM_CANCELMODE\n"); break;
  case WM_SETCURSOR: printf("WM_SETCURSOR\n"); break;
  case WM_MOUSEACTIVATE: printf("WM_MOUSEACTIVATE\n"); break;
  case WM_CHILDACTIVATE: printf("WM_CHILDACTIVATE\n"); break;
  case WM_QUEUESYNC: printf("WM_QUEUESYNC\n"); break;
  case WM_GETMINMAXINFO: printf("WM_GETMINMAXINFO\n"); break;


  case WM_PAINTICON: printf("WM_PAINTICON\n"); break;
  case WM_ICONERASEBKGND: printf("WM_ICONERASEBKGND\n"); break;
  case WM_NEXTDLGCTL: printf("WM_NEXTDLGCTL\n"); break;
  case WM_SPOOLERSTATUS: printf("WM_SPOOLERSTATUS\n"); break;
  case WM_DRAWITEM: printf("WM_DRAWITEM\n"); break;
  case WM_MEASUREITEM: printf("WM_MEASUREITEM\n"); break;
  case WM_DELETEITEM: printf("WM_DELETEITEM\n"); break;
  case WM_VKEYTOITEM: printf("WM_VKEYTOITEM\n"); break;
  case WM_CHARTOITEM: printf("WM_CHARTOITEM\n"); break;
  case WM_SETFONT: printf("WM_SETFONT\n"); break;
  case WM_GETFONT: printf("WM_GETFONT\n"); break;
  case WM_SETHOTKEY: printf("WM_SETHOTKEY\n"); break;
  case WM_GETHOTKEY: printf("WM_GETHOTKEY\n"); break;
  case WM_QUERYDRAGICON: printf("WM_QUERYDRAGICON\n"); break;
  case WM_COMPAREITEM: printf("WM_COMPAREITEM\n"); break;

  case WM_GETOBJECT: printf("WM_GETOBJECT\n"); break;

  case WM_COMPACTING: printf("WM_COMPACTING\n"); break;
  case WM_COMMNOTIFY: printf("WM_COMMNOTIFY\n"); break;
  case WM_WINDOWPOSCHANGING: printf("WM_WINDOWPOSCHANGING\n"); break;
  case WM_WINDOWPOSCHANGED: printf("WM_WINDOWPOSCHANGED\n"); break;
  case WM_POWER: printf("WM_POWER\n"); break;


  case WM_COPYDATA: printf("WM_COPYDATA\n"); break;
  case WM_CANCELJOURNAL: printf("WM_CANCELJOURNAL\n"); break;


  case WM_NOTIFY: printf("WM_NOTIFY\n"); break;
  case WM_INPUTLANGCHANGEREQUEST: printf("WM_INPUTLANGCHANGEREQUEST\n"); break;
  case WM_INPUTLANGCHANGE: printf("WM_INPUTLANGCHANGE\n"); break;
  case WM_TCARD: printf("WM_TCARD\n"); break;
  case WM_HELP: printf("WM_HELP\n"); break;
  case WM_USERCHANGED: printf("WM_USERCHANGED\n"); break;
  case WM_NOTIFYFORMAT: printf("WM_NOTIFYFORMAT\n"); break;


  case WM_CONTEXTMENU: printf("WM_CONTEXTMENU\n"); break;
  case WM_STYLECHANGING: printf("WM_STYLECHANGING\n"); break;
  case WM_STYLECHANGED: printf("WM_STYLECHANGED\n"); break;
  case WM_DISPLAYCHANGE: printf("WM_DISPLAYCHANGE\n"); break;
  case WM_GETICON: printf("WM_GETICON\n"); break;
  case WM_SETICON: printf("WM_SETICON\n"); break;

  case WM_NCCREATE: printf("WM_NCCREATE\n"); break;
  case WM_NCDESTROY: printf("WM_NCDESTROY\n"); break;
  case WM_NCCALCSIZE: printf("WM_NCCALCSIZE\n"); break;
  case WM_NCHITTEST: printf("WM_NCHITTEST\n"); break;
  case WM_NCPAINT: printf("WM_NCPAINT\n"); break;
  case WM_NCACTIVATE: printf("WM_NCACTIVATE\n"); break;
  case WM_GETDLGCODE: printf("WM_GETDLGCODE\n"); break;

  case WM_SYNCPAINT: printf("WM_SYNCPAINT\n"); break;

  case WM_NCMOUSEMOVE: printf("WM_NCMOUSEMOVE\n"); break;
  case WM_NCLBUTTONDOWN: printf("WM_NCLBUTTONDOWN\n"); break;
  case WM_NCLBUTTONUP: printf("WM_NCLBUTTONUP\n"); break;
  case WM_NCLBUTTONDBLCLK: printf("WM_NCLBUTTONDBLCLK\n"); break;
  case WM_NCRBUTTONDOWN: printf("WM_NCRBUTTONDOWN\n"); break;
  case WM_NCRBUTTONUP: printf("WM_NCRBUTTONUP\n"); break;
  case WM_NCRBUTTONDBLCLK: printf("WM_NCRBUTTONDBLCLK\n"); break;
  case WM_NCMBUTTONDOWN: printf("WM_NCMBUTTONDOWN\n"); break;
  case WM_NCMBUTTONUP: printf("WM_NCMBUTTONUP\n"); break;
  case WM_NCMBUTTONDBLCLK: printf("WM_NCMBUTTONDBLCLK\n"); break;

  case WM_NCXBUTTONDOWN: printf("WM_NCXBUTTONDOWN\n"); break;
  case WM_NCXBUTTONUP: printf("WM_NCXBUTTONUP\n"); break;
  case WM_NCXBUTTONDBLCLK: printf("WM_NCXBUTTONDBLCLK\n"); break;
  case WM_INPUT_DEVICE_CHANGE: printf("WM_INPUT_DEVICE_CHANGE\n"); break;
  case WM_INPUT: printf("WM_INPUT\n"); break;
  // case WM_KEYFIRST: printf("WM_KEYFIRST\n"); break;
  case WM_KEYDOWN: printf("WM_KEYDOWN\n"); break;
  case WM_KEYUP: printf("WM_KEYUP\n"); break;
  case WM_CHAR: printf("WM_CHAR\n"); break;
  case WM_DEADCHAR: printf("WM_DEADCHAR\n"); break;
  case WM_SYSKEYDOWN: printf("WM_SYSKEYDOWN\n"); break;
  case WM_SYSKEYUP: printf("WM_SYSKEYUP\n"); break;
  case WM_SYSCHAR: printf("WM_SYSCHAR\n"); break;
  case WM_SYSDEADCHAR: printf("WM_SYSDEADCHAR\n"); break;

  case WM_UNICHAR: printf("WM_UNICHAR\n"); break;
  // case WM_KEYLAST: printf("WM_KEYLAST\n"); break;
  case UNICODE_NOCHAR: printf("UNICODE_NOCHAR\n"); break;

  // case WM_KEYLAST: printf("WM_KEYLAST\n"); break;

  case WM_IME_STARTCOMPOSITION: printf("WM_IME_STARTCOMPOSITION\n"); break;
  case WM_IME_ENDCOMPOSITION: printf("WM_IME_ENDCOMPOSITION\n"); break;
  case WM_IME_COMPOSITION: printf("WM_IME_COMPOSITION\n"); break;
  // case WM_IME_KEYLAST: printf("WM_IME_KEYLAST\n"); break;
  case WM_INITDIALOG: printf("WM_INITDIALOG\n"); break;
  case WM_COMMAND: printf("WM_COMMAND\n"); break;
  case WM_SYSCOMMAND: printf("WM_SYSCOMMAND\n"); break;
  case WM_TIMER: printf("WM_TIMER\n"); break;
  case WM_HSCROLL: printf("WM_HSCROLL\n"); break;
  case WM_VSCROLL: printf("WM_VSCROLL\n"); break;
  case WM_INITMENU: printf("WM_INITMENU\n"); break;
  case WM_INITMENUPOPUP: printf("WM_INITMENUPOPUP\n"); break;
  case WM_MENUSELECT: printf("WM_MENUSELECT\n"); break;

  case WM_GESTURE: printf("WM_GESTURE\n"); break;
  case WM_GESTURENOTIFY: printf("WM_GESTURENOTIFY\n"); break;

  case WM_MENUCHAR: printf("WM_MENUCHAR\n"); break;
  case WM_ENTERIDLE: printf("WM_ENTERIDLE\n"); break;

  case WM_MENURBUTTONUP: printf("WM_MENURBUTTONUP\n"); break;
  case WM_MENUDRAG: printf("WM_MENUDRAG\n"); break;
  case WM_MENUGETOBJECT: printf("WM_MENUGETOBJECT\n"); break;
  case WM_UNINITMENUPOPUP: printf("WM_UNINITMENUPOPUP\n"); break;
  case WM_MENUCOMMAND: printf("WM_MENUCOMMAND\n"); break;
  case WM_CHANGEUISTATE: printf("WM_CHANGEUISTATE\n"); break;
  case WM_UPDATEUISTATE: printf("WM_UPDATEUISTATE\n"); break;
  case WM_QUERYUISTATE: printf("WM_QUERYUISTATE\n"); break;


  case WM_CTLCOLORMSGBOX: printf("WM_CTLCOLORMSGBOX\n"); break;
  case WM_CTLCOLOREDIT: printf("WM_CTLCOLOREDIT\n"); break;
  case WM_CTLCOLORLISTBOX: printf("WM_CTLCOLORLISTBOX\n"); break;
  case WM_CTLCOLORBTN: printf("WM_CTLCOLORBTN\n"); break;
  case WM_CTLCOLORDLG: printf("WM_CTLCOLORDLG\n"); break;
  case WM_CTLCOLORSCROLLBAR: printf("WM_CTLCOLORSCROLLBAR\n"); break;
  case WM_CTLCOLORSTATIC: printf("WM_CTLCOLORSTATIC\n"); break;
  case MN_GETHMENU: printf("MN_GETHMENU\n"); break;

  // case WM_MOUSEFIRST: printf("WM_MOUSEFIRST\n"); break;
  // case WM_MOUSEMOVE: printf("WM_MOUSEMOVE\n"); break;
  case WM_LBUTTONDOWN: printf("WM_LBUTTONDOWN\n"); break;
  case WM_LBUTTONUP: printf("WM_LBUTTONUP\n"); break;
  case WM_LBUTTONDBLCLK: printf("WM_LBUTTONDBLCLK\n"); break;
  case WM_RBUTTONDOWN: printf("WM_RBUTTONDOWN\n"); break;
  case WM_RBUTTONUP: printf("WM_RBUTTONUP\n"); break;
  case WM_RBUTTONDBLCLK: printf("WM_RBUTTONDBLCLK\n"); break;
  case WM_MBUTTONDOWN: printf("WM_MBUTTONDOWN\n"); break;
  case WM_MBUTTONUP: printf("WM_MBUTTONUP\n"); break;
  case WM_MBUTTONDBLCLK: printf("WM_MBUTTONDBLCLK\n"); break;
  case WM_MOUSEWHEEL: printf("WM_MOUSEWHEEL\n"); break;
  case WM_XBUTTONDOWN: printf("WM_XBUTTONDOWN\n"); break;
  case WM_XBUTTONUP: printf("WM_XBUTTONUP\n"); break;
  case WM_XBUTTONDBLCLK: printf("WM_XBUTTONDBLCLK\n"); break;

  case WM_MOUSEHWHEEL: printf("WM_MOUSEHWHEEL\n"); break;

  // case WM_MOUSELAST: printf("WM_MOUSELAST\n"); break;

 


  // case XBUTTON1: printf("XBUTTON1\n"); break;
  // case XBUTTON2: printf("XBUTTON2\n"); break;

  case WM_PARENTNOTIFY: printf("WM_PARENTNOTIFY\n"); break;
  case WM_ENTERMENULOOP: printf("WM_ENTERMENULOOP\n"); break;
  case WM_EXITMENULOOP: printf("WM_EXITMENULOOP\n"); break;
  case WM_NEXTMENU: printf("WM_NEXTMENU\n"); break;
  case WM_SIZING: printf("WM_SIZING\n"); break;
  case WM_CAPTURECHANGED: printf("WM_CAPTURECHANGED\n"); break;
  case WM_MOVING: printf("WM_MOVING\n"); break;
  case WM_POWERBROADCAST: printf("WM_POWERBROADCAST\n"); break;

  // case PBT_APMQUERYSUSPEND: printf("PBT_APMQUERYSUSPEND\n"); break;
  // case PBT_APMQUERYSTANDBY: printf("PBT_APMQUERYSTANDBY\n"); break;

  // case PBT_APMQUERYSUSPENDFAILED: printf("PBT_APMQUERYSUSPENDFAILED\n"); break;
  // case PBT_APMQUERYSTANDBYFAILED: printf("PBT_APMQUERYSTANDBYFAILED\n"); break;

  // case PBT_APMSUSPEND: printf("PBT_APMSUSPEND\n"); break;
  // case PBT_APMSTANDBY: printf("PBT_APMSTANDBY\n"); break;

  // case PBT_APMRESUMECRITICAL: printf("PBT_APMRESUMECRITICAL\n"); break;
  // case PBT_APMRESUMESUSPEND: printf("PBT_APMRESUMESUSPEND\n"); break;
  // case PBT_APMRESUMESTANDBY: printf("PBT_APMRESUMESTANDBY\n"); break;

  // case PBTF_APMRESUMEFROMFAILURE: printf("0x0\n"); break;

  // case PBT_APMBATTERYLOW: printf("PBT_APMBATTERYLOW\n"); break;
  // case PBT_APMPOWERSTATUSCHANGE: printf("PBT_APMPOWERSTATUSCHANGE\n"); break;

  // case PBT_APMOEMEVENT: printf("PBT_APMOEMEVENT\n"); break;
  // case PBT_APMRESUMEAUTOMATIC: printf("PBT_APMRESUMEAUTOMATIC\n"); break;

  case WM_DEVICECHANGE: printf("WM_DEVICECHANGE\n"); break;

  case WM_MDICREATE: printf("WM_MDICREATE\n"); break;
  case WM_MDIDESTROY: printf("WM_MDIDESTROY\n"); break;
  case WM_MDIACTIVATE: printf("WM_MDIACTIVATE\n"); break;
  case WM_MDIRESTORE: printf("WM_MDIRESTORE\n"); break;
  case WM_MDINEXT: printf("WM_MDINEXT\n"); break;
  case WM_MDIMAXIMIZE: printf("WM_MDIMAXIMIZE\n"); break;
  case WM_MDITILE: printf("WM_MDITILE\n"); break;
  case WM_MDICASCADE: printf("WM_MDICASCADE\n"); break;
  case WM_MDIICONARRANGE: printf("WM_MDIICONARRANGE\n"); break;
  case WM_MDIGETACTIVE: printf("WM_MDIGETACTIVE\n"); break;

  case WM_MDISETMENU: printf("WM_MDISETMENU\n"); break;
  case WM_ENTERSIZEMOVE: printf("WM_ENTERSIZEMOVE\n"); break;
  case WM_EXITSIZEMOVE: printf("WM_EXITSIZEMOVE\n"); break;
  case WM_DROPFILES: printf("WM_DROPFILES\n"); break;
  case WM_MDIREFRESHMENU: printf("WM_MDIREFRESHMENU\n"); break;
  default: printf("%s %x\n", "Unknown Message!: ", uMsg); break;
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
      printf("%i %i\n", (int)(short) LOWORD(lParam), (int)(short) HIWORD(lParam));
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