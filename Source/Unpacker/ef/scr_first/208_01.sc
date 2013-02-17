; ファイル: 208_01.txt
;■＜２章：８日目＞
;■背景：京介自室（夏，７時
;■　　　　堤京介　：私服（夏）
.transition 0 * 10
.stage	* WHITE.png 0 0
.panel 1
.message	100			啾啾啾啾……啾啾啾啾……。
.message	110		嫗丂夘	「嗯……」
.message	120			微弱的鸟鸣，以及见缝即插的日光叫醒了我。
.transition 0 * 20
.stage	* ev02_065.png 0 0
;（インのタイミング，注意して）
.message	130		嫗丂夘	「真热～啊……」
.message	140			从床上坐起身，穿在身上的T恤由于汗而紧紧帖在身上。
.message	150			还有时间，去洗个澡好了。
.transition 0 * 20
.stage	* bgc_home002a01_00_mugai_a.png 0 0
.message	160		嫗丂夘	「哟嗯」
.message	170			站起身来，脱掉被汗浸透的T恤。
.message	180		嫗丂夘	「…………」
;■ＳＥ：カ～テンを開ける音。
;何か画面効果必要。
;■空
.transition 0 * 20
.stage	* bgs_sky001a01_00.png 0 0
.message	190			窗外是透彻清丽的一片苍蓝。
.message	200			仿佛无垠的天空。
.message	210			鸟儿的声音温柔的回响，微风抚过树叶轻轻摇动。
.message	220		嫗丂夘	「世界真美丽……啊」
.message	230			把这个风景──只会把世界切成电影的我到底算什么啊。

;■回想
;.transition 1 fadeGray.png 20
.transition 1 fadeCircle.png 20
.stage	* ev02_066a01.png 0 0
.message	240	yuk-208_01-0003	桪丂巕	『你真的恋爱过吗？』

;.transition 1 fadeGray.png 20
.transition 1 fadeCircle.png 20
.stage	* bgs_sky001a01_00.png 0 0
.message	250			谁知道呢，究竟怎样呢？

;■回想
;.transition 1 fadeGray.png 20
.transition 1 fadeCircle.png 20
.stage	* ev02_066b01.png 0 0
.message	260	kei-208_01-0003	丂宨丂	『时间不停流逝，不能一直止步不前呢』

;.transition 1 fadeGray.png 20
.transition 1 fadeCircle.png 20
.stage	* bgs_sky001a01_00.png 0 0
.message	270			当然如此。
.message	280			想要忘记的事情，忘掉就好。
.message	290			至少我一直都是这样。
.message	300			忘记日常的琐事，逃进电影的世界里面。
.message	310			擅长忘掉那些讨厌的事情，麻烦的事情。
.message	320			但是现在，却好像有什么开始摇晃。
.message	330			有什么确实地在……。
.panel 0
.transition 0 * 10
.stage	* WHITE.png 0 0


;■背景：教室（夏，１１時
;■　　　　堤京介　　：制服（夏）
;■　　　　宫村宫子：制服（夏）
.playBGM efBGM010.ogg
;■御影チェック
;■　ちょっと遅すぎるな。
;■　直前の展開があるにせよ，ギャグ曲をかけるからには早めに。
;.transition 1 fadeSide.png 10
.transition 1 fadeSide.png 20
.stage	* ev02_067a01_mugai_a.png 0 0
;.stage	* bgs_sch004m01_01.png 0 0
;（教壇に先生がいるので注意。イベントＣＧから切り出すか，この背景から切り出すか？）
.panel 1
.message	340			今天，第四节的英语变成了自习。
.message	350			当然给出了作业，不会让你白白玩过去。
.message	360			作业是阅读理解。
.message	370			难度比较多，普通的学生就算花一个小时也不一定能够全部回答完成。
.message	380		嫗丂夘	「唔～嗯……」
.message	390			虽然这么说，这边现在也是苦战中。
.message	400			我虽然文科理科大体都不错，但只有英语稍微有些头痛。
.message	410			特别是阅读理解，只读问题文本身就会花不少时间……。
.transition 0 * 20
.stage	* ev02_067a01.png 0 0
.message	420	miy-208_01-0003	傒傗偙	「那么，堤堤。来对答案吧」
.message	430		嫗丂夘	「……不要」
.message	440			还不到二十分钟啊。
;■考え込み
.transition 0 * 40
.stage	* ev02_067a02.png 0 0
.message	450	miy-208_01-0005	傒傗偙	「总之，先把全文翻译成日文看下──」
.message	460		嫗丂夘	「等下等下。我还远没完成呢，没有对答案的必要吧」
.message	470			交上去的话，老师不就给分数了嘛。
.message	480	miy-208_01-0007	傒傗偙	「我也会有一些不太清楚的地方啊。想要现在搞明白啦」
.message	490		嫗丂夘	「我说你，难道不知道我英语不好吗」
;■笑顔
.transition 0 * 40
.stage	* ev02_067a03.png 0 0
.message	500	miy-208_01-0009	傒傗偙	「那是和其他学科相比而言，不是吗。虽然还赶不上我，但已经很强了啦」
.message	510		嫗丂夘	「承蒙夸奖」
.message	520			感觉被狠狠的取笑了。
.message	530			……………
.message	540			……
;■真剣
.transition 0 * 40
.stage	* ev02_067a04.png 0 0
;（三点が前に入ってるので，フェ～ドスピ～ドには注意して）
.message	550	miy-208_01-0011	傒傗偙	「堤堤只是讨厌读长篇文章而已啦。单词和语法的基础都不错，也有理解力」
.message	560	miy-208_01-0013	傒傗偙	「如果没有觉得自己差的意识的话，阅读会成为得分源的哦」
.message	570		嫗丂夘	「哈，是吗」
.message	580			和宫村交换了一下意见之后，所有的问题都解决了……。
.message	590			我再次确认这家伙年级第一的位置不是浪得虚名。
.message	600			虽然看表面想像不出，但脑子转的相当快，而且也有很好的直感。
;■笑顔
.message	610	miy-208_01-0015	傒傗偙	「距离最后关卡还有半年左右呢，大概可以作到的啦」
.message	620		嫗丂夘	「嘛，就算你不说我也会作些什么的」
.message	630	miy-208_01-0017	傒傗偙	「那么，这件事就此结束。我们来谈下个话题」
.message	640		嫗丂夘	「下个？」
.message	650	miy-208_01-0019	傒傗偙	「不是这比较好吧……」
.transition 0 * 40
.stage	* ev02_067b01.png 0 0
.message	660	miy-208_01-0021	傒傗偙	「小佐～木。抱歉，等下能把这个交出去吗～？」
.message	670			宫村说着，把两个人的答题纸递给了附近坐着的女生。
.transition 0 * 40
.stage	* ev02_067c01.png 0 0
;（フェ～ドスピ～ドには注意して）
.message	680			向毫无讨厌表情而接受的佐佐木道了一声谢后，宫村站了起来。
.message	690			真够受的，这次又是为了什么事啊。
.panel 0
.playBGM *
.transition 0 * 10
.stage	* WHITE.png 0 0


;■背景：屋上（夏，１２時
;■　　　　堤京介　　：制服（夏）
;■　　　　宫村宫子：制服（夏）
;■ため息
.transition 1 fadeSide.png 10
.stage	* ev02_038a01.png 0 0
;.stage	* bgs_sch007a01_01.png 0 0
;（ev02_038a01で，京介をトッたバ～ジョンのを？）
.panel 1
.message	700	miy-208_01-0023	傒傗偙	「……其实昨天，和纮君吵架了」
.message	710		嫗丂夘	「说起来……既然交往自然会偶尔吵架的吧」
.message	720			我还以为把我带到这种地方想要说什么呢。
.message	730			就算再怎么聪明，陷入爱情也只是一个普通的女生啊。
;■不安
.transition 0 * 20
.stage	* ev02_038b01.png 0 0
;（宫子の表情は注意して）
.message	740	miy-208_01-0025	傒傗偙	「然后呢，就想到听听打情骂俏的专家的意见……」
.message	750		嫗丂夘	「打扰一下～，那是指谁」
.message	760	miy-208_01-0027	傒傗偙	「京介是每周会被女生骂七天的男人──他这么说过哦」
.message	770		嫗丂夘	「广野那混蛋……」
.message	780			到底吃错什么药了。
.message	790			就算这是事实，最近骂我的可是广野你的青梅竹马啊喂。
.transition 0 * 20
.stage	* bgs_sky001a01_01.png 0 0
.message	800		嫗丂夘	「啊～，那么吵架的原因是？」
.message	810			再怎么说也知道自己是在打情骂俏，不会太严重。
.message	820	miy-208_01-0029	傒傗偙	「嗯～」
;■寂しげ
.message	830	miy-208_01-0031	傒傗偙	「和纮君呢，曾经作过一个约定」
.message	840			宫村的语气有些吞吞吐吐。
.message	850			这家伙会这样说话倒是第一次见。
.message	860		嫗丂夘	「约定？约定什么？」
.transition 0 * 20
.stage	* bgs_sch007a01_01.png 0 0 st_miyako08b03.png 410
;（ここで中距離使ってもいいのかもしれんが，ちと保留）
.message	870	miy-208_01-0033	傒傗偙	「到了夏天呢」
.message	880	miy-208_01-0035	傒傗偙	「抽出时间休息，一起去哪里玩这样……」
.message	890		嫗丂夘	「原来如此」
.message	900		嫗丂夘	「虽然约定了，但还是不能去是吧」
.transition 0 * 40
.stage	* bgs_sch007a01_01.png 0 0 st_miyako07b04.png 410
.message	910	miy-208_01-0037	傒傗偙	「嗯……」
.message	920			宫村的脸覆上一层阴云，沉默起来。
.message	930			对于当事人是很严重的问题吗……。
.message	940		嫗丂夘	「这不是没办法的吗？　你之前不也说过了吗，工作增加了如何」
.message	950			广野并不是为了玩而画漫画，他已经放弃学园没有退路了。
.message	960	miy-208_01-0039	傒傗偙	「嗯……」
.message	970			而且，最清楚这个的应该是宫村吧。
.transition 0 * 40
.stage	* bgs_sch007a01_01.png 0 0 st_miyako05b03.png 400
;（身体の向きを変えさせてます。注意して）
.message	980	miy-208_01-0041	傒傗偙	「但是…呢」
.message	990			求求您饶了我吧。
;■泣き
.transition 0 * 40
.stage	* bgs_sch007a01_01.png 0 0 st_miyako05b06.png 400
;（表情には注意して）
.message	1000	miy-208_01-0043	傒傗偙	「分明约好的……」
.transition 0 * 40
.stage	* bgs_sch007a01_01.png 0 0 st_miyako00b08.png 350
;.stage	* bgs_sch007a01_01.png 0 0 st_miyako05b09.png 400
;（目線注意されたし）
.message	1010	miy-208_01-0045	傒傗偙	「一直期待着的……所以我，才努力着……」
.message	1020			你只要哭就可以了。
.message	1030			虽然广野又笨又乖僻，但肯定会温柔的安慰你的吧。
.transition 0 * 40
.stage	* bgs_sch007a01_01.png 0 0 st_miyako04b03.png 400
;（表情，ポ～ズには注意して。目線もこの後，変えさせる？つ～か，涙を足す必要あんのか？この後の地文みると，，，）
.message	1040	miy-208_01-0047	傒傗偙	「抱歉呢，分明跟堤堤也没有用呢」
.transition 0 * 40
.stage	* bgs_sch007a01_01.png 0 0 st_miyako00b10.png 350
.message	1050	miy-208_01-0049	傒傗偙	「但是，不对谁说下的话。我……」
.message	1060			这样说出想说的话，至少会稍微轻松一点。
.transition 1 fadeSide.png 20
.stage	* ago_base_20801a.png 0 0
.message	1070			但是──
.transition 1 fadeSide.png 20
.stage	* ago_base_20801b.png 0 0
.message	1080			有一个女孩，就算哭泣，吐露出自己的心声也无法前进。
.transition 0 * 10
.stage	* bgs_sky001a01_01.png 0 0
.message	1090			到她选择出她该走的路究竟会到何时呢。
;.panel 0
.transition 0 * 10
.stage	* WHITE.png 0 0
.message	1100			……………………
.message	1110			…………
.message	1120			……


;■背景：屋上（夏，１３時
.transition 1 fadeSide.png 10
.stage	* bgs_sch007a01_01.png 0 0
;（背景のＣＧ，別なのに変える？屋上，いろいろバリエ～ションあるので）
;.panel 1
.message	1130			作为听她说话的谢礼，以及「不要说我哭过」的封口费，宫村把钥匙给了我然后回到了教室。
.message	1140			我也并不是十分喜欢孤独，拿了这种东西也不会有什么用。
.message	1150			啊啊，把新藤带到这一次拍摄下说不定会不错。
.message	1160		嫗丂夘	「然后，干什么呢」
.message	1170			第四节课已经结束了，现在是午休时间。
.message	1180			午饭之前，总之联络一下吧……。
.message	1190			我拿出手机，拨出号码。
.playSE hiro_keitai_out.ogg true 0 *
.message	1200			噜噜噜噜……噜噜噜噜噜……。
.playSE * f * 0
.message	1210	hir-208_01-0003	丂峢丂	『喂』
.playBGM efBGM029.ogg
;（フェ～ドさせないでイン？）
.transition 0 * 20
.stage	* ev02_068a01.png 0 0
;（ＣＧは夕設定ですが，昼に修正してもらうこと。さらにこの前，切り出しをちょっと挿む？）
.message	1220		嫗丂夘	「喂～，纮～君？　是我哦，为什么最近～都不给我打电话的啦～？」
.message	1230	hir-208_01-0005	丂峢丂	『……我宰了你』
.message	1240			哦哦，这越过电话扑面而来的杀气。
.transition 0 * 40
.stage	* ev02_068a02.png 0 0
.message	1250		嫗丂夘	「嘛，开场到此为止」
.message	1260	hir-208_01-0007	丂峢丂	『少突然就回复正常啊～你丫』
.message	1270	hir-208_01-0009	丂峢丂	『倒～是，我根本没有跟你这种白痴学生胡闹的时间』
.message	1280			老样子话不遮掩的男人啊。
.message	1290		嫗丂夘	「我有一个问题」
.message	1300	hir-208_01-0011	丂峢丂	『有话快说。我这边忙的很」
.message	1310			附带急性子。
.transition 0 * 40
.stage	* ev02_068a03.png 0 0
.message	1320		嫗丂夘	「广野，我说你啊」
.message	1330		嫗丂夘	「工作和女人哪个更重要？」
;■怒り
.message	1340	hir-208_01-0013	丂峢丂	『……哈？』
.message	1350			哦，比刚才更浓的杀气。
.message	1360	hir-208_01-0015	丂峢丂	『重要不重要，我可不想被你问这种问题』
.transition 0 * 40
.stage	* ev02_068a04.png 0 0
.message	1370		嫗丂夘	「我也不想这么做啊，你的女朋友太烦人而已啊」
.message	1380	hir-208_01-0017	丂峢丂	『……那白痴又做什么了吗』
.message	1390		嫗丂夘	「然，怎么样？　都重要的回答断固拒否哦」
.message	1400	hir-208_01-0019	丂峢丂	『…………』
.message	1410	hir-208_01-0021	丂峢丂	『哪个更重要──什么的，这不废话吗』
.message	1420	hir-208_01-0023	丂峢丂	『宫子』
.message	1430			毫无迷惘，广野清楚的说了出来。
.message	1440		嫗丂夘	「这句话，跟她本人说过吗？」
.message	1450	hir-208_01-0025	丂峢丂	『哈，少说傻话』
.message	1460			猜就如此。
.message	1470			如果说的话，就不可能吵什么架。
.message	1480	hir-208_01-0027	丂峢丂	『就算我想说也不能说啊。再怎么说我现在也是专业的漫画家了』
.message	1490	hir-208_01-0029	丂峢丂	『再说了，哪个更重要这个根本没有可比性。大概你这是世界上最笨蛋的问题』
.transition 0 * 40
.stage	* ev02_068a05.png 0 0
.message	1500		嫗丂夘	「也是。当我没问」
.message	1510	hir-208_01-0031	丂峢丂	『废话嘛，笨蛋』
.message	1520		嫗丂夘	「…………」
.message	1530			广野还真是有足够的根性啊……。
.message	1540	hir-208_01-0033	丂峢丂	『啊啊，对了』
.message	1550	hir-208_01-0035	丂峢丂	『有点事情想问你，你最近──』
.message	1560			然后不自然的没了声，让人不适的沉默在电话间流动着。
.message	1570	hir-208_01-0037	丂峢丂	『不，还是算了～』
.message	1580		嫗丂夘	「是吗」
.message	1590			想说什么也大概猜的到──
.message	1600		嫗丂夘	「那么，差不多该挂了。工作中抱歉了」
.message	1610	hir-208_01-0039	丂峢丂	『你该很抱歉』
.message	1620			到最后还是丢了一句讨厌的话，广野挂断了电话。
;（ここ，ev02_068a03の目つむりを挿む，，，ってのを頭に）
.message	1630			就算离开学园，他还是没什么大改变啊。
.message	1640			笨，乖僻，不过实际却相当为人着想。
.message	1650			对于妹妹一样的存在的新藤，那家伙不可能不介意。
.panel 0
.playBGM *
.transition 0 * 10
.stage	* WHITE.png 0 0


;■シ～ン転換
;■背景：教室（夏，１６時
;■　　　　堤京介　　：制服（夏）
;■　　　　宫村宫子：制服（夏）
.playSE AT_chime.ogg f 0 *
.playBGM efBGM052.ogg
;.playBGM BGM052_sample.ogg
.transition 1 fadeSide.png 10
.stage	* ev02_069.png 0 0
;（切り出し挿んで，このＣＧにイン？）
.panel 1
.message	1660			铛～叮～铛～咚～。
.message	1670			今天也是无事上课完成。
.message	1680			宫村她，呃。
.message	1690			被朋友们围着在说些什么。
.message	1700	miy-208_01-0051	傒傗偙	「啊哈哈哈，小佐木原来是外攻内受哦～」
.message	1710			虽然不明白她说什么，但看起来总之恢复正常模式了。
.message	1720			太好了，太好了。
.message	1730			那么，我就该去迎接我凶暴的公主大人了──
.playSE kyo_keitai_vib.ogg true 0 *
.message	1740			呜呜呜呜呜呜……呜呜呜呜呜呜……。
.message	1750		嫗丂夘	「嗯？」
.playSE * f * 0
.transition 0 * 20
.stage	* ev02_070a01.png 0 0
.message	1760		嫗丂夘	「喂，请问找谁」
.message	1770	kei-208_01-0005	丂宨丂	『我是新藤』
.transition 0 * 40
.stage	* ev02_070a02.png 0 0
.message	1780		嫗丂夘	「哦，我正要去你教室呢」
.message	1790	kei-208_01-0007	丂宨丂	『看来真的是正好呢』
.transition 0 * 40
.stage	* ev02_070a03.png 0 0
.message	1800		嫗丂夘	「哈？　怎么？」
.message	1810	kei-208_01-0009	丂宨丂	『今天，我有点……咳咳，咳咳……』
.transition 0 * 40
.stage	* ev02_070a04.png 0 0
.message	1820		嫗丂夘	「怎么，难道感冒了？」
.message	1830	kei-208_01-0011	丂宨丂	『嗯，稍有一点……』
.message	1840			说起来，昨天吹了很久的海风的啊。
.message	1850	kei-208_01-0013	丂宨丂	『果然是放弃部团活动体力下降了的原因吧。身体好象软弱了许多』
.message	1860		嫗丂夘	「现在，在自己家？」
.message	1870	kei-208_01-0015	丂宨丂	『不是理所当然的吗』
.transition 0 * 40
.stage	* ev02_070a02.png 0 0
.message	1880		嫗丂夘	「那～好，我去看望你好了」
.message	1890	kei-208_01-0017	丂宨丂	『想来也可以，我发着烧控制不了自己的意识，可是不会手下留情的哦』
.transition 0 * 40
.stage	* ev02_070a01.png 0 0
;.stage	* ev02_070a04.png 0 0
;（a01でも？）
.message	1900			唔～，虽然不太明白但十分可怕。
.message	1910			就算是看望也会对她造成消耗的吧。
.transition 0 * 40
.stage	* ev02_070a05.png 0 0
.message	1920		嫗丂夘	「呃～，那么今天的摄影就中止好了」
.message	1930	kei-208_01-0019	丂宨丂	『烧已经退了，明天就会去学校了吧』
.message	1940			一天就全好的话，还真是不死身啊。
.message	1950		嫗丂夘	「我知道了，保重身体」
;■弱々しく
.message	1960	kei-208_01-0021	丂宨丂	『……谢了』
.transition 0 * 20
.stage	* ev02_070a04_mugai_a.png 0 0
.message	1970			挂断电话，把手机放进口袋。
.message	1980			新藤她真的会明天什么事都没的来上课吗。
.message	1990			拍摄电影，因为突发事故而停止摄影很常见。
.message	2000			而且──我也不得不抑制下我心中的迷惘。
.transition 0 * 40
.stage	* ev02_070a01_mugai_a.png 0 0
.message	2010			雨宫优子的话，海边看到的新藤的表情在我脑中不断回旋。
.message	2020			心灵的迷惘会如实的在电影中表现出来。
.message	2030			为了帮助我的她，不能拍这种不负责的东西。
.message	2040			顺便换下心情，去作点别的好了。
.message	2050			一个人也能作到的事情，有很多。
.panel 0
.playSE *
.playBGM *
.transition 0 * 10
.stage	* WHITE.png 0 0


;■シ～ン転換
;■ここより景視点
;■背景：景自室（夏，１６時
;■　　　　景自室：私服（夏）
.playBGM efBGM047.ogg
;.playBGM BGM054_sample2.ogg
.transition 14 * 12
;.transition 0 * 10
.stage	vista_window.png ev02_071.png 0 0
.panel 3
.message	2060	kei-208_01-0023	#丂宨丂	「呼」
.message	2070	kei-208_01-1003		放下手机，轻轻叹了一口气。
.message	2080	kei-208_01-1005		堤前辈，就算我联络他很突然也没有责怪我一句。
.message	2090	kei-208_01-1007		说起电影导演的印象，一直是单手拿着扩音器喊来喊去的样子……。
.message	2100	kei-208_01-1009		而前辈生气的样子，却怎样都想像不出。
.message	2110	kei-208_01-0025	#丂宨丂	「和哥哥不一样呢……」
.message	2120	kei-208_01-1011		那个男人可是特别喜欢生气的啊。
.message	2130	kei-208_01-0027	#丂宨丂	「……嗯？」
.message	2140	kei-208_01-1013		啊～，不行不行。
.message	2150	kei-208_01-1015		已经决定要忘记的。
.message	2160	kei-208_01-1017		那个差劲的堤前辈都可以作到的事情。
.message	2170	kei-208_01-1019		我不可能做不到。
.transition 0 * 20
.stage	* ev02_072a01.png 0 0
.message	2180	kei-208_01-0029	#丂宨丂	「千寻……」
.message	2190	kei-208_01-1021		坐到电脑前，打开邮件软件。
.message	2200	kei-208_01-1023		痛苦的事，悲伤的事，这些束缚着我的枷锁总有一天会被砍断。
.transition 0 * 20
.stage	* ev02_072a02.png 0 0
;（フェ～ドスピ～ドには注意して）
.message	2210	kei-208_01-1025		我一定会砍断给他们看。
.message	2220	kei-208_01-1027		如果是我的话，一定能作到吧？
.transition 0 * 20
.stage	* ev02_073.png 0 0
;（インのタイミング，注意して）
.message	2230	kei-208_01-0031	#丂宨丂	「……邮件，不写不行呢」
.message	2240	kei-208_01-1029		牵挂着异地而居的我们姐妹两个的，唯一的红线。
.message	2250	kei-208_01-1031		无论何时何地，都不会让它断掉。
.transition 0 * 10
.stage	past_window.png ev02_073.png 0 0
.message	2260	kei-208_01-1033		我对于千寻来说，说不定也是她有力的支柱。
;.transition 1 fadeSide.png 10
;.stage	kei_window.png WHITE.png 0 0
.transition 0 * 10
.stage	* vista_white.png 0 0
.panel 0
;.transition 1 fadeSide.png 10

;■御影チェック
.playBGM *

.transition 0 * 10
.stage	* WHITE.png 0 0
.playVoice *



;■シ～ン転換
;■ここより京介視点
;■背景：商店街（夏，１６時３０分
;■　　　　堤京介　：制服（夏）
;■　　　　雨宫优子：私服（夏）
.transition 1 fadeSide.png 10
.stage	* ev02_074a01_mugai_a.png 0 0
;（切り出し，変なようなら修正を。もしくは，ビデオフレ～ム画像から入って，この切り出しに？）
;.stage	* bgs_normal001m01_02.png 0 0
.panel 1
.message	2270			想要拍出从来没有人看过的画面。
.message	2280			我也十分清楚我的技术和经验都还十分不足。
.message	2290			正是因为如此，才要有高的目标。
.message	2300			即使明白自己所追求的过于遥远的话，路程上也会充满艰难险阻。
.message	2310	yuk-208_01-0005	桪丂巕	「那个～」
.playBGM *
.playBGM efBGM017_2.ogg
.transition 0 * 20
.stage	* ev02_074a01.png 0 0
;（ＣＧ表示のタイミングにも注意して）
;（音声やイベントＣＧによっては前に戻すこと）
.message	2320		嫗丂夘	「嗯？　怎么？」
.message	2330			雨宫优子一脸疑惑表露无遗。
.message	2340	yuk-208_01-0007	桪丂巕	「我到底要跟着你到什么时候才好呢？」
.message	2350		嫗丂夘	「诶，不跟随我走到最后吗？」
;■微笑
.transition 0 * 40
.stage	* ev02_074a02.png 0 0
.message	2360	yuk-208_01-0009	桪丂巕	「作为托付一生的人的话，你还差的很远」
.message	2370		嫗丂夘	「说的还真是过分啊……」
.message	2380			虽然我对在教会晃悠时强行拉你出来感到抱歉。
.message	2390			但，这话也太富有打击力了。
.message	2400	yuk-208_01-0011	桪丂巕	「作什么来着……拍摄实景？」
.message	2410		嫗丂夘	「对对」
.message	2420			“实景”指的就是不是拍摄特定的人物而是风景或者小东西之类。
.message	2430			特别作为剧情间的联系，纯风景的剪辑必不可少，这如果不够的话编辑的时候就要堕入地狱了。
.message	2440			总之尽量的往前走，把能够看到的风景完整的收入摄影之中。
.message	2450	yuk-208_01-0013	桪丂巕	「为什么这种事情我非得陪着不行呢？」
.transition 0 * 40
.stage	* ev02_074a03.png 0 0
.message	2460		嫗丂夘	「以前呢，一个人拍实景走着的时候，被向警察举报过啊。哈哈哈」
;■呆れ
.message	2470	yuk-208_01-0015	桪丂巕	「很好笑吗」
.message	2480		嫗丂夘	「不知被那个女孩说，『有变态拿着摄像机跟着我』然后片警就过来了」
.message	2490	yuk-208_01-0017	桪丂巕	「说不定，那女孩子说的没错」
.message	2500		嫗丂夘	「那女孩只是偶尔被拍到而已啊」
.message	2510			都要被警官带走的时候，还好别的摄影研究部的朋友跑了过来……。
.message	2520			一个人拿着摄像机晃来晃去，怎么想都会觉得可疑。
.message	2530			不能期待今天再有援军，保险起见就把雨宫带了出来。
.transition 0 * 40
.stage	* ev02_074a04.png 0 0
.message	2540		嫗丂夘	「反正雨宫你不是闲的很吗？」
;■怒り
.message	2550	yuk-208_01-0019	桪丂巕	「不得不做的工作有很多的哦」
.message	2560		嫗丂夘	「你的工作到底是什么？」
;■笑顔
.transition 0 * 40
.stage	* ev02_074a05.png 0 0
.message	2570	yuk-208_01-0021	桪丂巕	「填补大家心灵的罅隙」
.message	2580		嫗丂夘	「你是哪的上班族吗……」
;■すっとぼけ
.transition 0 * 40
.stage	* ev02_074a06.png 0 0
.message	2590	yuk-208_01-0023	桪丂巕	「啊啦，真无聊的反应」
.message	2600		嫗丂夘	「嘛，我也没心思深究就是了」
.message	2610			特别对于是对女孩子的时候，是否想隐藏自己真正的心意。
.message	2620			是否真的想要让人知道。
.message	2630			这两点不明确的作出判断的话不行呐。
.message	2640	yuk-208_01-0025	桪丂巕	「只是，不知为何……」
.transition 0 * 40
.stage	* ev02_074a07.png 0 0
.message	2650		嫗丂夘	「嗯？」
;■真剣
.message	2660	yuk-208_01-0027	桪丂巕	「在这个城市的工作，不会再持续太久了的感觉」
.message	2670			莫名的雨宫优子高兴的笑了起来。
.message	2680		嫗丂夘	「最近要调动工作了吗？」
.transition 0 * 40
.stage	* ev02_074a08.png 0 0
.message	2690	yuk-208_01-0029	桪丂巕	「呵呵」
.message	2700			雨宫优子只是不停笑着──
.message	2710			我不由得放下了拍着街市的镜头。
.transition 0 * 40
.stage	* ev02_074b01.png 0 0
;（フェ～ドスピ～ド注意して。ここは20で？）
.message	2720		嫗丂夘	「那个，回答你之前的问题」
.message	2730	yuk-208_01-0031	桪丂巕	「是」
.message	2740		嫗丂夘	「放弃部团，依然继续拍着电影的路对我来说，从没迷惑过」
.message	2750		嫗丂夘	「但是，被女生拒绝之后──从来没有一次紧缠不松的」
.transition 0 * 40
.stage	* ev02_074b02.png 0 0
.message	2760	yuk-208_01-0033	桪丂巕	「是因为其实并不喜欢吗？」
.message	2770		嫗丂夘	「谁知道呢」
.message	2780		嫗丂夘	「不过──」
.message	2790			想起屋顶上宫村哭泣的表情。
.message	2800			正是认真的爱着对方，打破约定时才会不甘心到想哭的地步。
.message	2810			那就是真正陷入恋情的人的样子。
.message	2820		嫗丂夘	「我对于电影的心情更强一些吧」
.message	2830			至今为止分手过的女孩子，估计也都察觉到这一点了吧。
.message	2840	yuk-208_01-0035	桪丂巕	「你真的这样就好吗？」
.message	2850		嫗丂夘	「那个我也不知道啊」
.message	2860			唰唰……微风轻轻拂起雨宫优子的刘海。
;■寂しげ
.transition 0 * 40
.stage	* ev02_074b03.png 0 0
.message	2870	yuk-208_01-0037	桪丂巕	「人的心……只有梦想的话是装不满的哦」
.panel 0
.playBGM *
.transition 0 * 10
.stage	* WHITE.png 0 0


;フェ～ドアウト
;■背景：京介自室（夏，２３時
;■　　　　堤京介　：私服（夏）
.transition 1 fadeSide.png 10
.stage	* ev02_033.png 0 0
.panel 1
.message	2880			啪嚓一声，自动铅笔芯碎掉了。
.transition 0 * 20
.stage	* ev02_075.png 0 0
;（インのタイミング，注意して。次の地文で？シャ～ペンを放り出す効果音も？）
.message	2890		嫗丂夘	「切……」
.message	2900			啧了一下嘴，把铅笔扔到笔记本上。
.message	2910			开始学习快有两个小时了。
.message	2920			稍微休息一下吧……。
.message	2930		嫗丂夘	「呼～啊」
;.transition 0 * 20
;.stage	* ev02_041a01.png 0 0
;（机の上とかにノ～トがなかったりするけど，片付けたっちゅ～ことで）
.transition 0 * 20
.stage	* ev02_076a03.png 0 0
;（ベッドが軋む効果音を？）
.message	2940			打着哈欠躺到了床上。
;.transition 0 * 20
;.stage	* ev02_076a03.png 0 0
.message	2950			虽然今天摄影休息了，但还是发生了不少事啊。
.message	2960			只有梦想不行，吗……。
.message	2970			说不定雨宫说的没错。
.message	2980			不过──
.transition 0 * 20
.stage	* WHITE.png 0 0
;（フェ～ドはセンタ～２みたいなので？）
.message	2990			……………………
.message	3000			…………
.message	3010			……

;■白バックでいいかな。
.playBGM efBGM028mix.ogg
;.transition 0 * 20
;.stage	* ev02_077.png 0 0
;（白からのインの場合，きれいに移行できるように注意して）
;.panel 4
.message	3020	mom-208_01-0003	@嫗夘曣	「妈妈呢，实际以前，是女演员哦」
.message	3030		嫗丂夘	「女演员？」
.message	3040			啊啊，怎么。
.message	3050			好久之前的光景……。
.transition 0 * 20
.stage	* ev02_077.png 0 0
.message	3060	mom-208_01-0005	@嫗夘曣	「是哦。来，看看这个」


;■御影チェック
;■　バグにしか見えないそうで。
;.transition 0 * 20
;.stage	* ev02_077_kaisou_a.png 0 0


.message	3070		嫗丂夘	「…………」
.message	3080		嫗丂夘	「啊」
.message	3090		嫗丂夘	「那个，那个是妈妈吗？」
.message	3100			是啊，那还是我小时侯的记忆──
.message	3110			记得，季节应该是夏天吧。
.message	3120			长久不在家的母亲，经过数月从医院回来。
;.message	3120			長らく家を空けていた母が数ヶ月ぶりに帰ってきた。
.message	3130			虽然这么说，母亲也只是什么都没法做整天躺在床上而已。
.message	3140			有一天。
.message	3150			母亲难得的起床，把一卷电影胶卷给了无聊的我。
;■御影チェック
;.transition 0 * 20
;.stage	* ev02_077_kaisou_b.png 0 0
.message	3160	mom-208_01-0007	丂曣丂	「很漂亮吧」
;■御影チェック
;;■得意げ
;.transition 0 * 20
;.stage	* ev02_077_kaisou_c.png 0 0
.message	3170	mom-208_01-0009	丂曣丂	「当然妈妈本来就很漂亮，但导演真的很棒。我呢，想要一直出演这个人的电影呢」
.message	3180	mom-208_01-0011	丂曣丂	「也就是天才啊。感觉就像是只为了电影而存在的人一样」
.message	3190		嫗丂夘	「呼～，好厉害呢～」
.message	3200			那个时候的我，大概还不懂那些细腻的问题。
.message	3210			但那晚霞下的古街。
.message	3220			推着自行车走着的年轻的母亲的身姿，就算是小孩子也懂得其中的美丽。
.message	3230	mom-208_01-0013	丂曣丂	「所以呢，这个电影是妈妈最喜欢呢」
.message	3240			──而现在我明白了。
.message	3250			虽然母亲经过舞台走入电影圈，但都不是什么重要的角色而无法十分活跃的事。
.message	3260			以及，和父亲的结婚为尚未萌发的演员生活画上了句点，从银幕上消失的事。
.message	3270	mom-208_01-0015	丂曣丂	「小京。妈妈呢，虽然只有一瞬却实现了自己的梦想」
.message	3280		嫗丂夘	「梦想？」
.message	3290	mom-208_01-0017	丂曣丂	「对，梦想」
.message	3300	mom-208_01-0019	丂曣丂	「也希望小京你能实现呢。不是伟大的梦想也无所谓，自己真正希望的梦想……持续不停的梦想……」
.message	3310			那时的母亲的笑有些寂寞。
.message	3320			小孩子的我因为不想看到那种表情。
.message	3330			便说了，我会实现。
.message	3340			分明那时还没有发现自己究竟该实现什么样的梦想。
.transition 0 * 20
;■御影チェック
;.stage	* ev02_077.png 0 0
.message	3350	mom-208_01-0021	丂曣丂	「谢谢你，小京」
.message	3360			就算如此母亲还是温柔的笑了起来，抚摸着我的头──


;■通常背景
;.panel 0
.transition 0 * 20
.stage	* WHITE.png 0 0
;.panel 1
.message	3370		嫗丂夘	「…………」
.message	3380			现在回想起来，那个时候毫无杂念的对话大概就决定了我的人生。
.message	3390			虽然听起来傻傻的，但也没办法吧。
.message	3400			因为，那个是──
;■黒バック
.message	3410			和母亲最后的对话。
.panel 0

;■御影チェック
;.playBGM *

.transition 0 * 10
.stage	* WHITE.png 0 0

;■御影チェック
.playBGM *

.transition 0 * 10
.stage	* WHITE.png 0 0
.wait 100

.chain 209_01.sc
;■209_01へ。

;.end