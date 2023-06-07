#ifndef I_VECTORCONVERTER_H
#define I_VECTORCONVERTER_H


//----- MathConverter�錾
namespace EtherEngine {
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

        // Eigen�̍s��
        template <typename T>
        concept EigenMatrixConcept = requires(T instans) { instans[0, 0]; };

        // DirectX��2�����x�N�g����
        template <typename T>
        concept DirectX2DVectorConcept = requires(T instans) { instans.x; instans.y; };
        // DirectX��3�����x�N�g����
        template <typename T>
        concept DirectX3DVectorConcept = DirectX2DVectorConcept<T> && requires(T instans) { instans.z; };
        // DirectX��4�����x�N�g����
        template <typename T>
        concept DirectX4DVectorConcept = DirectX2DVectorConcept<T> && requires(T instans) { instans.w; };

        // DirectX�̍s��
        template <typename T>
        concept DirectXMatrixConcept = requires(T instans) { instans.m[0][0]; };


        // Eigen�̃x�N�g������DirectX�̃x�N�g���ɑ������
        // @ Arg1 : Eigen�̃x�N�g��
        // @ Arg2 : DirectX�̃x�N�g��
        template <Eigen2DVectorConcept EigenVec, DirectX2DVectorConcept DXVec = DirectX::XMFLOAT2>
        void EigenToDX(const EigenVec& eigenVec, DXVec* const dxVec);
        // Eigen�̃x�N�g������DirectX�̃x�N�g���ɑ������
        // @ Arg1 : Eigen�̃x�N�g��
        // @ Arg2 : DirectX�̃x�N�g��
        template <Eigen3DVectorConcept EigenVec, DirectX3DVectorConcept DXVec = DirectX::XMFLOAT2>
        void EigenToDX(const EigenVec& eigenVec, DXVec* const dxVec);
        // Eigen�̃x�N�g������DirectX�̃x�N�g���ɑ������
        // @ Arg1 : Eigen�̃x�N�g��
        // @ Arg2 : DirectX�̃x�N�g��
        template <Eigen4DVectorConcept EigenVec, DirectX4DVectorConcept DXVec = DirectX::XMFLOAT2>
        void EigenToDX(const EigenVec& eigenVec, DXVec* const dxVec);

        // Eigen�̍s���DirectX�̍s��ɕϊ�����
        // @ Memo : �]�u���s���܂�
        // @ Arg1 : Eigen�̍s��
        // @ Arg2 : DirectX�̍s��
        // @ Arg3 : ������(Default : 4)
        template <EigenMatrixConcept EigenMat, DirectXMatrixConcept DXMat = DirectX::XMMATRIX>
        void EigenToDX(const EigenMat& eigenMat, DXMat* const dxMat, const int dimension = 4);


        // DirectX�̃x�N�g������Eigen�̃x�N�g���ɑ������
        // @ Arg1 : DirectX�̃x�N�g��
        // @ Arg2 : Eigen�̃x�N�g��
        template <DirectX2DVectorConcept DXVec, Eigen2DVectorConcept EigenVec = Eigen::Vector2f>
        void DXToEigen(const DXVec& dxVec, EigenVec* const eigenVec);
        // DirectX�̃x�N�g������Eigen�̃x�N�g���ɑ������
        // @ Arg1 : DirectX�̃x�N�g��
        // @ Arg2 : Eigen�̃x�N�g��
        template <DirectX3DVectorConcept DXVec, Eigen3DVectorConcept EigenVec = Eigen::Vector3f>
        void DXToEigen(const DXVec& dxVec, EigenVec* const eigenVec);
        // DirectX�̃x�N�g������Eigen�̃x�N�g���ɑ������
        // @ Arg1 : DirectX�̃x�N�g��
        // @ Arg2 : Eigen�̃x�N�g��
        template <DirectX4DVectorConcept DXVec, Eigen4DVectorConcept EigenVec = Eigen::Vector4f>
        void DXToEigen(const DXVec& dxVec, EigenVec* const eigenVec);

        // DirectX�̍s���Eigen�̍s��ɕϊ�����
        // @ Memo : �]�u���s���܂�
        // @ Arg1 : DirectX�̍s��
        // @ Arg2 : Eigen�̍s��
        // @ Arg3 : ������(Default : 4)
        template <DirectXMatrixConcept DXMat, EigenMatrixConcept EigenMat = Eigen::Matrix4f>
        void EigenToDX(const DXMat& dxMat, EigenMat* const eigenMat, const int dimension = 4);
    }
}


//----- MathConverter�錾
namespace EtherEngine {
    namespace MathConverter {
        // Eigen�̃x�N�g������DirectX�̃x�N�g���ɑ������
        // @ Arg1 : Eigen�̃x�N�g��
        // @ Arg2 : DirectX�̃x�N�g��
        template <Eigen2DVectorConcept EigenVec, DirectX2DVectorConcept DXVec>
        void EigenToDX(const EigenVec& eigenVec, DXVec* const dxVec) {
            dxVec->x = eigenVec.x();
            dxVec->y = eigenVec.y();
        }
        // Eigen�̃x�N�g������DirectX�̃x�N�g���ɑ������
        // @ Arg1 : Eigen�̃x�N�g��
        // @ Arg2 : DirectX�̃x�N�g��
        template <Eigen3DVectorConcept EigenVec, DirectX3DVectorConcept DXVec>
        void EigenToDX(const EigenVec& eigenVec, DXVec* const dxVec) {
            dxVec->x = eigenVec.x();
            dxVec->y = eigenVec.y();
            dxVec->z = eigenVec.z();
        }
        // Eigen�̃x�N�g������DirectX�̃x�N�g���ɑ������
        // @ Arg1 : Eigen�̃x�N�g��
        // @ Arg2 : DirectX�̃x�N�g��
        template <Eigen4DVectorConcept EigenVec, DirectX4DVectorConcept DXVec>
        void EigenToDX(const EigenVec& eigenVec, DXVec* const dxVec) {
            dxVec->x = eigenVec.x();
            dxVec->y = eigenVec.y();
            dxVec->z = eigenVec.z();
            dxVec->w = eigenVec.w();
        }

        // Eigen�̍s���DirectX�̍s��ɕϊ�����
        // @ Memo : �]�u���s���܂�
        // @ Arg1 : Eigen�̍s��
        // @ Arg2 : DirectX�̍s��
        // @ Arg3 : ������(Default : 4)
        template <EigenMatrixConcept EigenMat, DirectXMatrixConcept DXMat>
        void EigenToDX(const EigenMat& eigenMat, DXMat* const dxMat, const int dimension) {
            *dxMat = DirectX::XMMatrixTranspose(*dxMat);
            for (int i = 0; i < dimension; i++) {
                for (int j = 0; j < dimension; j++) {
                    dxMat->m[i][j] = eigenMat[i, j];
                }
            }
        }

        // DirectX�̃x�N�g������Eigen�̃x�N�g���ɑ������
        // @ Arg1 : DirectX�̃x�N�g��
        // @ Arg2 : Eigen�̃x�N�g��
        template <DirectX2DVectorConcept DXVec, Eigen2DVectorConcept EigenVec>
        void DXToEigen(const DXVec& dxVec, EigenVec* const eigenVec) {
            eigenVec.x() = dxVec->x;
            eigenVec.y() = dxVec->y;
        }
        // DirectX�̃x�N�g������Eigen�̃x�N�g���ɑ������
        // @ Arg1 : DirectX�̃x�N�g��
        // @ Arg2 : Eigen�̃x�N�g��
        template <DirectX3DVectorConcept DXVec, Eigen3DVectorConcept EigenVec>
        void DXToEigen(const DXVec& dxVec, EigenVec* const eigenVec) {
            eigenVec.x() = dxVec->x;
            eigenVec.y() = dxVec->y;
            eigenVec.z() = dxVec->z;
        }
        // DirectX�̃x�N�g������Eigen�̃x�N�g���ɑ������
        // @ Arg1 : DirectX�̃x�N�g��
        // @ Arg2 : Eigen�̃x�N�g��
        template <DirectX4DVectorConcept DXVec, Eigen4DVectorConcept EigenVec>
        void DXToEigen(const DXVec& dxVec, EigenVec* const eigenVec) {
            eigenVec.x() = dxVec->x;
            eigenVec.y() = dxVec->y;
            eigenVec.z() = dxVec->z;
            eigenVec.w() = dxVec->w;
        }

        // DirectX�̍s���Eigen�̍s��ɕϊ�����
        // @ Memo : �]�u���s���܂�
        // @ Arg1 : DirectX�̍s��
        // @ Arg2 : Eigen�̍s��
        // @ Arg3 : ������(Default : 4)
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
