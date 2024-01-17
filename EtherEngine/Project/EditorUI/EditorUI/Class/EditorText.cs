using System;
using System.CodeDom;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Resources;
using Reactive.Bindings;


namespace EditorUI {
    /// <summary>エディターの各言語でのテキストを表現するクラス</summary>
    [Serializable]
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


        /// <summary>英語</summary>
        public string EN { set; get; } = new("");
        /// <summary>日本語</summary>
        public string JP { set; get; } = new("");


        /// <summary>現在の言語のテキスト->ENの順に何らか設定されている文字を返却</summary>
        public string SomeText {
            get {
                if (EN != null) { return EN; }
                if (JP != null) { return JP; }
                return new("");
            }
        }
        /// <summary>テキストを現在の言語で取得する</summary>
        /// <returns></returns>
        public override string ToString() {
            return GetText(EditorSetting.Get.Language.Value);
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
            default:
                return "";
            }
        }
    }
}
