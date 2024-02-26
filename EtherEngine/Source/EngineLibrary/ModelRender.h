#ifndef I_MODELRENDER_H
#define I_MODELRENDER_H
#include <DirectX/Model.h>
#include <EngineLibrary/DrawComponent.h>
#include <EngineLibrary/EngineLibraryUtility.h>
#include <EngineLibrary/ConvertManageToUnmanage.h>


//----- ModelRender �錾
namespace EtherEngine {
    public ref class ModelRender {
    public:
        // �R���X�g���N�^
        ModelRender(void);
        // �f�X�g���N�^
        ~ModelRender(void);
        // �t�@�C�i���C�U
        !ModelRender(void);


        property bool IsLoad {
            bool get(void) { return m_model.GetValue().GetIsLoad(); }
        }
        property bool IsFlip {
            bool get(void) { return m_model.GetValue().GetIsFlip(); }
            void set(bool value) { m_model.GetValue().SetIsFlip(value); }
        }
        property System::String^ LoadModel {
            System::String^ get(void) { return gcnew System::String(m_model.GetValue().GetLoadModel().c_str()); }
            void set(System::String^ value) { m_model.GetValue().SetLoadModel(ManageToUnmanage::String(value)); }
        }


        // ���f�����̂��擾����
        ModelBase GetModelBase(void) { return m_model.GetValue(); }

    private:
        [Attribute::OutputAttribute] UnmanageMaintainer<ModelBase> m_model;   // �ێ����f��
    };
}


#endif // !I_MODELRENDER_H
