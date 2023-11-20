using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace EditorUI {
    /// <summary>エディターの各言語でのテキストを表現するクラス</summary>
    public class EditorText {
        // コンストラクタ
        // @ Arg1 : 英語
        // @ Arg2 : 日本語
        /// <summary>コンストラクタ</summary>
        /// <param name="en">英語(Default : "")</param>
        /// <param name="jp">日本語(Default : "")</param>
        public EditorText(string en = "", string jp = "") {
            m_text.Add(EditorLanguageEnum.EN, en);
            m_text.Add(EditorLanguageEnum.JP, jp);
        }


        /// <summary>現在の言語設定</summary>
        public static EditorLanguageEnum Language {
            get { return ms_language; }
            set { ms_language = value; }
        }


        /// <summary>テキストを現在の言語で取得する</summary>
        /// <param name=""></param>
        /// <returns>取得したテキスト</returns>
        public string Text {
            get { return m_text[ms_language]; }
        }
        /// <summary>テキストを取得する</summary>
        /// <param name="language">言語</param>
        /// <returns>取得したテキスト</returns>
        public string GetText(EditorLanguageEnum language) {
            return m_text[language];
        }


        /// <summary>各言語ごとのテキスト</summary>
        private Dictionary<EditorLanguageEnum, string> m_text = new();
        /// <summary>現在の言語設定</summary>
        private static EditorLanguageEnum ms_language = EditorLanguageEnum.EN;
    }
}
