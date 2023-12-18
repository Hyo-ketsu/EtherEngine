using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.ComponentModel;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Reactive.Bindings;


// @ 修正途中。後回し


namespace EditorUI {
    /// <summary>エラーコード</summary>
    public enum StartupVMErrorCodeEnum { 
        NoVersion = 0,
        NoEdition,
        NoVS,
        NoMSBuild,
        OK,
    }


    /// <summary>ViewModel</summary>
    public class StartupVM : INotifyPropertyChanged {
        public event PropertyChangedEventHandler? PropertyChanged;


        /// <summary>入力されたパスが正当かチェック</summary>
        /// <returns></returns>
        internal StartupVMErrorCodeEnum InputPathCheak() {
            //----- 変数宣言
            List<string> directorys = new();

            //----- Path自体がない
            if (VisualStudioPath.Value != null) {
                return StartupVMErrorCodeEnum.OK;
            }
            else {
                return StartupVMErrorCodeEnum.NoMSBuild;
            }
        }
        /// <summary>入力されたVSのバージョン・エディションに合わせてパスを更新する</summary>
        /// <returns>VSが存在していたか</returns>
        internal StartupVMErrorCodeEnum PathUpdate() {
            //----- 変数宣言
            string[] drives = Directory.GetLogicalDrives(); // 念のため全ドライブ走査
            const string path = "Program Files\\Microsoft Visual Studio";
            string? edition = null;
            string? version = null;
            bool isDirectory = false;
            string vsDirectory = new("");

            //----- バージョン等の文字列取得
            switch (VisualStudioEdition.Select) {
            case VisualStudioEditionEnum.Community:
                edition = "Community";
                break;
            case VisualStudioEditionEnum.Professional:
                edition = "Professional";
                break;
            }
            switch (VisualStudioVersion.Select) {
            case VisualStudioVersionEnum.v2019:
                version = "2019";
                break;
            case VisualStudioVersionEnum.v2022:
                version = "2022";
                break;
            }

            //----- バージョン等が入力されているか
            if (edition == null) return StartupVMErrorCodeEnum.NoEdition;
            if (version == null) return StartupVMErrorCodeEnum.NoVersion;

            //----- 指定したディレクトリが存在するか
            foreach (var drive in drives) {
                vsDirectory = drive + path + "\\" + version + "\\" + edition;
                isDirectory = Directory.Exists(vsDirectory);
                if (isDirectory == true) break;
            }

            //----- 
            if (isDirectory) {
                //----- 存在する。パスを追加する
                this.VisualStudioPath.Value = vsDirectory;
                return StartupVMErrorCodeEnum.OK;
            }
            else {
                //----- 存在しない。
                return StartupVMErrorCodeEnum.NoVS;
            }
        }


        /// <summary>設定されているvsのエディション</summary>
        public EnumViewModel<VisualStudioEditionEnum> VisualStudioEdition { get; set; } = new();
        /// <summary>設定されているvsの年度</summary>
        public EnumViewModel<VisualStudioVersionEnum> VisualStudioVersion { get; set; } = new();
        /// <summary>設定されている言語</summary>
        public EnumViewModel<EditorLanguageEnum> Language {
            get { return m_language; }
            set {
                m_language = value;
                EditorText.Language = value.Select; 
            }
        }
        private EnumViewModel<EditorLanguageEnum> m_language = new();
        /// <summary>現在設定されているパス</summary>
        public ReactiveProperty<string> VisualStudioPath { get; set; } = new();
    }
}
