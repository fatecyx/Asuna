

.setGlobal EYE_SEQ_DEFAULT = 2

.pragma enable_control


.if ef_702_01 == 1 ef_702_01_b1
.if ef_702_01 <= 0 ef_702_01_a1


.label ef_702_01_a1

.pragma disable_control

.goto ef_702_01_b1
.end

.label ef_702_01_b1





.playBGM *
.panel 3
.transition 0 * 10
.stage	* WHITE.png 0 0
.wait 300
.playBGM efBGM026mix.ogg
.transition 0 * 10
.stage	vista_window2.png ev00_012a01_70002a.png 1500 500
.scroll	400 1167	10
.endScroll f



.wait 100

.transition 0 * 20
.stage	vista_window2.png ev00_015a02_70002a.png 0 0
.message	140	yuk-702_01-0003	#桪丂巕	「真是悲伤的事情呢……」\v\a
.wait 50
.message	150	yuk-702_01-0005	#桪丂巕	「失去的记忆……。再也取不回来了，什么的……」\v\a
.wait 50
.transition 0 * 20
.stage	vista_window2.png ev00_014a01_70002b.png 0 0
.message	160	him-702_01-0003	#丂梉丂	「并不是取不回来。虽然她失去了记忆，但是千寻和莲治所度过的时间是无论如何也不会消失的」\v\a
.wait 40
.message	170	him-702_01-0005	#丂梉丂	「会消失的毫无痕迹之类的事情——绝对不会发生」\v\a
.wait 50
.transition 0 * 20
.stage	vista_window2.png ev00_012a01.png 0 0
.message	180	yuk-702_01-0007	#桪丂巕	「即使是不成形的东西，也一定能传达到什么地方去」\v\a
.wait 50
.message	190	yuk-702_01-0009	#桪丂巕	「——相信这种事情，没关系吗？」\v\a
.wait 50
.message	200	him-702_01-0007	#丂梉丂	「相信吧，我们不得不信」\v\a
.wait 100
.transition 0 * 20
.stage	vista_window2.png ev00_014a03.png 0 0
.message	240	him-702_01-0009	#丂梉丂	「即使是你的回忆，也没有消失」\v\a
.wait 100
.transition 0 * 20
.stage	vista_window2.png ev00_013a05_close.png 0 0
.message	250	yuk-702_01-0011	#桪丂巕	「我的回忆……」\v\a
.wait 100
.transition 0 * 20
.stage	vista_window2.png ev00_013a05.png 0 0
.message	260	yuk-702_01-0013	#桪丂巕	「但是，我失去的东西已经数不胜数了呢」\v\a
.wait 120
.transition 0 * 20
.stage	vista_window2.png ev03_056a03.png 0 0
.message	280	yuk-702_01-0015	#桪丂巕	「记忆满是破绽，到处都是疑云密布的样子……」\v\a
.wait 150
.message	290	yuk-702_01-0017	#桪丂巕	「对于我们两人一起度过的时间，我是抱以怎么样的心情」\v\a
.wait 70
.message	300	yuk-702_01-0019	#桪丂巕	「连这份心情也已经消失的遥不可及」\v\a
.wait 100
.transition 0 * 20
.stage	vista_window2.png ev00_014a03_mugai_a.png 0 0
.message	320	him-702_01-0011	#丂梉丂	「我还记得。和你一起度过的时间，季节——任何事情都没有忘记」\v\a
.wait 70
.transition 0 * 20
.stage	vista_window2.png ev00_017.png 0 600
.message	330	yuk-702_01-0021	#桪丂巕	「……能让我回忆起来吗？」\v\a
.wait 100
.transition 0 * 20
.stage	vista_window2.png prologue_mugai_i2.png 0 0
.message	340	him-702_01-0013	#丂梉丂	「回忆起来吧」\v\a
.wait 80
.transition 0 * 20
.stage	vista_window2.png prologue_mugai_d.png 0 0
.message	350	him-702_01-0015	#丂梉丂	「这份记忆不仅仅是我的东西」\v\a
.wait 100
.message	360	him-702_01-0017	#丂梉丂	「虽然有很多痛苦的事情，但是对于你我来说，是绝对不可替代的回忆」\v\a
.wait 100
.transition 0 * 20
.stage	vista_window2.png prologue_mugai_c.png 0 0
.message	370	yuk-702_01-0023	#桪丂巕	「……是」\v\a
.transition 0 * 20
.stage	vista_window2.png ev00_014a01_mugai_a.png 0 0
.message	380	him-702_01-0019	#丂梉丂	「我为你预留着的记忆——现在开始返还给你」\v\a
.transition 0 * 10
.stage	vista_window2.png WHITE.png 0 0
.wait 100
.playBGM *
.transition 0 * 10
.stage	* WHITE.png 0 0

.setGlobal ef_702_01 = 1

.pragma enable_control



.chain 400_01.sc
