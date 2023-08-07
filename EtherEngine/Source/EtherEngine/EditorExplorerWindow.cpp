#include <EtherEngine/EditorExplorerWindow.h>
#include <Base/WindowsDefine.h>


//----- 関数実装
namespace EtherEngine {
    // パスを全て表示する
    // @ Arg1 : 何個目のノードか
    // @ Arg2 : フラグ
    // @ Arg3 : パス
    // @ Arg4 : 選択された場合に設定するカレントディレクトリ
    void ShowPath(int& number, const ImGuiTreeNodeFlags& flag, const PathClass& path, PathClass* current) {
        //----- 拡張子がある（ディレクトリではない）ファイルは表示は行わない
        if (path.HasExtension()) return;

        for (auto&& it : path.GetDirectory()) {
            //----- 通常ファイル(=拡張子が存在する)の表示はしない
            if (it.HasExtension()) continue;

            //----- 現在のパスを取得
            // @ Memo : "C:/Hoge/Fuga/Piyo" であれば "Piyo"
            std::string thisPath = it;
            auto pos = thisPath.find_last_of("/");
            if (std::string::npos != pos) {
                thisPath.erase(0, pos + 1);
            }
            else {
                pos = thisPath.find_last_of("\\"); 
                if (std::string::npos != pos) {
                    thisPath.erase(0, pos + 1);
                }
            }

            //----- 表示
            bool node_open = ImGui::TreeNodeEx(static_cast<void*>(&number), flag, thisPath.c_str());

            //----- 選択されたディレクトリをカレントディレクトリとして設定する
            if (ImGui::IsItemClicked()) {
                *current = it;
            }

            //----- D&D表示
            if (ImGui::BeginDragDropSource()) {
                ImGui::SetDragDropPayload("ExplorerHierarchyD&D", NULL, 0);
                ImGui::EndDragDropSource();
            }

            //----- 開かれているノードの表示(再帰)
            if (node_open) {
                ShowPath(number,flag, it, current);
                ImGui::TreePop();
            }

            number++;
        }
    }
}


//----- ExplorerWindow 定義
namespace EtherEngine {
    void ExplorerWindow::Start(void) {
        //----- 初期ディレクトリ設定
        // @ MEMO : 仮でカレントディレクトリ
        if (ms_topDirectory.has_value() == false) {
            ms_topDirectory = PathClass::GetCurDirectory();
            ms_currentDirectory = ms_topDirectory.value();
        }
    }
    void ExplorerWindow::Update(void) {
    }


    void ExplorerWindow::DrawWindow(void) {
        if (ms_topDirectory.has_value() == false) return;

        //----- ウィンドウフラグの設定
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_HorizontalScrollbar;

        //----- 階層ウィンドウサイズ設定
        m_hierarchyView.x = ImGui::GetWindowSize().x / 2;
        m_hierarchyView.y = 65535;

        //----- 階層ウィンドウ表示
        ImGui::BeginChild((ImGuiDefine::Name::WINDOW_EXPLORER + " HierarchyView").c_str(), m_hierarchyView, false, window_flags);
        {
            //----- リスト表示
            if (ImGui::BeginListBox("HierarchyList")) {
                //----- 変数宣言
                int i = 0;
                ImGuiTreeNodeFlags flags = 
                    ImGuiTreeNodeFlags_OpenOnArrow | 
                    ImGuiTreeNodeFlags_OpenOnDoubleClick | 
                    ImGuiTreeNodeFlags_SpanAvailWidth | 
                    ImGuiTreeNodeFlags_Selected;

                //----- 順次表示
                ShowPath(i, flags, ms_currentDirectory, &ms_currentDirectory);

                ImGui::EndListBox();
            }
        }
        ImGui::EndChild();

        //----- ディレクトリ内表示
        ImGui::BeginChild((ImGuiDefine::Name::WINDOW_EXPLORER + "FileView").c_str(), m_hierarchyView, false, window_flags);
        {
            //----- 内容物の表示
            for (auto&& it : ms_currentDirectory.GetDirectory()) {

            }
        }
    }


    std::optional<PathClass> ExplorerWindow::ms_topDirectory;   // 最上位ディレクトリ
    PathClass ExplorerWindow::ms_currentDirectory;              // 現在表示Directory
}
