#ifndef I_ATTRIBUTEDEFINE_H
#define I_ATTRIBUTEDEFINE_H


namespace EtherEngine {
    namespace Attribute {
        // Serialize,Deserializeするための属性
        public ref class Serialize : Attribute {
        };


        // Serialize,DeserializeされるものをSerialize,Deserializeしないための属性
        public ref class NonSerialize : Attribute {
        };
    }
}


#endif // !I_ATTRIBUTEDEFINE_H
