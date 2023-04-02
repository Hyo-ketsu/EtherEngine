//#ifndef I_OBJECT_H
//#define I_OBJECT_H
//
//
//// タグを単体・複数で保持するか
//enum class MultiTag {
//	Single = 0,
//	Multi = 1,
//};
//
//
//// タグ情報を保持するクラス
//// @ Temp : 複数タグを保持するか(デフォルト : Single)
//template <MultiTag MultiType = MultiTag::Single>
//class Tag {
//public:
//	// タグに使用する型
//	using tagData = unsigned long;
//
//
//	// コンストラクタ
//	// @ Arg1 : 初期設定タグ
//	// @ Arg2 : 追加設定タグ(複数設定でなければ無視する)
//	template <typename... T = std::string>
//	Tag(std::string tag, T... list);
//
//private:
//	tagData m_tag;	// 保持しているタグ
//};
//
//
//// コンストラクタ
//// @ Arg1 : 初期設定タグ
//// @ Arg2 : 追加設定タグ(複数設定でなければ無視する)
//template <MultiTag MultiType>
//template <typename... T>
//Tag<MultiType>::Tag(std::string tag, T... list)
//	: m_tag(tag) {
//	//----- 複数タグ使用なら展開する
//	if constexpr (MultiType == MultiTag::Multi) {
//
//	}
//}
//
//
//#endif // !I_OBJECT_H
