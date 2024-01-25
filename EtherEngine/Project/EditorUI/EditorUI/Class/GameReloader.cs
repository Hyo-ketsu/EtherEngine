using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using Microsoft.Build.Evaluation;
using Microsoft.Build.Execution;
using Microsoft.Build.Framework;
using Microsoft.Build.Logging;
using System.Threading;
using System.Xml.Linq;
using EtherEngine;


namespace EditorUI {
    /// <summary>アセンブリのビルドを行う</summary>
    public class GameReloader {
        /// <summary>インスタンスの取得</summary>
        static public GameReloader Get {
            get {
                if (Instance == null) {
                    Instance = new();
                }

                return Instance;
            }
        }


        /// <summary>コンストラクタ</summary>
        private GameReloader() {
            //----- プロジェクト作成
            ProjectCreate();
        }


        /// <summary>プロジェクトのビルド</summary>
        /// <param name="configuration">ビルド種類</param>
        public void ProjectLoad(BuildConfiguration configuration) {
            //----- 現在ビルド中なら何もしない
            // @ MEMO : 現在はシングルスレッドでのアクセスを想定しているためboolでいい。マルチスレッドでアクセスするつもりがあるならlock使って
            if (m_isBuild) return;

            //----- プロジェクトがなければ作成しておく
            ProjectCreate();

            //----- 変数宣言
            var sln = Path.Combine(Directory.GetCurrentDirectory(), EditorDefine.GameSourceSolutionName);    // ソリューションのパス

            //----- プロジェクトコレクションの作成
            var projectCollection = new ProjectCollection();
            var globalProperty = new Dictionary<string, string> {
                { "OutputType", configuration == BuildConfiguration.Debug ? "Library" : "Exe" },
                { "Configuration", configuration.ToString() },
            };

            //----- ビルドロガーの用意
            var gameLoaderLogger = new GameLoaderLogger();
            var buildParameters = new BuildParameters(projectCollection) {
                Loggers = new ILogger[] { gameLoaderLogger }
            };

            //----- ビルドスレッド立ち上げ
            m_isBuild = true;
            var buildTask = Task.Run(() => {
                //----- シーンファイル一斉捜査
                //@ MEMO : ビルドするときに.sceneの中身(Json)を.csに出力、Sceneを継承したクラスとして同時にビルドさせる

                //----- Nugetの初期化
                var restoreRequest = new BuildRequestData(sln, globalProperty, null, new[] { "Restore" }, null);
                var buildResult = BuildManager.DefaultBuildManager.Build(buildParameters, restoreRequest);

                //----- ビルドを行う
                var buildRequest = new BuildRequestData(sln, globalProperty, null, new[] { "Build" }, null);
                buildResult = BuildManager.DefaultBuildManager.Build(buildParameters, buildRequest);

                //----- ビルド完了
                m_isBuild = false;

                //----- DLLのロード
                if (configuration == BuildConfiguration.Debug) {
                    //----- メインプロジェクトから出力ディレクトリを取得
                    string outputPath = null;
                    var project = XDocument.Parse(EditorDefine.GameSourceSolutionSource);
                    var nameSpace = project.Root.Name.Namespace;
                    foreach (var propGroup in project.Descendants(nameSpace + "PropertyGroup")) {
                        var condition = propGroup.Attribute("Condition")?.Value;
                        if (condition == "'$(Configuration)|$(Platform)'=='Debug|AnyCPU'") {
                            outputPath = propGroup.Element(nameSpace + "OutputPath")?.Value;
                        }
                    }

                    //----- リロードを行う
                    GameApplication.Get.IsGameUpdate = false;   // ゲームの更新を止め、更新停止イベントで処理する
                    GameApplication.Get.GameLoopStopEvent += (_, _) => {
                        //----- 現在シーン状況出力
                        var sceneData = SceneWriter.SaveScene(EtherEngine.SceneLoader)

                        //----- assemblyのロード
                        AssemblyHolder.Get.LoadAssemblyPath = outputPath;
                        AssemblyHolder.Get.LoadAssembly();

                        //----- シーンを再読み込み

                    }
                }
            });

            //----- メッセージスレッド立ち上げ
            var messageTask = Task.Run(() => {
                while (m_isBuild) {
                    //----- 変数宣言
                    EditorLog log = null;

                    //----- ロガーからログを取得
                    lock (gameLoaderLogger.LockObject) {
                        //----- ログが追加されていないなら無視する
                        if (gameLoaderLogger.Logs.Count == 0) {
                            Thread.Sleep(1);
                            continue;
                        }

                        //----- ログを取得
                        log = gameLoaderLogger.Logs[0];
                        gameLoaderLogger.Logs.Remove(log);
                    }

                    //----- ログを追加
                    LogSystem.Get.AddLog(log);
                }
            });
        }


        /// <summary>プロジェクト作成</summary>
        public void ProjectCreate() {
            //----- 変数宣言
            string path = Path.Combine(Directory.GetCurrentDirectory(), EditorDefine.GameSourceMainName);

            //----- エントリーポイントがあるか
            if (Path.Exists(path) == false) {
                //----- ない。作成
                File.WriteAllText(path, EditorDefine.GameSourceMainSource);
            }

            //----- csprojが存在するか
            path = Path.Combine(Directory.GetCurrentDirectory(), EditorDefine.GameSourceProjectName);
            if (Path.Exists(path) == false) {
                //----- ない。作成
                File.WriteAllText(path, EditorDefine.GameSourceProjectSource);
            }

            //----- slnが存在するか
            path = Path.Combine(Directory.GetCurrentDirectory(), EditorDefine.GameSourceSolutionName);
            if (Path.Exists(path) == false) {
                //----- ない。作成
                File.WriteAllText(path, EditorDefine.GameSourceSolutionSource);
            }
        }


        /// <summary>保持しているインスタンス</summary>
        static private GameReloader? Instance { get; set; }
        /// <summary>ビルドしているか</summary>
        private bool m_isBuild;
    }
}
