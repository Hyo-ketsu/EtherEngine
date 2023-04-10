#ifndef I_RANDOM_H
#define I_RANDOM_H


namespace EtherEngine {
    namespace Random {
        // ���l�^�Ⴕ���͕��������A����32bit(4B)��
        template <class T>
        concept Random32BitConcept = (std::is_integral_v<T> || std::is_floating_point_v<T>) && (int)sizeof(T) == 4;
        // ���l�^�Ⴕ���͕��������A����64bit(8B)��
        template <class T>
        concept Random64BitConcept = (std::is_integral_v<T> || std::is_floating_point_v<T>) && (int)sizeof(T) == 8;


        // 32bit�����𐶐�����
        // @ Temp: �g�p����^
        // @ Ret : ����
        template <Random32BitConcept Type>
        Type GetRandom(void);
        // 64bit�����𐶐�����
        // @ Temp: �g�p����^
        // @ Ret : ����
        template <Random64BitConcept Type>
        Type GetRandom(void);
    }
}




//----- Random����
namespace EtherEngine {
    namespace Random {
        // 32bit�����𐶐�����
        // @ Temp: �g�p����^(�f�t�H���g : float)
        // @ Ret : ����
        template <Random32BitConcept Type>
        Type GetRandom(void) {
            //----- �ϐ��錾
            static std::random_device randomDevice; // �񌈒�I�ȗ���������
            static std::mt19937 mt(rnd());          // ����

            //----- �ԋp
            return (Type)mt();
        }
        // 64bit�����𐶐�����
        // @ Temp: �g�p����^(�f�t�H���g : long long)
        // @ Ret : ����
        template <Random64BitConcept Type>
        Type GetRandom(void) {
            //----- �ϐ��錾
            static std::random_device randomDevice; // �񌈒�I�ȗ���������
            static std::mt19937_64 mt(rnd());       // ����

            //----- �ԋp
            return (Type)mt();
        }
    }
}


#endif // !I_RANDOM_H
