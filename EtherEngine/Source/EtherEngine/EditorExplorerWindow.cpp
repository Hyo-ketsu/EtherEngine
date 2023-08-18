#include <EtherEngine/EditorExplorerWindow.h>
#include <Base/WindowsDefine.h>
#include <Base/EtherEngineUtility.h>
#include <EtherEngine/FileOpener.h>


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


    // ファイル名走査関数
    // @ Ret  : 判定結果のファイル名
    // @ Arg1 : 判定対象
    // @ Arg2 : 命名法則
    PathClass GetFileName(const PathClass& path, const Utilty::DuplicationNameObjectName& nameRule) {
        //----- 変数宣言
        int countNumber = 1; 
        std::vector<PathClass> directoryFile;
        auto createPath = PathClass(path.GetFile());

        //----- 同じ拡張子のファイル取得
        for (auto&& it : path.GetDirectory().GetLowerDirectory()) {
            if (it.GetExtension() == path.GetExtension()) {
                directoryFile.push_back(it.GetFile());
            }
        }

        //----- 同じ名前のファイル走査
        while (true) {
            //----- 変数宣言
            bool isEnable = false; // 同じファイル名が存在するか

            //----- 走査
            for (auto&& it : directoryFile) {
                if (createPath.Get() == it.Get()) {
                    //----- 同名が存在する。
                    isEnable = true;
                    break;
                }
            }

            //----- 同名が存在したか
            if (isEnable) {
                //----- 存在した。名前を生成し再判定
                auto extension = path.GetExtension();
                createPath = path.GetFileName();
                Utilty::DuplicationName(&createPath.Access(), countNumber, nameRule);
                createPath = createPath += extension;
                countNumber++;
            }
            else {
                //----- 存在しない。返却
                return path.GetDirectory() /= createPath;
            }
        }
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
            if (ImGui::MenuItem("Create")) {}
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
                        ms_isContentsSelect = true;
                        ImGui::SetItemDefaultFocus();
                    }
                }

                i++;
            }

            ImGui::EndChild();
        }


        //----- コンテンツウィンドウ右クリックメニュー表示
        if (ImGui::BeginPopupContextItem("Explorer Contents Popup")) {
            //----- オブジェクト生成
            if (ImGui::BeginMenu("Create")) {
                //----- 変数宣言
                PathClass createFile = ms_currentDirectory;
                std::string createFileName;     //
                std::string fileString = "";    // 新規生成ファイルに与える文字列

                //----- 各ファイル生成
                if (ImGui::MenuItem("Scene")) {
                    createFileName = "NewScene" + FileDefine::SCENE;
                }
                if (ImGui::MenuItem("Script")) {
                    createFileName = "NewScript" + FileDefine::CPPCLISCRIPT;
                    fileString = FileDefine::CPPCLISCRIPT_FILE_STRING;
                }

                //----- ファイル生成
                if (createFileName.empty() == false) {
                    createFile = GetFileName(createFile /= createFileName, Utilty::DuplicationNameObjectName::ParenthesesNumber);    // @ MEMO : 命名規則は仮置き
                    createFile.CreateFiles(fileString);
                }

                ImGui::EndMenu();
            }
            //----- オブジェクト削除
            if (ImGui::MenuItem("Delete")) {
                //----- 選択番号のファイル削除
                if (ms_currentDirectory.GetLowerDirectory().size() > ms_selectNumber) {
                    ms_currentDirectory.GetLowerDirectory()[ms_selectNumber + 1].DeleteFiles(true);
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
