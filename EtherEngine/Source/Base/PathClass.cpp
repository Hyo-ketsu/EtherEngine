#include <Base/PathClass.h>
#include <Base/BaseUtility.h>
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
    PathClass PathClass::GetCurDirectory(void) {
        return PathClass(current_path().string());
    }


    // �g���q�܂߂��t�@�C�����擾
    std::string PathClass::GetFile(void) const {
        return path(m_path).filename().string();
    }
    // �g���q�܂߂Ȃ��t�@�C�����擾
    std::string PathClass::GetFileName(void) const {
        return path(m_path).stem().string();
    }
    // �f�B���N�g�������擾
    PathClass PathClass::GetDirectory(void) const {
        return PathClass(path(m_path).remove_filename().string());
    }
    // �g���q�����擾
    std::string PathClass::GetExtension(void) const {
        return path(m_path).extension().string();
    }


    // ���ݎ��[����Ă���f�B���N�g����S�Đ�������
    bool PathClass::Create_Directorie(void) const {
        return create_directories(path(m_path));
    }
    // ���ݎ��[����Ă���f�B���N�g���𐶐�����
    bool PathClass::Create_Directory(void) const {
        return create_directory(path(m_path));
    }
    // ���݊i�[����Ă���p�X�Ńt�@�C���𐶐�����
    bool PathClass::Create_File(const std::string& fileString) const {
        //----- �ϐ��錾
        path path = m_path;

        //----- �t�@�C�������݂��Ă��邩�`�F�b�N
        if (exists(path)) return false;

        //----- �t�@�C���I�[�v��
        std::ofstream ofs(path);
        if (ofs.is_open() == false) return false;

        //----- ������i�[
        ofs << fileString;

        //----- �ԋp
        return true; 
    }
    // ���݂̃t�@�C���E�f�B���N�g�����폜���܂�
    bool PathClass::Delete_File(const bool isAllRemove) const {
        if (isAllRemove) {
            return remove_all(path(m_path)) > 0;
        }
        else {
            return remove(path(m_path));
        }
    }
    // ���݂̃t�@�C�����R�s�[����
    bool PathClass::Copy_File(const PathClass& copyPath) const {
        //----- �R�s�[���\������
        if (copyPath.IsExists() == false) return false;
        if (this->IsFile() == false) return false;

        //----- �����t�@�C����Ώۃp�X�ɍ쐬
        auto myFileString = Utility::RoadFileAll(m_path);
        (copyPath / this->GetFile()).Create_File(myFileString);

        return true;
    }


    // �p�X�v�f�ǉ�
    PathClass& PathClass::operator/=(const std::string& path) {
        m_path = (std::filesystem::path(m_path) /= path).string();
        return *this;
    }
    // �p�X�v�f�ǉ�
    PathClass PathClass::operator/(const std::string& path) const {
        return PathClass((std::filesystem::path(m_path) /= path).string());
    }
    // �p�X������ǉ�
    PathClass& PathClass::operator+=(const std::string& string)  {
        m_path = (std::filesystem::path(m_path) += string).string();
        return *this;
    }
    // �p�X������ǉ�
    PathClass PathClass::operator+(const std::string& string) const {
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
    // �g���q�������Ă��邩
    bool PathClass::HasExtension(void) const {
        return path(m_path).has_extension();
    }


    // �z���f�B���N�g�������ׂĎ擾����
    std::vector<PathClass> PathClass::GetLowerDirectory(void) const {
        //----- �錾
        std::vector<PathClass> ret;

        //----- �f�B���N�g���łȂ���΂��̂܂ܕԋp
        if (this->IsDirectory() == false) return ret;

        //----- �S�Ẳ��ʃt�@�C���擾
        for (auto& it : directory_iterator(path(m_path))) {
            ret.push_back(path(it).string());
        }

        //----- �ԋp
        return ret;
    }
}
