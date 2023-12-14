#ifndef I_CAMERASTORAGE_H
#define I_CAMERASTORAGE_H
#include <Base/Singleton.h>
#include <Base/CameraBase.h>
#include <Base/IDClass.h>


//----- CameraSystem �錾
namespace EtherEngine {
    // �J�������Ǘ�����N���X
    class CameraSystem : public Singleton<CameraSystem> {
    public:
        // �f�X�g���N�^
        ~CameraSystem(void) {}


        // �J������ǉ�����
        // @ Ret  : ID
        // @ Arg1 : �ǉ�����J����
        // @ Arg2 : �D�揇�� (Default : 0)
        [[nodiscard]] IDClass AddData(std::weak_ptr<CameraData> data, int priority = 0);
        // �J�������폜����
        // @ Arg1 : ID
        void DeleteData(const IDClass& id);


        // �J�������擾����
        // @ Ret  : �擾�����J�������
        // @ Arg1 : �w��ID
        std::optional<CameraData> GetData(const IDClass& id);
        // ���C���J�������擾����
        // @ Ret  : �擾�����J�������
        std::optional<CameraData> GetMainData(void);

    private:
        // �R���X�g���N�^
        CameraSystem(void) {}

        friend class Singleton<CameraSystem>;

        std::vector<std::tuple<IDClass, std::weak_ptr<CameraData>, int>> m_datas;   // �ێ����Ă���f�[�^
    };
}


#endif // !I_CAMERASTORAGE_H
