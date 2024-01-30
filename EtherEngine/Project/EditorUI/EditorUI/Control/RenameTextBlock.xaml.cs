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
using Reactive.Bindings;


namespace EditorUI {
    /// <summary>
    /// RenameTextBlock.xaml の相互作用ロジック
    /// </summary>
    public partial class RenameTextBlock : UserControl, INotifyPropertyChanged {
        public event PropertyChangedEventHandler? PropertyChanged;


        /// <summary>テキスト変更時のイベント</summary>
        public event EventHandler<string> TextChanged;


        /// <summary>コンストラクタ</summary>
        public RenameTextBlock() {
            InitializeComponent();
            RenameEnd();
            DataContext = this;
            ShowText.PropertyChanged += (_, _) => {
                //----- 変更時にイベントを発火させる
                if (m_isInputText) {
                    if (TextChanged != null) TextChanged.Invoke(this, ShowText.Value);
                }
            };
        }


        /// <summary>
        /// <para>何らかのキー入力時の処理</para>
        /// <para>@ Memo : 実装としてはRenameStartに委譲します</para>
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void RenameStartKeyDown(object sender, KeyEventArgs e) {
            if (e.Key == KeyDefines.RENAME) {
                RenameStart();
            }
        }
        /// <summary>
        /// <para>ダブルクリック時の処理</para>
        /// <para>@ Memo : 実装としてはRenameStartに委譲します</para>
        /// </summary>
        private void RenameStartMouse(object sender, MouseButtonEventArgs e) {
            RenameStart();
        }


        /// <summary>リネーム中、フォーカスが外れた際の処理</summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void RenameMouseLeave(object sender, MouseEventArgs e) {
            m_isLeave = true;
        }
        /// <summary>フォーカスがあてられているか</summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void RenameMouseEnter(object sender, MouseEventArgs e) {
            m_isLeave = false;
        }
        /// <summary>マウス左の入力時、リネーム終了を行うか判定する</summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void RenameMouseDown(object sender, PreProcessInputEventArgs e) {
            if (e.StagingItem.Input is MouseButtonEventArgs mouseArgs) {
                //----- 左が押されている、かつフォーカスが当たっていない
                if (mouseArgs.LeftButton == MouseButtonState.Pressed && m_isLeave) {
                    RenameEnd();
                }
            }
        }


        /// <summary>リネーム開始処理</summary>
        private void RenameStart() {
            Show.Visibility = Visibility.Collapsed;
            Rename.Visibility = Visibility.Visible;
            InputManager.Current.PreProcessInput += RenameMouseDown;
        }
        /// <summary>リネーム終了処理</summary>
        private void RenameEnd() {
            Show.Visibility = Visibility.Visible;
            Rename.Visibility = Visibility.Collapsed;
            InputManager.Current.PreProcessInput -= RenameMouseDown;
        }


        public string Text {
            get { return ShowText.Value; }
            set { ShowText.Value = value; }
        }
        /// <summary>イベントを発火させないでテキストを設定する</summary>
        public string InputText { 
            set {
                m_isInputText = false;
                ShowText.Value = value;
                m_isInputText = true;
            } 
        }
        public ReactiveProperty<string> ShowText { get; private set; } = new("");
        /// <summary>フォーカスが外れているか</summary>
        private bool m_isLeave = false;
        /// <summary>イベントを発火させるか</summary>
        private bool m_isInputText = true;
    }
}
