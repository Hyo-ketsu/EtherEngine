#include <EtherEngine/EditorObjectUpdater.h>
#include <Base/WindowsDefine.h>
#include <EtherEngine/EditorApplication.h>
#include <EtherEngine/EditorObjectStorage.h>


namespace EtherEngine {
    // エディターオブジェクトに更新処理を行う
    void EditorUpdater::Update(void) {
        auto update = EditorObjectStorage::Get()->GetEditorObjectAll();
        for (auto&& it : update) {
            it.GetAtomicData().Update();
        }
        EditorObjectStorage::Get()->DeleteEditorObjectsDelete();
    }

    // エディターオブジェクトの描画処理を行う
    void EditorUpdater::Draw(void) {
        //----- IMGUI描画処理
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        //----- 常時透明・ドッキング可能なウィンドウを表示する
        {
            //----- メニューバー用ウィンドウ表示
            ImGui::Begin(ImGuiDefine::Name::WINDOW_MENU.c_str(), NULL, ImGuiWindowFlags_None
                | ImGuiWindowFlags_NoTitleBar
                | ImGuiWindowFlags_NoResize
                | ImGuiWindowFlags_NoMove
                | ImGuiWindowFlags_NoScrollbar
                | ImGuiWindowFlags_NoScrollWithMouse
                | ImGuiWindowFlags_NoCollapse
                | ImGuiWindowFlags_NoBackground
                | ImGuiWindowFlags_NoSavedSettings
                | ImGuiWindowFlags_MenuBar
                | ImGuiWindowFlags_HorizontalScrollbar
                | ImGuiWindowFlags_NoFocusOnAppearing
                | ImGuiWindowFlags_NoDocking
            );
            //----- メニュー表示
            if (ImGui::BeginMenuBar()) {
                if (ImGui::BeginMenu("File")) {
                    //if (ImGui::MenuItem("Hoge", NULL, true)) {
                    //}
                    ImGui::EndMenu();
                }
                ImGui::EndMenuBar();
            }
            //----- ウィンドウ位置・座標設定
            ImGui::SetWindowPos(ImVec2(0 - 1, 0));
            ImGui::SetWindowSize(ImVec2(EditorApplication::Get()->GetWindSize().x() + 2, EditorApplication::Get()->GetWindSize().y()));

            //----- ドッキング用ウィンドウ作成
            {
                ImGui::Begin(ImGuiDefine::Name::WINDOW_SCENE_VIEW.c_str(), NULL, ImGuiWindowFlags_None
                    | ImGuiWindowFlags_NoTitleBar
                    | ImGuiWindowFlags_NoResize
                    | ImGuiWindowFlags_NoMove
                    | ImGuiWindowFlags_NoScrollbar
                    | ImGuiWindowFlags_NoScrollWithMouse
                    | ImGuiWindowFlags_NoCollapse
                    | ImGuiWindowFlags_NoBackground
                    | ImGuiWindowFlags_NoSavedSettings
                    | ImGuiWindowFlags_HorizontalScrollbar
                );
                ImGui::SetWindowPos(ImVec2(0 - 1, 18));
                ImGui::SetWindowSize(ImVec2(EditorApplication::Get()->GetWindSize().x() + 2, EditorApplication::Get()->GetWindSize().y() - 18));
                ImGui::End();
            }
            ImGui::End();
        }

        //----- EditorObject描画
        auto draw = EditorObjectStorage::Get()->GetEditorObjectAll();
        for (auto&& it : draw) {
            it.GetAtomicData().Draw();
        }

        EditorObjectStorage::Get()->DeleteEditorObjectsDelete();

        ImGui::Render();
    }
}
