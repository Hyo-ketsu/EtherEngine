using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Media;
using EtherEngine;
using Reactive.Bindings;


namespace EditorUI {
    /// <summary>ViewModel</summary>
    internal class OutLineVM : INotifyPropertyChanged {
        public event PropertyChangedEventHandler? PropertyChanged;


        /// <summary>コンストラクタ</summary>
        public OutLineVM(OldTreeView oldTreeView) {
            this.OldTreeView = oldTreeView;

            CompositionTarget.Rendering += UpdateGameObjectMethod;

            var gameObject = new GameObject();
            gameObject.Name = "HogeHoge";
            GameObjectStorage.Get.AddGameObject(gameObject);
        }

        private void UpdateGameObjectMethod(object? sender, EventArgs e) {
            if (GameObjectStorage.Get.UpdateGameObjectVersion != UpdateGameObjectVersion) {
                UpdateOutLineView();
                UpdateGameObjectVersion = GameObjectStorage.Get.UpdateGameObjectVersion;
            }
        }


        /// <summary>OutLineViewを更新する</summary>
        private void UpdateOutLineView() {
            //----- とりあえずリストを初期化
            OldTreeView.Items.Clear();

            foreach (var gameObject in EtherEngine.GameObjectStorage.Get.GameObjects) {
                var treeViewItem = new OldTreeViewItem();
                var renameInput = new RenameTextBlock();
                renameInput.InputText.Value = gameObject.Name;
                treeViewItem.Header = renameInput;

                OldTreeView.Items.Add(treeViewItem);
            }
        }

        
        private OldTreeView OldTreeView { get; set; }
        /// <summary>現在保持しているゲームオブジェクトの更新番号</summary>
        private int UpdateGameObjectVersion { get; set; }
    }
}
