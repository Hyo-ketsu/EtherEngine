#include <EngineLibrary/ClassLoader.h>
#include <EngineLibrary/AttributeDefine.h>
#include <EngineLibrary/BaseObject.h>
using namespace System;
using namespace System::Reflection;
using namespace System::IO;
using namespace System::Collections;
using namespace System::Collections::Generic;
using namespace Newtonsoft::Json;


//----- EtherEngineJsonConverter �錾
namespace EtherEngine {
    void EtherEngineJsonConverter::WriteJson(JsonWriter^ writer, Object^ value, JsonSerializer^ serializer) {
        //----- �V���A���C�Y�p�ϐ��錾
        auto serializeFields = ClassLoader::GetClassData(value->GetType(), GetClassDataOption::None, System::Object::typeid);

        //----- �������݂��J�n����
        writer->WriteStartObject();

        //----- �S�ăV���A���C�Y����
        for each (auto serializeField in serializeFields) {
            writer->WritePropertyName(serializeField->Menber->Name);
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


    Object^ EtherEngineJsonConverter::ReadJson(JsonReader^ reader, Type^ objectType, Object^ existingValue, JsonSerializer^ serializer) {
        //----- Json�擾
        auto jsonObject = Newtonsoft::Json::Linq::JObject::Load(reader);

        //----- �^�̐���
        auto newInstance = Activator::CreateInstance(objectType);

        //----- �f�V���A���C�Y�p�ϐ��錾
        auto deserializeFields = ClassLoader::GetClassData(objectType, GetClassDataOption::None, System::Object::typeid);

        //----- 
        for each (auto deserializeField in deserializeFields) {
            Newtonsoft::Json::Linq::JToken^ value;
            if (jsonObject->TryGetValue(deserializeField->Menber->Name, System::StringComparison::OrdinalIgnoreCase, value)) {
                if (jsonObject->TryGetValue(deserializeField->Menber->Name, System::StringComparison::OrdinalIgnoreCase, value)) {
                    //----- �t�B�[���h�p����
                    if (deserializeField->IsField) {
                        auto type = deserializeField->Field->FieldType;
                        if (type->IsPrimitive) {
                            deserializeField->SetValue(newInstance, Convert::ChangeType(value->ToObject(type), type));
                        }
                        else {
                            deserializeField->SetValue(newInstance, value->ToObject(type));
                        }
                        continue;
                    }
                    //----- �v���p�e�B�p����
                    if (deserializeField->IsProperty) {
                        auto type = deserializeField->Property->PropertyType;
                        if (type->IsPrimitive) {
                            deserializeField->SetValue(newInstance, Convert::ChangeType(value->ToObject(type), type));
                        }
                        else {
                            deserializeField->SetValue(newInstance, value->ToObject(type));
                        }
                    }
                }
            }
        }

        return newInstance;
    }


    bool EtherEngineJsonConverter::CanConvert(Type^ objectType) {
        return true;
    }
}


//----- ClassLoader ��`
namespace EtherEngine {
    // �N���X�̏����o�͂���
    String^ ClassLoader::Output(Object^ object) {

        auto serializer = gcnew JsonSerializer();
        serializer->Converters->Add(gcnew EtherEngineJsonConverter());
        auto stringWriter = gcnew StringWriter();
        auto jsonWriter = gcnew JsonTextWriter(stringWriter);
        serializer->Serialize(jsonWriter, object);
        return stringWriter->ToString();
    }
    // �N���X�̏�����͂���
    void ClassLoader::Input(String^ data, Type^ type) {
        // �N���X����Json�ɓ���
        auto serializer = gcnew JsonSerializer();
        serializer->Converters->Add(gcnew EtherEngineJsonConverter());
        auto stringReader = gcnew StringReader(data);
        auto jsonReader = gcnew JsonTextReader(stringReader);
        auto newInstance = serializer->Deserialize(jsonReader, type);
    }
    // �N���X�̊e�t�B�[���h���o�͂���
    List<ClassData^>^ ClassLoader::GetClassData(Type^ out, GetClassDataOption option, Type^ overClass) {
        //----- �ԋp�p�ϐ��錾
        List<ClassData^>^ ret = gcnew List<ClassData^>(0);

        //----- �ϐ��錾
        auto type = out;

        //----- �^�擾
        // @ Memo : �X�[�p�[�N���X��System::Object �܂��͎w�肵���N���X�ɂȂ�܂Ńt�B�[���h���擾��������
        while (type != Object::typeid && type != overClass) {
            //----- ���̌^�̃t�B�[���h�擾
            for each (auto member in type->GetMembers(BindingFlags::GetField | BindingFlags::GetProperty | BindingFlags::SetProperty |
                                                      BindingFlags::DeclaredOnly | BindingFlags::Instance | BindingFlags::FlattenHierarchy |
                                                      BindingFlags::Public | BindingFlags::NonPublic)) {
                //----- �t�B�[���h�̏������s���H
                auto field = dynamic_cast<FieldInfo^>(member);
                if (field != nullptr) {
                    //----- ���̃t�B�[���h�����o�͉\��
                    if (field->IsPublic) {
                        //----- �p�u���b�N�B�������`�F�b�N���o�͂��邩����
                        for each (auto attribute in field->GetCustomAttributes(true)) {
                            //----- ����o�͑���������ΏI���B�ǉ����Ȃ�
                            if (attribute->GetType() == Attribute::NoOutputAttribute::typeid) goto END_FIELD;

                            //----- �I�v�V���� : �G�f�B�^�[��\��������ΏI���B�ǉ����Ȃ�
                            if (option == decltype(option)::Editor) {
                                if (attribute->GetType() == Attribute::NonEditorOutputAttribute::typeid) goto END_FIELD;
                            }
                        }

                        //----- �o�͂ł���B���X�g�ɒǉ�
                        ret->Add(gcnew ClassData(field));
                    }
                    else {
                        //----- ��p�u���b�N�B���o�͑���������΃��X�g�ɒǉ�
                        // @ Memo : ����o�͑����͖������܂�
                        bool isAddList = false; // �ǉ��ł���Ȃ� true 
                        for each (auto attribute in field->GetCustomAttributes(true)) {
                            //----- ���o�͑��������邩
                            if (attribute->GetType() == Attribute::OutputAttribute::typeid) {
                                //----- �ǉ��t���O�𗧂Ă�
                                isAddList = true;
                            }
                            //----- �I�v�V���� : �G�f�B�^�[��\��������ΏI���B�ǉ����Ȃ�
                            if (option == decltype(option)::Editor) {
                                if (attribute->GetType() == Attribute::NonEditorOutputAttribute::typeid) goto END_FIELD;
                            }
                        }

                        //----- �ǉ��ł���Ȃ�ǉ�
                        if (isAddList) {
                            ret->Add(gcnew ClassData(field));
                        }
                    }
                    //----- �v���p�e�B�̏������s���H
                    auto property = dynamic_cast<PropertyInfo^>(member);
                    if (property != nullptr) {
                        //----- Getter,Setter�������Ȃ���Ή������Ȃ�
                        if (property->GetGetMethod() == nullptr || property->GetSetMethod() == nullptr) goto END_FIELD;

                        //----- ���̃v���p�e�B�����o�͉\��
                        if (property->GetGetMethod()->IsPublic && property->GetSetMethod()->IsPublic) {
                            //----- �p�u���b�N�B�������`�F�b�N���o�͂��邩����
                            for each (auto attribute in property->GetCustomAttributes(true)) {
                                //----- ����o�͑���������ΏI���B�ǉ����Ȃ�
                                if (attribute->GetType() == Attribute::NoOutputAttribute::typeid) goto END_FIELD;

                                //----- �I�v�V���� : �G�f�B�^�[��\��������ΏI���B�ǉ����Ȃ�
                                if (option == decltype(option)::Editor) {
                                    if (attribute->GetType() == Attribute::NonEditorOutputAttribute::typeid) goto END_FIELD;
                                }
                            }

                            //----- �o�͂ł���B���X�g�ɒǉ�
                            ret->Add(gcnew ClassData(property));
                        }
                        else {
                            //----- ��p�u���b�N�B���o�͑���������΃��X�g�ɒǉ�
                            // @ Memo : ����o�͑����͖������܂�
                            bool isAddList = false; // �ǉ��ł���Ȃ� true 
                            for each (auto attribute in property->GetCustomAttributes(true)) {
                                //----- ���o�͑��������邩
                                if (attribute->GetType() == Attribute::OutputAttribute::typeid) {
                                    //----- �ǉ��t���O�𗧂Ă�
                                    isAddList = true;
                                }
                                //----- �I�v�V���� : �G�f�B�^�[��\��������ΏI���B�ǉ����Ȃ�
                                if (option == decltype(option)::Editor) {
                                    if (attribute->GetType() == Attribute::NonEditorOutputAttribute::typeid) goto END_FIELD;
                                }
                            }

                            //----- �ǉ��ł���Ȃ�ǉ�
                            if (isAddList) {
                                ret->Add(gcnew ClassData(property));
                            }
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
    // �N���X�̊e�t�B�[���h���o�͂���B���N���X�̂�
    List<ClassData^>^ ClassLoader::GetClassData(Type^ out, GetClassDataOption option) {
        return GetClassData(out, option, out->BaseType);
    }
}
