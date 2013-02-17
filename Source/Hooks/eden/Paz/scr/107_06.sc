; ファイル: 107_06.txt
;■仕事を優先するを選択。
.message	100		丂峢丂	「没什么为什么吧。我还不得不工作，没办法的事情啊」
.message	110	miy-107_06-0003	傒傗偙	『但是……』
.message	120		丂峢丂	「又不是三岁小孩，懂点事啊」

;■御影チェック
;■　電話を切った際は，それにあわせてボイスが止まるように修正します。
;■　切ったはずなのにボイスがあると変だ。
;■　ただし，一部例外はもうけます（途中で切れるのが逆におかしな場合）。
.playVoice *

.playSE pi.ogg f 0 *
.message	130			我就说了这些，然后毫不留情的挂了电话。
.transition 0 * 20
.stage	* ev01_087a01.png 0 0
.message	140		丂峢丂	「真是的，老这样麻烦别人会让人困扰的啊」
.message	150			虽然被骚扰了是挺可怜的。
.message	160			一个走夜路回家会害怕也可以理解。
.message	170			但是，就因如此为什么我非得去接她不可。
.transition 0 * 20
.stage	* ev01_033b01.png 0 0
.message	180		丂峢丂	「少开玩笑了」
.transition 0 * 40
.stage	* ev01_033a01.png 0 0
;（フェ～ドスピ～ドは20でもいい？）
.message	190			我发着牢骚，再次看向原稿。
.message	200			草稿还剩一堆啊。
.message	210			这次有动作的情节，分格比较多而很耗费时间。
.message	220			嘛，分格的也不是别人正是自己啊。
.message	230		丂峢丂	「现在嗯，不快点结束草稿然后描线的话」
;（ここか３点リ～ダ～の途中で，纮の顔を携帯の方に振り向かせるか？つまり033b01を使うかってこと）
.message	240			……………………
.message	250			…………
.message	260			……
.playSE kusunoki_isu.ogg f 0 *
.transition 0 * 40
.stage	* ev01_093a01.png 0 0
.message	270		丂峢丂	「啊～～～！」
.message	280			我摔下铅笔喊起来。
.message	290			不行，完全没有头绪。
.message	300			不是为何什么不爽起来。
.message	310			在这种状态下画下去也……。
.message	320		丂峢丂	「对了」
.message	330		丂峢丂	「说起来，还没吃过饭呢」
.message	340			所以才会这么难受，嗯。
.transition 0 * 40
.stage	* ev01_093b01.png 0 0
;（ここら辺の３点リ～ダ～も絡めた演出は，しっかりと行っていくこと）
.message	350			…………
.message	360			……
.message	370			买来备用的食料一点不剩。
.message	380		丂峢丂	「对于一个人住这也是必然之一吗……」
.message	390			总之先冷静下来。
.message	400			之所以会变成这样的心情。
.message	410			是因为看过那个笑容之后──不能再无视那家伙所说的话吗。
.message	420			可恶，结果还是变成这样啊──
.transition 0 * 40
.stage	* ev01_093c01.png 0 0
.message	430			一边考虑着遇到宫子时该说什么，我把手伸向了外套。
.panel 0
.playBGM *
.transition 0 * 10
.stage	* WHITE.png 0 0


;■背景：駅前广場（冬），２０時
;■　　　　广野纮　　：私服（冬·外出）
;■　　　　宮村宫子：制服（冬·外出）
.screen sc_night01.png sc_night01.png
.overlay * or_miyako03a01.png
.playBGM efBGM030.ogg
.transition 1 fadeSide.png 10
.stage	* bgw_normal003m11_03.png 0 0 st_miyako03a04.png 400
;（モブ入りにしてあります）
.panel 1
.message	440	miy-107_06-0005	傒傗偙	「太慢了！　太慢了啊！」
.message	450			宫子不满的比我要快。
.message	460		丂峢丂	「那就是你见到自己拜托帮忙的人来时的第一声吗」
.message	470			虽然没说要去接她却还一直等着，让我稍微有些吃惊。
.transition 0 * 40
.stage	* bgw_normal003m11_03.png 0 0 st_miyako05a09.png 400
.message	480	miy-107_06-0007	傒傗偙	「因为，实在是太慢了啊。还在想是不是真的不会来了？」
.message	490		丂峢丂	「也不至于到满眼含泪的地步吧」
.transition 0 * 40
.stage	* bgw_normal003m11_03.png 0 0 st_miyako08a03.png 410
;（表情とポ～ズ，注意のこと）
.message	500	miy-107_06-0009	傒傗偙	「虽然风停了，但还是好～冷好冷呢……」
.message	510			用那种带哭的声音说话太卑鄙了吧。
.message	520			我也不是恶鬼也不是罗刹，良心也会疼的啊。
.message	530		丂峢丂	「知道了啦，我错了行了吧。这样就不生气了吧」
.transition 0 * 40
.stage	* bgw_normal003m11_03.png 0 0 st_miyako07a04.png 410
;（表情とポ～ズ，注意のこと）
.message	540	miy-107_06-0011	傒傗偙	「怎么觉得是在自暴自弃的敷衍我……」
.message	550			公主貌似还是不满意。
.message	560		丂峢丂	「赶快走吧。我还得回去继续工作呢」
.screen * *
.transition 0 * 20
.stage	* bgw_sky001a01_03.png 0 0
;（ここ，空に移行？）
.message	570			我转过身，而宫子也紧紧跟在后面走了起来。


;■背景：十字路
;☆（住宅地から十字路に変更になってるな，，，注意して）
.transition 1 fadeSide.png 20
.overlay	or_miyako03a01_620p.png * *
.screen	sc_night01_620p.png sc_night01_620p.png sc_night01_620p.png
.stage	st_miyako12a02-.png 0 0 bg_scl008a01_03.png 0 0 bg_scl008a01_03.png 0
.effect	WScroll2 * 60 -2


;.screen sc_night01.png sc_night01.png
;.transition 1 fadeSide.png 20
;.stage	* bgw_normal005a01_03.png 0 0
.message	580		丂峢丂	「说起来，到这就行了吧？　你家」
.transition 0 * 40
.stage	st_miyako11a01-.png 0 0 bg_scl008a01_03.png 0 0 bg_scl008a01_03.png 0
;.transition 0 * 40
;.stage	* bgw_normal005a01_03.png 0 0 st_miyako07a04.png 410
;（この前の纮の台詞で宫子の立ち絵表示？）
.message	590	miy-107_06-0013	傒傗偙	「能不能先去下广野君家呢……。现在回去家里也没有人呢」
.message	600		丂峢丂	「……虽然可以。但有一个交换条件，你作饭给我吃」
.transition 0 * 40
.stage	st_miyako11a03-.png 0 0 bg_scl008a01_03.png 0 0 bg_scl008a01_03.png 0
;.transition 0 * 40
;.stage	* bgw_normal005a01_03.png 0 0 st_miyako02a01.png 350
.message	610	miy-107_06-0015	傒傗偙	「嗯，好啊」
.message	620			宫子的脸突然有了光泽。
.transition 0 * 40
.stage	st_miyako11a05-.png 0 0 bg_scl008a01_03.png 0 0 bg_scl008a01_03.png 0
;.transition 0 * 40
;.stage	* bgw_normal005a01_03.png 0 0 st_miyako06a02.png 400
.message	630	miy-107_06-0017	傒傗偙	「那就做海鲜咖喱饭怎么样」
.message	640		丂峢丂	「咖喱？　又要作那些费工夫的东西…」
.message	650			我这边可是饿的要死啊。
.transition 0 * 40
.stage	st_miyako11a10-.png 0 0 bg_scl008a01_03.png 0 0 bg_scl008a01_03.png 0
;.transition 0 * 40
;.stage	* bgw_normal005a01_03.png 0 0 st_miyako06a03.png 400
;（目線注意）
.message	660	miy-107_06-0019	傒傗偙	「要做好吃的东西自然要费相应的工夫啊」
.message	670			突然宫子用像是在询问我反应似的眼睛看着我。
.message	680		丂峢丂	「……知道了，知道了啦。怎样都无所谓了啦」
.message	690		丂峢丂	「那就不得不在回去之前去躺商店街了呢」
;.message	690		丂峢丂	「なら，帰る前に商店街に寄らないとな」
.transition 0 * 40
.stage	st_miyako11a03-.png 0 0 bg_scl008a01_03.png 0 0 bg_scl008a01_03.png 0
;.transition 0 * 40
;.stage	* bgw_normal005a01_03.png 0 0 st_miyako02a01.png 350
.message	700	miy-107_06-0021	傒傗偙	「不愧是广野君。知道人要说什么」
.message	710			宫子的表情一瞬间闪烁起来。
.message	720			还真是突然心情就好了啊。
.message	730		丂峢丂	「另外问下，作的话要费多长时间呢？」
.transition 0 * 40
.stage	st_miyako11a12-.png 0 0 bg_scl008a01_03.png 0 0 bg_scl008a01_03.png 0
;.transition 0 * 40
;.stage	* bgw_normal005a01_03.png 0 0 st_miyako04a02.png 400
.message	740	miy-107_06-0023	傒傗偙	「嗯～，不买材料的话不清楚了啦，但估计会费些工夫呢～」
.message	750		丂峢丂	「不是吧」
.transition 0 * 40
.stage	st_miyako11a17-.png 0 0 bg_scl008a01_03.png 0 0 bg_scl008a01_03.png 0
;（表情，注意して）
.message	760	miy-107_06-0025	傒傗偙	「吃咖喱之前先吃掉我怎样？」
.message	770		丂峢丂	「…………」
.message	780		丂峢丂	「刚才，你说什么了？」

;■御影チェック
;.effect *
.effect end


.overlay	* * *
.screen	* * *
.screen sc_night01.png sc_night01.png
.overlay * or_miyako03a01.png
.transition 0 * 20
.stage	* bgw_normal005a01_03.png 0 0 st_miyako07a03.png 410
;（表情とポ～ズ注意）
.message	790	miy-107_06-0027	傒傗偙	「啊哈哈」
.message	800			宫子把手在胸前挥来挥去。
.message	810	miy-107_06-0029	傒傗偙	「说笑了啦」
.message	820		丂峢丂	「我说你，也差不多少开些这种擦边的玩笑啊」
.transition 0 * 40
.stage	* bgw_normal005a01_03.png 0 0 st_miyako08a01.png 410
;（表情注意）
.message	830	miy-107_06-0031	傒傗偙	「难道不好笑么……」
.message	840		丂峢丂	「你这叫恶趣味，恶趣味」
.transition 0 * 40
.stage	* bgw_normal005a01_03.png 0 0 st_miyako08a02.png 410
；（表情注意）
.message	850	miy-107_06-0033	傒傗偙	「说相声的道路还真是辛苦啊……」
.message	860		丂峢丂	「那种道路不走也行」
.screen * *
.transition 0 * 20
.stage	* bgw_sky001a01_03.png 0 0
.message	870			总之现在是在往商店街走着。
.message	880			大概走了几分钟后。


;■背景：商店街
.screen sc_night01.png sc_night01.png
.transition 1 fadeSide.png 20
.stage	* bgw_normal001m11_03.png 0 0
;（とりあえずモブ入りにしてあります）
.message	890			刚刚到达商店街的时候，宫子突然啪啪的拍了几下我的肩。
;.message	890			目的の商店街が見え始めたところで，宫子はとんとんと俺の肩を叩いた。
.transition 0 * 40
.stage	* bgw_normal001m11_03.png 0 0 st_miyako02a01.png 350
.message	900	miy-107_06-0035	傒傗偙	「喂喂，有一件事想要拜托」
.message	910		丂峢丂	「我说你不觉得拜托太多了吗」
.message	920	miy-107_06-0037	傒傗偙	「不是什么大事啦……好嘛？」
.message	930			反正也拒绝不了的吧。
.message	940			含糊回答也只是浪费时间而已，我点了点头。
.message	950		丂峢丂	「……又干吗」
.transition 0 * 40
.stage	* bgw_normal001m11_03.png 0 0 st_miyako07a01.png 410
;（表情注意）
.message	960	miy-107_06-0039	傒傗偙	「从现在开始呢……称呼你『纮君』可以吗？」
.message	970		丂峢丂	「为啥是敬语捏」
.transition 0 * 40
.stage	* bgw_normal001m11_03.png 0 0 st_miyako07a02.png 410
;（「笑いながら」，，，なので微妙に表情に違和があるかもしれませんが）
.message	980	miy-107_06-0041	傒傗偙	「为啥是大阪腔捏」
.message	990			宫子虽然一边在笑着，但目光却注视着我的反应。
.message	1000			仅仅在期待着一个回答。
.message	1010			如果我要是说出不同的答案呢……？
.message	1020			那样说会怎么样，虽说我也很想知道。
.message	1030		丂峢丂	「随你便了」
.message	1040			但却这样说出来的该算是我的温柔──不对，极限才对吧。
.transition 0 * 40
.stage	* bgw_normal001m11_03.png 0 0 st_miyako02a01.png 350
;（この表情とポ～ズの多用，注意。ポ～ズ変えて，次の宫子の台詞でこの立ち絵を？）
.message	1050	miy-107_06-0043	傒傗偙	「纮君」
.message	1060		丂峢丂	「干吗」
.message	1070	miy-107_06-0045	傒傗偙	「没什么，只是叫叫看」
.message	1080			别那么高兴好吧。
.message	1090			大概我只是──害怕被讨厌而已吧。
.message	1100			在现在来说，应该还没有除此以外的心情。
.panel 0
.screen * *
.overlay * *
.playBGM *
.transition 0 * 10
.stage	* WHITE.png 0 0
.transition 0 * 10
.stage	* WHITE.png 0 0
.wait 100

.chain 108_01.sc
;■108_01へ。

;.end
