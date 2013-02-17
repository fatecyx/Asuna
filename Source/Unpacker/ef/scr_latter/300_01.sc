.setGlobal EYE_SEQ_DEFAULT = 2



.if ef_321_01 == 1 ef_300_b1
.if ef_321_01 <= 0 ef_300_a1

.label ef_300_a1

.pragma disable_control


.transition 0 * 10
.stage	* WHITE.png 0 0
.wait 400
.transition 0 * 10
.stage	* ago_base_30001e.png 0 0
.panel 1
.message	100	chi-300_01-0003	@愮丂恞	「乌～鸦～哦　为何　哭泣～。乌鸦在　山～头～上～。因为～有　七～个　可爱的～孩子哟～」\v\a
.goto ef_300_c1
.end


.label ef_300_b1

.pragma enable_control

.transition 0 * 10
.stage	* WHITE.png 0 0
.wait 400
.transition 0 * 10
.stage	* ago_base_30001e.png 0 0
.panel 1
.message	100	chi-300_01-0003	@愮丂恞	「乌～鸦～哦　为何　哭泣～。乌鸦在　山～头～上～。因为～有　七～个　可爱的～孩子哟～」
.goto ef_300_c1
.end


.label ef_300_c1








.transition 0 * 10
.stage	* ago_base_30001d.png 0 0

.playBGM efBGM031.ogg

.pragma enable_control

.panel 1
.message	110			放学的路上，经过空无一人的车站时，听到了歌声。
.message	120			令人怀念的和风歌。
.message	130			…………。
.transition 0 * 20
.stage	* ago_base_30001c.png 0 0
.message	140			……也就是说，并不是空无一人的吧。
.message	150		楡丂帯	「好美的声音呢」
.transition 0 * 20
.stage	* ago_base_30001k.png 0 0
.message	160			尽量不让如星座般散落在地面上的石子发出声响。
.transition 0 * 20
.stage	* ago_base_30001i.png 0 0
.message	170			我轻轻地迈进车站内。

.playVoice *

.transition 0 * 20
.stage	* ago_base_30001j.png 0 0
.message	180			——在那里，我和她邂逅了。




.transition 0 * 15
.stage	* ago_base_30003f.png 0 0
.message	190			不……还是从故事的结尾开始说起吧。
.message	200			这是和结局对应着的故事。
.message	210			不连续地排列起来的记忆的故事。
.message	220			一部写错了的童话。
.transition 0 * 10
.stage	past_window.png BLACK.png 0 0
.message	230			如同被正确记录着一天又一天的日记切割得支离破碎后，重新组合起来的故事……。




.transition 0 * 10
.stage	* ago_base_30001f.png 0 0
.message	240	mid-300_01-0003	@儈僘僉	『你……后悔遇到她么？』


.message	250			我叙述完一切之后，电话那头的表妹这样问我。
.transition 0 * 20
.stage	* ago_base_30001h.png 0 0
.message	260			冬日的深夜里。
.message	270			我久久伫立在嗖嗖作响的冷风之中，那干冷的空气正一点点地从脚底带走我的体温。
.message	280			月色很美的夜晚。
.message	290			寂静得如同身处银色的盐之沙漠之中。

.transition 0 * 10

.stage	* ev03_001a.png 0 0
.message	300			这样静寥的夜晚，让人不禁产生“嗯，已经结束了呢”的感觉。
.transition 0 * 20
.stage	* ev03_003a03.png 0 0
.message	310	mid-300_01-0005	儈僘僉	「……不能告诉我吗？」
.message	320			因为我没有回答吧，表妹——羽山瑞希改口嘟哝道。
.transition 0 * 20
.stage	* ev03_002a01.png 0 0
.message	330		楡丂帯	「啊，不是……后悔？」
.message	340	mid-300_01-0007	儈僘僉	『是的，后悔』
.transition 0 * 20
.stage	* ev03_002a02.png 0 0
.message	350		楡丂帯	「稍微等一下」
.transition 0 * 20
.stage	* ev03_001a_mugai_a.png 0 0

.message	361			是这样么？我试着询问自己的内心。

.message	370			回想起和她在一起的那些日子。
.message	380			回想起和她的别离。
.transition 0 * 20
.stage	* ev03_002a01.png 0 0
.message	390		楡丂帯	「嗯，是后悔吧」
.message	400			我老实地回答道。
.message	410		楡丂帯	「“假如能够有更不同的邂逅”，“假如当时能做得更好一点”」
.message	420		楡丂帯	「“假如自己能有更强的能力”……之类的」
.transition 0 * 20
.stage	* ev03_002a03.png 0 0
.message	430		楡丂帯	「我不想……再经历那种后悔和痛心的感觉了」
.message	440	mid-300_01-0009	儈僘僉	『…………』
.transition 0 * 20
.stage	* ev03_003a01.png 0 0
.message	450	mid-300_01-0011	儈僘僉	「莲治，你在笑吧？」
.message	460		楡丂帯	『什么？』
.message	470	mid-300_01-0013	儈僘僉	「从声音里感觉得出来」
.message	480		楡丂帯	『……确实有后悔。但是从未有过那么幸福的时间』
.message	490			我老实答道。
.message	500			几乎是不假思索地回答出来。
.message	510	mid-300_01-0015	儈僘僉	「这样么？」


.transition 0 * 20
.stage	* ev03_003a05.png 0 0
.message	530	mid-300_01-0017	儈僘僉	「这样啊……大家都在努力呢」
.message	540		楡丂帯	『大家？』
.transition 0 * 20
.stage	* ev03_003a04.png 0 0
.message	550	mid-300_01-0019	儈僘僉	「呵呵。我自言自语而已」
.transition 0 * 40
.stage	* ev03_003a02.png 0 0
.message	560	mid-300_01-0021	儈僘僉	「已经很晚了，又要花电话费，就先挂断了哦」
.message	570	mid-300_01-0023	儈僘僉	「下次再来找你玩吧。替我向阿姨问好」
.transition 0 * 20
.stage	* ev03_002a01.png 0 0
.message	580		楡丂帯	「……谢谢了，瑞希」
.transition 0 * 20
.stage	* ev03_003a01.png 0 0
.message	590	mid-300_01-0025	儈僘僉	「诶？为什么要道谢呢？」
.transition 0 * 20
.stage	* ev03_002a04.png 0 0
.message	600		楡丂帯	「这通电话。你是在担心我吧」
.message	610			我苦笑着撇起嘴。
.message	620			一直以来都叽叽喳喳令人讨厌的表妹，从来没有表现出这样温柔的一面呢。
.transition 0 * 20
.stage	* ev03_003a05.png 0 0
.message	630	mid-300_01-0027	儈僘僉	「哈啊」
.transition 0 * 40
.stage	* ev03_003a04.png 0 0

.message	640	mid-321_01-0029	儈僘僉	「怎么可能嘛……晚安哦莲治」

.transition 0 * 20
.stage	* ev03_002a01.png 0 0
.message	650		楡丂帯	「晚安，瑞希」
.transition 0 * 20
.stage	* ev03_001b.png 0 0
.message	660			确认听到３下通话切断的声音后，我放下了话筒。
.message	670			月色柔美的夜晚。
.message	680		楡丂帯	「后悔什么的……是当然的……」
.transition 0 * 20
.stage	* ev03_254.png 0 0
.message	690			声音开始颤抖。
.message	700			感觉眼角和头脑有些发热。
.message	710			从今往后，也会一直后悔下去吧。
.message	720			完全没有睡意。
.message	730			身体已经冷透，想立刻躲进被窝停止这些想法。
.message	740			心里好疼，头脑好清醒。
.transition 0 * 20
.stage	* ev03_005.png 0 0
.message	750		楡丂帯	「…………」
.message	760			从口袋里拿出她交给我的记事本。
.message	770			这是在离别时得到的记事本。
.message	780			也是她宝贵的记忆。
.message	790			在月光下文字逐渐浮现出来。
.message	800			一段一段的回忆流淌而出。
.message	810			追寻着日记上的文字。
.message	820			即使不这么做，我也早已把它反复读过、记忆过了无数次——这个由我自己亲身体验过的故事。
.transition 0 * 20
.stage	* ev03_255.png 0 0
.message	830			开头的一页这样写着。
.message	840			用非常非常娟秀圆滑的字体写着。
.panel 1
.transition 0 * 10
.stage	* WHITE.png 0 0
.transition 0 * 5
.stage	* ev03_263.png 0 0

.message	850	chi-300_01-0005	@愮丂恞	『――由昨天的我，写给今天的我』\v\a
.wait 400

.panel 0
.transition 0 * 10
.stage	* WHITE.png 0 0
.playBGM *
.transition 0 * 10
.stage	* WHITE.png 0 0
.wait 100





.playBGM ef#01.ogg

.transition 0 * 10
.stage	* ev03_061c01_mugai_b2.png 0 0


.panel 1
.message	860			在站台上备置的长椅上，坐着一个少女。
.transition 0 * 20
.stage	* ev03_006a01.png 0 0
.message	870			那条长椅是我很喜欢的地方——虽然既没有留下漆得很漂亮的告示牌，也没有留下写着“占座”的标签。
.message	880			少女高高地昂着头，仰望着天空。
.message	890			空气很寒冷。
.message	900			少女保持着毫无防备把喉咙暴露在外的姿势，是不是沉浸在刚刚发射的航天飞机的余音里了呢，看起来就像是小鸡在等着喂食的样子。
.message	910			不，是没有机会出巢的雏鸟吗……。
.message	920		楡丂帯	「…………」


.message	930			我呆呆地凝视着少女，忽然间，产生了“不应该打扰到她”这样的心情。
.message	940			大概是因为这个景象太美了吧。
.message	960			我还在考虑着是不是要静静离开车站的时候……。


.transition 0 * 20
.stage	* ev03_006d01.png 0 0
.message	970			少女一心凝望着的到底是什么呢，这样想着，不由得顺着她的视线看去。
.transition 0 * 20
.stage	* bgw_sky001a01_02.png 0 0
.message	980			什么也没有。
.message	990			但是有天空在那里。
.message	1000			冬日的晚霞像是象征着寒冷一样传达着寒意。
.message	1010		楡丂帯	「……啊啊」
.message	1020			我想像这样发着呆也确实有其价值吧。
.message	1030			我从天空中移回视线。
.transition 0 * 20
.stage	* ev03_006b01.png 0 0
.message	1040	chi-300_01-0007	@愮丂恞	「…………」
.message	1050			不知什么时候开始，少女反过来正在盯着我看。

.message	1070			是患有睑腺炎吗。只用没被眼罩遮住的右眼看向我。

.message	1080			到了此时，我总算思考起接下来该怎么办的问题了。
.message	1090		楡丂帯	「这个车站不会有电车来的哦」
.message	1100	chi-300_01-0009	@愮丂恞	「诶？」
.message	1110		楡丂帯	「抱歉，没什么」
.message	1120			随口敷衍的一句话，却被她如此认真地回应了，我反射性地道了歉。
.message	1130			对话没有继续下去。
.message	1140			本来就没有可以继续下去的话题，这是理所当然的。
.message	1150			因为是对方先来的，应该离开的是我吧……我按照常理这样考虑。
.message	1160		楡丂帯	「我先走了」
.message	1170			举起右手轻轻挥了挥。

.message	1180	chi-300_01-0011	@愮丂恞	「……嗯」
.transition 0 * 20
.stage	* ev03_006c01.png 0 0
.message	1190			虽然还带着一脸茫然，少女也还是向我挥了挥她纤细的小手。
.transition 0 * 5
.stage	* WHITE.png 0 0
.message	1200			就这样，我们的第一次相遇结束了。


.message	1210			我和她的相遇，是在冬日。


.message	1220			那是一次不足４５秒的邂逅——。
.panel 0
.transition 0 * 10
.stage	* WHITE.png 0 0


.wait 100

.transition 0 * 7
.stage	* title_chap3.png 0 0
.message	999			\a　
.wait 500

.transition 0 * 7
.stage	* WHITE.png 0 0
.wait 300


.chain 301_01.sc
