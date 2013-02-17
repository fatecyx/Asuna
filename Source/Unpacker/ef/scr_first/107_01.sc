; ファイル: 107_01.txt
;■＜１章：７日目＞
;■背景：紘自室（冬，７時
;■　　　　广野紘：制服（冬）
;■　　　　新藤景：制服（冬）
.transition 0 * 10
.stage	* BLACK.png 0 0
;（白も考慮に。もしくは「顔をあげた」，，，なので天井でもいいかもしれません）
.panel 1
.message	100			最初的一步是从哪踏出的呢。
.message	110			被问到为什么在奔跑，我会回答不得不如此。
.message	120			不过，被问道为什么开始奔跑的话。
.message	130			──我找不出答案。
.message	140	kei-107_01-0003	丂宨丂	「什么找不出答案啊」
.message	150		丂峢丂	「咦？」
.transition 1 fadeGray.png 40
.stage	* ev01_076a01.png 0 0
.message	160			传至耳边的声音，让我呼的抬起了脸。
;.transition 1 fadeGray.png 40
;.stage	* ev01_076a01.png 0 0
.transition 0 * 40
.stage	* ev01_076a02.png 0 0
;（びっくりさせる演出，しっかりと。必要なら切り出しを絡めて）
.message	170	kei-107_01-0005	丂宨丂	「哇」
.message	180			景的脸就在我眼前至近的地方。
;■照れ
.message	190	kei-107_01-0007	丂宨丂	「不，不要吓人啦，真是的」
.message	200		丂峢丂	「……被吓到原来是你吗」
;.playBGM efBGM030.ogg
.transition 0 * 20
.stage	* ev01_077a01.png 0 0
.message	210			伸了一个大大的懒腰，为了确认时间而把手伸向了桌上的手机。
;（効果音，必須のこと）
.playSE hiro_otosu_a.ogg f 0 *
.transition 0 * 40
.stage	* ev01_077b01.png 0 0
.message	220		丂峢丂	「啊」
.message	230			啪,抓在手里的手机掉在了地上。
.playBGM efBGM030.ogg
.message	240	kei-107_01-0009	丂宨丂	「干什么啊。早上起床没有力气吗？」
.transition 0 * 20
.stage	* ev01_076b02_anime_a.png 0 0
;.stage	* ev01_076b02.png 0 0
;（前文でこのＣＧ表示を？）
.message	250			景捡起手机，把液晶画面对向我。
.message	260		丂峢丂	「分明都还没有睡够呢……已经早上了吗」
.transition 0 * 40
.stage	* ev01_076b01_anime_a.png 0 0
;.stage	* ev01_076b01.png 0 0
.message	270	kei-107_01-0011	丂宨丂	「所以我才会这儿的啊。早安，哥哥」
.overlay * or_kei00a.png
.transition 0 * 20
.stage	* bgc_home001a01_00.png 0 0 st_kei01a02.png 380
;.stage	* bgc_home001a01_00.png 0 0 st_kei01a01.png 380
;（表情とポ～ズには注意のこと）
;（キャラの立ち位置には注意のこと）
.message	280		丂峢丂	「早安……你，没晨练吗？」
.message	290	kei-107_01-0013	丂宨丂	「没啊」
.message	300		丂峢丂	「自主练习呢？」
;（ここ，表情注意）
.message	310	kei-107_01-0015	丂宨丂	「也休息了。所以才来了啊」
.message	320			景没有理由的挺起胸来。
.message	330		丂峢丂	「分明是正规队员这样行吗。不是每天持续练习的话不就没有意义了吗？」
.message	340			景嘟起了嘴唇。
.transition 0 * 40
.stage	* bgc_home001a01_00.png 0 0 st_kei01a03.png 380
.message	350	kei-107_01-0017	丂宨丂	「又不是我想休息才休息的」
.message	360	kei-107_01-0019	丂宨丂	「昨天的练习稍微有些过分了，被前辈下令晨练禁止了而已」
.transition 0 * 40
.stage	* bgc_home001a01_00.png 0 0 st_kei01a01.png 380
;（表情注意）
.message	370	kei-107_01-0021	丂宨丂	「今天的午后是和附中的学生们的共同练习……为了不被后辈们看到奇怪的地方，才休息的」
.message	380		丂峢丂	「你一直都很奇怪所以这也是没办法的啊」
.transition 0 * 40
.stage	* bgc_home001a01_00.png 0 0 st_kei01a07.png 380
;（表情注意。ギャグっぽすぎるか？）
.message	390	kei-107_01-0023	丂宨丂	「这句话被用来当作遗言的话，人生会留有遗憾吧」
.message	400			目光是认真的。
.message	410		丂峢丂	「嘛，嘛，偶尔休息也不错呢。因为你不知道什么叫做适度啊」
.transition 0 * 40
.stage	* bgc_home001a01_00.png 0 0 st_kei01a08.png 380
.message	420	kei-107_01-0025	丂宨丂	「说不定是这么回事。勉强作事的习惯大概是受哥哥的影响吧……。我也确实觉得这样很为难呢」
.transition 0 * 40
.stage	* bgc_home001a01_00.png 0 0 st_kei02a04.png 380
.message	430	kei-107_01-0027	丂宨丂	「真的是作不到斟酌呢」
.message	440			景她喀啦喀啦的捏着手指。
.message	450			这不稳的空气再次流动起来。
.message	460			说起来，我都忘光了来着──
.message	470		丂峢丂	「那个，景小姐？」
.message	480			误会我把宫子带到家中，难道现在还在怒火中烧吗？
.message	490			手无缚鸡之力的我，跟体育系的景比起来就算用尽全力也没有赢的自信。
.transition 0 * 40
.stage	* bgc_home001a01_00.png 0 0 st_kei01a03.png 380
.message	500	kei-107_01-0029	丂宨丂	「干吗要带个小姐啊，笨蛋」
.transition 0 * 40
.stage	* bgc_home001a01_00.png 0 0 st_kei01a01.png 380
.message	510	kei-107_01-0031	丂宨丂	「是还没睡醒吧，哥哥。今天没被打就起来了，脑子还没有转动起来么？」
.message	520		丂峢丂	「转起来了，转起来了」
.message	530			我用劲的把头摇来摇去。
.message	540			幸好景是记忆力为0的白痴啊……。
.transition 0 * 40
.stage	* bgc_home001a01_00.png 0 0 st_kei03a05.png 380
;（表情とポ～ズ注意）
.message	550	kei-107_01-0033	丂宨丂	「那就快作准备啦。反正你，今天又不会吃饭的吧？」
.message	560		丂峢丂	「啊啊，嗯。那稍微等我一会」
.message	570			一边说着，一边慢吞吞的手伸向衣服。
.transition 0 * 40
.stage	* bgc_home001a01_00.png 0 0 st_kei07a02.png 400
;（表情とポ～ズ注意）
.message	580	kei-107_01-0035	丂宨丂	「稍，稍等一下啊。脱衣服不要那么快好吧」
.message	590		丂峢丂	「想要慢慢的仔细的看吗？」
.playSE kei_kaban.ogg f 0 *
.transition 0 * 40
.stage	* bgc_home001a01_00.png 0 0 st_kei05a07.png 400
;.stage	* bgc_home001a01_00.png 0 0 st_kei06a05.png 400
;（表情とポ～ズ注意）
.message	600			咚！
.message	610		丂峢丂	「好痛！」
.message	620			飞过来的是东西是，不知放入什么东西而重的厉害的景的提包。
.transition 0 * 40
.stage	* bgc_home001a01_00.png 0 0 st_kei03a04.png 380
;（表情とポ～ズ注意）
.message	630	kei-107_01-0037	丂宨丂	「我的意思是不要让你在女孩子突然就脱衣服！」
.message	640		丂峢丂	「我说你，还真是不知道什么叫做斟酌啊。我要是脑挫伤的话怎么办」
.message	650			头有着快破掉一样的疼痛。
;（ここ，01a06で？）
.message	660	kei-107_01-0039	丂宨丂	「刺激一下你的脑袋还说不定聪明点」
.message	670		丂峢丂	「少说得跟自己很聪明似的。你不也是个受过期中的补考的笨蛋吗」
.transition 0 * 40
.stage	* bgc_home001a01_00.png 0 0 st_kei01a06.png 380
.message	680	kei-107_01-0041	丂宨丂	「很，很失礼诶。补考什么的我到现在不过才3次而已……」
.message	690		丂峢丂	「就算是我一年级也才补考两次啊」
.transition 0 * 40
.stage	* bgc_home001a01_00.png 0 0 st_kei02a06.png 380
;.stage	* bgc_home001a01_00.png 0 0 st_kei02a03.png 380
;（02a06でも？）
.message	700	kei-107_01-0043	丂宨丂	「糟了……干吗要认真回答啊我」
.message	710			景抱起头开始低沉起来。
.message	720			嘛，像景这样运动可以的人，稍微笨点还可以原谅嘛。
.message	730		丂峢丂	「再说了，还说什么女孩子。我怎么哪都看不到那样的东西」
.message	740			说着我迅速的摆好架势准备防御攻击。
.transition 0 * 40
.stage	* bgc_home001a01_00.png 0 0 st_kei03a06.png 380
;（表情とポ～ズ，注意して。「睨んでいる」表情とはちょっと違いますが，，，）
.message	750			……奇怪？
.message	760			我还以为会再有什么飞砸过来来着。
.message	770		丂峢丂	「景？」
.message	780			景她正带着一副考虑事情的表情盯着地板。
.message	790		丂峢丂	「诶？　哎呀，我是说笑的啦。别当真啊」
.message	800	kei-107_01-0045	丂宨丂	「……不管到什么时候我也仅仅只是妹妹一样的存在而已呢」
.message	810		丂峢丂	「哈？」
.message	820			妹妹一样的存在不是一直以来的事实吗，怎么现在注意起这个来……？
.message	830		丂峢丂	「景。我说你，出什么事了吗？」
.transition 0 * 40
.stage	* bgc_home001a01_00.png 0 0 st_kei04a04.png 400
;（表情とポ～ズ注意）
.message	840	kei-107_01-0047	丂宨丂	「没什么」
.message	850			突然景扬起了脸，注视着我。
.transition 0 * 40
.stage	* bgc_home001a01_00.png 0 0 st_kei06a01.png 400
;（表情とポ～ズ注意）
.message	860	kei-107_01-0049	丂宨丂	「什么都没哦。我跟平时一样啊」
.message	870		丂峢丂	「……是吗」
.message	880			真是个笨蛋啊，景。
.message	890			且不说我拥有漫画家的观察力，她那逞强的说话方式就已掩盖不住了。
.panel 0
.overlay * *
.playBGM *
.transition 0 * 10
.stage	* WHITE.png 0 0


;■背景：通学路（冬，８時
;■　　　　广野紘　　：制服（冬·外出）
;■　　　　新藤景　　：制服（冬·外出）
;■　　　　宫村宫子：制服（冬·外出）
.playSE2 otowa_kaze_first.ogg true

.transition 1 fadeSide.png 10
.overlay	or_kei00a.png * *
.screen	sc_morning01.png sc_morning01.png sc_morning01.png
;.screen	scl_morning01.png scl_morning01.png scl_morning01.png
.stage	st_kei11a01-.png 0 0 bg_scl002a01_00_f.png 0 0 bg_scl002a01_00_n.png 0
.effect	WScroll2 * 60 -2

;.playBGM efBGM020.ogg
;.transition 1 fadeSide.png 10
;.stage	* bgw_normal002a01_00.png 0 0
;（通学路ないんで保留）
;（さらにここは顔アップ＋無限スクロ～ルでいくみたいです。演出もそれに合わせるように注意のこと）
;（必要なら「唸るような風」の効果音を）
.panel 1
.message	900			冬日的寒风，带着呻吟的声音吹过音羽。
.message	910			虽然这个城市平常就会有海风吹过，但今天的风却格外的强烈。
.message	920			景按着裙子，缓缓的走在我身边。
.transition 0 * 40
.stage	st_kei10a01-.png 0 0 bg_scl002a01_00_f.png 0 0 bg_scl002a01_00_n.png 0
;（a05表情でも？）
.message	930	kei-107_01-0051	丂宨丂	「……怎么了？」
.message	940		丂峢丂	「没怎么啊」
.transition 0 * 40
.stage	st_kei11a01-.png 0 0 bg_scl002a01_00_f.png 0 0 bg_scl002a01_00_n.png 0
;（視線をa01に戻していいのか，注意して）
.message	950			到不是值得特意说出口的事情，想起来的话──
.message	960			景以前是绝对不穿裙子的。
.message	970			为了从服装上比较容易区别，景特意这么做也有可能，主要还是本人喜欢所以才一直都穿裤子吧。
.message	980			但是最近才注意到连私服的时候也是穿裙子了。
.message	990			从什么时候开始这样的呢？
.message	1000			虽然一直在身边这么近，却连这点事情都不知道。

;■御影チェック
;.effect *
.effect end

.overlay	* * *
.screen	* * *
;（サイドフェ～ドで次に？さらにここは歩きスクロ～ルを止めて演出？）

.screen sc_morning01.png sc_morning01.png
.overlay * or_kei00a.png
.transition 0 * 20
.stage	* bgw_normal002a01_00.png 0 0 st_kei04a05.png 400
;（04a05って目線，下に向いてる？だとしたら，「こちらを見据えている」からははずれるか，，，）
;（通常背景ですが，歩きスクロ～ル用背景の上に立ち絵をのせたいです。その時は，二人の立ち位置に注意して）
.message	1010	kei-107_01-0053	丂宨丂	「哥哥你……」
.message	1020		丂峢丂	「嗯？」
.message	1030			景站住了脚，用认真的表情看着我。
.message	1040			时间还早的原因，上学的路上一个其他学生的身影都看不到。
.transition 0 * 40
.stage	* bgw_normal002a01_00.png 0 0 st_kei04a04.png 400
;（表情注意）
.message	1050	kei-107_01-0055	丂宨丂	「是不是觉得我很烦？」
.message	1060		丂峢丂	「嗯」
.transition 0 * 40
.stage	* bgw_normal002a01_00.png 0 0 st_kei05a07.png 400
;（表示タイミング，注意のこと。もう少し後で？）
.message	1070			咚！
.message	1080		丂峢丂	「……好痛」
.message	1090			胃部传来的绞痛，让我禁不住弯下了腰。
.message	1100	kei-107_01-0057	丂宨丂	「是不是该开玩笑的场合，请看下状况再说话」
.message	1110		丂峢丂	「既然知道我是在开玩笑就别打啊……」
.message	1120			我一边晃着的站起来一边说道。
.message	1130	kei-107_01-0059	丂宨丂	「我是很认真的，请不要开玩笑」
.message	1140	kei-107_01-0061	丂宨丂	「每天喊你起床，吵着让你去学校……哥哥，不觉得我很让你麻烦吗？」
.message	1150		丂峢丂	「就算你这么说……。我也已经习惯了啊」
.message	1160			从一方面来说说不定还是好事。
.message	1170		丂峢丂	「怎么突然想起说这种话」
.transition 0 * 40
.stage	* bgw_normal002a01_00.png 0 0 st_kei04a04.png 400
;（表示タイミング，注意のこと。この04も目線，下を向いてる印象を与える？つまり「睨みつけてる」にそぐわない表情になってるか？）
.message	1180			景瞪了我一眼。
.message	1190	kei-107_01-0063	丂宨丂	「我认真说的话不也完全听不进去吗，哥哥你」
.message	1200		丂峢丂	「没那回事啦」
.message	1210	kei-107_01-0065	丂宨丂	「一直都在忙着，不是完全都没听过我说话吗。以前，可不是这样的呢……」
.message	1220		丂峢丂	「以前和现在不一样吧。我们也都已经不是小毛孩了啊」
.transition 0 * 40
.stage	* bgw_normal002a01_00.png 0 0 st_kei04a05.png 400
.message	1230	kei-107_01-0067	丂宨丂	「那是……」
.message	1240		丂峢丂	「那是？」
.transition 0 * 40
.stage	* bgw_normal002a01_00.png 0 0 st_kei05a08.png 400
;（表情とポ～ズ注意）
;.stage	* bgw_normal002a01_00.png 0 0 st_kei04a08.png 400
.message	1250	kei-107_01-0069	丂宨丂	「为什么……。哥哥你长大太快了啊」
.transition 0 * 40
.stage	* bgw_normal002a01_00.png 0 0 st_kei05a03.png 400
;（表情とポ～ズ，注意）
;.stage	* bgw_normal002a01_00.png 0 0 st_kei04a05.png 400
.message	1260	kei-107_01-0071	丂宨丂	「虽然我不能说永远。但至少，我想稍微多些时间和你在一起」
.message	1270		丂峢丂	「不是在你身边这么近吗」
.transition 0 * 40
.stage	* bgw_normal002a01_00.png 0 0 st_kei01a03.png 380
;（ポ～ズと表情，注意のこと）
.message	1280	kei-107_01-0073	丂宨丂	「不是这方面的问题！」
.message	1290			景踏近了一步。
.transition 0 * 40
.stage	* bgw_normal002a01_00.png 0 0 st_kei02a05.png 380
;（ポ～ズと表情，注意のこと）
.message	1300	kei-107_01-0075	丂宨丂	「哥哥成为了漫画家……然后……，从很久以前就觉得离我越来越远。现在，已经……」
.message	1310			说到这。景闭上了嘴唇。
.message	1320			虽然等着她往下说下去，但看来已经不想再说什么了。
.message	1330		丂峢丂	「那是啊」
.message	1340		丂峢丂	「那是，你想错了啊」
.message	1350			景她一定，十分恐惧亲人们从自己的身边消失这样的事。
.message	1360			虽然这样也觉得理所当然……。
.message	1370		丂峢丂	「我不会那样简单就消失到哪去的。你想太多了啦」
.transition 0 * 40
.stage	* bgw_normal002a01_00.png 0 0 st_kei05a03.png 400
;（ここ，目閉じで？）
.message	1380	kei-107_01-0077	丂宨丂	「…………是呢。我也觉得大概如此」
.message	1390			景虽然点着头，但表情却完全没有想要认同的样子。
.transition 0 * 40
.stage	* bgw_normal002a01_00.png 0 0 st_kei05a02.png 400
;（表情，注意のこと）
.message	1400	kei-107_01-0079	丂宨丂	「我只是想说一次而已。仅仅，就此而已」
;（ここで，05a02？）
.message	1410	kei-107_01-0081	丂宨丂	「抱歉，早上起来就说些奇怪的话。如果能忘掉的话就好」
.message	1420		丂峢丂	「是吗」
.message	1430			虽然我也同样不想认同，但也不值得再把这个话题缠下去。
.message	1440			正准备催景开始走的时候──
.playSE2 *
.playBGM efBGM020.ogg
.screen * *
.transition 0 * 20
.stage	* ev01_078a_mugai_a.png 0 0
.message	1450	miy-107_01-0003	傒傗偙	「广野君，早上～好。啊，小景也在一起呢」
.message	1460			听到了可怕的不合时宜的明朗的声音。
.transition 0 * 20
.stage	* ev01_078a01.png 0 0
;（表示タイミング，注意のこと。差分もまだ来ていません）
.message	1470		丂峢丂	「你就是专挑这种时机登场的吗」
.transition 0 * 40
.stage	* ev01_078a02.png 0 0
.message	1480	miy-107_01-0005	傒傗偙	「诶？　有什么不好吗？」
.message	1490			出现的宫子左右看看我和景的脸色，浮起不可思议的表情。
.message	1500		丂峢丂	「倒不是有什么不好……怎么说好呢，对了。赶快给我前面走人」
.transition 0 * 40
.stage	* ev01_078a03.png 0 0
.message	1510	miy-107_01-0007	傒傗偙	「哇，还真是冷血的说法方式呢」
.message	1520		丂峢丂	「我本来就是很冷淡的人」
.transition 0 * 20
.stage	* ev01_079.png 0 0
.message	1530			唰。
.message	1540			突然，我的制服的袖子被人拉了起来。
.transition 0 * 20
.stage	* ev01_078b01.png 0 0
.message	1550		丂峢丂	「怎么了吗，景」
.message	1560			景像小孩子一般拉住了我的袖子。
.message	1570			她轻轻的摇了摇头，却没有做声。
.message	1580			虽然不明白是怎么回事，但空气中却飘溢着微妙的不协调感。
.message	1590			刚才还在疯狂吹着的风也瞬间风平浪静，只有让人觉得疼痛的静寂包裹耳朵。
.message	1600			怎么办才好……。
.message	1610			就连一直都吵吵嚷嚷的宫子，都发着呆不说一句话。
.transition 0 * 20
.stage	* ev01_078d03.png 0 0
;（手を離すタイミング，注意して）
.message	1620	kei-107_01-0083	丂宨丂	「……没什么」
.message	1630			在没有任何前兆的这么说了一句之后，景啪的松开了手。
.transition 0 * 40
.stage	* ev01_078d01.png 0 0
.message	1640	kei-107_01-0085	丂宨丂	「那个，宫村前辈」
.message	1650	miy-107_01-0009	傒傗偙	「喵？」
.message	1660			景没有介意宫子玩笑般的回答，而有着认真的表情。
.transition 0 * 20
.stage	* ev01_078c01.png 0 0
;（フェ～ドスピ～ドは40で？）
.message	1670	kei-107_01-0087	丂宨丂	「之前说了些无聊的话，十分抱歉」
.message	1680			景轻轻的低下了头。
.message	1690			……说什么呢？
.message	1700	miy-107_01-0011	傒傗偙	「无聊的話……？　发生过什么事情吗？」
.message	1710			这家伙不是一直都是逃课的吗。
.transition 0 * 20
.stage	* ev01_078d02.png 0 0
;（景の表情，宫子の表情の変化には注意して）
;（フェ～ドスピ～ドは40で？）
;（紘が景に顔を向けるタイミングを次とするなら，ここは切り出しでうまく処理すること）
.message	1720	kei-107_01-0089	丂宨丂	「什么事情──！」
.message	1730		丂峢丂	「景，大庭广众下不要随便发火」
.message	1740			我小声对她说了句悄悄话。
.transition 0 * 40
.stage	* ev01_078d03.png 0 0
.message	1750	kei-107_01-0091	丂宨丂	「……我，我知道的啦」
.message	1760			总算冷却下来的景瞪着宫子说道。
.transition 0 * 40
.stage	* ev01_078d04.png 0 0
;（この前の地文でこの表情を？）
.message	1770	kei-107_01-0093	丂宨丂	「嗯，今天就到此为止吧」
.message	1780	kei-107_01-0095	丂宨丂	「对于现在的我来说，只能这样而已」
.message	1790		丂峢丂	「喂，景。你真的有点奇怪啊」
.message	1800			到不如说是，感觉要上升到「可怕」的层次了。
.transition 0 * 40
.stage	* ev01_078d05.png 0 0
.message	1810	kei-107_01-0097	丂宨丂	「早就开始开始奇怪了……。没注意到的只有我和哥哥而已吧」
.message	1820			怎么看都不像是在开玩笑。
.message	1830			好象在我不知道的时间内发生过什么的样子……。
.transition 0 * 40
.stage	* ev01_078d04.png 0 0
;（ここ，d06表情でも？）
.message	1840	kei-107_01-0099	丂宨丂	「我，先走一步了呢」
.message	1850		丂峢丂	「诶？　啊啊，嗯」
.message	1860			景她稍稍浮起了一丝笑容。
.transition 0 * 40
.stage	* ev01_078d06.png 0 0
；（この表情，前の地文で？）
.message	1870	kei-107_01-0101	丂宨丂	「宫村前辈，先行失礼一步了」
.message	1880	miy-107_01-0013	傒傗偙	「啊，嗯。再见呢」
.message	1890			景她就那样小跑着离开了。
.transition 0 * 20
.stage	* ev01_080a01.png 0 0
.message	1900	miy-107_01-0015	傒傗偙	「真的有些奇怪呢，小景」
.message	1910			目送着景小小的背影，宫子呆呆的说道。
.transition 0 * 40
.stage	* ev01_080a02.png 0 0
.message	1920		丂峢丂	「就算是景，也轮不到你来说『奇怪』这两个字」
.transition 0 * 20
.stage	* ev01_080b01.png 0 0
;（笑顔にするタイミング，注意のこと。フェ～ドスピ～ドも）
.message	1930	miy-107_01-0017	傒傗偙	「我很普通啊～。大概，要比广野君你所想的正经的多哦」
;■笑顔
.transition 0 * 40
.stage	* ev01_080b02.png 0 0
.message	1940	miy-107_01-0019	傒傗偙	「广野君，没有重新考虑的想法吗？」
.message	1950		丂峢丂	「没可能啊」
.transition 0 * 20
.stage	* ev01_080c01.png 0 0
.message	1960	miy-107_01-0021	傒傗偙	「切～」
.message	1970			宫子她对着什么都没有的地面踢起来。
.transition 0 * 40
.stage	* ev01_080c02.png 0 0
.message	1980	miy-107_01-0023	傒傗偙	「但是呢」
.transition 0 * 20
.stage	* ev01_080d01.png 0 0
.message	1990		丂峢丂	「嗯？」
.message	2000	miy-107_01-0025	傒傗偙	「小景她应该是从最开始就明白的呢。但是呢，就是因为明白才会感到痛苦，觉得残酷」
.message	2010	miy-107_01-0027	傒傗偙	「白痴最好了啦。考虑不到什么麻烦的事情，幸幸福福的，毎天都可以保持微笑」
.transition 0 * 40
.stage	* ev01_080d02.png 0 0
.message	2020		丂峢丂	「从真正的白痴嘴里说出来很有说服力啊」
.transition 0 * 20
.stage	* ev01_080e01.png 0 0
.message	2030	miy-107_01-0029	傒傗偙	「还真是不饶人呢。对我说也就算了，对于其他人也说这么过分的话可不行哦」
.message	2040		丂峢丂	「我可没有见风使舵那种乖巧啊」
.transition 0 * 40
.stage	* ev01_080e02.png 0 0
.message	2050	miy-107_01-0031	傒傗偙	「真是不乖巧呢，广野君也是，我也是是大家也──」
.message	2060			宫子噗的笑了出来。
.message	2070			风又一次开始吹起。
.message	2080			一边按住被风吹散的头发，宫子她──
.transition 0 * 20
.stage	* ev01_080f01.png 0 0
;（ここの演出，注意。乱れる髪を押さえながら，，，なので，必要なら切り出しを。もしくは新規にＣＧを作ってもらうこと）
.message	2090	miy-107_01-0033	傒傗偙	「这阵风是从哪而来，又带来了什么呢……」
.transition 0 * 20
.stage	* ev01_080f_mugai_a.png 0 0
;（この切り出しはあんま良くないか？）
.message	2100			一边说着脑袋坏掉一样的话，一边呆呆的望向前方。
.message	2110			从正面吹拂而过的这冬日的风，也开始持久不断的跟宫子的头发玩耍起来。
.panel 0
.overlay * *
.playBGM *
.transition 0 * 10
.stage	* WHITE.png 0 0


;■背景：教室（冬，８時３０分
;■　　　　广野紘：制服（冬）
;■　　　　堤京介：制服（冬）
.playBGM efBGM010.ogg
.transition 1 fadeSide.png 10
.stage	* bgw_sch004m01_00.png 0 0
;.stage	* bgc_sch004a01_00.png 0 0
;☆（実際はモブが入る？，，，が，教室朝のモブ入りはないんだな，，，どうすっべか）
.panel 1
.message	2120			坐到座位上，自然而然的长出了一口气。
.message	2130		丂峢丂	「哈～，为什么一大早的就非得这么累啊」
.message	2140	kyo-107_01-0105	嫗丂夘	「哟，广野。精神不错嘛～」
.message	2150			京介像是刚刚到达教室的样子，提着提包走了过来。
.message	2160		丂峢丂	「吵死了，回去」
.transition 0 * 20
.stage	* ev01_098a01.png 0 0
;（ここからＣＧ流用でインさせてます。もちっと前からでもアリなのかもしれませんが，あえてここで）
.message	2170	kyo-107_01-0109	嫗丂夘	「怎么可能一大早就第一个回去嘛。我又不是宫村」
.message	2180		丂峢丂	「越来越让人累了，少提那个名字」
.message	2190			诶，稍微等下。
.message	2200		丂峢丂	「你这个语气貌似也是对宫──宫村很了解的样子啊」
.message	2210			之前，还无所谓的问出「在和宫村交往吗」那样的话，那只是在装糊涂吗？
.transition 0 * 40
.stage	* ev01_098a08.png 0 0
;（表情，注意して）
.message	2220	kyo-107_01-0115	嫗丂夘	「嗯嗯？　啊啊，算是吧。因为确实有些可爱的过分啊……」
.message	2230		丂峢丂	「？　声音有些奇怪啊，我说你。难道……」
.transition 0 * 40
.stage	* ev01_098b03.png 0 0
;（表情，注意して）
.message	2240	kyo-107_01-0119	嫗丂夘	「哎呀哎呀，年轻真实可怕啊」
.message	2250			这京介，那坏习惯也用到宫子身上了吗……。
;☆（aポ～ズのb03表情を用意してもらう？）
.message	2260	kyo-107_01-0121	嫗丂夘	「啊啊，但是放心啦。宫村她十分～难对付来着，我很快就放弃了啦」
.message	2270		丂峢丂	「为什么我会为这事放心啊？」
.message	2280	kyo-107_01-0126		京介只是会心一笑，却没有回答。
.message	2290		丂峢丂	「但是，还是真是没改变啊，我说你。稍微收敛一下如何」
.message	2300	kyo-107_01-0127	嫗丂夘	「你的话里还真是感觉不出友情啊」
.message	2310		丂峢丂	「没有的东西你感觉个什么啊你。说梦话也要有个程度」
.message	2320	kyo-107_01-0131	嫗丂夘	「心情还真不好啊。干吗啊，分明左拥右抱两朵鲜花来学校的，还摆出这种态度对女孩子不是很失礼吗？」
.message	2330		丂峢丂	「京介～！」
.message	2340			我站起身，抓起京介的胸襟。
.transition 0 * 40
.stage	* ev01_098a06.png 0 0
;（表情，注意して。さらにここ，切り出しを？）
.message	2350	kyo-107_01-0135	嫗丂夘	「干～嘛突然站起来啊」
.message	2360		丂峢丂	「既然看到了就给我打个招呼。我被夹在那两个人中间有多不爽你知道吗！」
.transition 0 * 40
.stage	* ev01_098a05.png 0 0
;（視線を横にそらしたものを？）
.message	2370	kyo-107_01-0139	嫗丂夘	「就算你这么说，完全没有能让第三者插得进去的氛围嘛。来来，你自己看」
.message	2380			说着，京介那起他自己爱用的那台摄影机，把液晶的显示屏对向这边。
.message	2390	kyo-107_01-0141	嫗丂夘	「从客观上看一下不就明白了吗。你们早陷入到自己的平行世界中去了啊」
.playSE kyousuke_camera.ogg f
;（一周しかさせてないのはワザとで）
.transition 0 * 20
.stage	* ev01_081.png 0 0
;（このＣＧからどこで通常ＣＧに切り替えるかは注意のこと）
.message	2400			显示屏清清楚楚显示出来的是我和景，以及宫子。
.message	2410		丂峢丂	「我说你，旁观不算你还摄影吗～！」
.message	2420	kyo-107_01-0145	嫗丂夘	「拿起镜头的我，就不再是你的友人堤京介。而且拼尽全力寻找好的画面的，单纯的摄影者哦」
.message	2430		丂峢丂	「白痴啊！」
.playSE *
.transition 1 fadeGray.png 40
.stage	* ev01_098a04.png 0 0
;.stage	* bgc_sch004a01_00.png 0 0
;（フェイドグレイで入ってますが，レイヤ～のみスクロ～ルで移動させたいです）
.message	2440			我从京介一把夺过摄影机。
.message	2450	kyo-107_01-0149	嫗丂夘	「啊啊，干嘛啊你」
.message	2460		丂峢丂	「胶卷没收。我说你考虑下情况再拍好吧」
.transition 0 * 40
.stage	* ev01_098a02.png 0 0
;（表情を変える必要はない？）
.message	2470	kyo-107_01-0153	嫗丂夘	「切～」
.message	2480			真不知道这家伙在想些什么。
.transition 0 * 40
.stage	* ev01_098a03.png 0 0
.message	2490	kyo-107_01-0155	嫗丂夘	「但是啊，偶尔这也是必要的哦。像这样，客观的认识自己。仅仅用自己的眼睛的话有很多东西会视而不见的呢」
.message	2500		丂峢丂	「少装伟大，白痴」
.message	2510			什么用自己的眼睛看不见的东西啊。
.message	2520			那种东西怎么可能会被随便就拍出来……。
.transition 0 * 40
.stage	* ev01_098b02.png 0 0
;（表情，注意して）
.message	2530	kyo-107_01-0159	嫗丂夘	「小看我的镜头的话可是会困扰的哦」
.message	2540			自信满满的京介这样说着……
.message	2550			我却…无法否定掉。
.panel 0
.playBGM *
.transition 0 * 10
.stage	* WHITE.png 0 0


;■背景：学園·廊下（冬，１１時
;■　　　　广野紘　　：制服（冬）
;■　　　　宫村宫子：制服（冬）
.transition 1 fadeSide.png 10
.stage	* bgw_sch002m11_01.png 0 0
;.stage	* bgc_sch002a01_01.png 0 0
;（実際はモブが入る？）
.panel 1
.message	2560			只用自己的眼睛看不到的东西。
.message	2570			看不到的东西…吗……。
.message	2580			那种东西有很多吧。
.message	2590			镜头中的我。
.message	2600			在那冬日的寒风中，看着宫子的我。
.message	2610			在课休时间，从厕所回来的途中自然而然的走向了D班的教室。
.message	2620			D班认识的人很有那么几个，并没有什么奇怪之处。
.message	2630			啊啊，不是这样的。
.message	2640			说什么借口呢。
.message	2650			我大概只是，不得不去确认一件事。
.message	2660			对于现在的我是必要的，并且去理解的事。
.message	2670			一眼不看擦身而过的同学们，直直的走向D班的教室。
.message	2680			并不想要做什么。
.message	2690			只是，我就那样──
.message	2700			推开了D班教室的门扉。
.message	2710		丂峢丂	「…………」
;★遠景ＣＧ　紘の視点，教室の扉から窓際の宫子
;★遠景ＣＧに小窓かぶせて，そこに宫子の顔ＵＰ入れるか
;ＵＰは立ち絵をカットして流用できるか
.transition 0 * 20
.stage	* ev01_082a01.png 0 0
;（ＣＧの表示タイミングには注意のこと）
.message	2720			虽然不知道她坐在哪，但还是很快就发现了她的身影。
.message	2730			和谁都没有谈天，而是用手支着脸颊而把视线投向窗外。
.message	2740			没有感觉到不可思议，没有感觉好像很寂寞。
.message	2750			就那样自然的坐在那里──在从窗外射进的日光中，呆呆的宫子，就好像一副美丽的画一样。
.message	2760			如果是我的父亲或者姐姐的话，看到这副光景也会自然的提起画笔的吧。
.transition 0 * 20
.stage	* ev01_082b01.png 0 0
;（表示のタイミング，注意のこと。フェ～ドスピ～ドは40でもいい？）
.message	2770			从教室走出来的女孩子，用觉得我可疑的目光看着我一眼。
.message	2780		丂峢丂	「哦，抱歉」
.message	2790			为了不妨碍那女孩子过路，我退后了一步。
.message	2800			当我的视线再次回到教室的时候，
.transition 0 * 20
.stage	* ev01_082c01.png 0 0
;（この前，必要なら切り出しを。女子学生との距離の演出には注意のこと）
.message	2810		丂峢丂	「…………」
.message	2820			宫子已经向我这边看过来了。
.message	2830			在她有些惊讶的脸上，嘴微微张开着。
.message	2840			那景色就忽然变成了漫画的样子。
.message	2850			教室里中的宫子和，门外的我。
.message	2860			虽然现实的距离并没有改变，但却觉得宫子比刚才要更加接近。
.message	2870			缠绕着的视线，涌上胸口的不知是什么的感情。
.playSE AT_chime.ogg f 0 *
.message	2880			铛～叮～铛～咚～。
.message	2890			虽然铃声已不合时宜的响起。
.message	2900			但是，我和宫子只是互相看着彼此。
;■表情変化
.transition 0 * 20
.stage	* ev01_082c02.png 0 0
;（ここはフェ～ドスピ～ドは20でいい？）
.message	2910			随后宫子的脸上，浮起一个温柔的笑容。
.message	2920			那种世界被漂白的感觉，瞬间在我的心中如裂开般一样扩散开来──
.panel 0
.playSE *
.transition 0 * 10
.stage	* WHITE.png 0 0


;■背景：教室（冬，１５時
;■　　　　广野紘：制服（冬·外出）
.playBGM efBGM012.ogg
.transition 1 fadeSide.png 10
.stage	* bgw_sch004m13_02.png 0 0
;.stage	* bgc_sch004a01_02.png 0 0
;（実際はモブが入る？）
.panel 1
.message	2930			拿起空空的提包站起身来。
.message	2940			京介他丢下要早去参加部团活动的话，连放学前的班会都没有听走逃掉了。
.message	2950			部团活动，好似很愉快的样子啊。
.message	2960			其他的同学们也都一一扬起和上课时不同的，充满活泼感的表情。
.message	2970			但对我来说，就算是放学，也完全没有解放的心情。
.message	2980			回到家等待我的也只有工作而已啊～。
.message	2990			……说起来我会有解放的一天吗？
.message	3000			虽然连载完成就可以自由，但可能的话还不想那么快就到迎来那一天。
.message	3010		丂峢丂	「哈～」
.message	3020			回去吧。
;■背景：学園·廊下
.transition 1 fadeSide.png 20
.stage	* bgc_sch002a01_02.png 0 0
;（ここはモブがなくてもよい？）
.message	3030			缓缓地在走廊上走着的时候。
.message	3040			从窗外传来十分有威势的口号声。
.message	3050			运动部的人还真是一直都很有精神啊。
.message	3060			那精神也希望稍微分我一点啊。
.message	3070		丂峢丂	「啊，对了」
.message	3080			我一下停住了脚步。
.message	3090			从今早来学校的时候感觉虽然有些含糊，但景的样子确实有些奇怪。
.message	3100			从几年前开始就微妙的经常脸红，平时很少有机会正面说下。
.message	3110			但是，再怎么说，我也是在学园内类似于景的保护者的存在……。
.message	3120			稍微去见下她也好吧？
.select 去看下景的样子:label1 就这样回去:label2
.label label1
.chain 107_02.sc
.label label2
;.set favMiyako = favMiyako + 1
.chain 107_03.sc

;◆選択肢
;■·景の様子を見に行く。
;→107_02へ
;■·そのまま帰る。
;→107_03へ　宫子+1

;.end
