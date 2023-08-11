#ifndef I_PROJECTEDITORDATA_H
#define I_PROJECTEDITORDATA_H
#include <Base/EtherEngineUtility.h>
#include <Base/PathClass.h>
#include <Base/Scene.h>


//----- ProjectEditorData �錾
namespace EtherEngine {
    // �G�f�B�^�[��ł̃f�[�^��ێ����Ă����N���X
    class ProjectEditorData : public IInOuter {
    public:
        // @ MEMO : ��ŏ����̂Ńf�t�H���g��������
        // �R���X�g���N�^
        // @ Arg1 : �J���p�X
        ProjectEditorData(const PathClass& path = "");
        // �f�X�g���N�^
        ~ProjectEditorData(void) {}


        // �O���o��
        Json Output(void) override;
        // �O������
        void Input(const Json& input) override;

    private:
        std::optional<SceneData> m_currentScene;    // ���݊J���Ă���V�[��
    };
}


#endif // !I_PROJECTEDITORDATA_H
