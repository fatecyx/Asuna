; ファイル: 204_01.txt
;■＜２章：４日目＞
;■背景：通学路（夏，７時
;■　　　　堤京介：制服（夏）
;■　　　　新藤景：制服（夏）
.playBGM efBGM051.ogg
;.playBGM BGM054_sample.ogg

;■御影チェック
;■　ファインダ～モ～ドになる前にカウンタ～をリセット。
;■　ここは，これが撮り始めの場面なので念のため。
;■　　というか，ファインダ～モ～ドの前後を挟んでおかないと危ないかな。
.set finderCounter = 0

.frame finder.png
.set finderCounter = 0
.screen sc_morning01.png sc_morning01.png
.overlay * or_kei00a.png
.transition 0 * 10
.stage	* bgs_normal019a01_00_faceup.png 0 0 st_kei09b01.png 550
;☆（ぼかしはまだ入れていません。立ち絵の座標も仮です）
;.stage	* bgs_normal019m01_00.png 0 0
;（モブはとってもいい？ここは映画の内容もきちんと理解して構築していくこと）
.panel 1
.message	100		嫗丂夘	「OK，开始录了哦～」
.message	110	kei-204_01-0003	丂宨丂	「…………」
.message	120			而出现在液晶屏上的新藤只是向这边盯着，却一言不发。
.message	130		嫗丂夘	「新藤，听到了吗？　已经开始了哦」
.transition 0 * 40
.stage	* bgs_normal019a01_00_faceup.png 0 0 st_kei09b05.png 550
;（表情には注意して）
.message	140	kei-204_01-0005	丂宨丂	「听，听到了啦」
.message	150		嫗丂夘	「听到就好，那僵着干吗？」
.message	160	kei-204_01-0007	丂宨丂	「真烦人啊你」
.transition 0 * 40
.stage	* bgs_normal019a01_00_faceup.png 0 0 st_kei09b04.png 550
;（表情，注意して。この前文でこの表情を？）
.message	170	kei-204_01-0009	丂宨丂	「还不适应被镜头对着啊，没办法的吧！」
.message	180		嫗丂夘	「是吗，缺乏亲情而长大的吗……」
.transition 0 * 40
.stage	* bgs_normal019a01_00_faceup.png 0 0 st_kei09b06.png 550
.message	190	kei-204_01-0011	丂宨丂	「才不是！」
.message	200	kei-204_01-0013	丂宨丂	「被你这样的怪男人拿摄像机对着肯定会僵硬的啊！」
.message	210		嫗丂夘	「别介意，别介意。会给拍的很漂亮的哦～」
.transition 0 * 40
.stage	* bgs_normal019a01_00_faceup.png 0 0 st_kei09b07.png 550
.message	220	kei-204_01-0015	丂宨丂	「小看我吗你！」
.message	230		嫗丂夘	「生气的表情也好棒<音乐符号>」
.transition 0 * 40
.stage	* bgs_normal019a01_00_faceup.png 0 0 st_kei11b03_close-.png 450
;☆（歩きスクロ～ル用立ち絵を使う場合は，座標位置など諸々注意して）x
;☆（ここ，目つむりを？）
.message	240	kei-204_01-0017	丂宨丂	「哼……我终于明白了」
.message	250			新藤的身体晃了一晃。
.transition 0 * 40
.stage	* bgs_normal019a01_00_faceup.png 0 0 st_kei09b06.png 550
.message	260	kei-204_01-0019	丂宨丂	「好吧，别再罗嗦了，来吧！」
.message	270		嫗丂夘	「为什么非得打架不可」
.transition 0 * 40
.stage	* bgs_normal019a01_00_faceup.png 0 0 st_kei09b04.png 550
.message	280	kei-204_01-0021	丂宨丂	「你丫，在很开心地拿我玩没错吧」
.message	290			哦哦，这还真是严重被怀疑了啊。
.message	300		嫗丂夘	「虽然我不否定是在玩」
.transition 0 * 40
.stage	* bgs_normal019a01_00_faceup.png 0 0 st_kei09b06.png 550
.message	310	kei-204_01-0023	丂宨丂	「你说什么混蛋！」
.message	320			这女孩，偶尔会说话跟男生似的啊……。
.message	330		嫗丂夘	「只是愉快的做下去而已啦。别想太多，轻松轻松」
.transition 0 * 40
.stage	* bgs_normal019a01_00_faceup.png 0 0 st_kei11b03_close-.png 450
;.stage	* bgs_normal019a01_00_faceup.png 0 0 st_kei09b07.png 550	
;（表情，注意して）
.message	340	kei-204_01-0025	丂宨丂	「真是的，算什么吗……」
.message	350			新藤放弃般地说了一句，轻轻摇了下头。
.transition 0 * 40
.stage	* bgs_normal019a01_00_faceup.png 0 0 st_kei10b05-.png 450
;.stage	* bgs_normal019a01_00_faceup.png 0 0 st_kei09b05.png 550
.message	360	kei-204_01-0027	丂宨丂	「说起来，忘了一件事呢」
.message	370		嫗丂夘	「怎么？」
.message	380	kei-204_01-0029	丂宨丂	「我到现在还是不明白你的目的」
.message	390		嫗丂夘	「目的……您指的是？」
.message	400	kei-204_01-0031	丂宨丂	「拍了电影，然后呢？　参加比赛吗？」
.message	410		嫗丂夘	「不不，那我完全没想过哦」
.message	420			仅仅是拍摄能够参与比赛的作品的话，再怎么说我也会留在摄影研究部的吧。
.transition 0 * 40
.stage	* bgs_normal019a01_00_faceup.png 0 0 st_kei09b01.png 550
;（表情，注意して）
.message	430	kei-204_01-0033	丂宨丂	「那…为了什么？　要让拍了我的这份胶卷在你那腐烂掉吗！？」
.message	440		嫗丂夘	「我会认真地珍视它，一遍又一遍地看到胶卷断掉为止」
.transition 0 * 40
.stage	* bgs_normal019a01_00_faceup.png 0 0 st_kei09b07.png 550
;（表情，注意して。b03表情で？）
.message	450	kei-204_01-0035	丂宨丂	「你果然是个变态！」
.message	460		嫗丂夘	「就算你再怎么骂，为了拍出好的画面我可是不惜一切的哦」
;☆（ここ，目つむりを？）
.message	470	kei-204_01-0037	丂宨丂	「真是装正经啊……」
.message	480			就算被讨厌，我也会追着新藤绝不会让她逃掉。
.message	490			因为我已经下定决心。
.message	500		嫗丂夘	「而且你不是也说了吗。想拍你可以，不要随便就给别人看什么的」
.message	510			这就是新藤同意出演时给出的条件。
.message	520			当然，我是完全无所谓。
.message	530			因为既不是要参加比赛也不是什么商业作品嘛。
.message	540		嫗丂夘	「给谁看之类以后再考虑就好。现在我只想集中摄影而已」
.transition 0 * 40
.stage	* bgs_normal019a01_00_faceup.png 0 0 st_kei09b01.png 550
;（表情，注意して）
.message	550	kei-204_01-0039	丂宨丂	「不过，你难道想一直就这么追着我拍摄不成？」
.message	560		嫗丂夘	「当然」
.message	570		嫗丂夘	「我会从金色的摇篮追至灰白的墓碑」
.transition 0 * 40
.stage	* bgs_normal019a01_00_faceup.png 0 0 st_kei09b06.png 550
.message	580	kei-204_01-0041	丂宨丂	「你难道想一生跟着我吗！」
.message	590		嫗丂夘	「说笑而已啦」
.transition 0 * 40
.stage	* bgs_normal019a01_00_faceup.png 0 0 st_kei09b04.png 550
;（表情，注意して）
;.stage	* bgs_normal019a01_00_faceup.png 0 0 st_kei09b03.png 550
.message	600	kei-204_01-0043	丂宨丂	「这个没用的家伙……」
.message	610			被她那可怕的目光盯了一下，我不由缩了缩头。
.transition 0 * 40
.stage	* bgs_normal019a01_00_faceup.png 0 0 st_kei09b05.png 550
.message	620	kei-204_01-0045	丂宨丂	「跟在女生后面转圈，完全的可疑人物嘛。在学校里也要拍吗？」
.message	630		嫗丂夘	「啊，没室没事。我从一年级开始就一直抱着摄像机走来走去了」
.message	640		嫗丂夘	「老师同学无论谁到现在也不会觉得奇怪了啦」
;■呆れ
;☆（ここ，目つむりを？）
.message	650	kei-204_01-0047	丂宨丂	「那种东西一点也不值得骄傲…」
.panel 0
.playBGM *
.frame *
.screen * *
.overlay * *
.transition 0 * 10
.stage	* WHITE.png 0 0


;■背景：学園·階段（夏，１３時
;■　　　　堤京介　　：制服（夏）
;■　　　　宫村宫子：制服（夏）
.playBGM efBGM010.ogg
.transition 1 fadeSide.png 10
.stage	* ev02_037a01.png 0 0
;（階段を挿む？）
.panel 1
.message	660			在食堂吃过午饭，回教室的途中。
.message	670			发现和几个朋友一起走着的宫村宫子。
.message	680		嫗丂夘	「…………」
.message	690			分明当年我搭讪她的时候还没一个朋友的啊。
.message	700			而现在，在男生女生中都人气满满，人生真是神奇啊。
.transition 0 * 40
.stage	* ev02_037b01.png 0 0
;（フェ～ドスピ～ドには注意して）
.message	710	miy-204_01-0003	傒傗偙	「啊」
.message	720			呃，视线碰上了。
.transition 0 * 40
.stage	* ev02_037c01.png 0 0
.message	730	miy-204_01-0005	傒傗偙	「抱歉，我稍离一下～」
.message	740			对朋友轻声打过招呼，直直向我走来。
.transition 0 * 20
.stage	* ev02_037c01_mugai.png 0 0 st_miyako07b01.png 410
;☆（ev02_037の上に直接のせちゃってもいいのかもしれませんが，，，保留）
.message	750	miy-204_01-0007	傒傗偙	「堤堤，占用些时间好吗？」
.message	760		嫗丂夘	「虽然一点都不好……但就算逃也没用的吧」
.transition 0 * 40
;.stage	* ev02_037c01_mugai.png 0 0 st_miyako02b02.png 400
;（位置はわざと400にしてます。表情はこれまた注意）
.stage	* ev02_037c01_mugai.png 0 0 st_miyako01b02.png 400
;（表情は注意して）
.message	770	miy-204_01-0009	傒傗偙	「呵呵，看来已经很明事理了嘛，堤君」
.panel 0
.playBGM *
.transition 0 * 10
.stage	* WHITE.png 0 0
;（白は挿まずに？）


;■屋上
.playBGM efBGM029.ogg
.transition 1 fadeSide.png 10
.stage	* ev02_038a01.png 0 0
.panel 1
.message	780	miy-204_01-0011	傒傗偙	「啊～，好久不来这里了呢」
.message	790			宫村一边晃来晃去的走着一边高兴地说。
.message	800	miy-204_01-0013	傒傗偙	「最近，完全没有一人独处的机会呢～。有一个多月没来了吧」
.message	810		嫗丂夘	「我有问题」
.transition 0 * 20
.stage	* ev02_038b01.png 0 0
;（フェ～ドスピ～ドには注意して。さらにここでこの差分を使って良いのか？）
.message	820	miy-204_01-0015	傒傗偙	「好好，堤君请问」
.message	830			宫村唰的把食指指向我。
.message	840		嫗丂夘	「为什么你会有屋顶的钥匙？」
.message	850	miy-204_01-0017	傒傗偙	「哼哼哼，我只要用了我的美貌的话就没有我得不到的东西哦」
.message	860	miy-204_01-0019	傒傗偙	「嗯！　宇宙之海，就是我之海洋！」
.message	870		嫗丂夘	「事实呢？」
.message	880			午休没剩多久了，再不把事情说清楚的话。
.message	890	miy-204_01-0021	傒傗偙	「从纮君那拿到的哦」
.message	900			还真直接啊。
.message	910		嫗丂夘	「我倒不太明白广野为什么会有的理由」
.message	920	miy-204_01-0023	傒傗偙	「嗯，其实呢──」
.transition 0 * 20
.stage	* bgs_sky001a01_01.png 0 0
;（空を挿んでますが，どっかの切り出しでもいいかもしれません）
.message	930			…………
.message	940			……
.message	950			按照宫村的说明，那个音羽的毕业生，也就是广野的姐姐不知为何拿有钥匙，而作为入学的贺礼而给了她的弟弟。
.message	960			然后，已经离开学园的广野，这次把钥匙托付给了宫村。
.transition 0 * 20
.stage	* bgs_sch007a01_01.png 0 0 st_miyako04b02.png 400
;（ポ～ズと表情は注意して。なるべく手を強調したポ～ズで）
.message	970	miy-204_01-0025	傒傗偙	「但是，这个对我来说……可能已经没有用了呢」
.message	980			玩弄着手中的钥匙，宫村的表情有些复杂。
.transition 0 * 40
.stage	* bgs_sch007a01_01.png 0 0 st_miyako02b01.png 350
;.stage	* bgs_sch007a01_01.png 0 0 st_miyako00b02.png 350
;（表情，注意して）
.message	990	miy-204_01-0027	傒傗偙	「差不多该把这个给谁了吧～」
.message	1000		嫗丂夘	「是吗」
.transition 0 * 40
.stage	* bgs_sch007a01_01.png 0 0 st_miyako00b01.png 350
.message	1010	miy-204_01-0029	傒傗偙	「堤堤，确实在拍小景是吧」
.message	1020			突然就改变话题了啊。
.transition 0 * 40
.stage	* bgs_sch007a01_01.png 0 0 st_miyako07b01.png 410
;（ポ～ズ変化には注意して）
.message	1030	miy-204_01-0031	傒傗偙	「早晨时，看到你和小景在一起走呢」
.message	1040		嫗丂夘	「我可不会把拍电影当作说笑哦」
.transition 0 * 40
.stage	* bgs_sch007a01_01.png 0 0 st_miyako07b02.png 410
.message	1050	miy-204_01-0033	傒傗偙	「只拍小景一个人，这样也能拍成电影吗？」
.message	1060	miy-204_01-0035	傒傗偙	「又不是偶像的形象宣传片，那样的怎么想都不会有趣啊」
.message	1070		嫗丂夘	「大家都在小看我啊」
.message	1080		嫗丂夘	「这种问题都是小事而已啦」
.message	1090			我只是追寻着新藤，对话，想要让她说出她心中的真实。
.message	1100			我的话，对新藤说过的话当然之后全部剪掉也无所谓。
.message	1110			这次的摄影，根本就没想去符合什么普通“电影”的体裁。
.transition 0 * 20
.stage	* ev02_039a01.png 0 0
;（ここ，a02表情で？注意されたし）
.message	1120		嫗丂夘	「我想作的电影啊」
.message	1130	miy-204_01-0037	傒傗偙	「嗯？」
.transition 0 * 40
.stage	* ev02_039a02.png 0 0
.message	1140		嫗丂夘	「是否会让观众觉得复杂，想要哭泣都无所谓」
.message	1150			离开摄影研究部，可以自由拍自己喜欢的东西。
.message	1160			因此，我没必要再作那些和过去一样的事。
.transition 0 * 40
.stage	* ev02_039a03.png 0 0
.message	1170		嫗丂夘	「怎样都可以。只要可以稍微触动一下观众的心房──这样就足够了」
.message	1180			只要我追寻着她，一定可以抓到那样的一瞬。
.message	1190			这个预感一直紧紧围绕在我的身边。
.panel 0
.playBGM *
.transition 0 * 10
.stage	* WHITE.png 0 0


;■背景：学園·廊下（夏，１５時
;■　　　　堤京介：制服（夏）
;■　　　　新藤景：制服（夏）
;■ジト目
.playBGM efBGM042.ogg
.transition 1 fadeSide.png 10
.stage	* ev02_040a01.png 0 0
;.stage	* bgc_sch002a01_02.png 0 0
;（夕でアタッチでいいのか？さらにモブいる？）
;（ＣＧの関係から昼でアタッチ。そのため，この後の背景も昼に修正してあります）
.panel 1
.message	1200	kei-204_01-0049	丂宨丂	「果然对于堤前辈想的事情完全理解不能」
.message	1210	kei-204_01-0051	丂宨丂	「只要触动心灵就可以？　那到底算什么嘛那个」
.message	1220		嫗丂夘	「虽然这么说，不还是跟我合作了嘛」
.message	1230			我举着摄像机，向新藤微微一笑。
.message	1240			今天的班会时间稍微有些拖长，没想到新藤竟然没有先走，而是在教室里等着我。
.message	1250			不由得稍微有些感动。
.message	1260		嫗丂夘	「小景真是温柔啊～」
.transition 0 * 40
.stage	* ev02_040a02.png 0 0
.message	1270	kei-204_01-0053	丂宨丂	「再不改掉那个小看人的态度的话，我保证您看不到明天的太阳」
.message	1280		嫗丂夘	「十分抱歉，新藤同学」
.message	1290			为了我美好的明天，我老老实实的低了下头。
.transition 0 * 40
.stage	* ev02_040a03.png 0 0
;（フェ～ドスピ～ド注意して。ここは20でも？）
.message	1300	kei-204_01-0055	丂宨丂	「白痴」
.message	1310			虽然一如既往让人害怕……。
.message	1320			但是看起来却没有真正生气的样子。
.message	1330			倒不如说是，新藤虽然看起来生气了，其实却并没有认真。
.message	1340			和平日的样子比起来──没有动真格的那种感觉吧。
.transition 0 * 40
.stage	* ev02_040a01.png 0 0
;（表情，注意して）
.message	1350	kei-204_01-0057	丂宨丂	「总之，走就好了？」
.message	1360		嫗丂夘	「啊啊，当然」
.message	1370		嫗丂夘	「不用在意我。去你想去的地方，说你想说的话就是」
.message	1380	kei-204_01-0059	丂宨丂	「想说的话……什么也没有」

;■御影チェック
;■　数字はこんなもんかな～。
;■　フレ～ムがくる前においておかないと，数字が上手くあわない。
.set finderCounter = 135
.frame finder.png
.set finderCounter = 135


;■御影チェック
;.set finderCounter = 0
;☆（カウンタ～の数字は後で調整のこと）
.transition 1 fadeSide.png 20
.stage	st_kei11b01-.png 0 0 bg_scl004a01_01.png 0 0 bg_scl004a01_01.png 0
.effect	WScroll2 * 60 -2
.message	1390			新藤缓缓走起来，我也开始跟在一边。
.transition 0 * 40
.stage	st_kei10b01-.png 0 0 bg_scl004a01_01.png 0 0 bg_scl004a01_01.png 0
.message	1400	kei-204_01-0061	丂宨丂	「你还真是奇怪的人啊」
.message	1410		嫗丂夘	「是吗？　拍电影的人，脑子里都会少根螺丝之类」
.message	1420	kei-204_01-0063	丂宨丂	「大概你在那些人中也是佼佼者吧」
.message	1430			难道我刚才被取笑了吗。
;.transition 0 * 40
;.stage	st_kei10b01-.png 0 0 bg_scl004a01_01.png 0 0 bg_scl004a01_01.png 0
.message	1440	kei-204_01-0065	丂宨丂	「我偶尔也有看电影，也从来没有看到过只追着一个人拍的电影啊」
.message	1450		嫗丂夘	「我也没看过。倒不如说是，几乎不看电影」
.transition 0 * 40
.stage	st_kei10b09-.png 0 0 bg_scl004a01_01.png 0 0 bg_scl004a01_01.png 0
.message	1460	kei-204_01-0067	丂宨丂	「不看的吗！？」
.message	1470			新藤惊讶的声音回响在走廊上。
.transition 0 * 40
.stage	st_kei10b04-.png 0 0 bg_scl004a01_01.png 0 0 bg_scl004a01_01.png 0
.message	1480	kei-204_01-0069	丂宨丂	「我说你，不是电影研究部的吗！？」
.message	1490		嫗丂夘	「原研究部员，嗯」
.message	1500		嫗丂夘	「虽然相关知识有不少，但就连黑白电影几乎都没怎么看……」
.message	1510		嫗丂夘	「在情报杂志或者电视上看到有意思的电影的话总之会去电影院看下，大概就这样吧」
.message	1520		嫗丂夘	「然后，没能在剧场看的的大作的话会去租来看吧」
.transition 0 * 40
.stage	st_kei10b06-.png 0 0 bg_scl004a01_01.png 0 0 bg_scl004a01_01.png 0
.message	1530	kei-204_01-0071	丂宨丂	「那不就和普通人一样了吗！」
.message	1540			看来我之前被当作电影狂热者了的样子。
.message	1550		嫗丂夘	「我的兴趣仅仅集中在拍摄而已啦」
.message	1560		嫗丂夘	「不读小说的小说家，不读漫画的漫画家不也不少嘛。一个道理」
.transition 0 * 40
.stage	st_kei10b05-.png 0 0 bg_scl004a01_01.png 0 0 bg_scl004a01_01.png 0
;（表情，注意して）
.message	1570	kei-204_01-0073	丂宨丂	「是这样吗……」
.message	1580		嫗丂夘	「嘛，在拍学生电影的人中，像我这样应该算是minority吧」
.transition 0 * 40
.stage	st_kei11b03-.png 0 0 bg_scl004a01_01.png 0 0 bg_scl004a01_01.png 0
.message	1590	kei-204_01-0075	丂宨丂	「……呃」
.message	1600			不知为何她表情有些红润并且疑惑。
.message	1610		嫗丂夘	「怎么了吗？」
.message	1620			刚才的话应该没有什么羞人的成分吧。
.transition 0 * 40
.stage	st_kei10b09-.png 0 0 bg_scl004a01_01.png 0 0 bg_scl004a01_01.png 0
.message	1630	kei-204_01-0077	丂宨丂	「那个……」
.message	1640		嫗丂夘	「我又说什么不该说的了吗？」
.message	1650	kei-204_01-0079	丂宨丂	「不，不是这回事……」
.message	1660	kei-204_01-0081	丂宨丂	「嘛，嘛罗尼提是什么？」
.message	1670		嫗丂夘	「……原来如此啊」
.transition 0 * 40
.stage	st_kei10b06-.png 0 0 bg_scl004a01_01.png 0 0 bg_scl004a01_01.png 0
.message	1680	kei-204_01-0083	丂宨丂	「取笑我了吧！？　取笑我了是吧！？　肯定取笑我了没错吧！？」
.message	1690		嫗丂夘	「不不，古话说问之耻在一时，不问耻在一世嘛。只要能够提问，你就很伟大」
.message	1700		嫗丂夘	「就是少数派的意思啦」
.transition 0 * 40
.stage	st_kei10b01-.png 0 0 bg_scl004a01_01.png 0 0 bg_scl004a01_01.png 0
;（表情，注意して）
.message	1710	kei-204_01-0085	丂宨丂	「是，是吗……」
.message	1720			唔～，这孩子还真是不知世事呢。
.message	1730			啊～好可爱。
;.effect *


;■学園·階段
;.transition 1 fadeSide.png 20
;.stage	* bgc_sch003a01_01.png 0 0
;（背景移行する際，パネル消す？）
.message	1740		嫗丂夘	「无论如何，我这边怎样都好了啦」
.transition 0 * 40
.stage	st_kei11b01-.png 0 0 bg_scl004a01_01.png 0 0 bg_scl004a01_01.png 0
.message	1750	kei-204_01-0087	丂宨丂	「我也都无所谓啊」
.message	1760		嫗丂夘	「等下，那可一点都不好！」
.transition 0 * 40
.stage	st_kei10b04-.png 0 0 bg_scl004a01_01.png 0 0 bg_scl004a01_01.png 0
.message	1770	kei-204_01-0089	丂宨丂	「有什么不好？」
.message	1780			就算被瞪着，我也毫不怯阵。
.message	1790		嫗丂夘	「你还是没有明白我摄影的宗旨啊」
.message	1800		嫗丂夘	「就是因为你有趣，我才会这样把镜头对向你的啊」
.transition 0 * 40
.stage	st_kei10b05-.png 0 0 bg_scl004a01_01.png 0 0 bg_scl004a01_01.png 0
;（表情，注意して）
.message	1810	kei-204_01-0091	丂宨丂	「有趣？　啊啊，可能确实比较有趣呢」


;■御影チェック
;.effect *
.effect end


.transition 1 fadeSide.png 20
.stage	* bgc_sch003a01_01.png 0 0 st_kei01b01.png 380
;（フェ～ドは通常で？）
.message	1820			新藤用平静的口气说着，突然停下了脚步。
.message	1830			觉得──气氛有了突然的转变。
.message	1840			嗯，和我最初想要拍她的那个瞬间一样的空气……。
;■淡々と
.message	1850	kei-204_01-0093	丂宨丂	「堤前辈也知道的吧？　我对于广野前辈的心情……」
.message	1860		嫗丂夘	「……算是吧」
.message	1870			没有注意到新藤的心情的人，大概只有广野一人吧。
.transition 0 * 40
.stage	* bgc_sch003a01_01.png 0 0 st_kei01b03.png 380
.message	1880	kei-204_01-0095	丂宨丂	「被喜欢的男生抛弃，能够认真的部团活动也受伤退部了──」
.message	1890	kei-204_01-0097	丂宨丂	「看着堕入谷底的人肯定会有趣的吧」
.message	1900		嫗丂夘	「十分有趣哦」
;■息をのむ
.transition 0 * 40
.stage	* bgc_sch003a01_01.png 0 0 st_kei02b03.png 380
;（表情，注意して）
.message	1910	kei-204_01-0099	丂宨丂	「……」
.message	1920			我的话让新藤的身体悚然一震。
.message	1930			正如她所言。
.message	1940			新藤景不但貌美如画，而她的失恋和挫折也是拍电视剧的好素材。
.message	1950			根本不需要去特意写什么剧本，就她自己可以成为银幕的女主角。
.transition 0 * 40
.stage	* bgc_sch003a01_01.png 0 0 st_kei03b06.png 380
.message	1960	kei-204_01-0101	丂宨丂	「……我终于明白了」
;■呆れ
.transition 0 * 40
.stage	* bgc_sch003a01_01.png 0 0 st_kei03b03.png 380
;（表情，注意して）
.message	1970	kei-204_01-0103	丂宨丂	「你完全没有一丝人性。倒不如说是，根本就不是人……」
.message	1980		嫗丂夘	「请把我想象成会说话的摄影机」
.message	1990			说着不由浮起一丝微笑。
.message	2000			原来如此，新藤虽然学习不怎样，但有不错的直感啊。
.message	2010			我是台只会凭本能寻求好的影象的机器。
.message	2020			不勉强去追求什么故事情节，只是想要拍摄真实的新藤，以电影的形式表现出来。
.message	2030			不──我一定能表现出来。





;■背景：通学路，１５時３０分
.playBGM *

;■御影チェック
;■　ここは白フェ～ドを挟むか。
;■-----------------------------------------------
.panel 0
.playBGM *
.frame *
.transition 1 fadeSide.png 20
.stage	* white.png 0 0
.set finderCounter = 2004
.frame finder.png
;■-----------------------------------------------

.playBGM efBGM052.ogg
;.playBGM BGM052_sample.ogg
;■御影チェック
;.set finderCounter = 2000
.transition 1 fadeSide.png 20
.stage	st_kei11b01-.png 0 0 bg_scl003a01_01_f.png 0 0 bg_scl003a01_01_n.png 0
.effect	WScroll2 * 60 -2

;■御影チェック
;■-----------------------------------------------
.set finderCounter = 2004
.panel 1
;■-----------------------------------------------

;.transition 1 fadeSide.png 20
;.stage	* bgs_normal002a01_01.png 0 0
;（モブ入りのがある？）
.message	2040			虽然已经接近傍晚，但外面仍然热如蒸笼。
.message	2050			我和新藤穿插在放学的同学之间，缓缓地走着。
.message	2060	kei-204_01-0105	丂宨丂	「前辈你──」
.message	2070		嫗丂夘	「怎么？」
;■無表情
.transition 0 * 40
.stage	st_kei10b01-.png 0 0 bg_scl003a01_01_f.png 0 0 bg_scl003a01_01_n.png 0
.message	2080	kei-204_01-0107	丂宨丂	「前辈，看过我的比赛吧」
.message	2090		嫗丂夘	「只有两三次吧」
.message	2100			在篮球部拜托拍摄练习比赛的时候。
.message	2110		嫗丂夘	「虽然我不太懂篮球，但你不是能在混乱的选手中毫无阻碍吗」
.message	2120		嫗丂夘	「我觉得新藤你真的很厉害」
;■軽い怒り
.transition 0 * 40
.stage	st_kei10b04-.png 0 0 bg_scl003a01_01_f.png 0 0 bg_scl003a01_01_n.png 0
.message	2130	kei-204_01-0109	丂宨丂	「我可不想听什么台面话」
.transition 0 * 40
.stage	st_kei11b03-.png 0 0 bg_scl003a01_01_f.png 0 0 bg_scl003a01_01_n.png 0
;（表情，注意して）
.message	2140	kei-204_01-0111	丂宨丂	「而且──就算再怎么厉害，连自己状态不好都不注意的话就是失去了作为选手的资格」
.message	2150		嫗丂夘	「……你的伤是怎么回事？」
.message	2160			我也并不了解详细的情形。
.message	2170			仅仅是听说了女子篮球部的一年纪的TOP突然受伤然后离开战线这样的传闻而已。
.message	2180			那个时候，对新藤并没有太大兴趣，我也就没有深究……。
.transition 0 * 40
.stage	st_kei11b04-.png 0 0 bg_scl003a01_01_f.png 0 0 bg_scl003a01_01_n.png 0
.message	2190	kei-204_01-0113	丂宨丂	「内侧……副韧带损伤……好象是这么说的吧」
.message	2200		嫗丂夘	「那算是很严重的伤吗？」
.transition 0 * 40
.stage	st_kei10b01-.png 0 0 bg_scl003a01_01_f.png 0 0 bg_scl003a01_01_n.png 0
;.stage	st_kei10b05-.png 0 0 bg_scl003a01_01_f.png 0 0 bg_scl003a01_01_n.png 0
.message	2210	kei-204_01-0115	丂宨丂	「我的伤还没有严重到做手术的地步，固定然后康复治疗差不多就恢复了」
.message	2220		嫗丂夘	「既然如此的话，再回去打篮球不好吗？」
;■小さなため息
.transition 0 * 40
.stage	st_kei11b04-.png 0 0 bg_scl003a01_01_f.png 0 0 bg_scl003a01_01_n.png 0
.message	2230	kei-204_01-0117	丂宨丂	「…………」
.message	2240			…………
.message	2250			……

;■御影チェック
;.effect *
.effect end



;■商店街
;☆（向井が場所を「海辺の道」に変更しています）
;■御影チェック
;.set finderCounter = 2500
.transition 1 fadeSide.png 20
.stage	st_kei11b01-.png 0 0 bg_scl006a01_01.png 0 0 bg_scl006a01_01.png 0

;■御影チェック
.set finderCounter = 2500

;☆（背景をＢＧフォルダに置いてますが，ＳＴが正解かもしれんので注意して）
;☆（ここの景の表情にも注意）
.effect	WScroll2 * 60 -2
;.transition 1 fadeSide.png 20
;.stage	* bgs_normal001m01_01.png 0 0
.message	2260			新藤自己好像也并不清楚自己到底是何时受的伤。
.message	2270			我也去看的那场比赛──新藤她突然倒下的那个时候，她的膝盖就已经有隐患了。
.message	2280	kei-204_01-0119	丂宨丂	「事情并没有那么简单」
.message	2290			新藤却仍是一幅淡然的表情。
.message	2300	kei-204_01-0121	丂宨丂	「就算说是治好了，膝盖也和埋了一颗炸弹一样」
.message	2310		嫗丂夘	「比起这个，袭击我的时候倒是身手矫健啊……」
.transition 0 * 40
.stage	st_kei10b05-.png 0 0 bg_scl006a01_01.png 0 0 bg_scl006a01_01.png 0
.message	2320	kei-204_01-0123	丂宨丂	「袭击什么的哪有那么难听。那叫击退恶势力」
.message	2330		嫗丂夘	「恶势力……」
.message	2340	kei-204_01-0125	丂宨丂	「那个时候，如果我状态最佳的话，像堤前辈你这样的三秒内就可以敲碎」
.message	2350			你到底是使用什么技能的啊。
.message	2360			你那也算是护着受伤的膝盖时的动作吗？
.message	2370		嫗丂夘	「就算你说什么不是状态最佳，有各种各样的伤的运动选手不也很多吗？」
.transition 0 * 40
.stage	st_kei11b01-.png 0 0 bg_scl006a01_01.png 0 0 bg_scl006a01_01.png 0
.message	2380	kei-204_01-0127	丂宨丂	「是啊」
.message	2390		嫗丂夘	「那是为什么？」
.message	2400	kei-204_01-0129	丂宨丂	「我也不明白」
.message	2410			新藤轻轻摇了摇头。
.message	2420			然后，直直的盯着我。
.transition 0 * 40
.stage	st_kei10b05-.png 0 0 bg_scl006a01_01.png 0 0 bg_scl006a01_01.png 0
.message	2430	kei-204_01-0131	丂宨丂	「堤前辈，到现在为止有作过什么运动吗？」
.message	2440		嫗丂夘	「不，没特别作过」
;■真剣
.message	2450	kei-204_01-0133	丂宨丂	「说到最后，想要站在胜负的世界的顶端的人，心情也会是永远地胜利着的」
.transition 0 * 40
.stage	st_kei10b01-.png 0 0 bg_scl006a01_01.png 0 0 bg_scl006a01_01.png 0
;☆（ここの表情，注意して。目つむりも視野に？）
.message	2460	kei-204_01-0135	丂宨丂	「那份坚强的心情──我早已遗失可啊」
.transition 0 * 40
.stage	st_kei11b04-.png 0 0 bg_scl006a01_01.png 0 0 bg_scl006a01_01.png 0
.message	2470	kei-204_01-0137	丂宨丂	「跌倒，蹲下，好不容易扬起脸时──却无论如何也看不到终点」
;２章冒頭の体育館で佇む景のＣＧ
.message	2480	kei-204_01-0139	丂宨丂	「算了。虽然我不能很好的表达，但已经算了……」
;■自嘲気味に。
.message	2490	kei-204_01-0141	丂宨丂	「这就是现在的我的现实啊……」
.panel 0
.playBGM *
.frame *
;☆（ここまでのビデオフレ～ムのカウンタ～，場所が変わるたびに細かくかえていくこと）


;■御影チェック
;.effect *
.effect end

.transition 0 * 10
.stage	* WHITE.png 0 0


;■背景：京介自室（夏，２１時
;■　　　　堤京介：私服（夏）
.transition 1 fadeSide.png 10
.stage	* ev02_033.png 0 0
;（とりあえずこのイベントＣＧでアタッチしてますが，問題あるようなら別のに）
.panel 1
.message	2500		嫗丂夘	「OK……」
.message	2510			今天拍摄的素材确认完毕。
.message	2520			因为这次没有分镜之类所以不检查一下抽出能用的部分的话，编辑的时候会很麻烦的。
.message	2530			说起来，其实连最后究竟能拍成什么样子也完全不明白啊……。
.transition 0 * 20
.stage	* ev02_076a03.png 0 0
;.transition 0 * 20
;.stage	* ev02_041a01.png 0 0
;（この後，天井に移行で？）
.message	2540		嫗丂夘	「呼啊～啊」
.transition 0 * 20
.stage	* ev02_041a01.png 0 0
.message	2550			咚的一声躺倒在床上。
.message	2560			新藤景。
.message	2570			说实在的，我并不认为她不幸。
.message	2580			只是她自己沉迷于自我的悲剧而已吧。
.message	2590			不知该怎么做，不知前进的路在哪里──
.message	2600			现在的新藤的状态定然是如此的吧。
.message	2610			如果她有想要追寻的东西。
.message	2620			梦想越是鲜明，失去的时候越会造成更大的空白。
.message	2630			完成什么时的成就感只是一瞬便会消失，丧失感却一直持续着。
.transition 0 * 40
.stage	* ev02_041b01.png 0 0
;（フェ～ドスピ～ドは20で？）
.message	2640		嫗丂夘	「原来如此」
.message	2650			我坐起身来。
.message	2660			现在她就像是丧失了一切──如同一具空壳。
.message	2670			但是，正是因为一切都消失掉了，才会有新的开始吧。
.message	2680		嫗丂夘	「嗯，嗯」
.message	2690			这个电影的结局，不知不觉的在我眼前明朗起来。
.panel 0
.transition 0 * 10
.stage	* WHITE.png 0 0
.transition 0 * 10
.stage	* WHITE.png 0 0
.wait 100

.chain 205_01.sc
;■205_01へ。

;.end
