#ifndef I_RANDOMMANAGE_H
#define I_RANDOMMANAGE_H
#include <Base/Singleton.h>
#include <Base/Random.h>


//----- RandomManage��`
namespace EtherEngine {
    namespace RandomManage {
        // 32bit,�Ⴕ����64bit�̐��l�i�����A���������j��
        template <typename T>
        concept Number32_64Concept = Random::Random32BitConcept<T> || Random::Random64BitConcept<T>;


        // �����𐶐�����
        // @ Temp: �g�p����^
        // @ Ret : ����
        template <Number32_64Concept Type>
        Type GetRandom(void);
    };
}




//----- RandomManage�錾
namespace EtherEngine {
    // �����𐶐�����
    // @ Temp: �g�p����^
    // @ Ret : ����
    template <RandomManage::Number32_64Concept Type>
    Type RandomManage::GetRandom(void) {
        //----- �ÓI�ϐ��錾
        std::unordered_map<Type, nullptr> random32map;

        //----- ��������
        auto ret = Random:::GetRandom<Type>();
        
        //----- �������J��Ԃ�
        while (random32map.find(ret) == random32map.end()) {
            ret = Random::Random32BitConcept<Type>();
        }

        //----- �ԋp
        return ret;
    }
}


#endif // !I_RANDOMMANAGE_H
