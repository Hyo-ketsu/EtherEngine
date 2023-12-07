using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using MahApps.Metro.Controls;


namespace EditorUI {
    /// <summary>
    /// StartupWindow.xaml の相互作用ロジック
    /// </summary>
    public partial class StartupWindow : MetroWindow {
        public StartupWindow() {
            InitializeComponent();

            VM = DataContext as StartupVM;
            if (VM == null) throw new NullReferenceException();
        }


        /// <summary>完了ボタンが押された際の処理</summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void StartupEnd(object sender, RoutedEventArgs e) {
            //----- パスが正当か
            var inputPath = VM.InputPathCheak();

            switch (inputPath) {
            case StartupVMErrorCodeEnum.NoMSBuild:
                //----- MSBuild.exeが存在しない
                MessageBox.Show(ms_noMSBuild.Text, "Ether Engine", MessageBoxButton.OK, MessageBoxImage.Exclamation);
                break;
            case StartupVMErrorCodeEnum.OK:
                //----- 指定したファイルが存在する。スタートアップ完了
                MessageBox.Show(ms_okStartup.Text, "Ether Engine", MessageBoxButton.OK, MessageBoxImage.Information);
                this.Close();
                break;
            }
        }
        /// <summary>パスのリフレッシュ処理</summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void PathRefresh(object sender, RoutedEventArgs e) {
            //----- パスを更新する
            var pathUpdate = VM.PathUpdate();

            switch (pathUpdate) {
            case StartupVMErrorCodeEnum.NoVersion:
                MessageBox.Show(ms_noVersion.Text, "Ether Engine", MessageBoxButton.OK, MessageBoxImage.Exclamation);
                break;
            case StartupVMErrorCodeEnum.NoEdition:
                MessageBox.Show(ms_noEdition.Text, "Ether Engine", MessageBoxButton.OK, MessageBoxImage.Exclamation);
                break;
            case StartupVMErrorCodeEnum.NoVS:
                MessageBox.Show(ms_noVSDirectory.Text, "Ether Engine", MessageBoxButton.OK, MessageBoxImage.Exclamation);
                break;
            case StartupVMErrorCodeEnum.OK:
                MessageBox.Show(ms_pathRefresh.Text, "Ether Engine", MessageBoxButton.OK, MessageBoxImage.Information);
                break;
            }
        }


        /// <summary>ViewModel</summary>
        private StartupVM VM { get; set; }
        /// <summary>MSBuild不足時のメッセージ</summary>
        private static readonly EditorText ms_noMSBuild = new EditorText(
            en: "MSBuild.exe does not exist in the following subdirectory.",
            jp: "以下の下位ディレクトリにMSBuild.exeが存在しません。"
            );
        /// <summary>スタートアップ完了時のメッセージ</summary>
        private static readonly EditorText ms_okStartup = new EditorText(
            en: "Startup is complete.",
            jp: "スタートアップが完了しました。"
            );
        /// <summary>バージョン情報が指定されていない際のメッセージ</summary>
        private static readonly EditorText ms_noVersion = new EditorText(
            en: "No version information available. Please reset the settings.",
            jp: "バージョン情報がありません。設定し直してください。"
            );
        /// <summary>エディション情報が指定されていない際のメッセージ</summary>
        private static readonly EditorText ms_noEdition = new EditorText(
            en: "No edition information available. Please reset the settings.",
            jp: "エディション情報がありません。設定し直してください。"
            );
        /// <summary>VSのディレクトリが存在しない際のメッセージ</summary>
        private static readonly EditorText ms_noVSDirectory = new EditorText(
            en: "Visual Studio directory does not exist. Please reset the settings.",
            jp: "Visual Studioのディレクトリが存在しません。設定し直してください。"
            );
        /// <summary>パスリフレッシュ完了時のメッセージ</summary>
        private static readonly EditorText ms_pathRefresh = new EditorText(
            en: "Path refresh completed.",
            jp: "パスのリフレッシュが完了しました。"
            );
    }
}
