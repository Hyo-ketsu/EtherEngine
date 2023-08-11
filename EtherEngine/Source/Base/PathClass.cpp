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


    // �g���q�܂߂��t�@�C�����擾
    std::string PathClass::GetFile(void) const {
        return path(m_path).filename().string();
    }
    // �f�B���N�g�������擾
    PathClass PathClass::GetDirectory(void) const {
        return PathClass(path(m_path).remove_filename().string());
    }
    // �g���q�����擾
    std::string PathClass::GetExtension(void) const {
        return path(m_path).extension().string();
    }


    // �g���q�������Ă��邩
    bool PathClass::HasExtension(void) const {
        return path(m_path).has_extension();
    }


    // ���ݎ��[����Ă���f�B���N�g����S�Đ�������
    bool PathClass::CreateDirectories(void) const {
        return create_directories(path(m_path));
    }


    // �p�X�v�f�ǉ�
    const PathClass PathClass::operator/=(const std::string& path) const {
        return PathClass((std::filesystem::path(m_path) /= path).string());
    }
    // �p�X������ǉ�
    const PathClass PathClass::operator+=(const std::string& string) const {
        return PathClass((std::filesystem::path(m_path) += string).string());
    }


    // �t�@�C�������݂��Ă��邩
    bool PathClass::IsExists(void) const {
        return exists(path(m_path));
    }
    // �ʏ�t�@�C����
    bool PathClass::IsFile(void) const {
        return is_regular_file(path(m_path));
    }
    // �f�B���N�g�����@
    bool PathClass::IsDirectory(void) const {
        return is_directory(path(m_path));
    }


    // �z���f�B���N�g�������ׂĎ擾����
    std::vector<PathClass> PathClass::GetLowerDirectory(void) const {
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
