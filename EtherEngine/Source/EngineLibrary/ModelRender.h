#ifndef I_MODELRENDER_H
#define I_MODELRENDER_H
#include <DirectX/Model.h>
#include <EngineLibrary/DrawComponent.h>
#include <EngineLibrary/EngineLibraryUtility.h>


//----- ModelRender 宣言
namespace EtherEngine {
    public ref class ModelRender : NativeDrawComponent {
    public:
        // コンストラクタ
        ModelRender(void)
            : DrawComponent() {
            m_model.SetValue(ModelBase());
        }
        // 描画関数
        void Draw(void) override {
            m_model.GetValue().DrawModel(GetGameObject()->GetTransform().CreateWorld(), GetView().GetValue(), GetProjection().GetValue(), GetPixelShader());
        }

    private:
        [Attribute::OutputAttribute] UnmanageMaintainer<ModelBase> m_model;   // 保持モデル
    };
}


#endif // !I_MODELRENDER_H
