using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Reactive.Bindings;
using Reactive.Bindings.ObjectExtensions;


namespace EditorUI {
    /// <summary>vsのエディション</summary>
    public enum VisualStudioEdition {
        Community = 0,
        Professional,
        None,
    }
    /// <summary>vsの年度</summary>
    public enum VisualStudioVersion {
        v2019 = 0,
        v2022,
        None,
    }


    /// <summary>エラーコード</summary>
    public enum StartupVMErrorCode { 
        NoVersion = 0,
        NoEdition,
        NoVS,
        NoMSBuild,
        OK,
    }


    /// <summary>ViewModel</summary>
    public class StartupVM {
        /// <summary>設定されたMSBuildパス</summary>
        public string? MSBuildPath { get; private set; } = null;


        /// <summary>入力されたパスが正当かチェック</summary>
        /// <returns></returns>
        internal StartupVMErrorCode InputPathCheak() {
            //----- 変数宣言
            List<string> directorys = new();

            //----- Path自体がない
            if (VisualStudioPath.Value == null) return StartupVMErrorCode.NoMSBuild;

            //----- MSBuildが存在するかチェック
            var msbuilds = Directory.GetFiles(VisualStudioPath.Value, "MSBuild.exe", SearchOption.AllDirectories);

            if (msbuilds.Length > 0) {
                //----- 存在した。1つ目の要素をpathとして取得
                MSBuildPath = msbuilds[0];
                return StartupVMErrorCode.OK;
            }
            else {
                return StartupVMErrorCode.NoMSBuild;
            }
        }
        /// <summary>入力されたVSのバージョン・エディションに合わせてパスを更新する</summary>
        /// <returns>VSが存在していたか</returns>
        internal StartupVMErrorCode PathUpdate() {
            //----- 変数宣言
            string[] drives = Directory.GetLogicalDrives(); // 念のため全ドライブ走査
            const string path = "Program Files\\Microsoft Visual Studio";
            string? edition = null;
            string? version = null;
            bool isDirectory = false;
            string vsDirectory = new("");

            //----- バージョン等の文字列取得
            switch (VisualStudioEdition.Select) {
            case EditorUI.VisualStudioEdition.Community:
                edition = "Community";
                break;
            case EditorUI.VisualStudioEdition.Professional:
                edition = "Professional";
                break;
            }
            switch (VisualStudioVersion.Select) {
            case EditorUI.VisualStudioVersion.v2019:
                version = "2019";
                break;
            case EditorUI.VisualStudioVersion.v2022:
                version = "2022";
                break;
            }

            //----- バージョン等が入力されているか
            if (edition == null) return StartupVMErrorCode.NoEdition;
            if (version == null) return StartupVMErrorCode.NoVersion;

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
                return StartupVMErrorCode.OK;
            }
            else {
                //----- 存在しない。
                return StartupVMErrorCode.NoVS;
            }
        }


        /// <summary>設定されているvsのエディション</summary>
        public EnumViewModel<VisualStudioEdition> VisualStudioEdition { get; set; } = new();
        /// <summary>設定されているvsの年度</summary>
        public EnumViewModel<VisualStudioVersion> VisualStudioVersion { get; set; } = new();
        /// <summary>現在設定されているパス</summary>
        public ReactiveProperty<string> VisualStudioPath { get; set; } = new();
    }
}
