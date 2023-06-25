#ifndef I_CONCEPTUTILITY_H
#define I_CONCEPTUTILITY_H


namespace EtherEngine {
    namespace Concept {
        // ����̌^�Ɠ����^�����肷��R���Z�v�g
        template <typename T, typename U>
        concept SameConcept = std::is_same_v<T, U>;
        // ����̌^�ƈႤ�^�����肷��R���Z�v�g
        template <typename T, typename U>
        concept NotSameConcept = !(SameConcept<T, U>);

        // �w�肵���^���p�����Ă��邩���肷��R���Z�v�g
        template <typename T, typename U>
        concept BaseOfConcept = std::is_base_of_v<U, T>;
        // �w�肵���^���p�����Ă��Ȃ������肷��R���Z�v�g
        template <typename T, typename U>
        concept NotBaseOfConcept = !(BaseOfConcept<T, U>);

        // ���l�^�����肷��R���Z�v�g
        template <typename T>
        concept ArithmeticConcept = std::is_arithmetic_v<T>;
        // ���l�^�łȂ������肷��R���Z�v�g
        template <typename T>
        concept NotArithmeticConcept = !(ArithmeticConcept<T>);

        // �N���X�����肷��R���Z�v�g
        template <typename T>
        concept ClassConcept = std::is_class_v<T>;
        // �N���X�ł͂Ȃ������肷��R���Z�v�g
        template <typename T>
        concept NotClassConcept = !(ClassConcept<T>);

        // �|�C���^�����肷��R���Z�v�g
        template <typename T>
        concept PointerConcept = std::is_pointer_v<T>;
        // �|�C���^�ł͂Ȃ������肷��R���Z�v�g
        template <typename T>
        concept NotPointerConcept = !(PointerConcept<T>);

        // �I�u�W�F�N�g�^�����肷��R���Z�v�g
        template <typename T>
        concept ObjectConcept = std::is_object_v<T>;
        // �I�u�W�F�N�g�^�ł͂Ȃ������肷��R���Z�v�g
        template <typename T>
        concept NotObjectConcept = !(ObjectConcept<T>);
    }
}


#endif // !I_CONCEPTUTILITY_H
