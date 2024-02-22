#include <EtherEngine/EditorApplication.h>
#include <Base/BaseUtility.h>
#include <EngineLibrary/ManageLambda.h>
#include <EtherEngine/EditorCamera.h>
#include <EtherEngine/EditorObjectUpdater.h>
#include <EtherEngine/EditorUtility.h>
#include <Base/CameraStorage.h>


#pragma managed
ETHER_ENGINE_MANAGE_LAMBDA_DEFINE(InitEvent, System::EventArgs^,
    auto cameraGameObject = EditorObjectStorage::Get()->CreateEditorObject();
    cameraGameObject.GetAtomicData().AccessTransform().AccessPostion().z() = -5;
    auto camera = cameraGameObject.GetAtomicData().AddComponent<EditorCamera>();
);


#pragma managed
//----- EditorApplication ��`
namespace EtherEngine {
    // �R���X�g���N�^
    EditorApplication::EditorApplication(void) 
        : GameApplication()
        , m_sceneView(gcnew System::Collections::Generic::List<EditorUI::EditorExclusionObject<EditorUI::SceneViewVM^>^>(0)) {
        //----- �V���O���g���ݒ�
        void* getptr;
        EngineLibrarySingletonGetter::Get->GetCentrallySingleton(&getptr);
        auto singleton = static_cast<std::shared_ptr<CentrallySingleton>*>(getptr);
        CentrallySingleton::Set(*singleton);

        //----- �V���O���g���̃C���X�^���X�ݒ�
        GameApplication::Get = this;

        //----- �C�x���g�o�^
        this->InitEvent += ETHER_ENGINE_MANAGE_LAMBDA_USE(System::EventHandler, InitEvent);
        this->LoopFirstEvent += gcnew System::EventHandler(this, &EditorApplication::SceneViewFunction);
    }


    // �V�[���r���[���Ǘ����郁�\�b�h(�C�x���g�w�Ǘp)
    void EditorApplication::SceneViewFunction(System::Object^ s, System::EventArgs^ e) {
        using namespace System::Collections::Generic;
        using namespace EditorUI;

        //----- �E�B���h�E�̎擾
        while (true) {
            //----- �E�B���h�E�̎擾(�擾�ł��Ȃ�������I��)
            auto window = EditorMessageQue<SceneViewMessageType, EditorExclusionObject<SceneViewVM^>^>::GetEngineMessage(SceneViewMessageType::Add);
            if (window == nullptr) break;

            //----- �O����
            m_sceneView->Add(window->Data);
            auto size = window->Data->NoLock->NewWindowSize;    // ���̃E�B���h�E�̃T�C�Y
            while (size.HasValue == false) {
                Utility::ThisThreadSleep();
                size = window->Data->NoLock->NewWindowSize;
            }

            //----- �V�K�ɍ쐬
            auto id = GetDirectX().GetAtomicData().CreateDrawWindow(Eigen::Vector2i(size.Value.X, size.Value.Y), static_cast<HWND>(window->Data->NoLock->SceneViewTarget.ToPointer()), false);
            GetDirectX().GetAtomicData().GetWindowRender(id)->AccessWindowId() = window->Data->NoLock->ID->ID;
        }

        //----- SceneView�̃��b�Z�[�W�̎擾
        List<EditorExclusionObject<SceneViewVM^>^>^ messages = gcnew List<EditorExclusionObject<SceneViewVM^>^>(0);
        while (true) {
            auto window = EditorMessageQue<SceneViewMessageType, EditorExclusionObject<SceneViewVM^>^>::GetEngineMessage(SceneViewMessageType::IsDelete);
            if (window == nullptr) break;
            messages->Add(window->Data);
        }
        //----- SceneView�̍폜
        for (int i = 0; i < m_sceneView->Count; i++) {
            //----- �e�v�f�̎擾
            auto sceneView = EditorUtility::ListGet<EditorExclusionObject<SceneViewVM^>^>(m_sceneView, i);
            auto&& directXs = GetDirectX().GetAtomicData().AccessWindowRenders();

            //----- ���b�N�̎擾
            auto lock = sceneView->GetEngineLock();

            //----- �폜�m�F
            for (int j = 0; j < directXs.size(); j++) {
                for each (auto it in messages) {
                    //----- ������ŕێ����Ă���SceneView�ƃE�B���h�E��ID�����v����Η������폜����
                    if (it->NoLock->ID == sceneView->NoLock->ID && it->NoLock->ID->ID == directXs[j].AccessWindowId()) {
                        //----- ID�����v����B�폜
                        m_sceneView->RemoveAt(i);
                        directXs.erase(directXs.begin() + j);
                        j--;
                        i--;
                        goto LOOP_END;
                    }
                }
            }

            LOOP_END: {
            //----- ���b�N�̉���
            delete lock.Item1;
            }
        }
    }


    // DirectX���擾����
    Handle<DirectXRender>& EditorApplication::GetDirectX(void) {
        void* ret = nullptr;
        GetDirectX(&ret);
        return *static_cast<Handle<DirectXRender>*>(ret);
    }
}
