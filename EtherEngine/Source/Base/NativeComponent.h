#ifndef I_COMPONENTBASE_H
#define I_COMPONENTBASE_H
#include <Base/CollisionBase.h>
#include <Base/EtherEngineUtility.h>
class NativeGameObject;
#include <Base/NativeBaseObject.h>
#include <Base/Handle.h>


//----- ComponentBase �錾
namespace EtherEngine {
    // �R���|�[�l���g�̊�b�ƂȂ�N���X
    class NativeComponent : public NativeBaseObject {
    public:
        // �R���X�g���N�^
        // @ Arg1 : �Q�[���I�u�W�F�N�g
        NativeComponent(NativeGameObject* gameObject);
        // �f�X�g���N�^
        virtual ~NativeComponent(void) {}
        // �R�s�[�R���X�g���N�^
        NativeComponent(const NativeComponent& copy) = delete;
        // ���[�u�R���X�g���N�^
        NativeComponent(NativeComponent&& move) = default;
        // �R�s�[���
        NativeComponent& operator =(const NativeComponent& copy) = delete;
        // ���[�u���
        NativeComponent& operator =(NativeComponent&& move) = default;


        // �e�I�u�W�F�N�g�Q�b�^�[
        NativeGameObject* GetParentObject(void) const { return m_gameObject; }

        // �Փ˃R���W�����f�[�^�Q�b�^�[
        const std::vector<CollisionHitData>& GetCollisionHitData(void) const { return m_hitData; }
        // �Փ˃R���W�����f�[�^�Z�b�^�[
        void SetCollisionHitData(const std::vector<CollisionHitData>& in) { m_hitData = in; }
        // �Փ˃R���W�����f�[�^�A�N�Z�T�[
        std::vector<CollisionHitData>& AccessCollisionHitData(void) { return m_hitData; }

    private:
        NativeGameObject* m_gameObject;             // �����Q�[���I�u�W�F�N�g
        std::vector<CollisionHitData> m_hitData;    // �Փ˃R���W�����f�[�^
    };
}


#endif // !I_COMPONENTBASE_H
