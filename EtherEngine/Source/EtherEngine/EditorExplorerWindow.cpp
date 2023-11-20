#include <EtherEngine/EditorExplorerWindow.h>
#include <Base/WindowsDefine.h>
#include <Base/EtherEngineUtility.h>
#include <EtherEngine/FileOpener.h>
#include <EtherEngine/FileCreater.h>
#include <EtherEngine/FileDeleter.h>


//----- 関数実装
namespace EtherEngine {
    // パスを全て表示する
    // @ Arg1 : フラグ
    // @ Arg2 : パス
    // @ Arg3 : 選択された場合に設定するカレントディレクトリ
    // @ Arg4 : ルートディレクトリか
    // @ Arg5 : 選択フラグ
    void ShowPath(const ImGuiTreeNodeFlags& flag, const PathClass& path, PathClass* current, const bool isRoot, bool* isContentsFrag) {
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
                *isContentsFrag = false;
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
                ShowPath(flag, it, current, false, isContentsFrag);
            }
        }
        ImGui::TreePop();
    }
}


//----- ExplorerWindow 定義
namespace EtherEngine {
    void ExplorerWindow::StartWindow(void) {
        //----- 初期ディレクトリ設定
        // @ MEMO : 仮でカレントディレクトリ
        if (ms_rootDirectory.has_value() == false) {
            ms_rootDirectory = PathClass::GetCurDirectory();
            ms_currentDirectory = ms_rootDirectory.value();
        }
    }
    void ExplorerWindow::UpdateWindow(void) {
    }


    void ExplorerWindow::DrawWindow(void) {
        if (ms_rootDirectory.has_value() == false) return;

        //----- ウィンドウフラグの設定
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_HorizontalScrollbar;

        //----- ウィンドウサイズ設定
        m_windowSize.x = ImGui::GetWindowSize().x / 3;
        m_windowSize.y = 0;

        //----- 階層ウィンドウ表示
        auto oldPath = ms_currentDirectory; // 現在のパスが変わったら
        ImGui::BeginChild(ImGuiDefine::Name::WINDOW_EXPLORER_HIERARCHY.c_str(), m_windowSize, true, window_flags);
        {
            //----- 右クリックメニュー表示
            if (ImGui::IsWindowFocused() && ImGui::IsMouseReleased(1)) {
                ImGui::OpenPopup("Explorer Hierarchy Popup");
            }

            //----- 変数宣言
            ImGuiTreeNodeFlags flags =
                ImGuiTreeNodeFlags_Selected;
            ImGuiTreeNodeFlags_OpenOnArrow;
            ImGuiTreeNodeFlags_OpenOnDoubleClick;

            //----- 順次表示
            ShowPath(flags, ms_rootDirectory.value(), &ms_currentDirectory, true, &ms_isContentsSelect);

            ImGui::EndChild();
        }

        //----- 階層ウィンドウ右クリックメニュー表示
        if (ImGui::BeginPopupContextItem("Explorer Hierarchy Popup")) {
            //----- オブジェクト生成
            if (ImGui::MenuItem("Create")) {
                FileCreate("NewDirectory", "", ms_currentDirectory, Utility::DuplicationNameObjectName::ParenthesesNumber, "", true);
            }
            if (ImGui::MenuItem("Delete")) {
            }
            //----- メニュー表示終了
            ImGui::EndPopup();
        }

        //----- 現階層が更新されていたらコンテンツ選択番号をリセットする
        if (oldPath.Get() != ms_currentDirectory.Get()) {
            ms_selectNumber = -1;
        }

        //----- コンテンツ(ディレクトリ内)表示

        //----- ウィンドウサイズ設定
        m_windowSize.x = ImGui::GetWindowSize().x / 3 * 2;
        m_windowSize.y = 0;

        //----- 内容物の表示
        // @ MEMO : 仮で一列
        ImGui::SameLine();
        ImGui::BeginChild(ImGuiDefine::Name::WINDOW_EXPLORER_CONTENTS.c_str(), m_windowSize, true, window_flags);
        {
            //----- 右クリックメニュー表示
            if (ImGui::IsWindowFocused() && ImGui::IsMouseReleased(1)) {
                ImGui::OpenPopup("Explorer Contents Popup");
            }

            //----- 要素表示
            int i = 0;
            std::vector<std::pair<PathClass, std::string>> createFile;  // 作成ファイル一覧
            std::vector<PathClass> deleteFile;  // 削除ファイル一覧
            for (auto&& it : ms_currentDirectory.GetLowerDirectory()) {
                //----- ディレクトリは表示しない
                if (it.IsDirectory()) continue;

                //----- リスト要素表示
                ImGuiUtility::RenameableSelectableMessage mes;
                do {
                    if (i == ms_selectNumber) {
                        //----- その番号のものが選択済み。使用
                        mes = m_renameableSelectable.Show(it.GetFile(), i, true);

                        //----- 選択時
                        if (mes == decltype(mes)::SelectYes) {
                            ImGui::SetItemDefaultFocus();
                            FileOpen(it);
                            break;
                        }
                    }
                    else {
                        //----- 選択されていない。通常表示・選択
                        mes = m_renameableSelectable.Show(it.GetFile(), i, false);

                        //----- 選択時
                        if (mes == decltype(mes)::SelectYes) {
                            ms_selectNumber = i;
                            ms_isContentsSelect = true;
                            ImGui::SetItemDefaultFocus();
                            break;
                        }
                    }
                    //----- リネームが行われたか
                    if (mes == decltype(mes)::RenameDecision) {
                        createFile.push_back(std::make_pair<PathClass,std::string>(it.GetDirectory() / m_renameableSelectable.GetRename(), RoadFileAll(it)));
                        deleteFile.push_back(it);
                    }
                } while (false);

                i++;
            }

            //----- ファイル削除・ファイル作成
            for (auto&& it : deleteFile) {
                it.Delete_File(true);
            }
            for (auto&& it : createFile) {
                it.first.Create_File(it.second);
            }

            ImGui::EndChild();
        }


        //----- コンテンツウィンドウ右クリックメニュー表示
        if (ImGui::BeginPopupContextItem("Explorer Contents Popup")) {
            //----- オブジェクト生成
            if (ImGui::BeginMenu("Create")) {
                //----- 各ファイル生成
                if (ImGui::MenuItem("Scene")) {
                    FileCreate("NewScene", FileDefine::Extended::SCENE, ms_currentDirectory, Utility::DuplicationNameObjectName::ParenthesesNumber);
                }
                if (ImGui::MenuItem("Script")) {
                    FileCreate("Script", FileDefine::Extended::SCRIPT, ms_currentDirectory, Utility::DuplicationNameObjectName::ParenthesesNumber, FileDefine::SCRIPT_FILE_STRING);
                }

                ImGui::EndMenu();
            }
            //----- オブジェクト削除
            if (ImGui::MenuItem("Delete")) {
                //----- 選択番号のファイル削除
                if (ms_currentDirectory.GetLowerDirectory().size() > ms_selectNumber) {
                    FileDelete(ms_currentDirectory.GetLowerDirectory()[ms_selectNumber], true);
                }
            }

            //----- メニュー表示終了
            ImGui::EndPopup();
        }
    }


    std::optional<PathClass> ExplorerWindow::ms_rootDirectory;  // 最上位ディレクトリ
    PathClass ExplorerWindow::ms_currentDirectory;              // 現在表示ディレクトリ
    int ExplorerWindow::ms_selectNumber = -1; // 選択されているリスト番号
    bool ExplorerWindow::ms_isContentsSelect = true; // コンテンツウィンドウが選択されているか
}
