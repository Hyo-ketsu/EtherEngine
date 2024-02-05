using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;


namespace EditorUI {
    /// <summary>Inspectorを拡張する際の抽象クラス</summary>
    public abstract class InspectorExtension {
        /// <summary>表示物を取得する</summary>
        /// <returns></returns>
        public abstract FrameworkElement GetFramework();
    }


    /// <summary>
    /// <para>型の表示差し替え属性のスーパークラス</para>
    /// <para>@ Memo : 表示拡張を直接型に付与するのではなく、別で記述する形を取っています。</para>
    /// <para>@ Memo : (エディター拡張を直接記述しなければならないのはまずいと思ったためです)</para>
    /// </summary>
    [AttributeUsage(AttributeTargets.Class, AllowMultiple = false, Inherited = true)]
    abstract public class InspectorTypeBaseAttribute : Attribute {
        /// <summary>コンストラクタ</summary>
        /// <param name="type">表示対象の属性</param>
        /// <param name="thisType">拡張に使用する自身のクラス</param>
        public InspectorTypeBaseAttribute(Type type, Type thisType) {
            //----- InspectorGetUIElementを継承しているか
            if (thisType.IsSubclassOf(typeof(InspectorExtension)) == false) {
                //----- 継承していない。エラー
                throw new Exception($"Error! {thisType.FullName} does not inherit {typeof(InspectorExtension).Name}.");
            }

            //----- 生成して追加する
            var instance = Activator.CreateInstance(thisType);
            InspectorCreateClasss.Add((GetType(), type), instance as InspectorExtension); // 上で継承しているのは確実なのでnullはない
        }


        /// <summary>エディター拡張を取得します</summary>
        /// <typeparam name="ThisType">自身の型</typeparam>
        /// <param name="type">エディター拡張を取得する型</param>
        /// <returns>取得されたInspectorの表示物(Null許容)</returns>
        protected static FrameworkElement? GetInspectorExtension<ThisType>(Type type) 
            where ThisType : InspectorTypeBaseAttribute {
            //----- 型からインスタンスを取得する
            if (InspectorCreateClasss.TryGetValue((typeof(ThisType), type), out var instance)) {
                //----- 取得できた。コントロールを取得して返却
                return instance.GetFramework();
            }

            //----- 取得できない。Nullを返却
            return null;
        }


        /// <summary>表示物を生成するクラスのインスタンス</summary>
        private static Dictionary<(Type, Type), InspectorExtension> InspectorCreateClasss { get; set; } = new();
    }


    /// <summary>型のヘッダー表示を差し替える属性</summary>
    public class InspectorTypeHeaderAttribute : InspectorTypeBaseAttribute {
        /// <summary>コンストラクタ</summary>
        /// <param name="type">表示対象の属性</param>
        /// <param name="thisType">拡張に使用する自身のクラス</param>
        public InspectorTypeHeaderAttribute(Type type, Type thisType)
            : base(type, thisType) {
        }


        /// <summary>エディター拡張を取得します</summary>
        /// <param name="type">エディター拡張を取得する型</param>
        /// <returns>取得されたInspectorの表示物(Null許容)</returns>
        public static FrameworkElement? GetInspectorExtension(Type type) {
            return GetInspectorExtension<InspectorTypeHeaderAttribute>(type);
        }
    }
    /// <summary>型の表示自体を差し替える属性</summary>
    public class InspectorTypeShowAttribute : InspectorTypeBaseAttribute {
        /// <summary>コンストラクタ</summary>
        /// <param name="type">表示対象の属性</param>
        /// <param name="thisType">拡張に使用する自身のクラス</param>
        public InspectorTypeShowAttribute(Type type, Type thisType) 
            : base(type, thisType) {
        }


        /// <summary>エディター拡張を取得します</summary>
        /// <param name="type">エディター拡張を取得する型</param>
        /// <returns>取得されたInspectorの表示物(Null許容)</returns>
        public static FrameworkElement? GetInspectorExtension(Type type) {
            return GetInspectorExtension<InspectorTypeShowAttribute>(type);
        }
    }
    /// <summary>型の最後に表示物を追加する属性</summary>
    public class InspectorTypeBackShowAttribute : InspectorTypeBaseAttribute {
        /// <summary>コンストラクタ</summary>
        /// <param name="type">表示対象の属性</param>
        /// <param name="thisType">拡張に使用する自身のクラス</param>
        public InspectorTypeBackShowAttribute(Type type, Type thisType)
            : base(type, thisType) {
        }


        /// <summary>エディター拡張を取得します</summary>
        /// <param name="type">エディター拡張を取得する型</param>
        /// <returns>取得されたInspectorの表示物(Null許容)</returns>
        public static FrameworkElement? GetInspectorExtension(Type type) {
            return GetInspectorExtension<InspectorTypeBackShowAttribute>(type);
        }
    }
}
