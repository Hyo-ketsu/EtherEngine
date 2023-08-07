#ifndef I_PROJECTDATA_H
#define I_PROJECTDATA_H
#include <Base/PathClass.h>


//----- ProjectData �錾
namespace EtherEngine {
    // �v���W�F�N�g�Ɋւ���f�[�^��ێ������N���X
    class ProjectData {
    public:
        // @ MEMO : ����t�@�C������Ǎ�����@�\�͍쐬���Ă��܂���B��ō���Ă�������
        // �R���X�g���N�^
        // @ Arg1 : �ǂݍ��݃t�@�C���p�X(Default : �p�X�w��Ȃ�)
        ProjectData(const PathClass& path = PathClass(""));


        // �R�}���h�v�����v�g�p�X�Q�b�^�[
        const PathClass& GetCmdPath(void) const { return m_cmdPath; }
        // �R�}���h�v�����v�g�p�X�Z�b�^�[
        void SetCmdPath(const PathClass& in) { m_cmdPath = in; }

        // MSVC�p�X�Q�b�^�[
        const PathClass& GetMsvcPath(void) const { return m_msvcPath; }
        // MSVC�p�X�Z�b�^�[
        void SetMsvcPath(const PathClass& in) { m_msvcPath = in; }

    private:
        PathClass m_cmdPath;    // �R�}���h�v�����v�g�����݂���p�X
        PathClass m_msvcPath;   // MSVC������p�X
    };
}


#endif // !I_PROJECTDATA_H
