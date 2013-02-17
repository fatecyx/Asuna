; ファイル: 112_02.txt
;■·景のことも放っておけないを選択。
.transition 0 * 40
.stage	* bg_up002a01_00.png 0 0 st_miyako10a11.png 550
;（表情，注意して）
;.message	100		丂峢丂	「選ぶとか選ばないとか，大げさなことじゃねえよ。景がこんだけ気合い入れてんだから，試合くらい見に行ってやってもいいだろ」
.message	100		丂峢丂	「不是什么选择不选择那么重大的问题吧」
.message	105		丂峢丂	「景她也这么努力，去看下比赛也无所谓的吧」
.transition 0 * 40
.stage	* bg_up002a01_00.png 0 0 st_miyako10a09.png 550
;（表情，注意して）
.message	110	miy-112_02-0003	傒傗偙	「我也这么想呢。仅仅是去看下比赛而已，虽然这样也好」
.message	120		丂峢丂	「别的还有什么啊」
.message	130			赢得比赛的话，景说了会有重要的事情对我说。
.message	140			虽然想要说什么我还不明白，但就算说了也不会有什么改变。
.message	150			因为不可能改变──
.message	160		丂峢丂	「比赛，我会去看的。和你的之间的时间从现在开始要制造多少都行啊」
.message	170			就是相信着不会有任何改变，我才会去景所说的话。
.message	180		丂峢丂	「根本没有什么需要你担心的事情」
.message	190		丂峢丂	「不是吗？」
.transition 0 * 40
.stage	* bg_up002a01_00.png 0 0 st_miyako10a10.png 550
;（表情，注意して）
.message	200	miy-112_02-0005	傒傗偙	「纮君，真的这么想吗？」
.message	210			压着的胸部的触感瞬间消失了。
.message	220	miy-112_02-0007	傒傗偙	「如果是认真的话──那我就不去介意」
.message	230		丂峢丂	「啊啊，不介意就好」
.message	240			不如宫子你也一起去看吧──
.message	250			虽然想这么说，我还是半途把话咽了回去。
.transition 0 * 40
.stage	* bg_up002a01_00.png 0 0 st_miyako10a15.png 550
;（a14表情でも？）
.message	260	miy-112_02-0009	傒傗偙	「啊～啊，好不容易鼓气勇气说出那么害羞的话……全浪费了」
.message	270			看着带着有些遗憾的笑容的宫子的脸，不知为何我什么都说不出来。
.playSE kei_dribble_twice.ogg f 0 *
;☆（ここの効果音はちょっと注意して）
.message	280			咚！
.transition 0 * 20
.stage	* ev01_153b01.png 0 0
;☆（コンテ指定位置からのこの画像だと，ちょっと変だな…。もちっと後に？視点移動にも注意のこと。つ～か，ここでなんらかの動きは入れたいな，，，）
.message	290			一瞬间，高扬运球的声音。

;■御影チェック
;■　位置が違うね。
;.message	300			見ると，今まさに景がスリ～ポイントラインの外からシュ～トに入ろうとしているところだった。
.message	300			看过去，正是景投球的瞬间。
.message	310			运用膝盖的弹跳力，景轻轻的跳起来──
.message	320			放出的篮球朝向篮框，划出一道美丽的抛物线──
.panel 0
.overlay * *
.playBGM *
.transition 0 * 10
.stage	* WHITE.png 0 0


;■背景：体育館（冬，１３時
;■　　　　广野纮：制服（冬）
;■　　　　堤京介：制服（冬）
.playBGM efBGM012.ogg
.playSE basket_kansei.ogg f
.transition 1 fadeSide.png 10
.stage	* ev01_155a01_mugai_a.png 0 0
;☆（フェ～ドスピ～ドには注意。前から続いてますので，ここは変形で？さらにここは京介のイベントＣＧではなく，ゴ～ルのアップ……効果音とともに，がいいかもしれません。ボ～ルがスパッと入る感じ）
.panel 1
.message	330	kyo-112_02-0015	嫗丂夘	「进了！」
.message	340			在京介发话的同时，景射出的3分球准备的进入了篮框。
.message	350			瞬间便有音羽队员的欢呼和对手们的悲鸣响了起来。
.message	360			虽然对手队伍拼死速攻，但已经晚了。
.playSE basket_fue.ogg f 0 *
.message	370			主裁判的比赛终了的口哨声已经尖锐的响了起来。
.transition 0 * 40
.stage	* ev01_155a02_mugai_a.png 0 0
;☆（フェ～ドスピ～ドには注意のこと。つ～かこの絵，纮がいない気がするが……？ジャ～ジじゃないよな……？ここ，注意されたし）
.message	380	kyo-112_02-0017	嫗丂夘	「喂喂，真的赢了啊」
.message	390			握着DV镜头，京介小声的嘟囔道。
.message	400		丂峢丂	「而且还是结束前的紧张大逆转啊……」
.message	410			就好象设计好的一样，用3分球超越了最后时刻2分之差的戏剧般的结束方式。
.message	420			对阵在县内也数一数二的强校，音羽的女子篮球部的各位虽然前半场发挥很不错，但没想到竟然会赢啊。
.transition 0 * 40
.stage	* ev01_155a03_mugai_a.png 0 0
.message	430	kyo-112_02-0021	嫗丂夘	「这样的话，就有专门了摄影的价值了啊～」
.message	440			京介愉快的笑起来。
.message	450			好象是运动部为了作为今后的参考而经常拜托摄影研究会来作比赛的摄影。
.message	460		丂峢丂	「不过，只是练习比赛而已嘛」
.message	470	kyo-112_02-0025	嫗丂夘	「再怎么说也赢过了强校啊，这样部员们就会有自信了吧。我觉得很有意义啊」
.message	480		丂峢丂	「可能吧……」
.message	490			我望向下方骚乱着的篮球部的人们。
.message	500			不但投出逆转的1球而且还在整场比赛攻守各方面都活跃着的景，被大家围在了中央。
.message	510			实际而言，就算是对于篮球一无所知的我也觉得景真的很不错。
.message	520			但是，现在的我却完全无法直率的感动起来。
.message	530			今天早上来的1个电话。
.message	540			那个时候的，宫子的声音在我头中至今环绕不散。
.panel 0
.playSE *
.transition 0 * 10
.stage	* WHITE.png 0 0


;■背景：纮自室（冬，７時
;■　　　　广野纮：制服（冬）
.transition 0 * 10
;.stage	past_window.png bgc_home001a01_00.png 0 0
.stage	past_window.png ev01_156a01_past.png 0 0
;☆（a02差分がないな，，，）
;（通常背景で入ってますが，実際はイベントＣＧがあります）
.panel 1
.message	550	miy-112_02-0011	傒傗偙	『结束吧』
.message	560			突然，宫子这么说。
.message	570			没有任何招呼，和平常一样没有改变的语调。
.transition 0 * 20
.stage	past_window.png ev01_156a02_past.png 0 0
;.stage	past_window.png ev01_156b01_past.png 0 0
;（b01_mugaiを使うことも考慮に）
.message	580		丂峢丂	「结束……？　结束什么？」
.transition 0 * 20
.stage	past_window.png ev01_156b01_past.png 0 0
.message	590			想说什么完全不明白。
.message	600	miy-112_02-0013	傒傗偙	『简单的说……就是分手吧』
.message	610		丂峢丂	「分手……哈！？」
.message	620	miy-112_02-0015	傒傗偙	『哇，声音太大了啦』
.message	630			从电话那边传来宫子小小的悲鸣声。
.message	640			说起来，想要悲鸣该是我才对吧。
.transition 0 * 40
.stage	past_window.png ev01_156b02_past.png 0 0
.message	650		丂峢丂	「我说你你，突然之间说什么呢」
.message	660		丂峢丂	「分手什么的……我到底作了什么，说出那样的话！？」
.message	670	miy-112_02-0017	傒傗偙	『求你了，别发出太大的声音呢』
.message	680			宫子用平淡的过分的声音说着。
.message	690			那份冷静让我有异样的不适感。
.transition 0 * 40
.stage	past_window.png ev01_156b03_past.png 0 0
;（ここでb03表情で良いか？）
.message	700		丂峢丂	「不是因为你说了莫名其妙的话的原因吗。按着顺序给我解释清楚，顺序」
.message	710	miy-112_02-0019	傒傗偙	『顺序没有搞错哦。我只是想要结束掉而已』
.message	720		丂峢丂	「所！以！我在问你为什么会这样想！」
.message	730	miy-112_02-0021	傒傗偙	『就算你问也没有意义的啊。就算纮君说什么，我的心情也不会改变』
.message	740		丂峢丂	「……真的吗喂」
.message	750			完全理不出头绪──倒也不是。
.message	760			宫子她──一直都有哪里有些不安。
.message	770			对于我来说可能是些小事，但对于宫子说不定就不是这样。
.transition 0 * 40
.stage	past_window.png ev01_156b04_past.png 0 0
.message	780		丂峢丂	「你以为，我是会说『是的我知道了』然后就放过不管了吗？」
.message	790	miy-112_02-0023	傒傗偙	『对了，还只做了一回而已呢。虽然我还想着要不要多给你几次会好一些呢』
.message	800		丂峢丂	「我没说那个！」
.message	810	miy-112_02-0025	傒傗偙	『总之，就这样结束吧』
.message	820	miy-112_02-0027	傒傗偙	『我不会再给你打电话，也不会再去你家。不见面──应该会比较困难，那么见了我不要跟我说话好了』
.message	830		丂峢丂	「完全不说理由，少在那扯一堆没可能的事！」
.message	840	miy-112_02-0029	傒傗偙	『再见。至今为止，谢谢你了呢』
.message	850		丂峢丂	「啊，喂！　给我等──」
;☆（ここ，切り出しか，表情変えさせるか，ＦＧ消すか）
.message	860			挂掉了……。
.panel 0
.transition 0 * 10
.stage	* WHITE.png 0 0


;■背景：空
.transition 0 * 10
.stage	* bgw_sky001a01_02.png 0 0
;☆（実際は青空，，，ではなく夕空？が入る予定ですが未定で。とりあえず夕の空入れてます）
.panel 1
.message	870			宫子的声音到最后为止都是平淡如水。
.message	880			没有生气，也没有哭泣。
.message	890			我不明白她的心情。
.message	900			她到底是用什么表情对着电话说话的呢。
.message	910			我……哪里作错了吗？
.message	920	kei-112_02-0003	丂宨丂	「哥哥？」
.message	930			咚，肩膀被轻轻敲了一下。

;■背景：体育館（冬，１７時
;■　　　　广野纮：制服（冬）
;■　　　　新藤景：制服（冬）
.overlay * or_kei02a.png
.transition 0 * 20
.stage	* bgc_sch006a01_02.png 0 0 st_kei04a02.png 400
;（空から体育館，，，は良いか？もちろん，ドアら辺にいれば空は見えるわけだが，屋外→屋内の転換が急なように思えるなら考慮のこと）
.message	940	kei-112_02-0005	丂宨丂	「对不起，让你久等了」
.message	950		丂峢丂	「不，你已经没事了吗？」
.message	960			不该有一些比赛后的讨论，稍微的庆祝之类的吗。
.transition 0 * 40
.stage	* bgc_sch006a01_02.png 0 0 st_kei01a02.png 380
.message	970	kei-112_02-0007	丂宨丂	「嗯，适当撒了个慌就逃出来了」
.message	980		丂峢丂	「你还真的在有些地方很会算计啊」
.transition 0 * 40
.stage	* bgc_sch006a01_02.png 0 0 st_kei01a05.png 380
.message	990	kei-112_02-0009	丂宨丂	「因为，有其他更重要的事情啊」
.message	1000			不管怎样，景现在的心情是好的不能再好的样子。
.message	1010			有这么好的情绪的景好久没有见过了啊。
.message	1020			不过……。
.transition 0 * 40
.stage	* bgc_sch006a01_02.png 0 0 st_kei02a02.png 380
;（表情とポ～ズ注意）
.message	1030	kei-112_02-0011	丂宨丂	「不过还是谢谢你能来。其实我以为你根本都不会来呢」
.message	1040			在我眼前的景越来越不清晰。
.message	1050		丂峢丂	「嘛，再怎么忙也能抽出半天左右的空的吧」
.transition 0 * 40
.stage	* bgc_sch006a01_02.png 0 0 st_kei05a04.png 400
;（表情とポ～ズ注意）
.message	1060	kei-112_02-0013	丂宨丂	「因为哥哥不是很讨厌麻烦事吗。说真的，确实有点以外呢」
.message	1070			现在只有宫子的话在脑海里缭绕着。
.transition 0 * 40
.stage	* bgc_sch006a01_02.png 0 0 st_kei07a02.png 400
.message	1080	kei-112_02-0015	丂宨丂	「但是哥哥来看我了…所以……」
.message	1090			不只今天早上在电话中所说的。
.message	1100		丂峢丂	「所以？」
.message	1110			从圣诞节见面以来，和宫子一起度过的时间一个一个浮上心头。
.transition 0 * 40
.stage	* bgc_sch006a01_02.png 0 0 st_kei01a06.png 380
.message	1120	kei-112_02-0017	丂宨丂	「什，什么都没的啦！」
.transition 0 * 40
.stage	* bgc_sch006a01_02.png 0 0 st_kei02a05.png 380
.message	1130	kei-112_02-0019	丂宨丂	「真是的～……」
.message	1140			为什么我会犯错呢。
.transition 0 * 40
.stage	* bgc_sch006a01_02.png 0 0 st_kei01a09.png 380
.message	1150	kei-112_02-0021	丂宨丂	「该出哪说起好呢……」
.message	1160			为什么，我会理解那一切已经无法取回了呢。
.message	1170		丂峢丂	「从你想说的地方说啊。时间有的是」
.transition 0 * 40
.stage	* bgc_sch006a01_02.png 0 0 st_kei01a10.png 380
.message	1180	kei-112_02-0023	丂宨丂	「是，是呢……那么──」
.message	1190			就算再怎么后悔，我的话也已经再也无法传递给宫子了。
.transition 0 * 40
.stage	* bgc_sch006a01_02.png 0 0 st_kei07a02.png 400
;（表情とポ～ズ，注意のこと）
.message	1200	kei-112_02-0025	丂宨丂	「不，不行。不能这样。哥哥很迟钝的啦……不坦率的说是不可能明白的呢」
.message	1210			心脏被如此紧的束缚住──
.transition 0 * 40
.stage	* bgc_sch006a01_02.png 0 0 st_kei05a04.png 400
;☆（表情とポ～ズ，注意のこと。ここ，目閉じで？）
.message	1220	kei-112_02-0027	丂宨丂	「其实，我从很早以前就──」


;■御影チェック
;■　キ～入力無効
.pragma disable_control


;■御影チェック
.transition 0 * 10
.stage	* BLACK.png 0 0
.message	1230			分明我喜欢的是宫子。\a
.wait 270
.message	1240			已经，什么都──听不到了。\a
.wait 270
.message	1250			只有，那些过去的日子里宫子的笑颜，还在我的脑海中转动。\a
.wait 370

.panel 0
.playBGM * 0 6
.transition 0 * 10
.stage	* BLACK.png 0 0
.wait 300
.HSVfilter 0 0 0 0 0 0
.overlay * *
;■BAD　END_02


;■御影チェック
;■　キ～入力有効
.pragma enable_control

.end
