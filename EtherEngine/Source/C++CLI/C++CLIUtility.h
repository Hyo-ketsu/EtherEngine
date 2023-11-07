#ifndef I_CPPCLIUTILITY_H
#define I_CPPCLIUTILITY_H
#include <Base/ConceptUtility.h>
#include <Base/BaseDefines.h>


//----- �C���^�t�F�[�X��`
namespace EtherEngine {
    // Serialize, DeserializeInterface
    public interface class ISerializer {
    public:
        // �O���o�͂���
        std::string Serialize(void);
        // �O�����͂���
        void Deserialize(const std::string& input);
    };


    // Inspector�\��Interface
    public interface class IInspectorDrawer {
    public:
        // �\������
        void DrawInspector(void);
    };
}


//----- ������ϊ��֐�
namespace EtherEngine {
    // .NET�������C++������ɕϊ�����
    // @ Ret  : C++������
    // @ Arg1 : .NET������
    std::string ManageToUn(System::String^ manage);
    // C++�������.NET������ɕϊ�����
    // @ Ret  : .NET������
    // @ Arg1 : C++������
    System::String^ UnToManage(const std::string& un);
}


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


//----- Serializer �錾
namespace EtherEngine {
    // Serialize, Deserialize���̂��s���N���X
    public ref class Serializer : public ISerializer {
    public:
        // �O���o�͂���
        std::string Serialize(void) override {
            using namespace System::Reflection;

            //----- �ϐ��錾
            nlohmann::json serialize;   // �o�͂���Json������
            System::Type^ thisType = GetType();

            //----- �S�Ă�Field���擾�A�o�͂���
            auto fields = thisType->GetFields(BindingFlags::NonPublic | BindingFlags::Public | BindingFlags::DeclaredOnly);

            //----- �o�͂���t�B�[���h�𔻒肷��
            for each (auto field in fields) {
                //----- �o�̓t���O�錾
                bool isOutput = false;

                //----- ���J���Ă��邩����
                isOutput = field->IsPublic;

                //----- �w��̑������擾�ł��邩
                auto attributes = field->GetCustomAttributes(true);
                for each (auto attribute in attributes) {
                    if (isOutput) {
                        //----- Public���B����J������
                        if (attribute->GetType() == System::Type::GetType("EtherEngineNonSerializeAttribute")) {
                            //----- ��`����Ă���B���̃��[�v���I��
                            isOutput = false;
                            break;
                        }
                    }
                    else {
                        //----- ��Public���B���J������
                        if (attribute->GetType() == System::Type::GetType("EtherEngineSerializeAttribute")) {
                            //----- ��`����Ă���B���̃��[�v���I��
                            isOutput = true;
                            break;
                        }
                    }
                }

                //----- ���J����̂ł����Json�o��
                Serializer^ iSerialize = dynamic_cast<Serializer^>(field->GetValue(this));
                if (iSerialize != nullptr) {
                    serialize[ManageToUn(thisType->Name)][ManageToUn(field->Name)] = iSerialize->Serialize();
                }
                else {
                    serialize[ManageToUn(thisType->Name)][ManageToUn(field->Name)] = ManageToUn(field->ToString());
                }
            }

            //----- �ԋp
            return serialize.dump(FileDefine::JSON_DUMP_NUMBER_OF_STAGES);
        }
        // �O�����͂���
        void Deserialize(const std::string& input) override {
            using namespace System::Reflection;

            //----- �ϐ��錾
            nlohmann::json serialize = nlohmann::json::parse(input);   // ���͂���Json������
            System::Type^ thisType = GetType();

            //----- �S�Ă�Field���擾�A�o�͂���
            auto fields = thisType->GetFields(BindingFlags::NonPublic | BindingFlags::Public | BindingFlags::Instance);

            //----- �����������R���|�[�l���g�����݂��Ȃ���Γ��͂��Ȃ�
            if (serialize.contains(ManageToUn(thisType->Name)) == false) return;

            //----- �S�Ă�Field�ɑ΂����͂���
            for each (auto field in fields) {
                //----- ����Field�����݂��邩
                if (serialize.contains(ManageToUn(field->Name)) == false) continue;

                //----- ���
                Serializer^ iSerialize = dynamic_cast<Serializer^>(field->GetValue(this));
                if (iSerialize != nullptr) {
                    iSerialize->Deserialize(serialize[ManageToUn(thisType->Name)][ManageToUn(field->Name)]);
                }
                else {
                    try {
                        field->SetValue(this, System::Convert::ChangeType(UnToManage(serialize[ManageToUn(thisType->Name)][ManageToUn(field->Name)]), field->FieldType));
                    }
                    catch (System::InvalidCastException^) {
                    }
                }
            }
        }
    };
}


//----- UnmanageMaintainer �錾
namespace EtherEngine {
    // Unmanage Class �� value class �ŕێ�����N���X
    // @ Memo : �蓮�ŉ���������Ăяo���Ă�������
    template <typename UnmanageType>
    public value class UnmanageMaintainer : ISerializer {
    public:
        // �R���X�g���N�^
        // @ Arg1 : �Ώ�
        UnmanageMaintainer(UnmanageType* maintainer)
            : m_maintainer(maintainer)
            , m_isNew(false) {
        }
        // �R���X�g���N�^
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
            if (HasValue() == false) throw std::exception("Error! Non Maintainer");
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
