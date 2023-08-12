#include <EtherEngine/EditorExplorerWindow.h>
#include <Base/WindowsDefine.h>
#include <EtherEngine/FileOpener.h>


//----- 関数実装
namespace EtherEngine {
    // パスを全て表示する
    // @ Arg1 : フラグ
    // @ Arg2 : パス
    // @ Arg3 : 選択された場合に設定するカレントディレクトリ
    // @ Arg4 : ルートディレクトリか
    void ShowPath(const ImGuiTreeNodeFlags& flag, const PathClass& path, PathClass* current, const bool isRoot) {
        //----- 拡張子がある（ディレクトリではない）ファイルは表示は行わない
        if (path.HasExtension()) return;

        //----- 表示ラムダ定義
        auto showPath = [&](const PathClass& showPath) -> bool {
            //----- 通常ファイル(=拡張子が存在する)の表示はしない
            if (showPath.HasExtension()) return false;

            //----- 現在のパスを取得
            // @ Memo : "Hoge/Fuga" であれば "Hoge/Fuga"
            std::string thisPath = showPath.GetFile();

            //----- 表示
            bool ret = ImGui::TreeNodeEx(thisPath.c_str(), flag);

            //----- 選択されたディレクトリをカレントディレクトリとして設定する
            if (ImGui::IsItemClicked()) {
                *current = showPath;
            }

            //----- D&D表示
            if (ImGui::BeginDragDropSource()) {
                ImGui::SetDragDropPayload("ExplorerHierarchyD&D", NULL, 0);
                ImGui::EndDragDropSource();
            }

            //----- 返却
            return ret;
        };

        //----- 自身がルートディレクトリであれば表示する
        if (isRoot) {
            if (showPath(path) == false) return;
        }

        //----- ノード表示
        for (auto&& it : path.GetLowerDirectory()) {
            //----- 開かれているノードの表示(再帰)
            if (showPath(it)) {
                ShowPath(flag, it, current, false);
            }
        }
        ImGui::TreePop();
    }
}


//----- ExplorerWindow 定義
namespace EtherEngine {
    void ExplorerWindow::Start(void) {
        //----- 初期ディレクトリ設定
        // @ MEMO : 仮でカレントディレクトリ
        if (ms_rootDirectory.has_value() == false) {
            ms_rootDirectory = PathClass::GetCurDirectory();
            ms_currentDirectory = ms_rootDirectory.value();
        }
    }
    void ExplorerWindow::Update(void) {
    }


    void ExplorerWindow::DrawWindow(void) {
        if (ms_rootDirectory.has_value() == false) return;

        //----- ウィンドウフラグの設定
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_HorizontalScrollbar;

        //----- 階層ウィンドウサイズ設定
        m_hierarchyView.x = ImGui::GetWindowSize().x / 2;
        m_hierarchyView.y = 65535;

        //----- 階層ウィンドウ表示
        auto oldPath = ms_currentDirectory; // 現在のパスが変わったら
        ImGui::Begin(ImGuiDefine::Name::WINDOW_EXPLORER_HIERARCHY.c_str());
        {
            //----- 変数宣言
            ImGuiTreeNodeFlags flags = 
                ImGuiTreeNodeFlags_Selected;
                ImGuiTreeNodeFlags_OpenOnArrow;
                ImGuiTreeNodeFlags_OpenOnDoubleClick;

            //----- 順次表示
            ShowPath(flags, ms_rootDirectory.value(), &ms_currentDirectory, true);
        }
        ImGui::End();
        //----- 現階層が更新されていたらコンテンツ選択番号をリセットする
        if (oldPath.Get() != ms_currentDirectory.Get()) {
            ms_selectNumber = -1;
        }

        //----- コンテンツ(ディレクトリ内)表示
        ImGui::Begin(ImGuiDefine::Name::WINDOW_EXPLORER_CONTENTS.c_str());
        {
            //----- 内容物の表示
            // @ MEMO : 仮で一列
            if (ImGui::BeginListBox("ContentsList")) {
                int i = 0;
                for (auto&& it : ms_currentDirectory.GetLowerDirectory()) {
                    //----- ディレクトリは表示しない
                    if (it.IsDirectory()) continue;

                    //----- リスト要素表示
                    if (i == ms_selectNumber) {
                        //----- その番号のものが選択済み。使用
                        if (ImGui::Selectable(it.GetFile().c_str(), true)) {
                            ImGui::SetItemDefaultFocus();
                            FileOpen(it);
                        }
                    }
                    else {
                        //----- 選択されていない。通常表示・選択
                        if (ImGui::Selectable(it.GetFile().c_str(), false)) {
                            ms_selectNumber = i;
                            ImGui::SetItemDefaultFocus();
                        }
                    }

                    i++;
                }

                ImGui::EndListBox();
            }
        }
        ImGui::End();
    }


    std::optional<PathClass> ExplorerWindow::ms_rootDirectory;  // 最上位ディレクトリ
    PathClass ExplorerWindow::ms_currentDirectory;              // 現在表示ディレクトリ
    int ExplorerWindow::ms_selectNumber = -1; // 選択されているリスト番号
}
