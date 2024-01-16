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


namespace EditorUI {
    /// <summary>View Model</summary>
    public class LanguageButtonVM : INotifyPropertyChanged {
        public event PropertyChangedEventHandler? PropertyChanged;


        /// <summary>コンストラクタ</summary>
        public LanguageButtonVM() {
            Language.SelectValue.Value = EditorSetting.Get.Language.Value;
            Language.SelectValue.Subscribe(language => {
                EditorSetting.Get.Language.Value = language;
            });
        }


        /// <summary>言語設定</summary>
        public EnumViewModel<EditorLanguageEnum> Language { get; private set; } = new();
    }


    /// <summary>
    /// LanguageButton.xaml の相互作用ロジック
    /// </summary>
    public partial class LanguageButton : UserControl {
        public LanguageButton() {
            InitializeComponent();
        }
    }
}
