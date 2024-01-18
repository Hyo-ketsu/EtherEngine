using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace EditorUI {
    public static class EditorDefine {
        static EditorDefine() {
            NewCreateGameObjectName = new(en: "New GameObject", jp: "新しいゲームオブジェクト");
            NewCreateFile = new(en: "New File", jp: "New File");
        }

        /// <summary>ゲームオブジェクト作成時の名前</summary>
        public static readonly EditorText NewCreateGameObjectName;
        /// <summary>ファイル作成時の名前</summary>
        public static readonly EditorText NewCreateFile;
        /// <summary>DLL用ディレクトリ名</summary>
        public const string DLLDirectoryName = "DLL";
    }
}
