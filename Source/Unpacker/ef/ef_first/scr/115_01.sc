; ファイル: 115_01.txt
;■＜１章：１５日目＞
;■背景：纮自室（冬，８時
;■　　　　广野纮　　：制服（冬）


;.playBGM efBGM022_2.ogg
.transition 0 * 10
.stage	* ev01_177.png 0 0
;■御影
;■　画像表示後に指定をおいてみる。
.playBGM efBGM022_2.ogg
;☆（こっからイベントＣＧ，スタ～トさせてます。さらにこのＣＧ，どっか点滅させたい，もしくは点灯）
.panel 1
.message	100			把久濑修一的专辑放进CD机，开始随机播放。
;.playBGM efBGM022_2.ogg
;☆（ＣＧはコンポ？）
.message	110		丂峢丂	「…………」
;■曲を変更。
;.playBGM efBGM022_2.ogg
.message	120			澄清无比，毫无淤塞感的旋律静静的回响起来。
.message	130			这是久濑修一自己的原创曲，也是我喜欢的曲子之一……。
.message	140			但这首曲子是以「告別」为主题创作的，听起来稍稍有些心情沉重。
.message	150			不是适合早上听的曲子啊。
.message	160			真是，不懂得察言观色的CD机啊。
.message	170			我苦笑着，把手伸进制服的袖子。
.message	180			作的时候还有些余裕的这件制服，在两年的学园生活中已经变的有些紧了。
.message	190			仅仅两年。
.message	200			在仅仅如此的时间里我究竟变了多少，又得到了什么呢。
.panel 0


;■御影チェック
;■　久瀬の曲を止めないで，优子との会話の場面にいきます。
;■　纮が学園への別れを決意しているのが１つ（だから制服の丈を気にしたりしてる）。
;■　母親との別れの示唆が１つ。
;■　また，この久瀬の曲が优子にも繋がっているので。
;.playBGM *

.transition 0 * 10
.stage	* WHITE.png 0 0


;■背景：教会内（祭壇）（冬，９時
;■　　　　广野纮　：制服（冬·外出）
;■　　　　雨宮优子：私服（冬·外出）
;.playSE kyoukai_door.ogg f 0 *
;（この効果音は切ることも考えて）
.transition 1 fadeSide.png 10
.stage	* bgw_normal011a01_00.png 0 0
;☆（ここのスクロ～ルにスクリ～ンをかけるのか？については保留）
.vscroll	600	10
.endScroll f
.playSE kyoukai_door.ogg f 0 *
;（とりあえず教会·外観·朝のスクロ～ルから入ってます。プロロ～グラストの逆スクロ～ルで）
;.stage	* WHITE.png 0 0
;（外観指定ですが，イベントＣＧの指定で中にしてあります）
;（通常背景教会内部朝がないので，白で保留。実際は优子のモブも足したものを）
.panel 1
.message	210			虽然有些预感，但还是有些抵触。
.message	220		丂峢丂	「哟」
;.playBGM *

;■御影チェック
;■　コメントアウト
;.playBGM efBGM017_2.ogg

.transition 0 * 20
.stage	* ev01_178.png 0 250
;（0座標にしてますが，位置は後で調整のこと）
;（250に設定しました）
.message	230	yuk-115_01-0003	桪丂巕	「啊啦，早安呢」
.message	240			雨宮优子浮起淡淡的笑颜，轻轻低了下头。
.message	250	yuk-115_01-0005	桪丂巕	「今天也是精神满满的逃课吗？」
.message	260		丂峢丂	「真失礼啊。今天我是有事才来的」
.transition 0 * 20
.stage	* ev01_179a01.png 0 0
.message	270			我扬起手中抱着的花束给她看。
.message	280	yuk-115_01-0007	桪丂巕	「我们还没有见过几次面呢……突然就向我求婚的话会困扰的啊」
.transition 0 * 40
.stage	* ev01_179a03.png 0 0
.message	290		丂峢丂	「谁向你求婚了！」
.message	300	yuk-115_01-0009	桪丂巕	「诶，那花束不是送给我的吗？」
.transition 0 * 40
.stage	* ev01_179a04.png 0 0
;（ここでa04表情に変えてもいいか？03と04の交互使用はしっかりと）
.message	310		丂峢丂	「给仅仅认识而已的女人送花的话，不就跟危险人物一样了吗」
.transition 0 * 20
.stage	* ev01_180a02.png 0 0
.message	320	yuk-115_01-0011	桪丂巕	「没那回事哦，可爱的后辈的礼物的话，我自然会笑纳的哦」
.message	330		丂峢丂	「我怎么可能向根本都不尊敬的前辈送什么礼物嘛」
.message	340			就算是尊敬，也不会送花束这种有深刻意义的东西吧。
.transition 0 * 40
.stage	* ev01_180a05.png 0 0
.message	350	yuk-115_01-0013	桪丂巕	「啊啦啦，真是遗憾呢……」
.message	360		丂峢丂	「是该遗憾的事情吗」
.transition 0 * 20
.stage	* ev01_179a04.png 0 0
;☆（ここ，纮のノ～マル表情を用意してもらう？）
.message	370	yuk-115_01-0015	桪丂巕	「我最遗憾的是」
.message	380			雨宮优子的表情稍稍有些绷紧。
.message	390	yuk-115_01-0017	桪丂巕	「被说是『仅仅认识而已』，而有些伤心呢」
.message	400	yuk-115_01-0019	桪丂巕	「我分明很喜欢广野先生的呢」
.message	410		丂峢丂	「…………」
.message	420			又说些莫名其妙的话。
.message	430			正这么想着的时候──
.transition 0 * 20
.stage	* ev01_180a02.png 0 0
.message	440	yuk-115_01-0021	桪丂巕	「啊，脸是不是有些微妙的红了呢？」
.transition 0 * 20
.stage	* ev01_179a03.png 0 0
.message	450		丂峢丂	「怎么可能嘛。白痴啊」
.message	460			虽然不明白为什么，却有些奇怪的害羞感。
.message	470			和宫子或者景不一样，雨宮优子的话似乎有种能触碰到某些平常难以触及之处的感觉……。
.message	480			等等，想什么呢我。
.transition 0 * 40
.stage	* ev01_179a04.png 0 0
.message	490		丂峢丂	「那种事情怎样都无所谓了」
.message	500	yuk-115_01-0023	桪丂巕	「说起来，广野先生。认真地说，到底为什么事情而来这的呢？」
.message	510		丂峢丂	「扫墓啊」
.message	520			今天我的目的地，其实并不是这儿，而是教会里侧的墓场。
.transition 0 * 20
.stage	* ev01_180a02.png 0 0
;☆（ここ，最初と何か関連があるのか，調べておくこと）
.message	530	yuk-115_01-0025	桪丂巕	「是谁的……墓我可以问下吗？」
.message	540		丂峢丂	「那种有所介意的说话方式可不像你的作风呢。分明一直都是想说什么就说什么的」
.transition 0 * 40
.stage	* ev01_180a03.png 0 0
.message	550	yuk-115_01-0027	桪丂巕	「到底是扫谁的墓速速交代。慢吞吞的话我捅你哦」
.transition 0 * 40
.stage	* ev01_179a03.png 0 0
.message	560		丂峢丂	「不介意的过分了吧！」
.message	570			果然是在和我玩的吧。
.message	580			但是，为什么我不能认真的生气起来呢。
.message	590			……该说是我太和善了吗。
.transition 0 * 20
.stage	* ev01_180a04.png 0 0
.message	600	yuk-115_01-0029	桪丂巕	「不不，如果真的不想说的话就算了吧」
.message	610			我轻轻的摇了摇头。
;.transition 0 * 40
;.stage	* ev01_179a04.png 0 0
;（この手前でこの表情を？）
.message	620		丂峢丂	「母亲的」
.message	630		丂峢丂	「虽然她在我小时候就去世了，以至于都不怎么记得长相」
.transition 0 * 40
.stage	* ev01_180a01.png 0 0
.message	640	yuk-115_01-0031	桪丂巕	「……是这样吗」
.message	650			雨宮优子的声音中，并没有多余的同情。
.message	660			不做累赘的同情其实也有时也会让人舒心。
.message	670			虽然有些奇怪，但雨宮优子却好像懂得这一点。
.transition 0 * 20
.stage	* ev01_179a04.png 0 0
.message	680		丂峢丂	「今天是她的忌日。嘛，虽然我不是每年都会扫墓的大孝子，今年是替父亲来的而已」
.message	690	yuk-115_01-0033	桪丂巕	「代替父亲？」
.message	700		丂峢丂	「父亲他，现在身体不太好啦。嘛，现在还在监禁在医院里，就把我派来了」
.message	710			老姐已经回去海那边了自然没有办法。
.message	720	yuk-115_01-0035	桪丂巕	「你的家庭环境也足够复杂了饿」
.message	730		丂峢丂	「是很少见的家庭倒是没错……」
.message	740			再怎么说一家人全部都是画画的啊。
.message	750	yuk-115_01-0037	桪丂巕	「但是呢，广野先生」
;.transition 0 * 20
;.stage	* ev01_180a03.png 0 0
.message	760			雨宮优子又浮起认真的表情。
.transition 0 * 20
.stage	* ev01_180a03.png 0 0
.message	770	yuk-115_01-0039	桪丂巕	「就算广野先生不记得，也是生育下你的人啊。在忌日来扫墓的话才不会受到天罚呢……」
.message	780			雨宮她的话意外的认真，话中有些引人动摇的东西在的感觉──
.message	790			我用手指拂了一下鼻子说道。
.transition 0 * 20
.stage	* ev01_179a02.png 0 0
;☆（a02の使いどころがわからないんで，とりあえずここに放り込んでます。目閉じをつくるなど，いろいろ工夫をこれから先）
.message	800		丂峢丂	「偶尔啦，说起来我也是为了『我也是有母亲的啊』这样的回忆而来的而已」
.message	810		丂峢丂	「我不喜欢是忌日才来什么的。感觉像义务似了」
.message	820	yuk-115_01-0041	桪丂巕	「原来如此，真像你的考虑方式呢」
.transition 0 * 40
.stage	* ev01_179a03.png 0 0
.message	830		丂峢丂	「又在玩我了吧」
.message	840	yuk-115_01-0043	桪丂巕	「不不，怎么敢呢」
.message	850			雨宮优子仍然一副认真的表情，轻轻的摇了摇头表示否定。


;■御影チェック
;■　コメントアウト
;.playBGM *
;.playBGM efBGM022.ogg


.message	860	yuk-115_01-0045	桪丂巕	「是啊，说不定这样也不错呢。为了不忘记……那已经消失的人」
.transition 0 * 20
.stage	* ev01_180b01.png 0 0
;（この切り替えは再考のこと。あんまよくない？）

;■御影チェック
;■　確かに空はないわなぁ。
;.message	870			なにかに思いを馳せるように，雨宮优子は空を見上げた。
;.message	880			青く澄み渡った空に，どんな思い出が映し出されているのか……。
.message	870			好像回忆起什么一样，雨宮优子她仰头看向虚空。
.message	880			那视线的先端，究竟映出了什么样的回忆呢……。

.message	890			说不定，雨宮优子她也……。
.message	900	yuk-115_01-0047	桪丂巕	「我也有过呢。重要的人。分明是不可失去的，却失去了的人……」
.message	910			如果真的比我年纪大的话，雨宮优子的人生也自然是经历过各种各样的事情的吧。
.message	920			一直都把别人看作小笨蛋一样的生活的态度，说不定正是为了那「各种各样」的事情不被他人知道而戴上的假面。
.message	930		丂峢丂	「那个」
.transition 0 * 20
.stage	* ev01_180a02.png 0 0
;☆（优子の表情は注意して。180aシリ～ズの使いどころもきちんと）
.message	940	yuk-115_01-0049	桪丂巕	「嗯」
.transition 0 * 20
.stage	* ev01_180c01.png 0 0
;.stage	* ev01_180a01.png 0 0
;（优子の手にはまだ渡ってはいませんが，，，）
.message	950			对着转过头来的雨宮优子，我取出了几支花递给了她。
.transition 0 * 20
.stage	* ev01_181a01.png 0 0
;.stage	* ev01_180c.png 0 0
;（この切り替えでいいか，注意のこと）
.message	960	yuk-115_01-0051	桪丂巕	「这是？」
.message	970		丂峢丂	「虽然像顺便似的有些不妥的感觉，把这个给你重要的人吧」
.transition 0 * 20
.stage	* ev01_181b01.png 0 0
.message	980	yuk-115_01-0053	桪丂巕	「……不像你的作风呢」
.message	990			少管我。
.message	1000	yuk-115_01-0055	桪丂巕	「还是……对我都开始温柔起来，有了心境的変化吗？」
.message	1010		丂峢丂	「就算是我也会改变的啊。因为我也是活生生的人啊」
.transition 0 * 20
.stage	* ev01_181c01.png 0 0
;（181画像の使い方はまた再考のこと。次の画像へは，180c画像から繋げる？）
.message	1020	yuk-115_01-0057	桪丂巕	「是啊，因为是活着的人啊……」
.transition 0 * 20
.stage	* ev01_180d01.png 0 0
.message	1030			雨宮优子微笑起来，把手中的花凑到了自己的脸前。
.transition 0 * 20
.stage	* ev01_180d02.png 0 0
;（フェ～ドスピ～ド，注意して）
.message	1040	yuk-115_01-0059	桪丂巕	「好香的味道……」
.transition 0 * 20
.stage	* ev01_180c02.png 0 0
;（ここでd02表情を使う？）
;.stage	* ev01_180c01.png 0 0
;（c差分，こっちに挿みました）
.message	1050	yuk-115_01-0061	桪丂巕	「那个人一定…会高兴的收下的吧……」
.message	1060			雨宮优子失去的到底是谁。
.message	1070			但这个…是不能问的事情。
.message	1080			如果问的话，雨宮优子的微笑一定会消失的吧。
.message	1090			所以，我什么都没有问。
.message	1100	yuk-115_01-0063	桪丂巕	「广野先生」
.transition 0 * 20
.stage	* ev01_182a01.png 0 0
;☆（差分の構築はしっかりと）
;（切り替えは注意。つ～か，ここの一連のシ～ンは難しいな，，，）
.message	1110			雨宮优子静静的向我踏近一步。
;★イベントＣＧ？
.message	1120			虽然这么近看是第一次……但果然雨宮的脸，有着超凡脱俗的美丽。
.transition 0 * 20
.stage	* ev01_182a02.png 0 0
.message	1130	yuk-115_01-0065	桪丂巕	「作为花朵的还礼，让姐姐说一句话给你听」
.message	1140			薄薄的嘴唇轻轻道出话来。
.transition 0 * 20
.stage	* ev01_182a01.png 0 0
.message	1150	yuk-115_01-0067	桪丂巕	「就算再怎么重视她，人总有一天会消失不见。再怎么希望，也不会得到永远」
.message	1160	yuk-115_01-0069	桪丂巕	「和重要的人一起的时候愉快无比，即使有痛苦的事情也十分充实……」
.transition 0 * 20
.stage	* ev01_182a03.png 0 0
.message	1170	yuk-115_01-0071	桪丂巕	「然后，就会以无法相信的速度，迅速的消失而去」
.transition 0 * 20
.stage	* ev01_181c01_mugai_a.png 0 0
.message	1180	yuk-115_01-0073	桪丂巕	「为了总会来临的那个离别时不会后悔……请重视她，认真的重视她吧」
.message	1190			雨宮优子的话，好象纯净无比的祈祷一般，重重的在心中回响。
.transition 0 * 20
.stage	* ev01_178.png 0 250
;.stage	* ev01_178_mugai_a.png 0 0
;.stage	* ev01_182a01_mugai_b.png 0 0
.panel 0
;.transition 0 * 20
;.stage	* ev01_182_mugai_a.png 0 0
;☆（ここでa02とa03を使う？使いどころ，よくよく考察して）
;（切り出しする場合は，右寄りか左寄りで？）
;（切り出しが変なようなら，前のＣＧままで）

;■御影チェック
;.message	1200	yuk-115_01-0075	#桪丂巕	「广野さん……あなたにそれができますか？」\v\a
;.wait 250
.message	1200	yuk-115_01-0075	#桪丂巕	「广野先生……这个，你能作到吗？」

.if favMiyako > 1 miyakotrue
.if favMiyako <= 1 miyakobad

.label miyakotrue
.panel 0
.playBGM *
.transition 0 * 10
.stage	* WHITE.png 0 0
.chain 115_02.sc
.end

.label miyakobad
.panel 0
.playBGM *
.transition 0 * 10
.stage	* WHITE.png 0 0
.chain 115_03.sc
.end

;■好感度チェック
;■みやこ好感度（≧4）
;→115_02へ
;■みやこ好感度（＜4）
;→115_03へ

;.end
