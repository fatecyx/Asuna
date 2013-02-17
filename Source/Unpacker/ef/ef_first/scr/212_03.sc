; ファイル: 212_03.txt
;■212_01より。
;■２：やっぱり新藤を撮りたい。　を選択。
.message	100			我的心情早已决定，而且从未有过改变。
.message	110			那么……。
.message	120		嫗丂夘	「那么，我有一个请求」
.message	130		嫗丂夘	「再让我拍你一次。我想要拍摄你奔跑的样子──」
;■微笑
.transition 0 * 20
.stage	* ev02_110a07.png 0 0
;.stage	* ev02_110a02_mugai_a.png 0 0
;☆（差分を増やしてもらうこと。この切り出しを使う場合）
.message	140	kei-212_03-0003	丂宨丂	「正好呢」
.message	150		嫗丂夘	「嗯？」
.message	160	kei-212_03-0005	丂宨丂	「摄像机，拿着的吧？」
.message	170		嫗丂夘	「啊啊，那自然」
.message	180			一直都放到提包里，电池和胶卷也应该足够。
.transition 0 * 40
.stage	* ev02_110a08.png 0 0
.message	190	kei-212_03-0007	丂宨丂	「还没有跑够呢。还要再跑哦」
.message	200			新藤露出一个大大的笑容，宣言道。
.message	210	kei-212_03-0009	丂宨丂	「100米短跑，10次哦」
.message	220		嫗丂夘	「还要跑啊……。等，难道我也要跟着跑不成？」
.transition 0 * 20
.stage	* ev02_110a07_mugai_a.png 0 0
.message	230	kei-212_03-0011	丂宨丂	「不是想要拍我吗？」
.transition 0 * 20
.stage	* ev02_110a08_mugai_a.png 0 0
.message	235	kei-212_03-0012	丂宨丂	「这种程度起码做出来给我看」
;.message	230	kei-212_03-0011	丂宨丂	「わたしを撮りたいんでしょ？　それくらいはやってみせるわよね」
;.transition 0 * 20
;.stage	* ev02_110a08_mugai_a.png 0 0
.message	240			啊啊，小景的笑容好耀眼。
.message	250			虽然之后会很累人。
.message	260			但是，这也不错啊。
.message	270			只是──
.message	280			在真正的摄影再次开始之前，我还有不得不做的事情。
.panel 0
.playBGM *
.transition 0 * 10
.stage	* WHITE.png 0 0

.chain 212_04.sc
;■212_04へ。

;.end
