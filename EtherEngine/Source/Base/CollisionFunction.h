#ifndef I_COLLISIONFUNCTION_H
#define I_COLLISIONFUNCTION_H
#include <Base/ConceptUtility.h>
#include <Base/CollisionBase.h>
#include <Base/CollisionComponent.h>
#include <Base/CollisionHelper.h>
#include <Base/GameObject.h>
// @ MEMO : �d��������x�N�g�����ł���悤�v�����H


//----- �����蔻��p�\���̐錾
namespace EtherEngine {
    namespace CollisionFunction {
        // �Փ˔���p�֐��ɓn���p�̍\����
        template <Concept::BaseOfConcept<CollisionBase> CollisionData>
        struct CollisionCheckData {
            // �R���X�g���N�^
            // @ Arg1 : ���g�̃Q�[���I�u�W�F�N�g�ւ̃|�C���^
            // @ Arg2 : ���W
            // @ Arg3 : ���
            CollisionCheckData(GameObject* gameObject, const Transform& transform, const CollisionData& data) : m_gameObject(gameObject), m_transform(transform), m_data(data) {}


            GameObject* m_gameObject;   // ���g�̃Q�[���I�u�W�F�N�g
            Transform m_transform;      // ���W
            CollisionData m_data;       // ���
        };
    }
}


// �����蔻����s���֐�
namespace EtherEngine {
    // �����蔻����s���֐�
    // @ Arg1 : ������s�������蔻��R���|�[�l���g
    void AllCollisionCheck(std::vector<std::weak_ptr<CollisionComponent>> collisions);


    // �����蔻����Ƃ�
    // @ Ret  : �Փˏ��
    // @ Arg1 : ���g�̓����蔻��
    // @ Arg2 : �Ώۂ̓����蔻��
    std::optional<CollisionHitData> CollisionCheck(std::shared_ptr<CollisionComponent> thisCollision, std::shared_ptr<CollisionComponent> subjectCollision);
}


#endif // !I_COLLISIONFUNCTION_H
