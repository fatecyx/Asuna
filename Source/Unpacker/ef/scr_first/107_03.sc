; ファイル: 107_03.txt

.set favMiyako_d = favMiyako_d + 1
;■「そのまま帰る」を選択。
;■背景：学園·階段
;■　　　　广野纮　　：制服（冬）
;■　　　　宫村宫子：制服（冬）
.transition 1 fadeSide.png 20
.stage	* bgc_sch003a01_02.png 0 0
;（廊下からこの画像への移行，しっかりと）
.message	100			……景，也不是小孩子了。
.message	110			我一直这样注意下去也不是办法。
.message	120			我还有我要作的事情在。
.message	130		丂峢丂	「回去也没事吧」
.overlay * or_miyako02a.png
.playBGM * * 0
.transition 0 * 40
;■御影チェック
;■　目線逸れてて気持ち悪いな……。
;.stage	* bgc_sch003a01_02.png 0 0 st_miyako02a03.png 350
;.stage	* bgc_sch003a01_02.png 0 0 st_miyako03a02.png 400
.stage	* bgc_sch003a01_02.png 0 0 st_miyako05a09.png 400
;（ポ～ズと表情，注意のこと）
;（ここから立ち絵，モブのイベントＣＧへと繋げていきます）
.message	140	miy-107_03-0003	傒傗偙	「回去不行哦」
.message	150		丂峢丂	「诶？」
.message	160			就好象是瞬间移动一样，宫子突然就出现在了我面前。
.message	170		丂峢丂	「宫，宫子？」
.message	180			脸开始发烫，心跳开始加速。
.message	190			为什么我会如此动摇呢。
.transition 0 * 40
;.stage	* bgc_sch003a01_02.png 0 0 st_miyako01a03.png 400
.stage	* bgc_sch003a01_02.png 0 0 st_miyako01a03.png 370
;（表情，注意のこと）
;.stage	* bgc_sch003a01_02.png 0 0 st_miyako01a01.png 400
.message	200	miy-107_03-0005	傒傗偙	「稍微来下」
.message	210			也不等待这边的回答，宫子就拉着我的手走了起来。
.transition 0 * 20
.stage	* ev01_085.png 0 0
;（ＣＧの表示タイミング，フェ～ドスピ～ドにも注意のこと。40でもいい？）
.message	220		丂峢丂	「稍，稍等一下啊我说。来下去哪」
.message	230	miy-107_03-0007	傒傗偙	「屋顶」
.message	240			仅仅回答了这些，宫子就噌噌的走上了楼梯。
.panel 0


;■屋上（冬，１５時３０分
.playSE2 okuzyou_kaze.ogg f
;（ル～プさせてないのはワザと）
.transition 1 fadeSide.png 20
.stage	* ev01_086_mugai_a2.png 0 0
.panel 1
;（この切り出しだと，纮に当たる風が強くないように見える，，，のがネックだな）
;.stage	* ev01_086.png 0 0
;.stage	* bgw_sch007a01_02.png 0 0
;（いきなりイベントＣＧに移行させてますが，絵でも「屋上」であることを強調したい場合は，通常背景を挿むこと）
.message	250		丂峢丂	「干嘛啊，真是的」
.message	260			我一边挥掉宫子的手一边说。
.message	270			虽说预想到今天的风会很大……。
.message	280			但屋顶的风却强到了让人睁不开眼睛的程度。
.transition 0 * 20
.stage	* ev01_086_mugai_c.png 0 0
.message	290	miy-107_03-0009	傒傗偙	「呜～，果然很厉害呢，风」
;.transition 0 * 20
;.stage	* ev01_086_mugai_c.png 0 0
.transition 0 * 20
.stage	* ev01_086_mugai_b2.png 0 0
;（↑と切り出し逆転？）
.message	300			宫子的手紧紧按着头发和裙子。
;.transition 0 * 20
;.stage	* ev01_086_mugai_b2.png 0 0
.transition 0 * 20
.stage	* ev01_086a01.png 0 0
.message	310	miy-107_03-0011	傒傗偙	「但是除了广野君以外也没别的人，不按裙子也无所谓的吧？」
.transition 0 * 20
.stage	* ev01_086a02.png 0 0
;（a01表情の使いどころ，注意して。切り出しを一部ハキして？）
.message	320			说着，眼睛往上看着我征求这边的同意。
.transition 0 * 40
.stage	* ev01_086a03.png 0 0
.message	330		丂峢丂	「我说你，不要老戏弄人啊」
.message	340			我脸红着说。
.transition 0 * 40
.stage	* ev01_086a04.png 0 0
.message	350	miy-107_03-0013	傒傗偙	「我也不是随便就戏弄人啊～。我只会戏弄会作出有趣反应的人哦」
.message	360		丂峢丂	「……我可不是你的玩具啊」
.message	370	miy-107_03-0015	傒傗偙	「虽然我最开始是打算把你当玩具的呢～」
.transition 0 * 40
.stage	* ev01_086a05.png 0 0
.playSE2 *
.message	380		丂峢丂	「果然……最开始什么？」
.playBGM efBGM019.ogg
;（音楽位置は注意して。選曲含めて。音声が来てから，もう一度，確認のこと）
.transition 0 * 40
.stage	* ev01_086a06.png 0 0
.message	390	miy-107_03-0017	傒傗偙	「啊～啊，但是还真是糟糕呢」
.message	400			虽然我的问题被无视掉，但我也差不多习惯宫子这种态度了。
.message	410		丂峢丂	「……什么真是糟糕？」
.transition 0 * 40
.stage	* ev01_086a07.png 0 0
;.stage	* ev01_086a06.png 0 0
;（この前で06表情を？）
.message	420	miy-107_03-0019	傒傗偙	「嗯～，稍微有点小事。稍微变的麻烦起来了呢。真是的，怎么办呢」
.message	430		丂峢丂	「完全不明白你想说什么」
.message	440	miy-107_03-0021	傒傗偙	「虽然不知道该怎么说好……」
.message	450			宫子睁着本来就大大的眼睛盯着这边看。
.message	460	miy-107_03-0023	傒傗偙	「但是是哪错了呢，我是在这么想」
.message	470		丂峢丂	「所以说，我完全不明白你想说什么」
.message	480	miy-107_03-0025	傒傗偙	「班上的同学呢，这么说。我耳朵很尖所以听到了啦」
.message	490			宫子把视线移向一边说道。
;■真面目
.transition 0 * 40
.stage	* ev01_086a08.png 0 0
.message	500	miy-107_03-0027	傒傗偙	「宫村同学，也会那样的笑起来呢──之类的」
.transition 0 * 40
.stage	* ev01_086a09.png 0 0
.message	510	miy-107_03-0029	傒傗偙	「还真是失礼啊。我也是人，肯定会笑的啊」
.message	520		丂峢丂	「我到觉得是一直都看到你在笑来着」
.message	530			虽然偶尔也会露出认真的表情，但大体上都是像白痴一样在傻笑着。
.message	540			……一直都在笑着的女孩，吗。
.message	550			这样想起来，总觉得有点可疑的味道。
.message	560			这世间可不是能一直保持微笑那么轻松的。
.message	570		丂峢丂	「嘛，那到也算了啦」
.message	580	miy-107_03-0031	傒傗偙	「嗯」
.message	590		丂峢丂	「说起来你不是有事吗，到底要干吗？」
.transition 0 * 40
.stage	* ev01_086a10.png 0 0
.message	600	miy-107_03-0033	傒傗偙	「嗯～？　诶～嗯……怎么说好呢」
.message	610			虽然像是做出考虑的样子，但完全没有在考虑的感觉。
.message	620		丂峢丂	「不，无所谓了」
.message	630			就算被说明，我也不能保证可以理解。
.message	640		丂峢丂	「已经没事了吧。那我就要回去了，你怎么办？」
.message	650			好像又想说去你家之类的样子。
.message	660	miy-107_03-0035	傒傗偙	「不怎么办啊。今天要去买东西。啊，不能跟过来哦。也要买女孩子的秘密的东西呢」
.transition 0 * 40
.stage	* ev01_086a11.png 0 0
;（纮の表情変えるタイミング，注意して）
.message	670		丂峢丂	「谁要去啊」
.transition 0 * 40
.stage	* ev01_086a12.png 0 0
.message	680	miy-107_03-0037	傒傗偙	「嗯，我就喜欢明事理的好孩子哦」
.message	690			宫子微笑起来。
.message	700			就好像把人当弟弟看了一样……。
.message	710			而且确实有一点。
.message	720			看到宫子的笑颜时，会有确实的满足感。
.message	730			就好像找到忘记的重要的东西那样──取回什么的奇妙的感觉。
.panel 0
.playSE2 *
.playBGM *
.overlay * *
.transition 0 * 10
.stage	* WHITE.png 0 0

.chain 107_04.sc
;■107_04へ。

;.end
