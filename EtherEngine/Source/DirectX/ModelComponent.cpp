//#include <DirectX/ModelComponent.h>
//#include <Base/ComponentHelper.h>
//#include <Base/Converter.h>
//
//
//namespace EtherEngine {
//    // �R���X�g���N�^
//    ModelComponent::ModelComponent(GameObject* gameObject, const std::string& file, const Handle<DirectXRender>& directX, VertexShader& vertexShader, PixelShader& pixelShader,
//        const float scale, const bool isFlip) 
//        : DXDrawComponent(gameObject, vertexShader, pixelShader)
//        , Model(file, directX, &vertexShader, &pixelShader,scale, isFlip) {
//        SetVertexShader(vertexShader);
//        SetPixelShader(pixelShader);
//    }
//
//
//    // �`�揈��
//    void ModelComponent::Draw(void) {
//        //----- �e�Q�[���I�u�W�F�N�g�ێ�
//        auto gameObject = ComponentHelper::GetParentObject(this);
//
//        //----- ���[���h�s��쐬
//        DirectX::XMMATRIX world;
//        world = DirectX::XMMatrixScaling(
//                gameObject->AccessTransform().AccessScale().x(), gameObject->AccessTransform().AccessScale().y(), gameObject->AccessTransform().AccessScale().z()
//            ) * DirectX::XMMatrixRotationRollPitchYaw(
//                gameObject->AccessTransform().AccessRotation().x(), gameObject->AccessTransform().AccessRotation().y(), gameObject->AccessTransform().AccessRotation().z()
//            ) * DirectX::XMMatrixTranslation(
//                gameObject->AccessTransform().AccessPostion().x(), gameObject->AccessTransform().AccessPostion().y(), gameObject->AccessTransform().AccessPostion().z()
//            );
//
//        //----- Eigen�s��ɕϊ�
//        Eigen::Matrix4f eigenMat;
//        MathConverter::DXToEigen(world, &eigenMat);
//        eigenMat.transpose();
//
//        //----- �`��
//        DrawModel(eigenMat, GetView(), GetProjection());
//    }
//}
