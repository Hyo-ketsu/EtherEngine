#ifndef I_SCENEG_H
#define I_SCENEG_H

// @ MEMO : 現状この形で実装しています。要改修


//----- Scene 宣言
namespace EtherEngine {
    // シーンを表現するクラス
    class Scene {
        // コンストラクタ
        Scene(void);


        // 初期化関数
        virtual void Start(void) = 0;
    };
}


#endif // !I_SCENEG_H
