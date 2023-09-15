#include <EtherEngine/EditorApplication.h>
#include <Base/Timer.h>
#include <Base/HandleHelper.h>
#include <Base/WindowsDefine.h>
#include <Base/BaseInput.h>
#include <Base/GameObjectUpdater.h>
#include <C++CLI/C++CLIInit.h>
#include <C++CLI/AssemblyHolder.h>
#include <EtherEngine/EditorObjectUpdater.h>
#include <EtherEngine/MSVCMediation.h>
#include <EtherEngine/ProjectMediation.h> 
#ifdef _DEBUG
#include <EtherEngine/EditorCamera.h>
#include <DirectX/ModelComponent.h>
#include <DirectX/ShaderClass.h>
#include <Base/CollisionSphere.h>
#include <Base/GameObjectStorage.h>
#include <Base/CameraComponent.h>
#include <EtherEngine/Test/TestDefine.h>
#include <EtherEngine/Test/TestComponent.h>
#include <EtherEngine/EditorOutliner.h>
#include <EtherEngine/Test/EditorDebugWindow.h>
#include <EtherEngine/EditorExplorerWindow.h>
#endif // _DEBUG


namespace EtherEngine {
    // �R���X�g���N�^
    EditorApplication::EditorApplication(void)
        : BaseMainWindow(WindowDefine::Name::EDITOR_APPLICATION)
        , m_isGameMode(false) {
    }
    // �f�X�g���N�^
    EditorApplication::~EditorApplication(void) {
    }


    // �������֐�
    void EditorApplication::InitFirstFunction(void) {
        //----- �f�[�^�ǂݎ��
        // @ MEMO : �ЂƂ܂����Łi����ProjectData���Ńf�[�^�𐶐����Ă���̂Łj
        m_projectData = std::make_unique<ProjectData>();
        m_projectEditorData = std::make_unique<ProjectEditorData>();
    }
    // �������֐�
    void EditorApplication::InitLateFunction(void) {
        m_initUninitPerformer.AddInitUninit(
            [&]() { MSVCMediation::Get()->Init(m_projectData->GetCmdPath(), m_projectData->GetMsvcPath()); },
            []() { MSVCMediation::Get()->Uninit(); }
        );
        m_initUninitPerformer.AddInitUninit(
            [&]() { ProjectMediation::Get()->Init(PathClass::GetCurDirectory() / FileDefine::PROJECTNAME + FileDefine::SOLUTION, PathClass::GetCurDirectory() / FileDefine::PROJECTNAME + FileDefine::PROJECT); },
            []() { ProjectMediation::Get()->Uninit(); }
        );
        m_initUninitPerformer.AddInitUninit(
            [&]() { m_imGui = std::make_unique<IMGUI>(
                m_dxRender.GetAtomicData().GetDevice(),
                m_dxRender.GetAtomicData().GetContext(),
                m_hwnd.value()); },
            [&]() { m_imGui.reset(); }
        );
    }
    // ���C���֐�
    void EditorApplication::MainFunction(void) {
#ifdef _DEBUG
        //----- �e�X�g�E�B���h�E
        auto testWindow = EditorObjectStorage::Get()->CreateEditorObject();
        testWindow.GetAtomicData().AddComponent<EditorDebugWindow>(ImGuiDefine::Name::WINDOW_DEBUG);

        ////----- �e�X�g�R���|�[�l���g
        //auto testGameObject = GameObjectStorage::Get()->CreateGameObject();
        ////testGameObject.GetAtomicData().AddComponent("TestComponent");

        ////----- �G�f�B�^�[�p�J�����쐬
        //auto cameraGameObejct = EditorObjectStorage::Get()->CreateEditorObject();
        //cameraGameObejct.GetAtomicData().AccessTransform().AccessPostion().z() = -5;
        //auto camera = cameraGameObejct.GetAtomicData().AddComponent<EditorCamera>();

        ////----- �e�X�g�p�V�F�[�_�[�ǉ�
        //auto vs = VertexShader(this->GetDirectX());
        //vs.LoadFile((TestDefine::TEST_ASSET_SHADER_PASS + "VS_Test.cso").c_str());
        //auto ps = PixelShader(this->GetDirectX());
        //ps.LoadFile((TestDefine::TEST_ASSET_SHADER_PASS + "PS_Test.cso").c_str());

        ////----- �J�����ݒ�
        //m_dxRender.GetAtomicData().SetCameraID(camera.lock()->GetID().GetId());
#endif // _DEBUG

        //----- ���b�Z�[�W���[�v
        MSG message;
        Timer fpsTimer;
        milliSecond frameSecond = 0;
        while (true) {
            //----- ���b�Z�[�W�m�F
            if (PeekMessage(&message, NULL, 0, 0, PM_NOREMOVE)) {
                // ���b�Z�[�W���擾
                // WM_QUIT�̂݁A�擾�ł��Ȃ��Ɣ��肳���
                if (!GetMessage(&message, NULL, 0, 0)) {
                    // WM_QUIT���͂����������I��
                    break;
                }
                else {
                    TranslateMessage(&message); // �͂������b�Z�[�W��Windows�ɓ]��
                    DispatchMessage(&message);  // 
                }
            }
            else {   
                //----- �Q�[������
                frameSecond += fpsTimer.GetDeltaTime();

                //----- �A�Z���u�����݃`�F�b�N
                if (AssemblyHolder::IsLoadAssemblyEnable() == false) {

                }

                //----- FPS����
                if (frameSecond < ONE_FRAME * 1000) continue;
                frameSecond = 0;

                //----- �X�V
                InputSystem::Update();
                GlobalTimer::Get()->Update();

                //----- �G�f�B�^�[�X�V����
                EditorUpdater::Get()->Update();

                //----- �X�V����
                GameObjectUpdater::Get()->FixedUpdate();
                GameObjectUpdater::Get()->Update();

                //----- �`��O����
                m_dxRender.GetAtomicData().BeginDraw();

                //----- �G�f�B�^�[�`�揈��
                EditorUpdater::Get()->Draw();

                //----- �`�揈��
                m_dxRender.GetAtomicData().Draw();

                //----- IMGUI�`��㏈��
                ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

                //----- �`��㏈��
                m_dxRender.GetAtomicData().EndDraw();
            }
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