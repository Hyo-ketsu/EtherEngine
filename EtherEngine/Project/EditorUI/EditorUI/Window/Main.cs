using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.ComponentModel.DataAnnotations.Schema;
using System.Linq;
using System.Reflection;
using System.Reflection.Metadata;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;
using AvalonDock;
using AvalonDock.Layout;
using Reactive.Bindings;


namespace EditorUI {
    /// <summary>ウィンドウの生成情報</summary>
    public class CreateWindowData {
        public CreateWindowData(string name, UserControl window, Action<Type> createCommnad) {
            Name = name;
            Window = window;
            CreateCommnad.Subscribe(createWindow => {
                createCommnad(createWindow);
            });
        }


        /// <summary>ウィンドウ名</summary>
        public string Name { get; set; }
        /// <summary>生成するウィンドウ</summary>
        public UserControl Window { get; set; }
        /// <summary>ウィンドウ生成のコマンド</summary>
        public ReactiveCommand<Type> CreateCommnad { get; set; } = new();
    }


    /// <summary>ViewModel</summary>
    public class MainVM : INotifyCollectionChanged {
        public event NotifyCollectionChangedEventHandler? CollectionChanged;


        /// <summary>コンストラクタ</summary>
        public MainVM() {
            CreateWindowData();
        }


        /// <summary>ウィンドウ情報を生成する</summary>
        public void CreateWindowData() {
            //----- 初期化する
            CreateWindow = new();return;

            //----- CreatedWindow属性が付与されているウィンドウの情報を生成する
            //Assembly.get
            for (; ;/*後で書き直してくれ*/ ) {
                var action = new Action<Type>(createWindowType => {
                    //----- Nullなら例外出力
                    if (LayoutRoot == null) throw new NullReferenceException();
                    if (DockingManager == null) throw new NullReferenceException();

                    //----- ウィンドウを作成する
                    var window = Activator.CreateInstance(createWindowType) as UserControl;
                    if (window == null) throw new NullReferenceException();

                    //----- 追加する
                    // @ Memo : MeinWindowのPaneがない、もしくはPaneのみであればそこに生成、
                    // @ Memo : 複数に分割されていればフロートで生成します
                    if (LayoutRoot.ChildrenCount < 1) {
                        //----- 子パネルがない。追加
                        var pane = new LayoutDocumentPane();
                        LayoutRoot.RootPanel.Children.Add(pane);
                    }
                    foreach (var children in LayoutRoot.Children) {
                        //----- LayoutDocumentPaneか?
                        var pane = children as LayoutDocumentPane;
                        if (pane == null) continue;

                        //----- LayoutDocumentPaneが存在する。追加する
                        var document = new LayoutDocument();
                        document.Title = window.Name;
                        document.Content = window;
                        pane.Children.Add(document);
                        return;
                    }
                    //----- 全てLayoutDocumentPaneGroupだった。フロートで生成
                    var anchorable = new LayoutAnchorable() {
                        Title = window.Name,
                        Content = window
                    };
                    anchorable.AddToLayout(DockingManager, AnchorableShowStrategy.Most);
                    anchorable.Float();
                });

                //var windowData = new CreateWindowData(,, action);

                //CreateWindow.Add(windowData);
            }
        }


        /// <summary>生成するウィンドウ</summary>
        public ReactiveCollection<CreateWindowData> CreateWindow { get; set; }
        /// <summary>DockManager</summary>
        public DockingManager? DockingManager { get; set; }
        /// <summary>Dockウィンドウの生成元</summary>
        public LayoutRoot? LayoutRoot { get; set; }
    }
}
