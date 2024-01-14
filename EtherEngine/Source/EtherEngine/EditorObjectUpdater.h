#ifndef I_EDITOROBJECTUPDATER_H
#define I_EDITOROBJECTUPDATER_H
#include <Base/Singleton.h>
#include <EtherEngine/EditorObjectStorage.h>


//----- EditorUpdater宣言
namespace EtherEngine {
    class EditorUpdater : public Singleton<EditorUpdater> {
    public:
        // エディターオブジェクトに更新処理を行う
        void Update(void);
        // エディターオブジェクトの描画処理を行う
        void Draw(void);
        // エディターオブジェクトの描画後処理を行う
        void LateDraw(void);

    private:
        // コンストラクタ
        EditorUpdater(void) {}

        friend class CentrallySingleton;

        std::vector<Handle<EditorObject>> m_windows; // 現在表示しているウィンドウ一覧
    };
}


#endif // !I_EDITOROBJECTUPDATER_H
