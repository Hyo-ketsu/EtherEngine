#ifndef I_SCENELOADER_H
#define I_SCENELOADER_H
#include <Base/Singleton.h>
#include <Base/Scene.h>

// @ MEMO : ���i�K�ł́u�����v�ڕW�BDLL���n���āA�Ƃ����̂��l�����邪�ЂƂ܂��`�悳����


//----- SceneLoader�錾
namespace EtherEngine {
    // Scene�݂̂�\������R���Z�v�g
    // @ Temp2 : nullptr�����e���邩
    template <typename T, bool IsNullptr>
    concept SceneConcept = std::is_base_of_v<Scene, T> && (IsNullptr || std::is_null_pointer_v<T>);


    // �V�[���𑍊�����N���X
    class SceneLoader : public Singleton<SceneLoader> {
    public:
        // �f�X�g���N�^
        ~SceneLoader(void) override;


        // �V�[���ǉ�
        // @ Temp : �ǉ�����V�[��
        template <SceneConcept<false> SceneType>
        void AddScene(void);
        // �V�[���폜
        // @ Temp : �폜����V�[��(Default : nullptr_t�B�S�V�[���폜)
        template <SceneConcept<true> SceneType = nullptr_t>
        void DeleteScene(void);
        // �V�[���ړ�
        // @ Temp : �ړ�����V�[��
        template <SceneConcept<false> SceneType>
        [deprecated("������")]
        void MoveScene(void);


    private:
        // �R���X�g���N�^
        SceneLoader(void);


        friend class Singleton<SceneLoader>;
    };
}


//----- SceneLoader����
namespace EtherEngine {
    // �V�[���ǉ�
    // @ Temp : �ǉ�����V�[��
    template <SceneConcept<false> SceneType>
    void SceneLoader::AddScene(void) {

    }
    // �V�[���폜
    // @ Temp : �폜����V�[��(Default : nullptr_t�B�S�V�[���폜)
    template <SceneConcept<true> SceneType>
    void SceneLoader::DeleteScene(void) {

    }
    // �V�[���ړ�
    // @ Temp : �ړ�����V�[��
    template <SceneConcept<false> SceneType>
    void SceneLoader::MoveScene(void) {
    }
}


#endif // !I_SCENELOADER_H
