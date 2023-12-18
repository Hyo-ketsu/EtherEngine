#include <EtherEngine/EditorApplication.h>
#include <Base/Timer.h>
#include <Base/WindowsDefine.h>
#include <Base/BaseInput.h>
#include <Base/BaseDefines.h>
#include <Base/GameObjectUpdater.h>
#include <EtherEngine/EditorObjectUpdater.h>
#include <EtherEngine/CommandPrompt.h>
#include <EtherEngine/ProjectMediation.h>
#include <EtherEngine/EditorAssemblyRefresh.h>
#include <EtherEngine/EditorCamera.h>
#include <DirectX/ModelComponent.h>
#include <DirectX/ShaderClass.h>
#include <Base/CollisionSphere.h>
#include <Base/GameObjectStorage.h>
#include <Base/CameraComponent.h>
#include <EtherEngine/Test/TestDefine.h>
#include <EtherEngine/Test/TestComponent.h>
#include <EtherEngine/Test/EditorDebugWindow.h>
#include <EtherEngine/EditorDefine.h>
#include <Base/ThreadingUtility.h>
#include <Base/CameraStorage.h>
#include <EtherEngine/EditorUtility.h>


#pragma managed
//----- EditorApplication ��`
namespace EtherEngine {
    // �R���X�g���N�^
    EditorApplication::EditorApplication(void) 
        : m_isMainLoop(true)
        , m_isGameMode(false)
        , m_imGui(nullptr)
        , m_projectData(nullptr)
        , m_editorData(nullptr) 
        , m_dxRender(new Handle<DirectXRender>(DirectXRender())) 
        , m_sceneView(gcnew System::Collections::Generic::List<EditorUI::EditorExclusionObject<EditorUI::SceneViewVM^>^>(0)) {
    }
    // �f�X�g���N�^
    EditorApplication::~EditorApplication(void) {
        this->!EditorApplication();
    }
    // �t�@�C�i���C�U
    EditorApplication::!EditorApplication(void) {
        DELETE_NULL(m_imGui);
        DELETE_NULL(m_projectData);
        DELETE_NULL(m_dxRender);
        m_sceneView = nullptr;
    }


    // ���C���֐�
    void EditorApplication::MainFunction(void) {
#ifdef _DEBUG
        //----- �e�X�g�E�B���h�E
        //auto testWindow = EditorObjectStorage::Get()->CreateEditorObject();
        //testWindow.GetAtomicData().AddComponent<EditorDebugWindow>();

        ////----- �e�X�g�R���|�[�l���g
        //auto testGameObject = GameObjectStorage::Get()->CreateGameObject();
        ////testGameObject.GetAtomicData().AddComponent("TestComponent");

        ////----- �G�f�B�^�[�p�J�����쐬
        auto cameraGameObejct = EditorObjectStorage::Get()->CreateEditorObject();
        cameraGameObejct.GetAtomicData().AccessTransform().AccessPostion().z() = -5;
        auto camera = cameraGameObejct.GetAtomicData().AddComponent<EditorCamera>();

        ////----- �e�X�g�p�V�F�[�_�[�ǉ�
        //auto vs = VertexShader(this->GetDirectX());
        //vs.LoadFile((TestDefine::TEST_ASSET_SHADER_PASS + "VS_Test.cso").c_str());
        //auto ps = PixelShader(this->GetDirectX());
        //ps.LoadFile((TestDefine::TEST_ASSET_SHADER_PASS + "PS_Test.cso").c_str());

        ////----- �J�����ݒ�
        //m_dxRender.GetAtomicData().SetCameraID(camera.lock()->GetID().GetId());
#endif // _DEBUG
        //m_imGui = new IMGUI(*m_dxRender->GetAtomicData().GetEditableDevice(), *m_dxRender->GetAtomicData().GetEditableContext(),);

        ////----- �v���W�F�N�g�ݒ�̓ǂݍ���
        //try {
        //    m_projectData = new ProjectData(PathClass::GetCurDirectory() / EditorFileDefine::Directory::EDITOR_SETTING / EditorFileDefine::PROJECT_DATA);
        //}
        //catch (const EditorException& e) {
        //    using namespace EditorUI;

        //    //----- �Ȃ��B�X�^�[�g�A�b�v�E�B���h�E�N��
        //    auto VM = CreateEditorWindow::AddCreateWindow<StartupWindow^, StartupVM^>(true);

        //    //----- �X�^�[�g�A�b�v�E�B���h�E�I���҂�
        //    StartupMessage^ message = nullptr;
        //    while (message == nullptr) {
        //        message = MessageQue<StartupMessage^>::GetEngineMessage();
        //        ThreadingUtility::ThisThreadSleep();
        //    }

        //    //----- �擾�����p�X��ݒ�
        //    m_projectData = new ProjectData();
        //    m_projectData->SetMSBuildPath(ManageToUnmanage::String(message->Path));
        //}
        using namespace System::Collections::Generic;
        using namespace EditorUI;

        //----- �ϐ��錾
        List<MessageObject<SceneViewMessageType, EditorExclusionObject<SceneViewVM^>^>^>^ sceneViewMessage
            = gcnew List<MessageObject<SceneViewMessageType, EditorExclusionObject<SceneViewVM^>^>^>(0);

        //----- ���C�����[�v
        Timer fpsTimer;
        milliSecond frameSecond = 0;
        while (m_isMainLoop) {
            //----- �Q�[������
            frameSecond += fpsTimer.GetDeltaTime();

            //----- �E�B���h�E����
            // �V�[���E�B���h�E�̒ǉ�
            while (true) {
                //----- �E�B���h�E�̎擾(�擾�ł��Ȃ�������I��)
                auto window = EditorMessageQue<SceneViewMessageType, EditorExclusionObject<SceneViewVM^>^>::GetEngineMessage(SceneViewMessageType::Add);
                if (window == nullptr) break;

                //----- �O����
                m_sceneView->Add(window->Data);
                auto size = window->Data->NoLock->NewWindowSize;    // ���̃E�B���h�E�̃T�C�Y
                while (size.HasValue == false) {
                    ThreadingUtility::ThisThreadSleep();
                    size = window->Data->NoLock->NewWindowSize;
                }

                //----- �V�K�ɍ쐬
                auto id = m_dxRender->GetAtomicData().CreateDrawWindow(Eigen::Vector2i(size.Value.X, size.Value.Y), static_cast<HWND>(window->Data->NoLock->SceneViewTarget.ToPointer()), false);
                m_dxRender->GetAtomicData().GetWindowRender(id)->AccessWindowId() = window->Data->NoLock->ID->ID;
            }

            ////----- �A�Z���u�����݃`�F�b�N
            //if (AssemblyHolder::IsLoadAssemblyEnable() == false && Refresh::GetRefreshState() != Refresh::RefreshStateType::CurrentlyRefresh) {
            //    //----- Refresh���s��
            //    if (false) {
            //        ProjectMediation::Get()->RefreshAssembly();
            //    }
            //}

            //----- FPS����
            if (frameSecond < ONE_FRAME * 1000) continue;
            frameSecond = 0;

            //----- �X�V
            InputSystem::Update();
            GlobalTimer::Get()->Update();

            //----- �G�f�B�^�[�X�V����
            //EditorUpdater::Get()->Update();

            //----- �X�V����
            GameObjectUpdater::Get()->FixedUpdate();
            GameObjectUpdater::Get()->Update();

            //----- SceneView�̃��b�Z�[�W�̎擾
            while (true) {
                auto window = EditorMessageQue<SceneViewMessageType, EditorExclusionObject<SceneViewVM^>^>::GetEngineMessage(SceneViewMessageType::Delete);
                if (window == nullptr) break;
                sceneViewMessage->Add(window);
            }
            //----- �`�揈��
            for (int i = 0; i < m_sceneView->Count; i++) {
                //----- �e�v�f�̎擾
                auto sceneView = EditorUtility::ListGet<EditorExclusionObject<SceneViewVM^>^>(m_sceneView,i);
                auto& directXs = m_dxRender->GetAtomicData().AccessWindowRenders();

                //----- ���b�N�̎擾
                auto lock = sceneView->GetEngineLock();

                //----- �폜�m�F
                for (int j = 0; j < directXs.size(); j++) {
                    for each (auto it in sceneViewMessage) {
                        //----- ������ŕێ����Ă���SceneView�ƃE�B���h�E��ID�����v����Η������폜����
                        if (it->Data->NoLock->ID == sceneView->NoLock->ID && it->Data->NoLock->ID->ID == directXs[j].AccessWindowId()) {
                            //----- ID�����v����B�폜
                            m_sceneView->RemoveAt(i);
                            directXs.erase(directXs.begin() + j);
                            j--;
                            i--;
                            goto LOOP_END;
                        }
                    }

                    //----- �폜�͂���Ă��Ȃ��B�e�`�揈��
                    directXs[j].BeginDraw();
                    auto camera = CameraSystem::Get()->GetMainData();
                    if (camera.has_value()) {
                        directXs[j].Draw(*camera);
                    }
                    directXs[j].EndDraw();
                }
                
                LOOP_END: {
                //----- ���b�N�̉���
                delete lock.Item1;
                }
            }
            ////----- �G�f�B�^�[�`�揈��
            //EditorUpdater::Get()->Draw();

            ////----- �G�f�B�^�[�`��㏈��
            //EditorUpdater::Get()->LateDraw();
        }
    }


    // �Q�[�����[�h���J�n����
    void EditorApplication::StartGameMode(void) {

    }
    // �Q�[�����[�h���ꎞ���f����
    void EditorApplication::StopGameMode(void) {

    }
    // �Q�[�����[�h���I������
    void EditorApplication::EndGameMode(void) {

    }
}
