#ifndef I_CLASSLOADER_H
#define I_CLASSLOADER_H
#include <EngineLibrary/EngineLibraryDefine.h>
#include <EngineLibrary/ClassData.h>


//----- EtherEngineJsonConverter �錾
namespace EtherEngine {
    // ���̃G���W����JsonConverter
    public ref class EtherEngineJsonConverter : Newtonsoft::Json::JsonConverter {
    public:
        void WriteJson(Newtonsoft::Json::JsonWriter^ writer, System::Object^ value, Newtonsoft::Json::JsonSerializer^ serializer) override;


        System::Object^ ReadJson(Newtonsoft::Json::JsonReader^ reader, System::Type^ objectType, System::Object^ existingValue, Newtonsoft::Json::JsonSerializer^ serializer)  override;


        bool CanConvert(System::Type^ objectType) override;
    };
}


//----- ClassLoader �錾
namespace EtherEngine {
    // GetClassData�̓��o�̓I�v�V����
    public enum class GetClassDataOption {
        None = 0,   // ���ɂȂ�
        Editor,     // �G�f�B�^�[�ł̕\���E��\�����l��
    };


    // �w�肵���N���X����o�͂���N���X
    public ref class ClassLoader {
    public:
        // �N���X�̏����o�͂���
        // @ Ret  : �o�̓f�[�^
        // @ Arg1 : �o�͂���^�̎��ۂ̃f�[�^
        static System::String^ Output(System::Object^ object);
        // �N���X�̏�����͂���
        // @ MEMO : �擾�ł��Ȃ������t�B�[���h�����擾�ł���悤�ɂ��Ă����ׂ��B
        // @ Arg1 : ���͏��f�[�^
        // @ Arg2 : ���͂���^
        static void Input(System::String^ data, System::Type^ type);
        // �N���X�̊e�t�B�[���h���o�͂���B�X�[�p�[�N���X�̃t�B�[���h���擾����
        // @ Memo : �W����System::Object�̃t�B�[���h�͖������܂�
        // @ Ret  : �o�͂����^�ꗗ
        // @ Arg1 : �o�͂���I�u�W�F�N�g
        // @ Arg2 : �I�v�V����
        // @ Arg3 : �t�B�[���h���擾������E�̃N���X(Hoge->Fuga->Piyo��Piyo���w�肵���ꍇ�AHoge,Fuga�̃t�B�[���h���擾)
        static System::Collections::Generic::List<ClassData^>^ GetClassData(System::Type^ out, GetClassDataOption option, System::Type^ overClass);
        // �N���X�̊e�t�B�[���h���o�͂���B���N���X�̂�
        // @ Memo : �W����System::Object�̃t�B�[���h�͖������܂�
        // @ Ret  : �o�͂����^�ꗗ
        // @ Arg1 : �o�͂���I�u�W�F�N�g
        // @ Arg2 : �I�v�V����
        static System::Collections::Generic::List<ClassData^>^ GetClassData(System::Type^ out, GetClassDataOption option);
    };
}


#endif // !I_CLASSLOADER_H
