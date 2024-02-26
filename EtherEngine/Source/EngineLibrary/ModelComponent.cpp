#include <EngineLibrary/ModelComponent.h>
#include <EngineLibrary/GameObject.h>


//----- ModelComponent 宣言
namespace EtherEngine {
    // コンストラクタ
    ModelComponent::ModelComponent(void) 
        : m_modelRender(gcnew ModelRender()) {
    }


    // 描画
    void ModelComponent::Draw(void) {
        //----- （読み込みが行われていなければ）読み込みを行う
        if (m_modelRender->IsLoad == false) {
            m_modelRender->GetModelBase().Load(*GetDirectX());
        }

        //----- 読み込みができたなら描画
        if (m_modelRender->IsLoad) {
            m_modelRender->GetModelBase().DrawModel(ParentGameObject->NGameObject.GetData().GetTransform(),
                GetView().GetPointer(), GetProjection().GetPointer(), GetPixelShader());
        }
    }
}
