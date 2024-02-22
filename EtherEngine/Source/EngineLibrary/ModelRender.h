#ifndef I_MODELRENDER_H
#define I_MODELRENDER_H
#include <DirectX/Model.h>
#include <EngineLibrary/DrawComponent.h>
#include <EngineLibrary/EngineLibraryUtility.h>


//----- ModelRender �錾
namespace EtherEngine {
    public ref class ModelRender : NativeDrawComponent {
    public:
        // �R���X�g���N�^
        ModelRender(void)
            : DrawComponent() {
            m_model.SetValue(ModelBase());
        }
        // �`��֐�
        void Draw(void) override {
            m_model.GetValue().DrawModel(GetGameObject()->GetTransform().CreateWorld(), GetView().GetValue(), GetProjection().GetValue(), GetPixelShader());
        }

    private:
        [Attribute::OutputAttribute] UnmanageMaintainer<ModelBase> m_model;   // �ێ����f��
    };
}


#endif // !I_MODELRENDER_H
