#ifndef I_CLASSLOADER_H
#define I_CLASSLOADER_H
#include <EngineLibrary/EngineLibraryDefine.h>


//----- ClassLoader �錾
namespace EtherEngine {
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
        // @ Arg2 : ���͂���^�̎��ۂ̃f�[�^
        static void Input(System::String^ data, System::Object^ object);
        // �N���X�̊e�t�B�[���h���o�͂���
        // @ MEMO : ��Ńv���p�e�B���o�͂��s���悤�ɂ���H
        // @ Memo : �W����System::Object�̃t�B�[���h�͖������܂�
        // @ Ret  : �o�͂����^�ꗗ
        // @ Arg1 : �o�͂���I�u�W�F�N�g
        // @ Arg2 : �t�B�[���h���擾������E�̃N���X(Hoge->Fuga->Piyo��Piyo���w�肵���ꍇ�AHoge,Fuga�̃t�B�[���h���擾)
        static System::Collections::Generic::List<System::Reflection::FieldInfo^>^ GetClassData(System::Object^ out, System::Type^ overClass);
    };
}


#endif // !I_CLASSLOADER_H
