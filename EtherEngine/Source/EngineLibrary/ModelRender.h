#ifndef I_MODELRENDER_H
#define I_MODELRENDER_H
#include <DirectX/Model.h>
#include <EngineLibrary/WrapperDrawComponent.h>
#include <EngineLibrary/EngineLibraryUtility.h>


//----- ModelRender 宣言
namespace EtherEngine {
#ifdef _ENGINELIBRARY
    public ref class ModelRender : DrawBaseComponent {
    public:
        // コンストラクタ
        ModelRender(void)
            : DrawBaseComponent() {
            m_model.SetValue(Model());
        }
        // 描画関数
        void Draw(void) override {
            m_model.GetValue().DrawModel(GetGameObject()->GetTransform().CreateWorld(), GetView().GetValue(), GetProjection().GetValue(), GetPixelShader());
        }

    private:
        [Attribute::Serialize] UnmanageMaintainer<Model> m_model;   // 保持モデル
    };
#endif
}


#endif // !I_MODELRENDER_H
