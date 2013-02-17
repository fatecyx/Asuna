; ファイル: 213_01.txt
;■＜２章：１３日目＞
;■背景：校門（夏，７時
;■　　　　堤京介：制服（夏）
;■　　　　新藤景：制服（夏）
.playBGM efBGM042.ogg

;■御影チェック
.set finderCounter = 202
.frame finder.png
;.set finderCounter = 500
.set finderCounter = 202

.transition 0 * 10
.overlay	or_kei00a.png * *
.screen	sc_morning01.png sc_morning01.png sc_morning01.png
.stage	st_kei10b01-.png 0 0 bg_scl002a01_00_f.png 0 0 bg_scl002a01_00_n.png 0
.effect	WScroll2 * 60 -2


;.transition 0 * 10
;.stage	* bgs_sch001a01_00.png 0 0
.panel 1
.message	100		嫗丂夘	「呜噢噢噢噢噢……」
.transition 0 * 40
.stage	st_kei10b04-.png 0 0 bg_scl002a01_00_f.png 0 0 bg_scl002a01_00_n.png 0
.message	110	kei-213_01-0003	丂宨丂	「别发出奇怪的声音好吧，真不象样」
.message	120		嫗丂夘	「就算你这么说……」
.message	130			新藤啪嗒啪嗒走在前面，而我举着摄像机，拼死地紧跟其后。
.message	140			并不是有什么问题。
.message	150			仅仅是因为昨天跑的太过分而引起肌肉痛而已。
.message	160		嫗丂夘	「新藤你身体不痛吗？」
.transition 0 * 40
.stage	st_kei10b01-.png 0 0 bg_scl002a01_00_f.png 0 0 bg_scl002a01_00_n.png 0
.message	170	kei-213_01-0005	丂宨丂	「稍微有一些累，但肌肉并不痛哦」
.message	180		嫗丂夘	「啊啊，是吗。年纪大了，疲劳反应会变慢看来是真的啊」
.transition 0 * 40
.stage	st_kei10b06-.png 0 0 bg_scl002a01_00_f.png 0 0 bg_scl002a01_00_n.png 0
;（表情注意して）
.message	190	kei-213_01-0007	丂宨丂	「我比你年纪要小！」
.message	200		嫗丂夘	「哦哦，说起来也是呢」
.transition 0 * 40
.stage	st_kei11b03-.png 0 0 bg_scl002a01_00_f.png 0 0 bg_scl002a01_00_n.png 0
.message	210	kei-213_01-0009	丂宨丂	「我和前辈你基础体力不同啦」
.message	220		嫗丂夘	「我对运动也还是很有自信的啊……」
.message	230			平常不锻炼不会有持久力吧。
.message	240			还是新藤是讨论外的怪物呢。
.transition 0 * 40
.stage	st_kei10b02-.png 0 0 bg_scl002a01_00_f.png 0 0 bg_scl002a01_00_n.png 0
;.stage	st_kei10b01-.png 0 0 bg_scl002a01_00_f.png 0 0 bg_scl002a01_00_n.png 0
;☆（ここの表情はちょっと注意して。音声のラストに微笑み系入ってる？）
;.stage	st_kei10b04-.png 0 0 bg_scl002a01_00_f.png 0 0 bg_scl002a01_00_n.png 0
.message	250	kei-213_01-0011	丂宨丂	「顺带也锻炼一下前辈好了。确实也可以作不少运动呢，而且还能跟上我不是么？」
.message	260		嫗丂夘	「嘛，我也没有选择的余地，只有跟着而已啊……」
.message	270			这边已经决定要超越从前彻底的跟着新藤了。
.message	280			她走着的时候，就跟在她的后头。
.message	290			游泳的时候，就跟到水平线的尽头。
;.transition 0 * 40
;.stage	st_kei11b02-.png 0 0 bg_scl002a01_00_f.png 0 0 bg_scl002a01_00_n.png 0
;☆（もしかしたら，ここは無理して差分使う必要はないのかもしれん，，，）
;.stage	st_kei10b02-.png 0 0 bg_scl002a01_00_f.png 0 0 bg_scl002a01_00_n.png 0
;.stage	st_kei10b01-.png 0 0 bg_scl002a01_00_f.png 0 0 bg_scl002a01_00_n.png 0
.message	300	kei-213_01-0013	丂宨丂	「首先要重新锻炼你钝下来的的身体。到不是有什么意义，而是想不到别的该做的事」
;.transition 0 * 40
;.stage	st_kei10b02-.png 0 0 bg_scl002a01_00_f.png 0 0 bg_scl002a01_00_n.png 0
;.transition 0 * 40
;.stage	st_kei10b05-.png 0 0 bg_scl002a01_00_f.png 0 0 bg_scl002a01_00_n.png 0
.message	310	kei-213_01-0015	丂宨丂	「可以吧？」
.message	320		嫗丂夘	「如您所愿」
.message	330			我对她笑了一笑。
.transition 0 * 40
.stage	st_kei10b03-.png 0 0 bg_scl002a01_00_f.png 0 0 bg_scl002a01_00_n.png 0
;（表情は注意して）
.message	340	kei-213_01-0016		然后，新藤的脸上也盛开起闪亮的笑颜──
.panel 0
.playBGM *


;■御影チェック
;.effect *
.effect end

.overlay	* * *
.screen	* * *
.frame *
.transition 0 * 10
.stage	* WHITE.png 0 0


;■背景：図書室（夏，７時３０分
;■　　　　堤京介　　：制服（夏）
;■　　　　新藤景　　：制服（夏）
;■　　　　宫村宫子：制服（夏）
.playBGM efBGM046_2.ogg
;（図書室でかけるような曲ではないのかもしれんが·苦笑）


;■御影チェック
;.transition 1 fadeSide.png 10
.transition 1 fadeSide.png 15

.stage	* ev02_113a01.png 0 0
.panel 1
.message	350	kei-213_01-0017	丂宨丂	「呜呜呜……」
.message	360		嫗丂夘	「别发出奇怪的声音好吧」
.message	370	kei-213_01-0019	丂宨丂	「看着教科书这样排在一起我就头疼……」
.message	380			闪亮的笑颜绮丽的完全的从她脸上消失了。
.message	390			我们今天提前来学校的原因，是要为考试差劲的新藤补习功课。
.message	400			运动虽然不错，但临近期末还不努力学习的话。
.message	410			虽然她不太愿意，但舍不得孩子套不住狼啊。
.message	420		嫗丂夘	「然，新藤不拿手的科目是？」
.message	430	kei-213_01-0021	丂宨丂	「呜呜～」
.message	440		嫗丂夘	「不拿手的科目是？」
.message	450			再次问了一次，新藤才勉强张开了口。
.transition 0 * 40
.stage	* ev02_113a02.png 0 0
.message	460	kei-213_01-0023	丂宨丂	「现代文，古文，汉文，英语，数学，生物，日本史……」
.message	470		嫗丂夘	「……有什么拿手的吗？」
.message	480	kei-213_01-0025	丂宨丂	「体育……」
.message	490		嫗丂夘	「呜呜呜……」
.transition 0 * 40
.stage	* ev02_113b01.png 0 0
.message	500	kei-213_01-0027	丂宨丂	「也，也不必抱着头吧！」
.message	510	kei-213_01-0029	丂宨丂	「当我是体力白痴了是吧！　笑话我连大脑里都是肌肉了是吧！　没其他优点还真是抱歉呢！」
.message	520		嫗丂夘	「嘘～，大声会惹麻烦的」
.message	530			周围学习的人盯着这边看了过来。
;■照れ
.transition 0 * 40
.stage	* ev02_113b02.png 0 0
.message	540	kei-213_01-0031	丂宨丂	「啊……」
.message	550		嫗丂夘	「总觉得不能行啊」
.message	560	kei-213_01-0033	丂宨丂	「被京介前辈说更让人恼火……」
.message	570		嫗丂夘	「啊啊，嘛反正是事实，也没什么好恼火的啦」
.transition 0 * 40
.stage	* ev02_113b03.png 0 0
.message	580	kei-213_01-0035	丂宨丂	「…………」
.message	590			唰，用要杀人般的眼睛瞪了过来。
.message	600		嫗丂夘	「呃～，那么就马上开始」
.message	610			我调整好状态，拿出笔记本和教科书。
.message	620		嫗丂夘	「要从什么开始？　只是，我对英语有些不太拿手」
.message	630	miy-213_01-0003	傒傗偙	「那么，那个让我教好了」
.message	640		嫗丂夘	「出现了～！」
.transition 0 * 20
.stage	* ev02_114a01.png 0 0
.message	650	kei-213_01-0037	丂宨丂	「宫，宫村前辈！？」
.message	660	miy-213_01-0005	傒傗偙	「你们很吵诶。对别人造成困扰可不行哦」
.message	670		嫗丂夘	「哈……」
.transition 0 * 40
.stage	* ev02_114a02.png 0 0
.message	680	kei-213_01-0039	丂宨丂	「…………」
.message	690			又来了。
.transition 0 * 40
.stage	* ev02_114a03.png 0 0
.message	700	miy-213_01-0007	傒傗偙	「要注意哦，小景和堤堤都是」
.message	710			不过，突然出现然后吓人才是她的风格。
.message	720			话说回来，我可不想被穿着名为“麻烦”的制服到处走来走去的人指责。
.message	730		嫗丂夘	「宫村，我说你──」
;■真面目
.transition 0 * 40
.stage	* ev02_114a04.png 0 0
.message	740	miy-213_01-0009	傒傗偙	「小景」
.message	750			又被无视了。
.message	760	kei-213_01-0041	丂宨丂	「……是」
.message	770	miy-213_01-0011	傒傗偙	「再怎么看我成绩还是很好的哦。教人的方法也觉得很不错」
.message	780	kei-213_01-0043	丂宨丂	「宫村前辈是年级第一名这种事，就算我也是知道的」
.message	790			这两个人的对话，总会有微妙的紧张感啊。
.message	800	miy-213_01-0013	傒傗偙	「还是说，讨厌被我这样的人教呢？」
.message	810	kei-213_01-0045	丂宨丂	「当然讨厌」
.message	820			毫无犹豫的，新藤断然说道。
.message	830	kei-213_01-0047	丂宨丂	「但是」
.message	840	kei-213_01-0049	丂宨丂	「我也想问你。为什么想要教我这样的人学习呢？」
.message	850	miy-213_01-0015	傒傗偙	「啊啊，那是因为」
;■笑顔
.transition 0 * 40
.stage	* ev02_114a05.png 0 0
.message	860	miy-213_01-0017	傒傗偙	「小景很可爱啊」
.message	870	kei-213_01-0051	丂宨丂	「……可，可……？」
.message	880			这自然就算是小景也会动摇的啊。
.message	890	kei-213_01-0053	丂宨丂	「宫，宫村前辈，你说什么──」
.transition 0 * 40
.stage	* ev02_114a06.png 0 0
.message	900	miy-213_01-0019	傒傗偙	「觉得你可爱，喜欢你啊」
.message	910			这女人一边笑一边说什么啊。
.message	920			而且还很认真的样子也让人觉得恐怖。
.message	930		嫗丂夘	「那么，新藤怎么办？」
.transition 0 * 40
.stage	* ev02_114b01.png 0 0
.message	940	kei-213_01-0055	丂宨丂	「你问我怎么办……」
.message	950		嫗丂夘	「宫村的学力我可以作保证。在我们班，被她教过然后成绩上升的人很有那么几个的样子」
.message	960		嫗丂夘	「然，怎么办？」
.transition 0 * 40
.stage	* ev02_114b02.png 0 0
.message	970	kei-213_01-0057	丂宨丂	「……嗯」
.message	980			新藤看着我，叹出一声不知是肯定还是否定的气息。
.message	990			然后一段时间内，新藤带着困扰的表情沉默起来。
.message	1000			我和宫村，都静静地等待着她的答案。
.panel 0
.playBGM *
.transition 0 * 10
.stage	* WHITE.png 0 0


;■シ～ン転換
;■背景：屋上（夏，１３時
;■　　　　堤京介　　：制服（夏）
;■　　　　新藤景　　：制服（夏）
;■空
.playBGM efBGM052.ogg
;.playBGM BGM052_sample.ogg
.transition 1 fadeSide.png 10
.stage	* ev02_115.png 0 0
;（指定どおり，空からこのＣＧにイン？）
.panel 1
.message	1010			午休时间，我把新藤带到了屋顶。
.message	1020			一瞬突然想到。
.message	1030			虽然这里的景色还是十分不错的，但会觉得有些不安的心情是为什么呢。
.message	1040		嫗丂夘	「你觉得为什么？」
.message	1050	kei-213_01-0059	丂宨丂	「我怎么知道」
.message	1060			新藤冷淡的回了一句，把最后的面包丢进嘴里，开始喝塑料袋装的牛奶。
.message	1070		嫗丂夘	「真是冷淡的回答啊」
.message	1080	kei-213_01-0061	丂宨丂	「无所谓的东西。到是，不是要决定今后的预定的吗。给我快一点啦」
.message	1090		嫗丂夘	「是是」
.message	1100			把从小卖部买来的金枪鱼三明治迅速的塞进嘴里，然后顺着咖啡灌下去。
.message	1110		嫗丂夘	「也说不上什么预定啦。下周从周一到周四是期末测验。这段时间内，虽然很遗憾但摄影完全停止」
.message	1120	kei-213_01-0063	丂宨丂	「理所当然的」
.message	1130		嫗丂夘	「然后，虽然从周五开始直到期末考试几乎都是休息──」
.message	1140		嫗丂夘	「但新藤这边应该还有补习和补考吧」
.message	1150	kei-213_01-0065	丂宨丂	「少说得跟决定了似的！」
.message	1160		嫗丂夘	「嘛，能减少多少红灯才是这两天的课题啊……」
.message	1170	kei-213_01-0067	丂宨丂	「不，不做做看怎么知道。就是为了这个，我才……」
.message	1180			对，新藤接受了宫村的辅导。
.message	1190			我当然对于提案的宫村感到有些微微的惊讶。
.message	1200	kei-213_01-0069	丂宨丂	「总不能一直都说自己学习不行啊」
.message	1210		嫗丂夘	「那是自然。要是留级的话就不好看了啊～」
.message	1220	kei-213_01-0071	丂宨丂	「没糟糕到那种东西！」
.message	1230	kei-213_01-0073	丂宨丂	「自己成绩稍微好那么一点，好那么一点，少小看人～！」
.message	1240		嫗丂夘	「哦哦，小景放轻松放轻松」
.message	1250		嫗丂夘	「对了，给你零花钱好了」
.message	1260	kei-213_01-0075	丂宨丂	「谁要啊！」
.message	1270			说着就把空了的牛奶袋扔了过来。
.message	1280		嫗丂夘	「哦」
.message	1290			在要击中脸的瞬间接了下来。
.message	1300		嫗丂夘	「顺带一提，现在再喝牛奶来增长身高的就有点晚了」
.message	1310	kei-213_01-0077	丂宨丂	「我是喜欢喝才喝的！」
.message	1320		嫗丂夘	「不过，追求的是胸部限定的话还并不是没有希望」
.message	1330	kei-213_01-0079	丂宨丂	「再不闭嘴的话，你的命就是风中残烛了哦」
.message	1340		嫗丂夘	「稍微开个玩笑而已，继续往下说嗯」
.message	1350	kei-213_01-0081	丂宨丂	「别以为我什么时候都会笑啊你……」
.message	1360			然后，就摆出一副僵硬的脸看着我。
.message	1370			就算再怎么吓人，基本上只说脸就可爱的过分啊。
.message	1380	kei-213_01-0083	丂宨丂	「你在那傻笑什么的」
.message	1390		嫗丂夘	「什么也没有哦」
.message	1400		嫗丂夘	「总之就是考试之前，早晨的时候摄影」
.message	1410		嫗丂夘	「午休作为自由时间，放学后再次摄影。新藤还要继续运动的吧？」
.message	1420	kei-213_01-0085	丂宨丂	「说是运动，不如说是康复训练吧」
.message	1430			说到底，那样激烈的康复训练这世上存在吗……。
.message	1440		嫗丂夘	「是什么无所谓，到傍晚之前就是这个了。然后，晚上是和宫村一起的学习会。这样可以吧？」
.message	1450	kei-213_01-0087	丂宨丂	「我一向君子一言，驷马难追」
.message	1460		嫗丂夘	「小景，好帅哦～」
.message	1470	kei-213_01-0089	丂宨丂	「别叫我小景！」
.message	1480		嫗丂夘	「哎呀哎呀」
.message	1490			还以为刚才如果不追究的话，以后就可以喊她带小字了呢。
.message	1500	kei-213_01-0091	丂宨丂	「嘛……再怎么说我也不想留级啊。小失误倒还可以睁一眼闭一眼」
.message	1510			果然是有可能留级吗。
.message	1520	kei-213_01-0093	丂宨丂	「如果真的留级的话……就无法面对了」
.message	1530		嫗丂夘	「无法面对谁？　家人吗？」
.message	1540	kei-213_01-0095	丂宨丂	「家人当然也算……」
.message	1550	kei-213_01-0097	丂宨丂	「我必须认真的来到学园，愉快于学园生活，然后毕业」
.message	1560	kei-213_01-0099	丂宨丂	「如果不这样的话……真的会无法原谅自己的」
.message	1570		嫗丂夘	「…………」
.message	1580			虽然好似有所隐情，但她看起来并不想说。
.message	1590			当然，我也不会去逼问她不想说的事情。
.message	1600			让她把一切都说不出并不是我的目的，而且要把她的思念捕捉到影像中。
.panel 0
.transition 0 * 10
.stage	* WHITE.png 0 0


;■シ～ン転換
;■背景：教室（夏，１６時
;■　　　　堤京介　　：制服（夏）
;■　　　　新藤景　　：制服（夏）
.playSE AT_chime.ogg f 0 *
.transition 1 fadeSide.png 10
.stage	* bgs_sch004m03_02.png 0 0
.panel 1
.message	1610			铛～叮～铛～咚～。
.message	1620			本天的课程结束了～。
.message	1630		嫗丂夘	「那么，走吧」
.overlay * or_kei02a.png
.transition 0 * 20
.stage	* bgs_sch004m03_02.png 0 0 st_kei06b01.png 400
.message	1640	kei-213_01-0101	丂宨丂	「嗯，要走了哦」
.message	1650		嫗丂夘	「哇！？」
.message	1660		嫗丂夘	「新，新藤。你怎么在这？」
.message	1670			这可是三年级的教室啊。
.transition 0 * 40
.stage	* bgs_sch004m03_02.png 0 0 st_kei04b04.png 400
;（表情，注意して）
.message	1680	kei-213_01-0103	丂宨丂	「不想浪费时间啊。好了，赶快拿上你的提包」
.message	1690		嫗丂夘	「稍，稍微等下啊。我教科书都还没整理呢……」
.transition 0 * 40
.stage	* bgs_sch004m03_02.png 0 0 st_kei08b01.png 400
;（後ろを向かせるのではなくて，表情＆ポ～ズを変えさせる？）
.message	1700	kei-213_01-0105	丂宨丂	「不要磨蹭。反应迟钝我最讨厌了」
.message	1710			有干劲到是好事，小景稍微有些暴走的味道呢。
.panel 0
.playSE *
.overlay * *

;■御影チェック
.playBGM *

.transition 0 * 10
.stage	* WHITE.png 0 0


;■シ～ン転換
;■背景：砂浜（夏，１７時
;.playBGM efBGM047.ogg
.playBGM efBGM054.ogg
;.playBGM BGM054_sample2.ogg
.transition 1 fadeSide.png 10
.stage	* ev02_109.png 800 0
;（このＣＧでインしてますが，京介のカバン，景の服装が違うので再利用はできません。よって演出指定とズレますが，スクロ～ルはさせないで。ev02_111を使うのも手？切り出しも考慮に）
.panel 1
.message	1720		嫗丂夘	「哈～，哈～，哈啊……」
.message	1730	kei-213_01-0107	丂宨丂	「真是的，你要精疲力尽到什么时候啊」
.message	1740		嫗丂夘	「就，就算你……这么说……」
.message	1750			怎么跟昨天一模一样。
.message	1760			但是我身上的肌肉痛的程度要比昨天大的多。
.message	1770			现在回想起来，跑着的新藤我也不必拍那么多次啊。
;■笑顔


;■御影チェック
.set finderCounter = 2334
.frame finder.png
;.set finderCounter = 800
.set finderCounter = 2334


.transition 0 * 20
.stage	* ev02_116a02.png 0 0
;☆（a01差分をどこで使うかは，よくよく考えて）
.message	1780	kei-213_01-0109	丂宨丂	「跑起来不是很舒服吗」
.message	1790		嫗丂夘	「在，在这世上……有更舒服的事情……」
.transition 0 * 40
.stage	* ev02_116a03.png 0 0
.message	1800	kei-213_01-0111	丂宨丂	「再多说一句无聊的话我就踢你到死」
.message	1810		嫗丂夘	「还真是给出了够具体的的杀害方法啊……」
.transition 0 * 40
.stage	* ev02_116a04.png 0 0
.message	1820	kei-213_01-0113	丂宨丂	「因为我很认真哦」
;☆（ここ，切り出しで？）
.message	1830			新藤笑了一下，望向无垠的大海。
.message	1840		嫗丂夘	「哈～……」
.message	1850		嫗丂夘	「新藤还真是有体力啊。跑了这么久，一点都不累啊」
.message	1860	kei-213_01-0115	丂宨丂	「因为放弃部团活动还不到半年啊」
.message	1870			还在的时候她到底是做着什么样的猛烈练习啊。
.message	1880	kei-213_01-0117	丂宨丂	「膝盖也一点都不痛……这样的话说不定」
.transition 0 * 40
.stage	* ev02_116c01.png 0 0
;☆（わざとこのＣＧ，ここから表示させてます）
.message	1890		嫗丂夘	「返回部团？」
.transition 0 * 40
.stage	* ev02_116b02.png 0 0
.message	1900	kei-213_01-0119	丂宨丂	「…………」
.message	1910			新藤的表情稍微有些困扰。
.message	1920	kei-213_01-0121	丂宨丂	「地方无所谓。只要能够再一次打起篮球，这样就够了……」
.message	1930		嫗丂夘	「你是认真的吗？」
.transition 0 * 40
.stage	* ev02_116c01.png 0 0
;（フェ～ドスピ～ドには注意して）
.message	1940	kei-213_01-0123	丂宨丂	「你这什么意思？」
.message	1950		嫗丂夘	「你不是要做就要做的彻底的吗？　虽然只是玩玩或者打街球也不错，但是我觉得认真的赌出胜负才适合你」
.message	1960	kei-213_01-0125	丂宨丂	「…………」
.message	1970			新藤看了我一眼，表情愈加困扰起来。
.message	1980		嫗丂夘	「选择什么是你的自由。但是我希望新藤你做你真正希望的事」
.transition 0 * 40
.stage	* ev02_116c02.png 0 0
.message	1990	kei-213_01-0127	丂宨丂	「我真正希望的事……？」
.message	2000		嫗丂夘	「啊啊」
.transition 0 * 40
.stage	* ev02_116b02.png 0 0
;☆（手を腰にあてちゃってます，注意して。腕を下ろしてるものを作ってもらう？）
.message	2010	kei-213_01-0129	丂宨丂	「为什么京介前辈能说出这么话？」
.message	2020		嫗丂夘	「说为什么」
.frame *
.transition 0 * 20
.stage	* ev02_116b02.png 0 0
;☆（ここでカメラ下げてます。注意して）
.message	2030			我放下了手中的镜头。
.message	2040			然后，直直的看着还有汗珠偶尔从额头浮起的新藤的脸。
.transition 0 * 20
.stage	* ev02_117a01.png 0 0
;（インのタイミング，注意して）
.message	2050		嫗丂夘	「因为，我喜欢新藤啊」
.playSE AT_umi.ogg true
;（この効果音の挿入位置には注意して）
;■呆然
.transition 0 * 20
.stage	* ev02_118a01.png 0 0
.message	2060	kei-213_01-0131	丂宨丂	「…………」
;■驚き
.message	2070	kei-213_01-0133	丂宨丂	「…………诶？」
.transition 0 * 40
.stage	* ev02_118a02.png 0 0
.message	2080		嫗丂夘	「啊啊，是啊。就是如此。我也才刚刚注意到呢。哈哈哈」
.message	2090	kei-213_01-0135	丂宨丂	「哈哈哈……你」
.message	2100			新藤呆呆的张着嘴，不知该说些什么好。
.message	2110			会呆住也是理所当然的啊。
.message	2120			作为爱的告白，来的也太突然了啊。
.transition 0 * 40
.stage	* ev02_118a03.png 0 0
.message	2130	kei-213_01-0137	丂宨丂	「景」
.message	2140		嫗丂夘	「景？」
;■慌てて
.transition 0 * 40
.stage	* ev02_118a04.png 0 0
.message	2150	kei-213_01-0139	丂宨丂	「不叫我小景了吗？」
.message	2160		嫗丂夘	「那么喊你不是会生气吗」
.message	2170	kei-213_01-0141	丂宨丂	「因为……」
.message	2180	kei-213_01-0143	丂宨丂	「京介前辈开玩笑的时候，不总是带着小字的吗」
.message	2190		嫗丂夘	「就算是我也不能说我喜欢开玩笑吧」
.message	2200	kei-213_01-0145	丂宨丂	「你不是总是在开玩笑的吗……」
.transition 0 * 40
.stage	* ev02_118a05.png 0 0
.message	2210		嫗丂夘	「原来如此，以往的素行遭来的报应啊」
.message	2220			所以到现在都没有好好交往过一次。
.message	2230			都是从朋友开始一点点的变为恋人。
.transition 0 * 20
.stage	* ev02_119a01.png 0 0
.message	2240		嫗丂夘	「那么，我再说一次」
.message	2250	kei-213_01-0147	丂宨丂	「诶……」
.message	2260		嫗丂夘	「我喜欢新藤景」
.transition 0 * 20
.stage	* ev02_120a01.png 0 0
;（この前の，景の台詞でもこのＣＧ挿む？）
.message	2270	kei-213_01-0149	丂宨丂	「…………」
.message	2280			新藤什么都没有回答。
.message	2290			不知该如何回答，不知该往哪里看的眼睛。
.transition 0 * 20
.stage	* ev02_120a01_mugai_a.png 0 0
;（適当な切り出しやな，，，）
.message	2300			只有起伏的海潮轻轻拍打着空气发出阵阵回响。
.panel 0
.playSE *
.playBGM *
.transition 0 * 10
.stage	* WHITE.png 0 0


;■シ～ン転換
;■背景：京介自室（夏，１８時
;■　　　　堤京介　　：制服（夏）
;■　　　　新藤景　　：制服（夏）
;■　　　　宫村宫子：私服（夏）
.playBGM efBGM013.ogg
.transition 1 fadeSide.png 10
.stage	* ev02_121.png 0 0
.panel 1
.message	2310	miy-213_01-0021	傒傗偙	「打扰了～」
.message	2320		嫗丂夘	「真的是打扰了啊」
.message	2330			随着宫村走进房间的我说道。
.message	2340	miy-213_01-0023	傒傗偙	「真失礼啊……」
.message	2350			宫村不满的嘟囔了一句，啪嗒啪嗒地穿过房间，然后坐了下来。
.transition 0 * 20
.stage	* ev02_122a01.png 0 0
;.stage	* ev02_122_dammy.png 0 0
.message	2360	kei-213_01-0151	丂宨丂	「……你好」
;（↓の文章，ちょっと注意して。３人の位置について。まあ，問題ないか）
.message	2370			坐在我面前也是新藤的一边。
.message	2380	miy-213_01-0025	傒傗偙	「你们两个都已经开始了呢。再早些来会好点吧」
.message	2390		嫗丂夘	「啊啊，新藤也已经是进入康复第二日了，便提前结束了」
.transition 0 * 40
.stage	* ev02_122a02.png 0 0
.message	2400	miy-213_01-0027	傒傗偙	「慷父？　慷父啊……能行能行」
.message	2410			你「能行能行」什么啊你。
.message	2420			顺带一提，这个学习会是严禁摄影的。
.message	2430			当然，因为我也在学习不禁止也不行呢。
.transition 0 * 40
.stage	* ev02_122b01.png 0 0
.message	2440	miy-213_01-0029	傒傗偙	「说起来，我有一个十～分重要的问题」
.message	2450		嫗丂夘	「怎么？」
.message	2460	miy-213_01-0031	傒傗偙	「晚饭怎么办？」
.message	2470			新藤也注意到了这点，转头看向我了。
.message	2480		嫗丂夘	「我会适当做点什么的」
.transition 0 * 40
.stage	* ev02_122b02.png 0 0
.message	2490	miy-213_01-0033	傒傗偙	「诶～，堤堤会做料理的吗？」
.message	2500		嫗丂夘	「简单的东西可以。再怎么说不是白独居的啊」
.transition 0 * 40
.stage	* ev02_122c01.png 0 0
.message	2510	miy-213_01-0035	傒傗偙	「说到独居史的话我可不输给你哦」
.message	2520			宫村说着挺起了胸。
.transition 0 * 40
.stage	* ev02_122c02.png 0 0
.message	2530	miy-213_01-0037	傒傗偙	「好了啦，我来做了。材料也已经买了好哦」
.message	2540			上二楼之前擅自去了厨房，是去放材料了吗。
.message	2550		嫗丂夘	「要做什么？」
.message	2560	miy-213_01-0039	傒傗偙	「今天搞到了很不错的康吉鳗鱼，做鳗鱼盖浇饭好了」
.message	2570	miy-213_01-0041	傒傗偙	「刚在家里除过内脏的还很新鲜哦」
.message	2580		嫗丂夘	「除过……你吗？」
.transition 0 * 40
.stage	* ev02_122c03.png 0 0
.message	2590	miy-213_01-0043	傒傗偙	「理所当然的嘛」
.message	2600		嫗丂夘	「鳗鱼就算是生手也可以轻松分解吗？」
.message	2610	miy-213_01-0045	傒傗偙	「我练习过了啊」
.message	2620	kei-213_01-0153	丂宨丂	「练习……」
.message	2630	miy-213_01-0047	傒傗偙	「最开始到还不能做的很好」
.transition 0 * 40
.stage	* ev02_122c04.png 0 0
.message	2640	miy-213_01-0049	傒傗偙	「有让纮君来作试毒，然后试过很多次所以没事的啦！」
.message	2650			试毒的……。
.transition 0 * 40
.stage	* ev02_122c05.png 0 0
.message	2660		嫗丂夘	「你是恶鬼啊你」
.transition 0 * 40
.stage	* ev02_122d01.png 0 0
.message	2670	kei-213_01-0155	丂宨丂	「那个……你对人家的哥哥都作了些什么啊？」
.transition 0 * 40
.stage	* ev02_122d02.png 0 0
.message	2680	miy-213_01-0051	傒傗偙	「但是我现在也成为鳗鱼大师了哦」
.message	2690			这个女人会为了这种事情就利用男朋友吗。
.message	2700			广野那家伙在为工作倒下之前恐怕会因为宫村而被送到医院吧。
.transition 0 * 40
.stage	* ev02_122d03.png 0 0
.message	2710	miy-213_01-0053	傒傗偙	「总之，稍微再学习一会，然后就开饭好了～」
.message	2720		嫗丂夘	「也是」
.message	2730	kei-213_01-0157	丂宨丂	「啊，在此之前我要稍微……」
.transition 0 * 40
.stage	* ev02_122e01.png 0 0
.message	2740		嫗丂夘	「嗯？　怎么了？」
.transition 0 * 40
.stage	* ev02_122e02.png 0 0
.message	2750	kei-213_01-0159	丂宨丂	「呃…嗯……」
.message	2760			新藤憋着说不出来。
.message	2770	miy-213_01-0055	傒傗偙	「洗手间？」
.message	2780	kei-213_01-0161	丂宨丂	「嗯，嗯嗯……」
.message	2790		嫗丂夘	「洗手间的话，下去楼梯就到了哦」
.message	2800	kei-213_01-0163	丂宨丂	「谢，谢谢」
.message	2810			去下洗手间而已，也不必要害羞吧。
.message	2820	miy-213_01-0057	傒傗偙	「小景，要不要我陪你一起去？」
.transition 0 * 40
.stage	* ev02_122f01.png 0 0
.message	2830	kei-213_01-0165	丂宨丂	「不用！」
.playBGM *
.transition 0 * 20
.stage	* ev02_076a02.png 0 0
.message	2840			……………………
.message	2850			…………
.message	2860			……
.transition 0 * 20
.stage	* ev02_123a01.png 0 0
;（ここ，切り出しでイン？）
.message	2870			咚咚咚，随着清脆的足音新藤走下了台阶。
.message	2880	miy-213_01-0059	傒傗偙	「……小景啊」
.message	2890		嫗丂夘	「嗯？」
.message	2900	miy-213_01-0061	傒傗偙	「从我的口中说出纮君的名字时也没有动摇呢」
.message	2910			虽然有感觉在别的意义上有所动摇，不过现在的新藤是由于其他的事而心不在焉而已。
.transition 0 * 40
.stage	* ev02_123a02.png 0 0
.message	2920		嫗丂夘	「那自然，新藤也不可能永远不平静下来啊」
.message	2930	miy-213_01-0063	傒傗偙	「到不如说，我到是心跳了一下呢」
.message	2940		嫗丂夘	「你吗？」
.message	2950	miy-213_01-0064		宫村点了点头。
.message	2960	miy-213_01-0065	傒傗偙	「在听到小景叫纮君“哥哥”的时候，嗯」
.message	2970	miy-213_01-0067	傒傗偙	「纮君和小景之前确实有着羁绊呢。在长长的时间内缠绕起来，绝对无法切断的羁绊」
.message	2980	miy-213_01-0069	傒傗偙	「而且这也是，永久都不会改变的羁绊吧。所以，小景对我来说永远都是对手呢」
.message	2990		嫗丂夘	「那不是该叫小姑子吗？」
;■笑顔
.transition 0 * 40
.stage	* ev02_123a03.png 0 0
.message	3000	miy-213_01-0071	傒傗偙	「好可怕哦」
.message	3010			虽然这么说，宫村的脸上还是有着微微的笑容。
.message	3020			认同对方才算是对手啊。
.message	3030			嘛，这也不是别人的事。
.message	3040			对于我来说的对手就是……广野吧。
.panel 0
.transition 0 * 10
.stage	* ev02_076a02.png 0 0
;.transition 0 * 10
;.stage	* WHITE.png 0 0


;■シ～ン転換
;■背景：京介自室（夏，２１時
;■　　　　堤京介　　：制服（夏）
;■　　　　新藤景　　：制服（夏）
;■　　　　宫村宫子：私服（夏）
.playBGM efBGM042.ogg
;.transition 1 fadeSide.png 10
.transition 0 * 10
.stage	* ev02_076a03.png 0 0
;.stage	* ev02_124a01.png 0 0
;.stage	* ev02_124_dammy.png 0 0
;.stage	* bgc_home002a01_03.png 0 0
.panel 1
.message	3050			由于广野宝贵的牺牲，宫村的手制鳗鱼盖浇饭好吃到让人拍案叫绝。
.transition 0 * 20
.stage	* ev02_124a01.png 0 0
.message	3060	kei-213_01-0167	丂宨丂	「感谢招待」
.message	3070	miy-213_01-0073	傒傗偙	「咦，已经够了吗？」
.transition 0 * 40
.stage	* ev02_124b01.png 0 0
.message	3080		嫗丂夘	「不不，吃盖浇饭还能要添饭的才会让人觉得希奇」
.message	3090	miy-213_01-0075	傒傗偙	「是吗？」
.message	3100			宫村用第二碗鳗鱼盖浇饭塞着脸颊歪头说道。
.message	3110		嫗丂夘	「嘛，我也觉得新藤也多吃一点好。太小了哦，各种意义上」
.transition 0 * 40
.stage	* ev02_124a02.png 0 0
.message	3120	kei-213_01-0169	丂宨丂	「可以把刚才的发言认定成为性骚扰吗？」
.transition 0 * 40
.stage	* ev02_124c01.png 0 0
.message	3130		嫗丂夘	「哎呀哎呀，饭后的小笑话而已嘛」
.transition 0 * 40
.stage	* ev02_124a03.png 0 0
.message	3140	kei-213_01-0171	丂宨丂	「在我面前一句话就可以要了你的命」
;.transition 0 * 40
;.stage	* ev02_124a03.png 0 0
;（このa03の使いどころ，注意して。c01と同じに見えるが？）
.message	3150		嫗丂夘	「刻骨铭记」
.message	3160			我点头如捣蒜。
.transition 0 * 40
.stage	* ev02_124c02.png 0 0
.message	3170	miy-213_01-0077	傒傗偙	「堤堤还真是白痴呢……」
.message	3180	kei-213_01-0173	丂宨丂	「不用说也很清楚的事情」
.message	3190			说的还真是过分啊……。
.panel 0
.transition 0 * 10
.stage	* WHITE.png 0 0


;■シ～ン転換
.transition 1 fadeSide.png 10
.stage	* ev02_125a01.png 0 0
;.stage	* ev02_125_dammy.png 0 0
;.stage	* bgc_home002a01_03.png 0 0
.panel 1
.message	3200			晚饭过后，自然是学习。
.message	3210			宫村把自己的学习扔在一边，热心的指导着新藤。
.message	3220			几乎没有我出场的余地。
.message	3230			然后，差不多过了两个小时──
.transition 0 * 20
.stage	* ev02_125b01.png 0 0
;（フェ～ドスピ～ド注意して）
.message	3240	miy-213_01-0079	傒傗偙	「那么，今天就到底为止吧」
.message	3250			宫村一边整理教科书一边说。
.message	3260		嫗丂夘	「也是」
.message	3270	kei-213_01-0175	丂宨丂	「诶，就要结束了吗？」
.transition 0 * 40
.stage	* ev02_125c01.png 0 0
.message	3280		嫗丂夘	「差不多快九点了啊。宫村也就算了，你还不回去的话就不太好了吧？」
.message	3290	kei-213_01-0177	丂宨丂	「啊，真的呢……」
.message	3300	miy-213_01-0081	傒傗偙	「小景蛮有集中力的嘛。虽然到考试没有多长时间了，这样说不定还能追上不少呢……」
.transition 0 * 40
.stage	* ev02_125d01.png 0 0
.message	3310	kei-213_01-0179	丂宨丂	「……感谢您的教导」
.message	3320	miy-213_01-0083	傒傗偙	「诶？」
.message	3330			看着奇怪地真心低下头的新藤，宫村睁大了眼睛。
.transition 0 * 20
.stage	* ev02_125e01.png 0 0
.message	3340	miy-213_01-0085	傒傗偙	「小景是不是有点怪啊？」
.message	3350			宫村小声对我说悄悄话。
.message	3360		嫗丂夘	「嘛，偶尔也会这样的啦」
.message	3370	miy-213_01-0087	傒傗偙	「是吗……」
.message	3380			而新藤只是整理着教科书和笔记，不发一语。
.panel 0


;■御影チェック
.playBGM *

.transition 0 * 10
.stage	* WHITE.png 0 0


;■シ～ン転換
;■背景：通学路（夏，２１時２０分
;☆（通学路にするかはちょっと保留）
.playBGM efBGM027.ogg
.transition 1 fadeSide.png 10
.overlay	or_miyako03a01_620p.png * *
.screen	sc_night01_620p.png sc_night01_620p.png sc_night01_620p.png
.stage	st_miyako12e01-.png 0 0 bg_scl001a01_03_f.png 0 0 bg_scl001a01_03_n.png 0
;☆（宫子の頭切れてるんで·苦笑，後で差し替えのこと。とりあえずダミ～で一枚だけ使ってます）
.effect	WScroll2 * 60 -2


;.transition 1 fadeSide.png 10
;.stage	* bgs_normal005a01_03.png 0 0
.panel 1
.message	3390			让女孩子两个人走夜路会危险──于是，我就送新藤和宫村回去。
.message	3400		嫗丂夘	「确实很危险啊」
.message	3410		嫗丂夘	「真的有人被外表迷惑袭击这两个人的话，那变态不知道会遭到什么可怕的待遇啊」
.message	3420			新藤就不用提了，也听说了宫村也是运动能力十分优秀的人。
.message	3430			这两个没闸的人如果真的进入战斗模式的话……。
.message	3440			就算是痴汉，被杀也太可怜了。
.transition 0 * 40
.stage	st_miyako11e14-.png 0 0 bg_scl001a01_03_f.png 0 0 bg_scl001a01_03_n.png 0
.message	3450	miy-213_01-0089	傒傗偙	「嘟嘟哝哝说什么呢？」
.message	3460		嫗丂夘	「不，没什么」
.message	3470	kei-213_01-0181	丂宨丂	「那个，宫村前辈」
.message	3480			老老实实走着的新藤，突然张口说道。
.transition 0 * 40
.stage	st_miyako11e15-.png 0 0 bg_scl001a01_03_f.png 0 0 bg_scl001a01_03_n.png 0
;（e13でも？もしくはe08）
.message	3490	miy-213_01-0091	傒傗偙	「嗯？」
;■照れ
.message	3500	kei-213_01-0183	丂宨丂	「我有一个提案」
.message	3510	kei-213_01-0185	丂宨丂	「从明日起，想要在我家和宫村前辈两个人学习」
.message	3520		嫗丂夘	「哎？」
.transition 0 * 40
.stage	st_miyako11e12-.png 0 0 bg_scl001a01_03_f.png 0 0 bg_scl001a01_03_n.png 0
;（目線，注意して）
.message	3530	miy-213_01-0093	傒傗偙	「……这难道是什么陷阱？」
.transition 0 * 40
.stage	st_miyako11e13-.png 0 0 bg_scl001a01_03_f.png 0 0 bg_scl001a01_03_n.png 0
.message	3540	kei-213_01-0187	丂宨丂	「我干吗要到现在了还要对宫村前辈你设什么陷阱！」
.message	3550			以前的话就有理由设陷阱了吗。
.transition 0 * 40
.stage	st_miyako11e08-.png 0 0 bg_scl001a01_03_f.png 0 0 bg_scl001a01_03_n.png 0
.message	3560	kei-213_01-0189	丂宨丂	「不是这回事，一对一更容易集中……。而且，在男生的房间总有些静不下心来」
.message	3570	kei-213_01-0191	丂宨丂	「可以吗？」
.message	3580			在我家这种老爸都不知道是否存在的状态，完全没必要介意的嘛──
.message	3590			正是为这个原因才选择学习会的会场的啊。
.transition 0 * 40
.stage	st_miyako11e16-.png 0 0 bg_scl001a01_03_f.png 0 0 bg_scl001a01_03_n.png 0
.message	3600	miy-213_01-0095	傒傗偙	「我是完全无所谓」
.message	3610	kei-213_01-0193	丂宨丂	「…………」
.message	3620			两个女孩子的视线一起集中到了我的身上。
.message	3630			啊啊，被看着的快感。
.message	3640			不是说这种笑话的时候。
.message	3650		嫗丂夘	「我也没问题」
.message	3660		嫗丂夘	「反正禁止摄影啊，对于我来说只要减少新藤一盏红灯也好」
.message	3670	kei-213_01-0195	丂宨丂	「所以，不要不我会挂红灯说的跟理所当然似……」
.message	3680		嫗丂夘	「那么宫村。那边拜托了」
;■笑顔
.transition 0 * 40
.stage	st_miyako11e06-.png 0 0 bg_scl001a01_03_f.png 0 0 bg_scl001a01_03_n.png 0
;（表情，注意して）
.message	3690	miy-213_01-0097	傒傗偙	「万事放心！」
.message	3700			让人不安的回答啊。
.transition 0 * 40
.stage	st_miyako11e01-.png 0 0 bg_scl001a01_03_f.png 0 0 bg_scl001a01_03_n.png 0
.message	3710	miy-213_01-0099	傒傗偙	「那么，从明天开始就这样」
.transition 0 * 40
.stage	st_miyako11e03-.png 0 0 bg_scl001a01_03_f.png 0 0 bg_scl001a01_03_n.png 0
.message	3720	miy-213_01-0101	傒傗偙	「我先走一步回去了。再见」


;■御影チェック
;.effect *
.effect end

.overlay	* * *
.screen	* * *
.transition 0 * 20
.stage	* ev02_127a01.png 0 0
.message	3730			说着宫村就已经跑了出去，不一会就已经看不到人了。
.message	3740		嫗丂夘	「那家伙到底是什么人啊？」
.message	3750	kei-213_01-0197	丂宨丂	「请不要问我」
.message	3760			新藤仍然冷冷淡淡。
.message	3770			一直如此了。
.message	3780		嫗丂夘	「那么，接下来就向新藤家前进──」
.transition 0 * 20
.stage	* ev02_127b01.png 0 0
;（フェ～ドスピ～ドは注意して）
.message	3790	kei-213_01-0199	丂宨丂	「那个，前辈」
.message	3800		嫗丂夘	「怎么？」
.message	3810	kei-213_01-0201	丂宨丂	「稍微，散下歩好吗？」
.panel 0
.transition 0 * 10
.stage	* WHITE.png 0 0


;■シ～ン転換
;■背景：教会前（夏，２１時３０分
.screen sc_night01.png sc_night01.png
.transition 1 fadeSide.png 10
.stage	* ev02_128.png 0 0
;.stage	* bgs_normal011a01_03.png 0 600
.panel 1
.message	3820		嫗丂夘	「夜里的教会有些恐怖呢～」
.message	3830	kei-213_01-0203	丂宨丂	「京介前辈也会说普通人一样的话啊」
.message	3840		嫗丂夘	「我也是普通人啊」
.message	3850			城市静寂无声，路上也没有一个人影。
.message	3860			在现在这个时间，白天的热气也凉爽下来，微风拂过让人舒心无比。
.message	3870	kei-213_01-0205	丂宨丂	「……前辈，没有拿摄像机吗？」
.message	3880		嫗丂夘	「再说也算是作护卫嘛。拿着摄像机我不就麻烦派不上用场了嘛？」
.message	3890	kei-213_01-0207	丂宨丂	「不拿也一样派不上用场啊。因为我比你更强」
.message	3900		嫗丂夘	「啊啊，我男人的自尊心被重重的伤害了……」
.message	3910	kei-213_01-0209	丂宨丂	「不存在的东西怎么可能受伤嘛」
.message	3920		嫗丂夘	「…………」
.message	3930			真是说话不留情啊。
.message	3940			双胞胎的妹妹据说是很乖巧的，后天形成的吗。
.message	3950	kei-213_01-0211	丂宨丂	「没在想什么失礼的事吧？」
.message	3960		嫗丂夘	「属下不敢」
.message	3970	kei-213_01-0213	丂宨丂	「你根本不会撒谎呢。想的事情太容易被看出来了」
.message	3980		嫗丂夘	「虽然我喜欢开玩笑但我从不撒谎哦」
.message	3990		嫗丂夘	「撒谎之后要圆场麻烦的很，我才不想浪费这种时间」
.message	4000	kei-213_01-0215	丂宨丂	「…………」
.message	4010			在黑暗中，她陷入了思考。
;■照れ
.message	4020	kei-213_01-0217	丂宨丂	「果然那句话也不是撒谎吧……？」
.message	4030		嫗丂夘	「当然。你如果有疑问的话让我说几次都可以」
.message	4040	kei-213_01-0219	丂宨丂	「啊……」
.message	4050			我踏近一歩，新藤也迅速的后退了一下。
.message	4060	kei-213_01-0221	丂宨丂	「呃，呃嗯……」
.message	4070			就算在黑暗中也能明显的看出她脸上的红潮。
.message	4080	kei-213_01-0223	丂宨丂	「疑，疑问我没有啦，只是……」
.message	4090		嫗丂夘	「只是？」
.message	4100			我直直地凝视着新藤。
.message	4110			虽然确实是自作自受，但我也会不停地说下去知道她相信我的话为止。
.message	4120			因为我从来没有这么认真过。
.message	4130	kei-213_01-0225	丂宨丂	「为什么是我呢？」
.message	4140			为什么，吗……。
.message	4150		嫗丂夘	「谁知道呢，虽然这我也不懂……但如果硬要说的话」
.message	4160		嫗丂夘	「因为你和我不同」
.message	4170	kei-213_01-0227	丂宨丂	「不同？」
.message	4180		嫗丂夘	「对，你不是承认了自己受过伤的事实吗？」
.message	4190	kei-213_01-0229	丂宨丂	「……就算否定也没用吧。因为这是事实啊」
.message	4200		嫗丂夘	「我离开摄影研究会，被女朋友抛弃，我没有直面这份痛楚而是假装忘记」


;■御影チェック
;.message	4210		嫗丂夘	「それは俺が弱いから。傷ついて，惨めな自分を見る勇気なんてなかった……」
.message	4210		嫗丂夘	「这就是我的弱点」
.message	4215		嫗丂夘	「没有勇气看着伤痕累累的自己……」

.message	4220		嫗丂夘	「但是，你却不同。虽然有着悲伤的过分，却好好的接受了它不是吗」
.message	4230	kei-213_01-0231	丂宨丂	「这个……」
.message	4240			我与研究部的大家一起拍摄电影时非常快乐。
.message	4250			在那里的她既是一个朋友，也是我重要的恋人。
.message	4260			我分明已经同时失去了一切──
.message	4270		嫗丂夘	「失去重要的东西会痛苦万分。我却没有承认这本该是理所当然的事实」
;■真剣
.message	4280	kei-213_01-0233	丂宨丂	「但是……」
.message	4290	kei-213_01-0235	丂宨丂	「但是，京介前辈不是并不回头而望向前方了吗。这个普通人是做不到的啊」
.message	4300		嫗丂夘	「啊」
.screen * *
.transition 0 * 20
.stage	* ev02_129a01.png 0 0
.message	4310	kei-213_01-0237	丂宨丂	「诶，干，干吗啊」
.message	4320			我唰的靠近了新藤的脸。
.message	4330		嫗丂夘	「你也认同了我吗？」
.transition 0 * 40
.stage	* ev02_129a04.png 0 0
;（表情，注意して）
.message	4340	kei-213_01-0239	丂宨丂	「不，不是这回事」
.message	4350			新藤红着脸手忙脚乱起来。
.transition 0 * 40
.stage	* ev02_129a01.png 0 0
;（表情，注意して）
.message	4360	kei-213_01-0241	丂宨丂	「认，认同你也可以……。但这个和那个不一样」
.message	4370		嫗丂夘	「这个和那个是指什么？」
.transition 0 * 40
.stage	* ev02_129a02.png 0 0
;（フェ～ドスピ～ドは20で？）
.message	4380	kei-213_01-0243	丂宨丂	「对我，那个，喜，喜欢的……」
.message	4390		嫗丂夘	「嗯」
.message	4400	kei-213_01-0245	丂宨丂	「就算你说什么『嗯』……」
.message	4410		嫗丂夘	「我说啊，新藤」
.transition 0 * 40
.stage	* ev02_129a03.png 0 0
;（「うん，って言われても」でこの表情に？）
.message	4420			我一次又一次的摇头。
.message	4430			虽然能想出各种各样的理由，那样就不是我了。
.message	4440		嫗丂夘	「一旦喜欢上一个人，“为什么”什么的就已经不再重要了」
.message	4450		嫗丂夘	「不需要去说明什么理由，只想让你明白我真正的心情」
.message	4460			新藤赤红着脸低下了头。
.transition 0 * 40
.stage	* ev02_129a04.png 0 0
.message	4470	kei-213_01-0247	丂宨丂	「再怎么说……也太突然了啊」
.message	4480		嫗丂夘	「刚才也提到了，有一个到初春还在交往的女孩子」
.transition 0 * 40
.stage	* ev02_129a05.png 0 0
.message	4490	kei-213_01-0249	丂宨丂	「……诶？」
.message	4500		嫗丂夘	「虽然现在想起来完全没有重视她，但我仍然喜欢她」
.message	4510			我一度回到摄影研究会，一定是我还对她有些在意吧。
.message	4520			虽然觉得有些自说自话的感觉，但我现在才这样想。
.message	4530		嫗丂夘	「所以被她抛弃会痛苦无比，真的。虽然这份痛苦的感情已经被掩盖掉了」
.message	4540		嫗丂夘	「但是我已经再也不想尝到那种痛苦。这次我要真正的，重视自己喜欢的人」
.message	4550			我仅仅看着新藤一个人，继续说着。
.message	4560		嫗丂夘	「新藤，我喜欢你」
.message	4570			我的话能够传达给她多少我不知道。
.message	4580			但是如果不说的话就什么也不会开始。
.message	4590			所以我，无论多少次都会说下去。
.message	4600			无论多少次。
.transition 0 * 40
.stage	* ev02_129a04.png 0 0
;（表情，注意して）
.message	4610	kei-213_01-0251	丂宨丂	「我……该怎么办」
.message	4620			新藤像和父母走散了的孩子一样，眼神里充满着不安。
.message	4630			实际根本不知道自己该怎么办的吧。
.transition 0 * 40
.stage	* ev02_129a03_close.png 0 0
;.transition 0 * 40
;.stage	* ev02_129a06.png 0 0
.message	4640	kei-213_01-0253	丂宨丂	「京介前辈你」
.transition 0 * 40
.stage	* ev02_129a06.png 0 0
.message	4650	kei-213_01-0255	丂宨丂	「前辈你……」
.message	4660	kei-213_01-0256		新藤突然咬住了自己的嘴唇。
.transition 0 * 40
.stage	* ev02_129a07.png 0 0
.message	4670	kei-213_01-0257	丂宨丂	「好不容易要忘记掉了，为什么又说些让我不知所措的话啊！」
.transition 0 * 40
.stage	* ev02_129b01.png 0 0
.message	4680	kei-213_01-0259	丂宨丂	「京介大笨蛋！！」
.transition 0 * 20
.stage	* ev02_129b01_mugai_a.png 0 0
.message	4690			突然就去掉称呼吗。
.transition 0 * 20
.stage	* ev02_128_mugai.png 0 0
.message	4700			毫不斜视的，新藤便从我眼前跑着离开了。
.message	4710		嫗丂夘	「真是够呛啊……」
.screen * *
.transition 0 * 20
.stage	* ev02_130a01.png 0 0
.message	4720	yuk-213_01-0003	桪丂巕	「那个～」
.transition 0 * 40
.stage	* ev02_130a02.png 0 0
;（京介の表情変化，注意して）
.message	4730		嫗丂夘	「你在啊，雨宫」
.message	4740	yuk-213_01-0005	桪丂巕	「虽然无所谓，但在教会前不要太吵的好哦」
.message	4750		嫗丂夘	「无所谓的话就给我闭嘴。现在正是戏剧性情节中」
.transition 0 * 40
.stage	* ev02_130a03.png 0 0
;（京介の表情変化，注意して）
.message	4760		嫗丂夘	「抱歉，没有无关人士的出场」
.message	4770	yuk-213_01-0007	桪丂巕	「啊啦好过分呢。我是无关人士吗」
.message	4780			雨宫用平静的表情说道。
.transition 0 * 40
.stage	* ev02_130b01.png 0 0
;（フェ～ドスピ～ドには注意して。20で？）
.message	4790		嫗丂夘	「感觉你总是跟我们维持着若即若离的关系，很可疑啊」
;■微笑
.transition 0 * 40
.stage	* ev02_130b02.png 0 0
.message	4800	yuk-213_01-0009	桪丂巕	「这还真是让人感兴趣的意见呢」
.message	4810		嫗丂夘	「感觉你就像电影导演似的」
.message	4820		嫗丂夘	「也指导演员该怎么做，也和人家谈心，但却永不站在镜头之前──连配角都不肯做」
.message	4830	yuk-213_01-0011	桪丂巕	「说到这点，你不也一样吗？」
.message	4840			说不定是这样没错。
.message	4850			所以，我这次才要。
.message	4860		嫗丂夘	「踏入我该踏入的地方」
.message	4870		嫗丂夘	「不要通过镜头，而是想和新藤站在同样的地方看同样的东西」
.transition 0 * 40
.stage	* ev02_130b03.png 0 0
;（表情，注意して）
.message	4880	yuk-213_01-0013	桪丂巕	「这样是好事呢」
.message	4890		嫗丂夘	「嗯……？」
.transition 0 * 40
.stage	* ev02_130b04.png 0 0
;（この表情は次の台詞で？ただ，だとしたらここはb03を続行させるか，目を開かせるb02にするか？）
.message	4900	yuk-213_01-0015	桪丂巕	「主角在镜头外的话，故事就无法进展了呢」
.message	4910	yuk-213_01-0017	桪丂巕	「因为，这是你和新藤小姐的故事啊」
.message	4920			雨宫优子嘴角浮起一丝微笑。
.message	4930			见到她的这个笑脸是第一次也说不定……。
.message	4940		嫗丂夘	「是啊，没错呢……」
.message	4950			这个才是我所追求的真实。
.message	4960			仅仅在电影中捕捉虚构的她的话，所无法满足的感情。
.message	4970			我突然想到，说不定。
.message	4980			那时，最初在体育馆看到新藤景的时候──
.message	4990			我并不仅仅是想要拍摄她。
.message	5000			而是，在那个瞬间。
.message	5010			──我已经爱上了她了吧。
.panel 0
.playBGM *
.transition 0 * 10
.stage	* WHITE.png 0 0
.transition 0 * 10
.stage	* WHITE.png 0 0
.wait 100

.chain 214_01.sc
;■214_01へ。

;.end
