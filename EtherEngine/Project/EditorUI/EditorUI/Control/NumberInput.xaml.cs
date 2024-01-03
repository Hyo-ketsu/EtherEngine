using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Windows.Controls;
using ControlzEx.Standard;
using Reactive.Bindings;


namespace EditorUI {
    /// <summary>
    /// NumberInput.xaml の相互作用ロジック
    /// </summary>
    public partial class NumberInput : UserControl, INotifyPropertyChanged {
        public event PropertyChangedEventHandler? PropertyChanged;


        public NumberInput() {
            InitializeComponent();
            DataContext = this;
        }


        /// <summary>保持している数値を取得します</summary>
        /// <typeparam name="NumberType">数値（）</typeparam>
        /// <returns></returns>
        public Type? GetNumber<Type>() where Type : IConvertible {
            //----- 取得数値型と保持型が一致しているか
            if (NumberType == null || NumberType != typeof(Type)) {
                throw new Exception("Error! The type held and the type you are trying to retrieve do not match");
            }

            //----- 文字列を数値に変換
            return (Type)Convert.ChangeType(InputNumberText.Value, typeof(Type));
        }
        public void SetNumber<Type>(Type inputNumber) where Type :IConvertible {
            //----- 数値を文字列に変換
            InputNumberText.Value = inputNumber.ToString();
        }


        //----- 文字列を適切に修正する
        private void TextChanged(object sender, TextChangedEventArgs e) {
            //----- 現在実行中かのチェック
            if (IsTextChanged) return;
            IsTextChanged = true;

            //----- 変数宣言
            string newText = new("");
            bool isPeriod = false;  // ピリオドがすでに入力されていたか

            //----- 入力が指定された文字以外か判定
            for (int i = 0; i < InputNumber.Text.Length; i++) { 
                //----- 文字取得
                var letter = InputNumber.Text[i];

                //----- 入力された文字列が各型と合致しているか判定
                // @ Memo : 以下の正しくない入力が検知された際入力を終了します
                //----- 0~9の数値、マイナス、小数点以外
                if (char.IsDigit(letter) == false && letter != '-' && letter != '.') break;

                //----- 型が非符号なのに - が入力されている
                if ((NumberType == typeof(uint) || NumberType == typeof(ulong) || NumberType == typeof(ushort)) && letter == '-') break;

                //----- 先頭以外での - の入力
                if (i > 0 && letter == '-') break;

                //----- 小数点の入力？
                if (letter == '.') {
                    //----- すでに小数点は入力されている。不正
                    if (isPeriod) break;

                    //----- 先頭、もしくはマイナスの後の小数点であれば頭に0を足す
                    if (i == 0 || i == 1 && InputNumber.Text[0] ==  '-') {
                        newText += '0';
                    }

                    //----- 入力フラグの入力
                    isPeriod = true;
                }

                //----- 入力された文字は問題ない。追加
                newText += letter;
            }

            //----- 文字の入力
            InputNumber.Text = newText;

            //----- 修正終了
            IsTextChanged = false;
        }


        /// <summary>TextChangedを行っている最中か</summary>
        private bool IsTextChanged { get; set; } = false;
        /// <summary>保持している番号型</summary>
        public Type? NumberType { get; set; }
        /// <summary>保持している数値(UI・内部用)</summary>
        public ReactiveProperty<string> InputNumberText { get; private set; } = new();
    }
}
