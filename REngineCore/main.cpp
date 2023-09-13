#include <Windows.h>
#include <d3d9.h>


/** ���������� ��������� ����
 *
 * @param hWnd ���������� ����
 * @param uMsg ���������
 * @param wParam �������� ���� WORD
 * @param lParam �������� ���� LONG
 */
LRESULT CALLBACK WndMsgHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
		case WM_DESTROY: {
			PostQuitMessage(WM_QUIT); break;
		}
		case WM_PAINT: {
			PAINTSTRUCT ps{};
			HDC hdc{};
			hdc = BeginPaint(hWnd, &ps);
			FillRect(hdc, &ps.rcPaint, reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1));
			EndPaint(hWnd, &ps);
			return 0;
		}
		default: {
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
		}
	}
	return 0;
}


/** �������� ���� ���������
 * 
 * @param hInstance ��������� ����������
 * @param hPrevInstance ���������� ��������� ����������
 * @param lpCmdLine ��������� ��������� ������
 * @param nCmdShow ����� ����������� ����
 */
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow) {
	MSG msg{};
	HWND hWnd{};
	WNDCLASSEX wcEx{sizeof(WNDCLASSEX)};

	wcEx.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	wcEx.hCursor = LoadCursorW(NULL, IDC_ARROW);
	wcEx.hIcon = LoadIconW(NULL, IDI_APPLICATION);
	wcEx.hIconSm = LoadIconW(NULL, IDI_APPLICATION);
	wcEx.hInstance = hInstance;
	wcEx.lpszClassName = L"REngineMainWindow";
	wcEx.lpszMenuName = NULL;
	wcEx.style = CS_HREDRAW | CS_VREDRAW;
	wcEx.lpfnWndProc = WndMsgHandler;

	if (!RegisterClassEx(&wcEx)) {
		return EXIT_FAILURE;
	}

	hWnd = CreateWindow(wcEx.lpszClassName, L"REngine Core", WS_OVERLAPPEDWINDOW, 0, 0, 800, 600, NULL, NULL, wcEx.hInstance, NULL);

	if (hWnd == INVALID_HANDLE_VALUE) {
		return EXIT_FAILURE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&msg, NULL, NULL, NULL)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return static_cast<int>(msg.wParam);
}