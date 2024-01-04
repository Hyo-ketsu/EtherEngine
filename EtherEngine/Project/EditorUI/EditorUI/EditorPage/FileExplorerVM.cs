﻿using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.ComponentModel;
using System.IO;
using System.Linq;
using System.Reactive.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Shapes;
using Reactive.Bindings;


namespace EditorUI {
    /// <summary>ファイル構造をTreeViewで表現するクラス</summary>
    public class FileExplorerItem { 
        /// <summary>コンストラクタ</summary>
        /// <param name="pathName">フルパス</param>
        public FileExplorerItem(string pathName) {
            FullPath = pathName;
        }


        /// <summary>現在保持しているパス</summary>
        public string PathName { get { return FullPath.Substring(FullPath.LastIndexOf(System.IO.Path.DirectorySeparatorChar) + 1); } }
        /// <summary>保持してるフルパス</summary>
        public string FullPath { get; private set; }
        /// <summary>下位ディレクトリ</summary>
        public List<FileExplorerItem> SubPath { get; private set; } = new();
    }



    /// <summary>ViewModel</summary>
    public class FileExplorerVM : INotifyPropertyChanged {
        public event PropertyChangedEventHandler? PropertyChanged;


        /// <summary>コンストラクタ</summary>
        public FileExplorerVM() {
            PathUpdate();
        }
        /// <summary>選択ディレクトリが変更された際にItemViewを更新する</summary>
        /// <param name="changeDirectory">変更先</param>
        public void ItemViewChanged(string changeDirectory) {
            //----- 初期化
            Files.Clear();

            //----- 表示用データ作成
            var files = Directory.GetFiles(changeDirectory);
            foreach (var file in files) {
                Files.Add(file);
            }
        }


        /// <summary>パス情報を更新する</summary>
        private void PathUpdate() {
            Action<FileExplorerItem> subDirectoryGet = null;
            subDirectoryGet = (FileExplorerItem item) => {
                //----- 下位ディレクトリ追加
                var subDirectory = Directory.GetDirectories(item.FullPath, "*");
                foreach (var subDirectoryItem in subDirectory) {
                    //----- パスの取得
                    var subFile = new FileExplorerItem(subDirectoryItem);
                    item.SubPath.Add(subFile);
                    subDirectoryGet(subFile);
                }
            };

            //----- 初期化
            var item = new FileExplorerItem(System.IO.Directory.GetCurrentDirectory());
            subDirectoryGet(item);
            PathItems.Clear();
            PathItems.Add(item);
        }


        /// <summary>保持しているパス</summary>
        public ReactiveCollection<FileExplorerItem> PathItems { get; private set; } = new();
        /// <summary>表示しているカレントディレクトリのファイル</summary>
        public ReactiveCollection<string> Files { get; private set; } = new();
    }
}