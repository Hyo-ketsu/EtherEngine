#include <Base/SceneLoader.h>
#include <Base/DirectoryNameDefine.h>


namespace EtherEngine {
    // �R���X�g���N�^
    SceneLoader::SceneLoader(void) {
    }
    // �f�X�g���N�^
    SceneLoader::~SceneLoader(void) {
    }


    // �V�[���ǉ�
    void SceneLoader::AddScene(const SceneData data) {
        //----- �ǂݍ��݃f�B���N�g���C��
        // @ Memo : Hoge -> Scene/Hoge.dll
        std::string loadSceneName;
        if (data.rfind(".dll") == std::string::npos) {
            loadSceneName = DirectoryDefine::SCENE_DATA + data + ",dll";
        }
        else {
            loadSceneName = DirectoryDefine::SCENE_DATA + data;
        }

        //----- DLL�ǂݍ���
        HMODULE dll = LoadLibrary(loadSceneName.c_str());
        if (dll == nullptr) { throw std::exception("Error!"); }

        //----- �V�[���ǂݍ���
        using InitSceneFunction = void*(__stdcall*)();
        auto InitScene = (InitSceneFunction)GetProcAddress(dll, ETHERENGINE_INIT_SCENE_FUNCTION_LITERAL);
        // @ MEMO : �v���o������֐����Ȃ������ꍇ�̗�O����

        //----- �ǂݍ��񂾃V�[����p���ď��������s��
        m_currentSceneData = data;
        InitScene();
    }
    // �V�[���폜
    void SceneLoader::DeleteScene(const SceneData data) {

    }
    // �V�[���폜
    void SceneLoader::DeleteScene(void) {

    }
    // �V�[���ړ�
    void SceneLoader::MoveScene(const SceneData data) {

    }
}
