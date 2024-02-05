#ifndef I_ATTRIBUTEDEFINE_H
#define I_ATTRIBUTEDEFINE_H


#pragma managed
namespace EtherEngine {
    //----- ���o�͑���
    namespace Attribute {
        // ���o�͂��s�����߂̑���
        [System::AttributeUsageAttribute(System::AttributeTargets::Field)]
        public ref class OutputAttribute : System::Attribute {
        };
        // ���o�͂��s������̂���o�͂��Ȃ����߂̑���
        [System::AttributeUsageAttribute(System::AttributeTargets::Field)]
        public ref class NoOutputAttribute : System::Attribute {
        };
    }
    //----- BaseObject���䑮��
    namespace Attribute {
        // BaseObject�𒼐ړ��o�͂��鑮��
        [System::AttributeUsageAttribute(System::AttributeTargets::Field)]
            public ref class BaseObjectSerializeAttribute : System::Attribute {
        };
        //// BaseObject�̎Q�Ƃ�ێ�����̑���
        //[System::AttributeUsageAttribute(System::AttributeTargets::Field)]
        //    public ref class NoOutputAttribute : System::Attribute {
        //};
    }
}


#endif // !I_ATTRIBUTEDEFINE_H
