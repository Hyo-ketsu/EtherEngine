#ifndef I_CAMERASTORAGE_H
#define I_CAMERASTORAGE_H
#include <Base/Singleton.h>
#include <Base/CameraBase.h>
#include <Base/IDClass.h>


//----- CameraStorage�錾
namespace EtherEngine {
    // �J������ێ����Ă����N���X
    class CameraStorage : public Singleton<CameraStorage> {
    public:
        // �f�X�g���N�^
        ~CameraStorage(void) {}


        // �J������ǉ�����
        // @ Arg1 : �ǉ�����J����
        // @ Arg2 : ID
        void AddCamera(CameraBase& camera, const IDClass& id);
        // �J�������폜����
        // @ Arg1 : ID
        void DeleteCamera(const IDClass& id);


        // �w�肵��ID�̃J���������݂��邩
        // @ Arg1 : �w��ID
        bool IsIDToCamera(const IDClass& id);


        // �J�������擾����
        // @ MEMO : �|�C���^��Ԃ��̂����Ȃ�ŉ��C�\��
        // @ Ret  : �J�����ւ̃|�C���^(�Ȃ����nullptr)
        // @ Arg1 : �D��x�̏���(Default : 0)
        [[deprecated]]
        CameraBase* const GetCamera(const uint priority = 0);
        // �J�������擾����
        // @ Arg1 : �w��ID
        CameraBase* const GetCamera(const IDClass& id);


    private:
        // �R���X�g���N�^
        CameraStorage(void) {}

        friend class Singleton<CameraStorage>;

        std::vector<std::tuple<IDClass, CameraBase*, bool>> m_cameras;   // �ێ����Ă���J����
    };
}


#endif // !I_CAMERASTORAGE_H
