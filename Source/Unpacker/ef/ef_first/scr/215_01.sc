; ファイル: 215_01.txt
;■＜２章：１５日目＞
;■黒バック
.transition 0 * 10
.stage	* WHITE.png 0 0
.panel 1
.message	100			然后过了数日。
.message	110			因为是在备考期间，虽然决不可能会平稳无事，但也没有特别发生过什么事件。
.message	120			我只是每天学习，偶尔休息时看看电影读读书，普普通通地过着日子。
.message	130			唯一值得一提的就是，有一次在走廊和摄影研究部的部长大人擦身而过，被她踢了一脚。
.message	140			虽然一点不痛，但我还是投过去了抗议的眼神，而她只是不怀好意的微笑了一下，就无言地走了。
.message	150			值得提的真的就只有这点而已。
.message	160			也就是，极其无聊。
.message	170			在祈祷着无聊的日子能够早点结束中，终于迎来了考试最后一天……。
.panel 0
.transition 0 * 10
.stage	* WHITE.png 0 0


;■背景：教室（夏，１１時
;■　　　　堤京介　　：制服（夏）
;■　　　　宫村宫子：制服（夏）
;■　　　　新藤景　　：制服（夏）
.playSE AT_chime.ogg f 0 *
.transition 1 fadeSide.png 10
.stage	* bgs_sch004m02_01.png 0 0
.panel 1
.message	180			铛～叮～铛～咚～。
.message	190			音羽学园，通知第一学期期末考试结束的钟声终于响起。
.message	200			瞬间，深深的叹息声和欢笑声便充满了教室的各个角落。
.transition 0 * 20
.stage	* ev02_013b01_mugai_b.png 0 0
;.stage	* ev02_013a01.png 0 0
;☆（京介の机の上のものは取っ払ってもらうことも考慮に）
;（流用してますが，切り出しでもいいかもしれません）
.message	210		嫗丂夘	「呜～……」
.message	220			看起来，我是叹气派啊。
.message	230			结束了是好，但这结果我总是无法承认啊……。
;■楽しげ
.transition 0 * 20
.stage	* ev02_013b01_mugai_a.png 0 0
;.stage	* ev02_013b01.png 0 0
;（フェ～ドスピ～ドは20で？）
.message	240	miy-215_01-0003	傒傗偙	「上次的第三名～。考的怎么样？」


;■御影チェック
;.playBGM efBGM040.ogg
;;.playBGM efBGM013.ogg
.playBGM efBGM042.ogg


.transition 0 * 20
.stage	* ev02_181a01.png 0 0
.message	250		嫗丂夘	「呃～，你这次也是想要拿第一名？」
.message	260	miy-215_01-0005	傒傗偙	「想要？　不是什么想要，大概就是第一名哦」
.message	270		嫗丂夘	「…………」
.message	280			要是什么时候我有了女儿，绝对会注意不把她养成这个样子。
.message	290	miy-215_01-0007	傒傗偙	「因为啊」
;■威張り
.transition 0 * 20
.stage	* ev02_181a01_mugai_a.png 0 0
.message	300	miy-215_01-0009	傒傗偙	「我可是人气速度上升中的漫画家的女朋友哦。只有可爱的话怎么相称嘛」
.message	310		嫗丂夘	「好像很充分，但肯定不是这样的理由啊」
.message	320			我又叹了一口气。
.message	330		嫗丂夘	「我嘛，和平常差不了多少了啦。能不能赢你十分微妙啊」
.transition 0 * 20
.stage	* ev02_181a01.png 0 0
.message	340	miy-215_01-0011	傒傗偙	「那么，下仆决定了哦」
.transition 0 * 20
.stage	* bgs_sch004m02_01.png 0 0
;☆（013ＣＧの宫子取り外しバ～を用意してもらうのが吉やも）
.message	350			丢下自做主张的话之后，宫村回到了自己的位置上。
.message	360			无论怎样我是无所谓啦。
.message	370			总之，先把考试的事放的一边。
.message	380			“中断”是为了集中备考，这样的理由的话。
.message	390			那么。


;■御影チェック
;■　ここは曲を変えずに。
;■　宫子と景が接近したことで，２人の“場面”が同じ位置にという感じで。
;.playBGM *
;.playBGM efBGM042.ogg


.transition 0 * 20
.stage	* ev02_140.png 0 0
;（宫子の身体の後ろに景がうまく隠れるように配置，そこからイン？）
.message	400		嫗丂夘	「哦」
.message	410			教室的门边──
;（扉どころか，中に入ってるが，，，まあしゃ～ないか）
.message	420			新藤景站在那里。
.message	430		嫗丂夘	「还真会挑时间啊」
.message	440			行动的速度也值得评价。
.message	450			果然新藤是个好女孩啊，我再次这么想。
.message	460			我从座位上站起来，向她走过去。
.transition 1 fadeSide.png 20
.stage	* bgc_sch002a01_01.png 0 0 st_kei04b01.png 400
;☆（目線，注意して。ここは立ち絵挿まないという選択肢もありますが，その場合は全体の立ち絵構築に関わるので注意して）
.message	470		嫗丂夘	「哟」
.transition 0 * 40
.stage	* bgc_sch002a01_01.png 0 0 st_kei04b05.png 400
;☆（表情，注意されたし。このポ～ズのノ～マル表情を作ってもらう？つ～か，05b01で構築していくのが無難なんかな，，，）
.message	480	kei-215_01-0003	丂宨丂	「嗯」
.message	490			新藤没有表情地点了点头。
.message	500	kei-215_01-0005	丂宨丂	「宫子同学呢？」
.message	510		嫗丂夘	「宫子同学？」
.transition 0 * 40
.stage	* bgc_sch002a01_01.png 0 0 st_kei05b04.png 400
.message	520	kei-215_01-0007	丂宨丂	「呜……」
.message	530			新藤不知为何脸上一阵红潮而闭上了嘴。
.message	540		嫗丂夘	「你害羞什么呢？」
.transition 0 * 40
.stage	* bgc_sch002a01_01.png 0 0 st_kei05b07.png 400
.message	550	kei-215_01-0009	丂宨丂	「别，别在细小的地方问来问去好吧」


;■御影チェック
;■　すぐ後にもカタカナでの“ボク”がありますね。
;■　２回続くとギャグじゃなくて誤字に思われるかも。
;■　
;.message	560		嫗丂夘	「いや，僕も別に責めてるわけじゃ……」
.message	560		嫗丂夘	「哎呀，我也没什么追问的意思……」
;（「僕」だけど，，，まあここはわざとなんだろうな）


.transition 0 * 40
.stage	* bgc_sch002a01_01.png 0 0 st_kei04b04.png 400
;（顔を赤らめさせた立ち絵を？）
.message	570	kei-215_01-0011	丂宨丂	「真是的……那就别说话好吧」
.message	580			在没有见的这段时间里，好象和宫村相当融洽了的样子。
.message	590		嫗丂夘	「然，去把宫村叫出来就好了吧」
.transition 0 * 40
.stage	* bgc_sch002a01_01.png 0 0 st_kei04b05.png 400
;（表情，注意して）
.message	600	kei-215_01-0013	丂宨丂	「考试也结束了，想要对她教我学习道一下谢」
.message	610		嫗丂夘	「原来如此。那我就去叫她──」
.message	620		嫗丂夘	「呜哇」
.transition 0 * 40
.stage	* bgc_sch002a01_01.png 0 0 st_kei04b06.png 400
.message	630	kei-215_01-0015	丂宨丂	「在哪呢？」
.message	640			在宫村的坐位旁边挤满了人，都看不到她本人的了。
.message	650			大概是热心学习的同学们是在和宫村对答案吧。
.message	660		嫗丂夘	「真麻烦啊……好吧，强行突破」
.transition 0 * 40
.stage	* bgc_sch002a01_01.png 0 0 st_kei02b01.png 380
;（表情，注意して）
.message	670	kei-215_01-0017	丂宨丂	「等下啦，也不用作到这个地步吧」
.message	680		嫗丂夘	「以你的格斗能力的话，那种程度的人数根本不在话下吧？　扔飞他们啦，扔飞他们」
.transition 0 * 40
.stage	* bgc_sch002a01_01.png 0 0 st_kei03b04.png 380
.message	690	kei-215_01-0019	丂宨丂	「要我突破的吗！」
.message	700		嫗丂夘	「我对于野蛮的事情不在行啊」
.transition 0 * 40
.stage	* bgc_sch002a01_01.png 0 0 st_kei06b01.png 400
;（向き変えてます。注意して）
.message	710	kei-215_01-0021	丂宨丂	「第一个扔飞你好了」
.message	720			眼神极其认真啊。
.message	730		嫗丂夘	「道，道谢之后不也好嘛。她也不是那种没道谢就会记在心里的人」
.transition 0 * 40
.stage	* bgc_sch002a01_01.png 0 0 st_kei07b01.png 400
;（表情，注意して）
.message	740	kei-215_01-0023	丂宨丂	「也是。下次和瑞希一起来道谢也好……」
.message	750		嫗丂夘	「那么，就马上开始吧」
.message	760			我怪笑着拿出了摄像机。
;■苦笑
.transition 0 * 40
.stage	* bgc_sch002a01_01.png 0 0 st_kei05b02.png 400
;（ポ～ズ変えてます。表情にも注意して）
.message	770	kei-215_01-0025	丂宨丂	「所以啊，你那是从哪拿出来的啊？」
.panel 0
.playSE *
.playBGM *
.transition 0 * 10
.stage	* WHITE.png 0 0




;■シ～ン転換
;■背景：通学路（夏，１１時３０分
;■　　　　堤京介：制服（夏）
;■　　　　新藤景：制服（夏）
.playBGM efBGM051.ogg
;.playBGM BGM054_sample.ogg


;■御影チェック
.set finderCounter = 856
.frame finder.png
;.set finderCounter = 2000
.set finderCounter = 856


;☆（ここはカウンタ～の数字を調整を）
.transition 1 fadeSide.png 10
.stage	st_kei11b01-.png 0 0 bg_scl003a01_01_f.png 0 0 bg_scl003a01_01_n.png 0
.effect	WScroll2 * 60 -2
;☆（「久しぶりの撮影」，，，と後にあるので，カメラフレ～ムでイン？）


;.transition 1 fadeSide.png 10
;.stage	* bgs_normal002a01_01.png 0 0
.panel 1
.message	780		嫗丂夘	「考试怎么样？」
;■自信なさげ
.transition 0 * 40
.stage	st_kei11b04-.png 0 0 bg_scl003a01_01_f.png 0 0 bg_scl003a01_01_n.png 0
.message	790	kei-215_01-0027	丂宨丂	「大概，应该是至今为止最好的一次……吧」


;■御影チェック
;.message	800			久しぶりの撮影でこっちの心は昂揚してるが，新藤はいまいちテンションが低い。
.message	800			久违的摄影让我的心情十分不错，不过新藤的情绪却是很低落。


.message	810		嫗丂夘	「你看起来还真阴暗啊」
.message	820	kei-215_01-0029	丂宨丂	「因为很累了啊。昨天几乎算是通宵了呢」
.message	830		嫗丂夘	「考试前通宵可不太好吧」
.transition 0 * 40
.stage	st_kei10b01-.png 0 0 bg_scl003a01_01_f.png 0 0 bg_scl003a01_01_n.png 0
.message	840	kei-215_01-0031	丂宨丂	「现在就算这么说，既然已经做了也没办法吧」
.message	850		嫗丂夘	「那倒也是」
.message	860		嫗丂夘	「需要考虑的，是从今往后的事」
.message	870		嫗丂夘	「更准确的说的话，是从今以后我们之间的事──」
.transition 0 * 40
.stage	st_kei10b04-.png 0 0 bg_scl003a01_01_f.png 0 0 bg_scl003a01_01_n.png 0
;.stage	st_kei10b05-.png 0 0 bg_scl003a01_01_f.png 0 0 bg_scl003a01_01_n.png 0
.message	880	kei-215_01-0033	丂宨丂	「……我为什么觉得，话的走向有点奇怪？」
.message	890			新藤唰的瞪了过来。
.message	900		嫗丂夘	「讨厌啦，想太多了哦」
.message	910		嫗丂夘	「那么，现在去哪？　昨天通宵的话，别走太久的好」
.transition 0 * 40
.stage	st_kei11b01-.png 0 0 bg_scl003a01_01_f.png 0 0 bg_scl003a01_01_n.png 0
.message	920	kei-215_01-0035	丂宨丂	「那都可以啊」
.message	930			丢下这么一句话，新藤啪嗒啪嗒的走了起来。
.message	940			身体的情况看起来还可以，随她意好了……。
.message	950			新藤景什么都没说的走着。
.message	960			从刚开始拍我就注意到了，是错觉吗，她的步调貌似十分轻快的感觉。

;■御影チェック
;.effect *
.effect end



;■商店街
;（ここ，商店街でいいのか？ちょっと注意して）

;■御影チェック
;.set finderCounter = 3000

.transition 0 * 40
.stage	st_kei11b01-.png 0 0 bg_scl005a01_01.png 0 0 bg_scl005a01_01.png 0
.effect	WScroll2 * 60 -2

;■御影チェック
.set finderCounter = 2005

;☆（スクロ～ル背景からスクロ～ル背景への移行には充分，注意して）
;.transition 1 fadeSide.png 20
;.stage	* bgs_normal001m01_01.png 0 0
.message	970			不是那个时候，一边护着脚伤一边走的样子了。
.message	980			新藤虽然走的很慢──但她一定已经想出自己该怎样走下去了吧。

;■御影チェック
;.effect *
.effect end



;■十字路
;■　　　　堤京介：制服（夏）
;■　　　　新藤景：制服（夏）
;■　　　　广野纮：私服（夏）

;■御影チェック
;.set finderCounter = 4000

.transition 0 * 40
.stage	st_kei11b01-.png 0 0 bg_scl001a01_01_f.png 0 0 bg_scl001a01_01_n.png 0
.effect	WScroll2 * 60 -2

;■御影チェック
.set finderCounter = 2421

;.transition 1 fadeSide.png 20
;.stage	* bgs_normal005a01_01.png 0 0
.message	990	kei-215_01-0037	丂宨丂	「今天也好热啊」
.message	1000		嫗丂夘	「啊啊，好热啊……」
.message	1010		嫗丂夘	「……嗯？」
.message	1020	kei-215_01-0039	丂宨丂	「怎么？」
.playBGM *
.frame *


;■御影チェック
;.effect *
.effect end


.transition 0 * 20
.stage	* ev02_141a01.png 0 0
;（インのタイミング，注意して。この前，切り出しで？）
.message	1030		嫗丂夘	「新藤，你觉得那是什么？」
.message	1040	kei-215_01-0041	丂宨丂	「晕倒了……？　这么热的天气，也不是没可能」
.message	1050	kei-215_01-0043	丂宨丂	「这样才有夏天的风情啊」
.message	1060			意外的冷淡啊，小景。
.message	1070			我只把镜头对着新藤，扭头再次看过去。
.message	1080			一个男人倒在路的正中心。
.message	1090			旁边的是半废品化的自行车。
.message	1100		嫗丂夘	「这可不是晕倒是事故了啊」
.message	1110	kei-215_01-0045	丂宨丂	「是不是也被偷了皮包啊」
.message	1120		嫗丂夘	「街上还真是乱啊」
.message	1130			哈哈哈，我轻轻地一笑而过。
;■ため息
.message	1140	kei-215_01-0047	丂宨丂	「不过，嘛，总不能放着不管啊……」
.message	1150	kei-215_01-0049	丂宨丂	「诶？　稍微等下」
.message	1160		嫗丂夘	「等下等什么？」
.message	1170			不知为何新藤突然混乱起来。
.message	1180			她盯着倒下去的男人看着，然后突然跑了出去。
.transition 0 * 40
.stage	* ev02_141b01.png 0 0
;（駆け出すタイミング，注意して。この前でも？）
.message	1190		嫗丂夘	「新藤？」
.message	1200			不得已，我也随手追了上去。
.message	1210	hir-215_01-0003	@丂峢丂	「啊～」
.message	1220	hir-215_01-0005	@丂峢丂	「好疼疼～」
.message	1230			在跑过去的我们眼前，那个人呻吟着站了起来。
.message	1240			难道说，那是……。
;■驚き
.playBGM efBGM013.ogg
.transition 0 * 20
.stage	* ev02_142.png 0 0
.message	1250	kei-215_01-0051	丂宨丂	「哥哥！」
.message	1260		嫗丂夘	「广野？」
.message	1270			刚想着好久不见，到底在干吗啊。
.message	1280			广野刚刚站起来，就看到了那辆已经惨的不成样子了的自行车。
.transition 0 * 20
.stage	* ev02_143a01.png 0 0
.message	1290	hir-215_01-0007	丂峢丂	「啊啊，我的二号机啊……」
.message	1300	kei-215_01-0053	丂宨丂	「说什么呢！」
.transition 0 * 20
.stage	* ev02_143c01.png 0 0
;（b01は廃盤で？）
.message	1310	hir-215_01-0009	丂峢丂	「嗯？」
.message	1320			广野缓缓的抬起了头。
.message	1330	hir-215_01-0011	丂峢丂	「咦，这不是景嘛。京介也在」
.message	1340	kei-215_01-0055	丂宨丂	「不是『咦』，的问题吧。你在干吗啊！？」
.transition 0 * 40
.stage	* ev02_143c02.png 0 0
.message	1350	hir-215_01-0013	丂峢丂	「一边想事情一边骑车就撞上了」
.message	1360	kei-215_01-0057	丂宨丂	「…………」
.message	1370		嫗丂夘	「我说你，到底在干吗啊……」
.transition 0 * 40
.stage	* ev02_143c03.png 0 0
.message	1380	hir-215_01-0015	丂峢丂	「要你管啊」
.transition 0 * 40
.stage	* ev02_143c04.png 0 0
.message	1390	hir-215_01-0017	丂峢丂	「可恶～。刚刚用分配的零花钱买的啊……又成废物了啊」
.message	1400		嫗丂夘	「零花钱？」
.message	1410			不是已经独立自主生活的广野怎么还有零花钱？
.transition 0 * 40
.stage	* ev02_143c05.png 0 0
.message	1420	hir-215_01-0019	丂峢丂	「啊啊」
.message	1430	hir-215_01-0021	丂峢丂	「最近，我的存折是被宫子管着的啊。生活費和我能自用的钱都得从她那里拿」
;■呆れ
.transition 0 * 40
.stage	* ev02_143d01.png 0 0
.message	1440	kei-215_01-0059	丂宨丂	「哥，哥哥……」
.message	1450		嫗丂夘	「…………」
.message	1460			难道说，少女漫画家·新堂凪先生是个完全的妻管严吗？
.message	1470			不过笨的跟猪头一样的广野也没智商能管钱，其实这也不错嘛。
.message	1480	hir-215_01-0023	丂峢丂	「话说回来啊」
.message	1490	hir-215_01-0025	丂峢丂	「倒是你们在干吗啊？」
.panel 0
;.playBGM
;（わざとおいてません）
.transition 0 * 10
.stage	* WHITE.png 0 0


;■シ～ン転換
;■背景：砂浜（夏，１２時
;.playBGM efBGM047.ogg
.playBGM efBGM016.ogg
.transition 1 fadeSide.png 10
.stage	* bgs_normal006a01_01.png 0 0
;.stage	* bgs_normal007a01_01.png 0 0
.panel 1
.message	1500			把如同废铁的自行车擅自停在不会妨碍人的地方之后，我们走了起来。
.message	1510			虽然广野貌似有事，但稍微绕下远路的时间还是有的。
.transition 1 fadeSide.png 10
.stage	* bgs_normal007a01_01_mugai_a.png 0 0
.message	1520			──一直被关着，想要看下宽广的地方。
.transition 1 fadeSide.png 10
.stage	* bgs_normal007a01_01.png 0 0
;（フェ～ドスピ～ドは20で？）
.message	1530			接受了哭求着的广野的发言，我们来到了海边。
.message	1540			虽然这附近并不是海水浴场，但还是有些星星点点的人影。
;■不安
.transition 0 * 20
.stage	* ev02_144a01.png 0 0
.message	1550	kei-215_01-0061	丂宨丂	「哥哥没事吗？」
.message	1560	hir-215_01-0027	丂峢丂	「什么？」
.message	1570	kei-215_01-0063	丂宨丂	「那个…摔倒的时候没有碰到头吗？」
.transition 0 * 40
.stage	* ev02_144a02.png 0 0
.message	1580	hir-215_01-0029	丂峢丂	「没事啊。我只要右腕没事就行了」
.message	1590		嫗丂夘	「真是可怕的考虑方式啊」
.message	1600		嫗丂夘	「说起来那什么来着？　那什么肌腱炎的怎么样了？」
.message	1610			广野在即将离开学园之前，记得听说他到医院去过。
.message	1620	hir-215_01-0031	丂峢丂	「完全没好一点」
.message	1630			广野啪啪的拍着自己的右手腕若无其事的说。
.transition 0 * 40
.stage	* ev02_144a03.png 0 0
;（この差分の使いどころ，注意して）
.message	1640	hir-215_01-0033	丂峢丂	「是卖漫画的嘛。再怎么说也是痛手腕的生意啊」
.message	1650	hir-215_01-0035	丂峢丂	「痊愈既然没希望，除了去巧妙地适应疼痛以外就没别的办法了啊」
.message	1660	kei-215_01-0065	丂宨丂	「巧妙地…具体的怎么做？」
;■威張り
.transition 0 * 40
.stage	* ev02_144a04.png 0 0
.message	1670	hir-215_01-0037	丂峢丂	「不知道！」
.transition 0 * 40
.stage	* ev02_144b01.png 0 0
;（この差分の使いどころ，注意して）
.message	1680	kei-215_01-0067	丂宨丂	「这不是完全不行吗！」
.message	1690		嫗丂夘	「广野他就是这种人啊……」
.message	1700			就算向前而行，但却完全不动脑袋。
.transition 0 * 40
.stage	* ev02_144a05.png 0 0
.message	1710	hir-215_01-0039	丂峢丂	「要你管～啊」
.transition 0 * 40
.stage	* ev02_144a06.png 0 0
.message	1720	hir-215_01-0041	丂峢丂	「说起来，你不是要拍电影吗？　在这呆着好吗你」
.message	1730		嫗丂夘	「哎呀，从刚才就一直在拍哦」
.transition 0 * 40
.stage	* ev02_144a07.png 0 0
.message	1740	hir-215_01-0043	丂峢丂	「到底在干吗啊……」
.message	1750		嫗丂夘	「倒是你没事吗？　不是要去哪吗？」
.transition 0 * 40
.stage	* ev02_144c01.png 0 0
;（ここからインさせてますが，切り出しも考慮に入れて。あと，c02差分がない？）


;■御影チェック
;.message	1760	hir-215_01-0044		そう言うと，广野はなぜか頭を抱えてしまった。
.message	1760	hir-215_01-0044		我话一出口，广野的表情瞬间可怕起来。


.message	1770	kei-215_01-0069	丂宨丂	「哥哥？」
.message	1780	hir-215_01-0045	丂峢丂	「我老姐回来了，正要去机场接她」
;■軽い驚き
.message	1790	kei-215_01-0071	丂宨丂	「诶，凪姐姐回来了吗」
.message	1800		嫗丂夘	「哦？」
.message	1810			把屋顶的钥匙给广野的那个姐姐吗。
.message	1820	hir-215_01-0047	丂峢丂	「啊～，一点都不想见啊～。能不能飞机摔的只让她一个人死啊……」
.message	1830		嫗丂夘	「那怎么可能嘛」
.message	1840			特技飞行的达人也不可能啊。
.message	1850	kei-215_01-0073	丂宨丂	「哥哥就那么讨厌凪姐姐回来吗……？」
.message	1860	hir-215_01-0049	丂峢丂	「嗯，十分讨厌」
.message	1870			这么低落的广野还真少见啊。
.transition 0 * 40
.stage	* ev02_144d01.png 0 0
;（フェ～ドスピ～ドは注意して）
.message	1880		嫗丂夘	「喂，新藤」
.message	1890			我小声对新藤说。
.message	1900	kei-215_01-0075	丂宨丂	「怎么？」
.message	1910		嫗丂夘	「广野的姐姐是那么糟糕的人吗？」
;■睨み
.transition 0 * 40
.stage	* ev02_144d02.png 0 0
.message	1920	kei-215_01-0077	丂宨丂	「怎么可能嘛」
;■真剣
.message	1930	kei-215_01-0079	丂宨丂	「虽然确实有点……不，十分奇怪但还是很温柔的人哦」
.message	1940	kei-215_01-0081	丂宨丂	「就算是哥哥，我觉得他也不是真的讨厌啊」
.message	1950		嫗丂夘	「是吗。广野看起来是真的很怕的样子啊」
.message	1960	kei-215_01-0083	丂宨丂	「如果真的讨厌，就不会用姐姐的名字当自己的笔名了吧」
.transition 0 * 40
.stage	* ev02_144d03.png 0 0
.message	1970		嫗丂夘	「原来如此，说的也是」
.message	1980	kei-215_01-0085	丂宨丂	「哥哥会入音羽学园，大概也是凪姐姐的影响哦」
.message	1990	kei-215_01-0087	丂宨丂	「因为姐姐是音羽的毕业生年」
.message	2000		嫗丂夘	「唔～……」
.message	2010			虽然觉得不太聪明的广野会入音羽有些不可思议。
.message	2020		嫗丂夘	「广野也只是在闹别扭吧」
.message	2030			虽然是这种态度，但说不定实际上是很尊敬他姐姐的。
.transition 0 * 40
.stage	* ev02_144c01.png 0 0
;（フェ～ドスピ～ド，差分の使い方などには注意のこと）
.message	2040	hir-215_01-0051	丂峢丂	「虽然能成为战力可反而更麻烦啊……」
.message	2050			已经坏掉的漫画家不知在嘟囔些什么。
.message	2060	kei-215_01-0089	丂宨丂	「早些去不好吗，哥哥」
.message	2070	kei-215_01-0091	丂宨丂	「也不能逃啊，要是迟到的话才免不了要死的吧？」
.message	2080			新藤用戏弄的口气说着，露出了一丝笑容。
.message	2090			确实……在笑着。
.transition 0 * 40
.stage	* ev02_144a03.png 0 0
;（表情には注意して）
.message	2100	hir-215_01-0053	丂峢丂	「……也是」
.transition 0 * 40
.stage	* ev02_144a08.png 0 0
;（フェ～ドスピ～ドには注意して）
.message	2110	hir-215_01-0055	丂峢丂	「真没～辙。投降好了」
.transition 0 * 20
.stage	* ev02_145a01.png 0 0
;（ここ，切り出しで？）
.message	2120			广野踢了一脚脚下的海砂，站在了新藤身边。
.message	2130			然后，直直的看着她的眼睛。
;■照れ
.message	2140	kei-215_01-0093	丂宨丂	「诶，怎么？」
.message	2150	hir-215_01-0057	丂峢丂	「景，膝盖怎么样了？」
.message	2160			虽然有着乖僻的样子，脸色和声音都毫不温柔──但是也确实能感觉到他真心地担心着她。
.message	2170	kei-215_01-0095	丂宨丂	「那，那个……」
.message	2180	kei-215_01-0097	丂宨丂	「早就好了啦，都现在了说什么呢你」
.message	2190			她也还是完全不坦率啊。
.message	2200			脸都红到了耳朵──
.message	2210			分明是真的被担心而高兴，却装出一副生气的样子。
.transition 0 * 40
.stage	* ev02_145a02.png 0 0
.message	2220	hir-215_01-0059	丂峢丂	「是吗，早就好了吗」
.transition 0 * 40
.stage	* ev02_145a03.png 0 0
.message	2230			突然，广野的眼神尖锐起来。
.message	2240	hir-215_01-0061	丂峢丂	「那就过来对我说下。我可没空去找你」
;■悲しげ
.transition 0 * 40
.stage	* ev02_145a04.png 0 0
.message	2250	kei-215_01-0099	丂宨丂	「……因为」
.message	2260	hir-215_01-0063	丂峢丂	「什么时候都行，偶然来见下啊」
.transition 0 * 40
.stage	* ev02_145b01.png 0 0
;（フェ～ドスピ～ド，注意して）
.message	2270	hir-215_01-0065	丂峢丂	「见到妹妹的脸，当哥哥的什么时候都会高兴的啊」
.message	2280			啪，广野把手按到了新藤头上，然后微微的笑了起来。
.message	2290	hir-215_01-0067	丂峢丂	「可爱的妹妹更好哦」
;■悲しげ
.message	2300	kei-215_01-0101	丂宨丂	「哥哥……」
.message	2310			新藤用尽全身的力气，勉强平静着自己。
.message	2320	hir-215_01-0069	丂峢丂	「那么，回见」
.transition 0 * 40
.stage	* ev02_145c01.png 0 0
.message	2330	hir-215_01-0071	丂峢丂	「啊，对了对了。京介，你少来哦」
.message	2340		嫗丂夘	「真多废话啊」
.transition 0 * 20
.stage	* ev02_146a01_mugai_a.png 0 0
;.stage	* ev02_146a01.png 0 0
.message	2350			我说时并对着离开广野，而是已经转头看向了新藤。
.message	2360			阳光撒在海面上，反射出复杂的光芒。
.transition 0 * 20
.stage	* ev02_146a01.png 0 0
.message	2370			看着在温和美丽的海的背景中站着的新藤──我却完全失去了想要拍下去的心情。
.message	2380			不想用镜头，而只想用自己的眼睛清楚地看着现在的新藤。
.message	2390			因为，这就是所谓的喜欢一个人的心情。
.message	2400		嫗丂夘	「新藤……」
.message	2410			对着有着一张如此寂寞的脸的她，我该说些什么好呢。
.message	2420	kei-215_01-0103	丂宨丂	「前辈」
.message	2430		嫗丂夘	「诶？」
.message	2440			啪。
.message	2450			她轻轻地握住了我的手。
.message	2460			虽然小小的──却无比温柔而柔软。
;■無表情
.transition 0 * 40
.stage	* ev02_146b01.png 0 0
;（「手を握る」とこ，切り出しで？）
.message	2470	kei-215_01-0105	丂宨丂	「……带我走」
.message	2480		嫗丂夘	「新藤？」
.message	2490	kei-215_01-0107	丂宨丂	「带我到……随便什么没有人的地方去吧」
.message	2500			新藤用几乎要消失的声音轻声说着。
.message	2510			我都没能考虑她话的意义，只是听到她的声音如回声一般回响着。
.panel 0
.playBGM *
.transition 0 * 10
.stage	* WHITE.png 0 0


;■シ～ン転換
;■廃墟（夏，１４時
;■　　　　堤京介：制服（夏）
;■　　　　新藤景：制服（夏）
.transition 1 fadeSide.png 10
.stage	* bgs_normal014a01_01.png 0 0
.panel 1
.message	2520			如果可以的话再也不想来到这里。
.message	2530			不过，说起没有人的地方除了这里想不到别的地方。
.transition 0 * 40
.stage	* bgs_normal014a01_01_stm.png 0 0 stm_kei04b01.png 400
;（この立ち絵のイン，冒頭でもやっているので，ちょっと注意して）
.message	2540	kei-215_01-0109	丂宨丂	「总觉得这附近很凉快呢……」
.message	2550		嫗丂夘	「与其说是凉快，到不如说是让人觉得恶寒」
.transition 0 * 40
.stage	* bgs_normal014a01_01_stm.png 0 0 stm_kei04b02.png 400
.message	2560	kei-215_01-0111	丂宨丂	「意外的胆小呢」
.message	2570		嫗丂夘	「这叫天真」
.message	2580	kei-215_01-0113	丂宨丂	「脸皮真厚」
.message	2590			不是很精神嘛。
.transition 0 * 40
.stage	* bgs_normal014a01_01_stm.png 0 0 stm_kei05b02.png 400
;☆（「まだ握ったままの手」，，，顔アプ使えってことか？ちと注意）
.message	2600	kei-215_01-0114		新藤噗的一声笑了。
.message	2610			这地方虽然一如既往如时间停止般的死寂，但可能是新藤在身边吧，之前的恐怖再也没有感觉到。
.message	2620			可能是紧握的手让我安心了吧……。
.transition 0 * 40
.stage	* bgs_normal014a01_01_stm.png 0 0 stm_kei04b04.png 400
.message	2630	kei-215_01-0115	丂宨丂	「前辈」
.message	2640		嫗丂夘	「嗯？」
.message	2650	kei-215_01-0117	丂宨丂	「以前说过我和千寻──和妹妹在来往电子邮件吧」
.message	2660			我无言的点了点头。
.message	2670	kei-215_01-0119	丂宨丂	「最近要写的东西多到让我头痛呢」
.message	2680		嫗丂夘	「哦，都写了些什么？」
;■真面目，口調はあっさり
.message	2690	kei-215_01-0121	丂宨丂	「雨宫优子的坏话之类」
.message	2700		嫗丂夘	「……妹妹应该不认识雨宫的吧？」
.message	2710	kei-215_01-0123	丂宨丂	「虽然不认识但也没关系啊。写的尽量有趣奇怪就行了」
.message	2720			虽然不太明白其中的意义……但新藤的话，肯定是在邮件中把雨宫骂的死去活来的吧。
.message	2730			对那邮件稍微有点兴趣了呢。
.message	2740	kei-215_01-0125	丂宨丂	「那个女人好像是在等人呢」
.message	2750		嫗丂夘	「她说了那种话吗」
.message	2760	kei-215_01-0127	丂宨丂	「只是一个人孤单的等着。白痴吗」
.message	2770			一瞬，新藤看向远方。
;■感心
.message	2780	kei-215_01-0129	丂宨丂	「虽然是个白痴，但是好厉害呢」
.message	2790		嫗丂夘	「好厉害？」
.message	2800	kei-215_01-0131	丂宨丂	「一直一个人孤独地思念着……怎么可能作到吗」
.message	2810		嫗丂夘	「那种事情，你不也」
.message	2820			新藤轻轻的摇了摇头。
.message	2830	kei-215_01-0133	丂宨丂	「不」
.playBGM efBGM025mix.ogg
.message	2840		嫗丂夘	「不？」
.message	2850	kei-215_01-0135	丂宨丂	「我呢，前辈……」
;■悲しげ
.message	2860	kei-215_01-0137	丂宨丂	「我不是你想的那样坚强的人呢」
.message	2870			新藤的手突然攥地紧紧的。
.message	2880			她突然离我这么近，象是要包容着一般两手握着我的手掌。
.message	2890			离近看才发现新藤的眼睛似乎渗着泪水……。
.message	2900		嫗丂夘	「新藤……？」
;☆（ここから，ＣＧが入る予定です）
.transition 0 * 20
.stage	* ev02_147a01.png 0 0
.message	2910	kei-215_01-0139	丂宨丂	「我…一点都不坚强」
.message	2920	kei-215_01-0141	丂宨丂	「不，大概比谁都要软弱吧。所以不这样碰着谁的话会无法安心。从很久以前就是这样」
.message	2930	kei-215_01-0143	丂宨丂	「刚刚出生时就有千寻在我身边……所以一直不懂得什么叫做寂寞」
.message	2940	kei-215_01-0145	丂宨丂	「虽然性格一点都不像，但正是有着对方没有的东西，我们姐妹才会有这样强烈的羁绊吧」
.message	2950	kei-215_01-0147	丂宨丂	「虽然偶尔也会吵架……但在一起玩，在同一个被窝里睡觉，一直都愉快无比」
.message	2960	kei-215_01-0149	丂宨丂	「然后──」
.message	2970	kei-215_01-0151	丂宨丂	「遇到哥哥，马上就喜欢上他」
.transition 0 * 20
.stage	* ev02_147a02.png 0 0
;（フェ～ドスピ～ドは40で？）
.message	2980	kei-215_01-0153	丂宨丂	「哥哥和千寻和我。三人在一起的时光是最愉快的。对于我来说，是无法替换的重要的回忆……」
.message	2990	kei-215_01-0155	丂宨丂	「虽然生活中不可能一直都只有好事……」


;.message	3000	kei-215_01-0157	丂宨丂	「千寻……千寻が……どうして，あんなことに……」
.message	3000	kei-215_01-0156	丂宨丂	「但千寻……」
.message	3005	kei-215_01-0158	丂宨丂	「但千寻……为什么…会遇到那种事……」



.message	3010		嫗丂夘	「新藤……」
.message	3020			她到底承受着多么沉重的悲伤呢。
.message	3030			这个纤细的身体到底背负着些什么呢……。
.message	3040	kei-215_01-0159	丂宨丂	「不过，那个时候还有哥哥在，所以我才可以坚持下去」


;.message	3050	kei-215_01-0161	丂宨丂	「思えば，わたしはずっと依存してた。お兄ちゃんだけじゃない，千寻にだって甘えてた。お姉ちゃんなのに，情けないわよね……」
.message	3050	kei-215_01-0160	丂宨丂	「回想起来，我一直都在依存着生活」
.message	3055	kei-215_01-0162	丂宨丂	「不只是哥哥，也对千寻撒娇。分明我是姐姐的，真是没有脸面呢……」


.message	3060	kei-215_01-0163	丂宨丂	「所以孤单一人时……便一瞬之间，寂寞的痛苦的不知如何是好」
.message	3070	kei-215_01-0165	丂宨丂	「受了伤，失去各种各样的东西，心就好像空壳一样……」
.message	3080	kei-215_01-0167	丂宨丂	「不知何时开始寻找可替代的东西。能够让我忘记痛苦的什么东西」
.message	3090	kei-215_01-0169	丂宨丂	「我自己也明白。之所以会对天真无邪地靠近我的瑞希温柔……大概，只是想用她来代替千寻而已吧」
.message	3100	kei-215_01-0171	丂宨丂	「无法一直追求着无法得到的东西，所以才会找其他的来欺骗自己」
.transition 0 * 20
.stage	* ev02_147a03.png 0 0
.message	3110	kei-215_01-0173	丂宨丂	「但是，只有瑞希并不够。我的心仍然止步不前……」
.message	3120	kei-215_01-0175	丂宨丂	「就在这时，京介前辈在我面前出现了」
.message	3130			听到咚的一声钝锉的巨响。
.message	3140			大概是废屋的哪里崩塌了吧。



;.message	3150	kei-215_01-0177	丂宨丂	「あなたが向けてくるまっすぐな目に──圧倒されていたんだと思う。そんな目ができる，それだけの強い想いを持っている前辈が羨ましかったわ」
.message	3150	kei-215_01-0176	丂宨丂	「你直直看过来的目光──具有压倒性的力量」
.message	3155	kei-215_01-0178	丂宨丂	「可以拥有那种眼神，真是羡慕着有着这样强烈的意志的前辈呢」


.message	3160	kei-215_01-0179	丂宨丂	「这个人的话，这个一直向前方冲锋着的人说不定可以带着我停止的心走下去吧」
.transition 0 * 20
.stage	* ev02_147a04.png 0 0
.message	3170	kei-215_01-0181	丂宨丂	「我一直都是这样想的啊」
.message	3180	kei-215_01-0183	丂宨丂	「无论何时──都无法断掉被别人的依赖」
.message	3190	kei-215_01-0185	丂宨丂	「我如果稍微坚强些的话，就会去追求真正想要的东西了吧──」
.message	3200	kei-215_01-0187	丂宨丂	「也可以作到放弃吧」
.message	3210	kei-215_01-0189	丂宨丂	「正是因为坚强才可以放弃的啊。而就是软弱着──才会一直都被捆绑在这里」
.message	3220			这次是木制的什么东西折断的声音。
.message	3230			在这个毫无动静的废墟里，过去正一点点的崩碎。
.message	3240	kei-215_01-0191	丂宨丂	「所以才想要去充实自己的心，想要让谁在自己的身边──无论什么都无所谓」
.message	3250	kei-215_01-0193	丂宨丂	「分明自己什么都不做，真自私对吧……」
.message	3260	kei-215_01-0195	丂宨丂	「很过分对吧。分明是不能做的事情的」
.message	3270	kei-215_01-0197	丂宨丂	「不得不道歉呢……」
.message	3280			已经不想再听下去。
.message	3290			所以──我毫无迷茫地向前踏出了一步。
.message	3300		嫗丂夘	「分明没有一个人恨你，你要向谁道歉啊？」
.message	3310			我靠近垂下肩膀的新藤。
.message	3320			然后直直的看着她盖满悲伤却美丽的脸。
.transition 0 * 20
.stage	* ev02_148a01.png 0 0
.message	3330		嫗丂夘	「你从心底追求着谁，而那个人接受了不就好了吗？」
;■睨み
.message	3340	kei-215_01-0199	丂宨丂	「我的心情是假的啊」
.message	3350		嫗丂夘	「虽然只是举个例子……你的妹妹和羽山是不同的人啊」
.message	3360		嫗丂夘	「所以，如果你认为羽山可爱，这份心情对羽山来说就是真的」
.message	3370	kei-215_01-0201	丂宨丂	「……真麻烦。我是笨蛋，不用简单的说法我不懂的啊」
.message	3380			我深深的叹了口气。
.transition 0 * 40
.stage	* ev02_148a02.png 0 0
.message	3390		嫗丂夘	「契机啦理由啦都无所谓。只要有喜欢的心情就足够了」
;■悲しみ
.transition 0 * 20
.stage	* ev02_147b06_mugai_a.png 0 0
;☆（ev02_147b01の使いどころには注意して）
;.stage	* ev02_147b01.png 0 0
.message	3400	kei-215_01-0203	丂宨丂	「那么，这个心情也是吗？」
;.transition 0 * 20
;.stage	* ev02_148b01.png 0 0
.message	3410			新藤啪的把手按到了我的胸前。
.transition 0 * 20
.stage	* ev02_148b01.png 0 0
.message	3420	kei-215_01-0205	丂宨丂	「就算我对于京介前辈的这份心情──只是想要埋葬自己的寂寞而已」
;.transition 0 * 20
;.stage	* ev02_147b01.png 0 0
.message	3430	kei-215_01-0207	丂宨丂	「已经不想再抱着这种不会有结果的心情──为此我才和前辈在一起的话」
.transition 0 * 20
.stage	* ev02_147b02.png 0 0
.message	3440	kei-215_01-0209	丂宨丂	「你这样也可以吗？」
.message	3450		嫗丂夘	「如果新藤寂寞的话，我想要消除她的寂寞」
;■驚き
.message	3460	kei-215_01-0211	丂宨丂	「……」
.message	3470		嫗丂夘	「而且，也不是谁都可以的吧？　是因为觉得我是能改变你的心情的人不是吗？」
.transition 0 * 20
.stage	* ev02_148b02.png 0 0
.message	3480		嫗丂夘	「我很高兴啊，因为这代表你选择了我」
.message	3490		嫗丂夘	「形式暂且不提，新藤的心情是朝向我的不是吗？」
.message	3500	kei-215_01-0213	丂宨丂	「……嗯」
.message	3510			新藤轻轻的点了点头。



;.message	3520	kei-215_01-0215	丂宨丂	「だって……京介前辈はここにいるもの。わたしのそばに，いるんだもの……」
.message	3520	kei-215_01-0214	丂宨丂	「因为……京介前辈在这里啊」
.message	3525	kei-215_01-0216	丂宨丂	「在我的身边啊……」



.message	3530		嫗丂夘	「有点明白，又有点不太明白……新藤还真是说了有趣的话啊」
.transition 0 * 20
.stage	* ev02_147b03.png 0 0
.message	3540	kei-215_01-0217	丂宨丂	「笨蛋，少在这种时候开玩笑啊！」
.message	3550		嫗丂夘	「诶」
.message	3560			不象是女孩子该有的力量重重地打到了胸口上。
.message	3570		嫗丂夘	「……虽然有点痛，但果然新藤还是生气起来好呢」
.transition 0 * 20
.stage	* ev02_147b04.png 0 0
.message	3580	kei-215_01-0219	丂宨丂	「所，所以说了不要戏弄人」
.message	3590		嫗丂夘	「因为我不想再看到了悲伤的脸了啊」
.message	3600	kei-215_01-0221	丂宨丂	「…………」
.message	3610			在体育馆见到她时，新藤景忍耐着悲伤的身影迷住了我。
.message	3620			但是，已经再也不想看到那样的她。
;■悲しみ
.transition 0 * 20
.stage	* ev02_147b01.png 0 0
;（表情，注意して）
.message	3630	kei-215_01-0223	丂宨丂	「我……」
.message	3640	kei-215_01-0225	丂宨丂	「我到现在看到哥哥的脸……心情仍会摇摆不定」
.message	3650	kei-215_01-0227	丂宨丂	「无论如何都无法完全消除对哥哥的思念。因为，我那份心情是实实在在的啊」
.message	3660		嫗丂夘	「没事啦，现在就算如此」
.message	3670			其实一点都不好。
.message	3680			不过，我也明白马上改变她的心意是不可能呢。
.message	3690			不过，正式因为现在才想要一个契机。
.message	3700		嫗丂夘	「我想要给你……改变的契机啊」
.transition 0 * 20
.stage	* ev02_148b03.png 0 0
.message	3710		嫗丂夘	「你已经改变了。因为，已经走出去了。不是吗？」
.transition 0 * 20
.stage	* ev02_147b05.png 0 0
.message	3720	kei-215_01-0229	丂宨丂	「我也……想要改变呢」
.message	3730	kei-215_01-0231	丂宨丂	「和雨宫优子见面，聊天……决定再要开始奔跑时……」
.message	3740	kei-215_01-0233	丂宨丂	「想要和京介前辈一起奔跑。不是别人，而是前辈……」
.message	3750	kei-215_01-0235	丂宨丂	「因为你是告诉了我一直垂头丧气的话就什么都不会开始的人……」
.message	3760		嫗丂夘	「谢谢你，新藤」
.transition 0 * 20
.stage	* ev02_149_mugai_a.png 0 0
.message	3770			我踏近一步，然后紧紧地抱住新藤小小的身体。
.transition 0 * 20
.stage	* ev02_149.png 0 0
.message	3780	kei-215_01-0237	丂宨丂	「改变我吧……京介前辈」
.message	3790		嫗丂夘	「啊啊……」
.message	3800			已经充满裂缝的过去，全部崩坏掉就好了。
.message	3810			因为只有在所有都崩坏之后──才会创造出新的什么。
.playBGM *
.transition 0 * 10
.stage	* WHITE.png 0 0
.message	3820			（备注：接下来将要进入Hsence）
.select 略过阅读:label1 继续阅读:label2
.label label1
.chain 215_04.sc
.label label2
.chain 215_02.sc
;■111_05へ。

.end