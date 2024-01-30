using System;
using System.Collections.Generic;
using System.IO.Packaging;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;
using EtherEngine;
using Newtonsoft.Json.Linq;


namespace EditorUI {
    /// <summary>エディターでDefaultで保持しているシーン</summary>
    public class EditorDefaultScene : Scene {
        /// <summary>コンストラクタ</summary>
        public EditorDefaultScene(string sceneData) {
            SceneData = sceneData;
        }


        /// <summary>シーンのJson文字列を取得する</summary>
        /// <returns></returns>
        public override string GetScene() {
            return SceneData;
        }


        /// <summary>シーンの文字列として扱う文字列</summary>
        public string SceneData { get; set; } = new("");
    }


    /// <summary>シーンの読み書きを行う</summary>
    public static class SceneWriter {
        /// <summary>シーン情報をJsonとして出力する</summary>
        /// <returns></returns>
        public static string SaveScene() {
            //----- ゲームオブジェクトをシリアライズする
            JObject ret = new();
            int i = 0;
            foreach (var gameObject in GameObjectStorage.Get.GameObjects) {
                if (gameObject != null) ret.Add("GameObject " + i, ClassLoader.Output(gameObject));
                i++;
            }

            //----- 返却
            return ret.ToString();
        }


        /// <summary>シーン文字列からシーンを生成する</summary>
        /// <param name="sceneData"></param>
        /// <returns>特別なDefaultシーン</returns>
        public static Scene LoadDataScene(in string sceneData) {
            return new EditorDefaultScene(sceneData);
        }
    }
}
