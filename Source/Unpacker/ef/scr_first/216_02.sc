; ファイル: 216_02.txt
;重ねて問いかける　を選択
.message	100			我强迫自己挤出笑颜，再次向她问过去。
.message	110		嫗丂夘	「无论如何？」
;■悲しみ
.transition 0 * 40
.stage	* ev02_159d07.png 0 0
.message	120	kei-216_02-0003	丂宨丂	「……如果有回答的话，只能说更加不能」
.message	130	kei-216_02-0005	丂宨丂	「接受这个的资格……我根本没有」
.message	140		嫗丂夘	「不对。有接受它的资格的人只有你而已」
.message	150	kei-216_02-0007	丂宨丂	「这是你一个人的想法吧……！」
;■挑発
.transition 0 * 40
.stage	* ev02_159e01.png 0 0
.message	160	kei-216_02-0009	丂宨丂	「而且这算什么？　就对我那么执著？就因为没做到最后？」
.message	170	kei-216_02-0011	丂宨丂	「就那么可惜吗？」
.message	180		嫗丂夘	「啊ー，来这一招吗」
.transition 0 * 40
.stage	* ev02_159e02.png 0 0
.message	190	kei-216_02-0013	丂宨丂	「少装糊涂！　根本没有别的理由吧！」
.message	200		嫗丂夘	「说到可惜自然可惜啊」
.message	210		嫗丂夘	「因为你的身体很漂亮啊」
.transition 0 * 40
.stage	* ev02_159e03.png 0 0
.message	220	kei-216_02-0015	丂宨丂	「……！」
.message	230			新藤的脸又一下红透。
.message	240	kei-216_02-0017	丂宨丂	「说，说什么呢你！」
.message	250			喂，分明是你自己说出来的。
.message	260		嫗丂夘	「无论如何…我都需要你」
.message	270		嫗丂夘	「新藤景」
.transition 0 * 40
.stage	* ev02_159e04.png 0 0
.message	280	kei-216_02-0019	丂宨丂	「……我不要听」
.message	290			新藤激烈地把头摇了摇去。
.message	300			就像在拒绝着我，拒绝着我所追求的一切一样。
.message	310	kei-216_02-0021	丂宨丂	「求你了……不要再说什么了」
.message	320	kei-216_02-0023	丂宨丂	「我的心好痛，真的好痛……」
.message	330	kei-216_02-0025	丂宨丂	「你的心情愈加强烈，我也会愈加受到伤害……」
.message	340	kei-216_02-0027	丂宨丂	「你要明白啊……」
.message	350		嫗丂夘	「我并不是想要伤害你」
.message	360		嫗丂夘	「但是，我不会骗自己，我也不想骗自己」
.message	370	kei-216_02-0029	丂宨丂	「…………」
.transition 0 * 20
.stage	* ev02_159f01.png 0 0
.message	380			在我递出的胶卷前，新藤一瞬伸出了手──
;.transition 0 * 40
.transition 0 * 20
.stage	* ev02_159g01.png 0 0
;（フェードスピードは注意して）
.message	390			但还是什么都没说的转过了身。
.transition 0 * 20
.stage	* bgs_sky001a01_01.png 0 0
.message	400			然后，毫不停步地离开了屋顶。
.message	410			身体一下失去了力气。
.message	420			无论用什么样的手法作来的电影，都只是虚构的而已……。
.message	430			没有击碎现实的力量啊。
.message	440			一直都回旋于虚构的世界的我，一直不了解这一点。
.message	450			而现在这随之而来的报应，理所当然般折磨着我的心。
.panel 0
.transition 0 * 10
.stage	* WHITE.png 0 0

.chain 216_04.sc
;■216_04へ。

;.end
