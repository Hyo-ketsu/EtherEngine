#ifndef I_MODELRENDER_H
#define I_MODELRENDER_H
#include <DirectX/Model.h>
#include <EngineLibrary/UserDrawComponent.h>
#include <EngineLibrary/EngineLibraryUtility.h>


//----- ModelRender �錾
namespace EtherEngine {
#ifdef _ENGINELIBRARY
    public ref class ModelRender : UserDrawBaseComponent {
    public:
        // �R���X�g���N�^
        ModelRender(void)
            : UserDrawBaseComponent() {
            m_model.SetValue(Model());
        }
        // �`��֐�
        void Draw(void) override {
            m_model.GetValue().DrawModel(GetGameObject()->GetTransform().CreateWorld(), GetView().GetValue(), GetProjection().GetValue(), GetPixelShader());
        }

    private:
        [Attribute::Serialize] UnmanageMaintainer<Model> m_model;   // �ێ����f��
    };
#endif
}


#endif // !I_MODELRENDER_H