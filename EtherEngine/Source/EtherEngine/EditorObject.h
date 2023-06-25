#ifndef I_EDITOROBJECT_H
#define I_EDITOROBJECT_H
#include <Base/ConceptUtility.h>
#include <Base/Transform.h>
#include <Base/Handle.h>
#include <EtherEngine/EditorComponentBase.h>


//----- EditorObject�錾
namespace EtherEngine {
    class EditorObject {
    public:
        // �X�V�������s��
        void Update(void);
        // �`�揈�����s��
        void Draw(void);


        // Transform�A�N�Z�T�[
        Transform& AccessTransform(void) { return m_transform; }

        // �n���h���Q�b�^�[
        BaseHandle<EditorObject> GetHandle(void) const { return m_handle; }


        // �R���|�[�l���g��ǉ�����
        // @ Temp1: �ǉ�����R���|�[�l���g
        // @ Temps: �ǉ��R���|�[�l���g�̃R���X�g���N�^�Ɏg�p�������
        // @ Args : �ǉ��R���|�[�l���g�̃R���X�g���N�^�Ɏg�p�������
        template <Concept::BaseOfConcept<EditorComponentBase> ComponentType, typename ...ArgsType>
        std::weak_ptr<ComponentType> AddComponent(ArgsType... args);

    private:
        // �R���X�g���N�^
        // @ Arg1 : �������W
        EditorObject(const Transform& transform);

        friend class EditorObjectStorage;


        Transform m_transform;  // ���W
        BaseHandle<EditorObject> m_handle;  // ���g�̃n���h��
        std::vector<std::shared_ptr<EditorComponentBase>> m_component;  // �ێ����Ă���R���|�[�l���g
    };
}


//----- EditorObject��`
namespace EtherEngine {
    // �R���|�[�l���g��ǉ�����
    template <Concept::BaseOfConcept<EditorComponentBase> ComponentType, typename ...ArgsType>
    std::weak_ptr<ComponentType> EditorObject::AddComponent(ArgsType... args) {
        //----- �x���\��
        static_assert((std::is_constructible_v<ComponentType, EditorObject*, ArgsType...>), "Error! AddComponent Args");

        //----- ����
        auto ptr = std::make_shared<ComponentType>(this, args...);

        //----- �ǉ�
        m_component.push_back(ptr);

        //----- �ԋp
        return std::weak_ptr<ComponentType>(ptr);
    }
}


#endif // !I_EDITOROBJECT_H
