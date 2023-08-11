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


        // 拡張子含めたファイル名取得
        // @ Ret  : 拡張子含めたファイル名(例 : Hoge.exe)
        std::string GetFile(void) const;
        // ディレクトリ名を取得
        // @ Ret  : ディレクトリ名
        // @ Ret  : (例 : Hoge/Fuga.exe -> Hoge/     )
        // @ Ret  : (例 : Hoge/Fuga/    -> Hoge/Fuga/)
        // @ Ret  : (例 : Hoge/Fuga     -> Hoge/     )
        PathClass GetDirectory(void) const;
        // 拡張子名を取得
        // @ Ret  : 拡張子名(例 : exe)
        std::string GetExtension(void) const;


        // 拡張子を持っているか
        bool HasExtension(void) const;


        // 現在収納されているディレクトリを全て生成する
        // @ Memo : 例として、"Hoge/"まであるとして、"Hoge/Fuga/Piyo/foo.txt"を保持していたら、
        // @ Memo : "Hoge/Fuga","Hoge/Fuga/Piyo/"を生成する
        // @ Ret  : 生成できたか
        bool CreateDirectories(void) const;


        // パス要素追加
        const PathClass operator/=(const std::string& path) const;
        // パス文字列追加
        const PathClass operator+=(const std::string& string) const;


        // ファイルが存在しているか
        bool IsExists(void) const;
        // 通常ファイルか
        bool IsFile(void) const;
        // ディレクトリか　
        bool IsDirectory(void) const;


        // 取得
        std::string Get(void) const { return m_path; }
        // 取得
        operator std::string(void) const { return Get(); }
        // 配下ディレクトリをすべて取得する
        std::vector<PathClass> GetLowerDirectory(void) const;

    private:
        std::string m_path; // 保持しているパス情報
    };
}


#endif // !I_PATHCLASS_H
