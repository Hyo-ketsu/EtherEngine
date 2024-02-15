#include <EngineLibrary/ClassData.h>


//----- ClassData ��`
namespace EtherEngine {
    using namespace System;
    using namespace System::Reflection;


    // �R���X�g���N�^
    ClassData::ClassData(FieldInfo^ field, PropertyInfo^ property) 
        : m_field(field)
        , m_property(property) {
        //----- �ǂ��nullptr�B�G���[���o��
        if (m_property != nullptr && m_property->GetGetMethod() == nullptr && m_property->GetSetMethod() == nullptr) {
            throw gcnew Exception("Error! Input is not a field or property!");
        }
    }
    // �R���X�g���N�^
    ClassData::ClassData(System::Reflection::FieldInfo^ field) 
        : ClassData(field, nullptr) {
    }
    // �R���X�g���N�^
    ClassData::ClassData(System::Reflection::PropertyInfo^ property) 
        : ClassData(nullptr, property) {
    }


    // ���ۂ̒l�̎擾
    Object^ ClassData::GetValue(Object^ getInstance) {
        if (m_field != nullptr) {
            return m_field->GetValue(getInstance);
        }
        if (m_property != nullptr) {
            return m_property->GetValue(getInstance);
        }
    }
    // ���ۂ̒l�̐ݒ�
    void ClassData::SetValue(Object^ setInstance, Object^ value) {
        if (m_field != nullptr) {
            return m_field->SetValue(setInstance, value);
        }
        if (m_property != nullptr) {
            return m_property->SetValue(setInstance, value);
        }
    }


    // �����o�[�̎擾
    MemberInfo^ ClassData::Menber::get(void) { 
        if (m_field != nullptr) {
            return m_field;
        }
        if (m_property != nullptr) {
            return m_property;
        }
    }


    System::Type^ ClassData::TypeData::get(void) {
        if (m_field != nullptr) {
            return m_field->FieldType;
        }
        if (m_property != nullptr) {
            return m_property->PropertyType;
        }
    }
}
