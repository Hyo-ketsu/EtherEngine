#ifndef I_PROJECTDATA_H
#define I_PROJECTDATA_H
#include <Base/PathClass.h>
#include <Base/EtherEngineUtility.h>


//----- ProjectData �錾
namespace EtherEngine {
    // �v���W�F�N�g�Ɋւ���f�[�^��ێ������N���X
    class ProjectData : public IInOuter {
    public:
        // �R���X�g���N�^
        // @ Arg1 : �ǂݍ��݃t�@�C���p�X(Default : �p�X�w��Ȃ�)
        ProjectData(const PathClass& path);
        // �쐬�̂ݍs���R���X�g���N�^
        ProjectData(void) {}


        // �R�}���h�v�����v�g�p�X�Q�b�^�[
        const PathClass& GetCmdPath(void) const { return m_cmdPath; }
        // �R�}���h�v�����v�g�p�X�Z�b�^�[
        void SetCmdPath(const PathClass& in) { m_cmdPath = in; }
        // MSVC�p�X�Q�b�^�[
        const PathClass& GetMsvcPath(void) const { return m_msvcPath; }
        // MSVC�p�X�Z�b�^�[
        void SetMsvcPath(const PathClass& in) { m_msvcPath = in; }
        // VisualStudio�p�X�Z�b�^�[
        const PathClass& GetVisualStudioPath(void) const { return m_visualStudioPath; }
        // VisualStudio�p�X�Q�b�^�[
        void SetVisualStudioPath(const PathClass& in) { m_visualStudioPath = in; }


        // �o�͂���
        Json Output(void) override;
        // ���͂���
        void Input(const Json& input) override;

    private:
        PathClass m_cmdPath;    // �R�}���h�v�����v�g�����݂���p�X
        PathClass m_msvcPath;   // MSVC������p�X
        PathClass m_visualStudioPath;   // VisualStudio�̂���p�X
    };
}


#endif // !I_PROJECTDATA_H
