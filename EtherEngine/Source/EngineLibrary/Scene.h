#ifndef I_SCENE_H
#define I_SCENE_H
#include <EngineLibrary/EngineLibraryDefine.h>
#include <EngineLibrary/BaseObject.h>

//----- Scene �錾
namespace EtherEngine {
    // �V�[��
    // @ MEMO : �ЂƂ܂��N���X�Ƃ����̂ɂ��Č���Json��ǂݍ��ނ����ɂ��܂�
    public ref class Scene : BaseObject {
    public:
        // �R���X�g���N�^
        // @ Arg1 : Json�ǂݍ��݃f�B���N�g��
        Scene(PathString json);

    private:
    };
}


#endif // !I_SCENE_H
