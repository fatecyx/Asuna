; ファイル: 114_01.txt
;■＜１章：１４日目＞
;■背景：纮自室（冬，１６時
;■　　　　広野纮：制服（冬）
.playBGM efBGM024.ogg
.transition 0 * 10
.stage	* ev01_171a01_mugai.png 0 0
;.stage	* bgc_home010a01_02.png 0 0
;☆（物の位置が変わっているので，171の纮がいないバ～を用意してもらうこと）
;.stage	* ev01_171a01.png 0 0
.panel 1
.message	100		丂峢丂	「呼～」
.playSE hiro_yatsuatari_a.ogg f 0 *
.transition 0 * 20
.stage	* ev01_171a01.png 0 0
.message	110			扔下提包坐在地板上。
.message	120			今天也是整天一天，认真的从第一节课上到了最后。
.message	130			虽然只是作理所当然的事而已，但果然累啊。
.message	140			而且现在开始不得不工作……。
.message	150		丂峢丂	「啊～，一点都不想干」
.message	160			不知为何毫无干劲。
.message	170			大脑呆滞下来，身体也软绵绵的。
.message	180		丂峢丂	「不行啊……」
.message	190			从那天以来，一直都没怎么再和宫子和景说过话。
.message	200			因为完全不知道该说什么。
.message	210			都到了这个时候，为什么还会感到恐惧。
.message	220			虽然知道不是烦恼的时候，但却什么都做不到。
.message	230			什么都作不到──
.message	240			只是讨厌着自己的无力，讨厌着除了怨恨自己无力以外什么都作不到的自己，讨厌着讨厌着。
.message	250		丂峢丂	「啧！」
.playSE hiro_yatsuatari_b.ogg f 0 *
.message	260			对着地板上堆积的书和信封泄怒。
.message	270			虽然明白这什么意义都没有，但却停不下来。
.message	280		丂峢丂	「可恶！」
.playSE hiro_yatsuatari_b.ogg f 0 *
;（音変える？）

;■御影チェック
;■　動作を削っておけば，つなぎは問題なくなるかと。
;.message	290			立ち上がって，辺りに転がっている物を次々と蹴飛ばす。
.message	290			一个接一个踢飞滚到身边的东西。

.message	300			什么都做不好。
.message	310			无论做什么事都只会有坏的结果。
.message	320			都是我的错。
.message	330			就算伤害自己也没有意义。
.message	340			也对宫子那么说了，但为什么不能停止责备自己呢！

;■御影チェック
;■　ＣＧの区切りはこちらかと。
.transition 0 * 20
.stage	* ev01_171b01.png 0 0

.message	350		丂峢丂	「……哈」
;;（このＣＧの挿入位置をここにしてますが，切り出しなどの演出も考えつつ，再考のこと）
;.transition 0 * 20
;.stage	* ev01_171b01.png 0 0
.message	360			环视散乱的房间。
.message	370			什么都变的一团糟……什么东西在哪之类完全都不知道了。
.message	380		丂峢丂	「可恶！」
.panel 0
.transition 0 * 10
.stage	* WHITE.png 0 0


;■ＳＥ：ドアが開く音。
;■背景：公園（冬，１７時
;■　　　　広野纮　　：制服（冬·外出）
;■　　　　羽山瑞希：制服（冬·外出）
.screen sc_evening01.png sc_evening01.png
.transition 1 fadeSide.png 10

;■御影チェック
;■　空が続いてしまいますが，それでも空インのほうが自然そうです。
.stage	* bgs_sky001a01_02_mugai_a.png 0 0
;.stage	* ev01_172a01.png 0 0
;（とりあえず，イベントＣＧで処理しています。問題あるようなら，やはり空インで）
;（とりあえず空を挿んでますが，再考のこと）

.panel 1
.message	390			哪儿都不会去。
.message	400			也没有可以回去的地方。
.message	410			那个确实是和──世界中孤独一人同样。
.message	420			现在，宫子也是同样的心情吗。
.message	430			景呢……？
.message	440			越想越不明白。

;■御影チェック
.transition 0 * 20
.stage	* ev01_172a01.png 0 0

.message	450			大脑一片混乱，右手一跳一跳的疼痛──呼吸都快要停止了。

;■御影チェック
;■　話の重いタイミングで急に優子ＢＧＭを鳴らすと微妙な感じ。
;■　そこで，出だしから鳴らしておく方向に。
;■　前フリで，ここで曲を止める。
.playBGM *

.transition 0 * 20
.stage	* ev01_172b01.png 0 0
;（フェ～ドスピ～ドには注意のこと）
.message	460	mid-114_01-0003	儈僘僉	「咦～？」
;■ベンチあるのか？
.transition 0 * 20
.stage	* ev01_172c01.png 0 0
;（フェ～ドスピ～ドには注意のこと）
.message	470			啪的从椅子上站起来的是──
.message	480	mid-114_01-0005	儈僘僉	「纮前～辈！」
.message	490		丂峢丂	「……怎么，原来是你啊」
.message	500			说着话我稍微有了些安心感。
.message	510			一直都只会让我觉得吵闹的羽山的存在，现在倒值得感谢。
.message	520			羽山和现在我的事情没有牵连，可以轻松的说些话的吧。

;■御影チェック
;■　下のほうでこのＢＧＭを消しているのだが，ここで鳴らすとどうだ？
;■　纮も気が楽だと言ってるし，ここなら違和感はそうないか。
;■　まあ，ここよりも２章で，京介が笑みが似ていると指摘している
;■　シ～ンで鳴らすべきだと思う。
.playBGM efBGM017_2.ogg

.overlay * or_mizuki02a.png
.transition 0 * 20
.stage	* bgw_normal009a01_02_stm.png 0 0 stm_mizuki_a05a03.png 300
.message	530	mid-114_01-0007	儈僘僉	「『怎么』，不觉得过分吗。对着这么可爱的后辈说这种话」
.message	540		丂峢丂	「可爱吗……？　够微妙的啊」
.transition 0 * 40
.stage	* bgw_normal009a01_02_stm.png 0 0 stm_mizuki_a02a04.png 300
.message	550	mid-114_01-0009	儈僘僉	「哇～，真的好过分啊！」
.message	560			故意的装哭啊……。
.message	570			这种程度的演技，可骗不到你将来的男人哦。
.transition 0 * 40
.stage	* bgw_normal009a01_02_stm.png 0 0 stm_mizuki_a02a02.png 300
.message	580	mid-114_01-0011	儈僘僉	「然，纮前辈是在散步吗？」
.message	590			切换真快啊。
.message	600		丂峢丂	「嘛，也就那回事。换换心情而已」
.message	610		丂峢丂	「你在这干吗呢。来这偷看调情中的情侣的吗？」
.transition 0 * 40
.stage	* bgw_normal009a01_02_stm.png 0 0 stm_mizuki_a02a04.png 300
.message	620	mid-114_01-0013	儈僘僉	「才不是呢！」
.message	630			羽山生气的喊着，把一本厚厚的书塞给了我。
.transition 0 * 40
.stage	* bgw_normal009a01_02_stm.png 0 0 stm_mizuki_a01a06.png 300
.message	640	mid-114_01-0015	儈僘僉	「我在读这个」
.message	650		丂峢丂	「…………」
.message	660			那是刊登有我的作品的少女漫画杂志。
.transition 0 * 40
.stage	* bgw_normal009a01_02_stm.png 0 0 stm_mizuki_a01a02.png 300
.message	670	mid-114_01-0017	儈僘僉	「今天只有基础练习就结束了」
.message	680			然后就去了商店街，买了刚出刊的杂志在公园埋头读起来了的样子。
.message	690		丂峢丂	「那种东西回家慢慢读啊」
.transition 0 * 40
.stage	* bgw_normal009a01_02_stm.png 0 0 stm_mizuki_a02a01.png 300
.message	700	mid-114_01-0019	儈僘僉	「虽然是这么回事，但稍微有些等不及回去……然后呢，正好走到了公园，就…」
.message	710		丂峢丂	「我说你，毎个月都这样啊」
.message	720			连回家这点时间都忍不住吗。
.transition 0 * 40
.stage	* bgw_normal009a01_02_stm.png 0 0 stm_mizuki_a03a06.png 300
.message	730	mid-114_01-0021	儈僘僉	「没什么不可以吧。部团活动以外，人家唯一的兴趣啊」
.screen * *
.transition 0 * 20
.stage	* ev01_173a01.png 0 0
;☆（ベンチにカバンがないぜ，，，）
.message	740			乖戾的说着，羽山又坐到了椅子上，无视我读起杂志来。
.message	750		丂峢丂	「我也坐在这儿可以吗？」
.transition 0 * 40
.stage	* ev01_173b01.png 0 0
.message	760	mid-114_01-0023	儈僘僉	「请我喝奶茶」
.message	770			羽山眼睛不离杂志，而把手指向了一边。
;（「目を落としたまま」，，，ビジュアルには注意のこと）
.transition 0 * 20
.stage	* ev01_174.png 0 0
;（フェ～ドスピ～ドには注意のこと）
.message	780			那边的是一台饮料自助贩售机。
.message	790			仅仅是坐公园的椅子而已，为什么我还非得请羽山喝饮料啊。
.message	800		丂峢丂	「…………」
.playSE zidouhanbaiki.ogg f 0 *
.message	810			但是，最后还是买了就是我的弱点吧。
.transition 0 * 20
.stage	* ev01_173c01.png 0 0
;（次の台詞文でミスギの顔を上げさせ，ここは切り出しで？）
.message	820		丂峢丂	「拿着」
.message	830	mid-114_01-0025	儈僘僉	「哇，没想到真的会买啊」
.message	840		丂峢丂	「这小丫头，你说啥」
.transition 0 * 40
.stage	* ev01_173c02.png 0 0
.message	850	mid-114_01-0027	儈僘僉	「说笑而已啦。请坐，请坐。需要我铺手帕给您吗？」
.message	860		丂峢丂	「免了」
;（ここの箇所の演出，注意のこと）
.message	870			在羽山旁边坐了下来，掀开自己喝的罐装咖啡。
.transition 0 * 20
.stage	* ev01_175a01.png 0 0
.message	880	mid-114_01-0029	儈僘僉	「啊～，身体好暖和呢」
.message	890			羽山咕咚喝下一大口奶茶，笑了起来。
.message	900		丂峢丂	「那就好」
.transition 0 * 40
.stage	* ev01_175b01.png 0 0
;（フェ～ドスピ～ドは20で？ミルクティ～片手に，，，でまあ片手画面に映ってないからいいのか）
.message	910			羽山把奶茶一只手拿着，啪啦啪啦的翻动着书页。
.message	920			虽然我明白你是确实喜欢少女漫画，但也别一直笑着好吧。
.message	930			一个人嘻嘻笑着读漫画，从旁边看起来很诡异啊。
.message	940			嘛，对于作家来说，这总比读者用一副无聊的表情看下去好。
.transition 0 * 40
.stage	* ev01_175b02.png 0 0
.message	950	mid-114_01-0030		羽山偶尔小声的笑起来，完全无视我的存在继续翻动着书页──
.message	960		丂峢丂	「…………」
.message	970			然后，读到了我的作品，正以为她要看最初的2页的时候──
.message	980		丂峢丂	「啊」
.message	990			没有读之后的几页，而直接跳过去了。
.transition 0 * 40
.stage	* ev01_175c01.png 0 0
;.stage	* ev01_175c04.png 0 0
;（ここのフェ～ドスピ～ドは20？ここはコンテ指定どおり，きょとんではなくノ～マルでいくか，，，）
.message	1000	mid-114_01-0031	儈僘僉	「嗯？　怎么了吗？」
.message	1010		丂峢丂	「没，没什么。在想…没读那个漫画啊」
.message	1020			咚咚的心跳加速到无法相信的地步。
.message	1030			无法相信眼前的事实。
.message	1040			不想相信，不想看下去──心脏传来阵阵悲鸣。
.transition 0 * 40
.stage	* ev01_175c02.png 0 0
;（この差分，悲しそうに笑ってるか，，，？）
.message	1050	mid-114_01-0033	儈僘僉	「啊啊，这个吗」
;■御影チェック
;.message	1060			羽山はちょっと悲しそうに笑って，
.message	1070	mid-114_01-0035	儈僘僉	「这个的作者呢，叫做新堂凪先生」
.message	1080	mid-114_01-0037	儈僘僉	「这个人的作品，本来是很喜欢的。最近不知为何绘画和剧情都有一点……于是，就跳过去了」
.message	1090	mid-114_01-0039	儈僘僉	「就是因为喜欢，该说是画了无聊的东西有些心痛还是……就读不下去了」
.message	1100		丂峢丂	「是这样吗」
.message	1110			我拼命的抑制住自己的动摇，挤出这么一句话。
.transition 0 * 40
.stage	* ev01_175c01.png 0 0
;（ここ，c03で？）
.message	1120	mid-114_01-0041	儈僘僉	「但是我相信着。谁都会有状态不好的时候。新堂凪先生肯定也一样吧」
.message	1130		丂峢丂	「是吗……能再有趣起来就好了啊」
.transition 0 * 40
.stage	* ev01_175c03.png 0 0
.message	1140	mid-114_01-0043	儈僘僉	「嗯」
.transition 0 * 20
.stage	* ev01_176a01.png 0 0
;（挿入位置は注意のこと）
.message	1150			涌上心头的是──比起灰心更多的是对自己的愤怒。
.message	1160			对于什么都做不到的自己，没有干劲到可笑地步的自己的厌恶。
.transition 0 * 20
.stage	* ev01_176b01.png 0 0
;（フェ～ドスピ～ドには注意）
.message	1170			紧紧握起右拳。
.message	1180			我真的是什么都──没有作到。
.message	1190			不只宫子和景的事情。
;■御影チェック
;.playBGM *
.message	1200			自己所选择的，持续着的梦想──也是半吊子而已。
.message	1210		丂峢丂	「那个，羽山」
.message	1220			我压抑着激烈涡旋着的心情，张开了嘴。
.transition 0 * 20
.stage	* ev01_175c01.png 0 0
;（ここも「きょとん」ではなく「ノ～マル」で問題ないか？）
.message	1230	mid-114_01-0045	儈僘僉	「嗯？」
.message	1240		丂峢丂	「学校，快乐吗？」
.transition 0 * 40
.stage	* ev01_175c03.png 0 0
.message	1250	mid-114_01-0047	儈僘僉	「当然啦<音乐符号>」
.message	1260	mid-114_01-0049	儈僘僉	「不但有好多的朋友，如果升学的话还有景前辈呢」
.transition 0 * 40
.stage	* ev01_175c06.png 0 0
;（次の台詞文で，この表情？）
.message	1270			一瞬，羽山的脸上覆上一层阴影。

;■御影チェック
;.message	1280	mid-114_01-0051	儈僘僉	「景前辈は最近元気がないみたいですけど……」
.message	1280	mid-114_01-0051	儈僘僉	「……虽然景前辈最近没什么精神的样子」

.message	1290		丂峢丂	「…………」
.transition 0 * 40
.stage	* ev01_175c05.png 0 0
.message	1300	mid-114_01-0053	儈僘僉	「但是但是，只要我在她身边就不会给她把脸色沉闷下去的机会，粘在前辈身边去洗手间也在同一个小房间里──」
.message	1310		丂峢丂	「你还真是变态啊。这么年轻就已经爬升到如此神奇的层次了啊……」
.transition 0 * 40
.stage	* ev01_175c06.png 0 0
.message	1320	mid-114_01-0055	儈僘僉	「我说笑而已啦……」
;（ここの表情は要注意）
.message	1330	mid-114_01-0057	儈僘僉	「不过我呢，想要让景前辈笑起来」
.message	1340		丂峢丂	「那去作艺人怎么样？　当艺人的话说不定还会被说可爱哦」
.transition 0 * 40
.stage	* ev01_175c07.png 0 0
.message	1350	mid-114_01-0059	儈僘僉	「刚才说的话在各种意义上很失礼哦。倒是，别再提我的相貌问题好吧」
.message	1360			嘛，认真的说羽山还是很可爱的。
.message	1370			附加条件，如果不说话的话。
.transition 0 * 40
.stage	* ev01_175c01.png 0 0
;（ここ，表情は「ノ～マル」でいいか？）
.message	1380	mid-114_01-0061	儈僘僉	「认真的讲，我这么想」
.message	1390		丂峢丂	「什么？」

;■御影チェック
;.playBGM efBGM017_2.ogg

.transition 0 * 40
.stage	* ev01_175c08.png 0 0
.message	1400	mid-114_01-0063	儈僘僉	「学校不是快乐的东西，而是要去寻找快乐的东西」
.message	1405	mid-114_01-0064	儈僘僉	「我现在很快乐，也急切地期待着以后会发生的事情」
;.message	1400	mid-114_01-0063	儈僘僉	「学校は楽しいものじゃなくて，楽しくするものです。わたしは今楽しいし，これからのことも楽しみでしょうがないんです」
.message	1410			羽山浮起向日葵般的笑容──好像真的很快乐的样子。
.message	1420			这家伙还真的是天真无邪啊……。
.message	1430			虽然这份天真的光亮闪得我睁不开眼睛。
.message	1440		丂峢丂	「是啊，是这么回事」
.message	1450			但羽山的话却是事实。
.message	1460		丂峢丂	「我也不只是为了保证自己的将来而去学校而已。因为那儿让我愉快，让我有舒适的安心感啊」
.transition 0 * 40
.stage	* ev01_175c04.png 0 0
;（ここで「きょとん」で良いか？）
.message	1470	mid-114_01-0065	儈僘僉	「……纮前辈？」
.message	1480			就算工作辛苦，也坚持着学园的到勤。
.message	1490			那是虽然经常逃课，但只要去就接受我的一个存在。
.message	1500			这个存在，对我算是多大的救赎呢。
.message	1510			每个人都会想要自己的容身之处。
.message	1520			然后守护这个容身之处。
.message	1530			并不是只有宫子。
.message	1540			还有我，还有景。
.message	1550			但是总会有那么一天──不得不离开让自己安心的地方的一天。
.message	1560			那个时候，该作什么好呢。
.message	1570			为了要守护我重要的东西，
.message	1580			虽然重要的东西不只一个。
.message	1590			但是，如果能够去守护的重要之物有数量的限制的话──
.message	1600		丂峢丂	「羽山」
.message	1610	mid-114_01-0067	儈僘僉	「嗯？」
.message	1620		丂峢丂	「谢谢了」
.transition 0 * 40
.stage	* ev01_175c09.png 0 0
;（ここで09表情でいいのか？，，，まあ，こういう表情もアリか。その場合，「…………」と「はい？」の二文に分けるのも良いのやも）
.message	1630	mid-114_01-0069	儈僘僉	「……嗯？」
.panel 0
.overlay * *
.playBGM *
.transition 0 * 10
.stage	* WHITE.png 0 0
.transition 0 * 10
.stage	* WHITE.png 0 0
.wait 100

.chain 115_01.sc
;■115_01へ。

;.end
