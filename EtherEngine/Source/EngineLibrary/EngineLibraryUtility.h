#ifndef I_CPPCLIUTILITY_H
#define I_CPPCLIUTILITY_H
#include <Base/ConceptUtility.h>
#include <Base/BaseDefines.h>
#include <Base/EditorException.h>
#include <EngineLibrary/ConvertManageToUnmanage.h>


//----- �ϊ��֐� ��`
namespace EtherEngine {
}


#pragma managed
//----- �֗��֐� ��`
namespace EtherEngine {
#pragma managed
    public ref class EditorUtility {
    public:
        // List����w�肵���C���f�b�N�X�̗v�f���擾����
        // @ Ret  : �擾�����v�f
        // @ Arg1 : ���X�g
        // @ Arg2 : �C���f�b�N�X
        generic <typename Type>
        static Type ListGet(System::Collections::Generic::List<Type>^ list, int index);
    };


    static public ref class MatrixHelper {
    public:
        // 4x4�s��̍s�E��C���f�b�N�X���琔�l���擾����
        // @ Ret  : �擾�����l
        // @ Arg1 : �l���擾����s��
        // @ Arg2 : �s
        // @ Arg3 : ��
        static float GetElement(System::Numerics::Matrix4x4% matrix, int row, int column);
        // 4x4�s��̍s�E��C���f�b�N�X���琔�l��ݒ肷��
        // @ Arg1 : �l��ݒ肷��s��
        // @ Arg2 : �s
        // @ Arg3 : ��
        // @ Arg4 : �ݒ肷��l
        static void SetElement(System::Numerics::Matrix4x4% matrix, int row, int column, float value);
    };
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
        UnmanageMaintainer(UnmanageType& maintainer)
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


        // �ێ����̂��R�s�[���Ď擾����
        UnmanageMaintainer<UnmanageType> GetUnmanageMaintainer(void) {
            return UnmanageMaintainer<UnmanageType>(*m_maintainer);
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
        // �Ώۂ��擾����
        // @ Memo : �Ώۂ�������Η�O���o�͂��܂�
        // @ Ret  : �Ώ�
        UnmanageType* GetPointer(void) {
            if (HasValue() == false) throw EditorException("Error! Non Maintainer");
            return m_maintainer;
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
