using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
using Reactive.Bindings;


// @ MEMO : シングルトンにしてしまうのはどうかと思うけどいったんこれで(後でエディター関連で一元的に管理する場所が出たらそっちにコンポジットの形にする)
namespace EditorUI {
    /// <summary>エディターの設定を保持するクラス(シングルトン)</summary>
    public class EditorSetting {
        /// <summary>インスタンスを取得する</summary>
        public static EditorSetting Get {
            get {
                if (ms_singleton == null) {
                    ms_singleton = new();
                }
                return ms_singleton;
            } 
        }


        /// <summary>コンストラクタ</summary>
        private EditorSetting() {}


        /// <summary>出力ファイル名</summary>
        public const string OutPutFileName = "editorSetting.json";


        /// <summary>設定言語</summary>
        public ReactiveProperty<EditorLanguageEnum> Language { get; private set; } = new(EditorLanguageEnum.EN);
        /// <summary>使用したパス</summary>
        public ReactiveCollection<string> UsePath { get; private set; } = new();


        /// <summary>インスタンス</summary>
        private static EditorSetting? ms_singleton;
    }
}
