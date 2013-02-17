.setGlobal EYE_SEQ_DEFAULT = 2


.if ef_418_01 == 1 ef_418_b1
.if ef_418_01 <= 0 ef_418_a1

.label ef_418_a1

.pragma disable_control

.goto ef_418_b1
.end

.label ef_418_b1


.playBGM efLAT05_21.ogg
.transition 0 * 10
.stage	* title_4back.png 0 0
.message	999			\a　
.wait 980

.transition 0 * 10
.stage	* WHITE.png 0 0

.pragma enable_control




.transition 0 * 10
.stage	vista_window.png WHITE.png 0 0
.panel 3
.message	100	mid-415_02-0003		一切的开始，是怎样的呢……。
.message	110	mid-415_02-0005		开始慢慢稀薄的记忆，复苏了起来。
.message	120	mid-415_02-0007		大概，就是这毫不经意的一句话。
.transition 0 * 10
.stage	vista_window.png ev04_135a01.png 0 0
.message	130	yuk-415_02-0003	桪丂巕	『怎么了呢？』
.transition 0 * 20
.stage	vista_window.png WHITE.png 0 0
.message	140	mid-415_02-0009		从我被孤儿院领养之后，从来没有和人正面说过话。
.message	150	mid-415_02-0011		罗嗦。
.message	160	mid-415_02-0013		大家都好罗嗦。
.message	170	mid-415_02-0015		罗嗦，罗嗦，罗嗦，罗嗦，罗嗦，罗嗦，罗嗦，罗嗦，罗嗦……。
.transition 0 * 20
.stage	vista_window.png ago_base_40015a.png 0 0
.message	180	yuk-415_02-0005	桪丂巕	「为什么要哭呢？」
.transition 0 * 20
.stage	vista_window.png WHITE.png 0 0
.message	190	mid-415_02-0017		但是，只有这个人的声音不一样。
.message	200	mid-415_02-0019		如果就言语本身而言，明明是说我最讨厌的发言。
.message	210	mid-415_02-0021		但是这个漂亮的声音却印在了我寂寞的心里。
.message	220	mid-415_02-0023		所以。
.message	230	mik-415_02-0003	#枹丂棃	「我没哭」
.message	240	mid-415_02-0025		我无意识的理解到，在这个人面前我不能哭。
.message	250	mid-415_02-0027		明明早该结束的。
.transition 0 * 10
.stage	vista_window.png ev04_178.png 0 0
.message	260	mid-415_02-0029		我禁不住抬起了头。


.panel 0
.transition 0 * 10
.stage	vista_window.png ev05_163b01.png 0 0
.transition 0 * 10
.stage	vista_window.png ev05_163b01_mugai.png 0 0
.panel 3
.message	270	mid-415_02-0031		这就是，我和雨宫优子小姐的相遇。



.transition 0 * 10
.stage	vista_window.png WHITE.png 0 0
.message	280	mid-415_02-0033		呐，再给我听更多更多好听的声音吧。



.panel 0
.transition 0 * 10
.stage	vista_window.png ev05_181a04.png 0 0
.transition 0 * 10
.stage	vista_window.png ev05_181a04_mugai.png 0 0
.panel 3
.message	290	yuk-415_02-0007	桪丂巕	「在奇怪的地方碰面了呢。今天是来玩的么？」
.message	300	mik-415_02-0005	#枹丂棃	「教会前面」
.transition 0 * 40
.stage	vista_window.png ev05_181a05_mugai.png 0 0
.message	310	yuk-415_02-0009	桪丂巕	「教会前？」
.message	320	mik-415_02-0007	#枹丂棃	「在教会前走来走去不可以，老师说」
.message	330	mik-415_02-0009	#枹丂棃	「因为有车经过很危险。要玩的话，在公园玩，这么说」
.message	340	yuk-415_02-0011	桪丂巕	「确实是这样的哦」
.message	350	mid-415_02-0035		突然，优子小姐小小的歪了下脑袋。
.message	360	yuk-415_02-0013	桪丂巕	「为什么未来会在教会前呢？」
.transition 0 * 40
.stage	vista_window.png ev05_181a06_mugai.png 0 0
.message	370	mik-415_02-0011	#枹丂棃	「这个……这个是我自己的事」
.message	380	yuk-415_02-0015	桪丂巕	「难道是……」
.transition 0 * 40
.stage	vista_window.png ev05_181a07_mugai.png 0 0
.message	390	yuk-415_02-0017	桪丂巕	「是在等着我么？」
.message	400	mik-415_02-0013	#枹丂棃	「不是！」
.transition 0 * 40
.stage	vista_window.png ev05_181a08_mugai.png 0 0
.message	410	mik-415_02-0015	#枹丂棃	「不是……哼」


.transition 0 * 20
.stage	vista_window.png WHITE.png 0 0
.message	420	mid-415_02-0037		因为寂寞。
.transition 0 * 20
.stage	vista_window.png ago_base_40015o3.png 0 0
.message	430	mid-415_02-0039		因为讨厌一个人。



.panel 0
.transition 0 * 10
.stage	vista_window.png ev05_209a01.png 0 0
.transition 0 * 10
.stage	vista_window.png ev05_209a01_mugai.png 0 0
.panel 3
.message	440	yuk-415_02-0019	桪丂巕	「是了，我明明有……礼物要给你的……」
.message	450	yuk-415_02-0021	桪丂巕	「放哪里去了呢……」
.message	460	mik-415_02-0017	#枹丂棃	「那种事没关系的！」
.message	470	yuk-415_02-0023	桪丂巕	「之后再去找找吧……」
.message	480	mik-415_02-0019	#枹丂棃	「那种事……没关系的……」
.message	490	yuk-415_02-0025	桪丂巕	「未来。不可以哦，做出这种表情……」
.message	500	yuk-415_02-0027	桪丂巕	「女孩子，要经常微笑着，才是最好的……」



.transition 0 * 20
.stage	vista_window.png ago_base_40015o1.png 0 0
.message	510	mid-415_02-0041		我知道了。
.transition 0 * 20
.stage	vista_window.png ago_base_40015o2.png 0 0
.message	520	mid-415_02-0043		约好了。
.transition 0 * 20
.stage	vista_window.png ev04_136a01.png 0 0
.message	530	mid-415_02-0045		所以，请别消失……
.message	540	mid-415_02-0047		优子小姐……
.panel 0
.transition 0 * 10
.stage	vista_window.png WHITE.png 0 0




.transition 0 * 10
.stage	vista_window.png ev04_134a01.png 0 0
.panel 3
.message	550	mid-415_02-0049	#儈僘僉	「花朵总是像要马上凋谢的样子呢」
.message	560	mid-415_02-0051		我看着教会正前方的道路。

.message	570	him-415_01-0081	丂梉丂	「这里有什么？　不是为了死去的双亲，和以前的羽山水姬而来的么？」

.message	580	mid-415_02-0053	#儈僘僉	「不是。是为了雨宫优子小姐而来的」
.message	590	him-415_02-0005	丂梉丂	「…………？」
.message	600	mid-415_02-0055	#儈僘僉	「虽然真的，想要在真正的地方献上的呢」
.message	610	him-415_02-0007	丂梉丂	「你是……」
.message	620	mid-415_02-0057	#儈僘僉	「诶」
.panel 0
.vscroll	800	10
.endScroll f
.panel 3
.message	640	him-415_02-0009	丂梉丂	「你是谁？」
.transition 0 * 20
.stage	vista_window.png ago_base_40015l.png 0 0
.message	650	mid-415_02-0061		火村先生用着，简直就和那一天的久濑先生一样——更加黑暗的眼神，在那里站着。
.message	660	mid-415_02-0063		在讴歌着生命的夏日阳光中，只有那里像似拒绝光明一般的黑暗存在。
.message	670	mid-415_02-0065		我无意识的脚软了下。
.message	680	mid-415_02-0067	#儈僘僉	「那个……」


.transition 0 * 20
.stage	vista_window.png ev04_137a02.png 0 0

.message	690	him-415_02-0011	丂梉丂	「要忏悔的事情是什么」
.message	700	mid-415_02-0069		与其提问，不如说是诘问的语气。
.message	720	mid-415_02-0073		禁不住的抬高了喉咙。
.message	730	mid-415_02-0075	#儈僘僉	「那个……我是，被这个教会领养的……」
.message	740	mid-415_02-0077		言语梗塞了。
.message	750	mid-415_02-0079		我无法逃离火村先生认真的眼神。
.message	760	mid-415_02-0081		对这个人来说，也是重要的事情吧。
.message	770	mid-415_02-0083		所以，我深深的呼吸了下，让自己的心情冷静下来。
.transition 0 * 10
.stage	vista_window.png ev04_138a01.png 0 0
.message	780	mid-415_02-0085	#儈僘僉	「……我很害怕别人」
.message	790	mid-415_02-0087		每次有谁要触碰我的时候。
.message	800	mid-415_02-0089		伸出手的事情。
.message	810	mid-415_02-0091		我就感觉要掐我脖子。
.message	820	mid-415_02-0093		要把我拖入海里一样。
.transition 0 * 20
.stage	vista_window.png ev04_138a02.png 0 0
.message	830	mid-415_02-0095	#儈僘僉	「那个时候……」
.message	840	mid-415_02-0097		虽然回忆起来很辛酸。
.message	850	mid-415_02-0099		直到现在,那个时期经历的恐怖感依旧残存于脑海里的某个角落。
.message	860	mid-415_02-0101		我的碎片。
.message	870	mid-415_02-0103	#儈僘僉	「学校也不去，原来在孤儿院里的看护者我也害怕……」
.transition 0 * 20
.stage	vista_window.png ev04_138a03.png 0 0
.message	880	mid-415_02-0105	#儈僘僉	「因为差点被亲生父母杀死……所以根本不相信别人」
.message	890	mid-415_02-0107	#儈僘僉	「半年来……一句招呼都没打过……」
.message	900	mid-415_02-0109	#儈僘僉	「如果吃饭不是一个人的话胃就接受不了。如果有谁在一边说话的话，我就变得无法动弹……」
.transition 0 * 20
.stage	vista_window.png ev04_138a03_mugai_a.png 0 0
.message	910	mid-415_02-0111	#儈僘僉	「正因如此没有来领养我的人，我一直在教会里自闭着」
.message	920	mid-415_02-0113		季节从夏至冬。
.transition 0 * 20
.stage	vista_window.png ev04_138a05.png 0 0
.message	930	mid-415_02-0115	#儈僘僉	「那个时候，我和那个人相遇了……」


.transition 0 * 20
.stage	vista_window.png ev04_178.png 0 0
.message	940	yuk-415_02-0029	桪丂巕	『怎么了呢？』


.transition 0 * 20
.stage	vista_window.png ev04_138a06.png 0 0
.message	950	mid-415_02-0117	#儈僘僉	「我现在能这样笑着，全部都是那个人的功劳」
.message	960	mid-415_02-0119		那样的人。
.transition 0 * 20
.stage	vista_window.png ev04_138a01.png 0 0
.message	970	mid-415_02-0121	#儈僘僉	「那样的人……为了保护我死去了」
.transition 0 * 20
.stage	vista_window.png ev04_139.png 0 0
.message	980	mid-415_02-0123		代替了我。
.transition 0 * 20
.stage	vista_window.png ago_base_40015m.png 0 0
.message	990	mid-415_02-0125		救助了完全没有对应价值的孩子。
.transition 0 * 20
.stage	vista_window.png ev04_138a04.png 0 0
.message	1000	mid-415_02-0127	#儈僘僉	「……但是」
.message	1010	mid-415_02-0129		但是。
.transition 0 * 20
.stage	vista_window.png ev04_138a02.png 0 0
.message	1020	mid-415_02-0131	#儈僘僉	「正因为如此，我不可以动摇」
.message	1030	mid-415_02-0133		不能轻易低下头。


.transition 0 * 20
.stage	vista_window.png ev04_138a01.png 0 0
.message	1040	mid-415_02-0135	#儈僘僉	「即使自己没有价值和意义……」
.transition 0 * 20
.stage	vista_window.png ev04_140a01.png 0 0
.message	1050	mid-415_02-0137	#儈僘僉	「就算要代替那样漂亮的人是不可能的……」
.transition 0 * 20
.stage	vista_window.png ev04_140b01.png 0 0
.message	1060	mid-415_02-0139	#儈僘僉	「就算是这样，为了赶上那个人，我想努力」
.transition 0 * 40
.stage	vista_window.png ev04_140b02.png 0 0
.message	1070	mid-415_02-0141	#儈僘僉	「我决定了，要在这个世界上战斗到最后一刻！」
.transition 0 * 20
.stage	vista_window.png ev04_141a01.png 0 0
.message	1080	mid-415_02-0143		绝对要笑到最后一刻。
.message	1090	mid-415_02-0145	#儈僘僉	「而且，不仅仅是优子小姐」
.message	1100	mid-415_02-0147	#儈僘僉	「也有成为我目标的前辈们」



.transition 0 * 20
.stage	vista_window.png ev01_032_mugai.png 0 0
.message	1110	mid-415_02-0149	#儈僘僉	「有人教会了我，为了能继续实现自己的梦想——为了守护住重要的人，选择困难的道路的重要性」

.panel 0
.transition 1 fadeSide.png 20
.stage	vista_window.png ev01_032b01.png 0 0
.transition 1 fadeSide.png 20
.stage	vista_window.png ev01_203_mugai02.png 0 0
.panel 3
.message	1120	mid-415_02-0151	#儈僘僉	「有人教会了我，即使受伤也能再度站起来的勇气」

.panel 0
.transition 1 fadeSide.png 20
.stage	vista_window.png ev01_203_mugai.png 0 0
.transition 1 fadeSide.png 20
.stage	vista_window.png ev03_046_mugai.png 0 0
.panel 3
.message	1130	mid-415_02-0153	#儈僘僉	「那家伙也是，在谁看上去都不得不放弃的状况下，抓住了一心一意的希望。」


.panel 0
.transition 1 fadeSide.png 20
.stage	vista_window.png ev03_046.png 0 0
.transition 1 fadeSide.png 20
.stage	vista_window.png ev04_141b01.png 0 0
.panel 3
.message	1140	mid-415_02-0155	#儈僘僉	「……在我的心中，这种回忆一个一个的生存着」
.transition 0 * 20
.stage	vista_window.png ev04_141b02.png 0 0
.message	1150	mid-415_02-0157	#儈僘僉	「当然，那里没有完全的答案」
.transition 0 * 20
.stage	vista_window.png ev04_141b03.png 0 0
.message	1160	mid-415_02-0159	#儈僘僉	「有着为了让自己幸福所以让别人哭泣的事情，也有正因为体谅别人反而伤害了别人的事情……」
.transition 0 * 20
.stage	vista_window.png ev04_141b04.png 0 0
.message	1170	mid-415_02-0161	#儈僘僉	「但是，就算这种的不完全，也只是一个碎片」
.message	1180	mid-415_02-0163	#儈僘僉	「我无法从那种东西上，移开我的视线」
.message	1190	mid-415_02-0165	#儈僘僉	「正直与愚昧，强大与弱小，梦想与现实——这些大概都如同翅膀一样」
.message	1200	mid-415_02-0167	#儈僘僉	「仅仅１只翅膀是不行的。只有２只成对，才能展开翅膀飞翔起来」
.transition 0 * 20
.stage	vista_window.png ev04_141a02.png 0 0
.message	1220	mid-415_02-0171	#儈僘僉	「人类……一己之力能做到的事情是十分有限的」
.transition 0 * 20
.stage	vista_window.png ev04_141a03.png 0 0
.message	1230	mid-415_02-0173	#儈僘僉	「但是，我认为这样才是最好的」
.transition 0 * 20
.stage	vista_window.png ev04_141a01.png 0 0
.message	1240	mid-415_02-0175	#儈僘僉	「能出生在这个不完全的世界太好了，我真心这么认为」
.transition 0 * 20
.stage	vista_window.png ev04_141a04.png 0 0
.message	1250	mid-415_02-0177	#儈僘僉	「所以，正因为一个人很寂寞，所以才会去寻求别人」
.message	1260	mid-415_02-0179		大概，优子小姐也是这样的吧。
.message	1270	mid-415_02-0181		就算是那个仿佛如天使一般的人，也有我所不知道的作为普通人的一面吧。
.message	1280	mid-415_02-0183		并且，久濑先生恐怕也一样。
.transition 0 * 20
.stage	vista_window.png ago_base_40015n.png 0 0
.message	1290	mid-415_02-0185		……是啊。
.message	1300	mid-415_02-0187		我现在，终于发现了。
.message	1310	mid-415_02-0189		久濑先生……正因为那个人，和优子小姐相似。
.transition 0 * 20
.stage	vista_window.png ago_base_40015n2.png 0 0
.message	1320	mid-415_02-0191	#儈僘僉	「所以……所以……」
.message	1330	mid-415_02-0193	#儈僘僉	「那个～……」
.message	1340	mid-415_02-0195		啊咧？
.message	1350	mid-415_02-0197		我突然把一开始的问题给忘了。
.transition 0 * 20
.stage	vista_window.png ago_base_40015n3.png 0 0
.message	1360	mid-415_02-0199		火村先生刚才，问我什么来着？
.message	1370	mid-415_02-0201		…………。
.message	1380	mid-415_02-0203	#儈僘僉	「总，总而言之，我要成为优子小姐那样造福大家的人！」
.message	1390	mid-415_02-0205	#儈僘僉	「以上！」
.message	1400	mid-415_02-0207		虽然最后的发言很ＯＲＺ，但是那是我心中的全部。

.transition 0 * 20
.stage	vista_window.png ev04_142a02.png 0 0

.message	1410	him-415_02-0013	丂梉丂	「…………」
.message	1420	mid-415_02-0209		火村先生用严肃的目光。
.transition 0 * 20
.stage	vista_window.png ev04_143_mugai_a.png 800 0

.hscroll	0	-14

.endScroll f
.message	1430	mid-415_02-0211		向我伸出了手。
.transition 0 * 20
.stage	vista_window.png ev04_143_mugai_b.png 0 0
.message	1440	mid-415_02-0213		把头……。
.transition 0 * 20
.stage	vista_window.png ev04_143.png 0 0
.message	1450	him-415_02-0015	丂梉丂	「…………」

.transition 0 * 20
.stage	vista_window.png ev04_142b01_mikage.png 0 0

.message	1460	him-415_02-0017	丂梉丂	「……哈～」
.message	1470	mid-415_02-0215	#儈僘僉	「啊嘿？」

.transition 0 * 20
.stage	vista_window.png ev04_142b01.png 0 0

.message	1480	mid-415_02-0217		火村先生垂下手臂大大的叹了口气，这次是我呆若木鸡了。
.transition 0 * 40
.stage	vista_window.png ev04_142c01.png 0 0
.message	1490	him-415_02-0019	丂梉丂	「啊～，可恶，玛丽隔壁的！」
.transition 0 * 20
.stage	vista_window.png ev04_142b02.png 0 0
.message	1500	him-415_02-0021	丂梉丂	「明明以为忘的一干二净了……」
.transition 0 * 20
.stage	vista_window.png ev04_134a01.png 0 0
.message	1510	mid-415_02-0219		他分开前发仰视着青空。
.message	1520	him-415_02-0023	丂梉丂	「那个男人的心情到现在总算能理解了。这就像哑弹一样嘛」
.message	1530	him-415_02-0025	丂梉丂	「迷茫着不知道该怎么办的我也太嫩了啊」
.message	1540	him-415_02-0027	丂梉丂	「你如果是那样期望着的话」
.message	1550	him-415_02-0029	丂梉丂	「已经，没事了」
.transition 0 * 20
.stage	vista_window.png ev04_142b04.png 0 0
.message	1560	mid-415_02-0221	#儈僘僉	「啊？」
.transition 0 * 40
.stage	vista_window.png ev04_142b05.png 0 0
.message	1570	him-415_02-0031	丂梉丂	「宽恕你」
.transition 0 * 20
.stage	vista_window.png ev04_142b05_mugai_a.png 0 0
.message	1580	mid-415_02-0223		火村先生轻轻的拍了拍我的肩膀。
.transition 0 * 20
.stage	vista_window.png ev04_142b05.png 0 0
.message	1590	mid-415_02-0225		因为太突然了，我没反应上。
.message	1600	him-415_02-0033	丂梉丂	「是在忏悔吧」
.message	1610	mid-415_02-0227	#儈僘僉	「诶？啊，对」
.message	1620	him-415_02-0035	丂梉丂	「那样的话我的任务就是宽恕你」
.transition 0 * 40
.stage	vista_window.png ev04_142b06.png 0 0
.message	1630	him-415_02-0037	丂梉丂	「因为是人的罪过，所以由人来宽恕」

.transition 0 * 40
.stage	vista_window.png ev04_142b07.png 0 0

.message	1640	mid-415_02-0229		带着悲伤的笑着。


.message	1650	him-415_02-0039	丂梉丂	「不用再背负那种了，把那个和这花束一起放在这里吧」
.message	1660	mid-415_02-0231	#儈僘僉	「哈，啊」
.message	1670	mid-415_02-0233		为什么火村先生一定要说到这个地步，我不是很明白。
.message	1680	mid-415_02-0235		但是，我不自觉地安心了。
.message	1690	mid-415_02-0237		被这个人这样一说的话……。
.message	1700	mid-415_02-0239		不知道为什么全身都放松了下来。
.message	1710	mid-415_02-0241	#儈僘僉	「……呼～」
.transition 0 * 40
.stage	vista_window.png ev04_142b08.png 0 0
.message	1720	him-415_02-0041	丂梉丂	「不过有１点，说是订正我还是补充一下」
.message	1730	mid-415_02-0243		他回到了平时那张苦瓜脸，转移开了视线。
.transition 0 * 40
.stage	vista_window.png ev04_142b09.png 0 0
.message	1740	him-415_02-0043	丂梉丂	「如果想要让别人幸福的话，先要让自己幸福起来」
.message	1750	him-415_02-0045	丂梉丂	「这才是最重要的事情」
.message	1760	mid-415_02-0245	#儈僘僉	「啊，收到。我会努力的」
.transition 0 * 40
.stage	vista_window.png ev04_142b10.png 0 0
.message	1770	him-415_02-0047	丂梉丂	「久濑也拜托给你了」
.message	1780	mid-415_02-0247	#儈僘僉	「诶？」
.transition 0 * 40
.stage	vista_window.png ev04_142b11.png 0 0
.message	1790	him-415_02-0049	丂梉丂	「我可没打算陪那家伙玩什么青春啊」
.message	1800	mid-415_02-0249		到底是怎么了呢。
.message	1810	mid-415_02-0251		火村先生吃吃地笑着——感觉倒像是他摆脱了什么附体的邪灵一样笑得阳光灿烂。
.message	1820	him-415_02-0051	丂梉丂	「可以给我支花吗？」
.message	1830	mid-415_02-0253	#儈僘僉	「诶？啊啊，请请」
.message	1840	mid-415_02-0255		稍微扫了一眼，把一支开放的不错的花递给了火村先生。
.message	1850	mid-415_02-0257		他一边接下那个一边苦笑着说。
.transition 0 * 20
.stage	vista_window.png ev04_142d01.png 0 0
.message	1860	him-415_02-0053	丂梉丂	「能再给一支吗。虽然小点的也不错」
.message	1870	mid-415_02-0259	#儈僘僉	「啊，好的」
.transition 0 * 20
.stage	vista_window.png ev04_142e01.png 0 0
.message	1880	him-415_02-0055	丂梉丂	「谢谢」
.message	1890	mid-415_02-0261		２支花有什么意义吗。
.message	1900	mid-415_02-0263		火村先生转着花，凑近鼻子。
.transition 0 * 20
.stage	vista_window.png ev04_142f01.png 0 0
.message	1910	him-415_02-0057	丂梉丂	「……不错的香味」
.message	1920	mid-415_02-0265	#儈僘僉	「呜哇」
.transition 0 * 40
.stage	vista_window.png ev04_142f02.png 0 0
.message	1930	him-415_02-0059	丂梉丂	「怎么了？」
.message	1940	mid-415_02-0267	#儈僘僉	「……不不，没什么没什么」
.message	1950	mid-415_02-0269		帅的差点我鼻血都出来了。
.message	1960	mid-415_02-0271		虽然他感觉离人千里之外，但是那一刻，只不过泄露出了一点点感情，这个人就变得非常的帅。
.transition 0 * 20
.stage	vista_window.png ev04_144a01_big.png 800 750
.message	1970	him-415_02-0061	丂梉丂	「但是，为什么突然拿花过来。每年都送的吗？」
.panel 0
.hscroll	428	-10
.endScroll f
.panel 3
.message	1980	mid-415_02-0273	#儈僘僉	「不是，只不过……」
.panel 0
.vscroll	299	-10
.endScroll f
.panel 3
.message	1990	mid-415_02-0275		我想起了千寻前辈的日记。
.panel 0
.scroll	800 0	10
.endScroll f
.panel 3
.message	2000	mid-415_02-0277		明明知道那是不可能的。
.panel 0
.scroll	428 750	10
.endScroll f
.panel 3
.message	2010	mid-415_02-0279	#儈僘僉	「听说，雨宫优子小姐就在音羽的教会里」
.panel 0
.hscroll	800	10
.endScroll f
.panel 3
.message	2020	him-415_02-0063	丂梉丂	「…………」
.transition 0 * 20
.stage	vista_window.png ago_base_40015h3.png 0 0
.message	2030	mid-415_02-0281	#儈僘僉	「虽然那种事情明明是不可能的……但是，大家都遇见了，雨宫优子小姐」
.transition 0 * 20
.stage	vista_window.png ev04_144a01.png 0 0
.message	2040	mid-415_02-0283		我把手放在发热的石地上，让它稍微变冷后，放下了花束。
.transition 0 * 20
.stage	vista_window.png ago_base_40015h1.png 0 0
.message	2050	mid-415_02-0285		花也已经谢了。
.transition 0 * 20
.stage	vista_window.png ago_base_40015h2.png 0 0
.message	2060	mid-415_02-0287		为了祈祷，我闭上了眼睛。
.transition 0 * 20
.stage	vista_window.png ago_base_40015h2_close.png 0 0
.message	2070	mid-415_02-0289	#儈僘僉	「……一直，都在等着什么人」
.transition 0 * 10
.stage	* vista_white.png 0 0
.panel 0
.playBGM *
.transition 0 * 10
.stage	* WHITE.png 0 0
.transition 0 * 10
.stage	* WHITE.png 0 0
.wait 100

.chain 416_01.sc
