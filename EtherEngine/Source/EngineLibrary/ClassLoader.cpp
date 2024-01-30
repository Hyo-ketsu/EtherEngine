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
            auto fieldValue = serializeField->GetValue(value);
            if (fieldValue == nullptr) {
                writer->WriteNull();
                continue;
            }
            if (fieldValue->GetType()->IsPrimitive || fieldValue->GetType() == String::typeid) {
                writer->WriteValue(fieldValue);
            }
            else {
                serializer->Serialize(writer, fieldValue);
            }
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
        auto deserializeFields = ClassLoader::GetClassData(newInstance, System::Object::typeid);

        //----- 
        for each (auto deserializeField in deserializeFields) {
            Linq::JToken^ value;
            if (jsonObject->TryGetValue(deserializeField->Name, System::StringComparison::OrdinalIgnoreCase, value)) {
                if (jsonObject->TryGetValue(deserializeField->Name, System::StringComparison::OrdinalIgnoreCase, value)) {
                    if (deserializeField->FieldType->IsPrimitive) {
                        deserializeField->SetValue(newInstance, System::Convert::ChangeType(value->ToObject(deserializeField->FieldType), deserializeField->FieldType));
                    }
                    else {
                        deserializeField->SetValue(newInstance, value->ToObject(deserializeField->FieldType));
                    }
                }
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
        using namespace Newtonsoft::Json;

        auto serializer = gcnew JsonSerializer();
        serializer->Converters->Add(gcnew EtherEngineJsonConverter());
        auto stringWriter = gcnew System::IO::StringWriter();
        auto jsonWriter = gcnew JsonTextWriter(stringWriter);
        serializer->Serialize(jsonWriter, object);
        return stringWriter->ToString();
    }
    // �N���X�̏�����͂���
    void ClassLoader::Input(System::String^ data, System::Type^ type) {
        using namespace Newtonsoft::Json;
        using namespace System;
        using namespace System::IO;
        using namespace System::Collections;
        using namespace System::Collections::Generic;

        // �N���X����Json�ɓ���
        auto serializer = gcnew JsonSerializer();
        serializer->Converters->Add(gcnew EtherEngineJsonConverter());
        auto stringReader = gcnew StringReader(data);
        auto jsonReader = gcnew JsonTextReader(stringReader);
        auto newInstance = serializer->Deserialize(jsonReader, type);
    }
    // �N���X�̊e�t�B�[���h���o�͂���
    System::Collections::Generic::List<System::Reflection::FieldInfo^>^ ClassLoader::GetClassData(System::Object^ out, System::Type^ overClass) {
        using namespace System;
        using namespace System::Reflection;
        using namespace System::Collections::Generic;

        //----- �ԋp�p�ϐ��錾
        List<FieldInfo^>^ ret = gcnew List<FieldInfo^>(0);

        //----- �ϐ��錾
        Type^ type = (out == Type::typeid) ? safe_cast<Type^>(out) : out->GetType(); // out��Type�Ȃ炻�̂܂܎擾�A����ȊO�Ȃ�Type���擾

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
