#include <EtherEngine/FileDeleter.h>
#include <Base/BaseDefines.h>
#include <EtherEngine/ProjectMediation.h>


//----- FileDelete �錾
namespace EtherEngine {
    // ���̓t�@�C���E�f�B���N�g�����폜����
    bool FileDelete(const PathClass& deleteFile, bool isRecursion) {
        //----- �t�@�C�����݃`�F�b�N
        if (deleteFile.IsExists() == false) return false;

        //----- �g���q�擾
        auto extension = deleteFile.GetExtension();

        //----- �e�t�@�C�����Ə���
        do {
            //----- �f�B���N�g���E��g���q�폜
            if (deleteFile.IsDirectory()) {
                return deleteFile.Delete_File(isRecursion);
            }

            //----- �ʏ�t�@�C������
            if (extension == FileDefine::Extended::SCENE) {
            }
            if (extension == FileDefine::Extended::SCRIPT) {
                ProjectMediation::Get()->DeleteSource(deleteFile);
            }

            //----- �폜����
            return deleteFile.Delete_File();
        } while (false);
    }
}
