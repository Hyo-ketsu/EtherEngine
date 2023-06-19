struct VS_IN {
    float3 pos    : POSITION0; 
    float3 normal : NORMAL0; 
    float2 uv     : TEXCOORD0;
};


struct VS_OUT {
    float4 pos    : SV_POSITION0; 
    float2 uv     : TEXCOORD0;
    float3 normal : NORMAL0;
};


cbuffer WVP : register(b0) {
    float4x4 world;
    float4x4 view;
    float4x4 proj;
}


VS_OUT main(VS_IN vin) {
    //----- 変数宣言
    VS_OUT vout;

	//----- ローカル座標をスクリーン座標へ変換
    vout.pos = float4(vin.pos, 1.0f); 
    vout.pos = mul(vout.pos, world); 
    vout.pos = mul(vout.pos, view); 
    vout.pos = mul(vout.pos, proj); 

    //----- ピクセルシェーダーで利用するUV座標を渡す
    vout.uv = vin.uv;

    //----- ピクセルシェーダーで利用する法線を渡す
    vout.normal = mul(vin.normal, (float3x3) world);

    return vout;
}
