#include <EtherEngine/EditorObjectUpdater.h>
#include <Base/ConceptUtility.h>
#include <Base/EtherEngineUtility.h>
#include <Base/HandleHelper.h>
#include <Base/WindowsDefine.h>
#include <EtherEngine/EditorApplication.h>
#include <EtherEngine/EditorObjectStorage.h>

#include <EtherEngine/EditorBuildMenuWindow.h>

#include <EtherEngine/EditorLogWindow.h>
#include <EtherEngine/EditorOutliner.h>
#include <EtherEngine/EditorExplorerWindow.h>
#include <EtherEngine/EditorInspectorWindow.h>


namespace EtherEngine {
    // メインメニューを表示する
    // @ Temp : 表示するウィンドウの型
    // @ Arg1 : オブジェクト情報
    // @ Arg2 : 表示名
    template <Concept::BaseOfConcept<EditorWindowBase> WindowType>
    void ShowWindowMenu(std::vector<BaseHandle<EditorObject>>* windows, const std::string& name);
}


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
                //----- "File"項目表示
                if (ImGui::BeginMenu("File")) {
                    //if (ImGui::MenuItem("Hoge", NULL, true)) {
                    //}
                    ImGui::EndMenu();
                }

                //----- "Menu" 表示
                if (ImGui::BeginMenu("Menu")) {
                    using namespace EtherEngine::ImGuiDefine;

                    //----- 項目表示
                    ShowWindowMenu<BuildMenu>(&m_windows, Name::WINDOW_BUILD_MENU);

                    ImGui::EndMenu();
                }

                //----- "Editor Window"項目表示
                if (ImGui::BeginMenu("Editor Window")) {
                    using namespace EtherEngine::ImGuiDefine;

                    //----- 全削除メニュー表示
                    if (ImGui::MenuItem("All Window Delete", NULL)) {
                        for (auto&& it : m_windows) {
                            EditorObjectStorage::Get()->DeleteEditorObject(it);
                        }
                    }

                    //----- 項目表示
                    ShowWindowMenu<EditorLogWindow>(&m_windows, Name::WINDOW_LOG);
                    ShowWindowMenu<EditorOutliner>(&m_windows, Name::WINDOW_OUTLINER);
                    ShowWindowMenu<ExplorerWindow>(&m_windows, Name::WINDOW_EXPLORER);
                    ShowWindowMenu<EditorInspectorWindow>(&m_windows, Name::WINDOW_INSPECTOR);

                    ImGui::EndMenu();
                }
                ImGui::EndMenuBar();
            }
            //----- ウィンドウ位置・座標設定
            ImGui::SetWindowPos(ImVec2(0 - 1, 0));
            ImGui::SetWindowSize(ImVec2(EditorApplication::Get()->GetWindSize().x() + 2, 20));

            //----- ドッキング用ウィンドウ作成
            // @ MEMO : 一旦保留
            //{
            //    //----- フラグ設定
            //    ImGuiBackendFlags flags = ImGuiWindowFlags_None
            //        | ImGuiWindowFlags_NoTitleBar
            //        | ImGuiWindowFlags_NoResize
            //        | ImGuiWindowFlags_NoMove
            //        | ImGuiWindowFlags_NoScrollbar
            //        | ImGuiWindowFlags_NoScrollWithMouse
            //        | ImGuiWindowFlags_NoCollapse
            //        | ImGuiWindowFlags_NoBackground
            //        | ImGuiWindowFlags_NoSavedSettings
            //        | ImGuiWindowFlags_HorizontalScrollbar;

            //    //----- 表示
            //    ImGui::Begin(ImGuiDefine::Name::WINDOW_SCENE_VIEW.c_str(), NULL, flags);
            //    ImGui::SetWindowPos(ImVec2(0 - 1, 18));
            //    ImGui::SetWindowSize(ImVec2(EditorApplication::Get()->GetWindSize().x() + 2, EditorApplication::Get()->GetWindSize().y() - 18));
            //    ImGui::SetWindowFocus();
            //    ImGui::End();
            //}
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


namespace EtherEngine {
    // メインメニューを表示する
    template <Concept::BaseOfConcept<EditorWindowBase> WindowType>
    void ShowWindowMenu(std::vector<BaseHandle<EditorObject>>* windows, const std::string& name) {
        //----- 一応nullチェック
        if (windows == nullptr) throw std::exception("Error! Null");

        //----- 表示
        if (ImGui::MenuItem(name.c_str(), NULL)) {
            //----- 作成
            auto object = EditorObjectStorage::Get()->CreateEditorObject();

            //----- 同名捜索
            uint count = 0;  // 同名オブジェクト数
            for (auto&& it : *windows) {
                if (it.IsEnable() == false) continue;
                if (count == 0) {   // 重複した名前が出た際に Hoge(1) などと照合するため
                    //----- 通常の検索
                    if (it.GetNoAtomicData().GetName() == name) count++; 
                }
                else {
                    //----- 検索
                    if (Utilty::IsDuplicationName(it.GetNoAtomicData().GetName(), name, count, Utilty::DuplicationNameObjectName::ParenthesesNumber)) count++;
                }
            }

            //----- 名前変更・コンポーネント追加
            if (count == 0) {
                object.GetAtomicData().AddComponent<WindowType>(name);
                object.GetAtomicData().AccessName() = name;
            }
            else {
                object.GetAtomicData().AddComponent<WindowType>(Utilty::DuplicationName(name, count, Utilty::DuplicationNameObjectName::ParenthesesNumber));
                object.GetAtomicData().AccessName() = Utilty::DuplicationName(name.c_str(), count, Utilty::DuplicationNameObjectName::ParenthesesNumber);
            }

            //----- 追加
            windows->push_back(object);
        }
    }
}
