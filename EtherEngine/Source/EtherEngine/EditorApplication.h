#ifndef I_EDITORAPPLICATION_H
#define I_EDITORAPPLICATION_H
#include <Base/ProjectData.h>
#include <Base/InitUninitPerformer.h>
#include <DirectX/DirectX.h>
#include <EngineLibrary/ManageSingleton.h>
#include <EtherEngine/ImGuiClass.h>
#include <EtherEngine/ProjectEditorData.h>


#pragma managed
//----- EditorApplication �錾
namespace EtherEngine {
    // �G�f�B�^�[(�Q�[���G���W��)��\������N���X(Singleton)
    public ref class EditorApplication {
        ETHER_ENGINE_MANAGE_SINGLETON(EditorApplication);
    public:

        // �f�X�g���N�^
        ~EditorApplication(void);
        // �t�@�C�i���C�U
        !EditorApplication(void);


        // DirectX�Q�b�^�[
        const Handle<DirectXRender>& GetDirectX(void) { return *m_dxRender; }


        // �Q�[�����[�v�v���p�e�B
        property bool IsGameLoop {
            bool get(void) { return m_isMainLoop; }
            void set(bool value) { m_isMainLoop = value; }
        }


        // ���C���֐�
        void MainFunction(void);
        // �Q�[�����[�h���J�n����
        // @ Memo : ���ɊJ�n���Ă���ۂ̓Q�[�����[�h�̍ċN�����s���܂�
        void StartGameMode(void);
        // �Q�[�����[�h���ꎞ���f����
        // @ Memo : �J�n���Ă��Ȃ��ꍇ�͓��ɉ����N����܂���
        void StopGameMode(void);
        // �Q�[�����[�h���I������
        // @ Memo : �J�n���Ă��Ȃ��ꍇ�͓��ɉ����N����܂���
        void EndGameMode(void);

    private:
        bool m_isMainLoop;  // ���C�����[�v���s����
        bool m_isGameMode;  // �Q�[�����N�����Ă��邩
        IMGUI* m_imGui;     // �ێ����Ă���IMGUI
        ProjectData* m_projectData; // ���ݕێ����Ă���v���W�F�N�g�f�[�^
        EditorData* m_editorData;   // ���ݕێ����Ă���G�f�B�^�[�f�[�^
        Handle<DirectXRender>* m_dxRender;  // �ێ����Ă���DirectX
        System::Collections::Generic::List<EditorUI::SceneViewVM^>^ m_sceneView;    // �ێ����Ă���SceneView
    };
}


#endif // !I_EDITORAPPLICATION_H
