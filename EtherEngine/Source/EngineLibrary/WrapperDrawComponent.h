#ifndef I_GAMEDRAWCOMPONENT_H
#define I_GAMEDRAWCOMPONENT_H
#include <Base/NativeDrawComponent.h>
#include <EngineLibrary/WrapperDrawComponent.h>


//----- �`��R���|�[�l���g
namespace EtherEngine {
    // �`��R���|�[�l���g
    public ref class WrapperDrawComponent : public Component {
    public:
        // �R���X�g���N�^
        // @ Memo : �R���|�[�l���g�������ł��Ȃ���Η�O�𑗏o���܂�
        // @ Arg1 : �e�Q�[���I�u�W�F�N�g
        // @ Arg2 : �����R���|�[�l���g��
        WrapperDrawComponent(NativeGameObject* gameObject, const std::string& componentName);


        // �`��O�X�V����
        void Update(void) override;
        // �`���X�V����
        void LateUpdate(void) override;


        // �`��
        void Draw(void) override;
    };
}


#endif // !I_GAMEDRAWCOMPONENT_H
