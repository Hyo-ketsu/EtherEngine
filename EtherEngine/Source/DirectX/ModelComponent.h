#ifndef I_MODELCOMPONENT_H
#define I_MODELCOMPONENT_H
#include <Base/GraphicDefines.h>
#include <DirectX/Model.h>
#include <Base/ComponentBase.h>


//----- ModelComponentéŒ¾
namespace EtherEngine {
    class ModelComponent : public ComponentBase, public Model {
    public:
        using Model::Model;

        // •`‰æˆ—
        void Draw(void) override;
    };
}


#endif // !I_MODELCOMPONENT_H
