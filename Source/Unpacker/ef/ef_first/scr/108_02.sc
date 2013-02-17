; ファイル: 108_02.txt
;■宫子好感度(≧2)
.transition 0 * 40
;.stage	* bgc_sch002a01_02.png 0 0 st_miyako01a01.png 400
.stage	* bgc_sch002a01_02.png 0 0 st_miyako01a01.png 350
.message	100	miy-108_02-0003	傒傗偙	「那个」
.message	110		丂峢丂	「啊？」
.transition 0 * 40
;.stage	* bgc_sch002a01_02.png 0 0 st_miyako01a02.png 400
.stage	* bgc_sch002a01_02.png 0 0 st_miyako01a02.png 350
;（ここ02で，上下01？）
.message	120	miy-108_02-0005	傒傗偙	「稍微想换下心情呢～。走吧」
.message	130		丂峢丂	「这次又是哪啊……」
.transition 0 * 40
;.stage	* bgc_sch002a01_02.png 0 0 st_miyako01a01.png 400
.stage	* bgc_sch002a01_02.png 0 0 st_miyako01a01.png 350
.message	140	miy-108_02-0007	傒傗偙	「好·地·方·哦」
.message	150			宫子说着，恶作剧似的笑了起来。
.panel 0
.overlay * *
.transition 0 * 10
.stage	* WHITE.png 0 0
;（白を挿む必要はない？）


;■背景：屋上（冬），１６時３０分→１７時（夕方）へ。
;■　　　　广野纮　　：制服（冬）
;■　　　　宫村宫子：制服（冬）
.screen sc_evening01.png sc_evening01.png
.transition 1 fadeSide.png 10
.stage	* bgw_sch007a01_02.png 0 0
;（昼から夕方，，，というような指定になってますが，夕から夕と，とりあえず暫定で移行しています）
.panel 1
.message	160		丂峢丂	「干吗啊，原来是屋顶吗」
.overlay * or_miyako02a.png
.transition 0 * 40
.stage	* bgw_sch007a01_02.png 0 0 st_miyako06a02.png 400
.message	170	miy-108_02-0009	傒傗偙	「不是很好的地方吗。至少我在这学园里面最喜欢这里」
.transition 0 * 40
.stage	* bgw_sch007a01_02.png 0 0 st_miyako06a01.png 400
.message	180	miy-108_02-0011	傒傗偙	「还是说，在期待什么其他的么？」
.message	190			眼睛朝上盯着我看。
.message	200		丂峢丂	「什么跟什么啊，其他的」
.transition 0 * 40
.stage	* bgw_sch007a01_02.png 0 0 st_miyako05a05.png 400
;（05a02でも？）
.message	210	miy-108_02-0013	傒傗偙	「唔～，一如既往的乖僻反应呢」
.transition 0 * 40
.stage	* bgw_sch007a01_02.png 0 0 st_miyako05a01.png 400
.message	220	miy-108_02-0015	傒傗偙	「但是啊，怎么办呢？」
.message	230		丂峢丂	「什么怎么办」
.message	240			老样子，宫子的话总是少半句。
.transition 0 * 40
.stage	* bgw_sch007a01_02.png 0 0 st_miyako05a02.png 400
.message	250	miy-108_02-0017	傒傗偙	「未来志愿啊。不是说了明天为止要交上去吗」
.message	260		丂峢丂	「唔～嗯」
.message	270			那种东西，总能作出来的……。
.message	280		丂峢丂	「嘛，适当的写点不就行了。学校那边看到升学之类的字眼不也就闭嘴了嘛」
.transition 0 * 40
.stage	* bgw_sch007a01_02.png 0 0 st_miyako06a01.png 400
;（表情注意）
.message	290	miy-108_02-0019	傒傗偙	「要升学么？」
.message	300			宫子露出稍稍有些意外的表情。
.message	310		丂峢丂	「所以说了是适当。也不是到明天就能决定的，而且这也并不就决定未来真的如何」
.message	320		丂峢丂	「你怎么办？」
.transition 0 * 40
.stage	* bgw_sch007a01_02.png 0 0 st_miyako06a04.png 400
;（表情注意）
.message	330	miy-108_02-0021	傒傗偙	「我是看不清楚明天的迷茫的年纪哟」
.message	340			把这家伙推下楼好了……。
.transition 0 * 40
;.stage	* bgw_sch007a01_02.png 0 0 st_miyako01a09.png 400
.stage	* bgw_sch007a01_02.png 0 0 st_miyako01a09.png 350
;（表情注意）
.message	350	miy-108_02-0023	傒傗偙	「哦，纮君变成修罗一样了！　夜叉一样了！」
.message	360		丂峢丂	「你是有不能老实回答问题的病吧你？」
.transition 0 * 40
.stage	* bgw_sch007a01_02.png 0 0 st_miyako02a04.png 350
;（表情注意。02a06も視野に）
.message	370	miy-108_02-0025	傒傗偙	「我呢，是得了不治之症的薄幸美少──」
.message	380			我带有怒气的向宫子走近。
.transition 0 * 40
.stage	* bgw_sch007a01_02.png 0 0 st_miyako00a04.png 350
;.stage	* bgw_sch007a01_02.png 0 0 st_miyako01a04.png 400
.message	390	miy-108_02-0027	傒傗偙	「因为还不清楚，就写未定然后提交上去好了」
.message	400			感受到了自己的危险，宫子慌忙说道。
.message	410			我总之先忍推她下去的冲动，轻轻叹了一口气。
.message	420		丂峢丂	「怎么可能会让你那么写。下次说不定就会请你家人来了吧？」
.transition 0 * 40
.stage	* bgw_sch007a01_02.png 0 0 st_miyako00a05.png 350
;.stage	* bgw_sch007a01_02.png 0 0 st_miyako01a05.png 400
.message	430	miy-108_02-0029	傒傗偙	「嗯～，我的家人就算被通知也不是会轻易就来的人呢」
.message	440		丂峢丂	「工作很忙吗。说起来是，双人工作？」
.transition 0 * 40
.stage	* bgw_sch007a01_02.png 0 0 st_miyako08a03.png 410
.message	450	miy-108_02-0031	傒傗偙	「不啊。我的家人离婚了啦。现在只有爸爸和我两个人而已。真让人流泪啊」
.message	460		丂峢丂	「干吗哭啊你！」
.message	470			完全不可理解。
.transition 0 * 40
.stage	* bgw_sch007a01_02.png 0 0 st_miyako08a01.png 410
;（表情注意）
.message	480	miy-108_02-0033	傒傗偙	「开个小笑话而已啦……」
.message	490		丂峢丂	「你说的是不是笑话我都不知道！」
.message	500			不过，离婚啊……。
.message	510			嘛──虽然也并不少见。
.message	520			宫子也并不在意的样子。
.message	530		丂峢丂	「父亲很忙吗？　到是，什么工作呢？」
.transition 0 * 40
.stage	* bgw_sch007a01_02.png 0 0 st_miyako08a02.png 410
.message	540	miy-108_02-0035	傒傗偙	「好象是在哪的建筑公司工作」
.message	550		丂峢丂	「哦～」
.message	560	miy-108_02-0037	傒傗偙	「好象很厉害的样子。虽然不是很清楚，不过在城市的复兴计划里好似参与不少，还担当了重任的样子呢」
.message	570		丂峢丂	「哦～」
.message	580			虽然没打算要听到那么私人的问题……。
.message	590			宫子对于复兴计划微妙的详细原来是因为父亲的原因吗。
.transition 0 * 40
.stage	* bgw_sch007a01_02.png 0 0 st_miyako07a01.png 410
;（表情注意）
.message	600	miy-108_02-0039	傒傗偙	「也不怎么回家，这段时间貌似也很忙，就算被通知估计也不会来的吧」
.transition 0 * 40
.stage	* bgw_sch007a01_02.png 0 0 st_miyako07a02.png 410
.message	610	miy-108_02-0041	傒傗偙	「比起纮君来感觉要不方便的多呢」
.message	620		丂峢丂	「少把我说成方便好用的男人啊你」
.transition 0 * 40
.stage	* bgw_sch007a01_02.png 0 0 st_miyako07a01.png 410
.message	630	miy-108_02-0043	傒傗偙	「不是──」
.transition 0 * 40
;.stage	* bgw_sch007a01_02.png 0 0 st_miyako00a04.png 350
;.stage	* bgw_sch007a01_02.png 0 0 st_miyako01a04.png 400
.stage	* bgw_sch007a01_02.png 0 0 st_miyako01a04.png 350
.message	640			宫子慌忙又把话咽了回去。
.message	650		丂峢丂	「……我说你，刚才想说『不是吗？』没错吧」
.transition 0 * 40
.stage	* bgw_sch007a01_02.png 0 0 st_miyako07a03.png 410
.message	660	miy-108_02-0045	傒傗偙	「诶嗯，有些不可思议呢，为什么不写『漫画家』上去呢？」
.message	670			这个明显的转移话题的说法方式。
.message	680			看起来刚才是说中了，不过算了。
.message	690		丂峢丂	「如果写了漫画家上去的话，那才会被通知家人来的吧」
.message	700		丂峢丂	「我虽然稍微有了些实绩，但像漫画这种看不到未来的工作，学校自然不会认同的」
.message	710			特别这音羽学园的基本是全员志愿升学。
.transition 0 * 40
.stage	* bgw_sch007a01_02.png 0 0 st_miyako08a02.png 410
;☆（ここからの宫子の表情構築，しっかりと）
.message	720	miy-108_02-0047	傒傗偙	「我到觉得没必要要让学校认同吧？」
.message	730		丂峢丂	「你那是空谈吧。实际上，我们都是被学校和家人管束着，只有自己的话什么都决定不了」
;（ここ，目閉じで？）
.message	740	miy-108_02-0049	傒傗偙	「唔～嗯……」
.message	750			宫子她好象稍微考虑了下什么然后张开了嘴唇。
.message	760	miy-108_02-0051	傒傗偙	「纮君和家人怎样呢？　以前听你说过有姐姐的」
.message	770		丂峢丂	「父亲是坚定的画家，认为漫画什么的只是低俗的玩物而已」
.message	780	miy-108_02-0053	傒傗偙	「那就是你一个人住的理由吗？」
.message	790			宫子浮起稍稍有些惊讶的表情。
.message	800		丂峢丂	「到不是只有这点理由，嘛说了毕业不想升学要继续画漫画之后，自然要再吵一次。麻烦死」
.message	810			倒不是讨厌父亲。
.message	820			反不如说，尊敬着有着画功的他。
.message	830			而且，正是儿提时代被父亲的画迷住，才能在编不出什么好剧本的情况下仍然想当漫画家。
.message	840			感谢都来不及，怎么可能会去恨他呢。
.message	850			虽然也明白没理的是我啊。
.message	860	miy-108_02-0055	傒傗偙	「还真是有着各种各样的问题呢」
.message	870		丂峢丂	「父亲他并不是为了让我成为漫画家而教我画画的。嘛，教育我的时间被白白浪费了的心情也并不是不理解」
.message	880	miy-108_02-0057	傒傗偙	「父亲那边，不明白纮君的心情吗？」
.message	890		丂峢丂	「如果明白的话我就不会一怒之下离开家了」
.message	900	miy-108_02-0059	傒傗偙	「但是纮君还真是割舍不了呢。现在还注意着父亲对自己的反应」
.message	910		丂峢丂	「……大概吧」
.transition 0 * 40
.stage	* bgw_sch007a01_02.png 0 0 st_miyako07a01.png 410
.message	920	miy-108_02-0061	傒傗偙	「哎呀，难得的口里如一呢～」
.message	930			宫子明快的口气，让我的心情稍稍有些放松下来。
.message	940			但是，这也不过只是一时而已……。
.transition 0 * 40
.stage	* bgw_sch007a01_02.png 0 0 st_miyako07a02.png 410
;（表情とポ～ズ，注意のこと）
.message	950	miy-108_02-0063	傒傗偙	「纮君真的是……把一切都背在自己身上呢」
.message	960			一阵风飒地吹拂而过。
.message	970			…………
.message	980			……


;■ここより夕景
;☆（ここから夕方背景に移行，，，ってのは可能なのかな，，，ちょっと保留）
.screen * *
.transition 0 * 20
.stage	* bgw_sky001a01_02.png 0 0
;.transition 0 * 20
;.stage	* ev01_101.png 0 0
.message	990			云彩缓缓的流动，天空也被夕阳染成了赤色。
.message	1000			到底在这种地方作什么呢我。
.message	1010			分明工作早已堆积如山，不得不作的事情也在眼前堆满了的。
.message	1020			但为何，我会想要呆在宫子身旁呢。
.message	1030			只要宫子在身边就会心情舒畅。
.message	1040			为什么。
;■景の立ち絵表示
.transition 0 * 20
;.transition 1 fadeSide.png 20
.stage	* ev01_102.png 0 0
;☆（インの仕方など，注意して）
.message	1050	kei-108_02-0003	丂宨丂	『哥哥』
.transition 0 * 20
;.transition 1 fadeSide.png 20
.stage	* ev01_101_mugai_a.png 0 0
.message	1060			那家伙的脸一瞬在我眼前一闪而过。
.message	1070			没错，我可能是背负的太多太多。
;☆（横に振り向く，，，なので，横顔アップ立ち絵で構築を）
.message	1080	miy-108_02-0065	傒傗偙	「那个」
.message	1090			宫子轻轻的声音，从身边传来。
.message	1100	miy-108_02-0067	傒傗偙	「我们去哪里吧」
.message	1110		丂峢丂	「这次又是哪啊……」
.message	1120	miy-108_02-0069	傒傗偙	「之前说过的继续啊」
.message	1130		丂峢丂	「之前说过的？」
.message	1140	miy-108_02-0071	傒傗偙	「说过的要代替赔自行车，由我出钱去哪玩的啊」
.message	1150		丂峢丂	「你还记得啊」
.message	1160			我这边倒是早忘光了。
.message	1170	miy-108_02-0073	傒傗偙	「零花钱有很多的，所以连自行车都走不到的远远的地方也可以去哦」
.message	1180			宫子唰的指向天空。
.transition 0 * 20
.stage	* ev01_101.png 0 0
.message	1190	miy-108_02-0075	傒傗偙	「哪里都好只要是远～远的地方。别的不多要求，只要没有会对我们指指点点的人在的地方，哪都可以呢～」
.message	1200		丂峢丂	「那里的风要比这里还要冷吧」
.message	1210	miy-108_02-0076		宫子轻轻的微笑起来。
.message	1220	miy-108_02-0077	傒傗偙	「我呢，知道一个好地方哦。这次真的是好地方哦。虽然很远很远，虽然那里也不是全部都是愉快的东西……」
.message	1230	miy-108_02-0079	傒傗偙	「但觉得绝对会很有趣。去到那里的话，纮君会有什么样的表情呢……啊，真的会很有趣呢」
.message	1240			一副高兴的过分的脸，到底在想像些什么呢……。
.message	1250			有些想知道，又有些不想知道。
.message	1260		丂峢丂	「啊～！」
.message	1270			我禁不住揪起了头。
.message	1280	miy-108_02-0081	傒傗偙	「怎，怎么了吗？」
.message	1290	miy-108_02-0083	傒傗偙	「坏掉了吗？　要不要去医院？」
.message	1300		丂峢丂	「少想象些有的没的。真是的，到底最近的我怎么了！」
.message	1310	miy-108_02-0085	傒傗偙	「你很奇怪呢，纮君」
.message	1320		丂峢丂	「又怎么了！」
.message	1330			宫子她带着平静的表情张开嘴唇。
.message	1340	miy-108_02-0087	傒傗偙	「因为，每天画着少女漫画，画完漫画又来学校，忍着一堆麻烦事勉强着自己，连逃避都作不到吗？」
.message	1350		丂峢丂	「…………」
.message	1360	miy-108_02-0089	傒傗偙	「啊啊，对了。逃避这点是最简单也是最难的呢。对啊，还有这种考虑在啊……」
.message	1370			在自问自答什么呢。
.transition 0 * 20
.stage	* ev01_103.png 0 0
;（このＣＧへの移行タイミング，注意のこと）
.message	1380			从陷入沉思的宫子身上移开目光，望向下方广阔的街景。
;■ここで宫子の立ち絵外す
.message	1390		丂峢丂	「虽然你说的没错。说到逃避我也想逃避，对于你所说的有趣的场所我也并非没有兴趣，只是」
.message	1400		丂峢丂	「世间有些事情是作不到的。人既然活着，就会自然的背负起各种各样的负担，不是轻易就放的下的啊」
.message	1410		丂峢丂	「一次扯上关系之后，却当作什么都没有发生就突然逃掉之类…不可能做的到」
.message	1420			学校，家人，朋友，笨蛋似的后辈以及正体不明的怪女人。
.message	1430			还有景。
.message	1440			而且还有──
.message	1450		丂峢丂	「！？」
.message	1460			在那一瞬间，我正想着宫子的脸为什么会突然出现的眼前──
.playBGM *

;■御影チェック
;■　最初は鳴らしちゃいけないと思うんだな。
;■　突然ですし，無音で頭がまっしろになってる感を。
;.playBGM efBGM022.ogg

;★イベントＣＧ
.panel 0
.transition 0 * 40
.stage	* ev01_104_wide.png 800 600
.scroll	0 300	40
.endScroll f
.transition 0 * 40
.stage	* ev01_104_wide.png 0 300
.scroll	400 0	10
.endScroll f

.transition 0 * 10
.stage	* ev01_104.png 0 0
;（フェ～ドスピ～ドは20で？800*600画像には，次で変えさせるか？）
.panel 1
.message	1470			而下一个瞬间嘴唇便已重叠在了一起。
;.message	1480		丂峢丂	「…………っ」
.message	1480		丂峢丂	「…………」
.message	1490	miy-108_02-0091	傒傗偙	「…………嗯」
.transition 0 * 10
.stage	* ev01_105.png 0 0
;（フェ～ドスピ～ドは20で？ここ，切り出しで？）
.message	1500			仅仅只有一瞬松开了嘴唇，但宫子马上又更激烈的吻了上来。
.message	1510			虽然有些碰到牙齿，但就算如此两口也没有分离开来。
.message	1520			不知何时抱住我的背的宫子的手也愈加紧而有力。
;.message	1520			いつの間にか俺の首筋に回されていた宫子の手に，ぐっと力がこもる。
.message	1530			宫子的嘴唇的柔软──已经让我什么都无法考虑。
.message	1540			到底吻了多久了呢。
;☆（ここか，この次あたりからev01_105を？）

;■御影チェック
;■　ここかな。
;■　いっそ，鳴らさないで押し切る手もあるよな……曲がちょい派手すぎなのかな。
;■　あ～，纮の漫画のシ～ンと同じシチュエ～ションだからこの曲にしてるんだな。
;■　どうしようかと思ったが，あまりにも難しすぎる伏線なので，場面にあうほうで。
;.playBGM efBGM022.ogg
.playBGM efBGM019.ogg

.message	1550			不知从哪边松开了嘴唇，而发烧般的宫子的脸近在眼前。
.message	1560		丂峢丂	「…………」
.message	1570	miy-108_02-0093	傒傗偙	「…………」
.message	1580			呜，气氛有些麻烦呢……。
.message	1590			虽然那过分的柔软很舒服没错，但为什么要这样做？
.message	1600	miy-108_02-0095	傒傗偙	「说，说点什么啊」
.message	1610		丂峢丂	「你才是──」
.message	1620	miy-108_02-0097	傒傗偙	「我？　我吗……」
.message	1630			宫子捂住嘴唇，忸忸怩怩的说。
.message	1640	miy-108_02-0099	傒傗偙	「在想着……这种情况下果然只有沉默才好啊」
.message	1650	miy-108_02-0101	傒傗偙	「因为做的时候不就沉默了吗」
.message	1660		丂峢丂	「啊……？」
.message	1670		丂峢丂	「啊啊，对啊」
.message	1680			之前宫子说过的，除了睡觉和吃饭以外不能说话的情况。
.message	1690			那在吻的时候自然是没办法的啊……。
.message	1700	miy-108_02-0103	傒傗偙	「那个，那个」
.message	1710	miy-108_02-0105	傒傗偙	「不知为何，突然就想做了呢。那个……」
.message	1720		丂峢丂	「突，突然想做的时候谁都行吗」
.message	1730			在这种时候还能说出惹人厌的话的性格不能改了嘛喂。
.message	1740			倒是，这个过分的该死的心跳速度想个办法啊我说。
.message	1750	miy-108_02-0107	傒傗偙	「我在想纮君呢，偶尔也需要重启动一下呢」
.message	1760		丂峢丂	「重启动？」
.message	1770	miy-108_02-0109	傒傗偙	「什么都不去想的时间，脑袋也不得不清空的时间」
.message	1780	miy-108_02-0111	傒傗偙	「……如何呢？」
.message	1790		丂峢丂	「谁知道啊，那种东西」
.message	1800			虽然想背过脸去，但对着红着脸的宫子却完全移不开眼睛。
.message	1810	miy-108_02-0113	傒傗偙	「但是，但是呢。我误算了一点呢」
.message	1820		丂峢丂	「……误算？」
.message	1830			虽然不是该说话的场合，但总之还是问了回去。
.message	1840	miy-108_02-0115	傒傗偙	「我这边的头才完全的空白掉了」
.message	1850		丂峢丂	「……你还真是狡猾啊」
.message	1860	miy-108_02-0117	傒傗偙	「诶？　怎，怎么？」
.message	1870			我并没回答，而是啪的抓住了宫子的手。
.message	1880			烦恼之类的都已经完全飞走了。
.message	1890			为什么你能作到这种事情啊。
.message	1900		丂峢丂	「宫子」
.message	1910	miy-108_02-0119	傒傗偙	「诶诶！？」
.message	1920			仅仅是喊了一下名字而已，宫子却震了一下身体附带过剩反应。
.message	1930	miy-108_02-0121	傒傗偙	「呃，纮君刚才的应该是初吻吧？」
.message	1940			宫子语无伦次的说着。
.message	1950		丂峢丂	「反正只是第一次啊，还真是抱歉呢」
.message	1960	miy-108_02-0123	傒傗偙	「啊哈哈，还真晚呢。不过虽然这样说我也是第一次呢」
.message	1970			宫子也握住了我的手。
.message	1980	miy-108_02-0125	傒傗偙	「不过，算那个是吧。虽然都是第一次却难以想象的长呢～。都经过了几分钟了呢。稍稍有些奇怪呢，我们」
.message	1990		丂峢丂	「……要更新记录看看吗？」
.message	2000			宫子的嘴唇就在那么近的眼前。
.message	2010			想要再尝试一个那个感触的冲动，已经到了无法抑制的地步。
.message	2020			不过，宫子却摇了摇头。
.message	2030			摇了数次。
.message	2040	miy-108_02-0127	傒傗偙	「那样的…不行。因为…我……」
.message	2050			她再没有说下去，只是一直的摇着头。
.message	2060			为什么，为什么。
.message	2070			而宫子她的眼睛，现在像就要流出眼泪一样的湿润着。
.panel 0
.overlay * *
.playBGM *
.transition 0 * 10
.stage	* WHITE.png 0 0
;（こういうところの切り替え，ちょっと変えて，イベントＣＧパネル無しを数秒表示させて，白に移行させる？）
.transition 0 * 10
.stage	* WHITE.png 0 0
.wait 100

.chain 109_01.sc
;■109_01へ。

;.end
