
.setGlobal EYE_SEQ_DEFAULT = 2


.pragma enable_control

.transition 0 * 10
.stage	* BLACK.png 0 0



.if pre001 == 1 ef_000_b1
.if pre001 <= 0 ef_000_a1

.label ef_000_a1

.movie2 latter_intro.avi 800 600 latter_intro.ogg 44100 2 f

.pragma disable_control

.goto ef_000_c1
.end


.label ef_000_b1

.movie2 latter_intro.avi 800 600 latter_intro.ogg 44100 2 t

.goto ef_000_c1
.end
.label ef_000_c1





.transition 0 * 10
.stage	* BLACK.png 0 0

.transition 0 * 10

.panel 3
.stage	vista_window2.png ev00_013a02_WB.png 0 0
.message	130	yuk-701_01-0007	桪丂巕	「其实呢，很想和他们一起去玩呢」\v\a
.transition 0 * 20
.stage	vista_window2.png ev00_013a04_WB.png 0 0
.message	140	yuk-701_01-0009	桪丂巕	「这就体现出工作的人的艰辛之处了呢」\v\a
.wait 50
.transition 0 * 20
.stage	vista_window2.png ev00_014a02_mugai_a_WB.png 0 0
.message	170	him-701_01-0003	丂梉丂	「嘛——」\v\a
.transition 0 * 30
.stage	vista_window2.png ev00_014a04_mugai_a_WB.png 0 0
.message	180	him-701_01-0005	丂梉丂	「就算想要一起玩，也不能和年轻人在一起啊」\v\a
.transition 0 * 20
.stage	vista_window2.png ev00_013a03_WB.png 0 0
.message	190	yuk-701_01-0011	桪丂巕	「哼」\v\a
.message	200	yuk-701_01-0013	桪丂巕	「真过分呢，我还能行的哦」\v\a
.wait 20
.message	230	him-701_01-0007	丂梉丂	「抱歉，说笑而已啦。别介意」\v\a
.message	240	yuk-701_01-0015	桪丂巕	「真是让人困扰的人呢……」\v\a
.transition 0 * 20
.stage	vista_window2.png ev00_014a01_mugai_a_WB.png 0 0
.message	250	him-701_01-0009	丂梉丂	「然后，最近和他们有聊过吗？」\v\a
.transition 0 * 20
.stage	vista_window2.png ev00_013a03_WB.png 0 0
.message	260	yuk-701_01-0017	桪丂巕	「啊，在混水摸鱼哦。真的是让人困扰的人呢……」\v\a
.wait 100
.transition 0 * 20
.stage	vista_window2.png ev00_013a02_WB.png 0 0
.message	280	yuk-701_01-0019	桪丂巕	「和宫子他们一样哦」\v\a
.message	290	yuk-701_01-0021	桪丂巕	「已经很少再见到新藤小姐和堤先生了呢」\v\a
.transition 0 * 20
.stage	vista_window2.png ev00_014a05_mugai_a_WB.png 0 0
.message	300	him-701_01-0011	丂梉丂	「是吗……」\v\a
.wait 30
.transition 0 * 20
.stage	vista_window2.png ev00_013a01_WB.png 0 0
.message	310	yuk-701_01-0023	桪丂巕	「但是，这样也很好呢」\v\a
.message	320	yuk-701_01-0025	桪丂巕	「因为那些孩子们都已经可以用自己的脚走出去了呢」\v\a
.message	330	him-701_01-0013	丂梉丂	「…………」\v\a
.wait 150

.transition 0 * 20
.stage	vista_window2.png ev00_014a01_WB.png 0 0
.message	360	him-701_01-0015	丂梉丂	「接下来，就轮到优子了呢」\v\a
.message	370	yuk-701_01-0027	桪丂巕	「我……？」\v\a
.transition 0 * 20
.stage	vista_window2.png ev00_014a03_WB.png 0 0
.message	380	him-701_01-0017	丂梉丂	「是的」\v\a
.message	390	him-701_01-0019	丂梉丂	「因为你，有失去的东西」\v\a
.wait 50
.message	400	yuk-701_01-0029	桪丂巕	「……是的」\v\a
.wait 100
.message	420	yuk-701_01-0031	桪丂巕	「那重要的东西，已经离我而去」\v\a
.wait 100
.message	430	yuk-701_01-0033	桪丂巕	「现在留下的，只有些许的记忆残片……」\v\a
.wait 50
.message	440	him-701_01-0021	丂梉丂	「不，不对」\v\a
.wait 130
.message	480	him-701_01-0023	丂梉丂	「丢失的东西……取回来就好」\v\a
.wait 100
.message	490	him-701_01-0025	丂梉丂	「我会为你取回来」\v\a

.transition 0 * 20
.stage	vista_window2.png ev00_013a01_WB.png 0 0

.message	500	yuk-701_01-0035	桪丂巕	「还是老样子，你还是这么强硬的脾气呢」\v\a
.message	510	him-701_01-0027	丂梉丂	「你也不想看到软弱的我吧？」\v\a
.wait 80
.message	520	yuk-701_01-0037	桪丂巕	「你到今天为止一直都没有丢失你的那份坚强呢」\v\a
.wait 80

.transition 0 * 20
.stage	vista_window2.png ev00_013a04_WB.png 0 0

.message	530	yuk-701_01-0039	桪丂巕	「仍然是我憧憬的，坚强而温柔的火村夕君……」\v\a
.wait 150

.transition 0 * 20
.stage	vista_window2.png ev00_012a01_WB.png 0 0

.message	540	yuk-701_01-0041	桪丂巕	「而我却不一样」\v\a
.message	550	him-701_01-0029	丂梉丂	「没有不一样」\v\a
.message	560	yuk-701_01-0043	桪丂巕	「是不一样的啊。我已经变了……」\v\a



.playBGM efBGM053mix.ogg * * 100
.panel 0

.transition 0 * 200
.stage	vista_window2.png WHITE.png 0 0
.wait 100
.transition 0 * 200
.stage	vista_window2.png vista_mugai_omake_a.png 0 0
.transition 0 * 200
.stage	vista_window2.png vista_mugai_omake_b.png 0 0
.transition 0 * 200
.stage	vista_window2.png vista_mugai_omake_c.png 0 0
.wait 80
.transition 0 * 210
.stage	vista_window2.png vista_mugai_omake_d.png 0 0
.transition 0 * 210
.stage	vista_window2.png vista_mugai_omake_e.png 0 0
.transition 0 * 210
.stage	vista_window2.png vista_mugai_omake_p3.png 0 0
.transition 0 * 210
.stage	vista_window2.png vista_mugai_omake_k.png 0 0
.transition 0 * 210
.stage	vista_window2.png vista_mugai_omake_g.png 0 0
.transition 0 * 210
.stage	vista_window2.png vista_mugai_omake_b2.png 0 0
.transition 0 * 210
.stage	vista_window2.png vista_mugai_omake_c2.png 0 0
.transition 0 * 210
.stage	vista_window2.png vista_mugai_omake_d2.png 0 0
.transition 0 * 210
.stage	vista_window2.png vista_mugai_omake_m2.png 0 0
.transition 0 * 210
.stage	vista_window2.png vista_mugai_omake_n2.png 0 0
.transition 0 * 210
.stage	vista_window2.png vista_mugai_omake_r2.png 0 0
.transition 0 * 210
.stage	vista_window2.png vista_mugai_omake_s2.png 0 0
.transition 0 * 210
.stage	vista_window2.png vista_mugai_omake_a3.png 0 0
.transition 0 * 210
.stage	vista_window2.png vista_mugai_omake_b3.png 0 0
.transition 0 * 210
.stage	vista_window2.png vista_mugai_omake_f3.png 0 0
.transition 0 * 210
.stage	vista_window2.png vista_mugai_omake_g3.png 0 0
.transition 0 * 210
.stage	vista_window2.png vista_mugai_omake_k3.png 0 0
.transition 0 * 210
.stage	vista_window2.png vista_mugai_omake_l3.png 0 0
.transition 0 * 210
.stage	vista_window2.png vista_mugai_omake_q3.png 0 0
.transition 0 * 210
.stage	vista_window2.png vista_mugai_omake_r3.png 0 0
.transition 0 * 210
.stage	vista_window2.png vista_mugai_omake_u3.png 0 0
.transition 0 * 210
.stage	vista_window2.png vista_mugai_omake_v3.png 0 0
.transition 0 * 210
.stage	vista_window2.png vista_mugai_omake_z3.png 0 0
.transition 0 * 200
.stage	vista_window2.png vista_mugai_omake_w2.png 0 0
.transition 0 * 200
.stage	vista_window2.png vista_mugai_omake_f.png 0 0
.transition 0 * 200
.stage	vista_window2.png vista_mugai_omake_a4.png 0 0
.wait 140
.transition 0 * 200
.stage	vista_window2.png vista_mugai_omake_n3.png 0 0
.transition 0 * 200
.stage	vista_window2.png vista_mugai_omake_h.png 0 0
.transition 0 * 200
.stage	vista_window2.png vista_mugai_omake_i.png 0 0
.transition 0 * 200
.stage	vista_window2.png vista_mugai_omake_j.png 0 0
.transition 0 * 200
.stage	vista_window2.png vista_mugai_omake_l.png 0 0
.transition 0 * 200
.stage	vista_window2.png vista_mugai_omake_m.png 0 0
.transition 0 * 200
.stage	vista_window2.png vista_mugai_omake_n.png 0 0
.transition 0 * 200
.stage	vista_window2.png vista_mugai_omake_o.png 0 0
.transition 0 * 200
.stage	vista_window2.png vista_mugai_omake_p.png 0 0
.transition 0 * 200
.stage	vista_window2.png vista_mugai_omake_q.png 0 0
.transition 0 * 200
.stage	vista_window2.png vista_mugai_omake_r.png 0 0
.transition 0 * 200
.stage	vista_window2.png vista_mugai_omake_s.png 0 0
.transition 0 * 200
.stage	vista_window2.png vista_mugai_omake_t.png 0 0
.transition 0 * 200
.stage	vista_window2.png vista_mugai_omake_u.png 0 0
.transition 0 * 200
.stage	vista_window2.png vista_mugai_omake_v.png 0 0
.transition 0 * 200
.stage	vista_window2.png vista_mugai_omake_w.png 0 0
.transition 0 * 200
.stage	vista_window2.png vista_mugai_omake_x.png 0 0
.transition 0 * 200
.stage	vista_window2.png vista_mugai_omake_z.png 0 0
.transition 0 * 200
.stage	vista_window2.png vista_mugai_omake_e2.png 0 0
.transition 0 * 200
.stage	vista_window2.png vista_mugai_omake_f2.png 0 0
.transition 0 * 200
.stage	vista_window2.png vista_mugai_omake_g2.png 0 0
.transition 0 * 200
.stage	vista_window2.png vista_mugai_omake_h2.png 0 0
.transition 0 * 200
.stage	vista_window2.png vista_mugai_omake_i2.png 0 0
.transition 0 * 200
.stage	vista_window2.png vista_mugai_omake_j2.png 0 0
.transition 0 * 200
.stage	vista_window2.png vista_mugai_omake_k2.png 0 0
.transition 0 * 200
.stage	vista_window2.png vista_mugai_omake_l2.png 0 0
.transition 0 * 200
.stage	vista_window2.png vista_mugai_omake_o2.png 0 0
.transition 0 * 200
.stage	vista_window2.png vista_mugai_omake_p2.png 0 0
.transition 0 * 200
.stage	vista_window2.png vista_mugai_omake_q2.png 0 0
.transition 0 * 200
.stage	vista_window2.png vista_mugai_omake_t2.png 0 0
.transition 0 * 200
.stage	vista_window2.png vista_mugai_omake_u2.png 0 0
.transition 0 * 200
.stage	vista_window2.png vista_mugai_omake_v2.png 0 0
.transition 0 * 200
.stage	vista_window2.png vista_mugai_omake_x2.png 0 0
.transition 0 * 200
.stage	vista_window2.png vista_mugai_omake_y2.png 0 0
.transition 0 * 200
.stage	vista_window2.png vista_mugai_omake_z2.png 0 0
.transition 0 * 200
.stage	vista_window2.png vista_mugai_omake_c3.png 0 0
.transition 0 * 200
.stage	vista_window2.png vista_mugai_omake_d3.png 0 0
.transition 0 * 200
.stage	vista_window2.png vista_mugai_omake_e3.png 0 0
.transition 0 * 200
.stage	vista_window2.png vista_mugai_omake_h3.png 0 0
.transition 0 * 200
.stage	vista_window2.png vista_mugai_omake_i3.png 0 0
.transition 0 * 200
.stage	vista_window2.png vista_mugai_omake_j3.png 0 0
.transition 0 * 200
.stage	vista_window2.png vista_mugai_omake_m3.png 0 0
.transition 0 * 200
.stage	vista_window2.png vista_mugai_omake_y.png 0 0
.transition 0 * 200
.stage	vista_window2.png vista_mugai_omake_s3.png 0 0
.transition 0 * 200
.stage	vista_window2.png vista_mugai_omake_t3.png 0 0
.transition 0 * 200
.stage	vista_window2.png vista_mugai_omake_w3.png 0 0
.transition 0 * 200
.stage	vista_window2.png vista_mugai_omake_x3.png 0 0
.transition 0 * 200
.stage	vista_window2.png vista_mugai_omake_y3.png 0 0
.transition 0 * 200
.stage	vista_window2.png vista_mugai_omake_b4b.png 0 0
.transition 0 * 200
.stage	vista_window2.png vista_mugai_omake_c4.png 0 0
.transition 0 * 200
.stage	vista_window2.png vista_mugai_omake_o3.png 0 0
.transition 0 * 5
.stage	vista_window2.png ev00_012a01_WB.png 0 0
.transition 0 * 5
.stage	vista_window2.png ev00_012a01.png 0 0
.transition 0 * 3
.stage	vista_window2.png title_latter_mikage.png 0 0

.playBGM *
.wait 30
.wait 200
.panel 3
.message	570	him-701_01-0031	丂梉丂	「你就是你。至少对我来说是这样」\v\a
.wait 300





.playBGM efBGM016.ogg
.transition 0 * 3
.stage	vista_window2.png ev00_012a01.png 0 0
.panel 3
.message	600	yuk-701_01-0045	桪丂巕	「果然你还是温柔的过分呢……」\v\a
.wait 300

.panel 3
.message	650	yuk-701_01-0047	桪丂巕	「提１个问题可以吗？」\v\a
.message	660	him-701_01-0033	丂梉丂	「什么？」\v\a
.wait 80
.message	670	yuk-701_01-0049	桪丂巕	「我也想知道呢」\v\a
.message	680	him-701_01-0035	丂梉丂	「想知道？」\v\a
.message	690	yuk-701_01-0051	桪丂巕	「我所不知道的你的故事——讲给我听吧」\v\a
.wait 140
.message	730	him-701_01-0037	丂梉丂	「我这里也没发生什么了不起的事情。仅仅过着平凡的每一天罢了」\v\a
.wait 100
.transition 0 * 20
.stage	vista_window2.png ev00_015a01.png 0 0
.message	740	yuk-701_01-0053	桪丂巕	「夕君过着平凡的……？」\v\a
.transition 0 * 20
.stage	vista_window2.png ev00_015a03.png 0 0
.message	750	yuk-701_01-0055	桪丂巕	「总觉得十分可疑呢」\v\a




.transition 0 * 20
.stage	vista_window2.png ev00_014a03.png 0 0
.message	780	him-701_01-0041	丂梉丂	「我自己的事情暂且不说」\v\a
.transition 0 * 20
.stage	vista_window2.png ev00_014a01.png 0 0
.message	790	him-701_01-0043	丂梉丂	「遇到了难以置信的人了哪」\v\a
.transition 0 * 20
.stage	vista_window2.png ev00_013a01.png 0 0
.message	800	yuk-701_01-0057	桪丂巕	「啊啦，那是谁呢？」\v\a
.message	810	him-701_01-0045	丂梉丂	「要说这个的话就不得不稍微逆时而上了呢」\v\a
.message	820	him-701_01-0047	丂梉丂	「那是与我和你的过去也有关联的事情」\v\a
.transition 0 * 20
.stage	vista_window2.png ev00_013a03.png 0 0
.message	830	yuk-701_01-0059	桪丂巕	「我们的……？」\v\a
.message	840	him-701_01-0049	丂梉丂	「是的」\v\a
.wait 30
.message	850	him-701_01-0051	丂梉丂	「不——在此之前，不说一下那个孩子可不行」\v\a
.message	860	yuk-701_01-0061	桪丂巕	「那个孩子？」\v\a
.wait 100
.message	870	yuk-701_01-0063	桪丂巕	「那个孩子，是女孩子是吧？」\v\a
.message	880	him-701_01-0053	丂梉丂	「对奇怪的地方特别敏锐哪你」\v\a
.message	890	yuk-701_01-0065	桪丂巕	「因为我也是女孩子的说」\v\a
.wait 100
.transition 0 * 20
.stage	vista_window2.png ev00_014a01.png 0 0
.message	910	him-701_01-0055	丂梉丂	「不是这问题吧。只不过……」\v\a
.wait 60
.transition 0 * 20
.stage	vista_window2.png ev00_014a03_mugai_a.png 0 0
.message	920	him-701_01-0057	丂梉丂	「不说说那个孩子的话，我就说不出我到这里来的理由了」\v\a
.wait 130
.panel 3
.message	960	him-701_01-0059	丂梉丂	「因为她，我才会知道优子在这里不停的等待」\v\a
.wait 100
.transition 0 * 20
.stage	vista_window2.png ev00_014_mugai_b.png 0 0
.message	970	yuk-701_01-0067	桪丂巕	「夕君从那个孩子那里……知道了我的事情？」\v\a
.message	980	him-701_01-0061	丂梉丂	「是的。虽然并不是直接得知。但是至少，她起到了牵线搭桥的作用」\v\a
.wait 100
.message	990	him-701_01-0063	丂梉丂	「然后，那和你所说的故事也有着莫大的关系」\v\a
.wait 40
.message	1000	yuk-701_01-0069	桪丂巕	「……那个孩子，是谁呢？」\v\a
.message	1010	him-701_01-0065	丂梉丂	「她的名字是，新藤千寻」\v\a
.transition 0 * 20
.stage	vista_window2.png ev00_013a03.png 0 0
.message	1020	yuk-701_01-0071	桪丂巕	「新藤……？」\v\a
.wait 100
.transition 0 * 20
.stage	vista_window2.png ev00_014a03.png 0 0
.message	1030	him-701_01-0067	丂梉丂	「啊啊」\v\a
.wait 150

.transition 0 * 20
.stage	vista_window2.png ev00_014a01_mugai_a.png 0 0
.message	1070	him-701_01-0069	丂梉丂	「那么，从哪里说起好呢……」\v\a
.panel 0
.transition 0 * 10
.stage	vista_window2.png WHITE.png 0 0
.wait 100
.playBGM *
.transition 0 * 10
.stage	* WHITE.png 0 0


.setGlobal pre001 = 1

.pragma enable_control


.chain 300_01.sc
