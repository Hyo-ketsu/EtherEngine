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

    private:
        // コンストラクタ
        EditorUpdater(void) {}

        friend class Singleton<EditorUpdater>;
    };
}


#endif // !I_EDITOROBJECTUPDATER_H
