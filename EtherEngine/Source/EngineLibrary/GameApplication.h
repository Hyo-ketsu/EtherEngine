#ifndef I_GAMEAPPLICATION_H
#define I_GAMEAPPLICATION_H
#include <DirectX/DirectX.h>
#include <EngineLibrary/BaseMainWindow.h>

#pragma unmanaged

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
#pragma managed
//----- Wrapper
namespace EtherEngine {
    namespace Wrapper {
        //----- �G�f�B�^�[�̃A�v���P�[�V����
        public ref class GameApplication {
        public:
            // �G�f�B�^�[���I��������
            static property bool IsGameLoop {
                void set(bool value) {
                    EtherEngine::GameApplication::Get()->SetIsGameLoop(value);
                }
            }
        };
    }
}


#endif // !I_GAMEAPPLICATION_H
