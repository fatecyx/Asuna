; ファイル: 000_01.txt

;■御影チェック
;■　キー入力を無効（有効）にするスクリプト。
;■　危ないので必ずセットで使うこと！
;■----------------------------------------------
;.pragma disable_control
;.pragma enable_control
;■----------------------------------------------


;;■御影チェック
;;■　２週用の分岐スクリプト素体
;;■----------------------------------------------
.if ef_000 == 1 ef_000_b1
.if ef_000 <= 0 ef_000_a1
;
.label ef_000_a1

;■御影チェック
;■　キー入力無効
.pragma disable_control

.goto ef_000_b1
.end
;
.label ef_000_b1
;;■----------------------------------------------




.setGlobal EYE_SEQ_DEFAULT = 2


.wait 200
.effect Snow
.wait 100




;.transition 0 * 50
;.stage	* BLACK.png 0 0
.wait 80
;■序章
;街の全景（夜）からスタートかな。
;.transition 0 * 10
;.transition 0 * 15
;.stage	* BLACK.png 0 0
.wait 200
;.stage	* ef_tero_a_1.png 0 0
.panel 3
.message	100	yuk-000_01-0003	#桪丂巕	无论是谁都会有向神祈祷的时候。\v\a
.transition 0 * 10
.stage	* BLACK.png 0 0
.message	110	yuk-000_01-0005	#桪丂巕	\a就算毫无信仰，但也必然会有全心全意去祈祷的那一刻。\a\v
;.wait 50
;.transition 0 * 10
.transition 0 * 15
.stage	* BLACK.png 0 0
.message	120	yuk-000_01-0007	#桪丂巕	\a谁都会去寻觅之物。\v\a
;.transition 0 * 10
.transition 0 * 20
.stage	* BLACK.png 0 0
.message	130	yuk-000_01-0009	#桪丂巕	\a谁都会去祈望之物。\v\a
;.wait 50
;.transition 0 * 10
.transition 0 * 15
.stage	* BLACK.png 0 0
.message	140	yuk-000_01-0011	#桪丂巕	\a伸出双手，想要获得之物。\v\a
;.wait 50

;意味合い的に2つに分けるのはまずいので削除 5bも同様 nbkz 2006/04/12
;.transition 0 * 10
;.stage	* ef_tero_a_5c.png 0 0
;.wait 450

;.transition 0 * 10
.transition 0 * 15
.stage	* BLACK.png 0 0
.message	150	yuk-000_01-0013	#桪丂巕	\a无尽的思念中，由人与人的羁绊生出之物。\v\a
;.wait 250
.transition 0 * 10
.stage	* BLACK.png 0 0
;.wait 200
;.transition 0 * 10
.transition 0 * 30
.stage	* BLACK.png 0 0
.message	160	yuk-000_01-0015	#桪丂巕	\a那…一定是──\v\a
.wait 300
.effect fadeout
;.wait 150

;■御影チェック
;.wait 100
.wait 20


;.effect SnowH
.transition 0 * 10
;.stage	* WHITE.png 0 0

.stage	* BLACK.png 0 0




;とりあえず画像化したのではずしてあります。 nbkz 2006/04/12
.panel 3
;.stage	* ef_tero_a_1.png 0 0
;.message	100		#桪丂巕	誰もが一度は神様に祈ったことがあると思う。
;.stage	* ef_tero_a_2.png 0 0
;.message	110		#桪丂巕	たとえ何も信じていなくても，まっすぐな心で祈りを捧げる日がいつか必ずやってくる。
;.stage	* ef_tero_a_3b.png 0 0
;.message	120		#桪丂巕	誰もが探しているもの。
;.stage	* ef_tero_a_3c.png 0 0
;.message	130		#桪丂巕	誰もが求めているもの。
;.stage	* ef_tero_a_4.png 0 0
;.message	140		#桪丂巕	手を伸ばし，つかみ取ろうとするそれは。
;.stage	* ef_tero_a_5.png 0 0
;.message	150		#桪丂巕	めぐる想いと，人々の絆が作り出すその先にあるそれは。
;.stage	* ef_tero_a_6.png 0 0
;.message	160		#桪丂巕	それはきっと──




;■教会内（祭壇）（冬，１９時
;■　　　　火村夕　：私服（冬
;■　　　　雨宮优子：私服（冬
.panel 0
.transition 0 * 20
.stage	* BLACK.png 0 0
;（効果音を鳴らす間の確保のため，わざと黒はさんでます。フェードスピードは40がいい？）
.playSE kyoukai_door.ogg f 0 *
.transition 0 * 20
.stage	vista_window2.png ev00_001a01_mugai_a.png 0 0
.effect *
.panel 3
;.panel 1
.message	170			\a随着轧轧声，缓缓推开那道厚重的门。
.wait 250
.playSE2 yuka.ogg f 0 *
.message	180			\a踏入的瞬间，一瞬间感到冰冻般的寒冷。
.wait 300
.panel 0
.transition 0 * 20
.stage	vista_window2.png ev00_001a01_mugai_a.png 0 0
;.stage	* ev00_001a01_mugai_a.png 0 0
.vscroll	1200	10
.endScroll f
.playSE2 *
.panel 3
.message	190			\a呼出白色的气息，望向正面的祭坛。
.wait 270
.message	200			\a应该是熟悉得不能再熟悉的场所。
.wait 260
.message	210			\a然而，目前却是不可能出现的光景。
.wait 270
.message	220			\a我到底是什么时候……。
.wait 250
.message	230			\a软弱到会做这样的梦了。
.wait 320
;nbkz追加
.stage * BLACK.png 0 0
.panel 0
.wait 50
.stage	* planner.png 0 0
.message	231			\a　
.wait 200
.stage	vista_window2.png ev00_001b01.png 0 600
.transition 0 * 5
.panel 3
.message	240	yuk-000_01-0017	#桪丂巕	\a「啊啦」\a\v
.wait 100
.panel 3
.message	250			\a祭坛前的少女轻轻转过身来。
.wait 280
.panel 3
.message	260	yuk-000_01-0019	#桪丂巕	\a「晚上好」\a\v
.wait 100
.transition 0 * 20
.stage	vista_window2.png prologue_mugai_h3.png 0 0
;.stage	vista_window2.png prologue_mugai_j.png 0 0
.panel 3
.message	270			\a那少女浮起清澈的笑容，微微低了一下头。
.wait 300
.transition 0 * 20
.stage	vista_window2.png prologue_mugai_h.png 0 0
;.stage	vista_window2.png prologue_mugai_e.png 0 0
;.transition 0 * 20
;.stage	vista_window2.png prologue_mugai_f.png 0 0
.message	280			\a那头长发也随着漾出美丽的波纹。
.wait 280
.panel 0
.transition 0 * 20
.stage	vista_window2.png prologue_mugai_e.png 0 0
;.stage	vista_window2.png prologue_mugai_f.png 0 0
.panel 3
.message	290	him-000_01-0003	#丂梉丂	\a「…………」\a\v
.wait 100
.panel 3
.message	300			\a胸口有被勒紧般的疼痛。
.wait 280
.message	310			\a曾经，这对耳朵所听过无数遍的她的声音──
.wait 290
.message	320			\a每一言每一语都是如此柔和而悦耳动听。
.wait 260
.message	330	him-000_01-0005	#丂梉丂	\a「……哟」\a\v
.wait 100
.panel 3
.message	340			\a用尽全力力气才挤出一句话。
.wait 260
.message	350			\a不敢相信正在和她对话这个现实。
.wait 290
.panel 0
.transition 0 * 20
.stage	vista_window2.png ev00_002a01_mugai_a_vista.png 0 0
.panel 3
.message	360	yuk-000_01-0021	#桪丂巕	\a「啊，不对哦。今天应该是──」\a\v
;.wait 200
.panel 0
;nbkz追加 2006/04/07
.stage * BLACK.png 0 0
.transition 0 * 20
.wait 50
.stage	* os_sp.png 0 0
.message	361			\a　
.wait 200
.transition 0 * 20
.stage	vista_window2.png ev00_002a03_mugai_c.png 0 0
.panel 3
.message	370	yuk-000_01-0023	#桪丂巕	\a「圣诞快乐…才对呢」\a\v
.wait 100
.panel 3
.message	380			\a她站在那里──洋溢着和那时候一样的笑容。
.wait 270
.transition 0 * 20
.stage	vista_window2.png ev00_002a03_mugai_b.png 0 0
;（ここだけ繋がり悪い気がするので，切り出しでフェードさせてます）
.message	390			\a恍若梦境，难过万分。
.wait 270
.message	400	him-000_01-0007	#丂梉丂	\a「……圣诞快乐」\a\v
.wait 100
;.wait 200
.panel 3
.message	410			\a根本不是慢吞吞打招呼的时候。
.wait 240
.message	420			\a分明有更重要的话，不得不说的话。
.wait 240
.panel 0
.transition 0 * 20
.stage	vista_window2.png ev00_002a01.png 0 250
.panel 3
.message	430	yuk-000_01-0025	#桪丂巕	\a「分明是圣诞节……却是一个人吗？」\v
.wait 100
;.wait 300
.message	440	him-000_01-0009	#丂梉丂	\a「啊啊，一个人过圣诞节已经很多年了……」\v
;.wait 300
.transition 0 * 20
.stage	vista_window2.png ev00_002a03.png 0 250
.message	450	yuk-000_01-0027	#桪丂巕	\a「哎呀，还真是寂寞的人呢」\a\v
;.wait 200
.message	460	yuk-000_01-0029	#桪丂巕	\a「不过说起来我也总是一个人呢」\a\v
.wait 100
.message	470	him-000_01-0011	#丂梉丂	\a「那么……」\a\v
.wait 100
.message	480	him-000_01-0013	#丂梉丂	\a「如果可以的话，可以稍微聊聊吗？」\a\v
;.wait 50
;.wait 100
.wait 80
.message	490	yuk-000_01-0031	#桪丂巕	\a「嗯，十分乐意」\a\v
.wait 100
;nbkz追加 2006/04/07
.stage * BLACK.png 0 0
.transition 0 * 20
.panel 0
.wait 50
.stage	* cd.png 0 0
.message	491			\a　
.wait 200
.transition 0 * 20
.stage	vista_window2.png ev00_002a02.png 0 250
.panel 3
.message	500	yuk-000_01-0033	#桪丂巕	\a「十分乐意……」\a\v
.wait 100
.panel 3
.message	510			\a那少女的笑容，不意之间亲切起来。
.wait 260
.message	520	yuk-000_01-0035	#桪丂巕	\a「好久不见了呢……」\a\v
.wait 100
.message	530	him-000_01-0015	#丂梉丂	\a「……一直都」\a\v
;.wait 100
.wait 85
.message	540	him-000_01-0017	#丂梉丂	\a「让你等了很久了啊」\a\v
.wait 100
.panel 3
.message	550			\a就算是梦也无所谓。
.wait 200
.message	560	yuk-000_01-0037	#桪丂巕	\a「嗯，是这样没错」\a\v
;.wait 200
.transition 0 * 20
.stage	vista_window2.png ev00_002a01.png 0 250
.message	570	yuk-000_01-0039	#桪丂巕	\a「稍微……」\a\v
.wait 100
;.transition 0 * 20
;.stage	vista_window2.png ev00_002a02.png 0 250
;☆（mugaiバーのみの新規）
.message	580	yuk-000_01-0041	#桪丂巕	\a「稍微等的有些久了呢」\a\v
;.wait 200
.wait 60
.message	590	him-000_01-0019	#丂梉丂	\a「是吗」\a\v
;.wait 200
.panel 3
.message	600			\a只要现在她站在我的面前──
.wait 220
.message	610	him-000_01-0021	#丂梉丂	\a「真是抱歉呢，优子」\a\v
;.wait 200
.transition 0 * 20
.stage	vista_window2.png prologue_mugai_g.png 0 0
.panel 3
.message	620			\a我实在是让她等的太久了。
.wait 260
.message	630	him-000_01-0023	#丂梉丂	\a「优子，真的是……」\a\v
;.wait 200
.transition 0 * 20
.stage	vista_window2.png ev00_002a01_mugai02.png 0 0
;.stage	vista_window2.png ev00_002a01_mugai_b.png 0 0
;☆（mugaiバーのみの新規）
.message	640	yuk-000_01-0043	#桪丂巕	\a「您是……」\a\v
.wait 100
;nbkz追加 2006/04/07
.stage * BLACK.png 0 0
.transition 0 * 20
.panel 0
.wait 50
.stage	* color.png 0 0
.message	641			\a　
.wait 200
.transition 0 * 20
.stage	vista_window2.png ev00_002a01_mugai01_close.png 0 0
;☆（実際は目閉じバーを！）
;.transition 0 * 20
;.stage	vista_window2.png ev00_002a01_close.png 0 250
;.panel 3

;■御影チェック
;■　流れが悪いな……コメントアウト。
;■------------------------------------------------------------
;.message	650	him-000_01-0025	#丂梉丂	「え？」\v\a
;.wait 100
;.panel 3
;.message	660			少女はなにか考え込むような仕草をする。\a
;.wait 220
;.panel 0
;■------------------------------------------------------------


.panel 3
.message	670	yuk-000_01-0045	#桪丂巕	「火村……」\v\a
;.wait 200
.transition 0 * 20
.stage	vista_window2.png ev00_002a01_mugai01.png 0 0
;.stage	vista_window2.png ev00_002a01.png 0 250
.message	680	yuk-000_01-0047	#桪丂巕	「火村，夕君……没错吧」\v\a
;.wait 200
.panel 3
.message	690			目光像是在等待着这边的回答。\a
.wait 230
.message	700			难道说……。\a
.wait 190
.message	710	him-000_01-0027	#丂梉丂	「忘掉…关于我的事情了吗？」\v\a
;.wait 200
.transition 0 * 20
.stage	vista_window2.png ev00_002a03_mugai01.png 0 0
;.stage	vista_window2.png ev00_002a03.png 0 250
.message	720	yuk-000_01-0049	#桪丂巕	「嗯，其实呢」\v\a
;.wait 200
.panel 3
.message	730			她轻轻地笑了起来。\a
.wait 200
.message	740			是真的忘记了吗？还是…仅仅的一时恍惚呢。\a
.wait 270
.panel 0
.transition 0 * 20
.stage	vista_window2.png ev00_002a02_mugai01.png 0 0
;.stage	vista_window2.png ev00_002a02.png 0 250
.panel 3
.message	750	yuk-000_01-0051	#桪丂巕	「就在刚才。就在刚才，想起来了」\v\a
.wait 100
;.wait 150
;.wait 300
.message	760	yuk-000_01-0053	#桪丂巕	「这样子…总感觉和那时正好相反呢」\v\a
;.wait 300
.transition 0 * 20
.stage	vista_window2.png prologue_mugai_c.png 0 0
.panel 3
.message	770			不意间，记忆如潮，逆流而上。\a
.wait 200
.transition 0 * 20
.stage	vista_window2.png prologue_mugai_d.png 0 0
.message	780			那是多少季节轮回之前──某一天夕阳下的回忆。\a
.wait 250
;nbkz追加 2006/04/07
.stage * BLACK.png 0 0
.transition 0 * 20
.panel 0
.wait 50
.stage	* music.png 0 0
.message	781			\a　
.wait 200
.transition 0 * 20
.stage	vista_window2.png ev00_003_vista.png 0 0
.panel 3
.message	790	him-000_01-0029	#丂梉丂	「啊啊，没错……」\v\a
;.wait 200
.wait 70
.message	800	him-000_01-0031	#丂梉丂	「我们再会了，在那个夏日」\v\a
;.wait 300
;.transition 0 * 20
;.stage	vista_window2.png prologue_mugai_i2.png 0 0
.panel 3
.message	810			对，在那个夏天。\a
.wait 220
.transition 0 * 20
.stage	vista_window2.png prologue_mugai_j.png 0 0
.message	820			那个忘记优子的夏天。\a
.wait 230
.message	830			那个对她还一无所知的夏天。\a
.wait 250
.transition 0 * 20
.stage	vista_window2.png prologue_mugai_i2.png 0 0
.message	840			那个再也不会回来的，我和她的夏天……。\a
.wait 280
.panel 0
.transition 0 * 10
.stage	* WHITE.png 0 0








.wait 30
;■回想スタート
;■500_01より
;■背景：学園·廊下（夏，１８時
;■　　　　火村夕　：制服（夏）
;■　　　　雨宮优子：制服（冬）
;.playBGM BGM016_sample.ogg
.transition 0 * 10
.stage	* bgc_sch002a01_02_pastm3.png 0 0
.panel 1


;■御影チェック
;■　キー入力有効に
.pragma enable_control


.message	850			结束在图书馆的学习，来到走廊。
.transition 0 * 20
.stage	* bgc_sch002a01_02_pastm2.png 0 0
.message	860			四周静寂无声，连个人影都看不到。
.transition 0 * 20
.stage	* bgc_sch002a01_02_pastm.png 0 0
.message	870			平时应该还有部团活动和委员会工作的学生在的，为什么今天如此安静呢。
.message	880			连自己的足音，都大到让人吃惊。
;.message	890			夏の日差しを吸い込んだ廊下は夕暮れになっても，暑気が引かない。
.message	890			吸满夏日阳光的走廊，在傍晚仍然感受不到凉意。
.message	900			仅仅是走着而已，就已经汗流浃背。
;■空（夕暮れ）
;.playSE higurashi.ogg f 0 *
.transition 0 * 20
;.stage	* sky_pastm_a.png 0 0
.stage	past_window.png bgs_sch009a01_02.png 0 0
;（夏の校舎に差し替えのこと）
.message	910			换好靴子，走出教学楼。
.message	920			风也带有蒸笼般的暑气，闷热的空气包满全身。
.message	930			再次让我发觉，现在是夏天这个事实。
.message	940			我并不讨厌夏天。
.message	950			比起阴郁的冬天，很难找到讨厌这个充满音色和光芒的季节的理由。
.message	960			并不讨厌，吗。
.message	970			我发现总是如此。
.message	980			世界只会被我分为不算很讨厌和讨厌两种而已。
.message	990			真称不上是健全的生存方式…啊，我独自苦笑起来。
.message	1000			生存方式…吗。
;.playSE *
.transition 0 * 20
.stage	past_window.png ev00_004_mugai_h2.png 781 1037
;.stage	past_window.png ev00_004_mugai_h4.png 1121 1457
.message	1010			仰望天空。
.message	1020			我所希望的生存方式是──
.message	1030		丂梉丂	「那是什么……？」
.transition 0 * 20
;.stage	past_window.png ev00_004_mugai_h4.png 1121 1457
;.scroll	781 1037	6
.stage	past_window.png ev00_004_mugai_h2.png 781 1037
.scroll	581 837	6
.endScroll f
.message	1040			在那夕阳染红的天空，一片细小的白色轻轻舞动。
.transition 0 * 20
.stage	* ev00_004.png 0 0
.message	1050			那是……一架纸飞机。
.message	1060		丂梉丂	「哪里的笨蛋扔出来的」
;.transition 0 * 20
.transition 0 * 10
.stage	* ev00_005.png 0 0
.message	1070			捡起那飘落在地的纸飞机。
;■余裕があれば，紙飛行機を持った夕の手元のＣＧ。
.message	1080			都几岁了，在这学校里还会有哪个笨蛋在玩这样的东西。
.transition 0 * 20
.stage	* ev00_006_mugai_d.png 0 600
.message	1090			我带着些许的惊讶，开始一个个的确认教学楼的窗户。
.transition 0 * 20
.stage	* ev00_006_mugai_d.png 0 600
.vscroll	0	-10
.endScroll f
.message	1100			在我以为犯人可能已经不在的时候……。
.message	1110		丂梉丂	「啊……」
;★ここから屋上を下から見上げた遠景。
.transition 0 * 20
.stage	* ev00_006_mugai_a.png 0 0
.message	1120			一名少女的身影，滑入了我的视线。
.message	1130			而且不知为何，那女孩坐在屋顶的边缘，惬意地摇晃着自己的双足。
.transition 0 * 20
.stage	* ev00_006.png 0 0
.message	1140			在那种地方干什么呢。
.message	1150			不，比起这个──
.message	1160			就在我疑问接连涌出的时候，突然。
.message	1170			虽然很远，我却清楚地看到了。
.message	1180			那女孩停止了脚的晃动，而望向下方的我──微笑起来。


;■屋上（夏，１８時
;■　　　　火村夕　：制服（夏）
;■　　　　雨宮优子：制服（夏）
.transition 0 * 10
.stage	* bgs_sky001a01_02_mugai_a.png 0 0
.message	1190			打开那扇门，天空近的仿佛触手可及。
.message	1200			鲜艳的绯红色，红到会让人有那轮夕日马上便会落下将这地面燃尽的错觉。
.message	1210			在那弄痛眼睛的绯色之中──
.transition 0 * 10
.stage	* ev00_007a01_mugai_a.png 0 0
.message	1220			少女在微笑着。
.transition 0 * 20
.stage	* ev00_007a02.png 0 0
.message	1230		丂梉丂	「……为什么是冬服？」
.message	1240			虽然和想好的台词不同，总之就这样问过去。
.message	1250			或者说，无法说出什么适合的话语。
.message	1260			眼前的光景是如此绮丽，让人失去现实感。
.message	1270			而且虽然是第一次来到屋顶，但理然该在的栅栏却没有也让我稍有吃惊。
.transition 0 * 40
.stage	* ev00_007a03.png 0 0
.message	1280	yuk-000_01-0055	@桪丂巕	「冬服？」
.message	1290			在那强烈的不协调感所渲染出的景色中，那名少女歪了一下头。
.message	1300		丂梉丂	「你穿的不是冬服吗」
.message	1310		丂梉丂	「还是不知道什么叫做换衣服呢？」
.transition 0 * 40
.stage	* ev00_007a01.png 0 0
;（下の02と逆にする？04の使いどころもしっかり考えておくこと）
.message	1320	yuk-000_01-0057	@桪丂巕	「啊啊，这件衣服吗。这是夏服哦」
.message	1330		丂梉丂	「哈？」
.message	1340			她的衣服再怎么看都是音羽学园的冬服。
.message	1350			包裹的严严实实，更让人觉得奇怪的是连手套都带着。
.transition 0 * 40
.stage	* ev00_007a02.png 0 0
.message	1360	yuk-000_01-0059	@桪丂巕	「冬天穿的衣服才叫衣服。这是夏天穿的所以是夏服。不对吗？？」
.message	1370		丂梉丂	「完全不对的吧……」
.message	1380			看来是不能用常理说服了。
.transition 0 * 40
.stage	* ev00_007a01.png 0 0
.message	1390	yuk-000_01-0061	@桪丂巕	「请别介意啦。虽然偶尔会被人说，看着就觉得热的难受……」
.message	1400			被那样说也是理所当然的吧。
.message	1410			在夏天最热的时间里穿这样的衣服，自然会让人觉得不适。
.transition 0 * 40
.stage	* ev00_007a02.png 0 0
.message	1420	yuk-000_01-0063	@桪丂巕	「不太想穿半袖」
.message	1430	yuk-000_01-0065	@桪丂巕	「以前…稍微发生过些事呢」
.message	1440			她一边说着，隔着衣服轻轻抚摩自己的手腕。
.message	1450	yuk-000_01-0067	@桪丂巕	「当时是觉得无所谓，不过现在到了微妙的年纪啊……」
.message	1460		丂梉丂	「我倒也没有追问发生过什么的意思」
.message	1470			我明白那女孩的意思，而打断了她的话。
.message	1480			大概是，小孩子的时候受过伤而留下的创口吧。
.message	1490			在这个年纪的女孩，肌肤的伤口不想被看到也无可厚非。
.message	1500			这种程度的事情我还是懂的，不过认真看起来的话……
.message	1510			这女孩穿着冬服，有种不可思议的适合感。
.message	1520			当然，那样的话我可不会说出口。
;■御影チェック
;■　表情変化挿入。
.transition 0 * 40
.stage	* ev00_007a01.png 0 0
.message	1530	yuk-000_01-0069	@桪丂巕	「说起来，您不是专门为了说长袖看起来闷热而来的吧？」
.message	1540		丂梉丂	「怎么可能」
.message	1550			我摇了摇头，想起了本来的目的。
.transition 0 * 20
.stage	* ev00_008a01.png 0 0
.message	1560		丂梉丂	「我说你，屋顶是禁止进入的啊」
.message	1570			正常应该是被锁住的才对，如何把锁打开的也是一个迷。
.transition 0 * 40
.stage	* ev00_008a02.png 0 0
.message	1580	yuk-000_01-0071	@桪丂巕	「你不是也进来了吗」
.message	1590			少女露出稍稍执拗的神情。
.message	1600		丂梉丂	「我是来提醒你的。可别扯开话题哦」
.transition 0 * 40
.stage	* ev00_008a03.png 0 0
.message	1610	yuk-000_01-0073	@桪丂巕	「被人看到还是第一次呢。可惜，可惜」
.message	1620			不过完全没有想要说明为什么可惜的意思。
.message	1630		丂梉丂	「还好我不是教师。你是怎么进来的？」
;.message	1640			音羽学園の屋上は立ち入り禁止──というより，入学してその事実を聞いた後はもう屋上の存在すら忘れてしまうのが普通だろう。
.message	1640			音羽学园的屋顶禁止随意出入──虽然这么说，都是入学之后才听说这件事，忘记屋顶的存在很正常吧。
.message	1650			就这点来说，这地方学生们应该不熟悉才对。
.transition 0 * 40
.stage	* ev00_008a01.png 0 0
.message	1660	yuk-000_01-0075	@桪丂巕	「啊啊，这件事情吗」
.message	1670	yuk-000_01-0077	@桪丂巕	「我是天文部员哦。拥有特别可以进入屋顶的许可」
.message	1680		丂梉丂	「要撒谎的话，也找些更象样的出来」
.message	1690		丂梉丂	「在这种时间怎么能看见什么星星。再说，我们学校有天文部吗？」
.message	1700			看过去的话，也没看到拿有望远镜之类的器具。
.transition 0 * 40
.stage	* ev00_008a03.png 0 0
.message	1710	yuk-000_01-0079	@桪丂巕	「当然有啊。只是，昨天起废部了而已」
.message	1720		丂梉丂	「废部？」
.transition 0 * 40
.stage	* ev00_008a04.png 0 0
.message	1730	yuk-000_01-0081	@桪丂巕	「嗯，3年级的前辈提早一步引退了。没有2年级的部员，剩下的只有1年级的我而已」
.message	1740		丂梉丂	「只有1年级…吗」
.message	1750			虽然明白，这个少女应该是我的后辈。
.message	1760			但直观的看起来，倒好似比我小3到4岁。
.transition 0 * 40
.stage	* ev00_008a03.png 0 0
.message	1770	yuk-000_01-0083	@桪丂巕	「虽然我还妄想会不会有人正好这时入部呢～～可惜这个世界没那么一帆风顺啊」
.message	1780		丂梉丂	「只有一个人的话确实没法做什么。虽然遗憾但这也是没办法的事」
.message	1790			我这样说着毫无感情的话。
;.message	1800			最近は，退屈でくだらない話にもごく普通に相づちくらいを打てるようになった──それの是非はともかく。
.message	1800			最近，就算是极其无聊的话，也能普通的作出回应──这是好是坏暂且不论。
.transition 0 * 40
.stage	* ev00_008a01.png 0 0
.message	1810	yuk-000_01-0085	@桪丂巕	「是啊，没办法的事情呢」
.transition 0 * 40
.stage	* ev00_008a04.png 0 0
.message	1820	yuk-000_01-0087	@桪丂巕	「但是呢……」
.transition 0 * 20
.stage	* ev00_008a_mugai_a.png 0 0
.message	1830		丂梉丂	「怎么？」
.message	1840	yuk-000_01-0089	@桪丂巕	「跟我有关的人或事，都会迎来很坏的结局呢……」
.message	1850		丂梉丂	「那是什么意思」
.message	1860	yuk-000_01-0091	@桪丂巕	「呼唤厄运的存在之类吧，而且会把周围都卷进来」
.message	1870	yuk-000_01-0093	@桪丂巕	「虽然我并不怎么有自觉呢」
.message	1880			又说些可怕的事情。

;■御影チェック
;.message	1890			というか，初対面で通りすがりな人間に告白することではないと思う。
.message	1890			倒是，对于初次见面的人不会这么坦白吧。

.message	1900		丂梉丂	「嘛，那种事情无所谓了。我只是来提醒下而已。不要再坐在那么危险的地方了」
.transition 0 * 20
.stage	* ev00_008b02.png 0 0
.message	1910	yuk-000_01-0095	@桪丂巕	「啊啦，还真是温柔的人呢」
.message	1920			那名少女呵呵的笑起来。
;.message	1930			その笑い方はなぜかひどく癇に触った。
.message	1930			那个笑容不知为何让我有些不适。
.message	1940		丂梉丂	「……你偷偷来屋顶与否是你自己的事。但是，摔下去死掉的话会造成困扰的」
.transition 0 * 40
.stage	* ev00_008b03.png 0 0
.message	1950	yuk-000_01-0097	@桪丂巕	「为什么，你会困扰呢？」
.transition 0 * 20
.stage	* ev00_008b01_mugai_c.png 0 0
;（ここだけ，わざと目パチさせない？）
.message	1960			她歪着头，好像真的不理解的样子。
.message	1970		丂梉丂	「讨厌人死亡。不是理所当然的事情吗？」
.transition 0 * 20
.stage	* ev00_008a01_mugai_c.png 0 0
.message	1980	yuk-000_01-0099	@桪丂巕	「那是你个人的价值观吧」
.message	1990			她好象稍微有些生气的说道。
.message	2000			说起话来毫无考虑──少女给我留下了这样的印象。
.message	2010			同时也感觉到实际上也就是这么回事。
.transition 0 * 40
.stage	* ev00_008a04_mugai_c.png 0 0
.message	2020	yuk-000_01-0101	@桪丂巕	「虽然如此，当然，我并没有贬低你的价值观的意思哦」

;■御影チェック
;.message	2030			血のように赤い夕陽に照らされた少女の顔が，优しい微笑みに変わる。
.message	2030			红色的夕阳照耀下的少女的脸庞，浮起温柔的笑容。

;.transition 0 * 20
.transition 0 * 10
.stage	* ev00_008b01_mugai_b.png 0 0
.message	2040	yuk-000_01-0103	@桪丂巕	「火村夕前辈」
.message	2050			然后，她用柔软的声音喊出了我的名字──
.message	2060		丂梉丂	「……你是谁？」
.message	2070			是同一个学校的学生，知道我的名字本身并没有什么不思议。
.message	2080			但是。
.message	2090			我记得这个声音。
.message	2100			这个说话方式，这个笑容，确实存在于我久远记忆的某处。
.transition 0 * 20
.stage	* ev00_008a04_mugai_b.png 0 0
.message	2110	yuk-000_01-0105	@桪丂巕	「果然忘记了我啊。稍微有些受打击呢～」
.message	2120		丂梉丂	「回答我的问题」
;動きがくどいのでとりあえず削除 nbkz 2006/04/12
;.transition 0 * 20
;.stage	* ev00_008b04_mugai_b.png 0 0
.message	2130	yuk-000_01-0107	@桪丂巕	「不要作出那么可怕的表情啦。特别是在女孩子面前哦」
.message	2140			她摇摇头，用稍微带有叱责的口气说道。
;■御影チェック
;.message	2150			こんなにも苛つくのはなぜだろう。
.message	2150			为什么会如此不安。
.message	2160			这种心脏似乎被牵引着，几乎要失去呼吸的感觉。
.transition 0 * 20
.stage	* ev00_008a03_mugai_b.png 0 0
.message	2170			那名少女再次微笑起来。
;■御影チェック
;■　ここの名前を開くタイミングは，夕が思い出すか否かかと。
;■　なので，ラストまで閉じておく。最後の台詞が音声なしの文章なのも，
;■　この意味合いとあうと思う。
;.message	2180	yuk-000_01-0109	@桪丂巕	「……优子ですよ」
.message	2180	yuk-000_01-0109	@桪丂巕	「……我是优子啊」
;（名前をヒラかせるタイミング，よく考察のこと）
.message	2190		丂梉丂	「优…子？」
.transition 0 * 40
.stage	* ev00_008a04_mugai_b.png 0 0
.message	2200	yuk-000_01-0111	@桪丂巕	「嗯，这是我的请求……请不要说忘记掉那样的话好吗」
.message	2210			优…子……？
;.transition 0 * 40
;.stage	* ev00_008a01_mugai_b.png 0 0
.transition 0 * 40
.stage	* ev00_008a05_mugai_b.png 0 0
;（ここの表情，よくよく考察のこと。重要ポイントだぞっ）
.message	2220	yuk-000_01-0113	@桪丂巕	「我只看一眼就明白你是谁，而你却彻底的忘记了我呢……我的心已经被伤的无法治愈了」
.transition 0 * 10
.stage	past_window.png ev00_008a05_mugai_b_close.png 0 0
;.transition 0 * 40
;.stage	* ev00_008a05_mugai_b.png 0 0
;（a05の使いどころに関しては留意）
.message	2230	yuk-000_01-0115	@桪丂巕	「如果…」
.panel 0
.transition 0 * 10
.stage	* WHITE.png 0 0
;.transition 0 * 40
;.stage	* ev00_008a05_mugai_b_close.png 0 0

;(追加--画像で文字出します）ここのwaitはvoiceにあわせて調整すること nbkz 2006/04/12
;☆（↓の优子の台詞は，わざと音声トリました）
.wait 200
.transition 0 * 10
.stage	* ev00_moshi.png 0 0
.message	2240		桪丂巕	「如果真的忘记掉了，在想起之前请什么不要说」\v\a
.wait 300





;;■御影チェック
;;■　２週用の分岐スクリプト素体
;;■----------------------------------------------
.if ef_000 == 1 ef_000_b2
.if ef_000 <= 0 ef_000_a2
;
.label ef_000_a2

;■御影チェック
;■　キー入力無効
.pragma disable_control

.goto ef_000_b2
.end
;
.label ef_000_b2
;;■----------------------------------------------






.transition 0 * 10
.stage	* WHITE.png 0 0
.wait 200



;■回想·了
;.transition 0 * 10
.playBGM efBGM016.ogg
.transition 0 * 5
.stage	vista_window2.png ev00_012a01.png 500 0
.hscroll	0	-10
.endScroll f
.panel 3
.message	2250			优子仰头望向天空，微微的笑着。\a
.wait 250
.message	2260			她的笑颜跟过去相比丝毫未变。\a
.wait 260
.message	2270	yuk-000_01-0119	#桪丂巕	「那个夏天也好，屋顶的再会也好，还有其他的一切……都已经远远而去」\v\a
.wait 80
:.wait 50
;.wait 500
.message	2280	him-000_01-0033	#丂梉丂	「是很遥远……。很遥远。那已经是几年前的事情了呢」\v\a
.wait 100
;.wait 600
.message	2290	yuk-000_01-0121	#桪丂巕	「怎么好象是老爷爷的发言呢」\v\a
.wait 50
;.wait 120
.message	2300	him-000_01-0035	#丂梉丂	「你不也一样吗」\v\a
.wait 200
.panel 3
.message	2310			相互苦笑起来。\a
.wait 220
.message	2320			比起过去确实改变了的事实。\a
.wait 250
.message	2330			那是也是作为值得怀念的过去而在一点点增加的事实。\a
.wait 270
.message	2340	yuk-000_01-0123	#桪丂巕	「你……稍稍变了呢」\v\a
.wait 50
.message	2350	him-000_01-0037	#丂梉丂	「当然会变啊。都已经经过多少时间了」\v\a
.wait 100
;.wait 300
.message	2360	yuk-000_01-0125	#桪丂巕	「是啊……」\v\a
.wait 100
.message	2370	yuk-000_01-0127	#桪丂巕	「我们一起度过的那些时间……已经触不可及」\v\a
;.wait 300
.wait 90
.message	2380	him-000_01-0039	#丂梉丂	「回忆，记忆，都会随风而去。这是理所当然的事情」\v\a
.wait 100
.message	2390	yuk-000_01-0129	#桪丂巕	「虽然理所当然──但是，却让人悲伤难禁」\v\a
.wait 100
.message	2400	him-000_01-0041	#丂梉丂	「悲伤的事情虽然有许多。但是──」\v\a
.wait 200
.panel 3
.message	2410			时钟的指针不会回转。\a
.wait 250
.message	2420			寂寞和悲伤再怎么积累──总有一天会渐渐消散。\a
.wait 290
.message	2430			在时间的流逝中我已懂得。\a
.wait 250
.message	2440			大概，她也一样。\a
.wait 220
.panel 0
.transition 0 * 20
.stage	vista_window2.png ev00_012_mugai_c2.png 0 316
.panel 3
.message	2450	him-000_01-0043	#丂梉丂	「还是不要再摆出悲伤的表情了吧」\v\a
.wait 100
.message	2460	yuk-000_01-0131	#桪丂巕	「是啊……」\v\a
;.wait 100
.wait 90
.message	2470	yuk-000_01-0133	#桪丂巕	「这是我们第二次的再会啊」\v\a
.wait 200
;.wait 300
.message	2480	yuk-000_01-0135	#桪丂巕	「现在，我想要看到你的笑容」\v\a
.wait 200
.message	2490	yuk-000_01-0137	#桪丂巕	「我也想要满面笑颜」\v\a
;.wait 100
.transition 0 * 20
.stage	vista_window2.png ev00_012_mugai_c2.png 0 316
.vscroll	0	-7
.endScroll f
.transition 0 * 20
.stage	vista_window2.png ev00_012a02_mugai_a.png 0 0
.message	2500	yuk-000_01-0139	#桪丂巕	「只有在你的面前，才能让我展开笑颜呢」\v\a
;.wait 300
.transition 0 * 20
.stage	vista_window2.png ev00_014a01.png 0 0
;（ビスタに対応させるため挿入。表情に注意して）
.message	2510	him-000_01-0045	#丂梉丂	「不……」\v\a
.wait 200
;nbkz追加 2006/04/07
.stage * BLACK.png 0 0
.panel 0
.wait 50
.stage	* movie.png 0 0
.message	2511			\a　
.wait 200
.transition 0 * 20
.stage	vista_window2.png ev00_014a01_mugai_a.png 0 0
;（ここは夕の目つむり笑顔で？）
.panel 3
.message	2520	him-000_01-0047	#丂梉丂	「那张笑颜一开始你就已经拥有。只不过是我忘记掉了而已」\v\a
.wait 50
.message	2530	yuk-000_01-0141	#桪丂巕	「啊哈哈」\v\a
;.wait 200
.panel 3
.message	2540			她愉快的笑出了声。\a
.wait 250
.message	2550			渡过那再会的夏天，秋天转瞬既逝，然后冬天便接踵而来。\a
.wait 280
.message	2560			那个冷的过分的冬日。\a
.wait 270
.message	2570			虽然那过去的伤痕尚未平复。\a
.wait 250
.message	2580			但优子和我都在由衷的快乐着。\a
.wait 260
.panel 0
.transition 0 * 20
.stage	vista_window2.png ev00_014a04_mugai_a.png 0 0
.panel 3
.message	2590	him-000_01-0049	#丂梉丂	「……真愉快啊，那个时候」\v\a
;.wait 200
.transition 0 * 20
.stage	vista_window2.png ev00_014a04.png 0 0
;（ビスタサイズに対応のため，挿入）
.message	2600	yuk-000_01-0143	#桪丂巕	「虽然是一无所有呢」\v\a
.wait 50
.message	2610	yuk-000_01-0145	#桪丂巕	「虽然一无所有，但只要在一起就可以保持笑颜」\v\a
;.wait 300
.transition 0 * 20
.stage	vista_window2.png ev00_014a02_mugai_a.png 0 0
.message	2620	him-000_01-0051	#丂梉丂	「啊啊……」\v\a
.wait 200
.panel 3
.message	2630			只要看到她的笑颜我便会充实起来。\a
.wait 270
.message	2640			到不需要任何其他事物的程度。\a
.wait 250
.message	2650			比什么都重要的笑颜。\a
.wait 280
.message	2660			直到天涯海角，微笑着的她都会在我身边，我分明曾经如此坚信。\a
.wait 300
.panel 0
.transition 0 * 10
.stage	* WHITE.png 0 0






;■回想，607_01より。
;■夕自室（冬，２５時
;■　　　　火村夕　：私服（冬
;■　　　　雨宮优子：私服（冬
.transition 0 * 10
.stage	* ev00_009_pastm.png 0 0

;■御影チェック
;■　キー入力有効に
.pragma enable_control

.panel 1
.message	2670	yuk-000_01-0147	桪丂巕	「差不多该要休息了吧？」
.message	2680			优子她噗嗵的坐在我旁边说道。
.transition 0 * 20
.stage	* ev00_009_pastm2.png 0 0
;.transition 0 * 20
;.stage	* ev00_016_pastm2.png 0 0
.message	2690		丂梉丂	「咦，你还醒着吗」
.message	2700			我从笔记上扬起目光回答到。
.message	2710			看向钟表，日期已然是第二日了。
.message	2720	yuk-000_01-0149	桪丂巕	「还真是有集中力呢……。居然会像这样不闻身边事」
.message	2730		丂梉丂	「这个集中力如果能在设计时发挥出来的话……」
.transition 0 * 20
.stage	* bgw_home008a01_03_pastm.png 0 0
.message	2740	yuk-000_01-0151	桪丂巕	「那边不是才刚刚开始而已嘛。现在开始，现在开始」
.message	2750		丂梉丂	「就当是这样吧」
;.transition 0 * 20
;.stage	past_window.png ev00_010a03.png 0 0
.transition 0 * 20
.stage	* ev00_010a03_pastm2.png 0 0
.message	2760			我苦笑于优子的悠然自得，合起了笔记。
.message	2770			今日也打工了，差不多可以停下了吧。
.transition 0 * 20
.stage	* ev00_016_pastm2.png 0 0
.message	2780	yuk-000_01-0153	桪丂巕	「要不要沏茶给你喝？」
;（コーヒーが机の上にのっているが？）
.message	2790		丂梉丂	「啊啊，也好」
;■御影チェック
;.message	2800		丂梉丂	「……いや，もう寝るか。俺が起きてるとおまえ，寝そうにないし」
.message	2800		丂梉丂	「……不，还是睡吧」
.message	2805		丂梉丂	「我如果醒着的话，你也不会去安心休息」
;.transition 0 * 20
;.stage	* ev00_016a04_mugai_b.png 0 0
;.transition 0 * 20
;.stage	* ev00_016a04.png 0 0
:.transition 0 * 20
.transition 0 * 10
.stage	* ev00_016a01.png 0 0
;（表情注意）
.message	2810	yuk-000_01-0155	桪丂巕	「啊啦，露馅了吗？」
.message	2820		丂梉丂	「不是很明显吗。不要强迫自己做多余的事情」
.transition 0 * 40
.stage	* ev00_016a02.png 0 0
;.transition 0 * 40
;.stage	* ev00_016a03.png 0 0
.message	2830	yuk-000_01-0157	桪丂巕	「不是啦，只是看夕君认真的表情入迷了而已」
.message	2840		丂梉丂	「你啊……为什么能轻易说出那样让人会困扰的话呢？」
;.transition 0 * 40
;.stage	* ev00_016a01.png 0 0
.transition 0 * 40
.stage	* ev00_016a04.png 0 0
;（↑の表情と逆に？）
.message	2850	yuk-000_01-0159	桪丂巕	「嗯……啊」
.transition 0 * 40
.stage	* ev00_016a03.png 0 0
.message	2860	yuk-000_01-0161	桪丂巕	「是因为就是想要让那人困扰吧<音乐符号>」
.message	2870		丂梉丂	「啊…，是吗」
.message	2880			真是的，还真是好性格呢。
;.transition 0 * 20
.transition 0 * 10
.stage	* ev00_010a03.png 0 0
;.transition 0 * 40
;.stage	* ev00_016a02.png 0 0
;（02表情はさむ？）
.message	2890	yuk-000_01-0163	桪丂巕	「那么，我去铺被褥了」


;■夕自室（冬，２６時（夜·消灯）
;■それとも天井を１枚絵で出すか。
.transition 0 * 20
.stage	* ev00_010a04.png 0 0
.message	2900			确认优子已经钻进自己的被褥的时候，我也躺了下来。
.message	2910			被褥中有些微寒却十分舒心，一瞬全身的力气便松懈了下来。
.message	2920			比自己想象的还要疲劳。
.message	2930		丂梉丂	「…………」
.message	2940			好象只要闭上眼睛就可以进入梦乡…。
.message	2950	yuk-000_01-0165	桪丂巕	「夕君」
.message	2960		丂梉丂	「…………嗯？」
.message	2970	yuk-000_01-0167	桪丂巕	「那个……」
.message	2980		丂梉丂	「怎么了」
.message	2990	yuk-000_01-0169	桪丂巕	「其实我有事想拜托你……」
.message	3000		丂梉丂	「啊啊，怎么？」
.message	3010	yuk-000_01-0171	桪丂巕	「诶…嗯……」
.message	3020	yuk-000_01-0173	桪丂巕	「我能到那边去吗？」
.message	3030		丂梉丂	「…………哈？」
.message	3040			一瞬我以为耳朵是否出了毛病。
.message	3050			但是，却不是听错。
.message	3060		丂梉丂	「呃……我倒是无所谓」
.message	3070			我稍微有些浮躁的回答。
.message	3080		丂梉丂	「虽然我不是很懂，但这个时候不是该回避一下这种事情吗？」
.message	3090		丂梉丂	「而且我很累了……」
.message	3100	yuk-000_01-0175	桪丂巕	「夕君，你没误会什么吧？」
.message	3110			黑暗中那边传来微微的娇嗔。
.message	3120	yuk-000_01-0177	桪丂巕	「我，仅仅是说想要钻进夕君的被褥而已哦？」
.message	3130		丂梉丂	「…………少说容易让人想歪的话」
.message	3140	yuk-000_01-0179	桪丂巕	「明明是你自己想歪的…别生闷气嘛…」
.message	3150		丂梉丂	「没生气啦」
.message	3160			感到脸上的些许的灼热，我背向了优子。
.message	3170	yuk-000_01-0181	桪丂巕	「夕君啊，其实很H呢」
.message	3180		丂梉丂	「够了够了老实睡觉」
.message	3190	yuk-000_01-0183	桪丂巕	「诶～，那我的请求呢？」
.message	3200		丂梉丂	「随你便」
.message	3210			我背向着她说道。
.message	3220			可恶，对我来说真是大失误。
;■御影チェック
;.message	3230	yuk-000_01-0185	桪丂巕	「じゃ，失礼します」
.message	3230	yuk-000_01-0185	桪丂巕	「那么，打扰了～哦」
.message	3240			随着噌噌的声音，被褥被掀了起来。
.message	3250			然后，优子便钻了进来。
.transition 0 * 10
.stage	* ev00_011a01.png 0 0
.message	3260	yuk-000_01-0187	桪丂巕	「哼哼哼哼哼……」
;.message	3260	yuk-000_01-0187	桪丂巕	「ふふふ……」
.message	3270		丂梉丂	「那算什么，那个奇怪的笑声」
.message	3280			优子向着我的背靠了过来。
.message	3290			传来柔软的胸脯的触感……。
.message	3300		丂梉丂	「…………」
.transition 0 * 40
.stage	* ev00_011a02.png 0 0
.message	3310	yuk-000_01-0189	桪丂巕	「对不起」
.message	3320		丂梉丂	「为什么要道歉」
.message	3330	yuk-000_01-0191	桪丂巕	「那种事……再稍微忍耐下吧。现在还是控制一下的比较好」
.message	3340		丂梉丂	「……我知道」
.message	3350			稍稍高鸣的心脏也平静了下来。
.message	3360			为了她，就算是欲望也要抑制给她看。
.message	3370		丂梉丂	「优子」
.message	3380			我转过身体，和优子面对面，抱住她娇小的身体。
.transition 0 * 40
.stage	* ev00_011b01.png 0 0
.message	3390	yuk-000_01-0193	桪丂巕	「啊……」
.message	3400		丂梉丂	「互相取暖总可以吧？」
.transition 0 * 40
.stage	* ev00_011b02.png 0 0
.message	3410	yuk-000_01-0195	桪丂巕	「嗯！」
.message	3420			优子高兴的声音。
.transition 0 * 40
.stage	* ev00_011b03.png 0 0
.message	3430		丂梉丂	「姿势，不会不舒服吗？」
.message	3440	yuk-000_01-0197	桪丂巕	「嗯嗯，没事的」
.message	3450	yuk-000_01-0199	桪丂巕	「果然…不强迫自己多买那一组被褥也可以呢」
.message	3460			她又向这边靠了靠。
.message	3470	yuk-000_01-0201	桪丂巕	「你看，两个人盖一组被褥不也挺好吗」
.message	3480		丂梉丂	「毎晩的话会不舒服的吧。位置也很小」
.message	3490			说起来买被褥的时候。
.message	3500			当时，虽说是一起生活，但被褥──只有一组的话，怎样都不会安下心来。
.message	3510			在同一被褥里，欲望会抑制不住的。
.message	3520			毎晩都是这样的状态的话，我和优子都会头痛的。
.message	3530		丂梉丂	「偶尔还好啦」
.message	3540	yuk-000_01-0203	桪丂巕	「我呢，想一直这样」
.message	3550	yuk-000_01-0205	桪丂巕	「和夕君一起……一直在一起就好」
.message	3560	yuk-000_01-0207	桪丂巕	「这样的话──在梦中也可以在一起呢」
.message	3570		丂梉丂	「你又说出这么羞人的话来……」
.message	3580	yuk-000_01-0209	桪丂巕	「……我也很害羞啊」
.message	3590		丂梉丂	「那就别说啊」
.message	3600	yuk-000_01-0211	桪丂巕	「可是」
.transition 0 * 40
.stage	* ev00_011c01.png 0 0
.message	3610	yuk-000_01-0212		优子轻轻把桃唇凑了过来。
.transition 0 * 40
.stage	* ev00_011b03.png 0 0
.message	3620	yuk-000_01-0213	桪丂巕	「可是，本来就是如此啊」
.message	3630		丂梉丂	「……真是个小笨蛋」
.transition 0 * 40
.stage	* ev00_011c02.png 0 0
.message	3640			这次是我吻了过去，紧紧的抱住优子。
.transition 0 * 10
.stage	* ev00_010a04.png 0 0
;.transition 0 * 10
;.stage	* ev00_010a04_mugai_a.png 0 0
.message	3650			嗯，从此以后每天都一起入眠吧。
.transition 0 * 10
.stage	past_window.png ev00_010a04.png 0 0
;.transition 0 * 10
;.stage	past_window.png ev00_010a04_mugai_a.png 0 0
.message	3660			像这样身体互相靠近，双手紧握不分。
.panel 0
.transition 0 * 10
.stage	* WHITE.png 0 0




;;■御影チェック
;;■　２週用の分岐スクリプト素体
;;■----------------------------------------------
.if ef_000 == 1 ef_000_b3
.if ef_000 <= 0 ef_000_a3
;
.label ef_000_a3

;■御影チェック
;■　キー入力無効
.pragma disable_control

.goto ef_000_b3
.end
;
.label ef_000_b3
;;■----------------------------------------------





;ここ，文字を画像化しました nbkz 2006/04/12
.transition 0 * 10
.stage	* ev00_asaga.png 0 0
.message	3670			到次日来临，绝对不离不分。\v\a
.wait 400



;■回想·了
;.transition 0 * 10
.transition 0 * 5
.stage	vista_window2.png ev00_013a01_mugai_a.png 0 0
.panel 3
.message	3680	him-000_01-0053	#丂梉丂	「真的是非常愉快呢……」\v\a
.wait 50
;.wait 100
.transition 0 * 20
.stage	vista_window2.png ev00_013a01_mugai_a.png 0 0
.hscroll	660	10
.endScroll f
.message	3690	yuk-000_01-0215	#桪丂巕	「嗯，非常……」\v\a
.wait 200
.panel 3
.message	3700			虽然偶尔会吵吵架，但也不过是二人生活中的小插曲。\a
.wait 260
.transition 0 * 20
.stage	vista_window2.png ev00_013a01.png 0 0
.message	3710			比起什么都把对方看得最重要──\a
.wait 240
.message	3720			约好两人一起走下去。\a
.wait 280
.message	3730			约好如此的……。\a
.wait 220
.message	3740	him-000_01-0055	#丂梉丂	「但是我们却…」\v\a
;.wait 200
;nbkz追加 2006/04/07
.stage * BLACK.png 0 0
.transition 0 * 20
.panel 0
.wait 50
.stage	* sound.png 0 0
.message	3741			\a　
.wait 200
.transition 0 * 20
.stage	vista_window2.png ev00_013a05.png 0 0
.panel 3
.message	3750	yuk-000_01-0217	#桪丂巕	「…………」\v\a
;.wait 200
.message	3760	him-000_01-0057	#丂梉丂	「我们却松开紧握着的双手，走着不同的道路来到这里」\v\a
;.wait 300
.message	3770	yuk-000_01-0219	#桪丂巕	「嗯」\v\a
.wait 100
.panel 3
.message	3780			绝对不能说是短暂的时间。\a
.wait 240
.message	3790			甚至长到忘记对方都不奇怪的地步。\a
.wait 290
.message	3800			至少我的记忆已开始风化，许多重要的事物都已被扬灰而去了吧。\a
.wait 340
.panel 0
.transition 0 * 20
.stage	vista_window2.png ev00_013a05_close.png 0 0
.panel 3
.message	3810	yuk-000_01-0221	#桪丂巕	「为什么──」\v\a
.wait 100
.transition 0 * 20
.stage	vista_window2.png ev00_013a03.png 0 0
.message	3820	yuk-000_01-0223	#桪丂巕	「为什么，你要来到这里呢？」\v\a
.wait 100
.transition 0 * 20
.stage	vista_window2.png ev00_014a01.png 0 0
.message	3830	him-000_01-0059	#丂梉丂	「我们不是约好的吗」\v\a
.wait 100
.message	3840	him-000_01-0061	#丂梉丂	「在这儿相见的约定」\v\a
.wait 100
.panel 3
.message	3850			数年前的圣诞的早晨。\a
.wait 240
.message	3860			我确实作了这样的约定，她也点了点头。\a
.wait 280
.message	3870			调整呼吸，奔向优子等待着我的教会。\a
.wait 280
.message	3880			那日的事情现在仍记忆犹新。\a
.wait 280
.message	3890			没能履行约定而刻在胸口的痛楚，不会让我忘记……。\a
.wait 300
.message	3900	him-000_01-0063	#丂梉丂	「明明说过不会让你等久的」\v\a
.wait 100
.stage	vista_window2.png ev00_013a04.png 0 0
.message	3910	yuk-000_01-0225	#桪丂巕	「不。不……那种事情……」\v\a
;.wait 400
;.wait 300
.panel 3
.message	3920			优子她一次又一次的摇头。\a
.wait 230
.message	3930			我明白。\a
.wait 210
.message	3940			我已经被她原谅的事实。\a
.wait 250
.message	3950			但是，这份胸口的痛楚却不是如此就轻易消退。\a
.wait 270
.panel 0
.stage	vista_window2.png ev00_014a01.png 0 0
.panel 3
.message	3960	him-000_01-0065	#丂梉丂	「这次我终于能履行当时的约定而来到这里」\v\a
.wait 100
.message	3970	him-000_01-0067	#丂梉丂	「而且」\v\a
.wait 140
;.wait 100
.message	3980	him-000_01-0069	#丂梉丂	「大概，一直在呼唤着我的人是你……。没错吧？」\v\a
;.wait 300
.wait 20
.panel 3
.message	3990			优子直到现在还在这个地方等待着。\a
.wait 240
.message	4000			我明白这件事情绝非偶然。\a
.wait 270
.panel 0
.stage	vista_window2.png ev00_013a02.png 0 0
.panel 3
.message	4010	yuk-000_01-0227	#桪丂巕	「嗯……」\v\a
.wait 100
.message	4020	yuk-000_01-0229	#桪丂巕	「说不定是这样没错」\v\a
;.wait 200
;.stage	* ev00_014a01.png 0 0
;（酒井指定により削除）
.message	4030	him-000_01-0071	#丂梉丂	「告诉我吧。在你身边究竟发生了什么」\v\a
.wait 100
.transition 0 * 20
.stage	vista_window2.png ev00_014_mugai_b.png 0 0
.message	4040	yuk-000_01-0231	#桪丂巕	「发生了什么，吗……」\v\a
.wait 100
.panel 3
.message	4050			望向教会的门扉，优子开始找寻想要说的话。\a
.wait 240
.message	4060			我当然明白。\a
.wait 220
.message	4070			不是一言两语就可以说完的故事。\a
.wait 270
.message	4080	yuk-000_01-0233	#桪丂巕	「故事的开始……」\v\a
.wait 200
;nbkz追加 2006/04/07
.stage * BLACK.png 0 0
.transition 0 * 20
.panel 0
.wait 50
.stage	* direc.png 0 0
.message	4081			\a　
.wait 200
.transition 0 * 20
.stage	vista_window2.png ev00_015a02.png 0 0
.panel 3
.message	4090	yuk-000_01-0235	#桪丂巕	「果然还是圣诞节呢」\v\a
.wait 130
;.wait 150
;.wait 100
.message	4100	yuk-000_01-0237	#桪丂巕	「正好一年前的圣诞节的夜晚」\v\a
.wait 150
;.wait 100
.message	4110	yuk-000_01-0239	#桪丂巕	「那个人──对了，回想起来那个人与你有几分相似呢」\v\a
.wait 90
;.wait 100
.message	4120	him-000_01-0073	#丂梉丂	「和我吗？」\v\a
.wait 100
.panel 3
.message	4130			像我这样没品的人，在这城市还另有一个吗。\a
.wait 270
.message	4140	yuk-000_01-0241	#桪丂巕	「推开门扉，那个人走了进来」\v\a
.wait 150
.message	4150	yuk-000_01-0243	#桪丂巕	「走进来的是，一个男孩子」\v\a
.wait 150
.message	4160	yuk-000_01-0245	#桪丂巕	「某些地方和你相似──对，那种令人怀念的气息」\v\a
;.wait 300
.transition 0 * 20
.stage	vista_window2.png ev00_015a01.png 0 0
;（ここと下の01，もうちょっと目を細めた笑顔がいいな……）
.message	4170	yuk-000_01-0247	#桪丂巕	「所以我才会这么想吧」\v\a
.wait 100
.message	4180	him-000_01-0075	#丂梉丂	「什么？」\v\a
.wait 100
;nbkz追加 2006/04/07
.stage * BLACK.png 0 0
.transition 0 * 20
.panel 0
.wait 50
.stage	* produce.png 0 0
.message	4181			\a　
.wait 200
;.transition 0 * 20
.transition 0 * 10
.stage	vista_window2.png ev00_015a03.png 0 0
.panel 3
.message	4190	yuk-000_01-0249	#桪丂巕	「略微——，走进这个男孩的故事中去吧」\v\a
.wait 100
.message	4200	him-000_01-0077	#丂梉丂	「能让我听听看吗，那个人的故事」\v\a
.wait 100
.transition 0 * 20
.stage	vista_window2.png ev00_015a01.png 0 0
.message	4210	yuk-000_01-0251	#桪丂巕	「会是悠长的故事，可以吗？」\v\a

.wait 110
;.wait 100


;■御影チェック
;.panel 3
;.message	4220			微笑して，优子は問いかけてくる。\a
;.wait 260
;.panel 0


.message	4230	him-000_01-0079	#丂梉丂	「当然，到黎明还有很久呢」\v\a
;.wait 300
.transition 0 * 20
.stage	vista_window2.png ev00_015a02.png 0 0
.message	4240	yuk-000_01-0253	#桪丂巕	「那么，就让我娓娓道来吧」\v\a
.wait 100
;.wait 200
.transition 0 * 20
.stage	vista_window2.png ev00_015_mugai_a.png 0 0
.panel 0
;☆（パネル0はフェードと画像の間に挿むか，フェードの前に置くか，この位置でいいのか。よくよく考察して）
;（ここは実際はメッセージウインドウを消して，音声のみで）-- autoにしてwait追加 nbkz 2006/04/12



;■御影チェック
;■　実験用
;■-------------------------------------------------
;.label koko
;.playBGM efBGM016.ogg
;.transition 0 * 20
;.stage	vista_window2.png ev00_015_mugai_a.png 0 0
;.panel 0
;■-------------------------------------------------


.panel 3
.message	4250	yuk-000_01-0255	#桪丂巕	「从他来访这个教会的一刻所开始的，冬日的故事……」\v\a
.wait 150
.panel 0

;タイトルはここにもってきました nbkz 2006/04/07
;.panel 0
.transition 0 * 10
;.transition 0 * 5
.stage	vista_window2.png WHITE.png 0 0
.wait 100
.effect SnowH
.transition 0 * 10
.stage	vista_window2.png bgw_normal011a01_03.png 0 600
.transition 0 * 20
.stage	vista_window2.png bgw_normal011a01_03.png 0 600
.vscroll	0	-10
.endScroll f
;.transition 0 * 20
;.wait 120
.wait 160
;.transition 0 * 10
.transition 0 * 7
.stage	vista_window2.png bgw_normal011a01_03_tero_c.png 0 0
.message	4251			\a　
;.wait 200
;.transition 0 * 10
.wait 220
.transition 0 * 7
.stage	vista_window2.png bgw_normal011a01_03_tero_d.png 0 0
.message	4251			\a　
.wait 250
;.transition 0 * 10
.transition 0 * 7
.stage	vista_window2.png bgw_normal011a01_03_tero_out.png 0 0
.message	4251			\a　


;.wait 500
.wait 170



;.playBGM *
.transition 0 * 10
.stage	* WHITE.png 0 0

;■御影チェック
.playBGM * 10
.wait 40

.effect *
;.stage * BLACK.png 0 0




;■御影チェック
;■　「序章」読んだよフラグ。
;■----------------------------------------------
.setGlobal ef_000 = 1
;■----------------------------------------------


;■御影チェック
;■　キー入力有効に
.pragma enable_control


.chain 100_01.sc
;■100_01へ。
;.end
