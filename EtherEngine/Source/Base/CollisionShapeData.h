#ifndef I_COLLISIONSHAPEDATA_H
#define I_COLLISIONSHAPEDATA_H


//----- �񋓑� ��`
namespace EtherEngine {
    //----- �����蔻��̌`��
    enum class CollisionShape {
        Ray = 0,   // ���C(����)
        Sphere,    // ��
        Capsule,   // �J�v�Z��
        Box,       // ��(OBB)
        Mesh,      // ���b�V��
    };
}


//----- �e�`��f�[�^
namespace EtherEngine {
    //----- Ray
    namespace Collision {
        // ���̓����蔻��̂��߂̏��
        struct Ray {
            // �R���X�g���N�^
            // @ Arg1 : ���̏I�_�ւ̒P�ʃx�N�g��(Default : {0.0f, 1.0f, 0.0f})
            // @ Arg2 : ���̒���(Default : 1.0f)
            Ray(const Eigen::Vector3f& end = { 0.0f,1.0f,0.0f }, const float& length = 1.0f) : m_end(end), m_length(length) {}


            Eigen::Vector3f m_end;  // ���̏I�_�ւ̒P�ʃx�N�g��
            float m_length;         // ���̒���
        };
    }


    //----- Sphere
    namespace Collision {
        // ���̓����蔻��̂��߂̏��
        struct Sphere {
            // �R���X�g���N�^
            // @ Arg1 : ���̔��a(Default : 1.0f)
            Sphere(const float& radius = 1.0f) : m_radius(radius) {}

            float m_radius; // ���̔��a
        };
    }

    //----- Capsule
    namespace Collision {
        // �J�v�Z���̓����蔻��̂��߂̏��
        struct Capsule {
            // �R���X�g���N�^
            // @ Arg1 : �J�v�Z���̑傫��(Default : 1.0f)
            // @ Arg2 : �J�v�Z����(Default : 1.0f)
            Capsule(const float& radius = 1.0f, const float& size = 1.0f) : m_radius(radius), m_size(size) {}


            float m_radius; // �J�v�Z���̑傫��
            float m_size;   // �J�v�Z����
        };
    }


    //----- Box
    namespace Collision {
        // ��(OBB)�̓����蔻��̂��߂̏��
        struct Box {
            // �R���X�g���N�^
            // @ Arg1 : Box�̑傫��(Default : {1.0f,1.0f,1.0f})
            Box(const Eigen::Vector3f& size = { 1.0f,1.0f,1.0f }) : m_size(size) {}


            Eigen::Vector3f m_size;   // Box�̑傫��
        };
    }


    //----- Mesh
    // @ MEMO : ���
    namespace Collision {
        // ���b�V���̓����蔻��
        struct Mesh {
        };
    }
}


//----- CollisionData�錾
namespace EtherEngine {
    namespace Collision {
        // �R���W�����̏����i�[����N���X
        struct CollisionData {
            // �R���X�g���N�^
            // @ Temp1: �ǂ̌`��
            // @ Args : �������Ɏg�p����ϐ�
            template <CollisionShape Shape, class ...Args>
            CollisionData(Args ...args);
            // �R���X�g���N�^
            // @ Arg1 : �ǂ̌`��
            // @ Args : �������Ɏg�p����ϐ�
            template <class ...Args>
            CollisionData(CollisionShape shape, Args ...args);
            ~CollisionData(void) = default;
            CollisionData(const CollisionData& copy) = default;
            CollisionData(CollisionData&& move) = default;


            // �R���W�����f�[�^������
            // @ Temp1: �ǂ̌`��
            // @ Args : �������Ɏg�p����ϐ�
            template <CollisionShape Shape, class ...Args>
            void SetCollisionData(Args ...args);
            // �R���X�g���N�^
            // @ Arg1 : �ǂ̌`��
            // @ Args : �������Ɏg�p����ϐ�
            template <class ...Args>
            void SetCollisionData(CollisionShape shape, Args ...args);


            // �e�R���W�����f�[�^
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




//----- CollisionData��`
namespace EtherEngine {
    namespace Collision {
        // �R���X�g���N�^
        // @ Arg1 : �ǂ̌`��
        // @ Args : �������Ɏg�p����ϐ�
        template <CollisionShape Shape, class ...Args>
        CollisionData::CollisionData(Args ...args) 
            : m_data(0) {
            this->SetCollisionData<Shape, Args...>(args...);
        }
        // �R���X�g���N�^
        // @ Arg1 : �ǂ̌`��
        // @ Args : �������Ɏg�p����ϐ�
        template <class ...Args>
        CollisionData::CollisionData(CollisionShape shape, Args ...args) 
            : m_data(0) {
            this->SetCollisionData<Args...>(shape, args...);
        }


        // �R���W�����f�[�^������
        // @ Temp1: �ǂ̌`��
        // @ Args : �������Ɏg�p����ϐ�
        template <CollisionShape Shape, class ...Args>
        void CollisionData::SetCollisionData(Args ...args) {
            //----- Ray
            if constexpr (CollisionShape::Ray == Shape) {
                //----- �A�T�[�g
                static_assert(std::is_constructible_v<Ray, args...>, "Error! CollisionData Init Ray");

                //----- ������
                m_data.ray = Ray(args...);
            }
            //----- Sphere
            else if constexpr (CollisionShape::Sphere == Shape) {
                //----- �A�T�[�g
                static_assert(std::is_constructible_v<Sphere, args...>, "Error! CollisionData Init Sphere");

                //----- ������
                m_data.sphere = Sphere(args...);
            }
            //----- Capsule
            else if constexpr (CollisionShape::Capsule == Shape) {
                //----- �A�T�[�g
                static_assert(std::is_constructible_v<Capsule, args...>, "Error! CollisionData Init Capsule");

                //----- ������
                m_data.capsule = Capsule(args...);
            }
            //----- Box
            else if constexpr (CollisionShape::Box == Shape) {
                //----- �A�T�[�g
                static_assert(std::is_constructible_v<Box, args...>, "Error! CollisionData Init Box");

                //----- ������
                m_data.box = Box(args...);
            }
            //----- Mesh
            else if constexpr (CollisionShape::Mesh == Shape) {
                //----- �A�T�[�g
                static_assert(std::is_constructible_v<Mesh, args...>, "Error! CollisionData Init Mesh");

                //----- ������
                m_data.mesh = Mesh(args...);
            }
        }
        // �R���X�g���N�^
        // @ Arg1 : �ǂ̌`��
        // @ Args : �������Ɏg�p����ϐ�
        template <class ...Args>
        void CollisionData::SetCollisionData(CollisionShape shape, Args ...args) {
            switch (shape) {
            case EtherEngine::CollisionShape::Ray:
                //----- �A�T�[�g
                static_assert(std::is_constructible_v<Ray, args...>, "Error! CollisionData Init Ray");

                //----- ������
                m_data.ray = Ray(args...);
                break;
            case EtherEngine::CollisionShape::Sphere:
                //----- �A�T�[�g
                static_assert(std::is_constructible_v<Sphere, args...>, "Error! CollisionData Init Sphere");

                //----- ������
                m_data.sphere = Sphere(args...);
                break;
            case EtherEngine::CollisionShape::Capsule:
                //----- �A�T�[�g
                static_assert(std::is_constructible_v<Capsule, args...>, "Error! CollisionData Init Capsule");

                //----- ������
                m_data.capsule = Capsule(args...);
                break;
            case EtherEngine::CollisionShape::Box:
                //----- �A�T�[�g
                static_assert(std::is_constructible_v<Box, args...>, "Error! CollisionData Init Box");

                //----- ������
                m_data.box = Box(args...);
                break;
            case EtherEngine::CollisionShape::Mesh:
                //----- �A�T�[�g
                static_assert(std::is_constructible_v<Mesh, args...>, "Error! CollisionData Init Mesh");

                //----- ������
                m_data.mesh = Mesh(args...);
                break;
            }
        }
    }
}


#endif // !I_COLLISIONSHAPEDATA_H
