; ファイル: 110_01.txt
;■＜１章：１０日目＞
;■背景：学園·廊下（冬，１２時
;■　　　　广野纮　　：制服（冬）
;■　　　　堤京介　　：制服（冬）
;■　　　　宫村宫子：制服（冬）
.transition 0 * 10
.stage	* bgw_sch002m11_01.png 0 0
;.stage	* bgc_sch002a01_01.png 0 0
;.shakeScreen T 20 500
.panel 1
.message	100			突然，眼睛里的世界摇晃起来。
.shakeScreen O 30 200
.transition 0 * 20
.stage	* bgw_sch002m11_01_mugai_a.png 0 0
.message	110			世界仿佛转了一周，天花板变成了地板的感觉。
.playBGM efBGM013.ogg 0 *
;.transition 0 * 20
;.stage	* bgw_sch002m11_01_mugai_a.png 0 0
.message	120	kyo-110_01-0003	嫗丂夘	「呜哇，广～野！」
;.message	130		丂峢丂	「どこの国のヒトだ，俺は」
.message	130		丂峢丂	「我现在是在哪儿……」
.message	140			虽然很勉强，吐槽的余力还是有一些。
;.transition 0 * 20
;.stage	* bgw_sch002m11_01.png 0 0
;（インのタイミング，注意して）
.message	150			我靠着墙壁支撑起软弱的身体。
.transition 0 * 20
.stage	* bgw_sch002m11_01.png 0 0
.message	160		丂峢丂	「……，现在真的有点不行了」
.transition 0 * 20
.stage	* bgw_sch002m11_01.png 0 0 st_kyo01a09.png 400
;（京介立ち絵の表示タイミング，注意して。表情にも注意）
.message	170	kyo-110_01-0009	嫗丂夘	「喂喂，你一个人玩什么呢我说」
.message	180			觉得我刚才的像是在玩吗，你丫。
.message	190			长的什么眼睛啊，你丫。
.message	200			这也算是当朋友的么，你丫。
.transition 0 * 40
.stage	* bgw_sch002m11_01.png 0 0 st_kyo02a02.png 400
;（表情注意して。02a04でも？もしくは無難に02a01とか）
.message	210	kyo-110_01-0011	嫗丂夘	「哦哦，广野的身体内有蠕动的诅咒我明白」
.message	220		丂峢丂	「你能明白就好」
.transition 1 fadeSide.png 20
.stage	st_kyo08a02-.png 0 0 bg_scl004a01_01.png 0 0 bg_scl004a01_01.png 0
.effect	WScroll2 * 60 -2


.message	230			总之回过一句后，再次抬起了步子。
.message	240			现在是午休时间。
.message	250			在和食堂派的京介一起去食堂的途中……仅此而已。
;.transition 0 * 40
;.stage	* bgw_sch002m11_01.png 0 0 st_kyo01a02.png 400
;（表情注意して）
.message	260	kyo-110_01-0015	嫗丂夘	「要不要借肩膀给你？　特別价格哦」
.message	270		丂峢丂	「你还要收钱吗！」
.message	280			就算你免费我也没要借的心情。
.transition 0 * 40
.stage	st_kyo08a03-.png 0 0 bg_scl004a01_01.png 0 0 bg_scl004a01_01.png 0
;.transition 0 * 40
;.stage	* bgw_sch002m11_01.png 0 0 st_kyo01a04.png 400
.message	290	kyo-110_01-0019	嫗丂夘	「但是啊，广野你毎月总会有这么一段身体不好的时间。休课也满多的…」
.message	300		丂峢丂	「…………」
.transition 0 * 40
.stage	st_kyo08a01-.png 0 0 bg_scl004a01_01.png 0 0 bg_scl004a01_01.png 0
;.transition 0 * 40
;.stage	* bgw_sch002m11_01.png 0 0 st_kyo01a03.png 400
;（a05の使い分けも考えて。ここはa05のほうが良い？）
.message	310	kyo-110_01-0023	嫗丂夘	「其实你的真身是女孩子来那个了吗？　而且还比较严重的样子？」
.message	320		丂峢丂	「想死一次看看吗，京介」
.message	330			不能再跟这个家伙说笑话了。
.message	340			赶快一个人走了算了。

;■御影チェック
;.effect *
.effect end


;.transition 0 * 20
;■御影チェック
;■　エフェクトエンドで終わらせると，ちょい遅いな。
;.transition 1 fadeSide.png 20
.transition 1 fadeSide.png 30

.stage	* ev01_125.png 0 0
;（立ち絵からこのＣＧへの移行は違和感がないようにしっかりと）
;（さらにこの後，顔アップのスクロ～ル歩き使うみたいです。要留意のこと）
.message	350	kyo-110_01-0027	嫗丂夘	「等下，等下。真的没事吧」
.message	360			即便如此京介还是追了上来。
.transition 1 fadeSide.png 20
.stage	st_kyo08a03-.png 0 0 bg_scl004a01_01.png 0 0 bg_scl004a01_01.png 0
.effect	WScroll2 * 60 -2
.message	370		丂峢丂	「什么事都没啦」
.message	380			虽然各种事情混乱不堪，认真来上课而没时间也对画原稿造成危机。
.message	390			不过──
.message	400			虽然鱼贝类微妙的多觉得有些瑕疵，不过每天了总算保证了饮食。
.message	410			仅此而已就觉得身体的负担减轻了不少。
.message	420			虽然有些害羞而无法对其本人说，真的是很值得感谢。
.message	430			为此原因──我才不能倒下。
.transition 0 * 40
.stage	st_kyo09a01-.png 0 0 bg_scl004a01_01.png 0 0 bg_scl004a01_01.png 0
.message	440	kyo-110_01-0031	嫗丂夘	「嘛，你这么说也就算了。真的不太好的时候就说话哦」
.message	450		丂峢丂	「就算我说了，你能为我作点什么么」
.transition 0 * 40
.stage	st_kyo08a03-.png 0 0 bg_scl004a01_01.png 0 0 bg_scl004a01_01.png 0
.message	460	kyo-110_01-0035	嫗丂夘	「米啊，不会做什么」
.message	470		丂峢丂	「猜的就是这样」
.message	480			对京介抱有期待纯属浪费时间。
.transition 0 * 40
.stage	st_kyo08a01-.png 0 0 bg_scl004a01_01.png 0 0 bg_scl004a01_01.png 0
.message	490	kyo-110_01-0039	嫗丂夘	「什么都不做不也行吗？　被人听自己说话，不也会稍稍快乐点吗？」
.message	500		丂峢丂	「……我想没想要快乐什么的」
.message	510			偶尔觉得京介是个不错的家伙时就会自然而然的不爽起来。
.message	520			啊～，可恶。

;■御影チェック
;■　こんにゃ～（·～·）ノ
;.playBGM efBGM030.ogg
.playBGM *

.message	530	miy-110_01-0003	傒傗偙	「纮君」

;■御影チェック
;.effect *
.effect end

;■御影チェック
.playBGM efBGM030.ogg

;■御影チェック
;■　メモだが，出だしは宫子と纮だけ切り抜くか？

;.transition 0 * 20
.transition 1 fadeSide.png 20
.stage	* ev01_126a01.png 0 0
;（コンテより一つ後に置いてます）
.message	540		丂峢丂	「哇」
.message	550			宫子突然从背后出现。
.message	560		丂峢丂	「我说你们，除了吓到我之外就没法好好打招呼了么」
.transition 0 * 40
.stage	* ev01_126a02.png 0 0
.message	570	miy-110_01-0005	傒傗偙	「嗯～…………」
.transition 0 * 40
.stage	* ev01_126a03.png 0 0
;（ここはa02表情続行でもいい気がしますが）
.message	580	miy-110_01-0007	傒傗偙	「没可能吧？」
.message	590			算我拜托您，请努力。
.transition 0 * 40
.stage	* ev01_126a04.png 0 0
.message	600	miy-110_01-0009	傒傗偙	「说起来纮君，饮料之类的买了吗？」
.message	610		丂峢丂	「现在正要去」
.transition 0 * 40
.stage	* ev01_126b01.png 0 0
;（フェ～ドスピ～ドは20で？）
.message	620	miy-110_01-0011	傒傗偙	「那么，我就先到屋顶去了，早点过来哦」
.message	630			宫子亮出双手拿着的两个便当盒。
.transition 0 * 40
.stage	* ev01_126b02.png 0 0
.message	640	kyo-110_01-0049	嫗丂夘	「……最近，我还在想你只买了饮料就不知道消失到哪去了，原来是这个原因吗」
.message	650			糟了，京介还在的啊。
.message	660		丂峢丂	「不，不是这回事。你别误解啊。我可没和这家伙在屋顶享受过什么午餐时间哦～」
;（ここでb03表情でも？）
.message	670	miy-110_01-0013	傒傗偙	「不就是和我一起享受午餐时间的吗」
.message	680		丂峢丂	「你给我闭嘴」
.transition 0 * 40
.stage	* ev01_126b03.png 0 0
.message	690	miy-110_01-0015	傒傗偙	「诶～，我要是不说话的话会死的哟」
.message	700	kyo-110_01-0055	嫗丂夘	「在这种状况下撒谎不可能吧。放弃吧，广野」
.transition 0 * 40
.stage	* ev01_126b04.png 0 0
;（宫子の表情，注意して）
.message	710	miy-110_01-0017	傒傗偙	「放弃吧～」
.message	720			为什么你们拉起共同战线了。
.transition 0 * 40
.stage	* ev01_126c01.png 0 0
.message	730	miy-110_01-0019	傒傗偙	「说起来～，你是谁？」
.message	740			不意之间，宫子指向了京介。
.transition 0 * 40
.stage	* ev01_126c02.png 0 0
.message	750	kyo-110_01-0057	嫗丂夘	「我是堤啊，堤京介！　1年级的时候不是说过不少话的吗！」
.message	760			说起来，以前好似还发生过京介追求宫子的事情来着。
.transition 0 * 40
.stage	* ev01_126b05.png 0 0
.message	770	miy-110_01-0021	傒傗偙	「唔，是这样呢……。1年级的时候很经常被各种各样的人搭话呢」
.message	780	kyo-110_01-0059	嫗丂夘	「完全被当成路人了啊……」
.message	790			哦哦，京介快要哭出来了。
.transition 0 * 40
.stage	* ev01_126a05.png 0 0
;（京介の表情にも注意して）


;.message	800	miy-110_01-0023	傒傗偙	「まぁいいや。じゃ，あたし行くから。纮君はまた後で。エトセトラの人もバイバイ」
.message	800	miy-110_01-0022	傒傗偙	「嘛算了啦。那么我就先走了。纮君等下见哦」
.message	805	miy-110_01-0024	傒傗偙	「路人君也拜拜」


.message	810	kyo-110_01-0061	嫗丂夘	「不要说路人～！」
.transition 0 * 20
.stage	* bgw_sch002m11_01.png 0 0 st_kyo04a06.png 400
;（わざとモブ消してますが，違和感あるようならモブ入りで）
.message	820			宫子无视了京介的话，快步离开了。
.message	830	kyo-110_01-0063	嫗丂夘	「呜呜，我的自尊被挖空了……」
.message	840		丂峢丂	「你还有那种东西吗」
.message	850	kyo-110_01-0067	嫗丂夘	「你们，最讨厌了……。午饭什么的都无所谓了。我去寻找安慰去……」
.transition 0 * 20
.stage	* bgw_sch002m11_01.png 0 0
.message	860			想要再刺一句『谁啊』的时候，已经传达不到了。
.message	870			无力的垂着肩膀的京介已经不知何时消失掉了。
.message	880		丂峢丂	「能把这个作为契机而转换一下心态活下去就好了」
.message	890			嘛，不得不转换心态的人并不只京介一个。
.message	900			我也需要，宫子也一样。
.message	910			用着不正常的生存方式，那份人生帐单总有一天会转回来的。
.panel 0
.playBGM *
.transition 0 * 10
.stage	* WHITE.png 0 0


;■背景：屋上（冬，１３時
;■　　　　广野纮　　：制服（冬）
;■　　　　宫村宫子：制服（冬）
.playBGM efBGM029.ogg
.transition 1 fadeSide.png 10
.stage	* bgw_sch007a01_01.png 0 0
;（とりあえず通常背景でインしてますが，空，もしくは切り出しからのインも考慮に入れて）
.panel 1
.message	920		丂峢丂	「那么，我先走了」
.transition 0 * 20
.stage	* ev01_127a_mugai_b.png 0 0
.message	930	miy-110_01-0025	傒傗偙	「诶～，这就走了吗？」
.transition 0 * 20
.stage	* ev01_127a01.png 0 0
;（とりあえずここに挿むんでますが，必要なら切り出しを。このＣＧから切り出す場合は，纮の顔と宫子の顔をアウトにするように切り出しを）
.message	940			宫子啪的抱住了刚准备站起来的我。
.message	950		丂峢丂	「喂」
.transition 0 * 40
.stage	* ev01_127a02.png 0 0
;（纮の表情変化には注意して）
.message	960	miy-110_01-0027	傒傗偙	「诶？」
.message	970		丂峢丂	「胸。胸，胸部压到了啦」
.transition 0 * 20
.stage	* ev01_127a_mugai_a.png 0 0
.message	980			隔着衣服就能感觉到的巨大的胸部紧紧的压住了我的手臂。
.transition 0 * 20
.stage	* ev01_127a03.png 0 0
;.transition 0 * 20
;.stage	* ev01_127a_mugai_a.png 0 0
.message	990	miy-110_01-0029	傒傗偙	「那么，你想换什么地方压呢？」
.message	1000		丂峢丂	「哎呀，那自然是胸部是最舒服的」
.transition 0 * 40
.stage	* ev01_127a04.png 0 0
;.transition 0 * 20
;.stage	* ev01_127a01.png 0 0
.message	1010	miy-110_01-0031	傒傗偙	「不是没问题嘛」
.transition 0 * 40
.stage	* ev01_127a05.png 0 0
;（纮の表情変化，注意して）
.message	1020		丂峢丂	「虽说如此……等下不对！」
.message	1030		丂峢丂	「我说了我不得不走了啦！」
.message	1040	miy-110_01-0033	傒傗偙	「不是还很早嘛」
.message	1050			虽然午休还有10几分钟的时间，但我还是摇了摇头。
.transition 0 * 40
.stage	* ev01_127a06.png 0 0
;（宫子の表情注意）
.message	1060		丂峢丂	「下个科目是体育啊。教体育的大塚老师，如果迟到会很烦的，不得不早去啊」
.transition 0 * 20
.stage	* ev01_127b01.png 0 0
;（フェ～ドスピ～ドは注意のこと。次の文でこのＣＧを表示？）
.message	1070	miy-110_01-0035	傒傗偙	「原来如此。不过，我被吓了一跳呢」
.message	1080			宫子终于把胸部移开了。
.message	1090			随之而来的丧失感正是所谓的男人心理吗。
.message	1100		丂峢丂	「到是，有什么东西吓到你了？」
.message	1110	miy-110_01-0037	傒傗偙	「嗯～，我还在想你要抛弃我了吗」
.transition 0 * 40
.stage	* ev01_127b02.png 0 0
.message	1120		丂峢丂	「你啊～」
.message	1130			这不是什么抛弃不抛弃的问题吧。
.message	1140			再说了，那个说话方式完全就跟我已经作了一样啊。
.transition 0 * 40
.stage	* ev01_127b03.png 0 0
.message	1150		丂峢丂	「嗯？　奇怪？」
.message	1160			最近这段时间，每天都在一起吃午饭。
.message	1170			一到放学后，宫子就会来到我家，读书或者打扰我的工作。
.message	1180			到了傍晚，就会去准备晚饭，当然也是坐在一张餐桌周围一起吃。
.message	1190			而且，宫子就算晚饭结束，也会在我家呆到12点之后。
.message	1200			而且还有，虽说只有一次的Kiss……。
.message	1210			这如果不算交往的话，又算什么呢。
.transition 0 * 40
.stage	* ev01_127c01.png 0 0
;（フェ～ドスピ～ドは注意のこと）
.message	1220		丂峢丂	「呜噢噢……」
.message	1230			抱着头仰向天空。
.message	1240	miy-110_01-0039	傒傗偙	「怎，怎么了吗？　精神药用完了吗？　看到什么奇怪的东西了吗？」
.transition 0 * 40
.stage	* ev01_127b04.png 0 0
;（フェ～ドスピ～ドには注意して）
.message	1250		丂峢丂	「说什么呢你！」
.message	1260	miy-110_01-0041	傒傗偙	「笑话而已啦」
.message	1270			不好笑的笑话求您少开。
.transition 0 * 40
.stage	* ev01_127b05.png 0 0
.message	1280	miy-110_01-0043	傒傗偙	「真的没事吗？　课逃掉吧？」
.message	1290			宫子一副惊讶的表情。
.message	1300		丂峢丂	「不，我走了……」
.message	1310			嗯，总之先别在意好了。

;■御影チェック
;■　ここは通常背景に戻したほうがよさそう。
;■　宫子のボイスも，呼びかけになっているのと，次のシ～ンとの繋ぎがいまいち。
;.transition 0 * 40
;.stage	* ev01_127b06.png 0 0
;（ここらへんで通常背景に切り替えるか？要留意のこと）
.transition 0 * 40
.stage	* bgw_sch007a01_01.png 0 0

.message	1320	miy-110_01-0045	傒傗偙	「一路走好哦。回头见呢」
.message	1330		丂峢丂	「嗯～」
;.playBGM *


;■御影チェック
.panel 0


;■背景：学園·階段（冬，１３時
;■　　　　广野纮：制服（冬）
;■　　　　新藤景：制服（冬）

;■御影チェック
;■　前のBGMを止めないのとあわせて，ここも曲を変えない。
;■　京介との会話からBGM変化が多すぎるというのが１点。
;■　また，宫子と会っていたときの曲（纮の気持ち）を景の登場時にも
;■　継続させることで，２人が同じ位置に並ぶということを示せるかな。
;■　　ついでに，景が意志を明確にしたところで曲も止めやすくなる。
;.playBGM efBGM020.ogg



.transition 1 fadeSide.png 20
.stage	* ev01_128a01.png 0 0
;.stage	* bgw_sch003m11_01.png 0 0
.panel 1
.message	1340	kei-110_01-0003	丂宨丂	「广野前辈！」
.message	1350		丂峢丂	「啊」
.message	1360			景啪嗒啪嗒的对面跑过来。

;■御影チェック
;■　後述の景と宫子の位置関係の問題から，少しずつ景の座標をズラします。
.transition 0 * 20
;.stage	* bgw_sch003m11_01.png 0 0 st_kei01a03.png 380
.stage	* bgw_sch003m11_01.png 0 0 st_kei01a03.png 450

.message	1370	kei-110_01-0005	丂宨丂	「前辈，最近有认真出勤吧」
.message	1380		丂峢丂	「突然之间就是说这个么」
.transition 0 * 40
;.stage	* bgw_sch003m11_01.png 0 0 st_kei01a01.png 380
.stage	* bgw_sch003m11_01.png 0 0 st_kei01a01.png 450
;（表情注意。02a01でも？）
.message	1390	kei-110_01-0007	丂宨丂	「因为是最重要的事情啊」
.message	1400			景盯着我这边看。
.message	1410			我僵硬的点了点头。
.message	1420		丂峢丂	「就算你不说也会上的啦。就是因为出勤了，才会累的困的快要死了啊」
.transition 0 * 40
;.stage	* bgw_sch003m11_01.png 0 0 st_kei01a02.png 380
.stage	* bgw_sch003m11_01.png 0 0 st_kei01a02.png 450
.message	1430	kei-110_01-0009	丂宨丂	「前辈只要做不也是可以做到的嘛。虽然最近不怎么见面而有些在意」
.message	1440			想来看看，和景这样的对话貌似也很久没过了。
.message	1450		丂峢丂	「不用你担心啦」
.message	1460		丂峢丂	「比起我你怎么样啊。经常见不到是因为部团活动吗？」
.message	1470			景点了点头。
.transition 0 * 40
;.stage	* bgw_sch003m11_01.png 0 0 st_kei06a02.png 400
.stage	* bgw_sch003m11_01.png 0 0 st_kei06a02.png 470
;（ポ～ズ注意。「にっこり」ではないかもしれない表情にも注意）
.message	1480	kei-110_01-0011	丂宨丂	「最近呢，状态很不错呢」
.message	1490			景轻轻的笑起来，做出投球的姿势。
.transition 0 * 40
;.stage	* bgw_sch003m11_01.png 0 0 st_kei03a01.png 380
.stage	* bgw_sch003m11_01.png 0 0 st_kei03a01.png 450
.message	1500	kei-110_01-0013	丂宨丂	「身体可以跟着想法而动起来。过人也经常过的去，投球也很准。这么好的状态说不定是第一次呢」
.transition 0 * 40
;.stage	* bgw_sch003m11_01.png 0 0 st_kei01a05.png 380
.stage	* bgw_sch003m11_01.png 0 0 st_kei01a05.png 450
.message	1510	kei-110_01-0015	丂宨丂	「现在玩篮球很愉快。愉快的让人停不下来呢」
.message	1520		丂峢丂	「哈～，你竟然也有这么天真的一面呢」
;.transition 1 fadeGray.png 40
.playSE kei_panch.ogg f 0 *
.transition 0 * 40
.stage	* ev01_129.png 0 0
;（フェ～ドの仕方には注意。併せて，フェ～ドスピ～ドも）
.shakeScreen	R	10	10
.message	1530	kei-110_01-0017	丂宨丂	「前辈你把人想成什么了啊」
.message	1540			将景轻轻锤出的拳头用手掌接住。
.message	1550			当然，用的是左手。
.message	1560	kei-110_01-0019	丂宨丂	「这次的星期天」
.message	1570		丂峢丂	「星期天？」
.transition 0 * 20
;.stage	* bgw_sch003m11_01.png 0 0 st_kei06a02.png 400
.stage	* bgw_sch003m11_01.png 0 0 st_kei06a02.png 470
;（切り替えタイミング，しっかりと）
.message	1580	kei-110_01-0021	丂宨丂	「有练习比赛。对象是去年的县大会的第二名」
.message	1585	kei-110_01-0021a	丂宨丂	「虽然我们这边也不弱，不过估计也很难取胜」
.message	1587	kei-110_01-0022	丂宨丂	「虽然不想这么说，但部员的大家都会这么想的吧」
;.message	1580	kei-110_01-0021	丂宨丂	「練習試合があるの。相手は，去年の県大会準優勝校。ウチだって弱くはないけど，まず勝てる見込みなんてないと思う。口には出さないけど，部員のみんなはそう思ってるでしょうね」
.message	1590		丂峢丂	「……然后呢」
.transition 0 * 40
;.stage	* bgw_sch003m11_01.png 0 0 st_kei06a05.png 400
.stage	* bgw_sch003m11_01.png 0 0 st_kei06a05.png 470
;（06a01でも？）
.message	1600	kei-110_01-0023	丂宨丂	「但是我从最开始就讨厌放弃。自己状态也很好，队伍的大家也有很好的配合。有可能赢也说不定呢」
.message	1610			景唰的向前踏出一步。
.transition 0 * 40
;.stage	* bgw_sch003m11_01.png 0 0 st_kei06a01.png 400
.stage	* bgw_sch003m11_01.png 0 0 st_kei06a01.png 470
;☆（「一歩踏み出した」，，，の演出は注意のこと）
.message	1620	kei-110_01-0025	丂宨丂	「想让前辈也来看我的比赛」
.message	1630	kei-110_01-0027	丂宨丂	「地点是这里的体育馆。比赛从10点开始」
.message	1640		丂峢丂	「星期日吗……」
.message	1650			星期日的话原稿就已经结束了，去看看也没什么不可以。
.transition 0 * 40
;.stage	* bgw_sch003m11_01.png 0 0 st_kei04a04.png 400
.stage	* bgw_sch003m11_01.png 0 0 st_kei04a04.png 470
;（目線注意）
.message	1660	kei-110_01-0029	丂宨丂	「我，一定会赢」
.message	1670			景的眼瞳里包含着坚定的决心。
;.transition 0 * 40
;.stage	* bgw_sch003m11_01.png 0 0 st_kei04a05.png 400
.message	1680	kei-110_01-0031	丂宨丂	「绝对赢给哥哥看……到那时，我…会把重要的事情说给哥哥听」
.message	1690		丂峢丂	「重要的事情……」
.message	1700	kei-110_01-0033	丂宨丂	「虽然现在不能说，但我绝对会说出来」
.transition 0 * 40
;.stage	* bgw_sch003m11_01.png 0 0 st_kei04a05.png 400
.stage	* bgw_sch003m11_01.png 0 0 st_kei04a05.png 470
.message	1710	kei-110_01-0035	丂宨丂	「我会赢的，请等着我……。拜托了」
.message	1720		丂峢丂	「等待…等什么」
.transition 0 * 40
;.stage	* bgw_sch003m11_01.png 0 0 st_kei01a06.png 380
.stage	* bgw_sch003m11_01.png 0 0 st_kei01a06.png 450
.message	1730	kei-110_01-0037	丂宨丂	「吵死了，这以上的不会说了！」
.message	1740			一会温和一会怒喊还真忙啊。
.message	1750			不过。
.message	1760			等着我…吗。
.message	1770			说不定，景她一直在……。
.message	1780			景一直在等着也说不定。
;■御影チェック
;■　キリのよいところまで文章はあったほうが良さそう。
;.message	1790			待たせていたのが誰なのかは，考えるまでもな──
.message	1790			被等待的究竟是谁，我还没来得及考虑──

;■御影チェック
;■　ちょっと止めるの早いかな。
;■　少し無音を多くしすぎているかも。他の人の反応を見よう。
.playBGM *

.transition 0 * 40
;.stage	* bgw_sch003m11_01.png 0 0 st_kei02a03.png 380
.stage	* bgw_sch003m11_01.png 0 0 st_kei02a03.png 450
;（景の表情，注意して）
;.transition 0 * 20
;.stage	* ev01_128b01.png 0 0 st_kei08a01.png 500
.message	1800	miy-110_01-0047	傒傗偙	「纮～君！」

;■御影チェック
;■　景のぼかし，位置関係もおかしいな。
;■　普通に対処してみましょ。
;■　あわせて，位置を調整するために，景登場からここまでの座標をズラします。
.transition 0 * 20
;.stage	* ev01_128b01.png 0 0 stm_kei08a01_bokashi.png 600
.stage	* ev01_128b01.png 0 0 st_kei08a01.png 470

.message	1810			又是在最坏的时机出现了啊。
.message	1820			笑颜满面的宫子踩着轻快的脚步从楼梯上走下来。
.message	1830	miy-110_01-0049	傒傗偙	「刚才忘记说了，今天的晚饭──」
.message	1840			正说着，宫子站住了。
.transition 0 * 20
;.stage	* bgw_sch003m11_01.png 0 0 st_miyako04a05.png 300 stm_kei08a01_bokashi.png 600
.stage	* bgw_sch003m11_01.png 0 0 st_miyako04a05.png 200 st_kei04a05.png 470
;（景を後ろ姿中距離·右で置いて，宫子を通常距離·左で置く？）
.message	1850	miy-110_01-0051	傒傗偙	「啊，小景……」
.transition 0 * 20
;.stage	* bgw_sch003m11_01.png 0 0 st_miyako04a05.png 200 st_kei04a05.png 600
;.stage	* bgw_sch003m11_01.png 0 0 st_miyako04a05.png 200 st_kei04a05.png 470
.message	1860	kei-110_01-0039	丂宨丂	「……您好」
.message	1870			景一点都不隐藏自己的坏心情。
.transition 0 * 40
;.stage	* bgw_sch003m11_01.png 0 0 st_miyako04a03.png 200 st_kei04a04.png 600
.stage	* bgw_sch003m11_01.png 0 0 st_miyako04a03.png 200 st_kei04a04.png 470
;（ここの宫子の表情変化には要注意して）
.message	1880	kei-110_01-0041	丂宨丂	「……广野前辈？」
.message	1890			景向我投来锐利的视线。
.message	1900		丂峢丂	「你的眼睛十～分可怕啊……」
.transition 0 * 40
;.stage	* bgw_sch003m11_01.png 0 0 st_miyako04a02.png 200 st_kei04a04.png 600
.stage	* bgw_sch003m11_01.png 0 0 st_miyako04a02.png 200 st_kei04a04.png 470
.message	1910	miy-110_01-0053	傒傗偙	「纮君，不是体育课吗。早点去的好啦」
.message	1920		丂峢丂	「但是……」
.message	1930			把宫子和景就这么放着真的好吗。
.transition 0 * 40
;.stage	* bgw_sch003m11_01.png 0 0 st_miyako04a02.png 200 st_kei01a06.png 600
.stage	* bgw_sch003m11_01.png 0 0 st_miyako04a02.png 200 st_kei01a06.png 460
;.message	1940	kei-110_01-0043	丂宨丂	「授業に行って。ていうか，さっさと行け」
.message	1940	kei-110_01-0043	丂宨丂	「去上课去──倒不如说是，赶快给我走人！」
.message	1950			景的声音里有着前所未有的催促感。
.message	1960			看起来，这里只有老实听从比较好吧……。
.panel 0
.playBGM *
.transition 0 * 10
.stage	* WHITE.png 0 0


;■宫子視点
;■背景：屋上（冬，１３時
;■　　　　宫村宫子：制服（冬）
;■　　　　新藤景　　：制服（冬）
;■白バック.playSE kagi_ireru.ogg f 0 *
.transition 0 * 10
.stage	vista_window.png ev01_130.png 0 0
;（このＣＧからインしてますが，通常背景，もしくは↑の指定にあるように白からイン）
.panel 3
.message	1970	miy-110_01-0055	#傒傗偙	「这个钥匙呢，是纮君从他姐姐那儿拿来的。作为升学礼物的替代品」
.message	1980	miy-110_01-1003		最近由于经常是我先到屋顶，于是就这样交给了我。
.transition 0 * 20
.stage	* ev01_130.png 0 0
;.transition 0 * 20
;.stage	* ev01_131a01.png 0 0
.message	1990	kei-110_01-0045	丂宨丂	「凪姐姐还真能做出来呢」
.transition 0 * 20
.stage	* ev01_131a01.png 0 0
.message	2000	miy-110_01-0057	#傒傗偙	「哦对了，小景和那位姐姐见过呢」
.message	2010	kei-110_01-0047	丂宨丂	「最近倒没怎么见面。因为凪姐姐到海外去了」
.message	2020	miy-110_01-0059	#傒傗偙	「哼～嗯……」
.playSE kagi_akeru.ogg f 0 *
.message	2030	miy-110_01-1005		喀沙，锁被打开了。
;.transition 0 * 20
.playSE *
.playSE okuzyou_door_miyako.ogg f 0 *
.transition 0 * 10
.stage	* ev01_131b01.png 0 0
;（ここはフェ～ドは10でいいかもしれません）
;（鍵穴に鍵を入れてるＣＧからこの開けるまで，滞空が長すぎるか？苦笑）
.message	2040	miy-110_01-1007		当我推开了通往屋顶的门。


;■ここより屋上の通常背景
.playSE2 okuzyou_kaze.ogg f
;.transition 1 fadeSide.png 20
.transition 1 fadeSide.png 10
;.stage	* ev01_132a01_mugai_a.png 0 0
.stage	* bgw_sch007a01_01.png 0 0
.message	2050	miy-110_01-1009		瞬间就有冬日的寒风拂面而过。
.transition 0 * 20
.stage	* ev01_132a01_mugai_a.png 0 0
;.stage	* ev01_132a01.png 0 0
.message	2060	miy-110_01-0061	#傒傗偙	「啊～，果然还是很冷呢」
.transition 0 * 20
.stage	* ev01_132a01.png 0 0
.message	2070	kei-110_01-0049	丂宨丂	「那么，换到不是这儿的地方也好吧？」
.message	2080	miy-110_01-0063	#傒傗偙	「因为别人不会有人来啊。说悄悄话最好了呢」
.message	2090	kei-110_01-0051	丂宨丂	「……和广野前辈吗？」
.message	2100	miy-110_01-1011		小景整理着被风拂乱的头发。
.message	2110	miy-110_01-0065	#傒傗偙	「也没过说什么必须瞒着别人的话啊」
.transition 0 * 40
.stage	* ev01_132a02.png 0 0
;（視線そらしていいか？）
.message	2120	kei-110_01-0053	丂宨丂	「宫村前辈…想说那样的话吗？」
.message	2130	miy-110_01-0067	#傒傗偙	「那样也会很有趣呢」
.message	2140	miy-110_01-1013		虽然这么说，我和纮君之间却没怎么说过太牵涉到那方面的话。
.message	2150	miy-110_01-1015		分明这些天，只有两个人单独在一起的。
.message	2160	miy-110_01-1017		不过正是因为这个，才会刻意的避开的吧。
.message	2170	miy-110_01-1019		如果进入奇怪的状况的话，就不知道会发生什么了。
.message	2180	miy-110_01-1021		就是因为不知道，才会感到害怕。
.message	2190	miy-110_01-1023		我是这样，大概纮君也一样。
.message	2200	miy-110_01-0069	#傒傗偙	「小景…平常和纮君说些什么话呢？」
.message	2210	kei-110_01-0055	丂宨丂	「没什么啊……因为前辈和我都是笨蛋啊，都没说过什么正经话」
.message	2220	miy-110_01-1025		说话方式还真是顽固呢～。
.message	2230	miy-110_01-0071	#傒傗偙	「那个～，虽然我比你大一岁，不用敬語也行啦。不要在意太多」
.transition 0 * 40
.stage	* ev01_132a01.png 0 0
.message	2240	kei-110_01-0057	丂宨丂	「宫村前辈，我和广野前辈是从小时侯就在一起玩的」
.message	2250	miy-110_01-1027		啊，被无视了。
.transition 0 * 40
.stage	* ev01_132a03.png 0 0
;（ここで03差分に移行しても良いか？）
.message	2260	kei-110_01-0059	丂宨丂	「广野前辈从小就随着他的父亲学习画画，基本都不出外玩耍。理所当然的，完全没有什么朋友」
.message	2270	miy-110_01-1029		突然开始的这是什么呢。
.message	2280	kei-110_01-0061	丂宨丂	「但是呢，对于偶尔会逃出家一个人徘徊着的广野前辈，我总觉得看不下去」
.message	2285	kei-110_01-0062	丂宨丂	「为什么会独单一人呢」
;.message	2280	kei-110_01-0061	丂宨丂	「でも，時々家から抜け出してきては一人でうろうろしてる广野前辈を，わたしはなんだか見ていられなかったんです。どうしてひとりでいるんだろうって」
.message	2290	kei-110_01-0063	丂宨丂	「那个时候的我……还不理解什么叫做孤独」
;☆（ここで03差分を一瞬だけ使うのが通なのか？）
.message	2300	miy-110_01-1031		呼的一瞬，小景流露出像是望向远方的眼神。
.message	2310	miy-110_01-1033		那究竟是什么呢。
.message	2320	kei-110_01-0065	丂宨丂	「前辈…他很寂寞。所以，我觉得不能再让他一个人孤独下去」
.message	2330	miy-110_01-0073	傒傗偙	「不是多余的操心吗～」
.message	2340	kei-110_01-0067	丂宨丂	「是前辈自己跟过来的。虽说我把他带到我家」
.message	2350	miy-110_01-0075	#傒傗偙	「把男孩子突然就带到自己家？　小景你虽然那么小却很大胆啊……」
.transition 0 * 40
.stage	* ev01_132b01.png 0 0
.message	2360	kei-110_01-0069	丂宨丂	「小孩子时的事！　再说了，和身体大小没关系吧！」
.message	2370	miy-110_01-1035		迅速的反论。
.message	2380	miy-110_01-1037		之前就想到过，小景…很能干呢。
.transition 0 * 40
.stage	* ev01_132c01.png 0 0
.message	2390	kei-110_01-0071	丂宨丂	「……像这样，把话题转移掉就是宫村前辈的作法吗」
.message	2400	miy-110_01-0077	#傒傗偙	「没到那种层次啦。只是认真的说话，不过常常起到反效果呢。啊哈哈」
.transition 0 * 40
.stage	* ev01_132c02.png 0 0
.message	2410	kei-110_01-0073	丂宨丂	「就是讨厌这种你随口说话的地方啊……」
.message	2420	miy-110_01-1039		我听到了哦，小景。
.message	2430	miy-110_01-1041		不过这种程度的毒舌对我来说还不会在意。
.transition 0 * 40
.stage	* ev01_132c03.png 0 0
.message	2440	kei-110_01-0075	丂宨丂	「我呢，从很小就喜欢少女漫画，在家里漫画也有很多」
.message	2450	miy-110_01-0079	#傒傗偙	「还真是从外表上看不出的少女风的兴趣呢」
.transition 0 * 40
.stage	* ev01_132c05.png 0 0
.message	2460	kei-110_01-0077	丂宨丂	「少来管我！」
.message	2470	miy-110_01-1043		也不用那么大声喊吧～。
.message	2480	miy-110_01-1045		嘛，她也有那跟自己形象不符合的自觉吧。
.transition 0 * 40
.stage	* ev01_132c03.png 0 0
;（c04差分もあり？）
.message	2490	kei-110_01-0079	丂宨丂	「前辈他」
.message	2500	kei-110_01-0081	丂宨丂	「广野前辈他最初接触的娱乐就是少女漫画了。前辈他，瞬间就迷上而埋头读了起来」
.message	2510	miy-110_01-0081	#傒傗偙	「纮君向那方面倾斜的原因原来是小景吗」
.message	2520	miy-110_01-1047		果然呢，再怎么说纮君也是男孩子。
.message	2530	miy-110_01-1049		普通的话应该喜欢少年漫画或者青年漫画之类才对呢。
.message	2540	kei-110_01-0083	丂宨丂	「虽然知道很喜欢，不过却没想到他开始画少女漫画，而且还发表了处女作」
.message	2550	kei-110_01-0085	丂宨丂	「嗯，完全是预想之外的事情了」
.message	2555	kei-110_01-0085a	丂宨丂	「正是因为在身边很近才没有想到吧……」
.message	2557	kei-110_01-0086	丂宨丂	「广野前辈的能力完全超出我的想象」
;.message	2550	kei-110_01-0085	丂宨丂	「ええ，全然予想すらしてなかったんです。身近にいたからわからなかったのかもしれませんけど……广野前辈の力はわたしが思ってたより全然すごくて」
.message	2560	miy-110_01-0083	#傒傗偙	「怎么觉得，好似少年漫画的主人公一样呢～。那家伙的潜在能力远远的超出了我等的预料！　之类的」
.transition 0 * 40
.stage	* ev01_132c05.png 0 0
.message	2570	miy-110_01-1051		一闪，小景狠狠对我瞪了一眼。
.message	2580	miy-110_01-1053		难得有一副可爱的脸，笑下多好呢。

;■御影チェック
;■　いや，やはりここの景の言葉は，宫子に真っ直ぐぶつけるべきか。
;■　表情はまだ真っ直ぐに。
;.transition 0 * 40
;.stage	* ev01_132c04.png 0 0
;（ここでc04表情で良いか？）

.message	2590	kei-110_01-0087	丂宨丂	「我是这么想的，宫村前辈」
.message	2600	miy-110_01-0085	#傒傗偙	「嗯？」
.message	2610	kei-110_01-0089	丂宨丂	「看到努力的人，只觉得好厉害啊…是不行的」
.message	2620	kei-110_01-0091	丂宨丂	「果然是，努力着的人是不会认同什么都不做的人的。就算退一步讲，也不可能会喜欢上她」
.playSE2 *
;■息をのむ。
.message	2630	miy-110_01-0087	#傒傗偙	「…………」

;■御影チェック
;■　ちょっと028だと重いというか派手すぎるな。
;■　宫子は，このショックがなにか判別つきかねている程度のもの。
;■　このほうが，地の文章までボイスにしている宫子の心情に近い。
;■　　あと，宫子が纮と寝たと告げるシ～ンがこの056の曲──。
;■　　同じ曲にすることで，こことの対比にする。
;.playBGM efBGM028mix.ogg
.playBGM efBGM056.ogg

.message	2640	miy-110_01-1055		……这是什么。
.message	2650	miy-110_01-1057		这种好似被什么刺穿的疼痛。
.message	2660	miy-110_01-1059		这…到底是什么……。

;■御影チェック
;■　目線が逸れるのはここで。
;■　ボイスもここで落ち着くし。
;■　最後の押しで逸れるくらいが景らしいという点もあるか。
.transition 0 * 40
.stage	* ev01_132c04.png 0 0

.message	2670	kei-110_01-0093	丂宨丂	「我是这么想的」
.message	2680	miy-110_01-0089	#傒傗偙	「……这就是，小景开始打篮球的理由吗？」
.message	2690	kei-110_01-0095	丂宨丂	「我本来就喜欢篮球啊」
.message	2700	kei-110_01-0097	丂宨丂	「速攻过去，一个人切开敌人的防线然后投球入篮，会让人特别心情愉快呢」
.transition 0 * 40
.stage	* ev01_132e01.png 0 0
;（ここでネコミミもあったらどうしようかと思いましたが，ないのでシネマモ～ドで問題ないと思います）
.message	2710	miy-110_01-0091	#傒傗偙	「喵～」
.message	2720	kei-110_01-0099	丂宨丂	「你在取笑我吗？」
.message	2730	miy-110_01-0093	#傒傗偙	「不是，不是。我是太感动而一不小心猫化了而已」
.message	2740	miy-110_01-1061		我把头摇来摇去。
.transition 0 * 40
.stage	* ev01_132e02.png 0 0
;（どこで猫化をとくか注意）
.message	2750	kei-110_01-0101	丂宨丂	「无所谓了。不过，只有这点容我说出来」
.transition 0 * 40
.stage	* ev01_132d01.png 0 0
;（ここで猫化をといていいか？）
.message	2760	miy-110_01-1063		毫无迷惑的直直看过来的眼瞳。
.message	2770	miy-110_01-1065		能有这样的眼睛，肯定是小景抱有坚定的心情的原因吧。
.transition 0 * 40
.stage	* ev01_132d02.png 0 0
;（ここでd02差分で良い？）
.message	2780	kei-110_01-0103	丂宨丂	「我──喜欢哥哥」
.message	2790	kei-110_01-0105	丂宨丂	「从很早以前开始，超越现在直到未来，无论何时这份心意都会持续下去」
.message	2795	kei-110_01-0106	丂宨丂	「因为…我到现在为止从来都没有断掉过对哥哥的这份心意」
;.message	2790	kei-110_01-0105	丂宨丂	「ずっと昔から，これからもずっと，いつまでも思い続けます。だって，これまでも一度だってお兄ちゃんへの気持ちが途切れたことなんてなかったもの」
.message	2800	miy-110_01-0095	#傒傗偙	「……你对我说也…」
.transition 0 * 40
.stage	* ev01_132d03.png 0 0
;☆（d04差分がないで～。d04を交えて，ここからの構築はしっかりと）
.message	2810	kei-110_01-0107	丂宨丂	「你就像这样，一直装傻就可以了」
.message	2820	miy-110_01-0097	#傒傗偙	「…………」
.message	2830	kei-110_01-0109	丂宨丂	「而我，絶対不会输给你」
.transition 0 * 40
.stage	* ev01_132d04.png 0 0
.message	2840	kei-110_01-0111	丂宨丂	「不，我要把你从哥哥身边消除给你看」
.message	2850	kei-110_01-0113	丂宨丂	「像你这种人……」
.message	2860	miy-110_01-1067		我……要从纮君的心里消失？
.message	2870	miy-110_01-1069		再次，消失掉……？
.transition 0 * 40
.stage	* ev01_132d02.png 0 0


;.message	2880	kei-110_01-0115	丂宨丂	「わたしは，そこからお兄ちゃんと一緒に始めます。あなたとはそれでさよなら。それで……終わりです」
.message	2880	kei-110_01-0114	丂宨丂	「而我，要从那里和哥哥一起开始。同时在那里和你说出永别」
.transition 0 * 40
.stage	* ev01_132d01.png 0 0
.message	2885	kei-110_01-0116	丂宨丂	「然后……就是结束」



.message	2890	kei-110_01-0117	丂宨丂	「我会把它结束」
.transition 0 * 10
.stage	* vista_white.png 0 0
.panel 0
.playSE2 *
.playBGM *
.transition 0 * 10
.stage	* WHITE.png 0 0
.transition 0 * 10
.stage	* WHITE.png 0 0
.wait 100

.chain 111_01.sc
;■111_01へ。

;.end
