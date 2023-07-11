#ifndef I_COLLISIONCOMPONENT_H
#define I_COLLISIONCOMPONENT_H
#include <Base/ComponentBase.h>
#include <Base/CollisionBase.h>
#include <Base/ConceptUtility.h>


//----- CollisionComponent �錾
namespace EtherEngine {
    // �����蔻��̃R���|�[�l���g
    class CollisionComponent : public ComponentBase {
    public:
        // �R���X�g���N�^
        // @ Temp : �R���W�����̃^�C�v
        // @ Arg1 : �Q�[���I�u�W�F�N�g�̃|�C���^
        // @ Arg2 : �R���W����
        template <Concept::SameSubClass<CollisionBase> Type>
        CollisionComponent(void* gameObject, Type&& collision);

    
        // �R���W�����Q�b�^�[
        template <Concept::SameSubClass<CollisionBase> Type>
        std::weak_ptr<Type> GetCollision(void) { return std::weak_ptr<Type>(m_collision); }

        // �R���W�����`��Q�b�^�[
        CollisionShape GetCollisionShape(void) const { return m_collision->GetShape(); }
        // �R���W�������
        CollisionType GetCollisionType(void) const { return m_collision->GetType(); }

    private:
        std::shared_ptr<CollisionBase> m_collision; // �R���W����
    };
}


//----- CollisionComponent ��`
namespace EtherEngine {
    // �R���X�g���N�^
    template <Concept::SameSubClass<CollisionBase> Type>
    CollisionComponent::CollisionComponent(void* gameObject, Type&& collision) 
        : ComponentBase(gameObject) 
        , m_collision(std::make_shared<CollisionBase>(collision)) {
    }
}
#endif // !I_COLLISIONCOMPONENT_H
