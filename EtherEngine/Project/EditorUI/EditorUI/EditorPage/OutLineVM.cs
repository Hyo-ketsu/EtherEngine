using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.ComponentModel;
using System.Linq;
using System.Security.Permissions;
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

            //----- コマンド登録
            CreateCommand.Subscribe(() => {
                //----- 新規のゲームオブジェクト作成
                var gameObject = new GameObject();
                gameObject.Name = EditorDefine.NewCreateGameObjectName.ToString();
                GameObjectStorage.Get.AddGameObject(gameObject);
            });
            DeleteCommand.Subscribe(() => {
                //----- 現在選択中のオブジェクトを削除する
                var select = OldTreeView.SelectedItem as OldTreeViewItem;
                if (select != null) {
                    int i = 0;
                    foreach (var item in OldTreeView.Items) {
                        if (select == item) {
                            GameObjectStorage.Get.DeleteGameObject(GameObjectStorage.Get.GameObjects[i]);
                        }
                        i++;
                    }
                }
            });
        }


        /// <summary>ゲームオブジェクトが更新されているか毎フレームチェックを行う</summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
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
                //----- コントロール作成
                var treeViewItem = new OldTreeViewItem();
                var renameInput = new RenameTextBlock();

                //----- 名前表示
                renameInput.InputText.Value = gameObject.Name;
                gameObject.UpdateEvent += (gameObject,_)=> {
                    var baseObject = gameObject as EtherEngine.BaseObject;
                    renameInput.InputText.Value = baseObject?.Name;
                };

                //----- ツリー
                treeViewItem.Header = renameInput;
                treeViewItem.TreeItem.Value = gameObject;

                //----- TreeViewに追加する
                OldTreeView.Items.Add(treeViewItem);
            }
        }


        /// <summary>ゲームオブジェクト作成時の処理</summary>
        public ReactiveCommand CreateCommand { get; private set; } = new();
        /// <summary>ゲームオブジェクト削除時の処理</summary>
        public ReactiveCommand DeleteCommand { get; private set; } = new();

        
        private OldTreeView OldTreeView { get; set; }
        /// <summary>現在保持しているゲームオブジェクトの更新番号</summary>
        private int UpdateGameObjectVersion { get; set; }
    }
}
