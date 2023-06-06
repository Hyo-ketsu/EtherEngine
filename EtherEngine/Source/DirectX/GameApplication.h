#ifndef I_GAMEAPPLICATION_H
#define I_GAMEAPPLICATION_H
#include <DirectX/DirectX.h>
#include <DirectX/BaseMainWindow.h>


namespace EtherEngine {
    // �Q�[���A�v���P�[�V������\������N���X
    class GameApplication : public BaseMainWindow<GameApplication> {
    public:
        // �R���X�g���N�^
        GameApplication(void);
        // �f�X�g���N�^
        ~GameApplication(void);


        // ���C���֐�
        void MainFunction(void) override;
    };
}


#endif // !I_GAMEAPPLICATION_H
