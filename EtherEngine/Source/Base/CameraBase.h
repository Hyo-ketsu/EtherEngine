#ifndef I_CAMERABASE_H
#define I_CAMERABASE_H
#include <Base/IDClass.h>
#include <Base/StorageSystem.h>
#include <Base/EtherEngineUtility.h>


//----- CameraData 宣言
namespace EtherEngine {
    // 視野角等のカメラ情報を保持しているクラス
    class CameraData : public IInOuter {
    public:
        // コンストラクタ
        // @ Arg1 : 座標
        // @ Arg2 : 注視点
        CameraData(const Eigen::Vector3f& pos, const Eigen::Vector3f& look);
        // Jsonコンストラクタ
        // @ Arg1 : Json文字列
        CameraData(const std::string& json);
        // デストラクタ
        ~CameraData(void) {}


        // 座標ゲッター
        Eigen::Vector3f GetPos(void) const { return m_pos; }
        // 座標セッター
        void SetPos(const Eigen::Vector3f& in);
        // 注視点ゲッター
        Eigen::Vector3f GetLook(void) const { return m_look; }
        // 注視点セッター
        void SetLook(const Eigen::Vector3f& in);
        // 上方向ゲッター
        Eigen::Vector3f GetUp(void) const { return m_up; }
        // 上方向セッター
        void SetUp(const Eigen::Vector3f& in) { m_up = in; }
        // 優先度ゲッター
        int GetPriority(void) const { return m_priority; }
        // 優先度セッター
        void SetPriority(const int in) { m_priority = in; }
        // 視野角ゲッター
        float GetFovy(void) const { return m_fovy; }
        // 視野角セッター
        void SetFovy(const float in);
        // 画面アスペクト比率ゲッター
        float GetAspect(void) const { return m_aspect; }
        // 画面アスペクト比率セッター
        void SetAspect(const float in);
        // 最短クリップ距離ゲッター
        float GetNear(void) const { return m_near; }
        // 最短クリップ距離セッター
        void SetNear(const float in);
        // 最長クリップ距離ゲッター
        float GetFar(void) const { return m_far; }
        // 最長クリップ距離セッター
        void SetFar(const float in);


        // 外部出力する
        std::string Output(void) override;
        // 外部入力する
        void Input(const std::string& input) override;

    private:
        // 座標と注視点が同座標の場合に例外を出力します
        void CheckPosLookPosition(void) const;

        Eigen::Vector3f m_pos;  // 座標
        Eigen::Vector3f m_look; // 注視点
        Eigen::Vector3f m_up;   // 上方向
        int   m_priority;   // 優先度
        float m_fovy;   // 視野角
        float m_aspect; // 画面アスペクト比率
        float m_near;   // 最短クリップ距離
        float m_far;    // 最長クリップ距離
    };
}


//----- CameraBase 宣言
namespace EtherEngine {
    // カメラを表現するクラス
    class CameraBase : public IInOuter {
    public:
        // コンストラクタ
        // @ Arg1 : 座標
        // @ Arg2 : 注視点
        CameraBase(const Eigen::Vector3f& pos, const Eigen::Vector3f& look);
        // コンストラクタ
        // @ Arg1 : カメラ情報
        CameraBase(const CameraData& data);

        // デストラクタ
        virtual ~CameraBase(void);


        // カメラ情報アクセサー
        CameraData& AccessCameraData(void) { return m_cameraData; }

        // IDゲッター
        const StorageID<CameraBase>& GetID(void) { return m_id; }


        // ビュー行列を取得する
        // @ Ret  : 取得したビュー行列
        // @ Arg1 : 転置も行うか(Default : ture)
        Eigen::Matrix4f GetView(const bool isTranspose = true) const;
        // プロジェクション行列を取得する
        // @ Ret  : 取得したプロジェクション行列
        // @ Arg1 : 転置も行うか(Default : ture)
        Eigen::Matrix4f GetProjection(const bool isTranspose = true) const;


        // 外部出力する
        std::string Output(void) override;
        // 入力する
        void Input(const std::string& input) override;

    private:
        CameraData m_cameraData;        // カメラ情報
        StorageID<CameraBase> m_id;    // このobjectのID
    };
}


#endif // !I_CAMERABASE_H
