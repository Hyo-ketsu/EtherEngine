#ifndef I_EDITOROUTLINER_H
#define I_EDITOROUTLINER_H
#include <Base/Handle.h>
#include <DirectX/DirectX.h>
#include <EtherEngine/EditorObject.h>
#include <EtherEngine/EditorWindowBase.h>


//----- EditorOutliner �錾
namespace EtherEngine {
    class EditorOutliner : public EditorWindowBase {
    public:
        using EditorWindowBase::EditorWindowBase;


        // ����������
        void Start(void) override;
        // �X�V����
        void Update(void) override;
        // �`�揈��
        void DrawWindow(void) override;
    };
}


#endif // !I_EDITOROUTLINER_H
