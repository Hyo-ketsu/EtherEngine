#include <EtherEngine/FileCreater.h>
#include <Base/EtherEngineUtility.h>
#include <EtherEngine/ProjectMediation.h>


namespace EtherEngine {
    // @ �t�@�C���𐶐��A������(�s���̂ł����)�������s��
    PathClass FileCreate(const std::string& fileName, const PathClass& extension, const PathClass& createDirectory,
        const Utilty::DuplicationNameObjectName& nameRule, const std::string& fileString, bool isCreateDirectory) {
        //----- �t�@�C������
        PathClass createFile = GetFileName(createDirectory / fileName += extension, nameRule);
        if (isCreateDirectory) {
            //----- �f�B���N�g���쐬
            createFile.CreateDirectories();
        }
        else {
            //----- �ʏ�t�@�C���쐬
            createFile.CreateFiles(fileString);
        }

        //----- �e�t�@�C�����Ə���
        do {
            //----- �f�B���N�g������
            if (isCreateDirectory) {
                break;
            }

            //----- �����t�@�C��(�g���q)���Ƃɏ���
            if (extension.Get() == FileDefine::SCENE) {
                break;
            }
            else if (extension.Get() == FileDefine::CPPCLISCRIPT) {
                ProjectMediation::Get()->AddSource(createFile);
                break;
            }
        } while (false);

        //----- �ԋp
        return createFile;
    }
}