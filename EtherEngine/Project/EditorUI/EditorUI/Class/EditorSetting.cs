using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;


namespace EditorUI {
    /// <summary>vsのエディション</summary>
    public enum VisualStudioEditionEnum {
        Community = 0,
        Professional,
        None,
    }
    /// <summary>vsの年度</summary>
    public enum VisualStudioVersionEnum {
        v2019 = 0,
        v2022,
        None,
    }
    /// <summary>エディターの設定を保持するクラス</summary>
    public class EditorSetting {
        /// <summary>コンストラクタ</summary>
        public EditorSetting() {}


        /// <summary>設定言語</summary>
        public EditorLanguageEnum Language { get; set; } = new();
        /// <summary>設定 Visual Stadio のエディション</summary>
        public VisualStudioEditionEnum VisualStudioEdition { get; set; } = new();
        /// <summary>設定 Visual Stadio のバージョン</summary>
        public VisualStudioVersionEnum VisualStudioVersion { get; set; } = new();
        /// <summary>出力ファイル名</summary>
        public const string OutPutFileName = "editorSetting.json";
    }
}
