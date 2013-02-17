; ファイル: 701_01.txt
;■幕間２（２章終了後）
;■教会内（祭壇）（冬，２０時
;■　　　　火村夕　：私服（冬
;■　　　　雨宮优子：私服（冬



;;■御影チェック
;;■　２週用の分岐スクリプト素体
;;■----------------------------------------------
.if ef_clear == 1 ef_701_b
.if ef_clear <= 0 ef_701_a
;
.label ef_701_a

;■御影チェック
;■　キー入力無効
.pragma disable_control

.goto ef_701_b
.end
;
.label ef_701_b
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
;.playBGM efBGM053_2.ogg


;■御影チェック
;■　向井さんから指摘があったのだが。
;■　こっちのほうが，かっこいいか。確かに。
;.playBGM efBGM026mix.ogg
.playBGM efBGM016.ogg


.transition 0 * 10
.stage	vista_window2.png ev00_017.png 0 0
;.stage	* bgc_normal012a01_03.png 0 0
;（適当に挿んで，スクロールさせてます）
.vscroll	600	10
.endScroll f
.transition 0 * 10
.stage	vista_window2.png ev00_015a01.png 0 0
;（珍しくいっぱい挿んでますが，居心地悪いようなら変更を）
.panel 3
.message	100	yuk-701_01-0003	#桪丂巕	「然后──」\v\a
:.wait 200
.transition 0 * 20
.stage	vista_window2.png ev00_015a03.png 0 0
;（表情とフェードスピードは注意して）
;（適当に置いてるんで，後で要変更のこと）
.message	110	yuk-701_01-0005	#桪丂巕	「那些孩子们，现在也在这个城市里欢声笑语」\v\a
.wait 100
.panel 3
.message	120			优子带着笑容说出的，这个悠长──悠长无比的故事终于结束了。\a
.wait 290
.panel 0
.transition 0 * 20
.stage	vista_window2.png ev00_013a02.png 0 0
;（次でも一回表情変化させるために，ここはa01で？）
.panel 3
.message	130	yuk-701_01-0007	#桪丂巕	「其实呢，很想那他们一起去玩呢」\v\a
:.wait 300
.transition 0 * 20
.stage	vista_window2.png ev00_013a04.png 0 0
;（ここ，a04表情で？）
.message	140	yuk-701_01-0009	#桪丂巕	「这就体现出工作的人的艰辛之处了呢」\v\a
:.wait 200
.panel 3
.message	150			虽然如此遗憾的说着，但优子的脸上有充溢着满足的表情。\a
.wait 300
.message	160			大概，她已经作完自己该做的所有的事了吧。\a
.wait 280
.panel 0
.transition 0 * 20
.stage	vista_window2.png ev00_014a02_mugai_a.png 0 0
.panel 3
.message	170	him-701_01-0003	#丂梉丂	「嘛──」\v\a
:.wait 100
;.wait 200
.wait 30
;.transition 0 * 20
.transition 0 * 15
.stage	vista_window2.png ev00_014a04_mugai_a.png 0 0
;（表情変化，フェードスピードには注意して）
.message	180	him-701_01-0005	#丂梉丂	「就算想要一起玩，也不能和年轻人在一起啊」\v\a
:.wait 300
.transition 0 * 20
.stage	vista_window2.png ev00_013a03.png 0 0
;（「憮然」，，，という表情には注意して。まあ，差分自体がこれしかないよな，，，）
.message	190	yuk-701_01-0011	#桪丂巕	「哎呀」\v\a
:.wait 100
;.wait 200
;（优子の目，つむらせる？）
.message	200	yuk-701_01-0013	#桪丂巕	「真过分呢，我还能行的哦」\v\a
:.wait 300
.panel 3
.message	210			优子转瞬有些失望。\a
.wait 220
.message	220			倒是好像有些真的生气而觉得稍有奇怪。\a
.wait 270
.panel 3
.message	230	him-701_01-0007	#丂梉丂	「抱歉，说笑而已啦。别介意」\v\a
:.wait 200
.wait 20
.message	240	yuk-701_01-0015	#桪丂巕	「真是让人困扰的人呢……」\v\a
:.wait 200
.transition 0 * 20
.stage	vista_window2.png ev00_014a01_mugai_a.png 0 0
;（夕の表情には気をつけて。もっと柔らかいものを？）
.message	250	him-701_01-0009	#丂梉丂	「然，最近和他们有聊过吗？」\v\a
:.wait 200
;.wait 300
.transition 0 * 20
.stage	vista_window2.png ev00_013a03.png 0 0
;（a05のcloseでも？）
.message	260	yuk-701_01-0017	#桪丂巕	「啊，在混水摸鱼哦。真是让人困扰的人呢……」\v\a
:.wait 300
.panel 3
.message	270			优子轻轻叹了口气。\a
.wait 250
.panel 0
.transition 0 * 20
.stage	vista_window2.png ev00_013a02.png 0 0
.panel 3
.message	280	yuk-701_01-0019	#桪丂巕	「和宫子他们一样哦」\v\a
:.wait 200
.message	290	yuk-701_01-0021	#桪丂巕	「已经很少再见到新藤小姐和堤先生了呢」\v\a
:.wait 300
.transition 0 * 20
.stage	vista_window2.png ev00_014a05_mugai_a.png 0 0
.message	300	him-701_01-0011	#丂梉丂	「是吗……」\v\a
:.wait 200
.transition 0 * 20
.stage	vista_window2.png ev00_013a01.png 0 0
;（「嬉しそうに笑って」，，，表情には注意して）
.message	310	yuk-701_01-0023	#桪丂巕	「但是，这样也很好呢」\v\a
:.wait 200
.message	320	yuk-701_01-0025	#桪丂巕	「因为他们都已经可以用自己的脚走出去了呢」\v\a
:.wait 300
.message	330	him-701_01-0013	#丂梉丂	「…………」\v\a
:.wait 200
.panel 3
;（ここで014ＣＧに移行？）
.message	340			优子从心底高兴的笑起来，然后稍稍望向远方。\a
.wait 290
.message	350			那双眼睛清澈透明，而且充满着暖暖的温柔……。\a
.wait 310
.panel 0
.transition 0 * 20
.stage	vista_window2.png ev00_014a01.png 0 0
;（夕の表情には注意して）
.panel 3
.message	360	him-701_01-0015	#丂梉丂	「接下来，就轮到优子了呢」\v\a
:.wait 200
.message	370	yuk-701_01-0027	#桪丂巕	「我……？」\v\a
:.wait 200
.transition 0 * 20
.stage	vista_window2.png ev00_014a03.png 0 0
.message	380	him-701_01-0017	#丂梉丂	「对」\v\a
:.wait 200
.wait 50
.message	390	him-701_01-0019	#丂梉丂	「因为你，有失去的东西」\v\a
:.wait 300
.message	400	yuk-701_01-0029	#桪丂巕	「……对」\v\a
:.wait 200
.panel 3
.message	410			优子把目光收回，看向我轻轻点了点头。\a
.wait 260
.panel 3
.message	420	yuk-701_01-0031	#桪丂巕	「那重要的东西，已经离我而去」\v\a
.wait 100
:.wait 300
.message	430	yuk-701_01-0033	#桪丂巕	「现在留下的，只有些许的记忆残片……」\v\a
:.wait 300
.message	440	him-701_01-0021	#丂梉丂	「不，不对」\v\a
:.wait 200
.panel 3
.message	450			面对着悲伤的优子，我清楚地下定断言。\a
.wait 270
.message	460			优子她一直给迷途的人们箴言，推着他们走向正确的地方。\a
.wait 320
.message	470			而只有优子她自己，一直丢失着重要的东西停留在这──\a
.wait 310
.panel 3
.message	480	him-701_01-0023	#丂梉丂	「丢失的东西……取回来就好」\v\a
.wait 100
:.wait 300
.message	490	him-701_01-0025	#丂梉丂	「我会为你取回来」\v\a
:.wait 200
;■微笑
.transition 0 * 20
.stage	vista_window2.png ev00_012a01.png 0 0
;（二人の表情，このＣＧでいいのかにも注意して）
.message	500	yuk-701_01-0035	#桪丂巕	「还是老样子，你还是这么强硬的脾气呢」\v\a
:.wait 300
.message	510	him-701_01-0027	#丂梉丂	「你也不想看到软弱的我吧？」\v\a
.wait 100
:.wait 300
.message	520	yuk-701_01-0037	#桪丂巕	「你到今天为止一直都没有丢失你的那份坚强呢」\v\a
.wait 100
:.wait 400
;.wait 300
.message	530	yuk-701_01-0039	#桪丂巕	「仍然是我憧憬的，坚强而温柔的火村君……」\v\a
.wait 200
;■真剣
.message	540	yuk-701_01-0041	#桪丂巕	「而我却不一样」\v\a
:.wait 200
.message	550	him-701_01-0029	#丂梉丂	「没有不一样」\v\a
:.wait 200
.message	560	yuk-701_01-0043	#桪丂巕	「是不一样的啊。我已经变了……」\v\a
:.wait 300
.panel 3
.message	570			一副抱歉的样子，优子的表情阴郁起来。\a
.wait 250
.message	580			就算失去了无数的东西──\a
.wait 270
.panel 3
.message	590	him-701_01-0031	#丂梉丂	「你就是你。至少对我来说是这样」\v\a
.wait 150
;.wait 100
;■寂しい笑み
.message	600	yuk-701_01-0045	#桪丂巕	「果然你还是温柔的过分呢……」\v\a
:.wait 300
.wait 40
.panel 3
.message	610			并不是我温柔。\a
.wait 270
.message	620			而是我一直坚信。\a
.wait 270
.message	630			优子仍然是那个优子。\a
.wait 300
.message	640			只是多少有些记忆丧失而已吧？\a
.wait 280
;■真剣
.panel 3
.message	650	yuk-701_01-0047	#桪丂巕	「提一个问题可以吗？」\v\a
:.wait 200
.message	660	him-701_01-0033	#丂梉丂	「什么？」\v\a
.wait 100
.message	670	yuk-701_01-0049	#桪丂巕	「我也想知道呢」\v\a
:.wait 200
.message	680	him-701_01-0035	#丂梉丂	「想知道？」\v\a
:.wait 200
.message	690	yuk-701_01-0051	#桪丂巕	「我所不知道的你的故事──讲给我听吧」\v\a


.panel 0
.wait 200
;.playBGM * 0 7
.playBGM * 0 10
.transition 0 * 7
.stage	* BLACK.png 0 0

;■----------------------------------------------
.if ef_clear == 1 mozi

;.movie 10000 ef_first.avi 800 600 f
.movie 10000 ed_moji_test.avi 800 600 f
.goto movie
.end
;■----------------------------------------------
.label mozi
;.movie 10000 ef_first.avi 800 600 t
.movie 10000 ed_moji_test.avi 800 600 t
;■----------------------------------------------

.label movie



;.wait 320
.wait 120
.playBGM *
.wait 80


;■御影チェック
;■　キー入力有効
.pragma enable_control


;■ムービー挿入予定箇所。
;■もし位置が変わったとしても，必ず，ムービー突入前に
;■キー入力を有効にすること。
;■----------------------------------------------
.if ef_clear == 1 2nd

;■　「幕間２」読んだよ＆「first tale」クリアフラグ
.setGlobal ef_clear = 1
;.movie 10000 ef_first.avi 800 600 f
.movie2 ef_first.avi 800 600 ef_first.ogg 44100 2 f

;.transition 0 * 4
;.stage	* BLACK.png 0 0
.wait 120

;.movie2 ef_ED.avi 800 600 ef_ED.ogg 44100 2 f
.movie2 ef_ED.avi 800 600 ef_ED2.ogg 44100 2 f
.wait 600

.end
;■----------------------------------------------

.label 2nd
;.movie 10000 ef_first.avi 800 600 t
.movie2 ef_first.avi 800 600 ef_first.ogg 44100 2 t

;.transition 0 * 4
;.stage	* BLACK.png 0 0
.wait 120

;.movie2 ef_ED.avi 800 600 ef_ED.ogg 44100 2 t
.movie2 ef_ED.avi 800 600 ef_ED2.ogg 44100 2 t
.wait 600

.end
;■----------------------------------------------





;■御影チェック
;■　以下のスクリプトは，すべてコメントアウトします。
;■　使わないＣＧやなにかが，ひっかかってしまうかもなので。

;■----------------------------------------------
;■----------------------------------------------

;:.wait 300
;.panel 3
;.message	700			真摯なまなざしが向けられてくる。\a
;.wait 280
;.message	710			优子が関わってきた物語を俺が知りたがったように。\a
;.wait 290
;.message	720			彼女は空白の時間を少しでも埋めたいと願っているのか……。\a
;.wait 300
;.panel 3
;.message	730	him-701_01-0037	#丂梉丂	「俺自身には大したことはなかったな。割と平凡な日々だったよ」\v\a
;.wait 100
;:.wait 300
;.transition 0 * 20
;.stage	vista_window2.png ev00_015a01.png 0 0
;.message	740	yuk-701_01-0053	#桪丂巕	「夕くんが平凡……？」\v\a
:.wait 200
;;■苦笑
;.transition 0 * 20
;.stage	vista_window2.png ev00_015a03.png 0 0
;.message	750	yuk-701_01-0055	#桪丂巕	「なんかうさんくさいですね」\v\a
;:.wait 200
;.transition 0 * 20
;.stage	vista_window2.png ev00_014a05.png 0 0
;;（もっと「睨み系」のを？）
;.message	760	him-701_01-0039	#丂梉丂	「おまえは人をどういう目で見てるんだ」\v\a
;:.wait 300
;.panel 3
;.message	770			じろりと优子を睨む。\a
;.wait 250
;.panel 0
;.transition 0 * 20
;.stage	vista_window2.png ev00_014a03.png 0 0
;;（夕の表情，注意して）
.panel 3
;.message	780	him-701_01-0041	#丂梉丂	「俺自身のことはともかく」\v\a
;.wait 100
;:.wait 100
;;.wait 200
;.transition 0 * 20
;.stage	vista_window2.png ev00_014a01.png 0 0
;.message	790	him-701_01-0043	#丂梉丂	「信じられないような人間と会ったりしたな」\v\a
;:.wait 300
;.transition 0 * 20
;.stage	vista_window2.png ev00_013a01.png 0 0
;.message	800	yuk-701_01-0057	#桪丂巕	「あら，誰ですか？」\v\a
;:.wait 200
;.message	810	him-701_01-0045	#丂梉丂	「それを話すにはちょっと時間をさかのぼらなきゃいけない」\v\a
:;.wait 300
;.message	820	him-701_01-0047	#丂梉丂	「俺とおまえの過去にも関係のあることだ」\v\a
:;.wait 300
;.transition 0 * 20
;.stage	vista_window2.png ev00_013a03.png 0 0
;.message	830	yuk-701_01-0059	#桪丂巕	「私たちの……？」\v\a
;:.wait 200
;.message	840	him-701_01-0049	#丂梉丂	「そうだ」\v\a
;:.wait 200
;.message	850	him-701_01-0051	#丂梉丂	「いや──その前にあの子のことも話しておかなきゃいけないな」\v\a
;:.wait 300
;.message	860	yuk-701_01-0061	#桪丂巕	「あの子？」\v\a
;.wait 100
;:.wait 200
;;■ジト目
;.message	870	yuk-701_01-0063	#桪丂巕	「あの子って女の子なんですね？」\v\a
;:.wait 200
;.wait 30
;.message	880	him-701_01-0053	#丂梉丂	「変なところで鋭いな，おまえは」\v\a
;:.wait 200
;.message	890	yuk-701_01-0065	#桪丂巕	「これでも私も女の子ですので」\v\a
;:.wait 200
;.panel 3
;.message	900			少し機嫌が悪くなったようだ。\a
;.wait 270
;.panel 0
;.transition 0 * 20
;.stage	vista_window2.png ev00_014a01.png 0 0
;;（夕の表情は注意して）
.panel 3
;.message	910	him-701_01-0055	#丂梉丂	「そういうのじゃない。ただ……」\v\a
;.wait 100
;.transition 0 * 20
;.stage	vista_window2.png ev00_014a03_mugai_a.png 0 0
;;（a01_mugai_aで？）
;.message	920	him-701_01-0057	#丂梉丂	「その子のことを話さないと，俺がここにいる理由も語れないんだ」\v\a
;:.wait 300
;.panel 3
;.message	930			优子が話した物語。\a
;.wait 250
;.message	940			そこに登場人物として現れる优子を俺は知らなかった。\a
;.wait 300
;.message	950			同じように，优子が知らない俺もいるのだ。\a
;.wait 290
;.panel 3
;.message	960	him-701_01-0059	#丂梉丂	「彼女がいたから，俺は优子がここで待っているって知ることができたんだよ」\v\a
;.wait 100
;.transition 0 * 20
;.stage	vista_window2.png ev00_014_mugai_b.png 0 0
;;（このＣＧに移行でいいのか，注意して）
;.message	970	yuk-701_01-0067	#桪丂巕	「私のことを……その子が夕くんに？」\v\a
;:.wait 300
;.message	980	him-701_01-0061	#丂梉丂	「そうだよ。直接ってわけじゃないけどな。少なくとも，きっかけを作った人間の一人だ」\v\a
;.wait 100
;:.wait 500
;.message	990	him-701_01-0063	#丂梉丂	「それに，おまえが話した物語との深い関わりも持っている」\v\a
;:.wait 300
;.message	1000	yuk-701_01-0069	#桪丂巕	「……その子は，誰なんですか？」\v\a
;:.wait 200
;.message	1010	him-701_01-0065	#丂梉丂	「彼女の名前は，新藤千尋」\v\a
;:.wait 200
;.transition 0 * 20
;.stage	vista_window2.png ev00_013a03.png 0 0
;.message	1020	yuk-701_01-0071	#桪丂巕	「新藤……？」\v\a
;.wait 100
;.transition 0 * 20
;.stage	vista_window2.png ev00_014a03.png 0 0
;.message	1030	him-701_01-0067	#丂梉丂	「ああ」\v\a
;:.wait 200
;.panel 3
;.message	1040			あの子の──新藤千尋の瞳が脳裏に浮かぶ。\a
;.wait 290
;.message	1050			彼女がいなければ，俺は优子をいつまでも待たせたまま，日々を過ごしていったに違いない。\a
;.wait 310
;.message	1060			感謝しないとな，あの子には。\a
;.wait 290
;.panel 0
;.transition 0 * 20
;.stage	vista_window2.png ev00_014a01_mugai_a.png 0 0
;;（表情には注意して）
.panel 3
;.message	1070	him-701_01-0069	#丂梉丂	「さて，どこから話そうか……」\v\a
;:.wait 200
;;☆（目をつむらせる？）
;.panel 0
;.transition 0 * 10
;.stage	vista_window2.png WHITE.png 0 0
;.wait 100
;.playBGM *
;.transition 0 * 10
;.stage	* WHITE.png 0 0
;
;;■300_01へ。
.end
