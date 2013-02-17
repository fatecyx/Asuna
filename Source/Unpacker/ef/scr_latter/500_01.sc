.setGlobal EYE_SEQ_DEFAULT = 2

.transition 0 * 10
.stage	* BLACK.png 0 0
.wait 200



.transition 0 * 10
.stage	* BLACK.png 0 0
.panel 3
.message	100	him-500_01-0003	#丂梉丂	回想起来的话，我总会有这么一种感觉。\v\a
.wait 100
.message	110	him-500_01-0005	#丂梉丂	我从世界被切离分开的感觉。\v\a
.wait 150
.message	120	him-500_01-0007	#丂梉丂	虽然希望其他人知道自己的存在，却不知道自己该做些什么好。\v\a
.wait 150
.message	130	him-500_01-0009	#丂梉丂	如此寂寞。\v\a
.wait 100
.message	140	him-500_01-0011	#丂梉丂	如此悲伤。\v\a
.wait 200
.message	150	him-500_01-0013	#丂梉丂	在流逝的时间中，只有悲伤的心情在不断的日积月累，不论怎样都无法摆脱这种心情。\v\a
.wait 200
.message	160	him-500_01-0015	#丂梉丂	我，做不到。\v\a
.panel 0


.transition 0 * 10
.stage	* WHITE.png 0 0

.playSE kane_ef.ogg f
.transition 0 * 10
.stage	* title_summer.png 0 0
.message	999			\a　
.wait 1000
.playSE *

.transition 0 * 10
.stage	* WHITE.png 0 0





.wait 150
.playBGM efLAT05_02.ogg




.transition 0 * 10
.stage	* bgc_sch002a01_02_pastm3.png 0 0
.panel 1

.message	858			结束在图书馆的学习，来到走廊。
.transition 0 * 20
.stage	* bgc_sch002a01_02_pastm2.png 0 0
.message	868			四周静寂无声，连个人影都看不到。
.transition 0 * 20
.stage	* bgc_sch002a01_02_pastm.png 0 0
.message	878			平时应该还有社团活动和在委员会工作的学生在的，为什么今天如此安静呢。
.message	888			连自己的足音，都大的让人吃惊。
.message	898			浸染过夏日阳光的走廊，在傍晚仍然感受不到凉意。
.message	908			仅仅是走着而已，就已是汗流浃背。
.transition 0 * 20
.stage	past_window.png bgs_sch009a01_02.png 0 0
.message	918			换好鞋子，走出教学楼。
.message	928			风夹带着蒸笼般的暑气，闷热的空气包满全身。
.message	938			再次让我觉察到，现在是夏天。
.message	948			我并不讨厌夏天。
.message	958			比起阴郁的冬天，很难找到讨厌这个充满音色和光芒的季节的理由。
.message	968			并不讨厌，吗。
.message	978			我发现总是如此。
.message	988			世界只会被我分为不算很讨厌和讨厌两种而已。
.message	998			真称不上是健全的生存方式…啊，我独自苦笑起来。
.message	1008			生存方式…吗。
.transition 0 * 20
.stage	past_window.png ev00_004_mugai_h2.png 781 1037
.message	1018			仰望天空。
.message	1028			我所希望的生存方式是——
.message	1038		丂梉丂	「那是什么……？」
.transition 0 * 20
.stage	past_window.png ev00_004_mugai_h2.png 781 1037
.scroll	581 837	6
.endScroll f
.message	1048			在那被夕阳染红的天空，一片细小的白色轻轻舞动。
.transition 0 * 20
.stage	* ev00_004.png 0 0
.message	1058			那是……一架纸飞机。



.panel 0
.transition 0 * 10
.stage	* final_terop_a1.png 0 0
.wait 100
.transition 0 * 10
.stage	* final_terop_a2.png 0 0
.message	5999			\a　
.wait 500
.transition 0 * 10
.stage	* final_terop_a1.png 0 0
.wait 50



.transition 0 * 10
.stage	* ev00_005.png 0 0
.panel 1
.message	1068		丂梉丂	「哪里的笨蛋扔出来的」
.message	1078			捡起那飘落在地的纸飞机。
.message	1088			都几岁了，在这学校里还会有哪个笨蛋在玩这样的东西。
.transition 0 * 20
.stage	* ev00_006_mugai_d.png 0 600
.message	1098			我带着些许的惊讶，开始一个个的确认教学楼的窗户。
.transition 0 * 20
.stage	* ev00_006_mugai_d.png 0 600
.vscroll	0	-10
.endScroll f
.message	1108			在我以为犯人可能已经消失的时候……。
.message	1118		丂梉丂	「啊……」
.transition 0 * 20
.stage	* ev00_006_mugai_a.png 0 0
.message	1128			一名少女的身影，进入了我的视线。
.message	1138			而且不知为何，那女孩坐在屋顶的边缘，惬意地摇晃着自己的双足。
.transition 0 * 20
.stage	* ev00_006.png 0 0
.message	1148			在那种地方干什么呢。
.message	1158			不，比起这个——
.message	1168			突然，就在我的疑问接连涌出的时候。
.message	1178			虽然隔着很远，我却清楚地看到了。
.message	1188			那女孩停止了脚的晃动，望向下方的我——微笑起来。




.transition 0 * 10
.stage	* bgs_sky001a01_02_mugai_a.png 0 0
.message	1198			打开那扇门，天空近的仿佛触手可及。
.message	1208			鲜艳的绯红色，红到会让人产生那轮夕日马上便会坠下将这地面燃尽的错觉。
.message	1218			在那片弄痛眼睛的绯色之中——
.transition 0 * 10
.stage	* ev00_007a01_mugai_a.png 0 0
.message	1228			少女在微笑着。
.transition 0 * 20
.stage	* ev00_007a02.png 0 0
.message	1238		丂梉丂	「……为什么是冬服？」
.message	1248			虽然并不是想问这个，但就先这样问过去。
.message	1258			或者说，我无法说出什么合适的话来。
.message	1268			眼前的光景是如此绮丽，以至于让人失去现实感。
.message	1278			而且虽然是第一次来屋顶，但理所当然该有的栅栏却没有这点也让我稍有些吃惊。
.transition 0 * 40
.stage	* ev00_007a03.png 0 0
.message	1288	yuk-000_01-0055	@桪丂巕	「冬服？」
.message	1298			在那强烈的不协调感所渲染出的景色中，那名少女歪了一下头。
.message	1308		丂梉丂	「你穿的不是冬服吗」
.message	1318		丂梉丂	「还是不知道什么叫换衣服呢？」
.transition 0 * 40
.stage	* ev00_007a01.png 0 0
.message	1328	yuk-000_01-0057	@桪丂巕	「啊啊，这件衣服吗。这是夏服哦」
.message	1338		丂梉丂	「哈？」
.message	1348			她的衣服再怎么看都是音羽学园的冬服。
.message	1358			包裹的严严实实，更让人觉得奇怪的是连手套都带着。
.transition 0 * 40
.stage	* ev00_007a02.png 0 0
.message	1368	yuk-000_01-0059	@桪丂巕	「冬天穿的衣服才叫冬服。这是夏天穿的所以是夏服。不对吗？」
.message	1378		丂梉丂	「完全不对的吧……」
.message	1388			看来是不能用常理说服了。
.transition 0 * 40
.stage	* ev00_007a01.png 0 0
.message	1398	yuk-000_01-0061	@桪丂巕	「请别介意啦。虽然偶尔会被人说，看着就觉得热的难受……」
.message	1408			被那样说也是理所当然的吧。
.message	1418			在夏天最热的时间里穿这样的衣服，自然会让人觉得不适。
.transition 0 * 40
.stage	* ev00_007a02.png 0 0
.message	1428	yuk-000_01-0063	@桪丂巕	「不太想穿半袖」
.message	1438	yuk-000_01-0065	@桪丂巕	「以前…稍微发生过些事呢」
.message	1448			她一边说着，一边隔着衣服轻轻抚摩自己的手腕。
.message	1458	yuk-000_01-0067	@桪丂巕	「当时是觉得无所谓，不过现在到了微妙的年纪啊……」
.message	1468		丂梉丂	「我没有要刨根问底的意思」
.message	1478			我明白那女孩的意思，打断了她的话。
.message	1488			大概是，童年的时候受过伤而留下的创口吧。
.message	1498			在这个年纪的女孩，肌肤的伤口不想被看到也无可厚非。
.message	1508			这种程度的事情我还是懂的，不过认真看起来的话……
.message	1518			这女孩穿着冬服，有种不可思议的适合感。
.message	1528			当然，那样的话我可不会说出口。
.transition 0 * 40
.stage	* ev00_007a01.png 0 0
.message	1538	yuk-000_01-0069	@桪丂巕	「说起来，您不是专门为了说长袖看起来闷热才来的吧？」
.message	1548		丂梉丂	「怎么可能」
.message	1558			我摇了摇头，想起了本来的目的。
.transition 0 * 20
.stage	* ev00_008a01.png 0 0
.message	1568		丂梉丂	「我说你啊，屋顶是禁止进入的哦」
.message	1578			正常情况应该是被锁住的才对啊，是如何把锁打开的也是一个谜。
.transition 0 * 40
.stage	* ev00_008a02.png 0 0
.message	1588	yuk-000_01-0071	@桪丂巕	「你不是也进来了吗」
.message	1598			少女露出稍稍执拗的神情。
.message	1608		丂梉丂	「我是来提醒你的。可别扯开话题哦」
.transition 0 * 40
.stage	* ev00_008a03.png 0 0
.message	1618	yuk-000_01-0073	@桪丂巕	「被人看到还是第一次呢。可惜，可惜」
.message	1628			我完全想不出她为什么要说可惜的理由。
.message	1638		丂梉丂	「还好我不是教师。你是怎么进来的？」
.message	1648			音羽学园的屋顶禁止随意出入——话虽这么说，只是入学之后才听说这件事，之前都忘记了屋顶的存在吧。
.message	1658			就这点来说，这地方学生们应该不熟悉才对。
.transition 0 * 40
.stage	* ev00_008a01.png 0 0
.message	1668	yuk-000_01-0075	@桪丂巕	「啊啊，这件事情吗」
.message	1678	yuk-000_01-0077	@桪丂巕	「我是天文部部员哦。拥有可以进入屋顶的特别许可」
.message	1688		丂梉丂	「要撒谎的话，也找些更像样的出来吧」
.message	1698		丂梉丂	「在这种时间怎么可能看见什么星星。再说，我们学校有天文部吗？」
.message	1708			看过去的话，也没看到带有望远镜之类的器具。
.transition 0 * 40
.stage	* ev00_008a03.png 0 0
.message	1718	yuk-000_01-0079	@桪丂巕	「当然有啊。只是从昨天起废部了而已」
.message	1728		丂梉丂	「废部？」
.transition 0 * 40
.stage	* ev00_008a04.png 0 0
.message	1738	yuk-000_01-0081	@桪丂巕	「嗯，３年级的前辈提早一步引退了。没有２年级的部员，剩下的只有１年级的我而已」
.message	1748		丂梉丂	「只有１年级…吗」
.message	1758			虽然明白，这个少女应该是我的后辈。
.message	1768			但直观的看起来，她倒好像比我小３到４岁。
.transition 0 * 40
.stage	* ev00_008a03.png 0 0
.message	1778	yuk-000_01-0083	@桪丂巕	「虽然我还妄想会不会有人正好这时入部呢～～可惜这个世界没那么一帆风顺啊」
.message	1788		丂梉丂	「只有一个人的话确实没法做点什么。虽然遗憾但这也是没办法的事」
.message	1798			我这样说着毫无感情的话。
.message	1808			最近，就算是极其无聊的话，也能普通的作出回应——是好是坏暂且不论。
.transition 0 * 40
.stage	* ev00_008a01.png 0 0
.message	1818	yuk-000_01-0085	@桪丂巕	「是啊，没办法的事情呢」
.transition 0 * 40
.stage	* ev00_008a04.png 0 0
.message	1828	yuk-000_01-0087	@桪丂巕	「但是呢……」
.transition 0 * 20
.stage	* ev00_008a_mugai_a.png 0 0
.message	1838		丂梉丂	「怎么？」
.message	1848	yuk-000_01-0089	@桪丂巕	「跟我有关的人或事，都会迎来很坏的结局呢……」
.message	1858		丂梉丂	「那是什么意思」
.message	1868	yuk-000_01-0091	@桪丂巕	「呼唤厄运的存在之类吧，而且会把周围的人都卷进来」
.message	1878	yuk-000_01-0093	@桪丂巕	「虽然我并不怎么有自觉呢」
.message	1888			又说些可怕的事情。

.message	1898			不过，对于初次见面的人不会这么坦白吧。

.message	1908		丂梉丂	「嘛，那种事情无所谓了。我只是来提醒下而已。不要再坐在那么危险的地方了」
.transition 0 * 20
.stage	* ev00_008b02.png 0 0
.message	1918	yuk-000_01-0095	@桪丂巕	「啊啦，还真是位温柔的人呢」
.message	1928			那名少女呵呵的笑起来
.message	1938			那个笑容不知为何让我有些恼火。
.message	1948		丂梉丂	「……你偷偷来屋顶与否是你自己的事。但是，摔下去死掉的话是会造成困扰的」
.transition 0 * 40
.stage	* ev00_008b03.png 0 0
.message	1958	yuk-000_01-0097	@桪丂巕	「为什么，你会困扰呢？」
.transition 0 * 20
.stage	* ev00_008b01_mugai_c.png 0 0
.message	1968			她歪着头，好像真的不理解的样子。
.message	1978		丂梉丂	「讨厌人的死亡。不是理所当然的事情吗？」
.transition 0 * 20
.stage	* ev00_008a01_mugai_c.png 0 0
.message	1988	yuk-000_01-0099	@桪丂巕	「那是你个人的价值观吧」
.message	1998			她好象稍微有些生气的说道。
.message	2008			说起话来毫无顾忌——少女给我留下了这样的印象。
.message	2018			同时也感觉到实际上也就是这么回事。
.transition 0 * 40
.stage	* ev00_008a04_mugai_c.png 0 0
.message	2028	yuk-000_01-0101	@桪丂巕	「虽然如此，当然，我并没有贬低你的价值观的意思哦」


.playVoice *


.transition 0 * 10
.stage	* ev00_008b01_mugai_b.png 0 0

.playBGM *

.message	2048	yuk-000_01-0103	@桪丂巕	「火村夕前辈」
.message	2058			然后，她用柔软的声音喊出了我的名字——
.message	2068		丂梉丂	「……你是谁？」
.message	2078			是同一个学校的学生，知道我的名字本身并没有什么不可思议。
.message	2088			但是。
.message	2098			我记得这个声音。
.message	2108			这个说话方式，这个笑容，确实存在于我久远记忆的某处。
.transition 0 * 20
.stage	* ev00_008a04_mugai_b.png 0 0
.message	2118	yuk-000_01-0105	@桪丂巕	「果然忘了我啊。稍微有些受打击呢～」
.message	2128		丂梉丂	「回答我的问题」
.message	2138	yuk-000_01-0107	@桪丂巕	「不要做出那么可怕的表情啦。特别是在女孩子面前哦」
.message	2148			她摇摇头，用稍微带些叱责的口气说道。
.message	2158			为什么会直冒冷汗呢。
.message	2168			有什么东西正在牵引着心脏，让我产生几乎要停止呼吸的错觉。
.transition 0 * 20
.stage	* ev00_008a03_mugai_b.png 0 0
.message	2178			那名少女再次微笑起来。
.message	2188	yuk-000_01-0109	@桪丂巕	「……我是优子啊」
.message	2198		丂梉丂	「优子？」
.transition 0 * 40
.stage	* ev00_008a04_mugai_b.png 0 0
.message	2208	yuk-000_01-0111	@桪丂巕	「嗯，这是我的请求……请不要说忘记了那样的话好吗」
.message	2218			优子……？
.transition 0 * 40
.stage	* ev00_008a05_mugai_b.png 0 0
.message	2228	yuk-000_01-0113	@桪丂巕	「我只看一眼就明白你是谁，而你却彻底的忘记了我呢……我的心已经被伤害的无法治愈了」
.transition 0 * 10
.stage	past_window.png ev00_008a05_mugai_b_close.png 0 0
.message	2238	yuk-000_01-0115	@桪丂巕	「如果」
.panel 0
.transition 0 * 10
.stage	* WHITE.png 0 0


.wait 200
.transition 0 * 10
.stage	* ev00_moshi.png 0 0
.message	2248		桪丂巕	「如果忘记了的话，就沉默到回忆起来。」\v\a
.wait 300


.transition 0 * 10
.stage	* WHITE.png 0 0
.wait 200





.transition 0 * 10
.stage	* ev05_001.png 0 0
.panel 1
.message	1590	yuk-500_01-0071	@桪丂巕	「当成什么都没发生过，就这样告别也好……」
.playSE kane_ef.ogg f
.transition 0 * 20
.stage	* ev05_004_mugai_a2.png 0 0
.message	1600			突然，脑海里响起了声音。
.transition 0 * 20
.stage	* ev05_004_mugai_a3.png 0 0
.message	1610		丂梉丂	「你是……」
.transition 0 * 20
.stage	* ev05_002_mugai_a.png 0 0
.message	1620			那是简直就要把耳膜震破的，高声鸣唱的钟声。
.transition 0 * 20
.stage	* ev05_002_mugai_b.png 0 0
.message	1630			一边寻找着重要的人，一边哭喊着的孩子们。
.transition 0 * 20
.stage	* ev05_002.png 0 0
.message	1640		丂梉丂	「教会……」
.message	1650			忍着眼泪跑向的前方，是已经一无所有的景象。
.transition 0 * 20
.stage	* ev05_003_mugai_a.png 0 0
.message	1660			化为废墟的都市。
.transition 0 * 20
.stage	* ev05_003_mugai_b.png 0 0
.message	1670			在已经崩溃，不断运出瓦砾的建筑物前，呼喊着什么人的名字。
.transition 0 * 20
.stage	* ev05_003_mugai_c.png 0 0
.message	1680			那种自暴自弃般的叹息，以及撕心裂肺般悲痛的惨叫声。
.transition 0 * 20
.stage	* ev05_003_mugai_d.png 0 0
.message	1690			被绝望彻底击垮的人，对点滴的希望还有所寄托的人——
.transition 0 * 20
.stage	* ev05_003_mugai_f.png 0 0
.message	1700			在那个日常生活已经被摧毁的地方，人们各种各样的感情被凝聚成漩涡。
.transition 0 * 20
.stage	* ev05_003_mugai_e.png 0 0
.message	1710			在我惊恐的看着那个已经天翻地覆的世界，禁不住止步不前的时候——我的手碰到了温暖的东西。
.transition 0 * 20
.stage	* ev05_004.png 0 0
.message	1720			转过脸，那是——
.transition 0 * 20
.stage	* ev05_004_mugai_b.png 0 0
.message	1730		丂梉丂	「是么……」
.playSE *
.transition 0 * 20
.stage	* ev05_001_mugai_a.png 0 0
.message	1740			过去的影像被中止，我的目光聚焦在眼前的少女身上。
.transition 0 * 20
.stage	* ev05_001.png 0 0
.message	1750			如果认真看的话，那个时候的这张面容确实还残留在记忆中……




.transition 0 * 10
.stage	* ev00_008a01.png 0 0
.message	1760		丂梉丂	「不，我想起来了……回忆起你了，优子」
.transition 0 * 10
.stage	* ev00_008b02.png 0 0
.message	1770	yuk-500_01-0073	桪丂巕	「非常感谢您」
.message	1780		丂梉丂	「不用说那么客气的话」
.message	1790			是的，我也不想听到。
.message	1800			对于想忘记过去的我，居然还在某处残留着她的记忆，那必然——
.message	1810		丂梉丂	「优子，你……」
.transition 0 * 40
.stage	* ev00_008b03.png 0 0
.message	1820	yuk-500_01-0075	桪丂巕	「嗯？」
.message	1830		丂梉丂	「……没什么」
.message	1840			我略微摇了下头。
.transition 0 * 20
.stage	* ev00_008b01_50001a.png 0 0
.message	1850			然后，走近她一步。
.message	1860		丂梉丂	「别把这种东西飞出去。会成为垃圾的」
.transition 0 * 20
.stage	* ev05_006.png 0 0
.message	1870			一边尽可能的用不高兴的口气说着，一边把刚才捡到的纸飞机递了过去。
.transition 0 * 20
.stage	* ev00_008b05_50001a.png 0 0
.message	1880	yuk-500_01-0077	桪丂巕	「好不容易折出来的精品，被说成是垃圾太过分了哟」
.message	1890		丂梉丂	「如果是认真做的话自己当成重要的东西留着不是更好么」
.transition 0 * 40
.stage	* ev00_008b02_50001a.png 0 0
.message	1900	yuk-500_01-0079	桪丂巕	「说的是呢，应该是很重要的呢」
.message	1910			她不停地点着头。
.transition 0 * 40
.stage	* ev00_008b01_50001a.png 0 0
.message	1920	yuk-500_01-0081	桪丂巕	「那就请当作重要的东西收藏起来吧。虽然把翅膀折了下什么的还是没关系的，但不能丢掉哦」
.message	1930		丂梉丂	「等一下。你这是什么意思」
.transition 0 * 40
.stage	* ev00_008b04_50001a.png 0 0
.message	1940	yuk-500_01-0083	桪丂巕	「这个纸飞机，我送给火村前辈了哟」
.message	1950		丂梉丂	「什么？」
.message	1960			优子看似很高兴的微笑着，凝视着我。
.transition 0 * 40
.stage	* ev00_008b01_50001a.png 0 0
.message	1970	yuk-500_01-0085	桪丂巕	「虽然想着有点遗憾呢」
.message	1980		丂梉丂	「遗憾？」
.transition 0 * 40
.stage	* ev00_008b04_50001a.png 0 0
.message	1990	yuk-500_01-0087	桪丂巕	「这里明明是只属于我一个人的地方，但是却被别人不法闯入了」
.transition 0 * 40
.stage	* ev00_008b02_50001a.png 0 0
.message	2000	yuk-500_01-0089	桪丂巕	「不过，是你的话可以原谅哦」
.message	2010	yuk-500_01-0091	桪丂巕	「我一直，都想和你再一次的见面」
.message	2020			优子接二连三地说到。
.transition 0 * 40
.stage	* ev00_008b04_50001a.png 0 0
.message	2030	yuk-500_01-0093	桪丂巕	「作为再会的纪念，请收下吧」
.message	2040		丂梉丂	「你在说什么……不，比起这个」
.message	2050		丂梉丂	「这种东西，我不需要」
.message	2060			这个不应该是什么再会的纪念一类的。
.message	2070			至少，对我来说这不是什么值得高兴的事态。
.transition 0 * 10
.stage	* ev00_008a01_50001a.png 0 0
.message	2080	yuk-500_01-0095	桪丂巕	「我——」
.message	2090			我把纸飞机交出的手，突然震动了一下。

.message	2101	yuk-500_01-0096	桪丂巕	「至今为止，都在……」
.message	2102	yuk-500_01-0098	桪丂巕	「憎恨着你」

.message	2110		丂梉丂	「…………」
.message	2120			这绝对不是恐吓。
.message	2130			倒不如说，在她微笑的表情里浮现出了什么。
.message	2140			为什么，如此的——
.transition 0 * 20
.stage	* ev00_008a04_50001a.png 0 0
.message	2150	yuk-500_01-0099	桪丂巕	「嗯，一直都在」
.transition 0 * 20
.stage	* ev00_008a03_50001a.png 0 0
.message	2160	yuk-500_01-0101	桪丂巕	「再度见面真是太好了。终于可以确认了呢」
.message	2170		丂梉丂	「确认……？」
.transition 0 * 20
.stage	* ev00_008b01_50001b.png 0 0
.message	2180	yuk-500_01-0103	桪丂巕	「嗯，你至今为止——」
.transition 0 * 20
.stage	* ev00_008b05_mugai_c.png 0 0
.message	2190	yuk-500_01-0105	桪丂巕	「想伸出手来握住你的人，却被你用力甩掉的伤痛——你至今为止还不知道吗？」
.transition 0 * 20
.stage	* ev00_008b05_50001c.png 0 0
.message	2200			我可以想象到她的恐惧。
.transition 0 * 20
.stage	* ev05_006_mugai_a.png 0 0
.message	2210			感觉简直如同世界结成了坚冰一般，身体完全无法动弹。
.message	2220			什么声音都听不到。
.transition 0 * 20
.stage	* ev05_007a01_mugai_a.png 0 0
.message	2230	yuk-500_01-0107	桪丂巕	「……我是在开玩笑哟？」
.transition 0 * 20
.stage	* ev05_007a01_mugai_b.png 0 0
.message	2240			突然出现的声音，传到了耳朵里。
.transition 0 * 20
.stage	* ev05_007a01_mugai_c2.png 0 0
.message	2250			静止不动，被封闭着的空间迅速被解放开来。
.transition 0 * 20
.stage	* ev05_007a01.png 0 0
.message	2260	yuk-500_01-0109	桪丂巕	「别做出那么不安的表情哟。火村前辈还真是一本正经呢╋」
.transition 0 * 20
.stage	* ev05_007a02.png 0 0
.message	2270	yuk-500_01-0111	桪丂巕	「啊，这个纸飞机我可是认真的要你当成重要的东西保管的哦。我会经常突击检查看你有没有丢掉的」
.message	2280			那种没事一般，明朗的声音穿过了我的耳朵。
.message	2290			虽然心中想捏毁手上的纸飞机的冲动急速上升，不过不管怎么样还是先抑制下来。
.transition 0 * 20
.stage	* ev05_007a04.png 0 0
.message	2300		丂梉丂	「……真是廉价的纪念品」
.transition 0 * 20
.stage	* ev05_007a03.png 0 0
.message	2310	yuk-500_01-0113	桪丂巕	「呵呵，你可真是一点都没变」
.message	2320	yuk-500_01-0115	桪丂巕	「一如既往的坏心肠……」
.transition 0 * 20
.stage	* ev05_007b01.png 0 0
.message	2330			小小的叹了下气，少女轻轻的迈出步伐。
.transition 0 * 20
.stage	* ev05_008a01.png 0 0
.message	2340	yuk-500_01-0117	桪丂巕	「那么再见了哦……哥哥」
.playSE okuzyou_door_miyako.ogg f 0 *
.transition 0 * 20
.stage	* ev05_008b01.png 0 0
.message	2350		丂梉丂	「…………」
.playSE okuzyou_door_miyako_close.ogg f 0 *
.transition 0 * 20
.stage	* ev05_008c01.png 0 0
.message	2360			我没能叫住离开的优子。
.transition 0 * 20
.stage	* ev05_008d01.png 0 0
.message	2370			哥哥，吗？
.message	2380			已经有多少年没听到这个称呼了。
.message	2390			我已经觉得——不可能再次听到了。
.message	2400			被谁这样叫着，以及被触动心灵的事情……。
.message	2410	aka-500_01-0003	#丂埄丂	『哥哥』
.message	2420			――――！
.playSE town_dead_yuu.ogg true
.transition 0 * 20
.stage	* WHITE.png 0 0
.message	2430			脑海中爆发出了火焰。
.transition 0 * 20
.stage	* ev05_009.png 0 0
.message	2440			我冷静的调整着呼吸，把打开了的回忆慢慢关上。
.transition 0 * 20
.stage	* ev05_009_mugai_c.png 0 0
.message	2450			只有这个，不行——
.transition 0 * 20
.stage	* BLACK.png 0 0
.message	2460			绝对不可以想起的，连触碰都不被允许的记忆。
.playSE *
.transition 0 * 20
.stage	* ev05_007b01_mugai_a.png 0 0
.message	2470			我就这样拿着纸飞机低下目光。
.message	2480			如果看着现实的话——就不可以用禁忌的过去来充斥今天。
.transition 0 * 20
.stage	* ev05_007b01_mugai_b.png 0 0
.message	2490		丂梉丂	「……哈」
.message	2500			稍微叹了下气。
.message	2510			没事的，我一直都能很好的控制自己。
.message	2520			不可能迷失自我。
.message	2530			我一直都能做到。
.transition 0 * 20
.stage	* ev05_008d01_mugai_a.png 0 0
.message	2540		丂梉丂	「啊，是了。该去打工了……」
.message	2550			太阳差不多要下山了。
.message	2560			现在不是在这无聊的地方玩个人秀的时候。
.panel 0
.transition 0 * 20
.stage	* ev05_007b01_big.png 0 600
.scroll	800 350	10
.endScroll f

.panel 1
.message	2570		丂梉丂	「走吧」
.transition 0 * 20
.stage	* bgs_sky001a01_02.png 0 0
.message	2580			一边嘟嚷着，我开始迈步。
.message	2590			是的，不走不行。
.message	2600			没有闲工夫去回想已经无法回归的过去，不止是我，我认为谁都不会这样做。
.playSE semishigure_b.ogg f 0 *
.transition 0 * 20
.stage	* WHITE.png 0 0
.message	2610			好像回忆起了似的，蝉开始鸣叫起来。
.message	2620			夏天——我并不讨厌。
.panel 0
.playBGM *
.transition 0 * 5
.stage	* WHITE.png 0 0
.playSE *

.transition 0 * 10
.stage	* BLACK.png 0 0
.wait 100

.chain 501_01.sc
.end
