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
        // �R���X�g���N�^
        // @ Arg1 : �J���p�X
        ProjectEditorData(const PathClass& path);
        // �쐬�̂ݍs���R���X�g���N�^
        ProjectEditorData(void) {}
        // �f�X�g���N�^
        ~ProjectEditorData(void) {}


        // ���݃V�[���Q�b�^�[
        const SceneData& GetCurrentScene(void) const { return m_currentScene; }
        // ���݃V�[���Z�b�^�[
        void SetCurrentScene(const SceneData& in) { m_currentScene = in; }


        // �O���o��
        Json Output(void) override;
        // �O������
        void Input(const Json& input) override;

    private:
        SceneData m_currentScene;    // ���݃V�[��
    };
}


#endif // !I_PROJECTEDITORDATA_H
