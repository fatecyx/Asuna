; ファイル: 211_01.txt
;■＜２章：１１日目＞
;■背景：学園·廊下（夏，１３時
;■　　　　堤京介：制服（夏）
.playSE semishigure_b.ogg true 
.transition 0 * 10
.stage	* bgs_sch002m01_01.png 0 0
.panel 1
.message	100			让人心烦意乱的蝉鸣响彻耳际。
.message	110			还仅仅是七月而已，这种热算什么啊……。
.transition 0 * 20
.stage	* ev02_040a01_mugai_a.png 0 0
.message	120		嫗丂夘	「哈～，真够受的」
.message	130			再怎么发牢骚也不会有所改变。
.message	140			熱心的导演不惜一丝时间想要让摄影取得进展，连午休都把摄影研究部的部员们招集起来。
.message	150			这样一直忙着，我反而值得感谢。
.message	160			白天是上课和研究部的活动。
.message	170			跟随着部长的节奏只是转动着摄像机，晚上勤于努力功课。
.message	180			仅此而已的日子暂时持续着──
.panel 0
.playSE *
.transition 0 * 10
.stage	* WHITE.png 0 0


;■ここより景視点
;■背景：教室（夏，１５時
;■　　　　新藤景：制服（夏）
.playSE AT_chime.ogg f 0 *
.transition 14 * 12
;.transition 0 * 10
.stage	vista_window.png bgs_sch004m03_02.png 0 0
;（この背景は注意。「授業が終わった」＝「帰る準備」にはすぐに結びつかないこともあるので）
.panel 3
.message	190			铛～叮～铛～咚～。
.message	200	kei-211_01-1003		什么事都没有──虽然不能这么说，但今天的课程还是结束了。
.message	210	kei-211_01-1005		像我这样成绩不佳的学生，为了小心一旦地被指名，在上课中一直都是战战兢兢。
.message	220	kei-211_01-1007		作为升学学校的音羽，二年级的平均水平都很高，不会点名的课程也几乎不存在。
.message	230	kei-211_01-0003	#丂宨丂	「呼……」
.message	240	kei-211_01-1009		真的，累怀了啊。
.message	250	kei-211_01-1011		而且压力也越积越多。
.message	260	kei-211_01-1013		会不会再有飞贼出现啊。
;■ため息
.message	270	kei-211_01-0005	#丂宨丂	「…………」
.message	280	kei-211_01-1015		虽然说出来有些乱，但现在真的是想要找谁打一顿的心情。

;■校門
.playSE *
.screen sc_evening01.png sc_evening01.png
.transition 1 fadeSide.png 20
.stage	* bgs_sch009m01_02.png 0 0
.message	290	kei-211_01-1017		同要去图书馆学习的朋友告别之后，一个人走出校门。

;■通学路
.transition 1 fadeSide.png 20
.stage	* bgs_normal002a01_02.png 0 0
.message	300	kei-211_01-1019		不得不准备考试了。
.message	310	kei-211_01-1021		特别是我如果不付出超出他人数倍的努力的话，暑假说不定就要淹死在补习里面。
.message	320	kei-211_01-1023		但是，我在做什么啊……。
.screen * *
;.playSE efBGM053mix.ogg true 0 *
.playSE 025.ogg true 0 *
;☆（ＢＧＭで鳴らしてます。問題あるようならレ～トを変えてＳＥに回すこと）
;☆（ＡＴから「素直な心」引っ張ってきてます。問題あるようなら差し替えを）
;☆（ル～プさせるべきか？ちょっと注意して。ＦＦＤではル～プさせた？）
.transition 0 * 20
.stage	* ev02_092a01.png 0 0
.message	330	kei-211_01-0007	#丂宨丂	「啊」
.message	340	kei-211_01-1025		手机在口袋中响了起来。
.message	350	kei-211_01-1027		在手机响起的同时，我的心脏也咚地，大大的跳了一下。
.message	360	kei-211_01-1029		说不定我是在期待，期待那个人会打来电话。
.message	370	kei-211_01-1031		又不是吵架分手，打过电话来也没什么奇怪──
.message	380	kei-211_01-1033		我甚至想起来这种事情来。
;■自嘲
.transition 0 * 20
.stage	vista_window.png ev02_092b01.png 0 0
.message	390	kei-211_01-0009	#丂宨丂	「……真是笨蛋呢」
.message	400	kei-211_01-1035		轻轻摇了摇头，我把手伸进口袋。
.panel 0
.playSE *
.transition 0 * 10
.stage	vista_window.png WHITE.png 0 0


;■背景：景自室（夏，１６時
;■　　　　新藤景　　：制服（夏）
;■　　　　羽山瑞希：制服（夏）

;■御影チェック
;■　このＳＥは大不評～
;.playSE eakon.ogg f

.transition 1 fadeSide.png 10
.stage	vista_window.png ev02_093a01_54.png 0 0
;☆（このＣＧでインする場合，景の自室であることがわかるように注意すること）
;.stage	* bgc_home003a01_02.png 0 0
.panel 3
.message	410	kei-211_01-1037		室内有着空调保持着舒适的温度。
.message	420	kei-211_01-1039		去年的这个时候，还在热如蒸笼的体育馆里每天练习到站不起来，现在想起来毫无现实感。
.message	430	kei-211_01-1041		这里就是天国啊。
.message	440	kei-211_01-1043		不过天国说不定也是──会让人无限堕落下去的地方。
.transition 0 * 40
.stage	vista_window.png ev02_093a02_54.png 0 0
.message	450	mid-211_01-0003	儈僘僉	「呼啊～」
.playSE *
.playBGM efBGM013.ogg
;.playBGM efBGM013.ogg 0 *
.message	460	kei-211_01-1045		一心不乱看着参考书的瑞希突然发出奇怪的声音。
.transition 0 * 40
.stage	vista_window.png ev02_093b01_54.png 0 0
.message	470	kei-211_01-0011	#丂宨丂	「怎么了吗？」
.message	480	mid-211_01-0005	儈僘僉	「不，…稍微…那个，休息一下吧？」
.transition 0 * 40
.stage	vista_window.png ev02_093b02_54.png 0 0
.message	490	kei-211_01-0013	#丂宨丂	「我说，才刚刚开始好吧」
.message	500	kei-211_01-1047		我有些生气的说。
.message	510	kei-211_01-1049		刚才的电话，是瑞希打来的。
.message	520	kei-211_01-1051		景前辈，我也临近考试了要不要一起学习呢──
.message	530	kei-211_01-1053		我想不出拒绝这个邀请的理由。
.transition 0 * 40
.stage	vista_window.png ev02_093c01_54.png 0 0
.message	540	mid-211_01-0007	儈僘僉	「前辈的房间真让人安心呢。觉得好舒服，舒服到几乎都不想学习了」
.message	550	kei-211_01-0015	#丂宨丂	「算什么啊，那理由」
.message	560	kei-211_01-1055		我连苦笑都挤不出来。
.message	570	kei-211_01-1057		从我春天放弃部团活动以来，瑞希就时常这样到我家来。
.message	580	kei-211_01-1059		以前，还因为害羞收集少女漫画的事而没有让这个房间进过人……。
.message	590	kei-211_01-1061		而最近，却觉得这种事完全无所谓啊。
.transition 0 * 40
.stage	vista_window.png ev02_093c02_54.png 0 0
.message	600	mid-211_01-0009	儈僘僉	「啊啊，想更溶入这里啊……」
.transition 0 * 40
.stage	vista_window.png ev02_093c03_54.png 0 0
.message	610	mid-211_01-0011	儈僘僉	「更不如说，想和景前辈半同居啊……」
.message	620	kei-211_01-1063		微妙中途半端的愿望啊……。
.message	630	kei-211_01-0017	#丂宨丂	「我说你老这么悠闲没事吗？　不是想要推荐资格的吗？」
.transition 0 * 40
.stage	vista_window.png ev02_093c04_54.png 0 0
.message	640	mid-211_01-0013	儈僘僉	「就是因为没把握，才这样逃避现实的哦～」
.message	650	kei-211_01-0019	#丂宨丂	「我说你啊，瑞希」
.message	660	kei-211_01-1065		这孩子，成绩绝对不坏的，为什么会这样呢。
.message	670	kei-211_01-0021	#丂宨丂	「我还想学习呢，你松松垮垮的让我都失去干劲了啦」
.transition 0 * 40
.stage	vista_window.png ev02_093c05_54.png 0 0
;（ここの瑞希の表情，気をつけて）
.message	680	mid-211_01-0015	儈僘僉	「啊啊，没事没事的啦。一次两次考试，完全无所谓的嘛？」
.message	690	kei-211_01-0023	#丂宨丂	「别转来转去变意见好吧。我这边还混乱着呢」
.transition 0 * 40
.stage	vista_window.png ev02_093b03_54.png 0 0
.message	700	mid-211_01-0017	儈僘僉	「对了，景前辈」
.message	710	kei-211_01-1067		突然认真起来的瑞希。
.message	720	mid-211_01-0019	儈僘僉	「我呢，有一个堂兄。比我大一岁的男孩子」
.message	730	kei-211_01-0025	#丂宨丂	「你想说什么？」
.message	740	mid-211_01-0021	儈僘僉	「他呢，不止为何就是没有朋友」
.message	750	mid-211_01-0023	儈僘僉	「虽然不能对本人说，性格也没什么问题──倒不是说，是个满不错的人呢。但为何会这样真是不可思议」
.message	760	kei-211_01-0027	#丂宨丂	「如果性格很差还可以放弃，真是麻烦事呢」
.transition 0 * 40
.stage	vista_window.png ev02_093b04_54.png 0 0
.message	770	mid-211_01-0025	儈僘僉	「是啊」
.message	780	kei-211_01-1069		瑞希满足的一边笑一边点头。
.message	790	kei-211_01-0029	#丂宨丂	「然你那堂兄则怎么了吗？」
.transition 0 * 40
.stage	vista_window.png ev02_093b05_54.png 0 0
.message	800	mid-211_01-0027	儈僘僉	「呃呃──」
.message	810	mid-211_01-0029	儈僘僉	「我说什么来着？」
.transition 0 * 40
.stage	vista_window.png ev02_093d01_54.png 0 0
.message	820	kei-211_01-0031	#丂宨丂	「我怎么知道！」
.message	830	mid-211_01-0031	儈僘僉	「前辈，生气的表情也好美哦。啊啊，数码相机呢！　数码相机在哪！」
;■呆れ
.transition 0 * 40
.stage	vista_window.png ev02_093d02_54.png 0 0
.message	840	kei-211_01-0033	#丂宨丂	「…………」
.message	850	kei-211_01-1071		头痛看来不是空调房的原因。
.transition 0 * 40
.stage	vista_window.png ev02_093c01_54.png 0 0
.message	860	mid-211_01-0033	儈僘僉	「啊，对了对了」
.message	870	mid-211_01-0035	儈僘僉	「他虽然没有朋友，但他并不是孤单一人哦」
.message	880	mid-211_01-0037	儈僘僉	「因为他还有着温暖的家人，和一个温柔可爱又有些早熟的堂妹哦」
.transition 0 * 40
.stage	vista_window.png ev02_093b06_54.png 0 0
.message	890	kei-211_01-0035	#丂宨丂	「你到底想说什么啊你」
.message	900	mid-211_01-0039	儈僘僉	「因为人并非生活在极地的极点，所以人永远不会孤单」


;;■御影チェック
;.transition 0 * 40
;.stage	vista_window.png ev02_093b07_54.png 0 0


;■御影チェック
;.message	910	mid-211_01-0041	儈僘僉	「というより，ひとりになんてなれないんです。みんな，どこかで繋がってるんですから──」
.message	910	mid-211_01-0040	儈僘僉	「倒不如说是，人不可能会孤单吧」
;■御影チェック
;■　この表情，１個上だな。
;■　音声分割したら，最後のところ。
.transition 0 * 40
.stage	vista_window.png ev02_093b07_54.png 0 0
.message	915	mid-211_01-0042	儈僘僉	「大家，都会在哪里有着相互的羁绊呢──」

;■御影チェック
;■　こっちに持ってきてみる
.message	940	kei-211_01-1073		瑞希说着，绽放出满面的笑颜。

.message	920	kei-211_01-0037	#丂宨丂	「…………」
;.transition 0 * 40
;.stage	vista_window.png ev02_093b07.png 0 0
.message	930	kei-211_01-0039	#丂宨丂	「我有时会想。你到底是什么人？」

;■御影チェック
;■　コメントアウト。
;.message	940	kei-211_01-1073		瑞希は，ぱあっと満面の笑顔を咲かせる。

.message	950	mid-211_01-0043	儈僘僉	「我就是我哦，景前辈」
.panel 0
.playBGM *
.transition 0 * 10
.stage	vista_window.png WHITE.png 0 0




;■背景：紘の家の前（夏，２０時
;■　　　　新藤景　　：私服（夏）
;■　　　　宫村宫子：制服（夏）
.playBGM efBGM028mix.ogg
.screen sc_night01.png sc_night01.png
.transition 1 fadeSide.png 10
.stage	vista_window.png bgs_normal015a01_03.png 0 0
.panel 3
.message	960	kei-211_01-1075		几个月前──对，仅仅几个月前。
.message	970	kei-211_01-1077		只要走到这条路的最后就好。
.message	980	kei-211_01-1079		所以，就算闭上眼睛也可以走到目的地。
.message	990	kei-211_01-0041	#丂宨丂	「……我到底在干什么呢」
.message	1000	kei-211_01-1081		瑞希和我陪家人用过晚餐，然后回去之后，不止为何心情就是无法平静。
.message	1010	kei-211_01-1083		我并不是一个人。
.message	1020	kei-211_01-1085		大概瑞希说的没错。
.message	1030	kei-211_01-1087		但就算如此，去哥哥家要干什么？
.message	1040	kei-211_01-1089		又能怎样？
.message	1050	kei-211_01-1091		我也讨厌孤单一人。
.message	1060	kei-211_01-1093		但是，真正希望的是──想和哥哥在一起。
.message	1070	kei-211_01-1095		和哥哥紧密不分。
.message	1080	kei-211_01-1097		我真心希望的一定仅此而已。
.message	1090	kei-211_01-1099		但是，我也明白什么也做不到。
.message	1100	kei-211_01-1101		不，该说是──就算作了也毫无用处才对。
.message	1110	kei-211_01-1103		所以我停下了脚步。
.message	1120	kei-211_01-1105		应该全愈的膝盖隐隐作痛。
.message	1130	kei-211_01-0043	#丂宨丂	「别做傻事，回去吧……」
;■足音のSE入れるか？
;■不審
.playBGM *
.screen * *
.transition 0 * 20
.stage	* ev02_094a01_kei_a.png 0 0
;（インのタイミング，注意して）
.message	1140	kei-211_01-0045	#丂宨丂	「……嗯？」
.message	1150	kei-211_01-1107		有谁来了……。
.message	1160	kei-211_01-1109		站在这里的话会被觉得奇怪吧。
.message	1170	kei-211_01-1111		我转过身去──
;（「踵を返す」，，，立ち位置にちょっと注意して）
.transition 0 * 20
.stage	vista_window.png ev02_094b01_kei_a.png 0 0
;（フェ～ドスピ～ドは注意して）
.message	1180	miy-211_01-0003	@傒傗偙	「咦，难道是」
.message	1190	kei-211_01-0047	#丂宨丂	「诶？」
.message	1200	kei-211_01-1113		黑暗的那边的响声停了下来。
.message	1210	miy-211_01-0005	傒傗偙	「果然是小景呢」
;（↑は＠つけなくて良い？）
;■軽い驚き
.message	1220	kei-211_01-0049	#丂宨丂	「宫村前辈……」
.panel 0
.transition 0 * 10
.stage	vista_window.png WHITE.png 0 0


;■シ～ン転換
;■背景：公園（夏，２０時３０分
.playBGM efBGM031.ogg
.transition 1 fadeSide.png 10
.stage	vista_window.png ev02_095a01_kei_a.png 0 0
;.stage	* bgs_normal009a01_03.png 0 0
.panel 3
.message	1230	kei-211_01-1115		附近传来阵阵此起彼伏的虫子的夜鸣。
.message	1240	kei-211_01-1117		虽然被宫村前辈邀请，来到了这种地方……。
.message	1250	kei-211_01-1119		但到了现在，该和这个人说什么好呢。
.message	1260	miy-211_01-0007	傒傗偙	「果然到了这个时候，风就凉快起来了呢」
.message	1270	kei-211_01-0051	#丂宨丂	「……是啊」
.message	1280	kei-211_01-1121		什么啊，这个状況。
.transition 0 * 40
.stage	* ev02_095a02_kei_a.png 0 0
.message	1290	miy-211_01-0009	傒傗偙	「别那么僵硬嘛……不过说起来好像不可能呢？　好久好久没有好好说过什么话了呢」
.message	1300	kei-211_01-0053	#丂宨丂	「因为我没有和宫村前辈说话的理由」
.message	1310	kei-211_01-1123		为什么声音会突然高扬起来。
.message	1320	kei-211_01-1125		分明摆出这种态度，是我还在被过去牵挂着的证据。
.message	1330	miy-211_01-0011	傒傗偙	「小景……」
;■ぼそり
.transition 0 * 40
.stage	* ev02_095a03_kei_a.png 0 0
.message	1340	miy-211_01-0013	傒傗偙	「讨厌我吗？」
.message	1350	kei-211_01-1127		干吗，这个白痴。
.message	1360	kei-211_01-1129		不要问无聊的问题好不好。
.transition 0 * 40
.stage	* ev02_095b01_kei_a.png 0 0
.message	1370	miy-211_01-0015	傒傗偙	「啊啊～」
.message	1380	kei-211_01-1131		宫村前辈突然发出失望般的声音。
.message	1390	miy-211_01-0017	傒傗偙	「说什么呢我。讨厌自己，讨厌自己」
.transition 0 * 40
.stage	* ev02_095c01_kei_a.png 0 0
.message	1400	kei-211_01-0055	#丂宨丂	「你那种愚弄人的态度──」
.message	1410	kei-211_01-1133		──不行了。
.message	1420	kei-211_01-1135		我哗哗的摇着越来越热的头。
.message	1430	kei-211_01-1137		站在这个人面前，无论怎样都控制不住自己。
.message	1440	kei-211_01-1139		如果这样的话就是我输了。
.message	1450	kei-211_01-1141		虽然不太明白，但我这么想。
.transition 0 * 40
.stage	* ev02_095d01_kei_a.png 0 0
.message	1460	kei-211_01-0057	#丂宨丂	「你拿别人的困扰取乐对吧。我生气的话正会让前辈高兴而已」
.message	1470	miy-211_01-0019	傒傗偙	「虽然这个不能否定」
.message	1480	kei-211_01-1143		否定啊。
.message	1490	kei-211_01-0059	#丂宨丂	「……把我带到这的理由是什么？」
.message	1500	miy-211_01-0021	傒傗偙	「想要和小景聊聊天啊」
;■睨み
.message	1510	kei-211_01-0061	#丂宨丂	「自以为是哥哥的代理来安慰我吗？」
.message	1520	miy-211_01-0023	傒傗偙	「怎么可能，当然不是」
.message	1530	miy-211_01-0025	傒傗偙	「还是说小景想让谁安慰一下吗？」
.message	1540	kei-211_01-1145		……你说什么？
.message	1550	miy-211_01-0027	傒傗偙	「我不认为小景可怜，也不会想要道歉」
.message	1560	kei-211_01-0063	#丂宨丂	「理所当然的。被宫村前辈道歉什么的──」
.message	1570	kei-211_01-1147		突然，大脑沸腾起来。
.message	1580	kei-211_01-1149		从未感觉过的无法抑制的激烈的怒气。
.message	1590	kei-211_01-0065	#丂宨丂	「道歉的理由什么的──」
.transition 0 * 40
.stage	* ev02_095e01_kei_a.png 0 0
.message	1600	kei-211_01-0067	#丂宨丂	「根本没有！」
.message	1610	kei-211_01-1151		一次都不向我道歉的话，我还可以这样和宫村前辈说话。
.message	1620	kei-211_01-0069	#丂宨丂	「如果道歉的话，那我才真正不原谅你！」
.message	1630	kei-211_01-1153		如果道歉的话。
.message	1640	kei-211_01-1155		我也就太惨了。
.transition 0 * 40
.stage	* ev02_095d02_kei_a.png 0 0
.message	1650	miy-211_01-0029	傒傗偙	「这才是小景啊」
.message	1660	kei-211_01-0071	#丂宨丂	「……哈？」
.transition 0 * 40
.stage	* ev02_095d03_kei_a.png 0 0
.message	1670	miy-211_01-0031	傒傗偙	「这样強气的小景，我才喜欢哦」
.message	1680	kei-211_01-0073	#丂宨丂	「说，说什么呢你……」
.message	1690	miy-211_01-0033	傒傗偙	「我的朋友里呢，有一个一直爱着一个人的女孩子」
.message	1700	kei-211_01-1157		宫村前辈忽然笑了起来。
.message	1710	miy-211_01-0035	傒傗偙	「小景和那女孩一样。坚强……很坚强」
.message	1720	kei-211_01-1159		我很坚强？
.message	1730	kei-211_01-1161		这个，一直都是迟疑不决的我吗？
.transition 0 * 40
.stage	vista_window.png ev02_095d02_kei_a.png 0 0
;（表情，注意して）
.message	1740	miy-211_01-0037	傒傗偙	「说不定堤君想要拍摄的，也就是小景坚强的一面吧」
.message	1750	kei-211_01-0075	#丂宨丂	「堤前辈吗……」
.message	1760	kei-211_01-1163		拥有坚强的是堤前辈和……虽然不甘心，这个宫村前辈一样的人。
.message	1770	kei-211_01-1165		虽然一直这么想，我也是吗？
.transition 0 * 10
.stage	past_window.png ev02_095d02_kei_a.png 0 0
.message	1780	kei-211_01-1167		真的吗……？
;.panel 0
;.transition 1 fadeSide.png 10
;.stage	kei_window.png WHITE.png 0 0
.transition 0 * 10
.stage	* vista_white.png 0 0
.playBGM *
.panel 0
;.transition 1 fadeSide.png 10
.transition 0 * 10
.stage	vista_window.png WHITE.png 0 0
.transition 0 * 10
.stage	vista_window.png WHITE.png 0 0
.wait 100

.chain 212_01.sc
;■212_01へ。

;.end
