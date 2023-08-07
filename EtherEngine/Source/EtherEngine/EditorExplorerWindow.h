#ifndef I_EDITOREXPLORERWINDOW_H
#define I_EDITOREXPLORERWINDOW_H
#include <EtherEngine/EditorComponentBase.h>
#include <EtherEngine/EditorWindowBase.h>


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
        static void SetTopDirectory(const PathClass& in) { ms_topDirectory = in; }

    private:
        static std::optional<PathClass> ms_topDirectory;     // 最上位ディレクトリ
        static PathClass ms_currentDirectory; // 現在表示Directory
        ImVec2 m_hierarchyView;  // 階層表示ウィンドウのサイズ
    };
}


#endif // !I_EDITOREXPLORERWINDOW_H
