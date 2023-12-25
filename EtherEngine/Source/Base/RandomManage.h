#ifndef I_RANDOMMANAGE_H
#define I_RANDOMMANAGE_H
#include <Base/Singleton.h>
#include <Base/Random.h>


//----- RandomManage �錾
namespace EtherEngine {
    // 32bit,�Ⴕ����64bit��
    template <typename T>
    concept Number32_64ByteConcept = Random::RandomBitConcept<T, 4> || Random::RandomBitConcept<T, 8>;


    // �����̐������s���A�������ԍ��𐶐����Ȃ��N���X
    template <Number32_64ByteConcept Type>
    class RandomManage : public Singleton<RandomManage<Type>> {
    public:
        // �����𐶐�����
        // @ Temp: �g�p����^
        // @ Ret : ����
        Type GetRandom(void);

    private:
        // �R���X�g���N�^
        RandomManage(void) {}

        friend class Singleton<RandomManage>;

        static std::vector<Type> m_usedNumber; // �ێ����Ă��鐶�������ԍ�
    };
}




//----- RandomManage ��`
namespace EtherEngine {
    // �����𐶐�����
    template <Number32_64ByteConcept Type>
    Type RandomManage<Type>::GetRandom(void) {
        //----- �ϐ��錾
        Type number;

        //----- ���X�g����Ȃ疳�����ɒǉ�
        if (m_usedNumber.size() == 0) {
            number = Random::GetRandom<Type>();
            m_usedNumber.push_back(number);
            return number;
        }

        while (true) {
            //----- �����𐶐�����
            number = Random::GetRandom<Type>();

            //----- ���X�g�ɂȂ����m�F�A�Ȃ���Βǉ��A����΍Đ���
            for (auto it = m_usedNumber.begin(); it != m_usedNumber.end(); it++) {
                if (*it >= number) {
                    //----- �������ꂽ�ԍ��ȏ�̔ԍ��B�Đ���
                    break;
                }
                if (*it < number) {
                    //----- �������ꂽ�ԍ��̕����������B�ǉ�
                    m_usedNumber.insert(it, number);
                    return number;
                }
            }
        }
    }


    template <Number32_64ByteConcept Type>
    std::vector<Type> RandomManage<Type>::m_usedNumber; // �ێ����Ă��鐶�������ԍ�
}


#endif // !I_RANDOMMANAGE_H
