#ifndef I_ATTRIBUTEDEFINE_H
#define I_ATTRIBUTEDEFINE_H


namespace EtherEngine {
    namespace Attribute {
        // Serialize,Deserialize���邽�߂̑���
        public ref class Serialize : Attribute {
        };


        // Serialize,Deserialize�������̂�Serialize,Deserialize���Ȃ����߂̑���
        public ref class NonSerialize : Attribute {
        };
    }
}


#endif // !I_ATTRIBUTEDEFINE_H
