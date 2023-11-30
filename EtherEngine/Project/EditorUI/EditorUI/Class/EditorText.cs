using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Resources;


namespace EditorUI {
    /// <summary>エディターの各言語でのテキストを表現するクラス</summary>
    public class EditorText {
        /// <summary>コンストラクタ</summary>
        /// <param name="en">英語(Default : "")</param>
        /// <param name="jp">日本語(Default : "")</param>
        public EditorText(string en = "", string jp = "") {
            EN = en;
            JP = jp;
        }
        public EditorText() {
        }


        /// <summary>現在の言語設定</summary>
        public static EditorLanguageEnum Language {
            get { return ms_language; }
            set { ms_language = value; }
        }

        /// <summary>英語</summary>
        public string EN { set; get; } = new("");
        /// <summary>日本語</summary>
        public string JP { set; get; } = new("");


        /// <summary>テキストを現在の言語で取得する</summary>
        /// <param name=""></param>
        /// <returns>取得したテキスト</returns>
        public string Text {
            get { return GetText(ms_language); }
        }
        /// <summary>テキストを取得する</summary>
        /// <param name="language">言語</param>
        /// <returns>取得したテキスト</returns>
        public string GetText(EditorLanguageEnum language) {
            switch (language) {
            case EditorLanguageEnum.EN:
                return EN;
            case EditorLanguageEnum.JP:
                return JP;
            case EditorLanguageEnum.None:
            default:
                return "";
            }
        }


        /// <summary>現在の言語設定</summary>
        private static EditorLanguageEnum ms_language = EditorLanguageEnum.EN;
    }
}
