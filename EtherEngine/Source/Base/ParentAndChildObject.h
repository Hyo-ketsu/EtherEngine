#ifndef I_PARENTANDCHILDOBJECT_H
#define I_PARENTANDCHILDOBJECT_H
#include <Base/Handle.h>
#include <Base/HandleHelper.h>


//----- ParentAndChildObject�錾
namespace EtherEngine {
    // �e�q�֌W���N���X�ł݈̂����R���Z�v�g
    // �N���X���Q�Ƃ�|�C���^�ł͂Ȃ�
    template <typename T>
    concept ParentAndChildObjectConcept = std::is_class_v<T> && 
        !(std::is_reference_v<T>) && !(std::is_pointer_v<T>);


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
        template <HandleCountTypeConcept<Type, HandleCountType::Count> HandleType>
        void SetParent(const Handle<Type, HandleCountType::Count>& handle);
        // �e��ݒ肷��
        // @ Arg1 : �e�ɐݒ肷��n���h��
        template <HandleCountTypeConcept<Type, HandleCountType::UnCount> HandleType>
        void SetParent(const Handle<Type, HandleCountType::UnCount>& handle);

        // �e�ւ̃A�N�Z�X���폜����
        void DeleteParent(void);

        // �e�v�f�����݂��邩
        bool IsParent(void) const;

        // �e���擾����
        // @ Ret  : �e�v�f�ւ̃n���h��
        void GetParent(void) const;


        // �q��ǉ�����
        // @ Arg1 : �q�Ƃ��Ēǉ�����n���h��
        template <HandleCountTypeConcept<Type, HandleCountType::Count> HandleType>
        void AddChild(const Handle<Type, HandleCountType::Count>& handle);
        // �q��ǉ�����
        // @ Arg1 : �q�Ƃ��Ēǉ�����n���h��
        template <HandleCountTypeConcept<Type, HandleCountType::UnCount> HandleType>
        void AddChild(const Handle<Type, HandleCountType::UnCount>& handle);

        // �C���f�b�N�X�Ŏq�ւ̃A�N�Z�X���폜����
        // @ Arg1 : �C���f�b�N�X
        void DeleteChild(const uint index);
        // �w��n���h���Ŏq�ւ̃A�N�Z�X���폜����
        template <HandleCountTypeConcept<Type, HandleCountType::Count> HandleType>
        void DeleteChild(const Handle<Type, HandleCountType::Count>& handle);
        // �w��n���h���Ŏq�ւ̃A�N�Z�X���폜����
        template <HandleCountTypeConcept<Type, HandleCountType::UnCount> HandleType>
        void DeleteChild(const Handle<Type, HandleCountType::UnCount>& handle);
        // �S�Ă̎q�ւ̃A�N�Z�X���폜����
        void DeleteChildAll(void);

        // �q�v�f�̐�
        // @ Ret  : �q�v�f�̐�
        uint GetChildCount(void) const;
        // �q�v�f����ł����݂��邩
        bool IsChild(void) const;

        // �C���f�b�N�X�Ŏq�ւ̃A�N�Z�X���擾����
        // @ Arg1 : �C���f�b�N�X
        void GetChild(const uint index);
        // �w��n���h���Ŏq�ւ̃A�N�Z�X���擾����
        template <HandleCountTypeConcept<Type, HandleCountType::Count> HandleType>
        void GetChild(const Handle<Type, HandleCountType::Count>& handle);
        // �w��n���h���Ŏq�ւ̃A�N�Z�X���擾����
        template <HandleCountTypeConcept<Type, HandleCountType::UnCount> HandleType>
        void GetChild(const Handle<Type, HandleCountType::UnCount>& handle);
        // �S�Ă̎q�ւ̃A�N�Z�X���擾����
        void GetChildAll(void);

    private:
        RefHandle<Type>              m_parent;  // �e
        std::vector<RefHandle<Type>> m_child;   // �q
    };
}


//----- ParentAndChildObject����
namespace EtherEngine {
    // �e��ݒ肷��
    // @ Arg1 : �e�ɐݒ肷��n���h��
    template <ParentAndChildObjectConcept Type>
    template <HandleCountTypeConcept<Type, HandleCountType::Count> HandleType>
    void ParentAndChildObject<Type>::SetParent(const Handle<Type, HandleCountType::Count>& handle) {
        SetParent(HandleHelper::GetRefHandle(handle));
    }
    // �e��ݒ肷��
    // @ Arg1 : �e�ɐݒ肷��n���h��
    template <ParentAndChildObjectConcept Type>
    template <HandleCountTypeConcept<Type, HandleCountType::UnCount> HandleType>
    void ParentAndChildObject<Type>::SetParent(const Handle<Type, HandleCountType::UnCount>& handle) {
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

    }

    // �e���擾����
    // @ Ret  : �e�v�f�ւ̃n���h��
    template <ParentAndChildObjectConcept Type>
    void ParentAndChildObject<Type>::GetParent(void) const {

    }


    // �q��ǉ�����
    // @ Arg1 : �q�Ƃ��Ēǉ�����n���h��
    template <ParentAndChildObjectConcept Type>
    template <HandleCountTypeConcept<Type, HandleCountType::Count> HandleType>
    void ParentAndChildObject<Type>::AddChild(const Handle<Type, HandleCountType::Count>& handle) {

    }
    // �q��ǉ�����
    // @ Arg1 : �q�Ƃ��Ēǉ�����n���h��
    template <ParentAndChildObjectConcept Type>
    template <HandleCountTypeConcept<Type, HandleCountType::UnCount> HandleType>
    void ParentAndChildObject<Type>::AddChild(const Handle<Type, HandleCountType::UnCount>& handle) {

    }

    // �C���f�b�N�X�Ŏq�ւ̃A�N�Z�X���폜����
    // @ Arg1 : �C���f�b�N�X
    template <ParentAndChildObjectConcept Type>
    void ParentAndChildObject<Type>::DeleteChild(const uint index) {

    }
    // �w��n���h���Ŏq�ւ̃A�N�Z�X���폜����
    template <ParentAndChildObjectConcept Type>
    template <HandleCountTypeConcept<Type, HandleCountType::Count> HandleType>
    void ParentAndChildObject<Type>::DeleteChild(const Handle<Type, HandleCountType::Count>& handle) {

    }
    // �w��n���h���Ŏq�ւ̃A�N�Z�X���폜����
    template <ParentAndChildObjectConcept Type>
    template <HandleCountTypeConcept<Type, HandleCountType::UnCount> HandleType>
    void ParentAndChildObject<Type>::DeleteChild(const Handle<Type, HandleCountType::UnCount>& handle) {

    }
    // �S�Ă̎q�ւ̃A�N�Z�X���폜����
    template <ParentAndChildObjectConcept Type>
    void ParentAndChildObject<Type>::DeleteChildAll(void) {

    }

    // �q�v�f�̐�
    // @ Ret  : �q�v�f�̐�
    template <ParentAndChildObjectConcept Type>
    uint ParentAndChildObject<Type>::GetChildCount(void) const {

    }
    // �q�v�f����ł����݂��邩
    template <ParentAndChildObjectConcept Type>
    bool ParentAndChildObject<Type>::IsChild(void) const {

    }

    // �C���f�b�N�X�Ŏq�ւ̃A�N�Z�X���擾����
    // @ Arg1 : �C���f�b�N�X
    template <ParentAndChildObjectConcept Type>
    void ParentAndChildObject<Type>::GetChild(const uint index) {

    }
    // �w��n���h���Ŏq�ւ̃A�N�Z�X���擾����
    template <ParentAndChildObjectConcept Type>
    template <HandleCountTypeConcept<Type, HandleCountType::Count> HandleType>
    void ParentAndChildObject<Type>::GetChild(const Handle<Type, HandleCountType::Count>& handle) {

    }
    // �w��n���h���Ŏq�ւ̃A�N�Z�X���擾����
    template <ParentAndChildObjectConcept Type>
    template <HandleCountTypeConcept<Type, HandleCountType::UnCount> HandleType>
    void ParentAndChildObject<Type>::GetChild(const Handle<Type, HandleCountType::UnCount>& handle) {

    }
    // �S�Ă̎q�ւ̃A�N�Z�X���擾����
    template <ParentAndChildObjectConcept Type>
    void ParentAndChildObject<Type>::GetChildAll(void) {

    }
}


#endif // !I_PARENTANDCHILDOBJECT_H
