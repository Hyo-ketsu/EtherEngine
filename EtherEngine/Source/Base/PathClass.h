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


        // �J�����g�f�B���N�g���Q�b�^�[
        static std::string GetCurDirectory(void);


        // �g���q�������Ă��邩
        bool HasExtension(void) const;


        // �z���f�B���N�g�������ׂĎ擾����
        std::vector<PathClass> GetDirectory(void) const;


        // �擾
        std::string Get(void) const { return m_path; }
        // �擾
        operator std::string(void) const { return Get(); }

    private:
        std::string m_path; // �ێ����Ă���p�X���
    };
}


#endif // !I_PATHCLASS_H
