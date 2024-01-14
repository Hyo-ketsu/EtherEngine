#ifndef I_EDITORAPPLICATION_H
#define I_EDITORAPPLICATION_H
#include <EngineLibrary/ManageSingleton.h>
#include <EtherEngine/ImGuiClass.h>
#include <Base/Handle.h>
#include <DirectX/DirectX.h>


#pragma managed
//----- EditorApplication 宣言
namespace EtherEngine {
    // エディター(ゲームエンジン)を表現するクラス(Singleton)
    public ref class EditorApplication : public GameApplication {     
        ETHER_ENGINE_MANAGE_SINGLETON(EditorApplication);
    private:
        // シーンビューを管理するメソッド(イベント購読用)
        void SceneViewFunction(System::Object^ s, System::EventArgs^ e);


        // DirectXを取得する
        // @ Arg1 : 取得したDirectXRender
        Handle<DirectXRender>& GetDirectX(void);


        IMGUI* m_imGui;     // 保持しているIMGUI
        System::Collections::Generic::List<EditorUI::EditorExclusionObject<EditorUI::SceneViewVM^>^>^ m_sceneView;    // 保持しているSceneView  // 保持しているSceneViewのメッセージ
    };
}


#endif // !I_EDITORAPPLICATION_H
