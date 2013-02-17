; ファイル: 113_01.txt
;■＜１章：１３日目＞
;■背景：纮自室（冬，１４時
;■　　　　广野纮　　：私服（冬）
;■　　　　宮村宫子：私服（冬）
;■「宫子のそばにいる」を選択

;■御影チェック
;■　ノイズにしか聞こえないと複数から。
;.playSE2 eakon.ogg f

.transition 0 * 10
.stage	* ev01_157a01_mugai_a.png 0 0
;.stage	* bgc_home001a01_01.png 0 0
;（ここ，157の切り出し画像を？）
;（通常背景でインしてますが，実際はイベントＣＧを挿むこと）
.panel 1
.message	100			沙，沙，沙。
.panel 0
.transition 0 * 40
.stage	* ev01_157a01_mugai_b.png 0 0
.hscroll	800	10
.endScroll f

;.transition 0 * 20
.transition 0 * 10
.stage	* ev01_157a01.png 0 0
.panel 1
.message	110			铅笔在在写生簿上自由的游动着。
.message	120			从小时侯起一直都在做这个。
.message	130			父亲一直不知道自己作为父亲该作些什么。
.message	140			作为画家的他，除了教授绘画便再没有和孩子们的交流方式。
.message	150			所以才只教给了姐姐和我画画而已。
.message	160			其結果就是姐姐到了海外的名门美术学校留学，而弟弟却背父亲之道而驰当了漫画家。

;■御影チェック
;.message	170			でも，俺も今でもこうして絵を描き続けてる。
.message	170			但是，我现在还会这样把画画下去。

.message	180			大概是确实有被传达到的东西，有被继承过来的东西吧。
.transition 0 * 20
.stage	* ev01_157b01.png 0 0
.message	190	miy-113_01-0003	傒傗偙	「嗯～……」
.message	200			宫子在床上睡着翻了一下身。
.message	210		丂峢丂	「啊～，POSE变了」
.message	220			为了不惊醒睡着的宫子而轻声说着，停下了手。
.message	230		丂峢丂	「不过，这个姿势也不错呢……」
.message	240			宫子一丝不挂的睡着。
.message	250			虽然稍微有些冷，但因为妨碍了写生我就掀掉了她的被褥。
.message	260			再说还有暖气在，大概不会感冒的吧──我擅自的这么作了决定。
.message	270			翻过身的宫子的样子有不错的H感。
.message	280			画好的画之后再整理上线，我又翻过写生簿的一页。
.message	290		丂峢丂	「现在先不要动哦～」
.transition 0 * 20
.stage	* ev01_157b02.png 0 0
;.stage	* ev01_157b01.png 0 0
.message	300			虽然也不可能听到，但总之先就这么说了一句，再次动起铅笔。
.message	310		丂峢丂	「不过」
.message	320			宫子真的体型很好啊。
.message	330			果然模特的等级高的话，下笔的走向完全都会不同。
.message	340			好愉快。
.message	350			画画原来是这么愉快的事情吗。
.message	360			右手的疼痛已经注意不到，心脏有着出乎寻常的跃动。
.message	370			漫画的工作如果也有这么愉快的话……不，现在觉得只要宫子在身边怎样都会愉快。
.message	380			就是这样没错。
.message	390			一直都是紧绷的状态，仅仅注意着截稿而画画自然不会快乐。
.message	400			虽然没说到想要有放松的空余时间，但如果工作也能愉快起来的话……。
.message	410	miy-113_01-0005	傒傗偙	「呜～……」
.transition 0 * 20
.stage	* ev01_157a01.png 0 0
.message	420			转圈。
.transition 0 * 40
.stage	* ev01_157a02.png 0 0
;（フェ～ドスピ～ド20で？）
.message	430		丂峢丂	「呀～」
.message	440			又翻身！
.message	450			这个死女人！
.message	460		丂峢丂	「绑起来好了……」
.message	470			虽然那便会开启新的世界的大门了，但如果宫子不是醒着的话就没意思了。
.transition 0 * 20
.stage	* ev01_157a03.png 0 0
.message	480		丂峢丂	「嘛，顺便做做看……。也算是练习，画各种各样的POSE看吧」
.message	490			因为现在没怎么改变姿势，换下地方从其它视点画画看好了。
.transition 0 * 20
.stage	* ev01_157a04.png 0 0
;（次で立ち上がらせる？テンポは注意）
.message	500		丂峢丂	「嗯，到这页就用光了啊」
.transition 0 * 20
.stage	* ev01_158a01.png 0 0
;.transition 0 * 20
;.stage	* ev01_157a04.png 0 0
.message	510			站起来看向书柜。
.message	520			原来买的写生簿没有了吗。
.message	530			在书柜找来找去，虽然找出一堆神秘文件，但却完全找不到想要的东西。
.playSE hondana_barabara.ogg f 0 *
;（後半の音は余計なので切ること。要加工）
.transition 0 * 40
.stage	* ev01_158b01.png 0 0
.message	540			咚唰咚唰咚唰！
.message	550		丂峢丂	「呜哇」
.message	560			堆起来的资料本和用过写生簿的发生了雪崩。
.playSE *
.transition 0 * 20
.stage	* ev01_158c01.png 0 0
.message	570			偷偷的看向床那边……。
.message	580	miy-113_01-0007	傒傗偙	「呼～呼～……」
.message	590			呼呼睡的正香。
.message	600			从早上开始就一直是全力Mode，自然会累的吧。
;☆（「取り上げた」，，，というこの箇所の演出は注意。切り出し？）
.message	610			我苦笑着捡起落在地方的本子。
.message	620		丂峢丂	「啊……」
.transition 0 * 20
.stage	* ev01_159a01.png 0 0
.message	630			我把目光停在了一本素描簿上。
.message	640			那是一本不算很旧，但也不算很新的素描簿。
.message	650			在这里面画着谁──我瞬间就明白过来。
.message	660			我深深叹了一口气，慢慢的掀开封面。
;.transition 0 * 20
.playSE hiro_page.ogg f 0 *
.transition 1 fadeSide2.png 20
.stage	* ev01_159b01.png 0 0
;（めくる演出，注意）
.message	670			──上面画着的是，景。

;■御影チェック
;.message	680			日付を見ると……今の羽山と同じ年の頃か。
.message	680			看向日期……那时的她大概和现在羽山一样年纪吧。

.message	690			对了，那个时间还没有连载，有空的时候就会画画。
.transition 0 * 20
.stage	* ev01_160a01_mugai_a.png 0 0
.message	700			说到模特的话，除了景便再也想不到别人。


;■黒バック
;■回想，恥ずかしそうに
.transition 0 * 20
.stage	* ev01_160a01.png 0 0
;（四角く，白マスクで覆う？）
;.stage	* WHITE.png 0 0
;（白挿んでますが，実際にはイベントＣＧです。大胆に，past_windowを使って演出してください）
.message	710	kei-113_01-0003	丂宨丂	「等下，哥哥。别那样盯着人家看啊」
.message	720		丂峢丂	「少胡说了。如果不看就能画的话就不要什么模特了」
.transition 0 * 40
.stage	* ev01_160a02.png 0 0
;（フェ～ドスピ～ドは20で？）
.message	730	kei-113_01-0005	丂宨丂	「真是的～。等下要陪我练习哦」
.message	740		丂峢丂	「知道了啦老实给我别动」
.message	750	kei-113_01-0007	丂宨丂	「装伟大。真的的哥哥似的……」


;■通常背景，纮自室
.transition 0 * 20
.stage	* ev01_159b01.png 0 0
;（過去からうまく，このイラストに移行するように。重ねる感じで）
.message	760			坐在椅子上，掀开少女漫画的景。
;.transition 0 * 20
.playSE hiro_page_b.ogg f 0 *
;（ペ～ジを繰る音をはやく？）
.transition 1 fadeSide2.png 20
.stage	* ev01_159b02.png 0 0
.message	770			提着制服的裙裾，轻轻笑着的景。
;.transition 0 * 20
.playSE hiro_page_b.ogg f 0 *
.transition 1 fadeSide2.png 20
.stage	* ev01_159b03.png 0 0
.message	780			拿着明显和身体不协调的篮球的景。
.message	790			当然，虽然我的画还很差。
.message	800			但却尽全力把景画的美丽。
.message	810			简直让我觉得都不像自己的画了。
.message	820		丂峢丂	「景她……」
.message	830			等下，景她现在应该正在比赛中的吧。
.message	840			在体育馆看不到我的身影自然会失望的吧……。
.message	850			但是，我所选择的是──
.transition 0 * 20
.stage	* ev01_158a01.png 0 0

;■御影チェック
;■　文章でちょっと対応してみますか。
;■　他に気になる人が出てくるようなら，切り出そう。
;（この画像にインしてますが，纮の姿勢などに問題あるようなら切り出しか別の画像を）
;.message	860			ちらりと，ベッドを見る。
.message	860			把素描簿放回书柜，扭头看向床上。
.message	870			宫子带着安稳的呼声睡着。
.transition 0 * 20
.stage	past_window.png ev01_158a01.png 0 0
.message	880			我已经作出了选择，已经再也无法回头。
.message	890			我已经知道了和宫子重叠起来时的心情……。

;■御影チェック
;■　やっぱ変だわ。
;■　後，回想であるＨシ～ンから復帰する113_03が，上記「ev01_158a01.png」の
;■　画像から始まっていることを考えると，ここでホワイトアウトしかない。
.transition 0 * 10
.stage	* WHITE.png 0 0
;;.transition 0 * 20
;.transition 0 * 10
;.stage	past_window.png evh01_012.png 0 0

.message	900			今天早晨的记忆瞬间涌上心头。
.playSE2 *
.message	910			（备注：接下来将要进入Hsence）


.select 略过阅读:label1 继续阅读:label2
.label label1
.chain 113_04.sc
.label label2
.chain 113_02.sc
.transition 0 * 10
.stage	* WHITE.png 0 0

.chain 113_02.sc
;■113_02へ。

;.end
