#ifndef I_DRAWCOMPONENT_H
#define I_DRAWCOMPONENT_H
#include <Base/ComponentBase.h>


//----- DrawComponent宣言
namespace EtherEngine {
    class DrawComponent : public ComponentBase {
    public:
        using ComponentBase::ComponentBase;

        // 描画処理を行う
        void DrawFuntion(void);

        // ビュー行列ゲッター
        Eigen::Matrix4f GetView(void) const { return m_view; }
        // ビュー行列セッター
        void SetView(const Eigen::Matrix4f& in) { m_view = in; }
        // プロジェクション行列ゲッター
        Eigen::Matrix4f GetProjection(void) const { return m_projection; }
        // プロジェクション行列セッター
        void SetProjection(const Eigen::Matrix4f& in) { m_projection = in; }


    protected:
        // 各プラットフォーム用描画処理
        virtual void DrawPlatformFunction(void) {}
        // 描画処理
        virtual void Draw(void) {}

    private:
        Eigen::Matrix4f m_view; // ビュー行列
        Eigen::Matrix4f m_projection;   // プロジェクション行列
    };
}


#endif // !I_DRAWCOMPONENT_H
