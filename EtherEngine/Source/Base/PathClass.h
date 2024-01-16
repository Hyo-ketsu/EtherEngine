#ifndef I_PATHCLASS_H
#define I_PATHCLASS_H
// @ Memo : std::filesystem���b�v�N���X


//----- PathClass �錾
namespace EtherEngine {
    // std::filesystem::path���b�p�[�N���X
    class PathClass {
    public:
        // �R���X�g���N�^
        // @ Arg1 : �p�X(Default : �w��Ȃ�)
        PathClass(const std::string& path = "");
        // �R���X�g���N�^
        // @ Arg1 : �p�X
        PathClass(const char* path);
        // �f�X�g���N�^
        ~PathClass(void) = default;
        // �R�s�[�R���X�g���N�^
        PathClass(const PathClass& copy) = default;
        // ���[�u�R���X�g���N�^
        PathClass(PathClass&& move) = default;
        // �R�s�[���
        PathClass& operator =(const PathClass& copy) = default;
        // ���[�u���
        PathClass& operator =(PathClass&& move) = default;


        // �g���q�܂߂��t�@�C�����擾
        // @ Ret  : �g���q�܂߂��t�@�C����(�� : Hoge.exe)
        std::string GetFile(void) const;
        // �g���q�܂߂Ȃ��t�@�C�����擾
        // @ Ret  : �g���q�܂߂Ȃ��t�@�C����(�� : Hoge.exe -> Hoge)
        std::string GetFileName(void) const;
        // �f�B���N�g�������擾
        // @ Ret  : �f�B���N�g����
        // @ Ret  : (�� : Hoge/Fuga.exe -> Hoge/     )
        // @ Ret  : (�� : Hoge/Fuga/    -> Hoge/Fuga/)
        // @ Ret  : (�� : Hoge/Fuga     -> Hoge/     )
        PathClass GetDirectory(void) const;
        // �g���q�����擾
        // @ Ret  : �g���q��(�� : exe)
        std::string GetExtension(void) const;



        // ���ݎ��[����Ă���f�B���N�g����S�Đ�������
        // @ Memo : ��Ƃ��āA"Hoge/"�܂ł���Ƃ��āA"Hoge/Fuga/Piyo/foo.txt"��ێ����Ă�����A
        // @ Memo : "Hoge/Fuga","Hoge/Fuga/Piyo/"�𐶐�����
        // @ Ret  : �����ł�����
        bool Create_Directorie(void) const;
        // ���ݎ��[����Ă���f�B���N�g���𐶐�����
        // @ Ret  : �����ł�����
        bool Create_Directory(void) const;
        // ���݊i�[����Ă���p�X�Ńt�@�C���𐶐�����
        // @ Memo : ���Ƀt�@�C��������ꍇ�͐������܂���
        // @ Memo : �r���̊K�w�̃f�B���N�g���͐������܂���
        // @ Ret  : �����ł�����
        // @ Arg1 : ���������t�@�C���ɓn��������(Default : "")
        bool Create_File(const std::string& fileString = "") const;
        // ���݂̃t�@�C���E�f�B���N�g�����폜����
        // @ Ret  : �폜���s��ꂽ��
        // @ Arg1 : �ċA�I�ɍ폜���邩(true : ���g������f�B���N�g���폜�\, false : ���g������f�B���N�g���폜�s�BDefault : false)
        bool Delete_File(const bool isAllRemove = false) const;
        // ���݂̃t�@�C�����R�s�[����
        // @ Ret  : �R�s�[���s��ꂽ��
        // @ Arg1 : �R�s�[��p�X
        bool Copy_File(const PathClass& copyPath) const;


        // �p�X�v�f�ǉ�
        PathClass& operator/=(const std::string & path);
        // �p�X�v�f�ǉ�
        PathClass operator/(const std::string& path) const;
        // �p�X������ǉ�
        PathClass& operator+=(const std::string& string);
        // �p�X������ǉ�
        PathClass operator+(const std::string& string) const;


        // �t�@�C�������݂��Ă��邩
        bool IsExists(void) const;
        // �ʏ�t�@�C����
        bool IsFile(void) const;
        // �f�B���N�g�����@
        bool IsDirectory(void) const;
        // �g���q�������Ă��邩
        bool HasExtension(void) const;


        // �擾
        std::string Get(void) const { return m_path; }
        // �擾
        std::string& Access(void) { return m_path; }
        // �擾
        operator std::string(void) const { return Get(); }
        // �z���f�B���N�g�������ׂĎ擾����
        std::vector<PathClass> GetLowerDirectory(void) const;

    private:
        std::string m_path; // �ێ����Ă���p�X���
    };
}


#endif // !I_PATHCLASS_H
