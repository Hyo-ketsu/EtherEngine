#ifndef I_GAMEOBJECT_H
#define I_GAMEOBJECT_H
#include <Base/Transform.h>
#include <Base/Handle.h>
#include <Base/Scene.h>


namespace EtherEngine {
    // �V�[����̃Q�[�����\������I�u�W�F�N�g��\������
    class GameObejct {
    public:
        
    public:
        // �R���X�g���N�^
        // @ Arg1 : ���W
        // @ Arg2 : ����Scene
        GameObejct(const Transform& transform, const Handle<Scene> scene);


    private:
        Transform m_transform;  // ���W
    };
}
// �V�[�����
#endif
