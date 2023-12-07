#include <EtherEngine/EditorApplication.h>
#include <Base/Timer.h>
#include <Base/HandleHelper.h>
#include <Base/WindowsDefine.h>
#include <Base/BaseInput.h>
#include <Base/BaseDefines.h>
#include <Base/GameObjectUpdater.h>
#include <EngineLibrary/EngineLibraryInit.h>
#include <EngineLibrary/AssemblyHolder.h>
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


//----- EditorApplication ��`
namespace EtherEngine {
    // �R���X�g���N�^
    EditorApplication::EditorApplication(void)
        : BaseMainWindow(WindowDefine::Name::EDITOR_APPLICATION)
        , m_isGameMode(false) 
        , m_isWindowFunctionEnable(true) {
    }
    // �f�X�g���N�^
    EditorApplication::~EditorApplication(void) {
    }


    // �������O�֐�
    void EditorApplication::InitFirstFunction(void) {
        //----- �p�X���̃f�[�^�ǂݎ��
//#ifdef _DEBUG
        try {
            m_projectData = std::make_unique<ProjectData>(PathClass::GetCurDirectory() / EditorFileDefine::Directory::EDITOR_SETTING / EditorFileDefine::PROJECT_DATA);
        }
        catch (...) {
            m_projectData = std::make_unique<ProjectData>();
            m_projectData->SetMSBuildPath(R"(C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe)");
            m_projectData.reset();  // �ۑ������邽�߁B
        }
//#endif // _DEBUG
    }
    // ��������֐�
    void EditorApplication::InitLateFunction(void) {
        m_initUninitPerformer.AddInitUninit(
            [&]() { m_imGui = std::make_unique<IMGUI>(
            m_dxRender.GetAtomicData().GetDevice(),
            m_dxRender.GetAtomicData().GetContext(),
            m_hwnd.value()); },
            [&]() { m_imGui.reset(); }
        );

        //----- �v���W�F�N�g�ݒ�̓ǂݍ���
        try {
            m_projectData = std::make_unique<ProjectData>(PathClass::GetCurDirectory() / EditorFileDefine::Directory::EDITOR_SETTING / EditorFileDefine::PROJECT_DATA);
        }
        catch (const EditorException& e) {
            using namespace EditorUI;

            //----- �Ȃ��B�X�^�[�g�A�b�v�E�B���h�E�N��
            auto VM = CreateEditorWindow::AddCreateWindow<StartupWindow^, StartupVM^>(true);

            //----- �X�^�[�g�A�b�v�E�B���h�E�I���҂�
            StartupMessage^ message = nullptr;
            while (message == nullptr) { 
                message = MessageQue<StartupMessage^>::GetEngineMessage();
                Utility::ThisThreadSleep();
            }

            //----- �擾�����p�X��ݒ�
            m_projectData = std::make_unique<ProjectData>();
            m_projectData->SetMSBuildPath(ManageToUnmanage::String(message->Path));
        }

        //----- �G�f�B�^�[�ݒ�̓ǂݍ���
        try {
            m_editorData = std::make_unique<EditorData>(PathClass::GetCurDirectory() / EditorFileDefine::Directory::EDITOR_SETTING / EditorFileDefine::EDITOR_SETTING);
        }
        catch (...) {
            //----- �Ȃ��B1���琶��
            m_editorData = std::make_unique<EditorData>();
        }

        m_initUninitPerformer.AddInitUninit(
            []() { ProjectMediation::Get()->Init(PathClass::GetCurDirectory() / FileDefine::PROJECT_NAME + FileDefine::Extended::SOLUTION, PathClass::GetCurDirectory() / FileDefine::PROJECT_NAME + FileDefine::Extended::PROJECT); },
            []() { ProjectMediation::Get()->Uninit(); }
        );
    }
    // �������I����֐�
    void EditorApplication::EndInitLateFunction(void) {

    }
    // �I���O�֐�
    void EditorApplication::UninitFirstFunction(void) {
#ifndef _DEBUG
        //----- �o��
        // @ MEMO : �ʓ|�Ȃ�Ō��
#endif // !_DEBUG
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

        //----- VS���̐ݒ�
        // @ MEMO : ��Ŏ�������

        // @ MEMO : �e�X�g
        Refresh::AssemblyRefresh();

        //----- ���b�Z�[�W���[�v
        MSG message;
        Timer fpsTimer;
        milliSecond frameSecond = 0;
        while (GetIsGameLoop()) {
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

                //----- �E�B���h�E����
                // �V�[���E�B���h�E�̒ǉ�
                while (true) {
                    //----- �E�B���h�E�̎擾(�擾�ł��Ȃ�������I��)
                    auto window = EditorUI::GetEditorWindow::GetCreateWindow<EditorUI::SceneViewVM^>();
                    if (window == nullptr) break;

                    //----- �O����
                    auto engineLock = window->GetEngineLock();  // ���b�N�擾
                    auto size = engineLock.Item2->NewWindowSize;    // ���̃E�B���h�E�̃T�C�Y
                    if (size.HasValue == false) throw std::exception("Error! Is SceneView size?");

                    //----- �����_�p��
                    // @ MEMO : ���ʓI�ɎQ�Ƃ������_�ŃL���v�`�����Ă���BwindowRender�����񂾂�������邾�낤���Ǘv���ӁH
                    DrawFunctionLambda drawFunction = [&](Eigen::Matrix4f view, Eigen::Matrix4f projection) {    // �E�B���h�E�ōs���`��
                        GameObjectUpdater::Get()->Draw(view, projection);
                    };
                    msclr::gcroot<decltype(window)> enableWindow = window;  // �E�B���h�E�����m�Flambda�ŃL���v�`�����邽��
                    WindowEnableLambda enableFunction = [=]() -> bool {
                        return enableWindow->GetEngineLock().Item2 != nullptr && enableWindow->GetEngineLock().Item2 != nullptr;
                    };
                    WindowFunctionLambda windowFunction = [=](DXWindowRender* const window) {   // �E�B���h�E�ł̒ǉ������B���T�C�Y���o
                        auto size = enableWindow->GetEngineLock().Item2->NewWindowSize;
                        if (size.HasValue) {
                            //----- ���T�C�Y���s��
                            // @ MEMO : ����s���Ă���܂���B
                        }
                    };

                    //----- �V�K�ɍ쐬
                    m_dxRender.GetAtomicData().CreateDrawWindow(Eigen::Vector2i(size.Value.X, size.Value.Y),static_cast<HWND>(engineLock.Item2->SceneViewTarget.ToPointer()),
                        false, drawFunction, enableFunction, windowFunction);
                }

                //----- �A�Z���u�����݃`�F�b�N
                if (AssemblyHolder::IsLoadAssemblyEnable() == false && Refresh::GetRefreshState() != Refresh::RefreshStateType::CurrentlyRefresh) {
                    //----- Refresh���s��
                    if (false) {
                        ProjectMediation::Get()->RefreshAssembly();
                    }
                }

                //----- �V�[���E�B���h�E�X�V����
                auto& windowData = m_dxRender.GetAtomicData();
                for (auto it = windowData.AccessWindowRenders().begin(); it != windowData.AccessWindowRenders().end();) {
                    //----- �����`�F�b�N
                    if (it->GetWindowEnableFunction()()) {
                        //----- �������Ă���B�X�V
                        it->GetWindowFunction()(&*it);
                        it++;
                    }
                    else {
                        //----- �������Ă��Ȃ��B�폜
                        windowData.AccessWindowRenders().erase(it);
                    }
                }

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

                //----- �`��O����
                for (auto&& it : m_dxRender.GetAtomicData().AccessWindowRenders()) {
                    it.BeginDraw();
                }

                //----- �`�揈��
                for (auto&& it : m_dxRender.GetAtomicData().AccessWindowRenders()) {
                    it.Draw();
                }

                ////----- �G�f�B�^�[�`�揈��
                //EditorUpdater::Get()->Draw();

                ////----- �G�f�B�^�[�`��㏈��
                //EditorUpdater::Get()->LateDraw();

                //----- �`��㏈��
                for (auto&& it : m_dxRender.GetAtomicData().AccessWindowRenders()) {
                    it.EndDraw();
                }
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


    // �E�B���h�E�̈ړ��Ȃǂ̗L��������؂�ւ���
    void EditorApplication::SetWindowFunctionEnable(const bool isEnable, const bool isClose) {
        //----- �ϐ��錾
        uint enable = isEnable ? MF_ENABLED : MF_BYCOMMAND | MF_GRAYED;

        //----- �ȉ����j���[�ݒ�
        if (isClose) EnableMenuItem(GetSystemMenu(GetHWND(), FALSE), SC_CLOSE, enable);

        m_isWindowFunctionEnable = isEnable;
    }
}
