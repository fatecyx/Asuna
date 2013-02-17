; ファイル: 202_01.txt
;■＜２章：２日目＞
;■背景：京介自室（夏，８時
;■　　　　堤京介：制服（夏）
.transition 0 * 10
.stage	* bgc_home002a01_00.png 0 0
.panel 1
.message	100			今天又是一个神清气爽的早晨。
.message	110			一如既往，迅速的换好制服然后整理好东西。
.message	120			虽然昨天搞的一团糟，但今天一定要和她聊一下。
.message	130			虽然在摄影研究部时，也有过几次跟女演员交涉演出的经历──
.message	140			但可以肯定，新藤景是至今为止最让人头痛的。
.message	150			不过正是这样，才会让我想作下去。
.panel 0
.transition 0 * 10
.stage	* WHITE.png 0 0


;■背景：通学路（夏，８時３０分
;■　　　　堤京介：制服（夏）
;■　　　　新藤景：制服（夏）
.playBGM efBGM051.ogg
;.playBGM BGM054_sample.ogg
.screen sc_morning01.png sc_morning01.png
.transition 1 fadeSide.png 10
.stage	* ev02_021a01.png 0 0
.panel 1
.message	160		嫗丂夘	「早上好～」
;■ため息
.message	170	kei-202_01-0003	丂宨丂	「…………」
.message	180			和左右的朋友走在一起的新藤显出一副明显讨厌我的表情。
.message	190			但就算看到这样的表情也会觉得──真是好表情啊，这恐怕就是我除了想拍她以外再没有考虑其他的证据了吧。
.message	200		嫗丂夘	「抱歉，能稍微借下新藤同学吗？」
.message	210			我向新藤的朋友笑了一下。
.message	220	etc-202_01-0003	桭恖侾	「哈，哈啊……」
.message	230	etc-202_01-0005	桭恖俀	「如果景同意的话……我们倒是无所谓」
.message	240			她们犹豫着放松了警戒，重要的本人则是──
.message	250	kei-202_01-0005	丂宨丂	「什么借与不借的……我可不是用来出租的录像带」
.message	260		嫗丂夘	「啊啊，我会员证带了吗？」
.message	270			一闪，锐利的目光便刺了过来。
.message	280		嫗丂夘	「抱歉抱歉，说笑而已啦」
.message	290	kei-202_01-0007	丂宨丂	「我…最讨厌说笑」
.message	300		嫗丂夘	「我会牢记在心。就算如此，我也确实是有话要说啊」
.message	310	kei-202_01-0009	丂宨丂	「……哈～」
.message	320			新藤深深的叹了一口气，向左右的女生露出有些疲惫的笑容。
.transition 0 * 40
.stage	* ev02_021b01.png 0 0
.message	330	kei-202_01-0011	丂宨丂	「抱歉，能请你们前面先走吗？」
.message	340	etc-202_01-0007	桭恖侾	「可以是可以……」
.message	350			不知为何，她们脸上稍微有些不安。
.message	360	kei-202_01-0013	丂宨丂	「没事的啦，我不会杀了他的」
.message	370			果然这个女孩子危险的有些过分啊。
.message	380			倒是，让朋友都担心成这个样子算什么啊，新藤景。
.transition 0 * 20
.stage	* ev02_021c01.png 0 0
.message	390			那些女生虽然表情有些困扰，但还是离开我们先走了。
.message	400	kei-202_01-0015	丂宨丂	「一边走一边说吧。站下去的话就要迟到了」
.screen * *
.transition 1 fadeSide.png 20
.overlay	or_kei00a.png * *
.screen	sc_morning01.png sc_morning01.png sc_morning01.png
;.screen	scl_morning01.png scl_morning01.png scl_morning01.png
.stage	st_kei11b01-.png 0 0 bg_scl002a01_00_f.png 0 0 bg_scl002a01_00_n.png 0
.effect	WScroll2 * 60 -2


.message	410		嫗丂夘	「然，你考虑过了吗？」
;.overlay	or_kei00a.png * *
;.screen	scl_morning01.png scl_morning01.png scl_morning01.png
;.stage	st_kei11b01-.png 0 0 bg_scl002a01_00_f.png 0 0 bg_scl002a01_00_n.png 0
;.effect	WScroll2 * 60 -2
;（夏のスクロ～ル用背景ある場合には注意して。あんど，もいっこ前から歩きスクロ～ルを？）
.message	420			新藤一如既往的缓缓走在一边。
.transition 0 * 40
.stage	st_kei10b01-.png 0 0 bg_scl002a01_00_f.png 0 0 bg_scl002a01_00_n.png 0
.message	430	kei-202_01-0017	丂宨丂	「还是指在堤前辈的电影中出演的事情吗？」
.message	440		嫗丂夘	「当然」
.transition 0 * 40
.stage	st_kei11b03-.png 0 0 bg_scl002a01_00_f.png 0 0 bg_scl002a01_00_n.png 0
;（景の視線，注意して。そらさせる必要はない？）
.message	450	kei-202_01-0019	丂宨丂	「白痴吗」
.message	460			哎呀，一刀两断。
.message	470			虽然昨天也是这么说的。
.transition 0 * 40
.stage	st_kei10b04-.png 0 0 bg_scl002a01_00_f.png 0 0 bg_scl002a01_00_n.png 0
.message	480	kei-202_01-0021	丂宨丂	「非得让我陪着摄影研究部，到底有什么意思嘛」
.message	490		嫗丂夘	「啊，我没说过吗。我，不是摄影研究部的哦」


;■御影チェック
;.effect *
.effect end


.overlay	* * *
.screen	* * *
.screen sc_morning01.png sc_morning01.png
.overlay * or_kei00a.png

;■御影チェック
;■　フェ～ドエンドからの復帰であることと。
;■　「え？」と，ピタっと止まる感じだし，ちょい早く
;.transition 1 fadeSide.png 20
.transition 1 fadeSide.png 40

.stage	* bgs_normal002a01_00.png 0 0 st_kei04b06.png 400
;.stage	* bgs_normal002a01_00.png 0 0 st_kei04b05.png 400
;（フェ～ドのさせ方，注意して。普通に通常フェ～ドで？）
;（背景は019が妥当なのかもしれませんが，あえてこれで）
;（景の表情にも注意して）
.message	500	kei-202_01-0023	丂宨丂	「嗯……？」
.message	510			新藤吃惊的站住了脚步。
.message	520		嫗丂夘	「我已经退部了啦，在今年早春」
.message	530		嫗丂夘	「和你一样哦」
.transition 0 * 40
.stage	* bgs_normal002a01_00.png 0 0 st_kei04b05.png 400
.message	540			虽然我对她笑着，新藤也只是用怀疑的目光看着我而已。
.message	550			虽然没奢望会马上取得信任，但看起来是相当戒备啊。
.message	560		嫗丂夘	「顺带一提，我也差不多比较了解你的事情……」
.message	570		嫗丂夘	「虽然昨天也问过，你对我了解多少？」
.message	580			想要取得信任当然要从让她了解我开始。
;■悩み
.overlay * *
.screen * *
.overlay	or_kei00a.png * *
.screen	sc_morning01.png sc_morning01.png sc_morning01.png
;.screen	scl_morning01.png scl_morning01.png scl_morning01.png
.stage	st_kei11b04-.png 0 0 bg_scl002a01_00_f.png 0 0 bg_scl002a01_00_n.png 0
.effect	WScroll2 * 60 -2
;（表情には気をつけて）
.message	590	kei-202_01-0025	丂宨丂	「……了解多少」
.message	600			新藤一边再次迈起脚步，一边慢慢想着。
;■無表情
.transition 0 * 40
.stage	st_kei11b01-.png 0 0 bg_scl002a01_00_f.png 0 0 bg_scl002a01_00_n.png 0
.message	610	kei-202_01-0027	丂宨丂	「偶尔，会来拍摄篮球部比赛的摄影研究部的人」
.transition 0 * 40
.stage	st_kei10b01-.png 0 0 bg_scl002a01_00_f.png 0 0 bg_scl002a01_00_n.png 0
.message	620	kei-202_01-0029	丂宨丂	「在女生中很有人气也知道」
.transition 0 * 40
.stage	st_kei10b05-.png 0 0 bg_scl002a01_00_f.png 0 0 bg_scl002a01_00_n.png 0
;（表情変える必要はない？）
.message	630			说到这新藤脸色上稍微浮出一丝讨厌的感觉。
.message	640			大概是听说了关于我的一些不怎样的事情吧。
.message	650		嫗丂夘	「虽然关于这点我也有很多想要解释……还是以后再说吧。别的呢？」
.transition 0 * 40
.stage	st_kei11b01-.png 0 0 bg_scl002a01_00_f.png 0 0 bg_scl002a01_00_n.png 0
;☆（ここの表情は注意。専用の表情をつくってもらうくらいの気構えで）
.message	660	kei-202_01-0031	丂宨丂	「还有……」
.message	670			一瞬，新藤把目光移向远方。
.message	680			对，就是这个目光。
.message	690			从心底我想要拍摄的愿望的来由就是──
;■視線逸らし，気落ち気味。
.transition 0 * 40
.stage	st_kei11b04-.png 0 0 bg_scl002a01_00_f.png 0 0 bg_scl002a01_00_n.png 0
.message	700	kei-202_01-0033	丂宨丂	「广野前辈的朋友……对吧」
.message	710		嫗丂夘	「算是吧」
.message	720			实际身份是少女漫画家的一个大混蛋。
.message	730			不和身为死党的我谈一句，就退学了的男人。
.message	740			同时，也是眼前这位少女一心一意钟情着的人。
.message	750			广野纮的朋友──就目前来说，这就应该是她对我的认识的全部了吧。
.message	760		嫗丂夘	「嗯，虽然你列举的都没错……但现在那些都无所谓」
.message	770		嫗丂夘	「我只是，想拍摄你而已」
.message	780		嫗丂夘	「是不是摄影研究部的人，是不是广野的朋友之类，全部都无所谓」
.message	790			当然，我是认真的。
.message	800			开玩笑说想要去拍谁的事情，我从没有作过。
.message	810			但是，新藤却并不了解这些，她仍只是不愉快地张开了嘴唇。
;■睨み
.transition 0 * 40
.stage	st_kei10b05-.png 0 0 bg_scl002a01_00_f.png 0 0 bg_scl002a01_00_n.png 0
;.stage	st_kei10b04-.png 0 0 bg_scl002a01_00_f.png 0 0 bg_scl002a01_00_n.png 0
;（表情注意）
.message	820	kei-202_01-0035	丂宨丂	「真搞不懂你」
.panel 0


;■御影チェック
;.effect *
.effect end

.overlay	* * *
.screen	* * *
.playBGM *
.transition 0 * 10
.stage	* WHITE.png 0 0


;■背景：教室（夏，１２時
;■　　　　堤京介　　：制服（夏）
;■　　　　宫村宫子：制服（夏）
.transition 1 fadeSide.png 10
.stage	* ev02_022f01_mugai.png 0 0
;.stage	* bgs_sch004m01_01.png 0 0
;（切り出ししかないか……）
.panel 1
.message	830			从小时就做什么都很棒。
.message	840			虽然对于细致的事情有些不太拿手，但学习和运动，还有和人之间的交往都还不错。
.message	850			倒也不是有特别努力。
.message	860			跟别人说也只会惹人厌而已，但自己确实是不做什么特别的努力就可以作到大部分的事情。
.message	870			自己也觉得有些不可思议。
.message	880			但是，大概是大部分的事情都能轻松解决的原因吧。
.message	890			总觉得生活中有一些不足……。
.message	900	etc-202_01-0009	愭丂惗	「那么，这个问题……宫村，你来回答」
.transition 0 * 20
.stage	* ev02_022a01_mugai.png 0 0
.message	910	miy-202_01-0003	傒傗偙	「是～」
.message	920			宫村玩笑地回答着，站了起来。
.transition 0 * 20
.stage	* ev02_022b01.png 0 0
.message	930			轻快的走到黑板前，我正以为她会考虑几秒时。
.message	940	miy-202_01-0005	傒傗偙	「呃～嗯」
.transition 0 * 40
.stage	* ev02_022c01.png 0 0
;（フェ～ドスピ～ドは注意して）
.message	950			粉笔便已经随着轻快的声音滑动起来。
.message	960	miy-202_01-0007	傒傗偙	「先分解这个因数，然后把共通因数……」
.message	970			虽然是极具难度的问题，但宫村也毫无迷惑的作出了解答。
.message	980			我也慢慢地用圆珠笔计算。
.message	990			然后过了几分钟──
.transition 0 * 40
.stage	* ev02_022d01.png 0 0
.message	1000	miy-202_01-0009	傒傗偙	「完成了！」
.message	1010			宫村呵呵的笑着，扭头看向老师。
.message	1020	etc-202_01-0011	愭丂惗	「嗯，正确。真不错啊，宫村」
.message	1030	miy-202_01-0011	傒傗偙	「嗯嗯，真不错吧」
.message	1040			宫村的玩笑让教室内顿时笑声一片。
.message	1050			我看向手中的笔记，确认自己得出的答案和宫村的答案是否一致。
.message	1060			不过，宫村却比我要稍快那么一点。
.message	1070			那家伙又是如何呢。
.message	1080			宫村她是努力着，才取得了那么高的成绩吗……。
.message	1090	etc-202_01-0013	愭丂惗	「那么，下一个问题……佐佐木」
.transition 0 * 20
.stage	* ev02_022e01.png 0 0
;（この画像の挿入タイミング，注意して。もう少し後？）
.message	1100	miy-202_01-0013	傒傗偙	「加油哦，小佐木」
.message	1110			宫村对被点名的女同学轻声地送过声援。
.message	1120	etc-202_01-0014		佐佐木也露出明快的笑容，向宫村轻轻挥了下手然后走向黑板。
.message	1130			不管怎么说，宫村比起以前确实改变了。
.message	1140			而且，从此之后也会继续改变下去的吧。
.panel 0
.transition 0 * 10
.stage	* WHITE.png 0 0


;■シ～ン転換
.playSE AT_chime.ogg f 0 *
.playBGM efBGM010.ogg
.transition 1 fadeSide.png 10
.stage	* ev02_013a01.png 0 0
;.stage	* bgs_sch004m01_01.png 0 0
;（休み時間の夏モブはないのか……。さらにここ，201で使ったＣＧを使って再利用してもいいやも）
.panel 1
.message	1150			铛～叮～铛～咚～。
.message	1160			啊～，结束了结束了。
.message	1170			终于到午休时间了。
.transition 0 * 40
.stage	* ev02_013b01.png 0 0
.message	1180	miy-202_01-0015	傒傗偙	「那么，堤堤」
.transition 0 * 20
.stage	* bgs_sch004m02_01.png 0 0 st_miyako01b01.png 350
;（インのタイミングには注意して。宫子の表情にも注意）
.message	1190		嫗丂夘	「哇」
.message	1200			宫村宫子突然出现在课桌前。
;■無表情。どうでもよさそうに。
.transition 0 * 40
.stage	* bgs_sch004m02_01.png 0 0 st_miyako01b05.png 350
.message	1210	miy-202_01-0017	傒傗偙	「啊，首先不是让你跑腿的」
.message	1220		嫗丂夘	「首先！？」
.transition 0 * 40
.stage	* bgs_sch004m02_01.png 0 0 st_miyako01b01.png 350
.message	1230	miy-202_01-0019	傒傗偙	「嗯，首先有点话要跟你谈」
;■笑顔
.transition 0 * 40
.stage	* bgs_sch004m02_01.png 0 0 st_miyako00b02.png 350
.message	1240	miy-202_01-0021	傒傗偙	「买果汁在此之后。不会把堤堤当废物踢开的放心啦」
.message	1250		嫗丂夘	「是吗……」
.message	1260			请您还是把我扔了吧。
.transition 0 * 40
.stage	* bgs_sch004m02_01.png 0 0 st_miyako00b04.png 350
.message	1270	miy-202_01-0023	傒傗偙	「啊，有话说并不意味着会发生告白之类酸酸甜甜的剧情哦」
;■威張り
.transition 0 * 40
.stage	* bgs_sch004m02_01.png 0 0 st_miyako00b03.png 350
;（表情は注意して）
.message	1280	miy-202_01-0025	傒傗偙	「我呢，是纮君专用的哦」
.message	1290		嫗丂夘	「那种事情我没抱半点期待……话说回来，专用的啊你」
.transition 0 * 40
.stage	* bgs_sch004m02_01.png 0 0 st_miyako08b02.png 410
.message	1300	miy-202_01-0027	傒傗偙	「实际啊，刚才的课有些不太明白的地方呢」
.message	1310			完全都没有听我说话。
.message	1320		嫗丂夘	「那样的话，就去问老师啊」
.transition 0 * 40
.stage	* bgs_sch004m02_01.png 0 0 st_miyako07b02.png 410
.message	1330	miy-202_01-0029	傒傗偙	「老师不也要午休的吗。打扰的话多不好啦」
.message	1340		嫗丂夘	「我也有午饭要吃啊……打扰我没什么不好吗？」
.transition 0 * 40
.stage	* bgs_sch004m02_01.png 0 0 st_miyako02b01.png 350
;.stage	* bgs_sch004m02_01.png 0 0 st_miyako07b01.png 410
.message	1350	miy-202_01-0031	傒傗偙	「我一点都不介意哦<音乐符号>」
.message	1360		嫗丂夘	「…………」
.message	1370			稍微也关心一下我好吧。
.message	1380		嫗丂夘	「说起来，宫村你不明白的我也不可能明白啊」
.message	1390		嫗丂夘	「你，期中测试时不还得到了全级第一的么。我也不过只是第三而已」
.message	1400			对，自从这个宫村宫子在二年级的第三学期开始认真的上课。
.message	1410			本来就十分优秀，总在年级前十以内的成绩便再次上升，以至于瞬间到达顶点。
.transition 0 * 40
.stage	* bgs_sch004m02_01.png 0 0 st_miyako07b03.png 410
.message	1420	miy-202_01-0033	傒傗偙	「嗯～，第三名也会有相应于第三名的考虑方式嘛」
.message	1430			少提那第三名。
.message	1440		嫗丂夘	「抱歉，我还有事。问别人去吧」
.message	1450		嫗丂夘	「果汁也请自己去买」
.message	1460			我说着站起身来。
.transition 0 * 40
.stage	* bgs_sch004m02_01.png 0 0 st_miyako08b01.png 410
.message	1470	miy-202_01-0035	傒傗偙	「哼～……还真强硬诶。有事是什么事？」
.message	1480		嫗丂夘	「撒手不管绝对行不通。就算努力也不一定就会有成果」
.transition 0 * 40
.stage	* bgs_sch004m02_01.png 0 0 st_miyako08b02.png 410
.message	1490	miy-202_01-0037	傒傗偙	「嗯？」
.message	1500		嫗丂夘	「世间就是有这种有趣的事哦」
.message	1510			无论如何都不满足的我所知道的唯一乐趣。
.message	1520			就是拍摄电影。
.message	1530			为了能够更加的有趣──我需要那个女孩。
.playSE *


;■背景：学園·廊下（夏，１３時
;■　　　　堤京介：制服（夏）


;■御影チェック
;■　早いな。画面切り替えてから鳴るように
;.playSE chime_yobidashi.ogg f 0 *

.transition 1 fadeSide.png 20
.stage	* bgs_sch002m01_01.png 0 0

;■御影チェック
.playSE chime_yobidashi.ogg f 0 *

;（ダイレクトに前から繋げてますが，おかしいようなら白を挿むこと）
.message	1540			铛～叮～铛～咚～。
.message	1550			在我前往二年级教室的途中，一个傻呼呼的声音突然在校园内回响起来。
.message	1560		嫗丂夘	「お？」
;■御影チェック
;.message	1570	etc-202_01-0015	丂惡丂	「２年Ｄ組の新藤景さん。繰り返します，２年Ｄ組の新藤景さん。浅黄先生がお呼びです。至急，職員室まで来てください」
.message	1570	etc-202_01-0015	丂惡丂	『二年D班的新藤景同学。重复一遍，二年D班的新藤景同学。浅黄老师在找你。请迅速到教师办公室来』
.message	1580		嫗丂夘	「……怎么？」
.message	1590			被校内广播点名之类，肯定是作了什么过分的坏事没错。
.message	1600			省点事不用广播，直接去喊不就得了嘛。
.message	1610			总之，新藤被点名，这个决不能无视。
.message	1620			前进方向变更。
.panel 0
.playBGM *
.playSE *
.transition 0 * 10
.stage	* WHITE.png 0 0


;■シ～ン転換
;■背景：学園·廊下（夏，１３時
;■　　　　堤京介：制服（夏）
;■　　　　新藤景：制服（夏）
;■白バック
.transition 1 fadeSide.png 10
.stage	* ev02_023.png 0 0
.panel 1
.message	1630	kei-202_01-0037	丂宨丂	「那就先行告辞了」
.message	1640		嫗丂夘	「告～辞」
.message	1650			既然在新藤眼前，总之低一下头，随即便走出了教师办公室。

;■階段
.playBGM efBGM042.ogg
;（これと010を差し替えてもいいのやも）
.transition 1 fadeSide.png 20
.stage	* bgc_sch003a01_01.png 0 0
;（モブ入れる？）
.message	1660		嫗丂夘	「呼呼，肩膀都快凝固了啊」
.transition 0 * 20
.stage	* bgc_sch003a01_01.png 0 0 st_kei06b01.png 400
.message	1670	kei-202_01-0039	丂宨丂	「比起这个……为什么前辈也来了？」
.message	1680		嫗丂夘	「你一个人肯定瞒不过去的吧？」
.transition 0 * 40
.stage	* bgc_sch003a01_01.png 0 0 st_kei07b01.png 400
.message	1690	kei-202_01-0041	丂宨丂	「呜」
.message	1700			瞬间，新藤便没了话说。
.message	1710			被点名的理由十分单纯。
.message	1720			简单的说，也就是昨天新藤的暴行传到了老师的耳朵里的样子。
.message	1730		嫗丂夘	「嘛，在校内堂而皇之地做那种事，必然会被点名的吧」
.transition 0 * 40
.stage	* bgc_sch003a01_01.png 0 0 st_kei06b05.png 400
.message	1740	kei-202_01-0043	丂宨丂	「也不想一下原因到底出在谁身上！？」
.message	1750		嫗丂夘	「是啊，是谁呢～」
.message	1760			为什么我倒没有被点名。
.message	1770			难道是向老师打小报告的家伙不知道我的名字吗……。
.message	1780			这种时候，我的运气还真不错啊～。
.message	1790		嫗丂夘	「你有时运气还真是背啊」
;■イヤミっぽく
.transition 0 * 40
.stage	* bgc_sch003a01_01.png 0 0 st_kei06b01.png 400
.message	1800	kei-202_01-0045	丂宨丂	「只能说前辈您的恶运很强而已」
.transition 0 * 40
.stage	* bgc_sch003a01_01.png 0 0 st_kei06b05.png 400
;（表情注意して。変える必要はない？）
.message	1810	kei-202_01-0047	丂宨丂	「而且还用那种明知故犯的表情拉拢先生。真让人不可置信」
.message	1820			我仅仅是稍稍开个玩笑而已──，那借口我自己都觉得行不通，但结果却ALL　RIGHT。
.message	1830		嫗丂夘	「再怎么说我也是优等生嘛。对成绩比较好的学生，就算是老师也不会说什么太严厉的话的啦」
;(ここで06b05を？）
.message	1840	kei-202_01-0049	丂宨丂	「您的隐意是指我的成绩很差是吧？」
.message	1850		嫗丂夘	「怎么可能嘛。我仅仅是说我自己的成绩而已哦」
;（ここ，ポ～ズ変えさせる？）
.message	1860	kei-202_01-0051	丂宨丂	「这谈话还真是越来越让人不舒服……」
.message	1870			新藤她看起来完全没有认同的意思。
.message	1880		嫗丂夘	「既然无事平息不就OK了嘛」
.message	1890			我啪啪地拍着新藤的肩。
.transition 0 * 40
.stage	* bgc_sch003a01_01.png 0 0 st_kei01b06.png 380
;.stage	* bgc_sch003a01_01.png 0 0 st_kei01b03.png 380
;（ここ，01b06を？もしくは05b07を？しかしこれは，パタ～ン作りすぎか，，，）
.message	1900	kei-202_01-0053	丂宨丂	「喂喂，不要随便碰我好吧！」
.message	1910		嫗丂夘	「那我就认真的碰你好了」
.message	1920	kei-202_01-0055	丂宨丂	「不是你抱什么心情的问题！」
.message	1930			还真是要求多啊的女孩啊。
.transition 0 * 40
.stage	* bgc_sch003a01_01.png 0 0 st_kei08b01.png 400
;☆（背中向かせていいか，注意して。さらに，階段と位置を合わせるように）
.message	1940		嫗丂夘	「嗯，要去哪？」
.message	1950			那方向不是新藤教室的方向。
;■睨み
.transition 0 * 40
.stage	* bgc_sch003a01_01.png 0 0 st_kei04b04.png 400
;（この後，また後ろ向かせる？）
.message	1960	kei-202_01-0057	丂宨丂	「去哪都无所谓吧」
.message	1970		嫗丂夘	「那倒也是」
.message	1980			嗯，去哪都无所谓。
.message	1990			对于我来说，只要新藤在，哪里都完全不是问题。
.panel 0
.playBGM *
.transition 0 * 10
.stage	* WHITE.png 0 0


;■体育館
.playSE AT_chime.ogg f 0 *
.transition 1 fadeSide.png 10
.stage	* ev02_024a01.png 0 0
.panel 1
.message	2000			铛～叮～铛～咚～。
.transition 0 * 20
.stage	* ev02_024b01.png 0 0
;（バスケやバドミントンやってるのがピンポイントで残ってるな…）
.message	2010			随着响起的预备铃，喜欢玩篮球和羽毛球的学生们也逐渐地散去。
.transition 0 * 20
.stage	* ev02_024c01.png 0 0
;（もしかしたらa差分は使わない方向でいったほうがいいのかもしれんが……ちょっと保留）
.message	2020			就算如此新藤也一动不动，在体育馆的一角如同雕像一样呆滞着。
.message	2030			那凝视着不同的地方的视线，稍微有些可怕的感觉。
.message	2040		嫗丂夘	「午休，已经结束了哦」
;■無表情
.transition 0 * 20
.stage	* ev02_025a01.png 0 0
;（インのタイミング，注意して）
.message	2050	kei-202_01-0059	丂宨丂	「我知道的」
.message	2060		嫗丂夘	「午饭也没有吃的吧？」
.message	2070	kei-202_01-0061	丂宨丂	「没有食欲」
.message	2080		嫗丂夘	「是吗」
.message	2090			虽然我也稍微有些饿了，但这时需要忍耐。
.transition 0 * 40
.stage	* ev02_025a02.png 0 0
.message	2100	kei-202_01-0063	丂宨丂	「……比起这个，已经开始上课了哦」
.transition 0 * 40
.stage	* ev02_025a03.png 0 0
.message	2110		嫗丂夘	「我知道」
.message	2120	kei-202_01-0065	丂宨丂	「不去吗？」
.message	2130		嫗丂夘	「不无所谓吗？　就算没我课程一样会开始」
.message	2140	kei-202_01-0067	丂宨丂	「这不是废话嘛」
.message	2150			说着，新藤又沉默了下去。
.message	2160			一边听着不知从哪传来的蝉鸣，我看向新藤的脸。
.message	2170			她有着给人自傲感的吊眼角，紧绷着的粉唇。
.message	2180			但是，凛然的脸上却完全没有一丝表情。
.message	2190			正式上课铃声已然响起，但新藤仍然站在那里。
.message	2200	kei-202_01-0069	丂宨丂	「就在不久之前──还从来没有想过自己会逃课」
.message	2210			新藤缓缓张开嘴唇。
.message	2220	kei-202_01-0071	丂宨丂	「但现在却好象理所当然的做着。分明之前还会因为别人逃课而生气来着」
.transition 0 * 40
.stage	* ev02_025b01.png 0 0
;（この差分の使用タイミング，注意して）
.message	2230		嫗丂夘	「我也一样啊。并不是我认真，而且没有什么特别逃课的必要而已」
.message	2240			新藤用稍微有些意外的表情看着我。
.message	2250			我微微一笑，
.message	2260		嫗丂夘	「最近呢，在老师发觉不到的范围内偶尔逃下」
.transition 0 * 40
.stage	* ev02_025c01.png 0 0
.message	2270		嫗丂夘	「铛铛」
.message	2280			我取出摄影机，不按录像键而把镜头对向新藤。
;■呆れ
.message	2290	kei-202_01-0073	丂宨丂	「那东西从哪拿出来的啊」
.message	2300		嫗丂夘	「为了追求美丽的画面，要四处追求的嘛」
.transition 0 * 40
.stage	* ev02_025c02.png 0 0
.message	2310	kei-202_01-0075	丂宨丂	「白痴一样」
.message	2320			毫不留情的一句话，让我苦笑起来。
.transition 0 * 40
.stage	* ev02_025c03.png 0 0
;（この一歩手前からインせたい場合は，景の表情に注意して）
.message	2330		嫗丂夘	「自己有时也会这么想──但果然这样做没有错」
.message	2340		嫗丂夘	「因为，我发现了你」
.message	2350	kei-202_01-0077	丂宨丂	「…………哼」
.transition 0 * 40
.stage	* ev02_025c04.png 0 0
;（京介の表情，注意して）
.message	2360		嫗丂夘	「那时没拿摄影机啊。可恶啊，真的是可惜啊」
.message	2370	kei-202_01-0079	丂宨丂	「那时？」
.message	2380		嫗丂夘	「嗯，那时在体育馆中站着的你的身姿……只能用如神一般来形象啊」
.transition 0 * 40
.stage	* ev02_025c05.png 0 0
.message	2390	kei-202_01-0081	丂宨丂	「你，你还真能随便就说出这么不害臊的话啊」
.transition 0 * 40
.stage	* ev02_025c06.png 0 0
.message	2400		嫗丂夘	「事实嘛」
.message	2410	kei-202_01-0083	丂宨丂	「白痴，真的是个白痴」
;（ここ，視線そらさせる？その場合は，京介の表情に注意して）
.message	2420			新藤在一瞬看了一眼摄影机的透镜，然后又别过脸去。
.message	2430			看来这次没有想要否定在体育馆发生的事情的意思。
.transition 0 * 40
.stage	* ev02_025c07.png 0 0
.message	2440	kei-202_01-0085	丂宨丂	「……前辈你」
.message	2450	kei-202_01-0087	丂宨丂	「说了，自己退出了摄影研究部是吧」
.message	2460		嫗丂夘	「嗯？　啊啊」
.message	2470	kei-202_01-0089	丂宨丂	「我问个问题可以吗？」
.message	2480		嫗丂夘	「当然，问什么都行」
.transition 0 * 40
.stage	* ev02_025c08.png 0 0
.message	2490	kei-202_01-0091	丂宨丂	「为什么要……放弃部团活动呢？」
.transition 0 * 40
.stage	* ev02_025d01.png 0 0
;（インのタイミング，フェ～ドスピ～ドには注意して）
.message	2500			我放下拿着摄影机的手，稍微选了一下该说的话。
.message	2510		嫗丂夘	「嘛……」
.message	2520		嫗丂夘	「说是放弃，还不如说是被赶出来的吧」
.transition 0 * 40
.stage	* ev02_025d02.png 0 0
.message	2530	kei-202_01-0093	丂宨丂	「那是前辈你自己的被害妄想吧？」
.message	2540		嫗丂夘	「这真又是毫不留情的话」
.transition 0 * 40
.stage	* ev02_025d03.png 0 0
;（京介と景の表情，注意して）
.message	2550		嫗丂夘	「不过嘛，一半意义上也确实如此」
.transition 0 * 40
.stage	* ev02_025d04.png 0 0
;（この差分の使いどころ，注意して）
.message	2560	kei-202_01-0095	丂宨丂	「你啊……」
.message	2570		嫗丂夘	「嘛，这个就是所谓的方向不同吧。摄影研究部的人所追求的东西，和我想要拍摄的东西有所不同，嗯」
.message	2580			摄影研究部的人所追求的，是“在比赛中能够取得高名次的作品”。
.message	2590			自己所作出的成果想要被认同也是理所当然。
.message	2600			就算是文化部，如果有好的成绩得到的预算也会有所不同。
.message	2610			理解这个的话，就不会再去说他们的不是。
.transition 0 * 40
.stage	* ev02_025b01.png 0 0
;（京介の表情，景の表情には気をつけて。京介を上向かせる必要はない？）
.message	2620		嫗丂夘	「没办法的啊。他们并没有错，当然我也没有」
.message	2630		嫗丂夘	「我在现场的话只会造成困扰，不想让我在也是当然的吧」
.message	2640			对于我来说，只要一个镜头──不，一个分镜就可以。
.message	2650			拍出那种能够震撼人心的，真正美丽的画面。
.message	2660			我所追求的仅此而已，他人的评价都是次要的了。
.message	2670	kei-202_01-0097	丂宨丂	「堤前辈你……这样就好吗？」
.transition 0 * 40
.stage	* ev02_025d01.png 0 0
;（景の表情には気をつけて）
.message	2680		嫗丂夘	「是否如此，关键在于你。因为如果继续待在摄影研究部的话，就不会想倒会去拍你的电影了吧」
.transition 0 * 40
.stage	* ev02_025d02.png 0 0
;（景の表情，京介の表情には気をつけて。d04表情でも？）
.message	2690	kei-202_01-0099	丂宨丂	「最后，还是转到了这边吗……」
.message	2700			也不必那么讨厌吧，真是顽固的女生啊。
.transition 0 * 40
.stage	* ev02_025a01.png 0 0
;（景の顔をそらさせていいか注意して。二人の表情にも注意）
.message	2710	kei-202_01-0101	丂宨丂	「完全不明白你为什么想要拍我……」
.transition 0 * 40
.stage	* ev02_025a02.png 0 0
;（景の目，つむらせてもいいか？）
.message	2720	kei-202_01-0103	丂宨丂	「对你来说都已经是三年级的夏天了，集中考试复习不就好了嘛。电影之类，升学之后不也可以拍吗」
.message	2730			我缓缓的摇了下头。
.message	2740		嫗丂夘	「并非如此」
.message	2750		嫗丂夘	「我认为有除了现在就无法拍摄的一瞬存在。如果一次让它逃走，就再也无法取回，那样的一瞬」
.transition 0 * 40
.stage	* ev02_025d03.png 0 0
;（「わずかに目を見開き」，，，表情には注意して）
.message	2760	kei-202_01-0105	丂宨丂	「再也无法取回……」
.message	2770			新藤稍稍睁开眼睛，注视着我。
.message	2780		嫗丂夘	「我想要拍你的电影。我只是跟着自己的心情走而已」
.message	2790	kei-202_01-0107	丂宨丂	「……前辈你，能够抓到那个一瞬吗？」
.message	2800		嫗丂夘	「虽然现在说不清，但想要抓到的意志是最重要的吧」
.message	2810		嫗丂夘	「就因如此，我才会来拜托你」
.message	2820			仅仅等待的话不可能拍到什么美丽的画面。
.message	2830			要踏出自己的双脚去寻找，就算是强行也要做下去。
.message	2840		嫗丂夘	「而且呢」
.message	2850	kei-202_01-0109	丂宨丂	「而且？」
.transition 0 * 40
.stage	* ev02_025d01.png 0 0
;（ここまでの景と京介の表情には注意して）
.message	2860		嫗丂夘	「不拍电影的我，就不是我了啊」
.panel 0
.playSE *
.transition 0 * 10
.stage	* WHITE.png 0 0


;■背景：教会前（夏，１６時
;■　　　　堤京介　：制服（夏）
;■　　　　雨宫优子：私服（夏）
.HSVfilter 0 0 0 0 5 -5
.overlay * or_yuko02a.png
.playBGM efBGM017_2.ogg
.transition 1 fadeSide.png 10
.stage	* bgc_normal012a01_02.png 0 600 st_yuko02f02.png 370
;（优子の表情，気をつけて。02g07でも？立ち絵を配置して，スクロ～ルさせる？）
.panel 1
.message	2870	yuk-202_01-0003	桪丂巕	「这还真是又说了很酷的话呢」
.message	2880		嫗丂夘	「我可是一直都很酷的……」
.message	2890	yuk-202_01-0005	桪丂巕	「初次听说哦」
;☆（礼拝堂の中……なのか？教会前とは大きく違うので，注意して）
.message	2900			在这热气环绕的礼拜堂里，雨宫优子清爽地说着。
.message	2910			不知是有什么信念还是其他，世界已分明要接近真正入夏了，她不知为何却仍然穿着长袖。
.message	2920			虽然看起来完全是修女风的衣服，但好象却并非是教会的相关人员。
.message	2930			毫不留情的话也好，服装也好，雨宫总让我有种她脱离尘世的感觉……。
.transition 0 * 40
.stage	* bgc_normal012a01_02.png 0 600 st_yuko02f03.png 370
.message	2940	yuk-202_01-0007	桪丂巕	「不过，还真是奇怪的主意呢。仅仅用一个女孩子去拍电影，从来都没有听说过呢」
.message	2950		嫗丂夘	「也并不是什么新奇的手法啊」
.message	2960		嫗丂夘	「嘛，正好的啦。对于普通的摄影早已厌倦了」
.transition 0 * 40
.stage	* bgc_normal012a01_02.png 0 600 st_yuko02f04.png 370
.message	2970	yuk-202_01-0009	桪丂巕	「总觉得你有白努力的味道……」
.message	2980			啊啊，完全被她震撼到了。
.message	2990			正如广野所言，会被不良社会人雨宫当成傻瓜的确难以接受啊。
.transition 0 * 40
.stage	* bgc_normal012a01_02.png 0 600 st_yuko03f01.png 400
.message	3000	yuk-202_01-0011	桪丂巕	「你还真是奇怪哦。不愧是广野先生的朋友呢」
.message	3010		嫗丂夘	「被和广野当成同类的话，稍微有点那啥了吧」
.transition 0 * 40
.stage	* bgc_normal012a01_02.png 0 600 st_yuko03f02.png 400
.message	3020	yuk-202_01-0013	桪丂巕	「是同类哦。你和广野先生很像的，表面上的暂且不提嗯」
.message	3030		嫗丂夘	「是吗……？」
.message	3040			完全想不出。
.message	3050			那种乖僻的家伙，和一直直面胜负的我哪里像了？
.message	3060	yuk-202_01-0015	桪丂巕	「说的更准确些，是和宫子交往前的广野先生吧」
.message	3070		嫗丂夘	「少提童贞时好吧」
;■呆れ
.transition 0 * 40
.stage	* bgc_normal012a01_02.png 0 600 st_yuko03f03.png 400
;（表情，注意して）
.message	3080	yuk-202_01-0017	桪丂巕	「你的脑中总是堆满那类想法的吗？」
.message	3090		嫗丂夘	「你的脑中也差不多该被我的事情塞满了吧？」
.transition 0 * 40
.stage	* bgc_normal012a01_02.png 0 600 st_yuko01f03.png 370
;.stage	* bgc_normal012a01_02.png 0 600 st_yuko03f02.png 400
;（ポ～ズも変える？）
.message	3100	yuk-202_01-0019	桪丂巕	「就现在而言，还完全没有这个预定哦」
.message	3110			满面笑容的全力拒绝啊。
.message	3120			唔～，想要击落这个雨宫优子果然是件难事啊。
.message	3130			虽然过分美丽反而拍摄起来会不好看，但做女朋友决不会有所遗憾。
.transition 0 * 40
.stage	* bgc_normal012a01_02.png 0 600 st_yuko01f01.png 370
;.stage	* bgc_normal012a01_02.png 0 600 st_yuko04f01.png 400
.message	3140	yuk-202_01-0021	桪丂巕	「然，那女孩接受了吗？」
.message	3150		嫗丂夘	「是啊，怎样呢？我也不明白啊」
.transition 0 * 40
.stage	* bgc_normal012a01_02.png 0 600 st_yuko01f02.png 370
;.stage	* bgc_normal012a01_02.png 0 600 st_yuko04f02.png 400
.message	3160	yuk-202_01-0023	桪丂巕	「不过，该说的话已经全部都说了不是吗？」
.message	3170		嫗丂夘	「是啊，该出的牌全都扔出去了。接下来就只有等待她的判断而已了」
.message	3180			新藤看了那个的话，她的反应应该会有所改变──当然这只是希望。
.transition 0 * 40
.stage	* bgc_normal012a01_02.png 0 600 st_yuko07f02.png 400
;（ポ～ズを反転させていいものか，注意して）
.message	3190	yuk-202_01-0025	桪丂巕	「那么，我就为你祈祷吧。祈祷你的话能够传达到她的心房」
.message	3200			雨宫露出和刚才稍有不同感的成熟的笑容。
.message	3210			看到这副表情──就有了相信这个女孩比我年纪大的感觉。
;■笑顔（意地悪く）
.transition 0 * 40
.stage	* bgc_normal012a01_02.png 0 600 st_yuko03f02.png 400
;.stage	* bgc_normal012a01_02.png 0 600 st_yuko07f01.png 400
.message	3220	yuk-202_01-0027	桪丂巕	「因为只是祈祷的话免费的哦」
.message	3230		嫗丂夘	「…………」
.message	3240			如果她不是这种说话多余型的话，我就会全力搭讪她了吧。
.panel 0
.HSVfilter 0 0 0 0 0 0
.overlay * *
.playBGM *
.transition 0 * 10
.stage	* WHITE.png 0 0


;■ここより景視点
;■背景：景自室（夏，２２時
;■　　　　新藤景：私服（夏）
;.transition 0 * 10
;.stage	vista_window.png WHITE.png 0 0
.playBGM efBGM047.ogg
;.playBGM BGM054_sample2.ogg
;（ここは無音でも良い？）
;.transition 14 * 12
.transition 14 * 12
.stage	vista_window.png ev02_026.png 0 0
.panel 3
;.panel 1
.message	3250	kei-202_01-1003		那个叫做堤的前辈，真是让人搞不明白。
.message	3260	kei-202_01-1005		想用既不是摄影研究部，又完全没有演戏的经验的我去拍电影，怎么想都是在说笑。
.transition 0 * 100
.stage	vista_window.png ev02_026.png 0 0
.message	3270	kei-202_01-1007		说不定，根本就不是认真的吧。
;■回想，白バック？　体育館の背景をビスタにするか？
;.transition 0 * 40
;.stage	kei_window.png ev02_026.png 0 0
.panel 0
.transition 17 * 20
.stage	vista_window.png ev02_027a01_kei_a.png 0 0
.panel 3
.message	3280		嫗丂夘	『这个，是去年的电影赛上参赛的作品，你看看好了』
.message	3290	kei-202_01-0111	#丂宨丂	『根本不想看啦，那种东西』
.message	3300		嫗丂夘	『嘛也不必这么说嘛。再怎么说也算是佳作的作品嘛，也不至于那么无聊啦』
.message	3310	kei-202_01-0113	#丂宨丂	『所以我说了不要──』
.message	3320		嫗丂夘	『顺带一提摄影和导演都是我哦』
.transition 0 * 40
.stage	vista_window.png ev02_027a02_kei_a.png 0 0
;（フェ～ドスピ～ドは20でも？）
.message	3330	kei-202_01-0115	#丂宨丂	『听人说话啊你！』
;■再び，景自室
;.transition 0 * 20
;.transition 6 * 150
.panel 0
.transition 17 * 20
.stage	vista_window.png ev02_028.png 0 0
.panel 3
.message	3340	kei-202_01-1009		虽然抵抗到了最后，结果还是被强塞着收下了。
.message	3350	kei-202_01-0117	#丂宨丂	「不是说了怎样都是徒劳的嘛……」
.message	3360	kei-202_01-1011		就算看了这种东西，我的心情也不可能改变。
.transition 0 * 20
.stage	* ev02_029.png 0 0
;（表示タイミング，注意して）
.message	3370	kei-202_01-0119	#丂宨丂	「不是很普通的电影吗，这个」
.message	3380	kei-202_01-1013		总之，播放出来看一下，也并不怎么有趣。
.message	3390	kei-202_01-1015		该说是故事沉重呢，还是该说引人发困呢。
.message	3400	kei-202_01-1017		演员的演技也并不怎样，台词也读的生硬而错误百出听不清楚。
.message	3410	kei-202_01-0121	#丂宨丂	「但是……」
.message	3420	kei-202_01-1019		就算如此，为何不能停止呢。
.message	3430	kei-202_01-1021		分明对于这种沉闷而迟疑不决的故事没有兴趣的。
.message	3440	kei-202_01-1023		故事的舞台是这音羽城。
.message	3450	kei-202_01-1025		应该是看惯的风景，却让我感觉那是遥远的异世界一般。
.message	3460	kei-202_01-1027		场景顺次切替。
.message	3470	kei-202_01-1029		人，事物，以及光──
.message	3480	kei-202_01-1031		摄影的位置找不出绝妙以外的形容词。
.message	3490	kei-202_01-1033		镜头并不怎么移动。
.message	3500	kei-202_01-1035		在那固定的取景框中，光影及景色如画铺开。
.transition 0 * 20
.stage	vista_window.png ev02_029_mugai_a.png 0 0
.message	3510	kei-202_01-1037		无法把眼睛从画面移开。
.message	3520	kei-202_01-1039		就好象被魅惑了一般。
;.panel 0
.transition 1 fadeSide.png 20
.stage	kei_window.png kei_vista_a.png 0 0
;.panel 6
.message	3530		嫗丂夘	『我认为有除了现在就无法拍摄的一瞬存在』
;.panel 0
.transition 1 fadeSide.png 20
.stage	vista_window.png ev02_029_mugai_a.png 0 0
;.panel 3
.message	3540	kei-202_01-1041		那个人说出这样的话。
.message	3550	kei-202_01-1043		我也明白。
.message	3560	kei-202_01-1045		比起任何事物都要重要的，就是那叫做“现在”的时间。
.message	3570	kei-202_01-0123	#丂宨丂	「我知道的啊……」
.message	3580	kei-202_01-1047		无论再怎么后悔，时间也一去不返。
.message	3590	kei-202_01-1049		而且，只考虑以后会怎样的话，也永远无法提起勇气。
.message	3600	kei-202_01-0125	#丂宨丂	「如果说出自己的心意，无论如何目前的关系都不可能再继续下去。所以，我……什么都没有说……」
.message	3610	kei-202_01-1051		一直到这次冬天，我都恐惧着未来，现在扔被过去紧紧束缚。
;.panel 0
.transition 1 fadeSide.png 20
.stage	kei_window.png ev02_025d01_mugai02.png 0 0
;.stage	kei_window.png kei_vista_b.png 0 0
;.panel 6
.message	3620		嫗丂夘	『不拍电影的我，就不是我了啊』
;.panel 0
.transition 1 fadeSide.png 20
.stage	vista_window.png ev02_029_mugai_a.png 0 0
;.panel 3
.message	3630	kei-202_01-1053		堤前辈他就算失去了安身之处，而没有放弃自己的梦想。
.message	3640	kei-202_01-1055		追求着那无可替代的一瞬，努力着。
.message	3650	kei-202_01-1057		我又如何呢。
.message	3660	kei-202_01-1059		仅仅是去着学园，和朋友说话，玩耍──
.message	3670	kei-202_01-1061		决不会说是无聊。
.message	3680	kei-202_01-1063		但是，却和什么都没做一样。
.message	3690	kei-202_01-1065		──我一直不知道。
.message	3700	kei-202_01-1067		什么都不做会是这样引人疲累的事情，我一直都不知道。
.message	3710	kei-202_01-1069		眼睛仍然看着画面。
.transition 0 * 20
.stage	* ev02_030_mugai_b.png 0 0
;.stage	vista_window.png ev02_030_mugai_a.png 0 0
;（前の地文の「画面」がどこを指すかで表示タイミングが変わってくるので注意して）
.message	3720	kei-202_01-1071		把手伸向电脑键盘。
.transition 0 * 20
.stage	* ev02_030.png 0 0
.message	3730	kei-202_01-1073		呐，你觉得我怎么做才好呢？
.message	3740	kei-202_01-1075		我问向不在这里的那个女孩。
.message	3750	kei-202_01-1077		当然，不可能得到答案。
.transition 0 * 10
;.transition 1 fadeSide.png 10
.stage	past_window.png ev02_030.png 0 0
.message	3760	kei-202_01-1079		答案──已经在我的心中，我感觉到了。
;.transition 1 fadeSide.png 10
.transition 0 * 10
.stage	* vista_white.png 0 0
.panel 0
.playBGM *
.transition 0 * 10
;.transition 1 fadeSide.png 10
.stage	* WHITE.png 0 0
.transition 0 * 10
.stage	* WHITE.png 0 0
.wait 100

.chain 203_01.sc
;■203_01へ。

;.end
