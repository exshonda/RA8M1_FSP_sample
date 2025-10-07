# ルネサスFSPを用いたサンプルプログラム

## フォルダ
- baremetal_ek_ra8m1_ep
  - ルネサスのベアメタルサンプル
    - https://github.com/renesas/ra-fsp-examples/tree/master/example_projects/ek_ra8m1/baremetal/baremetal_ek_ra8m1_ep
    - DOCの確認後，無限ループでLEDの点灯とログ出力を行う
  - 変更点
    - GPIO出力
      - P601/P602を使用
    - LEDの周期点滅
    - S1/S2による割込み
      - 
- doc_tz_ek_ra8m1
  - ルネサスのTZのサンプル
    - https://github.com/renesas/ra-fsp-examples/tree/master/example_projects/ek_ra8m1/trustzone/doc
  - SC関数
    - LEDの操作
      -  fsp_err_t led_set_guard (bsp_io_port_pin_t pin, bsp_io_level_t level)
   -  DOCのイベント取得
      -  doc_event_t doc_cfg_event_read_guard (void)
   -  DOCのドライバのガード関数
      -  g_doc_guard.c
  - 周辺回路
    - S
      - S2(IRQ12)割込み
        - ボタンを押すと g_external_irq12_callback() が実行される
      - IOポート
        - P601 : S2が押されると，g_external_irq12_callback() 内で1us間HIGHにする
        - P602 : led_set_guard()が実行されるとHIGH->LOWとする
    - NS
      - S1(IRQ13)割込み
        - ボタンを押すと g_external_irq13_callback() が実行される
          - 一定周期でLED2をトグルする
      - IOポート
        - P603 : メインループでHIGH/LOWを繰り返す
        - P604 : S1が押されると，g_external_irq13_callback() が実行される

## 使用方法
- ワークスペースの作成とインポート
  - cloneしたフォルダを指定
  - ファイル -> インポート -> 既存プロジェクトをワークスペースへ
  - 参照 -> フォルダの選択
    - 3つのプロジェクトが表示されるので，終了を乙

- baremetal_ek_ra8m1_ep
  - プロジェクトのツリーを開く
  - configuration.xml をダブルクリック
    - 表示されるペインの"Generate Project Content"を押す
  - ビルド
  - デバッグ
    - プロジェクトフォルダで右クリック -> デバッグ -> 一番下の項目を選択
    
- doc_tz_ek_ra8m1
  - セキュアプロジェクト（doc_s_tz_ek_ra8m1）を対象に
    - configuration.xml をダブルクリック
      - 表示されるペインの"Generate Project Content"を押す
    - ビルド
  - ノンセキュアプロジェクト（doc_ns_tz_ek_ra8m1）を対象に
    - configuration.xml をダブルクリック
      - 表示されるペインの"Generate Project Content"を押す
    - ビルド
  - 実行
    - ノンセキュアプロジェクト（doc_ns_tz_ek_ra8m1）を対象に
       - プロジェクトフォルダで右クリック -> デバッグ -> 一番下の項目を選択

## RA8MP1の基本
- 割込み
  - NVICがサポートする本数より多いので，一旦ICUで受けてNVICに設定
  - IELSRで設定
  - イベント番号
    - IRQ12 : 0x0d
    - IRQ13 : 0x0e

## FSPの基本
- Secureで使用しないデバイスやピンはすべてNonSecureから操作可能．
- 割込みも同様

## TrustZone

### SC関数の書き方

```
  - Secure 関数には次のプラグマを関数の先頭に入れる
/* Non secure callable function that returns g_doc_cfg.event */
BSP_CMSE_NONSECURE_ENTRY doc_event_t doc_cfg_event_read_guard (void)
{
    return g_doc_cfg.event;
}
```

### FSPのコンポーネントをNonSecureから呼び出す方法
- Secure側にドライバを置き，NonSecureからはガード関数を経由して呼び出す
- Secure
  - Stacksのタブでコンポーネントを右クリックして Non-Secure Callable を選択する．
    - FSP の API_guard というSC関数をSecureユーザーが用意する必要がある
- Non-Secure
  - Stacksのタブで New Stack -> Use Secure からSecure側ののスタックを選択する

### IRQとIOポートをNonSecureに分配する方法
- 対象のIRQのピンをSecureでコンフィギュレーションしないようにする．
- NonSecureで通常のSecureと同じようにスタックを追加する．


## プロジェクトのビルド
- configure.xml をダブルクリックして FSP Configuration を起動
- 右上の Generate Project Content のボタンを押す
- 左のプロジェクトを指定して右クリックしてビルド

## デバッグ
- 左のプロジェクトを指定して右クリックしてDebu 
- 
## ログの出力方法
- 概要
  - ルネサスのサンプルのコンソール出力はUARTではなく，デバッガ経由で出力される
  - 出力されたログは，J-Link RTT Viwer 経由で見る
- 使用方法
  - e2studioでデバッグを開始する
  - RTT Viewrを起動
  - 1回のみ以下の選択を実施
    - File -> Conect を選択
      - Connection to J-Link
        - Existing Session
      - RTT Control Block
        - Search Range
          - 0x22000000 0x80000
- 再接続
- File -> Connect を選択

## GPIOの出力として使用
- FSPコンフィギュレータから対象のピンを選択してOutPut modeに設定
- 出力用マクロ
  - R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_06_PIN_01, BSP_IO_LEVEL_HIGH);

## GPIOの入力（割込み）として使用  
- S2:P008(IRQ12)
- S1:P009(IRQ13)
- FSPの操作
  - Stacksタブ
    - New Stack > Input > ICU > External IRQ を追加（例: g_external_irq0）。
    - Trigger: Falling Edge（プルアップ＋GND落ちで押下検出）
    - IRQ Priority: 適切な優先度（例: 2）
    - Digital Filter: 有効にするとチャタリング対策になります
    - Callback : g_external_irq0_callback
（例: Enable、Filter Clock: PCLK/64 など）
  - Pinsタブ
    - スイッチに接続したピンを Mode: IRQ に設定し、該当の IRQチャネル を一致させます（例: P105 → IRQ8 など、ボード配線に合わせる）。
    - 可能なら内部プルアップ（Pull-up）を有効化。外付け回路に合わせて調整。
    - Clock/Interrupts
    - 既定でOK。必要ならICUに供給されるPCLK設定を確認。
  - Generate Project Content を実行