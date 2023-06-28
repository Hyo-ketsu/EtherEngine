#include <EtherEngine/EditorApplication.h>
#include <ImGUI/Platform/imgui_impl_win32.h>


// �O���錾
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


namespace EtherEngine {
    LRESULT CALLBACK WindowEditorProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
        if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam)) return true;

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
