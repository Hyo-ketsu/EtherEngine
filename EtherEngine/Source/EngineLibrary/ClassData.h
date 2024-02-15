#ifndef I_CLASSDATA_H
#define I_CLASSDATA_H


//----- ClassData ��`
namespace EtherEngine {
    // �t�B�[���h��GetSet�\�ȃv���p�e�B�����b�v����N���X
    public ref class ClassData {
    public:
        // �R���X�g���N�^
        // @ Arg1 : �t�B�[���h���
        ClassData(System::Reflection::FieldInfo^ field);
        // �R���X�g���N�^
        // @ Arg1 : �v���p�e�B���
        ClassData(System::Reflection::PropertyInfo^ property);


        // ���ۂ̒l�̎擾
        System::Object^ GetValue(System::Object^ getInstance);
        // ���ۂ̒l�̐ݒ�
        void SetValue(System::Object^ setInstance, System::Object^ value);


        // �����o�[�̎擾
        property System::Reflection::MemberInfo^ Menber {
            System::Reflection::MemberInfo^ get(void);
        }
        // �t�B�[���h���̎擾
        property System::Reflection::FieldInfo^ Field {
            System::Reflection::FieldInfo^ get(void) { return m_field; }
        }
        // �v���p�e�B���̎擾
        property System::Reflection::PropertyInfo^ Property {
            System::Reflection::PropertyInfo^ get(void) { return m_property; }
        }


        // �ێ����Ă���t�B�[���h�E�v���p�e�B�̌^���擾
        property System::Type^ TypeData {
            System::Type^ get(void);
        }


        // �t�B�[���h��ێ����Ă��邩�H
        property bool IsField {
            bool get(void) { return m_field != nullptr; }
        }
        // �v���p�e�B��ێ����Ă��邩�H
        property bool IsProperty {
            bool get(void) { return m_property != nullptr; }
        }

    private:
        // �R���X�g���N�^
        // @ Arg1 : �t�B�[���h���
        // @ Arg2 : �v���p�e�B���
        ClassData(System::Reflection::FieldInfo^ field, System::Reflection::PropertyInfo^ property);

        System::Reflection::FieldInfo^    m_field;      // �ێ����Ă���t�B�[���h���
        System::Reflection::PropertyInfo^ m_property;   // �ێ����Ă���v���p�e�B���
    };
}


#endif // !I_CLASSDATA_H
