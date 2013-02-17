; ファイル: 115_02.txt
;■宫子好感度（≧4）
;■宫子視点
;■背景：砂浜（冬，１３時
;■　　　　宫村宫子：制服（冬·外出）
.playSE AT_umi.ogg true
;☆（別の海の音にするか？）
.transition 0 * 10
.stage	vista_window.png ev01_183.png 0 0
.panel 3
.message	100	miy-115_02-0003	#傒傗偙	「好冷啊……」
.message	110	miy-115_02-1003		轻轻喝一口从自动贩卖机买来的咖啡。
.message	120	miy-115_02-1005		女孩子不经常喝的，罐装的纯味黑咖啡。
.message	130	miy-115_02-1007		虽然喝黑咖啡是第一次，但却有让自己也有些惊讶的好喝。
.message	140	miy-115_02-1009		到底是什么时候开始，身体开始渴求这种毫无牛奶砂糖的纯咖啡了呢。
.message	150	miy-115_02-1011		真奇怪。
.message	160	miy-115_02-1013		一小口一小口的含下咖啡。
.message	170	miy-115_02-1015		有些苦却热热的液体通过喉咙，暖透我的身体。
.message	180	miy-115_02-0005	#傒傗偙	「真好喝～」
.message	190	miy-115_02-1017		低声说着，把视线投向远处。
.transition 0 * 20
.stage	* ev01_184.png 0 0
.message	200	miy-115_02-1019		眼前有着海，只有海在孤单的宽广着。
.message	210	miy-115_02-1021		不知为何，有地平线的那边一无所有的感觉。
.message	220	miy-115_02-1023		海虽然宽广，却一无所有。只是看着都会感觉寂寞。
.message	230	miy-115_02-1025		咕咚咕咚。
.message	240	miy-115_02-0007	#傒傗偙	「呼～」
.message	250	miy-115_02-1027		我还真是变了呢……。
.message	260	miy-115_02-1029		觉得苦咖啡好喝，和男孩子H，还有……。
.message	270	miy-115_02-1031		伤害那并非讨厌的女孩子。
.transition 0 * 20
.stage	* ev01_185a01.png 0 0
;（b01もありますが，サイズが合わないのでここでは使っていません。調整してもらうこと）
.message	280	miy-115_02-0009	#傒傗偙	「我还真是…讨厌的家伙呢……」
.message	290	miy-115_02-1033		性格越来越差。
.message	300	miy-115_02-1035		为了阻止喜欢的人去交往，什么时候都会作吗？
.message	310	miy-115_02-1037		这样最后就可以幸福吗？
.message	320	miy-115_02-0011	#傒傗偙	「我不明白」
.message	330	miy-115_02-1039		不想要就这样毫不明白。
.message	340	miy-115_02-1041		这样的话，也太半途而废了。
.message	350	miy-115_02-1043		但是，却拿不出勇气。
.message	360	miy-115_02-1045		该用什么脸去见纮君才好呢？
.message	370	miy-115_02-1047		告诉我。
.message	380	miy-115_02-1049		告诉我啊，优子……。
.message	390	miy-115_02-0013	#傒傗偙	「到底想要被告诉什么呢……」
.message	400	miy-115_02-1051		分明我自己的心已经下了决定。
.message	410	miy-115_02-1053		分明我的愿望明了无比。
.transition 0 * 20
.stage	* ev01_185b01.png 222 0
.hscroll	0	-10
.endScroll f
;（座標合わせはしっかりと）
;（フェードスピードはもっと速くして，スクロール移行にスムーズに？）
;☆（↓向井が音声削りました。演出としては良いんやけど，全体としてみたときにおかしくなるので）
.message	420		@丂峢丂	「一个人沉闷什么呢」
.transition 0 * 20
.stage	* ev01_186_mugai_a.png 0 0
;.transition 0 * 20
;.stage	* ev01_186a01.png 0 0
;（コンテ指定より一つ前でこのＣＧを表示させてます。フェードスピードにも注意のこと）
.message	430	miy-115_02-0015	#傒傗偙	「诶？」
.message	440	miy-115_02-1055		反射般地转过身。
.message	450	miy-115_02-1057		还不知道该摆出什么样的表情。
.message	460	miy-115_02-1059		因为，不是毫无办法吗。
.playBGM efBGM031.ogg
.message	470	miy-115_02-1061		我的愿望，只有一个──
.transition 0 * 20
.stage	* ev01_186a01.png 0 0
;（纮表示をここまで引っ張っていいか注意のこと）
.message	480	miy-115_02-1063		那就是能和纮君在一起。
.transition 0 * 10
.stage	* vista_white.png 0 0
.panel 0
.playSE *
.transition 0 * 10
.stage	* WHITE.png 0 0
;（とりあえず白にしてますが，うまく繋げること）
;.transition 0 * 10
;.stage	vista_window.png ev01_186a01.png 0 0


;■フェードアウト
;■纮視点
;■背景：砂浜（冬，１３時
;■　　　　広野纮　　：制服（冬·外出）
;■　　　　宫村宫子：制服（冬·外出）
;（ここから音楽イン，前は効果音のみで）
;.transition 0 * 10
;.stage	* ev01_186_mugai_b.png 0 0
.transition 0 * 10
.stage	* ev01_186a01_mugai_c.png 0 0
;.stage	* WHITE.png 0 0
;☆（纮の足のＣＧから入ってもいいのやも）
;（宫子の髪がインしてるのが変なようなら，切り出しはやめること）
;.transition 0 * 10
;.stage	* ev01_186a01.png 0 0
;（切り替えの演出注意。実際は新規の画像が入るのかもしれませんが，とりあえずこれで保留で）
.panel 1
.message	490		丂峢丂	「一个人沉闷什么呢」
.transition 0 * 20
.stage	* ev01_186a01.png 0 0
.message	500	miy-115_02-0017	傒傗偙	「诶？」
.message	510			刚刚喊出声，宫子便迅速的转过身来。
.message	520			睁开大大的眼睛呆住了。
.message	530	miy-115_02-0019	傒傗偙	「为，为什么？」
.message	540			大概在问我为什么在这里吧。
.message	550		丂峢丂	「女人的第六感……之类的吧」
.message	560			去海边看看的话，说不定会有些好事情发生。
.message	570			雨宫优子这么说，却没想到宫子会在这里。
.message	580			说起来，她到底是什么人啊。
.message	590			本以为只是一个喜欢开玩笑的大姐姐而已，却说出好像看透一切的话……。
.message	600	miy-115_02-0021	傒傗偙	「那个～，说的什么我不明白啦」
.message	610			宫子还是呆呆的。
.message	620		丂峢丂	「不明白也无所谓。那么，走吧」
.message	630			我伸出左手，握住了宫子的手。
.message	640	miy-115_02-0023	傒傗偙	「走，走去哪？」
.message	650		丂峢丂	「约会」
.message	660	miy-115_02-0025	傒傗偙	「约会！？」
.panel 0
.transition 0 * 10
.stage	* WHITE.png 0 0


;■背景：屋上（冬，１４時
.transition 1 fadeSide.png 10
.stage	* bgw_sch007a01_01.png 0 0 st_miyako09a01.png 400
;（冒険的な立ち絵挿んでますが，とりあえず）
;（実際は切り出しインを考えて）
.panel 1
.message	670	miy-115_02-0027	傒傗偙	「呜～，结果是这里吗……」
.message	680		丂峢丂	「你有什么地方想去吗？」
.message	690	miy-115_02-0029	傒傗偙	「虽然倒是没有……」
.message	700			虽然宫子的表情上看不出不满，但却稍微有些阴沉。
.message	710			像迷路的孩子一样，不安的表情。
.message	720			因为不想看到喜欢的人露出这样的表情，所以我…
.transition 0 * 20
.stage	* ev01_187a01_mugai_a.png 0 0
;（ここから187の切り出しで？）
.message	730	miy-115_02-0031	傒傗偙	「哇」
.transition 0 * 20
.stage	* ev01_187a01_mugai_d.png 0 0
.message	740			拉过了宫子的手。
.transition 0 * 20
.stage	* ev01_187a01_mugai_b.png 0 0
.message	750	miy-115_02-0033	傒傗偙	「嗯！？」
.transition 0 * 20
.stage	* ev01_187a01.png 0 0
;（フェードスピードは10で？）
.message	760			不由分辩的，重叠上她的嘴唇。
.transition 0 * 20
.stage	* ev01_187a02.png 0 0
.message	770	miy-115_02-0035	傒傗偙	「嗯～，嗯嗯嗯～～！　呼啊！」
.message	780			在我充分品尝过宫子嘴唇的柔软，并把舌头塞进口中转过几次之后才松开了她。
.transition 0 * 20
.stage	* ev01_187b01.png 0 0
;（コンテ指定より一つ手前でＣＧ配置。フェードスピードは40で？）
.message	790	miy-115_02-0037	傒傗偙	「突，突然之间干吗！？」
.message	800			宫子的手也瞬间松开。
.message	810		丂峢丂	「要是作预告的话，估计你就要逃了」
.message	820	miy-115_02-0039	傒傗偙	「不，不是这回事。为什么要吻我！？」
.message	830			就好像刚才的是初吻一般，宫子红透了脸。
.message	840		丂峢丂	「不可以吻吗？」
.transition 0 * 20
.stage	* ev01_187b02.png 0 0
;（ここ，フェードスピード40で？）
.message	850	miy-115_02-0041	傒傗偙	「虽然不是……不可以。我…和纮君这样下去的话……」
.message	860		丂峢丂	「觉得会结束吗？」
.message	870	miy-115_02-0043	傒傗偙	「…………」
.message	880		丂峢丂	「我…终于明白了啊。究竟该重视什么，究竟该怎样守护自己重要的东西……」
.message	890	miy-115_02-0045	傒傗偙	「重要的东西……」
.transition 0 * 20
.stage	* ev01_188a01.png 0 0
.message	900			宫子轻轻念着，向着屋顶的边缘走去。
.transition 0 * 20
.stage	* ev01_188b01_mugai_a.png 0 0
;（この切り出しを使う場合，しばらく顔を見せなくていいのかは留意のこと）
;.transition 0 * 20
;.stage	* ev01_188b01.png 0 0
.message	910			在那一瞬，以为她在看远方的街市的时候，她又突然的向我转过身来。
;★ここから遠景ＣＧ？
.message	920			原来就有些娇小的宫子的身体，感觉比平时还要小些是我的错觉吗……？
.message	930	miy-115_02-0047	傒傗偙	「纮君，你听说过这样的故事吗？」
.message	940	miy-115_02-0049	傒傗偙	「从前呢，不知是意大利还是哪的国王，作过一个实验」
.message	950		丂峢丂	「实验？」
.message	960	miy-115_02-0051	傒傗偙	「把好多婴儿聚集起来，隔离并且不和其他任何人说话而成长起来的婴儿，到底会说什么样的话呢？　这样的实验」
.message	970		丂峢丂	「虽然不太明白……被那样养育起来的话，肯定不可能会说话的吧」
.message	980			那个有名的狼少女就是不会说话才对。
.transition 0 * 20
.stage	* ev01_188b01.png 0 0
.message	990	miy-115_02-0053	傒傗偙	「只对了一半……哦」
.message	1000		丂峢丂	「一半？」
.message	1010			宫子轻轻的张开嘴唇。
;☆（ここ，189の目閉じで？）
.message	1020	miy-115_02-0055	傒傗偙	「不但一句话都没有出，那些婴儿们还一个不剩的全部死掉了。分明是给他们充足的营养，绝对不让他们生病那样，细心照料养大的」
.message	1030	miy-115_02-0057	傒傗偙	「唯一没给他们的就是话语和爱情。但是，这却是最重要的东西」
.message	1040		丂峢丂	「真是悲伤的故事呢……」
.message	1050			这个该算是什么呢。
.transition 0 * 20
.stage	* ev01_189a01.png 0 0
.message	1060	miy-115_02-0059	傒傗偙	「和我有些相似呢。虽然我也没有，也好好的说着话，但是却没有得到重要的东西」
.message	1070		丂峢丂	「宫子……？」
;★イベントＣＧ
.transition 0 * 20
.stage	* ev01_189a02.png 0 0
;（ここで02表情に変えていいのかは留意のこと）
.message	1080	miy-115_02-0061	傒傗偙	「我的家里从来没有声音」
.message	1090		丂峢丂	「没有声音……？」
.message	1100	miy-115_02-0063	傒傗偙	「我的双亲在我记事的时候就关系不好了，渐渐的不说话……最后好像就连听到对方的话或者足音都会觉得讨厌」
.message	1110	miy-115_02-0065	傒傗偙	「爸爸妈妈在家几乎都没说过话。对我也是一样。只顾想着对方如何讨厌，根本没有心思管女儿的样子」
.message	1120	miy-115_02-0067	傒傗偙	「包括名字──」
.message	1130		丂峢丂	「名字？」
.message	1140	miy-115_02-0068		宫子点了点头。
.message	1150	miy-115_02-0069	傒傗偙	「几乎连喊我名字都没有几次。就像那样，根本都没有说过什么话」
.message	1160	miy-115_02-0071	傒傗偙	「取得再好的成绩，运动拿多少第一名都得不到夸奖……」
.message	1170	miy-115_02-0073	傒傗偙	「爸爸和妈妈喜欢的海鲜料理的作法，我也认真学了。被菜刀搞到满手伤痕，却根本没有人在家吃饭……」
.message	1180			所以宫子她──才会那样充满喜悦的为我作料理吗。
.message	1190			是因为以前…都没有被吃过吗……。
.transition 0 * 20
.stage	* ev01_189a01.png 0 0
;（表情，注意して）
.message	1200	miy-115_02-0075	傒傗偙	「真是有些奇怪呢，分明没必要像爸爸他们一样的，我却也开始习惯屏息诘口的生活」
.message	1210	miy-115_02-0077	傒傗偙	「为什么呢，果然人都是──看着父母的背影长大的吗」
.message	1220			宫子的语气完全感觉不到沉重，就好像再说他人的事情一般。
.message	1230		丂峢丂	「…………」
.message	1240			我对「双亲」完全没有什么概念。
.message	1250			虽然想像不出宫子的家庭到底是什么情况……。
.transition 0 * 20
.stage	* ev01_189a02.png 0 0
.message	1260	miy-115_02-0079	傒傗偙	「最后，大约在六年前离了婚，说实在我还真是舒坦了呢。妈妈离开家到了很远很远的城市去……紧张的空气也消失掉了」

;■御影チェック
.playBGM *

.transition 0 * 20
.stage	* ev01_189b03.png 0 0
;（表情，注意して）
.message	1270	miy-115_02-0081	傒傗偙	「就是如此，我为此而解放了啊」
.transition 0 * 20
.stage	* ev01_189b02.png 0 0
;（表情，注意して）
.message	1280	miy-115_02-0083	傒傗偙	「这样我就可以扔掉那个没有任何声音的家，自由的到想到的地方，充满人声的地方去」
.transition 0 * 20
.stage	* ev01_189a01_mugai_a.png 0 0
.message	1290	miy-115_02-0085	傒傗偙	「期待着总有一天在什么地方……能够找到自己的容身之处」

;■御影チェック
;.playBGM *
;.playBGM efBGM053.ogg
.playBGM efBGM023.ogg

.message	1300		丂峢丂	「真罗嗦啊」
;.playBGM *
;.playBGM BGM042_sample.ogg
.transition 0 * 20
.stage	* ev01_189b01.png 0 0
;（フェードスピードは40で？）
;.transition 0 * 20
;.stage	* ev01_190a.png 0 0
;（挿入位置は注意のこと）
.message	1310	miy-115_02-0087	傒傗偙	「诶？」
.message	1320		丂峢丂	「少一个人啪啦啪啦的说个不停好吧。我说你，果然还是没适应如何和人说话吧」
.message	1330			什么都不懂就让我来教你。
.message	1340			虽然我并不是都明白，但宫子要比我还要白痴。
.message	1350		丂峢丂	「第一，为什么不早早的说出来。不是很寂寞吗，不是很痛苦吗。既然如此说出来不就好吗」
;（ここで宫子の表情189b02に変えさせるか？）
.message	1360		丂峢丂	「不是已经找到自己的容身之处了吗。所以，家的事情孤独的事情，全部已经是过去的事了」
;.playBGM *
;.playBGM BGM042_sample.ogg
.transition 0 * 20
.stage	* ev01_190b01.png 0 0
;（この表情でいいか，注意のこと）
.message	1370	miy-115_02-0089	傒傗偙	「找到容身之处……我不想失去终于找到的容身之处啊！」
.message	1380		丂峢丂	「才没有失去！」
.message	1390	miy-115_02-0091	傒傗偙	「你为什么能这么说！？」
.transition 0 * 20
.stage	* ev01_189b02_mugai_c.png 0 0
;.stage	* ev01_189b02_mugai_b.png 0 0
;.stage	* ev01_189b02.png 0 0
;（この前でこのＣＧに？）
.message	1400	miy-115_02-0093	傒傗偙	「我本以为终于找到了容身之处……找到它，守护它我已经拼尽全力了啊」
.message	1405	miy-115_02-0094	傒傗偙	「为了守护──我甚至连抢跑之类的事都做了！」
;.message	1400	miy-115_02-0093	傒傗偙	「居場所見つけたと思ったの……見つけて，それを守るのに必死なんだよ。守るために──抜け駆けまでした！」
.transition 0 * 20
.stage	* ev01_189b03_mugai_c.png 0 0
;.stage	* ev01_189b03_mugai_b.png 0 0
;.stage	* ev01_189b03.png 0 0
.message	1410	miy-115_02-0095	傒傗偙	「因为小景把她的心情告诉了我──我就抢先一步，我身体给了纮君。我以为这样作的话，纮君就再也不会接受我以外的女孩子……」
.message	1420		丂峢丂	「你还没能计算到这种地步的吧」
.transition 0 * 20
.stage	* ev01_190c_mugai_a.png 0 0
;.stage	* ev01_190c.png 0 0
;（この表情でいいか，注意のこと）
.message	1430	miy-115_02-0097	傒傗偙	「真是最差的人呢…我这样的。只考虑自己的事情。不只对小景，连对纮君也是一样」
.transition 0 * 20
.stage	* ev01_190c01.png 0 0
.message	1440		丂峢丂	「任性不也无所谓吗。比起只考虑他人的事情，而丢失了自己的幸福之类更像人的作法」
.message	1450		丂峢丂	「我的事情我自己会考虑。你也只要如同过去一样就好。那才是你的风格」
.transition 0 * 20
.stage	* ev01_190a01.png 0 0
;☆（a02表情の使いどころ，しっかりと）
;（ここでこのオーバーアクションはＯＫか？）
.message	1460	miy-115_02-0099	傒傗偙	「……哎」
.message	1470			宫子惊讶的屏住了呼吸。
.message	1480			完全不是值得吃惊的事，我所说的都是理所当然的而已。
;★イベントＣＧ（差分か）
.message	1490			我踏近一步──抱住了宫子曼妙的身躯。
.transition 0 * 20
.stage	* ev01_191a01_mugai_a.png 0 0
;.transition 0 * 20
;.stage	* ev01_191a01.png 0 0
;（コンテ指定より一つ後ですが）
.message	1500	miy-115_02-0101	傒傗偙	「啊……」
.transition 0 * 20
.stage	* ev01_191a01.png 0 0
.message	1510		丂峢丂	「听着，宫子。如果有想要的东西的话。有想要守护的东西的话」
.transition 0 * 20
.stage	* ev01_191a02.png 0 0
.message	1520	miy-115_02-0103	傒傗偙	「已经讨厌消失不见。已经讨厌分明我在这里，却被无视的感觉」
.message	1530		丂峢丂	「任性就可以了。我会原谅你的」
.transition 0 * 20
.stage	* ev01_191a03.png 0 0
;（ここで03表情の涙を見せて良いか？）
.message	1540	miy-115_02-0105	傒傗偙	「我想要…我作的料理在热的时候就被吃掉」
.transition 0 * 20
.stage	* ev01_191a04.png 0 0
.message	1550	miy-115_02-0107	傒傗偙	「想要被包容。想要被触碰」
.message	1560		丂峢丂	「我想要和你的羁绊。在你取得好成绩时对你说好厉害。在你做了坏事时对你训斥。你的料理我当然会照单全收」
.message	1570		丂峢丂	「这就是──叫做羁绊的东西」
.transition 0 * 20
.stage	* ev01_191a05.png 0 0
.message	1580	miy-115_02-0109	傒傗偙	「再怎么没面子都无所谓……我想要被紧紧拥抱啊！」
.message	1590		丂峢丂	「你想做的事情，去做就是。除此以外再无其他」
.message	1600	miy-115_02-0111	傒傗偙	「纮君……！」
.transition 0 * 20
;.stage	* ev01_191a05_mugai_c.png 0 0
.stage	* ev01_191a05_mugai_a.png 0 0
;（ここからのＣＧ構築はしっかりと）
.message	1610			现在再说相互会多重视对方也已毫无意义。
.message	1620			我和宫子都一样，刚刚得到那无法让步的东西。
.message	1630			想像不到失去时会如何，也不愿去想像。
.transition 0 * 20
.stage	* ev01_191a05_mugai_c.png 0 0
.message	1640			仅仅，仅仅，想要温柔的包容起宫子。
.message	1650			为了不让任何人伤害到宫子。
.message	1660			为了不让宫子伤害到她自己。
.transition 0 * 20
.stage	* ev01_191a04.png 0 0
;.transition 0 * 20
;.stage	* ev01_191a05_mugai_b.png 0 0
.message	1670			因为能作到这个只有我而已。
.message	1680			无论何时，都希望只有我而已。
;.playBGM *
.panel 0
.transition 0 * 10
.stage	* ev01_105_mugai.png 0 0

;■御影チェック
;.wait 500
.wait 300

.playBGM *
.transition 0 * 10
.stage	* WHITE.png 0 0
;.message	1690			…………
;.message	1700			……

.wait 200

;■背景：通学路（冬，１７時
;.screen sc_evening01.png sc_evening01.png
;.overlay * or_miyako02a.png
;.playBGM efBGM019.ogg
.playBGM efBGM016.ogg
.transition 0 * 10
.stage	* bgw_sky001a01_02.png 0 0
;.transition 0 * 10
;.overlay	or_miyako02a_620p.png * *
;.screen	sc_evening01_620p.png sc_evening01_620p.png sc_evening01_620p.png
;.stage	st_miyako11a03-.png 0 0 bg_scl003a01_02_f.png 0 0 bg_scl003a01_02_n.png 0
;.effect	WScroll2 * 60 -2
;（宫子の目線には注意して。11ポーズで問題ないか？）


;.transition 0 * 10
;.stage	* bgw_normal002a01_02.png 0 0
;（とりあえず夕でアタッチしています）
;.stage	* WHITE.png 0 0
;（通学路の通常背景がまだないので，白で保留にしています）
.panel 1
.message	1710	miy-115_02-0113	傒傗偙	「晩饭作些什么好呢～」

;■御影チェック
;■　さすがに３行はなぁ。
;.transition 1 fadeSide.png 10
;.overlay	or_miyako02a_620p.png * *
;.screen	sc_evening01_620p.png sc_evening01_620p.png sc_evening01_620p.png
;.stage	st_miyako11a03-.png 0 0 bg_scl003a01_02_f.png 0 0 bg_scl003a01_02_n.png 0
;.effect	WScroll2 * 60 -2

.message	1720			摇着牵在一起的手，宫子心情似乎十分愉快。
.message	1730			再怎么说能迅速恢复就是好事情。
.message	1740		丂峢丂	「啊，对了」
;.effect *
.effect end
.overlay	* * *
.screen	* * *


.screen sc_evening01.png sc_evening01.png
.overlay * or_miyako02a.png
.transition 0 * 20
.stage	* bgw_normal002a01_02_stm.png 0 0 stm_miyako07a01.png 410
;☆（中距離の07と08，何ピクセルかズレてるような気がするな，，，。後で修正を）
.message	1750	miy-115_02-0115	傒傗偙	「嗯，怎么？」
.message	1760		丂峢丂	「在还没忘的时候先说下。总之，回到家以后，你全裸决定」
.transition 0 * 40
.stage	* bgw_normal002a01_02_stm.png 0 0 stm_miyako08a01.png 410
.message	1770	miy-115_02-0117	傒傗偙	「全裸！？」
.message	1780			宫子惊讶的睁圆了眼睛。
.transition 0 * 40
.stage	* bgw_normal002a01_02_stm.png 0 0 stm_miyako08a03.png 410
.message	1790	miy-115_02-0119	傒傗偙	「那个，我可不是裸奔族……」
.message	1800		丂峢丂	「女朋友是裸奔族的话绝对不要……」
.transition 0 * 40
.stage	* bgw_normal002a01_02_stm.png 0 0 stm_miyako08a01.png 410
.message	1810	miy-115_02-0121	傒傗偙	「那，那为什么。再怎么说，好歹也给我一个围裙吧……」
.message	1820			看起来好像是误解了什么了啊。
.message	1830		丂峢丂	「虽然那倒也不错……等等不是那回事。那个，这段时间啊，在你睡的时候画了素描」
.transition 0 * 40
.stage	* bgw_normal002a01_02_stm.png 0 0 stm_miyako08a02.png 410
;（表情注意）
.message	1840	miy-115_02-0123	傒傗偙	「完全都没有注意到……」
.message	1850		丂峢丂	「画到一半觉得不太舒服，想要画完而已」
.transition 0 * 40
.stage	* bgw_normal002a01_02_stm.png 0 0 stm_miyako07a04.png 410
.message	1860	miy-115_02-0125	傒傗偙	「裸，裸体吗？」
.message	1870		丂峢丂	「现在也没什么可害羞的吧」
.transition 0 * 40
.stage	* bgw_normal002a01_02_stm.png 0 0 stm_miyako07a05.png 410
.message	1880	miy-115_02-0127	傒傗偙	「会害羞不是理所当然的吗！」
.message	1890			宫子的声音都有些接近悲鸣的感觉了。
.transition 0 * 40
.stage	* bgw_normal002a01_02_stm.png 0 0 stm_miyako03a03.png 400
;（ポーズ注意）
.message	1900	miy-115_02-0129	傒傗偙	「难道是，全部？　没马赛克吗？」
.message	1910		丂峢丂	「那是画好吧。为什么我画素描还要马赛克啊喂」
.message	1920			手绘能画出马赛克吗我说。
.transition 0 * 40
.stage	* bgw_normal002a01_02_stm.png 0 0 stm_miyako03a05.png 400
.message	1930	miy-115_02-0131	傒傗偙	「为什么要画我的画？」

;■御影チェック
;.message	1940		丂峢丂	「描きたかったから」
.message	1940		丂峢丂	「因为我想要画」

.transition 0 * 40
;.stage	* bgw_normal002a01_02_stm.png 0 0 stm_miyako02a04.png 350
.stage	* bgw_normal002a01_02_stm.png 0 0 stm_miyako02a04.png 340
;（02a06との使い分け，注意）
.message	1950	miy-115_02-0133	傒傗偙	「……呜」
.message	1960			宫子顿时没了话说。
.message	1970		丂峢丂	「而且，这次还不得不画一个单回短篇……想要你来作主人公的模型」
.transition 0 * 40
;.stage	* bgw_normal002a01_02_stm.png 0 0 stm_miyako02a03.png 350
.stage	* bgw_normal002a01_02_stm.png 0 0 stm_miyako02a03.png 340
.message	1980	miy-115_02-0135	傒傗偙	「……真狡猾啊～。这样说的话我不就无法拒绝了吗……」
.message	1990		丂峢丂	「嘛不会被人看到的啦」
.transition 0 * 40
.stage	* bgw_normal002a01_02_stm.png 0 0 stm_miyako03a04.png 400
;（ポーズと表情，注意）
.message	2000	miy-115_02-0137	傒傗偙	「理所当然的啊！　第一，做漫画的模型的话有必要裸体吗？」
.message	2010		丂峢丂	「没啊」
.transition 0 * 40
.stage	* bgw_normal002a01_02_stm.png 0 0 stm_miyako03a03.png 400
.message	2020	miy-115_02-0139	傒傗偙	「那么清爽的回答……」
.message	2030		丂峢丂	「让我多画些各种各样把。只做模型的话会无聊的啦」
.transition 0 * 40
.stage	* bgw_normal002a01_02_stm.png 0 0 stm_miyako05a06.png 400
;（05a03との使い分け，注意）
.message	2040	miy-115_02-0141	傒傗偙	「……我知道了啦」
.message	2050			宫子勉强点了点头。
.transition 0 * 40
.stage	* bgw_normal002a01_02_stm.png 0 0 stm_miyako05a03.png 400
.message	2060	miy-115_02-0143	傒傗偙	「但是……」
.message	2070		丂峢丂	「如果真的不想的话，也可以拒绝」
.transition 0 * 40
.stage	* bgw_normal002a01_02_stm.png 0 0 stm_miyako04a03.png 400
;（表情注意。微妙に笑み入ってても良い？）
.message	2080	miy-115_02-0145	傒傗偙	「不是这回事。画单回之类没事吗？　平常的连载暂时停掉吗？」
.message	2090		丂峢丂	「不，和往常一样啊。只是工作量增加而已」
.message	2100	miy-115_02-0147	傒傗偙	「纮君的右手……」
.message	2110			宫子握起我的右手，温柔的抚摸着。
.message	2120			喂喂，别在大街上做这种事好吧。
.message	2130		丂峢丂	「不必担心的啦」
.transition 0 * 40
.stage	* bgw_normal002a01_02_stm.png 0 0 stm_miyako00a03.png 350
;.stage	* bgw_normal002a01_02.png 0 0 st_miyako01a03.png 400
.message	2140	miy-115_02-0149	傒傗偙	「那么，我有一个条件」
.message	2150		丂峢丂	「怎么」
.transition 0 * 40
.stage	* bgw_normal002a01_02_stm.png 0 0 stm_miyako00a07.png 350
;.stage	* bgw_normal002a01_02.png 0 0 st_miyako01a07.png 400
;（表情注意。怒ってる表情はＮＧ？01a03で？）
.message	2160	miy-115_02-0151	傒傗偙	「那短篇，在画好的时候马上给我看哦」
.message	2170		丂峢丂	「不用你说我也会这么做」
.transition 0 * 40
.stage	* bgw_normal002a01_02_stm.png 0 0 stm_miyako02a01.png 350
.message	2180	miy-115_02-0153	傒傗偙	「谢谢」
.message	2190			宫子的笑颜，让我从心底感到一阵温柔。
.message	2200			为了不失去这个笑颜我也要…
.message	2210		丂峢丂	「宫子，我决定了」
.transition 0 * 40
.stage	* bgw_normal002a01_02_stm.png 0 0 stm_miyako04a02.png 400
.message	2220	miy-115_02-0155	傒傗偙	「什么？」
.message	2230		丂峢丂	「回到家再告诉你。有关于我和你的安身之处……要用好长好长的时间…」
.transition 0 * 40
.stage	* bgw_normal002a01_02_stm.png 0 0 stm_miyako05a02.png 400
;（目閉じ笑顔，，，でなくても良いか？）
.message	2240	miy-115_02-0157	傒傗偙	「……嗯」
.message	2250			虽然重要的东西不只一个，但却不得不决定她们的顺序。
.message	2260			那烦恼缠身的时间马上就要过去了……。
.message	2270			因为，宫子所找到的东西。
.message	2280			以及我所得到的东西。
.message	2290			不得不去守护。
.panel 0
.overlay * *
.screen * *
.playBGM *
.transition 0 * 10
.stage	* WHITE.png 0 0
.transition 0 * 10
.stage	* WHITE.png 0 0
.wait 100

.chain 116_01.sc
;■116_01へ。

;.end
