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
        // @ Arg1 : �ǂݍ��݃t�@�C���p�X
        ProjectData(const PathClass& path);
        // �f�t�H���g�R���X�g���N�^
        ProjectData(void) {}
        // �f�X�g���N�^
        ~ProjectData(void);


        // MSBuild�p�X�Z�b�^�[
        const PathClass& GetMSBuildPath(void) const { return m_msbuildPath; }
        // MSBuild�p�X�Q�b�^�[
        void SetMSBuildPath(const PathClass& in) { m_msbuildPath = in; }


        // �o�͂���
        Json Output(void) override;
        // ���͂���
        void Input(const Json& input) override;

    private:
        PathClass m_msbuildPath;    // MSBuild�̂���p�X
        PathClass m_path;           // ��񎩑̂�ێ����Ă���N���X
    };
}


#endif // !I_PROJECTDATA_H
