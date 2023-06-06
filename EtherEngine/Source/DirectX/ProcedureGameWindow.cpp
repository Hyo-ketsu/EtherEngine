#include <DirectX/ProcedureGameWindow.h>

namespace EtherEngine {
    LRESULT CALLBACK WindowGameProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
        switch (message) {
        case WM_SIZE:
            break;

        case WM_CLOSE:  // �E�B���h�E���폜���悤�Ƃ��Ă���
            break;

        case WM_DESTROY:    // �E�B���h�E���폜
            PostQuitMessage(0); // WM_QUIT ���b�Z�[�W�𑗐M
            break;
        }

        return DefWindowProc(hWnd, message, wParam, lParam);
    }
}
