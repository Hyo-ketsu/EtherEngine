#ifndef I_FILEDELETER_H
#define I_FILEDELETER_H
#include <Base/PathClass.h>


//----- FileDelete ��`
namespace EtherEngine {
    // ���̓t�@�C���E�f�B���N�g�����폜����
    // @ Ret  : ���̓t�@�C���E�f�B���N�g�����폜���ꂽ��
    // @ Arg1 : �폜�t�@�C���E�f�B���N�g��
    // @ Arg2 : �����f�B���N�g���폜���A�ċA�I�Ƀf�B���N�g���̍폜���s���B�ʏ�t�@�C�����͖���(Default : ture)
    bool FileDelete(const PathClass& deleteFile, bool isRecursion = true);
}


#endif // !I_FILEDELETER_H
