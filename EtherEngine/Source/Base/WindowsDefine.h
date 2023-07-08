#ifndef I_WINDOWSDEFINE_H
#define I_WINDOWSDEFINE_H


namespace EtherEngine {
    namespace WindowDefine {
        //----- WindowsのWindow用名称
        namespace Name {
            const std::string GAME_APPLICATION = "EtherEgnine Game";        // ゲーム自体のデフォルト名
            const std::string EDITOR_APPLICATION = "EtherEgnine Engine";    // エンジンの表示名
        }

        //----- その他
        namespace Define {
            const uint MAX_CAPTION_TEXT_SIZE = 255; // キャプションの最大文字長
        }
    }

    namespace ImGuiDefine {
        //----- ImGui等用名称
        namespace Name {
            const std::string WINDOW_MENU = "Mein Menu";
            const std::string WINDOW_SCENE_VIEW = "Scene View";
            const std::string WINDOW_OUTLINER = "Out Liner";
            const std::string WINDOW_DEBUG = "Debug Window";
            const std::string WINDOW_LOG = "Log Window";
        }
    }
}


#endif // !I_WINDOWSDEFINE_H
