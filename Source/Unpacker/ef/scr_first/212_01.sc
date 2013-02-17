; ファイル: 212_01.txt
;■＜２章：１２日目＞
;■背景：景自室（夏，６時
;■　　　　新藤景：制服（夏）
;■空
.transition 0 * 10
.stage	vista_window.png bgs_sky001a01_00.png 0 0
;（イベントＣＧを流用する場合は，ここ，景はパジャマかもしれんので注意して）
.panel 3
.message	100	kei-212_01-1003		今天也是晴空万里，早晨的空气也澄清无比呼吸舒畅。
.message	110	kei-212_01-1005		心情也阳光灿烂──却是不可能的。
;☆（ここ，ＣＧがない？流用できるものがないか探して）
.message	120	kei-212_01-1007		我离开窗边，坐到了电脑前。
.transition 0 * 20
.stage	vista_window.png ev02_096a01.png 0 0
.message	130	kei-212_01-0003	#丂宨丂	「……写些什么好呢」
.message	140	kei-212_01-1009		以前的话，早醒的早晨就会理所当然的自主练习。
.transition 0 * 20
.stage	* kei_vista_p.png 0 0
.message	150	kei-212_01-1011		当然，去学园之前会绕下远路，去叫醒某个懒虫。
.message	160	kei-212_01-1013		这两个习惯都已经从我的生活里消失一段日子了，但仍然不知道这时间该怎么用。
.transition 0 * 20
.stage	vista_window.png ev02_096a02.png 0 0
;（フェ～ドスピ～ドには注意して）
.message	170	kei-212_01-0005	#丂宨丂	「啊～，真是的！」
.message	180	kei-212_01-1015		又开始想起过去。
.message	190	kei-212_01-1017		分明决定了只看前方的，为什么又会这样。
.transition 0 * 20
.stage	vista_window.png ev02_096a03.png 0 0
.message	200	kei-212_01-0007	#丂宨丂	「现在的我能做到的，只有写邮件了啊」
.transition 0 * 20
.stage	vista_window.png ev02_096a03_mugai.png 0 0
;.stage	* kei_vista_q.png 0 0
.message	210	kei-212_01-1019		但是，写些什么好呢？
.message	220	kei-212_01-1021		对着连这样的我也喜欢着的妹妹。
.message	230	kei-212_01-1023		现在的我无论写些什么，感觉也只是会千寻让灰心而已吧。
.transition 0 * 20
.stage	vista_window.png ev02_096a03_mugai_close.png 0 0
.message	240	kei-212_01-0009	#丂宨丂	「呼……」
.transition 0 * 10
.stage	past_window.png bgs_sky001a01_00.png 0 0
.message	250	kei-212_01-1025		抱歉我是个没用的姐姐──
;.transition 1 fadeSide.png 10
;.stage	kei_window.png WHITE.png 0 0
.transition 0 * 10
.stage	* vista_white.png 0 0
.panel 0
;.transition 1 fadeSide.png 10
.transition 0 * 10
.stage	* WHITE.png 0 0


;■ここより京介視点
;■背景：通学路（夏，７時
;■　　　　堤京介：制服（夏）
;■　　　　新藤景：制服（夏）
.playBGM efBGM051.ogg
;.playBGM BGM054_sample.ogg
.screen sc_morning01.png sc_morning01.png
;.transition 1 fadeSide.png 10
.transition 0 * 10

;■御影チェック
;.stage	* bgs_normal019m01_00.png 0 0
.stage	* ev02_009b01.png 0 0


.panel 1
.message	260			啊啊～，完全迟到了。
.message	270			不不，距离上课还安全的很，但却绝对赶不上摄影开始了。
.message	280			鬼女化的导演的脸浮现在我眼前。
.message	290			不只导演，虽然摄影研究部的大家没有对回来的我抱什么反感，但该生气的时候还不介意就不太好了。
.message	300			……等下？
.message	310		嫗丂夘	「反正迟到了，慢走快走不都一样……」
.message	320		嫗丂夘	「肯定不行啊」
.message	330			啊啊啊，真是不爽。
.transition 0 * 20
.stage	* ev02_097.png 0 0
;（通常背景からの移行には注意して）
.message	340		嫗丂夘	「……嗯？」
.message	350	kei-212_01-0011	丂宨丂	「啊」
.message	360			当在上学路上刚刚看到她的脸的同时──
.message	370			迟到的郁闷便完全飞走了。
;■驚き
.overlay * or_kei00a.png
.transition 0 * 20
.stage	* ev02_097_mugai.png 0 0 st_kei05b08.png 400
;（この前，切り出しでせめるか？さらに，もっと「驚き」系のを？07a03とか？）
.message	380	kei-212_01-0013	丂宨丂	「堤前辈……」
.message	390		嫗丂夘	「新藤，真够早的啊」
;■不機嫌
.transition 0 * 40
.stage	* ev02_097_mugai.png 0 0 st_kei04b04.png 400
.message	400	kei-212_01-0015	丂宨丂	「稍微有些早起罢了。在家待着也无事可做……」
.message	410			和平时有些不同，哪儿有些不对劲。
.message	420		嫗丂夘	「怎么了吗？」
.transition 0 * 40
.stage	* ev02_097_mugai.png 0 0 st_kei04b05.png 400
;（この表情，この後で？）
.message	430	kei-212_01-0017	丂宨丂	「没怎么啊」
.message	440	kei-212_01-0019	丂宨丂	「到是前辈，不着急吗？」
.message	450		嫗丂夘	「啊～，对了」
.message	460		嫗丂夘	「哎呀，摄影研究部的部长兼导演的姐姐可是个不逊于你的S啊，迟到的话就要上鞭子了啊」
.transition 0 * 40
.stage	* ev02_097_mugai.png 0 0 st_kei04b04_close.png 400
.message	470	kei-212_01-0021	丂宨丂	「鞭子也就算了……大清早就想跟我吵架吗？」
.message	480		嫗丂夘	「不不，岂敢岂敢」
.message	490			我把头左右摇到要掉下来。
;■嫌味
.transition 0 * 40
.stage	* ev02_097_mugai.png 0 0 st_kei04b04.png 400
;（表情注意して）
.message	500	kei-212_01-0023	丂宨丂	「前辈还真是精神呢。只要拍电影就OK真是单纯的人」
.message	510		嫗丂夘	「难道说，你也想跟我吵架吗？」
.transition 0 * 40
.stage	* ev02_097_mugai.png 0 0 st_kei04b05.png 400
;（表情注意して）
.message	520	kei-212_01-0025	丂宨丂	「是又如何？」
.message	530		嫗丂夘	「我早已决定和女生作对手的话只在床上──」

;■御影チェック
;■　これでどうだ？
.playSE kei_attack_b.ogg f 0 *
.shakeScreen	R	100	100

;（画面揺らす？もしくはイベントＣＧの流用を。切り出しなんか使って）
.message	540		嫗丂夘	「咕啊！」
.message	550			新藤华丽的炸裂直击。

;■御影チェック
;■　景の表情を早めに動かしたいので下の台詞とあわせます。
;.message	560		嫗丂夘	「ぐうぅ……」

.transition 0 * 40
.stage	* ev02_097_mugai.png 0 0 st_kei06b05.png 400
;（身体の向き，変えさせてます。気を付けて）
.message	570	kei-212_01-0027	丂宨丂	「不要说些让清爽的早晨失去气氛的话」

;■御影チェック
;.message	580		嫗丂夘	「すいません……」
.message	580		嫗丂夘	「呜……十分抱歉……」

.message	590			不知为何，突然觉得这种无聊的对手戏十分怀念。
.message	600			从摄影中断开始还不到三天啊。
.transition 0 * 40
.stage	* ev02_097_mugai.png 0 0 st_kei06b01.png 400
;（表情注意して）
.message	610	kei-212_01-0029	丂宨丂	「……干吗啊，那奇怪的表情」
.message	620		嫗丂夘	「真过分啊，就算如此我还是很有自信的啊～」
.transition 0 * 40
.stage	* ev02_097_mugai.png 0 0 st_kei06b03.png 400
.message	630	kei-212_01-0031	丂宨丂	「没人指那方面」
.transition 0 * 40
.stage	* ev02_097_mugai.png 0 0 st_kei07b01.png 400
;（06b04でも？）
.message	640	kei-212_01-0033	丂宨丂	「……啊～，够了够了。和你说话头都疼了」
.message	650			唔哇，完全被讨厌了。
.message	660			虽然被讨厌了，但果然和新藤说话十分愉快。
.message	670			会觉得怎样都会愉快──这样子，真的很少见。
.message	680			虽然和至今为止交往过的女孩子们，也都十分愉快的在一起过……。
.message	690		嫗丂夘	「小景」
.transition 0 * 40
.stage	* ev02_097_mugai.png 0 0 st_kei01b06.png 380
;（表情注意して。もっと冷めたのを？）
.message	700	kei-212_01-0035	丂宨丂	「别叫我小景」
.message	710			虽然发着牢骚，新藤还是在等我的下一句话。
.message	720		嫗丂夘	「抱住你可以吗？」
;■笑顔
.transition 0 * 40
.stage	* ev02_097_mugai.png 0 0 st_kei03b02.png 380
.message	730	kei-212_01-0037	丂宨丂	「可以哦」
.message	740		嫗丂夘	「诶？　真的吗？」
.message	750			这还真是让人意外的反应。
.message	760	kei-212_01-0039	丂宨丂	「如果等下，抱着石头永远地沉入海底也无所谓的话」
.message	770		嫗丂夘	「我得意忘形了，十分抱歉十分抱歉」
.message	780			再怎么说仅仅抱一下就归于极乐的话，有点划不来。
.transition 0 * 40
.stage	* ev02_097_mugai.png 0 0 st_kei03b06.png 380
.message	790	kei-212_01-0041	丂宨丂	「好了啦快走吧你。不想再被赶出去吧？」
.message	800		嫗丂夘	「…………」
.transition 0 * 40
.stage	* ev02_097_mugai.png 0 0 st_kei04b01.png 400
;（目線，注意して）
.message	810	kei-212_01-0043	丂宨丂	「走吧」
;■笑顔
.transition 0 * 40
.stage	* ev02_097_mugai.png 0 0 st_kei04b02_close.png 400
;（表情には注意して。目つむり，変なようなら修正を）
.message	820	kei-212_01-0045	丂宨丂	「我没事的」
.message	830			看到那样的笑容，我反而更加挪不开脚步。
.transition 0 * 40
.stage	* ev02_097_mugai.png 0 0 st_kei04b02.png 400
.message	840	kei-212_01-0047	丂宨丂	「前辈所回去的地方，有需要你的人在不是吗？」
.message	850		嫗丂夘	「……嗯」
.message	860			我仅仅点了点头。
.message	870			别的我什么做不到。
.panel 0
.overlay * *
.screen * *
.playBGM *
.transition 0 * 10
.stage	* WHITE.png 0 0


;■景視点
;■背景：体育館（夏，１１時
;■　　　　新藤景　：制服（夏）
;■　　　　雨宫优子：私服（夏）
;.playSE kei_dribble_twice.ogg f 0 *
;.transition 0 * 10
.transition 14 * 12
.stage	vista_window.png ev02_002c01_mugai_a.png 0 0
.playSE kei_dribble_twice.ogg f 0 *
.hscroll	800	15
.endScroll f
;（ここ，スクロ～ルさせながらメッセ～ジをクリックできるように？さらにウインドウ黒をくっつけてインさせるか？）
;（もちっとスクロ～ルはやく？＆切り出しで，景の片手は画面外に出るように？）
;.stage	* bgc_sch006a01_01.png 0 0
;（イベントＣＧの流用も考えて）
.panel 3
.message	880	kei-212_01-1027		咚，咚的运了两下球。
.transition 0 * 20
.stage	* ev02_002c01_mugai.png 0 0
.message	890	kei-212_01-1029		这是射篮前我的习惯，也是我的仪式。
.message	900	kei-212_01-1031		如果不这样就射篮的话，篮球连在篮框上都不会。
.transition 1 fadeGray.png 40
.stage	* ev02_098.png 0 0
.message	910	kei-212_01-1033		从手指到脚尖，控制全身的神经集中起来进入射篮状态。
.playSE kei_shoot.ogg f 0 *
.transition 1 fadeGray.png 40
.stage	* ev02_099.png 0 0
.message	920			唰……。
.transition 1 fadeGray.png 40
.stage	* ev02_100b01.png 0 0
;（a01はここでは使ってません）
.message	930	kei-212_01-0049	#丂宨丂	「不行」
.playSE kei_board.ogg f 0 *
.transition 1 fadeGray.png 40
.stage	* ev02_100c01.png 0 0
.message	940	kei-212_01-1035		在低声嘟囔的同时，篮球撞到了篮板弹了回来，然后滚向别的方向。
.playSE kei_ball_korogaru.ogg f 0 *
.transition 0 * 20
.stage	* ev01_203_mugai.png 0 0
;.transition 1 fadeGray.png 40
;.stage	* ev02_100d01.png 0 0
.message	950	kei-212_01-1037		只进一次也好啊，但看来是被篮球女神讨厌了呢。
.transition 0 * 20
.stage	* ev02_101a01.png 0 0
;（ここ，イベントＣＧの流用を，，，？景がリングを見上げてるやつか？ただ，時間帯は昼なので注意されたし，流用する場合）
.message	960	kei-212_01-0051	#丂宨丂	「我现在又，怎么样呢……」
.message	970	kei-212_01-1039		我现在还爱着篮球的女神吗。
.transition 0 * 20
.stage	* ev02_101b01.png 0 0
;（优子のインの仕方，注意して。普通に亡霊のようにフェ～ドでインしてますが·笑）

;■御影チェック
;.message	980	yuk-212_01-0003	桪丂巕	「あらら，惜しかったですね」
.message	980	yuk-212_01-0003	@桪丂巕	「啊啦啦，真可惜呢」

.message	990	kei-212_01-0053	#丂宨丂	「──！」
.transition 0 * 40
.stage	* ev02_101c01.png 0 0
;（フェ～ドスピ～ドには注意して。20で？）
.message	1000	kei-212_01-1041		我迅速地转过身，面对背后出现的人物。
.message	1010	kei-212_01-0055	#丂宨丂	「……啊」
.playBGM efBGM017_2.ogg
.message	1020	kei-212_01-0057	#丂宨丂	「雨宫优子……小姐？」
.transition 0 * 40
.stage	* ev02_101c03.png 0 0
.message	1030	yuk-212_01-0005	桪丂巕	「虽然只是见过一面，但竟然记着我呢」
.message	1040	kei-212_01-1043		说着，她高兴地笑起来。
.message	1050	kei-212_01-0059	#丂宨丂	「分明是夏天，还穿着这么热的衣服的人当然不会简单忘掉」
.message	1060	kei-212_01-1045		而且，还是因为这个人身上有种微妙的气氛吧。
.transition 0 * 40
.stage	* ev02_101c01.png 0 0
;（表情，注意して）
.message	1070	yuk-212_01-0007	桪丂巕	「很热……吗？」
.message	1080	kei-212_01-0061	#丂宨丂	「仅仅看着都要出汗了。你也不是什么修女之类的吧」
.transition 0 * 40
.stage	* ev02_101c02.png 0 0
.message	1090	yuk-212_01-0009	桪丂巕	「嗯，善良的一般市民哦」
.message	1100	kei-212_01-0063	#丂宨丂	「虽然我觉得修女也是善良的一般市民……但为什么要穿成这样？」
.message	1110	kei-212_01-1047		细致到连手套都戴着，不得不感到奇怪。
.transition 0 * 40
.stage	* ev02_101d01.png 0 0
;.stage	* ev02_101c03.png 0 0
.message	1120	yuk-212_01-0011	桪丂巕	「嘛不也好吗。你看，不是很有神秘的气氛吗？」
.transition 0 * 40
.stage	* ev02_101e01.png 0 0
.message	1130	kei-212_01-0065	#丂宨丂	「你演戏吗！」


;■御影チェック
;■　これ，くどいなぁ……。
;.transition 0 * 20
;.stage	* kei_vista_d.png 0 0


.message	1140	kei-212_01-1049		又出现一个让我头疼的角色……。
;.transition 0 * 40
.transition 0 * 20
.stage	* ev02_101c04.png 0 0
.message	1150	yuk-212_01-0013	桪丂巕	「这个暂且不提。逃课可是不行的哦」
.message	1160	kei-212_01-0067	#丂宨丂	「我可不想让不法侵入的外人说」
.transition 0 * 40
.stage	* ev02_101c01.png 0 0
;（表情，注意して。ここで変える必要はない？）
.message	1170	yuk-212_01-0015	桪丂巕	「我也不是外人哦。再怎么说，我也曾经是这里的学生过呢」
.message	1180	kei-212_01-0069	#丂宨丂	「诶，音羽的OB吗？」
.transition 0 * 40
.stage	* ev02_101c02.png 0 0
;（c04表情で？）
.message	1190	yuk-212_01-0017	桪丂巕	「要说的话应该是OG吧」
.message	1200	kei-212_01-0071	#丂宨丂	「真，真罗嗦呢。稍微失误一下而已啊」
.message	1210	kei-212_01-1051		不要在小事情挑毛病好吧。
.transition 0 * 40
.stage	* ev02_101c03.png 0 0
.message	1220	yuk-212_01-0019	桪丂巕	「嘛，实际上发生了不少事……没能毕业而已。和你的哥哥是同样的立场呢」
.message	1230	kei-212_01-1053		说着，雨宫优子浮起一个淡淡的微笑。
.message	1240	kei-212_01-0073	#丂宨丂	「哥哥，又不是我真正的哥哥」
.message	1250	yuk-212_01-0021	桪丂巕	「你还真是有趣的人呢」
.message	1260	kei-212_01-0075	#丂宨丂	「你很烦诶」
.message	1270	kei-212_01-1055		不知为何处于被动让我有些不快……。
.transition 0 * 40
.stage	* ev02_101c02.png 0 0
.message	1280	yuk-212_01-0023	桪丂巕	「你和广野先生还有堤先生还有宫子，在一起还真是一个比一个有趣呢」
.message	1290	kei-212_01-1057		这个人和宫村前辈也认识的吗。
.transition 0 * 40
.stage	* ev02_101c01.png 0 0
.message	1300	yuk-212_01-0025	桪丂巕	「这个学园，是不是开设了什么特殊的课程啊？」
.transition 0 * 40
.stage	* ev02_101c03.png 0 0
;（表情，注意して）
.message	1310	yuk-212_01-0027	桪丂巕	「能够如此量产奇怪的人，有些不寻常呢。是不是有什么隐情呢」
.message	1320	kei-212_01-0077	#丂宨丂	「你不也曾经是这里的学生吗！」
.message	1330	kei-212_01-1059		这个也是那个也是，都喜欢看我生气取乐吗。
.transition 0 * 40
.stage	* ev02_101c01.png 0 0
;（表情，注意して）
.message	1340	yuk-212_01-0029	桪丂巕	「新藤小姐」
.message	1350	kei-212_01-0079	#丂宨丂	「干吗」
.message	1360	kei-212_01-1061		说起来，这个人到底是来干吗的？
.message	1370	yuk-212_01-0031	桪丂巕	「你明白你的射篮为什么不会进吗？」
.message	1380	kei-212_01-0081	#丂宨丂	「……不是很明显吗」
.message	1390	kei-212_01-0083	#丂宨丂	「因为我很差啊」
.message	1400	yuk-212_01-0033	桪丂巕	「原来如此，你这么想的吧」
.message	1410	kei-212_01-1063		嘲笑我的口气。
.message	1420	yuk-212_01-0035	桪丂巕	「虽然这个理由也有，但大概不太对呢」
.message	1430	kei-212_01-0085	#丂宨丂	「你知道什么啊你」
.transition 0 * 40
.stage	* ev02_101c02.png 0 0
;（ここ，04表情を？）
.message	1440	yuk-212_01-0037	桪丂巕	「新藤小姐，你呢……」
.transition 0 * 20
.stage	* ev02_102.png 0 0
.message	1450	kei-212_01-1065		雨宫优子说着捡起了滚落在地上的篮球。
.transition 0 * 20
.stage	* ev02_103a01_kei_a.png 0 75
.message	1460	kei-212_01-1067		然后，摆出一个很明显的外行人的姿势。
;■軽く
.playBGM *
.transition 0 * 40
.stage	* ev02_103b01_kei_a.png 0 75
.vscroll	0	-5
.endScroll f
;（フェ～ドスピ～ドには注意して）
.message	1470	yuk-212_01-0039	桪丂巕	「哟～咻……」
.message	1480	kei-212_01-1069		随着奇怪的运劲姿势投出了球。
.message	1490	kei-212_01-0087	#丂宨丂	「……啊」
;（イベントＣＧの流用を？ボ～ルのアップのやつ）
.message	1500	kei-212_01-1071		虽然姿势乱的可以，但是──
.playSE kei_goal.ogg f 0 *
.transition 0 * 40
.stage	* ev02_103c01_kei_a.png 0 0
;.vscroll	75	5
;.endScroll f
;（スクロ～ルさせて下に戻す？それとも普通にフェ～ドで？）
;（常道から，表示位置をずらしてます）
.message	1510	kei-212_01-1073		随着轻轻一响，篮球钻过了篮圈。
;■笑顔
.message	1520	yuk-212_01-0041	桪丂巕	「啊啦，意外很容易进呢」
.message	1530	kei-212_01-0089	#丂宨丂	「想说什么就直说好吧」
.transition 0 * 20
.stage	* ev02_102.png 0 0
;（イベントＣＧの流用を？优子がボ～ル拾うやつ）
.message	1540	yuk-212_01-0043	桪丂巕	「你呢」

;■御影チェック
;■　絵があるから解説はいらないな。
;.message	1550	kei-212_01-1075		雨宫优子はゴ～ル下に歩いていって，またボ～ルを手に取る。

.transition 0 * 20
.stage	* ev02_104a01_kei_a.png 0 0
.message	1560	yuk-212_01-0045	桪丂巕	「在害怕自己会投不进呢」
.message	1570	kei-212_01-0091	#丂宨丂	「我不想听这种无聊的精神论」
.message	1580	yuk-212_01-0047	桪丂巕	「但是这是事实」
.playBGM efBGM023.ogg
.message	1590	kei-212_01-1077		啪，我清楚的听到好似什么断裂的声音。
.message	1600	kei-212_01-1079		胸口一点一点地燥热起来。
;■真剣
.transition 0 * 20
.stage	* ev02_104a02_kei_a.png 0 0
;（フェ～ドスピ～ドは40で？）
.message	1610	yuk-212_01-0049	桪丂巕	「你曾经受过一次伤害。所以，害怕再次受伤」
.message	1620	yuk-212_01-0051	桪丂巕	「害怕着得不到想要的东西，就算现在有想要追求的东西也畏惧不安」
.message	1630	kei-212_01-0093	#丂宨丂	「你……」
.message	1640	kei-212_01-1081		仅仅见过两面的这个怪女人……。
.message	1650	yuk-212_01-0053	桪丂巕	「你不承认自己是在停滞不前，不承认自己是在恐惧。不是吗？」
.message	1660	kei-212_01-0095	#丂宨丂	「像你这样的……」
.transition 0 * 20
.stage	* ev02_104a03_kei_a.png 0 0
.message	1670	yuk-212_01-0055	桪丂巕	「从头再来，谁都可以轻易的说出来」
;.transition 0 * 20
;.stage	* ev02_104a02_mugai.png 0 0
;.stage	* kei_vista_e.png 0 0
.message	1680	yuk-212_01-0057	桪丂巕	「新藤景小姐，而你却只是在一边原地踏步」
.message	1690	yuk-212_01-0059	桪丂巕	「一边希望什么时候有谁能够拉着你到哪里去」
.transition 0 * 40
.stage	* ev02_104b01_kei_a.png 0 0
.message	1700	kei-212_01-1083		雨宫优子迅速的甩过手，把篮球传给我了。
.playSE kei_ball_ukeru.ogg f 0 *
.transition 0 * 20
.stage	* ev02_105a01.png 0 0
.message	1710	kei-212_01-0097	#丂宨丂	「……！」
.message	1720	kei-212_01-1085		啪，随着尖锐的声音我接住了球。
;■挑発
.transition 0 * 40
.stage	* ev02_105b01.png 0 0
.message	1730	yuk-212_01-0061	桪丂巕	「少撒娇了，大小姐」
.message	1740	kei-212_01-1087		好似快要炸裂的感觉。
.transition 0 * 40
.stage	* ev02_105c01.png 0 0
.message	1750	kei-212_01-1089		我咬住嘴唇瞪大眼睛。
;■画面黒
.message	1760	kei-212_01-0099	#丂宨丂	「……」
.message	1770	kei-212_01-0101	#丂宨丂	「…………」
;■声にならない怒り
.message	1780	kei-212_01-0103	#丂宨丂	「……………………！」
.transition 0 * 20
.stage	* ev02_105c01_mugai.png 0 0
;.stage	* kei_vista_f.png 0 0
.message	1790	kei-212_01-0105	#丂宨丂	「少给我自说自话！」
.playSE kei_ball_ban.ogg f 0 *
.transition 0 * 40
.stage	* kei_vista_g.png 0 0
.message	1800	kei-212_01-1091		随着怒气爆发扔下篮球，睁开眼睛时──
.playBGM *
.transition 0 * 20
.stage	* ev02_106a01.png 0 0
;（インのタイミング，注意して）
.message	1810	kei-212_01-0107	#丂宨丂	「……诶？」
.message	1820	kei-212_01-1093		已经没有一个人了。
.message	1830	kei-212_01-1095		只有篮球孤单在地板上滚动着。
.message	1840	kei-212_01-0109	#丂宨丂	「怎，怎么回事？」
.message	1850	kei-212_01-1097		当然，也没有人回答我的问题。
.transition 0 * 20
.stage	* ev02_106b01.png 0 0
;（表示タイミング，注意して）
.message	1860	kei-212_01-1099		到底发生了什么完全理解不能──
.message	1870	kei-212_01-1101		但是，有一点可以确认。
.message	1880	kei-212_01-1103		雨宫优子把真实清楚的摆了出来。
.message	1890	kei-212_01-1105		分明对我的事应该一无所知的那个女人──
.message	1900	kei-212_01-1107		脑中剧烈的感情汹涌着，拍打着。
.message	1910	kei-212_01-1109		并不仅仅是生雨宫优子的气而已。
.transition 0 * 10
.stage	past_window.png ev02_106b01.png 0 0
.message	1920	kei-212_01-1111		而是对于将真实深深埋下的自己，被那种女人指指点点却什么作不到的自己无比怨恨。
;.transition 1 fadeSide.png 10
;.stage	kei_window.png WHITE.png 0 0
.transition 0 * 10
.stage	* vista_white.png 0 0
.panel 0
;.transition 1 fadeSide.png 10
.transition 0 * 10
.stage	* WHITE.png 0 0


;■京介視点
;■背景：屋上（夏，１３時
;■　　　　堤京介　　：制服（夏）
;■　　　　宫村宫子：制服（夏）
;■　　　　新藤景　　：制服（夏）
.playBGM efBGM029.ogg
.transition 1 fadeSide.png 10
.stage	* ev02_107a01.png 0 0
;（インのタイミングは注意して）
;.stage	* bgs_sch007a01_01.png 0 0
.panel 1
.message	1930	miy-212_01-0003	傒傗偙	「堤～堤」
.message	1940		嫗丂夘	「…………」
.message	1950			拿着火腿三明治的手停了下来。
.message	1960			偶尔打算体验下孤独的心情就来这个吗。
.message	1970	miy-212_01-0005	傒傗偙	「怎么，一个人吃午饭？　真寂寞啊」
.message	1980	miy-212_01-0007	傒傗偙	「难道说没有朋友吗？」
.message	1990		嫗丂夘	「怎么可能」
.message	2000			朋友的话不论年纪还是性别，我都有很多。
.message	2010			宫村知道还问这种问题还真是不识相啊。
.transition 0 * 40
.stage	* ev02_107a02.png 0 0
.message	2020		嫗丂夘	「找我有事吗？」
.message	2030	miy-212_01-0009	傒傗偙	「啊，对了」
.message	2040	miy-212_01-0011	傒傗偙	「刚才呢，摄影研究部的人来我们教室了哦。好像是找堤堤有事呢。虽然满漂亮的但很严厉的样子」
.message	2050		嫗丂夘	「啊啊，那是那个恶鬼导演嘛」
.message	2060	miy-212_01-0013	傒傗偙	「好像很生气的样子，难道说传染性病给人家了？」
.transition 0 * 40
.stage	* ev02_107b01.png 0 0
.message	2070		嫗丂夘	「少提性病！」
.message	2080	miy-212_01-0015	傒傗偙	「那个人不是堤堤以前的女朋友吗？　是你的话，分手也会去性骚扰之类的吧」
.message	2090		嫗丂夘	「我什么都没做」
.message	2100			我的主义是对于分手的女人绝对再不碰一根指头。
.message	2110			再接触的话，生出依恋和后悔就可怕了。
.message	2120		嫗丂夘	「现在仅仅是怠工没去摄影而已」
.transition 0 * 40
.stage	* ev02_107a03.png 0 0
.message	2130	miy-212_01-0017	傒傗偙	「……你在想什么呢？」
.message	2140			宫村会疑惑也是理所当然的。
.message	2150			我也觉得自己干什么都傻傻的。
.transition 0 * 40
.stage	* ev02_107a04.png 0 0
.message	2160		嫗丂夘	「我呢，从小的时候就十分想要拍电影」
.message	2170	miy-212_01-0019	傒傗偙	「嗯？」
.message	2180			契机是和母亲一起最后的时间看的那段影像。
.message	2190			然后，就自己下定决心，把拍摄电影作为唯一的梦想追寻下去。
.message	2200		嫗丂夘	「我只想要拍摄电影而已。仅仅把这个认真的作下去，别的事情随便就好」
.message	2210			所以，女朋友都没有长久的交往下去。
.transition 0 * 40
.stage	* ev02_107c01.png 0 0
.message	2220	miy-212_01-0021	傒傗偙	「唔～嗯……？」
.message	2230		嫗丂夘	「不作的彻底的话，就不可能实在梦想」
.message	2240		嫗丂夘	「不，简单就能实现的梦想我也根本不需要」
.transition 0 * 40
.stage	* ev02_107d01.png 0 0
.message	2250	miy-212_01-0023	傒傗偙	「唔唔唔……？」
.transition 0 * 40
.stage	* ev02_107b02.png 0 0
.message	2260		嫗丂夘	「我说，你别用那种奇怪的回应好吧」
;.transition 0 * 40
;.stage	* ev02_107a05.png 0 0
;（表情変化とポ～ズ変えのイン，注意して）
.message	2270	miy-212_01-0025	傒傗偙	「明白」
.message	2280			宫村虽然回答仍是不一为然，但表情却认真起来。
.message	2290			虽然说不定我找错了说话对象，但宫村也有可能意外听的很认真。
.transition 0 * 40
.stage	* ev02_107a05.png 0 0
;（京介の表情変化，注意して）
.message	2300	miy-212_01-0027	傒傗偙	「不需要简单就可以实现的梦想。然后呢？」
.message	2310		嫗丂夘	「觉得这样就够了。但最近我的确信却开始摇摆不定」
.transition 0 * 40
.stage	* ev02_107a06.png 0 0
;（宫子の表情変化，注意して）
.message	2320	miy-212_01-0029	傒傗偙	「只想追寻梦想并不是什么坏事啊。嘛，只是」
.message	2330		嫗丂夘	「只是？」
.message	2340	miy-212_01-0031	傒傗偙	「固执认为只追寻着梦想就可以了什么的，这个并不是绝对的东西啊」
.message	2350	miy-212_01-0033	傒傗偙	「人的心情是会改变的呢」
.transition 0 * 40
.stage	* ev02_107b03.png 0 0
.message	2360		嫗丂夘	「那说法好像你什么都懂似的」
.message	2370	miy-212_01-0035	傒傗偙	「不知为什么，反正就是知道啦」
.message	2380			在倾注的夏日的阳光里，宫村微笑起来。
.message	2390	miy-212_01-0037	傒傗偙	「因为只重视工作的纮君也选择了我」
.message	2400		嫗丂夘	「是啊……」
.message	2410	miy-212_01-0039	傒傗偙	「堤君。堤君所追求的东西，究竟是什么？」
.message	2420			我所追求的东西……。
.message	2430			这再明显不过。
.message	2440		嫗丂夘	「当然是拍电影」
.message	2450		嫗丂夘	「还有……」
.playSE kei_tobira_ban.ogg f 0 *
.playBGM * * 0
.transition 0 * 20
.stage	* ev02_108a01.png 0 0
.message	2460	kei-212_01-0111	丂宨丂	「找到了～！！」
.message	2470			跟随门被粗暴撞开的声音而来的高鸣的怒吼。
.transition 0 * 20
.stage	* ev02_107e01.png 0 0
;（このＣＧを挿む必要性があるかどうか，注意して）
.message	2480	miy-212_01-0041	傒傗偙	「小，小景？」
.message	2490			比起我来宫村貌似更吃惊。
;.transition 0 * 20
;.stage	* ev02_108a01.png 0 0
;（移行，注意して）
.message	2500	kei-212_01-0113	丂宨丂	「宫村前辈也在吗……嘛算了」
.transition 0 * 20
.stage	* ev02_108a01.png 0 0
;（移行，注意して）
.message	2510		嫗丂夘	「新藤，你又因什么事生气了？」
.message	2520	kei-212_01-0115	丂宨丂	「因为那个女人，说完就跑了啊……」
.message	2530			想说什么完全不明白。
.transition 0 * 40
.stage	* ev02_108b01.png 0 0
;（フェ～ドスピ～ドは注意して）
.message	2540	kei-212_01-0117	丂宨丂	「京介前辈！」
.message	2550		嫗丂夘	「是！」
.message	2560			怎，怎么觉得叫法变了。
.message	2570	kei-212_01-0119	丂宨丂	「我有话要对你说。能来一下吗？」
.transition 0 * 40
.stage	* ev02_108b02.png 0 0
.message	2580		嫗丂夘	「有话说……看起来不会是什么平静的事情啊」
.message	2590	kei-212_01-0121	丂宨丂	「够了啦，来还是不来？　还是跟宫村前辈聊天更有趣？」
.message	2600			今天看来是相当怒啊。
.message	2610			还是该说今天也是？
.transition 0 * 40
.stage	* ev02_108b03.png 0 0
.message	2620	miy-212_01-0043	傒傗偙	「啊～，没事没事。我的话已经说完了啦」
.message	2630	miy-212_01-0045	傒傗偙	「那回见了哦～，小景」
.transition 0 * 20
.stage	* bgs_sch010a01_01.png 0 0
;（ここ，切り出しでインで？）
.message	2640			宫村挥了挥手离开了屋顶。
.message	2650			对我连个告别都说么。
.message	2660		嫗丂夘	「然，麻烦的人已经走了……要换地方吗？」
.transition 0 * 20
.stage	* bgs_sch010a01_01.png 0 0 st_kei01b03.png 380
.message	2670	kei-212_01-0123	丂宨丂	「不，这儿就好。马上就说完」
.transition 0 * 40
.stage	* bgs_sch010a01_01.png 0 0 st_kei01b01.png 380
;（表情変化，注意して。目をつむらせる？）
.message	2680	kei-212_01-0124		新藤轻轻呼了一口气，摆出一副陷入思考的表情。
.message	2690		嫗丂夘	「新藤，怎么了吗？」
.transition 0 * 40
.stage	* bgs_sch010a01_01.png 0 0 st_kei03b03.png 380
.message	2700	kei-212_01-0125	丂宨丂	「是啊，怎么回事啊那么突然」
.playBGM efBGM042.ogg
;.playBGM efBGM047.ogg
.transition 0 * 40
.stage	* bgs_sch010a01_01.png 0 0 st_kei03b06.png 380
;（表情，注意して）
.message	2710	kei-212_01-0127	丂宨丂	「算什么吗，那个叫雨宫优子的人……」
.message	2720			原来是这回事吗。
.message	2730			雨宫不经意说了什么不该说的挑衅到了她了吧。
.transition 0 * 40
.stage	* bgs_sch010a01_01.png 0 0 st_kei05b08.png 400
.message	2740	kei-212_01-0129	丂宨丂	「京介前辈」
.message	2750		嫗丂夘	「嗯？」
.message	2760	kei-212_01-0131	丂宨丂	「放学后，陪我」
.message	2770		嫗丂夘	「放学后？　就算你这么说，我还有研究部的摄影……」
.transition 0 * 40
.stage	* bgs_sch010a01_01.png 0 0 st_kei05b07.png 400
;（表情，注意して）
.message	2780			唰，新藤锐利的目光钉上了我。
.message	2790	kei-212_01-0133	丂宨丂	「不过一次，都不愿意陪下我的任性吗？」
.message	2800		嫗丂夘	「任性吗……」
.message	2810			虽然我也是擅自把新藤拉来摄影，有欠她的没错。
.message	2820			这人情不还不可了啊……。
.message	2830		嫗丂夘	「那么，陪你具体干什么？」
;■真剣
.transition 0 * 40
.stage	* bgs_sch010a01_01.png 0 0 st_kei01b03.png 400
;（表情とポ～ズ，注意して）
.message	2840	kei-212_01-0135	丂宨丂	「跑步」
.message	2850		嫗丂夘	「跑步？」
.message	2860			在歪了头的我面前，新藤点了点头。
.message	2870			她脸上浮现的决意清晰可见。
.message	2880			说不定，是已经决定了什么了吧。
.panel 0
.playBGM *
.transition 0 * 10
.stage	* WHITE.png 0 0



;■背景：砂浜（夏，１７時
;■　　　　堤京介：制服（夏）
;■　　　　新藤景：運動着（夏）
;.playBGM efBGM047.ogg
.playBGM efBGM054.ogg
;.playBGM BGM054_sample2.ogg
.transition 1 fadeSide.png 10
.stage	* ev02_109.png 800 0


;■御影チェック
;.hscroll	0	-10
.hscroll	0	-12


;（スクロ～ルはもちっとはやく？15くらい？）
.endScroll f
.panel 1
.message	2890		嫗丂夘	「哈～，哈～，哈啊……」
.message	2900	kei-212_01-0137	丂宨丂	「真是的，你要精疲力尽到什么时候啊」
.message	2910		嫗丂夘	「就，就算你……这么说……」
.message	2920			跑步，就是这如字面的意思啊。
.message	2930			放学后，回了一下家换好运动服的新藤在公园约好见面。
.message	2940			然后这死亡之路便开始了──
.message	2950		嫗丂夘	「到，到底跑了有多少公里了啊……？」
.message	2960			平常都没有好好作过运动的身体跑了这么长的距离已经累坏了。
.message	2970	kei-212_01-0139	丂宨丂	「大概十公里左右吧」
.message	2980		嫗丂夘	「十，十公里！？」
.message	2990	kei-212_01-0141	丂宨丂	「虽然是我也稍微有点累了」
.message	3000			稍微有点？
.message	3010		嫗丂夘	「你不是最近也没作过什么运动吗？　突然跑这么长的距离……」
.message	3020	kei-212_01-0143	丂宨丂	「没事啊，跑时已经放慢步调了啦」
.message	3030		嫗丂夘	「就算这么说也太乱来了啊」
.message	3040		嫗丂夘	「这可是要给我生孩子的重要的身体，万一出了什么事」
.message	3050	kei-212_01-0145	丂宨丂	「谁，谁啊！」
.message	3060		嫗丂夘	「说笑而已啦。你不擅长对付说笑是吧」
.message	3070	kei-212_01-0147	丂宨丂	「前辈的笑话太差劲了啦！」
.message	3080			说着，新藤的脸红到了耳边。
.message	3090			呼～，还真是可爱啊。
.transition 0 * 20
.stage	* ev02_110a01.png 0 0
.message	3100	kei-212_01-0149	丂宨丂	「真是的，你啊……。到底是被怎么养，才养有这种差劲的性格的啊」
.message	3110		嫗丂夘	「这个以后慢慢跟你讲就好」
.transition 0 * 20
.stage	* ev02_110a02.png 0 0
;☆（a02差分の使いどころは注意して。よくわからん，，，フェ～ドスピ～ドも20でいいのか？）
.message	3120		嫗丂夘	「说实在的，膝盖没事吗？」
.message	3130			再怎么说也跑的太快了啊。
.message	3140			就算是健康的身体出些问题也不奇怪。
.transition 0 * 20
.stage	* ev02_110b02.png 0 0
;（表情とフェ～ドスピ～ドは注意して）
.message	3150	kei-212_01-0151	丂宨丂	「…………」
.message	3160			新藤嘟着嘴压下视线。
.transition 0 * 40
.stage	* ev02_110b01.png 0 0
.message	3170	kei-212_01-0153	丂宨丂	「不痛……呢」
.message	3180		嫗丂夘	「没什么自信啊。过来，让我给你诊视一下」
.transition 0 * 40
.stage	* ev02_110a03.png 0 0
;（フェ～ドスピ～ドは注意して）
.message	3190	kei-212_01-0155	丂宨丂	「别想浑水摸鱼！」
.message	3200			可惜，被看出来了吗。
.message	3210		嫗丂夘	「但是真的不痛吗？　小景没在强撑吧？」
.transition 0 * 40
.stage	* ev02_110a04.png 0 0
.message	3220	kei-212_01-0157	丂宨丂	「别叫我小景」
.message	3230		嫗丂夘	「到是，回想起来运动之前不应该去医院接受下检查的吗？」
;■きっぱり
.transition 0 * 40
.stage	* ev02_110a05.png 0 0
.message	3240	kei-212_01-0159	丂宨丂	「讨厌医院」
.message	3250		嫗丂夘	「没事的啦，不会打针的哦」
.transition 0 * 40
.stage	* ev02_110a03.png 0 0
.message	3260	kei-212_01-0161	丂宨丂	「我是小孩子吗！」
.message	3270			嘛，也不必担心这地步吧？
.message	3280			没什么异常才会跑那么远的距离的啊。
.transition 0 * 40
.stage	* ev02_110b02.png 0 0
;（フェ～ドスピ～ドは注意して）
.message	3290	kei-212_01-0163	丂宨丂	「不过，真的」
.message	3300	kei-212_01-0165	丂宨丂	「一点都不痛。自己都吃惊了呢」
.message	3310	kei-212_01-0166		然后，新藤轻轻叹了口气。
.message	3320	kei-212_01-0167	丂宨丂	「不过，却还觉得会不会在哪一天突然膝盖再次坏掉」
.message	3330	kei-212_01-0169	丂宨丂	「真不行呢。什么时候开始这么软弱起来」
.message	3340		嫗丂夘	「不也好吗？　谁都会有这样的时候。想说什么就说，说不出口的也就算了」
.transition 0 * 40
.stage	* ev02_110b03.png 0 0
.message	3350	kei-212_01-0171	丂宨丂	「……嗯」
.message	3360			怎么突然坦诚起来。
.message	3370			虽然这也是一种有趣的可爱也不错……。
.message	3380		嫗丂夘	「虽然害怕着，但你不还想要再一次奔跑起来吗？」
.message	3390	kei-212_01-0173	丂宨丂	「……谁知道呢」
.message	3400		嫗丂夘	「果然还没有下定决心吗？」
.transition 0 * 40
.stage	* ev02_110a05.png 0 0
;（表情，注意して。フェ～ドスピ～ドにも）
.message	3410	kei-212_01-0175	丂宨丂	「说不定还没有被打够啊」
;☆（こっからの画像構築には注意して）
.message	3420			新藤啪嗒啪嗒走了几步，站到了我眼前。
.message	3430	kei-212_01-0177	丂宨丂	「京介前辈也来打我吗？」
.message	3440		嫗丂夘	「怎么可能」
.message	3450			我摇了摇头。
.message	3460		嫗丂夘	「我不会打你……也没这理由」
.message	3470		嫗丂夘	「而且，我也无法为你拨开你的双眼」
.message	3480	kei-212_01-0179	丂宨丂	「说不定是如此……」
.message	3490	kei-212_01-0181	丂宨丂	「你对于我来说，只是拿镜头对着我的人而已」
.message	3500			……这对我也一样。
.message	3510			新藤景的存在，只是一个被摄体而已。
.message	3520	kei-212_01-0183	丂宨丂	「但是，现在」
.message	3530	kei-212_01-0185	丂宨丂	「现在，前辈的手中并没有摄像机」
.message	3540		嫗丂夘	「啊啊」
.message	3550			在这站着的堤京介只是一个普通人，而新藤景也不是镜头中的存在。
.message	3560	kei-212_01-0187	丂宨丂	「再让我说一个……任性的要求吧」
.message	3570		嫗丂夘	「任性的？」


;.message	3580	kei-212_01-0189	丂宨丂	「わたしを見届けてほしい。走り出して，もしまた倒れるならその瞬間も見ていてもらいたいの」
.message	3580	kei-212_01-0188	丂宨丂	「希望你看着我」
.message	3585	kei-212_01-0190	丂宨丂	「我奔跑出去，如果倒下了──希望你能看着那个瞬间」


.message	3590		嫗丂夘	「……为什么是我？」
.message	3600	kei-212_01-0191	丂宨丂	「说不定谁都可以呢」
.message	3610		嫗丂夘	「诶，喂喂」
.message	3620			说谁都可以就太伤人了吧。
.message	3630	kei-212_01-0193	丂宨丂	「说笑啦」
.message	3640			新藤说着，轻轻地笑了起来。
.message	3650	kei-212_01-0195	丂宨丂	「给我契机的是你啊」
.message	3660	kei-212_01-0197	丂宨丂	「如果没有前辈的话，大概我还会什么都不做的哦」
.message	3670		嫗丂夘	「我只是看着你而已。而且只是从你离群那刻开始」
.message	3680	kei-212_01-0199	丂宨丂	「这已经够了。托前辈的福我才懂得了许多」
.message	3690			其实我真的什么都没做。
.message	3700			而且，现在对于自己的无为──不知为何有些懊悔。
.message	3710	kei-212_01-0201	丂宨丂	「给我契机的前辈你──从今以后」
.message	3720	kei-212_01-0203	丂宨丂	「也必要要看着我」
.message	3730		嫗丂夘	「命令吗！？」
.message	3740			刚才还是听下我的任性的要求吧──之类，拜托的口气呢。
.message	3750	kei-212_01-0205	丂宨丂	「还是说，摄影研究部的摄影很愉快？」
.message	3760		嫗丂夘	「不，说愉快的话有些微妙啊」
.message	3770	kei-212_01-0207	丂宨丂	「那和我的摄影呢？」
.message	3780		嫗丂夘	「当然不可能不愉快啊。如果不这样，我也不会拍你了啊」
.message	3790	kei-212_01-0209	丂宨丂	「坦白是好事。只是乖僻着的话，重要的东西就会从手中溜走了啊」
.message	3800			如果她也坦白的把自己的心情告诉广野的话──
.message	3810			也会在短短的时间内坐着幸福的梦的吧。
.message	3820	kei-212_01-0211	丂宨丂	「那么就只要去做愉快的事，和想做的事情就好不是吗。我也会这么做的」
.message	3830			但是，新藤景现在已经越过幻想面对眼前的现实。
.message	3840			大概，我在体育館看到新藤时也是。
.message	3850			就算再痛苦，她也咬着牙齿坚持着。
.message	3860			而现在，新藤已经找到了自己该走的路了吧。
.transition 0 * 20
.stage	* ev02_111.png 0 0
;（インのタイミング，注意して）
.message	3870			那么，我呢……？
.select 但是，不能背叛摄影研究会:label1 还是想要拍摄新藤的:label2
.label label1
.chain 212_02.sc
.label label2
.set favKei = favKei + 1
.chain 212_03.sc

;◆選択肢分岐
;■１：でも，映研を裏切れない。
;→212_02へ。
;■２：やっぱり新藤を撮りたい。
;→212_03へ。
;■２を選択した場合，216_01の選択肢無し。

;.end
