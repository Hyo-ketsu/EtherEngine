#ifndef I_GAMEAPPLICATION_H
#define I_GAMEAPPLICATION_H
#include <DirectX/DirectX.h>
#include <EngineLibrary/BaseMainWindow.h>


namespace EtherEngine {
    // �Q�[���A�v���P�[�V������\������N���X
    class ENGINELIBRARY_API GameApplication : public BaseMainWindow, public Singleton<GameApplication> {
    public:
        // �f�X�g���N�^
        ~GameApplication(void);

    protected:
        // ���C���֐�
        void MainFunction(void) override;

    private:
        // �R���X�g���N�^
        GameApplication(void);

        friend class Singleton<GameApplication>;
    };
}


#endif // !I_GAMEAPPLICATION_H
