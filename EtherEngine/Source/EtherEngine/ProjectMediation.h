#ifndef I_PROJECTMEDIATION_H
#define I_PROJECTMEDIATION_H
#include <Base/Singleton.h>
#include <Base/PathClass.h>


#pragma unmanaged
//----- ProjectMediation �錾
namespace EtherEngine {
    // vcxproj���Ƃ̒�����s���N���X
    // @ MEMO : ���݂̓G���W���N�����͋����I�Ɂu�X�V����Ă���v���̂Ƃ��܂��i�̂��ɂ��̃t�@�C���󋵂��G�N�X�|�[�g�ł���悤�ɂ���H�j
    class ProjectMediation : public Singleton<ProjectMediation> {
    public:
        // �f�X�g���N�^
        ~ProjectMediation(void);
        

        // �v���W�F�N�g�t�@�C���Q�b�^�[
        PathClass GetVcxproj(void) const { return m_vcxproj; }
        // �\�����[�V�����t�@�C���Q�b�^�[
        PathClass GetSln(void) const { return m_sln; }

        // �t�@�C���X�V���Q�b�^�[
        bool GetIsUpdateFile(void) const { return m_isUpdateFile; }


        // ����������
        // @ Arg1 : �\�����[�V����
        // @ Arg2 : �v���W�F�N�g�t�@�C��
        void Init(const PathClass& sln, const PathClass& vcxproj);
        // �I������
        void Uninit(void);


        // �t�@�C�����v���W�F�N�g�ɒǉ�����
        // @ Ret  : �ǉ����s��ꂽ��
        // @ Arg1 : ���̓t�@�C��(.h��������.cpp)
        bool AddSource(const PathClass& source);
        // �t�@�C�����v���W�F�N�g����폜����
        // @ Ret  : �폜���s��ꂽ��
        // @ Arg1 : �폜�t�@�C��(.h��������.cpp)
        bool DeleteSource(const PathClass& source);


        // �A�Z���u�������t���b�V������
        // @ Ret  : ����������
        bool RefreshAssembly(void);
        // �A�Z���u�����������t���b�V������
        // @ Ret  : ����������
        bool CoercionRefreshAssembly(void);


        // �X�V���X�V
        // @ Memo : �X�V���łɍX�V������Ă��邩�����肵�܂�(���ʂ�GetIsUpdateFile�Ŋm�F�\)�B
        void FileUpdateDataUpdate(void);

    private:
        // �R���X�g���N�^
        ProjectMediation(void);

        friend class Singleton<ProjectMediation>;

        bool m_isUpdateFile;    // �t�@�C�����X�V����Ă��邩
        PathClass m_vcxproj;    // �v���W�F�N�g�t�@�C��
        PathClass m_sln;        // �\�����[�V�����t�@�C��
        std::vector<std::string> m_projectFile;   // �v���W�F�N�g�Ɋ܂܂�Ă���.h��.cpp
        std::unordered_map<std::string, SYSTEMTIME> m_projectFileTime;    // �v���W�F�N�g�Ɋ܂܂�Ă���t�@�C���̍ŏI�X�V��
    };
}


#endif // !I_PROJECTMEDIATION_H
