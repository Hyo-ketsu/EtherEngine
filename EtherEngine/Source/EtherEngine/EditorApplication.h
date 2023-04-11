#ifndef I_EDITORAPPLICATION_H
#define I_EDITORAPPLICATION_H

#include <Base/Singleton.h>
#include <DirectX/GameApplication.h>
#include <EtherEngine/ImGuiClass.h>


namespace EtherEngine {
    // �G�f�B�^�[(�Q�[���G���W��)��\������N���X(Singleton)
    class EditorApplication : public GameApplication, public Singleton<EditorApplication> {
    public:
        // �f�X�g���N�^
        ~EditorApplication(void) override {}


    private:
        // �R���X�g���N�^
        using GameApplication::GameApplication;


        // �ǉ�������(��)
        void InitLast(void) override;

        std::unique_ptr<IMGUI> m_imGui; // �ێ����Ă���IMGUI


        friend Singleton<EditorApplication>;
    };
}


#endif // !I_EDITORAPPLICATION_H
