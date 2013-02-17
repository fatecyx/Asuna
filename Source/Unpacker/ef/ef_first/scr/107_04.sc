; ファイル: 107_04.txt
;■背景：纮自室（冬，１８時
;■　　　　广野纮：私服（冬）
.playBGM efBGM022_2.ogg
.transition 1 fadeSide.png 10
.stage	* ev01_033a01.png 0 0
;（とりあえずこのＣＧでアタッチしてます。再利用ということで）
.panel 1
.message	100			先找到整体的平衡感。
.message	110			这时的描线要尽量的细微，细到手上的肤脂一抹就能让之消失的程度。
.message	120			然后画出脸的轮廓，然后按照顺序画上鼻子，嘴巴，眉毛，眼睛的部分。
.message	130			我曾经十分喜欢人物的样子一点点浮现出来的这个过程。
.message	140			然而，何时开始失去了这份高扬感呢。
.message	150			考虑对话的时候也就算了，打草稿和描线变成单纯的「工作」已经感觉有很长一段时间了。
.message	160			分明以前画漫画的整个过程都是愉快的。
.message	170			带着这种冷淡的心情动手究竟是何时开始的呢？
.message	180			各种各样的事情累加起来让铅笔越来越重。
.message	190		丂峢丂	「……不想了啦」
.message	200			再慢吞吞的话某个魔鬼不会一声不吭的。
.message	210			又加了一把力气到拿笔的手上。
.transition 0 * 20
.stage	* ev01_087a01.png 0 0
;（挿入位置，注意。ペンが置かれていることにも注意。このペンとは別のペンを纮は握っているという逃げ？）
.message	220			而且，也差不多了吧──
.playSE hiro_keitai_2.ogg true 0 *
.transition 0 * 40
.stage	* ev01_087a02.png 0 0
;☆（ここ，087画像のどこかピカピカ光らせましょうよ，ええ）
.message	230			哔哩哩哩哩哩，哔哩哩哩哩哩。
.transition 0 * 20
.stage	* ev01_033b01.png 0 0
;（フェ～ドスピ～ドは40で？）
.message	240		丂峢丂	「看吧果然来了」
.transition 0 * 20
.stage	* ev01_087b01_anime_c.png 0 0
;.stage	* ev01_087b01.png 0 0
;（033画像は挿まないという演出もありなのかもしれませんが）
.message	250			也不是总是有业务联络，但大村先生的电话总不会少。
.message	260			这样每天都会打来的电话，再怎么说都会有压力。
.message	270			所以才要赶在截稿之前交稿啊。
.playSE * f * 0
.playSE pi.ogg f 0 *
.transition 0 * 20
.stage	* ev01_033c01.png 0 0
;（フェ～ドスピ～ドは40で？）
.message	280		丂峢丂	「喂，您好──」
.message	290	miy-107_04-0003	@傒傗偙	『您好……』
.message	300		丂峢丂	「嗯！？」
.message	310			和预料的正好相反，听到的完全不是大叔的粗糙的声音。
.transition 0 * 20
.stage	* ev01_087b01_mugai_a.png 0 0
;☆（「着信」の文字，変えてもらうか？ちょっと留意）
.message	320			啪的把手机从耳边拿开，看向液晶画面。
.message	330			来电显示上清楚表示出「公共电话」几个字。
.transition 0 * 20
.stage	* ev01_033c01.png 0 0
.message	340		丂峢丂	「诶，谁？」
.message	350	miy-107_04-0005	傒傗偙	『是我』
.message	360		丂峢丂	「什么啊，宫子啊」
.message	370			难得有人从公共电话打进来，我还以为谁呢。
;.transition 1 fadeSide.png 20
.playSE miyako_station_people.ogg f 0 *
.transition 1 fadeGray.png 20
.stage	* ev01_088a01.png 0 0
;.stage	* ev01_088.png 0 0
;（グレイフェ～ドでもいいのかもしれません）
.message	380	miy-107_04-0007	傒傗偙	「嗯。广野君，现在在作什么呢？」
;.transition 1 fadeSide.png 20
.playSE *
.transition 1 fadeGray.png 20
.stage	* ev01_033c01.png 0 0
;（切り替えは注意）
.message	390		丂峢丂	「作什么，自然是在工作」
.message	400	miy-107_04-0009	傒傗偙	『稍微有些事情想要拜托你。能听我说吗？』
.message	410		丂峢丂	『怎么了，听起来没什么精神呢。怎么了吗」
.message	420	miy-107_04-0011	傒傗偙	『……』
.message	430			从电话那边，传来轻轻的叹气声。
.message	440	miy-107_04-0013	傒傗偙	『那个，我刚才去附近的小区买东西来着』


; 好感度判定
.if favMiyako_a > 0 miyako_a
.if favMiyako_a <= 0 miyako_b


;■107_02を通過してる場合。
.label miyako_a
.message	450		丂峢丂	「买东西？　买东西怎么了吗？」
.message	460			不会是又被抢劫，回不去了吧。
.goto miyako_c


;■107_03を通過してる場合。
.label miyako_b
.message	470		丂峢丂	「啊啊」
.message	480			说起来，在屋顶说过要去买东西来着。
.goto miyako_c


;■以下，変更無し。
.label miyako_c
.message	490	miy-107_04-0015	傒傗偙	『然后呢，在回去的路人……那个，』
.message	500			不知为何突然不说话了。
.message	510		丂峢丂	「有话想说就说啊。我会听下去的啦」
.message	520			啊啊，为什么我要用这么温柔的语气啊。
.message	530			在景她们面前分明老是一幅严肃的样子。
.message	540	miy-107_04-0017	傒傗偙	『在电车里』
.message	550		丂峢丂	「嗯」
.message	560	miy-107_04-0019	傒傗偙	『被人骚扰了』
.message	570		丂峢丂	「…………」
.message	580			怎么，原来如此吗──总不能这么说吧。
.message	590		丂峢丂	「嘛，怎么说呢，还真糟糕啊」
.message	600	miy-107_04-0021	傒傗偙	『特别让人恶心。没有我的许可就随便碰我……』
.message	610		丂峢丂	「抓住犯人了吗？」
.message	620	miy-107_04-0023	傒傗偙	『怎么可能做的到吗。男人虽然应该不会明白，但真的好可怕……』
.message	630		丂峢丂	「虽说如此……那，想我做些什么好呢」
.playSE miyako_station_people.ogg f 0 *
.transition 1 fadeSide.png 20
.stage	* ev01_089.png 0 0
.message	640	miy-107_04-0025	傒傗偙	「来接我。现在，在音羽的车站」
.playSE *
.transition 1 fadeSide.png 20
.stage	* ev01_033c01.png 0 0
;（ここから頻繁に切り替えて，宫子の不安定な感情を表現していくのもいいかもしれません）
.message	650		丂峢丂	「……为什么要这样？」
.message	660			被人骚扰和去接她是怎么联系起来的。
.playSE miyako_station_people.ogg f 0 *
.transition 1 fadeSide.png 20
.stage	* ev01_089_mugai_a.png 0 0
.message	670	miy-107_04-0027	傒傗偙	「好害怕」
.playSE *
.transition 1 fadeSide.png 20
.stage	* ev01_033c01.png 0 0
.message	680		丂峢丂	「哈？」
.message	690	miy-107_04-0029	傒傗偙	『一个人回家好害怕！　所以来接我啊！』
.message	700			该说是任性呢……还是什么呢。
.message	710		丂峢丂	「等下等下，为什么要来拜托我」
.message	720			又不是不知道我很忙。
.message	730		丂峢丂	「仅仅是去接你这种小事，不是我也无所──」
.message	740	miy-107_04-0031	傒傗偙	『为什么？』
.message	750		丂峢丂	「嗯？」
.message	760	miy-107_04-0033	傒傗偙	『我分明在求广野君，为什么会说出这样的话？』
.message	770		丂峢丂	「…………」
.select 去接宫子:label1 工作优先:label2
.label label1
.set favMiyako = favMiyako + 1
.panel 0
.playBGM *
.transition 0 * 10
.stage	* WHITE.png 0 0
.chain 107_05.sc
.label label2
.chain 107_06.sc
;◆選択肢
;■·宫子を迎えにいく
;→107_05へ　 宫子+1
;■·仕事を優先する
;→107_06へ

;.end
