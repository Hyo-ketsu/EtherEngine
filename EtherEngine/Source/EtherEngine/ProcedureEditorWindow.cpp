#include <EtherEngine/EditorApplication.h>
#include <ImGUI/Platform/imgui_impl_win32.h>


// 前方宣言
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


namespace EtherEngine {
    LRESULT CALLBACK WindowEditorProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
        if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam)) return true;

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
