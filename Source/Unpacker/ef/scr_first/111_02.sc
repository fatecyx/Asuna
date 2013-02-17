; ファイル: 111_02.txt
;■様子を見に行く。
.message	100			总之，去喊一声看看吧。
.message	110			就算是最坏的情况被认为是偷窥，对方是宫子的话就无所谓。
;■ここより白バック
.transition 0 * 20
.stage	* ev01_141a01.png 0 0
;（白バックではなくイベントＣＧで処理してます）
.message	120		丂峢丂	「喂～，宫子」
.message	130		丂峢丂	「…………」
.message	140			没有回答。
.message	150		丂峢丂	「我说喂，宫子！」
.playSE hiro_knock.ogg f 0 *
;（ドンドンッ，，，で音じゃないので，注意されたし。要加工のこと）
.transition 0 * 40
.stage	* ev01_141b01.png 0 0
;（フェ～ドスピ～ドには注意。効果音も用意のこと）

;■御影チェック
;■　SEと文章があわないな。
;■　そこまで強く叩くほど慌てる時間じゃないか。
;.message	160			ドンドンドン！
;.message	170			脱衣所に続くドアを叩きながら呼びかけてみる。
.message	160			咚咚。
.message	170			我一边敲着更衣室的门一边喊。

.transition 0 * 20
.stage	* ev01_141a01.png 0 0
;（フェ～ドスピ～ドは注意。次の台詞でこのＣＧを？）
.message	180		丂峢丂	「…………」
.message	190			果然没有反应。
.message	200		丂峢丂	「……进去了哦」
;■音声加工
.message	210	miy-111_02-0003	傒傗偙	「进来的时候要打报告哦～」
.message	220		丂峢丂	「你还活着吗！」
;■音声加工
.message	230	miy-111_02-0005	傒傗偙	「我已经决定好要把纮君的份一起活下去了啊～」
.message	240		丂峢丂	「我还没死！」
.message	250			可恶，白担心了。
.message	260			这种白痴，扔下不管好了。
;■音声加工
.message	270	miy-111_02-0007	傒傗偙	「谢谢你～」
.message	280		丂峢丂	「哈？」
.message	290			我停下正准备踏出去的脚。
;■音声加工
.message	300	miy-111_02-0009	傒傗偙	「我…刚刚睡着了」
.message	310		丂峢丂	「……你还真没被淹死啊」
;■音声加工
.message	320	miy-111_02-0011	傒傗偙	「我现在就出去……能不能准备一些凉的东西呢」
.message	330			原来如此，看来完全泡头晕了啊。
.message	340		丂峢丂	「出来的时候注意哦」
;■音声加工
.message	350	miy-111_02-0013	傒傗偙	「了～解」
.panel 0
.transition 0 * 10
.stage	* WHITE.png 0 0


;■背景：纮の家の前（冬，２２時
;■　　　　広野纮　　：私服（冬）
;■　　　　宫村宫子：制服（冬）
;.screen sc_night01.png sc_night01.png
;.overlay * or_miyako03a01.png
.playBGM efBGM027.ogg
.transition 1 fadeSide.png 10
.overlay	or_miyako03a01_620p.png * *
.screen	sc_night01_620p.png sc_night01_620p.png sc_night01_620p.png
.stage	st_miyako12a05-.png 0 0 bg_scl008a01_03.png 0 0 bg_scl008a01_03.png 0
.effect	WScroll2 * 60 -2


;.transition 1 fadeSide.png 10
;.stage	* bgw_normal015a01_03.png 0 0 st_miyako08a03.png 410
;（表情注意。もっと元気な表情で？））
;☆（とりあえず通常背景でインしてますが，実際は顔アップ歩きスクロ～ルを）
.panel 1
.message	360	miy-111_02-0015	傒傗偙	「啊～，风好舒服呢～」
.message	370			旁边走着的宫子，啪嗒啪嗒的解开领扣。
.message	380		丂峢丂	「喂喂，干吗呢你」
.message	390			虽然明白你身体现在很热，但这样会感冒的啊。
.transition 0 * 40
.stage	st_miyako11a08-.png 0 0 bg_scl008a01_03.png 0 0 bg_scl008a01_03.png 0
;.transition 0 * 40
;.stage	* bgw_normal015a01_03.png 0 0 st_miyako08a02.png 410
.message	400	miy-111_02-0017	傒傗偙	「不可以吗？」
.message	410			就算你用那么可爱的问法也是不可以。
.message	420			我摇摇头。
.message	430		丂峢丂	「够了赶快给我盖住」
.transition 0 * 40
.stage	st_miyako11a02-.png 0 0 bg_scl008a01_03.png 0 0 bg_scl008a01_03.png 0
;.transition 0 * 40
;.stage	* bgw_normal015a01_03.png 0 0 st_miyako07a02.png 410
;（07a03でも？）
.message	440	miy-111_02-0019	傒傗偙	「是～」
.chain 111_04.sc
;■111_04へ。

;.end
