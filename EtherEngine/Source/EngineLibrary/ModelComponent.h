#ifndef I_MODELCOMPONENT_H
#define I_MODELCOMPONENT_H
#include <DirectX/Model.h>
#include <EngineLibrary/DrawComponent.h>
#include <EngineLibrary/ModelRender.h>


#pragma managed
//----- ModelComponent 宣言
namespace EtherEngine {
    public ref class ModelComponent : DrawComponent {
    public:
        // コンストラクタ
        ModelComponent(void);


        // 表示モデル
        property ModelRender^ Model {
            ModelRender^ get(void) { return m_modelRender; }
            void set(ModelRender^ value) { m_modelRender = value; }
        }


        // 描画
        void Draw(void) override;

    private:
        ModelRender^ m_modelRender; // 表示モデル
    };
}


#endif // !I_MODELCOMPONENT_H
