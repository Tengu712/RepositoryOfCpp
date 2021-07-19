# DirectX11学習録

## コーディング

命名規則は以下のようにする。

* クラス名、構造体名、列挙型名は大文字開始
* 関数名・メソッド名は小文字開始
* const定数は接頭辞k
* ポインタは接頭辞p
* ハンドルは接頭辞h
* マクロ定数はすべて大文字
* 役割を先頭に（カウンタならcnt、結果ならres）
* ofの順（numやdescが先）

スコープはできるだけ小さくする。所謂グローバル変数は作らない。まとまった処理は一つのブロックに統括する。

変数の変更回数はできるだけ少なくする。できるだけ初期化処理の直前に宣言を置く。

COMコンポーネントについては、ComPtrスマートポインタを用いる。

情報オブジェクトをstructで、一般オブジェクトをclassで定義する。

ラッパーライブラリの実践的な実装は、アプリケーション側に委ねる。

管理クラスは「実装を便利にするメソッド群」であって、これに依存することはない。

## 画面クリア

初期化後も必要なインターフェイスは以下。

* ID3D11Device：バッファ等を作成
* ID3D11DeviceContext：描画系を司る
* IDXGISwapChain：ダブルバッファリングを司る
* ID3D11RenderTargetView：バックバッファとバインドされた描画先

初期化手順は以下。

1. IDXGIFactory作成
2. D3D11CreateDeviceでID3D11DeviceとID3D11DeviceContext作成
3. IDXGIFactory::CreateSwapChainでIDXGISwapChain作成
4. IDXGISwapChain::GetBufferでバックバッファ(ID3D11Texture2D)取得
5. ID3D11Device::CreateRenderTargetViewでバックバッファからID3D11RenderTargetView作成

描画手順は以下。

1. （ID3D11DeviceContext::OMSetRenderTargetsでレンダーターゲット指定）
2. 色を指定するfloat配列作成
3. ID3D11DeviceContext::ClearRenderTargetViewでレンダーターゲットをクリア
4. IDXGISwapChain::Presentでスワップ

ただ、Presentの第一引数を0UにするとGPUが全力稼働してしまう。1Uにすると垂直同期が取られると考えて良いか。

## デプス・ステンシルバッファ

要調査

## HLSL 5.0

fxc.exeで以下のように.hファイルへコンパイルする。

```
fxc /T vs_5_0 /E vs_main /Fh ../directx/include/vshader.h ../directx/shader.vsh
fxc /T ps_5_0 /E ps_main /Fh ../directx/include/pshader.h ../directx/shader.psh 
```

インターフェイスはID3D11VertexShaderとID3D11PixelShader。以下のように作成できる。

```c++
m_pDevice->CreateVertexShader(g_vs_main, sizeof(g_vs_main), nullptr, m_pVShader.GetAddressOf());
```

必須のセマンティクスは以下。

* バーテックスシェーダ
  * 入力
    * POSITION[n]：頂点位置（w座標は自動的に1になる？）
    * COLOR[n]：頂点色
  * 出力
    * SV_Position：均質空間における頂点位置
* ピクセルシェーダ
  * 入力
    * SV_Position：（何故必要？）
    * COLOR[n]：（補完された色？）
  * 出力
    * SV_Target：

変換行列は定数バッファで転送する。ただし、何故か転置する必要がある。

## ポリゴン描画

UNDER CONSTRUCTION