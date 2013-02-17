; ファイル: 102_03.txt
;■宫村を追いかけるを選択
.playBGM efBGM010.ogg
.transition 1 fadeSide.png 20
.stage	* bgc_sch002a01_01.png 0 0
;（階段にしたら，，，変か）
.message	100		丂峢丂	「宫村」
.message	110			我追向慢慢走着的宫村，从背后喊住了她。
.transition 0 * 20
.stage	* bgc_sch002a01_01.png 0 0 st_miyako07a04.png 410
;（ここからの宫子の表情構築は要注意。かなり極端に構築してますが）
.message	120	miy-102_03-0003	傒傗偙	「嗯……？」
.message	130		丂峢丂	「难道说，已经要回去了吗？」
.transition 0 * 40
.stage	* bgc_sch002a01_01.png 0 0 st_miyako08a03.png 410
.message	140	miy-102_03-0005	傒傗偙	「诶？　啊啊，嗯。是打算要回去，有什么事情吗？」
.message	150			怎么感觉跟平时不太一样……。
.message	160			情绪有些异样的低啊。
.message	170		丂峢丂	「呃，到不是有什么事情。还在午休就打算回去么，身体哪里不舒服吗」
.message	180			果然是，那一夜碰到头留下的后遗症吗……？
.message	190	miy-102_03-0007	傒傗偙	「不，我很好啊。和平常一样精神十足哦」
.message	200		丂峢丂	「……嘛，那样就好」
.message	210			虽然看上去不怎么有精神，但本人这么说的话就没办法了吧。
.message	220			再追问下去，也不会有什么意义。
.transition 0 * 40
.stage	* bgc_sch002a01_01.png 0 0 st_miyako07a04.png 410
.message	230	miy-102_03-0009	傒傗偙	「话就这些吗？」
.message	240		丂峢丂	「啊啊」
.message	250	miy-102_03-0011	傒傗偙	「那么，我就回去了……」
.transition 0 * 40
.stage	* bgc_sch002a01_01.png 0 0 st_miyako08a03.png 410
.message	260			突然宫村看向我的身侧。
;.transition 0 * 20
.transition 1 fadeSide.png 20
.stage	* ev01_038a01.png 0 0
.message	270			在那站着的，是不知何时跟过来的景。
.message	280	miy-102_03-0013	傒傗偙	「作把女朋友放在一边，跟别的女孩子搭话可不太好哦，广野君」
.transition 0 * 40
.stage	* ev01_038a02.png 0 0
.message	290	kei-102_03-0003	丂宨丂	「才，才不是什么女朋友！」
.message	300			景比我还要快的否定了下来。
.message	310	miy-102_03-0015	傒傗偙	「诶，是这样吗？　因为紧紧的跟着所以就那么想了……」
.transition 0 * 40
.stage	* ev01_038a03.png 0 0
;（ここで激怒表情でいいのか注意）
.message	320	kei-102_03-0005	丂宨丂	「仅仅是青梅竹马而已！　而且，谁紧紧的跟着了……」
.message	330			不，我也这么认为。
.message	340			话说回来，你脸红的过分了喂。
.message	350	miy-102_03-0017	傒傗偙	「仅仅是青梅竹马？」
.message	360	kei-102_03-0007	丂宨丂	「嗯！再说为什么我非得是广野前辈的女朋友不可呢」
.message	370	miy-102_03-0019	傒傗偙	「哼～嗯……」
.message	380	kei-102_03-0009	丂宨丂	「那算什么，那带有暗示色彩的说法方式！」
.message	390	miy-102_03-0021	傒傗偙	「不，没什么啊。那就这样，我必须在午休结束之前逃掉呢」
.message	400			轻轻的挥了挥手，宫子离开了。
.transition 1 fadeSide.png 20
.stage	* bgc_sch002a01_01.png 0 0
;（フェードの仕方，切り替えのタイミングなど注意のこと。ここは通常フェードで？）
.message	410		丂峢丂	「相性不行啊，你们」
.transition 0 * 20
.stage	* bgc_sch002a01_01.png 0 0 st_kei01a03.png 380
;（04a04でも？）
.message	420	kei-102_03-0011	丂宨丂	「广野先辈，和宫村先辈认识的吗？」
.message	430			不知为何景狠狠的盯着我。
.message	440		丂峢丂	「嘛，稍有个机会便认识了而已。并没有说过多少次话呢」
.message	450		丂峢丂	「难道说，你知道关于宫村的事情吗？」
.chain 102_04.sc
;■102_04へ。

;.end
