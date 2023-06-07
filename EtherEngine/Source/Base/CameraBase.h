#ifndef I_CAMERABASE_H
#define I_CAMERABASE_H


//----- CameraBase宣言
namespace EtherEngine {
    // カメラを表現するクラス
    class CameraBase {
    public:
        // コンストラクタ
        CameraBase(void);
        // デストラクタ
        virtual ~CameraBase(void);


        // 座標ゲッター
        Eigen::Vector3f GetPos(void) const { return m_pos; }
        // 座標セッター
        void SetPos(const Eigen::Vector3f& in) { m_pos = in; }
        // 注視点ゲッター
        Eigen::Vector3f GetLook(void) const { return m_look; }
        // 注視点セッター
        void SetLook(const Eigen::Vector3f& in) { m_look = in; }
        // 上方向ゲッター
        Eigen::Vector3f GetUp(void) const { return m_up; }
        // 上方向セッター
        void SetUp(const Eigen::Vector3f& in) { m_up = in; }


        // ビュー行列を取得する
        // @ Ret  : 取得したビュー行列
        // @ Arg1 : 転置も行うか(Default : ture)
        Eigen::Matrix4f GetView(const bool isTranspose = true) const;
        // プロジェクション行列を取得する
        // @ Ret  : 取得したプロジェクション行列
        // @ Arg1 : 転置も行うか(Default : ture)
        Eigen::Matrix4f GetProjection(const bool isTranspose = true) const;

    protected:
        Eigen::Vector3f m_pos;  // 座標
        Eigen::Vector3f m_look; // 注視点
        Eigen::Vector3f m_up;   // 上方向
        float m_fovy;   // 視野角
        float m_aspect; // 画面比率
        float m_near;   // 最短クリップ距離
        float m_far;    // 最長クリップ距離
    };
}


#endif // !I_CAMERABASE_H
