; ファイル: 216_03.txt
;ここは引き下がる。　を選択
.message	100			我想新藤已经完全明白我的话了。
.message	110			虽然是这样，她还是一副拒绝的面孔。
.message	120		嫗丂夘	「这样，不行啊」
.message	130	kei-216_03-0003	丂宨丂	「虽然感觉不好，但是，无论怎么样都不能收下。」
.message	140			新藤真的是一副抱歉的样子。
.message	150			她还在抵抗。
.message	160			不，现在的新藤的来说可能除了抵抗再没别的了。
.message	170		嫗丂夘	「我明白了。」
.message	180			已经，这样的一个东西已经起不了多大作用了吗。
.message	190			如果有能够让你改变心意的东西的话，无论用什么东西来换我也想得到它。
.message	200			但是，这样合适的东西一定，哪里都没有。
;■悲しみ
.message	210	kei-216_03-0005	丂宨丂	「看了这份电影的话，我的心一定会再次乱起来」
.message	220	kei-216_03-0007	丂宨丂	「现在不要，再让我迷惑了」
.message	230			新藤低下头。
.message	240	kei-216_03-0009	丂宨丂	「这样下去，我会哪里都去不了」
.message	250		嫗丂夘	「……我知道了」
.message	260			我点了点头，把手收了回去。
.message	270			她已经这样说了，不能强硬地让她接受。
.message	280	kei-216_03-0011	丂宨丂	「……这样」
.message	290		嫗丂夘	「哎？」
.transition 0 * 40
.stage	* ev02_159c04.png 0 0
.message	300	kei-216_03-0013	丂宨丂	「就这样，你的手就收回去了呢。」
.message	310		嫗丂夘	「不喜欢硬来」
.transition 0 * 40
.stage	* ev02_159c05.png 0 0
.message	320	kei-216_03-0015	丂宨丂	「对呢，京介前辈就是这样的人。虽然有执著的东西，但是不会硬来」
.message	330	kei-216_03-0017	丂宨丂	「这或许是一种温柔，这样的温柔却会让人受到伤害。
.message	340			到底想说些什么。
.message	350			俺甩掉我的手不是别人正是她啊……
.message	360		嫗丂夘	「你，到底希望从我哪里得到什么？？」
.transition 0 * 4
.stage	* ev02_159c06.png 0 0
.message	370	kei-216_03-0019	丂宨丂	「为什么我不告诉你就不明白呢」
.message	380		嫗丂夘	「这个……」
.message	390	kei-216_03-0021	丂宨丂	「不回答也可以」
.transition 0 * 40
.stage	* ev02_159c07.png 0 0
.message	400	kei-216_03-0023	丂宨丂	「我已经没有问这个的资格了……」
.message	410			不明白，虽然不明白。
.message	420			我现在就在深深地伤害新藤，正在挖一个不能填补的水沟。。
.message	430			这点是不用怀疑的。
;■無表情
.message	440	kei-216_03-0025	丂宨丂	「再见了，前辈。」
.message	450			为什么会这样。。
.message	460			我最不想使之受到伤害的人，却被我逼到这般境地。
.message	470			笨蛋阿，无论怎么样都是笨蛋阿。
.message	480			我这样的笨蛋没有去追从天台离开的她的资格……。
.panel 0
.playBGM *
.transition 0 * 10
.stage	* WHITE.png 0 0


;■背景：体育館（夏、１２時
;■　　　　堤京介：制服（夏
.playBGM efBGM019.ogg
.transition 1 fadeSide.png 10
.stage	* bgc_sch006a01_01.png 0 0
.panel 1
.message	490			现在已经确信了。
.message	500			在这里第一次遇到她，我就被她迷倒了。
.message	510			没有什么特殊的理由。
.message	520			只是，眼睛不能离开新藤景在赛场上的身姿。
.message	530		嫗丂夘	「但是，这样就结束了吗……」
.message	540			虽然直到现在已经有好几次经验，但是不知道会这么辛苦。
.message	550			胸口一直很苦闷。
.message	560			拿出手机，拨打电话。
.message	570			长长的拨号音仿佛是在叫人放弃，但还是接上了。
.message	580	hir-216_03-0003	丂峢丂	『……什么啊』
.transition 0 * 20
.stage	* ev02_160a01.png 0 0
;（インのタイミング、注意して）
.message	590		嫗丂夘	「不高兴的样子啊」
.message	600	hir-216_03-0005	丂峢丂	『刚刚睡下就被些什么东西吵醒，就算是神也会不高兴的吧』
.transition 0 * 40
.stage	* ev02_160a02.png 0 0
.message	610		嫗丂夘	「你，已经到早上了啊」
.message	620			果然有些惊讶。
.message	630	hir-216_03-0007	丂峢丂	『笨蛋，这里也有不方便的情况啊』
.message	640		嫗丂夘	「嘛，广野的睡眠时间无论怎么样都行吧」
.message	650	hir-216_03-0009	丂峢丂	『好个屁啊』
.message	660	hir-216_03-0011	丂峢丂	『……那么，到底什么事情』
.transition 0 * 40
.stage	* ev02_160a03.png 0 0
.message	670		嫗丂夘	「其实呢，只是想听听你的声音」
.message	680	hir-216_03-0013	丂峢丂	『你，就在那里别动，我现在就过来杀你』
.transition 0 * 40
.stage	* ev02_160a04.png 0 0
.message	690		嫗丂夘	「开玩笑的，对不起啦」
.message	700			真的会来的样子，我乖乖地道歉。。
.transition 0 * 40
.stage	* ev02_160a05.png 0 0
.message	710		嫗丂夘	「那个，其实呢」
.message	720	hir-216_03-0015	丂峢丂	『其实？』
.transition 0 * 40
.stage	* ev02_160a06.png 0 0
;（表情、注意して）
.message	730		嫗丂夘	「被小景甩了」。
.message	740	hir-216_03-0017	丂峢丂	『这样啊』
.transition 0 * 40
.stage	* ev02_160a07.png 0 0
.message	750		嫗丂夘	「……就这样啊！」
.message	760			明明是对我来说是很有冲击力的事实。
.message	770			广野也有点想说的话吧。
.message	780	hir-216_03-0019	丂峢丂	『怎么，想让我安慰你吗？』
;（ここで表情変える？）
.message	790		嫗丂夘	「……这个还是免了。」
.message	800			让广野安慰的话，总觉得很恶心。
.message	810	hir-216_03-0021	丂峢丂	『嘛，不是也是件好事吗』
.transition 0 * 40
.stage	* ev02_160a08.png 0 0
.message	820		嫗丂夘	「不好」
.message	830	hir-216_03-0023	丂峢丂	『你也是一个相当笨的笨蛋，这样稍微能清醒些了把。』
.message	840			清醒吗？
.message	850			这次是真的清醒了也说不定。
.message	860			头像是被钝器所打一样痛……
.transition 0 * 40
.stage	* ev02_160a09.png 0 0
.message	870		嫗丂夘	「……觉得我是傻瓜把」
.message	880	hir-216_03-0025	丂峢丂	『啊，无论怎么样也是笨蛋。』
.message	890	hir-216_03-0027	丂峢丂	『听到景和你的事情的时候，只是吓了一跳，感觉不坏』
.message	900	hir-216_03-0029	丂峢丂	『这也只是我的一厢情愿的想法吗』
.transition 0 * 40
.stage	* ev02_160a10.png 0 0
;☆（この後の京介の表情構築はしっかりと）
.message	910		嫗丂夘	「抱歉……」
.message	920	hir-216_03-0031	丂峢丂	『没有什么啦，这也是其中一个结果吧。』
.message	930	hir-216_03-0033	丂峢丂	『清醒了的话这样也好。』
.message	940			真的是这样吗。
.message	950			至少，我并不期望着这样的结果。
.message	960		嫗丂夘	「哪，广野」
.message	970	hir-216_03-0035	丂峢丂	『嗯？』
.message	980		嫗丂夘	「我已经是第几次遇到这样的痛苦了。」
.message	990	hir-216_03-0037	丂峢丂	『那是你自作自受吧。』
.message	1000		嫗丂夘	「但是，很痛啊。感到这么痛，还是第一次啊。」
.message	1010	hir-216_03-0039	丂峢丂	『这样很好啊。』
.message	1020		嫗丂夘	「还是这样的说，说些别的什么话吧」
.message	1030	hir-216_03-0041	丂峢丂	『你，不是直到现在为止和女孩子分别的之后仍然一副没事的样子吗』
.message	1040	hir-216_03-0043	丂峢丂	『但是，这次的你不是这样吧？』
.message	1050			啊啊──
.message	1060			是这样啊。
.message	1070			虽然对不起到目前为止所交往的女孩子。
.message	1080			新藤景对于我来说，是比谁都特殊的女孩子。。
.message	1090			和她在一起的话。
.message	1100			一定会看到一直没发现的很重要的东西。
.message	1110			有这样的预感。
.message	1120	hir-216_03-0045	丂峢丂	『一定要记着这种痛苦啊。这样的话，总有一天会把失去的东西拿回来的。』
.message	1130		嫗丂夘	「……什么时候变得象伟人的一样了啊，广野」
.message	1140	hir-216_03-0047	丂峢丂	『笨蛋！我是在睡眠不足的情况下脑子转不过来，那有一一给你考虑措辞的精力啊』
.message	1150	hir-216_03-0049	丂峢丂	『总之，我去睡了。』
.message	1160		嫗丂夘	「……啊啊，不好意思阿。」
.transition 0 * 20
.stage	* ev02_160b01.png 0 0
;（フェードスピードと表情は注意して）
.message	1170			就这样，广野没怎么问候就挂了电话。
.message	1180			看来已经是困到问候的精力都没了。
.message	1190			就算是这样也跟我聊了这么久，他还真是一个挺不错的人啊。
.transition 0 * 40
.stage	* ev02_160b02.png 0 0
.message	1200		嫗丂夘	「呼……」
.message	1210			和广野比起来，我怎么样呢？
.message	1220			既不温柔，也不受人欢迎。
.message	1230			而且被喜欢的女孩子甩掉。
.message	1240			还真的一点优点都没。
;（ここから161を？それとも表情をb01差分に？）
.message	1250		嫗丂夘	「结果，我只是这样的啊」
.transition 0 * 20
.stage	* ev02_161.png 0 0
.message	1260			不觉意间拿出了摄像机。
.message	1270			显示在摄像机的液晶显示屏上面的只是个空白的舞台。
.message	1280			拍这些东西根本不有趣。
.message	1290			只是因为喜欢新藤，所以希望她能够出现在我的电影上面。
.message	1300			拍摄没有她的世界的话，这绝对不是算是电影。
.message	1310			我坐在床上。
.message	1320			总有一天。
.message	1330			总有一天会忘记这种感觉的吧。
.message	1340			抱着无法回答的问题，我按下影片的播放键。


;■御影チェック
;■　キー入力無効
.pragma disable_control

;■御影チェック
;.transition 0 * 20
.transition 0 * 10
.stage	* BLACK.png 0 0
.message	1350			突然间她的身影出现了。\a
.wait 250
.message	1360			不断地，不断地。\a
.wait 250
.message	1370			不断地换着表情的新藤景。\a
.wait 270
.message	1380			毫无笑容的面容，愤怒的面容，悲伤的面容──\a
.wait 320
.message	1390			我一直在看着新藤。\a
.wait 270
.message	1400			没有实现的愿望。\a
.wait 250
.message	1410			溶化在了这刺目的夏日的阳光之中……。\a
.wait 350


.panel 0
.playBGM * 0 6
.transition 0 * 10
.stage	* BLACK.png 0 0
.wait 300
.HSVfilter 0 0 0 0 0 0
.overlay * *
;■BAD　END_01


;■御影チェック
;■　キー入力有効
.pragma enable_control

.end
