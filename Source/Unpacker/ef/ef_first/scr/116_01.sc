; ファイル: 116_01.txt
;■＜１章：１６日目＞
;■画面黒
.transition 0 * 10
.stage	* bgc_home001a01_00.png 0 0
;（キャラのせてませんが，とりあえずワザとで）
;（通常背景でインしてますが，問題あるようなら切り出しで）
.panel 1
.message	100			为了能让我和她的安身之处可以存续。
.message	110			为了可以做自己想做的事情。
.message	120			我，决定了再不会拖延我所决定的事──
.transition 0 * 10
.stage	* WHITE.png 0 0
.message	130			…………
.message	140			……


;■背景：教室（冬，８時
;■　　　　广野纮：制服（冬）
;■　　　　堤京介：制服（冬）
.playSE kyoushitsu_door_open.ogg f 0 *
.playBGM efBGM027.ogg
.transition 0 * 10
.stage	* bgw_sch004m01_00.png 0 0
;.stage	* bgc_sch004a01_00.png 0 0
;（通常背景でインしてますが，問題あるようなら切り出しで）
.message	150			咯啦。
.message	160			打开教室的门，一边向已经到校的同学们打着招呼，一边走向自己的位置。
.message	170	kyo-116_01-0003	嫗丂夘	「哟～早」
.transition 0 * 20
.stage	* ev01_199a01.png 0 0
;（切り替えタイミング，注意のこと）
.message	180			然后停在了京介的位置旁边。
.message	190		丂峢丂	「哟早」
.transition 0 * 20
.stage	* ev01_199a03_mugai_a.png 0 0
;（ここ，必要なら切り出しを）
.message	200		丂峢丂	「……你丫，脸有些红吧？」
.message	210	kyo-116_01-0009	嫗丂夘	「啊啊，我对广野君的心情一不小心便浮上了脸」
.transition 0 * 20
.stage	* ev01_199a02.png 0 0
.message	220		丂峢丂	「要是你害羞的话，会只有一个脸颊红吗」
.message	230			真是厉害啊。
.message	240			说起来，肯定又是被女朋友打了吧。
.transition 0 * 40
.stage	* ev01_199a03.png 0 0
;（ここでa03表情で良いか？フェードスピードにも注意して）
.message	250	kyo-116_01-0013	嫗丂夘	「无所谓的嘛，这也是交流情感的一种啊。不打不成交，这不是老话了吗」
.message	260		丂峢丂	「那是男人之间好吧！」
.message	270			男人被女人打，怎么想都不算什么好事。
.transition 0 * 40
.stage	* ev01_199a03_close.png 0 0
.message	280	kyo-116_01-0017	嫗丂夘	「才没那回事。她打的时候，也就是还对我有兴趣的表现哦。这叫还没结束」
.transition 0 * 40
.stage	* ev01_199a02.png 0 0
.message	290	kyo-116_01-0019	嫗丂夘	「如果真的没感觉的的话，那时会什么都不做才对」
.message	300		丂峢丂	「……是啊。说不定是如此」
.message	310			虽然有些不服气，但人生经验方面看来还是京介比我强些。
.message	320			和一直在家啃笔杆──才刚刚开始和人有所关联的我不一样。
.message	330		丂峢丂	「京介。你…确实很厉害啊」
.transition 0 * 40
.stage	* ev01_199b01.png 0 0
;（フェードスピードは40でも？）
.message	340	kyo-116_01-0025	嫗丂夘	「……嗯？你有什么目的？」
.message	350			京介装出一副害怕的想要逃跑的表情。
.message	360	kyo-116_01-0027	嫗丂夘	「钱吗！？　难，难道是我的身体吗！？　我，我坚守至今的童贞啊～～！！」
.message	370		丂峢丂	「你就只会往恶心的地方想吗！」
.message	380			这家伙已经完全腐化了啊。
.message	390			不能再和他来往下去了……。
.transition 0 * 40
.stage	* ev01_199b02.png 0 0
;（ここで京介の表情，a02に変えても問題ないか？）
.message	400		丂峢丂	「我说你就改改那坏毛病，好好的活下去吧」
.transition 0 * 40
.stage	* ev01_199b03.png 0 0
.message	410	kyo-116_01-0033	嫗丂夘	「……广野，你出什么事了吗？」
.message	420			京介用认真的表情盯着我。
.message	430		丂峢丂	「不～啊，没什么」
.message	440			我轻轻摇了摇头。
.message	450		丂峢丂	「只是…决定了自己该站在哪里而已」
.panel 0
.transition 0 * 10
.stage	* WHITE.png 0 0


;■背景：体育館（冬，１０時
;■　　　　广野纮：制服（冬）
;■　　　　新藤景：制服（冬）
.playSE kei_ring.ogg f 0 *
.transition 1 fadeSide.png 10
.stage	* ev01_200a01.png 0 0
;（画面，揺らすように。ボールなしから入って，唐突にボールをインさせて画面揺らす演出にするか？）
.panel 1
.message	460			嘭！
.transition 0 * 20
.stage	* ev01_200b01.png 0 0
;（フェードスピードは40でも？）
.message	470			篮球撞上了篮板然后弹向一边。
.playSE kei_ball_korogaru.ogg f 0 *
;（もっとバウンドしてる効果音を？）
.message	480			然后就那样滚到了我这边。
.message	490		丂峢丂	「哟」
.playSE *
.transition 0 * 20
.stage	* bgc_sch006a01_01.png 0 0
;（通常背景のインのタイミング，注意して）
.message	500			我捡起球，走近那个站在罚球线旁边的人影。
.transition 0 * 20
.stage	* bgc_sch006a01_01.png 0 0 st_kei01a03.png 380
;（立ち絵のインのタイミング，注意して）
.message	510	kei-116_01-0003	丂宨丂	「既然把人家喊出来，就别迟到好吧」
.message	520		丂峢丂	「抱歉，抱歉。稍微被个笨蛋浪费了点时间」
.message	530			第1、2节课之间的休息时间。
.message	540			让景等着的我，被京介的「你要去哪」咬住不放。
.message	550			看起来还是在意上次那赌博的结果的样子。
.message	560			那家伙大概在以他的方式，那种笨蛋般的吵闹方式想让我轻松起来也说不定。
.message	570			希望这不是我自作多情。
.message	580		丂峢丂	「嘛，还有时间不无所谓嘛」
.transition 0 * 40
.stage	* bgc_sch006a01_01.png 0 0 st_kei03a05.png 380
;（表情には注意して。a03が妥当？）
.message	590	kei-116_01-0005	丂宨丂	「再怎么说，我又不是像哥哥那样的不良学生。我可不想被在上课途中喊出来」
.message	600		丂峢丂	「偶尔逃逃课不也挺好吗」
.transition 0 * 40
.stage	* bgc_sch006a01_01.png 0 0 st_kei03a06.png 380
.message	610	kei-116_01-0007	丂宨丂	「一点都不好。一直在注意着老师看到了怎么办之类的」
.message	620		丂峢丂	「没事啦，没事啦」
.message	630			这个时间没有任何一个班级用体育馆，这里应该谁也不会来才对。
.message	640		丂峢丂	「你还真是认真啊」
.transition 0 * 40
.stage	* bgc_sch006a01_01.png 0 0 st_kei03a03.png 380
;（表情注意して。「冷笑」使ってますが，，，）
.message	650	kei-116_01-0009	丂宨丂	「我这已经算很小心了啊。我可作不到哥哥你们那样那么大胆」
.message	660	kei-116_01-0010		景露出看傻瓜的神情，轻轻的哼笑了一声。
.transition 0 * 40
.stage	* bgc_sch006a01_01.png 0 0 st_kei04a06.png 400
.message	670	kei-116_01-0011	丂宨丂	「话说回来，到底什么事呢？　哥哥，又正大光明的逃课……」
.message	680		丂峢丂	「那已经无所谓了」
.transition 0 * 40
.stage	* bgc_sch006a01_01.png 0 0 st_kei04a04.png 400
;（a05でも？）
.message	690	kei-116_01-0013	丂宨丂	「一点都不好。想要和我当同级生么？」
.message	700			一如既往，景是在认真的担心我。
.message	710			虽然说话恶口，但却决定不会说伤害到人的话。
.message	720			真是温柔呢，景。
.message	730		丂峢丂	「我，决定了」
.message	740		丂峢丂	「放弃学校，专心画漫画」
.transition 0 * 40
.stage	* bgc_sch006a01_01.png 0 0 st_kei04a06.png 400
;（a05表情でも？）
.message	750	kei-116_01-0015	丂宨丂	「诶……？」
.message	760		丂峢丂	「本来，作业余职业太奇怪了啦。中途半端的作下去，可是没法画出象样的作品啊」
.message	770		丂峢丂	「喜欢漫画的你，应该能明白吧」
.transition 0 * 40
.stage	* bgc_sch006a01_01.png 0 0 st_kei02a03.png 3801
;（表情注意して）
.message	780	kei-116_01-0017	丂宨丂	「不……不是明白不明白的问题吧！　我说你，白痴吗！」
.transition 0 * 40
.stage	* bgc_sch006a01_01.png 0 0 st_kei01a06.png 380
;（↑の02a03と入れ替える？）
.message	790	kei-116_01-0019	丂宨丂	「到底在想些什么啊，哥哥！　要休学！？」
.message	800		丂峢丂	「3学期还是会上下去。虽然没什么大改变，至少把2年级上完吧」
.transition 0 * 40
.stage	* bgc_sch006a01_01.png 0 0 st_kei05a07.png 400
.message	810	kei-116_01-0021	丂宨丂	「干吗啊，发生什么事了？　为什么会突然说出这样的话啊？」
.transition 0 * 40
.stage	* bgc_sch006a01_01.png 0 0 st_kei05a04.png 400
;（表情注意して）
.message	820			说到这儿，景突然闭上了嘴唇。
.message	830			她紧紧捏起拳头，一瞬视线有些彷徨──
.message	840			然后再次说出话来。
.transition 0 * 40
.stage	* bgc_sch006a01_01.png 0 0 st_kei05a08.png 400
.message	850	kei-116_01-0023	丂宨丂	「和宫村前辈有关吗？」

;■御影チェック
;.message	860		丂峢丂	「ない，とは言い切れないけど俺が自分で決めたことだよ。宫子はなにも言わない」
.message	860		丂峢丂	「虽然不能清楚的说『没有』，但这是我自己的决定。宫子她什么都没有说」

.transition 0 * 40
.stage	* bgc_sch006a01_01.png 0 0 st_kei05a03.png 400
.message	870	kei-116_01-0025	丂宨丂	「……已经决定了吗？」
.message	880		丂峢丂	「啊啊，决定了」
.message	890			为了画出不会被羽山瑞希跳过不读的漫画。
.message	900			梦想不应该这么早就结束。
.message	910			我，不会半途而废。
.message	920			为了追梦的自己。
.message	930			为了能让那所有包容我的读者和编辑看到我的梦想。
.transition 0 * 40
.stage	* bgc_sch006a01_01.png 0 0 st_kei05a03_close.png 400
.message	940	kei-116_01-0027	丂宨丂	「是吗」
.message	950	kei-116_01-0028		景轻轻呼出一口气。
.transition 0 * 40
.stage	* bgc_sch006a01_01.png 0 0 st_kei05a02_close.png 400
.message	960	kei-116_01-0029	丂宨丂	「哥哥一直都是这个样子。自己决定一切，独自奔向前方呢」
.message	970		丂峢丂	「我只是作自己想作的事情，以及做我自己可以作到的事情而已」
.message	980	kei-116_01-0031	丂宨丂	「但是……」
.transition 0 * 40
.stage	* bgc_sch006a01_01.png 0 0 st_kei05a02.png 400
.message	990	kei-116_01-0033	丂宨丂	「正是因为哥哥是这样的人，我才会喜欢」
.message	1000	kei-116_01-0035	丂宨丂	「一直都是闪闪发亮。实现自己的梦想，做自己想做的事。就算痛苦……也会坚持到最后完成的哥哥」
.message	1010		丂峢丂	「我还没那么伟大。而且，是因为你在看着我才会努力」
.transition 0 * 40
.stage	* bgc_sch006a01_01.png 0 0 st_kei05a01.png 400
.message	1020	kei-116_01-0037	丂宨丂	「我吗……？」
.message	1030		丂峢丂	「虽然没有血缘，但想要在称呼自己哥哥的女孩面前装酷啊」
.message	1040			回想起来──
.message	1050		丂峢丂	「对孤独的我温柔的你，说不定就是为了让你愉快──我才开始画漫画」
.message	1060			该说那时是喜欢景吗。
.message	1070			虽然，过去的心情都已回忆不清。
.message	1080			但正是有景，才会有现在的我。
.message	1090		丂峢丂	「嘛，到了最后，只是让你看了不光彩的地方呢」
.transition 0 * 40
.stage	* bgc_sch006a01_01.png 0 0 st_kei05a02_close.png 400
.message	1100	kei-116_01-0039	丂宨丂	「没那回事。没那回事……只是」
.message	1110	kei-116_01-0041	丂宨丂	「我对哥哥只有憧憬而已」


;.message	1120	kei-116_01-0043	丂宨丂	「優しい言葉をかけられたり，ちょっと触られるだけで嬉しくてたまらなかった。でも，自分からはなにもしようとしてなかったわ」
.message	1120	kei-116_01-0042	丂宨丂	「温柔的和我说说话，稍微摸摸我就会喜悦万分」
.message	1125	kei-116_01-0044	丂宨丂	「但是，我自己却什么都没有做」


.message	1130			景咬住了自己的嘴唇。
.message	1140	kei-116_01-0045	丂宨丂	「仅仅看着就好──这样骗着自己」
.message	1150			沉默起来。
.message	1160			谁都说不出话，安静的让人着急。
.message	1170			该说些什么好呢。
.message	1180			我不想伤害景。
.message	1190			也不想伤害我自己。
.message	1200			仅仅想着这些，却说不出一句话来。
.transition 0 * 40
.stage	* bgc_sch006a01_01.png 0 0 st_kei03a03.png 380
;（表情，注意して）
.message	1210	kei-116_01-0047	丂宨丂	「我呢，超讨厌宫村前辈」
.message	1220		丂峢丂	「景……」
.transition 0 * 40
.stage	* bgc_sch006a01_01.png 0 0 st_kei03a05.png 380
;☆（a05は「ひらめき」っぽく，口の開きが大きいのか，，，ちょっと保留）
.message	1230	kei-116_01-0049	丂宨丂	「但是，那个只是憧憬却什么都不说的我……」
.message	1240	kei-116_01-0051	丂宨丂	「想要被哥哥不只当作妹妹，而作为一个女孩子看待的原因」
.transition 0 * 40
.stage	* bgc_sch006a01_01.png 0 0 st_kei04a04.png 400
;（表情，注意して）
.message	1250	kei-116_01-0053	丂宨丂	「大概是因为…宫村前辈的出现吧。正因如此，我才鼓起了告白自己心情的勇气」
.transition 0 * 40
.stage	* bgc_sch006a01_01.png 0 0 st_kei04a02.png 400
;（表情，注意して）
.message	1260	kei-116_01-0055	丂宨丂	「对于这点我表示感谢」
.transition 0 * 40
.stage	* bgc_sch006a01_01.png 0 0 st_kei02a02.png 380
;（表情，注意して）
.message	1270	kei-116_01-0057	丂宨丂	「果然讨厌的还是讨厌呢」
.message	1280			景明显的在勉强自己。
.message	1290			虽然她的脸上的痛楚，和那娇小的身躯仿佛立刻就会崩溃的感觉让人不忍看下去。
.message	1300			但只有我，不能把目光离开现在的景。
.transition 0 * 40
.stage	* bgc_sch006a01_01.png 0 0 st_kei01a05.png 380
;（表情，注意して。目つむりの連続なので避ける？）
.message	1310	kei-116_01-0059	丂宨丂	「哥哥，把球给我」
.message	1320		丂峢丂	「嗯？　啊啊」
.message	1330			我嗖的把球传了过去。
.playSE kei_dribble_twice.ogg f 0 *
.transition 0 * 20
.stage	* ev01_201.png 0 0
;（フェードのさせ方にも注意のこと。小曽根フェードを？）
;（効果音はあえて入れないのがきれいか？ラストなんで）
.message	1340			接到的景，在那带了两下球。
.playSE kei_shoot.ogg f 0 *
.transition 0 * 20
.stage	* ev01_202.png 0 0
;（フェードのさせ方にも注意のこと。小曽根フェードを？）
.message	1350			用那不知用几千次，几万次而熟练起来的手法光滑的投出了球。
.message	1360			划出绮丽的弧线，球旋转着就要被篮框吸进去了──

;■御影チェック
.playBGM *
.wait 10

.playSE kei_ring.ogg f 0 *
.transition 0 * 20
.stage	* ev01_200a01.png 0 0
；（画面揺らすか？）
.message	1370			嘭。
.transition 0 * 20
.stage	* ev01_200b01.png 0 0
.message	1380		丂峢丂	「啊……」
.playSE kei_ball_korogaru.ogg f 0 *
.message	1390			篮球再次无情的撞上篮板，啪的掉了下来。
.transition 0 * 20
.stage	* ev01_203.png 0 0
;（フェードスピードは10でもいいかもしれません）
.message	1400	kei-116_01-0061	丂宨丂	「啊～啊」
.message	1410	kei-116_01-0063	丂宨丂	「又失误了呢。完全不行呢」
.message	1420		丂峢丂	「……我说你，状态不太好吗」

;■御影チェック
;■　止める場所が違う。
;■　この流れで止めるなら，ゴールできなかった瞬間か。
;.playBGM *

;.playBGM efBGM047.ogg
.transition 0 * 20
.stage	* ev01_203_mugai_b.png 0 0
;.stage	* ev01_203_mugai_a.png 0 0
.message	1430	kei-116_01-0065	丂宨丂	「稍微有点……」
;.playBGM efBGM047.ogg


;■御影チェック
;.playBGM efBGM016.ogg


.message	1440			景回答着，走到我可以触碰到她的距离。

;■御影チェック
.playBGM efBGM016.ogg

.transition 0 * 20
.stage	* ev01_204a01.png 0 0
.message	1450	kei-116_01-0067	丂宨丂	「膝盖嗯」
.message	1460		丂峢丂	「膝盖？」
.transition 0 * 20
.stage	* ev01_204a02.png 0 0
;（フェードスピードは注意して）
;.transition 0 * 20
;.stage	* ev01_204a_mugai_a.png 0 0
;.transition 0 * 20
;.stage	* ev01_204a.png 0 0
.message	1470	kei-116_01-0069	丂宨丂	「之前比赛时碰到的膝盖有些痛呢……」
.transition 0 * 20
.stage	* ev01_204a_mugai_a.png 0 0
;（ここの涙の演出はしっかりと。必要なら切り出しか新規画像発注を）
.message	1480			瞬间，景的脸上划出一道泪痕。
.message	1490		丂峢丂	「景……？」
;.playBGM efBGM047.ogg
.transition 0 * 20
.stage	* ev01_204a03.png 0 0
;.transition 0 * 20
;.stage	* ev01_204a01.png 0 0
.message	1500	kei-116_01-0071	丂宨丂	「膝盖好痛……。因为痛而哭起来好像小孩子一样呢」
.message	1510			这么说着，景的眼泪却完全停不下来。
.message	1520			虽然我是白痴，但也不会被这样的谎骗到。
.message	1530			到哭的时候，就不必逞强了吧。
.transition 0 * 20
.stage	* ev01_204a04.png 0 0
;（フェードスピード，ここは40で？）
.message	1540	kei-116_01-0073	丂宨丂	「转头……看那边啊。这样的…样子……不要看好吧」
.message	1550			这个逞强的家伙啊……。
.message	1560			这家伙从小时侯就是这个样子。
.message	1570			一直喜欢逞强，讨厌被人看到弱处。
.message	1580			我拼命抑制住想要抱住景的双肩的冲动。
.message	1590			这种半途的温柔，只会更伤害景而已。
.message	1600			因为我背叛了景的心情──是千真万确的事实。
.message	1610	kei-116_01-0075	丂宨丂	「……为什么这样？　为什么我就不行……？」
.message	1620		丂峢丂	「说为什么……」
.message	1630	kei-116_01-0077	丂宨丂	「我的心情，你不是也了解吗。因为……分明知道……我……不会说谎的…………」
.message	1640	kei-116_01-0079	丂宨丂	「想要让你…喜欢景啊……」
.message	1650			理由──简单得不能再简单。
.message	1660			仅仅一句话就可以说明。
.message	1670			因为我──遇见了宫村宫子。
.message	1680			但是，只有这点绝对不可以说出口。
.transition 0 * 20
.stage	* ev01_204b01.png 0 0
;（ここで顔あげるタイミングで問題ないか？）
.message	1690	kei-116_01-0081	丂宨丂	「哥哥……我有一个请求」
.message	1700			一边抽噎着，景抬起头看向我。
.message	1710	kei-116_01-0083	丂宨丂	「虽然之前约好不在人前喊哥哥的……」
.transition 0 * 20
.stage	* ev01_204b02.png 0 0
.message	1720	kei-116_01-0085	丂宨丂	「但从此以后，让我一直喊哥哥吧。至少……至少，想要还当作妹妹……」
.message	1730		丂峢丂	「笨蛋。以前说笑啊，其实不喊前辈什么的才好」
.transition 0 * 20
.stage	* ev01_204b03.png 0 0
.message	1740	kei-116_01-0087	丂宨丂	「好过分，哥哥果然是坏心眼呢……」
.message	1750		丂峢丂	「当老哥的大部分…都是坏心眼吧」
.message	1760	kei-116_01-0089	丂宨丂	「是啊，我们真的就跟真正的兄妹一样……」
;（ここでb03表情を？）
.message	1770	kei-116_01-0091	丂宨丂	「也许一直当妹妹就好吧……。像哥哥这样的乖僻的人能找到女朋友……也许为这个高兴就好吧」
.message	1780			景的泪水染遍双颊，努力的挤出微笑。
.message	1790	kei-116_01-0093	丂宨丂	「那个，从妹妹这里再有一个请求可以吗？」
.message	1800		丂峢丂	「当然」
.message	1810	kei-116_01-0095	丂宨丂	「哥哥」
.message	1820	kei-116_01-0097	丂宨丂	「膝盖好痛……想要你稍微支撑我一会呢」
.message	1830			景的真意暂且不论，单单是作为妹妹的请求的话。
.message	1840			我想要接受。
.message	1850			如果什么都说不出的话，至少这些…
.transition 0 * 20
.stage	* ev01_205a02.png 0 0
;（ここ，205の切り出しで？ただ，多用しすぎか？）
.message	1860	kei-116_01-0099	丂宨丂	「啊……」
;★イベントＣＧ
.message	1870			我把景小小的头抱向胸口，环住她的腰。
.transition 0 * 20
.stage	* ev01_205a03.png 0 0
.message	1880	kei-116_01-0101	丂宨丂	「哥哥……」
.message	1890			认真的支持起失去力气的景的身体。
.message	1900			景真的好轻啊……。
.message	1910	kei-116_01-0103	丂宨丂	「呜……」
.transition 0 * 20
.stage	* ev01_205a01.png 0 0


;.message	1920	kei-116_01-0105	丂宨丂	「帰りたい……帰りたいよ……。お兄ちゃんとずっと一緒にいられた頃に……わたしのお兄ちゃんでいてくれた頃に……」
.message	1920	kei-116_01-0104	丂宨丂	「想要回去……」
.message	1925	kei-116_01-0106	丂宨丂	「想要回去啊……。那和哥哥一直在一起的日子……作着我的哥哥的日子……」


.message	1930	kei-116_01-0107	丂宨丂	「哥哥……」
.message	1940	kei-116_01-0108		景也会这样爱哭这样撒娇啊。
.message	1950			一直都在逞强……一直都没能哭过没能撒娇过啊。
.message	1960			我如果更温柔些的话，大概就不会这样了吧……。
.message	1970	kei-116_01-0109	丂宨丂	「分明不……想哭…的啊」
.message	1980		丂峢丂	「景」
.message	1990	kei-116_01-0111	丂宨丂	「别担心……马上…就可以用自己的脚站起来的……」
.message	2000		丂峢丂	「不必着急……」
.message	2010			现在撒娇就可以了。
.message	2020			现在还可以。
.message	2030			嗯，没事的。
.message	2040			景一定可以站起来。
.message	2050			站起来，向往常一样走下去。
.message	2060			是吧，景。
.message	2070			对不起呢，景……。
.panel 0
.playBGM *
.transition 0 * 10
.stage	* WHITE.png 0 0


.chain 117_01.sc
;■117_01へ。

;.end
