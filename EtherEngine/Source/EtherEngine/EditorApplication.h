#ifndef I_EDITORAPPLICATION_H
#define I_EDITORAPPLICATION_H
#include <EngineLibrary/ManageSingleton.h>
#include <EtherEngine/ImGuiClass.h>
#include <Base/Handle.h>
#include <DirectX/DirectX.h>


#pragma managed
//----- EditorApplication �錾
namespace EtherEngine {
    // �G�f�B�^�[(�Q�[���G���W��)��\������N���X(Singleton)
    public ref class EditorApplication : public GameApplication {     
        ETHER_ENGINE_MANAGE_SINGLETON(EditorApplication);
    private:
        // �V�[���r���[���Ǘ����郁�\�b�h(�C�x���g�w�Ǘp)
        void SceneViewFunction(System::Object^ s, System::EventArgs^ e);


        // DirectX���擾����
        // @ Arg1 : �擾����DirectXRender
        Handle<DirectXRender>& GetDirectX(void);


        IMGUI* m_imGui;     // �ێ����Ă���IMGUI
        System::Collections::Generic::List<EditorUI::EditorExclusionObject<EditorUI::SceneViewVM^>^>^ m_sceneView;    // �ێ����Ă���SceneView  // �ێ����Ă���SceneView�̃��b�Z�[�W
    };
}


#endif // !I_EDITORAPPLICATION_H
