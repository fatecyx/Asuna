; ファイル: 108_01.txt
;■＜１章：８日目＞
;■背景：イメ～ジＢＧ？
;■　　　　广野纮　：私服（冬）
;■　　　　雨宫优子：私服（冬）
.transition 0 * 10
.stage	* WHITE.png 0 0
;（とりあえず白でアタッチしてますが，ここ，イベントＣＧきちんとありますので）
;（ここ，向かって左上に优子？口元をマスク入りでのせて，天から語りかけているように演出？その場合は横顔アップを使って）
.panel 1
.message	100			所追寻的东西究竟是什么。
.message	110			自己到底缺少什么。
.message	120			如果确实有所缺少，那就祈祷可以得到。
.effect Snow
.message	130			只是，在漫长的人生中，去追寻什么的时候──也总会忘记更加重要的事物的啊。
;.effect Snow
.transition 0 * 20
.stage	* ev01_094a01_mugai_a.png 0 0
.message	140	yuk-108_01-0003	@桪丂巕	「于是，你现在，正在想起你所忘记的」
.transition 0 * 20
.stage	* ev01_094a02_mugai_a.png 0 0
.message	150	yuk-108_01-0005	@桪丂巕	「更为重要的事物究竟是什么，看来你已经理解了呢」
.message	160		丂峢丂	「……大概吧」
.message	170			不知何时，在梦中遇到的少女。
.message	180			突然的再会，也让我没有半点惊异。
.message	190			就好象她在那儿是理所当然的一样。
.transition 0 * 20
.stage	* ev01_094a01_mugai_b.png 0 0
.message	200	yuk-108_01-0007	@桪丂巕	「但是」
.message	210	yuk-108_01-0009	@桪丂巕	「取回什么东西的时候，必然也要同时失去些什么。不是吗？」
.message	220		丂峢丂	「没啊，那种东西」
.message	230			她浮起稍微有些困扰的微笑。
.message	240	yuk-108_01-0011	@桪丂巕	「你一直看往前方……所以才没有注意到呢。虽然这不能说是坏事」
.message	250		丂峢丂	「就算是坏事，现在也无法回头了啊。已经早已经起跑了啊」
.transition 0 * 20
.stage	* ev01_094a01_mugai_c.png 0 0
.message	260	yuk-108_01-0013	@桪丂巕	「不，还有机会呢。只是你现在仍未发现」
.message	270	yuk-108_01-0015	@桪丂巕	「自己的心。对于那些女孩真正的心情」
.message	280		丂峢丂	「那些女孩，你指谁啊」
.message	290	yuk-108_01-0017	@桪丂巕	「那个，我想你也是知道的哦」
.message	300			教诫般的口气，柔和的语调。
.effect *
.transition 0 * 20
.stage	* ev01_094a01.png 0 0
.message	310	yuk-108_01-0019	@桪丂巕	「在你的前方，肯定还会有更多的艰辛等待着」
.message	320	yuk-108_01-0021	@桪丂巕	「那会是，十分十分的痛苦艰辛。艰辛到眼泪流干的地步，会想要逃走也说不定」
.message	330		丂峢丂	「干吗啊你。恐吓我么……？」
.message	340			给我展示出这样的未来会很麻烦的啊。
.transition 0 * 20
.stage	* ev01_094a02.png 0 0
.message	350	yuk-108_01-0023	@桪丂巕	「不，没事的」
.message	360	yuk-108_01-0025	@桪丂巕	「一定没事的。因为，你已经懂得了什么叫做温暖。只要有被温柔环绕过的记忆在，你就不会走向错误的方面」
.message	370	yuk-108_01-0027	@桪丂巕	「一定，如此」
.panel 0
;.effect *
;.transition 0 * 10
.transition 0 * 15
.stage	* ev01_094a02_close.png 0 0
.wait 40
.transition 0 * 10
.stage	* WHITE.png 0 0


;■背景：纮自室（冬，６時
;■　　　　广野纮：私服（冬）
;■　　　　新藤景：制服（冬）
.transition 1 fadeSide.png 10
.stage	* ev01_095a01.png 0 0
;（ここ，入りは通常フェ～ドで？）
.panel 1
.message	380			在门边惊了一下而一瞬停下脚步的景，咚咚咚的走了过来。
.playSE hiro_genkan_close.ogg f 0 *
.transition 0 * 20
.stage	* ev01_095b01.png 0 0
.message	390	kei-108_01-0003	丂宨丂	「早安」
.message	400		丂峢丂	「啊啊，早安」
.message	410			我用手支着脸说到。
.message	420			桌子上放着画到一半的原稿，但被景看到也无所谓。
.message	430			景在我身边理所当然，因为她比谁都更可以信用的人。
.message	440			一直在身边最近的人就是景……。
.transition 0 * 20
.stage	* ev01_096a01.png 0 0
.message	450	kei-108_01-0005	丂宨丂	「今天是少见的早起呢？　还是没睡呢？」
.transition 0 * 40
.stage	* ev01_096a03.png 0 0
;（纮の表情，注意して。01の「呆けた」が適当？）
.message	460		丂峢丂	「稍微打了个小瞌睡……不知道看到什么奇怪的梦就醒了」
.message	470	kei-108_01-0007	丂宨丂	「梦，吗……」
.transition 0 * 40
.stage	* ev01_096a02.png 0 0
.message	480	kei-108_01-0009	丂宨丂	「无论是哪个，在这种时间哥哥的眼睛是睁着的真是奇迹。明天说不定太阳就从西边出来了」
.message	490		丂峢丂	「……用点更有艺术性的说法好吧」
.transition 0 * 20
.stage	* ev01_096b01.png 0 0
;（そっぽを向かせるタイミング，注意のこと。フェ～ドスピ～ドも併せて）
.message	500	kei-108_01-0011	丂宨丂	「抱歉啊，反正我没艺术细胞啊。除了运动以外一无所长」
.message	510		丂峢丂	「我也没说到那地步吧」
.message	520			景嘟起嘴唇，把头转向一边。
.message	530		丂峢丂	「好歹也是个大人了，不要老耍小孩脾气」
.message	540			我用手指在她头上咯吱咯吱划着说。
.transition 0 * 40
.stage	* ev01_096b02.png 0 0
.message	550		丂峢丂	「我说你，今天的晨练呢？」
.transition 0 * 20
.stage	* ev01_096c01.png 0 0
;（b差分からこのc差分への移行，注意。景の姿勢の変化，，，は問題ないか）
.message	560	kei-108_01-0013	丂宨丂	「去晨练之前稍微过来下而已。嗯……有着咖喱似的的味道呢」
.message	570		丂峢丂	「不是什么似的，就是咖喱。还真能闻出来啊，分明放在冰箱里的」
.playSE hiro_reizouko_open.ogg f 0 *
.transition 0 * 20
.stage	* ev01_095c01.png 0 0
;☆（立ち上がって，，，注意して）
.message	580			景站起身，去看了一眼冰箱。
.message	590	kei-108_01-0015	丂宨丂	「哼～嗯……」
.playSE hiro_reizouko_close.ogg f 0 *
;（絵とのタイミングが微妙にズレているので注意）
.message	600			景一边关上冰箱的门走回来，一边好象明白了什么似的点着头。
.transition 0 * 20
.stage	* ev01_095b01.png 0 0
;（この挿入タイミングでいいか，留意のこと。さらに纮の椅子向きが変わるので，併せて注意）
.message	610			然后，停在了我的面前。
.message	620		丂峢丂	「干吗？」
.message	630	kei-108_01-0017	丂宨丂	「坐在你身边可以吗？」
.message	640		丂峢丂	「随便你，无所谓……我说，晨练呢」
.transition 0 * 20
.stage	* ev01_095d01.png 0 0
;（c01からd01までの流れ，纮の向き，，，というか姿勢などを考慮に，必要なら切り出しを。黒い丸椅子の移動も，１カットでやってしまってよいのか注意）
.message	650			景也不回答，拉起椅子在我的旁边坐了下来。
;.message	650			景は返事をせず，俺の隣に腰を下ろした。
.transition 0 * 20
.stage	* ev01_097a01.png 0 0
.message	660	kei-108_01-0019	丂宨丂	「原稿进展不错？」
.message	670		丂峢丂	「有进展的话我就好好睡觉了」
.transition 0 * 20
.stage	* ev01_097b01.png 0 0
.message	680			景拿起一张才刚刚画到一半的原稿。
.message	690	kei-108_01-0021	丂宨丂	「原来如此，这次看来也很危险呢」
.transition 0 * 40
.stage	* ev01_097b02.png 0 0
;（フェ～ドスピ～ドは20で？）
.message	700	kei-108_01-0023	丂宨丂	「……嗯？」
.message	710			突然景的声音有些惊讶。
.message	720		丂峢丂	「怎么了？」
.message	730	kei-108_01-0025	丂宨丂	「只是有描线跟以往的风格不太一样的感觉」
.message	740		丂峢丂	「我说你，知道什么叫描线吗」
.message	750	kei-108_01-0027	丂宨丂	「如果是哥哥的话当然知道。都已经多少年了呢，不同的一眼就看的明白」
.message	760		丂峢丂	「分明不明白嘛。跟以往没改变啊」
.message	770	kei-108_01-0029	丂宨丂	「是吗……」
.message	780			虽然表情还没有认同，景却没有再说什么而把原稿放了回去。
.message	790			景会这么细腻颇为少见。
.message	800			不是出什么事反常了吧。
.transition 0 * 20
.stage	* ev01_097c01.png 0 0
.message	810	kei-108_01-0031	丂宨丂	「以前…」
.message	820		丂峢丂	「嗯？」
.transition 0 * 40
.stage	* ev01_097c02.png 0 0
;（フェ～ドスピ～ドは20で？閉じ目にさせていいかも注意のこと）
.message	830	kei-108_01-0033	丂宨丂	「以前经常这样呢」
.message	840			景稍稍晃了下头，顿时有淡淡的芳香扩散开来。
.message	850			确实，小时候天天呆在景她们的屋子里面。
.message	860			座在一起，并不说什么话，只是埋头看景收集的少女漫画。
.message	870			只是，那个时候这家伙身上飘出过这么好闻的味道过吗。
.message	880		丂峢丂	「…………」
.transition 0 * 20
.stage	* ev01_097c02_mugai_a3.png 0 0
;.stage	* ev01_097c02_mugai_a2.png 0 0
;☆（ここだけ，ビスタにするのもありかもしれません。もしくは，とにかく画面を狭める演出で？）
;（挿入位置は注意のこと。切り出し位置は，もう少し上に？）
.message	890			小小的脸，一直都很强气的眼神。
.message	900			虽然是看惯的脸，但却稍微看到嘴唇上少许的光泽。
.message	910			因为最近比较干燥，大概涂了些唇膏吧。
.message	920			在这么近看起来，景的嘴唇有着奇特的柔软。
.transition 0 * 20
.stage	* ev01_097c02.png 0 0
;（景もこの表情のままでいいのか，注意のこと）
.message	930		丂峢丂	「……」
.message	940			狠狠的摇了摇头，赶走那些白痴般的想法。
.message	950			景，并不是那样的啊。
.message	960			……但又是哪样呢？
.message	970	kei-108_01-0035	丂宨丂	「但是」
.message	980		丂峢丂	「诶？」
.message	990	kei-108_01-0037	丂宨丂	「但是现在呢，哥哥从读漫画变成了画漫画，而我也天天忙于部团活动漫画看的越来越少了」
.message	1000		丂峢丂	「干吗啊你，就要死了吗？」

;■御影チェック
;■　また落ち込むと後である以上，ここで一度目を開けさせるか。
;■　どうかな。確かに表情がパ～ペキにはあわないから動かしすぎかな？
.transition 0 * 40
.stage	* ev01_097a01.png 0 0

.message	1010	kei-108_01-0039	丂宨丂	「我还这么年轻干吗要死！」
.message	1020		丂峢丂	「哎呀，你不是说着像怀念过去的老人那样的话」
.message	1030			再怎么说，景也不像会提往事的人物类型。

;■御影チェック
.transition 0 * 20
.stage	* ev01_097c02.png 0 0

.message	1040	kei-108_01-0041	丂宨丂	「并不是那么回事啊…」
.message	1050			突然情绪又低落下去。
.message	1060	kei-108_01-0043	丂宨丂	「只是，果然我和哥哥都变了好多。跟那个时候有太大的不同了」
.message	1070		丂峢丂	「当然会变的啊。到是，如果保持那样才会让人不适」
.message	1080		丂峢丂	「不过你呢，身高和胸部倒没怎么变」
.transition 0 * 20
.stage	* ev01_097d01.png 0 0
;（ここの演出は注意のこと。頭突きらしいので，拡大縮小の画面効果をあざとく使うのもいいのかもしれません）
.message	1090			咚！
.message	1100		丂峢丂	「好痛！」
.message	1110			景用头对下颚来了一下狠狠的爆击。
.message	1120		丂峢丂	「我，我说你……普通的女性会有头撞人吗！」
.transition 0 * 40
.stage	* ev01_097d03.png 0 0
;（すました顔，，，だからこの表情はちと違うのかもしれんが）
.message	1130	kei-108_01-0045	丂宨丂	「真不凑巧，我不是什么普通的女性」
.message	1140			景一幅清爽的表情。
.message	1150		丂峢丂	「完全复活了啊……」
.transition 0 * 40
.stage	* ev01_097d02.png 0 0
;（ここがd03か？確認して，おかしいようなら修正のこと）
.message	1160	kei-108_01-0047	丂宨丂	「是啊，我就是不普通。这么小的身体打篮球之类也不会被人认为是普通的吧」
.message	1170	kei-108_01-0049	丂宨丂	「但是，哥哥不一样吗」
.message	1180	kei-108_01-0051	丂宨丂	「分明是个男人，却是少女漫画家。而且还有连载，在这条路上走到无法回头的地步」
.message	1190		丂峢丂	「結局，你到底想说什么」
.transition 0 * 40
.stage	* ev01_097d04.png 0 0
.message	1200	kei-108_01-0053	丂宨丂	「呵呵」
.message	1210			看到景少见的没有任何恶意的笑容，不觉有些心跳加速。
.message	1220	kei-108_01-0055	丂宨丂	「只是在想虽然我们不是兄妹……却确实有些像呢。比如明白是勉强的事情却勉强去作之类」
.message	1230		丂峢丂	「……我说你，你是不是真的吃错什么药了」
.message	1240	kei-108_01-0057	丂宨丂	「正常的话就无法和哥哥交往下去了啊」
.transition 0 * 20
.stage	* ev01_097e01.png 0 0
.message	1250			景淡淡的说着，站了起来。
.message	1260			我的周围没有正常的人，原来就是这个原因吗……。
.message	1270	kei-108_01-0059	丂宨丂	「嗯，就是勉强自己也不能放弃。在这点上，我的年限可是比哥哥长啊」
.message	1280			虽然景到底想说什么我完全理解不能。
.message	1290			虽然不知为何，但可以确认的是景貌似已经恢复之前的开朗了。
.panel 0
.transition 0 * 10
.stage	* WHITE.png 0 0


;■背景：教室（冬，８時３０分
;■　　　　广野纮：制服（冬）
;■　　　　堤京介：制服（冬）
.playBGM efBGM010.ogg
.transition 1 fadeSide.png 10
.stage	* ev01_098a01.png 0 0
.panel 1
.message	1300	kyo-108_01-0065	嫗丂夘	「重新振作的人还真是厉害啊」
.message	1310			刚刚坐到位置上，京介便不知从哪冒出来，丢出这样的话来。
.message	1320		丂峢丂	「那算什么啊。这个学校最近的倾向是以搞迷糊我为乐吗？」
.transition 0 * 40
.stage	* ev01_098a02.png 0 0
.message	1330	kyo-108_01-0069	嫗丂夘	「那种学校，我可不想上啊……」
.message	1340			京介一副从心底觉得讨厌的表情。
.message	1350			当然，我更讨厌。
.transition 0 * 40
.stage	* ev01_098a03.png 0 0
.message	1360	kyo-108_01-0071	嫗丂夘	「哎呀，到不是那回事啦。摄影研究部的人脑袋还真是石头啊。只会想到些那的摄影研究部都会做的理所当然的事情而已」
.message	1370	kyo-108_01-0073	嫗丂夘	「結局，几乎所有的人都无法突破那个陈旧的框架思维……就因为这个，就毫无根据的说常见剧情有什么坏的之类。真是让人头痛啊」
.message	1380		丂峢丂	「我对部团活动一无所知啊。你对说这些也没用」
.transition 0 * 40
.stage	* ev01_098a04.png 0 0
;（「寝るなよ！」……で表情変わる気もしますが，保留）
.message	1390	kyo-108_01-0077	嫗丂夘	「沉默的听下去才叫友情吧……诶少睡觉啊你！」
.message	1400			我勉勉强强的抬起头。
.message	1410		丂峢丂	「既然沉默无所谓，那睡觉不也一样嘛」
.message	1420	kyo-108_01-0081	嫗丂夘	「完全不一样！　和睡着的人大聊特聊，那我不就单纯是个危险人物而已了吗！」
.message	1430		丂峢丂	「从世界上所有的女性的视点来看，你都已经够危险了」
.message	1440			反正也没什么区别。
.message	1450	kyo-108_01-0085	嫗丂夘	「别把人说成跟强奸犯一样的变态好吧」
.transition 0 * 40
.stage	* ev01_098a05.png 0 0
;（a05は「ジト目」表情ではない気もしますが，とりあえずこれでアタッチ）
.message	1460	kyo-108_01-0087	嫗丂夘	「再说，如果提起现在的这个学园的女性公敌话，第一位被举出来的就该是你吧」
.message	1470		丂峢丂	「干吗会是我啊！」
.transition 0 * 40
.stage	* ev01_098a06.png 0 0
.message	1480	kyo-108_01-0091	嫗丂夘	「咦，不知道吗」
;（ここでa01表情を？）
.message	1490	kyo-108_01-0094		京介轻轻咳嗽了一声。
.message	1500		丂峢丂	「到底是怎么一回事」
.message	1510			我抑制住自己的不安问道。
.transition 0 * 40
.stage	* ev01_098a07.png 0 0
;（ここで「ニヤニヤ」のa07表情を？）
.message	1520	kyo-108_01-0095	嫗丂夘	「简单的说……『广野纮，新藤景，宫村宫子的三角关系会如何进展』这样子，已经成为学园内不小的话题了哦」
.message	1530		丂峢丂	「哈！？」
.transition 0 * 40
.stage	* ev01_098b02.png 0 0
;（フェ～ドスピ～ド注意のこと。この前の台詞で，このポ～ズに？）
.message	1540	kyo-108_01-0099	嫗丂夘	「也就是说……」
;☆（ここ，ちょこっとだけノベルモ～ドで？）
;☆（さらにこの後の京介の表情にも気を配って。表情をまだ入れてない？）
.message	1550			京介开始为我说明起来。
.message	1560			原来，学园的同学们都认为是我和景在交往。
.message	1570			嘛，一直在一起会被这样误解也是没办法的吧。
.message	1580			然后，最近和宫子的接触又比较多……。
.message	1590	kyo-108_01-0101	嫗丂夘	「简而言之，你就是那脚踏两头船的臭男人」
.message	1600		丂峢丂	「…………」
.message	1610		丂峢丂	「一直以为这个学校的人都是一心升学的书虫……没想到还会流传出这么无聊的流言……」
.message	1620			真是头痛啊。
.message	1630	kyo-108_01-0107	嫗丂夘	「新藤同学是1年级就被篮球部正式录用的好手，在学年内无关性別人气都很高。宫村她的可爱也是一眼就看的出来」
.message	1640	kyo-108_01-0109	嫗丂夘	「而你呢……作为逃课神而十分有名啊」
.message	1650		丂峢丂	「…………」
.message	1660			怎么感觉跟其他二人好大的差别啊。
.message	1670	kyo-108_01-0113	嫗丂夘	「这个组合的话，就算是我们这样的学校也会有流言啊。就算是受验高中，来这的也都是这个年纪的少男少女啊」
.message	1680		丂峢丂	「原来如此吗」
.message	1690			学校的家伙们怎么想虽然无所谓，但被当戏看的话就有点那什么了吧。
.transition 0 * 40
.stage	* ev01_098c01.png 0 0
;（フェ～ドスピ～ドは注意のこと。２文後でこのＣＧを？）
.message	1700	kyo-108_01-0117	嫗丂夘	「除此以外，还有这种东西的哦」
.message	1710		丂峢丂	「又是什么？」
.message	1720			京介从口袋中取出来一枚折好的纸片。
.message	1730			拿过来看下内容……。
.transition 0 * 20
.stage	* ev01_099.png 0 0
;（表示タイミング，注意のこと。次はノベルで表示すること）
.message	1740		丂峢丂	「这算啥啊！」
.panel 2
.message	1750			\n\n\n\n\n１：广野纮×新藤景
.message	1750			２：广野纮×宫村宫子
.message	1750			３：广野纮被双方同时甩掉
.message	1750			４：新藤景和宫村宫子萌发出禁断的爱（※大冷门）
.panel 1
.message	1790		丂峢丂	「…………」

;■御影チェック
;.message	1800			パソコンで作成したと思われる表に，手書きの文字でいくつかの人名や数字がごちゃごちゃと書きこまれている。
.message	1800			手制的表单上，乱糟糟写着一些人名和数字。
.message	1810		丂峢丂	「呃～，京介君。这是什么？」
.message	1820			我用尽量稳重的声音问道。
.transition 0 * 20
.stage	* ev01_098b01.png 0 0
;（シフトタイミング，注意のこと）
.message	1830	kyo-108_01-0127	嫗丂夘	「如你所见，你们三人的恋爱方向预测啊。最有人气的是你和新藤同学的组合哦」
.message	1840		丂峢丂	「这个学园的人也都是些闲的无聊的闲人吗？」
.message	1850	kyo-108_01-0131	嫗丂夘	「所以说，再怎么说大家也都是对恋爱感兴趣的年龄啊」
.message	1860		丂峢丂	「就算你说什么『所以说』啊……」
.message	1870			这个瞬间，我突然心中一闪。
.message	1880		丂峢丂	「稍微有些在意一点啊……为什么你会拿着这种东西？」
.transition 0 * 40
.stage	* ev01_098a07.png 0 0
;（bポ～ズでこの表情を？）
.message	1890	kyo-108_01-0137	嫗丂夘	「诶？　诶～嗯，那是因为……」
.message	1900			京介吞吐不清的回答道。
.message	1910		丂峢丂	「难道说，你才是元凶吗！」
.transition 0 * 40
.stage	* ev01_098a04.png 0 0
;.stage	* ev01_098a01.png 0 0
;（この画像への切り替えのタイミング，しっかりと）
.message	1920	kyo-108_01-0141	嫗丂夘	「糟糕了，因为你的反应太有趣一不小心就……。就是啊，不能被当事人看到的啊！」
.message	1930		丂峢丂	「白痴啊～！」
.message	1940			到是，各种意义上的白痴啊。
.message	1950		丂峢丂	「难道说除了散播流言，聚众赌博也是你作的吗」
.message	1960	kyo-108_01-0147	嫗丂夘	「也可以这么说吧」
.message	1970		丂峢丂	「少给我这么说！」
.message	1980			京介故意耸了耸肩。
.message	1990	kyo-108_01-0151	嫗丂夘	「哎呀哎呀，做电影也是要钱的啊。部团费用再怎么说也是不够用啊」
.message	2000		丂峢丂	「为了电影的话，你就算散播朋友的恶意流言也要赚钱吗！」
.transition 0 * 40
.stage	* ev01_098b03.png 0 0
.message	2010	kyo-108_01-0155	嫗丂夘	「这就是被电影附身的人的末路啊……」
.message	2020		丂峢丂	「少说的跟别人的事情似的！」
.message	2030			虽然我已经在这个学园内呆了近2年了，但我现在才注意到这个事实。
.message	2040			这个学园，正经的人根本没有。
.panel 0
.playBGM *
.transition 0 * 10
.stage	* WHITE.png 0 0


;■背景：体育館（冬）１５時
;■　　　　广野纮　　：制服（冬）
;■　　　　羽山瑞希：制服（冬）
.playBGM efBGM020.ogg
.transition 1 fadeSide.png 10
.stage	* bgc_sch006a01_01.png 0 0 st_mizuki_a01a06.png 420
;（表情注意）
;（１５時は夕にしてるパタ～ンもありますが＞グラフィッカ～側で＞放課後のみと規定して，ここでは昼の画像でアタッチしています）
.panel 1
.message	2050	mid-108_01-0003	儈僘僉	「请不要说那样的话啦～」
.message	2060			在安静的体育馆里，羽山尖锐的声音回响着。
.transition 0 * 40
.stage	* bgc_sch006a01_01.png 0 0 st_mizuki_a01a04.png 420
.message	2070	mid-108_01-0005	儈僘僉	「就算是我，也是要升本校的啊」
.message	2080		丂峢丂	「诶，是这样吗？」
.transition 0 * 40
.stage	* bgc_sch006a01_01.png 0 0 st_mizuki_a05a01.png 400
;（「当然のような顔」，，，ではないかもしれないので注意）
.message	2090	mid-108_01-0007	儈僘僉	「普通而言，附中的人不都是升学来这里的吗」
.message	2100			羽山一副理所当然的表情。
.message	2110			说到为什么附中的羽山为什么会在这……。
.message	2120			单单是为了来见景。
.message	2130			说到为什么分明该在上课的我会在这……。
.message	2140			那是因为逃课出来偶尔在这碰上了羽山而已。
.message	2150		丂峢丂	「话说在前面，笨蛋是进不了本校的哦」
.transition 0 * 40
.stage	* bgc_sch006a01_01.png 0 0 st_mizuki_a03a01.png 400
;（表情とポ～ズ注意）
.message	2160	mid-108_01-0009	儈僘僉	「纮前辈都能进来，我怎么可能作不到嘛」
.message	2170			分明还是个后辈，一副自大的口气。
.message	2180		丂峢丂	「但是，我刚才也说过了，这可不是什么认真的好学校」
.transition 0 * 40
.stage	* bgc_sch006a01_01.png 0 0 st_mizuki_a03a02.png 400
;（表情注意）
.message	2190	mid-108_01-0011	儈僘僉	「纮前辈是因为戴着有色眼镜，才会有这种理解方式」
.transition 0 * 40
.stage	* bgc_sch006a01_01.png 0 0 st_mizuki_a02a01.png 400
;（表情とポ～ズ注意）
.message	2200	mid-108_01-0013	儈僘僉	「前辈的大家都那么愉快，而且你知道吗？　这个学园的毕业人有不少名人哦」
.message	2210		丂峢丂	「名人？　比如？」
.message	2220			我的漫画家如果有大成就的话，也会成为名人的一员的吧。
.message	2230			虽然这个现在还丝毫感觉不到。
.transition 0 * 40
.stage	* bgc_sch006a01_01.png 0 0 st_mizuki_a02a02.png 400
;（表情注意）
.message	2240	mid-108_01-0015	儈僘僉	「我怎么可能知道具体的名字嘛。纮前辈你，分明是在校生却不知道吗」
.message	2250		丂峢丂	「……我说你，到那里都是自以为是啊。一定景没有好好教育过你」
.transition 0 * 40
.stage	* bgc_sch006a01_01.png 0 0 st_mizuki_a03a01.png 400
;.stage	* bgc_sch006a01_01.png 0 0 st_mizuki_a01a03.png 420
;（ポ～ズと表情，注意）
.message	2260	mid-108_01-0017	儈僘僉	「啊，对了。景前辈又生气了哦」
.message	2270			不知为何羽山一副高兴的样子。
.transition 0 * 40
.stage	* bgc_sch006a01_01.png 0 0 st_mizuki_a04a02.png 380
.message	2280	mid-108_01-0019	儈僘僉	「郁闷着说什么虽然教育纮前辈不要逃课，但是却完全听不进去之类」
.message	2290			所以说景她算什么人啊。
.message	2300		丂峢丂	「说回来，景她一直都在生气的吧」
.transition 0 * 40
.stage	* bgc_sch006a01_01.png 0 0 st_mizuki_a02a02.png 400
.message	2310	mid-108_01-0021	儈僘僉	「啊啊，说起来也是呢」
.message	2320		丂峢丂	「哇哈哈」
.transition 0 * 40
.stage	* bgc_sch006a01_01.png 0 0 st_mizuki_a02a01.png 400
.message	2330	mid-108_01-0023	儈僘僉	「啊哈哈哈哈」
.transition 0 * 40
.stage	* bgc_sch006a01_01.png 0 0 st_mizuki_a01a07.png 420
;（01a07でも？）
.message	2340	mid-108_01-0025	儈僘僉	「……诶，景前辈是温柔的人才对！　是纮前辈你惹人家生气的不对！」
.message	2350		丂峢丂	「干吗突然就变矛头了啊你」
.message	2360		丂峢丂	「景很可怕的哦。了解她的所有的我这么说不会有错的」
.transition 0 * 40
.stage	* bgc_sch006a01_01.png 0 0 st_mizuki_a01a06.png 420
;（表情注意）
.message	2370	mid-108_01-0027	儈僘僉	「从，从心灵到身体全部都了解吗！　什么时候你们二人踏入了大人的台阶了！」
.transition 0 * 40
.stage	* bgc_sch006a01_01.png 0 0 st_mizuki_a02a04.png 400
.message	2380	mid-108_01-0029	儈僘僉	「那样的讨厌啦！」
.message	2390		丂峢丂	「少奇怪的误解好吧！　干吗我要和景…！」
.transition 0 * 40
.stage	* bgc_sch006a01_01.png 0 0 st_mizuki_a03a09.png 400
.message	2400	mid-108_01-0031	儈僘僉	「讨厌景前辈了吗！　更加不可原谅！」
.message	2410		丂峢丂	「你到底想怎样！」
.message	2420			附中那边，看来一直在进行着育成不正经人物的教育啊。
.message	2430		丂峢丂	「够了啦，你还不回去？　有什么话想说的我替你转告景好了」
.transition 0 * 40
.stage	* bgc_sch006a01_01.png 0 0 st_mizuki_a04a03.png 380
;.stage	* bgc_sch006a01_01.png 0 0 st_mizuki_a04a01.png 380
;（表情とポ～ズ，注意のこと）
.message	2440	mid-108_01-0033	儈僘僉	「到不是有什么话说才来的啊」
.message	2450		丂峢丂	「那你来干吗」
.transition 0 * 40
.stage	* bgc_sch006a01_01.png 0 0 st_mizuki_a05a01.png 380
.message	2460	mid-108_01-0034		羽山嗯的摇了下头。
;.transition 0 * 40
;.stage	* bgc_sch006a01_01.png 0 0 st_mizuki_a05a01.png 380
.message	2470	mid-108_01-0035	儈僘僉	「其实昨日也来了这儿哦。和本校的前辈们共同的练习来着……」


;.if favMiyako_d > 0 miyako_d
.if favMiyako_d > 0 miyako_f
.if favMiyako_d <= 0 miyako_e


;■107_02を通過してる場合。
;☆（ここ，107_02を通過した場合か？ちゃんと確認しておくこと）
.label miyako_e
.message	2480		丂峢丂	「我知道哦。到是，昨日不是见过了嘛」
.message	2490	mid-108_01-0037	儈僘僉	「是吗……。纮前辈我不怎么放在眼里啦」
.message	2500			这个小鬼，总有一天要宰掉。
.goto miyako_f


;■以下，変更なし。
.label miyako_f
.message	2510	mid-108_01-0039	儈僘僉	「景前辈她好厉害啊」
.message	2520		丂峢丂	「很激烈吗」
.message	2530	mid-108_01-0041	儈僘僉	「嗯嗯，很厉害的。激烈的太过分，我都快要失神了……」
.message	2540			这是在说什么呢我说。
.transition 0 * 40
.stage	* bgc_sch006a01_01.png 0 0 st_mizuki_a04a04.png 380
;（表情注意）
.message	2550	mid-108_01-0043	儈僘僉	「其实今天是期待的新刊的发行日来着，但那个扔下过来了」
.message	2560			附带着连部团活动也逃了吧，这家伙。
.message	2570	mid-108_01-0044	儈僘僉	「有些在意呢，关于景前辈的事情」
.message	2580		丂峢丂	「唷～」
.message	2590			不错嘛，景。
.message	2600			貌似被当作比漫画还要重要的存在了啊。
.transition 0 * 40
.stage	* bgc_sch006a01_01.png 0 0 st_mizuki_a05a01.png 380
.message	2610	mid-108_01-0045	儈僘僉	「昨天该说是充满阴气呢还是……练习结束之后就一副清爽的表情」
.message	2620		丂峢丂	「那还是真是让人毛骨悚然啊」
;.transition 0 * 40
;.stage	* bgc_sch006a01_01.png 0 0 st_mizuki_a04a05.png 380
.message	2630	mid-108_01-0047	儈僘僉	「嗯嗯，确实如此……」
.transition 0 * 40
.stage	* bgc_sch006a01_01.png 0 0 st_mizuki_a04a05.png 380
.message	2635	mid-108_01-0048	儈僘僉	「──等你说什么来着！　毛骨悚然什么的，是和景前辈完全没关系的话嘛！」
;.message	2630	mid-108_01-0047	儈僘僉	「ええ，確かにそれはあります……ってなんてことを言うんですか！　不気味なんて，景前辈からもっとも縁遠い言葉じゃないですか！」
;☆（↑ここ，２文に分けたいな，，，）
.message	2640		丂峢丂	「该说你是忙呢，还是爱演独角戏呢」
.playSE AT_chime.ogg f 0 *
.message	2650			铛～叮～铛～咚～。
.message	2660		丂峢丂	「啊，铃声」
.transition 0 * 40
.stage	* bgc_sch006a01_01.png 0 0 st_mizuki_a05a02.png 380
;（前の表情からのこの変化，注意のこと）
.message	2670	mid-108_01-0049	儈僘僉	「纮前辈，逃课真的好吗」
.message	2680		丂峢丂	「一点都不好啊。留级的现实感已经近在眼前了」
.transition 0 * 40
.stage	* bgc_sch006a01_01.png 0 0 st_mizuki_a01a10.png 420
.message	2690	mid-108_01-0051	儈僘僉	「诶诶！　那，那不是很糟糕吗」
.message	2700	mid-108_01-0053	儈僘僉	「虽说纮前辈的人生是前途灰暗，但如果有了留年这样的前科的话，那岂不成为住所不定的无职业者了吗！」
.message	2710		丂峢丂	「能对我说出景都说不出的暴言还真是万分感谢」
.message	2720			好不容易才逃掉了关乎人生的课，结果还是白白浪费时间了啊。
.transition 0 * 40
.stage	* bgc_sch006a01_01.png 0 0 st_mizuki_a04a01.png 380
;（表情とポ～ズ，注意のこと）
.message	2730			都已经放学了，赶快回去工作吧。
.message	2740	mid-108_01-0055	儈僘僉	「那个，纮前辈」
.message	2750		丂峢丂	「干吗啊」
;（「羽山は珍しく真面目な顔を」，，，04a01表情を使う場合，この一連だけで使うように？）
.message	2760			羽山浮起少见的认真的表情。
.message	2770	mid-108_01-0057	儈僘僉	「景前辈她一直都在拼命努力。部团活动当然如此，对于纮前辈的事情也是真正的担心。这件事……」
.message	2780		丂峢丂	「我知道了啦。不是说了吗，景的事情我清楚的很」
.message	2790		丂峢丂	「她确实是过分的拼命了。该说是不知道自己也是有极限的还是什么呢」
.message	2800		丂峢丂	「我也注意一下吧，让她不要过分勉强好了」
.transition 0 * 40
.stage	* bgc_sch006a01_01.png 0 0 st_mizuki_a03a07.png 400
;（表情とポ～ズ，注意のこと）
.message	2810	mid-108_01-0059	儈僘僉	「景前辈还没堕落到需要纮前辈去担心的程度呢」
.message	2820		丂峢丂	「我说你，到底是找我有事谈的还是要来吵架的」
.transition 0 * 40
.stage	* bgc_sch006a01_01.png 0 0 st_mizuki_a03a02.png 400
.message	2830	mid-108_01-0061	儈僘僉	「那当然是──」
.playSE *
.playSE chime_yobidashi.ogg f 0 *
;.playSE kounaihousou.ogg f 0 *
;（仮っす。申し訳ない）
.message	2840			哔咚哔咚。
.transition 0 * 40
.stage	* bgc_sch006a01_01.png 0 0 st_mizuki_a01a09.png 420
;（表情とポ～ズ，注意のこと）
.message	2850	mid-108_01-0063	儈僘僉	「啊？」
.transition 0 * 20
.stage	* ev01_100.png 0 0
;.message	2860	etc-108_01-0003	丂惡丂	「２年Ｂ組の广野纮くん，２年Ｄ組の宫村宫子さん。ただちに進路指導室まで来てください。繰り返します……」
.message	2860	etc-108_01-0003	丂惡丂	『2年B班的广野纮君，2年D班的宫村宫子同学。现在请到前途指导室来。重复一遍……』
.message	2870			…………
.message	2880			……
;.transition 1 fadeSide.png 20
.transition 0 * 20
.stage	* bgc_sch006a01_01.png 0 0 st_mizuki_a03a08.png 400
;.message	2890	mid-108_01-0065	儈僘僉	「いよいよ退学ですか……」
.message	2890	mid-108_01-0065	儈僘僉	「……终于要退学了吗」
.message	2900		丂峢丂	「少说毫无根据的话！」
.transition 0 * 20
.stage	* bgc_sch006a01_01.png 0 0 st_mizuki_a03a10.png 400
;（ちょっとギャグっぽすぎるか？苦笑）
.message	2910	mid-108_01-0067	儈僘僉	「…………啊～啊」
.message	2920		丂峢丂	「干吗，那双可怜人的眼睛！」
.message	2930			说起来，前途指导室？
.message	2940			如果是说逃课的事情的吧，已经会被叫到职员室或者会议室的才对……。
.message	2950			虽说不想是这样，难道真的要让我退学不成？
.message	2960			而且，为什么宫子也在一起……？
.panel 0
.playBGM *
.transition 0 * 10
.stage	* WHITE.png 0 0


;■背景：学園·廊下（冬，１６時
;■　　　　广野纮　　：制服（冬）
;■　　　　宫村宫子：制服（冬）
.overlay * or_miyako02a.png
.playBGM efBGM012.ogg
.transition 1 fadeSide.png 10
.stage	* bgc_sch002a01_02.png 0 0 st_miyako08a01.png 410
;（とりあえずこの時間帯は夕方でアタッチ）
.panel 1
.message	2970	miy-108_01-0003	傒傗偙	「虽然完全不明白为什么被点名……但还真是意外的展开呢」
.message	2980			连一句「先走一步了」都没有说，俺和宫子就离开了前途指导室在走廊上走起来。
.message	2990			在身边，宫子轻轻叹了一口气。
.message	3000		丂峢丂	「老师也很意外了啊」
.transition 0 * 40
.stage	* bgc_sch002a01_02.png 0 0 st_miyako07a02.png 410
;（07a01でも？）
.message	3010	miy-108_01-0005	傒傗偙	「啊啊，对啊对啊。完全放弃了呢，那个老师」
.message	3020			宫子这么说着不知为何突然明朗起来。
.message	3030		丂峢丂	「嘛，不放弃也不行的吧」
.message	3040			被点名是理所当然的。
.message	3050			只有我和宫子，到现在还没有填报未来志愿表。
.message	3060		丂峢丂	「但你也太过分了」
.transition 0 * 40
.stage	* bgc_sch002a01_02.png 0 0 st_miyako08a01.png 410
.message	3070	miy-108_01-0007	傒傗偙	「诶诶，是这样吗。都差不多了啦」
.transition 1 fadeSide.png 40
.stage	* WHITE.png 0 0
;（白挿んでますが，保留で）
.message	3080			对于老师的「表格怎么样了」的提问，我的回答是，
.message	3090		丂峢丂	「忘光了」
.message	3100			而另一边，宫子的则是…
.message	3110	miy-108_01-0009	傒傗偙	「杂用，扔掉了」
.message	3120			如此。
.message	3130			虽然轮不到我说，宫子这也太差了。
.transition 1 fadeSide.png 40
.stage	* bgc_sch002a01_02.png 0 0 st_miyako07a04.png 410
.message	3140	miy-108_01-0011	傒傗偙	「偶尔想着认真听课到最后的，没想到最后还有这样的埋伏啊……」
.message	3150	miy-108_01-0013	傒傗偙	「我分明什么坏事都没做，为什么运气这么不好呢」
.message	3160			到底是哪里搞错了，能把自己正当化到这种地步啊。
.message	3170		丂峢丂	「但是啊……」
.transition 0 * 40
.stage	* bgc_sch002a01_02.png 0 0 st_miyako08a02.png 410
;（「不審そうな顔」，，，ではないかもしれませんが）
.message	3180			我停下脚步，宫子也一脸疑惑的站住了。
.message	3190		丂峢丂	「那个老师，说了不会置若罔闻的哦」
.message	3200	miy-108_01-0015	傒傗偙	「嗯？」
.message	3210		丂峢丂	「你成绩那么优秀，如果平常行为好点的话会有更好的前途之类」
.transition 0 * 40
.stage	* bgc_sch002a01_02.png 0 0 st_miyako07a02.png 410
;（表情，要注意）
.message	3220	miy-108_01-0017	傒傗偙	「啊啊」
.message	3230			宫子缓缓的点了点头。
.transition 0 * 40
.stage	* bgc_sch002a01_02.png 0 0 st_miyako07a03.png 410
;（表情注意）
.message	3240	miy-108_01-0019	傒傗偙	「无所谓了嘛，那种小事」
.message	3250		丂峢丂	「可恶，分明我一直相信你也是补习组的……竟然被背叛了」
.transition 0 * 40
.stage	* bgc_sch002a01_02.png 0 0 st_miyako07a01.png 410
;（表情注意）
.message	3260	miy-108_01-0021	傒傗偙	「说起来纮君真的是笨蛋先生呢……」
.message	3270		丂峢丂	「少刺人痛处！」
.message	3280			从教师的语气中才觉察到，宫子的成绩一直是年级顶级的样子。
.message	3290			虽然说人不可貌相，但竟然被完美的骗了啊……。
.transition 0 * 40
;.stage	* bgc_sch002a01_02.png 0 0 st_miyako01a04.png 400
.stage	* bgc_sch002a01_02.png 0 0 st_miyako01a04.png 350
;（表情とポ～ズ注意）
.message	3300	miy-108_01-0023	傒傗偙	「啊～，好累呢」
.message	3310			宫子伸了一个大大的懒腰。

; 好感度判定
.if favMiyako > 0 miyakotrue
.if favMiyako <= 0 miyakobad

.label miyakotrue
.chain 108_02.sc
.end

.label miyakobad
.chain 108_03.sc
.end

;■好感度チェック
;■宫子好感度(≧3)
;→108_02へ。
;■宫子好感度(＜3)
;→108_03へ

;.end
