#ifndef I_COLLISIONFUNCTION_H
#define I_COLLISIONFUNCTION_H
#include <Base/CollisionComponent.h>
#include <Base/CollisionHelper.h>
// @ MEMO : �d��������x�N�g�����ł���悤�v�����H


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
