#ifndef I_HANDLERAPPER_H
#define I_HANDLERAPPER_H
#include <Base/Handle.h>
#include <Base/HandleHelper.h>


//----- HandleRapper�錾
namespace EtherEngine {
    // ���b�v�ł���^
    // @ Memo : ���^�łȂ��A���L���X�g�ł���
    template <typename T, typename U>
    concept HandleCovertConcept = !(std::is_same_v<U, T>) && std::is_convertible_v<U, T>;


    // �L���X�g���Ďg�p�������n���h�������b�v����N���X
    // @ Temp : �L���X�g��
    template <HandleSystemConcept Type>
    class HandleRapper {
    public:
        // �R���X�g���N�^
        // @ Temp : �L���X�g��̌^
        // @ Arg1 : �ێ�����n���h��
        template <HandleCovertConcept<Type> BaseType>
        HandleRapper(const BaseHandle<BaseType>& handle);
        // �R���X�g���N�^
        // @ Temp : �L���X�g��̌^
        // @ Arg1 : �ێ�����n���h��
        template <HandleCovertConcept<Type> BaseType>
        HandleRapper(BaseHandle<BaseType>&& handle);
        // �f�X�g���N�^
        ~HandleRapper(void);
        // �R�s�[�R���X�g���N�^
        HandleRapper(const HandleRapper& copy) = default;
        // ���[�u�R���X�g���N�^
        HandleRapper(HandleRapper&& move) = default;

        // Handle����r�����䂳��Ă��Ȃ��v�f���擾����
        // @ Ret  : �擾�����v�f
        NonAtomicData<Type> GetNoAtomicItem(void) const;
        // Handle����r�����䂳�ꂽ�v�f���擾����
        // @ Ret  : �擾�����v�f
        AtomicData<Type> GetAtomicItem(void) const;
        // Handle����r�����䂳�ꂽ�ǂݎ���p�v�f���擾����
        // @ Ret  : �擾�����v�f
        AtomicReadData<Type> GetAtomicReadItem(void) const;

        // Handle����r�����䂳��Ă��Ȃ��v�f�𒼐ڎ擾����
        // @ Ret  : �擾�����v�f
        Type& GetNoAtomicData(void) const;
        // Handle����r�����䂳�ꂽ�v�f�𒼐ڎ擾����
        // @ Ret  : �擾�����v�f
        Type& GetAtomicData(void) const;
        // Handle����r�����䂳�ꂽ�ǂݎ���p�v�f�𒼐ڎ擾����
        // @ Ret  : �擾�����v�f
        Type& GetAtomicReadData(void) const;

    private:
        Handle<Type> m_handle;  // �ێ����Ă���n���h��
    };
}




//----- HandleRapper����
namespace EtherEngine {
    // �R���X�g���N�^
    // @ Temp : �L���X�g��̌^
    // @ Arg1 : �ێ�����n���h��
    template <HandleSystemConcept Type>
    template <HandleCovertConcept<Type> BaseType>
    HandleRapper<Type>::HandleRapper(const BaseHandle<BaseType>& handle) {

    }
    // �R���X�g���N�^
    // @ Temp : �L���X�g��̌^
    // @ Arg1 : �ێ�����n���h��
    template <HandleSystemConcept Type>
    template <HandleCovertConcept<Type> BaseType>
    HandleRapper<Type>::HandleRapper(BaseHandle<BaseType>&& handle) {

    }
    // �f�X�g���N�^
    template <HandleSystemConcept Type>
    HandleRapper<Type>::~HandleRapper(void) {

    }


    // Handle����r�����䂳��Ă��Ȃ��v�f���擾����
    // @ Ret  : �擾�����v�f
    template <HandleSystemConcept Type>
    NonAtomicData<Type> HandleRapper<Type>::GetNoAtomicItem(void) const {
        NonAtomicData<Type>() m_handle.GetAtomicItem()
    }
    // Handle����r�����䂳�ꂽ�v�f���擾����
    // @ Ret  : �擾�����v�f
    template <HandleSystemConcept Type>
    AtomicData<Type> HandleRapper<Type>::GetAtomicItem(void) const {
        AtomicData<Type>()
    }
    // Handle����r�����䂳�ꂽ�ǂݎ���p�v�f���擾����
    // @ Ret  : �擾�����v�f
    template <HandleSystemConcept Type>
    AtomicReadData<Type> HandleRapper<Type>::GetAtomicReadItem(void) const {

    }

    // Handle����r�����䂳��Ă��Ȃ��v�f�𒼐ڎ擾����
    // @ Ret  : �擾�����v�f
    template <HandleSystemConcept Type>
    Type& HandleRapper<Type>::GetNoAtomicData(void) const {

    }
    // Handle����r�����䂳�ꂽ�v�f�𒼐ڎ擾����
    // @ Ret  : �擾�����v�f
    template <HandleSystemConcept Type>
    Type& HandleRapper<Type>::GetAtomicData(void) const {

    }
    // Handle����r�����䂳�ꂽ�ǂݎ���p�v�f�𒼐ڎ擾����
    // @ Ret  : �擾�����v�f
    template <HandleSystemConcept Type>
    Type& HandleRapper<Type>::GetAtomicReadData(void) const {

    }
}


#endif // !I_HANDLERAPPER_H
