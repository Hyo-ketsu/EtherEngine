#ifndef I_PATHCLASS_H
#define I_PATHCLASS_H
// @ Memo : std::filesystemラップクラス


//----- PathClass 宣言
namespace EtherEngine {
    // std::filesystem::pathラッパークラス
    class PathClass {
    public:
        // コンストラクタ
        // @ Arg1 : パス(Default : 指定なし)
        PathClass(const std::string& path = "");
        // コンストラクタ
        // @ Arg1 : パス
        PathClass(const char* path);
        // デストラクタ
        ~PathClass(void) = default;
        // コピーコンストラクタ
        PathClass(const PathClass& copy) = default;
        // ムーブコンストラクタ
        PathClass(PathClass&& move) = default;
        // コピー代入
        PathClass& operator =(const PathClass& copy) = default;
        // ムーブ代入
        PathClass& operator =(PathClass&& move) = default;


        // カレントディレクトリゲッター
        static std::string GetCurDirectory(void);


        // 拡張子を持っているか
        bool HasExtension(void) const;


        // 配下ディレクトリをすべて取得する
        std::vector<PathClass> GetDirectory(void) const;


        // 取得
        std::string Get(void) const { return m_path; }
        // 取得
        operator std::string(void) const { return Get(); }

    private:
        std::string m_path; // 保持しているパス情報
    };
}


#endif // !I_PATHCLASS_H
