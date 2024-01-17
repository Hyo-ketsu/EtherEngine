using System;
using System.Collections.Generic;
using System.IO;
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
using Microsoft.WindowsAPICodePack.Dialogs;
using MahApps.Metro.Controls;
using System.ComponentModel;
using System.Text.RegularExpressions;


namespace EditorUI {
    /// <summary>
    /// StartupWindow.xaml の相互作用ロジック
    /// </summary>
    public partial class StartupWindow : MetroWindow {
        /// <summary>コンストラクタ</summary>
        public StartupWindow() {
            InitializeComponent();

            Closed += (_, _) => {
                if (m_path != null) {
                    Directory.SetCurrentDirectory(m_path);
                }
            };
        }


        /// <summary>新規パスのダブルクリック時のイベント</summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void NewPathMouseDoubleClick(object sender, MouseButtonEventArgs e) {
            //----- ダイアログ表示
            using (var openFile = new CommonOpenFileDialog() {
                Title = mr_newPathTitle.ToString(),
                IsFolderPicker = true,
            }) {
                //----- 選択されているか
                if (openFile.ShowDialog() != CommonFileDialogResult.Ok) return;

                //----- 半角大文字小文字アルファベットと半角記号以外がパスにあったら検知する
                if (Regex.IsMatch(openFile.FileName, @"^[a-zA-Z0-9\s\p{P}]+$") == false) {
                    System.Windows.MessageBox.Show(mr_pathFraud.ToString());
                    return;
                }

                //----- 選択されている。取得してウィンドウを閉じる
                m_path = openFile.FileName;
                m_isFolderChoice = true;
                Close();
            }
        }
        /// <summary>ウィンドウ自体の終了ボタンを押して終了した際の処理</summary>
        private void WindowClosing(object s, CancelEventArgs e) {
            //----- アプリケーションの終了
            if (m_isFolderChoice == false) {
                var etherEngine = Application.Current as EtherEngineApplication;
                if (etherEngine != null) etherEngine.IsCancelStartup = true;
                Application.Current.Shutdown();
            }
        }


        private readonly EditorText mr_newPathTitle = new(en:"Use Folder……", jp:"使用するフォルダを選択……");
        private readonly EditorText mr_pathFraud = new(en:"The path contains alphabets and symbols. Please select again.", 
                                                       jp: "パスにアルファベット、記号が含まれています。選択しなおしてください。");
        /// <summary>保持しているパス</summary>
        private string m_path;
        /// <summary>フォルダーが選択された後か</summary>
        private bool m_isFolderChoice = false;
    }
}
