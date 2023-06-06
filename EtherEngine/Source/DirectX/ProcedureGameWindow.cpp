#include <DirectX/ProcedureGameWindow.h>

namespace EtherEngine {
    LRESULT CALLBACK WindowGameProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
        switch (message) {
        case WM_SIZE:
            break;

        case WM_CLOSE:  // ウィンドウを削除しようとしている
            break;

        case WM_DESTROY:    // ウィンドウを削除
            PostQuitMessage(0); // WM_QUIT メッセージを送信
            break;
        }

        return DefWindowProc(hWnd, message, wParam, lParam);
    }
}
