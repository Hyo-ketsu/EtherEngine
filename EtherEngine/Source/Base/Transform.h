#ifndef I_TRANSFORM_H
#define I_TRANSFORM_H


namespace EtherEngine {
    // 座標・回転・拡縮を保持するクラス
    class Transform {
    public:
        // コンストラクタ
        // @ Arg1 : 座標(デフォルト：全て0)
        // @ Arg2 : 拡縮(デフォルト：全て0)
        // @ Arg3 : 回転(デフォルト：全て0)
        Transform(Eigen::Vector3f pos = { 0,0,0 }, Eigen::Vector3f sca = { 1,1,1 }, Eigen::Vector3f rot = { 0,0,0 });


        // 座標を取得する
        // @ Arg1 : 座標
        Eigen::Vector3f& AccessPostion(void) noexcept { return m_postion; }
        // 拡縮を取得する
        // @ Arg1 : 拡縮
        Eigen::Vector3f& AccessScale(void) noexcept { return m_scale; }
        // 回転を取得する
        // @ Arg1 : 回転
        Eigen::Vector3f& AccessRotation(void) noexcept { return m_rotation; }

    private:
        Eigen::Vector3f m_postion;  // 座標
        Eigen::Vector3f m_scale;    // 拡縮
        Eigen::Vector3f m_rotation; // 回転
    };
}


#endif // !I_TRANSFORM_H
