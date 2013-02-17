; ファイル: 201_01.txt
;■＜２章：１日目＞
;■背景：京介自室（夏，８時
;■　　　　堤京介：制服（夏）
.transition 0 * 10
.stage	* ev02_076a00.png 0 0
;.stage	* bgc_home002a01_00.png 0 0
.panel 1
.message	100			朝阳扫过我闭着的眼睑。
.message	110			虽然不是什么值得自夸的事情，但我从很久以前就是睡的很死的类型。
.message	120			附带起床也总是毫无异常精神满满。
.message	130			我的辞典里没有低血压这种词。
.transition 0 * 20
.stage	* ev02_065.png 0 0
.message	140		嫗丂夘	「……哟」
.message	150			随着轻快的声音，我迅速地坐起身来。
.transition 0 * 20
.stage	* bgc_home002a01_00.png 0 0
.message	160			瞬间换好衣服，拿起自己的提包。
.message	170			当然，也决不会忘记把爱用的摄像机放进去。
.message	180		嫗丂夘	「嗯，走吧」
;■白バック
.transition 0 * 20
.stage	* WHITE.png 0 0
.message	190			打开房间的门，来到走廊。
.message	200		嫗丂夘	「老爸……还没回来啊。跑哪闲逛去了啊」
.message	210			有着记者这样一个可疑头衔的老爸基本上很少回家。
.message	220			从很久以前开始，从学校回家也没有人会对我说「欢迎回来」。
.message	230			这种状态已经持续几年了呢──
.message	240			小孩的时候也就算了，而现在家人不在家反而会有各种各样的方便到无所谓。
.message	250			嗒嗒嗒嗒地一口气走下楼梯。
.message	260			……………………
.message	270			…………
;■空
.playSE semishigure_b.ogg true 0 *
;.playSE semishigure_b.ogg f 0 *
;（「かすかな蝉の声」ではありませんが·苦笑。ル～プさせるのかにも留意して。つか，この効果音，出がちょっと遅いか？）
.transition 0 * 20
.stage	* bgs_sky001a01_00.png 0 0
.message	280		嫗丂夘	「呜哇～，好热～……」

;■御影チェック
;（蝉の声，用意する？用意する場合は，プロロ～グもちと考えて）
;.message	290			軽く朝メシを食って外に出ると，かすかに蝉の声が聞こえ，目がくらみそうな日差しが降り注いでいた。
.message	290			稍微吃些早饭走出门，顿时传来此起彼伏的蝉鸣，阳光也刺得让人睁不开眼睛。

.message	300			啊啊～，已经是初夏了啊。
.message	310			我最喜欢的季节。
.message	320			虽说去学校很烦人，但这个时期却可以迈出轻快的脚步。
.message	330		嫗丂夘	「我出门了！」
.playSE * 20
.message	340			在无人的门口高声打过招呼，也不顾会被邻居们觉得可疑，我走出门去。
;.panel 0



;;■御影チェック
;.wait 50
;.panel 0
;;.wait 170
;.transition 0 * 9
;.stage	* WHITE.png 0 0
;.wait 260
;.transition 0 * 8
;.stage	* second_title.png 0 0
;.wait 350

;;.panel 0
;;.transition 0 * 10
;;.stage	* second_title.png 0 0
;.message	341			\a　
;（タイトルは適当に作ってます。後できちんとしたものを作ってもらって！フェ～ドスピ～ドも適当）
;;.transition 0 * 10
;;.transition 0 * 5
;.transition 0 * 7
;.stage	* WHITE.png 0 0

;.wait 140




;■背景：通学路（夏，８時２０分
;■　　　　堤京介：制服（夏）
;■　　　　新藤景：制服（夏）
;.playBGM efBGM020.ogg
.playBGM efBGM051.ogg
;.playBGM BGM054_sample.ogg
.screen sc_morning01.png sc_morning01.png
;.transition 1 fadeSide.png 10
.transition 0 * 10

;■御影チェック
;■　左のモブないバ～ジョンを使用
;.stage	* bgs_normal019m01_00.png 0 0
.stage	* ev02_009b01.png 0 0

.panel 1
.message	350			一边和朋友和认识的人打着招呼，我快步独自向前走着。
.message	360			倒不是因为我很急，而是今天早上完全没有钻进朋友圈里聊天的心情。
.message	370			这怡人清晨的气息想要一人独享而已。
.message	380			我就这样一边哼着一边向前走，忽然──
.message	390		嫗丂夘	「哦，竟然能看到那个啊……」
.transition 0 * 20
.stage	* ev02_009.png 0 0
;（表示タイミング，注意して。この前で？）
.message	400			清爽的短发，比周围的女生们小上一圈的的娇柔身体。
.message	410			稍微会让人觉得有些生硬的走路姿势──
.message	420			毫无疑问，是那个原为篮球少女的新藤景。
.screen * *
.transition 0 * 20
.stage	* ev02_010.png 0 0
;（表示タイミング，注意して。もちっと前で？）
.message	430	kei-201_01-0003	丂宨丂	「你又说那种没边的话～。就算是我，也不会被每次都被骗哦」
;.message	440			彼女はころころと楽しそうに笑いながら，何人かの友達とおしゃべりしている。
.message	440			她愉快的笑着，和朋友们聊着天。

;■御影チェック
;.message	450			新藤の周りにいる女の子たちの顔は異様に嬉しそうだ。
.message	450			新藤周围的女孩子们的表情也似乎十分愉快。

.message	460			感觉好像只要和新藤聊天就会很愉快。
.message	470			她，是被大家欢迎的啊。
.screen sc_morning01.png sc_morning01.png
.transition 0 * 20
.stage	* ev02_009.png 0 0
;（この画像に戻してよいか，注意して）
.message	480			我停下脚步，把手伸向提包。
.message	490		嫗丂夘	「唔～……」
.screen * *
.transition 0 * 20
.stage	* ev02_011.png 0 0
;（ここの演出は注意して。ビデオカメラのモニタ～に表示されてる画を動かしたいな……）
.message	500			把取出摄像机对向新藤景。
.message	510			看着液晶显示器上她的身影──
.screen sc_morning01.png sc_morning01.png
.transition 0 * 20
.stage	* ev02_012.png 0 0
;.stage	* ev02_009.png 0 0
;（この画像に戻してよいか，注意して）
.message	520			我又马上放下了镜头，摇了摇头。

;■御影チェック
;■　景たちが立ち去った後の京介です。
;.screen * *
;.frame finder.png
;.set finderCounter = 0
;;☆（ここはカウンタ～の数字を調整を）
;.transition 0 * 20
;.stage	* ev02_010.png 0 0
;;（切り出しで？）
.message	530		嫗丂夘	「嗯～……总觉得哪有些不对劲啊」
;.frame *

.panel 0
.playBGM *
.transition 0 * 10
.stage	* WHITE.png 0 0


;■シ～ン転換
;■背景：教室（夏，１３時
;■　　　　堤京介　　：制服（夏）
;■　　　　宫村宫子：制服（夏）
.playSE AT_chime.ogg f 0 *

;■御影チェック
;■　ＢＧＭ開始を少し後ろに。ここはチャイムの音があるしね。
;.playBGM efBGM010.ogg

.transition 1 fadeSide.png 10
.stage	* bgs_sch004m02_01.png 0 0
;（夏教室の背景でアタッチを。ないね…。とりあえず適当な背景でアタッチしてます。要差し替えのこと）
.panel 1
.message	540			铛～叮～铛～咚～。
.message	550			第2节课结束的铃声响起，向老师行过礼后，教室瞬间混乱起来。
.transition 0 * 20
.stage	* ev02_013a02.png 0 0

;■御影チェック
.playBGM efBGM010.ogg

;（a01の使いどころ，注意して）
.message	560		嫗丂夘	「呼～」
.message	570			我把头躺着还展开着的笔记上。
.message	580			升入三年级之后课业的等级变的过分的高，被点名的次数也越来越多，消耗也越来越大。
.message	590			现在还只是六月。
.message	600			距离真正考试还久的很。
.transition 0 * 40
.stage	* ev02_013a01.png 0 0
.message	610			这真是地狱啊……。
.transition 0 * 20
.stage	* ev02_013b01.png 0 0
;（フェ～ドスピ～ドは注意して）
.message	620	miy-201_01-0003	@傒傗偙	「堤堤～」
.message	630		嫗丂夘	「…………」
.message	640	miy-201_01-0005	@傒傗偙	「喂～，堤堤叫你的啦」
.message	650		嫗丂夘	「……………………」
;■笑顔
.message	660	miy-201_01-0007	@傒傗偙	「原来如此，那您希望从哪个秘密开始曝光呢？　顺带一提我的推荐是──」
.transition 0 * 20
.stage	* ev02_181a01.png 0 0
;.stage	* bgs_sch004m02_01.png 0 0 st_miyako01b01.png 400
;（夏教室の背景でアタッチを。ないね…。とりあえず適当な背景でアタッチしてます。要差し替えのこと）
.message	670		嫗丂夘	「有何贵干，宫村同学」
.message	680			我顺势坐起身，正対那声音的来源。
;.transition 0 * 40
;.stage	* bgs_sch004m02_01.png 0 0 st_miyako02b01.png 350
.message	690	miy-201_01-0009	傒傗偙	「嗯嗯，要能从最开始就这样干脆的回答的话我会很高兴哦」
.message	700		嫗丂夘	「就算我恨那分班的人也没办法啊……」
.message	710			我再次发出在这3个月间不知发过多少次的牢骚。
.message	720			到底是作了什么孽，让我升入3年级和这个可怕的宫村宫子在同一个班啊。
.message	730			仅是如此倒也好……。
.message	740		嫗丂夘	「那个，我只有两个愿望」
.transition 0 * 40
.stage	* ev02_181a02.png 0 0
;.stage	* bgs_sch004m02_01.png 0 0 st_miyako00b06.png 350
;（09表情との使い分けは注意して）
.message	750	miy-201_01-0011	傒傗偙	「唔？」
.message	760		嫗丂夘	「能不能别叫我堤堤啊？」
.message	770			这种像娱乐界的名字的感觉真的不喜欢。
.transition 0 * 40
.stage	* ev02_181a01.png 0 0
;.transition 0 * 40
;.stage	* bgs_sch004m02_01.png 0 0 st_miyako00b05.png 350
.message	780	miy-201_01-0013	傒傗偙	「但是啊，不是『堤京介』吗。除了『堤堤』以外没有什么别的外号可以取了啊」
.message	790		嫗丂夘	「第一为什么非得喊外号不可啊」
.message	800			升入同一班级，刚以为她好不容易记住了我的名字，便被这家伙取了一个这么奇怪的外号。
;■あっさり
;.transition 0 * 40
;.stage	* ev02_181a01.png 0 0
;.stage	* bgs_sch004m02_01.png 0 0 st_miyako00b01.png 350
.message	810	miy-201_01-0015	傒傗偙	「那么，第2个愿望是什么？」
.message	820		嫗丂夘	「第1个无视吗！？」
.transition 0 * 40
.stage	* ev02_181a01_close.png 0 0
;.transition 0 * 40
;.stage	* bgs_sch004m02_01.png 0 0 st_miyako00b02.png 350
.message	830	miy-201_01-0017	傒傗偙	「虽然值得同情，但世间也有那无法实现的愿望啊<音乐符号>」
.message	840			这便是她笑颜满面的台词吗。
.message	850		嫗丂夘	「感觉既然说了第2个也是徒劳便失去心情了……」
.transition 0 * 40
.stage	* ev02_181a01.png 0 0
;.transition 0 * 40
;.stage	* bgs_sch004m02_01.png 0 0 st_miyako02b01.png 350
.message	860	miy-201_01-0019	傒傗偙	「嘛，有话说是世上无难事只要肯登攀哦」
.message	870		嫗丂夘	「……那能不能别再这样拿我的秘密当玩具？」
.message	880	miy-201_01-0021	傒傗偙	「我任何时候都可以捅出去。这样不也很有趣吗<音乐符号>」
.message	890		嫗丂夘	「求您别……」
.message	900			啊啊，就要哭出来了。
.message	910			我在1，2年纪堆积的数多罪行。
.message	920			如果传到学校那边至少够我退学5次以上的捏他，都被这个宫村宫子捏在手里。
.message	930			如果说到为什么此等绝密的事实会被捏在3年级以前根本没什么接触的宫村手里的话──
;.transition 0 * 40
;.stage	* bgs_sch004m02_01.png 0 0 st_miyako02b02.png 350
.message	940	miy-201_01-0023	傒傗偙	「难得被告诉这种事情，为了舒适的学园生活当然要物尽其用哦」
.message	950			原因很简单。
.message	960			便是那个既是宫村的男朋友，也是我的死党的那个男人。
.message	970			已经退学的那个死男人，口无遮掩的把各种各样的事情都漏给了宫村。
.message	980			他轻轻松松得对宫村说来说去，对我来说却是大麻烦。
.message	990			那家伙已经不算什么朋友了。
;.transition 0 * 40
;.stage	* bgs_sch004m02_01.png 0 0 st_miyako02b01.png 350
.message	1000	miy-201_01-0025	傒傗偙	「总之呢，堤堤的愿望我明白了」
.message	1010		嫗丂夘	「虽然明白，却完全没有想要去实现是吧……」
;.transition 0 * 40
;.stage	* bgs_sch004m02_01.png 0 0 st_miyako03b02.png 400
.message	1020	miy-201_01-0027	傒傗偙	「去食堂，给我买些饮料来。袋装乌龙茶最好哦」
;.transition 0 * 40
;.stage	* bgs_sch004m02_01.png 0 0 st_miyako03b01.png 400
;（目をつむらせていいか，注意して）
.message	1030	miy-201_01-0029	傒傗偙	「当然会去的对吧？」
.message	1040		嫗丂夘	「完全成了跟班么……。真是的，把人都当什么了……」
;■真面目くさって
.transition 0 * 40
.stage	* ev02_181a03.png 0 0
;.stage	* bgs_sch004m02_01.png 0 0 st_miyako06b04.png 400
;（表情には注意して。06b01でも？）
.message	1050	miy-201_01-0031	傒傗偙	「1年级时的学园祭，把偶尔一个人来的附校女孩子带到部团活动室里──」
.message	1060		嫗丂夘	「哇～！」
.message	1070			再怎么说，也不至于把那件事提出来吧！
;■笑顔
.transition 0 * 40
.stage	* ev02_181a01.png 0 0
;.stage	* bgs_sch004m02_01.png 0 0 st_miyako06b02.png 400
.message	1080	miy-201_01-0033	傒傗偙	「当然会去的吧？」
.message	1090		嫗丂夘	「是……」
.message	1100			当然，我完全没有抵抗的权利。
.panel 0
.playSE *
.playBGM *
.transition 0 * 10
.stage	* WHITE.png 0 0


;■シ～ン転換
;■背景：教室（夏，１４時
.transition 1 fadeSide.png 10
.stage	* ev02_014.png 0 0
.panel 1
;■イツト　ハベカラヌ　ナカニモ，キシカタ　ユクサキ　カキクラシ
.message	1110	miy-201_01-0035	傒傗偙	「而今瞻前顾后，不知该行往何方──」
.message	1120			在静静的教室里，清澈的声音回响着。
.message	1130			在刚刚满腹的这个时间段，再听到这个毫无沉渍的读音，不由便有了几分睡意。
;■ツレヅレト　スギニシカタノ　オモウタマエ　イデラルルニ　ツケテモ　コリズマノ　ウラノミルユメノ　ユカシキヲ
.message	1140	miy-201_01-0037	傒傗偙	「追忆往事如烟，聊以慰藉」
;■シオヤクアマヤ　イカガオモハン
.message	1150	miy-201_01-0039	傒傗偙	「试问：无所顾虑思重叙，柔情聊君怀我无？」
;■サマザマ　カキツクシタマウ　コトノハ，オモイヤルベシ
.message	1160	miy-201_01-0041	傒傗偙	「此外种种话语，读者自可想象。」
.message	1170			宫村如果这样普普通通的话还是挺可爱的啊。
.message	1180			嘛，我对别人的女人没什么兴趣。
.message	1190			在现在，我有兴趣的是──
.message	1200			没有别人，只有那个新藤景而已。
.message	1210			虽说她和那叫宫子的家伙也有点关系让人少许头疼，姑且忽视这点好了。
;■サマカワリタルココチスルモ　イミジキニ，サラヌカガミトノタマイシオモカゲノ，ゲニミニソイタマエルモカイナシ
.message	1220	miy-201_01-0043	傒傗偙	「甚是怪异，令人望而悲叹。公子临别吟唱『镜影随君永不离』时的形貌，始终不能消失。然而这犹如镜中花，水中月，只得空自嗟叹──」
.message	1230			这样下去会很无聊啊……。
.message	1240			那么有趣的素材，我才不会放弃。
.panel 0
.playVoice *
.transition 0 * 10
.stage	* WHITE.png 0 0


;■背景：学園·廊下（夏，１６時
;■　　　　堤京介：制服（夏）
;■　　　　新藤景：制服（夏）
;.playBGM efBGM012.ogg
.playBGM efBGM052.ogg
;.playBGM BGM052_sample.ogg
.transition 1 fadeSide.png 10
.stage	* bgs_sch002m01_02.png 0 0
.panel 1
.message	1250			第一当然很可爱。
.message	1260			甚至可以说比目前为止摄影研究部拍过的所有的女孩子都要漂亮。
.message	1270		嫗丂夘	「但是，并不只是如此」
.message	1280			不管多么美丽的脸，不能被拍摄下来不会有任何意义。
.message	1290			就这点来说，一个人在体育馆运球的新藤可以说是绝对合格。
.message	1300			不知远望何处的目光，娇小的背影，梦幻般的气氛。
.message	1310			能那样美妙如画的情节，可不是想拍就能拍的到的。
.message	1320			为了这次能让那副情景印入镜头──
.transition 0 * 20
.stage	* ev02_015.png 0 0
.message	1330		嫗丂夘	「哦，出来了出来了」
.message	1340		嫗丂夘	「……嗯？」
.message	1350			奇怪啊。
.message	1360			新藤景她每天都是和朋友一起走出教室的，为什么今天会是一个人？
.message	1370		嫗丂夘	「…………」
.message	1380			总之，跟平常一样追上去看看吧……。
.message	1390			新藤景她也一如往常，一歩一歩地，好像在确认什么似的缓缓的走着。
.transition 0 * 20
.stage	* bgs_sch002m01_02.png 0 0
;（消す演出は注意して。どっかから切り出しを？）
.message	1400			突然，新藤的身影消失在了拐角那边。
.message	1410			还是和往常一样，就这样离开学校回家吗。
.message	1420		嫗丂夘	「偶尔也得发生点什么吧，一直如此也不会拍到什么好画……」
.transition 1 fadeSide.png 20
.stage	* bgc_sch003a01_02.png 0 0
.message	1430			我自言自语着，转过拐角的那个瞬间──

;■学園·階段
.playBGM * * 0
.playSE kei_karaburi_a.ogg f 0 *

;■御影チェック
;.effect Cutin ev02_017.png -1 1000
.effect Cutin ev02_017_mikage.png -1 1000
.message	1431			\a　

.wait 100
.effect fadeout

;.transition 1 fadeSide.png 20
;.stage	* bgc_sch003a01_02.png 0 0
;（ここの演出も注意して。切り出しを？フェ～ドの仕方，スピ～ドなどにも留意）
;（イベントＣＧを使う場合は，横から流れるカットインを）
.message	1440			咻！
.message	1450		嫗丂夘	「哇！？」


;.message	1460			凄まじい勢いで，なにかが目の前をかすめた。
.message	1460			不知有什么东西以迫人的速度擦过我的脸颊。


.message	1470		嫗丂夘	「什么，什么东西！？」
.message	1480			如果不是反射而退了一步的话，刚才的就是直击啊。
.message	1490	kei-201_01-0005	丂宨丂	「切，歪了吗」
.message	1500		嫗丂夘	「诶？　诶？」
.message	1510			是我眼睛的错觉吗。
.playBGM efBGM041.ogg
.transition 0 * 20
.stage	* ev02_016.png 0 0
.message	1520			新藤拿着提包如燃烧的怒火般站在楼梯前。
.message	1530		嫗丂夘	「哦哦……」
.message	1540			这顺脊背而上这种恶寒般的感觉。
.message	1550			原来如此啊──
.message	1560			这就是──恐怖啊──
;■冷静
.message	1570	kei-201_01-0007	丂宨丂	「那么，嗯」
.message	1580			新藤轻轻摇了下手中的提包。

;■御影チェック
;■　どう見ても，ＣＧが鞄じゃないわな。
;.message	1590			さっき眼前をかすめたのはアレか。

.message	1600	kei-201_01-0009	丂宨丂	「到今天正好一周呢。实在没想到您能执着的跟踪这么久呢」
.message	1610	kei-201_01-0011	丂宨丂	「既然作到这一步，杀了你也不算犯罪吧」
.message	1620		嫗丂夘	「等下等下。我国可是法治国家啊！　私刑是绝对禁止的啊！」
;■怒り
.message	1630	kei-201_01-0013	丂宨丂	「法治国家是什么东西啊。少说莫名其妙的话！」
.message	1640			糟了，是个笨蛋女孩。
.message	1650		嫗丂夘	「呃～，简单容易理解的说，你好像误解了些什么啊！」
.message	1660	kei-201_01-0015	丂宨丂	「误解的是你吧」
.message	1670		嫗丂夘	「何出此言？」
.message	1680			为什么是身为高年级的我使用敬语啊。
.message	1690	kei-201_01-0017	丂宨丂	「光说就能讲明白的阶段早过去了哦」
.message	1700		嫗丂夘	「啊……」
.message	1710	kei-201_01-0019	丂宨丂	「仅仅是一天两天的偷窥的话，我也会睁一只眼闭一只眼」
.message	1720	kei-201_01-0021	丂宨丂	「如果在这时注意到而自己放弃的话，我也不会生气」
.message	1730	kei-201_01-0023	丂宨丂	「但是你──」
;.effect Cutin ev01_019.png 200
;.wait 100
;.effect fadeout
;☆（とりあえず１章の流用で挿んでますが，余計なようならトルこと。このＣＧは上下透明にしても良い？）
.message	1740			唰啦，新藤的眼瞳愤怒的燃烧了起来。
.message	1750	kei-201_01-0025	丂宨丂	「看着我不吭声就自以为是，然后如此执着──也就是早抱有被杀的觉悟了对吧？」
.message	1760		嫗丂夘	「没有没有，我完全没有那觉悟啊！」
.message	1770	kei-201_01-0027	丂宨丂	「死吧」
.message	1780			完全说不通啊～！
.message	1790			新藤扔下提包，瞬间缩短了距离。
.playSE kei_karaburi_b.ogg f 0 *
.effect Cutin ev02_017.png -1 1000
.message	1791			\a　
.wait 100
.effect fadeout

.message	1800			我连吃惊的空都没有，右拳直击便迅速接踵而来。
.message	1810		嫗丂夘	「等下啊喂！」
.playSE kei_karaburi_b.ogg f 0 *
;☆（ここの効果音は使いまわしやめて，別のに？）
.effect Cutin ev02_018.png -1 -1000
;.wait 100
;.effect fadeout

.message	1820			无视拼命喊着的我，新藤以右腕的击打姿势，顺势甩出肘击。
.message	1830			──到底是在哪掌握的这种技术！
.effect fadeout
.message	1840			我一边暗自佩服，一边逃出她右肘击的轨道。
.message	1850	kei-201_01-0029	丂宨丂	「切～！」
.message	1860		嫗丂夘	「哎呀，不是『切～』的问题吧！」
.message	1870			我迅速的和新藤保持距离，也不敢放松警戒。
.message	1880			倒是，为什么我不得和一个女生作这种战斗不可。
.playSE kei_meramera.ogg true 0 *
;☆（メラメラではなくて，ゴゴゴ系のを？）
.transition 0 * 20
.stage	* ev02_019.png 0 0
;（このＣＧの表示タイミング，注意して）
.message	1890	kei-201_01-0031	丂宨丂	「真是的……你不慌慌张张乱躲的话就能一瞬让你升入极乐的」
.message	1900		嫗丂夘	「我，我还不想升入极乐啊」
.message	1910		嫗丂夘	「说起这个新藤同学。你真的是误解了一些事情啊」
.message	1920	kei-201_01-0033	丂宨丂	「给我闭嘴」
.message	1930			新藤总之回了句话，同时也带着充满杀气的眼睛慢慢收近之间的距离。
.message	1940			如果我稍稍有一点的大意的话──
.message	1950			我就会在一瞬间跳过生死线。
.message	1960		嫗丂夘	「而且──」
.playSE *
;（止める位置，注意して）
.transition 0 * 20
.stage	* ev02_020a01.png 0 0
;（フェ～ドスピ～ドは40で？）
.message	1970	kei-201_01-0035	丂宨丂	「怎么？」
.message	1980		嫗丂夘	「那样激烈的转动裙子的话，只会让看热闹的各位更兴奋的哦」
.playBGM * * 0
.transition 0 * 40
.stage	* ev02_020b01.png 0 0
.message	1990	kei-201_01-0037	丂宨丂	「哈……！？」
.message	2000			她呀的一声，瞬间站直然后按住了裙子。
.playBGM efBGM052.ogg
;.playBGM BGM052_sample.ogg
;（インのタイミング，注意して）
.message	2010			然后，偷偷的看过一圈。
.message	2020			现在正好是每个班级归宅班会刚刚结束的时间。
.message	2030			自然而然，在楼梯旁边走过的学生络绎不绝。
.message	2040	kei-201_01-0039	丂宨丂	「…………哼」
.message	2050			新藤脸红透着捡起了自己的提包。
.transition 0 * 40
.stage	* ev02_020c01.png 0 0
.message	2060	kei-201_01-0041	丂宨丂	「绝对不会有下次！」
.transition 0 * 20
.stage	* ev02_020d01.png 0 0
;（フェ～ドスピ～ドには注意して）
.message	2070			她用如美杜沙般的目光瞪了我一眼，慢慢的走下楼去。
.message	2080		嫗丂夘	「哈……」
.message	2090		嫗丂夘	「捡了一条命啊」
.message	2100			充满兴趣的看着发展的同学们也开始次第散去。
.message	2110			我也回去吧。
.message	2120			好久没作过的剧烈运动让我累的要死……。
.message	2130		嫗丂夘	「……不是这回事！」
.message	2140			不去解开误会的话，下次拍摄新藤的话毫无疑问肯定没命。
.message	2150		嫗丂夘	「差不多是该到下个阶段的时候了吧」

;■背景：校門
.screen sc_evening01.png sc_evening01.png
.overlay * or_kei02a.png
.transition 1 fadeSide.png 20
.stage	* bgs_sch009a01_02.png 0 0 st_kei08b01.png 400
;（フェ～ドスピ～ドやパネル有無など注意して）
;（立ち絵の演出については注意して。距離感に微妙に違和が生まれているかもしれません）
.message	2160			就是如此，再次发现了新藤家的小景。
.message	2170			嘛，那么慢的走着追不上才会奇怪。
.message	2180			现在，该怎么打招呼好呢……。
.message	2190			分明没什么烦恼的必要的。
.transition 0 * 40
.stage	* bgs_sch009a01_02.png 0 0 st_kei04b03.png 400
;（フェ～ドスピ～ドは20で？）
.message	2200	kei-201_01-0043	丂宨丂	「呼～」
.message	2210			新藤转过身，慢慢的走近我，然后轻轻叹了一口气。
;■睨み
.transition 0 * 40
.stage	* bgs_sch009a01_02.png 0 0 st_kei01b03.png 380
.message	2220	kei-201_01-0045	丂宨丂	「干吗，就那么想决一胜负？　我倒是无所谓」
.message	2230		嫗丂夘	「不不，不是那种野蛮的事情啊」
.message	2240	kei-201_01-0047	丂宨丂	「如果我是完全状态的话，最初的一击就会让你沉入血海……」
.message	2250		嫗丂夘	「你也稍稍有些太危险了吧？」
.message	2260	kei-201_01-0049	丂宨丂	「对你这种变态才这样，平时我可是拥有着温柔心灵的女孩子」
.message	2270		嫗丂夘	「对我也稍微给点温柔好吧」
;■微笑
.transition 0 * 40
;.stage	* bgs_sch009a01_02.png 0 0 st_kei03b01.png 380
.stage	* bgs_sch009a01_02.png 0 0 st_kei03b03.png 380
;（表情は注意して）
.message	2280	kei-201_01-0051	丂宨丂	「当然可以」
.message	2290		嫗丂夘	「哦哦」
.message	2300	kei-201_01-0053	丂宨丂	「起码我会为你喊救护车哦」
.message	2310		嫗丂夘	「诶，我会被狠揍到那种地步吗？」
;■ジト目
.transition 0 * 40
.stage	* bgs_sch009a01_02.png 0 0 st_kei01b07.png 380
;（表情は注意して）
.message	2320	kei-201_01-0055	丂宨丂	「笨蛋」
.transition 0 * 40
.stage	* bgs_sch009a01_02.png 0 0 st_kei04b05.png 400
;（04b04でも？）
;.stage	* bgs_sch009a01_02.png 0 0 st_kei01b01.png 380
;（表情は注意して）
.message	2330	kei-201_01-0057	丂宨丂	「干吗啊，真是的……」
;.transition 0 * 20
.transition 0 * 40
.stage	* bgs_sch009a01_02.png 0 0 st_kei08b01.png 400
;（フェ～ドスピ～ドは40で？）
.message	2340			忽然丢了这么一句牢骚，新藤就啪嗒啪嗒的走开了。
.message	2350		嫗丂夘	「等，等下啊」
.overlay * *
.screen * *

;■通学路
.transition 1 fadeSide.png 20
.overlay	or_kei02a.png * *
.screen	sc_evening01.png sc_evening01.png sc_evening01.png
;.screen	scl_evening01.png scl_evening01.png scl_evening01.png
;☆（sclってなんだ？ここ，思い出せないけど，ちゃんと調べておくこと）
.stage	st_kei11b01-.png 0 0 bg_scl003a01_02_f.png 0 0 bg_scl003a01_02_n.png 0
.effect	WScroll2 * 60 -2


;（景の表情，注意して）
;.transition 1 fadeSide.png 20
;.stage	* bgs_normal006a01_02.png 0 0
.message	2360	kei-201_01-0059	丂宨丂	「到底是干吗？」
.message	2370			完全不看我的脸，新藤一边走着一边慢慢地说。
.message	2380		嫗丂夘	「干吗是指？」
.message	2390	kei-201_01-0061	丂宨丂	「总不会毫无意义的追着人这么久吧？　起码请给我一个理由」
.message	2400		嫗丂夘	「这种事情该在动手打人之前问吧」
;■ジト目
.transition 0 * 40
.stage	st_kei10b04-.png 0 0 bg_scl003a01_02_f.png 0 0 bg_scl003a01_02_n.png 0
;（視線を京介に向けるタイミング，気をつけて）
.message	2410	kei-201_01-0063	丂宨丂	「总之我先打了就是」
.message	2420		嫗丂夘	「原，原来如此吗……」
.message	2430			这个女孩，看起来是动手不怎么过大脑的类型啊。
.message	2440		嫗丂夘	「在回答之前我也有一点想要确认，你认识我吗？」
.transition 0 * 40
.stage	st_kei11b01-.png 0 0 bg_scl003a01_02_f.png 0 0 bg_scl003a01_02_n.png 0
.message	2450	kei-201_01-0065	丂宨丂	「我还是1年级的时候，见过几次面是吧」
.message	2460		嫗丂夘	「嗯，而且这段时间在体育馆里──」
;■あたふた
.transition 0 * 40
.stage	st_kei10b09-.png 0 0 bg_scl003a01_02_f.png 0 0 bg_scl003a01_02_n.png 0
;（表情注意して）
.message	2470	kei-201_01-0067	丂宨丂	「……体，体育馆？　你指什么？」
.message	2480		嫗丂夘	「嗯？　难道不记得了吗？」
.transition 0 * 40
.stage	st_kei11b03-.png 0 0 bg_scl003a01_02_f.png 0 0 bg_scl003a01_02_n.png 0
.message	2490	kei-201_01-0069	丂宨丂	「……我，我什么都不知道」
.message	2500		嫗丂夘	「…………」
.message	2510			明显口气有些奇怪。
.message	2520			看过去，新藤的脸甚至都红到了耳边。
.message	2530		嫗丂夘	「…………」
.message	2540			回想起来，那时在体育馆作的事情可能确实有些微妙的难为情。
.message	2550			但我倒不介意就是。
.message	2560		嫗丂夘	「嘛，这倒无所谓。总之…是认识我对吧」
.transition 0 * 40
.stage	st_kei11b03_close-.png 0 0 bg_scl003a01_02_f.png 0 0 bg_scl003a01_02_n.png 0
;（目を閉じさせていいか注意）
.message	2570	kei-201_01-0071	丂宨丂	「算吧……」
.message	2580	kei-201_01-0073	丂宨丂	「名字记得是……」
.transition 0 * 40
.stage	st_kei10b09-.png 0 0 bg_scl003a01_02_f.png 0 0 bg_scl003a01_02_n.png 0
.message	2590	kei-201_01-0075	丂宨丂	「什么京介同学，没错吧」
.message	2600			原来如此，知道我的后名啊。
.message	2610			因为那家伙一直都是喊我『京介』来着。
.message	2620		嫗丂夘	「姓堤啦。堤京介」
.message	2630		嫗丂夘	「而且，别再用那没大没小的口气了啦。普通交谈的话我会更感恩的」
.transition 0 * 40
.stage	st_kei10b06-.png 0 0 bg_scl003a01_02_f.png 0 0 bg_scl003a01_02_n.png 0
.message	2640	kei-201_01-0077	丂宨丂	「那么，堤。你到底想感什么？」
.message	2650		嫗丂夘	「……啊，哎呀。能在名字上加上“同学”或者“前辈”什么的更好」
.transition 0 * 40
.stage	st_kei10b04-.png 0 0 bg_scl003a01_02_f.png 0 0 bg_scl003a01_02_n.png 0
.message	2660	kei-201_01-0079	丂宨丂	「干吗啊，要求好真多啊」
.message	2670		嫗丂夘	「为了守护我仅存些许的自尊心，请您帮忙」
.transition 0 * 40
.stage	st_kei10b09-.png 0 0 bg_scl003a01_02_f.png 0 0 bg_scl003a01_02_n.png 0
.message	2680	kei-201_01-0081	丂宨丂	「那么，堤前辈。我比较喜欢直接的方式。所以，我只问一句」
.message	2690	kei-201_01-0083	丂宨丂	「你的目的究竟是什么？」
.message	2700			比起说是喜欢直接，还不如说是复杂的会理解不了才对吧。
.message	2710			当然我不会说出口，而只是轻轻一笑。
.message	2720			无需多说，我的愿望也并不是什么难事。
.message	2730			直言的话，就仅仅只有一个愿望。
.message	2740		嫗丂夘	「我呢」
.message	2750		嫗丂夘	「想拍你的电影」
.panel 0
.playBGM *


;■御影チェック
;.effect *
.effect end


.overlay	* * *
.screen	* * *
.transition 0 * 10
.stage	* WHITE.png 0 0
.transition 0 * 10
.stage	* WHITE.png 0 0
.wait 100

.chain 202_01.sc
;■202_01へ。

;.end
