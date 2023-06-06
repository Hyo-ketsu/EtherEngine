#ifndef I_EDITORAPPLICATION_H
#define I_EDITORAPPLICATION_H
#include <DirectX/BaseMainWindow.h>
#include <EtherEngine/ImGuiClass.h>


namespace EtherEngine {
    // �G�f�B�^�[(�Q�[���G���W��)��\������N���X(Singleton)
    class EditorApplication : public BaseMainWindow<EditorApplication> {
    public:
        // �R���X�g���N�^
        EditorApplication(void);
        // �f�X�g���N�^
        ~EditorApplication(void);


        // ���C���֐�
        void MainFunction(void) override;

    private:
        std::unique_ptr<IMGUI> m_imGui; // �ێ����Ă���IMGUI
    };
}


#endif // !I_EDITORAPPLICATION_H
