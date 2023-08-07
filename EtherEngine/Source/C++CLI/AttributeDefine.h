#ifndef I_ATTRIBUTEDEFINE_H
#define I_ATTRIBUTEDEFINE_H


namespace EtherEngine {
    namespace Attribute {
        // Serialize,Deserialize‚·‚é‚½‚ß‚Ì‘®«
        public ref class Serialize : Attribute {
        };


        // Serialize,Deserialize‚³‚ê‚é‚à‚Ì‚ğSerialize,Deserialize‚µ‚È‚¢‚½‚ß‚Ì‘®«
        public ref class NonSerialize : Attribute {
        };
    }
}


#endif // !I_ATTRIBUTEDEFINE_H
