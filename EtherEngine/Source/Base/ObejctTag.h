//#ifndef I_OBJECT_H
//#define I_OBJECT_H
//
//
//// �^�O��P�́E�����ŕێ����邩
//enum class MultiTag {
//	Single = 0,
//	Multi = 1,
//};
//
//
//// �^�O����ێ�����N���X
//// @ Temp : �����^�O��ێ����邩(�f�t�H���g : Single)
//template <MultiTag MultiType = MultiTag::Single>
//class Tag {
//public:
//	// �^�O�Ɏg�p����^
//	using tagData = unsigned long;
//
//
//	// �R���X�g���N�^
//	// @ Arg1 : �����ݒ�^�O
//	// @ Arg2 : �ǉ��ݒ�^�O(�����ݒ�łȂ���Ζ�������)
//	template <typename... T = std::string>
//	Tag(std::string tag, T... list);
//
//private:
//	tagData m_tag;	// �ێ����Ă���^�O
//};
//
//
//// �R���X�g���N�^
//// @ Arg1 : �����ݒ�^�O
//// @ Arg2 : �ǉ��ݒ�^�O(�����ݒ�łȂ���Ζ�������)
//template <MultiTag MultiType>
//template <typename... T>
//Tag<MultiType>::Tag(std::string tag, T... list)
//	: m_tag(tag) {
//	//----- �����^�O�g�p�Ȃ�W�J����
//	if constexpr (MultiType == MultiTag::Multi) {
//
//	}
//}
//
//
//#endif // !I_OBJECT_H
