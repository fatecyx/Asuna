; ファイル: 111_03.txt
;■気にしないを選択。
.message	100			宫子也不是小孩子了，不管她应该没事的吧。
.transition 0 * 20
.stage	* ev01_142.png 0 0
.message	110			拉起袖子看向自己的右腕。
.message	120		丂峢丂	「总之这次也算熬过了啊……啊」
.message	130			帖满绷布的手腕已经失去痛感只有麻痹了。
.message	140			果然在短时间要画大量的画的话，对于手腕的负担太大。
.message	150			虽然如果计划好时间，让手腕能有所休息的画下去的话，可能会稍微好一点……。
.message	160			但在不得不去学校的前提下是行不通的。
.message	170		丂峢丂	「嘛，只有这样继续欺骗下去啊」
.message	180			不会去说让连载停下之类的话，因为本身就不想停下。
.message	190			如果停下的话，就会有离漫画越来越远的感觉。
.message	200			不得不一直硬撑着继续欺骗自己──继续欺骗周围的人。
;☆（↑句点がありません。要修正を）
.transition 0 * 20
.stage	* ev01_142_mugai_a.png 0 0
;（この切り出しでいいか注意のこと。もう少し手の平，左寄りに？）
.message	210		丂峢丂	「到底会持续到什么时候呢……」
.playSE miyako_taoreru.ogg f 0 *
;（音は仮です）
.message	220			噗通！
.transition 0 * 20
.stage	* ev01_143.png 0 0
;（フェ～ドスピ～ドは40で？表示タイミングも，この一つ前の文で？）
.message	230		丂峢丂	「呜哇！！」
.message	240			怎，怎么回事！？
.message	250			突然响起的声音差点把我吓的挑起来。
.playSE *
.message	260		丂峢丂	「啊～，吓死我了……」
.message	270		丂峢丂	「浴室吗？」
.message	280			宫子那笨蛋好象又作了什么。
.message	290			我慌忙站起来跑了过去。
.panel 0
.transition 0 * 10
.stage	* WHITE.png 0 0


;■背景：纮の家の前（冬，２２時
;■　　　　广野纮　　：私服（冬·外出）
;■　　　　宫村宫子：制服（冬·外出）
;.screen sc_night01.png sc_night01.png
;.overlay * or_miyako03a01.png
.playBGM efBGM027.ogg
.transition 1 fadeSide.png 10
.overlay	or_miyako03a01_620p.png * *
.screen	sc_night01_620p.png sc_night01_620p.png sc_night01_620p.png
.stage	st_miyako11a13-.png 0 0 bg_scl008a01_03.png 0 0 bg_scl008a01_03.png 0
.effect	WScroll2 * 60 -2


;.transition 1 fadeSide.png 10
;.stage	* bgw_normal015a01_03.png 0 0 st_miyako08a01.png 410
;☆（とりあえず通常背景でインしてますが，実際はここも顔アップ歩きスクロ～ルを？）
.panel 1
.message	300	miy-111_03-0003	傒傗偙	「啊～，说起来还真是吓坏了呢。突然眼前就全白一片」
.message	310		丂峢丂	「被吓到的是我好吧」
.message	320			由于洗澡太长时间而头晕的宫子，再打开浴室门走进更衣室的时候就倒下了。
.message	330			没有伤到头部实在是不幸中的万幸。
.message	340			不过意外的意识却十分清晰，由于其本人希望而两人一起出门开始夜间散步。
.message	350		丂峢丂	「啊啊，干脆把你那糨糊头也撞正常就好了。为什么你会泡到那种不省人事的地步啊」
.transition 0 * 40
.stage	st_miyako11a16-.png 0 0 bg_scl008a01_03.png 0 0 bg_scl008a01_03.png 0
;.transition 0 * 40
;.stage	* bgw_normal015a01_03.png 0 0 st_miyako01a04.png 400
;（表情とポ～ズ注意）
.message	360	miy-111_03-0005	傒傗偙	「小事啦～。因为确实是很舒服的水呢……」
.message	370			真是的，到底在干什么呢。
.message	380			不搞出点事故就不舒服么。
.chain 111_04.sc
;■111_04へ。

;.end
