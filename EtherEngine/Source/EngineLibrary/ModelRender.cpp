#include <EngineLibrary/ModelRender.h>


//----- ModelRender ��`
namespace EtherEngine {
    // �R���X�g���N�^
    ModelRender::ModelRender(void) 
        : m_model(ModelBase()) {
    }
    // �f�X�g���N�^
    ModelRender::~ModelRender(void) {
        this->!ModelRender();
    }
    // �t�@�C�i���C�U
    ModelRender::!ModelRender(void) {
        m_model.MaintainerClear();
    }
}
