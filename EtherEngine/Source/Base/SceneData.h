#ifndef I_SCENEDATA_H
#define I_SCENEDATA_H


namespace EtherEngine {
    // 各Scene用の情報を管理するクラス
    //（別個にしたのはGameObjectとうにコンポジションした際にデータのみを保持できている方が良いため）
    class SceneData {
    public:
        // コンストラクタ
        // @ Arg1 : シーン名
        SceneData(const std::string& sceneName);

    private:
        static std::unordered_map<std::string, unsigned long long> ms_sceneNumber;  // シーン名に対応した番号
    };
}


#endif // !I_SCENEDATA_H
