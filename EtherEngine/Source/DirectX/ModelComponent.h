#ifndef I_MODELCOMPONENT_H
#define I_MODELCOMPONENT_H
#include <Base/GraphicDefines.h>
#include <DirectX/Model.h>
#include <Base/ComponentBase.h>


//----- ModelComponent�錾
namespace EtherEngine {
    class ModelComponent : public ComponentBase, public Model {
    public:
        using Model::Model;

        // �`�揈��
        void Draw(void) override;
    };
}


#endif // !I_MODELCOMPONENT_H
