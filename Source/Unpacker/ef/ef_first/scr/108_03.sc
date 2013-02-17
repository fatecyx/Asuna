; ファイル: 108_03.txt
;■宫子好感度(＜2)
.message	100		丂峢丂	「嘛，居然被缠了那么久」
.transition 0 * 40
.stage	* bgc_sch002a01_02.png 0 0 st_miyako06a01.png 400
;（表情注意）
.message	110	miy-108_03-0003	傒傗偙	「还真是能那样一句接一句的说下去呢。感觉就象是对着学生在发散压力一样」
.message	120		丂峢丂	「我们这样的不正是好目标么」
.message	130			在音羽学园内认真的学生比较多，没有疼爱对象老师也会觉得无聊的吧。
.message	140		丂峢丂	「而且这次，连反驳的余地都没有是我们的失策啊」
.transition 0 * 40
.stage	* bgc_sch002a01_02.png 0 0 st_miyako05a10.png 400
.message	150	miy-108_03-0005	傒傗偙	「那个老师，能不能用偷窥或者性骚扰之类的罪名抓起来呢」
.transition 0 * 40
.stage	* bgc_sch002a01_02.png 0 0 st_miyako02a03.png 350
.message	160	miy-108_03-0007	傒傗偙	「说起来，说在指导室被性骚扰能不能作到呢。纮君，能和我凑口供吗？」
.message	170		丂峢丂	「……我说你，太狠了吧」
.message	180			完全没有反省也就算了，还陷害教师。
.message	190			真是可怕的女人啊……。
.transition 0 * 40
.stage	* bgc_sch002a01_02.png 0 0 st_miyako02a02.png 350
;（表情注意。ここは前の表情を継続させて？）
;.stage	* bgc_sch002a01_02.png 0 0 st_miyako06a04.png 400
.message	200	miy-108_03-0009	傒傗偙	「还有更多更有效的办法呢……。计划就之后慢慢充分的草拟好了」
.message	210	miy-108_03-0010		宫子说着不吉的话，却又同时叹了一口气。
.transition 0 * 40
.stage	* bgc_sch002a01_02.png 0 0 st_miyako08a03.png 410
.message	220	miy-108_03-0011	傒傗偙	「回去睡觉了。真的累死了啦」
.message	230		丂峢丂	「我还有工作……」

;■御影チェック
;.transition 0 * 40
;.stage	* bgc_sch002a01_02.png 0 0 st_miyako01a08.png 400
.transition 0 * 40
.stage	* bgc_sch002a01_02.png 0 0 st_miyako01a08.png 360
;（「投げやりな表情」，，，ではないかもしれませんが）
;.stage	* bgc_sch002a01_02.png 0 0 st_miyako07a04.png 410
;（表情注意）
.message	240	miy-108_03-0013	傒傗偙	「努力哦～」
.message	250		丂峢丂	「啊啊……」
.message	260			宫子抛过来的声音，我都没能精神的回答。
.message	270			真的是累坏了。
.message	280			现在也完全没有想要工作的心情了……。
.panel 0
.overlay * *
.transition 0 * 10
.stage	* WHITE.png 0 0


;■背景：教会前（冬，１７時
;■　　　　广野纮　：制服（冬）
;■　　　　雨宫优子：私服（冬）
.HSVfilter 0 0 0 0 5 -5
.overlay * or_yuko03c.png
.transition 1 fadeSide.png 10
.stage	* bgc_normal012a01_03.png 0 600 st_yuko01g01.png 370
;.stage	* bgw_normal011a01_03.png 0 600
;（とりあえず夜で教会内部でアタッチしています）
;（教会外観だから，このＣＧだよな……？それとも内部……？）
.panel 1
.message	290	yuk-108_03-0003	桪丂巕	「一副疲倦的表情呢」
.message	300		丂峢丂	「你还是老样子清澈的表情啊」
.message	310			雨宫优子今天也是如同往日精神很好的样子。
.transition 0 * 40
.stage	* bgc_normal012a01_03.png 0 600 st_yuko01g03.png 370
.message	320	yuk-108_03-0005	桪丂巕	「商业习惯，笑容绝对不可缺少哦<音乐符号>」
.message	330		丂峢丂	「你原来是商人吗……」
.message	340	yuk-108_03-0007	桪丂巕	「如果知道这个的话，会越来越不幸的哦？」
.message	350		丂峢丂	「『越来越』算什么啊？」
.transition 0 * 40
.stage	* bgc_normal012a01_03.png 0 600 st_yuko01g02.png 370
.message	360	yuk-108_03-0009	桪丂巕	「幸福的人不会露出那样的表情的哦」
.message	370			我连着摸了几下自己的脸颊。
.message	380			当然，就算这样做也不会明白自己究竟是什么样的表情。
.message	390			我难道就露着那么清晰的萧条的脸吗。
.message	400		丂峢丂	「嘛，稍微有些让人不舒服的事情发生」
.transition 0 * 40
.stage	* bgc_normal012a01_03.png 0 600 st_yuko02g02.png 370
.message	410	yuk-108_03-0011	桪丂巕	「哦哦，原来如此吗。那样的话，和姐姐谈谈怎么样呢？」
.message	420		丂峢丂	「我说你，只是觉得有趣吧……」
.transition 0 * 40
.stage	* bgc_normal012a01_03.png 0 600 st_yuko03g02.png 400
.message	430	yuk-108_03-0013	桪丂巕	「仅仅是引导迷途的羊羔而已哦」
.message	440		丂峢丂	「分明既不是修女也不是生活顾问的吧！」
.transition 0 * 40
.stage	* bgc_normal012a01_03.png 0 600 st_yuko04g02.png 400
.message	450	yuk-108_03-0015	桪丂巕	「嘛嘛，不无所谓的吗。也不是什么不能对人说的话对吧？」
.message	460		丂峢丂	「……也不是什么能对人说的话啊」
.message	470			虽然这么说着，但还是把关于前途的问题说了个遍。
.transition 0 * 40
.stage	* bgc_normal012a01_03.png 0 600 st_yuko04g01.png 400
.message	480	yuk-108_03-0017	桪丂巕	「原来如此……嘛，经常会有的故事呢」
.message	490		丂峢丂	「只有这种程度的感想吗」
.message	500			和这个女人说话是我的失误。
.transition 0 * 40
.stage	* bgc_normal012a01_03.png 0 600 st_yuko07g01.png 400
;（前からこのポ～ズ変化はオッケ～か？）
.message	510	yuk-108_03-0019	桪丂巕	「像你这样乖僻的学生，自然不能如自己心情真实的的选出该走的道路的吧」
.message	520		丂峢丂	「到也不是这么回事……」
.message	530			对于我来说，道路已经选下，就是不确认走下去是否正确。
.message	540			挺起胸口，说出自己是漫画家什么的做不到。
.message	550		丂峢丂	「虽然很烦恼，有时也会想着反正车到山前必有路，管它变成怎样呢」
.transition 0 * 40
.stage	* bgc_normal012a01_03.png 0 600 st_yuko07g02.png 400
.message	560	yuk-108_03-0021	桪丂巕	「把东西就那么中途半端的扔出去而不管的……也很常见呢」
.message	570		丂峢丂	「……我知道」
.message	580			把自己想做的事情一直做的最后的人必然少之又少。
.message	590			就算是我，这点我还是明白的。
.message	600	yuk-108_03-0023	桪丂巕	「既然讨厌的话不是可以逃走吗」
.transition 0 * 40
.stage	* bgc_normal012a01_03.png 0 600 st_yuko02g03.png 370
;（表情とポ～ズ注意）
.message	610	yuk-108_03-0025	桪丂巕	「也可以的哦，就算受到了挫折人生仍然会继续下去……」
.message	620		丂峢丂	「我说你，干吗进入安慰Mode了啊？」
.transition 0 * 40
.stage	* bgc_normal012a01_03.png 0 600 st_yuko01g03.png 370
.message	630	yuk-108_03-0027	桪丂巕	「诶？　我并没有安慰你啊。“也可以这样做啊”，我只是作为前辈告诉你一些理所当然的事呢」
.message	640		丂峢丂	「啊～，是吗」
.transition 0 * 40
.stage	* bgc_normal012a01_03.png 0 600 st_yuko01g01.png 370
.message	650	yuk-108_03-0029	桪丂巕	「对了广野先生」
.message	660		丂峢丂	「啊？」
.transition 0 * 40
.stage	* bgc_normal012a01_03.png 0 600 st_yuko01g04.png 370
;（g09との使い分けにも注意のこと）
;.stage	* bgc_normal012a01_03.png 0 600 st_yuko01g02.png 370
;（「マジな目」，，，なので表情はちょっと違うのかな）
.message	670	yuk-108_03-0031	桪丂巕	「你的烦恼只有这些而已吗？」
.message	680			干吗啊，那个认真的眼神。
.message	690			就算你说烦恼啊……。
;■宫子と景の近距離立ち絵を交互に出すか。
;☆（どういう演出なんだろ，，，ちょっと保留）
.message	700			说到其他大的烦恼的话……。
.message	710			没有，我认为。
.message	720			就是啊，我不得不要考虑的是自己的事。
.message	730			现在只考虑着这些──
.message	740			直到有了可以环顾周围的空余为止。
.transition 0 * 40
.stage	* bgc_normal012a01_03.png 0 600 st_yuko01g03.png 370
.message	750	yuk-108_03-0033	桪丂巕	「什么都没的样子呢」
.message	760		丂峢丂	「……啊啊，什么都没」
.transition 0 * 40
.stage	* bgc_normal012a01_03.png 0 600 st_yuko02g02.png 370
.message	770	yuk-108_03-0035	桪丂巕	「如果说再有了迷惘或者疑惑──随时都可以来找我」
.message	780		丂峢丂	「如果有心情的话」
.transition 0 * 40
.stage	* bgc_normal012a01_03.png 0 600 st_yuko02g03.png 370
.message	790	yuk-108_03-0037	桪丂巕	「以前我就这么想过──你果然」
.message	800		丂峢丂	「果然？」
.transition 0 * 40
.stage	* bgc_normal012a01_03.png 0 600 st_yuko03g02.png 400
;（表情とポ～ズ，注意のこと）
.message	810	yuk-108_03-0039	桪丂巕	「不，我不会说。女孩子的秘密呢」
.message	820			无意之间，雨宫优子好似愉快起来。
.message	830			虽然完全不明白她为什么为何而愉快。
.message	840			如果真的有心情的话，说不定我会再来见下雨宫优子的吧。
.message	850			我一边想着，挥手同雨宫告别走了起来。


;■御影チェック
;■　キ～入力無効
.pragma disable_control


;■御影チェック
;.transition 0 * 20
.transition 0 * 10
.stage	* BLACK.png 0 0
.message	860			现在，为了做自己要做的事。\a
.wait 270
.message	870			以及能让自己做到自己还不能做到的事。\a
.wait 270
.message	880			仅仅向着前方前进──我决定了。\a
.wait 300

.panel 0
.playBGM * 0 6
.transition 0 * 10
.stage	* BLACK.png 0 0
.wait 300
.HSVfilter 0 0 0 0 0 0
.overlay * *
;■BAD　END_01


;■御影チェック
;■　キ～入力有効
.pragma enable_control

.end
