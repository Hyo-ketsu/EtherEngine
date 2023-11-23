#ifndef I_ATTRIBUTEDEFINE_H
#define I_ATTRIBUTEDEFINE_H


namespace EtherEngine {
#ifdef _ENGINELIBRARY
    namespace Attribute {
        // Serialize,Deserializeするための属性
        public ref class Serialize : System::Attribute {
        };


        // Serialize,DeserializeされるものをSerialize,Deserializeしないための属性
        public ref class NonSerialize : System::Attribute {
        };
    }
#endif
}


#endif // !I_ATTRIBUTEDEFINE_H
