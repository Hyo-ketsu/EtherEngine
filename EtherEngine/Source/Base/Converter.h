#ifndef I_VECTORCONVERTER_H
#define I_VECTORCONVERTER_H


//----- MathConverter宣言
namespace EtherEngine {
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
        template <Eigen3DVectorConcept EigenVec, DirectX3DVectorConcept DXVec = DirectX::XMFLOAT2>
        void EigenToDX(const EigenVec& eigenVec, DXVec* const dxVec);
        // EigenのベクトルからDirectXのベクトルに代入する
        // @ Arg1 : Eigenのベクトル
        // @ Arg2 : DirectXのベクトル
        template <Eigen4DVectorConcept EigenVec, DirectX4DVectorConcept DXVec = DirectX::XMFLOAT2>
        void EigenToDX(const EigenVec& eigenVec, DXVec* const dxVec);

        // Eigenの行列をDirectXの行列に変換する
        // @ Memo : 転置も行います
        // @ Arg1 : Eigenの行列
        // @ Arg2 : DirectXの行列
        // @ Arg3 : 次元数(Default : 4)
        template <EigenMatrixConcept EigenMat, DirectXMatrixConcept DXMat = DirectX::XMMATRIX>
        void EigenToDX(const EigenMat& eigenMat, DXMat* const dxMat, const int dimension = 4);


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
        // @ Memo : 転置も行います
        // @ Arg1 : DirectXの行列
        // @ Arg2 : Eigenの行列
        // @ Arg3 : 次元数(Default : 4)
        template <DirectXMatrixConcept DXMat, EigenMatrixConcept EigenMat = Eigen::Matrix4f>
        void EigenToDX(const DXMat& dxMat, EigenMat* const eigenMat, const int dimension = 4);
    }
}


//----- MathConverter宣言
namespace EtherEngine {
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
        // @ Memo : 転置も行います
        // @ Arg1 : Eigenの行列
        // @ Arg2 : DirectXの行列
        // @ Arg3 : 次元数(Default : 4)
        template <EigenMatrixConcept EigenMat, DirectXMatrixConcept DXMat>
        void EigenToDX(const EigenMat& eigenMat, DXMat* const dxMat, const int dimension) {
            *dxMat = DirectX::XMMatrixTranspose(*dxMat);
            for (int i = 0; i < dimension; i++) {
                for (int j = 0; j < dimension; j++) {
                    dxMat->m[i][j] = eigenMat[i, j];
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
        // @ Memo : 転置も行います
        // @ Arg1 : DirectXの行列
        // @ Arg2 : Eigenの行列
        // @ Arg3 : 次元数(Default : 4)
        template <DirectXMatrixConcept DXMat, EigenMatrixConcept EigenMat>
        void EigenToDX(const DXMat& dxMat, EigenMat* const eigenMat, const uint dimension) {
            dxMat = DirectX::XMMatrixTranspose(dxMat);
            for (uint i = 0; i < dimension; i++) {
                for (uint j = 0; j < dimension; j++) {
                    (*eigenMat)[i,j] = dxMat.m[i][j];
                }
            }
        }
    }
}


#endif // !I_VECTORCONVERTER_H
