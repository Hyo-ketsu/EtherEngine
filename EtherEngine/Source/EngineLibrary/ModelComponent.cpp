#include <EngineLibrary/ModelComponent.h>
#include <EngineLibrary/GameObject.h>


//----- ModelComponent �錾
namespace EtherEngine {
    // �R���X�g���N�^
    ModelComponent::ModelComponent(void) 
        : m_modelRender(gcnew ModelRender()) {
    }


    // �`��
    void ModelComponent::Draw(void) {
        //----- �i�ǂݍ��݂��s���Ă��Ȃ���΁j�ǂݍ��݂��s��
        if (m_modelRender->IsLoad == false) {
            m_modelRender->GetModelBase().Load(*GetDirectX());
        }

        //----- �ǂݍ��݂��ł����Ȃ�`��
        if (m_modelRender->IsLoad) {
            m_modelRender->GetModelBase().DrawModel(ParentGameObject->NGameObject.GetData().GetTransform(),
                GetView().GetPointer(), GetProjection().GetPointer(), GetPixelShader());
        }
    }
}
