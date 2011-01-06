# lib2ch

## コンパイル

ライブラリのコンパイル(Mac OS X)

`$ gcc -dynamiclib -o lib2ch.dylib lib2ch.c connection.c -lcurl`

lib2ch.dylibを使ってサンプルコードのコンパイル。

`$ gcc -o main main.c -lm lib2ch.dylib`

サンプルプログラムの実行。ラウンジのスレッド一覧と、最後のスレッドのレスを全て取得して、テキストファイルに書き出す。

`$ ./main yuzuru entrance > ~/Desktop/sample.txt`


##使い方

関数の使い方。(のちのち変更すると思うけど)

Ch構造体の初期化。

`Ch ch;
lib2ch_init(&ch);`

Boardの初期化。第一引数はCh、第二引数はサーバー名、第三引数は板名(entranceなど)

`Board board;
lib2ch_board_init(&board, &ch, args[1], args[2]);`

Threadの初期化。ここでsubject.txt取得。第一引数はBoard。

`Thread thread;
lib2ch_thread_init(&board);`

スレッドのタイトルと番号をThread構造体に格納。以降呼び出すごとにインクリメントに上のスレッドから順に格納。

`lib2ch_get_thread(&board, &thread);`

Responseの初期化。ここでdatファイルを取得。

`Response response;
lib2ch_response_init(&thread);`

レスの各情報(名前、ID、本文、メール、日付)を、例によって呼び出すごとに1から順にResponse構造体に格納。

`lib2ch_get_response(&thread, &response);`

## 積み残しTODO

* 解放していない大量のヒープをなんとかする
* やっつけをなんとかする。タイムアウトとか想定外のことが起きると普通にセグる。
* 差分取得の実装
* gzip転送の実装
* 書き込み機能の実装
* 掲示板一覧の取得
* autoconfとか
