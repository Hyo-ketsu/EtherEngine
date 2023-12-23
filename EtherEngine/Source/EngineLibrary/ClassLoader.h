#ifndef I_CLASSLOADER_H
#define I_CLASSLOADER_H
#include <EngineLibrary/EngineLibraryDefine.h>


//----- ClassLoader �錾
namespace EtherEngine {
    // �w�肵���N���X����o�͂���N���X
    public ref class ClassLoader {
    public:
        // �N���X�̏����o�͂���
        // @ Arg1 : �o�͐�
        // @ Arg2 : �o�͂���^�̎��ۂ̃f�[�^
        static void Output(PathString path, System::Object^ object);
        // �N���X�̏�����͂���
        // @ Arg1 : ���͏��p�X
        // @ Arg2 : ���͂���^�̎��ۂ̃f�[�^
        static void Input(PathString path, System::Object^ object);
        // �N���X�̊e�t�B�[���h���o�͂���
        // @ MEMO : ��Ńv���p�e�B���o�͂��s���悤�ɂ���H
        // @ Arg1 : �o�͂���^
        static System::Collections::Generic::List<System::Object^>^ 
    };
}


#endif // !I_CLASSLOADER_H
