; ファイル: 102_02.txt
;■「景と話を続ける」を選択
.playBGM efBGM010.ogg
.transition 0 * 20
.stage	* ev01_037b01_mugai_a.png 0 0
;（挿入位置，注意。もう少し後で？）
.message	100			嘛，宫村作什么都和我无关。
.message	110			她也应该有她自己的事情，我和她的关系也没到能追根刨底的地步。
.message	120			死缠的话只会被讨厌而已吧。
.message	130			突然我的袖子被扯了一下。
.transition 0 * 20
.stage	* bgc_sch002a01_01.png 0 0 st_kei05a05.png 400
;（この表情を使う場合，目線と対象物との位置関係がおかしくなるので気になる人は気になるとも思うのだが，，，）
.message	140		丂峢丂	「嗯？」
.message	150	kei-102_02-0003	丂宨丂	「……哥哥，和宫村前辈认识的吗？」
.message	160		丂峢丂	「啊啊，稍微有过点事情。说起来，你知道关于宫村的事情吗？」
.chain 102_04.sc
;■102_04へ。

;.end
