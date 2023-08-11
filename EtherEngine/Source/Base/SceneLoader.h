#ifndef I_SCENELOADER_H
#define I_SCENELOADER_H
#include <Base/Singleton.h>
#include <Base/ConceptUtility.h>
#include <Base/Scene.h>


//----- SceneLoader �錾
namespace EtherEngine {
    // �V�[���𑍊�����N���X
    class SceneLoader : public Singleton<SceneLoader> {
    public:
        // �f�X�g���N�^
        ~SceneLoader(void) override;


        // ���݃V�[�����Q�b�^�[
        const std::optional<SceneData>& GetCurrentSceneData(void) const { return m_currentSceneData; }


        // �V�[�����o�^
        // @ Memo : �Ǎ������s��Ȃ��A�����ɃV�[������^���邾���̃����o�֐��ł�
        // @ Arg1 : �ǉ�����V�[��
        // @ Arg2 : �T�u�V�[�����i���݂̃V�[���Ƃ��ēo�^����܂���BDefault : false)
        void RegistryScene(const SceneData data, const bool isSubScene = false);

        
        // �V�[���ǉ�
        // @ Arg1 : �ǉ�����V�[��
        // @ Arg2 : �T�u�V�[�����i���݂̃V�[���Ƃ��ēo�^����܂���BDefault : false�j
        void AddScene(const SceneData data, const bool isSubScene = false);
        // �V�[���폜
        // @ Arg1 : �폜����V�[��
        void DeleteScene(const SceneData data);
        // �V�[���폜
        // @ Memo : �S�ẴV�[���̍폜���s���܂�
        void DeleteScene(void);
        // �V�[���ړ�
        // @ Arg1 : �ړ�����V�[��
        void MoveScene(const SceneData data);


    private:
        // �R���X�g���N�^
        SceneLoader(void);

        
        friend class Singleton<SceneLoader>;

        std::vector<SceneData>   m_sceneData;  // ���ݕێ����Ă���V�[���̏��
        std::optional<SceneData> m_currentSceneData;    // ���ݏ��������Ă���V�[���̏��
    };
}


#endif // !I_SCENELOADER_H
