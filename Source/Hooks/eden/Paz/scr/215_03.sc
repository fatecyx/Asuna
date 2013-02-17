; ファイル: 215_03.txt
;■＜２章：１５日目＞
;■京介自室（夏，２２時
;■　　　　堤京介：私服（夏）
.transition 1 fadeSide.png 10
.stage	* ev02_150.png 0 0
;（150はここで使用でいいのか，注意して）
;.stage	* bgc_home002a01_03.png 0 0
.panel 1
.message	100			在近处的套餐店吃过晚饭，然后去超市买过杂志后回到家中。
.message	110			真是够戗，分明是考试结束的日子却还是一团糟啊。
.message	120			大概大家都在做考试的结束庆贺吧，混到哪个圈子里玩玩也好吧。
.message	130		嫗丂夘	「没那心情啊……」
.message	140			叹着气嘟囔出声。
.message	150			考试结束并不意味就是能从备考中解放出来。
.message	160			虽然说已经实际上像是暑假了，但还是不能懈怠。
.message	170		嫗丂夘	「暑假啊」
.message	180			总觉得好像是另外一个世界的词汇。
.message	190			比起这个，倒是她的话一直在我耳边环绕不散。
.message	200			──广野的味道…吗。
.message	210			广野的味道？
.message	220		嫗丂夘	「那算什么吗！」
.message	230			怒火一下窜上心头。
.message	240			会这么生气之前可从未有过。
.message	250			是因为第一次被女孩子拒绝了吗？
.message	260			不，不是那回事。
.message	270			不是别人，而是被新藤拒绝这点让我愤愤不平。
.message	280			为什么我一直无法抓住新藤的心呢。
.message	290			分明要决定击碎她过去全部的回忆的。
.message	300			却连解放她的心我都作不到吗。
.message	310		嫗丂夘	「不对……！」
.message	320			不──不是已经知道的吗。
.message	330			无论被怎么说，但我决不能放弃。
.message	340			胜负──还没有决出。
.panel 0
.transition 0 * 10
.stage	* WHITE.png 0 0


;■シ～ン転換
;■黒バック
.playBGM efBGM042.ogg
;（もちっと後から？）
.transition 1 fadeSide.png 10
.stage	* ev02_151a01.png 0 0
;.stage	* WHITE.png 0 0
;（白で入ってますが，実際はイベントＣＧあります）
.panel 1
.message	350		嫗丂夘	「我来了<音乐符号>」
.message	360	hir-215_03-0003	丂峢丂	「…………」
.playBGM * * 0
.playSE hiro_door_close.ogg f 0 *
.transition 0 * 40
.stage	* ev02_151b01.png 0 0
;（効果音はしっかりと）
.message	370			嘭。
.playSE kyo_tobira_knock.ogg true 0 *
.transition 0 * 40
.stage	* ev02_151c01.png 0 0
;（フェ～ドスピ～ドには注意して）
.message	380		嫗丂夘	「喂喂，等下。你难道就这么不屑一顾地赶走深夜来访的好友吗！？」
;.playSE * f * 0
.transition 0 * 40
.stage	* ev02_151c02.png 0 0
.message	390			又敲了无数次门，这家的主人才明显一副勉勉强强地样子再次出现在我眼前。
.playSE * f * 0
.playSE hiro_door_open.ogg f 0 *
.playBGM efBGM042.ogg
;（鳴らすタイミングはちょっと保留）
.transition 0 * 20
.stage	* ev02_151d01.png 0 0
;（フェ～ドスピ～ドは注意して。わざと20にしてます）
.message	400	hir-215_03-0005	丂峢丂	「是好友的话就别来妨碍我工作」
.message	410	hir-215_03-0007	丂峢丂	「真是的……」


;■背景：纮自室（夏，２３時
;■　　　　堤京介：私服（夏）
;■　　　　广野纮：私服（夏）
;.playBGM efBGM042.ogg
.transition 0 * 20
.stage	* ev02_152a01.png 0 0
;.stage	* bgc_home010a01_03.png 0 0
;（実際は，モブ入りのイベントＣＧがここにはあります。インはサイドフェ～ドで？）
.message	420			这个地方，在广野离开学园之后只来过一次。
.message	430		嫗丂夘	「完全没改变啊。男人单身感十足的房间啊」
.message	440	hir-215_03-0009	丂峢丂	「你丫是专程半夜里来对我的房间品首论足的吗？」
.message	450		嫗丂夘	「我还没闲到那地──哟」
.playSE kami_rs.ogg f 0 *
;☆（御影効果音を使用）
.transition 0 * 20
.stage	* ev02_153.png 0 0
;（インのタイミング，注意して）
.message	460			我捡起无意间踩到的一张薄纸。
.message	470		嫗丂夘	「焰火大会的传单……？」
.message	480			毎年都会在这个城市搞的那个啊。
.message	490		嫗丂夘	「倒是你啊，有资格舒坦地去看什么焰火吗？」
.message	500	hir-215_03-0011	丂峢丂	「宫子不知从哪找来的啊。她就喜欢这类东西啊」
.message	510		嫗丂夘	「唔～」
.message	520			应该是想要一起去看的，广野看来还不明白吧。
.message	530			也轮不到我上什么忠告，不管了。
.transition 0 * 20
.stage	* ev02_152b01.png 0 0
.message	540		嫗丂夘	「啊，这个是慰劳」
.message	550	hir-215_03-0013	丂峢丂	「……谢了」
;（ここは切り出しを？）
.message	560			一边收了我递过的慰劳品袋，广野坐了下来。
.message	570			我也找了个适当的位置坐了下来。
.transition 0 * 20
.stage	* ev02_154a01.png 0 0
.message	580	hir-215_03-0015	丂峢丂	「这是什么东西？」
.message	590		嫗丂夘	「营养饮料。因为不清楚哪个好，就适当的买了几瓶。在没热之前全部喝光吧」
.transition 0 * 40
.stage	* ev02_154b01.png 0 0
.message	600	hir-215_03-0017	丂峢丂	「喝了这东西，脑浆就爆了！」
.message	610			这个男人想要浪费他人的好意思吗。
.transition 0 * 40
.stage	* ev02_154b02.png 0 0
.message	620		嫗丂夘	「说起来，宫村没来啊」
.message	630	hir-215_03-0019	丂峢丂	「啊啊」
.message	640	hir-215_03-0021	丂峢丂	「你们不是今天考试结束了吗。宫子她要去通宵开庆祝会」
.transition 0 * 40
.stage	* ev02_154b03.png 0 0
.message	650		嫗丂夘	「这样好啊？」
.message	660	hir-215_03-0023	丂峢丂	「怎么？」
.message	670		嫗丂夘	「庆祝会什么的，大体上绝对会有男人吧。让她通宵玩真的没事？」
.transition 0 * 40
.stage	* ev02_154b04.png 0 0
.message	680	hir-215_03-0025	丂峢丂	「你真无聊」
.transition 0 * 40
.stage	* ev02_154c01.png 0 0
.message	690			广野扭开一瓶营养饮料，灌了起来。
.transition 0 * 40
.stage	* ev02_154d01.png 0 0
.message	700	hir-215_03-0027	丂峢丂	「刺激性真大啊，这东西」
.message	710		嫗丂夘	「比起这个」
.transition 0 * 40
.stage	* ev02_154d02.png 0 0
.message	720	hir-215_03-0029	丂峢丂	「……就算是宫子也会想偶尔玩一下啊。知道吗。那家伙，期中测试得了年级第一的哦」
.message	730		嫗丂夘	「这我倒是知道」
.transition 0 * 40
.stage	* ev02_154d03.png 0 0
.message	740	hir-215_03-0031	丂峢丂	「那可是如同发疯一样的学习了啊，宫子她」
.message	750	hir-215_03-0033	丂峢丂	「她以前好似跟能量过剩似的，而最近却是无论何时都有全力投球的感觉」
.message	760	hir-215_03-0034		轻轻的晃着空了的饮料瓶，广野笑了起来。
.transition 0 * 40
.stage	* ev02_154d04.png 0 0
.message	770	hir-215_03-0035	丂峢丂	「为此原因，能量补给的幅度也是大幅上升啊」
.message	780		嫗丂夘	「能量补给啊。原来如此」
.message	790			宫村有那样的食欲也是有她相应的理由的啊。
.message	800			我差点以为她只是单纯的能吃而已。
.message	810	hir-215_03-0037	丂峢丂	「宫子她啊，还没有找到自己该做的事情」
.message	820			为了能够做自己想做的事，连学校都放弃的这个男人的声音──温柔起来。
.message	830	hir-215_03-0039	丂峢丂	「所以，才会为现在的自己能做的事情不懈地努力」
.message	840	hir-215_03-0041	丂峢丂	「于是，她就来照顾我，最近不是还教了景和羽山学习了吗」
.message	850			景…吗──
.message	860	hir-215_03-0043	丂峢丂	「不偶尔去玩下换下心情的话，她也会受不了的啊」
.message	870		嫗丂夘	「和你一起出去玩的计划呢？」
.message	880	hir-215_03-0045	丂峢丂	「到了暑假再说了。而且，并不是只和我，能和其他人一起玩也很重要啊」
.message	890	hir-215_03-0047	丂峢丂	「那家伙…一直都没有朋友啊……」
.message	900		嫗丂夘	「你还真是容易被女人诱惑的类型啊」
.transition 0 * 40
.stage	* ev02_154d05.png 0 0
.message	910	hir-215_03-0049	丂峢丂	「少多嘴～！」
.message	920			满面赤红怒吼着的广野的样子，果然和新藤哪里有些相似。
.message	930			她只注释着广野，只想着广野的吗。
.transition 0 * 40
.stage	* ev02_154d06.png 0 0
.message	940	hir-215_03-0051	丂峢丂	「啊～，怎么觉得热起来了。这个营养饮料也太即效了吧」
.message	950			不会掩饰自己害羞的地方也是一模一样啊。
.message	960	hir-215_03-0053	丂峢丂	「稍微出去吹吹风好了」
.message	970		嫗丂夘	「容某同行」
.panel 0
.playBGM *
.transition 0 * 10
.stage	* WHITE.png 0 0


;■シ～ン転換
;■公園
.playBGM efBGM031.ogg
.screen sc_night01.png sc_night01.png
.transition 1 fadeSide.png 10
.stage	* bgs_normal009a01_03.png 0 0
.panel 1
.message	980			我和广野晃晃悠悠地走着，来到了公园。
.message	990			两个臭男人在半夜的公园，虽然这位置有点冷，但总不能在这里转回头去
.message	1000		嫗丂夘	「说起来，广野。那个自行车怎么办了？」
.overlay * or_hiro03a01.png
.transition 0 * 20
.stage	* bgs_normal009a01_03.png 0 0 st_hiro04e04.png 400
.message	1010	hir-215_03-0055	丂峢丂	「巨大垃圾化啊」
.message	1020		嫗丂夘	「你姐姐呢？」
.transition 0 * 40
.stage	* bgs_normal009a01_03.png 0 0 st_hiro04e05.png 400
;（表情，注意して）
.message	1030	hir-215_03-0057	丂峢丂	「巨大垃圾化啊」
.transition 0 * 40
.stage	* bgs_normal009a01_03.png 0 0 st_hiro04e03.png 400
;☆（こっから先，05ポ～ズも使いたいので，修正されたのがきてからで）
.message	1040	hir-215_03-0059	丂峢丂	「……等等不对，现在在家中闲着呢」
.message	1050	hir-215_03-0061	丂峢丂	「来帮我忙的话要再过几天吧……哈」
.message	1060			广野一副明显垂头丧气的样子。
.message	1070			看来是真的不想见那个姐姐。
.transition 0 * 40
.stage	* bgs_normal009a01_03.png 0 0 st_hiro04e04.png 400
;（表情，注意して）
.message	1080	hir-215_03-0063	丂峢丂	「分明可以一直平和生活下去啊」
.message	1090		嫗丂夘	「哈，是吗？」
.message	1100			我稍微有些吃惊。
.message	1110			从和宫村交往开始，就和“平和”已经相距甚远了吧。


.transition 0 * 40
;.stage	* bgs_normal009a01_03.png 0 0 st_hiro03e03.png 380
.stage	* bgs_normal009a01_03.png 0 0 st_hiro03e03.png 358

;（座標，注意して）
.message	1120	hir-215_03-0065	丂峢丂	「不，真的很平和啊。虽然说是发生过各种各样的事没错，最近却感觉都是在往好的方向走」
.message	1130		嫗丂夘	「虽然我觉得不太可能，你不会想说“我有幸运的女神陪伴左右”之类的吧？」
.transition 0 * 40
.stage	* bgs_normal009a01_03.png 0 0 st_hiro01e09.png 400
.message	1140	hir-215_03-0067	丂峢丂	「白痴啊！」
.transition 0 * 40
.stage	* bgs_normal009a01_03.png 0 0 st_hiro01e06.png 400
.message	1150	hir-215_03-0069	丂峢丂	「宫子不是什么女神，而是一个满大街都能找到的普通女生而已」
.message	1160			那种人要是一抓一大把的话，这个星球就该迎来世界末日了吧。
.transition 0 * 40
.stage	* bgs_normal009a01_03.png 0 0 st_hiro01e08.png 400
;（表情，注意して）


;.message	1170	hir-215_03-0071	丂峢丂	「女神とかじゃなくて，そうだな──って，バカバカしい。どうでもいいや」
.message	1170	hir-215_03-0070	丂峢丂	「并不是什么女神，应该说是──」
.transition 0 * 40
.stage	* bgs_normal009a01_03.png 0 0 st_hiro04e04.png 400
.message	1175	hir-215_03-0070a	丂峢丂	「等，真白痴。无所谓了」


.message	1180	hir-215_03-0072		广野自己掐掉话头，轻轻叹了一口气。
.transition 0 * 40
.stage	* bgs_normal009a01_03.png 0 0 st_hiro01e06.png 400
;（表情，注意して）
.message	1190	hir-215_03-0073	丂峢丂	「然……」
.screen * *
.transition 0 * 20
.stage	* ev02_155a01.png 0 0
.message	1200	hir-215_03-0075	丂峢丂	「和景出什么事了吗？」
.message	1210		嫗丂夘	「我还什么都没说呢」
.message	1220	hir-215_03-0077	丂峢丂	「跟说了不一样吗。到了明白会打扰我工作还来的程度，应该很严重了吧？」
.message	1230			毫无疑问的，充满确认的语气。
.message	1240		嫗丂夘	「不愧是漫画家……洞察力高人一筹么？」
.message	1250	hir-215_03-0079	丂峢丂	「是不是漫画家没关系。因为是景和你的事」
.message	1260		嫗丂夘	「…………」
.message	1270			又觉得有些不爽起来。
.message	1280			就算自己的电影被直接的否定，也不曾有过这种心情。
.message	1290			这团怒火到底是为什么而燃烧起来的呢。
.transition 0 * 40
.stage	* ev02_155a02.png 0 0
.message	1300	hir-215_03-0081	丂峢丂	「虽然我不清楚到底发生了什么」
.message	1310			我捏紧拳头，几近捏碎。
.message	1320		嫗丂夘	「……我想上新藤，被她抵抗然后逃了而已」
.transition 0 * 40
.stage	* ev02_155a03.png 0 0
.message	1330	hir-215_03-0083	丂峢丂	「你说什么？」
.message	1340		嫗丂夘	「她不但速度很快，而且虽然那么小却还满有力气的啊」
.transition 0 * 40
.stage	* ev02_155a04.png 0 0
.message	1350	hir-215_03-0085	丂峢丂	「……你这家伙」
.message	1360			广野的样子顿时变了。
.message	1370	hir-215_03-0087	丂峢丂	「你不懂如何区分该说与不该说的玩笑吗？」
.message	1380		嫗丂夘	「到是你，别以为我说笑啊」
.transition 0 * 40
.stage	* ev02_155a05.png 0 0
.message	1390	hir-215_03-0089	丂峢丂	「京介，少他妈开玩笑啊你！」
.message	1400		嫗丂夘	「开玩笑怎么着了。就你，就你……！」
.message	1410			可恶，连话都无法成句的说出来了。
.message	1420		嫗丂夘	「不对，我不是想说这个」
.message	1430	hir-215_03-0091	丂峢丂	「到底是干吗啊。你到底想说什么完全不明白」
.message	1440			想说什么，吗？
.message	1450			那种东西……
.message	1460		嫗丂夘	「我……」
.message	1470		嫗丂夘	「我只是喜欢新藤而已！」
.message	1480	hir-215_03-0093	丂峢丂	「那样的话，就赶快给我滚到景那去！」
.message	1490	hir-215_03-0095	丂峢丂	「来我这不是什么改变都不会发生吗！　你白痴啊！」
.message	1500		嫗丂夘	「……！」
.transition 0 * 40
.stage	* ev02_155a06.png 0 0
.message	1510	hir-215_03-0097	丂峢丂	「让景承受痛苦的是我。但是，我却无法拯救她」
.message	1520	hir-215_03-0099	丂峢丂	「不过，如果是你的话……你如果是真心的的话……！」
.message	1530	hir-215_03-0100		广野说到这，轻轻啧了一声。
.message	1540			就算是他，只要是能帮到新藤的事毫无疑问也会想去做的吧。
.message	1550			不过，广野对新藤温柔的话，只会让她的心更加摇摆不定而已。
;■無表情
.transition 0 * 40
.stage	* ev02_155b01.png 0 0
;（フェ～ドスピ～ドは注意して。20で？）
.message	1560	hir-215_03-0101	丂峢丂	「我回去工作了」
.message	1570		嫗丂夘	「啊啊……」
.message	1580			我叹了一口气。
.message	1590			正如广野所说，不见新藤的话就无法说清楚。
.message	1600			我，还没有看清楚现实吗……。
.message	1610	hir-215_03-0103	丂峢丂	「京介」
.message	1620		嫗丂夘	「干吗」
.message	1630			不是回去的吗。
.transition 0 * 40
.stage	* ev02_155b02.png 0 0
.message	1640	hir-215_03-0105	丂峢丂	「弄哭妹妹是哥哥的特权啊」
.message	1650		嫗丂夘	「啥」
.message	1660	hir-215_03-0107	丂峢丂	「你……不要再让她哭了」
.message	1670		嫗丂夘	「…………」
.message	1680			能作到的话谁会让她哭啊
.message	1690			不过，已经晚了啊。
.message	1700		嫗丂夘	「你可没资格说别人啊。宫村，之前哭了哦」
.transition 0 * 40
.stage	* ev02_155b03.png 0 0
.message	1710	hir-215_03-0109	丂峢丂	「……是吗」
.message	1720		嫗丂夘	「就这点反应？」
.message	1730	hir-215_03-0111	丂峢丂	「没事的」
.message	1740	hir-215_03-0113	丂峢丂	「只是哭了而已，之后温柔地对待她，自然会原谅的啊」

;■シ～ン転換
;■夜空
.transition 0 * 20
.stage	* bgs_sky001a01_03.png 0 0
.message	1750			温柔…吗。
.transition 0 * 20
.stage	* ev02_156.png 0 0
.message	1760			广野和宫村的话说不定这不错。
.message	1770			但是，只有温柔的话是无法把心意传递给新藤的。
.message	1780			传递不到……？
.message	1790			不是传递不到吧。
.message	1800			我必须得把我的一切都告诉给她。
.message	1810			因为，那是…为了真正喜欢的女孩，所能作到的唯一的一件事啊。
.panel 0
;.playBGM *
.overlay * *
.transition 0 * 10
.stage	* WHITE.png 0 0
.playBGM *
.transition 0 * 10
.stage	* WHITE.png 0 0
.wait 100

.chain 216_01.sc
;■216_01へ。

;.end
