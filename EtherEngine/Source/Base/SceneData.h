#ifndef I_SCENEDATA_H
#define I_SCENEDATA_H


namespace EtherEngine {
    // 各Scene用の情報を管理するクラス
    //（別個にしたのはGameObject等にコンポジションした際にデータのみを保持できている方が良いため）
    class SceneData {
    public:
        // コンストラクタ
        // @ Temp1 : Scene名
        // @ Temp2 : Scene番号
        template <const char* Name, uint Number>
        SceneData(void);

    private:

    };
}


#endif // !I_SCENEDATA_H
