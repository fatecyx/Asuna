; ファイル: 107_02.txt

.set favMiyako_a = favMiyako_a + 1
;☆（↑って必要か？）
;■景の様子を見に行くを選択。
;■背景：学園·廊下（冬，１５時
;■　　　　广野纮：制服（冬）
;■　　　　新藤景：制服（冬）
.message	100			1年级的教室也是很久不来了呢。
.message	110			分明去年我还在这里，但现在却稍稍有些不习惯。
.message	120			不算不习惯也要往前走。
.message	130			哪有时间去介意这群后辈。
.playSE kyoushitsu_door_open.ogg f 0 *
.message	140			咯啦。


;■背景：教室
.transition 1 fadeSide.png 20
.stage	* ev01_084_mugai_b.png 0 0
;.stage	* ev01_084_mugai_a.png 0 0
;（あんまいい切り出しの仕方じゃないやも）
;.stage	* ev01_083a01.png 0 0
;（このＣＧの表示タイミング，注意のこと。一年生の教室なので，通常背景から入る場合はモブにも注意。３年教室，，，じゃなくて２年教室と一緒のモブじゃまずいとか）
.message	150			打开目标的教室门，无视掉后辈觉得可疑的目光，走近那家伙的课桌。
.message	160			目标在一边作着回去的准备，一边和附近座位的女孩聊着天。
.message	170		丂峢丂	「喂」
;.transition 0 * 40
.transition 0 * 20
.stage	* ev01_083a02.png 0 0
;（ぽかんとするタイミングに注意。a01のノ～マル表情の使いどころも考えておくこと）
.message	180	kei-107_02-0003	丂宨丂	「……你怎么来了」
.message	190			景呆呆的张着嘴看着站在桌前的我。
.message	200		丂峢丂	「还好，还没去参加部团活动的是吧。稍微过来下好吧？」
.transition 0 * 40
.stage	* ev01_083a03.png 0 0
;（強気表情の使いどころはここでいいのか注意）
.message	210	kei-107_02-0005	丂宨丂	「虽然可以，但也不要堂堂正正的就走进低年级的教室好吧。大家会想成什么事的啊」
.message	220			如景所言，留在教室里的1年级学生们都明显露着疑惑的表情。
.message	230		丂峢丂	「什么事都没啊。走吧」
.message	240			我拉起景的手开始走起来。
.transition 1 fadeSide.png 20
.stage	* ev01_084.png 0 0
;（通常フェ～ドで？）
.message	250	kei-107_02-0007	丂宨丂	「稍，稍等一下啊。哥──先辈！」


;■背景：学園·階段
.overlay * or_kei02a.png
.transition 1 fadeSide.png 20
.stage	* bgc_sch003a01_02.png 0 0 st_kei01a06.png 380
.message	260	kei-107_02-0009	丂宨丂	「真是的。不要这样好吧！」
.message	270			走到楼梯的地方时，景啪的拍掉了我的手。
.message	280		丂峢丂	「你想的太多了啦」
.transition 0 * 40
.stage	* bgc_sch003a01_02.png 0 0 st_kei05a07.png 400
.message	290	kei-107_02-0011	丂宨丂	「前辈太不注意了好吧！　要是传出什么奇怪的流言怎么办啊」
.message	300		丂峢丂	「脸红的像熟透的一样说什么呢。我说你，没病吧？」
.transition 0 * 40
.stage	* bgc_sch003a01_02.png 0 0 st_kei01a10.png 380
;（表情とポ～ズ注意。「うつむいて」はいないので，，，）
.message	310	kei-107_02-0013	丂宨丂	「……！」
.transition 0 * 40
.stage	* bgc_sch003a01_02.png 0 0 st_kei01a09.png 380
;（表示タイミング，注意のこと）
.message	320			景她发出不算声音的声音，低下了头。
.message	330		丂峢丂	「抱歉，抱歉。说笑的啦」
.message	340	kei-107_02-0015	丂宨丂	「最讨厌你了啦……」
.message	350			是在哭还是在生气啊。
.message	360			还是一如既往麻烦的性格啊，景。
.message	370	kei-107_02-0017	丂宨丂	「总有一天吊死你……」
.message	380		丂峢丂	「…………」
.message	390			在，在哪作呢……。
.transition 0 * 40
.stage	* bgc_sch003a01_02.png 0 0 st_kei01a03.png 380
.message	400	kei-107_02-0019	丂宨丂	「够了。到底干吗，有什么话要说啊。不会什么话都没还玩刚才那样的羞耻PLAY吧！」
.message	410		丂峢丂	「我说你，ON/OFF太激烈了吧」
.message	420			刚才的也算不上什么羞耻PLAY吧我说。
.transition 0 * 40
.stage	* bgc_sch003a01_02.png 0 0 st_kei01a06.png 380
.message	430	kei-107_02-0021	丂宨丂	「不是前辈你按的开关吗！　又不是我的错！」
.message	440			而且还反过来发火。
.message	450			我叹了一口气，啪的把手放在了景的头上。
.transition 0 * 20
.stage	* bgc_sch003a01_02_stm.png 0 0 stm_kei05a04.png 400
;（表情とポ～ズ，注意のこと）
.message	460	kei-107_02-0023	丂宨丂	「所，所以说了这样的事情──」
.message	470		丂峢丂	「嘛，总之精神还是精神着的」
.transition 0 * 40
.stage	* bgc_sch003a01_02_stm.png 0 0 stm_kei06a05.png 400
;（02a03でも？）
;.stage	* bgc_sch003a01_02.png 0 0 st_kei05a07.png 400
;（表情とポ～ズ注意）
.message	480	kei-107_02-0025	丂宨丂	「不要一个人自己在那认同好吧」
.message	490		丂峢丂	「虽然精神着好……」
.message	500		丂峢丂	「但是有一句话让我说出来，你也稍微放松下吧」
.message	510			希望景她能生活的更为自然。
.message	520			嗯，像那家伙一样轻松着，浮起普通的笑颜──
.transition 0 * 40
.stage	* bgc_sch003a01_02_stm.png 0 0 stm_kei05a08.png 400
.message	530	kei-107_02-0027	丂宨丂	「……我看来就像那么顽固的人吗？」
.message	540		丂峢丂	「部分吧」
.message	550		丂峢丂	「特别是最近的你。不是自己也说了自己奇怪了吗」
.message	560		丂峢丂	「虽然你可能也发生了各种各样的事」
.transition 0 * 40
.stage	* bgc_sch003a01_02_stm.png 0 0 stm_kei05a03.png 400
.message	570	kei-107_02-0029	丂宨丂	「没有」
.message	580			清楚的丢出一句话。
.transition 0 * 40
.stage	* bgc_sch003a01_02_stm.png 0 0 stm_kei04a04.png 400
;（04a04の多用，注意）
.message	590	kei-107_02-0031	丂宨丂	「没有什么各种各样。我之所以会奇怪，原因只会有一个而已！」
.message	600		丂峢丂	「什么啊，那个原因」

;■御影チェック
.playBGM *

.transition 0 * 20
.stage	* bgc_sch003a01_02.png 0 0 st_kei02a03.png 380
;（表示タイミング注意。この後で？01a06も視野に）
.message	610			啪，景退后了一歩。
.message	620	kei-107_02-0033	丂宨丂	「你很烦诶，这点事情自己去──」

;■御影チェック
;.playBGM *
.playBGM efBGM013.ogg 0 *

.message	630	mid-107_02-0003	儈僘僉	「景前～辈～！」
.message	640			突然，从楼梯下面传来一声大大的喊声。
.message	650		丂峢丂	「诶」
.transition 0 * 40
.stage	* bgc_sch003a01_02.png 0 0 st_kei01a10.png 380
.message	660	kei-107_02-0035	丂宨丂	「瑞希，来了吗？」
.message	670			景用稍微有些惊讶的声音说道。
.transition 0 * 20
;.stage	* bgc_sch003a01_02.png 0 0 st_kei01a10.png 200 st_mizuki_a01a03.png 600

;■御影チェック
;.stage	* bgc_sch003a01_02.png 0 0 st_kei01a10.png 200 st_mizuki_a01a03.png:[0,0,0]or_mizuki02a.png 600
.stage	* bgc_sch003a01_02.png 0 0 st_kei01a10.png 200 st_mizuki_a01a03.png:[0,0,0]or_mizuki02a.png 615

;（景の01，02ポ～ズと瑞希を並ばせると，景の身長差に違和が出るんだな，，，並べる場合は01,02ポ～ズ以外のものを使って？）
.message	680	mid-107_02-0005	儈僘僉	「是是，你的瑞希，在此见参！」
.message	690			就像要摇出尾巴那样，羽山愉快的说着。
.message	700	mid-107_02-0007	儈僘僉	「景先辈怎么都不见出现，就来接你了哦！」
.transition 0 * 40
;.stage	* bgc_sch003a01_02.png 0 0 st_kei02a02.png 200 st_mizuki_a01a03.png 600

;■御影チェック
;.stage	* bgc_sch003a01_02.png 0 0 st_kei02a02.png 200 st_mizuki_a01a03.png:[0,0,0]or_mizuki02a.png 600
.stage	* bgc_sch003a01_02.png 0 0 st_kei02a02.png 200 st_mizuki_a01a03.png:[0,0,0]or_mizuki02a.png 615

;（景の表情，注意）
.message	710	kei-107_02-0037	丂宨丂	「是，是吗。抱歉呢」
.message	720			说起来，还有和附中篮球部的共同练习来着。
.transition 0 * 40
;.stage	* bgc_sch003a01_02.png 0 0 st_kei02a02.png 200 st_mizuki_a02a01.png 600
.stage	* bgc_sch003a01_02.png 0 0 st_kei02a02.png 200 st_mizuki_a02a01.png:[0,0,0]or_mizuki02a.png 600
.message	730	mid-107_02-0009	儈僘僉	「就是如此，去练习了啦。大家都已经到了哦～」
.transition 0 * 40
;.stage	* bgc_sch003a01_02.png 0 0 st_kei02a02.png 200 st_mizuki_a02a01.png 600
.stage	* bgc_sch003a01_02.png 0 0 st_kei02a02.png 200 st_mizuki_a02a01.png:[0,0,0]or_mizuki02a.png 600
.message	740		丂峢丂	「我说啊，羽山。我这边的话还没──」
.transition 0 * 40
;.stage	* bgc_sch003a01_02.png 0 0 st_kei02a03.png 200 st_mizuki_a03a03.png 600
.stage	* bgc_sch003a01_02.png 0 0 st_kei02a03.png 200 st_mizuki_a03a03.png:[0,0,0]or_mizuki02a.png 600
.message	750	mid-107_02-0011	儈僘僉	「你说什么了吗？」
.message	760			浮起对景完全相反的表情，羽山一副不高兴的样子说道。
.message	770		丂峢丂	「我还有点话要和景……」
.transition 0 * 40
;.stage	* bgc_sch003a01_02.png 0 0 st_kei02a03.png 200 st_mizuki_a03a06.png 600
.stage	* bgc_sch003a01_02.png 0 0 st_kei02a03.png 200 st_mizuki_a03a06.png:[0,0,0]or_mizuki02a.png 600
.message	780	mid-107_02-0013	儈僘僉	「不能随便和我的景前辈说话！」
.message	790		丂峢丂	「怎能如此」
.message	800	kei-107_02-0039	丂宨丂	「什么时候我成了瑞希的所有物了……」
.transition 0 * 40
;.stage	* bgc_sch003a01_02.png 0 0 st_kei02a03.png 200 st_mizuki_a03a02.png 600
.stage	* bgc_sch003a01_02.png 0 0 st_kei02a03.png 200 st_mizuki_a03a02.png:[0,0,0]or_mizuki02a.png 600
.message	810	mid-107_02-0015	儈僘僉	「那就这样了哦，纮前辈」
.message	820			无视我们两个的话，羽山拉起了景的手。
.transition 0 * 40
;.stage	* bgc_sch003a01_02.png 0 0 st_kei02a03.png 200 st_mizuki_a01a02.png 600
.stage	* bgc_sch003a01_02.png 0 0 st_kei02a03.png 200 st_mizuki_a01a02.png:[0,0,0]or_mizuki02a.png 600
.message	830	mid-107_02-0017	儈僘僉	「那就再见了哦～<音乐符号>」
.transition 0 * 40
;.stage	* bgc_sch003a01_02.png 0 0 st_kei01a11.png 200 st_mizuki_a01a03.png 600
.stage	* bgc_sch003a01_02.png 0 0 st_kei01a11.png 200 st_mizuki_a01a03.png:[0,0,0]or_mizuki02a.png 600
;（景の表情，注意のこと）
.message	840	kei-107_02-0041	丂宨丂	「……回见」
.message	850			带着复杂的表情，景轻轻的挥了下手。
.transition 0 * 20
.stage	* bgc_sch003a01_02.png 0 0
.message	860			然后她就那么被羽山拉着离开了。
.message	870		丂峢丂	「算什么啊」
.message	880			不由得嘟囔起来。
.message	890			羽山那白痴，也太不会挑时机了吧。
.message	900		丂峢丂	「……但是嘛，算了」
.message	910			也并不是没有精神，以后有时间再多问些吧。
.message	920			机会之类有一堆呢。
.panel 0
.overlay * *
.playBGM *
.transition 0 * 10
.stage	* WHITE.png 0 0

.chain 107_04.sc
;■107_04へ。

;.end
