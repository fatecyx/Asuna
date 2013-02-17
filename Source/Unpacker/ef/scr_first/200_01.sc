; ファイル: 200_01.txt
;■＜２章：ＯＰ＞
;■背景：体育館（夏，１５時
;■　　　　堤京介：制服（夏）
;■　　　　新藤景：制服（夏）
.setGlobal EYE_SEQ_DEFAULT = 2

.transition 0 * 10
.stage	* WHITE.png 0 0
;.wait 500
;.wait 250
.wait 100
.transition 0 * 10
.stage	* ago_base_second.png 0 0
.message	101			\a　
;.wait 450
.wait 300
.transition 0 * 10
.stage	* WHITE.png 0 0

;.transition 0 * 10
.transition 0 * 8
.stage	* ago_base_20001a.png 0 0
;.stage	* ev02_001a01.png 0 0
.panel 1
.message	100			那一天，我看到一名少女。
.transition 0 * 20
.stage	* ago_base_20001b.png 0 0
.message	110			她的目光落向手中的篮球，分纹不动的站在那里──
.transition 0 * 20
.stage	* ago_base_20001c.png 0 0
.message	120			她伫立在斜射而进的初夏阳光中的身影，让我一瞬以为那是一个精致的人偶。
;.transition 0 * 20
.transition 0 * 10
.stage	* ev02_002a01.png 0 0
;（インのタイミング，注意して。フェードスピードにも注意。スピード感をだすために，なるべくはやく？）
.message	130			从这里要有什么即将开始──
.message	140			那场面可以让我清楚地预感到。
.message	150			为什么会如此。
.message	160			为什么偏偏在这种时候却没有带着摄像机。
.message	170			那么，至少也要让这光景深深刻入眼中。
.transition 0 * 20
.stage	* ev02_002b01.png 0 0
;（次でこのＣＧを？）
;（ここまでビスタで，指で囲ったあと，上下黒をはずす演出で？）
.message	180			我用双手的拇指和食指组成四角形的取景框。
.message	190			闭上一只眼，把那女孩圈在取景框中。
.playSE kei_dribble_twice.ogg f 0 *
.transition 0 * 20
.stage	* ev02_002c01.png 0 0
;（フェードスピードは注意して）
.message	200			咚，咚。
.message	210			她带了两下球。

;.playSE kei_shoot.ogg f 0 *
.transition 0 * 20
.stage	finder_finger.png ev02_002c02_mugai_a.png 0 32
.vscroll	0	-5
.endScroll f
;☆（下に白は出てないか，チェックはしっかりと）

;.transition 0 * 20
;.stage	* ev02_002c02.png 0 0
.message	220			然后突然举起拿着球的手摆出姿势。
;■何かＳＥあったほうがいいかも。ボールを放る音なんてあるか？
.playSE kei_shoot.ogg f 0 *
;☆（いっこ前で鳴らすのが普通なのかもしれませんが，あえてここで）
.transition 0 * 20
.stage	* ev02_003.png 0 0
;（指で囲っての演出は，要考えること）
.message	230			然后用无比柔顺的姿势投出了球。

.transition 0 * 20
.stage	finder_finger.png ev02_004a01_big.png 800 600
.transition 0 * 20
.stage	finder_finger.png ev02_004b01_big.png 600 400
.transition 0 * 20
.stage	finder_finger.png ev02_004c01_big.png 400 200

;.transition 0 * 20
;.stage	finder_finger_second.png ev02_004a01_mugai.png 0 0
;.transition 0 * 20
;.stage	finder_finger_second.png ev02_004b01_mugai.png 0 0
;.transition 0 * 20
;.stage	finder_finger_second.png ev02_004c01_mugai.png 0 0
;（連続で表示させてます。画面をパンさせるかどうかは保留。パネルトル？）
;.transition 0 * 20
;.stage	* ev02_005a01.png 0 0
;（フェードスピードには注意して）
.message	240			画面的范围追寻着篮球的移动。
.transition 0 * 20
.stage	* ev02_005a01.png 0 0
.message	250		嫗丂夘	「啊……」
.playSE kei_ring.ogg f 0 *
.transition 0 * 20
.stage	* ev02_005b01.png 0 0
.message	260			咚。
.playSE kei_round.ogg f 0 *
.transition 0 * 20
.stage	* ev02_005c01.png 0 0
.message	270			但是，有什么地方不太好吗。
.transition 0 * 20
.stage	* ev02_005d01.png 0 0
.message	280			篮球绕着篮框滚动了一周，然后掉到了地板上。
.playSE kei_ball_korogaru.ogg f 0 *
;（ここ，もちっとボールがはねてる感のものを？おとなしすぎる気もするので）
.transition 0 * 20
.stage	finder_finger.png ev02_001b01.png 0 0
.message	290			她稍微扭过头，看着掉在地板上的篮球的滚动。
.transition 0 * 20
.stage	* ev02_002b02.png 0 0
;（この002b02のＣＧの使いどころ，注意して）
;（「初めて彼女の顔が見えた」，，，ここの演出は注意して）
.message	300			这个时候，我才刚刚意识到那女孩本身的存在。
;.message	300			そのとき，初めて彼女の顔が見えた。
.message	310			有些缺少活力的那个脸色，以前记得好像在什么地方见过──
.message	320			那个女孩子叫什么名字来着……。
.message	330	kei-200_01-0003	@丂宨丂	「又没中…吗……」
.message	340			她缓缓的说着。
.message	350			那话中没有任何感情。
.message	360			但为何这种无机质般的感觉，却会如此的震动我的心灵。
.transition 0 * 20
.stage	* ev02_002b03.png 0 0
.message	370			过了一会，少女把目光从篮球移开。
;■自嘲気味に
.transition 0 * 20
.stage	finder_finger.png ev02_001b01.png 0 0
;（001b01を使ってますが，景の視線は京介に向いてます。そう見えないようなら変更を）
;.transition 0 * 20
;.stage	finder_finger.png ev02_001c01.png 0 0
;☆（指フレームを別レイヤーで使う場合，上と左上にはよくよく注意して）
;（フェードスピード，表示タイミングには注意して）
.message	380	kei-200_01-0005	@丂宨丂	「我呢，以前是篮球部的……虽然自己说起来不太像话，但曾经很活跃的哦」
.transition 0 * 20
.stage	* ev02_001b01.png 0 0
;.stage	* ev02_001c01.png 0 0
;（ここで「フレームを作っていた手」を下げるので，注意して）
.message	390			我放下取景的手。
.message	400		嫗丂夘	「注意到了啊。难道说打扰了吗？」
.message	410	kei-200_01-0007	@丂宨丂	「不，到无所谓。无论是否被人看着，我的球都不可能会进的」
.message	420		嫗丂夘	「但是不是有很标准的姿势吗」
.transition 0 * 20
.stage	* ev02_001c01.png 0 0
;（このＣＧの使いどころ，注意して。さらにここから，どうすんのかも）
.message	430			她缓缓的转过身来，正面看向我。
.message	440	kei-200_01-0009	@丂宨丂	「虽然有些失礼，但您没什么观察力呢」
.message	450		嫗丂夘	「诶？」
;■挑戦的
.transition 0 * 20
.stage	* ev02_007a01_mugai_a.png 0 0
;（この切り出しはちょっと保留。立ち絵，，，はやりたくないので，新しくイベントＣＧを作ってもらうくらいの覚悟を）
.message	460	kei-200_01-0011	@丂宨丂	「我的投球什么的最差了」
.message	470			突然口气骤然改变。
.transition 0 * 20
.stage	* ev02_007a02_mugai_a.png 0 0
;☆（フェードスピードは20でいい？ここ）
;（表情変化，注意。次でこの表情を？）
.message	480	kei-200_01-0013	@丂宨丂	「如果真的是用标准的姿势所投出的球，绝对不会不进。更不用说，现在是没人防守的状态」
.message	490	kei-200_01-0015	@丂宨丂	「如果是前段时间的我，绝对不可能不进的。而现在……」
;☆（ここ，目つむりを？）
.message	500	kei-200_01-0017	@丂宨丂	「真是不能看呢」
.message	510		嫗丂夘	「……看起来我真的没有什么观察力呢」
.message	520			为什么会觉得她像人偶一般呢。
.message	530			这个女孩不是如此激烈──拥有着人类的感情吗。
.message	540			不过，却有一些自暴自弃的感觉。
.transition 0 * 20
.stage	* ev02_007a03_mugai_a.png 0 0
;☆（フェードスピードは20でいい？ここ）
.message	550	kei-200_01-0019	@丂宨丂	「……差不多要走了呢。马上部团活动的人就会来了」
.message	560			就好像什么事都没有发生过一样，她的口气恢复了平常。
.message	570			刚才的激烈感像错觉一样消失掉了。
.message	580		嫗丂夘	「啊啊，是啊。我也差不多走人的好」
.transition 0 * 20
.stage	* ev02_007a03_mugai_c.png 0 0
;☆（この切り出しはちょっと注意）
.message	590	kei-200_01-0021	@丂宨丂	「嗯，在这呆下去的话是会被打出去的哦。篮球部和排球部的不少人都很暴躁的呢」
.message	600		嫗丂夘	「那还真是可怕呢」
;（ここで切り出しを？）
.transition 0 * 20
.stage	* bg_up002a01_01_mugai_a.png 0 0
;☆（フェードスピード注意して。もちっと遅く？）
.message	610	kei-200_01-0023	@丂宨丂	「那么，我就先告辞了」
.message	620			毫无失礼之处，认真严谨的告别。

;■御影チェック
;.message	630			まあ，制服を見れば俺のほうが先輩だってわかるだろうから，それが当然といえば当然だし。

.message	640		嫗丂夘	「那个」
.message	650			我喊住了已经踏出脚步的那个女孩。
.transition 0 * 20
.stage	* ev02_106a01_mugai_a.png 0 0
.message	660	kei-200_01-0025	@丂宨丂	「怎么？」
.message	670			我用手示意让她站在那里，然后去拿落在那儿的篮球。
;■不審
.transition 0 * 20
.stage	* ev02_006a01_mugai_a.png 0 0
.message	680	kei-200_01-0027	@丂宨丂	「……那个？」
.message	690		嫗丂夘	「不用管，看着就是」
.transition 0 * 10
.stage	* ev02_006a01.png 0 0
;（フェードスピードは20で？）
.message	700			我拿住拾起的篮球，站在那女孩的身边。
.message	710			然后，慎重的选择目标──
;.transition 0 * 20
;.stage	* ev02_006b01.png 0 0
.transition 0 * 20
.stage	* ev02_006b01_mugai_a.png 0 0
.message	720			投球。
.playSE kei_board.ogg f 0 *
.transition 0 * 20
.stage	* ev02_100c01.png 0 0
;☆（b01を使うのが普通なのかもしれませんが，ひねくれてこれで）
;.transition 0 * 20
;.stage	* ev02_006b01.png 0 0
.message	730			咚。
.playSE kei_round.ogg f 0 *
.transition 0 * 20
.stage	* ev02_006b01.png 0 0
.message	740			咚咚。
.message	750			篮球像是掠过篮框一样，撞在篮板上，又在篮框上滑动了一下──
.playSE kei_goal.ogg f 0 *
.transition 0 * 20
.stage	* ev02_006c01.png 0 0
.message	760			然后唰的，穿过了篮网。
;.transition 0 * 20
;.stage	* ev02_006c01.png 0 0
.message	770		嫗丂夘	「OK！」
.message	780		嫗丂夘	「如何，我的射球？」
;■ジト目
.transition 0 * 20
.stage	* ev02_007a01.png 0 0
.message	790	kei-200_01-0029	@丂宨丂	「差的要死」
.message	800			她毫无笑容的说道。
;■視線逸らし
.transition 0 * 40
.stage	* ev02_007a02.png 0 0
;（フェードスピードはここから40にしてますが，注意して）
.message	810	kei-200_01-0031	@丂宨丂	「但是……」
.message	820			稍微有些犹豫之后，她扬起一只手。
.transition 0 * 20
.stage	* ev02_007b01.png 0 0
.message	830	kei-200_01-0033	@丂宨丂	「好球」
.message	840			说着，她终于露出了些许的微笑。
.playSE hirate.ogg f 0 *
;☆（はるおとの平手再利用してますが，問題あるようなら·苦笑）
;.transition 0 * 20
.transition 0 * 40
.stage	* ev02_007c01.png 0 0
;（フェードスピードは40で？）
.message	850		嫗丂夘	「谢啦」
.message	860			我也笑着，对着她扬起的手拍了过去。
.message	870			啪，稍稍有些让人愉快的声音。
.transition 0 * 20
.stage	past_window.png ev02_007c01.png 0 0
;（ここの演出はちょっと保留）
.message	880			这个瞬间──我回忆起两件事情。
.transition 0 * 20
.stage	* ago_base_20001d.png 0 0
.message	890			一个是冬去春来之时有一个朋友从这学园离去。
.transition 0 * 20
.stage	past_window.png ev02_007d01_mugai01.png 0 0
;.stage	* ago_base_20001e.png 0 0
;.transition 0 * 20
;.stage	past_window.png ev02_007d01.png 0 0
;（このＣＧへの移行タイミング，注意して）
.message	900			另一个就是毕业之后，和那家伙也是像这样击掌告别。
.transition 0 * 20
.stage	past_window.png ev02_007d01_mugai02.png 0 0
;.stage	* ago_base_20001f.png 0 0
.message	910		嫗丂夘	「──是吗，那家伙吗」
.transition 0 * 20
.stage	* ev02_007d01.png 0 0
.message	920			她好像并没有听到我低声的话，却不知为何紧紧盯着自己的手掌。
.message	930			不过，她马上又扬起了脸。
.transition 0 * 20
.stage	* ev02_007a03.png 0 0
;（フェードスピードには注意して）
.message	940	kei-200_01-0035	@丂宨丂	「那么，这次真的…先行告辞了」
.message	950		嫗丂夘	「啊啊」
.transition 0 * 20
.stage	* ev02_008b01.png 0 0
;.stage	* bg_up002a01_01.png 0 0
;（顔アップ用背景を流用しています。ここからの演出には注意して）
.message	960			望着她从体育馆的门离开，我紧紧捏起拳头。
.message	970			从学园离开的朋友，那人的妹妹般的存在。
.message	980			1年级还是篮球部的主将──而在升入2年级之前离开部团的女孩。
.transition 0 * 20
.stage	* ev02_008a01.png 0 0
;（↑と↓，逆にするか？）
;.stage	* bg_up002a01_01_mugai_b.png 0 0
.message	990		嫗丂夘	「对了」
.message	1000		嫗丂夘	「是叫新藤景同学……没错吧」
.message	1010			那就是她的名字。
.transition 0 * 20
.stage	* WHITE.png 0 0
;（白にする必要はないかもしれませんが。フェードスピードにも注意して）
.message	1020			和一起度过这个炎热的季节的新藤景的最初的相遇──就这样结束了。



;■御影チェック
.panel 0
.wait 50
;.wait 170
;.transition 0 * 9
;.transition 0 * 10
;.stage	* WHITE.png 0 0
;.wait 260
.wait 100
.transition 0 * 8
.stage	* second_title.png 0 0
.message	1021			\a　
.wait 350


;.panel 0
;.transition 0 * 10
;.stage	* WHITE.png 0 0
;.transition 0 * 10
.transition 0 * 8
.stage	* WHITE.png 0 0
;.wait 100
.wait 50

.chain 201_01.sc
;■201_01へ。

;.end
