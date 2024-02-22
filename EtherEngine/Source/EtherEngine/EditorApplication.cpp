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
//----- EditorApplication 定義
namespace EtherEngine {
    // コンストラクタ
    EditorApplication::EditorApplication(void) 
        : GameApplication()
        , m_sceneView(gcnew System::Collections::Generic::List<EditorUI::EditorExclusionObject<EditorUI::SceneViewVM^>^>(0)) {
        //----- シングルトン設定
        void* getptr;
        EngineLibrarySingletonGetter::Get->GetCentrallySingleton(&getptr);
        auto singleton = static_cast<std::shared_ptr<CentrallySingleton>*>(getptr);
        CentrallySingleton::Set(*singleton);

        //----- シングルトンのインスタンス設定
        GameApplication::Get = this;

        //----- イベント登録
        this->InitEvent += ETHER_ENGINE_MANAGE_LAMBDA_USE(System::EventHandler, InitEvent);
        this->LoopFirstEvent += gcnew System::EventHandler(this, &EditorApplication::SceneViewFunction);
    }


    // シーンビューを管理するメソッド(イベント購読用)
    void EditorApplication::SceneViewFunction(System::Object^ s, System::EventArgs^ e) {
        using namespace System::Collections::Generic;
        using namespace EditorUI;

        //----- ウィンドウの取得
        while (true) {
            //----- ウィンドウの取得(取得できなかったら終了)
            auto window = EditorMessageQue<SceneViewMessageType, EditorExclusionObject<SceneViewVM^>^>::GetEngineMessage(SceneViewMessageType::Add);
            if (window == nullptr) break;

            //----- 前準備
            m_sceneView->Add(window->Data);
            auto size = window->Data->NoLock->NewWindowSize;    // このウィンドウのサイズ
            while (size.HasValue == false) {
                Utility::ThisThreadSleep();
                size = window->Data->NoLock->NewWindowSize;
            }

            //----- 新規に作成
            auto id = GetDirectX().GetAtomicData().CreateDrawWindow(Eigen::Vector2i(size.Value.X, size.Value.Y), static_cast<HWND>(window->Data->NoLock->SceneViewTarget.ToPointer()), false);
            GetDirectX().GetAtomicData().GetWindowRender(id)->AccessWindowId() = window->Data->NoLock->ID->ID;
        }

        //----- SceneViewのメッセージの取得
        List<EditorExclusionObject<SceneViewVM^>^>^ messages = gcnew List<EditorExclusionObject<SceneViewVM^>^>(0);
        while (true) {
            auto window = EditorMessageQue<SceneViewMessageType, EditorExclusionObject<SceneViewVM^>^>::GetEngineMessage(SceneViewMessageType::IsDelete);
            if (window == nullptr) break;
            messages->Add(window->Data);
        }
        //----- SceneViewの削除
        for (int i = 0; i < m_sceneView->Count; i++) {
            //----- 各要素の取得
            auto sceneView = EditorUtility::ListGet<EditorExclusionObject<SceneViewVM^>^>(m_sceneView, i);
            auto&& directXs = GetDirectX().GetAtomicData().AccessWindowRenders();

            //----- ロックの取得
            auto lock = sceneView->GetEngineLock();

            //----- 削除確認
            for (int j = 0; j < directXs.size(); j++) {
                for each (auto it in messages) {
                    //----- こちらで保持しているSceneViewとウィンドウのIDが合致すれば両方を削除する
                    if (it->NoLock->ID == sceneView->NoLock->ID && it->NoLock->ID->ID == directXs[j].AccessWindowId()) {
                        //----- IDが合致する。削除
                        m_sceneView->RemoveAt(i);
                        directXs.erase(directXs.begin() + j);
                        j--;
                        i--;
                        goto LOOP_END;
                    }
                }
            }

            LOOP_END: {
            //----- ロックの解除
            delete lock.Item1;
            }
        }
    }


    // DirectXを取得する
    Handle<DirectXRender>& EditorApplication::GetDirectX(void) {
        void* ret = nullptr;
        GetDirectX(&ret);
        return *static_cast<Handle<DirectXRender>*>(ret);
    }
}
