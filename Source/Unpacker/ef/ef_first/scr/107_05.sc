; ファイル: 107_05.txt
;■「迎えにいく」を選択。
;■背景：駅前广場（冬），１９時
;■　　　　广野纮　　：私服（冬·外出）
;■　　　　宮村宫子：制服（冬·外出）
.playBGM efBGM031.ogg
.transition 1 fadeSide.png 10
.stage	* bgw_sky001a01_03.png 0 0
.panel 1
.message	100			于是，便有了没能拒绝而去接人了的笨蛋一名。
.message	110			对方的宫子该怎么说呢──
.screen sc_night01.png sc_night01.png
.overlay * or_miyako03a01.png
.transition 1 fadeSide.png 20
.stage	* bgw_normal003m11_03.png 0 0 st_miyako07a02.png 410
;.stage	* bgw_normal003m11_03.png 0 0 st_miyako07a01.png 410
;（モブ入りにしてあります）
.message	120	miy-107_05-0003	傒傗偙	「风差不多已经停了呢。今天一直被头发搔得眼睛痛痛的好难受呢」
.message	130			刚才那副小媳妇的样子哪去了。
.message	140			仅仅能清楚的看到她的高兴而已。
.message	150			难道说，说害怕什么的只是幌子，又跟往常一样在耍我吗？
.transition 0 * 40
.stage	* bgw_normal003m11_03.png 0 0 st_miyako08a01.png 410
.message	160	miy-107_05-0005	傒傗偙	「难道说广野君，生气了吗？」
.message	170			宫子停下脚步，这样说道。
.message	180		丂峢丂	「别把我当成随叫随到的那么好用的人就行，这次只是偶尔为之」
;■真面目
.transition 0 * 40
.stage	* bgw_normal003m11_03.png 0 0 st_miyako08a02.png 410
.message	190	miy-107_05-0007	傒傗偙	「我想着就是随叫随到的……」
.message	200		丂峢丂	「给我等下」
.transition 0 * 40
.stage	* bgw_normal003m11_03.png 0 0 st_miyako02a01.png 350
.message	210	miy-107_05-0009	傒傗偙	「广野君～G～O～！　那样叫着，然后水池的水就被分开，从那里缓缓的现出身影…」
.message	220		丂峢丂	「我是从哪来的巨大机器人啊」
.message	230			再说，这也太老套吧。
.message	240		丂峢丂	「那种事情怎样都无所谓了，赶快给我走啦」
.transition 0 * 40
.stage	* bgw_normal003m11_03.png 0 0 st_miyako04a01.png 400
;（表情とポ～ズ変化，注意）
.message	250			虽然我这么说，宫子却没有移动一步。
.message	260			刚才过分的淘气不知何时已经飞走，留下的一张认真的脸。
.message	270		丂峢丂	「喂」
.message	280	miy-107_05-0011	傒傗偙	「广野君，还没吃晩饭吗？」
.message	290		丂峢丂	「……啊啊」
.transition 0 * 40
.stage	* bgw_normal003m11_03.png 0 0 st_miyako04a02.png 400
.message	300	miy-107_05-0013	傒傗偙	「作为还礼今天也作晚饭给你吃。去下商店街买点东西吧」
.message	310			也就是要到我家了吗。
.message	320			然后还不得不把她送回自己家去……。
.message	330			虽然比较麻烦，但宫子作的饭确实很有魅力。
.message	340		丂峢丂	「那还真是感谢……准备做什么呢？」
.transition 0 * 40
.stage	* bgw_normal003m11_03.png 0 0 st_miyako00a02.png 350
;.stage	* bgw_normal003m11_03.png 0 0 st_miyako01a02.png 400
;（01a01で？）
.message	350	miy-107_05-0015	傒傗偙	「海鲜咖喱饭怎么样呢。虽然会稍微花些时间」
.message	360		丂峢丂	「时间无所谓了。倒是，还没吃过海鲜咖喱饭呢。很好吃吗？」
.transition 0 * 40
.stage	* bgw_normal003m11_03.png 0 0 st_miyako02a01.png 350
.message	370	miy-107_05-0017	傒傗偙	「很好吃啊。虾仁、墨鱼以及海贝。而且还要加入没刺的鱼身。别长时间的煮才是要点哦」
.message	380			宫子她浮起一副从心底高兴的表情。
.message	390		丂峢丂	「嘿诶」
.message	400		丂峢丂	「说起来，你很喜欢鱼啊」
.transition 0 * 40
.stage	* bgw_normal003m11_03.png 0 0 st_miyako06a02.png 400
.message	410	miy-107_05-0019	傒傗偙	「嗯，超喜欢。但是，鱼那边却不爱我啊～」
.message	420		丂峢丂	「那算什么。被鱼爱上也只会困扰的吧」
.message	430			到是，少用爱这个词啊。
.transition 0 * 40
.stage	* bgw_normal003m11_03.png 0 0 st_miyako06a03.png 400
.message	440	miy-107_05-0021	傒傗偙	「会困扰……吗？」
.message	450		丂峢丂	「如果是我的话，对象比起鱼类来，还是人类好点」
.transition 0 * 40
.stage	* bgw_normal003m11_03.png 0 0 st_miyako06a04.png 400
;（表情注意。ポ～ズも変える？05ポ～ズとか）
.message	460	miy-107_05-0023	傒傗偙	「如果是小景的话更好？」
.message	470		丂峢丂	「……少把话转移到别的地方去」
.screen * *
.transition 0 * 20
.stage	* ev01_090a01_mugai_a.png 0 0
;.stage	* ev01_090a_mugai_a.png 0 0
;（ここから切り出しで？）
.message	480			我这么说着，背向宫子走了起来。
.message	490			不跟过来的话也无所谓。
.message	500			现在不想在这提到景。
.transition 0 * 20
.stage	* ev01_090a01.png 0 0
.message	510	miy-107_05-0025	傒傗偙	「纮君」
.transition 0 * 40
.stage	* ev01_090a02.png 0 0
.message	520			纮君？
.transition 0 * 40
.stage	* ev01_090b01.png 0 0
;（フェ～ドスピ～ドは40でいいか？）
.message	530		丂峢丂	「干吗啊」
.message	540			被这样叫就站住，正是我的温柔之处啊。
;（ここでb02表情でも？）
.message	550	miy-107_05-0027	傒傗偙	「手，拉起来好吗」
.message	560			对着转过头的我，宫子轻轻说道。
.message	570		丂峢丂	「不要，拉手什么的」
.transition 0 * 40
.stage	* ev01_090b02.png 0 0
.message	580	miy-107_05-0029	傒傗偙	「真的讨厌的话我就放弃。但是，如果只是害羞的话……不也好吗。拉起来吧」
.message	590		丂峢丂	「…………」
.transition 0 * 40
.stage	* ev01_090b04.png 0 0
.message	600	miy-107_05-0031	傒傗偙	「我真的好害怕好害怕。虽然知道自己是多么的软弱无力，但是那样的，经历多少次也不会习惯啊」
.message	610			遭遇过很多次吗。
.message	620			但是，嘛……被订上也不是无稽之谈。再怎么说也有着这样的外表啊。
.transition 0 * 40
.stage	* ev01_090b03.png 0 0
;（b03とb04の使い分け，注意して）
.message	630	miy-107_05-0033	傒傗偙	「在这个时候，就算像我这样总是孤独飘荡的人也会有需要呢」
.message	640		丂峢丂	「需要，需要什么」


.transition 0 * 40
.stage	* ev01_090b06.png 0 0


.message	650	miy-107_05-0035	傒傗偙	「能让我觉得并不孤独的人」
.message	660			……果然女人是狡猾的。
.message	670			不对，是宫子是狡猾的。
.transition 0 * 40
.stage	* ev01_090b05.png 0 0
;（纮の表情，ここで変えていいか注意して）
.message	680		丂峢丂	「你想说的话还是一直理解不能」
.message	690			在一边说出掩盖害羞的话同时。
.transition 0 * 20
.stage	* ev01_091_mugai_b.png 0 0
;.stage	* ev01_091_mugai_a.png 0 0
;（もう少し左寄りに？）
.message	700			我，紧紧的抓住了宫子的手。
.transition 0 * 20
.stage	* ev01_091a01.png 0 0
;.stage	* ev01_091.png 0 0
.message	710	miy-107_05-0037	傒傗偙	「…………哈～」
.message	720		丂峢丂	「干吗一副发呆的表情啊你」
.message	730			怎么都行给点反应好吧，越来越让人害羞了。
.message	740	miy-107_05-0039	傒傗偙	「但是……真的没想到会拉起来呢」
.message	750		丂峢丂	「那我松开了」
.message	760	miy-107_05-0041	傒傗偙	「呜哇，不行不行！　松开的话我恨你一生～」
.transition 0 * 20
.stage	* ev01_092.png 0 0
.message	770			这样说着，宫子抱住了我手臂怎样都挥不掉。
.message	780			这一定是，在我不知道的时候，这家伙又心血来潮的原因吧。
.message	790			一定是这样没错。
.panel 0
.overlay * *
.playBGM *
.transition 0 * 10
.stage	* WHITE.png 0 0
.transition 0 * 10
.stage	* WHITE.png 0 0
.wait 100

.chain 108_01.sc
;■108_01へ。

;.end
