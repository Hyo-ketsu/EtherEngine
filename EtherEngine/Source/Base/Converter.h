#ifndef I_VECTORCONVERTER_H
#define I_VECTORCONVERTER_H


//----- MathConverter宣言
namespace EtherEngine {
    //----- EigenとDXのベクトル変換
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


        // DirectXの2次元ベクトルか
        template <typename T>
        concept DirectX2DVectorConcept = requires(T instans) { instans.x; instans.y; };
        // DirectXの3次元ベクトルか
        template <typename T>
        concept DirectX3DVectorConcept = DirectX2DVectorConcept<T> && requires(T instans) { instans.z; };
        // DirectXの4次元ベクトルか
        template <typename T>
        concept DirectX4DVectorConcept = DirectX2DVectorConcept<T> && requires(T instans) { instans.w; };


        // EigenのベクトルからDirectXのベクトルに代入する
        // @ Arg1 : Eigenのベクトル
        // @ Arg2 : DirectXのベクトル
        template <Eigen2DVectorConcept EigenVec, DirectX2DVectorConcept DXVec = DirectX::XMFLOAT2>
        void EigenToDX(const EigenVec& eigenVec, DXVec* const dxVec);
        // EigenのベクトルからDirectXのベクトルを取得する
        // @ Ret  : DirectXのベクトル
        // @ Arg1 : Eigenのベクトル
        // @ Arg2 : DirectXのベクトル
        template <Eigen2DVectorConcept EigenVec, DirectX2DVectorConcept DXVec = DirectX::XMFLOAT2>
        DXVec EigenToDX(const EigenVec& eigenVec, const DXVec& dxVec);


        // DirectXのベクトルからEigenのベクトルに代入する
        // @ Arg1 : DirectXのベクトル
        // @ Arg2 : Eigenのベクトル
        template <DirectX2DVectorConcept DXVec, Eigen2DVectorConcept EigenVec = Eigen::Vector2f>
        void DXToEigen(const DXVec& dxVec, EigenVec* const eigenVec);
        // DirectXのベクトルからEigenのベクトルを取得する
        // @ Ret  : Eigenのベクトル
        // @ Arg1 : DirectXのベクトル
        // @ Arg2 : Eigenのベクトル
        template <DirectX2DVectorConcept DXVec, Eigen2DVectorConcept EigenVec = Eigen::Vector2f>
        EigenVec DXToEigen(const DXVec& dxVec, const EigenVec& eigenVec);
    }


    //----- EigenとDXの行列変換
    namespace MathConverter {
        // Eigenの行列か
        template <typename T>
        concept EigenMatrixConcept = requires(T instans) { instans[0, 0]; };
        
        // DirectXの行列か
        template <typename T>
        concept DirectXMatrixConcept = requires(T instans) {
            typeid(DirectX::XMVECTOR) == typeid(instans.r[0]);
        };


        // Eigenの行列をDirectXの行列に変換する
        // @ Arg1 : Eigenの行列
        // @ Arg2 : DirectXの行列
        // @ Arg3 : 次元数(Default : 4)
        template <EigenMatrixConcept EigenMat, DirectXMatrixConcept DXMat = DirectX::XMMATRIX>
        void EigenToDX(const EigenMat& eigenMat, DXMat* const dxMat, const uint dimension = 4);
        // Eigenの行列をDirectXの行列を取得する
        // @ Ret  : DirectXの行列
        // @ Arg1 : Eigenの行列
        // @ Arg2 : DirectXの行列
        // @ Arg3 : 次元数(Default : 4)
        template <EigenMatrixConcept EigenMat, DirectXMatrixConcept DXMat = DirectX::XMMATRIX>
        DXMat EigenToDX(const EigenMat& eigenMat, const DXMat& dxMat, const uint dimension = 4);


        // DirectXの行列をEigenの行列に変換する
        // @ Arg1 : DirectXの行列
        // @ Arg2 : Eigenの行列
        // @ Arg3 : 次元数(Default : 4)
        template <DirectXMatrixConcept DXMat, EigenMatrixConcept EigenMat = Eigen::Matrix4f>
        void DXToEigen(const DXMat& dxMat, EigenMat* const eigenMat, const uint dimension = 4);
        // DirectXの行列をEigenの行列を取得する
        // @ Ret  : Eigenの行列
        // @ Arg1 : DirectXの行列
        // @ Arg2 : Eigenの行列
        // @ Arg3 : 次元数(Default : 4)
        template <DirectXMatrixConcept DXMat, EigenMatrixConcept EigenMat = Eigen::Matrix4f>
        EigenMat DXToEigen(const DXMat& dxMat, const EigenMat& eigenMat, const uint dimension = 4);
    }


    //----- XMMATRIXとXMFLOAT4X4変換
    namespace MathConverter {
        // XMMATRIXをXMFLOAT4X4に変換する
        // @ Ret  : 変換されたXMFLOAT4X4
        // @ Arg1 : XMMATRIX
        DirectX::XMFLOAT4X4 MatrixToFloat4x4(const DirectX::XMMATRIX& mat);
    }
}


//----- MathConverter定義
namespace EtherEngine {
    //----- EigenとDXのベクトル変換
    namespace MathConverter {
        // EigenのベクトルからDirectXのベクトルに代入する
        // @ Arg1 : Eigenのベクトル
        // @ Arg2 : DirectXのベクトル
        template <Eigen2DVectorConcept EigenVec, DirectX2DVectorConcept DXVec>
        void EigenToDX(const EigenVec& eigenVec, DXVec* const dxVec) {
            dxVec->x = eigenVec.x();
            dxVec->y = eigenVec.y();
            if constexpr (Eigen3DVectorConcept<EigenVec> && DirectX3DVectorConcept<DXVec>) {
                dxVec->z = eigenVec.z();
            }
            if constexpr (Eigen4DVectorConcept<EigenVec> && DirectX4DVectorConcept<DXVec>) {
                dxVec->w = eigenVec.w();
            }
        }
        // EigenのベクトルからDirectXのベクトルを取得する
        // @ Ret  : DirectXのベクトル
        // @ Arg1 : Eigenのベクトル
        // @ Arg2 : DirectXのベクトル
        template <Eigen2DVectorConcept EigenVec, DirectX2DVectorConcept DXVec>
        DXVec EigenToDX(const EigenVec& eigenVec, const DXVec& dxVec) {
            //----- 宣言
            DXVec ret = DXVec();
            
            //----- 変換
            EigenToDX(eigenVec, &ret);

            //----- 返却
            return ret;
        }


        // DirectXのベクトルからEigenのベクトルに代入する
        // @ Arg1 : DirectXのベクトル
        // @ Arg2 : Eigenのベクトル
        template <DirectX2DVectorConcept DXVec, Eigen2DVectorConcept EigenVec>
        void DXToEigen(const DXVec& dxVec, EigenVec* const eigenVec) {
            eigenVec.x() = dxVec->x;
            eigenVec.y() = dxVec->y;
            if constexpr (DirectX3DVectorConcept<DXVec> && Eigen3DVectorConcept<EigenVec>) {
                eigenVec.z() = dxVec->z;
            }
            if constexpr (DirectX4DVectorConcept<DXVec> && Eigen4DVectorConcept<EigenVec>) {
                eigenVec.w() = dxVec->w;
            }
        }
        // DirectXのベクトルからEigenのベクトルを取得する
        // @ Ret  : Eigenのベクトル
        // @ Arg1 : DirectXのベクトル
        // @ Arg2 : Eigenのベクトル
        template <DirectX2DVectorConcept DXVec, Eigen2DVectorConcept EigenVec>
        EigenVec DXToEigen(const DXVec& dxVec, const EigenVec& eigenVec) {
            //----- 変数宣言
            EigenVec ret = EigenVec();

            //----- 変換
            DXToEigen(dxVec, &ret);

            //----- 返却
            return ret;
        }
    }


    //----- EigenとDXの行列変換
    namespace MathConverter {
        // Eigenの行列をDirectXの行列に変換する
        // @ Arg1 : Eigenの行列
        // @ Arg2 : DirectXの行列
        // @ Arg3 : 次元数(Default : 4)
        template <EigenMatrixConcept EigenMat, DirectXMatrixConcept DXMat>
        void EigenToDX(const EigenMat& eigenMat, DXMat* const dxMat, const uint dimension) {
            for (int i = 0; i < dimension; i++) {
                for (int j = 0; j < dimension; j++) {
                    dxMat->r[i].m128_f32[j] = eigenMat(i, j);
                }
            }
        }
        // Eigenの行列をDirectXの行列を取得する
        // @ Ret  : DirectXの行列
        // @ Arg1 : Eigenの行列
        // @ Arg2 : DirectXの行列
        // @ Arg3 : 次元数(Default : 4)
        template <EigenMatrixConcept EigenMat, DirectXMatrixConcept DXMat>
        DXMat EigenToDX(const EigenMat& eigenMat, const DXMat& dxMat, const uint dimension) {
            //----- 宣言
            DXMat ret = DXMat();
            
            //----- 変換
            EigenToDX(eigenMat, &ret, dimension);

            //----- 返却
            return ret;
        }



        // DirectXの行列をEigenの行列に変換する
        // @ Arg1 : DirectXの行列
        // @ Arg2 : Eigenの行列
        // @ Arg3 : 次元数(Default : 4)
        template<DirectXMatrixConcept DXMat, EigenMatrixConcept EigenMat>
        void DXToEigen(const DXMat& dxMat, EigenMat* const eigenMat, const uint dimension) {
            for (uint i = 0; i < dimension; i++) {
                for (uint j = 0; j < dimension; j++) {
                    (*eigenMat)(i, j) = dxMat.r[i].m128_f32[j];
                }
            }
        }
        // DirectXの行列をEigenの行列を取得する
        // @ Ret  : Eigenの行列
        // @ Arg1 : DirectXの行列
        // @ Arg2 : Eigenの行列
        // @ Arg3 : 次元数(Default : 4)
        template <DirectXMatrixConcept DXMat, EigenMatrixConcept EigenMat>
        EigenMat DXToEigen(const DXMat& dxMat, const EigenMat& eigenMat, const uint dimension) {
            //----- 宣言
            EigenMat ret = EigenMat();

            //----- 変換
            DXToEigen(dxMat, &ret, dimension);

            //----- 返却
            return ret;
        }

    }
}


#endif // !I_VECTORCONVERTER_H
