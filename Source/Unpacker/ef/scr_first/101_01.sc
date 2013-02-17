; ファイル: 101_01.txt
;■＜１章：１日目＞
;■背景：纮自室（冬，７時（朝
;■　　　　广野纮：私服（冬）
;■　　　　新藤景：制服（冬）
;■御影チェック
;■　ねぼけ状態で聞こえている景の声が２ファイルあります。
;■　位置に関しては，適宜調整を。
.playSE hiro_yume_a.ogg true
.transition 0 * 10
.stage	* BLACK.png 0 0
.panel 1
.message	100	kei-101_01-0001		听到远远的声音。
.message	110			谁谁在吵嚷的声音。
.message	120			用什么东西敲打着的声音。
.message	130	kei-101_01-0002		……闭嘴。
.message	140			吵死了。
.message	150			去别的地方闹去。
.playSE *
.message	160	kei-101_01-0003	@丂宨丂	「不是说了要你给我起来！」
.playSE kei_kick.ogg f 0 *
.shakeScreen	R	100	100
.message	170			咚！
.message	180		丂峢丂	「…………好…痛」
.transition 0 * 20
.stage	* ev01_016a01.png 0 0
.message	190			头部传来撕裂般的疼痛，不是真的破掉了吧？
.message	200		丂峢丂	「刚才的一击是什么……。用的拳头还是脚……？」
.transition 0 * 20
.stage	* ev01_016b01.png 0 0
;（このＣＧでしゃべらせる場合は，目パチ·口パクに注意。次の台詞でこのＣＧを？）
.message	210	kei-101_01-0005	@丂宨丂	「脚后跟啦」
.message	220		丂峢丂	「我说怎么一瞬间有如此大的伤害……」
.transition 0 * 20
.stage	* ev01_016c01.png 0 0
.message	230			而且，这家伙虽说没有练习什么格斗技，但攻击力却日益见长。
.message	240			啊啊，真可怕。
.transition 0 * 40
.stage	* ev01_016c02.png 0 0
;（ここ，目をつむらせていいか，注意のこと）
.message	250	kei-101_01-0007	@丂宨丂	「醒了？」
.message	260		丂峢丂	「……醒了」
.playBGM efBGM030.ogg
.transition 0 * 20
.stage	* ev01_017a01.png 0 0
;（コンテではここよりもう少し前でこのＣＧ指定になってます）
.message	270	kei-101_01-0009	@丂宨丂	「真是的……。都说了对身体不好，不要趴在桌子上睡觉的。别人的话，完全听不进去呢」
.message	280			那个穿着制服俯视着我的少女──新藤景无奈的说。
.transition 0 * 20
.stage	* ev01_018a01.png 0 0
;（挿入位置，注意のこと）
.message	290			我凝起眼睛望向时钟，有些愕然。
.message	300		丂峢丂	「……不是才7点嘛」
.transition 0 * 40
.stage	* ev01_018b01.png 0 0
;（フェードスピードは40で？腰に手をやるタイミングにも注意のこと）
.message	310	kei-101_01-0011	丂宨丂	「有什么问题吗？」
.message	320			冰冷的声音可吓不倒我。
.message	330		丂峢丂	「我过6点才睡的啊……」
.message	340	kei-101_01-0013	丂宨丂	「那是你自己的事吧。是你在那样的时间还醒着的错」
.message	350		丂峢丂	「如果能考虑下我的立场，我会感谢你的……」
.message	360	kei-101_01-0015	丂宨丂	「工作倒也算了，哥哥的本业是学生。认真点啊」
.message	370			这个高姿态的女生叫做新藤景。
.message	380			是租给我房住的房东的孙女，比我要小1岁。
.message	390			虽然叫我哥哥，但却没有任何血缘关系，完全的外人。
.message	400			只是从小就认识而已。
.message	410			主要是，称呼认识的中年男子为『伯伯』的同时，偶尔就对年龄相近的我叫起了『哥哥』。
.message	420			都到了这个年纪了…但即使你对这个称呼有意见，景也不是你说了就会听的类型。
.message	430			反正能区别开，无所谓。
.transition 0 * 20
.stage	* ev01_017a01.png 0 0
;（ここにぶちこんでますが，変なようなら再考のこと）
.message	440	kei-101_01-0017	丂宨丂	「你要趴在桌子上到几时呢。快去洗脸了啦。记得也要刷牙哦」
.message	450		丂峢丂	「…………」
.message	460			最开始是兄妹那样的关系，为什么现在像小狗跟饲主似的。
.message	470			不过呢，小事情就别去介意了……。
;.transition 0 * 20
;.stage	* ev01_018b01.png 0 0
;☆（a01はどこで使う？a01を使うことも考慮に。このＣＧへの切り替えにも注意のこと）
.message	480	kei-101_01-0019	丂宨丂	「乘洗漱的时候给你作些早饭吧。肯定是什么都没吃吧？」
.transition 0 * 20
.stage	* ev01_018b01.png 0 0
.message	490		丂峢丂	「啊—，不不，算了」
.message	500			我慌忙摇头。
.message	510		丂峢丂	「肚子不是很饿」
.message	520	kei-101_01-0021	丂宨丂	「不好好吃早饭的话。再加上睡眠不足可是会晕倒的哦」
.message	530		丂峢丂	「吃坏肚子的话，不也不得不休息么」
;■笑顔
.transition 0 * 40
.stage	* ev01_018a01.png 0 0
.message	540	kei-101_01-0023	丂宨丂	「哼哼哼……。只要脚可以动就可以去学校不是嘛」
.message	550			景的眼瞳中浮现出危险的光彩。
.message	560		丂峢丂	「抱歉，请忘记我刚才说过的话吧」
.message	570			我慌忙再次摇头。
.message	580			景她在这方面令人绝望的笨，连削蔬菜皮都作不好。
.message	590			说起这个，吃了连煎鸡蛋都不会做的人所做的饭的话，接下来的一天会如何──我十分清楚。
.message	600			另外，不承认自己厨艺不行这点也让人头痛。
.message	610	kei-101_01-0025	丂宨丂	「哼。总有一天让你看看。绝对让你说出美味这两个字来」
.message	620		丂峢丂	「那自信是从哪来的……」
.message	630	kei-101_01-0027	丂宨丂	「这件事到底结束。不吃早餐的话，那就赶快去准备吧」
.message	640		丂峢丂	「是是」
.message	650			我咚咚的点着头，叹了一口气。
.message	660		丂峢丂	「但是啊，今天是开学典礼而已，休息也无所谓嘛。截稿日已经近了，我现在可是大危机状态啊」
.message	670	kei-101_01-0029	丂宨丂	「危机危机，毎个月不都是在喊危机么。危机什么啊你？」
.message	680		丂峢丂	「但事实如此我也没办法啊」
.message	690	kei-101_01-0031	丂宨丂	「我说啊。哥哥，你知道吗？」
.message	700			长长的叹了一口气之后，景说道。
.message	710	kei-101_01-0033	丂宨丂	「哥哥，你的出勤日数现在很糟知道吗？　3学期不取得全勤奖的话，不能升级的你知道吗？」
.message	720		丂峢丂	「那我当然知道……」
.message	730	kei-101_01-0035	丂宨丂	「又笨又不愿努力。没有毅力。在此之上，还不能补足出勤日数的话，就要被强迫再读一年2年生的啊」
.message	740		丂峢丂	「跟毅力没关吧……，说不定明年可以跟景同班啊」
.transition 0 * 20
.stage	* ev01_018c01.png 0 0
;（フェードスピードは40で？）
.message	750	kei-101_01-0037	丂宨丂	「就是为了不这样，才警告你乖乖的去学校！」
.message	760	kei-101_01-0038		景撩了一下前额的刘海，放弃似的的叹了口气。
.message	770	kei-101_01-0039	丂宨丂	「我也不是每天都有空来叫你。还有晨练要做的」
.message	780		丂峢丂	「那个我知道」
.message	790			景所属篮球部，用本人的话说就是，虽然是1年级就已经以得分手的身份活跃在球场了。
.message	800			因为身体小而灵巧，她有着很好的运动才能，估计那话是真的。
.message	810	kei-101_01-0041	丂宨丂	「最初的最重要哦，哥哥。今天逃课休息的话，以后不用猜肯定天天逃课」
.message	820		丂峢丂	「怎么我好象跟讨厌去学校的撒娇小孩似的」
.message	830	kei-101_01-0043	丂宨丂	「本来不就像嘛」
.message	840			完全不同好吧。
.message	850			分明这边还有重要的事情要忙。
.message	860		丂峢丂	「啊啊，找个时间退学好了……」
.transition 1 fadeSide.png 40
.stage	* ev01_019.png 0 0
;（フェードスピードは40で？）
.message	870	kei-101_01-0045	丂宨丂	「啊！？」
.playSE kei_meramera.ogg true
.transition 1 fadeSide.png 40
.stage	* ev01_020a01.png 0 0
;（移行は通常フェードでもいいのかも）
.message	880			口气瞬间豹変的景抓住我的胸口开始晃来晃去。
.message	890			糟了，改变模式了。
.message	900	kei-101_01-0047	丂宨丂	「我说你，开什么玩笑！　想看看血什么颜色么！」
.message	910		丂峢丂	「景，景。注意用词，注意用词」
.playSE * f * 0
.transition 0 * 40
.stage	* ev01_017b01.png 0 0
;（フェードスピードは40でも？）
.message	920	kei-101_01-0049	丂宨丂	「啊！？」
.message	930			景啪的送开了手。
.message	940	kei-101_01-0050		故意咳嗽了两声，害羞的脸上浮起两朵红晕。
.message	950		丂峢丂	「我说你，那个瞬间切换的性格，想想办法啊喂」
;.transition 0 * 20
.transition 0 * 30
.stage	* ev01_017c01.png 0 0
;（フェードスピードは40でも？）
.message	960	kei-101_01-0051	丂宨丂	「啊，一不小心……」
.message	970			景一直参与体育类的活动，在前辈们各种各样的影响下，说话和性格都很男孩子气。
.message	980			除此之外……。
.message	990	kei-101_01-0053	丂宨丂	「但，但是，这也是受哥哥的毒舌影响……从以前一直就被你的恶言熏陶，才变成这样的」
.message	1000		丂峢丂	「又把错往别的人身上推」
.message	1010	kei-101_01-0055	丂宨丂	「而且，刚才是哥哥的错啊。说什么要退学什么的」
.message	1020		丂峢丂	「别当真啊，我只是说说看而已」
.message	1030	kei-101_01-0057	丂宨丂	「这样的话就算了……」
.message	1040		丂峢丂	「再说了，也轮不到景你生气吧」
.message	1050			我的话，让景轻轻咬起了嘴唇。
.message	1060	kei-101_01-0059	丂宨丂	「我呢，比哥哥年纪要小啊」
.message	1070		丂峢丂	「我知道啊」
.message	1080			为此原因才是高姿态满载的啊。
.message	1090	kei-101_01-0061	丂宨丂	「就是现在能在同一学校内读书的时间也很少。所以，现在放弃的话……」
.message	1100		丂峢丂	「……也就是说，就算我留级也好，只要能留在学校的话就行了？」
;.shakeScreen	R	20	20
;（とりあえずシェイク入れてますが，変なようなら切ること。Zシェイクで？値にも注意のこと）
.transition 0 * 40
.stage	* ev01_016c01.png 0 0
.shakeScreen	R	20	20
;（フェードのスピードには注意のこと）
;（016c01を使うことも考慮に。切り出しでも可）
.message	1110	kei-101_01-0063	丂宨丂	「完全不是那回事！」
.transition 0 * 20
.stage	* ev01_017c01_mugai_c.png 0 0
.message	1120	kei-101_01-0065	丂宨丂	「……虽然比起退学要好很多啦」
.message	1130			到底在说些什么呢。
.transition 0 * 20
.stage	* ev01_017c01_mugai_a.png 0 0
;（このカメラ位置の移動は留意のこと）
.message	1140	kei-101_01-0067	丂宨丂	「够了啦。赶快去准备！　等下把你拉也要拉到学校去！」
.message	1150		丂峢丂	「了～解」
;（「立ち上がった」……なので切り替えに注意のこと）
.message	1160			毫无释然的感觉，我慢吞吞的站了起来。
.message	1170			说起来，一大清早的还真是能闹啊。
.panel 0
.playBGM *
.transition 0 * 10
.stage	* WHITE.png 0 0


;■シーン転換
;■背景：通学路（冬，７時３０分
;■　　　　广野纮：制服（冬·外出）
;■　　　　新藤景：制服（冬·外出）
.playBGM efBGM020.ogg
;.screen sc_morning01.png sc_morning01.png
.transition 1 fadeSide.png 10
;.stage	* bgw_sky001a01_00.png 0 0
.stage	* bgw_normal019m01_00_mugai_b.png 0 0
;.stage	* bgw_normal002a01_00.png 0 0
;.stage	* WHITE.png 0 0
.panel 1
;（青空挿む予定ですが，青空がないので保留にしています）
;（とりあえず通学路挿んでます。通学路の背景はこれでいいか，さらにイベントＣＧの繋ぎで，カメラの移動などは不自然さがないようにきちんと行っておくこと）
.message	1180			在往学校去的路上，我打了一个大大的哈欠。
;.screen * *
.transition 1 fadeSide.png 20
.overlay	or_kei00a.png * *
.screen	sc_morning01.png sc_morning01.png sc_morning01.png
;.screen	scl_morning01.png scl_morning01.png scl_morning01.png
.stage	st_kei10a02-.png 0 0 bg_scl002a01_00_f.png 0 0 bg_scl002a01_00_n.png 0
.effect	WScroll2 * 60 -2
;（景の表情，注意して）


;.stage st_kei10a01_dammy.png bg_scr003a01_00.png 0 0
;.effect WScroll bg_scr003a01_00.png 150 -20
;（オーバーレイは忘れないように。スクリーンはかける？はるおとで調べておくこと，顔アプの場合）
;（フェードはサイドで入ってますが，保留のこと）
;（ここから立ち絵，顔アプで横スクロールの予定ですが，これまた保留）
;（通学路の背景がありません。ファイルネームはnormal019で）
.message	1190	kei-101_01-0069	丂宨丂	「哥哥，在开学典礼中可不要睡着哦」
.message	1200			在旁边走着的景微微的盯着我。
.message	1210		丂峢丂	「我还没确认是否出席开学典礼呢」
.transition 0 * 40
.stage	st_kei10a04-.png 0 0 bg_scl002a01_00_f.png 0 0 bg_scl002a01_00_n.png 0
;（顔は赤らんでいていいのか注意して）
.message	1220	kei-101_01-0071	丂宨丂	「什～么？」
.message	1230			瞬间，从那边射来景尖锐的视线。
.message	1240		丂峢丂	「说笑了啦……。不过，要睡是必然的。学园长讲起话来长的要命。分明老得活不了几年了」
;■呆れ
.transition 0 * 40
.stage	st_kei10a05-.png 0 0 bg_scl002a01_00_f.png 0 0 bg_scl002a01_00_n.png 0
.message	1250	kei-101_01-0073	丂宨丂	「真是的，又说这么失礼的话……」
.message	1260		丂峢丂	「可这是事实啊」
.transition 0 * 40
.stage	st_kei11a04-.png 0 0 bg_scl002a01_00_f.png 0 0 bg_scl002a01_00_n.png 0
;（表情には注意して）
.message	1270	kei-101_01-0075	丂宨丂	「真实的……。但是，哥哥也稍微认真的考虑下某些问题如何？」
.message	1280		丂峢丂	「什么？」
.transition 0 * 40
.stage	st_kei10a01-.png 0 0 bg_scl002a01_00_f.png 0 0 bg_scl002a01_00_n.png 0
.message	1290	kei-101_01-0077	丂宨丂	「学业和工作如何并存」
.message	1300		丂峢丂	「真是困难的主题啊」
.transition 0 * 40
.stage	st_kei10a02-.png 0 0 bg_scl002a01_00_f.png 0 0 bg_scl002a01_00_n.png 0
;（表情注意して）
.message	1310	kei-101_01-0079	丂宨丂	「应该有考虑的价值吧？　对吧，『新堂凪』先生」
.message	1320		丂峢丂	「别那样叫我」
.message	1330			新堂凪──
.message	1340			那是我的另外一个名字。
.message	1350			说笔名的话比较容易理解吧。
.message	1360			另外一提『新堂』是取了景的姓氏稍微作了下变更，而『凪』则是直接借用了我姐姐的名字。
.transition 0 * 40
.stage	st_kei10a05-.png 0 0 bg_scl002a01_00_f.png 0 0 bg_scl002a01_00_n.png 0
.message	1370	kei-101_01-0081	丂宨丂	「但是，说真的啊。认真考虑一下的好啊。不然各方面都很麻烦吧？」
.message	1380		丂峢丂	「那到也不至于……」
.message	1390	kei-101_01-0083	丂宨丂	「工作之类，在当学生时不作也无所谓的吧？　学校生活摆在眼前，有很多只有现在才能做的事情不是吗？」
.message	1400		丂峢丂	「哈哈，青春可只有一次啊」
.transition 0 * 40
.stage	st_kei10a09-.png 0 0 bg_scl002a01_00_f.png 0 0 bg_scl002a01_00_n.png 0
.message	1410	kei-101_01-0085	丂宨丂	「我是在认真的谈问题！」
.message	1420		丂峢丂	「说了不要那么快就生气……」
.transition 0 * 40
.stage	st_kei10a06-.png 0 0 bg_scl002a01_00_f.png 0 0 bg_scl002a01_00_n.png 0
.message	1430	kei-101_01-0087	丂宨丂	「不正是因为你在一再的糊弄我么！再这样的话，我就要爆料了哦！」
.message	1440		丂峢丂	「爆料？爆成一块块的话，会被埋进山里的哦？」
.transition 0 * 40
.stage	st_kei10a03-.png 0 0 bg_scl002a01_00_f.png 0 0 bg_scl002a01_00_n.png 0
;（この後に，この表情変化を？）
.message	1450			我的回答，让景把眼睛眯了一起。
.message	1460	kei-101_01-0089	丂宨丂	「嘿，这样的应对态度吗……」
.message	1470	kei-101_01-0091	丂宨丂	「广野纮外看，只是一个不良学生。但是，他的真身却是」


;.message	1480	kei-101_01-0093	丂宨丂	「少女漫画家だったので……モガッ！」
.message	1480	kei-101_01-0093	丂宨丂	「所谓的少女漫画家──！」\v\a

;■御影チェック
;.effect *
.effect end


.overlay	* * *
.screen	* * *
.screen sc_morning01.png sc_morning01.png
.transition 0 * 20
.stage	* ev01_022a01.png 0 0
;（フェードスピードは40で？）
.message	1490	kei-101_01-0094		我慌忙捂住景的嘴巴，望向四周。
.message	1500			幸好，周围毫无人影。
.message	1510			然后呼的放开了景。
.transition 0 * 20
.stage	* ev01_022b01.png 0 0
;（フェードスピードは40で？）
;（ここからのカメラの移行，注意のこと）
.message	1520	kei-101_01-0095	丂宨丂	「……呼啊！」
.message	1530			景的脸色直红到了耳根，然后还用袖子拼命擦着自己的嘴唇。
.message	1540			那种好象碰了脏东西的态度，稍微有点打击到我。
.screen * *



.transition 1 fadeSide.png 20
.overlay	or_kei00a.png * *
.screen	sc_morning01.png sc_morning01.png sc_morning01.png
.stage	st_kei10a09-.png 0 0 bg_scl002a01_00_f.png 0 0 bg_scl002a01_00_n.png 0
.effect	WScroll2 * 60 -2

;.overlay * or_kei00a.png
;.transition 0 * 20
;.stage	* bgw_normal002m11_00.png 0 0 st_kei02a03.png 380
;（フェードの仕方には注意のこと）
.message	1550	kei-101_01-0097	丂宨丂	「真，真是的，突然之间你干吗嘛！」
.message	1560		丂峢丂	「那是我的台词好吧。不是约好对谁都不说的吗」
.message	1570			到不是为自己是少女漫画家这点感到害羞，但也不是什么随便就好说出去的事情。
.message	1580			另外，编辑听说这少女漫画的作者是男人的时候，也说了最好别被人知道这样的话。
.transition 0 * 40
.stage	st_kei10a05-.png 0 0 bg_scl002a01_00_f.png 0 0 bg_scl002a01_00_n.png 0
;.stage	* bgw_normal002m11_00.png 0 0 st_kei01a07.png 380
.message	1590	kei-101_01-0099	丂宨丂	「是否保密要看哥哥你是否用心」
.message	1600		丂峢丂	「我说，那不是约定是威胁了吧」
.transition 0 * 40
.stage	st_kei10a01-.png 0 0 bg_scl002a01_00_f.png 0 0 bg_scl002a01_00_n.png 0
;.stage	* bgw_normal002m11_00.png 0 0 st_kei01a11.png 380
.message	1610	kei-101_01-0101	丂宨丂	「……我倒也不是说让你停止连载，但也稍微认真去下学校吧」
.message	1620			虽然逃掉学校出勤我可能会留级，但如果原稿不赶上的话，会对不起读者的。
.message	1630			责编的怒吼我也听怕了。
.message	1640			不得不工作优先啊，景。
.message	1650		丂峢丂	「……嘛，我会考虑的」
.message	1660			我这样言不从心的说着。
.transition 0 * 40
.stage	st_kei10a03-.png 0 0 bg_scl002a01_00_f.png 0 0 bg_scl002a01_00_n.png 0
;.stage	* bgw_normal002m11_00.png 0 0 st_kei01a05.png 380
;（ここ，04a02でも？）
.message	1670	kei-101_01-0103	丂宨丂	「嗯，考虑下吧」
.message	1680			景点着头微笑起来。
;（↓ここ，歩きスクロール？その場合は，景がまた立ち止まるところで距離感を出すために中距離立ち絵を使うように）
.message	1690			虽然没表现出来，但也看的出步调轻快了不少。
.message	1700			虽然骗人不太好，这也是为了取得您的好心情，而且我也不能扔下工作不管。
.transition 0 * 40
.stage	st_kei10a02-.png 0 0 bg_scl002a01_00_f.png 0 0 bg_scl002a01_00_n.png 0
;☆（ここ，a01表情で？）
;.stage	* bgw_normal002m11_00.png 0 0 st_kei04a02.png 400
;（ここ，この表情でいいか注意のこと）
.message	1710	kei-101_01-0105	丂宨丂	「哥哥，年末和正月都会无休画画吗？」
.message	1720		丂峢丂	「是啊……」
.transition 0 * 40
.stage	st_kei10a01-.png 0 0 bg_scl002a01_00_f.png 0 0 bg_scl002a01_00_n.png 0
;.stage	* bgw_normal002m11_00.png 0 0 st_kei04a03.png 400
.message	1730	kei-101_01-0107	丂宨丂	「完全不是人类的生活嘛。漫画家什么的，那个也好这个也好都是糟透了呢」
.message	1740		丂峢丂	「也没必要说到这种地步吧……」
.message	1750			景好似最近，有些开始讨厌漫画这种东西了。
.message	1760		丂峢丂	「我说你，最近看了我的漫画了吗？」
.transition 0 * 40
.stage	st_kei10a05-.png 0 0 bg_scl002a01_00_f.png 0 0 bg_scl002a01_00_n.png 0
;.stage	* bgw_normal002m11_00.png 0 0 st_kei04a04.png 400
.message	1770	kei-101_01-0109	丂宨丂	「那自然看了啊」
.message	1780			你傻瓜吗，景露出那样的神色。
.message	1790		丂峢丂	「但是都没有听你说过什么感想」
.message	1800	kei-101_01-0111	丂宨丂	「就算我不说，读者们也会来信的吧？」
.message	1810		丂峢丂	「虽然来信也不算少……」
.message	1820			啊啊，真难过。
.transition 0 * 40
.stage	st_kei11a01-.png 0 0 bg_scl002a01_00_f.png 0 0 bg_scl002a01_00_n.png 0
;.stage	* bgw_normal002m11_00.png 0 0 st_kei04a01.png 400
;（ここで視線そらしていいか注意。表情にも注意すること）
.message	1830	kei-101_01-0113	丂宨丂	「另外……」
.message	1840		丂峢丂	「另外？」
.message	1850	kei-101_01-0115	丂宨丂	「感觉现在突然问我感想什么的……会害羞的」
.message	1860		丂峢丂	「……是吗」
.message	1870			真的只是害羞就好了。
.message	1880			景她从很早以前起，就对我会画少女漫画这点从心底感到高兴。
.message	1890			对于尚未熟练的我的作品，景会用笨拙的却是她所能想到的所有语言予以赞美。
.message	1900			而像这样，对我工作开始抱怨，是从什么时候开始的呢。
.transition 0 * 40
.stage	st_kei10a01-.png 0 0 bg_scl002a01_00_f.png 0 0 bg_scl002a01_00_n.png 0
;.stage	* bgw_normal002m11_00.png 0 0 st_kei03a03.png 380
;（03a05でも？）
.message	1910	kei-101_01-0117	丂宨丂	「哥哥，你不是过度劳累了吧？　本来身体就不怎样，再这样下去真会被带到医院去哦」
.message	1920	kei-101_01-0119	丂宨丂	「最近的哥哥越来越可疑──」
.message	1930			嘭，景敲了一下自己的掌心。

;■御影チェック
;.effect *
.effect end

.overlay	* * *
.screen	* * *
.screen sc_morning01.png sc_morning01.png
.overlay * or_kei00a.png
.transition 0 * 20
.stage	* bgw_normal002m11_00.png 0 0 st_kei07a03.png 400
;（このポーズに変える時は，前のポーズとの繋がりに注意して）
.message	1940	kei-101_01-0121	丂宨丂	「啊！　我想起来了！」
.message	1950		丂峢丂	「怎…怎么了？突然…」
.transition 0 * 40
.stage	* bgw_normal002m11_00.png 0 0 st_kei02a03.png 380
.message	1960	kei-101_01-0123	丂宨丂	「圣诞节！」
.message	1970			景的食指突然指向了我。
.message	1980		丂峢丂	「诶？」
.message	1990			『圣诞节』这个单词，让我稍微顿了一下。
.message	2000			发生了各种各样糟透事件的圣诞节，我现在仍记忆犹新。
.transition 0 * 40
.stage	* bgw_normal002m11_00.png 0 0 st_kei06a01.png 400
;（06a05でも？）
.message	2010	kei-101_01-0125	丂宨丂	「哥哥，难得我们聚会叫你却没有来！」
.message	2020		丂峢丂	「什么嘛，这件事吗……。你现在提起来我也…」
.message	2030			说起来，景在寒假中一直忙于部团活动和家族旅行之类，一直都没有机会见上一面。
.message	2040	kei-101_01-0127	丂宨丂	「大家，都在等着哥哥你来啊！」
.message	2050			确实，景和她的数名朋友一起邀约了我参加圣诞聚会。
.message	2060			可是，那天却没去参加。
.message	2070		丂峢丂	「在圣诞节等待人之类。不觉得很像电视剧片段吗」
.transition 0 * 40
.stage	* bgw_normal002m11_00.png 0 0 st_kei06a05.png 400
.message	2080	kei-101_01-0129	丂宨丂	「别说的那么轻巧！　你自己也去等等看啊！」
.message	2090		丂峢丂	「只有女性的聚会没错吧？　那我怎么可能去参加嘛」
.message	2100	kei-101_01-0131	丂宨丂	「但是，你不是说要来的吗」
.message	2110			景用充满恨意的目光瞪着我。
.message	2120			两周前的事情就别去挖坟了好吧。
.message	2130		丂峢丂	「不对，我说的可是『能去的话就去』」
.message	2140	kei-101_01-0133	丂宨丂	「那个跟『我去』一个意思！」
.message	2150			这是哪个世界的法则啊……。
.message	2160			明明是当时被景闹的不行了，随意应付了一下而已。
.transition 0 * 40
.stage	* bgw_normal002m11_00.png 0 0 st_kei04a04.png 400
.message	2170	kei-101_01-0135	丂宨丂	「总之，去向聚会的女孩子们道歉。我也对她们很抱歉呢」
.message	2180		丂峢丂	「爽约的人是我，为什么你要抱歉」
.transition 0 * 40
.stage	* bgw_normal002m11_00.png 0 0 st_kei05a07.png 400
;（別のポーズと表情で？）
.message	2190	kei-101_01-0137	丂宨丂	「总之要道歉！　啊，电话也好，去向瑞希道一个歉去」
.message	2200		丂峢丂	「哎，要给羽山打电话么」
.message	2210			羽山瑞希是附属国中的学生，见面的机会很少。
.message	2220			但是，实话说我很不会应付那种活泼好动的女孩子啊……。
.transition 0 * 40
.stage	* bgw_normal002m11_00.png 0 0 st_kei01a03.png 380
;（ポーズと表情，注意のこと）
.message	2230	kei-101_01-0139	丂宨丂	「不是当然的吗。那孩子也在期待哥哥你来参加聚会呢」
.message	2240		丂峢丂	「……知道了啦」
.message	2250			当然，我完全没有想要打电话的意思。
.message	2260			羽山脑袋没几根筋，肯定早就忘光这回事了。
.message	2270			应该，嗯，肯定是这样。
.panel 0
.overlay * *
.screen * *
.playBGM *
.transition 0 * 10
.stage	* WHITE.png 0 0


;■シーン転換
;■背景：学園·廊下（冬，８時
;■　　　　广野纮：制服（冬）
.playBGM efBGM027.ogg
.transition 1 fadeSide.png 10
.stage	* bgc_sch002a01_00.png 0 0
.panel 2
;（時間指定は８時なので，朝背景でアタッチしています）
.message	2280			\n\n\n\n\n兹有，作为音羽学园2年级学生，少女漫画家。
.message	2280			3年左右之前取得少女漫画杂志举办的比赛之新人奖。
.message	2280			数部短篇漫画被杂志收录之后，1年前取得连载机会，开始月刊连载。
.message	2280			作品的人气不高不低。
.message	2280			単行本尚未发行一册。
.message	2330			\n\n\n\n\n连载开始时搬出了家，在姓新藤的老爷爷所经营的公寓里租了房间开始一人生活。
.message	2330			每次都是卡着截稿日完成原稿，承受着学习和漫画两立的辛苦，但依然努力着。
.message	2330			以上就是我，广野纮的个人资料。
.transition 0 * 20
.stage	* bgc_sch003a01_00.png 0 0
.message	2360			\n\n\n\n\n──就这样每日挣扎于生死线之间的我，现在正朝屋顶走去。
.message	2360			虽然距早晨的班会还稍有时间，但我可没有在教室里跟朋友闲聊的工夫。
.message	2360			而且，突然就在教室画的话，不知会遭到什么恶作剧，也会被人得知身份。
.message	2360			于是──
.transition 0 * 20
.stage	* ev01_023.png 0 0
;（この前の文でこのＣＧを？）
.message	2400			\n\n\n\n\n我从口袋中取出一枚古老的钥匙。
.message	2400			轮到它的登场了。
.panel 0


;■シーン転換
;■背景：屋上（冬，８時
;■　　　　广野纮　　：制服（冬）
.screen sc_morning01.png sc_morning01.png
;☆（ここからスクリーン挿んでますが，ちょっと注意して）
.transition 1 fadeSide.png 10
.stage	* bgw_sch007a01_00.png 0 0
.panel 2
;（フェードスピードは20で？あんど，時間指定は８時なので朝でアタッチしてます）
.message	2420			\n\n\n\n\n屋顶基本是禁止进入的，学生除了得到教师许可以外都不能进出。
.message	2420			另外，也不会有谁那么有空在这么冷的日子里来到屋顶。
.message	2420			对于不想被人注意而工作的我来说，这儿是最好的地方。
.message	2420			不过还真是…冻死人啊。
;.playBGM *
.transition 0 * 20
.stage	* ev01_024.png 0 0
.panel 1
;（ここでこのＣＧを挿んでますが，もう少し後でもいいのかもしれません）

.message	2460		丂峢丂	「那么……」
.message	2470			虽然原稿还在上色中，但在屋顶带着原稿用纸还有色盒工作的话就太怪异了。
.message	2480			因此，在屋顶的主要工作是把接下来的铅笔稿和设定描好。
.message	2490			那样的话只要笔记和铅笔就够了，就算谁突然出现也容易藏起来。
.message	2500			坐在地板上，从背包中取出各类道具，还有随身CD机。
;■御影チェック
;■　ここでBGMを止めました。
.playBGM *
;☆（「イヤホンを耳にはめこみ」，，，この前の画像は注意して）
.message	2510			把耳机塞进耳朵，按下播放键。
;.playBGM *
.playBGM efBGM022_2.ogg
.message	2520			我所喜欢的小提琴手─久濑修一的曲子开始传出。
.message	2530			平时听起来心神宁静，而高潮的时候却也激昂澎湃，有种──灵感汹涌而出的错觉。
.message	2540			不知为何，听着他的曲子笔尖便可以顺畅的走下去──我经常有这样的感觉。
.message	2550			虽然可能只是心情问题而已，但不管怎么说，久濑修一的音乐对我的创作来说是必不可少的。
.message	2560			故事的分镜该如何一时半会想不出来。
.message	2570			到灵感来临为止，只能维持着苦闷，以及被不时的幻觉和幻听袭击的状态而继续想下去。
.screen * *
.transition 0 * 20
.stage	* BLACK.png 0 0
;（フェードスピード10で？）
.message	2580			闭上眼睛，让角色们的姿态在脑海中浮现。
.message	2590			他们会想些什么，会怎么行动──
.message	2600			仅仅考虑这些而已。
.message	2610			想着，想着──
.playBGM *
;.transition 0 * 10
;.stage	* WHITE.png 0 0
.message	2620			……………………
.message	2630			………………
.message	2640			……
;■以下のシーンを挿入するかはちょっと考慮。
;■イメージＢＧ？
.playBGM efBGM028mix.ogg
.transition 0 * 20
.stage	* ev01_025_mugai_a.png 0 0
;.stage	* ev01_025.png 0 0
.message	2650			和过去一样，有种缺少了什么的丧失感袭来。
.message	2660			自己看着的世界是否缺少了某种颜色。
.message	2670			究竟是哪一种颜色呢，我总是不能找到答案。
.transition 0 * 20
.stage	* ev01_025_mugai_d.png 0 0
;.stage	* ev01_025.png 0 0
;（この切り出しは注意のこと。足……とわからないようなら別の切り出しを。まあ，気持ち悪さを演出するにはいいのかもしれませんが）
.message	2680			焦急一点点地啃噬着我的心脏。
.message	2690	yuk-101_01-0003	@桪丂巕	「即便如此你也对于一度抓到的东西决不放手。实现梦想，并以更前方为自己新的道标」
.message	2700		丂峢丂	「那不是当然的吗」
.message	2710			突然出现的少女的声音没有让我吃惊，我单单作出了普通的回答。
.transition 0 * 20
.stage	* ev01_026.png 0 0
.message	2720	yuk-101_01-0005	@桪丂巕	「真是坚强的人呢」
.transition 0 * 20
.stage	* ev01_025_mugai_c.png 0 0
;.stage	* ev01_025.png 0 0
;（この次の地文で？）
.message	2730			我摇了摇头。
.message	2740		丂峢丂	「仅仅是笨蛋而已，不懂得什么叫做放弃」
.transition 0 * 20
.stage	* ev01_026.png 0 0
.message	2750	yuk-101_01-0007	@桪丂巕	「不，我认为你是坚强的」
.message	2760	yuk-101_01-0009	@桪丂巕	「你的这份坚强是从何而来的呢？」
.transition 0 * 20
.stage	* ev01_025_mugai_b.png 0 0
;.stage	* ev01_025.png 0 0
.message	2770		丂峢丂	「为什么会问这样的问题」
.transition 0 * 20
.stage	* ev01_026.png 0 0
.message	2780	yuk-101_01-0011	@桪丂巕	「单纯的好奇心而已哦」
.transition 0 * 20
.stage	* ev01_025_mugai_a.png 0 0
;.stage	* ev01_025.png 0 0
.message	2790		丂峢丂	「好奇心到也无所谓了，观察以及推测也是重要的啊。不是什么事情靠询问就可以解决的」
.transition 0 * 20
.stage	* ev01_026.png 0 0
.message	2800	yuk-101_01-0013	@桪丂巕	「哎呀，还真是严厉呢」
.transition 0 * 20
.stage	* ev01_025_mugai_c.png 0 0
;.stage	* ev01_025.png 0 0
.message	2810		丂峢丂	「我不是什么温柔的人呢」
.transition 0 * 20
.stage	* ev01_026.png 0 0
;（ここは白黒にしないで？）
.message	2820	yuk-101_01-0015	@桪丂巕	「看起来是这样呢」
.message	2830			少女轻轻的笑了起来。
.transition 0 * 20
.stage	* ev01_025_mugai_b.png 0 0
;.stage	* ev01_025.png 0 0
.message	2840		丂峢丂	「我坚强与否我不知道。只是……」
.transition 0 * 20
.stage	* ev01_026.png 0 0
.message	2850	yuk-101_01-0017	@桪丂巕	「只是？」
.transition 0 * 20
.stage	* ev01_025.png 0 0
.message	2860		丂峢丂	「我只是在想，实现了梦想的人不是应该负起责任吗」
.transition 0 * 20
.stage	* ev01_026_mugai_a.png 0 0
;（ここは白黒にしないで？）
.message	2870	yuk-101_01-0019	@桪丂巕	「那责任，是针对谁的呢？」
.transition 0 * 10
.stage	* WHITE.png 0 0
;.transition 0 * 20
;.stage	* ev01_025.png 0 0
;☆（ここで白にするか，文字テロップで？）
.message	2880		丂峢丂	「……对追寻梦想时的自己」
.playBGM *
.transition 0 * 10
.stage	* WHITE.png 0 0
.message	2890			……………………
.message	2900			…………
.message	2910			……

;■御影チェック
.panel 0


;■背景：屋上（冬，８時
;■　　　　广野纮　　：制服（冬）
;■　　　　宫村宫子：制服（冬）
;（青空がないので保留です）
;.transition 0 * 10
.transition 1 fadeCenter2.png 10
.stage	* bgw_sky001a01_00.png 0 0
;（フェードスピードは注意のこと）
;（フェードの仕方にも注意のこと）
.panel 1
.message	2920		丂峢丂	「…………嗯？」
.message	2930			睁开双眼，看到的只有一如既往的蓝天无垠。
.message	2940			摇了一下自己的头，确认眼前的现实。
.message	2950			嗯，我现在正呆在学校的屋顶。
.message	2960			完全没错。
.transition 0 * 20
.stage	* ev01_027a01.png 0 0
;（移行，注意）
.message	2970		丂峢丂	「……睡着了吗，我」
.message	2980			看起来应该是刚开始画时就睡着了的样子。
.message	2990			当然，工作也完全没有进展，说不定开学典礼也已经结束了。
.message	3000			不知何时音乐也已停止。
.transition 0 * 20
.stage	* ev01_027b01_anime2.png 0 0
.message	3010			取出手机，打算确认时间时，我突然感觉到异样的气息。
.transition 0 * 20
.stage	* ev01_027c01_anime.png 0 0
.message	3020	miy-101_01-0003	@傒傗偙	「哦，你醒了吗」
.message	3030			听到那个声音，我仰起脸。
.transition 0 * 20
.stage	* ev01_028a01_mugai_b.png 0 0
.message	3040			在视线的那边，屋顶的边缘站着的是──
.transition 0 * 20
.stage	* ev01_028a01_mugai_a.png 0 0
.message	3050		丂峢丂	「宫村宫子──？」
.playBGM efBGM029.ogg 0 *
.transition 0 * 20
.stage	* ev01_028a01.png 0 0
.message	3060	miy-101_01-0005	傒傗偙	「早安」
.message	3070			如在海滨那一夜时一样，在那寒风吹拂的地方，她站在那里。
.message	3080		丂峢丂	「啊，啊啊。早安……」
.message	3090			呃～嗯。
.message	3100			为什么这家伙会在这里？
.message	3110			而且还穿着音羽学园的制服。
.message	3120		丂峢丂	「我，我说你，在干吗呢？」
.transition 0 * 40
.stage	* ev01_028a02.png 0 0
.message	3130	miy-101_01-0007	傒傗偙	「干吗？和广野君说话啊」
.message	3140		丂峢丂	「你，是音羽的学生吗？」
.message	3150			啊啊，声音稍微有些兴奋。
.transition 0 * 20
.stage	* ev01_028b01_mugai_a.png 0 0
;（これ挿入すると，この差分の目パチ·口パクがもったいないことになるが……）
;.transition 0 * 20
;.stage	* ev01_028b01.png 0 0
;（フェードスピードは20？）
.message	3160	miy-101_01-0009	傒傗偙	「当然了。没看见我穿着学校的制服吗？」
.transition 0 * 20
.stage	* ev01_028b01.png 0 0
.message	3170			宫村她拉住裙角，稍微向这边抬起。
.message	3180			啊啊，大腿露出这么多…。
.transition 0 * 40
.stage	* ev01_028a04.png 0 0
;（bポーズのにっこりがあってもいいのかも。フェードスピードは20で？）
.message	3190	miy-101_01-0011	傒傗偙	「穿制服的样子也很合适吧」
.message	3200		丂峢丂	「『也』算什么啊『也』。不过，确实满可爱──等等不是那回事」
.message	3210			啊啊，我在动摇什么呢。
.message	3220		丂峢丂	「稍微冷静一下」
.message	3230			宫村宫子是这儿的学生也没什么不可思议的。
.transition 0 * 40
.stage	* ev01_028a03.png 0 0
.message	3240	miy-101_01-0013	傒傗偙	「该冷静的不是广野君吗」
.message	3250		丂峢丂	「呃～嗯，你也是我们学校学生的事实我明白了。但是，为什么你会在这里？」
.transition 0 * 40
.stage	* ev01_028a01.png 0 0
;（ここ，04で？）
.message	3260	miy-101_01-0015	傒傗偙	「你还真是完全的熟睡呢。在这种地方睡觉会感冒的啦」
.message	3270			我左右转了转头。
.message	3280			感冒什么到应该没有，不过奇怪的姿势睡的身体有些痛。
.transition 0 * 40
.stage	* ev01_028a03.png 0 0
;（ここ，01で？）
.message	3290	miy-101_01-0017	傒傗偙	「一副睡的好熟的样子。我还在想要不要给你膝枕呢──」
.message	3300		丂峢丂	「诶？」
.transition 0 * 40
.stage	* ev01_028a04.png 0 0
.message	3310	miy-101_01-0019	傒傗偙	「想到那样腿会麻的，就放弃了」
.message	3320			这么说着，宫村她哈哈的笑了起来。
.message	3330			……还好她放弃了自己的想法。
.message	3340			醒来的时候发现自己的头搁在别人的大腿上，该算什么样的状况，该作出什么样的反应呢。
.message	3350		丂峢丂	「那种事情怎样都无所谓了，我说你，还没回答我的问题呢。为什么会在这里？」
;（ここの表情，前のを引き継がせてますが，要考察のこと）
.message	3360	miy-101_01-0021	傒傗偙	「那不是很明显的吗」
.message	3370			宫村浮起“这还不明白吗？”的满面笑颜。
.message	3380			好不甘心──
.message	3390			虽然不知道为什么好不甘心──
.message	3400			因为那个笑颜，一瞬间我的心脏剧烈地鼓动起来。
.transition 0 * 40
.stage	* ev01_028a01.png 0 0
.message	3410	miy-101_01-0023	傒傗偙	「我呢」
.transition 0 * 40
.stage	* ev01_028a03.png 0 0
.message	3420	miy-101_01-0025	傒傗偙	「是为了见广野君来的哦」
.panel 0
.transition 0 * 10
.stage	* WHITE.png 0 0


;■フェードアウト
;■シーン転換
;■背景：屋上（冬，８時
;■　　　　广野纮　　：制服（冬）
;■　　　　宫村宫子：制服（冬）
.screen sc_morning01.png sc_morning01.png
.transition 1 fadeSide.png 10
.stage	* bgw_sch007a01_00.png 0 0
.panel 1
;（フェードスピードは20で？あんど，時間指定は８時なので朝でアタッチしてます）
.message	3430			也就是说，宫村宫子偶尔在走廊看到了我的身影，然后跟了过来这样。
.message	3440		丂峢丂	「看到我的话，早早的打个招呼不好吗」
.overlay * or_miyako00a.png
.transition 0 * 20
.stage	* bgw_sch007a01_00.png 0 0 st_miyako07a01.png 410
;（この表情で目閉じ·笑顔を？05a01でも？）
.message	3450	miy-101_01-0027	傒傗偙	「那个呢，是那个啦」
.message	3460			哪个啊。
.transition 0 * 40
.stage	* bgw_sch007a01_00.png 0 0 st_miyako02a01.png 350
.message	3470	miy-101_01-0029	傒傗偙	「我要作好心里的准备啊。再怎么说我也是女孩子～」
.message	3480		丂峢丂	「完全不明白你说什么」
.message	3490	miy-101_01-0031	傒傗偙	「一起度过圣诞夜的两人的再会。想要罗曼蒂克一点啊」
.message	3500		丂峢丂	「请不要说出引人误解的话，宫村小姐」
.message	3510			只是被没有回家钥匙的宫村她强行拉着，在卡拉OK和家庭餐馆消磨时间直到早上而已。
.message	3520			而且，全部是我买单。
.transition 0 * 40
.stage	* bgw_sch007a01_00.png 0 0 st_miyako05a01.png 400
.message	3530	miy-101_01-0033	傒傗偙	「不过没想到，光是同一个学校不算还是同一学年的呢」
.message	3540		丂峢丂	「我是不怎么来学校啦……。自己班上的同学也有只知道长相不知道名字的人」
.message	3550			就算是同一学年，也不可能认识什么別班的学生。
.transition 0 * 40
.stage	* bgw_sch007a01_00.png 0 0 st_miyako06a02.png 400
.message	3560	miy-101_01-0035	傒傗偙	「啊，一样的。其实不怕笑话的说，我也是个缺勤大王呢」
.message	3570		丂峢丂	「还真是糟糕啊」
.transition 0 * 40
.stage	* bgw_sch007a01_00.png 0 0 st_miyako03a01.png 400
.message	3580	miy-101_01-0037	傒傗偙	「嗯，广野君不也是同类吗？稍微有些高兴呢。伙伴哦，伙伴<音乐符号>」
.message	3590		丂峢丂	「就算你自说自话的冒出伙伴意识……」
.message	3600			我也会困扰的啊，正想这么说时候，我和宫村的视线接触了了一起。
.transition 0 * 40
.stage	* bgw_sch007a01_00.png 0 0 st_miyako00a05.png 350
.message	3610	miy-101_01-0039	傒傗偙	「说起来，有件让人在意的事情呢」
.message	3620		丂峢丂	「又怎么了」
.transition 0 * 40
.stage	* bgw_sch007a01_00.png 0 0 st_miyako00a06.png 350
;（表情注意）
.message	3630	miy-101_01-0041	傒傗偙	「屋顶不是禁止进入的吗。一直都上有锁的」
.message	3640		丂峢丂	「啊啊，这件事吗」
.message	3650		丂峢丂	「我的姐姐，是这学园的毕业生。偶尔的，从奇怪的朋友那拿来的的钥匙这样」
.transition 0 * 40
.stage	* bgw_sch007a01_00.png 0 0 st_miyako00a09.png 350
；(表情注意）
.message	3660	miy-101_01-0043	傒傗偙	「呼诶～」
.message	3670			宫村好象很佩服似的声音提高了些。
.transition 0 * 40
.stage	* bgw_sch007a01_00.png 0 0 st_miyako00a06.png 350
;（表情注意）
.message	3680	miy-101_01-0045	傒傗偙	「从那个怪朋友到姐姐，从姐姐到广野君，代代相传的秘密场所啊」
.message	3690		丂峢丂	「没那么夸张吧」
.message	3700			姐姐仅仅是为庆祝我入学，又不想送钱或者什么其他东西才给了我这把钥匙。
.message	3710			一个人的话会是不错的地方，还是十分值得感谢的。
.transition 0 * 40
.stage	* bgw_sch007a01_00.png 0 0 st_miyako08a02.png 410
.message	3720	miy-101_01-0047	傒傗偙	「但是还真是让人吃惊呢」
.message	3730			宫村她好象栅栏内的熊一样转来转去的说着。
.message	3740			还真是不安分的女生啊。
.transition 0 * 40
.stage	* bgw_sch007a01_00.png 0 0 st_miyako07a01.png 410
.message	3750	miy-101_01-0049	傒傗偙	「分明是屋顶却没有围栏呢。虽然从校园看屋顶就可以明白，但我还是刚刚注意到」
.message	3760		丂峢丂	「啊啊，这个虽然我也有些吃惊，但仔细想想也没什么奇怪吧」
.transition 0 * 40
.stage	* bgw_sch007a01_00.png 0 0 st_miyako07a02.png 410
.message	3770	miy-101_01-0051	傒傗偙	「围栏是为了防止人掉下去的东西。但禁止进入了就不需要了对吧」
.message	3780		丂峢丂	「就是这么回事啊」
.message	3790			应该是没考虑过偶尔也会有我这样的人会进入的情况吧。
.transition 0 * 40
.stage	* bgw_sch007a01_00.png 0 0 st_miyako06a02.png 400
.message	3800	miy-101_01-0053	傒傗偙	「没烦人的围栏也好呢。视野清爽许多」
.transition 0 * 40
.stage	* bgw_sch007a01_00.png 0 0 st_miyako09a01.png 400
;.stage	* bgw_sch007a01_00.png 0 0 st_miyako05a02.png 400
;（このポーズと表情ではなく，視線そらしさせたものを？）
;（屋上，カメラを二箇所における背景になっているので，それをうまく使っていくこと）
.message	3810	miy-101_01-0055	傒傗偙	「而且──还会有呼啦～被地面吸走那样的感觉呢」
.message	3820		丂峢丂	「喂」
.screen * *
.transition 0 * 20
.stage	* ev01_029_mugai_a.png 0 0
;（元ＣＧとの中心線から微妙にずらしてますが，厳密に合わせる？）
;.transition 0 * 20
;.stage	* ev01_029.png 0 0
;（ここ，前の地文でうまく切り出し使って）
.message	3830			宫村她毫无警戒向屋顶的边缘靠近过去。
.transition 0 * 20
.stage	* ev01_029.png 0 0
.message	3840			我突然有她会在下一瞬间消失在那边的错觉──
.transition 0 * 20
.stage	* ev01_030.png 0 0
;（フェードスピードは40で？）
.message	3850			我啪的抓住了她的手。
.transition 0 * 20
.stage	* ev01_030_mugai_a.png 0 0
.message	3860	miy-101_01-0057	傒傗偙	「诶，怎么？」
.message	3870		丂峢丂	「很危险啊。别太往那边去」
.message	3880	miy-101_01-0059	傒傗偙	「还真是喜欢担心人呢，广野君」
.message	3890		丂峢丂	「那是你太危险了啦」
.message	3900			想想那个圣诞节的事情，这个宫村宫子确实有点糟糕。
.message	3910			普通的人不会碰触的界限──她虽然不会去跨过，却会一副没事的样子去踩。
.message	3920			虽然不能很好的表达，但就是有那样的感觉。
.screen sc_morning01.png sc_morning01.png
.transition 0 * 20
;.stage	* bgw_sch010a01_00.png 0 0 st_miyako01a09.png 400
.stage	* bgw_sch010a01_00.png 0 0 st_miyako01a09.png 370
;（切り替えのタイミング，注意のこと。表情にも注意。さらにここ１カット，中距離で？）
.message	3930	miy-101_01-0061	傒傗偙	「这算什么呢，如此炽热的眼神？」
.message	3940		丂峢丂	「什么都不～算」
.message	3950			我松开了她的手。
.message	3960			她轻轻抚过我刚才握过的地方，微笑起来。
.transition 0 * 40
.stage	* bgw_sch010a01_00.png 0 0 st_miyako08a02.png 410
;（表情注意）
.message	3970	miy-101_01-0063	傒傗偙	「广野君，我又想要换话题」
.message	3980		丂峢丂	「……又怎么了」
.message	3990	miy-101_01-0065	傒傗偙	「对不起。其实我，看到了哦」
.message	4000			惊。
.message	4010	miy-101_01-0067	傒傗偙	「那本笔记」
.message	4020			回头想起来，我刚才是完全的无防备状态。
.message	4030			画着原稿的笔记本也就那样……。
.transition 0 * 40
.stage	* bgw_sch010a01_00.png 0 0 st_miyako08a03.png 410
;（表情注意）
.message	4040	miy-101_01-0069	傒傗偙	「难道说，广野君，在追逐青春的梦么？」
.message	4050		丂峢丂	「说什么呢」
.transition 0 * 40
.stage	* bgw_sch010a01_00.png 0 0 st_miyako04a02.png 400
;（前からのポーズ変化に問題ないか注意）
.message	4060	miy-101_01-0071	傒傗偙	「别害羞嘛，别害羞嘛。也不是值得害羞的事情啊」
.message	4070			……都已经被看到了，也没法再瞒下去吧。
.message	4080			可恶，分明到之前此为止除了家人和景以外还无一人知晓的。
.message	4090		丂峢丂	「该说是梦想呢还是……。我，其实是个漫画家啦」
.transition 0 * 40
.stage	* bgw_sch010a01_00.png 0 0 st_miyako04a05.png 400
.message	4100	miy-101_01-0073	傒傗偙	「那算什么，自称？　妄想？」
.message	4110		丂峢丂	「事实啊！」
.message	4120			这家伙大概把我当作梦想成为漫画家的人了吧。
.message	4130		丂峢丂	「再怎么看，我也是拥有杂志连载专用版块的啊」
.transition 0 * 40
.stage	* bgw_sch010a01_00.png 0 0 st_miyako04a01.png 400
.message	4140	miy-101_01-0075	傒傗偙	「……真的吗？」
.message	4150		丂峢丂	「真的」
.message	4160	miy-101_01-0076		宫村先用抱有很大兴趣的目光看着我，然后就转换成佩服的表情，深深的呼出一口气。
.message	4170	miy-101_01-0077	傒傗偙	「在画什么样的画呢？」
.message	4180		丂峢丂	「粗略来说……算少女漫画吧」
.transition 0 * 40
.stage	* bgw_sch010a01_00.png 0 0 st_miyako02a06.png 350
;（ちょっとオーバーアクションすぎるか？苦笑）
.message	4190	miy-101_01-0078		她的眼睛瞬间睁大起来。
.message	4200			嘛，吃惊也是当然的吧。
.message	4210	miy-101_01-0079	傒傗偙	「说起来，广野君有着一张很女孩子气的脸呢」
.message	4220		丂峢丂	「…………」
.message	4230			这让我说点什么好呢。
.transition 0 * 40
.stage	* bgw_sch010a01_00.png 0 0 st_miyako03a05.png 400
;（ここ，03a03で？）
.message	4240	miy-101_01-0081	傒傗偙	「呜哇，认真看的话，感觉越来越象呢。还真是有一张女孩脸呢，广野君」
.transition 0 * 40
.stage	* bgw_sch010a01_00.png 0 0 st_miyako03a03.png 400
.message	4250	miy-101_01-0083	傒傗偙	「普通的男孩子说不定会为此走上外道啊」
.message	4260		丂峢丂	「你稍微给点别的方面的反应」
.message	4270		丂峢丂	「同一年纪，而且是男的画少女漫画这样的事情，不应该算是足够的冲击性发言吗」
.transition 0 * 40
.stage	* bgw_sch010a01_00.png 0 0 st_miyako06a03.png 400
.message	4280	miy-101_01-0085	傒傗偙	「唔～嗯，我很少读漫画啦，说起漫画家我也没什么概念……」
.transition 0 * 40
.stage	* bgw_sch010a01_00.png 0 0 st_miyako06a04.png 400
;（この表情でいいか，注意のこと）
.message	4290	miy-101_01-0087	傒傗偙	「咦，怎么好象心情不太好的样子？」
.message	4300			宫村她凝视着我说道。
.message	4310		丂峢丂	「被说像女人还能高兴的男人这世界会存在吗？」
.transition 0 * 40
.stage	* bgw_sch010a01_00.png 0 0 st_miyako06a02.png 400
;（ポーズ変えるか？01ポーズで目閉じ·笑顔を用意してもらうか）
.message	4320	miy-101_01-0089	傒傗偙	「啊啊，我小时候呢，还被取过『假小子』这样的外号呢」
.message	4330		丂峢丂	「谁也没说这个吧」
.message	4340			虽然是这么回事。
.message	4350			宫村她轻轻的笑着，忽然毫无意义的将身体转了一周。
.transition 0 * 40
.stage	* bgw_sch010a01_00.png 0 0 st_miyako05a01.png 400
;（ポーズと表情に注意のこと）
.message	4360	miy-101_01-0091	傒傗偙	「不过，还真是厉害的人呢，广野君。虽然不好怎么表达……不过我明白哦。嗯，也就是说已经工作着的意思呢。唔～嗯」
.message	4370			用上扬的目光看着我，宫村像是在从心里感叹着。
.message	4380		丂峢丂	「有夸奖别人的时间，就努力让自己会被夸奖吧」
.transition 0 * 40
.stage	* bgw_sch010a01_00.png 0 0 st_miyako05a07.png 400
;（表情良いか？）
.message	4390	miy-101_01-0093	傒傗偙	「呜哇，装伟大」
.message	4400		丂峢丂	「读读我的漫画吧。装伟大的台词很多呢，虽然只是笑点」
.transition 0 * 40
.stage	* bgw_sch010a01_00.png 0 0 st_miyako06a02.png 400
;.stage	* bgw_sch010a01_00.png 0 0 st_miyako05a02.png 400
;（この表情に変えて問題ないか，注意のこと。もしくは切り出しで？青空に移行でもいいのかも）
.message	4410	miy-101_01-0094		我轻轻的笑起来，宫村她也扬起了笑脸。
.message	4420			风声鸣动。
.message	4430			舞动着的她的头发和裙子。
.message	4440			在这个天空触手可及的地方，我们对望着，傻乎乎的笑起来。
.panel 0
.overlay * *
.screen * *
.playBGM *
.transition 0 * 10
.stage	* WHITE.png 0 0


;■シーン転換
;■背景：纮自室（冬，２１時
;■　　　　广野纮：私服（冬）
;☆（纮が原稿に取り掛かってるシーン，久濑のＢＧＭを極力鳴らす，，，ということにするか？）
;.transition 0 * 20
.playBGM efBGM022_2.ogg
.transition 1 fadeSide.png 10
.stage	* ev01_033a01.png 0 0
.panel 1
.playSE2 hiro_keitai_male.ogg f 0 *
;（ここにもぶちこんでます。問題あれば，再構築を）
.message	4450			叮<音乐符号>
;.message	4450			ちゃ～ちゃらららららら～??
.transition 0 * 40
.stage	* ev01_033b01.png 0 0
;（フェードスピードは注意のこと）
.message	4460			短信啊。
.message	4470			我停下手中的笔，拿起桌上的手机。
;.panel 2
.transition 0 * 20
.stage	ev01_031a01_kiridashi_FG.png ev01_031a01_kiridashi_base.png 0 0
.effect Cutin ev01_031a01_kiridashi_yuuna.png -10
.wait 100

.transition 0 * 40
.stage	ev01_031a01_kiridashi_FG.png ev01_031c01.png 0 0
;.stage	* ev01_031a01.png 0 0
.effect fadeout
.panel 2
.message	4480			\n\n\n\n\n\n\n\n『明天有晨练不能去喊你起床了。记得要起来老实去学校』
.panel 1
.message	4490			唔。
.transition 0 * 40
.stage	* ev01_031c02.png 0 0
.panel 2
.message	4500			\n\n\n\n\n\n\n\n『追伸：逃掉的话只有死。景』
.panel 1
.message	4510		丂峢丂	「…………」
.message	4520			景还真是说了多余的一句呢。
.message	4530			一直这样的话，真为娶了她的男人担心。
.message	4540		丂峢丂	「嘛，我担心景的未来老公也没用的吧」
.transition 0 * 20
.stage	* ev01_032a01.png 0 0
;☆（ここは，切り出しをうまく使ってください）
.message	4550			我一边嘟哝着，将目光落向原稿。
.message	4560			呼～，放眼望去一片空白啊。
.message	4570			距离截稿已经没有时间了，该拿这纯白的原稿怎么办呢。
.message	4580			如果有谁帮忙也好……。
.message	4590			我没有助手，背景就不用说了，并图以及色调之类的工作都是我自己在做。
.message	4600			在音羽这样的地方都市能不能找到助手是一个问题──
.message	4610			而且就算想雇也没经济能力。
.message	4620		丂峢丂	「不得不做啊」
.transition 0 * 20
.stage	* ev01_032b01.png 0 0
;（フェードスピードは40で？手，布，出てくるので１カットで移行させていいのか注意）
.message	4630			拍下自己的双颊集中起精神，握起细钢笔蘸上墨水，继续描线吧──
.playSE hiro_keitai_2.ogg true 0 *
.transition 0 * 20
.stage	* ev01_033a01.png 0 0
;.transition 0 * 20
;.stage	* ev01_033b01.png 0 0
.message	4640			哔哩哩哩哩哩，哔哩哩哩哩哩。
;.transition 0 * 20
;.stage	* ev01_033a01_mugai_a.png 0 0
;（この切り出し，使うかどうかも考慮のこと。没。意図がわからん）
.message	4650			一惊。
.transition 0 * 20
.stage	* ev01_033b01.png 0 0
;（フェードスピードは注意のこと）
.message	4660		丂峢丂	「……人才刚刚有了干劲，真是的」
.playSE * f * 0
.playSE pi.ogg f 0 *
.transition 0 * 20
.stage	* ev01_031b01.png 0 0
.message	4670			再次拿起手机，慢慢的按下了通话键。
.transition 0 * 20
.stage	* ev01_033c01.png 0 0
.message	4680		丂峢丂	「喂，我是广野」
;■御影チェック
;■　画像に表示でてるので名前はここで開くよ～
;.message	4690	omu-101_01-0003	@大　村	『俺や』
.message	4690	omu-101_01-0003	戝丂懞	『是我』
.message	4700			一个尖锐的的声音传入鼓膜。
.transition 0 * 20
.stage	* ev01_034a02.png 0 0
;（a02でもいいのかもしらんが）
.message	4710		丂峢丂	「……这个黑社会一样的口气您不能想想办法吗，大村先生」
.message	4720			还是感觉极坏的关西腔。
.message	4730	omu-101_01-0005	戝丂懞	『少挑人说话毛病。说起来，怎样了』
.transition 0 * 40
.stage	* ev01_034a01.png 0 0
;（02でもいいのかもしらんが，原稿を落としたことのない性格から冷静な表情で）
.message	4740		丂峢丂	「描线还差5页」
.message	4750			电话的对象，大村义彦是我的责编。
.message	4760			虽然没问过年纪，大概是30到35岁左右的样子。
.message	4770			原本是在一个武斗派出版社作过汉气十足的漫画杂志的编辑的样子。
.message	4780			来到现在的事务所，不知道是哪搞错，而进入了少女漫画的编辑部。
.message	4790			或者说，该不是仅因文件搞错而安排错地方了吧？
.message	4800			恶口暂且不提，附带性格糟糕，脸型凶恶的这个男人，真不知道和其他的少女漫画家们是怎么交流的。
.message	4810	omu-101_01-0007	戝丂懞	『上色还好了，新堂先生。这样能赶上出刊吗？』
.message	4820		丂峢丂	「能赶上的」
.message	4830	omu-101_01-0009	戝丂懞	『如果不行的话，我就临时找些助手，给你送过去好了』
.message	4840			不过，虽然面色凶恶，大村先生工作却很认真。
.message	4850			大概已经准备好了助手，我点头的话就会马上送到音羽来的吧。
.message	4860			但是。
.transition 0 * 40
.stage	* ev01_034a02.png 0 0
.message	4870		丂峢丂	「不用了啦。不是到现在为止都没有原稿赶不上的事么，相信我吧」
.message	4880	omu-101_01-0011	戝丂懞	『是吗，我明白了。你这么说的话就拜托了』
.message	4890	omu-101_01-0013	戝丂懞	『说起来，有好好吃东西吗？』
.transition 0 * 40
.stage	* ev01_034a01.png 0 0
;（ここで02使ってもいいのかもしらんけど……必要なら切り出しを）
.message	4900		丂峢丂	「今天……午饭吃了些米饭，腌菜和酱汤」
.message	4910	omu-101_01-0015	戝丂懞	『……我说你啊，又不是封建社会的农民，要稍微吃些有营养的东西啊』
.transition 0 * 40
.stage	* ev01_034a04.png 0 0
.message	4920		丂峢丂	「穷人啊，除了白米饭以外还能吃什么呢。说起来还不提升稿费吗？」
.message	4930			我这样开玩笑的说着。
.message	4940	omu-101_01-0017	戝丂懞	『那个以前不就说过么。想要加稿费的话就要打倒我啊』
.message	4950		丂峢丂	「为什么漫画家非得向编辑挑战肉搏啊！」
.message	4960			对于学生时代就在棒球部锻炼出一身肌肉的大村先生，运动不足的漫画家怎么可能赢嘛。
.message	4970	omu-101_01-0019	戝丂懞	『男人间，有除了拳头相交之外就无法说明的东西啊』
.transition 0 * 40
.stage	* ev01_034a05.png 0 0
.message	4980		丂峢丂	「完全不理解！」
.message	4990			还真是拿他没辙啊，这个大叔。
.message	5000	omu-101_01-0021	戝丂懞	『嘛，什么时候都可以来挑战。这个先放在一边』
.transition 0 * 40
.stage	* ev01_034a02.png 0 0
.message	5010		丂峢丂	「……又怎么了？」
.message	5020	omu-101_01-0023	戝丂懞	『虽然听着有些矛盾，你还是别太勉强自己。倒下了也没什么人能得到好处啊』
.transition 0 * 40
.stage	* ev01_034a06.png 0 0
;（次の地文でこの表情を？この表情の使いどころにも注意のこと）
.message	5030			哎呀，这还真是毫无感情的温馨的说法方式呢。
.message	5040			不愧是老编了，软硬兼施运用自如……。
.transition 0 * 40
.stage	* ev01_034a05.png 0 0
.message	5050		丂峢丂	「少说傻话了！　不勉强的话就赶不上了！　你身为编辑还能说出这样的话啊！」
.message	5060			比起关心，感觉被骂来骂去我反而会舒心一点。
.message	5070	omu-101_01-0025	戝丂懞	『啊啊，是吗！　如果那样的话，就算死也给我交出稿子。在死掉之前啊。知道吗！』
.message	5080			仅仅说到这儿，大村先生连我的回答都不等就挂了电话。
.transition 0 * 40
.stage	* ev01_034a03.png 0 0
;（この表情への移行，注意）
.message	5090			真是的，该说是关心作者还是如何呢。
.transition 0 * 20
.stage	* ev01_033a01.png 0 0
;（このＣＧから，原稿の切り出しへ移行してもいいかもしれません）
.message	5100			我放下手中的手机，重新拿起笔来。
.message	5110		丂峢丂	「就算你不说我也会交稿的啊」
.message	5120			不过之前的压力，却也一扫而空。
.panel 0
.playBGM *
.transition 0 * 10
.stage	* WHITE.png 0 0
.transition 0 * 10
.stage	* WHITE.png 0 0
.wait 100
.chain 102_01.sc

;■102_01へ。

;.end
