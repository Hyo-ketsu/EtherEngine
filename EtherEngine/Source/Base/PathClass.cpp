#include <Base/PathClass.h>
#include <filesystem>


//----- PathClass ��`
namespace EtherEngine {
    using namespace std::filesystem;

    // �R���X�g���N�^
    PathClass::PathClass(const std::string& path) 
        : m_path(path) {
    }
    // �R���X�g���N�^
    PathClass::PathClass(const char* path) 
        : m_path(path) {
    }


    // �J�����g�f�B���N�g���Q�b�^�[
    std::string PathClass::GetCurDirectory(void) {
        return current_path().string();
    }


    // �g���q�������Ă��邩
    bool PathClass::HasExtension(void) const {
        return path(m_path).has_extension();
    }


    // �z���f�B���N�g�������ׂĎ擾����
    std::vector<PathClass> PathClass::GetDirectory(void) const {
        //----- �錾
        std::vector<PathClass> ret;

        //----- �S�Ẳ��ʃt�@�C���擾
        for (auto& it : directory_iterator(path(m_path))) {
            ret.push_back(path(it).string());
        }

        //----- �ԋp
        return ret;
    }
}
