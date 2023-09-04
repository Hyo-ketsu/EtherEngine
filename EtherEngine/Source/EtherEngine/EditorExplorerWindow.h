#ifndef I_EDITOREXPLORERWINDOW_H
#define I_EDITOREXPLORERWINDOW_H
#include <EtherEngine/EditorComponentBase.h>
#include <EtherEngine/EditorWindowBase.h>
#include <EtherEngine/ImGuiUtility.h>


//----- ExplorerWindow 宣言
namespace EtherEngine {
    // ファイルを表示する
    class ExplorerWindow : public EditorWindowBase {
    public:
        using EditorWindowBase::EditorWindowBase;


        void Start(void) override;
        void Update(void) override;
        void DrawWindow(void) override;

        // 最上位ディレクトリセッター
        static void SetTopDirectory(const PathClass& in) { ms_rootDirectory = in; }

    private:
        static std::optional<PathClass> ms_rootDirectory;    // 最上位ディレクトリ
        static PathClass                ms_currentDirectory; // 現在表示ディレクトリ
        static int ms_selectNumber; // 選択されているリスト番号
        static bool ms_isContentsSelect; // コンテンツウィンドウが選択されているか
        ImVec2 m_windowSize;  // 階層表示ウィンドウのサイズ
        ImGuiUtility::RenameableSelectable m_renameableSelectable;
    };
}


#endif // !I_EDITOREXPLORERWINDOW_H
