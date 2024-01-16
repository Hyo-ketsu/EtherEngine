using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Reactive.Bindings;


namespace EditorUI {
    /// <summary>EnumをViewModelで扱うクラス</summary>
    /// <typeparam name="EnumType"></typeparam>
    public class EnumViewModel<EnumType> : INotifyPropertyChanged
        where EnumType : Enum, new() {
        public event PropertyChangedEventHandler? PropertyChanged;


        /// <summary>コンストラクタ</summary>
        public EnumViewModel()
            : this(new EnumType()) {
        }
        /// <summary>コンストラクタ</summary>
        /// <param name="initEnumType">最初から指定するEnum</param>
        public EnumViewModel(EnumType initEnumType) {
            //----- Enumをリストに追加
            foreach (var value in Enum.GetValues(typeof(EnumType)).Cast<EnumType>()) {
                Item.Add(value);
            }

            //----- 現在の選択に追加
            Select = initEnumType;
        }


        /// <summary>表示する要素</summary>
        public ReactiveCollection<EnumType> Item { get; set; } = new();
        /// <summary>選択している要素</summary>
        public EnumType Select { get { return SelectValue.Value; } set { SelectValue.Value = value; } }
        public ReactiveProperty<EnumType> SelectValue { get; private set; } = new();
    }
}
