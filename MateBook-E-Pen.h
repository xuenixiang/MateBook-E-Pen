#pragma once

#include "resource.h"
#include "thread"
#include "iostream"
#include "gdiplus.h"
#include "atlbase.h"
#include "comutil.h"
#include "shellapi.h"
#include "string"
#include "Shlobj.h"
#include "fstream"
#include "TlHelp32.h"
#include "vector"

using namespace std;
using namespace ATL;
using namespace Gdiplus;

#pragma comment(lib, "uuid.lib")
#pragma comment(lib, "Oleacc.lib")
#pragma comment(lib, "comsuppw.lib")
#pragma comment(lib, "WS2_32")
#pragma comment(lib,"gdiplus.lib")

#define WM_TRAY (WM_USER + 1)

#define CanUpdate 1
#define UpToDate 2
#define CheckUpdateFailed 3

#define LBUTTONDOWN 1
#define LBUTTONUP 2
#define LBUTTONREDOWN 3

#define NOTOUT 0
#define SELECTING 1
#define NOSELECTING 4

#define MAX_LOADSTRING 100

#pragma warning(disable: 4996)
#pragma warning(disable: 4267)
#pragma warning(disable: 4244)

struct IAcc_Located
{
	HWND hwnd_current = nullptr;
	HWND hwnd_old = nullptr;
	CComPtr<IAccessible> acc_eraser = nullptr;
	wstring acc_eraser_name = L"";
	CComPtr<IAccessible> acc_pen = nullptr;
	wstring acc_pen_name = L"";
};

// 全局变量
HINSTANCE hInst;                                // 当前实例
HHOOK hHook;									// 钩子句柄
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名
HWND inst_hwnd;                                 // 主窗口句柄
HWND hwnd_popup;                                // 弹出窗口句柄
NOTIFYICONDATA nid;                             // 托盘图标结构体
int state;                                      // 当前托盘图标
HMENU hMenu;    					    		// 菜单句柄
HRESULT hr;                                     // HRESULT
long current_count = 0;                         // 当前子元素的数量
BOOL BUTTON = FALSE;                            // 笔侧键是否按下
string update_version;  					    // 更新版本号
string update_info; 			  			    // 更新信息
BOOL if_init = FALSE;                           // 是否初始化
GdiplusStartupInput m_gdiplusStartupInput;		// GDI+初始化结构体
ULONG_PTR m_pGdiToken;							// GDI+初始化标识符
int default_mode = 1;							// 默认模式
BOOL float_mode = TRUE;							// 悬浮球开关

const char* windowname;                         // 寻找的窗口名
HWND hwnd_temp;     						    // 窗口句柄
int if_used;                                    // 使用情况计数
BOOL switch_back;                               // 是否切换回原窗口
BOOL go_update;                                 // 是否更新
BOOL note_pic_copy_running = FALSE;             // 是否正在运行复制批注
int ClickFloatState;							// 鼠标左键状态传递
int FloatSelectState;							// 鼠标左键状态传递
int SubFloatSelecting;							// 悬浮窗选择状态传递
WCHAR temp_file[MAX_PATH];                      // 批注模式临时文件路径
POINT posMouseClick;							// 鼠标点击位置

// 图标
int idi_MAIN, idi_WnE, idi_SCREENSHOT, idi_COPY, idi_NOTE, idi_PASTE, idi_UNDO;
Bitmap *idb_MAIN, *idb_WnE, *idb_SCREENSHOT, *idb_NOTE, *idb_COPY, *idb_PASTE, *idb_UNDO;
HWND WnE, SCREENSHOT, NOTE, COPY, PASTE, UNDO;

// 此代码模块中包含的函数的前向声明
ATOM                    MyRegisterClass(HINSTANCE hInstance);
BOOL                    InitInstance(HINSTANCE hInstance, int nCmdShow);
LRESULT CALLBACK        WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK		PenProc(int nCode, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK        ToUpdate(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK        show_error(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK        popup(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
BOOL					UpdateFloat(Image* image, HWND hwnd, int Width, int Height);
Bitmap*					LoadImageFromResource(HMODULE hMod, const wchar_t* resid, const wchar_t* restype);
void					FloatMouse(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void					IconRightClick(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
bool					IsCursorInTriangle(POINT cursorPos, POINT triVertex1, POINT triVertex2, POINT triVertex3);
void*					SubFloatMotion();
void*					SubFloatSelect();
void                    Tray(HWND hWnd);
void                    Change_Icon();
void					init(HWND hWnd);
void					show_message(const wchar_t* title, const wchar_t* message);
HWND                    findwindow(const char* Windowname);
HWND                    findchlidwindow(HWND hwnd_in, const char* Windowname);
CComPtr<IAccessible>    findchild(CComPtr<IAccessible> acc_in, const wchar_t* name, int which);
CComPtr<IAccessible>    findchild_which(CComPtr<IAccessible> acc_in, int which);
vector<CComPtr<IAccessible>> findchild_all(CComPtr<IAccessible> acc_in);
wstring                 getname(CComPtr<IAccessible> acc, CComVariant varChild);
wstring                 getrole(CComPtr<IAccessible> acc, CComVariant varChild);
wstring					getstate(CComPtr<IAccessible> acc, CComVariant varChild);
BOOL					isProgramRunning(const wchar_t* program_name);
BOOL					killProcess(const wchar_t* program_name);
vector<wstring>			findfiles(wstring filePath, wstring fileFormat);
BOOL					modify_file_text(string file_name, wstring start_str, wstring end_str, wstring new_text);
wstring					read_file_text(string file_name, wstring start_str, wstring end_str);
string                  GetRegValue(int nKeyType, const string& strUrl, const string& strKey);
BOOL                    SetRegValue_REG_DWORD(int nKeyType, const string& strUrl, const string& strKey, const DWORD& dwValue);
string                  midstr(string str, PCSTR start, PCSTR end);
string                  wstring2string(const wstring& ws);
wstring                 string2wstring(const string& s);
BOOL                    get_if_dark();
void                    switch_dark(BOOL if_dark);
HRESULT                 check_update();
HRESULT                 update(HWND hWnd, int state);
bool					CopyFileAsBitmapToClipboard(WCHAR FileName[MAX_PATH]);
int                     CopyFileToClipboard(WCHAR szFileName[MAX_PATH]);
void*					main_thread();
void*					auto_switch_back();
void*					light_or_dark();
void*					ink_setting_lock();
void*					note_pic_copy();