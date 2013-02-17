; ファイル: 205_01.txt
;■＜２章：５日目＞
;■背景：駅前广場（夏，１１時
;■　　　　堤京介：私服（夏）
;■　　　　新藤景：私服（夏）
.transition 0 * 10
.stage	* bgs_sky001a01_01.png 0 0
;.stage	* bgs_normal003m01_01.png 0 0
;☆（ここ，空からイン？）
.panel 1
.message	100			星期日的天空万里无云。
.message	110			毫不吝啬撒下的日光让我不由眯起了眼睛。
.message	120			虽然天气热的有些过分，但对于摄影来说却是绝好的天气倒也不错。
.transition 0 * 20
.stage	* bgs_normal003m01_01.png 0 0
.message	130			光线的感觉也很不错，这样看起来很拍出不错的画面呢。
.message	140	kei-205_01-0003	丂宨丂	「堤前辈」
.message	150		嫗丂夘	「哇」
.message	160			听到突然响起的低声回过头去看时。
.playBGM efBGM042.ogg
;（インのタイミング，注意して。さらにフェ～ドさせないでイン？）
.transition 0 * 20
.stage	* bgs_normal003m01_01.png 0 0 st_kei01e03.png 380
;（表情には注意して。「仏頂面」です）
.message	170		嫗丂夘	「哦哦～！」
.message	180	kei-205_01-0005	丂宨丂	「……干吗啊」
.message	190			新藤景分明是迟到，不知为何却一脸不高兴的瞪着我。
.message	200			但是今天新藤样子却新鲜到我可以完完全全的原谅这回事。
.transition 0 * 40
.stage	* bgs_normal003m01_01.png 0 0 st_kei04e04.png 400
;.stage	* bgs_normal003m01_01.png 0 0 st_kei02e01.png 380
;（表情には注意。変える必要はない？）
.message	210	kei-205_01-0007	丂宨丂	「想说什么吗？」
.message	220		嫗丂夘	「不不，只是第一次见到新藤你穿日常服的样子而已啦」
.message	230		嫗丂夘	「很棒，这个很配你。可爱的过分」


;■御影チェック
.set finderCounter = 0


.frame finder.png
.set finderCounter = 0
.transition 0 * 40
.stage	* bgs_normal003m01_01.png 0 0 st_kei04e04.png 400
;（↑実験的に，ここから配置。インはカットインの機能を使うと新鮮かもしれません）
.message	240			我一边架起摄像机，一边真心的称赞到。
;■呆れ
.transition 0 * 40
.stage	* bgs_normal003m01_01.png 0 0 st_kei05e08.png 400
;（ここ，04ポ～ズでも？）
.message	250	kei-205_01-0009	丂宨丂	「你还真能毫不掩饰的说出这种话啊……」
.message	260		嫗丂夘	「对于我来说，朴素直接就是信条」
.message	270		嫗丂夘	「哎呀～，说起来还真的很可爱啊。可爱到我想把这影片放到网络上全球发送」
.transition 0 * 40
.stage	* bgs_normal003m01_01.png 0 0 st_kei05e07.png 400
.message	280	kei-205_01-0011	丂宨丂	「要是真敢那么做，就三刀分掉再大火烧熟你」
.message	290			我成鱼了么。
.message	300			今天的毒舌也是格外出众啊。
.message	310			说起来。
.message	320		嫗丂夘	「新藤，你是不是心情不太好？」
.transition 0 * 40
.stage	* bgs_normal003m01_01.png 0 0 st_kei03e03.png 380
;（表情は注意して。もちっと眉を吊り上げてる表情を？）
.message	330	kei-205_01-0013	丂宨丂	「我心情不好会对前辈你造成不便么？」
.message	340		嫗丂夘	「哦，难道是女孩子的那一天么？」
.transition 0 * 40
.stage	* bgs_normal003m01_01.png 0 0 st_kei03e04.png 380
.message	350	kei-205_01-0015	丂宨丂	「那是能用清爽的表情说的话吗你这该死的！！」
.message	360		嫗丂夘	「哇！」
.message	370			勉强躲过她毫不留情打出的右直拳。
.transition 0 * 40
.stage	* bgs_normal003m01_01.png 0 0 st_kei01e06.png 380
.message	380	kei-205_01-0017	丂宨丂	「不要闪！」
.message	390		嫗丂夘	「抱歉抱歉，我错了我错了！」
.message	400			这反应还真是过剩啊……。
.message	410			难道说中了吗。
.transition 0 * 40
.stage	* bgs_normal003m01_01.png 0 0 st_kei05e07.png 400
.message	420	kei-205_01-0019	丂宨丂	「…………不懂细腻的男人我最讨厌」
.message	430		嫗丂夘	「我会深深铭记的……」
.message	440			还在摄影研究部的时候，包括女子部员在内这种不太有品的对话说起来完全无所谓的啊。
.message	450			而如果还跟那时一样跟新藤对话的话就真的要见血了啊。
;■呆れ
.transition 0 * 40
.stage	* bgs_normal003m01_01.png 0 0 st_kei04e03.png 400
;（表情とポ～ズは注意して）
.message	460	kei-205_01-0021	丂宨丂	「真是的，连星期天都陪着一起……我到底在干吗啊」
.message	470		嫗丂夘	「休息日穿日常服的样子定要纳入素材的啊」
.transition 0 * 40
.stage	* bgs_normal003m01_01.png 0 0 st_kei04e04.png 400
.message	480	kei-205_01-0023	丂宨丂	「这完全是仅仅按着前辈的想法的吧……」
.message	490		嫗丂夘	「但是，拍摄的素材啊，不到最后会使用多少完全不可预测啊……」
.message	500		嫗丂夘	「某种意义上，说不定是浪费时间呢。哈哈哈」
.transition 0 * 40
.stage	* bgs_normal003m01_01.png 0 0 st_kei01e06.png 380
;（顔赤らめさせていいか注意。ま，怒ると顔赤くなるが，赤くなってない怒り表情との使い分けには気を付けて）
.message	510	kei-205_01-0025	丂宨丂	「少笑啊你！」
.frame *
.panel 0
.playBGM *
.transition 0 * 10
.stage	* WHITE.png 0 0





;■背景：商店街，１１時３０分
.playBGM efBGM046_2.ogg

;■御影チェック
.set finderCounter = 317

.frame finder.png

;■御影チェック
;■　商店街，駅前のすぐそばだしなぁ。
;.set finderCounter = 1500
.set finderCounter = 317

;（カウンタ～をゼロにしてます。注意して）

.transition 1 fadeSide.png 10
.stage	st_kei10e01-.png 0 0 bg_scl005a01_01.png 0 0 bg_scl005a01_01.png 0
.effect	WScroll2 * 60 -2
;☆（ビデオフレ～ムはインで？）
;.transition 1 fadeSide.png 10
;.stage	* bgs_normal001m01_01.png 0 0
.panel 1
.message	520	kei-205_01-0027	丂宨丂	「今天怎么办法？」
.message	530			总之，我们走到了商店街。
.message	540			在这么炎热的天气，总不会有专门坐电车到远的地方的心情，这附近才算妥当吧。
.message	550		嫗丂夘	「我什么都不做啦。仅仅跟着新藤你而已」
.transition 0 * 40
.stage	st_kei10e05-.png 0 0 bg_scl005a01_01.png 0 0 bg_scl005a01_01.png 0
;（表情，注意して）
.message	560	kei-205_01-0029	丂宨丂	「也就是，随便我怎样都行是吧」
.transition 0 * 40
.stage	st_kei11e01-.png 0 0 bg_scl005a01_01.png 0 0 bg_scl005a01_01.png 0
.message	570	kei-205_01-0031	丂宨丂	「那么……去买些夏天用的东西好了」
.message	580		嫗丂夘	「那种东西不该是夏天前去买的吗？」
.transition 0 * 40
.stage	st_kei10e04-.png 0 0 bg_scl005a01_01.png 0 0 bg_scl005a01_01.png 0
.message	590	kei-205_01-0033	丂宨丂	「烦人啊你。不是随便我的吗」
.message	600		嫗丂夘	「说起来，你难道没有几件夏服吗？」
.message	610			又不是男生。
.transition 0 * 40
.stage	st_kei10e09-.png 0 0 bg_scl005a01_01.png 0 0 bg_scl005a01_01.png 0
.message	620	kei-205_01-0035	丂宨丂	「真是罗嗦啊你」
.message	630	kei-205_01-0037	丂宨丂	「到去年为止毎天都会练习然后浸透，日常服几乎都不能要了啊」
.message	640		嫗丂夘	「原来如此原来如此。那么，就让我为你选出可爱的衣服好了」
.transition 0 * 40
.stage	st_kei10e06-.png 0 0 bg_scl005a01_01.png 0 0 bg_scl005a01_01.png 0
.message	650	kei-205_01-0039	丂宨丂	「我的判断力还没有差到让男人来给我选衣服！」
.message	660			男女歧视大概就是这种东西吧。
.message	670			嘛，我也没晕到去给不是女朋友的女生买衣服，无所谓了。


;■御影チェック
;.effect *
.effect end


.frame *


;■白バック
;■御影チェック
.transition 1 fadeSide.png 20
;.transition 0 * 20
.stage	* WHITE.png 0 0
;（白バックではなくて，切り出しで？もしくはモブ対応？）
.message	680	kei-205_01-0041	丂宨丂	「我想你应该明白的吧，店内禁止摄像」
.message	690		嫗丂夘	「放进皮包内偷偷来如何？」
.message	700	kei-205_01-0043	丂宨丂	「你……」
.message	710			一瞬，被用看脏东西的眼神瞪了一眼。
.message	720	kei-205_01-0045	丂宨丂	「不是有过前科吧？」
.message	730		嫗丂夘	「怎，怎么可能……」
.message	740	kei-205_01-0047	丂宨丂	「干吗要把眼睛移开啊你！」
.message	750			哎呀，虽然偷拍是作过几次啦，但也全部是为了电影的伟大事业啊。
.message	760			因为我从没作过用仰角拍过女孩子──之类的事，良心应该毫无愧疚才对。
.message	770			……我是这么想的啦。
.message	780		嫗丂夘	「走啦走啦，站在人家店前会造成困扰的啦」
.message	790	kei-205_01-0049	丂宨丂	「少来，话还没说完呢──」



;■自動ドアの開閉音？
;■フェ～ドイン（白）
;★遠景ＣＧかな？


;■御影チェック
.playVoice *
.panel 0
.transition 1 fadeSide.png 20
;.transition 0 * 20


.stage	* ev02_042a01.png 0 0
.panel 1
;（フェ～ドの入り方，注意して。一工夫する？）
.message	800	kei-205_01-0051	丂宨丂	「嗯～……」
.message	810	kei-205_01-0053	丂宨丂	「总觉得不太对呢……」
.message	820	kei-205_01-0055	丂宨丂	「这个的颜色也有点……」
.message	830			新藤从刚才开始就拿着衣服一直在念叨个不停。
.message	840			虽然我觉得不可能，不是忘记我的存在了吧。
.message	850			回想起来，不能拍摄的话我跟着就毫无意义了啊……。
.transition 0 * 40
.stage	* ev02_042a02.png 0 0
.message	860	kei-205_01-0057	丂宨丂	「唔嗯……」
.message	870			看到认真烦恼到可怕程度的新藤，就算是店员也不敢跟她打招呼。
.message	880			衣服不多的人，买东西应该也会有些不习惯吧。
.message	890		嫗丂夘	「那个」
.message	900	kei-205_01-0059	丂宨丂	「唔～嗯……」
.message	910		嫗丂夘	「那个，新藤同学」
.transition 0 * 40
.stage	* ev02_042b01.png 0 0
;（フェ～ドのスピ～ド，注意して）
.message	920	kei-205_01-0061	丂宨丂	「干吗啊你？」
.message	930			真是,为什么偶尔会跟男人的口气似的。
.message	940		嫗丂夘	「容我说一句话……你应该穿什么都会合适的吧？　再怎么说身材也很不错」
.message	950	kei-205_01-0063	丂宨丂	「……飘来飘去，晃来晃去的衣服你也觉得合适？」

;■御影チェック
;.message	960		嫗丂夘	「…………」
.message	960		嫗丂夘	「……」

.message	970		嫗丂夘	「…………」
.message	980		嫗丂夘	「那算是对设计者的亵渎啊」
.transition 0 * 40
.stage	* ev02_042b02.png 0 0
.message	990	kei-205_01-0065	丂宨丂	「也不至于说到这份上吧！」
.message	1000		嫗丂夘	「啊，这个感觉比较适合你吧」
.transition 0 * 40
.stage	* ev02_042b03.png 0 0
.message	1010	kei-205_01-0067	丂宨丂	「……少转移话题啊你」
.message	1020			虽然这么说，新藤还是接过我递过去的那件中国风的衣服。
.message	1030			哦哦，虽然是被迫抓出的东西，但意外地满合适？
.transition 0 * 20
.stage	* ev02_043a01.png 0 0
.message	1040	kei-205_01-0069	丂宨丂	「真的吗？」
.message	1050		嫗丂夘	「诶？」
.message	1060	kei-205_01-0071	丂宨丂	「这个，真的觉得合适吗？」
.message	1070			新藤的表情上，有稍显哀怨的不安。
.message	1080			她实际上说不定是选衣服很慎重的类型啊。
.message	1090		嫗丂夘	「新藤也意外有着普通女孩子的一面啊……」
.transition 0 * 40
.stage	* ev02_043b01.png 0 0
.message	1100	kei-205_01-0073	丂宨丂	「意外是什么意思啊！」
.message	1110			对对，就得这样啊。
.message	1120		嫗丂夘	「来吧，新藤如果穿上这件中国服的话……」
.message	1130		嫗丂夘	「就可以向神秘的老人学会报家仇的拳法哦」
.message	1140	kei-205_01-0075	丂宨丂	「我是什么角色啊我！」
.message	1150		嫗丂夘	「顺便我也不拍记录片了，改拍动作功夫片好了」
.transition 0 * 40
.stage	* ev02_043b02.png 0 0
.message	1160	kei-205_01-0077	丂宨丂	「顺便个什么啊你！」
.message	1170		嫗丂夘	「嗯嗯，说笑而已啦」
.message	1180		嫗丂夘	「认真的说，真的很适合你。嗯，可爱可爱。感觉这件衣服就为了让新藤你穿而设计的啊」
.transition 0 * 40
.stage	* ev02_043b03.png 0 0
.message	1190	kei-205_01-0079	丂宨丂	「虽然还是极其可疑……嘛算了」
.message	1200			对我这个从没有骗过女孩的绅士说这种话，还真是让人伤怀啊。
;■再び遠景か？　でも景を書き換えなきゃだし微妙。
.transition 0 * 20
.stage	* ev02_043a02.png 0 0
;（フェ～ドスピ～ドに注意して。ここは20で？）
.message	1210	kei-205_01-0081	丂宨丂	「真的很合适是吧……」
.message	1220		嫗丂夘	「也不用那么怀疑吧」
.message	1230	kei-205_01-0083	丂宨丂	「不，不是那回事」
.message	1240	kei-205_01-0085	丂宨丂	「看着镜子我才这么想」
.message	1250		嫗丂夘	「哈？　什么？」
.message	1260	kei-205_01-0087	丂宨丂	「这个，如果对我合适的话……对千寻来说是否合适」
.message	1270		嫗丂夘	「千寻？」
.transition 0 * 40
.stage	* ev02_043a03.png 0 0
.message	1280	kei-205_01-0089	丂宨丂	「嗯，一定和她很合适」
.message	1290			新藤没有听我说的话，而只是认真注视着镜子中的自己。
.panel 0
.playBGM *
.transition 0 * 10
.stage	* WHITE.png 0 0


;■背景：喫茶店（夏，１２時
.playBGM efBGM051.ogg
;.playBGM BGM054_sample.ogg
.transition 1 fadeSide.png 10
.stage	* ev02_044a01.png 0 0
;（スクロ～ルさせても？喫茶店の通常背景挿む？）
.panel 1
.message	1300		嫗丂夘	「新藤，真的这样就可以么？」
.message	1310			新藤买的只有我选的那一件，而且看起来还不是为自己买的。
.message	1320	kei-205_01-0091	丂宨丂	「当然啊，我也没买多几件衣服的钱啊」
.message	1330		嫗丂夘	「但是，你自己的呢？」
.message	1340	kei-205_01-0093	丂宨丂	「我无所谓的啊」
.transition 0 * 40
.stage	* ev02_044b01.png 0 0
;（フェ～ドスビ～ドには注意して）
.message	1350	kei-205_01-0095	丂宨丂	「回想起来，打扮得漂漂亮亮对我来说也毫无必要」
.message	1360			新藤难得稳重地说了一句，然后一口喝完了冰咖啡。
.message	1370			我们为了稍微吃些午餐而来了这家咖啡店。
.message	1380			已经吃过了主食，现在是饭后的用茶时间。
.message	1390		嫗丂夘	「新藤你没去打过工吗？」
.transition 0 * 40
.stage	* ev02_044c01.png 0 0
;（ここのフェ～ドスピ～ドは20で？）
.message	1400	kei-205_01-0097	丂宨丂	「以前在家庭餐馆稍微作了一些女服务生的工作……」
.message	1410			然后就垂了下头，再也不多说一句。
.message	1420			对于容易生气的她来说，会发生什么大体也猜的到啊……。
.message	1430		嫗丂夘	「是啊，新藤如果打工的话……」
.message	1440		嫗丂夘	「应该是保镖或者赌场的司赌之类吧」
.transition 0 * 40
.stage	* ev02_044d01.png 0 0
.message	1450	kei-205_01-0099	丂宨丂	「为什么是这类啊！」
.message	1460		嫗丂夘	「粗暴的人很多很辛苦吧？」
.message	1470	kei-205_01-0101	丂宨丂	「说了没作过！」
.message	1480		嫗丂夘	「到现在为止杀了多少人了？」
.transition 0 * 40
.stage	* ev02_044d02.png 0 0
.message	1490	kei-205_01-0103	丂宨丂	「就在现在，决定了你就是第一个……」
.message	1500		嫗丂夘	「虽然万分光荣，但恕我放弃」
.message	1510			一次次正直的作出反映还真是有趣啊，这个女孩子。
.transition 0 * 40
.stage	* ev02_044a01.png 0 0
;（044a01に戻してよいか？フェ～ドスピ～ドも20で？）
.message	1520	kei-205_01-0105	丂宨丂	「前辈」
.message	1530		嫗丂夘	「嗯？」
.message	1540			啊，已经回复正常Mode了啊。
.transition 0 * 40
.stage	* ev02_044a02.png 0 0
.message	1550	kei-205_01-0107	丂宨丂	「……只是对别人问过来问过去，堤前辈你怎么样呢？」
.message	1560		嫗丂夘	「我？」
.message	1570			我抱起手腕，开始寻找过去的记忆。
.message	1580		嫗丂夘	「嗯～，说实在的应该算是几乎没有参加过什么正常的打工吧……」
.message	1590		嫗丂夘	「而且烦死人的老爸会说“如果真的有空就来给我帮忙”」
.message	1600	kei-205_01-0109	丂宨丂	「前辈的父亲是？」
.message	1610		嫗丂夘	「用他本人宣扬的话说，算是自由记者吧」
.message	1620		嫗丂夘	「是个会为了新闻取材跑到战场或者毫无国交的国家去的大白痴」
.message	1630		嫗丂夘	「在现在这个瞬间……究竟是在家里睡觉，还是在子弹下面寻找拍照机会完全不知道」
.transition 0 * 40
.stage	* ev02_044a03.png 0 0
.message	1640	kei-205_01-0111	丂宨丂	「好，好厉害的父亲呢……」
.message	1650			我多心吗，好似连看我的眼神也改变了似的。
.message	1660		嫗丂夘	「不过，在那么厉害的老爸身边，却能够培育出我这样正直的性格，我也够强的啊」
.transition 0 * 40
.stage	* ev02_044a04.png 0 0
.message	1670	kei-205_01-0113	丂宨丂	「堤前辈正直认真？　混乱不清地说出这种话，还真是厚颜无耻啊」
.message	1680			新藤同学，真严厉啊。
.message	1690			而正是由于我储备把这份严厉转化为快感的M能力才能轻松的交往下去啊。
;■上目遣い
.transition 0 * 40
.stage	* ev02_044a05.png 0 0
.message	1700	kei-205_01-0115	丂宨丂	「说起来，前辈你……」
.message	1710		嫗丂夘	「嗯？」
.transition 0 * 40
.stage	* ev02_044a06.png 0 0
.message	1720	kei-205_01-0117	丂宨丂	「不，没什么」
.message	1730			新藤略显抱歉的抱歉的表情，让我顿时明白了。
;（ここで，景の視線，京介に？）
.message	1740		嫗丂夘	「啊啊，我的老妈吗？」
.message	1750		嫗丂夘	「死了啊，我还是小孩子的时候」
;.message	1750		嫗丂夘	「死んだよ，俺がまだ赤ん坊の頃に」
;☆（「俺が赤ん坊の頃に」，，，ちょっと注意して。伏線なのかもしらんが）
.message	1760	kei-205_01-0119	丂宨丂	「是吗……」
.message	1770			新藤脸上的阴云又加厚了几分。
.message	1780	kei-205_01-0121	丂宨丂	「和哥──广野前辈一样呢……」
.message	1790		嫗丂夘	「啊啊，我和广野难得的几个共通点之一呢」
.message	1800			不过，对于对方的母亲，自然从没提过。
.message	1810			我们都已经接受了没有母亲的事实。
.message	1820			家人总有一天会离开。
.message	1830			会死去。
.message	1840			我和广野都十分清楚的明白这点。
.panel 0
.playBGM *
.transition 0 * 10
.stage	* WHITE.png 0 0




;■駅前广場（夏，１４時
;■　　　　堤京介　　：私服（夏）
;■　　　　新藤景　　：私服（夏）
;■　　　　羽山瑞希：私服（夏）

;■御影チェック
;■　カメラを構えたところで鳴らすか？
;.playBGM efBGM027.ogg


;.frame finder.png
;.set finderCounter = 0
;（カウンタ～をゼロにしてます。注意して）

.transition 1 fadeSide.png 10
.stage	st_kei11e01-.png 0 0 bg_scl005a01_01.png 0 0 bg_scl005a01_01.png 0
.effect	WScroll2 * 60 -2
;☆（ビデオフレ～ムはインで？）


;.transition 1 fadeSide.png 10
;.stage	* bgs_normal003m01_01.png 0 0
;（ここは空でインしてもいいかもしれません。つ～かＣＧでは「駅前广場」ではなく「商店街」の指定になってんな，，，）
.panel 1
.message	1850			走出咖啡店，我们再次抬起脚步。
.message	1860		嫗丂夘	「那个，新藤」
.transition 0 * 40
.stage	st_kei10e01-.png 0 0 bg_scl005a01_01.png 0 0 bg_scl005a01_01.png 0
.message	1870			我向一如既往不高兴的表情的新藤搭话。
.message	1880			她在这么炎热的天气里，走来走去也不怎么累的样子。
.message	1890			不愧是原篮球部的TOP。
.message	1900			现在还仍有体力啊。
.message	1910		嫗丂夘	「千寻是谁……我能问吗？」
;■無表情
.transition 0 * 40
.stage	st_kei10e05-.png 0 0 bg_scl005a01_01.png 0 0 bg_scl005a01_01.png 0
;（「無表情」，，，なんで表情は変えんでもいいのかな，，，）
.message	1920	kei-205_01-0123	丂宨丂	「……打开摄像机」
.message	1930		嫗丂夘	「嗯？」
.message	1940	kei-205_01-0125	丂宨丂	「别忘了，我仅仅是配合你拍电影而已」
.message	1950	kei-205_01-0127	丂宨丂	「从我个人而言一般是决不会跟堤前辈说起的」
.message	1960		嫗丂夘	「了～解」
.transition 0 * 40
.stage	st_kei11e01-.png 0 0 bg_scl005a01_01.png 0 0 bg_scl005a01_01.png 0
.message	1970			不愧是是广野的青梅竹马。
.message	1980			在微妙的地方摆出乖僻的脾气啊。



;■御影チェック
.set finderCounter = 0

.frame finder.png
.set finderCounter = 0
.transition 0 * 40
.stage	st_kei11e01-.png 0 0 bg_scl005a01_01.png 0 0 bg_scl005a01_01.png 0

;■御影チェック
;■　カメラを構えたところで鳴らすか？
.playBGM efBGM027.ogg

.message	1990			我把摄像机对向新藤。
.message	2000		嫗丂夘	「那么从头再来」
.message	2010			『千寻』这个人对于新藤来说不是一个小的存在，我朦胧感觉的到。
.message	2020			所以，我才会想要去了解『千寻』的事情。
.message	2030			即便她提起『千寻』的会有些踌躇。
.message	2040		嫗丂夘	「千寻是谁？」
.message	2050	kei-205_01-0128		新藤轻轻吸进一口气。
;■真剣
.transition 0 * 40
.stage	st_kei10e05-.png 0 0 bg_scl005a01_01.png 0 0 bg_scl005a01_01.png 0
.message	2060	kei-205_01-0129	丂宨丂	「我和千寻……」
.message	2070	kei-205_01-0131	丂宨丂	「我们一直都在一起。从生下来的时候」
.message	2080		嫗丂夘	「从生下来的时候……？」
.message	2090		嫗丂夘	「难道说是双胞胎？」
.message	2100			新藤点点头，继续说下去。
;■微笑
.transition 0 * 40
.stage	st_kei10e02-.png 0 0 bg_scl005a01_01.png 0 0 bg_scl005a01_01.png 0
.message	2110	kei-205_01-0133	丂宨丂	「也就是所谓的同卵双生。总之，虽然我是姐姐，但样子和体形几乎都没有什么差别」
.message	2120	kei-205_01-0135	丂宨丂	「只是，只有性格……算是正相反吧」
.message	2130		嫗丂夘	「妹妹有那么稳重吗？」
.transition 0 * 40
.stage	st_kei10e09-.png 0 0 bg_scl005a01_01.png 0 0 bg_scl005a01_01.png 0
.message	2140	kei-205_01-0137	丂宨丂	「少管！」
.message	2150			分明是你自己说正相反的……。
.transition 0 * 40
.stage	st_kei10e04-.png 0 0 bg_scl005a01_01.png 0 0 bg_scl005a01_01.png 0
.message	2160	kei-205_01-0139	丂宨丂	「我是认真地在跟你说，不要随便添些没用的话头好吧」


;■御影チェック
;.effect *
.effect end

.transition 0 * 20
.stage	* bgs_sky001a01_01.png 0 0
.message	2170			生气的丢下一句后，新藤抬头望向天空。
;☆（ここで，カメラを空に向けさせんのか？）
.message	2180			我也把镜头转向她视线透过的远方。
.message	2190			在那儿的是澄清如碧,青蓝宽广的夏空。
.message	2200			新藤到底在想些什么呢。
.transition 0 * 20
.stage	st_kei11e04-.png 0 0 bg_scl005a01_01.png 0 0 bg_scl005a01_01.png 0
.effect	WScroll2 * 60 -2
;（表情，注意して）
.message	2210	kei-205_01-0141	丂宨丂	「但是，千寻现在却不在我的身边」
.message	2220	kei-205_01-0143	丂宨丂	「如果她在的话……一定会有些不同的吧，不过…」
.message	2230			双胞胎姐妹分开居住了吗。
.message	2240		嫗丂夘	「为什么不在一起？」
.transition 0 * 40
.stage	st_kei10e05-.png 0 0 bg_scl005a01_01.png 0 0 bg_scl005a01_01.png 0
.message	2250	kei-205_01-0145	丂宨丂	「我的事情倒无所谓，千寻的事情不可能擅自就说的吧」
.message	2260		嫗丂夘	「唔～，那到也是」
.message	2270			新藤姐妹之间一定发生过些什么。
.message	2280			虽然很是介意，但追问下去也毫无意义的吧。
.message	2290		嫗丂夘	「但是，新藤你不寂寞吗？」
;■悲しみ
.transition 0 * 40
.stage	st_kei11e04-.png 0 0 bg_scl005a01_01.png 0 0 bg_scl005a01_01.png 0
.message	2300	kei-205_01-0147	丂宨丂	「不要问那种一目了然的问题」


;.message	2310	kei-205_01-0149	丂宨丂	「たぶん，千寻も寂しがってる。プレゼントなんかで，あの子の寂しさは埋められないし……もちろんわたしも」
.message	2310	kei-205_01-0148	丂宨丂	「大概，千寻也很寂寞吧……。就算有礼物，也不会抚平她寂寞的心」
.message	2315	kei-205_01-0150	丂宨丂	「……当然我也一样」


.transition 0 * 40
.stage	st_kei11e01-.png 0 0 bg_scl005a01_01.png 0 0 bg_scl005a01_01.png 0
.message	2320	kei-205_01-0151	丂宨丂	「不过，这是没有办法的事情呢」
.message	2330	kei-205_01-0153	丂宨丂	「就算是双胞胎，我们两个也终究不是一个人。总有一天不得不分离」
;.transition 0 * 40
;.stage	st_kei11e01-.png 0 0 bg_scl005a01_01.png 0 0 bg_scl005a01_01.png 0
;（ここらへんの表情変化，要注意して）
.message	2340	kei-205_01-0155	丂宨丂	「千寻是千寻，我是我」
.message	2350	kei-205_01-0157	丂宨丂	「因为不用自己的脚走下去是不行的啊……」
.transition 0 * 40
.stage	st_kei11e02-.png 0 0 bg_scl005a01_01.png 0 0 bg_scl005a01_01.png 0
.message	2360	kei-205_01-0159	丂宨丂	「就算这双脚溃烂断掉也是如此」
.message	2370	kei-205_01-0160		然后，新藤露出一个微弱的笑容。
.message	2380			看到那个不合年龄，貌似大彻大悟的笑容──不知为何我不安起来。
.message	2390			分明新藤的笑容是那么难得的。
;☆（ここの演出，注意して）
.message	2400			我就那样举着镜头，一动不动。
.message	2410			不，如果不通过镜头的话说不定就不可能看到的吧。

;■御影チェック
;■　こうしてみてはどうかと。
;.message	2420			それくらい，今の新藤は痛々しくて……。
;.playBGM *
;.message	2430	mid-205_01-0003	@儈僘僉	「景せんぱ～いっ！！」
.message	2420	mid-205_01-0003		这隐晦的，新藤现在流露出的伤痛……。
.playBGM *
;.message	2430	mid-205_01-0003	@儈僘僉	「景せんぱ～いっ！！」


;■御影チェック
;.effect *
.effect end




.frame *
.transition 1 fadeSide.png 20

;■御影チェック
;■　なんで駅前なんだ？
;.stage	* bgs_normal003m01_01.png 0 0
.stage	* bgs_normal001m01_01.png 0 0


.message	2440	kei-205_01-0161	丂宨丂	「诶？」
;.effect *
;.frame *
;.transition 1 fadeSide.png 20
;.stage	* bgs_normal003m01_01.png 0 0
.message	2450		嫗丂夘	「哈？」
.message	2460			随着那几乎要刺破耳膜的大声跑过来的，是一个女孩子。
.message	2470	kei-205_01-0163	丂宨丂	「啊啦，瑞希」
.playBGM *
.playBGM efBGM040.ogg
.transition 0 * 20
.stage	* ev02_045a01.png 400 0
;.stage	* ev02_045_dammy.png 0 0
;（インのタイミング，注意して。さらにフェ～ドさせないでイン？）
.message	2480	mid-205_01-0005	儈僘僉	「嗯！」
.message	2490			那个叫做瑞希的女孩，高兴的点着头。
.message	2500	kei-205_01-0165	丂宨丂	「你也来买东西吗？」
.transition 0 * 40
.stage	* ev02_045b01.png 400 0
.message	2510	mid-205_01-0007	儈僘僉	「嗯嗯，惯例要买的东西」

;■御影チェック
;.message	2520			女の子は書店のマ～クが入った手提げ袋を差し出してみせた。
.message	2520			那女孩拿出一个近处书店的手提袋。

.message	2530			虽然不太清楚是什么，但据这女孩子的外表推测肯定不会是参考书之类吧。
.transition 0 * 40
.stage	* ev02_045a02.png 400 0
.message	2540	mid-205_01-0009	儈僘僉	「说起来，景前辈」
.message	2550	kei-205_01-0167	丂宨丂	「嗯？」
.transition 0 * 40
.stage	* ev02_045c01.png 400 0
.message	2560	mid-205_01-0011	儈僘僉	「这个举着摄影机的可疑人物是谁？」
.message	2570			小姐，请您不要随便指人好吧。
.transition 0 * 40
.stage	* ev02_045c02.png 400 0
.message	2580	kei-205_01-0169	丂宨丂	「啊啊，这东西吗？」
.message	2590			新藤的说话方式更加过分。
.message	2600		嫗丂夘	「我说，你们啊……」
.message	2610			无视打算引起注意的我，新藤便开始说明事情的大体经过。
.message	2620			总觉得，有些奇怪的状况啊。
.message	2630			……………………
.message	2640			…………
.message	2650			……
.transition 0 * 20
.stage	* ev02_045a03.png 400 0
.message	2660	mid-205_01-0013	儈僘僉	「哈，景前辈的电影……」
.message	2670			这个女孩子，全名叫作羽山瑞希，看起来好象是附中的三年级的样子。
.message	2680	kei-205_01-0171	丂宨丂	「嘛，就是这么回事。我也觉得很白痴」
.message	2690	mid-205_01-0015	儈僘僉	「不，说起来」
.transition 0 * 40
.stage	* ev02_045c03.png 400 0
.message	2700			唰，羽山瑞希把头转向了我。
.message	2710		嫗丂夘	「？」
.message	2720	mid-205_01-0017	儈僘僉	「那么，那个摄像机中便收录了景前辈的美妙身姿……？」
.message	2730		嫗丂夘	「啊啊，那是自然」
.transition 0 * 40
.stage	* ev02_045d01.png 400 0
.message	2740	mid-205_01-0019	儈僘僉	「怎，怎么可以……！」
.message	2750			羽山一副受到打击的表情，后退了一步。
.message	2760			但马上又恢复了状态，把充满好奇心的眼瞳对向了我。
.transition 0 * 40
.stage	* ev02_045e01.png 400 0
.message	2770	mid-205_01-0021	儈僘僉	「怎，怎么卖？」
.message	2780	kei-205_01-0173	丂宨丂	「不要突然就给我买！」


;■御影チェック
;.message	2790			既に財布を取り出そうとしてた羽山を，新藤が叱りつける。
.message	2790			已经取出钱包的羽山被新藤给骂了回去。


.message	2800		嫗丂夘	「虽然底片不能给你，但副本还可以商量」
.transition 0 * 40
.stage	* ev02_045f01.png 400 0
.message	2810	kei-205_01-0175	丂宨丂	「你商量什么啊你！」
.message	2820			说笑而已。
.transition 0 * 40
.stage	* ev02_045g01.png 400 0
.message	2830		嫗丂夘	「没事啦，约定我会认真遵守的」
.message	2840			拍摄的胶卷，没有新藤的许可丝毫不会给别人看。
.message	2850	kei-205_01-0177	丂宨丂	「堤前辈对我来说，信任不能」
.transition 0 * 40
.stage	* ev02_045e02.png 400 0
.message	2860	mid-205_01-0023	儈僘僉	「诶诶。呜，不卖的吗」
.message	2870	kei-205_01-0179	丂宨丂	「不是当然的吗！」
.message	2880	mid-205_01-0025	儈僘僉	「诶～～，景前辈的可爱电影……好想要的……」
.message	2890			根据这个情况看来，羽山是十分喜欢新藤的样子。

;■御影チェック
;.transition 0 * 40
;.stage	* ev02_045a04.png 400 0

.message	2900	kei-205_01-0181	丂宨丂	「真是的，你少想些笨蛋事情吧」

;■御影チェック
.transition 0 * 40
.stage	* ev02_045a04.png 400 0

.message	2910	mid-205_01-0027	儈僘僉	「诶～，但是～」
.message	2920	kei-205_01-0183	丂宨丂	「但是，也禁止」
.message	2930			虽然嘴上这么说着，但今天的新藤确实有着几分温柔。
.message	2940			并不只有我，连学园的朋友们都没有看过的温柔的表情……。
.transition 0 * 40
.stage	* ev02_045h01.png 400 0
.message	2950	kei-205_01-0185	丂宨丂	「堤前辈」
.message	2960		嫗丂夘	「诶，啊啊」
.message	2970	kei-205_01-0187	丂宨丂	「今天的摄影就到此结束好了。我来决定也可以的吧？」
.message	2980		嫗丂夘	「啊，也好。今天也拍的足够了……」
.transition 0 * 40
.stage	* ev02_045h03.png 400 0
;.transition 0 * 40
;.stage	* ev02_045h02.png 400 0
;（景の視線が瑞希にいってない気もするが，，，）
.message	2990	kei-205_01-0189	丂宨丂	「那么，瑞希。你有时间吗？」
.message	3000	mid-205_01-0029	儈僘僉	「当然绝对一定有！」
;■笑顔
;.transition 0 * 40
;.stage	* ev02_045h03.png 400 0
.message	3010	kei-205_01-0191	丂宨丂	「难得一次，一起去玩吧。和你平常也很难见面呢」
.message	3020	mid-205_01-0031	儈僘僉	「是～，我也有好多话想要和景前辈说哦！」
.transition 0 * 40
.stage	* ev02_045h04.png 400 0
;（h04もリスト表情とはちと違うけど，ここはこれでいいのかな）
.message	3030	mid-205_01-0033	儈僘僉	「……但是请稍等一下」
.transition 0 * 20
.stage	* ev02_045i01_mugai_a.png 0 0
.message	3040			羽山瑞希对我浮起煞是阴险的表情，跟对新藤时形成鲜明对照。
.message	3050			眼神上下环视着盯了过来。
.message	3060		嫗丂夘	「干，干吗？」
.message	3070			羽山瑞希半开着眼睛盯着我，把脸凑了过来。
;■ジト目
.transition 0 * 20
.stage	* ev02_045i01.png 400 0
.message	3080	mid-205_01-0035	儈僘僉	「……不要对我的景前辈作什么可疑的事哦」
.message	3090			看起来不像是玩笑。
.message	3100		嫗丂夘	「是不是你的东西先暂且不论……」
.message	3110		嫗丂夘	「但请放心。我可是决不对“演员”出手的人」
.message	3120			和演员有异样的亲近的话，对于摄影也可能造成影响──这是我的考虑方式。
.message	3130			虽然这次的电影比较特别，但我也没想要去改变这个想法。
.message	3140	mid-205_01-0037	儈僘僉	「那我相信你好了」
.message	3150		嫗丂夘	「请相信我」
.message	3160	kei-205_01-0193	丂宨丂	「瑞希，说什么呢？」
.transition 0 * 40
.stage	* ev02_045j01.png 400 0
.message	3170	mid-205_01-0039	儈僘僉	「不不，没什么」
.hscroll	0	-10
.endScroll f
.message	3180			带着一个明朗的笑容说完，羽山再次转向新藤。
.message	3190	mid-205_01-0041	儈僘僉	「走吧，景前辈」
.transition 0 * 20
.stage	* ev02_045j01_mugai_a.png 0 0
.message	3200		嫗丂夘	「啊，新藤。稍等一下」
.transition 0 * 20
.stage	* ev02_045j01_mugai_b.png 0 0
.message	3210	kei-205_01-0195	丂宨丂	「诶？」


;■御影チェック
.set finderCounter = 0

.frame finder.png
.set finderCounter = 0
.transition 0 * 20
.stage	* bgs_normal001m01_01_stm.png 0 0 stm_kei04e06.png 300
.message	3220			我迅速的架起摄像机，捕捉到转过头来的新藤。
.transition 0 * 40
.stage	* bgs_normal001m01_01_stm.png 0 0 stm_kei01e01.png 300
;★（この表情はよくよく注意。すまん，時間なくて後回し）
.message	3230	kei-205_01-0197	丂宨丂	「……干吗啊？」
.message	3240		嫗丂夘	「现在的你有着很好的表情」
;■照れ
.transition 0 * 40
.stage	* bgs_normal001m01_01_stm.png 0 0 stm_kei02e03.png 300
.message	3250	kei-205_01-0199	丂宨丂	「说，说什么呢？」
.message	3260		嫗丂夘	「你，并不是一个人的意思」
;■軽い怒り
.transition 0 * 40
.stage	* bgs_normal001m01_01_stm.png 0 0 stm_kei01e09.png 300
.message	3270	kei-205_01-0201	丂宨丂	「……我明白」
.message	3280			我向新藤一笑之后，她便哼了一下转头走开了。
;■ワイプか何か。
.playBGM *
.frame *



.transition 0 * 20
.stage	* ev02_046.png 0 0
;（インのタイミング，注意して）
.message	3290			没有把镜头对向离开的两名少女的心情。
.message	3300			不知为何，觉得被扔下的自己──跟个白痴一样。
.message	3310			羽山瑞希吗。
.message	3320			虽然像是比较可爱，还很有趣的女孩子……。
.message	3330			但那种吵吵嚷嚷的类型不在我的审查范围内。
.playSE kyo_keitai_vib.ogg true 0 *
.message	3340			呜呜呜呜呜…呜呜呜呜呜……。
.message	3350		嫗丂夘	「嗯？」
.transition 0 * 20
.stage	* ev02_047.png 0 0
;（表示タイミング，注意して）
.message	3360			取出口袋中的手机，看向来电显示。
;（切り出しを？）
.message	3370		嫗丂夘	「还真是挑了个不错的时间打电话啊，那家伙」
.panel 0
.playSE *
;.playBGM *
.transition 0 * 10
.stage	* WHITE.png 0 0


;■公園（夏，１５時
;■　　　　堤京介　　：私服（夏）
;■　　　　宫村宫子：私服（夏）
.transition 1 fadeSide.png 10
.stage	* ev02_048.png 0 0
.panel 1
.message	3380			随意用电话把我喊出来的人，已经先行早到公园了。
.message	3390			一副闲的无聊的样子，不安稳的转过来转过去。
.message	3400			虽然平常就不太安稳。
.message	3410		嫗丂夘	「哟～」
.playBGM efBGM013.ogg 0 *
.transition 0 * 20
.stage	* ev02_048_mugai.png 0 0 st_miyako02e01.png 350
;☆（手前に宫子持ってきてますが，ここは問題なしで。つ～か，背景に犬連れたやつ入ってます。削除して）
.message	3420	miy-205_01-0003	傒傗偙	「啊，终于来了～」
.message	3430			为什么会我要被抱怨啊。
.message	3440			我可没有非来不可的理由。
.message	3450			还是说，拒绝女孩子约你出来的男人也不多。
.message	3460	miy-205_01-0005	傒傗偙	「今天也好热呢～」
.message	3470		嫗丂夘	「嗯，所以我想回家」
;■威張り
.transition 0 * 40
.stage	* ev02_048_mugai.png 0 0 st_miyako03e04.png 400
.message	3480	miy-205_01-0007	傒傗偙	「不能那么软弱！　在严酷的环境中锻炼自己才是真正的男人！」
.message	3490		嫗丂夘	「还真是自说自话啊你」
.message	3500			什么叫真的男人啊。
.message	3510		嫗丂夘	「突然把我喊出来到底有什么事」
.message	3520			不会是又想差遣我吧。
.transition 0 * 40
.stage	* ev02_048_mugai.png 0 0 st_miyako06e01.png 400
;（表情注意して）
.message	3530	miy-205_01-0009	傒傗偙	「那个」
.message	3540			宫村点了一下头。
.transition 0 * 40
.stage	* ev02_048_mugai.png 0 0 st_miyako06e03.png 400
;（06e04表情でも？）
.message	3550	miy-205_01-0011	傒傗偙	「本来想要去纮君的家来着，但电话里他说不到晚上别过来」
;.transition 0 * 40
;.stage	* ev02_048_mugai.png 0 0 st_miyako06e04.png 400
;（表情変化のタイミング，注意して）
.message	3560		嫗丂夘	「啊啊，带了别的女人回房了吧」
.playVoice * * 0
.playBGM * * 0
.playSE miyako_kakato.ogg f 0 *
.transition 0 * 40
.stage	* ev02_048_mugai.png 0 0 st_miyako06e04.png 400
;（画面を揺らすことを忘れないように）
.message	3570			咚！
.shakeScreen 2 40 20
.message	3580		嫗丂夘	「啊！？」
.message	3590			突入其来的矬痛，低头一看脚下──
.playSE kyo_syougeki.ogg f 0 *
.transition 0 * 20
.stage	* ev02_049.png 0 0
;（「じゃじゃじゃ～ん」みたいな効果音を·笑。つ～ことで，わざと常道から外してます）
.message	3600			宫村的脚后根已经深深的刺入我的脚背。
.playSE *
.playBGM efBGM013.ogg 0 *
;.transition 0 * 20
;.stage	* ev02_048_mugai.png 0 0
.transition 0 * 20
.stage	* ev02_048_mugai_stm.png 0 0 stm_miyako03e01.png 400
;（宫子も表示させる？もしくは画面全体にぼかしを？）
.message	3610		嫗丂夘	「～～～～」
;.transition 0 * 20
;.stage	* ev02_048_mugai.png 0 0 st_miyako03e01.png 400
;（ポ～ズは注意して）
.message	3620	miy-205_01-0013	傒傗偙	「大意一秒，伤痛一生<音乐符号>」
.message	3630		嫗丂夘	「我，我错了……不过」
.message	3640		嫗丂夘	「……不要一边笑着一边使出那么阴险的攻击好吧」
;.playSE *


.transition 0 * 20
;■御影チェック
;.stage	* ev02_048_mugai.png 0 0 st_miyako01e01.png 400
.stage	* ev02_048_mugai.png 0 0 st_miyako01e01.png 350
;（座標とポ～ズは注意して）
.message	3650	miy-205_01-0015	傒傗偙	「说什么，现在正在作细致的工作～。没有办法，所以我就打算稍微找堤堤聊聊天」
.message	3660			完全没听我说话。
.message	3670			脚痛的要死，不是骨折了吧喂……。
.transition 0 * 40
.stage	* ev02_048_mugai.png 0 0 st_miyako00e10.png 350
;（目をつむらせていいか，注意して。涙もトレてるかどうかも，要チェックを）
.message	3680	miy-205_01-0017	傒傗偙	「最近，原稿的质量越来越高了呢。感觉就只剩工作了的样子」
.message	3690			宫村的表情稍微有些寂寞。
.message	3700	miy-205_01-0019	傒傗偙	「从此以后工作量看来也会日益增多，就算是我也不能每天见面」
.message	3710		嫗丂夘	「哼～……」
.message	3720			正是因为放弃学校而有了时间，编辑部那边才会毫无顾虑的压工作给他的吧。
.transition 0 * 40
.stage	* ev02_048_mugai.png 0 0 st_miyako00e07.png 350
.message	3730	miy-205_01-0021	傒傗偙	「忙的过分很辛苦呢。前段时间还因为从耳朵里流出奇怪的液体闹的乱糟糟的」
.message	3740		嫗丂夘	「把他带去医院啊喂！」
.message	3750			我不由得瞪圆了眼。
;■寂しげ
.transition 0 * 40
.stage	* ev02_048_mugai.png 0 0 st_miyako00e08.png 350
.message	3760	miy-205_01-0023	傒傗偙	「毎个月在截稿之前都完全没有睡觉的时间啊」
.message	3770		嫗丂夘	「这还真是……」
.message	3780			虽然看起来真的很凄惨，但这也他自己所选择的道路。
.transition 0 * 40
.stage	* ev02_048_mugai.png 0 0 st_miyako00e05.png 350
;（表情注意して）
.message	3790	miy-205_01-0025	傒傗偙	「嘛，但是呢」
.message	3800		嫗丂夘	「嗯？」
.transition 0 * 40
.stage	* ev02_048_mugai.png 0 0 st_miyako00e02.png 350
.message	3810	miy-205_01-0027	傒傗偙	「一旦原稿完成的时候，就轮到我睡不着了呢」
.transition 0 * 40
.stage	* ev02_048_mugai.png 0 0 st_miyako02e01.png 350
;（この立ち絵は仮です。専用立ち絵があるようですので，，，）
.message	3820	miy-205_01-0029	傒傗偙	「呀～！　不要～！」
.message	3830		嫗丂夘	「我还不要呢！」
.message	3840			正是因为认识这两人，才会浮起一副让人不爽的绘图啊。
.message	3850			广野那家伙还真能给这种有趣到过分的女人交往啊。
.message	3860			虽然以前就想过，那家伙在某些意义上很强啊。
.message	3870		嫗丂夘	「但是嘛，广野不是作的很不错吗」
.transition 0 * 40
.stage	* ev02_048_mugai.png 0 0 st_miyako04e02.png 400
;（ポ～ズ変えていいか，注意して）
.message	3880	miy-205_01-0031	傒傗偙	「嗯，工作顺利到过分呢。人气也是日日攀升」
.message	3890		嫗丂夘	「虽然他不跟我谈一句就放弃学业让我有点不爽……但只要现在他充实着这样就好」
.transition 0 * 40
.stage	* ev02_048_mugai.png 0 0 st_miyako04e05.png 400
;（ここの表情は注意して）
.message	3900	miy-205_01-0033	傒傗偙	「哼嗯……」
.message	3910	miy-205_01-0034		宫村一瞬露出有些吃惊的表情，随即微笑起来。
.transition 0 * 40
.stage	* ev02_048_mugai.png 0 0 st_miyako04e02.png 400
.message	3920	miy-205_01-0035	傒傗偙	「谢谢你」
.message	3930	miy-205_01-0037	傒傗偙	「我会转告纮君的嗯」
.message	3940		嫗丂夘	「不不，那还是算了」
.message	3950			刚才的台词再怎么说也有点羞人啊。
.transition 0 * 40
.stage	* ev02_048_mugai.png 0 0 st_miyako05e02.png 400
;（05e01表情でも？）
.message	3960	miy-205_01-0039	傒傗偙	「是啊，纮君是充实着的。但是──」
.transition 0 * 40
.stage	* ev02_048_mugai.png 0 0 st_miyako05e03.png 400
.message	3970			瞬间，宫村的表情又蒙上了一层阴影。
.message	3980	miy-205_01-0041	傒傗偙	「纮君呢，在担心小景哦」
.message	3990		嫗丂夘	「…………」
.message	4000	miy-205_01-0043	傒傗偙	「小景，连篮球都放弃了」
.message	4010		嫗丂夘	「据我看，新藤还没有堕落到那种地步」
.message	4020		嫗丂夘	「当然，说不介意是假话，但肯定会摆脱掉的」
.message	4030			有关广野。
.message	4040			有关篮球。
.message	4050			有关那分离开来的双胞胎妹妹。
.message	4060			虽然现实无比艰辛，但她也并没有逃避。
.transition 0 * 40
.stage	* ev02_048_mugai.png 0 0 st_miyako05e06.png 400
;（目線，注意して。05e09でも？）
.message	4070	miy-205_01-0045	傒傗偙	「但是还没有摆脱的吧？」
.message	4080		嫗丂夘	「谁知道呢」
.message	4090			这个我也不明白──
.message	4100			新藤本身就是难以理解的东西啊。
.message	4110		嫗丂夘	「不过，我觉得广野没必要担心。虽然我不知为什么」
.transition 0 * 40
.stage	* ev02_048_mugai.png 0 0 st_miyako05e05.png 400
.message	4120	miy-205_01-0047	傒傗偙	「我呢」
.message	4130			宫村稍微浮起一丝微笑。
.message	4140	miy-205_01-0049	傒傗偙	「有些吃惊呢。没想到小景会再次配合堤堤的摄影」
.message	4150		嫗丂夘	「她一旦同意，就不会再反悔的吧」
.message	4160			因为她十分倔脾气的啊。
.message	4170	miy-205_01-0051	傒傗偙	「是吗？」
.transition 0 * 40
.stage	* ev02_048_mugai.png 0 0 st_miyako05e02.png 400
;（表情変化，注意して。06ポ～ズを使うことも考慮に）
.message	4180	miy-205_01-0053	傒傗偙	「以前呢，纮君这样说过」
.message	4190	miy-205_01-0055	傒傗偙	「如果是纮君喜欢的人的话，小景也会喜欢」
.transition 0 * 40
.stage	* ev02_048_mugai.png 0 0 st_miyako05e01.png 400
;（表情変化，注意して）
.message	4200	miy-205_01-0057	傒傗偙	「堤堤不是纮君为数不多的朋友之一吗」
.message	4210		嫗丂夘	「……你想说什么？」
.transition 0 * 40
.stage	* ev02_048_mugai.png 0 0 st_miyako06e02.png 400
.message	4220	miy-205_01-0059	傒傗偙	「小景说不定意外地对堤堤有好感也说不定哦」
.message	4230		嫗丂夘	「是吗」
.message	4240			我感觉新藤只是在打发时间，自暴自弃的味道多一些。
.transition 0 * 40
.stage	* ev02_048_mugai.png 0 0 st_miyako05e02.png 400
;.stage	* ev02_048_mugai.png 0 0 st_miyako05e01.png 400
;（05e02表情でも？）
.message	4250	miy-205_01-0061	傒傗偙	「说不定，这次摄影对堤堤和小景都是一个好机会呢」
.message	4260		嫗丂夘	「机会指什么啊机会」
;■微笑
.transition 0 * 40
.stage	* ev02_048_mugai.png 0 0 st_miyako07e03.png 410
;（身体の向きを強引に変えていいのか，注意して）
.message	4270	miy-205_01-0063	傒傗偙	「哼喵喵喵喵」
.message	4280		嫗丂夘	「不然突然变成猜灯谜好吧」
.transition 0 * 40
.stage	* ev02_048_mugai.png 0 0 st_miyako02e01.png 350
.message	4290	miy-205_01-0065	傒傗偙	「啊哈哈哈哈」
.message	4300			完全进入装糊涂模式了。
.message	4310			但无需追问，也大致能明白宫村想说的……。
.message	4320			现在还是当成没听到好了。
.panel 0
.playBGM *
.transition 0 * 10
.stage	* WHITE.png 0 0


;■京介自室（夏，１９時
;■　　　　堤京介：私服（夏）
.transition 1 fadeSide.png 10
.stage	* ev02_050.png 0 0
;.stage	* ev02_033.png 0 0
.panel 1
.message	4330			把关于明天摄影的事宜发了短信给新藤后，放下了手机。
.message	4340			今天要做的事情到此为止。
.message	4350			不不，得去学习啊。
.message	4360			在三年级的这个时候为了拍电影而升学失败──我可不想被这么说。
.message	4370		嫗丂夘	「我倒也不是特别想去当什么电影导演啊……」
.message	4380			我只是有想要去拍摄，这样单纯的冲动而已。
.message	4390			完成这个小小的电影之后，大概就会专心学习吧。
.message	4400			大概，升学以后也会继续拍电影的吧。
.message	4410			但是，先不管这些──
.message	4420			宫村在期待我什么呢。
.message	4430			到最后，她想让新藤站起来也只是为了自己和广野而已。
.message	4440			宫村和广野两个人，都对新藤抱有罪恶感。
.message	4450			消除这个可不是我的工作。
.message	4460			话说回来，这种事情我根本就做不到。
.message	4470			我仅仅是为了拍电影而在新藤身边。
.message	4480			这样就够了。
.panel 0
.transition 0 * 10
.stage	* WHITE.png 0 0
.transition 0 * 10
.stage	* WHITE.png 0 0
.wait 100

.chain 206_01.sc
;■206_01へ。

;.end
