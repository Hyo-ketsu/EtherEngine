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

        ////----- 常時透明・ドッキング可能なウィンドウを表示する
        //{
        //    //----- メニューバー用ウィンドウ表示
        //    if (ImGui::Begin(ImGuiDefine::Name::WINDOW_MENU.c_str(), NULL, ImGuiWindowFlags_None
        //        | ImGuiWindowFlags_NoTitleBar
        //        | ImGuiWindowFlags_NoResize
        //        | ImGuiWindowFlags_NoMove
        //        | ImGuiWindowFlags_NoScrollbar
        //        | ImGuiWindowFlags_NoScrollWithMouse
        //        | ImGuiWindowFlags_NoCollapse
        //        | ImGuiWindowFlags_NoBackground
        //        | ImGuiWindowFlags_NoSavedSettings
        //        | ImGuiWindowFlags_MenuBar
        //        | ImGuiWindowFlags_HorizontalScrollbar
        //        | ImGuiWindowFlags_NoFocusOnAppearing
        //        | ImGuiWindowFlags_NoDocking
        //        )) {
        //        //----- メニュー表示
        //        if (ImGui::BeginMenuBar()) {
        //            //----- "File"項目表示
        //            if (ImGui::BeginMenu("File")) {
        //                //if (ImGui::MenuItem("Hoge", NULL, true)) {
        //                //}
        //                ImGui::EndMenu();
        //            }

        //            //----- "Menu" 表示
        //            if (ImGui::BeginMenu("Menu")) {
        //                using namespace EtherEngine::ImGuiDefine;

        //                //----- 項目表示
        //                ShowWindowMenu<BuildMenu>(&m_windows, Name::WINDOW_BUILD_MENU);

        //                ImGui::EndMenu();
        //            }

        //            //----- "Editor Window"項目表示
        //            if (ImGui::BeginMenu("Editor Window")) {
        //                using namespace EtherEngine::ImGuiDefine;

        //                //----- 全削除メニュー表示
        //                if (ImGui::MenuItem("All Window Delete", NULL)) {
        //                    for (auto&& it : m_windows) {
        //                        EditorObjectStorage::Get()->DeleteEditorObject(it);
        //                    }
        //                }

        //                //----- 項目表示
        //                ShowWindowMenu<EditorLogWindow>(&m_windows, Name::WINDOW_LOG);
        //                ShowWindowMenu<EditorOutliner>(&m_windows, Name::WINDOW_OUTLINER);
        //                ShowWindowMenu<ExplorerWindow>(&m_windows, Name::WINDOW_EXPLORER);
        //                ShowWindowMenu<EditorInspectorWindow>(&m_windows, Name::WINDOW_INSPECTOR);

        //                ImGui::EndMenu();
        //            }
        //            ImGui::EndMenuBar();
        //        }
        //        //----- ゲーム再生・停止ボタン表示
        //        ImGui::Columns(5, (ImGuiDefine::Name::WINDOW_MENU + "GameButton Columns").c_str(), false);
        //        ImGui::Dummy(ImVec2()); ImGui::NextColumn(); ImGui::Dummy(ImVec2()); ImGui::NextColumn();
        //        if (ImGui::Button("Start")) EditorApplication::Get()->StartGameMode(); ImGui::SameLine();
        //        if (ImGui::Button("Stop")) EditorApplication::Get()->StopGameMode(); ImGui::SameLine();
        //        if (ImGui::Button("End")) EditorApplication::Get()->EndGameMode(); ImGui::SameLine();
        //        ImGui::Dummy(ImVec2()); ImGui::NextColumn(); ImGui::Dummy(ImVec2()); ImGui::NextColumn();

        //        //----- ウィンドウ位置・座標設定
        //        Eigen::Vector2i windowPostion;
        //        Eigen::Vector2i frameSize;
        //        RECT clientSize;
        //        {
        //            auto hWnd = EditorApplication::Get()->GetHWND();

        //            //----- 変数宣言
        //            RECT windowSize;

        //            //----- ウィンドウ位置・サイズを取得
        //            if (GetWindowRect(hWnd, &windowSize) == false) std::exception("Error! Non GetWindowRect");

        //            //----- クライアント領域を取得
        //            if (GetClientRect(hWnd, &clientSize) == false) std::exception("Error! Non GetClientRect");

        //            //----- フレームサイズ算出
        //            frameSize.x() = (windowSize.right - windowSize.left) - (clientSize.right - clientSize.left);
        //            frameSize.y() = (windowSize.bottom - windowSize.top) - (clientSize.bottom - clientSize.top);

        //            //----- 最終的な位置計算
        //            windowPostion.x() = windowSize.left + clientSize.left;
        //            windowPostion.y() = windowSize.top + clientSize.top;
        //        }
        //        ImGui::SetWindowPos(ImVec2(windowPostion.x() + (frameSize.x() / 2), windowPostion.y() + (frameSize.y() / 2) + (frameSize.y() / 4)));
        //        ImGui::SetWindowSize(ImVec2(clientSize.right, 60));

        //        ImGui::End();
        //    }
        //}

        //----- EditorObject描画
        auto draw = EditorObjectStorage::Get()->GetEditorObjectAll();
        for (auto&& it : draw) {
            it.GetAtomicData().Draw();
        }

        EditorObjectStorage::Get()->DeleteEditorObjectsDelete();

        ImGui::Render();
    }
    // エディターオブジェクトの描画後処理を行う
    void EditorUpdater::LateDraw(void) {
        //----- IMGUI描画後処理
        auto io = ImGui::GetIO();
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
        }
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
                    if (Utility::IsDuplicationName(it.GetNoAtomicData().GetName(), name, count, Utility::DuplicationNameObjectName::ParenthesesNumber)) count++;
                }
            }

            //----- 名前変更・コンポーネント追加
            if (count == 0) {
                object.GetAtomicData().AddComponent<WindowType>(name);
                object.GetAtomicData().AccessName() = name;
            }
            else {
                object.GetAtomicData().AddComponent<WindowType>(Utility::DuplicationName(name, count, Utility::DuplicationNameObjectName::ParenthesesNumber));
                object.GetAtomicData().AccessName() = Utility::DuplicationName(name.c_str(), count, Utility::DuplicationNameObjectName::ParenthesesNumber);
            }

            //----- 追加
            windows->push_back(object);
        }
    }
}
