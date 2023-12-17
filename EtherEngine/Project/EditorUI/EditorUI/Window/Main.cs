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
using ControlzEx.Standard;
using Reactive.Bindings;


namespace EditorUI {
    /// <summary>ウィンドウの生成情報</summary>
    public class CreateWindowData {
        /// <summary>コンストラクタ</summary>
        /// <param name="name">ウィンドウ名</param>
        /// <param name="windowType">生成するウィンドウのType</param>
        /// <param name="createCommnad">ウィンドウの生成Action</param>
        public CreateWindowData(string name, Type windowType, Action<Type, string> createCommnad) {
            Name = name;
            WindowType = windowType;
            CreateCommnad.Subscribe(createWindow => {
                createCommnad(createWindow, Name);
            });
        }


        /// <summary>ウィンドウ名</summary>
        public string Name { get; set; }
        /// <summary>生成するウィンドウのType</summary>
        public Type WindowType { get; set; }
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
            CreateWindow = new();

            //----- CreatedWindow属性が付与されているウィンドウの情報を生成する
            var types = Assembly.GetExecutingAssembly().GetTypes();
            var windowTypes = types.Where(
                type => 
                type.GetCustomAttributes(typeof(CreatedWindowAttribute),true).Any() && 
                type.IsSubclassOf(typeof(UserControl))).ToArray();

            foreach (var window in windowTypes) {
                var action = new Action<Type, string>((createWindowType, Name) => {
                    //----- Nullなら例外出力
                    if (LayoutRoot == null) throw new NullReferenceException();
                    if (DockingManager == null) throw new NullReferenceException();

                    //----- ウィンドウを作成する
                    var window = Activator.CreateInstance(createWindowType);
                    var useControl = window as UserControl;
                    if (useControl == null) throw new NullReferenceException();

                    //----- 変数宣言
                    uint groupCount = 0;
                    LayoutDocumentPaneGroup? group = null;

                    //----- 追加する
                    // @ Memo : MeinWindowのPaneがない、もしくはPaneのみであればそこに生成、
                    // @ Memo : 複数に分割されていればフロートで生成します
                    if (LayoutRoot.RootPanel.ChildrenCount < 1) {
                        //----- 子パネルがない。追加
                        var pane = new LayoutDocumentPane();
                        LayoutRoot.RootPanel.Children.Add(pane);
                    }
                    foreach (var children in LayoutRoot.RootPanel.Children) {
                        //----- LayoutDocumentPaneもしくはLayoutDocumentPaneGroupか?
                        var pane = children as LayoutDocumentPane;
                        group = children as LayoutDocumentPaneGroup;
                        if (group != null) groupCount++;
                        if (pane == null) continue;

                        //----- LayoutDocumentPaneが存在する。追加
                        var document = new LayoutDocument();
                        document.Title = Name;
                        document.Content = useControl;

                        //----- 終了時処理を追加できるのであれば追加する
                        var closeInterface = useControl as IUserControlClose;
                        if (closeInterface != null) {
                            document.Closed += closeInterface.CloseEvent;
                        }
                        pane.Children.Add(document);
                        return;
                    }

                    // @ MEMO : 現状不要だと思うけど必要になったら実装して
                    if (false) { } //groupCount == 1) { //----- LayoutDocumentPaneGroupのみ }
                    else { 
                        //----- LayoutDocumentPaneGroupがないor全てだった。フロートで生成
                        var anchorable = new LayoutAnchorable() {
                            Title = Name,
                            Content = window
                        };
                        anchorable.AddToLayout(DockingManager, AnchorableShowStrategy.Most);
                        anchorable.Float();
                    }
                });

                //----- 生成追加する
                var createWindowAttribute = window.GetCustomAttribute<CreatedWindowAttribute>(false);
                if (createWindowAttribute == null) throw new NullReferenceException();  // 念のため null チェック
                var windowData = new CreateWindowData(createWindowAttribute.ShowText.Text, window, action);
                CreateWindow.Add(windowData);
            }

            //----- ソートする
            CreateWindow.OrderBy(window => window);
        }


        /// <summary>生成するウィンドウ</summary>
        public ReactiveCollection<CreateWindowData> CreateWindow { get; set; }
        /// <summary>DockManager</summary>
        public DockingManager? DockingManager { get; set; }
        /// <summary>Dockウィンドウの生成元</summary>
        public LayoutRoot? LayoutRoot { get; set; }
    }
}
