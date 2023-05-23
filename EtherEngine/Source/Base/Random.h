#ifndef I_RANDOM_H
#define I_RANDOM_H


namespace EtherEngine {
    namespace Random {
        // ���l�^�Ⴕ���͕��������A���w�肵��Byte����
        template <class T, int Byte>
        concept RandomBitConcept = (std::is_integral_v<T> || std::is_floating_point_v<T>) && (int)sizeof(T) == Byte;


        // 32bit(4Byte)�����𐶐�����
        // @ Temp: �g�p����^
        // @ Ret : ����
        template <RandomBitConcept<4> Type>
        Type GetRandom(void);
        // 64bit(8Byte)�����𐶐�����
        // @ Temp: �g�p����^
        // @ Ret : ����
        template <RandomBitConcept<8> Type>
        Type GetRandom(void);
    }
}




//----- Random����
namespace EtherEngine {
    namespace Random {
        // 32bit(4Byte)�����𐶐�����
        // @ Temp: �g�p����^(�f�t�H���g : float)
        // @ Ret : ����
        template <RandomBitConcept<4> Type>
        Type GetRandom(void) {
            //----- �ϐ��錾
            static std::random_device randomDevice; // �񌈒�I�ȗ���������
            static std::mt19937 mt(randomDevice()); // ����

            //----- �ԋp
            return (Type)mt();
        }
        // 64bit(8Byte)�����𐶐�����
        // @ Temp: �g�p����^(�f�t�H���g : long long)
        // @ Ret : ����
        template <RandomBitConcept<8> Type>
        Type GetRandom(void) {
            //----- �ϐ��錾
            static std::random_device randomDevice;    // �񌈒�I�ȗ���������
            static std::mt19937_64 mt(randomDevice()); // ����

            //----- �ԋp
            return (Type)mt();
        }
    }
}


#endif // !I_RANDOM_H
