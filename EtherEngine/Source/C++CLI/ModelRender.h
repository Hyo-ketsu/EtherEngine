#ifndef I_MODELRENDER_H
#define I_MODELRENDER_H
#include <DirectX/Model.h>
#include <C++CLI/UserDrawComponent.h>
#include <C++CLI/C++CLIUtility.h>


//----- ModelRender 宣言
namespace EtherEngine {
#ifndef CPPCLI_CPPCLI_CLASS_DECLARATION
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
#endif
}


#endif // !I_MODELRENDER_H
