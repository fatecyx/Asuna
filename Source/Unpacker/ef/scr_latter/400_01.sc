.setGlobal EYE_SEQ_DEFAULT = 2

.transition 0 * 10
.stage	* WHITE.png 0 0
.wait 500

.transition 0 * 10
.stage	vista_window.png ago_base_40000a.png 0 0
.panel 3
.message	100	yuk-400_01-0003	桪丂巕	「我叫做优子哟」
.message	110	mid-400_01-0003		教会之前，漂亮的女人在微笑着。
.transition 0 * 20
.stage	vista_window.png ago_base_40000c4.png 0 0
.message	120	mid-400_01-0005		这是，我获得现在这个名字之前所经历的故事。
.transition 0 * 20
.stage	vista_window.png ago_base_40000c5.png 0 0
.message	130	mid-400_01-0007		这是，在和终点的车站的话语所不同的，冬日尽头的一幕。
.transition 0 * 20
.stage	vista_window.png ago_base_40000c6.png 0 0
.message	140	mik-400_01-0003	#枹丂棃	「优子」
.transition 0 * 20
.stage	vista_window.png ago_base_40000c7.png 0 0
.message	150	yuk-400_01-0005	桪丂巕	「…………」
.transition 0 * 20
.stage	vista_window.png ago_base_40000c1.png 0 0
.message	160	yuk-400_01-0007	桪丂巕	「嗯嗯，是优子。你的名字是？」
.message	170	mid-400_01-0009		女人稍微顿了下，询问着她的名字。
.message	180	mik-400_01-0005	#枹丂棃	「…………」
.transition 0 * 20
.stage	vista_window.png ago_base_40000c2.png 0 0
.message	190	yuk-400_01-0009	桪丂巕	「啊啦啦」
.transition 0 * 20
.stage	vista_window.png ago_base_40000c3.png 0 0
.message	200	yuk-400_01-0011	桪丂巕	「姐姐，想知道你的名字哟～」
.message	210	yuk-400_01-0013	桪丂巕	「想知道哟～」
.message	220	mik-400_01-0007	#枹丂棃	「……美希」
.message	230	mid-400_01-0011		在孩子般的连续招呼中，她粗鲁的回答。
.message	240	yuk-400_01-0015	桪丂巕	「美希……吗？」
.message	250	mik-400_01-0009	#枹丂棃	「未来」
.message	260	yuk-400_01-0017	桪丂巕	「诶？是哪个啊？」
.message	270	mik-400_01-0011	#枹丂棃	「写作“未来（ＭｉＲａｉ）”，但是读作“美希（ＭｉＫｉ）”……」
.message	280	yuk-400_01-0019	桪丂巕	「啊，原来是这样吗」
.message	290	mid-400_01-0013		像是理解了什么似的，自称叫做优子的女人，露出了满面的笑容。
.message	300	yuk-400_01-0021	桪丂巕	「嗯，是个好名字呢」
.message	310	mik-400_01-0013	#枹丂棃	「罗嗦」

.playSE yuuko_kachin.ogg f 0 *

.transition 0 * 10
.stage	vista_window.png WHITE.png 0 0


.message	330	mid-400_01-0017		只能听到微弱的空气流动的声音，两个人一时无言，相互凝视着对方。
.message	340	mid-400_01-0019		这是一次平淡无奇的相遇。
.message	350	mid-400_01-0021		但是，一切的源头，的确是从这里开始的。
.transition 0 * 10
.stage	* vista_white.png 0 0
.panel 0
.playBGM *



.panel 0
.transition 0 * 8
.stage	* BLACK.png 0 0
.wait 400





.if ef400_01 == 1 400_01_b1
.if ef400_01 <= 0 400_01_a1

.label 400_01_a1
.movie2 op2.avi 800 600 op2.ogg 44100 2 f

.pragma disable_control

.goto 400_01_c1
.end

.label 400_01_b1
.movie2 op2.avi 800 600 op2.ogg 44100 2 t
.goto 400_01_c1
.end


.label 400_01_c1



.setGlobal ef400_01 = 1




.transition 0 * 8
.stage	* BLACK.png 0 0
.wait 300

.transition 0 * 10
.stage	* WHITE.png 0 0


.pragma enable_control


.chain 400_02.sc
