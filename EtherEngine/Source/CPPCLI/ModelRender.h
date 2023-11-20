#ifndef I_MODELRENDER_H
#define I_MODELRENDER_H
#include <DirectX/Model.h>
#include <CPPCLI/UserDrawComponent.h>
#include <CPPCLI/CPPCLIUtility.h>


//----- ModelRender 宣言
namespace EtherEngine {
    public ref class ModelRender : UserDrawBaseComponent {
    public:
        // コンストラクタ
        ModelRender(void)
            : UserDrawBaseComponent() {
            m_model.SetValue(Model());
        }
        // 描画関数
        void Draw(void) override {
            m_model.GetValue().DrawModel(GetGameObject()->GetTransform().CreateWorld(), GetView().GetValue(), GetProjection().GetValue(), GetPixelShader());
        }

    private:
        [Attribute::Serialize] UnmanageMaintainer<Model> m_model;   // 保持モデル
    };
}


#endif // !I_MODELRENDER_H
