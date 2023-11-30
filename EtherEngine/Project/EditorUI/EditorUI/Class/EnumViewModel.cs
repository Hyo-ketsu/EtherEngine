using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Reactive.Bindings;


namespace EditorUI {
    /// <summary>EnumをViewModelで扱うクラス</summary>
    /// <typeparam name="EnumType"></typeparam>
    public class EnumViewModel<EnumType> where EnumType : Enum {
        public EnumViewModel() {
            //----- Enumをリストに追加
            foreach (var value in Enum.GetValues(typeof(EnumType)).Cast<EnumType>()) {
                Item.Add(value);
            }
        }


        /// <summary>表示する要素</summary>
        public ReactiveCollection<EnumType> Item { get; set; } = new();
        /// <summary>選択している要素</summary>
        public EnumType Select { get { return SelectValue.Value; } set { SelectValue.Value = value; } }
        private ReactiveProperty<EnumType> SelectValue { get; set; } = new();
    }
}
