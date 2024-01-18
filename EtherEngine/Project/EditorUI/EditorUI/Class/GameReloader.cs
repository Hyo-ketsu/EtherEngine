using System;
using System.Collections;
using System.Collections.Generic;
using Microsoft.CodeAnalysis;
using Microsoft.CodeAnalysis.CSharp;
using Microsoft.CodeAnalysis.Emit;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Reflection.Emit;
using System.Reflection;


namespace EditorUI {
    /// <summary>アセンブリのビルドを行う</summary>
    public static class GameReloader {
        static GameReloader() {
            //----- デフォルト設定属性追加
            AddType(typeof(object));

            //----- デフォルト設定アセンブリ追加
            AddAssembly("System");
            AddAssembly("System.Runtime");
            AddAssembly("EngineLibrary");
            AddAssembly("EtherEngine");
        }


        public static void ProjectLoad() {
            //----- カレントディレクトリの直下にDLLフォルダ作成
            Directory.CreateDirectory(Directory.GetCurrentDirectory() + Path.DirectorySeparatorChar +  EditorDefine.DLLDirectoryName);
            
            //----- 全ての.csファイル取得
            var csFiles = Directory.GetFiles(Directory.GetCurrentDirectory(), "*.cs", SearchOption.AllDirectories);

            //----- .csファイルを読み取る
            var fileStrings = new string[csFiles.Length + 1];

            //----- 読み取り
            for (int i = 0; i < csFiles.Length; i++) {
                fileStrings[i] = File.ReadAllText(csFiles[i]);
            }

            //----- 最後にエントリーポイントを追加する
            fileStrings[fileStrings.Length - 1] =
                @"using System; public class EntryPoint { public static void Main(void) { Console.WriteLine(""Hoge""); Console.ReadKey(); } }";

            //----- アセンブリ用変数宣言
            var references = new MetadataReference[m_types.Count + m_assembly.Count];

            //----- アセンブリ追加
            int j = 0;
            for (;j < m_assembly.Count; j++) {
                //----- 変数宣言
                Assembly assembly = null;

                //----- アセンブリ読み込み（見つかるまで走査）
                string path;
                do {
                    //----- DLLディレクトリ
                    path = Directory.GetCurrentDirectory() + EditorDefine.DLLDirectoryName + m_assembly[j];
                    if (File.Exists(path)) break;
                    //----- カレントディレクトリ
                    path = Directory.GetCurrentDirectory() + m_assembly[j];
                    if (File.Exists(path)) break;
                    //----- エンジンディレクトリ
                    path = EditorDirectory.Directory + m_assembly[j];
                    if (File.Exists(path)) break;

                    //----- アセンブリ読み込み
                    try {
                        assembly = Assembly.Load(m_assembly[j]);
                        path = null;
                        break;
                    }
                    catch {
                        //----- ない。終了する
                        LogSystem.Get.AddLog(new EditorLog(MessageType.Error, $"BuildError : {m_assembly[j]} assembly is missing."));
                        return;
                    }
                } while (false);

                //----- パスの読み込み
                if (path != null) {
                    assembly = Assembly.LoadFrom(path);
                }

                //----- 配列に追加
                references[j] = MetadataReference.CreateFromFile(assembly.Location);
            }
            //----- 属性追加
            for (int k = 0; k < m_types.Count; j++, k++) {
                references[j] = MetadataReference.CreateFromFile(m_types[k].Assembly.Location);
            }

            //----- アセンブリの取得

            //----- 以下テスト
            List<SyntaxTree> syntaxTrees = new();
            foreach (var code in fileStrings) {
                syntaxTrees.Add(CSharpSyntaxTree.ParseText(code));
            }

            // コンパイルオプションを設定（ここでは、出力種別をConsoleApplicationに設定）
            var options = new CSharpCompilationOptions(OutputKind.ConsoleApplication);

            // コンパイルオブジェクトを作成
            var compilation = CSharpCompilation.Create("MyAssembly", syntaxTrees, options: options);

            // 実行可能なアセンブリを出力
            using (var file = File.OpenWrite("MyAssembly.exe")) {
                var result = compilation.Emit(file);
                if (result.Success) {
                    //----- 正常処理
                }
                else {
                    //----- 異常処理
                    IEnumerable<Diagnostic> failures = result.Diagnostics.Where(diagnostic =>
                        diagnostic.IsWarningAsError ||
                        diagnostic.Severity == DiagnosticSeverity.Error);

                    foreach (Diagnostic diagnostic in failures) {
                        Console.Error.WriteLine("{0}: {1}", diagnostic.Id, diagnostic.GetMessage());
                    }
                }
            }
        }


        /// <summary>追加する属性</summary>
        /// <param name="type"></param>
        public static void AddType(Type type) {
            m_types.Add(type);
        }
        /// <summary>追加するassembly</summary>
        /// <param name="type"></param>
        public static void AddAssembly(string assembly) {
            m_assembly.Add(assembly);
        }
        /// <summary>アセンブリ追加時に使用する型</summary>
        private static List<Type> m_types = new();
        /// <summary>ロードするassembly名</summary>
        private static List<string> m_assembly = new();
    }
}
