; ファイル: 100_01.txt
;■＜１章：ＯＰ＞
;■100はすべて夜色。
;.playBGM *
;.panel 0
.setGlobal EYE_SEQ_DEFAULT = 2
.transition 0 * 10
.stage	* WHITE.png 0 0
;.playBGM *
;.effect *
;（000からの雪の演出を，ここで止めてます）


;■御影チェック
;■　前のシーンのフェードと，下のウェイトもあるので，ちと長すぎだな。
;■　ワンテンポだけ軽く。
;.wait 500
.wait 400


;.playBGM *
.transition 0 * 10
.stage	* terop_10001a.png 0 0
.message	101			\a　
.wait 450
.transition 0 * 10
.stage	* WHITE.png 0 0
;■夜空
;.transition 0 * 10
;.stage	* 10001_sky_c_sepia.png 0 0
.playBGM efBGM025mix.ogg
.transition 0 * 10
.stage	* ev01_sky_a_sepia.png 0 0
;（地文と違い，星は瞬きまくってますが……保留。全体的に夜·曇りを用意してもらうか？）
.panel 1
.message	100			漫步在冰冷的夜色里。
.transition 0 * 20
.stage	* ev01_sky_b_sepia.png 0 0
.message	110			窜入靴中的寒气使身体为之颤抖，充斥四周的寂静使双耳为之刺痛。
.message	120			从五光十色的街道仰望天空，只有那轮明月绽放着朦胧的残光。
;.message	120			光に彩られた街から仰ぎ見る空に，星は見えない。
;.message	130			月だけがぼんやりとした光を放っている。
.transition 0 * 20
.stage	past_window.png bgw_normal011a01_03_10001_sepia.png 0 0
.message	140		丂峢丂	「好冷……」
.message	150			呼出的白气也溶入无边的黑暗。
.message	160			我蜷缩着身体，缓缓挪动着脚步。
.message	170			虽说冬天会冷是理所当然──


;■背景：教会前（冬，２０時
;■　　　　广野纮　：私服（冬·外出）
.transition 0 * 20
.stage	past_window.png bgw_normal011a01_03_10001_sepia.png 0 0
.vscroll	1096	10
.endScroll f
.message	180			希望不要下雪啊。
.message	190			我对白色圣诞可没什么兴趣。
.message	200			无论是不是圣诞节，下雪都只是单纯的自然现象。
.transition 0 * 20
.stage	past_window.png bgw_normal011a01_03_10001_b_sepia.png 0 1096
.scroll	400 1046	6
.endScroll f
.message	210			琐事而已。

;■御影チェック
.panel 0


;■ＳＥ：木製の扉が開く音
;■シーン転換(フェード？）
;■背景：教会内（祭壇）
;■　　　　广野纮　：私服（冬·外出）
;■　　　　雨宮优子：私服（冬·外出）
.playSE kyoukai_door.ogg f 0 *
.transition 0 * 20
.stage	* ev00_001a01_sepia.png 0 600
.transition 0 * 10
.stage	* ev00_001a01.png 0 600
.panel 1
.message	220			厚重的门扉的另一侧，站着一位少女。
.transition 0 * 40
.stage	* ev00_001b01.png 0 600
.message	230	yuk-100_01-0003	@桪丂巕	「哎呀」
.playBGM efBGM026mix.ogg
.panel 0
.transition 0 * 20
.stage	* ev00_002a03.png 0 900
.vscroll	250	-10
.endScroll f
.panel 1
.message	240			站在祭坛前的少女转过身来，对我嫣然一笑。
.message	250			看起来很娇弱的样子，年龄大概比我小一两岁吧？
.message	260	yuk-100_01-0005	@桪丂巕	「虽然很遗憾，但圣诞弥撒已经结束了哦。如果想参加的话，还请明年再来」
.message	270		丂峢丂	「啊…我并不是什么信徒啦」
.transition 0 * 40
.stage	* ev00_002a01.png 0 250
.message	280	yuk-100_01-0007	@桪丂巕	「那么，为什么来这呢？　这儿的教会并不搞赈灾救济活动的哦」
.message	290		丂峢丂	「白痴啊你」
.message	300			我又不是流浪汉。
;■御影チェック
;.message	310		丂峢丂	「ただ，ちょっと……クリスマスの教会っていうのはどんなもんなのかなーと思って，のぞいてみたんだけど。勝手に入ったらまずい？」
.message	310		丂峢丂	「只是…心中稍微…有些好奇圣诞夜的教会是什么样子…，便过来看看而已」
.message	315		丂峢丂	「擅自进来会造成不便吗？」
.transition 0 * 40
.stage	* ev00_002a02.png 0 250
.message	320	yuk-100_01-0009	@桪丂巕	「倒没有什么不便，不过你还真是对一些怪事感兴趣呢。既然今天是圣诞节，比起教会去街上逛逛会更加有趣吧？」
.message	330		丂峢丂	「嘛，对怪事感兴趣该说是职业病吧…」
.transition 0 * 20
.stage	* ev01_001a01.png 0 0
;（フェードスピード40で？さらにこのＣＧで笑顔も用意してもらう）
.message	340	yuk-100_01-0011	@桪丂巕	「职业…吗……？」
.message	350			少女略显疑惑。
.message	360			毕竟怎么看我都不像个已踏入社会的人，心存疑问也是理所当然。
.message	370		丂峢丂	「不用太介意这些小事。说起来还真是冷清啊，这里…」
.message	380	yuk-100_01-0013	@桪丂巕	「弥撒结束的话，虽说是圣诞节这儿也与普通的教会别无不同。再说，弥撒本身也不是什么有趣的事情呢」
.message	390		丂峢丂	「唔……。说起来，你是谁？」
.message	400	yuk-100_01-0015	@桪丂巕	「我么？　和你相同哦」
.message	410		丂峢丂	「嗯？　那是什么意思？」
.message	420	yuk-100_01-0017	@桪丂巕	「明明是圣诞节，却没有恋人可以共渡良宵的寂寞的人哦」

;■御影チェック
;.message	430			少女は口元をシニカルに歪める。
.message	430			少女显露出自嘲的口吻。

.message	440		丂峢丂	「……我想问的可不是这个」
.message	450	yuk-100_01-0019	@桪丂巕	「说笑而已。露出那样的表情好吓人的啦」
.message	460			话虽如此，那少女的态度倒是十分轻松，完全看不出有害怕的神情。
.transition 0 * 20
.stage	* ev01_002a06.png 0 0
.message	470	yuk-100_01-0021	桪丂巕	「我的名字叫雨宮优子。写法是，在“雨”中，参拜神宫的“宫”以及“优”秀善良的孩“子”」
;（名前をヒラかせるタイミング，よく考察のこと）
.message	480	yuk-100_01-0023	桪丂巕	「顺提,我仅仅是个路人而已哦」
.message	490		丂峢丂	「不是穿着修女似的衣服嘛。不是这里的工作人员么？」
.message	500	yuk-100_01-0025	桪丂巕	「只是凑巧穿了这种式样的服装啦。我既不是教会的工作人员也不是相关人士哦」
.message	510		丂峢丂	「感谢您的细致解说」
.message	520	yuk-100_01-0027	桪丂巕	「不不，别客气」
.message	530		丂峢丂	「……嗯？　雨…宫…优…子……？」
.message	540			总觉得有些在意。
.message	550			雨宮优子──
.message	560			微微有种似曾相识的感觉，却不能确定。
.transition 0 * 40
.stage	* ev01_002a01.png 0 0
.message	570	yuk-100_01-0029	桪丂巕	「嗯？　怎么了吗？」
.message	580		丂峢丂	「……没什么」
.message	590			我摇了摇头。
.message	600			对她的样子并没有印象，可能仅仅是错觉吧。
.message	610	yuk-100_01-0031	桪丂巕	「难道是，对我一见钟情？」
.transition 0 * 40
.stage	* ev01_002a02.png 0 0
.message	620	yuk-100_01-0033	桪丂巕	「虽说这也是情不自禁的事情，但如果可以的话我希望先从朋友做起呢……」
.message	630		丂峢丂	「你想吵架吗？」
;.transition 0 * 40
;.stage	* ev01_002a06.png 0 0
;（ここの表情の演出，留意のこと）
.message	640			我使劲瞪了她一眼，宫村优子故意缩了缩脖子，装出想要逃跑的样子。
.message	650			完全被小看了……。
.transition 0 * 40
.stage	* ev01_002a05.png 0 0
.message	660	yuk-100_01-0035	桪丂巕	「是个不太懂幽默的人呢」
.message	670		丂峢丂	「很抱歉，我就是这么一本正经」
.transition 0 * 40
.stage	* ev01_002a01.png 0 0
.message	680	yuk-100_01-0037	桪丂巕	「原来如此。那么，一本正经的你的名字是？」
.message	690		丂峢丂	「没什么报上名字的必要吧」
.message	700			为什么我非得要对一路人甲报上名字不可呢。
.transition 0 * 40
.stage	* ev01_002a03.png 0 0
.message	710	yuk-100_01-0039	桪丂巕	「这样太狡猾了啦。我都有认真报上自己的名字的哦」
.message	720			她微微嘟起了她的小嘴。
.message	730		丂峢丂	「那是你自说自话报上来的吧」
.message	740	yuk-100_01-0041	桪丂巕	「又没关系嘛，名字而已。说出来又不会少点什么」
.message	750			听她这么一说，就越来越不想说了。
.message	760		丂峢丂	「…………」
.message	770	yuk-100_01-0043	桪丂巕	「哇哇，终于进入沉默模式了吗」
.message	780		丂峢丂	「…………」
.transition 0 * 40
.stage	* ev01_002a03_close.png 0 0
.message	790	yuk-100_01-0045	桪丂巕	「算了算了。我也不是特别想知道你叫什么名字。知道你的名字对我也没有任何好处」
.message	800		丂峢丂	「广野啦。广野纮」
.transition 0 * 40
.stage	* ev01_002a01.png 0 0
.message	810	yuk-100_01-0047	桪丂巕	「…………」
;（「目を半開きにして」……ちょっと保留）

;■御影チェック
;■　コメントアウトしておけばいいか。
;.message	820			雨宮优子は目を半開きにして，俺を凝視している。

.transition 0 * 40
.stage	* ev01_002a02.png 0 0
.message	830	yuk-100_01-0049	桪丂巕	「乖僻的家伙」
.message	840		丂峢丂	「要你管」
.transition 0 * 40
.stage	* ev01_002a06.png 0 0
.message	850	yuk-100_01-0051	桪丂巕	「呵呵呵」
.message	860			突然，她呵呵地笑了起来。
.message	870		丂峢丂	「……有什么好笑的…」
.message	880	yuk-100_01-0053	桪丂巕	「不不，没什么」
.message	890			雨宮优子收起笑容，摇了摇头。
.transition 0 * 40
.stage	* ev01_002a02.png 0 0
.message	900	yuk-100_01-0055	桪丂巕	「广野…纮先生吗……」
.transition 0 * 40
.stage	* ev01_002a06.png 0 0
.message	910	yuk-100_01-0057	桪丂巕	「嗯，是个好名字呢」
.message	920		丂峢丂	「被人夸奖有个好名字有什么可高兴的。那是在自己不知情的情况下被人擅自取的」
.transition 0 * 40
.stage	* ev01_002a01.png 0 0
.message	930	yuk-100_01-0059	桪丂巕	「啊啦啦，还真是性格乖僻呢……」
.transition 0 * 40
.stage	* ev01_002a02.png 0 0
.message	940	yuk-100_01-0061	桪丂巕	「不过，我不讨厌这种类型的哦」
.message	950		丂峢丂	「哈，你就是讨厌我也完全无所谓」
.message	960			我在说什么废话呢。
.message	970			而且，还是在这深夜的教会，对着一个陌生的女孩子。
.transition 0 * 40
.stage	* ev01_002a06.png 0 0
.message	980	yuk-100_01-0063	桪丂巕	「总觉得……你还真是一个奇怪的人呢……」
.message	990		丂峢丂	「一个人呆在这种地方的你也够奇怪了吧。说真的，你到底是在这干什么啊？」
.message	1000	yuk-100_01-0065	桪丂巕	「是哦……」
.transition 0 * 20
;.transition 1 fadeSide.png 20
.stage	* ev01_001a01_mugai_a.png 0 0
.message	1010			接下来的一段时间，教会陷入了沉默。
.message	1020			墙壁上并列的蜡烛的微光，也为少女的面庞笼罩上一层朦胧的暗色。
;（「壁面に並んだキャンドル」……ちょっと注意）
.message	1030			少女将视线移向虚空，我正以为她可能在认真的为什么事烦恼的时候，她却又突然露出了笑容。
.transition 0 * 20
;.transition 1 fadeSide.png 20
.stage	* ev01_002a04.png 0 0
.message	1040	yuk-100_01-0067	桪丂巕	「……我有一个必须要见的人」
.message	1050			和刚才那种略带作弄感的微笑似乎稍有不同。
.message	1060		丂峢丂	「必须要见的人……？　谁呢？」
.transition 0 * 40
.stage	* ev01_002a06.png 0 0
.message	1070	yuk-100_01-0069	桪丂巕	「是啊，是谁呢」
.message	1080		丂峢丂	「这算什么意思」
.message	1090			果然，是被戏弄了吗。
.transition 0 * 40
.stage	* ev01_002a01.png 0 0
.message	1100	yuk-100_01-0071	桪丂巕	「我，并不是在开玩笑哦」
.message	1110		丂峢丂	「真的吗」
.message	1120			我觉得十分值得怀疑。
.message	1130	yuk-100_01-0073	桪丂巕	「我也不知道那个人是谁啊」
.message	1140			这家伙，是在玩我吧……。
.message	1150		丂峢丂	「虽然不知道是谁，总之的确是有个想要见的人」
.transition 0 * 40
.stage	* ev01_002a04.png 0 0
.message	1160	yuk-100_01-0075	桪丂巕	「嗯」
.message	1170		丂峢丂	「约定见面的地点是这个教会吗？」
.message	1180	yuk-100_01-0077	桪丂巕	「大概吧…」
.message	1190		丂峢丂	「大概是……时间呢？」
.message	1200			雨宫优子轻轻地摇了摇头。
.message	1210			连时间都没决定下来的话，根本束手无策吧。
.transition 0 * 40
.stage	* ev01_002a02.png 0 0
.message	1220	yuk-100_01-0079	桪丂巕	「那也是没办法的」
.message	1230	yuk-100_01-0081	桪丂巕	「因为那是远到连记忆都已模糊不清的过去所订下的约定了……」
.message	1240		丂峢丂	「久远的过去啊……」
.message	1250			孩提时代所作的约定吧。
.message	1260			相信那种东西，根本毫无意义。
.message	1270		丂峢丂	「再怎么说，还真是含糊的说法啊。真的认为可以见到那个人吗？」
.transition 0 * 40
.stage	* ev01_002a06.png 0 0
.message	1280	yuk-100_01-0083	桪丂巕	「当然」
.message	1290			雨宮优子用力点了点头。
.transition 0 * 40
.stage	* ev01_002a01.png 0 0
.message	1300	yuk-100_01-0085	桪丂巕	「虽然不知道那是谁……。但觉得只要呆在这就能见到。而且，今夜不是圣诞节嘛」
.transition 0 * 40
.stage	* ev01_002a02.png 0 0
.message	1310	yuk-100_01-0087	桪丂巕	「只是今晚的话，做做美梦也是可以的吧」
.message	1320			这该不会是在征求我的同意吧。
.message	1330		丂峢丂	「就算不是今晚，美梦什么的随时都可以做吧」
.transition 0 * 40
.stage	* ev01_002a06.png 0 0
.message	1340	yuk-100_01-0089	桪丂巕	「不，圣诞节是特别的呢」
.message	1350	yuk-100_01-0091	桪丂巕	「虽然可能是无法实现的愿望，不过只要是在今晚许梦的话，一定是能被允许的」
.message	1360		丂峢丂	「被允许？被谁？」

;■御影チェック
;.message	1370	yuk-100_01-0092		雨宮优子は答えず，白い歯を見せて嬉しそうに笑った。
.message	1370	yuk-100_01-0092		雨宮优子她没有回答，只是微微一笑。

.message	1380			完全理解不能。
.message	1390			真是让人莫名其妙的女孩啊。
.message	1400			反正也没理解的必要，放弃好了。
.message	1410		丂峢丂	「嘛，能见到的话就好了呢。努力吧……」
.transition 0 * 40
.stage	* ev01_002a01.png 0 0
.message	1420	yuk-100_01-0093	桪丂巕	「你呢？」
.message	1430		丂峢丂	「我怎么了？」
.transition 0 * 40
.stage	* ev01_002a06.png 0 0
.message	1440	yuk-100_01-0095	桪丂巕	「你，难道没有想一起过圣诞的人吗？」
.message	1450		丂峢丂	「没有」
.message	1460			我断然答道。
.transition 0 * 40
.stage	* ev01_002a01.png 0 0
.message	1470	yuk-100_01-0097	桪丂巕	「还真是迅速的回答呢」
.message	1480		丂峢丂	「即使装模作样答案也不会改变嘛」
.message	1490		丂峢丂	「没有，想呆在一起的人之类。就是因为没有，才会一个人在这儿」
.transition 0 * 40
.stage	* ev01_002a02.png 0 0
.message	1500	yuk-100_01-0099	桪丂巕	「那样没关系吗？」
.message	1510		丂峢丂	「又没什么困扰的地方」
.message	1520			我也并不是说孤身一人更好。
.message	1530			即便如此，也确实没有积极的想过想要和谁在一起。
.message	1540			也并不是寂寞或者无聊什么的──
.message	1550			只是，不知为何有些静不下来。
.message	1560			我会到这里来的理由仅此而已，并没有特别期望着什么。
.message	1570		丂峢丂	「和你不一样哦」
.transition 0 * 20
;.transition 1 fadeSide.png 20
.stage	* ev01_001b01.png 0 0
;（ここだけ，サイドフェードにしていくか？後は通常フェードでも）
;（フェードスピード40で？）
.message	1580			我转身想要离开。
.message	1590	yuk-100_01-0101	桪丂巕	「咦，你要去哪？」
.transition 0 * 40
.stage	* ev01_001b02.png 0 0
.message	1600		丂峢丂	「回去。我在这里也无事可做，而且冷死了」
.message	1610	yuk-100_01-0103	桪丂巕	「再稍微陪陪我不行吗？」
.message	1620		丂峢丂	「我可没那么多闲工夫。再会」
.message	1630			虽然估计不会再见面了吧。
.message	1640	yuk-100_01-0105	桪丂巕	「啊，请稍待一下」
.transition 0 * 20
.stage	* ev01_001c01.png 400 0
;（振り向かせるタイミング，注意のこと。さらにこの差分で，优子が画面外に出ているものも用意してもらう？）
.message	1650			正要起步离开时，又被她从背后叫住。
.message	1660		丂峢丂	「嗯？」
.message	1670	yuk-100_01-0107	桪丂巕	「有一句话忘记说了呢」
.message	1680		丂峢丂	「……什么」
.message	1690			雨宮优子扬起一个恶作剧般的微笑──
.transition 0 * 20
.stage	* ev00_015a03.png 0 0
.panel 0
;（フェードスピード40で？さらにここ，メッセージウインドウを消して，音声のみで演出？）
.message	1700	yuk-100_01-0109	#桪丂巕	「圣诞快乐」\v\a
.wait 200
;.wait 250
;.wait 450
;.panel 0
.transition 0 * 10
.stage	* WHITE.png 0 0
;（場面転換のさせ方，フェードのスピードなどは要考察のこと）
;.panel 0


;■タイトルＩＮ
;.wait 500
;.transition 0 * 10
;.stage	* terop_10001d.png 0 0
;.wait 420
.wait 300
;.transition 0 * 10
.transition 0 * 7
.stage	* terop_10001e.png 0 0
.message	1701			\a　
;.wait 400
.wait 380
;.transition 0 * 10
.transition 0 * 7
.stage	* terop_10001g.png 0 0
.message	1701			\a　


;■宫子主観
;■背景：火村の家の前（冬，２０時３０分
;■　　　　宮村宫子：私服（冬·外出）
.panel 3
.playBGM *
;.transition 0 * 5
.transition 0 * 8
.stage	* bgw_sky001a01_03.png 0 0
.message	1710	miy-100_01-1003		会不会下雪呢――
.message	1720	miy-100_01-1005		忽然，这个念头闪入我的脑海。
.message	1730	miy-100_01-1007		觉得如果下一场雪的话，今年的圣诞节就可以在残留在回忆中。
.message	1740	miy-100_01-1009		难得的圣诞节，下雪这种程度的事件赠送一下也没什么吧？
.message	1750	miy-100_01-1011		我心中如此这般地想着。
.message	1760	miy-100_01-1013		虽然一个人看雪的话，也根本毫无浪漫可言。
.message	1770	miy-100_01-1015		走在街上的大家看起来好幸福啊。
.message	1780	miy-100_01-1017		分明不可能所有人都幸福的。
.message	1790	miy-100_01-1019		可能是我的偏见吧，也许只是大家都认为自己很幸福，而在不断欺骗着自己。
.message	1800	miy-100_01-1021		大家，都在拼命的骗着自己――
.message	1810	miy-100_01-1023		连身边的事都忘记了关心。
.message	1820	miy-100_01-1025		就算我哭，大家也只会从我身边走过而已。
.message	1830	miy-100_01-0003	#傒傗偙	「嘛，虽然我倒是没哭」
;（主観，宫子に移りつつも，名前は？が指定されているが，問題はないのか？）
;（#と@の使い方はよく研究しておくこと）
.screen sc_night01.png sc_night01.png
.transition 0 * 20
.stage	* bgw_normal017a01_03.png 0 0
.message	1840	miy-100_01-1027		不知何时已经离开街市的喧嚣，回过神来已经到了这里。
.message	1850	miy-100_01-1029		寥无人烟呢……。
.message	1860	miy-100_01-0005	#傒傗偙	「呼─」
.message	1870	miy-100_01-1031		喝着刚从自动贩卖机买来的热热的罐装咖啡，轻叹了一口气。
.message	1880	miy-100_01-1033		加入了大量牛奶和砂糖的咖啡，又甜又暖真是至高的享受。
.message	1890	miy-100_01-1035		虽然很好喝，却又有些空虚。
.message	1900	miy-100_01-0007	#傒傗偙	「差不多该回去了吧」
.message	1910	miy-100_01-1037		我看了一眼手表。
.message	1920	miy-100_01-1039		虽然这附近治安也不是很差，但毕竟也不是适合一个女孩子孤身瞎转的时间段了。
.message	1930	miy-100_01-0009	#傒傗偙	「真不知是为了什么才跑出来的……」
.playSE akikan.ogg f 0 *
.message	1940	miy-100_01-1041		我叹了一口气，把剩下的咖啡一饮而尽，然后把它丢进了近处的垃圾箱。
.message	1950	miy-100_01-0011	#傒傗偙	「好！　回去吧！」
.playSE bike_a2.ogg f 0 *
;（ここ，ケツはフェードアウトさせて？）
.message	1960			呜呜呜呜……
.message	1970	miy-100_01-0013	#傒傗偙	「嗯？」
.message	1980	miy-100_01-1043		低沉的引擎声从远处渐渐接近。
.message	1990	miy-100_01-1045		带发动机的机车吗？
.message	2000	miy-100_01-1047		这么冷的天还骑摩托车上街，还真是有毅力呢。
.message	2010	miy-100_01-1049		慢慢地，摩托车的灯光越来越近。
.message	2020	miy-100_01-1051		…………诶？
.message	2030	miy-100_01-1053		怎么似乎笔直地朝这边──
.screen * *
.playSE bike_b.ogg f 0 *
.transition 0 * 40
.stage	* bgw_normal017a01_03_10001b.png 0 0
.transition 0 * 40
.stage	* bgw_normal017a01_03_10001a.png 0 0
.message	2040	miy-100_01-1055		哇，好耀眼─。
.transition 0 * 40
.stage	* WHITE.png 0 0
.message	2050	miy-100_01-1057		就在我眯起眼睛的同时。
;■画面白，揺れも加味
.playSE butsukaru.ogg f 0 *
.transition 0 * 100
.stage	* WHITE.png 0 0
.shakeScreen	R	100	100
.shakeScreen	R	100	100
.shakeScreen	R	100	100
.message	2060	miy-100_01-0015	#傒傗偙	「呀！」
.message	2070	miy-100_01-1059		刚感觉到肩膀突然受到的冲击时，我就已经躺倒在地面了。
.transition 0 * 20
.stage	* ev01_003_10001.png 0 600
.scroll	200 400	10
;（目ではなくカメラを動かした錯覚を利用した手法……まあ１カットなのでそれほど問題はないはず）
.message	2080	miy-100_01-0017	#傒傗偙	「好疼………怎么回事？」
;■通常背景
.screen sc_night01.png sc_night01.png
.transition 0 * 20
.stage	* ev01_003.png 0 0
.message	2090	miy-100_01-1061		抬起头来，摩托车已经开至前方数十米之外了。
.message	2100	miy-100_01-0019	#傒傗偙	「干什么嘛，真是的─」
.transition 0 * 40
.stage	* bgw_normal017a01_03.png 0 0
.message	2110	miy-100_01-1063		似乎也并不是被摩托车给撞了。
.message	2120	miy-100_01-1065		仅仅是臀部碰到而已，别的地方倒不觉得疼。
.message	2130	miy-100_01-0021	#傒傗偙	「咦，啊啊──────！」
.message	2140	miy-100_01-0023	#傒傗偙	「不见了！　我的提包！」
.message	2150	miy-100_01-1067		本来应该是在肩膀上挎着的提包不见了。
.screen * *
.transition 0 * 100
.stage	* bgw_normal017a01_03_10001.png 200 600
.hscroll	600	100
.endScroll f
.hscroll	200	-100
.endScroll f
.hscroll	800	150
.endScroll f
.hscroll	0	-150
.endScroll f
.message	2160	miy-100_01-1069		我迅速的站起来，观察四周的情况。
.message	2170	miy-100_01-1071		昏暗的街灯照耀下的地面上，并没有那只眼熟的提包。
.vscroll	200	-150
.endScroll f
.message	2180	miy-100_01-1073		难道，难道是刚才的摩托车……。
.transition 0 * 20
.stage	vista_window.png bgw_normal017a01_03_10001.png 0 200
.panel 0
;.panel 0
;.transition 0 * 20
;.stage	* bgw_normal017a01_03_10001.png 0 200
.message	2190	miy-100_01-0025	#傒傗偙	「小偷─！！」\a
.transition 0 * 10
.stage	* vista_white.png 0 0
;.panel 0
.transition 0 * 10
.stage	* WHITE.png 0 0
;（白を挿まなくても良いか？シネマから通常ウインドウに移行する時のパネル0の置き方はよく研究しておくこと）


;■シーン転換
;■背景：教会前（冬，２０時３０分
;■　　　　广野纮　　：私服（冬·外出）
;■　　　　宮村宫子：私服（冬·外出）
.screen sc_night01.png sc_night01.png

.transition 0 * 10
.stage	* bgw_normal011a01_03.png 0 600
.panel 1
.message	2200	miy-100_01-0027	@傒傗偙	「小偷─！！」
.message	2210		丂峢丂	「……啊嗯？」
.message	2220			正准备骑上自己停在教会旁的自行车时，突然听到了奇怪的声音。
.message	2230		丂峢丂	「小偷？」
.message	2240			正想着就在刚刚，才有辆摩托车以疯狂的速度行驶了过去，现在又来了什么小偷？
.message	2250			还真是骚乱的夜晚呢……。
.message	2260	miy-100_01-0029	@傒傗偙	「站住─！」
.playBGM efBGM013.ogg 0 *
.transition 0 * 20
.stage	* ev01_004.png 0 0
.message	2270			一个女孩子从道路那边啪嗒啪嗒地跑了过来。
.message	2280			即使是在夜路上也可以清楚察觉到，那个女孩子非常的慌忙。
.message	2290		丂峢丂	「…………」

.overlay * or_miyako03a02.png

;（スクリーンはかけてません。値は仮のものです）
;.transition 0 * 20
.transition 0 * 30
.stage	* bgw_normal011a01_03.png 0 600 st_miyako03d04.png 400
;（ここから，立ち絵初使用。後ろのモブを消して，前に来た感じをスムーズに構築。フェードスピードにも注意）
.message	2300	miy-100_01-0031	@傒傗偙	「啊，喂喂，那边的人！」
.message	2310			唔哇，跟我搭话了吗？
.message	2320		丂峢丂	「怎么？」
.message	2330			保持警戒状态，总之还是回应了一声。
.transition 0 * 40
.stage	* bgw_normal011a01_03.png 0 600 stm_miyako03d04.png 400
;（同じポーズ，同じ表情で，中距離立ち絵を）
.message	2340	miy-100_01-0033	@傒傗偙	「有没看到一辆摩托车！？」
.message	2350		丂峢丂	「看是看到了」
.message	2360	miy-100_01-0035	@傒傗偙	「知道往哪边走了吗！？」
.message	2370		丂峢丂	「……那边」
.message	2380			我指了指那摩托车开走的方向。
.transition 0 * 40
.stage	* bgw_normal011a01_03.png 0 600 st_miyako01d07.png 500
;（フェードスピード50で？）
.message	2390	miy-100_01-0037	@傒傗偙	「谢了！　啊，这个借用下！」
.message	2400		丂峢丂	「哈？」
.transition 0 * 40
.stage	* bgw_normal011a01_03.png 0 600 st_miyako03d04.png 400
;（今回はトラジションを，立ち絵でもきちんと置くようにしています）
;（ポーズは変えて，右寄りに立ち絵は配置？）
.message	2410	miy-100_01-0039	@傒傗偙	「拦路抢劫啊！　我重要的提包，被那人偷了啊！」
.transition 0 * 40
.stage	* bgw_normal011a01_03.png 0 600
.message	2420			话音未落，这个陌生女人已经跨上了我的爱车，消失在冬夜的夜幕里了……。
.message	2430		丂峢丂	「喂，给我等等啊」
.message	2440			我不知道你是不是被人拦路抢劫了……
.message	2450			然你这不就是一自行车强盗吗！
.message	2460			我边发着牢骚，边大步追了上去。
.panel 0
.HSVfilter 0 0 0 0 0 0
.overlay * *
.screen * *
.playBGM *
.transition 0 * 10
.stage	* WHITE.png 0 0
;（サイドフェードで？）


;■シーン転換
;■背景：十字路（冬，２１時
;■　　　　广野纮　　：私服（冬·外出）
;■　　　　宮村宫子：私服（冬·外出）
.playSE karakara.ogg f

.screen sc_night01.png sc_night01.png

.transition 1 fadeSide.png 10
.stage	* ev01_005a01.png 0 0
.panel 1
;（サイドフェードで？）
.message	2470		丂峢丂	「…………」
.message	2475		丂峢丂	「………………」
;☆（↑向井が三点一行追加）
;（ここの３点リーダー，４クリックぐらいのばせるといいかも）
.message	2480		丂峢丂	「……………………」
.message	2490			在道路上发现惨不忍睹的爱车倒在地上时，是10分钟之后的事情了。
.message	2500			貌似摔法十分之华丽，连车把手和骨架都扭曲变形了。
.message	2510			看着咯啦咯啦空转着的车轮，我都有些想哭了。
.playSE *
.message	2520		丂峢丂	「我该怎么办好orz」
;★イベントＣＧ　道路に寝転がる宫子
.message	2530			在自行车的旁边，还有一位在道路中间摆着大字一动不动的女孩子。
.message	2540			虽然我个人很想先确认一下我爱车的状况，但作为一个有良识的人还是得先考虑怎么处理这个女孩子……。
;☆（纮の位置，注意して。モブを作ってもらう？）
.message	2550		丂峢丂	「我也算是，为人子女嘛」
.message	2560			这女孩，还真是一动不动哎。
.message	2570			乍看之下似乎没有什么外伤，可能是撞到头了吧。
.message	2580			若真是死了还的确有些棘手，但就这么放着不管的话首先冻死是必然的吧。
.message	2590		丂峢丂	「喂，我说你。还活着吗？」
.message	2600			…………。
.message	2610			完全没有反应。
.screen * *
.transition 0 * 20
.stage	* ev01_006a01_mugai_e.png 0 0
;☆（仮に挿んでます）
.message	2620			轻轻的摇了摇她的肩膀，试着拍了拍脸颊，都没有任何醒来的征兆。
.message	2630		丂峢丂	「糟了。难道真的成佛了么……」
.message	2640		丂峢丂	「没办法了」
;■通常背景
.screen sc_night01.png sc_night01.png

.transition 0 * 20
.stage	* ev01_005b01.png 0 0
.message	2650			我取出手机，拨了119。
.playSE hiro_keitai_out.ogg true 0 *
.message	2660			噜噜噜噜噜……
.playSE * f * 0
;（ガチャ……とかいう音でも入れるか？つーか携帯でガチャ（リ）はないか……。それでも携帯で相手が出た時の音……実際はどうなのかをきちんと調べておくこと）
.message	2670	etc-100_01-0003	徚丂杊	『这里是消防119。请问是火灾？　还是急救？』
.message	2680		丂峢丂	「啊…，这里有位伤者。好像是骑自行车时摔倒了，现在一动也不动了」
.message	2690	etc-100_01-0005	徚丂杊	『请问是在哪里？』
.message	2700		丂峢丂	「恩，记得这确实是……」
.message	2710			…………
.message	2720			……
.message	2730		丂峢丂	「……总之，这样就行了吧」
;（携帯をポケットにしまう……つまりev01_005b01の続行ができないということなので考えておくこと）
.screen * *
.transition 0 * 20
.stage	* ev01_005b01_mugai_a.png 0 0
;（背景ぼかして…まあ逆もありうるが，纮立ち絵後ろ向きを配置というのも有りかもしれん）
.message	2740			通完话，我把手机放回口袋里。
.message	2750		丂峢丂	「该不会，等下救护车来了，我也得陪着一起吧」
.message	2760			最根本的问题，这个人到底是活着还是死了……。
;★イベントＣＧ　道路に寝転がる宫子
.message	2770			总之，在救护车来之前先确认一下生死吧。
.message	2780			看起来是完全失去了意识，呼吸方面怎么样呢。
;.transition 0 * 20
;.stage	* ev01_006a01.png 0 0
.transition 0 * 20
.stage	* ev01_006a01_mugai_b.png 0 0
;（このＣＧはもう少し前で表示させて，ここからは切り出しを使ったＣＧで演出していくか？）
.message	2790			我试着把耳朵凑向女孩的鼻子附近。
.message	2800		丂峢丂	「听不太明白呢」
.transition 0 * 20
.stage	* ev01_006a01_mugai_c.png 382 402
.scroll	100 100	6
.message	2810		丂峢丂	「…………嗯？」
.transition 0 * 20
.stage	* ev01_006a01.png 0 0
.message	2820			在近处看她的脸庞才刚刚注意到。
.message	2830			这个女孩子，可爱的有点过分了吧？
.message	2840			如果不是这种紧急状态，实在是想取出素描簿给画上一张。
.message	2850			不，反正现在我也没什么事做，画张素描似乎也不错……。
.message	2860			身上背着的背包里一直都有放着铅笔和素描簿。
.message	2870			OK，万事俱备。
.transition 0 * 20
.stage	* ev01_006a01_mugai_a2.png 0 0
.message	2880			总之，再认真的观察一下脸庞吧……。
.transition 0 * 40
.stage	* ev01_006a02_mugai_a2.png 0 0
.message	2890			──睁开。
.message	2900		丂峢丂	「唔哇！」
.transition 0 * 20
.stage	* ev01_006a02.png 0 0
.message	2910			正当我接近到几乎可以数清她有几根睫毛的时候，她突然睁开了眼睛。
.message	2920	miy-100_01-0041	@傒傗偙	「…………」
.message	2930		丂峢丂	「啊，不是这样的……」
.message	2940			什么不是这样啊，我辩解什么呢。
.transition 0 * 40
.stage	* ev01_006a03.png 0 0
;（「２，３度まばたき」……まあ瞬きまで考えなくてもいいかあ）
.message	2950	miy-100_01-0043	@傒傗偙	「……咦」
;■ここから通常背景
.message	2960			那女孩子眨了两三下眼睛之后，忽地站了起来。

.screen sc_night01.png sc_night01.png

.overlay * or_miyako03a02.png


.transition 0 * 20
.stage	* ev01_005a01_mugai.png 0 0 st_miyako06d03.png 400
;.stage	* ev01_005a01_mugai.png 0 0 st_miyako06d01.png 400
.message	2970	miy-100_01-0045	@傒傗偙	「呃嗯，我……在干什么呢？」
.transition 0 * 40
.stage	* ev01_005a01_mugai.png 0 0 st_miyako08d02.png 410
.message	2980		丂峢丂	「我可什么都不知道」
.transition 0 * 40
;.stage	* ev01_005a01_mugai.png 0 0 st_miyako06d03.png 400
;.stage	* ev01_005a01_mugai.png 0 0 st_miyako06d01.png 400
.stage	* ev01_005a01_mugai.png 0 0 st_miyako06d01_close.png 400
.message	2990			看来没招来什么奇怪的误解，我安下心来。
;.transition 0 * 40
;.stage	* ev01_005a01_mugai.png 0 0 st_miyako08d02.png 410
;.transition 0 * 40
;.stage	* ev01_005a01_mugai.png 0 0 st_miyako06d01.png 400
.transition 0 * 40
.stage	* ev01_005a01_mugai.png 0 0 st_miyako09d01.png 400
.message	3000			那女孩子东张西望的看了下四周，最后把目光停在了坏掉的自行车上。
;☆（ここから無音が続くので，さすがにここは激しいＢＧＭでもかける？）
.transition 0 * 40
.stage	* ev01_005a01_mugai.png 0 0 stm_miyako03d04.png 400
;.stage	* ev01_005a01_mugai.png 0 0 st_miyako07d05.png 410
;（03d04でもいいのかも）
;（中距離を使うこと）
.message	3010	miy-100_01-0047	@傒傗偙	「…………啊我想起来了！」
;.playBGM efBGM041.ogg
;.playBGM efBGM040.ogg
;☆（ＢＧＭはとりあえず入れてみています）
.transition 0 * 40
.stage	* ev01_005a01_mugai.png 0 0 st_miyako01d01.png 792
;（位置は正式立ち絵が来てから，座標を調整）
;（ここキャラを消すか，後ろ向きの立ち絵はさむか？）
.message	3020			才说完，她突然便跑了起来。
;.playBGM efBGM040.ogg
.message	3030		丂峢丂	「等，等一下！」
.screen * *
.playBGM efBGM040.ogg
.transition 0 * 40
.stage	* ev01_007a01_big.png 0 0
.scroll	400 300	40
.endScroll f
.transition 0 * 40
.stage	* ev01_007a01_big.png 400 300
.scroll	700 200	20
.endScroll f
;☆（目パチさせてませんが，ここはわざとで）
.message	3040			我慌忙拉住了她的手。
.transition 0 * 40
.stage	* ev01_007a01.png 0 0
.message	3050	miy-100_01-0049	@傒傗偙	「……要调戏我等会再说！」
.message	3060		丂峢丂	「誰要调戏你了！」
.message	3070			再说也不是什么先后的问题吧。
.message	3080	miy-100_01-0051	@傒傗偙	「我，现在很急的啦」
.message	3090			似乎是的确觉得很为难的口气。
.message	3100		丂峢丂	「你白痴啊，到刚才为止还处于昏迷状态的人想干什么啊你？」
.message	3110	miy-100_01-0053	@傒傗偙	「我的提包被偷了。所以不去追不行的啊」
.message	3120		丂峢丂	「这句话刚才听过了。但是，比起包起来命更重要的吧」
.transition 0 * 40
.stage	* ev01_007a02.png 0 0
.message	3130	miy-100_01-0055	@傒傗偙	「呜～嗯……比较微妙」
.message	3140			喂喂，大小姐。那不是你该烦恼的重点吧。
.message	3150		丂峢丂	「总·而·言·之，给我老实呆着就好」
.message	3160		丂峢丂	「而且，我已经叫过救护车了，你如果不呆在这的话我会有麻烦的」
.transition 0 * 40
.stage	* ev01_007a03.png 0 0
.message	3170			她的表情有些困惑。
.transition 0 * 20
.stage	* ev01_007a01_mugai_b.png 0 0
;.stage	* ev01_007a01_mugai_a.png 0 0
;（フェードスピードは仮）
.message	3180	miy-100_01-0057	@傒傗偙	「但是我又没拜托你去叫救护车吖，那是你自己的问题吧……？」
.message	3190		丂峢丂	「我要是只考虑自己的问题的话，伤员什么的一开始就无视掉了！」
.message	3200	miy-100_01-0059	@傒傗偙	「呜哇，你这冷酷无情的禽兽」
.transition 0 * 20
.stage	* ev01_007a04.png 0 0
;（フェードスピードは仮）
.message	3210		丂峢丂	「就是因为不冷酷无情我才叫了救护车吧！」
.transition 0 * 40
.stage	* ev01_007a05.png 0 0
.message	3220	miy-100_01-0061	@傒傗偙	「啊，原来如此。这是盲点嗯……」
.message	3230		丂峢丂	「……你能明白我好高兴」
.message	3240			我无力的说道。
.message	3250			我真的有点累了。
.transition 0 * 40
.stage	* ev01_007a01.png 0 0
.message	3260	miy-100_01-0063	@傒傗偙	「虽然我明白……。但果然还是不行」
.message	3270			她很明确的把话说绝，然后啪的甩掉了我抓住她的手。

.screen sc_night01.png sc_night01.png

.transition 0 * 20
.stage	* ev01_005a01_mugai.png 0 0 st_miyako03d04.png 400
;.stage	* bgw_normal005a01_03.png 0 0
;（ここから立ち絵で構築）
.message	3280	miy-100_01-0065	@傒傗偙	「提包里放着钱包还有手机，单说那个提包就是很贵的东西呢」
.message	3290	miy-100_01-0067	@傒傗偙	「任凭重要的东西被人偷走，我才不要呢」
.transition 0 * 40
.stage	* ev01_005a01_mugai.png 0 0 st_miyako07d05.png 410
.message	3300	miy-100_01-0069	@傒傗偙	「我绝对不放弃。无论如何都要抓住那家伙！」
;.playBGM *
.transition 0 * 40
.stage	* ev01_005a01_mugai.png 0 0
.message	3310			这次连阻止的机会都没有，她就已经跑开了。
.playBGM *
.message	3320			那女孩子不会真的是白痴吧。
.message	3330			再说了，犯人是开着摩托车逃掉的，早就逃到九霄云外去了吧。
.playSE ambulance_b.ogg f
;（『はるおと』からの流用です。保留）
.message	3340			哔～嘭～哔～嘭～哔～嘭～。
.message	3350		丂峢丂	「糟糕」
.message	3360			总觉得，情况好象变得非常之麻烦了。
.message	3370			救护车到达这里的话，我就不得不从头开始把事情原委解释清楚。
.message	3380			我明明没做什么坏事，为什么非得受到这样的待遇……。
.message	3390			不过说起来。
.message	3400			那个女孩子，放着不管不会有事吧。
.message	3410			她不是在追逐的途中摔倒过么？
.message	3420			就算她运气好找到了犯人，也不见得能取回提包。
.message	3430			再怎么看那女孩子都不像很有力气的类型。
.message	3440			最坏的情况下，说不定还会被反咬一口……。
.message	3450		丂峢丂	「啧─」
.message	3460		丂峢丂	「糟糕的一夜啊，真是的」
.playSE *
.playSE hiro_keitai_2.ogg true 0 *
;（曲は着歌と仮定して，ダミーのものです。ループはさせてません）
.message	3470			哔哩哩哩哩哩，哔哩哩哩哩哩。
.message	3480		丂峢丂	「嗯？」
.message	3490			正准备开始跑的时候，口袋中的手机突然响了起来。。
.message	3500		丂峢丂	「啊，糟了」
.message	3510		丂峢丂	「……果然是那家伙啊……」
.playSE * f * 0
;（効果音を瞬間的に止める場合はfを置くこと忘れずに）
.playSE pi.ogg f 0 *
;.transition 0 * 20
;.stage	* ev01_008a01.png 0 0
;（挿入位置，注意）
.message	3520			心情稍微有些紧张，我边跑边取出手机按下了通话键。
.screen * *
.transition 0 * 20
.stage	* ev01_008a01.png 0 0
;（ここからまだ来てませんが，イベントＣＧあります。歩きながら……なので，前の場所から移動した背景を？）
.message	3530		丂峢丂	「喂」
.message	3540	kei-100_01-0003	@丂宨丂	『喂！？』
;（ケツが二重鍵括弧になってない。注意されたし）
;（さらに妹から…じゃないのか·笑，まあ知り合いからの電話だが，【？】で表記させていいのか？）
;.transition 0 * 40
;.stage	* ev01_008a02.png 0 0
;（表情，注意）
.message	3550		丂峢丂	「喂，我是广野」
.message	3560	kei-100_01-0005	@丂宨丂	『不是什么“喂”吧！　哥哥，你现在在哪里！？』
.message	3570			不用说那么大声也听的到的啦喂。
.transition 0 * 40
.stage	* ev01_008a02.png 0 0
.message	3580		丂峢丂	「哪里啊……某个地方……」
.message	3590	kei-100_01-0007	@丂宨丂	『说了等于没说吧！　虽然我不希望这么想，但你该不是忘了我们的约定吧』
.message	3600		丂峢丂	「没忘记啊。只是放置不管了而已」
.message	3610	kei-100_01-0009	@丂宨丂	『你还真是死猪不怕开水烫诶！　稍微知错一下不好么！』
.transition 0 * 40
.stage	* ev01_008a03.png 0 0
.message	3620		丂峢丂	「因为没有能穿去参加城堡里舞会的礼服嘛」
.message	3630	kei-100_01-0011	@丂宨丂	『你是白雪公主吗！』
.transition 0 * 40
.stage	* ev01_008a04.png 0 0
;（二重鍵括弧になってない，注意されたし）
.message	3640			哎我说，那是灰姑娘吧。
.message	3650	kei-100_01-0013	@丂宨丂	『再说又不是什么舞会，是圣诞节聚会！』
.message	3660			哎呀，有点糟了啊……。
.message	3670			差不多真要把她惹火了。
.transition 0 * 40
.stage	* ev01_008a01.png 0 0
.message	3680		丂峢丂	「其实啊，现在不是说这些的时候」
.message	3690			由于后果实在可怕，现在暂且先把话题岔开。
.message	3700	kei-100_01-0015	@丂宨丂	『……突然来了紧急工作么？』
.transition 0 * 40
.stage	* ev01_008a04.png 0 0
.message	3710		丂峢丂	「不，怎么说呢──」
.message	3720			从远处传来了啪嗒啪嗒的脚步声。
.message	3730			糟了，说不定是救护队员们。
.transition 0 * 40
.stage	* ev01_008a05.png 0 0
.message	3740		丂峢丂	「有事下次再说吧」
.message	3750	kei-100_01-0017	@丂宨丂	『什么叫下次再说啊喂。给我等下！』
;（ここでヒラクのか？)
; 景であることは後にわかるので，主人公の台詞をいじりました nbkz）
;（↓効果音？ぷちっ……という音ではありませんが）

;■御影チェック
;■　電話を切った際は，それにあわせてボイスが止まるように修正します。
;■　切ったはずなのにボイスがあると変だ。
;■　ただし，一部例外はもうけます（途中で切れるのが逆におかしな場合）。
.playVoice *

.playSE pi.ogg f 0 *
;.transition 0 * 20
;.stage	* ev01_005a01_mugai.png 0 0
.transition 0 * 20
.stage	* ev01_005a01_mugai_a.png 0 0
;（主人公のいる場所，注意）
.message	3760			嘟。
.message	3770			我什么都没回答就切断了通话，然后收起手机。
.message	3780		丂峢丂	「好吧，接下来……」
.message	3790			不快一点的话，就要被救护队员们逮个正着了。
.message	3800			真是的，圣诞节之类的真是没件好事。
.panel 0
.transition 0 * 10
.stage	* ev01_005a01_mugai_a.png 0 0
;.stage	* ev01_005a01_mugai.png 0 0


;■黒バック
;■海辺の道
;（海の音を小さくして鳴らすか？）
;（灯台の光，回したいな……）
.transition 1 fadeSide.png 10
.stage	* bgw_normal006a01_03_10001.png 0 0
.panel 1
;（モブの立ち位置と微妙にかぶっているかもしれませんが…）
.message	3810			真的，一点好事都没有。
.message	3820			正以为不可能再相见的时候……。

.screen sc_night01.png sc_night01.png

.transition 0 * 20
.stage	* ev01_009.png 0 0
.message	3830	miy-100_01-0071	@傒傗偙	「咦，跟过来了吗？　不行的哟，就算跟着我也不会养你的啦」
.message	3840		丂峢丂	「……我是得过饵料的小狗么？」
;■		あの子は，事故現場から１００メートルほど離れた路上にぽつんと立っていた。
.message	3850			那个女孩，孤零零地站在距离事故现场数百米外的道路上。
.message	3860		丂峢丂	「再说我也并非跟着你，仅仅是在躲避救护车而已。说明事情经过实在麻烦」
.message	3870	miy-100_01-0073	@傒傗偙	「这样么。真无聊哼」
.message	3880			我还非得让这女孩高兴不可么……？
.panel 0
.HSVfilter 0 0 0 0 0 0
.overlay * *
.screen * *
.transition 0 * 10
.stage	* WHITE.png 0 0


;■背景：砂浜（冬，２１時
;■　　　　广野纮　　：私服（冬·外出）
;■　　　　宮村宫子：私服（冬·外出）
;■ＳＥ：波の音
;.playBGM efBGM025mix.ogg
.playSE AT_umi.ogg true
;☆（『ＡＴ』からの流用です。これも保留。つーか，鳥の鳴き声が微妙に入ってるね。まあ，いいんかな，，，夜だけど）
.transition 1 fadeSide.png 10
.stage	* ev01_010.png 0 0
.panel 1
.message	3890	miy-100_01-0075	@傒傗偙	「啊哈，夜里的大海，真是容易让人静下心来呢」
.message	3900		丂峢丂	「你在那感慨什么啊你」
.message	3910			我和不知身份的少女，站在夜晚的海滨。
.message	3920			如果要问为什么会出现这种情况的话。
.message	3930			那之后，女孩晃晃悠悠步履蹒跚地走开了──
.message	3940			我也莫名地跟在她的身后──于是，现在就在这里了。
.message	3950			我究竟在做什么啊。
.message	3960			分明没有追着这个女孩子的必要。
.message	3970		丂峢丂	「对了，我说你，不是说绝不放弃的吗？」
.message	3980	miy-100_01-0077	@傒傗偙	「跑久了觉得累了啦。啊，已经无所谓了嗯」
.message	3990			大小姐，您刚才的气势哪去了。
.message	4000	miy-100_01-0079	@傒傗偙	「里面也没多少现金，银行卡也不是说动就能动的，手机里也只有自己家跟奶奶家的号码而已……」
.message	4010	miy-100_01-0081	@傒傗偙	「那个提包虽然很贵，但也用蛮久了，差不多该到换掉的时候了，正好正好哼」
.message	4020	miy-100_01-0083	@傒傗偙	「所以，无所谓了嗯」
.message	4030		丂峢丂	「跟刚才说的完全不一样……」
.message	4040			真让人受不了。
.HSVfilter 0 0 0 5 -5 0
.screen sc_night03.png sc_night03.png
.overlay * or_miyako03d.png
.transition 0 * 20
.stage	* bgw_normal007b01_03.png 0 0 st_miyako09d01.png 300
;（立ちｕｐをここから使用。背景については保留。専用のがある？月の光にも注意。画面向かって左から差し込んでいると思うので，好都合に加工してもらう？その場合は背景も加工。とりあえず通常立ち絵でアタッチしてます）
;（通常立ち絵でこのポーズなら，ここは左寄りに？）
.message	4050			她到是好象真的怎样都无所谓了，转过头去看着墨色的夜海，呆呆的站在那里。
.message	4060	miy-100_01-0085	@傒傗偙	「啊，对了」
.message	4070		丂峢丂	「嗯？」
.transition 0 * 40
.stage	* bgw_normal007b01_03.png 0 0 st_miyako00d01.png 350
;.stage	* bgw_normal007b01_03.png 0 0 st_miyako01d01.png 400
.message	4080	miy-100_01-0087	@傒傗偙	「刚才开始我就觉得很在意，你…谁啊？」
.message	4090		丂峢丂	「就算你这么问……」
.message	4100	miy-100_01-0089	@傒傗偙	「名字呢？」
.message	4110		丂峢丂	「…………广野纮」
.message	4120			我也觉得无所谓了就回答了她的问题。
.transition 0 * 40
.stage	* bgw_normal007b01_03.png 0 0 st_miyako06d01.png 410
;☆（06ポーズと05ポーズ，420から410に座標を変更しました。気をつけされたし）
;（ここだけ，宫子立ち絵06と05は座標を400から微妙にずらしてます）
.message	4130	miy-100_01-0091	@傒傗偙	「唔～嗯。稍稍有些奇怪的名字呢」
.transition 0 * 40
.stage	* bgw_normal007b01_03.png 0 0 st_miyako05d05.png 410
;（表情注意）
;■御影チェック
;.message	4140	miy-100_01-0093	@傒傗偙	「あたしはね，宮村宫子」
.message	4140	miy-100_01-0093	傒傗偙	「我叫宮村宫子」
;（名前をヒラくタイミング，注意のこと。ここから？）
.message	4150		丂峢丂	「你不也是奇怪的名字吗」
.message	4155			[注释：广野纮=hirono　hiro　宮村宫子=miyamura　miyako]
.transition 0 * 40
.stage	* bgw_normal007b01_03.png 0 0 st_miyako06d01.png 410
.message	4160	miy-100_01-0095	傒傗偙	「是吗？」
.transition 0 * 40
.stage	* bgw_normal007b01_03.png 0 0 st_miyako06d02.png 410
;（名前をヒラくタイミング，注意のこと）
.message	4170	miy-100_01-0097	傒傗偙	「啊啊，好象是诶」
.message	4180			她──宮村宫子自顾自的认同起来，不断的点着头。。
.message	4190			眼前是静静的摇曳着波浪的海。
.message	4200			身旁是可爱的无以形容的女孩子。
.message	4210			而且是…圣诞节的夜晚。
.message	4220			这虽然是我人生至此以来都未曾发生过的，富有戏剧性的情景，但是心却没有一丝浮动的感觉。
.message	4230			反倒是，肉体和精神都已经到了疲劳的极限。
.transition 0 * 40
;.transition 0 * 20
.stage	* bgw_normal007b01_03.png 0 0 st_miyako05d02.png 410
.message	4240	miy-100_01-0099	傒傗偙	「我呢，有些不明白，广野君为什么会在这里呢？」
.message	4250		丂峢丂	「为什么……那是因为……哦对了！」
.message	4260			我突然想了起来。
.message	4270			由于这家伙的原因而挂掉的我的爱车。
.message	4280		丂峢丂	「你要怎么赔啊，我的自行车！」
.transition 0 * 40
.stage	* bgw_normal007b01_03.png 0 0 st_miyako08d02.png 410
.message	4290	miy-100_01-0101	傒傗偙	「字型车？」
.message	4300			宮村宫子显得很疑惑的样子。
.message	4310			这该死的女人…已经忘了啊。
.message	4320		丂峢丂	「被你骑走，然后在一系列壮举之后被撞坏的我的自行车啊！」
.transition 0 * 40
.stage	* bgw_normal007b01_03.png 0 0 st_miyako08d01.png 410
.message	4330	miy-100_01-0103	傒傗偙	「……哦哦」
.message	4340			宮村啪地敲了一下自己的手掌心。
.message	4350		丂峢丂	「不是“哦哦”的问题吧。那已经是损坏到无法修好的程度了，大概」
.transition 0 * 40
.stage	* bgw_normal007b01_03.png 0 0 st_miyako08d02.png 410
.message	4360	miy-100_01-0105	傒傗偙	「说起来，那辆自行车，怎么办了？」
.message	4370		丂峢丂	「那个么──」
.message	4380			啊。
.message	4390			糟了。
.message	4400			从救护车那逃走的时候忘在那里了……
.message	4410	miy-100_01-0107	傒傗偙	「老实去回收回来比较好哦。那样的东西，放在路中央的话会给别人添麻烦的」
.message	4420		丂峢丂	「啊啊，是啊，是这么回事。但你没什么资格说吧」
.transition 0 * 40
.stage	* bgw_normal007b01_03.png 0 0 st_miyako02d01.png 350
.message	4430	miy-100_01-0109	傒傗偙	「啊哈哈，说的也是呢」
.message	4440			宮村开朗的笑着说道。
.message	4450			对我来说可一点都不好笑啊。
.message	4460			那辆自行车可绝对不是什么便宜货啊。
.message	4470		丂峢丂	「我说啊……」
.screen * *
.transition 0 * 20
.stage	* ev01_011a01.png 0 0
;（ここは覗き込むように……はしてないな。指定とのズレ……だな。とりあえずスルー）
.message	4480	miy-100_01-0111	傒傗偙	「难道说，生气了？」
.message	4490			回过神来，发现宫村正偷偷盯着我的脸。
.message	4500		丂峢丂	「倒也不是生气……」
.transition 0 * 40
.stage	* ev01_011a02.png 0 0
.message	4510	miy-100_01-0113	傒傗偙	「呜～嗯」
.message	4520			宮村宫子她，抱着胳膊好象在想些什么，然后便突然低下了头。
.transition 0 * 40
.stage	* ev01_011b01.png 0 0
.message	4530	miy-100_01-0115	傒傗偙	「对不起」
.transition 0 * 40
.stage	* ev01_011c01.png 0 0
.message	4540			她用和之前完全不同的态度…真挚的眼神望着我。
.message	4550	miy-100_01-0117	傒傗偙	「是很重要的东西吧？真的对不起呢」
.message	4560			算什么嘛，这突然之间的态度转变。
.message	4570		丂峢丂	「……算了啦」
.transition 0 * 40
.stage	* ev01_011c02.png 0 0
.message	4580	miy-100_01-0119	傒傗偙	「能原谅我吗？」
.message	4590			宮村立刻喜形于色高兴的说道。
.message	4600			感情说变就变啊，这家伙。
.message	4610		丂峢丂	「当然还是要你赔的」
.transition 0 * 40
.stage	* ev01_011c03.png 0 0
.message	4620	miy-100_01-0121	傒傗偙	「哎～」
.message	4630			就算你发出不满的声音，这点我也不会让步。
.message	4640		丂峢丂	「那是当然的吧」
.transition 0 * 40
.stage	* ev01_011c04.png 0 0
.message	4650	miy-100_01-0123	傒傗偙	「我觉得啊……对待一个刚被偷掉钱包，身无分文的女孩子这样不太～好吧」
.message	4660		丂峢丂	「那是你自己的事情吧」
.transition 0 * 40
.stage	* ev01_011a01.png 0 0
;（「小首を傾げ」……なので，この表情はもう少し前に使い，首を傾げてるＣＧを？）
.message	4670	miy-100_01-0125	傒傗偙	「呃嗯，我发财之后再还好吗？」
.message	4680			她歪着脑袋，眼睛向上瞟着我看。
.message	4690			哼哼，我可不会被这种程度的装可爱给混过去的。
.message	4700		丂峢丂	「你的将来也配用来当担保的么」
.transition 0 * 40
.stage	* ev01_011c05.png 0 0
.message	4710	miy-100_01-0127	傒傗偙	「好过分……」
.message	4720		丂峢丂	「我也没让你现在赔啊。给我一个联系方法就好」
.message	4730	miy-100_01-0129	傒傗偙	「呜～，知道了啦……」
.message	4740	miy-100_01-0131	傒傗偙	「但是不要打骚扰电话，也不要在网上公布说『这是可爱女孩子的电话哟！』之类的哦」
.message	4750		丂峢丂	「谁会做那种事情啊！」
.message	4760			另外，虽说是事实，也不要自己说自己可爱好吧。
.transition 0 * 40
.stage	* ev01_011c03.png 0 0
.message	4770	miy-100_01-0133	傒傗偙	「世态炎凉，防人之心不可无哟」
.message	4780		丂峢丂	「你这疑心病才可怕吧」
.message	4790			因为宮村她的手机已经被偷掉了，就把她家的电话记录到了手机上。
.message	4800		丂峢丂	「好了嗯……。那么，之后再联络」
.transition 0 * 40
.stage	* ev01_011c05.png 0 0
.message	4810	miy-100_01-0135	傒傗偙	「好～吧……」
.message	4820		丂峢丂	「别发出那么遗憾的声音嘛。那么，我差不多该走了」
.message	4830	miy-100_01-0137	傒傗偙	「我实在累了，还一点都不想动啊～～」
.message	4840			那就是说，想让我再这再多陪她一会吗。
.message	4850		丂峢丂	「我可没有那么多火星闲时间……」
.transition 0 * 40
.stage	* ev01_011b01.png 0 0
.message	4860	miy-100_01-0139	傒傗偙	「好久没有这样活动过身体了。明天估计会肌肉痛嗯」
.message	4870			无视我么，这个死女人。
.message	4880			但是等等？
.message	4890			因为本人过分泰然自若我都忘了，肌肉痛之类的暂且不论……。
.message	4900		丂峢丂	「你没事吧？」
.transition 0 * 40
.stage	* ev01_011a01.png 0 0
;（表情はc03で？）
;（この表情は↓の台詞で）
.message	4910	miy-100_01-0141	傒傗偙	「诶？　什么？」
.message	4920		丂峢丂	「身体状况啊。没有哪里痛，或者呕吐感什么的？」
.transition 0 * 40
.stage	* ev01_011c01.png 0 0
.message	4930	miy-100_01-0143	傒傗偙	「没啊，完全没」
.message	4940			真的假的。
.message	4950			刚在那里可是完全失去了意识啊。
.message	4960		丂峢丂	「可能是仅仅症状自己感觉不到而已」
.transition 0 * 40
.stage	* ev01_011a02.png 0 0
.message	4970	miy-100_01-0145	傒傗偙	「这么一说的话，臀部好象稍稍还有些痛……」
.message	4980		丂峢丂	「屁股怎样都好啦……」
.transition 0 * 40
.stage	* ev01_011c02.png 0 0
.message	4990	miy-100_01-0147	傒傗偙	「不好啦」
.message	5000			宮村她虽然笑着，但真的没问题吗。
.message	5010			我开始认真担心起来。
.message	5020	miy-100_01-0149	傒傗偙	「没事的啦。别摆那么不安的表情出来」
.message	5030		丂峢丂	「分明让人看见晕倒在路边的……」
.message	5040			虽说是刚刚才认识的女孩，但毕竟像这样聊过天，要是让她死了还是会让人睡不好觉的。
.transition 0 * 40
.stage	* ev01_011c01.png 0 0
.message	5050	miy-100_01-0151	傒傗偙	「我没晕倒过啊」
.message	5060		丂峢丂	「分明意识都没了还说！」
.transition 0 * 40
.stage	* ev01_011c04.png 0 0
.message	5070	miy-100_01-0153	傒傗偙	「不是吧～。我完全没印象诶」
.message	5080			宮村她摆出一副意外的表情。
.message	5090		丂峢丂	「这个嘛，都失去意识了还怎么可能有记忆嘛」
.transition 0 * 40
.stage	* ev01_011c03.png 0 0
.message	5100	miy-100_01-0155	傒傗偙	「啊，说的也是」
.message	5110			不得不一点一点细细说明到这种地步吗。
.message	5120			还真是麻烦的女人啊。
.message	5130			再说，我要陪这家伙到几时啊。
.transition 0 * 20
.stage	* ev01_010.png 0 0
.message	5140	miy-100_01-0157	傒傗偙	「广野君」
.message	5150			淡淡的月色下，她轻轻的笑了起来。
.message	5160			海面吹来的凉风扬起着她的秀发，挲啦啦的摇曳着。
;.transition 0 * 20
;.stage	* ev01_012a01.png 0 0
.transition 0 * 20
.stage	* ev01_012a01_mugai_b.png 0 0
;（ここからまだ来てませんが，イベントＣＧあります）
.message	5170			她伸手按住被拂起的长发，缓缓的张开那两片粉色的嘴唇。
.transition 0 * 20
.stage	* ev01_012a01.png 0 0
.message	5180	miy-100_01-0159	傒傗偙	「谢谢你」
.message	5190		丂峢丂	「……什么啊」
.transition 0 * 40
.stage	* ev01_012a02.png 0 0
.message	5200	miy-100_01-0161	傒傗偙	「谢谢你担心我呢，谢谢你」
.message	5210		丂峢丂	「说什么呢你」
.message	5220			我转过脸去。
.message	5230			我不太喜欢别人向自己道谢。
.message	5240	miy-100_01-0163	傒傗偙	「广野君，真是温柔的人呢」
.message	5250		丂峢丂	「吵死了」
.transition 0 * 40
.stage	* ev01_012a03.png 0 0
.message	5260	miy-100_01-0165	傒傗偙	「别害羞嘛，别害羞嘛」
.message	5270			宮村她一边很熟地样子拍着我的肩膀一边说。
.message	5280			可恶，这莫名的失败感是怎么回事啊喂。
.transition 0 * 40
.stage	* ev01_012a01.png 0 0
;.stage	* ev01_012a02.png 0 0
;（ここ，01表情で？）
.message	5290	miy-100_01-0167	傒傗偙	「看在你这份温柔的面子上我就原谅你吧」
.message	5300		丂峢丂	「原谅？」
.transition 0 * 40
.stage	* ev01_012a03.png 0 0
.message	5310	miy-100_01-0169	傒傗偙	「对失去意识的我作了这样那样猥琐的事情吧？」
.message	5320		丂峢丂	「没！作！」
.message	5330			而且别用“猥琐”那样生动的词汇好么。
;.transition 0 * 40
;.stage	* ev01_012a04.png 0 0
.transition 0 * 40
.stage	* ev01_012a02.png 0 0
;（表情，ここ要考察）
.message	5340	miy-100_01-0171	傒傗偙	「因为啊，我睁开眼睛的时候，某人离我很近很近很近哟」
.message	5350		丂峢丂	「那只是……只是确认一下你还有没气而已啦」
.message	5360			虽然稍微说了点假话。
.transition 0 * 40
.stage	* ev01_012a01.png 0 0
.message	5370	miy-100_01-0173	傒傗偙	「没有亲我，或者摸摸女孩子难以启齿的地方之类的吗？」
.message	5380		丂峢丂	「没！有！」
.transition 0 * 40
.stage	* ev01_012a04.png 0 0
.message	5390	miy-100_01-0175	傒傗偙	「……原来你喜欢男人的吗？」
.message	5400		丂峢丂	「那！也！不！对！」
.message	5410			啊啊，真让人不爽啊。
.transition 0 * 40
.stage	* ev01_012a05.png 0 0
.message	5420	miy-100_01-0177	傒傗偙	「我难道就那么，就那么没有魅力吗？」
.message	5430		丂峢丂	「我说啊……」
.message	5440			你就没有那是因为我是绅士的想法吗。
.message	5450		丂峢丂	「我说你，真是个奇怪的女人啊……。怪女人2号」
.message	5460			我恢复情绪后嘟囔道。
.transition 0 * 40
.stage	* ev01_012a04.png 0 0
.message	5470	miy-100_01-0179	傒傗偙	「有1号吗？」
.message	5480		丂峢丂	「算是吧」
.transition 0 * 20
.stage	* ev01_010.png 0 0
;（挿入位置，注意）
.message	5490			教会里遇到的雨宮优子也好，这个宮村宫子也好，今夜好象与奇妙的女孩子特别有缘。
.message	5500			用雨宮优子的话说，今夜似乎是特别的夜晚……。
.message	5510			啊啊啊我不需要什么特别啊，还我一个平静安详的夜晚吧。
.playSE2 hiro_keitai_male.ogg f 0 *
;（文章と全く違う着信音ですが，保留。ちなみに競合していたのでSE2に配置がえ）
.message	5520			叮咚
.message	5530		丂峢丂	「哦」
.message	5540			听到大衣口袋内手机的短信提示音。
.message	5550			估计，又是那家伙吧……。。
.transition 0 * 20
.stage	ev01_013_kiridashi_FG.png ev01_013_kiridashi_base.png 0 0
.effect Cutin ev01_013_kiridashi_yuuna.png -10
.wait 100
;.stage	* ev01_013.png 0 0
.message	5560			我拿出手机，看向液晶画面。
.message	5570		丂峢丂	「…………」
.transition 0 * 40
.stage	ev01_013_kiridashi_FG.png ev01_013b.png 0 0
.effect fadeout
;.effect *
;.transition 0 * 20
;.stage	* ev01_013b.png 0 0
.panel 2
.message	5575			\n\n\n\n\n\n\n\n『逃掉圣诞聚会，跑到哪儿溜达去了，笨蛋！　去死吧！！』
;（↑上記文は向井が追加。名前ラベルはとるか？名前ラベルつけたまま改行はできんかったんだっけ？ここでは使わなくても調べておくこと）
.panel 1
.message	5580			显示出的是从预料之中的那个人，发来的预料之中的内容。
.message	5590	miy-100_01-0181	傒傗偙	「唔嗯，『逃掉圣诞聚会，跑到哪儿溜达去了，笨蛋！　去死吧！』啊。真严厉诶」
.message	5600		丂峢丂	「喂，别看啊」
.transition 0 * 20
.stage	* ev01_014a01.png 0 0
.message	5610			不知什么时候宫村走近过来，偷看着我的手机画面。
.transition 0 * 40
.stage	* ev01_014a02.png 0 0
.message	5620	miy-100_01-0183	傒傗偙	「啊，对不起。一不小心就…」
.message	5630		丂峢丂	「什么叫不小心啊。真是的……」
.screen sc_night03.png sc_night03.png
.transition 0 * 20
.stage	* bgw_normal007b01_03.png 0 0 st_miyako00d04.png 350
;.stage	* bgw_normal007b01_03.png 0 0 st_miyako01d04.png 400
;（こっから立ち絵）
.message	5640			我一边与毫无防备的凑过来的宫村拉开距离，一边合起了手机。
.message	5650	miy-100_01-0185	傒傗偙	「刚才的就是『怪女人1号』吗？」
.message	5660		丂峢丂	「不是。怎么说呢，仅仅是认识的人而已」
.transition 0 * 40
.stage	* bgw_normal007b01_03.png 0 0 st_miyako02d02.png 350
;.stage	* bgw_normal007b01_03.png 0 0 st_miyako01d02.png 400
.message	5670	miy-100_01-0187	傒傗偙	「女朋友？」
.message	5680		丂峢丂	「我说你，听人说话啊喂」
.transition 0 * 40
.stage	* bgw_normal007b01_03.png 0 0 st_miyako02d01.png 350
.message	5690	miy-100_01-0189	傒傗偙	「亲爱的？」
.message	5700		丂峢丂	「不是一样的吗！」
.message	5710			我分明说了仅仅是认识的人吧。
.transition 0 * 40
.stage	* bgw_normal007b01_03.png 0 0 st_miyako07d01.png 410
;.stage	* bgw_normal007b01_03.png 0 0 st_miyako05d02.png 400
.message	5720	miy-100_01-0191	傒傗偙	「但是……」
.message	5730		丂峢丂	「啊嗯？」
.message	5740	miy-100_01-0193	傒傗偙	「广野君，也有这样担心你的人在呢」
.message	5750		丂峢丂	「去死吧，这样的台词我觉得无论怎么解释也没有担心我的意思吧……」
.message	5760			短信的发送者――新藤景虽然估计并不是真的想让我去死，但看来是真的生气了。
.message	5770			真发起火来的景比负伤的野兽还要可怕，暂不见她才是上策。
.transition 0 * 40
.stage	* bgw_normal007b01_03.png 0 0 st_miyako07d02.png 410
;.stage	* bgw_normal007b01_03.png 0 0 st_miyako05d05.png 400
;（05d05の目つむりを？）
.message	5780	miy-100_01-0195	傒傗偙	「广野君，不是这样的哦」
.message	5790		丂峢丂	「不是这样？」
.message	5800	miy-100_01-0197	傒傗偙	「我并不是这个意思。我是说能互相说“去死吧”这样的话的这种直率关系很令人羡慕」
.message	5810		丂峢丂	「你在说什么，我完全不明白」
.transition 0 * 40
.stage	* bgw_normal007b01_03.png 0 0 st_miyako07d03.png 410
;.stage	* bgw_normal007b01_03.png 0 0 st_miyako06d03.png 400
;（表情注意）
.message	5820	miy-100_01-0199	傒傗偙	「不明白也无所谓啊。其实我也不太明白呢」
.message	5830			宮村宫子说着──轻轻的笑了起来。
.message	5840			稍稍的有着寂寞的表情。
.message	5850			为什么她会浮出那样的表情呢──
.message	5860			忽然好象想要知道缘由，又好象不想知道。
.message	5870			但一定…没有知道的必要吧。
.message	5880			所以，我什么都没说。
.transition 0 * 40
.stage	* bgw_normal007b01_03.png 0 0 st_miyako04d02.png 400
;（この表情は下で，ここは別表情で？）
.message	5890	miy-100_01-0201	傒傗偙	「不回短信没问题吗？」
.message	5900		丂峢丂	「这种时候不该愚蠢的去刺激对方，等着对方忘掉这件事才是最好的」
.message	5910	miy-100_01-0203	傒傗偙	「真软弱呢」
;（目つむりを？）
.message	5920			宮村宫子用很有兴趣的眼光看了我一眼，然后“呼～”的大叹了一口气。
.transition 0 * 40
.stage	* bgw_normal007b01_03.png 0 0 st_miyako00d01.png 350
;.stage	* bgw_normal007b01_03.png 0 0 st_miyako01d01.png 400
.message	5930	miy-100_01-0205	傒傗偙	「差不多该走了呢」
.message	5940		丂峢丂	「是么」
.transition 0 * 40
.stage	* bgw_normal007b01_03.png 0 0 st_miyako00d02.png 350
;.stage	* bgw_normal007b01_03.png 0 0 st_miyako01d02.png 400
.message	5950	miy-100_01-0207	傒傗偙	「总之，说下拜拜吧」
.message	5960		丂峢丂	「啊啊，对了。你还是去下医院的好」
.transition 0 * 40
;.stage	* bgw_normal007b01_03.png 0 0 st_miyako01d04.png 350
.stage	* bgw_normal007b01_03.png 0 0 st_miyako01d04.png 400
.message	5970	miy-100_01-0209	傒傗偙	「嗯，我会考虑的」
.transition 0 * 40
.stage	* bgw_normal007b01_03.png 0 0
;（ここでＣＧ切り替える？）
.message	5980			宮村她事不关己般的说完，迈出了步子。
.message	5990			我也正想着跟在她的后面开始走的时候──
.message	6000			她突然站下不动了。
.playSE *
;（効果音を止めるのをここまで引っ張ってますが，もちろん仮です。音楽の有無によっては，もっと前で止める可能性もあります）
.message	6010	miy-100_01-0211	傒傗偙	「啊……」
.message	6020		丂峢丂	「？」
.message	6030	miy-100_01-0213	傒傗偙	「雪诶！雪！──」
.message	6040		丂峢丂	「哎？」
;.effect Snow
;.effect SnowH
.screen * *
;.playBGM efBGM028mix.ogg 0 *
.transition 0 * 20
.stage	* bgw_sky001a01_03.png 0 0
;（とりあえず，夜空はさんでますが，保留。雪を降らせる場合は，一点から降らせるように）
.message	6050			我抬头望向天空。
;★イベントＣＧ　雪降る浜辺で踊ってる宫子
.message	6060			那阴云密布的夜空，不知何时开始有一片片雪如花飘落。
;.effect *
.transition 0 * 20
.stage	* ev01_015b01_mugai_a_snowoff.png 0 0
;.transition 0 * 10
;.transition 0 * 5
.transition 1 fadeVertical.png 5
.stage	* ev01_015b01_mugai_a.png 0 0
;（10だと微妙なので20に戻す。もっと遅くしてもいいのかも）
.message	6070	miy-100_01-0215	傒傗偙	「哇～～，好漂亮呢」
.message	6080			宮村宫子一边快乐的笑着，一边看着那如舞动般飘下的雪花。
.panel 0
;.transition 0 * 10
;.stage	* ev01_015b01_mugai_a.png 0 0
.transition 0 * 20
.stage	* ev01_015a02_mugai_c.png 0 406
;.vscroll	0	-8
.vscroll	0	-10
.endScroll f
.panel 1
.message	6090	miy-100_01-0217	傒傗偙	「啊哈哈哈哈」
.transition 0 * 20
.stage	* ev01_015a02_snow.png 0 0
.message	6100			看起来真的很高兴的样子。
.message	6110			不断发出天真烂漫的笑声。
.transition 0 * 20
.stage	* ev01_015a02_mugai_d.png 0 0
.message	6120			转着圈子，好象跳舞一般跟落下的雪花玩耍着。
.transition 0 * 20
.stage	* ev01_015c02.png 0 0
.message	6130	miy-100_01-0219	傒傗偙	「白色…圣诞节呢……」
.message	6140		丂峢丂	「无所谓的东西啦」
.message	6150			嗯，无所谓的东西。
.message	6160			雪不过是单纯的自然现象罢了。
.message	6170			为什么这家伙会这么高兴的跳起来。
.message	6180			我个人完全是什么都──什么都感觉不到。
.transition 0 * 20
.stage	* ev01_015b01_mugai_e2.png 0 0
;（カメラを雪降る空に向かせるか？）
.message	6190	miy-100_01-0221	傒傗偙	「不觉得很美妙吗？　这样的」
.message	6200			她背向着我，张口问道。
;（顔を横に向かせるタイミングにも注意のこと）
.transition 0 * 20
.stage	* ev01_015b01_snow.png 0 0
.message	6210		丂峢丂	「不觉得」
.transition 0 * 20
.stage	* ev01_015b02_snow.png 0 0
.message	6220	miy-100_01-0223	傒傗偙	「如果能和一个互通心意的人一起看雪就好了啊……」
.message	6230		丂峢丂	「真抱歉，让你扫兴了」
.message	6240	miy-100_01-0225	傒傗偙	「嘛，只是有个人陪着也挺好了啦。一个人的白色圣诞节只会感觉到寂寞而已呢」
.message	6250			这家伙，是在安慰自己吧。
.message	6260			虽然这么想，但并没有说出来。
.message	6270			宮村要一个沉浸在浪漫的气氛里是她的事，我也没必要特意去给她泼盆冷水。
.transition 0 * 40
.stage	* ev01_015b01_snow.png 0 0
.message	6280	miy-100_01-0227	傒傗偙	「说起来，广野君」
.message	6290		丂峢丂	「怎么了」
.message	6300	miy-100_01-0229	傒傗偙	「仔细想来，我家的钥匙也放到那个提包里去了」
.message	6310		丂峢丂	「……所以？」
.message	6320			啊，不好的予感。
.message	6330	miy-100_01-0231	傒傗偙	「我的家呢，现在没有人在。所以呢，至少今天晚上不得不在外面过夜了呢」
.message	6340		丂峢丂	「看来是这么回事」
.message	6350	miy-100_01-0233	傒傗偙	「你想啊，让一个女孩子独守至黎明的话不会有各种各样的危险吗」
.message	6360		丂峢丂	「你不会想说让我陪着吧？」
.panel 0
;.transition 0 * 20
;.stage	* ev01_015b02.png 0 0
.transition 0 * 20
.stage	* ev01_015b01.png 0 0
.transition 0 * 10
.stage	* ev01_015a02.png 0 0
.transition 0 * 10
.stage	* ev01_015c01_snow.png 0 0
.transition 0 * 10
.stage	* ev01_015c02.png 0 0
.panel 1
.message	6370	miy-100_01-0235	傒傗偙	「没听过帮人帮到底，送佛送到西么。来，走吧」
.message	6380			宮村宫子她转过头来，对我微微一笑。
.panel 0
.transition 0 * 10
.stage	* WHITE.png 0 0
.transition 0 * 10
.stage	* ev01_tero_last_a.png 0 0
.message	6381			\a　
.wait 350
.transition 0 * 10
.stage	* WHITE.png 0 0
.wait 100
.transition 0 * 10
.stage	* ev01_tero_last_b.png 0 0
.message	6382			\a　
.wait 350
.transition 0 * 10
.stage	* WHITE.png 0 0
.wait 100
.transition 0 * 10
.stage	* ev01_tero_last_c.png 0 0
.message	6383			\a　
.wait 400
;.playBGM *
.transition 0 * 10
.stage	* WHITE.png 0 0
.HSVfilter 0 0 0 0 0 0
.overlay * *
.wait 100
.stage	* BLACK.png 0 0

;.message	6390		丂峢丂	「…………」
;.message	6400			看起来今年的圣诞节还完全没有想要结束的样子呢。
;.message	6410			得到这确实的预感同时，我踏出了脚下的一步──

;体験版の場合，ここでムービーを再生して終了。
;for trial ver.

;.if trial_comp == 1 retry
;.movie 10000 test01.mpg 800 600 f
;.setGlobal trial_comp = 1
;.end
;.label retry
;.movie 10000 test01.mpg 800 600 t
;.end

;TG版の場合，発売日表記をして終了。
;for trial ver.

;.transition 0 * 10
;.stage	* trial_staff.png 0 0
;.wait 300
;.transition 0 * 10
;.stage	* trial_ohp.png 0 0
;.wait 300
;.transition 0 * 10
;.stage	* trial_date.png 0 0
;.wait 300
;.playBGM *
;.stage	* BLACK.png 0 0

.playBGM *
.chain 101_01.sc
;■101_01へ。

.end
