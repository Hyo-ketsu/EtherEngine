#ifndef I_COLLISIONSHAPEDATA_H
#define I_COLLISIONSHAPEDATA_H


//----- 列挙体 定義
namespace EtherEngine {
    //----- 当たり判定の形状
    enum class CollisionShape {
        Ray = 0,   // レイ(直線)
        Sphere,    // 球
        Capsule,   // カプセル
        Box,       // 箱(OBB)
        Mesh,      // メッシュ
    };
}


//----- 各形状データ
namespace EtherEngine {
    //----- Ray
    namespace Collision {
        // 線の当たり判定のための情報
        struct Ray {
            // コンストラクタ
            // @ Arg1 : 線の終点への単位ベクトル(Default : {0.0f, 1.0f, 0.0f})
            // @ Arg2 : 線の長さ(Default : 1.0f)
            Ray(const Eigen::Vector3f& end = { 0.0f,1.0f,0.0f }, const float& length = 1.0f) : m_end(end), m_length(length) {}


            Eigen::Vector3f m_end;  // 線の終点への単位ベクトル
            float m_length;         // 線の長さ
        };
    }


    //----- Sphere
    namespace Collision {
        // 球の当たり判定のための情報
        struct Sphere {
            // コンストラクタ
            // @ Arg1 : 球の半径(Default : 1.0f)
            Sphere(const float& radius = 1.0f) : m_radius(radius) {}

            float m_radius; // 球の半径
        };
    }

    //----- Capsule
    namespace Collision {
        // カプセルの当たり判定のための情報
        struct Capsule {
            // コンストラクタ
            // @ Arg1 : カプセルの大きさ(Default : 1.0f)
            // @ Arg2 : カプセル長(Default : 1.0f)
            Capsule(const float& radius = 1.0f, const float& size = 1.0f) : m_radius(radius), m_size(size) {}


            float m_radius; // カプセルの大きさ
            float m_size;   // カプセル長
        };
    }


    //----- Box
    namespace Collision {
        // 箱(OBB)の当たり判定のための情報
        struct Box {
            // コンストラクタ
            // @ Arg1 : Boxの大きさ(Default : {1.0f,1.0f,1.0f})
            Box(const Eigen::Vector3f& size = { 1.0f,1.0f,1.0f }) : m_size(size) {}


            Eigen::Vector3f m_size;   // Boxの大きさ
        };
    }


    //----- Mesh
    // @ MEMO : 後回し
    namespace Collision {
        // メッシュの当たり判定
        struct Mesh {
        };
    }
}


//----- CollisionData宣言
namespace EtherEngine {
    namespace Collision {
        // コリジョンの情報を格納するクラス
        struct CollisionData {
            // コンストラクタ
            // @ Temp1: どの形状か
            // @ Args : 初期化に使用する変数
            template <CollisionShape Shape, class ...Args>
            CollisionData(Args ...args);
            // コンストラクタ
            // @ Arg1 : どの形状か
            // @ Args : 初期化に使用する変数
            template <class ...Args>
            CollisionData(CollisionShape shape, Args ...args);
            ~CollisionData(void) = default;
            CollisionData(const CollisionData& copy) = default;
            CollisionData(CollisionData&& move) = default;


            // コリジョンデータ初期化
            // @ Temp1: どの形状か
            // @ Args : 初期化に使用する変数
            template <CollisionShape Shape, class ...Args>
            void SetCollisionData(Args ...args);
            // コンストラクタ
            // @ Arg1 : どの形状か
            // @ Args : 初期化に使用する変数
            template <class ...Args>
            void SetCollisionData(CollisionShape shape, Args ...args);


            // 各コリジョンデータ
            union {
                int def;
                Ray ray;
                Sphere sphere;
                Capsule capsule;
                Box box;
                Mesh mesh;
            } m_data;
        };
    }
}




//----- CollisionData定義
namespace EtherEngine {
    namespace Collision {
        // コンストラクタ
        // @ Arg1 : どの形状か
        // @ Args : 初期化に使用する変数
        template <CollisionShape Shape, class ...Args>
        CollisionData::CollisionData(Args ...args) 
            : m_data(0) {
            this->SetCollisionData<Shape, Args...>(args...);
        }
        // コンストラクタ
        // @ Arg1 : どの形状か
        // @ Args : 初期化に使用する変数
        template <class ...Args>
        CollisionData::CollisionData(CollisionShape shape, Args ...args) 
            : m_data(0) {
            this->SetCollisionData<Args...>(shape, args...);
        }


        // コリジョンデータ初期化
        // @ Temp1: どの形状か
        // @ Args : 初期化に使用する変数
        template <CollisionShape Shape, class ...Args>
        void CollisionData::SetCollisionData(Args ...args) {
            //----- Ray
            if constexpr (CollisionShape::Ray == Shape) {
                //----- アサート
                static_assert(std::is_constructible_v<Ray, args...>, "Error! CollisionData Init Ray");

                //----- 初期化
                m_data.ray = Ray(args...);
            }
            //----- Sphere
            else if constexpr (CollisionShape::Sphere == Shape) {
                //----- アサート
                static_assert(std::is_constructible_v<Sphere, args...>, "Error! CollisionData Init Sphere");

                //----- 初期化
                m_data.sphere = Sphere(args...);
            }
            //----- Capsule
            else if constexpr (CollisionShape::Capsule == Shape) {
                //----- アサート
                static_assert(std::is_constructible_v<Capsule, args...>, "Error! CollisionData Init Capsule");

                //----- 初期化
                m_data.capsule = Capsule(args...);
            }
            //----- Box
            else if constexpr (CollisionShape::Box == Shape) {
                //----- アサート
                static_assert(std::is_constructible_v<Box, args...>, "Error! CollisionData Init Box");

                //----- 初期化
                m_data.box = Box(args...);
            }
            //----- Mesh
            else if constexpr (CollisionShape::Mesh == Shape) {
                //----- アサート
                static_assert(std::is_constructible_v<Mesh, args...>, "Error! CollisionData Init Mesh");

                //----- 初期化
                m_data.mesh = Mesh(args...);
            }
        }
        // コンストラクタ
        // @ Arg1 : どの形状か
        // @ Args : 初期化に使用する変数
        template <class ...Args>
        void CollisionData::SetCollisionData(CollisionShape shape, Args ...args) {
            switch (shape) {
            case EtherEngine::CollisionShape::Ray:
                //----- アサート
                static_assert(std::is_constructible_v<Ray, args...>, "Error! CollisionData Init Ray");

                //----- 初期化
                m_data.ray = Ray(args...);
                break;
            case EtherEngine::CollisionShape::Sphere:
                //----- アサート
                static_assert(std::is_constructible_v<Sphere, args...>, "Error! CollisionData Init Sphere");

                //----- 初期化
                m_data.sphere = Sphere(args...);
                break;
            case EtherEngine::CollisionShape::Capsule:
                //----- アサート
                static_assert(std::is_constructible_v<Capsule, args...>, "Error! CollisionData Init Capsule");

                //----- 初期化
                m_data.capsule = Capsule(args...);
                break;
            case EtherEngine::CollisionShape::Box:
                //----- アサート
                static_assert(std::is_constructible_v<Box, args...>, "Error! CollisionData Init Box");

                //----- 初期化
                m_data.box = Box(args...);
                break;
            case EtherEngine::CollisionShape::Mesh:
                //----- アサート
                static_assert(std::is_constructible_v<Mesh, args...>, "Error! CollisionData Init Mesh");

                //----- 初期化
                m_data.mesh = Mesh(args...);
                break;
            }
        }
    }
}


#endif // !I_COLLISIONSHAPEDATA_H
