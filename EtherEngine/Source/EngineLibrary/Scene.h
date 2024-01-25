#ifndef I_SCENE_H
#define I_SCENE_H
#include <EngineLibrary/EngineLibraryDefine.h>
#include <EngineLibrary/BaseObject.h>

//----- Scene �錾
namespace EtherEngine {
    // �V�[��
    public ref class Scene : BaseObject {
    public:
        // �R���X�g���N�^
        Scene(void);


        // �V�[���ԍ����擾����
        // @ Ret  : �擾�����V�[���ԍ�
        SceneIDType GetSceneID(void);


        // �V�[���̏����擾����
        // @ Arg1 : �V�[���̒��g�̏���Json
        virtual System::String^ GetScene(void) = 0;
    };
}


#endif // !I_SCENE_H
