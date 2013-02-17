; ファイル: 700_01.txt
;■幕間１（１章と２章の間）
;■教会内（祭壇）（冬，２０時
;■　　　　火村夕　：私服（冬
;■　　　　雨宫优子：私服（冬


;;■御影チェック
;;■　２週用の分岐スクリプト素体
;;■----------------------------------------------
.if ef_700 == 1 ef_700_b
.if ef_700 <= 0 ef_700_a
;
.label ef_700_a

;■御影チェック
;■　キー入力無効
.pragma disable_control

.goto ef_700_b
.end
;
.label ef_700_b
;;■----------------------------------------------




.setGlobal EYE_SEQ_DEFAULT = 2
.transition 0 * 10
.stage	* WHITE.png 0 0
.wait 500
;.transition 0 * 10
;.stage	* terop_10001a.png 0 0
;.wait 450
;.transition 0 * 10
;.stage	vista_window2.png WHITE.png 0 0
.playBGM efBGM026mix.ogg
.transition 0 * 10
.stage	vista_window2.png ev00_017.png 0 0
;.stage	* bgc_normal012a01_03.png 0 0
;（適当に挿んで，スクロールさせてます）
.vscroll	600	10
.endScroll f
.transition 0 * 10
.stage	vista_window2.png ev00_015a03.png 0 0
;（珍しくいっぱい挿んでますが，居心地悪いようなら変更を）
.panel 3
.message	100			轻轻的呼出一口气，优子向我微笑起来。\a
.wait 270
.message	110			虽然这儿很冷，但在她的笑颜却让我忘记了这些。\a
.wait 290
.panel 0
.transition 0 * 20
.stage	vista_window2.png ev00_015a01.png 0 0
;（表情とフェードスピードは注意して）
.panel 3
.message	120	yuk-700_01-0003	#桪丂巕	「和广野先生在这相遇已经经过一年了呢……」\v\a
.wait 100
:.wait 300
.message	130	him-700_01-0003	#丂梉丂	「在这1年里，就在和那个乖僻的小孩打交道啊」\v\a
.wait 100
;.wait 300
.message	140	yuk-700_01-0005	#桪丂巕	「最近很少在这见到了呢。广野先生工作很忙，宫子则是考试呢」\v\a
:.wait 300
.transition 0 * 20
.stage	vista_window2.png ev00_015a02.png 0 0
;（ここで表情変えていいか，注意して）
.message	150	yuk-700_01-0007	#桪丂巕	「虽然2个人好似都很辛苦，但是……」\v\a
:.wait 300
;■笑顔
.transition 0 * 20
.stage	vista_window2.png ev00_015a03.png 0 0
;（フェードスピード変えてます）
.message	160	yuk-700_01-0009	#桪丂巕	「却都有着充实的表情」\v\a
:.wait 200
.transition 0 * 20
.stage	vista_window2.png ev00_014a02.png 0 0
.message	170	him-700_01-0005	#丂梉丂	「……你也很高兴啊」\v\a
:.wait 100
;.wait 200
.transition 0 * 20
.stage	vista_window2.png ev00_012a02.png 0 0
;（ev00_013のＣＧで？）
.message	180	yuk-700_01-0011	#桪丂巕	「啊啦，是这样吗？」\v\a
:.wait 200
.panel 3
.message	190			优子呵呵的笑起来。\a
.wait 200
.message	200			看到身边的人的成长是值得愉快的事。\a
.wait 240
.message	210			这点，现在的我也十分清楚。\a
.wait 230
.panel 3
.message	220	him-700_01-0007	#丂梉丂	「嘛，当一个守护者应该很辛苦吧？」\v\a
:.wait 300
;■微笑
.transition 0 * 20
.stage	vista_window2.png ev00_013a02.png 0 0
.message	230	yuk-700_01-0013	#桪丂巕	「我对他们什么都没做哦」\v\a
.wait 100
:.wait 300
.message	240	yuk-700_01-0015	#桪丂巕	「大家…都是随着自己的想法选出前进的道路，然后得到那愉快欢笑的每一日」\v\a
:.wait 300
.transition 0 * 20
.stage	vista_window2.png ev00_013a04.png 0 0
.message	250	yuk-700_01-0017	#桪丂巕	「从此之后能不能继续笑着走下去要看那些孩子们自己呢」\v\a
:.wait 300
.panel 3
.message	260			在这个城市里，少年少女们的故事。\a
.wait 220
.message	270			各自的感情交错，融合，然后──\a
.wait 240
.panel 3
.message	280	him-700_01-0009	#丂梉丂	「是啊」\v\a
:.wait 100
;.wait 200
.transition 0 * 20
.stage	vista_window2.png ev00_013a01.png 0 0
;（优子の表情，注意して。フェードスピード変えてます）
.message	290	yuk-700_01-0019	#桪丂巕	「诶？」\v\a
:.wait 200
.transition 0 * 20
.stage	vista_window2.png ev00_014a03.png 0 0
;（夕の表情，注意して）
.message	300	him-700_01-0011	#丂梉丂	「正是有你在，他们才会笑到现在。我是这么想的」\v\a
:.wait 300
;■苦笑
.message	310	yuk-700_01-0021	#桪丂巕	「怎么可能，我没有那么大的力量哦」\v\a
:.wait 300
.message	320	yuk-700_01-0023	#桪丂巕	「夕君真是的，太护内了拉。会让我又想开始撒娇哦？」\v\a
:.wait 300
.transition 0 * 40
.stage	vista_window2.png ev00_014a02.png 0 0
;（夕の表情，注意して。a04差分を使うことも考慮に入れて。フェードスピードにも注意してください）
.message	330	him-700_01-0013	#丂梉丂	「少管我啦」\v\a
:.wait 200
.panel 3
.message	340			我笑着摇摇头。\a
.wait 220
.panel 3
.message	350	him-700_01-0015	#丂梉丂	「我只是自做主张的这样想而已」\v\a
:.wait 200
.message	360	him-700_01-0017	#丂梉丂	「说起来，“广野”啊……」\v\a
:.wait 300
.panel 3
.message	370			倒不是什么很稀少的姓氏。\a
.wait 240
.message	380			不过，我却确信那近在身边。\a
.wait 230
.message	390			大概那个姓作广野的少年……。\a
.wait 250
.panel 0
.transition 0 * 20
.stage	vista_window2.png ev00_014a01.png 0 0
.panel 3
.message	400	him-700_01-0019	#丂梉丂	「优子。你不记得了吗？」\v\a
.wait 100
:.wait 300
.message	410	yuk-700_01-0025	#桪丂巕	「诶，您指什么？」\v\a
:.wait 200
.transition 0 * 20
.stage	vista_window2.png ev00_014a05.png 0 0
.message	420	him-700_01-0021	#丂梉丂	「没……」\v\a
:.wait 200
.transition 0 * 20
.stage	vista_window2.png ev00_014a03.png 0 0
.message	430	him-700_01-0023	#丂梉丂	「叫做新藤景的女孩子的事情呢？」\v\a
:.wait 300
.panel 3
.message	440			优子把头歪向一边。\a
.wait 210
.panel 3
.message	450	yuk-700_01-0027	#桪丂巕	「难道说，那两人和以前的我有什么关系吗……」\v\a
:.wait 300
.transition 0 * 20
.stage	vista_window2.png ev00_014a05.png 0 0
;（ここの表情変化は注意して）
.message	460	him-700_01-0025	#丂梉丂	「……不，算了」\v\a
:.wait 200
.panel 3
.message	470			觉得哪里有些奇怪，果然没错。\a
.wait 250
;■寂しげ
.panel 0
.transition 0 * 20
.stage	vista_window2.png ev00_014_mugai_b.png 0 0
;（カメラが下方にさがりすぎてる違和感がある場合は，トルこと。もしくは別の切り出しで？）
.panel 3
.message	480	yuk-700_01-0029	#桪丂巕	「对不起呢」\v\a
.wait 100
:.wait 200
.message	490	yuk-700_01-0031	#桪丂巕	「我呢，好像失去了各种各样的东西的样子……」\v\a
:.wait 300
.panel 3
.message	500			果然如此吗。\a
.wait 240
.message	510			忘掉我的名字说不定是真的。\a
.wait 250
.message	520			……就算如此。\a
.wait 200
.message	530			就算如此也无所谓。\a
.wait 250
.panel 0
.transition 0 * 20
.stage	vista_window2.png ev00_014a02.png 0 0
;（夕の顔アプ切り出しからインする？それで次にこの画像にみたいな）
.panel 3
.message	540	him-700_01-0027	#丂梉丂	「优子，能让我再听些吗？」\v\a
:.wait 300
.message	550	yuk-700_01-0033	#桪丂巕	「诶？」\v\a
:.wait 200
.message	560	him-700_01-0029	#丂梉丂	「刚才的故事的后续啊」\v\a
:.wait 200
.message	570	him-700_01-0031	#丂梉丂	「差不多1年前的故事没错吧。从那以后到今天不可能什么都没发生」\v\a
:.wait 300
.panel 3
.message	580			嗯，冬天的结束并不是一切就已终结。\a
.wait 240
.panel 3
.message	590	him-700_01-0033	#丂梉丂	「那些小鬼的故事，应该不只一个吧？」\v\a
:.wait 300
.panel 3
.message	600			──那故事尚未结束，我清楚的明白。\a
;.message	600			──まだ終わりではないことを，俺はわかっている。
.wait 220
.panel 0
.transition 0 * 20
.stage	vista_window2.png ev00_015_mugai_a.png 0 0
.panel 3
.message	610	yuk-700_01-0035	#桪丂巕	「是啊……」\v\a
.wait 100
.panel 3
.message	620			优子柔和的浮起微笑，轻轻点了点头。\a
.wait 220
.panel 3
.message	630	yuk-700_01-0037	#桪丂巕	「季节流转，到了夏天──有一个相遇」\v\a
:.wait 300
.wait 30
.message	640	yuk-700_01-0039	#桪丂巕	「从那里开始，又有一个新的故事开始了……」\v\a
:.wait 300
.panel 3
;（ここで切り出しを？）
.message	650			啊啊，再让我多听些吧。\a
.wait 270
.transition 0 * 20
.stage	vista_window2.png ev00_015a03_mugai_c.png 0 0
;（笑顔使ってますが，目つむりでもいいのかもしれません。ハッピーエンドを期待させるために，笑顔にしています）
.message	660			和现在的优子有关的人们的故事，用你的话语。\a
.wait 260
.message	670			那些得到幸福的人们的，另一个故事──\a
.wait 280
.panel 0
.transition 0 * 10
.stage	vista_window2.png WHITE.png 0 0
.wait 100
.playBGM *
.transition 0 * 10
.stage	* WHITE.png 0 0



;■御影チェック
;■　「幕間１」読んだよフラグ。
;■----------------------------------------------
.setGlobal ef_700 = 1
;■----------------------------------------------



;■御影チェック
;■　キー入力有効に
.pragma enable_control



.chain 200_01.sc
;■200_01へ。
;.end
