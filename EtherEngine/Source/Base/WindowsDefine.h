#ifndef I_WINDOWSDEFINE_H
#define I_WINDOWSDEFINE_H


namespace EtherEngine {
    namespace WindowDefine {
        //----- Windows��Window�p����
        namespace Name {
            const std::string GAME_APPLICATION = "EtherEngine Game";  // �Q�[�����̂̃f�t�H���g��
            const std::string EDITOR_APPLICATION = "Ether Engine";    // �G���W���̕\����
        }

        //----- ���̑�
        namespace Define {
            const uint MAX_CAPTION_TEXT_SIZE = 255; // �L���v�V�����̍ő啶����
        }
    }

    namespace ImGuiDefine {
        //----- ImGui���p����
        namespace Name {
            const std::string WINDOW_MENU = "Mein Menu";
            const std::string WINDOW_SCENE_VIEW = "Scene View";
            const std::string WINDOW_OUTLINER = "Out Liner";
            const std::string WINDOW_EXPLORER = "Explorer";
            const std::string WINDOW_DEBUG = "Debug Window";
            const std::string WINDOW_LOG = "Log Window";
            const std::string WINDOW_INSPECTOR = "Inspector";

            const std::string WINDOW_BUILD_MENU = "Build";

            const std::string WINDOW_EXPLORER_HIERARCHY = ImGuiDefine::Name::WINDOW_EXPLORER + " HierarchyView";
            const std::string WINDOW_EXPLORER_CONTENTS = ImGuiDefine::Name::WINDOW_EXPLORER + " ContentsView";
        }
    }
}


#endif // !I_WINDOWSDEFINE_H
