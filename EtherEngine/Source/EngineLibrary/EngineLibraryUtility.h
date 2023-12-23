#ifndef I_CPPCLIUTILITY_H
#define I_CPPCLIUTILITY_H
#include <Base/ConceptUtility.h>
#include <Base/BaseDefines.h>
#include <Base/EditorException.h>
#include <EngineLibrary/ConvertManageToUnmanage.h>


//----- ���S�C�����擾�֐� ��`
namespace EtherEngine {
    // ���S�C�������擾����
    // @ Exce : �N���X�������݂��Ȃ�
    // @ Ret  : ���S�C����(Hoge.Fuga)
    // @ Arg1 : �N���X��
    // @ Arg2 : ���Ԗ��̖��O��Ԃ��̗p���邩(Default : 0)�B��Ƃ���"Foo.Hoge", "Bar.Hoge"���A0�Ԃ��w�肷���"Foo.Hoge"���擾����
    // @ Arg3 : System���O��Ԃ��܂߂邩(Default : �܂߂Ȃ��Bfalse)
    std::string GetFullName(const std::string& className, const uint index = 0, const bool isSystem = false);
    // ���S�C�������擾����
    // @ Exce : �N���X�������݂��Ȃ�
    // @ Ret  : ���S�C����(Hoge.Fuga)
    // @ Arg1 : �N���X��
    // @ Arg2 : ���Ԗ��̖��O��Ԃ��̗p���邩(Default : 0)�B��Ƃ���"Foo.Hoge", "Bar.Hoge"���A0�Ԃ��w�肷���"Foo.Hoge"���擾����
    // @ Arg3 : System���O��Ԃ��܂߂邩(Default : �܂߂Ȃ��Bfalse)
    System::String^ GetFullName(System::String^ className, const uint index = 0, const bool isSystem = false);
}




//----- UnmanageMaintainer �錾
namespace EtherEngine {
    // Unmanage Class �� value class �ŕێ�����N���X
    // @ Memo : �蓮�ŉ���������Ăяo���Ă�������
    template <typename UnmanageType>
    public value class UnmanageMaintainer {
    public:
        // �|�C���^��ێ�����R���X�g���N�^
        // @ Arg1 : �Ώ�
        UnmanageMaintainer(UnmanageType* maintainer)
            : m_maintainer(maintainer)
            , m_isNew(false) {
        }
        // �R�s�[��new���s���R���X�g���N�^
        // @ Arg1 : �Ώ�
        UnmanageMaintainer(UnmanageType&& maintainer)
            : m_maintainer(new UnmanageType(maintainer))
            , m_isNew(true) {
        }
        // �������
        void MaintainerClear(void) {
            if (m_isNew == true) {
                delete m_maintainer;
                m_maintainer = nullptr;
            }
            m_isNew = false;
        }


        // �Ώۂ������Ă��邩
        // @ Ret  : �l�������Ă���� true
        bool HasValue(void) {
            return m_maintainer != nullptr;
        }
        // �Ώۂ��擾����
        // @ Memo : �Ώۂ�������Η�O���o�͂��܂�
        // @ Ret  : �Ώ�
        UnmanageType& GetValue(void) {
            if (HasValue() == false) throw EditorException("Error! Non Maintainer");
            return *m_maintainer;
        }
        // �Ώۂ�ݒ肷��
        // @ Arg1 : �Ώ�
        void SetValue(UnmanageType* maintainer) {
            //----- ���g���|�C���^�ŕێ����Ă���A���������|�C���^�ŕێ����Ă��邩�A�A�h���X���Ⴄ�ꍇ�������
            if (m_maintainer != nullptr && m_maintainer != nullptr && m_maintainer != maintainer) MaintainerClear();

            //----- �|�C���^�̕ێ�
            m_maintainer = maintainer;
        }
        // �Ώۂ�ݒ肷��
        // @ Arg1 : �Ώ�
        void SetValue(UnmanageType&& maintainer) {
            //----- ���
            MaintainerClear();

            //----- �ێ�
            m_maintainer = new UnmanageType(maintainer);
        }


        // �O���o�͂���
        std::string Serialize(void) override {
            if constexpr (Concept::BaseOfConcept<UnmanageType, IInOuter>) {
                return dynamic_cast<IInOuter*>(m_maintainer)->Output();
            }
            else {
                return "";
            }
        }
        // �O�����͂���
        void Deserialize(const std::string& input) override {
            if constexpr (Concept::BaseOfConcept<UnmanageType, IInOuter>) {
                dynamic_cast<IInOuter*>(m_maintainer)->InputString(input);
            }
            else {
            }
        }

    private:
        UnmanageType* m_maintainer; // �ێ����Ă���Ώ�
        bool m_isNew;               // �E�Ӓl���󂯎��\�z������
    };
}


#endif // !I_CPPCLIUtility_H
