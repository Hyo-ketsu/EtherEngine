#include <EtherEngine/EditorApplication.h>
#include <DirectX/ProcedureGameWindow.h>
#include <ImGUI/Platform/imgui_impl_win32.h>


// 前方宣言
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


namespace EtherEngine {
    LRESULT CALLBACK WindowEditorProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
        //----- ImGui処理
        if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam)) return true;

        //----- ベース処理
        Procedure::BaseFunction();

        //----- メッセージ処理
        switch (message) {
            break;
        case WM_SYSCOMMAND:
            //----- 無効時使用しない
            if (EditorApplication::Get()->GetIsWindowFunctionEnable() == false) {
                if (wParam && SC_MINIMIZE == SC_MINIMIZE) return 0;
                if (wParam && SC_MAXIMIZE == SC_MAXIMIZE) return 0;
                if (wParam && SC_MOVE == SC_MOVE) return 0;
            }
            break;

        case WM_SIZE:
            // @ MEMO : リサイズされた際にレンダーターゲットリサイズが必要かと
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
