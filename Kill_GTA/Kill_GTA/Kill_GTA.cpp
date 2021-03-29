﻿
#include <cstdint>
#include <string>
#include <vector>

#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <psapi.h>

#include "framework.h"
#include "Kill_GTA.h"

#define MAX_LOADSTRING 100

HINSTANCE hInst;
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

class Processor
{
public:
	void PrintProcessNameAndID(DWORD processID)
	{
		char szProcessName[MAX_PATH] = "<unknown>";

		HANDLE hProcess = OpenProcess(
			PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | PROCESS_TERMINATE,
			FALSE, processID);

		if (hProcess)
		{
			HMODULE hMod{};
			DWORD cbNeeded{};

			if (EnumProcessModules(hProcess, &hMod, sizeof(hMod),
				&cbNeeded))
			{
				GetModuleBaseNameA(hProcess, hMod, szProcessName,
					sizeof(szProcessName) / sizeof(TCHAR));
			}

			if (std::string("GTA5.exe") == szProcessName)
			{
				TerminateProcess(hProcess, 0);
			}
			CloseHandle(hProcess);
		}
	}

	void find_and_kill()
	{
		DWORD aProcesses[1024], cbNeeded, cProcesses;

		if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
			return;

		cProcesses = cbNeeded / sizeof(DWORD);
		for (int i = 0; i < cProcesses; i++)
		{
			if (aProcesses[i] != 0)
			{
				PrintProcessNameAndID(aProcesses[i]);
			}
		}
	}

	enum class e_keyboard_key_id : uint32_t
	{
		undefined = 0,
		_0,
		_1,
		_2,
		_3,
		_4,
		_5,
		_6,
		_7,
		_8,
		_9,
		_a,
		_b,
		_c,
		_d,
		_e,
		_f,
		_g,
		_h,
		_i,
		_j,
		_k,
		_l,
		_m,
		_n,
		_o,
		_p,
		_q,
		_r,
		_s,
		_t,
		_u,
		_v,
		_w,
		_x,
		_y,
		_z,
		numpud_0,
		numpud_1,
		numpud_2,
		numpud_3,
		numpud_4,
		numpud_5,
		numpud_6,
		numpud_7,
		numpud_8,
		numpud_9,
		f1,
		f2,
		f3,
		f4,
		f5,
		f6,
		f7,
		f8,
		f9,
		f10,
		f11,
		f12,
		f13,
		f14,
		f15,
		f16,
		f17,
		f18,
		f19,
		f20,
		f21,
		f22,
		f23,
		f24,
		backspace,
		tab,
		clear,
		enter,
		shift,
		shift_left,
		shift_right,
		control,
		control_left,
		control_right,
		menu,
		menu_left,
		menu_right,
		pause_break,
		caps_lock,
		escape,
		spacebar,
		end,
		home,
		arrow_left,
		arrow_right,
		arrow_up,
		arrow_down,
		select,
		print,
		insert,
		del, // delete
		win_left,
		win_right,
		apps,
		sleep,
		multiply, // num *
		add, // num +
		separator,
		substract, // num -
		decimal, // num .
		devide, // num /
		num_lock,
		scroll_lock,
		browser_back,
		browser_forward,
		browser_refresh,
		browser_stop,
		browser_search,
		browser_favorites,
		browser_home,
		volume_mute,
		volume_up,
		volume_down,
		media_next,
		media_previous,
		media_stop,
		media_play_pause,
		launch_mail,
		launch_media_select,
		launch_app1,
		launch_app2,
		plus, // '+' or '='
		minus, // '-'
		period,// '.', '>'
		comma,// ',', '<'
		print_screen,
		page_up,
		page_down,
		tilde, // '`'
		bracket_open, // '['
		slash, // '\'
		slash_back, // '/'
		bracket_close, // ']'
		quote, // `'`
		semicolon, // ';'
	};

	int32_t to_virtual_key(const e_keyboard_key_id vk)
	{
		using id = e_keyboard_key_id;

		if (vk == id::_0) return 0x30;
		if (vk == id::_1) return 0x31;
		if (vk == id::_2) return 0x32;
		if (vk == id::_3) return 0x33;
		if (vk == id::_4) return 0x34;
		if (vk == id::_5) return 0x35;
		if (vk == id::_6) return 0x36;
		if (vk == id::_7) return 0x37;
		if (vk == id::_8) return 0x38;
		if (vk == id::_9) return 0x39;

		if (vk == id::_a) return 0x41;
		if (vk == id::_b) return 0x42;
		if (vk == id::_c) return 0x43;
		if (vk == id::_d) return 0x44;
		if (vk == id::_e) return 0x45;
		if (vk == id::_f) return 0x46;
		if (vk == id::_g) return 0x47;
		if (vk == id::_h) return 0x48;
		if (vk == id::_i) return 0x49;
		if (vk == id::_j) return 0x4A;
		if (vk == id::_k) return 0x4B;
		if (vk == id::_l) return 0x4C;
		if (vk == id::_m) return 0x4D;
		if (vk == id::_n) return 0x4E;
		if (vk == id::_o) return 0x4F;
		if (vk == id::_p) return 0x50;
		if (vk == id::_q) return 0x51;
		if (vk == id::_r) return 0x52;
		if (vk == id::_s) return 0x53;
		if (vk == id::_t) return 0x54;
		if (vk == id::_u) return 0x55;
		if (vk == id::_v) return 0x56;
		if (vk == id::_w) return 0x57;
		if (vk == id::_x) return 0x58;
		if (vk == id::_y) return 0x59;
		if (vk == id::_z) return 0x5A;

		if (vk == id::numpud_0) return VK_NUMPAD0;
		if (vk == id::numpud_1) return VK_NUMPAD1;
		if (vk == id::numpud_2) return VK_NUMPAD2;
		if (vk == id::numpud_3) return VK_NUMPAD3;
		if (vk == id::numpud_4) return VK_NUMPAD4;
		if (vk == id::numpud_5) return VK_NUMPAD5;
		if (vk == id::numpud_6) return VK_NUMPAD6;
		if (vk == id::numpud_7) return VK_NUMPAD7;
		if (vk == id::numpud_8) return VK_NUMPAD8;
		if (vk == id::numpud_9) return VK_NUMPAD9;

		if (vk == id::f1) return VK_F1;
		if (vk == id::f2) return VK_F2;
		if (vk == id::f3) return VK_F3;
		if (vk == id::f4) return VK_F4;
		if (vk == id::f5) return VK_F5;
		if (vk == id::f6) return VK_F6;
		if (vk == id::f7) return VK_F7;
		if (vk == id::f8) return VK_F8;
		if (vk == id::f9) return VK_F9;
		if (vk == id::f10) return VK_F10;
		if (vk == id::f11) return VK_F11;
		if (vk == id::f12) return VK_F12;

		if (vk == id::enter) return VK_RETURN;
		if (vk == id::spacebar) return VK_SPACE;
		if (vk == id::escape) return VK_ESCAPE;
		if (vk == id::page_up) return VK_PRIOR;
		if (vk == id::page_down) return VK_NEXT;
		if (vk == id::end) return VK_END;
		if (vk == id::home) return VK_HOME;
		if (vk == id::arrow_left) return VK_LEFT;
		if (vk == id::arrow_up) return VK_UP;
		if (vk == id::arrow_right) return VK_RIGHT;
		if (vk == id::arrow_down) return VK_DOWN;
		if (vk == id::del) return VK_DELETE;
		if (vk == id::tab) return VK_TAB;
		if (vk == id::backspace) return VK_BACK;
		if (vk == id::print_screen) return VK_SNAPSHOT;
		if (vk == id::pause_break) return VK_PAUSE;
		if (vk == id::caps_lock) return VK_CAPITAL;
		if (vk == id::insert) return VK_INSERT;
		if (vk == id::apps) return VK_APPS;
		if (vk == id::multiply) return VK_MULTIPLY;
		if (vk == id::add) return VK_ADD;
		if (vk == id::substract) return VK_SUBTRACT;
		if (vk == id::decimal) return VK_DECIMAL;
		if (vk == id::devide) return VK_DIVIDE;
		if (vk == id::num_lock) return VK_NUMLOCK;
		if (vk == id::tilde) return VK_OEM_3;
		if (vk == id::minus) return VK_OEM_MINUS;
		if (vk == id::plus) return VK_OEM_PLUS;
		if (vk == id::bracket_open) return VK_OEM_4;
		if (vk == id::bracket_close) return VK_OEM_6;
		if (vk == id::slash) return VK_OEM_5;
		if (vk == id::quote) return VK_OEM_7;
		if (vk == id::semicolon) return VK_OEM_1;
		if (vk == id::slash_back) return VK_OEM_2;
		if (vk == id::period) return VK_OEM_PERIOD;
		if (vk == id::comma) return VK_OEM_COMMA;
		if (vk == id::scroll_lock) return VK_SCROLL;
		if (vk == id::volume_mute) return VK_VOLUME_MUTE;
		if (vk == id::volume_down) return VK_VOLUME_DOWN;
		if (vk == id::volume_up) return VK_VOLUME_UP;
		if (vk == id::media_next) return VK_MEDIA_NEXT_TRACK;
		if (vk == id::media_previous) return VK_MEDIA_PREV_TRACK;
		if (vk == id::media_stop) return VK_MEDIA_STOP;
		if (vk == id::media_play_pause) return VK_MEDIA_PLAY_PAUSE;
		if (vk == id::clear) return VK_CLEAR;

		if (vk == id::win_left) return VK_LWIN;
		if (vk == id::win_right) return VK_RWIN;

		if (vk == id::shift) return VK_SHIFT;

		if (vk == id::shift_left) return VK_LSHIFT;
		if (vk == id::shift_right) return VK_RSHIFT;

		if (vk == id::control_left) return VK_LCONTROL;
		if (vk == id::control) return VK_CONTROL;

		if (vk == id::menu_left) return VK_LMENU;
		if (vk == id::menu_right) return VK_RMENU;

		return 0;
	}

	bool scancode_filtered(const e_keyboard_key_id vk)
	{
		using id = e_keyboard_key_id;
		switch (vk)
		{
		case id::arrow_down:
		case id::arrow_left:
		case id::arrow_right:
		case id::arrow_up:
		case id::del:
		case id::insert:
		case id::home:
		case id::end:
		case id::page_down:
		case id::page_up:
		case id::win_left:
			return true;
		}

		return false;
	}

	auto generate_key_press(e_keyboard_key_id vk, bool press)
	{
		INPUT input{};
		input.type = INPUT_KEYBOARD;
		input.ki.wVk = to_virtual_key(vk);

		input.ki.wScan = static_cast<WORD>(MapVirtualKey(static_cast<UINT>(input.ki.wVk), MAPVK_VK_TO_VSC));
		input.ki.dwFlags = KEYEVENTF_SCANCODE;

		if (scancode_filtered(vk))
			input.ki.dwFlags |= KEYEVENTF_EXTENDEDKEY;

		if (!press)
			input.ki.dwFlags |= KEYEVENTF_KEYUP;

		return input;
	}

	void push_double_event(e_keyboard_key_id vk, int times = 1)
	{
		INPUT input{};
		for (int idx = 0; idx < times; ++idx)
		{
			input = generate_key_press(vk, true);
			SendInput(1, &input, sizeof(INPUT));
			input = generate_key_press(vk, false);
			SendInput(1, &input, sizeof(INPUT));
		}
	}

	void generate_armor_use(bool i_am_chief)
	{
		push_double_event(e_keyboard_key_id::_m);
		push_double_event(e_keyboard_key_id::arrow_down, i_am_chief ? 3 : 2);
		push_double_event(e_keyboard_key_id::enter);
		push_double_event(e_keyboard_key_id::arrow_down, 1);
		push_double_event(e_keyboard_key_id::enter);
		push_double_event(e_keyboard_key_id::arrow_down, 4);
		push_double_event(e_keyboard_key_id::enter);
		push_double_event(e_keyboard_key_id::_m);
	}

	void generate_snack_use(bool i_am_chief)
	{
		push_double_event(e_keyboard_key_id::_m);
		push_double_event(e_keyboard_key_id::arrow_down, i_am_chief ? 3 : 2);
		push_double_event(e_keyboard_key_id::enter);
		push_double_event(e_keyboard_key_id::arrow_down, 2);
		push_double_event(e_keyboard_key_id::enter, 2);
		push_double_event(e_keyboard_key_id::_m);
	}

	void on_keyboard_event(uint32_t msg, KBDLLHOOKSTRUCT* data)
	{
		static bool ctrl_pressed = false;

		if (msg == WM_KEYDOWN && data)
		{
			if (data->vkCode == VK_LCONTROL)
			{
				ctrl_pressed = true;
			}
			else if (data->vkCode == VK_F12)
			{
				if (ctrl_pressed)
					find_and_kill();
			}
			else if (data->vkCode == VK_F11)
			{
				if (ctrl_pressed)
					generate_armor_use(false);
			}
			else if (data->vkCode == VK_F10)
			{
				if (ctrl_pressed)
					generate_snack_use(false);
			}
		}
		else if (msg == WM_KEYUP)
		{
			if (data->vkCode == VK_LCONTROL)
			{
				ctrl_pressed = false;
			}
		}
	}
};
int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPWSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_KILLGTA, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_KILLGTA));

	MSG msg;

	auto hookKeyboard = SetWindowsHookExA(WH_KEYBOARD_LL,
		[](int code, WPARAM wParam, LPARAM lParam)->LRESULT
		{
			if (code < 0)
				return CallNextHookEx(0, code, wParam, lParam);

			on_keyboard_event(static_cast<uint32_t>(wParam), reinterpret_cast<KBDLLHOOKSTRUCT*>(lParam));

			return CallNextHookEx(0, code, wParam, lParam);
		}, 0, 0);

	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	UnhookWindowsHookEx(hookKeyboard);
	return (int)msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_KILLGTA));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_KILLGTA);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance;

	HWND hWnd = CreateWindowW(szWindowClass, L"Я НЕ ШЕФ", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, 250, 160, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		switch (wmId)
		{
		case IDM_IAMCHIEF:
			SetWindowText(hWnd, L"Я ШЕФ, СУЧКА!!!");
			break;
		case IDM_IAMNOTCHIEF:
			SetWindowText(hWnd, L"Я НЕ ШЕФ");
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
