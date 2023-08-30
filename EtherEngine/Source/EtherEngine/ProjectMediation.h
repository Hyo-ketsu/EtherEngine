#ifndef I_PROJECTMEDIATION_H
#define I_PROJECTMEDIATION_H
#include <Base/Singleton.h>
#include <Base/PathClass.h>


//----- ProjectMediation �錾
namespace EtherEngine {
    class ProjectMediation : public Singleton<ProjectMediation> {
    public:
        // �f�X�g���N�^
        ~ProjectMediation(void);
        

        // �v���W�F�N�g�t�@�C���Q�b�^�[
        PathClass GetVcxproj(void) const { return m_vcxproj; }
        // �\�����[�V�����t�@�C���Q�b�^�[
        PathClass GetSln(void) const { return m_sln; }


        // ����������
        // @ Arg1 : �\�����[�V����
        // @ Arg2 : �v���W�F�N�g�t�@�C��
        void Init(const PathClass& sln, const PathClass& vcxproj);
        // �I������
        void Uninit(void);


        // .h��.cpp�����v���W�F�N�g�ɒǉ�����
        // @ Ret  : �ǉ����s��ꂽ��
        // @ Arg1 : ���̓t�@�C��(.h��������.cpp)
        bool AddSource(const PathClass& source);
        // .h��.cpp�����v���W�F�N�g����폜����
        // @ Ret  : �폜���s��ꂽ��
        // @ Arg1 : �폜�t�@�C��(.h��������.cpp)
        bool DeleteSource(const PathClass& source);

    private:
        // �R���X�g���N�^
        ProjectMediation(void);

        friend class Singleton<ProjectMediation>;

        PathClass m_vcxproj;    // �v���W�F�N�g�t�@�C��
        PathClass m_sln;        // �\�����[�V�����t�@�C��
    };
}


#endif // !I_PROJECTMEDIATION_H
