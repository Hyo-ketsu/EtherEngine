#ifndef I_SCENEG_H
#define I_SCENEG_H

// @ MEMO : 現状この形で実装しています。要改修


//----- Scene定義
namespace EtherEngine {
    // シーンを表現するクラス
    class Scene {
        // コンストラクタ
        Scene(void);

        // 初期化関数
        virtual void Init(void);
    };
}


#endif // !I_SCENEG_H
