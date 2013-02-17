; ファイル: 113_03.txt
;■再び時間戻って。
;■背景：纮自室（冬，１５時
;■　　　　广野纮　　：私服（冬）
;■　　　　宫村宫子：私服（冬）
.transition 0 * 10
;.stage	* ev01_157a04.png 0 0
;（コンテ指定によりこのＣＧを入れてますが，ちょっと変か？）
.stage	past_window.png ev01_158a01_past.png 0 0
;.stage	* bgc_home001a01_01.png 0 0
;（通常背景を挿んでますが，実際はイベントＣＧを挿んでください）
.panel 1
.message	100			对，我不想和宫子分开。
.transition 0 * 10
.stage	* ev01_158a01.png 0 0
.message	110			只有这点我确信不移。
.transition 0 * 20
.stage	* ev01_158d01.png 0 0
.message	120			把掉下的书和素描簿全部放回去之后，重新进入被褥里。
.message	130			宫子还是老样子睡的很熟。
.message	140			轻轻碰了两下她柔软的脸颊。
.message	150	miy-113_03-0003	傒傗偙	「嗯嗯～」
.message	160			宫子一低低声哼着一边有些郁闷的样子打掉我的手指。
.message	170			果然不会起来吧。
.message	180			嘛，无所谓了。
.transition 0 * 20
.stage	* ev01_158e01.png 0 0
;（ここでこの差分に移行で問題はない？）
.message	190			抱过宫子的身体，收束起来。
.message	200		丂峢丂	「这样也不坏呢……」
.message	210			嗯，大概这个就叫做──
.playSE hiro_keitai_2.ogg true 0 *
.transition 0 * 20
.stage	* ev01_158f01.png 0 0
;（フェ～ドスピ～ドは40で？）
.message	220			哔哩哩哩哩哩，哔哩哩哩哩哩。
.message	230		丂峢丂	「啊」
.message	240			糟了，忘记关掉手机的电源了。
.message	250			但是，既然打过来就没有办法。
;（ここの演出は注意。背景に宫子が描かれていることから，華麗にスル～はできませんので。時間に注意して，切り出しするなら切り出しを）
.message	260			迅速的下了床，拿起电话。
.playSE * f * 0
.playSE pi.ogg f 0 *
.transition 0 * 20
.stage	* ev01_161a01.png 0 0
.message	270		丂峢丂	「喂，请问您找谁」
.transition 0 * 40
.stage	* ev01_161d01.png 0 0
.message	280	miy-113_03-0005	傒傗偙	「啊……？」
.message	290			接电话的时候向床上看一眼，宫子稍微睁开了一些眼睛。
.transition 0 * 40
.stage	* ev01_161d02.png 0 0
.message	300	miy-113_03-0007	傒傗偙	「呜～」
.message	310			但是马上又睡着了。
;.transition 0 * 40
.transition 0 * 20
.stage	* ev01_161a01.png 0 0
;（ピント，ここで京介に戻していいのか注意のこと）
.message	320			奇怪的女人啊……。
.message	330	kyo-113_03-0009	嫗丂夘	『喂，广野』
.message	340		丂峢丂	「谁啊，京介啊。发部团活动的牢骚的话我可不听哦」
.message	350	kyo-113_03-0013	嫗丂夘	『才不是这回事！」
.message	360			奇怪，少见的认真的语气。
.message	370	kyo-113_03-0015	嫗丂夘	『那个，我今天，受篮球部的拜托去拍摄练习比赛』
.message	380		丂峢丂	「没有拍到投球瞬间之类的？」
.message	390	kyo-113_03-0019	嫗丂夘	『这边也发生很多事啊。那些小事都无所谓了，闭嘴给我听着』
.message	400		丂峢丂	「干吗啊，发生什么了吗」
.message	410			大概是景的事情吧，难道输掉了吗……？
.playBGM *
.message	420	kyo-113_03-0023	嫗丂夘	『新藤同学，在比赛的途中突然倒下被抬走了啊』
.message	430		丂峢丂	「……什么？」
.message	440			一瞬间，我完全没有明白他到底说了什么。
.message	450	kyo-113_03-0027	嫗丂夘	『说了，新藤同学倒下了』
.transition 0 * 40
.stage	* ev01_161b01.png 0 0
;（この前の纮の台詞でこの差分？）
.message	460		丂峢丂	「倒下了，为什么……？」
.message	470			我虽然也知道什么失去血色。
.message	480			倒下了？
.message	490			那个一直精神满满的景──？
.message	500	kyo-113_03-0031	嫗丂夘	『跑着的时候突然就倒下了，意识到还是有的样子』
.message	510	kyo-113_03-0033	嫗丂夘	『比赛还在继续，我不能离开现场。总之觉得对你说声比较好」
.message	520		丂峢丂	「……知道了。谢了」
.message	530	kyo-113_03-0037	嫗丂夘	『虽然大概没什么大碍……记得去看望下啊』
.message	540		丂峢丂	「啊啊……」

;■御影チェック
;■　ここの京介の台詞は，どうやっても最後まで聞かないと変だ。
;■　というわけで，逆に携帯を切ったときの音をコメントアウト。
;.playSE pi.ogg f 0 *

.message	550			又道了一声谢，挂掉了电话。
.message	560			虽然不清楚具体发生了什么，但景倒下去了不是假话。
.message	570			虽然京介一直嘻嘻哈哈，但却不是会说谎的人。
.transition 0 * 40
.stage	* ev01_161c01.png 0 0
.message	580		丂峢丂	「──不是想这种事情的时候」
.message	590			不得不去。
.transition 0 * 20
.stage	* ev01_161e01.png 0 0
;（ここのフェ～ドは20でいいか？ピントの移行にも注意のこと。全部の差分を無理して使う必要はありません！）
.message	600			就算我选择了宫子没错，但这是另一回事。
.message	610			听到景倒下了的消息，就绝对不可能放着不管。
.message	620			不可能做到。
.panel 0
.transition 0 * 10
.stage	* WHITE.png 0 0


;■背景：纮の家の前→十字路→通学路
.playBGM efBGM028mix.ogg
.screen sc_evening01.png sc_evening01.png
.transition 1 fadeSide.png 10
.stage	* bgw_normal005a01_02.png 0 0
;（御影指定により変更）
;.stage	* bgw_normal015a01_02.png 0 0
;（やっぱ夕方でアタッチ）
;.stage	* bgw_normal015a01_01.png 0 0
;（背景の切り替えと，時間には注意してください。ここでは昼でアタッチしてますが）
.panel 1
.message	630			大概是刚刚H过的原因，体力几乎都消耗殆尽。
.message	640			稍微跑了两步就呼吸不过来，脚也根本移不开步子。
.message	650			这个毎天只是学园和家两点一线的身体，这个时候才觉得可恨。
.message	660			可恶，「倒下了」到底是什么啊。

;■御影チェック
;.message	670			親父の入院を聞いたときよりも，受けた衝撃は遙かにでかいと思う。
.message	670			这个比我听到父亲住院时的打击还要大。

.message	680			景──对我来说是很重要的存在。
.message	690			直到现在，我才感觉到这点。
.message	700			我一边祈祷着什么都不要发生，用几乎缓慢的动不了的脚继续跑着。
.panel 0
.screen * *
.transition 0 * 10
.stage	* WHITE.png 0 0
;（白は挿まなくてよい？）


;■背景：校門（冬，１６時
;■　　　　广野纮：制服（冬·外出）
;■　　　　新藤景：制服（冬·外出）
.screen sc_evening01.png sc_evening01.png
.overlay * or_kei02a.png
.transition 1 fadeSide.png 10
.stage	* bgw_sch001a01_02.png 0 0 st_kei04a06.png 400
;（ここで夕に切り替えてます。場所は校門でいいのかなど，留意のこと）
.panel 1
.message	710	kei-113_03-0003	丂宨丂	「咦？」
.message	720			多么重要多么重要的景，带着一副什么事都没发生过的表情出现在我眼前。
.message	730		丂峢丂	「…………」
.message	740	kei-113_03-0005	丂宨丂	「哥哥，为什么会在这里？」

;■御影チェック
;■　一瞬，なんのことか混乱しますね。
;■　鏡センセに確認して下記のように修正。
;.message	750		丂峢丂	「おまえ，景か？」
;.message	760			実は入れ替わってるとかじゃねぇだろうな。
.message	750		丂峢丂	「你…你，真的是景吗？　没和千寻掉包了吧？」
.message	751			千寻──景的双胞胎妹妹，两人有着同一张脸。
.message	752			已经倒下的景不可能好好的在这走着，在那站着必定是千寻不是别……。


.transition 0 * 40
.stage	* bgw_sch001a01_02.png 0 0 st_kei03a04.png 380
;（表情とポ～ズ，注意のこと）
.message	770	kei-113_03-0007	丂宨丂	「那个问题算什么啊。不要现在说些让人搞不清的话好吧」
.message	780		丂峢丂	「……你不是晕倒了吗」
.transition 0 * 40
.stage	* bgw_sch001a01_02.png 0 0 st_kei05a04.png 400
.message	790	kei-113_03-0009	丂宨丂	「为什么哥哥会知道？　比赛，不是没看的吗？」
.message	800		丂峢丂	「京介告诉我的」
.transition 0 * 40
.stage	* bgw_sch001a01_02.png 0 0 st_kei05a06.png 400
;（表情，注意のこと）
.message	810	kei-113_03-0011	丂宨丂	「京介是谁？」
.message	820		丂峢丂	「堤京介……啊，那无所谓了。我说你稍微让我看下脸色」
;.transition 0 * 20
;.stage	* bgw_sch001a01_02_stm.png 0 0 stm_kei05a06.png 400

;■御影チェック
;■　ここは山場なので，なるべく気になる箇所は潰しましょう。
;■　頬を掴んではニュアンス的にひっかかりそうではありますね。
;（「頬を掴んで」，，，ちょっと注意）
;.message	830			ぐっと景の頬を掴んで引き寄せる。
.message	830			啪的对着景的肩膀拉了过来。

.transition 0 * 20
.stage	* bgw_sch001a01_02_stm.png 0 0 stm_kei07a02.png 380
.message	840	kei-113_03-0013	丂宨丂	「稍，稍微等下啊哥哥」
.message	850			脸红起来的景准备挥掉我的手。
.message	860		丂峢丂	「好了给我闭嘴」
.transition 0 * 40
.stage	* bgw_sch001a01_02_stm.png 0 0 stm_kei01a09.png 360
.message	870	kei-113_03-0015	丂宨丂	「真是的……」
.message	880			虽然抱怨着，但景还是停止了抵抗。
.message	890			虽然脸红有些影响判断，但脸色确实并不好。
.message	900			该说是失去血色还是…。
.message	910			一直湿润的嘴唇也有些奇怪的干燥。
.message	920		丂峢丂	「你…没事吧？」
.transition 0 * 20
.stage	* bgw_sch001a01_02.png 0 0 st_kei02a04.png 380
;（赤味とって問題なし？）
.message	930	kei-113_03-0017	丂宨丂	「没事的啦，不是这样好好走着的么。哥哥还是意外的爱担心呢……」
.message	940		丂峢丂	「我说你，想要一个人回去吗」
.transition 0 * 40
.stage	* bgw_sch001a01_02.png 0 0 st_kei02a05.png 380
.message	950	kei-113_03-0019	丂宨丂	「顾问老师说了让我回去。虽然老师说了要送我，但还有赛后的讨论会。不能再麻烦别人更多啊」
.message	960		丂峢丂	「啊啊，比赛结束了吗」
.message	970			对于现在来说，胜败之类都已经无所谓了。
;■以下の景の台詞，２つに分割しました。
;■問題ないと思うが，演出とぶつかるようなら戻します。
.transition 0 * 40
.stage	* bgw_sch001a01_02.png 0 0 st_kei03a06.png 380
;（表情とポ～ズ，注意のこと）
.message	980	kei-113_03-0021	丂宨丂	「输了」
.transition 0 * 40
.stage	* bgw_sch001a01_02.png 0 0 st_kei03a02.png 380
.message	990	kei-113_03-0023	丂宨丂	「啊～啊，果然很强呢。虽然比分一度咬的很紧呢」
.message	1000		丂峢丂	「是吗……。我送你回去，走吧。把包给我」
.transition 0 * 40
.stage	* bgw_sch001a01_02.png 0 0 st_kei03a03.png 380
;（03a01でも？）
.message	1010	kei-113_03-0025	丂宨丂	「哥哥温柔起来，反而有些可怕呢」
.message	1020		丂峢丂	「吵死了～」
.message	1030			虽然这么说景还是老实的把包交给我，我拿过来抬起了步子。
.panel 0
.overlay * *
.screen * *
.playBGM *
.transition 0 * 10
.stage	* WHITE.png 0 0
;（白は挿まなくてよい？）


;■背景：通学路（冬，１６時
;■　　　　广野纮　　：制服（冬·外出）
;■　　　　新藤景　　：制服（冬·外出）
;■　　　　宫村宫子：私服（冬·外出）
.playBGM efBGM012.ogg
.transition 1 fadeSide.png 20
.overlay	or_kei02a.png * *
.screen	sc_evening01.png sc_evening01.png sc_evening01.png
.stage	st_kei11a02-.png 0 0 bg_scl003a01_02_f.png 0 0 bg_scl003a01_02_n.png 0
.effect	WScroll2 * 60 -2


;.screen sc_evening01.png sc_evening01.png
;.transition 1 fadeSide.png 10
;.stage	* bgw_normal002a01_02.png 0 0
;.stage	* WHITE.png 0 0
;☆（実際は通学路の通常背景，，，ではなく顔アップ歩きスクロ～ルを挿む予定ですが，どちらも来ていないので白で）
.panel 1
.message	1040		丂峢丂	「然，怎么回事？」
.transition 0 * 40
.stage	st_kei10a01-.png 0 0 bg_scl003a01_02_f.png 0 0 bg_scl003a01_02_n.png 0
;（表情，注意して）
.message	1050	kei-113_03-0027	丂宨丂	「什么？」
.message	1060		丂峢丂	「为什么会倒下去」
.transition 0 * 40
.stage	st_kei11a04-.png 0 0 bg_scl003a01_02_f.png 0 0 bg_scl003a01_02_n.png 0
.message	1070	kei-113_03-0028		景的表情一瞬间盖满了阴云。
.message	1080			对于一直很自傲的这家伙来说，在人前倒下肯定是很大的屈辱吧。
.message	1090	kei-113_03-0029	丂宨丂	「倒下什么的没那么严重啦。怎么说呢，比较近似于头晕吧」
.message	1100		丂峢丂	「头晕？」
.message	1110	kei-113_03-0030		景点了点头。
.transition 0 * 40
.stage	st_kei10a05-.png 0 0 bg_scl003a01_02_f.png 0 0 bg_scl003a01_02_n.png 0
;（表情，注意して）
.message	1120	kei-113_03-0031	丂宨丂	「轻微的脱水还有贫血。头稍稍糊涂了一下，就已经站不稳了」
.message	1130		丂峢丂	「脱水还有贫血……？」
.message	1140	kei-113_03-0033	丂宨丂	「大概就是这样吧，一直在作硬性训练。都不怎么有食欲」
.message	1150			景稍稍有些害羞起来。
.message	1160		丂峢丂	「你是白痴啊」

;■御影チェック
;.effect *
.effect end

.overlay	* * *
.screen	* * *
.screen sc_evening01.png sc_evening01.png
.overlay * or_kei02a.png
.transition 0 * 20
.stage	* bgw_normal002a01_02_stm.png 0 0 stm_kei02a03.png 360
;（表情注意。怒ってる表情で？）
.message	1170			我啪的把手放在了景的头上。
.message	1180			景瞬间脸便红透，站在那儿一动不动了。
;.effect *
;.overlay	* * *
;.screen	* * *
;.screen sc_evening01.png sc_evening01.png
;.overlay * or_kei02a.png
;.transition 0 * 20
;.stage	* bgw_normal002a01_02.png 0 0 st_kei02a03.png 380
;（表情注意。怒ってる表情で？）
.message	1190	kei-113_03-0035	丂宨丂	「干，干吗，也不至于被叫白痴吧。就算是我，也是一直努力着……」
.message	1200		丂峢丂	「到晕倒为止都要干下去的不是白痴是什么。真的没事吧？　已经什么都没了吗？　老实回答我」
.message	1210			我一边摸着景的头尽量温柔的说。
.transition 0 * 40
.stage	* bgw_normal002a01_02_stm.png 0 0 stm_kei01a09.png 360
.message	1220	kei-113_03-0037	丂宨丂	「已经喝了足够的水没事的。啊啊，但是头晕的时候碰到的膝盖还稍微有点……」
.message	1230		丂峢丂	「…………」
;（ここ，切り出しで？）
.message	1240			我蹲下来看向景的膝盖。
;■普通の立ち絵表示で違和感あるか？
.screen * *
.transition 0 * 20
.stage	* ev01_162a01.png 0 0
.message	1250	kei-113_03-0039	丂宨丂	「呀。等，等下啊。哥哥你干什么──」
.message	1260			景的脸愈加红起来，慌忙按住自己的裙子。
.message	1270			我可没想要偷看你的内裤啊。
.message	1280		丂峢丂	「唔～」
.message	1290			膝盖上好象稍微有些擦伤，但还没有红肿。
.message	1300		丂峢丂	「痛吗？」
.transition 0 * 40
.stage	* ev01_162a02.png 0 0
;.stage	* ev01_162a04.png 0 0
;（フェ～ドスピ～ドは良いか？さらにこの差分は，もちっと手前で表示して？）
.message	1310	kei-113_03-0041	丂宨丂	「有一点……」
.message	1320		丂峢丂	「真没办法啊」
.message	1330			虽然这不是我的风格，但既脱水又贫血，怎么想都不可能会完全回复。
.transition 0 * 20
;.stage	* ev01_163a01_mugai_b.png 0 0
.stage	* ev01_163a_mugai_a.png 0 0
;（ここ，切り出しで？）
.message	1340	kei-113_03-0043	丂宨丂	「……干吗？」
.message	1350			看着被背向她的我，景用怀疑的声音问道。
.transition 0 * 20
;.stage	* ev01_163a_mugai_c.png 0 0
.stage	* ev01_163a01.png 0 0
;（切り替えタイミング，注意。この一つ前の文あたりで？）
.message	1360		丂峢丂	「我背你走」
.message	1370	kei-113_03-0045	丂宨丂	「诶！？　不行的啊，那样的！！」
.transition 0 * 40
;.transition 0 * 20
.stage	* ev01_163b01.png 0 0
;（「向き直る」，，，ですが，このＣＧ差分でいいのか注意）
.message	1380			我向景转过头去。
;.transition 0 * 20
;.stage	* ev01_163b01.png 0 0
.message	1390		丂峢丂	「不想让你勉强啊。你，只有你……」
.message	1400			景，应该是比其他人重要一倍的存在。
.message	1410			有不得不这样做的理由。
.message	1420	kei-113_03-0047	丂宨丂	「那……」
.message	1430			景她也应该明白的。
.message	1440		丂峢丂	「是吧？」
.message	1450	kei-113_03-0049	丂宨丂	「但是，不行。绝对不行」
.message	1460			景顽固地摇摇头。
.transition 0 * 20
.stage	* ev01_163a01_mugai_c2.png 0 0
;.stage	* ev01_163b_mugai_b.png 0 0
.message	1470	kei-113_03-0051	丂宨丂	「因为，如果现在被哥哥背起来的话……就会那样永远下不来了……」
.message	1480			冬日的风舞动着，抚摸下景的头发然后一穿而去。
.transition 1 fadeSide.png 20
.stage	* bgw_normal002a01_02_mugai_a.png 0 0
.message	1490			远处传来轻轻的鸟鸣。
.message	1500			悲切的，斩不断，理还乱的声音……。
;.transition 0 * 20
.transition 1 fadeSide.png 20
.stage	* ev01_163b02.png 0 0
;（纮の表情変化，注意して）
;.stage	* ev01_163b01.png 0 0
.message	1510	kei-113_03-0053	丂宨丂	「哥哥，为什么没来看比赛呢……？」
.message	1520			答案--也是该说出来的时候了。
.transition 0 * 20
.stage	* ev01_163a01.png 0 0
.message	1530			虽然这时候说未免有些残酷……。
.message	1540		丂峢丂	「对不起，我……」
.message	1550	miy-113_03-0009	傒傗偙	「纮君……！」
.message	1560			啊啊，就是这么回事。
.message	1570			宫子她──那家伙她总是在最坏的时机出现。

;■御影チェック
;.message	1580			──そうじゃないか，俺が最悪の状況を作ってるんだ。
.message	1580			不，不只如此。
.message	1580			还把我推进了最坏的情况里面。

.message	1590	kei-113_03-0055	丂宨丂	「宫村前辈」
.transition 0 * 20
.stage	* ev01_166a01.png 0 0
.message	1600		丂峢丂	「宫子」
.message	1610			扭过头去，站在那儿的宫子一副快要哭出来的表情。
.message	1620			拜托了，不要露出那种表情好吗。
.transition 0 * 20
.stage	* ev01_164a01.png 0 0
.message	1630	miy-113_03-0011	傒傗偙	「纮君……果然来这边了呢」
;★ここから遠景ＣＧ
.message	1640		丂峢丂	「啊啊」
;（ここの表情注意。微笑み，，，だとちょっとアレなので，視線そらしさせるか，前差分続行か，，，）
.message	1650	miy-113_03-0013	傒傗偙	「我被吓了一跳呢……。因为，醒来的时候你就已经不在了……」
.message	1660			这个无意间丢下的炸弹让景的肩膀猛烈的震动了一下。
.transition 0 * 40
.stage	* ev01_164a02.png 0 0
.message	1670	miy-113_03-0015	傒傗偙	「不要这个。沉默着就消失什么的，不要……」
.message	1680	kei-113_03-0057	丂宨丂	「宫村前辈。这到底……是怎么回事？」
.message	1690			我抓住了坚强的挺起胸膛问过去的景的肩膀。
.message	1700			不能让这个话从宫子口中说出。
.message	1710			因为这一切都是我造成的。
.message	1720		丂峢丂	「景，听我说。我──」
.playBGM *
.transition 0 * 40
.stage	* ev01_164b03.png 0 0
;.stage	* ev01_164a03.png 0 0
;（ここで宫子の微笑み差分を使っても良いか？）
.message	1730	miy-113_03-0017	傒傗偙	「我…被纮君抱过了」
.message	1740	kei-113_03-0059	丂宨丂	「诶……？」
.transition 0 * 40
.stage	* ev01_166b01.png 0 0
.message	1750		丂峢丂	「喂，宫子！」
.message	1760			就算惊慌也已经来不及了。
.message	1770			为什么你要先说出口啊。
.message	1780	miy-113_03-0019	傒傗偙	「小景」
.message	1790			宫子已经停不下来了。
.message	1800			不可能停下来了。
.message	1810	miy-113_03-0021	傒傗偙	「我呢，没有能赢过小景的信心」
.transition 0 * 40
.stage	* ev01_166a02.png 0 0
;（景の頬を赤らめさせて問題ないのか，ここ注意）
.message	1820	kei-113_03-0061	丂宨丂	「宫村前辈……？」
.message	1830	miy-113_03-0023	傒傗偙	「小景比谁都更了解纮君，一直在他的身边。而且，十分可爱。无论是谁都会喜欢小景的吧」


;.message	1840	miy-113_03-0025	傒傗偙	「そうだよ，景ちゃんは勝てたの。勝てるのに，勝負しなかったからこうなっちゃったんだよ」
.message	1840	miy-113_03-0024	傒傗偙	「没错……是小景你赢了」
.message	1845	miy-113_03-0026	傒傗偙	「虽然赢了，但你没有决一胜负才会这样的」


;★イベントＣＧかな？
.transition 0 * 20
.stage	* ev01_165a01.png 0 0
.message	1850	kei-113_03-0063	丂宨丂	「少说……少说自做主张的话啊！」
.message	1860	kei-113_03-0065	丂宨丂	「你这种人，能懂什么！？」
.transition 0 * 40
.stage	* ev01_165a03.png 0 0
;（ここでこの差分でいいか？）
.message	1870	kei-113_03-0067	丂宨丂	「我是用什么心情面对着哥哥──为什么一直都没说出口的心情，你根本就不懂！」
.message	1880	miy-113_03-0027	傒傗偙	「我是不懂」
.transition 0 * 40
.stage	* ev01_165a02.png 0 0
.message	1890			景的身体震了一下，僵硬了。
.message	1900	miy-113_03-0029	傒傗偙	「虽然我不懂……但我知道小景再说些什么，都已经传达不到了。我不会让你传达到的。因为我一直都会在纮君的身边」
.message	1910		丂峢丂	「宫子，停下吧。不要再说了」
.transition 0 * 40
.stage	* ev01_165a04.png 0 0
;（ここでこの差分でいいか注意）
.message	1920	miy-113_03-0031	傒傗偙	「已经，结束了」
.message	1930			什么结束了。
.message	1940			就算不说，我也明白。
.message	1950			结束的是我和景青梅竹马的关系，类似的兄妹的关系。
.message	1960			还有，景对于我的心情──
.message	1970	miy-113_03-0033	傒傗偙	「小景你已经什么都做不到了」
.transition 0 * 40
.stage	* ev01_165a05.png 0 0
;（この差分をここで使っていいか注意。涙を見せるのはまだ早い？）
.message	1980	kei-113_03-0069	丂宨丂	「什么都……」
.message	1990	miy-113_03-0035	傒傗偙	「就算有──也只有放弃这一件事而已」
.message	2000		丂峢丂	「宫子！」
;.playBGM * * 0
;.playBGM efBGM053_2.ogg

.transition 0 * 20
.stage	* ev01_167a01.png 0 0
;（ここから，角度を変えながらの切り出しを交えつつ，あざとく演出）
.message	2010	kei-113_03-0071	丂宨丂	「不要，哥哥不要生气！」
.message	2020		丂峢丂	「诶……？」
.message	2030			为什么景会阻止。
.message	2040	kei-113_03-0072		景咬住自己的嘴唇，肩膀震动着轻轻的呜咽起来。

;■御影チェック
;■　こっちじゃないような。
;■　上の景のところで鳴らさない勇気があるなら，もう一歩。
;.playBGM efBGM056.ogg
;.playBGM efBGM053_2.ogg 0 *
;.playBGM BGM024_sample.ogg

.message	2050	kei-113_03-0073	丂宨丂	「……现在，哥哥现在什么都别说」

;■御影チェック
;■　こっちじゃないか？
;■　景の目線にあわせて。
.playBGM efBGM056.ogg

.transition 0 * 40
.stage	* ev01_167a02.png 0 0
;（フェ～ドスピ～ドに注意。20で？併せて，景の目を開かせるタイミングにも注意のこと）
.message	2060	kei-113_03-0075	丂宨丂	「已经无所谓了。比赛输了什么的，都已经无所谓了。有什么关系啊，那种事情」

;■御影チェック
;■　ボイスでついていけるからトル。流れ優先。
;.message	2070			どんどん景の感情が高ぶっていく。

.message	2080	kei-113_03-0077	丂宨丂	「因为我是笨蛋，又不懂事。虽然我可能已经没有资格再说什么了……」
.transition 0 * 40
.stage	* ev01_167b01_mugai_a.png 0 0
;（フェ～ドスピ～ドは20で？）
;.transition 0 * 40
;.stage	* ev01_167b01.png 0 0
;（フェ～ドスピ～ドには注意のこと）
.message	2090	kei-113_03-0079	丂宨丂	「但是就算是我也是喜欢哥哥的啊！」
.transition 0 * 20
.stage	* ev01_167b01.png 0 0
;（フェ～ドスピ～ドは40で？）
.message	2100		丂峢丂	「……！」
.message	2110			景的视线没有看向我，而是直直的面对着宫子──
.message	2120			尽管如此，从景口中说出的话也让我哑口无言。
.message	2130	kei-113_03-0081	丂宨丂	「被哥哥抱过了……？　那算什么。那又能怎么样！」
.message	2140	kei-113_03-0083	丂宨丂	「不过这点小事而已，别以为你就可以赢了！」
.message	2150	miy-113_03-0037	傒傗偙	「小景喜欢的人，是会没有任何想法就随便和女孩子H的人吗？」
.transition 0 * 40
.stage	* ev01_167b02.png 0 0
.message	2160	kei-113_03-0085	丂宨丂	「……！」
.message	2170			宫子的反击，让景退后了一步。
.message	2180			分明不得不阻止的──却无论如何都无法插入她们两人之间。
.message	2190	miy-113_03-0039	傒傗偙	「我和纮君做那样的事的意义……小景应该是最明白的才对」
.message	2200	kei-113_03-0087	丂宨丂	「我不明白……我不明白啊！」
.message	2210			景激烈的摇头否定。
.message	2220	kei-113_03-0089	丂宨丂	「不管你说些什么──这种程度我怎么可能就会放弃！」
.message	2230	miy-113_03-0041	傒傗偙	「就算不放弃──又能怎么样？」
.message	2240			宫子一瞬看向我。
.message	2250			我到底该怎么做──？
.message	2260	miy-113_03-0043	傒傗偙	「等待我们分手？　或者是，无论怎么做就要拆散我们？」
.message	2270	miy-113_03-0045	傒傗偙	「不是明显做不到的吗？那种事…」
.transition 0 * 20
.stage	* ev01_167a01_mugai_b.png 0 0
.message	2280	kei-113_03-0091	丂宨丂	「就算是我……还没……」
.message	2290		丂峢丂	「景，我──」
.message	2300			该说些什么好呢──却完全找不出该说什么。
.transition 0 * 20
.stage	* ev01_167b02_mugai.png 0 0
.message	2310	kei-113_03-0093	丂宨丂	「哥哥……你说啊」

;■御影チェック
;■　あ～，目は千尋とかぶせてるんだろうが……これはどうしようもないな。
;.message	2320			景の左目から──すうっと涙が一筋流れた。
.message	2320			从景的右眼──轻轻滑出一道泪来。
;☆（「左目から」，，，なので，ビジュアルには注意のこと）

.message	2330	kei-113_03-0095	丂宨丂	「哥哥自己的心情──真正喜欢的谁。从哥哥嘴里说出来啊」
.message	2340		丂峢丂	「我……我喜欢的是……」
.transition 0 * 40
.stage	* ev01_167c01_mugai.png 0 0
.message	2350	kei-113_03-0097	丂宨丂	「不要说！」
.message	2360			一边喊着，景堵住了自己的耳朵。
.message	2370		丂峢丂	「景……」
.message	2380	kei-113_03-0099	丂宨丂	「不要……还是不要……。什么都不要说」
.message	2390	kei-113_03-0101	丂宨丂	「那种看可怜人的眼神……不要……」
.message	2400			景低下头。
.transition 0 * 40
.stage	* ev01_167c02.png 0 0
;（涙が目視できちんとわかるか，確認のこと）
.message	2410	kei-113_03-0103	丂宨丂	「是吗。我，输了啊……」
;.message	2420	kei-113_03-0105	丂宨丂	「負けたんだ」
.message	2420	kei-113_03-0105	丂宨丂	「输了啊……」
.message	2430			虽然景的表情让我心疼万分。
.message	2440			不过，我却无法在此时背过脸去逃避……。
.transition 0 * 20
.stage	* ev01_168.png 0 0
;（コンテに従いここに挿んでますが，タイミング的にはもう少し後，ここは切り出しかなんかでうまく演出のこと）
.message	2450	kei-113_03-0107	丂宨丂	「抱歉…」
.message	2460			景突然夺走了我拿着的提包──
.message	2470			就像逃走一样跑着离开了。
;■ここから通常背景
.message	2480		丂峢丂	「景！　我说你，稍微等下！」
.message	2490			为什么我周围的女人总是这样逞强啊。
.message	2500			不是刚刚才晕倒过吗。
;.transition 0 * 20
.transition 0 * 40
.stage	* ev01_169a01_mugai_a.png 0 0
;.stage	* ev01_169a02.png 0 0
;（ここ，切り出しで？）
;（a01の使いどころはよく考えておくこと）
;.stage	* ev01_169a01.png 0 0
;（修羅場にしては宫子の表情和みすぎてるので注意されたし）
;.transition 0 * 20
;.stage	* bgw_normal002a01_02.png 0 0
;（通常背景切り替え指定位置より後に置いてますが，もちっと後に置いてもいいくらいか？）
.message	2510	miy-113_03-0047	傒傗偙	「纮君！」

;■御影チェック
;■　むき～。ＢＧＭはそのままいこう。
;.playBGM *
;.playBGM efBGM024.ogg

.transition 0 * 20
.stage	* ev01_169a02.png 0 0
;（フェ～ドスピ～ド40で？）
.message	2520			袖子啪的被拉住了。
.message	2530	miy-113_03-0049	傒傗偙	「要追过去吗？」
.message	2540		丂峢丂	「没办法的啊。按家伙，刚刚才在比赛中晕倒啊」
.transition 0 * 40
.stage	* ev01_169a03.png 0 0
.message	2550	miy-113_03-0051	傒傗偙	「是这样吗……」
.message	2560			宫子轻轻摇了摇头。
.transition 0 * 40
.stage	* ev01_169a04.png 0 0
;（ここでこの差分表情でいいか？03をもちっと継続？）
.message	2570	miy-113_03-0053	傒傗偙	「但是呢，无论何时我都想让你只看着我一个人」
.message	2580		丂峢丂	「就算如此，她也是青梅竹马啊。担心景不是理所当然的吗？」
.message	2590	miy-113_03-0055	傒傗偙	「…………」
.message	2600			别不说话啊。
.message	2610		丂峢丂	「对于什么都不说就出去了这点我道歉」
.message	2620		丂峢丂	「但是，也不可能一直只看着你吧。实际上做不到啊」
.message	2630	miy-113_03-0057	傒傗偙	「……我知道啊。我知道的哦。不可能只有我一个人」
.transition 0 * 20
.stage	* ev01_169b05.png 0 0
.message	2640			她松开了拉住我袖子的手。
.message	2650			宫子又浮起一如既往的笑容。
.transition 0 * 40
.stage	* ev01_169b01.png 0 0
.message	2660	miy-113_03-0059	傒傗偙	「抱歉。不过，我……只是不想松开重要的东西而已」
.transition 0 * 40
.stage	* ev01_169b02.png 0 0
.message	2670			宫子微笑着，向着景离开的方向望去。
.message	2680	miy-113_03-0061	傒傗偙	「虽然我也有我的理由，但小景听了也只会被认做是借口吧」


;.message	2690	miy-113_03-0063	傒傗偙	「わかってるから，あたしはタチが悪い。自分が安心するためだけに，誰かを傷つけて，重荷を背負わせて。勝手なことばかりしてたら，嫌われるだけなのに」
.message	2690	miy-113_03-0062	傒傗偙	「我知道的啦，我本身就是个坏人……」
.message	2695	miy-113_03-0064	傒傗偙	「只为了自己安心，伤害别人，让别人背上重担。一直自以为是，自然会被讨厌的吧」


.message	2700		丂峢丂	「宫子」
.message	2710			在满是笑颜说着话的宫子脸上──我却除了痛苦以外什么都看不到。
.message	2720			已经不想让任何人受到伤害。
.message	2730			我所希望的只有这点而已……。
.message	2740		丂峢丂	「别笑」
.transition 0 * 40
.stage	* ev01_169b01.png 0 0
;（ここで視線，纮に戻してｏｋ？）
.message	2750	miy-113_03-0065	傒傗偙	「……诶？」
.message	2760		丂峢丂	「不想笑的时候就不要笑。不要强迫自己。为什么你到什么时候都不会坦诚一点呢」
.transition 0 * 40
.stage	* ev01_169b03.png 0 0
.message	2770	miy-113_03-0067	傒傗偙	「我，我……」
.message	2780			宫子的脸瞬间阴暗下来。
.message	2790			看到那张脸虽然会有些心痛，但果然还是这样才好。
.transition 0 * 40
.stage	* ev01_169b04.png 0 0
;（ここ，03表情をもちっと継続させるのもありかもしれません。03表情で最後までいってしまうのもありかと）
.message	2800	miy-113_03-0069	傒傗偙	「因为…不知道该作出什么表情好……」
.message	2810		丂峢丂	「你啊」
;☆（↑の台詞は問題ない？）
.message	2820		丂峢丂	「就算如此，你也不该伤害自己啊。就算你那么做，也不可能和伤害别人的事相互抵消」
.message	2830		丂峢丂	「最起码，没必要你来演坏人啊。景要恨的话，恨我一个就足够了」
.message	2840		丂峢丂	「你其实并不是景讨厌的那类女人啊」
;（ここでb04表情を？）
.message	2850	miy-113_03-0071	傒傗偙	「……我说过讨厌别人骗我的」
.message	2860		丂峢丂	「你不是也说过吗。我和景有些相似」
.message	2870		丂峢丂	「既然是我喜欢的人，大概景肯定也会喜欢。就算真的讨厌，那也是我的错」
.transition 0 * 40
.stage	* ev01_169b05.png 0 0
;（ここでこの差分表情でいいか？）
.message	2880	miy-113_03-0073	傒傗偙	「我不想归咎成任何其他人的错。如果那么做的话，我就真的已经堕落的无可救药了」
.message	2890	miy-113_03-0075	傒傗偙	「说不定已经堕落了呢」
.message	2900		丂峢丂	「宫子」
.message	2910			我直直的看向宫子的双眼。
.message	2920		丂峢丂	「不要讨厌自己。如果否定了自己的话，就什么都无法开始了」
.message	2930		丂峢丂	「无论作什么事，都有你自己的理由在。这个又有什么错？」
.message	2940	miy-113_03-0077	傒傗偙	「对不起。我不明白……」


;■御影チェック
;■　確かに，ここまでの流れを踏まえた上で，きっかり見るとつらいな……。
;■　ちょっと姿月先生に相談。
;■　夕焼けに逃げておきましょう──と，冬だが，色合い的に向井さん作の
;■　終章過去編·夏の夕焼け空をもってきてみましたが大丈夫かな？
;☆（つ～かこのＣＧ，あんま良くないな，，，。さて，どうすっべか）
;（後半は切り出しをうまく使っていってください。このモブＣＧも，纮と宫子の表情には注意のこと）
;.transition 0 * 20
;.stage	* bgw_sky001a01_02.png 0 0
;.stage	* bgs_sky001a01_02_mugai_a.png 0 0

;■御影チェック
;■　ＣＧを修正してもらったので復活。
;■　これならそれほど違和感はないか。
.transition 0 * 20
.stage	* ev01_170.png 0 0


.message	2950			穿着音羽制服的几个女孩子，看着我们走了过去。
.message	2960			大概，那些女孩们在想像些各种各样的事情吧。
.message	2970			而且，那想像大概也距事实不远。

;■御影チェック
;■　ここで追加で空に飛ばそう。
.transition 0 * 20
.stage	* bgs_sky001a01_02_mugai_a.png 0 0

.message	2980			真奇怪啊，为什么会这样呢。
.message	2990			分明就在刚才，还和宫子一起在床上──觉得自己多么幸福的。
.panel 0
.overlay * *

;■御影チェック
;■　BGMを変えたので，ここで止めます。
;.playBGM *
.playBGM *

.transition 0 * 10
.stage	* WHITE.png 0 0
.transition 0 * 10
.stage	* WHITE.png 0 0
.wait 100

.chain 114_01.sc
;■114_01へ。

;.end
