#include <EngineLibrary/WrapperComponent.h>
#include <Base/BaseDefines.h>
#include <Base/EditorException.h>
#include <EngineLibrary/EngineLibraryUtility.h>
#include <EngineLibrary/ConvertManageToUnmanage.h>


namespace EtherEngine {
    // �R���X�g���N�^
    // @ Memo : �R���|�[�l���g�������ł��Ȃ���Η�O�𑗏o���܂�
    // @ Arg1 : �e�Q�[���I�u�W�F�N�g
    // @ Arg2 : �����R���|�[�l���g��
    WrapperComponent::WrapperComponent(NativeGameObject* gameObject, const std::string& componentName) 
        : ComponentBase(gameObject, componentName) 
        , m_componentName(componentName) {
        // @ MEMO : ���O����̐���
        System::Type^ type = System::Type::GetType(UNMANAGE_TO_MANAGE_STRING(componentName));
        auto component = dynamic_cast<Component^>(System::Activator::CreateInstance(type));

        if (component == nullptr) throw EditorException("Error! Non UserComponent");

        m_component = component;

        // @ MEMO : GameObject��NeitiveGameObject�̃|�C���^�����ׂ����낤��?
        //m_component->SetGameObject(gameObject);
    }


    // �J�n����
    void WrapperComponent::Start(void) {
        m_component->Start();
    }
    // �X�V����
    void WrapperComponent::Update(void) {
        m_component->Update();
    }
    // �폜������
    void WrapperComponent::Delete(void) {
        m_component->Delete();
    }
    // �ՓˊJ�n����
    void WrapperComponent::CollisionStart(void) {
        m_component->CollisionStart();
    }
    // �ՓˏI������
    void WrapperComponent::CollisionEnd(void) {
        m_component->CollisionEnd();
    }
    // �Փˏ���
    void WrapperComponent::CollisionHit(void) {
        m_component->CollisionHit();
    }


    // �O���o��
    Json WrapperComponent::Output(void) {
        // @ MEMO : ��ŏC������
        //auto ret = Json(Json::parse(m_component->Serialize()));
        //ret["ComponentName"] = this->GetId();
        //ret["Active"] = this->GetActive();
        //return ret;
    }
    // �O������
    void WrapperComponent::Input(const Json& input) {
        // @ MEMO : ��ŏC������
        //m_component->Deserialize(input.dump(FileDefine::JSON_DUMP_NUMBER_OF_STAGES));
        SetActive(input["Active"]);
    }
}
