#ifndef I_PARENTANDCHILDOBJECT_H
#define I_PARENTANDCHILDOBJECT_H
#include <Base/Handle.h>


namespace EtherEngine {
    // �e�q�֌W���N���X�ł݈̂����R���Z�v�g
    // �N���X���Q�Ƃ�|�C���^�ł͂Ȃ�
    template <typename T>
    concept ParentAndChildObjectConcept = std::is_class_v<T> && !(std::is_reference_v<T>) && !(std::is_pointer_v<T>);
}


//----- ParentAndChildObject�錾
namespace EtherEngine {
    // �e�q�֌W���I�u�W�F�N�g�Ƃ��ĕ\�����邽�߂̃N���X
    // @ Temp: �e�q�֌W��\������N���X
    template <ParentAndChildObjectConcept Type>
    class ParentAndChildObject {
    public:
        // �R���X�g���N�^
        ParentAndChildObject(void) {}
        // �f�X�g���N�^
        virtual ~ParentAndChildObject(void) {}


        // �e��ݒ肷��
        // @ Arg1 : �e�ɐݒ肷��n���h��
        void SetParent(const Handle<Type>& handle);

        // �e�ւ̃A�N�Z�X���폜����
        void DeleteParent(void);

        // �e�v�f�����݂��邩
        bool IsParent(void) const;

        // �e���擾����
        // @ Ret  : �e�v�f�ւ̃n���h��
        Handle<Type> GetParent(void) const;


        // �q��ǉ�����
        // @ Arg1 : �q�Ƃ��Ēǉ�����n���h��
        void AddChild(const Handle<Type>& handle);

        // �C���f�b�N�X�Ŏq�ւ̃A�N�Z�X���폜����
        // @ Arg1 : �C���f�b�N�X
        void DeleteChild(const uint index);
        // �w��n���h���Ŏq�ւ̃A�N�Z�X���폜����
        void DeleteChild(const Handle<Type>& handle);
        // �S�Ă̎q�ւ̃A�N�Z�X���폜����
        void DeleteChildAll(void);

        // �q�v�f�̐�
        // @ Ret  : �q�v�f�̐�
        uint GetChildCount(void) const;
        // �q�v�f����ł����݂��邩
        bool IsChild(void) const;

        // �C���f�b�N�X�Ŏq�ւ̃A�N�Z�X���擾����
        // @ Arg1 : �C���f�b�N�X
        Handle<Type> GetChild(const uint index);
        // �w��n���h���Ŏq�ւ̃A�N�Z�X���擾����
        Handle<Type> GetChild(const Handle<Type>& handle);
        // �S�Ă̎q�ւ̃A�N�Z�X���擾����
        std::vector<Handle<Type>> GetChildAll(void);

    private:
        Handle<Type>              m_parent;  // �e
        std::vector<Handle<Type>> m_childs;  // �q
    };
}


//----- ParentAndChildObject����
namespace EtherEngine {
    // �e��ݒ肷��
    // @ Arg1 : �e�ɐݒ肷��n���h��
    template <ParentAndChildObjectConcept Type>
    void ParentAndChildObject<Type>::SetParent(const Handle<Type>& handle) {
        m_parent = handle;
    }

    // �e�ւ̃A�N�Z�X���폜����
    template <ParentAndChildObjectConcept Type>
    void ParentAndChildObject<Type>::DeleteParent(void) {
        m_parent.DeleteRef();
    }

    // �e�v�f�����݂��邩
    template <ParentAndChildObjectConcept Type>
    bool ParentAndChildObject<Type>::IsParent(void) const {
        return m_parent.GetEnable();
    }

    // �e���擾����
    // @ Ret  : �e�v�f�ւ̃n���h��
    template <ParentAndChildObjectConcept Type>
    Handle<Type> ParentAndChildObject<Type>::GetParent(void) const {
        return m_parent;
    }


    // �q��ǉ�����
    // @ Arg1 : �q�Ƃ��Ēǉ�����n���h��
    template <ParentAndChildObjectConcept Type>
    void ParentAndChildObject<Type>::AddChild(const Handle<Type>& handle) {
        m_childs.push_back(handle);
    }

    // �C���f�b�N�X�Ŏq�ւ̃A�N�Z�X���폜����
    // @ Arg1 : �C���f�b�N�X
    template <ParentAndChildObjectConcept Type>
    void ParentAndChildObject<Type>::DeleteChild(const uint index) {
        m_childs[index].DeleteRef();
    }
    // �w��n���h���Ŏq�ւ̃A�N�Z�X���폜����
    template <ParentAndChildObjectConcept Type>
    void ParentAndChildObject<Type>::DeleteChild(const Handle<Type>& handle) {
        for (int i = 0; i < m_childs.size(); i++) {
            if (m_childs[i] == handle) {
                m_childs[i].DeleteRef();
                return;
            }
        }
    }
    // �S�Ă̎q�ւ̃A�N�Z�X���폜����
    template <ParentAndChildObjectConcept Type>
    void ParentAndChildObject<Type>::DeleteChildAll(void) {
        m_childs.clear();
    }

    // �q�v�f�̐�
    // @ Ret  : �q�v�f�̐�
    template <ParentAndChildObjectConcept Type>
    uint ParentAndChildObject<Type>::GetChildCount(void) const {
        return m_childs.size();
    }
    // �q�v�f����ł����݂��邩
    template <ParentAndChildObjectConcept Type>
    bool ParentAndChildObject<Type>::IsChild(void) const {
        return m_childs.size() > 0;
    }

    // �C���f�b�N�X�Ŏq�ւ̃A�N�Z�X���擾����
    // @ Arg1 : �C���f�b�N�X
    template <ParentAndChildObjectConcept Type>
    Handle<Type> ParentAndChildObject<Type>::GetChild(const uint index) {
        return m_childs[index];
    }
    // �w��n���h���Ŏq�ւ̃A�N�Z�X���擾����
    template <ParentAndChildObjectConcept Type>
    Handle<Type> ParentAndChildObject<Type>::GetChild(const Handle<Type>& handle) {
        for (int i = 0; i < m_childs.size(); i++) {
            if (m_childs[i] == handle) {
                return m_childs[i];
            }
        }
    }
    // �S�Ă̎q�ւ̃A�N�Z�X���擾����
    template <ParentAndChildObjectConcept Type>
    std::vector<Handle<Type>> ParentAndChildObject<Type>::GetChildAll(void) {
        return m_childs;
    }
}


#endif // !I_PARENTANDCHILDOBJECT_H
