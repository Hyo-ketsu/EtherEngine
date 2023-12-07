using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Reactive.Bindings;


namespace EditorUI {
    /// <summary>送信メッセージ</summary>
    public class StartupMessage {
        public StartupMessage(string path) { 
            Path = path;
        }


        public string Path { get; private set; }
    }


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


    /// <summary>エラーコード</summary>
    public enum StartupVMErrorCodeEnum { 
        NoVersion = 0,
        NoEdition,
        NoVS,
        NoMSBuild,
        OK,
    }


    /// <summary>ViewModel</summary>
    public class StartupVM : INotifyCollectionChanged {
        public event NotifyCollectionChangedEventHandler? CollectionChanged;


        /// <summary>入力されたパスが正当かチェック</summary>
        /// <returns></returns>
        internal StartupVMErrorCodeEnum InputPathCheak() {
            //----- 変数宣言
            List<string> directorys = new();

            //----- Path自体がない
            if (VisualStudioPath.Value == null) return StartupVMErrorCodeEnum.NoMSBuild;

            //----- MSBuildが存在するかチェック
            var msbuilds = Directory.GetFiles(VisualStudioPath.Value, "MSBuild.exe", SearchOption.AllDirectories);

            if (msbuilds.Length > 0) {
                //----- 存在した。1つ目の要素をpathとして取得
                var msbuildPath = msbuilds[0];

                //----- メッセージを送信する
                MessageQue<StartupMessage>.AddUIMessage(new(msbuildPath));

                //----- 返却
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
        /// <summary>現在設定されているパス</summary>
        public ReactiveProperty<string> VisualStudioPath { get; set; } = new();
    }
}
