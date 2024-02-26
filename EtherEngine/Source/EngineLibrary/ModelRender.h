#ifndef I_MODELRENDER_H
#define I_MODELRENDER_H
#include <DirectX/Model.h>
#include <EngineLibrary/DrawComponent.h>
#include <EngineLibrary/EngineLibraryUtility.h>
#include <EngineLibrary/ConvertManageToUnmanage.h>


//----- ModelRender 宣言
namespace EtherEngine {
    public ref class ModelRender {
    public:
        // コンストラクタ
        ModelRender(void);
        // デストラクタ
        ~ModelRender(void);
        // ファイナライザ
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


        // モデル自体を取得する
        ModelBase GetModelBase(void) { return m_model.GetValue(); }

    private:
        [Attribute::OutputAttribute] UnmanageMaintainer<ModelBase> m_model;   // 保持モデル
    };
}


#endif // !I_MODELRENDER_H
