#include <EngineLibrary/ClassLoader.h>
#include <EngineLibrary/AttributeDefine.h>
#include <EngineLibrary/BaseObject.h>


//----- EtherEngineJsonConverter �錾
namespace EtherEngine {
    void EtherEngineJsonConverter::WriteJson(Newtonsoft::Json::JsonWriter^ writer, System::Object^ value, Newtonsoft::Json::JsonSerializer^ serializer) {
        using namespace System;
        using namespace System::Reflection;
        using namespace System::Collections::Generic;

        //----- �V���A���C�Y�p�ϐ��錾
        auto serializeFields = ClassLoader::GetClassData(value, System::Object::typeid);

        //----- �������݂��J�n����
        writer->WriteStartObject();

        //----- �S�ăV���A���C�Y����
        for each (auto serializeField in serializeFields) {
            writer->WritePropertyName(serializeField->Name);
            writer->WriteValue(serializeField);
            serializer->Serialize(writer, serializeField->GetValue(value));
        }

        writer->WriteEndObject();
    }


    System::Object^ EtherEngineJsonConverter::ReadJson(Newtonsoft::Json::JsonReader^ reader, System::Type^ objectType, System::Object^ existingValue, Newtonsoft::Json::JsonSerializer^ serializer) {
        using namespace Newtonsoft::Json;

        //----- Json�擾
        auto jsonObject = Linq::JObject::Load(reader);

        //----- �^�̐���
        auto newInstance = System::Activator::CreateInstance(objectType);

        //----- �f�V���A���C�Y�p�ϐ��錾
        auto deserializeFields = ClassLoader::GetClassData(objectType, System::Object::typeid);

        //----- 
        for each (auto deserializeField in deserializeFields) {
            Linq::JToken^ value;
            if (jsonObject->TryGetValue(deserializeField->Name, System::StringComparison::OrdinalIgnoreCase, value)) {
                // Deserialize the property value
                deserializeField->SetValue(newInstance, value->ToObject(deserializeField->FieldType));
            }
        }

        return newInstance;
    }


    bool EtherEngineJsonConverter::CanConvert(System::Type^ objectType) {
        return true;
    }
}


//----- ClassLoader ��`
namespace EtherEngine {
    // �N���X�̏����o�͂���
    System::String^ ClassLoader::Output(System::Object^ object) {
        // @ MEMO : ���
        //----- �N���X���擾
        //auto fields = GetClassData(object, BaseObject::typeid);
        return gcnew System::String("");
    }
    // �N���X�̏�����͂���
    void ClassLoader::Input(System::String^ data, System::Object^ object) {
        // @ MEMO : ���
    }
    // �N���X�̊e�t�B�[���h���o�͂���
    System::Collections::Generic::List<System::Reflection::FieldInfo^>^ ClassLoader::GetClassData(System::Object^ out, System::Type^ overClass) {
        using namespace System;
        using namespace System::Reflection;
        using namespace System::Collections::Generic;

        //----- �ԋp�p�ϐ��錾
        List<FieldInfo^>^ ret = gcnew List<FieldInfo^>(0);

        //----- �ϐ��錾
        Type^ type = out->GetType();

        //----- �^�擾
        // @ Memo : �X�[�p�[�N���X��System::Object �܂��͎w�肵���N���X�ɂȂ�܂Ńt�B�[���h���擾��������
        while (type != Object::typeid && type != overClass) {
            //----- ���̌^�̃t�B�[���h�擾
            for each (auto field in type->GetFields(BindingFlags::Instance | BindingFlags::Public | BindingFlags::NonPublic | BindingFlags::FlattenHierarchy)) {
                //----- ���̃t�B�[���h�����o�͉\��
                if (field->IsPublic) {
                    //----- �p�u���b�N�B����o�͑���������΃��X�g�ɒǉ����Ȃ�
                    for each (auto attribute in field->GetCustomAttributes(true)) {
                        if (attribute->GetType() == Attribute::NoOutputAttribute::typeid) {
                            goto END_FIELD;
                        }
                    }

                    //----- ����o�͑������Ȃ������B���X�g�ɒǉ�
                    ret->Add(field);
                }
                else {
                    //----- ��p�u���b�N�B���o�͑���������΃��X�g�ɒǉ�
                    // @ Memo : ����o�͑����͖������܂�
                    for each (auto attribute in field->GetCustomAttributes(true)) {
                        if (attribute->GetType() == Attribute::OutputAttribute::typeid) {
                            //----- ���o�͑������������B���X�g�ɒǉ�
                            ret->Add(field);
                        }
                    }
                }

                END_FIELD: {}
            }

            //----- �X�[�p�[�N���X�̎擾�A�ݒ�
            type = type->BaseType;
        }

        //----- field���X�[�p�[->�T�u�̏��ɂ��邽�ߔ��]������
        ret->Reverse();

        //----- �ԋp
        return ret;
    }
}
