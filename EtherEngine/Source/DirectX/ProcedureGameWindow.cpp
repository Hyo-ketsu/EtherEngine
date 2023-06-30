#include <DirectX/ProcedureGameWindow.h>
#include <Base/BaseInput.h>


namespace EtherEngine {
    namespace Procedure {
        // �}�E�X���W���͓��̏������s��
        void BaseFunction(void) {
            //----- �}�E�X�J�[�\���ʒu�擾
            tagPOINT pos;
            if (GetCursorPos((LPPOINT)&pos)) {
                InputSystem::SetMousePostion({ pos.x, pos.y });
            }
        }
    }
    LRESULT CALLBACK WindowGameProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
        Procedure::BaseFunction();

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
