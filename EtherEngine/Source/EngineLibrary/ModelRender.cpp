#include <EngineLibrary/ModelRender.h>


//----- ModelRender 定義
namespace EtherEngine {
    // コンストラクタ
    ModelRender::ModelRender(void) 
        : m_model(ModelBase()) {
    }
    // デストラクタ
    ModelRender::~ModelRender(void) {
        this->!ModelRender();
    }
    // ファイナライザ
    ModelRender::!ModelRender(void) {
        m_model.MaintainerClear();
    }
}
