//#include <DirectX/ModelComponent.h>
//#include <Base/ComponentHelper.h>
//#include <Base/Converter.h>
//
//
//namespace EtherEngine {
//    // コンストラクタ
//    ModelComponent::ModelComponent(GameObject* gameObject, const std::string& file, const Handle<DirectXRender>& directX, VertexShader& vertexShader, PixelShader& pixelShader,
//        const float scale, const bool isFlip) 
//        : DXDrawComponent(gameObject, vertexShader, pixelShader)
//        , Model(file, directX, &vertexShader, &pixelShader,scale, isFlip) {
//        SetVertexShader(vertexShader);
//        SetPixelShader(pixelShader);
//    }
//
//
//    // 描画処理
//    void ModelComponent::Draw(void) {
//        //----- 親ゲームオブジェクト保持
//        auto gameObject = ComponentHelper::GetParentObject(this);
//
//        //----- ワールド行列作成
//        DirectX::XMMATRIX world;
//        world = DirectX::XMMatrixScaling(
//                gameObject->AccessTransform().AccessScale().x(), gameObject->AccessTransform().AccessScale().y(), gameObject->AccessTransform().AccessScale().z()
//            ) * DirectX::XMMatrixRotationRollPitchYaw(
//                gameObject->AccessTransform().AccessRotation().x(), gameObject->AccessTransform().AccessRotation().y(), gameObject->AccessTransform().AccessRotation().z()
//            ) * DirectX::XMMatrixTranslation(
//                gameObject->AccessTransform().AccessPostion().x(), gameObject->AccessTransform().AccessPostion().y(), gameObject->AccessTransform().AccessPostion().z()
//            );
//
//        //----- Eigen行列に変換
//        Eigen::Matrix4f eigenMat;
//        MathConverter::DXToEigen(world, &eigenMat);
//        eigenMat.transpose();
//
//        //----- 描画
//        DrawModel(eigenMat, GetView(), GetProjection());
//    }
//}
