#ifndef I_VECTORCONVERTER_H
#define I_VECTORCONVERTER_H


//----- MathConverter�錾
namespace EtherEngine {
    //----- Eigen��DX�̃x�N�g���ϊ�
    namespace MathConverter {
        // Eigen��2�����̃x�N�g����
        template <typename T>
        concept Eigen2DVectorConcept = requires(T instans) { instans.x(); instans.y(); };
        // Eigen��3�����̃x�N�g����
        template <typename T>
        concept Eigen3DVectorConcept = Eigen2DVectorConcept<T> && requires(T instans) { instans.z(); };
        // Eigen��4�����̃x�N�g����
        template <typename T>
        concept Eigen4DVectorConcept = Eigen3DVectorConcept<T> && requires(T instans) { instans.w(); };


        // DirectX��2�����x�N�g����
        template <typename T>
        concept DirectX2DVectorConcept = requires(T instans) { instans.x; instans.y; };
        // DirectX��3�����x�N�g����
        template <typename T>
        concept DirectX3DVectorConcept = DirectX2DVectorConcept<T> && requires(T instans) { instans.z; };
        // DirectX��4�����x�N�g����
        template <typename T>
        concept DirectX4DVectorConcept = DirectX2DVectorConcept<T> && requires(T instans) { instans.w; };


        // Eigen�̃x�N�g������DirectX�̃x�N�g���ɑ������
        // @ Arg1 : Eigen�̃x�N�g��
        // @ Arg2 : DirectX�̃x�N�g��
        template <Eigen2DVectorConcept EigenVec, DirectX2DVectorConcept DXVec = DirectX::XMFLOAT2>
        void EigenToDX(const EigenVec& eigenVec, DXVec* const dxVec);
        // Eigen�̃x�N�g������DirectX�̃x�N�g�����擾����
        // @ Ret  : DirectX�̃x�N�g��
        // @ Arg1 : Eigen�̃x�N�g��
        // @ Arg2 : DirectX�̃x�N�g��
        template <Eigen2DVectorConcept EigenVec, DirectX2DVectorConcept DXVec = DirectX::XMFLOAT2>
        DXVec EigenToDX(const EigenVec& eigenVec, const DXVec& dxVec);


        // DirectX�̃x�N�g������Eigen�̃x�N�g���ɑ������
        // @ Arg1 : DirectX�̃x�N�g��
        // @ Arg2 : Eigen�̃x�N�g��
        template <DirectX2DVectorConcept DXVec, Eigen2DVectorConcept EigenVec = Eigen::Vector2f>
        void DXToEigen(const DXVec& dxVec, EigenVec* const eigenVec);
        // DirectX�̃x�N�g������Eigen�̃x�N�g�����擾����
        // @ Ret  : Eigen�̃x�N�g��
        // @ Arg1 : DirectX�̃x�N�g��
        // @ Arg2 : Eigen�̃x�N�g��
        template <DirectX2DVectorConcept DXVec, Eigen2DVectorConcept EigenVec = Eigen::Vector2f>
        EigenVec DXToEigen(const DXVec& dxVec, const EigenVec& eigenVec);
    }


    //----- Eigen��DX�̍s��ϊ�
    namespace MathConverter {
        // Eigen�̍s��
        template <typename T>
        concept EigenMatrixConcept = requires(T instans) { instans[0, 0]; };
        
        // DirectX�̍s��
        template <typename T>
        concept DirectXMatrixConcept = requires(T instans) {
            typeid(DirectX::XMVECTOR) == typeid(instans.r[0]);
        };


        // Eigen�̍s���DirectX�̍s��ɕϊ�����
        // @ Arg1 : Eigen�̍s��
        // @ Arg2 : DirectX�̍s��
        // @ Arg3 : ������(Default : 4)
        template <EigenMatrixConcept EigenMat, DirectXMatrixConcept DXMat = DirectX::XMMATRIX>
        void EigenToDX(const EigenMat& eigenMat, DXMat* const dxMat, const uint dimension = 4);
        // Eigen�̍s���DirectX�̍s����擾����
        // @ Ret  : DirectX�̍s��
        // @ Arg1 : Eigen�̍s��
        // @ Arg2 : DirectX�̍s��
        // @ Arg3 : ������(Default : 4)
        template <EigenMatrixConcept EigenMat, DirectXMatrixConcept DXMat = DirectX::XMMATRIX>
        DXMat EigenToDX(const EigenMat& eigenMat, const DXMat& dxMat, const uint dimension = 4);


        // DirectX�̍s���Eigen�̍s��ɕϊ�����
        // @ Arg1 : DirectX�̍s��
        // @ Arg2 : Eigen�̍s��
        // @ Arg3 : ������(Default : 4)
        template <DirectXMatrixConcept DXMat, EigenMatrixConcept EigenMat = Eigen::Matrix4f>
        void DXToEigen(const DXMat& dxMat, EigenMat* const eigenMat, const uint dimension = 4);
        // DirectX�̍s���Eigen�̍s����擾����
        // @ Ret  : Eigen�̍s��
        // @ Arg1 : DirectX�̍s��
        // @ Arg2 : Eigen�̍s��
        // @ Arg3 : ������(Default : 4)
        template <DirectXMatrixConcept DXMat, EigenMatrixConcept EigenMat = Eigen::Matrix4f>
        EigenMat DXToEigen(const DXMat& dxMat, const EigenMat& eigenMat, const uint dimension = 4);
    }


    //----- XMMATRIX��XMFLOAT4X4�ϊ�
    namespace MathConverter {
        // XMMATRIX��XMFLOAT4X4�ɕϊ�����
        // @ Ret  : �ϊ����ꂽXMFLOAT4X4
        // @ Arg1 : XMMATRIX
        DirectX::XMFLOAT4X4 MatrixToFloat4x4(const DirectX::XMMATRIX& mat);
    }
}


//----- MathConverter��`
namespace EtherEngine {
    //----- Eigen��DX�̃x�N�g���ϊ�
    namespace MathConverter {
        // Eigen�̃x�N�g������DirectX�̃x�N�g���ɑ������
        // @ Arg1 : Eigen�̃x�N�g��
        // @ Arg2 : DirectX�̃x�N�g��
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
        // Eigen�̃x�N�g������DirectX�̃x�N�g�����擾����
        // @ Ret  : DirectX�̃x�N�g��
        // @ Arg1 : Eigen�̃x�N�g��
        // @ Arg2 : DirectX�̃x�N�g��
        template <Eigen2DVectorConcept EigenVec, DirectX2DVectorConcept DXVec>
        DXVec EigenToDX(const EigenVec& eigenVec, const DXVec& dxVec) {
            //----- �錾
            DXVec ret = DXVec();
            
            //----- �ϊ�
            EigenToDX(eigenVec, &ret);

            //----- �ԋp
            return ret;
        }


        // DirectX�̃x�N�g������Eigen�̃x�N�g���ɑ������
        // @ Arg1 : DirectX�̃x�N�g��
        // @ Arg2 : Eigen�̃x�N�g��
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
        // DirectX�̃x�N�g������Eigen�̃x�N�g�����擾����
        // @ Ret  : Eigen�̃x�N�g��
        // @ Arg1 : DirectX�̃x�N�g��
        // @ Arg2 : Eigen�̃x�N�g��
        template <DirectX2DVectorConcept DXVec, Eigen2DVectorConcept EigenVec>
        EigenVec DXToEigen(const DXVec& dxVec, const EigenVec& eigenVec) {
            //----- �ϐ��錾
            EigenVec ret = EigenVec();

            //----- �ϊ�
            DXToEigen(dxVec, &ret);

            //----- �ԋp
            return ret;
        }
    }


    //----- Eigen��DX�̍s��ϊ�
    namespace MathConverter {
        // Eigen�̍s���DirectX�̍s��ɕϊ�����
        // @ Arg1 : Eigen�̍s��
        // @ Arg2 : DirectX�̍s��
        // @ Arg3 : ������(Default : 4)
        template <EigenMatrixConcept EigenMat, DirectXMatrixConcept DXMat>
        void EigenToDX(const EigenMat& eigenMat, DXMat* const dxMat, const uint dimension) {
            for (int i = 0; i < dimension; i++) {
                for (int j = 0; j < dimension; j++) {
                    dxMat->r[i].m128_f32[j] = eigenMat(i, j);
                }
            }
        }
        // Eigen�̍s���DirectX�̍s����擾����
        // @ Ret  : DirectX�̍s��
        // @ Arg1 : Eigen�̍s��
        // @ Arg2 : DirectX�̍s��
        // @ Arg3 : ������(Default : 4)
        template <EigenMatrixConcept EigenMat, DirectXMatrixConcept DXMat>
        DXMat EigenToDX(const EigenMat& eigenMat, const DXMat& dxMat, const uint dimension) {
            //----- �錾
            DXMat ret = DXMat();
            
            //----- �ϊ�
            EigenToDX(eigenMat, &ret, dimension);

            //----- �ԋp
            return ret;
        }



        // DirectX�̍s���Eigen�̍s��ɕϊ�����
        // @ Arg1 : DirectX�̍s��
        // @ Arg2 : Eigen�̍s��
        // @ Arg3 : ������(Default : 4)
        template<DirectXMatrixConcept DXMat, EigenMatrixConcept EigenMat>
        void DXToEigen(const DXMat& dxMat, EigenMat* const eigenMat, const uint dimension) {
            for (uint i = 0; i < dimension; i++) {
                for (uint j = 0; j < dimension; j++) {
                    (*eigenMat)(i, j) = dxMat.r[i].m128_f32[j];
                }
            }
        }
        // DirectX�̍s���Eigen�̍s����擾����
        // @ Ret  : Eigen�̍s��
        // @ Arg1 : DirectX�̍s��
        // @ Arg2 : Eigen�̍s��
        // @ Arg3 : ������(Default : 4)
        template <DirectXMatrixConcept DXMat, EigenMatrixConcept EigenMat>
        EigenMat DXToEigen(const DXMat& dxMat, const EigenMat& eigenMat, const uint dimension) {
            //----- �錾
            EigenMat ret = EigenMat();

            //----- �ϊ�
            DXToEigen(dxMat, &ret, dimension);

            //----- �ԋp
            return ret;
        }

    }
}


#endif // !I_VECTORCONVERTER_H
