#ifndef I_EDITOROBJECT_H
#define I_EDITOROBJECT_H
#include <Base/ConceptUtility.h>
#include <Base/GameObject.h>
#include <Base/Transform.h>
#include <Base/Handle.h>
#include <EtherEngine/EditorComponentBase.h>


//----- EditorObject�錾
namespace EtherEngine {
    class EditorObject : public BaseObject {
    public:
        // �X�V�������s��
        void Update(void);
        // �`�揈�����s��
        void Draw(void);
        // �폜���������s��
        void Delete(void);


        // Transform�Q�b�^�[
        const Transform& GetTransform(void) const { return m_transform; }
        // Transform�Z�b�^�[
        void SetTransform(const Transform& in) { m_transform = in; }
        // Transform�A�N�Z�T�[
        Transform& AccessTransform(void) { return m_transform; }


        // �n���h���Q�b�^�[
        Handle<EditorObject> GetHandle(void) const { return m_handle; }


        // �R���|�[�l���g��ǉ�����
        // @ Temp1: �ǉ�����R���|�[�l���g�̌^
        // @ Temps: �ǉ��R���|�[�l���g�̃R���X�g���N�^�Ɏg�p�������
        // @ Args : �ǉ��R���|�[�l���g�̃R���X�g���N�^�Ɏg�p�������
        template <Concept::SubClassOnly<EditorComponentBase> ComponentType, typename ...ArgsType>
        std::weak_ptr<ComponentType> AddComponent(ArgsType ...args);
        // �R���|�[�l���g�폜
        // @ Temp : �폜����R���|�[�l���g�̌^
        // @ Ret  : �폜������
        template <Concept::SubClassOnly<EditorComponentBase> ComponentType>
        bool DeleteComponent(void);
        // �R���|�[�l���g���擾����
        // @ Temp : �擾����R���|�[�l���g�^(EditorComponentBase�͎g�p�s��)
        // @ Ret  : �擾�����R���|�[�l���g
        // @ Arg1 : ���Ԗڂ̃R���|�[�l���g���g�p���邩(Default : 0)
        template <Concept::SubClassOnly<EditorComponentBase> ComponentType>
        std::weak_ptr<ComponentBase> GetComponent(uint index = 0);
        // �R���|�[�l���g�𕡐��擾����
        // @ Temp : �擾����R���|�[�l���g�^(EditorComponentBase�͎g�p�s��)
        // @ Ret  : �擾�����R���|�[�l���g�i�����j
        template <Concept::SubClassOnly<EditorComponentBase> ComponentType>
        std::vector<std::weak_ptr<ComponentBase>> GetComponents(void);


        // �O���o��
        Json Output(void) override { return Json(); }
        // �O������
        void Input(const Json& json) override {}


        // Inspector�\��
        void ShowInspector(void) override {}

    protected:
        // �R���X�g���N�^
        // @ Arg1 : �������W
        // @ Arg2 : �I�u�W�F�N�g��
        EditorObject(const Transform& transform, const std::string& name = "EditorObject");

    private:
        // �폜���ꂽ�R���|�[�l���g���폜����
        void DeleteComponentsDelete(void);


        friend class EditorObjectStorage;

        Transform m_transform;  // ���W
        Handle<EditorObject> m_handle;  // ���g�̃n���h��
        std::vector<std::shared_ptr<EditorComponentBase>> m_components;  // �ێ����Ă���R���|�[�l���g
    };
}


//----- EditorObject��`
namespace EtherEngine {
    // �R���|�[�l���g��ǉ�����
    template <Concept::SubClassOnly<EditorComponentBase> ComponentType, typename ...ArgsType>
    std::weak_ptr<ComponentType> EditorObject::AddComponent(ArgsType ...args) {
        //----- �x���\��
        static_assert((std::is_constructible_v<ComponentType, EditorObject*, ArgsType...>), "Error! AddComponent Args");

        //----- ����
        auto ptr = std::make_shared<ComponentType>(this, args...);

        //----- �ǉ�
        m_components.push_back(ptr);

        //----- �ԋp
        return std::weak_ptr<ComponentType>(ptr);
    }
    // �R���|�[�l���g�폜
    // @ Temp : �폜����R���|�[�l���g�̌^
    // @ Ret  : �폜������
    template <Concept::SubClassOnly<EditorComponentBase> ComponentType>
    bool EditorObject::DeleteComponent(void) {
        for (auto& component : m_components) {
            if (dynamic_cast<ComponentType>(component) != nullptr) {
                //----- �폜
                component->DeleteFuntion();
                component->SetDelete(true);
            }
        }
    }
    // �R���|�[�l���g���擾����
    // @ Temp : �擾����R���|�[�l���g�^(EditorComponentBase�͎g�p�s��)
    // @ Ret  : �擾�����R���|�[�l���g
    // @ Arg1 : ���Ԗڂ̃R���|�[�l���g���g�p���邩(Default : 0)
    template <Concept::SubClassOnly<EditorComponentBase> ComponentType>
    std::weak_ptr<ComponentBase> EditorObject::GetComponent(uint index) {
        for (auto& component : m_components) {
            if (dynamic_cast<ComponentType>(component) != nullptr) {
                //----- �w��ԍ���
                if (index != 0) {
                    //----- �w��̔ԍ��܂ŒB���Ă��Ȃ��B�ԍ���1�팸���Ď擾���p������
                    index--;
                    continue;
                }

                //----- �ԋp
                return std::weak_ptr<ComponentType>(component);
            }
        }
        //----- �����l�ԋp
        return std::weak_ptr<ComponentType>();
    }
    // �R���|�[�l���g�𕡐��擾����
    // @ Temp : �擾����R���|�[�l���g�^(EditorComponentBase�͎g�p�s��)
    // @ Ret  : �擾�����R���|�[�l���g�i�����j
    template <Concept::SubClassOnly<EditorComponentBase> ComponentType>
    std::vector<std::weak_ptr<ComponentBase>> EditorObject::GetComponents(void) {
        //----- �ԋp�p�ϐ��錾
        std::vector<std::weak_ptr<ComponentBase>> ret;

        //----- �擾
        for (auto& component : m_components) {
            if (dynamic_cast<ComponentType>(component) != nullptr) {
                //----- �ԋp�p�ϐ��ɒǉ�
                ret.push_back(std::weak_ptr<ComponentType>(component));
            }
        }

        //----- �ԋp
        return ret;
    }
}


#endif // !I_EDITOROBJECT_H
