#ifndef I_VECTORCONVERTER_H
#define I_VECTORCONVERTER_H


//----- MathConverter宣言
namespace EtherEngine {
    //----- EigenとDXのベクトル・行列変換
    namespace MathConverter {
        // Eigenの2次元のベクトルか
        template <typename T>
        concept Eigen2DVectorConcept = requires(T instans) { instans.x(); instans.y(); };
        // Eigenの3次元のベクトルか
        template <typename T>
        concept Eigen3DVectorConcept = Eigen2DVectorConcept<T> && requires(T instans) { instans.z(); };
        // Eigenの4次元のベクトルか
        template <typename T>
        concept Eigen4DVectorConcept = Eigen3DVectorConcept<T> && requires(T instans) { instans.w(); };

        // Eigenの行列か
        template <typename T>
        concept EigenMatrixConcept = requires(T instans) { instans[0, 0]; };


        // DirectXの2次元ベクトルか
        template <typename T>
        concept DirectX2DVectorConcept = requires(T instans) { instans.x; instans.y; };
        // DirectXの3次元ベクトルか
        template <typename T>
        concept DirectX3DVectorConcept = DirectX2DVectorConcept<T> && requires(T instans) { instans.z; };
        // DirectXの4次元ベクトルか
        template <typename T>
        concept DirectX4DVectorConcept = DirectX2DVectorConcept<T> && requires(T instans) { instans.w; };

        // DirectXの行列か
        template <typename T>
        concept DirectXMatrixConcept = requires(T instans) { instans.m[0][0]; };


        // EigenのベクトルからDirectXのベクトルに代入する
        // @ Arg1 : Eigenのベクトル
        // @ Arg2 : DirectXのベクトル
        template <Eigen2DVectorConcept EigenVec, DirectX2DVectorConcept DXVec = DirectX::XMFLOAT2>
        void EigenToDX(const EigenVec& eigenVec, DXVec* const dxVec);
        // EigenのベクトルからDirectXのベクトルに代入する
        // @ Arg1 : Eigenのベクトル
        // @ Arg2 : DirectXのベクトル
        template <Eigen3DVectorConcept EigenVec, DirectX3DVectorConcept DXVec = DirectX::XMFLOAT3>
        void EigenToDX(const EigenVec& eigenVec, DXVec* const dxVec);
        // EigenのベクトルからDirectXのベクトルに代入する
        // @ Arg1 : Eigenのベクトル
        // @ Arg2 : DirectXのベクトル
        template <Eigen4DVectorConcept EigenVec, DirectX4DVectorConcept DXVec = DirectX::XMFLOAT4>
        void EigenToDX(const EigenVec& eigenVec, DXVec* const dxVec);

        // Eigenの行列をDirectXの行列に変換する
        // @ Arg1 : Eigenの行列
        // @ Arg2 : DirectXの行列
        // @ Arg3 : 次元数(Default : 4)
        template <EigenMatrixConcept EigenMat, DirectXMatrixConcept DXMat = DirectX::XMMATRIX>
        void EigenToDX(const EigenMat& eigenMat, DXMat* const dxMat, const uint dimension = 4);


        // DirectXのベクトルからEigenのベクトルに代入する
        // @ Arg1 : DirectXのベクトル
        // @ Arg2 : Eigenのベクトル
        template <DirectX2DVectorConcept DXVec, Eigen2DVectorConcept EigenVec = Eigen::Vector2f>
        void DXToEigen(const DXVec& dxVec, EigenVec* const eigenVec);
        // DirectXのベクトルからEigenのベクトルに代入する
        // @ Arg1 : DirectXのベクトル
        // @ Arg2 : Eigenのベクトル
        template <DirectX3DVectorConcept DXVec, Eigen3DVectorConcept EigenVec = Eigen::Vector3f>
        void DXToEigen(const DXVec& dxVec, EigenVec* const eigenVec);
        // DirectXのベクトルからEigenのベクトルに代入する
        // @ Arg1 : DirectXのベクトル
        // @ Arg2 : Eigenのベクトル
        template <DirectX4DVectorConcept DXVec, Eigen4DVectorConcept EigenVec = Eigen::Vector4f>
        void DXToEigen(const DXVec& dxVec, EigenVec* const eigenVec);

        // DirectXの行列をEigenの行列に変換する
        // @ Arg1 : DirectXの行列
        // @ Arg2 : Eigenの行列
        // @ Arg3 : 次元数(Default : 4)
        template <DirectXMatrixConcept DXMat, EigenMatrixConcept EigenMat = Eigen::Matrix4f>
        void DXToEigen(const DXMat& dxMat, EigenMat* const eigenMat, const uint dimension = 4);
    }


    //----- XMMATRIXとXMFLOAT4X4変換
    namespace MathConverter {
        // XMMATRIXをXMFLOAT4X4に変換する
        // @ Ret  : 変換されたXMFLOAT4X4
        // @ Arg1 : XMMATRIX
        DirectX::XMFLOAT4X4 MatrixToFloat4x4(const DirectX::XMMATRIX& mat);
    }
}


//----- MathConverter宣言
namespace EtherEngine {
    //----- EigenとDXのベクトル・行列変換
    namespace MathConverter {
        // EigenのベクトルからDirectXのベクトルに代入する
        // @ Arg1 : Eigenのベクトル
        // @ Arg2 : DirectXのベクトル
        template <Eigen2DVectorConcept EigenVec, DirectX2DVectorConcept DXVec>
        void EigenToDX(const EigenVec& eigenVec, DXVec* const dxVec) {
            dxVec->x = eigenVec.x();
            dxVec->y = eigenVec.y();
        }
        // EigenのベクトルからDirectXのベクトルに代入する
        // @ Arg1 : Eigenのベクトル
        // @ Arg2 : DirectXのベクトル
        template <Eigen3DVectorConcept EigenVec, DirectX3DVectorConcept DXVec>
        void EigenToDX(const EigenVec& eigenVec, DXVec* const dxVec) {
            dxVec->x = eigenVec.x();
            dxVec->y = eigenVec.y();
            dxVec->z = eigenVec.z();
        }
        // EigenのベクトルからDirectXのベクトルに代入する
        // @ Arg1 : Eigenのベクトル
        // @ Arg2 : DirectXのベクトル
        template <Eigen4DVectorConcept EigenVec, DirectX4DVectorConcept DXVec>
        void EigenToDX(const EigenVec& eigenVec, DXVec* const dxVec) {
            dxVec->x = eigenVec.x();
            dxVec->y = eigenVec.y();
            dxVec->z = eigenVec.z();
            dxVec->w = eigenVec.w();
        }

        // Eigenの行列をDirectXの行列に変換する
        // @ Arg1 : Eigenの行列
        // @ Arg2 : DirectXの行列
        // @ Arg3 : 次元数(Default : 4)
        template <EigenMatrixConcept EigenMat, DirectXMatrixConcept DXMat>
        void EigenToDX(const EigenMat& eigenMat, DXMat* const dxMat, const uint dimension) {
            for (int i = 0; i < dimension; i++) {
                for (int j = 0; j < dimension; j++) {
                    dxMat->m[i][j] = eigenMat(i, j);
                }
            }
        }


        // DirectXのベクトルからEigenのベクトルに代入する
        // @ Arg1 : DirectXのベクトル
        // @ Arg2 : Eigenのベクトル
        template <DirectX2DVectorConcept DXVec, Eigen2DVectorConcept EigenVec>
        void DXToEigen(const DXVec& dxVec, EigenVec* const eigenVec) {
            eigenVec.x() = dxVec->x;
            eigenVec.y() = dxVec->y;
        }
        // DirectXのベクトルからEigenのベクトルに代入する
        // @ Arg1 : DirectXのベクトル
        // @ Arg2 : Eigenのベクトル
        template <DirectX3DVectorConcept DXVec, Eigen3DVectorConcept EigenVec>
        void DXToEigen(const DXVec& dxVec, EigenVec* const eigenVec) {
            eigenVec.x() = dxVec->x;
            eigenVec.y() = dxVec->y;
            eigenVec.z() = dxVec->z;
        }
        // DirectXのベクトルからEigenのベクトルに代入する
        // @ Arg1 : DirectXのベクトル
        // @ Arg2 : Eigenのベクトル
        template <DirectX4DVectorConcept DXVec, Eigen4DVectorConcept EigenVec>
        void DXToEigen(const DXVec& dxVec, EigenVec* const eigenVec) {
            eigenVec.x() = dxVec->x;
            eigenVec.y() = dxVec->y;
            eigenVec.z() = dxVec->z;
            eigenVec.w() = dxVec->w;
        }

        // DirectXの行列をEigenの行列に変換する
        // @ Arg1 : DirectXの行列
        // @ Arg2 : Eigenの行列
        // @ Arg3 : 次元数(Default : 4)
        template<DirectXMatrixConcept DXMat, EigenMatrixConcept EigenMat>
        void DXToEigen(const DXMat& dxMat, EigenMat* const eigenMat, const uint dimension) {
            for (uint i = 0; i < dimension; i++) {
                for (uint j = 0; j < dimension; j++) {
                    (*eigenMat)(i,j) = dxMat.m[i][j];
                }
            }
        }
    }


    //----- XMMATRIXとXMFLOAT4X4変換
    namespace MathConverter {
        // XMMATRIXをXMFLOAT4X4に変換する
        // @ Ret  : 変換されたXMFLOAT4X4
        // @ Arg1 : XMMATRIX
        DirectX::XMFLOAT4X4 MatrixToFloat4x4(const DirectX::XMMATRIX& mat) {
            DirectX::XMFLOAT4X4 ret;
            DirectX::XMStoreFloat4x4(&ret, mat);
            return std::move(ret);
        }
    }
}


#endif // !I_VECTORCONVERTER_H
