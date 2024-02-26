#ifndef I_MODELCOMPONENT_H
#define I_MODELCOMPONENT_H
#include <DirectX/Model.h>
#include <EngineLibrary/DrawComponent.h>
#include <EngineLibrary/ModelRender.h>


#pragma managed
//----- ModelComponent �錾
namespace EtherEngine {
    public ref class ModelComponent : DrawComponent {
    public:
        // �R���X�g���N�^
        ModelComponent(void);


        // �\�����f��
        property ModelRender^ Model {
            ModelRender^ get(void) { return m_modelRender; }
            void set(ModelRender^ value) { m_modelRender = value; }
        }


        // �`��
        void Draw(void) override;

    private:
        ModelRender^ m_modelRender; // �\�����f��
    };
}


#endif // !I_MODELCOMPONENT_H
