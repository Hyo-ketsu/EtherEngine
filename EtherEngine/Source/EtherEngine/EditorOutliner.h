#ifndef I_EDITOROUTLINER_H
#define I_EDITOROUTLINER_H
#include <Base/Handle.h>
#include <DirectX/DirectX.h>
#include <EtherEngine/EditorObject.h>
#include <EtherEngine/EditorComponentBase.h>


//----- EditorOutliner �錾
namespace EtherEngine {
    class EditorOutliner : public EditorComponentBase {
    public:
        // �R���X�g���N�^
        // @ Arg1 : �Q�[���I�u�W�F�N�g�̃|�C���^
        // @ Arg2 : DirectX
        EditorOutliner(EditorObject* editorObject, const BaseHandle<DirectXRender>& directX);


        // �X�V����
        void Update(void) override;
        // �`�揈��
        void Draw(void) override;
    };
}


#endif // !I_EDITOROUTLINER_H
