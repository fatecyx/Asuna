; ファイル: 207_01.txt
;■＜２章：７日目＞
;■背景：廃墟（夏，１６時
;■　　　　堤京介　：制服（夏）
;■　　　　雨宫优子：私服（夏）
.playBGM efBGM025mix.ogg
;.frame finder.png
;.set finderCounter = 0
;.screen sc_evening01.png sc_evening01.png
.transition 0 * 10
.stage	* bg_ex001a01_02.png 0 0
;.stage	* bgs_normal014a01_02.png 0 0
;（カメラフレ～ムから入ってますが，おかしなようならトルこと。さらにここ，背景の切り出しの連続カットで？）
;（街の全景からイン？）
.panel 2
.message	100			\n\n\n\n\n\n\n\n曾经，这个城市降临过一场巨大的灾难──
.message	110			\n\n\n\n\n\n\n\n掠过大海的寒风卷出旋涡，刺耳的声音响彻冬夜的城市。
.message	120			\n\n\n\n\n\n\n\n在大规模地震后的城市里，倒塌的建筑物中人们瑟瑟发抖，寒风嘲笑着他们，不断将火之恶魔带到各处。
.message	130			\n\n\n\n\n\n\n\n那个夜晚情形，据说凄惨到无法描述的地步。
.message	140			\n\n\n\n\n\n\n\n那不祥的赤炎燃烧着，燃烧着，就算半夜下起雨来也毫不停息，仿佛连天空都要烧灼了一般……。
.message	150			\n\n\n\n\n\n\n\n城市被残暴的蹂躏，无数的生命悄然逝去。
.message	160			\n\n\n\n\n\n\n\n然后，时光流转──
.panel 0
.transition 0 * 20
.stage	* bg_ex001a01_02.png 0 0


;■御影チェック
.set finderCounter = 2541

.frame finder.png
;.set finderCounter = 5000
.set finderCounter = 2541


.screen sc_evening01.png sc_evening01.png
.transition 0 * 20
.stage	* bgs_normal014a01_02_mugai_b.png 0 0
.panel 1
;.stage	* bgs_normal014a01_02.png 0 0
.message	170		嫗丂夘	「那爪痕还余息尚存……」
.transition 0 * 20
.stage	* bgs_normal014a01_02_mugai_c.png 0 0
.message	180			不知是因复兴计划的预算而放置了，还是单纯的开发迟缓。
.message	190			在这一角，还残存着灾害当时的模样。
.message	200			小的时候被说过不要靠近倒塌的建筑物。
.message	210			现在看起来也多少有些危险……。
.transition 0 * 20
.stage	* bgs_normal014a01_02_mugai_f.png 0 0
;（インのタイミング，注意して）
.message	220		嫗丂夘	「新藤到底跑到哪去了啊～」
.message	230			放学后，我们──具体的说，是我想拍些奇怪的风景来到这里。
.message	240			但是分明应该是在这寂寞的景色中和几乎不发一语的新藤走着的，但不知何时就走散了。
.message	250			好奇怪──
.message	260			仅仅一会，真的只是仅仅一会没有注意新藤的身影便不见了。
.transition 0 * 20
.stage	* bgs_normal014a01_02.png 0 0
.message	270			总不可能是迷路啊。
.frame *
.transition 0 * 20
.stage	* bgs_normal014a01_02.png 0 0
;（もいっこ後でフレ～ムはずす？）
.message	280		嫗丂夘	「真是安静啊……」
.screen * *
;☆（次のＣＧみたいなところにもスクリ～ンはかけるべきか？ここはよくよく考察して）
.transition 0 * 20
.stage	* ev02_056a01.png 0 0
;（特殊なインをしてます。気を付けて）
.message	290			我放下摄像机，环顾四周。
.transition 0 * 20
.stage	* ev02_056b01.png 0 0
;（フェ～ドスピ～ドは注意して。全体的に一歩ずらす？）
.message	300			这里安静的完美，安静到几乎不会认为这儿还是音羽。
.message	310			安静到恐怖──倒不如说是，十分恐怖。

;■御影チェック
;.message	320			昼間だっていうのに，なんでこんな不気味な雰囲気が漂ってるんだ。
.message	320			分明还不到晚上，为什么会有这么不协调的气氛。

.message	330		嫗丂夘	「就算是夏天……也不该在这种时间开试胆大会吧」
;.message	330		嫗丂夘	「いくら夏だからって……こんな昼間から肝試しとはね」
.message	340			第一，试胆大会要和女孩子一起听她呀呀的叫着才有意义啊……。
.message	350		嫗丂夘	「不是考虑这种问题的时候」
.message	360			虽然不认为这世上能有可以诱拐新藤那样恐怖的女孩子的人……。
.message	370			但这在这种地方丢下她一个确实很糟。
.transition 0 * 20
.stage	* ev02_057.png 0 0
;（フェ～ドの仕方には注意して）
.message	380			手机……果然是没有信号啊。
.transition 0 * 20
.stage	* ev02_056c01.png 0 0
;.transition 0 * 20
;.stage	* bgs_normal014a01_02.png 0 0
.message	390		嫗丂夘	「新藤～！　喂～！」
.message	400		嫗丂夘	「小～景，出来吧～！」
.message	410			…………
.message	420			……
.transition 0 * 40
.stage	* ev02_056b01.png 0 0
;（フェ～ドスピ～ドは注意して。ここで手を下げさせる必要はない？前のを続行で？）
.message	430			果然不在啊。
.message	440			我也没做什么惹人厌的事情，也不会是生气回去了啊。
.transition 0 * 20
.stage	* ev02_058.png 0 0
;（表示タイミングは注意して）
.message	450		嫗丂夘	「嗯～，到底怎么回事啊」
.message	460			……为什么。
.message	470			分明不是天气炎热，但汗珠却越来越多。
.message	480			这里是大量的人失去性命，被忘掉并被舍弃的地方。
.message	490			所以，肯定哪里有些不同。
.message	500			空气和味道──时间的流动，都并非寻常才对。
.message	510		嫗丂夘	「不早点找到新藤的话……」
;.playBGM *
;.playBGM efBGM017_2.ogg
.transition 0 * 20
.stage	* ev02_059a03.png 0 0
;（表情，注意して。a02表情でも？）
;（インのタイミング，注意して）
.message	520	yuk-207_01-0003	桪丂巕	「……为什么你会在这里呢？」
.message	530		嫗丂夘	「…………」
.message	540		嫗丂夘	「雨宫……优子？」
.message	550			好像融合在坏掉的街市中一样，一名黒衣的少女站在了我的眼前。
.message	560			「为什么你会在这里呢」是我的台词好吧。
.message	570			──虽然我想这么说，却张不开口。
.message	580			十分自然的，几乎就是这寂寞风景的一部分的她，不止为何让我有些压力……。
;■真剣
.transition 0 * 40
.stage	* ev02_059a01.png 0 0
.message	590	yuk-207_01-0005	桪丂巕	「不行的哦，呆在这种地方」
.message	600		嫗丂夘	「虽然你这么说」
.message	610			既然来了也没有办法。
.message	620	yuk-207_01-0007	桪丂巕	「这里拥有的，只是已经结束的过去的残骸」
.message	630	yuk-207_01-0009	桪丂巕	「没有给你看的有趣的东西。只是浪费时间，回去的好哦」
.message	640		嫗丂夘	「但是，新藤还没」
.message	650			虽然觉得雨宫说的没错，但总不可能只有一个人回去。
.transition 0 * 40
.stage	* ev02_059a02.png 0 0
.message	660	yuk-207_01-0011	桪丂巕	「新藤？　新藤景小姐吗？」
.message	670			雨宫优子歪了一下头。


;■御影チェック
;.playBGM *
;.playBGM efBGM017_2.ogg


.transition 0 * 40
.stage	* ev02_059a04.png 0 0
;（ここの优子の表情は注意して。b01まで続行させて良いのかも）
.message	680	yuk-207_01-0013	桪丂巕	「最后，摄影得到同意了是吧」
.message	690		嫗丂夘	「算吧。说起来，你认识新藤吗？」
.message	700	yuk-207_01-0015	桪丂巕	「不……只是听宫子和广野先生提到过而已」
.transition 0 * 20
.stage	* ev02_059b01.png 0 0
;（フェ～ドスピ～ドは注意して。このa05の使いどころに関しても）
.message	710	yuk-207_01-0017	桪丂巕	「嘛，总之走吧」
.message	720		嫗丂夘	「现在的话，邀我约会有些困扰啊」
;■笑顔
.transition 0 * 40
.stage	* ev02_059a04.png 0 0
;（フェ～ドスピ～ドは注意して）
.message	730	yuk-207_01-0019	桪丂巕	「这是您的遗言吗？」
.message	740			这个笑容恐怖无比。
;■真剣
.transition 0 * 40
.stage	* ev02_059a01.png 0 0


;■御影チェック
.playBGM *


.message	750	yuk-207_01-0021	桪丂巕	「笑话就开到这里，赶快去找新藤小姐吧」


;■御影チェック
.playBGM efBGM017_2.ogg


;■シ～ン転換
;■と言っても，背景は変わらず。白フェ～ド。
.transition 1 fadeSide.png 20
.overlay	or_yuko02a_610p.png * *
.screen	sc_evening01_610p.png sc_evening01_610p.png sc_evening01_610p.png
.stage	st_yuko13f04-.png 0 0 bg_scl007a01_02_f.png 0 0 bg_scl007a01_02_n.png 0
.effect	WScroll2 * 60 -2


;.screen sc_evening01.png sc_evening01.png
;.transition 1 fadeSide.png 20
;.stage	* bgs_normal014a01_02.png 0 0
;（実際は歩きスクロ～ルが入る，，，はず）
.message	760			雨宫优子踏着如羽毛般轻松的脚步，毫无迷惑的向前走着。
.message	770			好像完全不害怕周围令人毛骨悚然的空气。
.message	780		嫗丂夘	「雨宫你经常来这附近吗？」
.transition 0 * 40
.stage	st_yuko13f01-.png 0 0 bg_scl007a01_02_f.png 0 0 bg_scl007a01_02_n.png 0
.message	790	yuk-207_01-0023	桪丂巕	「怎么可能。我也没闲到那种地步哦」
.transition 0 * 40
.stage	st_yuko13f02-.png 0 0 bg_scl007a01_02_f.png 0 0 bg_scl007a01_02_n.png 0
.message	800	yuk-207_01-0025	桪丂巕	「只是……」
.message	810			雨宫寂寞的微微一笑。
.transition 0 * 40
.stage	st_yuko11f03-.png 0 0 bg_scl007a01_02_f.png 0 0 bg_scl007a01_02_n.png 0
.message	820	yuk-207_01-0027	桪丂巕	「……因为这里是引人怀念的地方」
.message	830		嫗丂夘	「怀念……？」
.message	840			在城市变为燎原之前，住在这附近的吗。
.message	850			用广野的话，雨宫应该要比我们年纪要大，所以并不是不可能。
.message	860			说不定会有些特别的回忆在吧。
.transition 0 * 40
.stage	st_yuko13f05-.png 0 0 bg_scl007a01_02_f.png 0 0 bg_scl007a01_02_n.png 0
.message	870	yuk-207_01-0029	桪丂巕	「为什么觉得怀念，我到是也完全不明白哦<音乐符号>」
.message	880		嫗丂夘	「怎么！？」
.message	890			刚才的不是认真模式吗。
.message	900	yuk-207_01-0031	桪丂巕	「不不。其实我呢，记忆力很差的哦」
.message	910	yuk-207_01-0033	桪丂巕	「以前的事情，总会微妙地忘记」
.message	920		嫗丂夘	「这个已经跨越了爱忘事的程度，已经进入白痴等级了啊……」
.transition 0 * 40
.stage	st_yuko11f09-.png 0 0 bg_scl007a01_02_f.png 0 0 bg_scl007a01_02_n.png 0
;（表情，注意）
.message	930	yuk-207_01-0035	桪丂巕	「我说你，难道刚才是在认真的取笑我吗？」
;■笑顔
.transition 0 * 40
.stage	st_yuko11f06-.png 0 0 bg_scl007a01_02_f.png 0 0 bg_scl007a01_02_n.png 0
;（表情，注意）
.message	940	yuk-207_01-0037	桪丂巕	「就算如此，我也是算是姐姐的哦」
.transition 0 * 40
.stage	st_yuko13f02-.png 0 0 bg_scl007a01_02_f.png 0 0 bg_scl007a01_02_n.png 0
.message	950			这个最不可信。
.message	960			在旁边走着的雨宫优子，无论怎么被太阳晒着，在这炎热中也不出一滴汗。
.message	970			难道是当上一流的女演员或者模特的话，再热的天拍摄也不会出汗的那种……特殊体质吗？
.message	980			能怪到这种地步的女生，我真是闻所未闻。
.transition 0 * 40
.stage	st_yuko11f07-.png 0 0 bg_scl007a01_02_f.png 0 0 bg_scl007a01_02_n.png 0
.message	990	yuk-207_01-0039	桪丂巕	「啊啊，堤先生的眼睛里充满了对年纪大的女性的憧憬」
.message	1000		嫗丂夘	「没有那种东西」
.message	1010			我对雨宫的话一笑了之。
.message	1020		嫗丂夘	「憧憬什么的跟我无缘。如果真的喜欢的话，我肯定会直接冲上去」
.message	1030			一直抱着单方面的的感情，沉闷着之类我才不要。
.message	1040			所以，就算碰碎也好直接一点更让人愉快，也不会浪费时间。
;■呆れ
.transition 0 * 40
.stage	st_yuko11f05-.png 0 0 bg_scl007a01_02_f.png 0 0 bg_scl007a01_02_n.png 0
.message	1050	yuk-207_01-0041	桪丂巕	「真的该说是积极呢，还是不知畏惧呢」
.message	1060		嫗丂夘	「人生，可是没有慢吞吞的余裕的哦？」
.transition 0 * 40
.stage	st_yuko11f02-.png 0 0 bg_scl007a01_02_f.png 0 0 bg_scl007a01_02_n.png 0
.message	1070	yuk-207_01-0043	桪丂巕	「正如所言」
.transition 0 * 40
.stage	st_yuko12f02-.png 0 0 bg_scl007a01_02_f.png 0 0 bg_scl007a01_02_n.png 0
;（表情，注意して）
.message	1080	yuk-207_01-0045	桪丂巕	「不过……」
.message	1090			不知为何，雨宫优子歪了一下头。
.message	1100			她一边想着该说的话，一边缓缓的走着。
.message	1110			──在墓地一样的街道上走着的黑衣少女啊。
.message	1120			可能是构景太好的原因，我反而失去了拍摄的心情。


;■御影チェック
;■　ここだけはフェ～ドを止めずに押し切るか。
;.effect *
;.effect end


.transition 0 * 40
.stage	st_yuko11f01-.png 0 0 bg_scl007a01_02_f.png 0 0 bg_scl007a01_02_n.png 0
.message	1130	yuk-207_01-0047	桪丂巕	「堤京介先生」
.message	1140		嫗丂夘	「怎么？」
;■御影チェック
;.message	1150			雨宫は，足をとめて微笑する。
;■真剣
.transition 0 * 40
.stage	st_yuko11f04-.png 0 0 bg_scl007a01_02_f.png 0 0 bg_scl007a01_02_n.png 0
.message	1160	yuk-207_01-0049	桪丂巕	「你真的恋爱过吗？」
.message	1170		嫗丂夘	「干吗啊这么突然」
.message	1180		嫗丂夘	「话说在前面，我比广野之类要经验丰富的多」
.transition 0 * 40
.stage	st_yuko11f10-.png 0 0 bg_scl007a01_02_f.png 0 0 bg_scl007a01_02_n.png 0
.message	1190	yuk-207_01-0051	桪丂巕	「不，并不是数量的问题哦」
.message	1200			雨宫摇了摇头。
.message	1210	yuk-207_01-0053	桪丂巕	「你真的喜欢过谁吗？」
.message	1220		嫗丂夘	「…………」
.message	1230			那种事情，我不知道。
.message	1240			自己的心情是真是假，根本都没有确认过吧。
.message	1250			雨宫盯着不回答的我──


;■御影チェック
.effect end
.screen * *


;.transition 0 * 40
;.stage	st_yuko13f04-.png 0 0 bg_scl007a01_02_f.png 0 0 bg_scl007a01_02_n.png 0
;（ここ，イベントＣＧからの切り出しで？）
.transition 0 * 20
.stage	* ev02_060a01_mugai_b.png 0 0
.message	1260			突然伸出了手指。
.transition 0 * 20
.stage	* ev02_060a01_mugai_a.png 0 0
.message	1270	yuk-207_01-0055	桪丂巕	「……找到了哦」
;.effect *
.transition 0 * 20
.stage	* ev02_060a01.png 0 0
;（もいっこ前からイン？）
.message	1280			在黒衣少女指向的地方，她在那里。


;■御影チェック
;■　この前に解除しないと駄目だよな。
;.screen * *


.transition 0 * 20
.stage	* ev02_060a02.png 0 0
;（フェ～ドスピ～ドは注意して）
.message	1290	kei-207_01-0003	丂宨丂	「啊……」
;■笑顔
.message	1300	yuk-207_01-0057	桪丂巕	「那么，接下来就交给年轻的两个人单独相处吧」
.message	1310		嫗丂夘	「你是婚介所的大妈吗你」
.transition 0 * 20
.stage	* ev02_060b01.png 0 0
.message	1320			雨宫并不回答，而只是微笑着向新藤走过去。
.transition 0 * 20
.stage	* ev02_061a01.png 0 0
;（ここの演出は注意して。スクロ～ル，切り出しも絡めて）
.message	1330			两名少女靠近，然后擦肩而过。
.message	1340	kei-207_01-0005	丂宨丂	「……你是？」
;■微笑
.message	1350	yuk-207_01-0059	桪丂巕	「我是──雨宫优子」
.transition 0 * 20
.stage	* ev02_061b01.png 0 0
.message	1360	kei-207_01-0007	丂宨丂	「雨宫……？」
.message	1370	yuk-207_01-0061	桪丂巕	「嗯，有缘再见吧」
.transition 0 * 20
.stage	* ev02_061b01_mugai.png 0 0
.message	1380			她笑着说过之后，雨宫优子便穿过新藤消失在了废墟的尽头。
.panel 0

;.panel 0
.playBGM *
.transition 0 * 10
.stage	* WHITE.png 0 0
.wait 100
.panel 1
.message	1390			……………………
.message	1400			…………
.message	1410			……


;■背景：砂浜（夏，１７時
;■　　　　堤京介：制服（夏）
;■　　　　新藤景：制服（夏）
.playBGM efBGM028mix.ogg
.transition 1 fadeSide.png 10
.stage	* ev02_062a01_mugai_g.png 0 0
;.stage	* ev02_062a01_mugai_e.png 0 0
;.stage	* ev02_062a01.png 0 600
;（とりあえずこれでインしてます）
;.stage	* bgs_normal007a01_02.png 0 0
;.panel 1
.message	1420			波浪拍打的声音温柔的耳边回响。
.message	1430			微暖的海风，沙沙响着的沙滩，让我有着异样的安心感。
.message	1440			就算这海边什么都没有，也会比那个鬼城有着更多的真实感。
;■無表情
.message	1450	kei-207_01-0009	丂宨丂	「太阳落下去了，却还是很热呢」
.message	1460		嫗丂夘	「……是啊」
.message	1470			无事找到新藤到是不错，但她却好像在想些什么。
.message	1480			本来想换下心情而把她带到了海边，但还是有些疙瘩的样子。
.transition 0 * 20
;.stage	* ev02_062a01.png 0 600
.stage	* ev02_062a01_mugai_f.png 0 0
;☆（ev02_062a01の使いどころはしっかりと）
;.stage	* ev02_062a01_mugai_d.png 0 0
.message	1490	kei-207_01-0011	丂宨丂	「刚才的雨宫是认识的人吗？」
.message	1500			由于太无聊，新藤张口问道。
.message	1510		嫗丂夘	「啊啊，嘛总之算是认识」
.transition 0 * 20
.stage	* ev02_062a01_mugai_a.png 0 0
.message	1520	kei-207_01-0013	丂宨丂	「那个人就是雨宫小姐啊……」
.message	1530		嫗丂夘	「嗯，你也认识么？」
.message	1540	kei-207_01-0015	丂宨丂	「不是──」
.message	1550	kei-207_01-0017	丂宨丂	「以前，哥哥提到过这个名字，所以……」
.message	1560		嫗丂夘	「……哥哥，吗」
.message	1570	kei-207_01-0019	丂宨丂	「啊……」
.message	1580			新藤的脸瞬间红透。
.message	1590	kei-207_01-0021	丂宨丂	「想，笑话你就笑吧。以前就是这么叫的没办法好吧」
.message	1600		嫗丂夘	「我也没说不好啊。不无所谓的吗，你爱怎么叫怎么叫」
.message	1610	kei-207_01-0023	丂宨丂	「……你真的这么想？」
.message	1620		嫗丂夘	「你注意来注意去不累吗」
.message	1630			说着，我对她笑了一下。
;■真剣
.message	1640	kei-207_01-0025	丂宨丂	「说的……也是呢」
;■感心
.message	1650	kei-207_01-0027	丂宨丂	「偶尔前辈也会说些正经的话呢」
.message	1660		嫗丂夘	「嘛，还说刚才的。雨宫是广野介绍给我的哦」
.message	1670			那是刚刚离开摄影研究部不久的事。
.message	1680			跟广野打电话时，说笑说「介绍可爱的女孩子给我认识」，就真的接受然后介绍给我了雨宫。
.message	1690			去拜托广野这种事，大概当时的我太累了吧。
.message	1700		嫗丂夘	「对于我来说只是朋友──？　嗯～，感觉也不算是什么朋友」
.message	1710		嫗丂夘	「嘛，不是什么奇怪的关系就是」
;■睨み
.message	1720	kei-207_01-0029	丂宨丂	「谁也没问那种问题」
.message	1730			说的也是。
.message	1740			就算真的我和雨宫是情人也和新藤没有任何关系。
.message	1750			我找什么借口呢我？
;■ここから砂浜（夕景）にするか
.transition 0 * 20
.stage	* ev02_062a01_mugai_c.png 0 0
.message	1760	kei-207_01-0031	丂宨丂	「今天的摄影也差不多该结束了呢」
.message	1770		嫗丂夘	「是啊～」
.message	1780			总之也不能拉着是女孩子的新藤到太晚。
.transition 0 * 20
.stage	* ev02_062a01_mugai_b.png 0 0
.message	1790		嫗丂夘	「不过真是遗憾呢，今天拍摄的差不多都要束之高阁了」
.message	1800	kei-207_01-0033	丂宨丂	「是吗？」
.message	1810		嫗丂夘	「那个废墟的气氛，稍微有些异样的过分吧～」
.message	1820			至今为此的储备和今天的影像很难联系起来。
.message	1830			虽然编辑的时候可以试验下，但毫无意义的卖奇特也没用。
.transition 0 * 20
.stage	* ev02_062a01_mugai_d.png 0 0
;.stage	* ev02_062a01_mugai_c.png 0 0
.message	1840	kei-207_01-0035	丂宨丂	「那个，前辈」
.message	1850		嫗丂夘	「是是」
;■真剣
.message	1860	kei-207_01-0037	丂宨丂	「我呢，这么想」
.transition 0 * 20
.stage	* ev02_063c01.png 0 0
;（波の演出は注意して）
.message	1870			哗哗哗，一个大浪拍过来又席卷而去。
;★波打ち際の寄り絵（キャラ無し）を一枚用意しておくか？
;海は１～４章通して登場頻度が高そうだし，演出時に繋ぎの絵として使えるかも。
.transition 0 * 20
.stage	* ev02_063c02.png 0 0
.message	1880			在那一瞬的静寂中，新藤张开了嘴唇。
.transition 0 * 20
.stage	* ev02_063c03.png 0 0
.message	1890	kei-207_01-0039	丂宨丂	「数年以前，音羽的街市全部都是那样的废墟过是吧？」
.message	1900		嫗丂夘	「啊啊，好像十分严重的」
.message	1910			我的老爸也去取了材，那时的报道和资料我也读过一些。
.message	1920		嫗丂夘	「虽然我没有实际体验过……」
.message	1930		嫗丂夘	「大概，就好像是世界末日一般吧」
.transition 0 * 20
.stage	* ev02_063c04.png 0 0
.message	1940	kei-207_01-0041	丂宨丂	「但是……城市却复活了」
;.transition 0 * 20
;.stage	* ev02_063c01.png 0 0
.message	1950			我点了一下头。
.transition 0 * 20
.stage	* ev02_063c01.png 0 0
;.transition 0 * 20
;.stage	* ev02_063c02.png 0 0
.message	1960		嫗丂夘	「人类这种生物，不懂得什么叫做放弃啊。无论是怎样的逆境都会努力的爬出来」
.transition 0 * 20
.stage	* ev02_063c02.png 0 0
;.transition 0 * 20
;.stage	* ev02_063c03.png 0 0
.message	1970			这并不仅仅指音羽，全人类的历史都证明了这点。
.transition 0 * 20
.stage	* ev02_063c03.png 0 0
.message	1980	kei-207_01-0043	丂宨丂	「嗯，看到你就会这么想」
.message	1990	kei-207_01-0045	丂宨丂	「就算被摄影研究部赶出来，无论怎样也追寻着自己喜欢的东西好厉害呢」
.message	2000		嫗丂夘	「……你的企图是什么？」
.message	2010	kei-207_01-0047	丂宨丂	「夸奖你而已！　别说我像还有什么阴谋吧！」
.message	2020		嫗丂夘	「哦哦，那还真是失礼」
.message	2030	kei-207_01-0049	丂宨丂	「真是的……」
.transition 0 * 20
.stage	* ev02_063c04.png 0 0
.message	2040			新藤用十分厉害的眼神瞪了我一眼。
;.transition 0 * 20
;.stage	* ev02_062a01.png 0 600
.transition 0 * 20
.stage	* ev02_064b02.png 0 0
;（挿入位置，注意して）
.message	2050	kei-207_01-0051	丂宨丂	「……我也差不多该动起来了呢」
.message	2060			她浮起一个平静的微笑。
.transition 0 * 40
.stage	* ev02_064a02.png 0 0
.message	2070	kei-207_01-0053	丂宨丂	「时间不停流逝，不能一直止步不前呢」
.message	2080		嫗丂夘	「怎么，突然大彻大悟了？」
.transition 0 * 40
.stage	* ev02_064a03.png 0 0
;.transition 0 * 40
;.stage	* ev02_064a02.png 0 0
.message	2090	kei-207_01-0055	丂宨丂	「因为从今往后，积极到乱来的前辈也要和我一直在一起的错哦」
.message	2100			不明白究竟是在夸奖还是在取笑的口气。
.message	2110			但是，她的笑容却没有消失。
.transition 0 * 40
.stage	* ev02_064a02.png 0 0
;（ここの表情，注意して）
.message	2120	kei-207_01-0057	丂宨丂	「我……」
;■苦笑
.transition 0 * 40
.stage	* ev02_064a07.png 0 0
.message	2130	kei-207_01-0059	丂宨丂	「我…大概休息的太久了吧……」
.transition 0 * 40
.stage	* ev02_064b02.png 0 0
;.stage	* ev02_064a02.png 0 0
.message	2140	kei-207_01-0061	丂宨丂	「堤前辈那样的人都不服输努力着，我可不想输呢」
.message	2150		嫗丂夘	「难道是，讨厌失败的本性终于出现了吗？」
.transition 0 * 40
.stage	* ev02_064a03.png 0 0
.message	2160	kei-207_01-0063	丂宨丂	「哼，少管我」
.message	2170			虽然口气充满了挑战，但她确实在微笑着。
.message	2180		嫗丂夘	「我觉得你没有止步不前啊。不是这样跟我合作着吗」
;■不安
.transition 0 * 40
.stage	* ev02_064b04.png 0 0
;（ここの表情，注意して）
.message	2190	kei-207_01-0065	丂宨丂	「现在只是被堤前辈拉着走而已……」
.message	2200		嫗丂夘	「慢慢来就好。总之我还想让你配合我的摄影呢」
;■微笑
.transition 0 * 40
.stage	* ev02_064b02.png 0 0
;☆（視線，注意して。京介に向けさせる？）
.message	2210	kei-207_01-0067	丂宨丂	「是啊……」
.transition 0 * 20
.stage	* ev02_062b01.png 0 600
;（カメラ向けるタイミングが違うかもしれませんが，とりあえずここから）
.message	2220			柔和的海风抚摸着新藤景，而她静静的看着水平线的彼端──
;.panel 0
;.vscroll	0	-10
;.endScroll f
;.panel 1
;（ここはパネル解除する必要はないかもしれませんが）
.message	2230			而我直到胶卷用完为止，都一直拍摄着她的身影。
.panel 0
.transition 0 * 20
.stage	* ev02_062b01.png 0 600
;（１クリック移行防止のため，画像を一枚挿んでます）
.vscroll	0	-7
.endScroll f
;（ここはパネル解除する必要はないかもしれませんが）
.playBGM *
.transition 0 * 10
.stage	* WHITE.png 0 0
.transition 0 * 10
.stage	* WHITE.png 0 0
.wait 100

.chain 208_01.sc
;■208_01へ。

;.end
