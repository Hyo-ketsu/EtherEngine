#ifndef I_ATTRIBUTEDEFINE_H
#define I_ATTRIBUTEDEFINE_H


namespace EtherEngine {
#ifdef _ENGINELIBRARY
    namespace Attribute {
        // Serialize,Deserialize���邽�߂̑���
        public ref class Serialize : System::Attribute {
        };


        // Serialize,Deserialize�������̂�Serialize,Deserialize���Ȃ����߂̑���
        public ref class NonSerialize : System::Attribute {
        };
    }
#endif
}


#endif // !I_ATTRIBUTEDEFINE_H
