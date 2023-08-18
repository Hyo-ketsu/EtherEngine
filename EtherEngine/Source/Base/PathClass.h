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
        // 拡張子含めないファイル名取得
        // @ Ret  : 拡張子含めないファイル名(例 : Hoge.exe -> Hoge)
        std::string GetFileName(void) const;
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
        // 現在格納されているパスでファイルを生成する
        // @ Memo : 既にファイルがある場合は生成しません
        // @ Memo : 途中の階層のディレクトリは生成しません
        // @ Ret  : 生成できたか
        // @ Arg1 : 生成したファイルに渡す文字列(Default : "")
        bool CreateFiles(const std::string& fileString = "");
        // 現在のファイル・ディレクトリを削除します
        // @ Ret  : 削除が行われたか
        // @ Arg1 : 再帰的に削除するか(true : 中身があるディレクトリ削除可能, false : 中身があるディレクトリ削除不可。Default : false)
        bool DeleteFiles(const bool isAllRemove = false);


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
        std::string& Access(void) { return m_path; }
        // 取得
        operator std::string(void) const { return Get(); }
        // 配下ディレクトリをすべて取得する
        std::vector<PathClass> GetLowerDirectory(void) const;

    private:
        std::string m_path; // 保持しているパス情報
    };
}


#endif // !I_PATHCLASS_H
