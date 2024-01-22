using System;
using System.Collections.Generic;
using System.ComponentModel;
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
using System.Windows.Navigation;
using System.Windows.Shapes;
using EditorUI;
using Reactive.Bindings;


namespace EditorUI {
    /// <summary>
    /// MessageIcon.xaml の相互作用ロジック
    /// </summary>
    public partial class MessageIcon : UserControl, INotifyPropertyChanged {
        public event PropertyChangedEventHandler? PropertyChanged;


        /// <summary>コンストラクタ</summary>
        public MessageIcon() {
            InitializeComponent();
            DataContext = this;
        }


        public static readonly DependencyProperty TypeProperty = DependencyProperty.Register(
            "Type", 
            typeof(MessageType),
            typeof(MessageIcon), 
            new PropertyMetadata(default(MessageType))
        );


        /// <summary>表示しているメッセージタイプ</summary>
        public MessageType Type {
            get { return (MessageType)GetValue(TypeProperty); }
            set { SetValue(TypeProperty, value); }
        }


        /// <summary>表示しているメッセージタイプ</summary>
        public ReactiveProperty<MessageType> MessageType { get; private set; } = new(EditorUI.MessageType.None);
    }
}
