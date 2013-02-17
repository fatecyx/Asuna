; ファイル: 212_04.txt
;■212_02，212_03より
;■背景：京介自室（夏，２０時
;■　　　　堤京介：私服（夏）


;■御影チェック
;.playSE kyo_keitai_vib.ogg true

.transition 1 fadeSide.png 10
.stage	* bgc_home002a01_03.png 0 0
;（イベントＣＧからのインでもいいかもしれません）

;■御影チェック
.playSE kyo_keitai_vib.ogg true

.panel 1
.message	100			摄影结束后，刚回到家手机便震动起来。
.message	110			预想外的人物──不，也不算没想到。
.playSE * f * 0
.transition 0 * 20
.stage	* ev02_112a01.png 0 0
.message	120		嫗丂夘	「喂，您找谁」
;.transition 0 * 20
;.stage	* ev02_112a01_mugai_b.png 0 0
.message	130	izu-212_04-0003	丂愹丂	『那么，就让我听听你的高见吧』
.message	140			连前置的寒暄都没有，她就这么说起来。
;.transition 0 * 20
;.stage	* ev02_112a01_mugai_a.png 0 0
.message	150		嫗丂夘	「不是说了明天到学校再说了嘛」
.message	160	izu-212_04-0005	丂愹丂	『要重视时间啊』
.message	170	izu-212_04-0007	丂愹丂	『刚刚入摄影研究会时，最初传授给我们不就是这个吗？』
;.transition 0 * 20
;.stage	* ev02_112a01.png 0 0
.message	180		嫗丂夘	「你还真能记起那么旧的事情啊」
.message	190	izu-212_04-0009	丂愹丂	『是京介你太爱忘事』
.message	200		嫗丂夘	「可能吧」
.message	210			本来，不用说也知道也会重视关于电影拍摄的时间。
.message	220			摄影本身就会受到天气和时间巨大的影响。
.message	230			磨磨蹭蹭的话，就会失去拍好画面的机会。
.message	240	izu-212_04-0011	丂愹丂	『午休时逃掉摄影的事原谅你也就算了』
.message	250	izu-212_04-0013	丂愹丂	『好了，你想说的到底是什么？』
.message	260			今天放学后摄影休息──因为演员有事休息──如此。
.message	270			课程结束之后，我联络了她，对白天逃掉摄影作了道歉，以及说明天早上会有话对她说。
.message	280			然后马上就被新藤拉走，没空详细对她解释。
;.transition 0 * 40
;.stage	* ev02_112b01_mugai_c.png 0 0
.transition 0 * 40
.stage	* ev02_112b01.png 0 0
;（フェ～ドスピ～ド，ポ～ズを変えるタイミングには注意して）
.message	290		嫗丂夘	「想要重视时间啊」
;.transition 0 * 20
;.stage	* ev02_112b01.png 0 0
.message	300	izu-212_04-0015	丂愹丂	『给我用容易理解的说法。这个前辈不也说过吗？』
.message	310		嫗丂夘	「不凑巧，我可不是什么懂事的后辈」
.message	320	izu-212_04-0017	丂愹丂	『但是很有能力。而且是非同寻常的有能力』
.message	330		嫗丂夘	「哈～，你会说这种话还真是第一次啊」
.message	340	izu-212_04-0019	丂愹丂	『对你来说，夸奖打击都没用的吧。谁说什么也只会做自己想做的事情而已』
.message	350			单是听发言的话，宫村宫子也是个足够自我主义了的人啊。
.playBGM efBGM016.ogg
.message	360	izu-212_04-0021	丂愹丂	『这次是来真的是吧……？』
.message	370		嫗丂夘	「啊啊」
.message	380	izu-212_04-0023	丂愹丂	『京介你，终于找到了想做的事情了呢』
;.transition 0 * 20
;.stage	* ev02_076a03.png 0 0
;.stage	* ev02_112b01_mugai_c.png 0 0
.message	390		嫗丂夘	「啊啊，找到了。这次是真的」
.message	400			想要拍摄新藤景──想要和那女孩一起。
.message	410			对于我来说她已经跨越了演员的框架，是非常重要的存在。
;.transition 0 * 20
;.stage	* ev02_112b01.png 0 0
.message	420		嫗丂夘	「我终于发现自己只是想着电影的事，而没有注意身边的现实」
.message	430		嫗丂夘	「电影虽然是虚构的东西，但它也是来源于现实的」
.message	440	izu-212_04-0025	丂愹丂	『现在才理解这点，你还真是迟钝的』
.transition 0 * 20
.stage	* ev02_112a01.png 0 0
;.transition 0 * 20
;.stage	* ev02_112b01_mugai_a.png 0 0
.message	450		嫗丂夘	「确实如此呢。所以才会对研究部引来一堆麻烦。抱歉」
.message	460	izu-212_04-0027	丂愹丂	『是啊，所以才不能再让你去现场转来转去』
;■笑顔
;.transition 0 * 40
;.transition 0 * 20
;.stage	* ev02_112a01.png 0 0
;.transition 0 * 20
;.stage	* ev02_112b01.png 0 0
.message	470	izu-212_04-0029	丂愹丂	『京介，你还是要被炒了呢』
;.transition 0 * 40
;.stage	* ev02_112a01.png 0 0
.message	480		嫗丂夘	「……谢了」
.message	490			真的很值得感谢。
.message	500			无论去还是离开，我擅自的行为都被她原谅了。
.message	510	izu-212_04-0031	丂愹丂	『大家那边我会适当说点什么的，别再多说什么哦』
;.transition 0 * 40
;.stage	* ev02_112b01.png 0 0
.message	520		嫗丂夘	「我知道」
;■静かな怒り
.message	530	izu-212_04-0033	丂愹丂	『永远也不要回来哦。你就算回来，我也绝对不会再管了』
;.transition 0 * 40
.transition 0 * 20
.stage	* ev02_112b01.png 0 0
.message	540		嫗丂夘	「……啊啊」
.message	550	izu-212_04-0035	丂愹丂	『所以，你呢……』
.message	560			一瞬的沉默。
.message	570	izu-212_04-0036		听到她轻轻吸了一口气的声音。
.message	580	izu-212_04-0037	丂愹丂	『一定要拍自己的电影到最后哦』
.message	590		嫗丂夘	「啊啊，我知道的。我知道的……」
.message	600	izu-212_04-0039	丂愹丂	『就算你回来……也不会让你入我们的圈子的呢』
.message	610			也许是心理作用吧，她的声音好象有些颤抖。
.message	620			我一瞬想到。
.message	630			难道说，把我喊回研究部的是不是她一个人下的决定。

;■御影チェック
;.message	640			彼女はたぶん，俺のことを本当に思っていてくれていた……。
.message	640			她大概，是真的喜欢着我的吧……。
.message	650		嫗丂夘	「抱歉…呢」
.message	660	izu-212_04-0041	丂愹丂	『笨～蛋，别道歉啊』
.message	670			一同在研究部同事的时候。
.message	680			作为恋人交往的时候。
.message	690			说不定对她更温柔些好吧。
;■笑顔
.message	700	izu-212_04-0043	丂愹丂	『再见，要努力哦』
.message	710		嫗丂夘	「你也一样」
.transition 0 * 40
.stage	* ev02_112c01.png 0 0
;（フェ～ドスピ～ドは20で？）
.message	720			后悔已经太迟了，所以我什么都没说的挂了电话。
.message	730			已经无法在取回和她在一起的时间。
.message	740			那么至少要考虑从今往后的事。
.transition 0 * 20
.stage	* ev02_112c01_mugai_a.png 0 0
.message	750			我和陷入同样的境地，就算如此仍然直视真实，那个坚强的她的事。
.message	760			仅仅是新藤景的事──
.panel 0
.playBGM *
.transition 0 * 10
.stage	* WHITE.png 0 0
.transition 0 * 10
.stage	* WHITE.png 0 0
.wait 100

.chain 213_01.sc
;■213_01へ。

;.end
