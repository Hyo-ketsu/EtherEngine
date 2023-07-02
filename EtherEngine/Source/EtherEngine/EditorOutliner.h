#ifndef I_EDITOROUTLINER_H
#define I_EDITOROUTLINER_H
#include <Base/Handle.h>
#include <DirectX/DirectX.h>
#include <EtherEngine/EditorObject.h>
#include <EtherEngine/EditorWindowBase.h>


//----- EditorOutliner éŒ¾
namespace EtherEngine {
    class EditorOutliner : public EditorWindowBase {
    public:
        using EditorWindowBase::EditorWindowBase;


        // ‰Šú‰»ˆ—
        void Start(void) override;
        // XVˆ—
        void Update(void) override;
        // •`‰æˆ—
        void DrawWindow(void) override;
    };
}


#endif // !I_EDITOROUTLINER_H
