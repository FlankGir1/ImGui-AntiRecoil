[ Readme ]  
[English](https://github.com/FlankGir1/ImGui-AntiRecoil/blob/main/README-en.md)

ApexLegendsで最も使われたであろうアンチリコイルの外部ソフトウェア。  
人々はこれを"ジッターマクロ"と呼びました。

# ImGui-AntiRecoil
* ImGuiを使用した比較的シンプルなアンチリコイルツール。
* 設定の保存/読み込み機能が削除されているので実装はご自身でお願いします。

![image](https://user-images.githubusercontent.com/124275926/222131768-5e7c8776-ee33-4fa6-9ae7-faed57763fca.png)

## 特徴 / 機能
* Randomize  
  -> (未完成ですが) 値をランダム化
* Sound  
  -> 切り替えキーを押して有効/無効を切り替えた時にビープ音を鳴らす
* 3つのモード  
  -> 真下に動く通常モード、左右に動くジッターモード、ひし形のような挙動のCircleモード
* KeyBinder  
  -> ボタンを押して対象のキーを押すだけで簡単にキーの割り当てが可能
* Window HIDER  
  -> 自身のウィンドウを非表示にする。プログラムは引き続き実行されます。  
     ※キーの割り当て後、すぐにウィンドウが非表示になってしまいます。割り当てたキーを押せば再度表示されます。

## 使い方
* VisualStudioで"Release + x64"でビルドする

## 注意
* 各ゲームのアンチチートにより検出/BANされる危険性があります。
* 自己責任で使ってください。

### Credit
* ImGui  
https://github.com/ocornut/imgui
