#ifndef I_SCENEG_H
#define I_SCENEG_H

// @ MEMO : ���󂱂̌`�Ŏ������Ă��܂��B�v���C


//----- Scene �錾
namespace EtherEngine {
    // �V�[����\������N���X
    class Scene {
        // �R���X�g���N�^
        Scene(void);


        // �������֐�
        virtual void Start(void) = 0;
    };
}


#endif // !I_SCENEG_H
