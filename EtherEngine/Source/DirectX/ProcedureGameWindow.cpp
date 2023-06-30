#include <DirectX/ProcedureGameWindow.h>
#include <Base/BaseInput.h>


namespace EtherEngine {
    namespace Procedure {
        // マウス座標入力等の処理を行う
        void BaseFunction(void) {
            //----- マウスカーソル位置取得
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

        case WM_CLOSE:  // ウィンドウを削除しようとしている
            break;

        case WM_DESTROY:    // ウィンドウを削除
            PostQuitMessage(0); // WM_QUIT メッセージを送信
            break;
        }

        return DefWindowProc(hWnd, message, wParam, lParam);
    }
}
