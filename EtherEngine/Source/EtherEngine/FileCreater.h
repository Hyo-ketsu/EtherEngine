#ifndef I_FILECREATER_H
#define I_FILECREATER_H
#include <Base/PathClass.h>
#include <Base/EtherEngineUtility.h>


namespace EtherEngine {
    // @ �t�@�C���𐶐��A������(�s���̂ł����)�������s��
    // @ Ret  : �����t�@�C��
    // @ Arg1 : �t�@�C����
    // @ Arg2 : �t�@�C���g���q
    // @ Arg3 : �t�@�C�������f�B���N�g��
    // @ Arg4 : �t�@�C�������K��
    // @ Arg5 : �������Ƀt�@�C���ɗ^���镶����(Default : "")
    // @ Arg6 : �t�@�C���ł͂Ȃ��f�B���N�g���𐶐����邩(Default : false)
    PathClass FileCreate(const std::string& fileName, const PathClass& extension, const PathClass& createDirectory, 
        const Utilty::DuplicationNameObjectName& nameRule, const std::string& fileString = "", bool isCreateDirectory = false);
}


#endif // !I_FILECREATER_H
