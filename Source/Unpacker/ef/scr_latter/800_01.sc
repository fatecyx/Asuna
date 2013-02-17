.setGlobal EYE_SEQ_DEFAULT = 2


.if ef_800_01 == 1 ef_800_01_b1
.if ef_800_01 <= 0 ef_800_01_a1


.label ef_800_01_a1

.pragma disable_control

.goto ef_800_01_b1
.end

.label ef_800_01_b1




.transition 0 * 10
.stage	* BLACK.png 0 0

.transition 0 * 10
.stage	* title_final2.png 0 0
.message	5999			\a　
.wait 800

.transition 0 * 10
.stage	* BLACK.png 0 0
.wait 200




.transition 0 * 10
.stage	vista_window2.png BLACK.png 0 0
.panel 3
.message	110			\a从我打开教会的门开始，经过了多少时间了呢。
.wait 350
.message	120			\a感觉流逝了好几年的时光，但是又感觉只是一瞬之间的事情。
.wait 370


.panel 3
.transition 0 * 5
.stage	vista_window2.png ago_base_80001a.png 0 0
.message	130	yuk-800_01-0003	#桪丂巕	「今晚好静呢……」\v\a
.transition 0 * 10
.stage	vista_window2.png ago_base_80001b.png 0 0
.message	140	him-800_01-0003	#丂梉丂	「简直就像，世界只剩下了我们两人一样」\v\a
.wait 50
.transition 0 * 10
.stage	vista_window2.png ev00_002a03.png 0 250
.message	150	yuk-800_01-0005	#桪丂巕	「只剩下和夕君的两人吗……，这也不错呢」\v\a

.transition 0 * 20
.stage	vista_window2.png ev00_002a02.png 0 250
.message	170	yuk-800_01-0007	#桪丂巕	「每一天都很快乐的样子……」\v\a
.transition 0 * 10
.stage	vista_window2.png ev00_013a04.png 0 250
.message	180	yuk-800_01-0009	#桪丂巕	「嘛，因为是坏心眼的夕君，会在没人看到的时候用好事情欺负人家」\v\a
.message	190	him-800_01-0005	丂梉丂	「你啊，说了很失礼的话了啊」\v\a
.transition 0 * 15
.stage	vista_window2.png ev00_017.png 0 600
.message	200	yuk-800_01-0011	#桪丂巕	「啊哈」\v\a
.wait 50

.transition 0 * 15
.stage	vista_window2.png ev00_013a03.png 0 0
.message	230	yuk-800_01-0013	#桪丂巕	「但是，真的」\v\a
.wait 70


.message	250	yuk-800_01-0015	#桪丂巕	「今天——只有今晚，不想让任何人来打扰我们」\v\a
.transition 0 * 20
.stage	vista_window2.png ev00_014a03.png 0 0
.message	260	him-800_01-0007	#丂梉丂	「……我也是」\v\a
.wait 50
.message	270	him-800_01-0009	#丂梉丂	「因为……终于能完成约定了」\v\a
.transition 0 * 15
.stage	vista_window2.png ev00_015a01.png 0 0
.message	280	yuk-800_01-0017	#桪丂巕	「那个孩子告诉你了呢」\v\a
.wait 30
.transition 0 * 20
.stage	vista_window2.png ev00_015a02.png 0 0
.message	290	yuk-800_01-0019	#桪丂巕	「我的事情。和我在这里等待的事情」\v\a
.transition 0 * 20
.stage	vista_window2.png ev00_014a02_mugai_a.png 0 0
.message	300	him-800_01-0011	#丂梉丂	「啊啊，是的」\v\a

.transition 0 * 15
.stage	vista_window2.png BLACK.png 0 0
.panel 3
.message	330			\a如果其他人和我这样说的话，我大概不会相信吧。
.wait 370
.message	340			\a但是，是因为那个孩子的话。
.wait 330
.message	350			\a正是因为是优子赌上性命救下的少女所说的话，所以我想相信。
.wait 390
.message	360			\a所以我才回到了这个城市。
.wait 350


.panel 3
.transition 0 * 10
.stage	vista_window2.png ev00_013a02.png 0 0
.message	370	yuk-800_01-0021	#桪丂巕	「未来，也已经长大了吧」\v\a
.panel 3

.transition 0 * 15
.stage	vista_window2.png ev00_014a02.png 0 0

.message	390	him-800_01-0013	#丂梉丂	「那个孩子现在，和久濑开心的过夏天的圣诞节吧」\v\a
.transition 0 * 10
.stage	vista_window2.png ev00_012a01.png 0 0
.message	400	yuk-800_01-0023	#桪丂巕	「夏天的圣诞节……」\v\a
.message	410	him-800_01-0015	#丂梉丂	「啊啊，你以前说过的吧？好想过夏天的圣诞节」\v\a
.wait 120
.message	420	yuk-800_01-0025	#桪丂巕	「这样一说……是曾经发生过那种事情呢」\v\a
.wait 100
.message	430	him-800_01-0017	#丂梉丂	「去去看吧？虽然赶不上今年的圣诞节了，但是那边可是夏天哦」\v\a
.wait 100
.message	440	yuk-800_01-0027	#桪丂巕	「……不用了」\v\a
.transition 0 * 20
.stage	vista_window2.png ev00_012a02.png 0 0
.message	450	yuk-800_01-0029	#桪丂巕	「不用了，未来正在享受夏天的圣诞节的话，我这样就可以了」\v\a
.wait 50
.message	460	him-800_01-0019	#丂梉丂	「是吗……」\v\a


.transition 0 * 15
.stage	vista_window2.png BLACK.png 0 0
.panel 3
.message	470			\a羽山瑞希和久濑所度过的圣诞节，这是第一次也可能是最后一次了吧。
.wait 370
.message	480			\a那个特别的日子是——夏天的圣诞节。
.wait 330
.message	490			\a我和优子不可思议地互相吸引着的，夏天的圣诞节。
.wait 390
.message	500			\a那也是种缘分吧。
.wait 300


.panel 3
.transition 0 * 10
.stage	vista_window2.png ev00_015a03.png 0 0
.message	510	yuk-800_01-0031	#桪丂巕	「即使这样，还是好神奇呢。到了现在，未来还能有机会和我们再会」\v\a
.transition 0 * 15
.stage	vista_window2.png ev00_014a03_mugai_a.png 0 0
.message	520	him-800_01-0021	#丂梉丂	「不只有未来。还有和我们相遇的，有关的人们」\v\a
.transition 0 * 15
.stage	vista_window2.png ev00_014a03.png 0 0
.message	530	him-800_01-0023	#丂梉丂	「正因为大家的回忆，连接成了１条纽带，造就了我们的再会」\v\a
.transition 0 * 20
.stage	vista_window2.png ev00_014a02.png 0 0
.message	540	him-800_01-0025	#丂梉丂	「我就是这样认为的哦」\v\a
.transition 0 * 20
.stage	vista_window2.png ev00_014_mugai_b.png 0 0
.message	550	yuk-800_01-0033	#桪丂巕	「啊啦」\v\a
.wait 20
.message	560	yuk-800_01-0035	#桪丂巕	「真是不像夕君，好浪漫的想法呢」\v\a
.transition 0 * 20
.stage	vista_window2.png ev00_014a02_mugai_a.png 0 0
.message	570	him-800_01-0027	#丂梉丂	「因为今天是圣诞节啊。偶尔这样也可以吧」\v\a


.transition 0 * 10
.stage	vista_window2.png BLACK.png 0 0
.panel 3
.message	580			\a在圣诞节引发了奇迹。
.wait 330
.message	590			\a这完全不是什么戏法，这样相信着也好。
.wait 390
.message	600			\a不——
.wait 280
.message	610			\a是这状况令人不得不信。
.wait 330


.panel 3
.transition 0 * 15
.stage	vista_window2.png ev00_014a03.png 0 0
.message	620	him-800_01-0029	#丂梉丂	「优子」\v\a
.transition 0 * 20
.stage	vista_window2.png ev00_013a03.png 0 0
.message	630	yuk-800_01-0037	#桪丂巕	「是」\v\a


.transition 0 * 15
.stage	vista_window2.png BLACK.png 0 0
.panel 3
.message	640			\a还是不得不问一下。
.wait 320
.message	650			\a只是如果接受现在的状况的话。
.wait 320
.message	660			\a只是这样的话，我会认为我自己不过是在做着梦。
.wait 390
.message	670			\a所以——让我确认下吧。
.wait 320


.panel 3
.transition 0 * 20
.stage	vista_window2.png ago_base_80001c.png 0 0
.message	680	him-800_01-0031	#丂梉丂	「为什么，你还是和以前一样」\v\a
.transition 0 * 15
.stage	vista_window2.png ago_base_80001d.png 0 0
.message	690	yuk-800_01-0039	#桪丂巕	「…………」\v\a

.panel 3
.transition 0 * 15
.stage	vista_window2.png ago_base_80001e.png 0 0
.message	730	him-800_01-0033	#丂梉丂	「为什么你会……在这里？」\v\a
.wait 140
.message	740	him-800_01-0035	#丂梉丂	「因为，你……」\v\a
.wait 50
.transition 0 * 20
.stage	vista_window2.png ed05_004_mugai.png 0 0
.message	750	yuk-800_01-0041	#桪丂巕	「嗯，是呢」\v\a

.transition 0 * 10
.stage	vista_window2.png WHITE.png 0 0
.panel 3
.message	760			\a优子小小的点着头。
.wait 320
.message	770			\a虽然是有些悲伤的表情，但是的确点了点头。
.wait 390

.panel 3
.playBGM * * 5
.transition 0 * 20
.stage	vista_window2.png ago_base_80001f.png 0 0
.message	780	yuk-800_01-0043	#桪丂巕	「雨宫优子这个存在……应该在很早以前就消失了」\v\a



.playBGM efLAT04_08.ogg
.transition 0 * 10
.stage	vista_window2.png WHITE.png 0 0


.panel 3
.message	790			\a有这样一个女孩子。
.wait 300
.message	800			\a她有着很多悲伤的回忆。
.wait 350
.message	810			\a一直都在哭泣着。
.wait 330
.message	820			\a哭泣着，哭泣着，即使如此她也没有失去她的温柔。
.wait 380
.message	830			\a温柔的，可爱的――随处可见的普通的女孩子。
.wait 390
.playSE2 *
.message	840		#丂梉丂	「可是……」\v\a
.wait 330
.message	850			\a明明应该笑着度过日日夜夜的。
.wait 340

.transition 0 * 10
.stage	* ev05_216_mugai.png 0 0
.message	860		#丂梉丂	「为什么，你……」\v\a
.wait 330


.wait 360
.transition 0 * 20
.stage	* ev05_218a01_mugai.png 0 0
.message	1060		#丂梉丂	「优子……」\v\a
.wait 320


.transition 0 * 15
.stage	* ev05_218a02_mugai.png 0 0
.message	1140		#丂梉丂	「优……子」\v\a
.wait 330
.transition 0 * 15
.stage	* ev05_218a03_mugai.png 0 0
.message	1150		#丂梉丂	「你去了哪里啊……！」\v\a
.wait 300
.transition 0 * 15
.stage	* ev05_218a04_mugai.png 0 0
.message	1160		#丂梉丂	「说了要等我……不是说了要等我的么……！」\v\a
.wait 330
.transition 0 * 15
.stage	* ev05_218b01_mugai.png 0 0
.message	1170		#丂梉丂	「约定了……约定过吧……！」\v\a
.wait 330


.transition 0 * 15
.stage	* ev05_218b01_mugai_bk.png 0 0
.message	1190		#丂梉丂	「从今以后３个人……创造家庭……」\v\a
.wait 300
.transition 0 * 15
.stage	* ev05_218b01_mugai_ek.png 0 0
.message	1200		#丂梉丂	「家庭……！」\v\a
.wait 300
.transition 0 * 10
.stage	* ev05_218b01_mugai.png 0 0
.message	1210			\a言语哽咽在喉咙里，已经无处可去。
.wait 360
.message	1220			\a即使如此仍然声嘶力竭地大喊――可她再也听不到了。
.wait 390
.message	1230			\a优子——
.wait 300
.message	1240			\a不要……再让我变成一个人。
.wait 330
.message	1250			\a把我丢下……你去哪儿了啊……
.wait 370
.transition 0 * 10
.stage	* ev05_218b01_mugai_jk.png 0 0
.message	1260			\a呐，优子。
.wait 330
.message	1270			\a再一次。
.wait 350
.message	1280			\a让我听到你的声音。
.wait 350
.transition 0 * 10
.stage	* ev05_218b01_mugai_fk.png 0 0
.message	1290			\a再一次――笑起来吧。

.playBGM * * 5
.wait 150
.panel 3
.wait 350



.transition 0 * 10
.stage	vista_window2.png BLACK.png 0 0
.panel 3
.message	1300			\a我记得，那个圣诞节的那天也是特别的寒冷。
.wait 350


.message	1310			\a在这个教会的。
.wait 310
.message	1320			\a冰冷的地板上。
.wait 310
.message	1330			\a抱着她的时候的那份温暖——
.wait 380
.message	1340			\a我至今都无法忘却。
.wait 330


.playBGM efBGM016.ogg

.panel 3
.transition 0 * 10
.stage	vista_window2.png ev00_014a05_mugai_a.png 0 0
.message	1350	him-800_01-0037	#丂梉丂	「那个时候」\v\a
.transition 0 * 10
.stage	vista_window2.png ev00_013a03.png 0 0
.message	1360	him-800_01-0039	#丂梉丂	「那个时候，你……」\v\a

.transition 0 * 15
.stage	vista_window2.png BLACK.png 0 0
.panel 3
.message	1370			\a紧紧咬住了嘴唇。
.wait 310
.message	1380			\a虽然怎么都不想认可。
.wait 330
.message	1390			\a因为我触碰过了她的身体。
.wait 360
.message	1400			\a所以，优子再也不会笑起来了——伴随着剧痛，我理解了这件事。
.wait 430

.panel 3
.transition 0 * 15
.stage	vista_window2.png ev00_013a05.png 0 0
.message	1410	yuk-800_01-0045	#桪丂巕	「……请不要去恨未来」\v\a
.wait 30
.transition 0 * 15
.stage	vista_window2.png ev00_014a03.png 0 0
.message	1420	him-800_01-0041	#丂梉丂	「我知道。那个孩子没有任何罪过」\v\a
.wait 50
.message	1430	him-800_01-0043	#丂梉丂	「你做的事情也没有任何错误哦」\v\a
.transition 0 * 15
.stage	vista_window2.png ev00_013a05_close.png 0 0
.message	1440	yuk-800_01-0047	#桪丂巕	「被这样说的话，我也……被拯救了呢」\v\a


.transition 0 * 10
.stage	vista_window2.png BLACK.png 0 0
.panel 3
.message	1450			\a她拯救了在眼前就快被夺走了的生命。
.wait 420
.message	1460			\a有谁会去责备这种事呢。
.wait 360
.message	1470			\a虽然要完全想通那件事，也花了相当多的时间。
.wait 390


.panel 3
.transition 0 * 10
.stage	vista_window2.png ago_base_80001g.png 0 0
.message	1480	him-800_01-0045	#丂梉丂	「所以，你……」\v\a
.wait 50


.transition 0 * 10
.stage	vista_window2.png ev00_003_vista.png 0 0

.message	1500	yuk-800_01-0051	#桪丂巕	「大概，我并不是雨宫优子吧」\v\a

.panel 3
.transition 0 * 15
.stage	vista_window2.png ago_base_80001h.png 0 0
.message	1530	him-800_01-0047	#丂梉丂	「……不，毫无疑问你就是优子」\v\a
.wait 30

.panel 3
.transition 0 * 15
.stage	vista_window2.png ev00_013a04.png 0 0
.message	1550	yuk-800_01-0053	#桪丂巕	「夕君……」\v\a

.panel 3
.transition 0 * 15
.stage	vista_window2.png ev00_013a02.png 0 0
.message	1570	yuk-800_01-0055	#桪丂巕	「我是什么时候回到这个城市的，完全都不记得了」\v\a
.transition 0 * 20
.stage	vista_window2.png ev00_013a03.png 0 0
.message	1580	yuk-800_01-0057	#桪丂巕	「回过神来的时候我已经在这里了，记忆也非常混乱——」\v\a
.wait 110
.message	1590	yuk-800_01-0059	#桪丂巕	「只能想起１个名字，“雨宫优子”。所以我想这就是我的名字」\v\a
.transition 0 * 15
.stage	vista_window2.png ago_base_80001i.png 0 0
.message	1600	yuk-800_01-0061	#桪丂巕	「但是，现在我知道了。我既是雨宫优子，也不是雨宫优子」\v\a


.transition 0 * 15
.stage	vista_window2.png ev00_014a05_mugai_a.png 0 0
.message	1610	him-800_01-0049	#丂梉丂	「原来是这样吗……」\v\a

.panel 3
.transition 0 * 10
.stage	vista_window2.png ev00_015_mugai_a.png 0 0
.message	1640	yuk-800_01-0063	#桪丂巕	「听了你的回忆后，我才注意到的」\v\a
.wait 120
.message	1650	yuk-800_01-0065	#桪丂巕	「我啊」\v\a
.transition 0 * 15
.stage	vista_window2.png ev00_013a05_close.png 0 0
.message	1660	yuk-800_01-0067	#桪丂巕	「大概，我是从雨宫优子和在她体内孕育着的小生命中诞生的……」\v\a
.wait 50
.transition 0 * 20
.stage	vista_window2.png ev00_013a05.png 0 0
.message	1670	him-800_01-0051	#丂梉丂	「我们的……孩子……」\v\a

.transition 0 * 10
.stage	vista_window2.png BLACK.png 0 0
.panel 3
.message	1680			\a和优子一起消失的生命……。
.wait 380
.message	1690			\a我和优子，应该组成３个人的家庭的……。
.wait 390


.panel 3
.transition 0 * 10
.stage	vista_window2.png ev00_013a03.png 0 0
.message	1700	yuk-800_01-0069	#桪丂巕	「回到了音羽之城的我，有着必须要做的事情」\v\a
.wait 80
.message	1710	him-800_01-0053	#丂梉丂	「必须要做的事情……？」\v\a
.wait 130
.message	1720	yuk-800_01-0071	#桪丂巕	「总是那么的温柔的我」\v\a


.transition 0 * 15
.stage	vista_window2.png ago_base_80001j.png 0 0
.panel 3
.message	1740	yuk-800_01-0073	#桪丂巕	「即使孤身一人，也会去温柔地对待很多人」\v\a

.transition 0 * 15
.stage	vista_window2.png ev00_013a03.png 0 0
.message	1750	yuk-800_01-0075	#桪丂巕	「为了别人奉献出自己，是我的工作」\v\a
.wait 80
.message	1760	yuk-800_01-0077	#桪丂巕	「请这么做吧，被谁这样告诫着」\v\a
.wait 80
.message	1770	him-800_01-0055	#丂梉丂	「……被谁？」\v\a
.transition 0 * 15
.stage	vista_window2.png ev00_013a04.png 0 0
.message	1780	yuk-800_01-0079	#桪丂巕	「谁知道呢……？」\v\a
.transition 0 * 15
.stage	vista_window2.png ev00_013a02.png 0 0
.message	1790	yuk-800_01-0081	#桪丂巕	「如果要说的话，说不定是神吧」\v\a
.wait 100
.message	1800	him-800_01-0057	#丂梉丂	「神，么……」\v\a

.transition 0 * 15
.stage	vista_window2.png ago_base_80001k.png 0 0
.panel 3
.message	1810			\a在失去她的那一天。
.wait 300
.transition 0 * 15
.stage	vista_window2.png ago_base_80001k2.png 0 0
.message	1820			\a那一天，仰视天空——我回忆起了在云层的缝隙中撒下的美丽光芒。
.wait 390

.panel 3
.transition 0 * 10
.stage	vista_window2.png ev00_014a02_mugai_a.png 0 0
.message	1830	him-800_01-0059	#丂梉丂	「所以，你就是天使吧？」\v\a
.transition 0 * 15
.stage	vista_window2.png ev00_014_mugai_b.png 0 0
.message	1840	yuk-800_01-0083	#桪丂巕	「天使……」\v\a
.transition 0 * 10
.stage	vista_window2.png ev00_015a03.png 0 0
.message	1850	yuk-800_01-0085	#桪丂巕	「嗯。说不定是这样」\v\a
.wait 100


.transition 0 * 15
.stage	vista_window2.png BLACK.png 0 0
.panel 3
.message	1860			\a优子满面微笑着——
.wait 350
.message	1870			\a真诚地，浮起了如同天使般清澈的笑容。
.wait 400


.panel 3
.transition 0 * 15
.stage	vista_window2.png ev00_015a01.png 0 0
.message	1880	yuk-800_01-0087	#桪丂巕	「神应该不存在于世上」\v\a
.wait 20
.message	1890	yuk-800_01-0089	#桪丂巕	「你以前有这么说呢」\v\a
.wait 30
.message	1900	him-800_01-0061	#丂梉丂	「嗯」\v\a
.transition 0 * 20
.stage	vista_window2.png ev00_015a02.png 0 0
.message	1910	yuk-800_01-0091	#桪丂巕	「现在还这么认为吗？」\v\a


.transition 0 * 15
.stage	vista_window2.png WHITE.png 0 0
.panel 3
.message	1920			\a我慢慢琢磨着她的问题。
.wait 350
.message	1930			\a优子还在这里，本来就是不可能的事情。
.wait 390
.message	1940			\a或者说，说不定该被称为“奇迹”。
.wait 400
.message	1950			\a然后，我要回答的是——
.wait 400


.panel 3
.transition 0 * 10
.stage	vista_window2.png ev00_015a01.png 0 0
.message	1960	him-800_01-0063	#丂梉丂	「我是注视着自己，和自己身边的人们，相信着活下来的哦」\v\a
.transition 0 * 20
.stage	vista_window2.png ev00_015a03.png 0 0
.message	1970	yuk-800_01-0093	#桪丂巕	「……啊哈」\v\a
.wait 50
.message	1980	yuk-800_01-0095	#桪丂巕	「真的，很有你的风格」\v\a
.transition 0 * 15
.stage	vista_window2.png ev00_014a02_mugai_a.png 0 250
.message	1990	him-800_01-0065	#丂梉丂	「因为我除了自己这样活下去以外，别无他法」\v\a


.transition 0 * 15
.stage	vista_window2.png WHITE.png 0 0
.panel 3
.message	2000			\a如果发生了奇迹，就会改变自己的想法吗。
.wait 380
.message	2010			\a我觉得，这样也没关系。
.wait 330


.panel 3
.transition 0 * 15
.stage	vista_window2.png ev00_014a01.png 0 0
.message	2020	him-800_01-0067	#丂梉丂	「呐」\v\a
.transition 0 * 15
.stage	vista_window2.png ev00_013a01.png 0 0
.message	2030	yuk-800_01-0097	#桪丂巕	「……嗯」\v\a
.transition 0 * 10
.stage	vista_window2.png ev00_012a01.png 0 0
.message	2040	him-800_01-0069	#丂梉丂	「对我来说，你就是优子。我想这么叫你」\v\a
.transition 0 * 15
.stage	vista_window2.png ev00_012a02.png 0 0
.message	2050	yuk-800_01-0099	#桪丂巕	「……谢谢你」\v\a


.transition 0 * 10
.stage	vista_window2.png WHITE.png 0 0
.panel 3
.message	2060			\a优子的眼睛里闪着泪光。
.wait 300
.message	2070			\a透明的，晶莹剔透的，真的是非常漂亮的眼泪——
.wait 400


.panel 3
.transition 0 * 15
.stage	vista_window2.png ev00_014a02_mugai_a.png 0 0
.message	2080	him-800_01-0071	#丂梉丂	「优子。以前，我有一句话没能对你说」\v\a


.transition 0 * 10
.stage	vista_window2.png WHITE.png 0 0
.panel 3
.message	2100			\a因为害羞，一次都没能说出来的话。
.wait 380
.message	2110			\a现在说出来吧。
.wait 390
.message	2120			\a倾注我的真情。
.playBGM *
.wait 400


.playBGM efLAT05_25.ogg


.panel 3
.transition 0 * 10
.stage	vista_window2.png ev00_018a01.png 0 0
.message	2130	him-800_01-0073	#丂梉丂	「优子，我爱你——」\v\a
.wait 150
.transition 0 * 10
.stage	vista_window2.png ev00_015_mugai_a.png 0 0
.message	2140	yuk-800_01-0101	#桪丂巕	「夕，君……」\v\a


.panel 3
.transition 0 * 10
.stage	vista_window2.png ev00_018a01.png 0 0
.message	2160	him-800_01-0075	#丂梉丂	「我爱你，优子……」\v\a

.panel 3
.transition 0 * 15
.stage	vista_window2.png ev00_014a02.png 0 0
.message	2190	him-800_01-0077	#丂梉丂	「一直都没说出来……对不起」\v\a
.wait 50
.message	2200	yuk-800_01-0103	#桪丂巕	「夕君……」\v\a

.panel 3
.transition 0 * 15
.stage	vista_window2.png ev00_014_mugai_b.png 0 0
.message	2220	yuk-800_01-0105	#桪丂巕	「不对哦，那个」\v\a
.wait 100
.message	2230	him-800_01-0079	#丂梉丂	「不对……？」\v\a
.transition 0 * 15
.stage	vista_window2.png ev00_015a04.png 0 0
.message	2240	yuk-800_01-0107	#桪丂巕	「是爱过我，才对吧？」\v\a
.wait 30
.transition 0 * 15
.stage	vista_window2.png ev00_015a05.png 0 0
.message	2250	him-800_01-0081	#丂梉丂	「优子……」\v\a
.wait 130

.message	2270	yuk-800_01-0109	#桪丂巕	「夕君，我呢」\v\a
.wait 150
.message	2280	yuk-800_01-0111	#桪丂巕	「我很幸福……」\v\a


.transition 0 * 15
.stage	vista_window2.png ev00_013a06.png 0 0

.message	2300	yuk-800_01-0113	#桪丂巕	「谢谢你……」\v\a
.wait 150
.message	2310	yuk-800_01-0115	#桪丂巕	「能和你相遇真的太好了……」\v\a
.wait 170
.message	2320	yuk-800_01-0117	#桪丂巕	「和你约定……在这个地方再次见面，真的好开心……」\v\a
.wait 140
.message	2330	yuk-800_01-0119	#桪丂巕	「所以已经可以了。我已经，从你这里得到了很多的东西了」\v\a
.transition 0 * 10
.stage	vista_window2.png ev00_014a05_mugai_a.png 0 0
.message	2340	him-800_01-0083	#丂梉丂	「要走了吗……」\v\a


.panel 0
.transition 0 * 10
.stage	vista_window2.png ev00_012a02.png 0 0
.panel 3
.message	2410	yuk-800_01-0121	#桪丂巕	「对不起」\v\a
.wait 110
.message	2420	him-800_01-0085	#丂梉丂	「别道歉……」\v\a




.transition 0 * 13
.stage	vista_window2.png ev00_012a12.png 0 0
.panel 3
.message	2430			\a没有任何需要道歉的事情。
.wait 50
.transition 0 * 7
.stage	vista_window2.png ev00_012a22.png 0 0
.message	2440			\a就算她只是回来一瞬间也好。
.wait 100
.transition 0 * 7
.stage	vista_window2.png ev00_012a32.png 0 0
.message	2450			\a应该在永恒的时间里沉沦的，想传递给她的思念和言语。
.wait 130
.transition 0 * 7
.stage	vista_window2.png ev00_012a42.png 0 0
.message	2460			\a将这些传达给了她，我也应该满足了。
.wait 100
.transition 0 * 7
.stage	vista_window2.png ev00_012a52.png 0 0
.message	2470			\a除此之外，不可以再有任何期望……。
.wait 300




.panel 0
.playBGM * * 8
.transition 0 * 4
.stage	* BLACK.png 0 0
.wait 100
.playBGM *
.transition 0 * 10
.stage	* BLACK.png 0 0



.if ef_800_01 == 1 800_01_b1
.if ef_800_01 <= 0 800_01_a1

.label 800_01_a1
.movie2 ed.avi 800 600 ed.ogg 44100 2 f

.pragma disable_control

.goto 800_01_c1
.end

.label 800_01_b1
.movie2 ed.avi 800 600 ed.ogg 44100 2 t
.goto 800_01_c1
.end


.label 800_01_c1



.setGlobal ef_800_01 = 1

.pragma enable_control

.wait 600


.end

