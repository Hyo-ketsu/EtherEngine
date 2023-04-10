#ifndef I_EDITORAPPLICATION_H
#define I_EDITORAPPLICATION_H

#include <Base/Singleton.h>
#include <DirectX/GameApplication.h>


namespace EtherEngine {
    // �G�f�B�^�[(�Q�[���G���W��)��\������N���X(Singleton)
    class EditorApplication : public GameApplication, public Singleton<EditorApplication> {
    public:
        using GameApplication::GameApplication;


    private:
        // �R���X�g���N�^
        EditorApplication(void) {}
        // �f�X�g���N�^
        ~EditorApplication(void) override {}


        friend Singleton<EditorApplication>;
    };
}


#endif // !I_EDITORAPPLICATION_H
