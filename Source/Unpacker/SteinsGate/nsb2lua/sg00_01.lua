require('N2ScriptBin')
local fscr, err = Create('sg00_01')
if not fscr then
    print(err)
    return -1
end

chapter('main')
SetEntry('chapter.main')
OP_C8()
OP_D1('$GameStart')
OP_D0('INT', '1')
OP_C1()
OP_98('label.if.111')
OP_C8()
OP_68()
OP_B0('$GameName')
OP_8E()
OP_D0('INT', '1')
OP_B0('$GameContiune')
OP_8E()
OP_5B()
OP_8E()
OP_C9()
OP_CF('label.if.end11')
label('if.111')
label('if.end11')
OP_C9()
OP_D4('chapter.main')
scene('sg00_01.nss_MAIN')
OP_95('scene.sg00_01.nss_MAIN')
OP_C8()
OP_D0('STRING', 'NO_TARGET')
OP_B0('$SW_RNDMAIL_CRS')
OP_8E()
OP_D0('STRING', 'NO_TARGET')
OP_B0('$SW_RNDMAIL_MAY')
OP_8E()
OP_D0('STRING', 'NO_TARGET')
OP_B0('$SW_RNDMAIL_RUK')
OP_8E()
OP_D0('STRING', 'NO_TARGET')
OP_B0('$SW_RNDMAIL_SUZ')
OP_8E()
OP_D0('STRING', 'NO_TARGET')
OP_B0('$SW_RNDMAIL_FEI')
OP_8E()
OP_D1('$SYSTEM_skip')
OP_D1('#SYSTEM_skip_express')
OP_C6()
OP_D1('$AllRead')
OP_C6()
OP_D1('$SYSTEM_skip')
OP_D1('#SYSTEM_skip_express')
OP_C6()
OP_D1('#SYSTEM_skip_absolute')
OP_C6()
OP_C7()
OP_98('label.if.211')
OP_C8()
OP_CE('SkipOut')
OP_8E()
OP_C9()
OP_CF('label.if.end21')
label('if.211')
OP_C8()
OP_D0('STRING', '@->')
OP_D1('$GameName')
OP_A5()
OP_B0('$MainGameName')
OP_8E()
OP_CE('GameMainSet')
OP_8E()
OP_A3('$MainGameName')
OP_CE('GameMainSet2')
OP_8E()
OP_C9()
label('if.end21')
OP_D1('$GameName')
OP_B0('$PreGameName')
OP_8E()
OP_D0('STRING', 'sg01_01.nss')
OP_B0('$GameName')
OP_8E()
OP_C9()
OP_D5('scene.sg00_01.nss_MAIN')
scene('sg00_01.nss')
OP_95('scene.sg00_01.nss')
OP_C8()
OP_D0('STRING', '  Version $Revision: $')
OP_B0('$スクリプトバージョン')
OP_8E()
OP_68()
OP_B0('$構成名')
OP_8E()
OP_D1('$SYSTEM_present_process')
OP_B0('$構文名')
OP_8E()
OP_CE('SystemInit')
OP_8E()
OP_CE('InitSG')
OP_8E()
OP_D0('STRING', 'true')
OP_B0('$SYSTEM_menu_lock')
OP_8E()
OP_D0('STRING', 'START_GAME')
OP_CE('AchievementOn', 'START_GAME')
OP_8E()
OP_D0('INT', '0728')
OP_B0('$LR_DATE')
OP_8E()
OP_D0('STRING', '１．１３０２４６')
OP_B0('$DGMP')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('INT', '9000')
OP_D0('STRING', '#000000')
OP_D0('INT', '0')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_CE('ColorOut', '9000', '#000000', '0', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_24('BGBUF1')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_D0('INT', '100')
OP_D0('STRING', 'cg/bg/BG_BLACK.jpg')
OP_CE('BgLoad', 'BGBUF1', '100', 'cg/bg/BG_BLACK.jpg')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('BGBUF1', '0', '1000', 'null', 'true')
OP_8E()
OP_D0('STRING', 'OnColor*')
OP_D0('INT', '0')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_CE('FadeDelete', 'OnColor*', '0', 'null', 'true')
OP_8E()
OP_D0('INT', '1')
OP_B0('$SF_SYSTEMCHIP_HIDE')
OP_8E()
OP_D0('INT', '1')
OP_B0('$SYSTEM_menu_lock')
OP_8E()
OP_D0('INT', '1')
OP_B0('$SYSTEM_backlog_lock')
OP_8E()
OP_D0('INT', '1')
OP_B0('$SYSTEM_save_lock')
OP_8E()
OP_D0('INT', '0')
OP_B0('$SF_PhoneSD_Disp')
OP_8E()
OP_D0('INT', '1')
OP_CE('PhoneOperation', '1')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('INT', '9000')
OP_D0('STRING', '#000000')
OP_D0('INT', '0')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_CE('ColorOut', '9000', '#000000', '0', 'null', 'true')
OP_8E()
OP_D0('STRING', 'OnColor*')
OP_D0('INT', '0')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_CE('FadeDelete', 'OnColor*', '0', 'null', 'true')
OP_8E()
OP_CE('SetChapterHeadBacklog')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('INT', '9000')
OP_D0('STRING', '#000000')
OP_D0('INT', '0')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_CE('ColorOut', '9000', '#000000', '0', 'null', 'true')
OP_8E()
OP_D0('STRING', 'OnColor*')
OP_D0('INT', '0')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_CE('FadeDelete', 'OnColor*', '0', 'null', 'true')
OP_8E()
OP_D0('STRING', 'ムービー')
OP_D0('INT', '9900')
OP_D0('INT', '0')
OP_D0('INT', '0')
OP_D0('STRING', 'false')
OP_D0('STRING', 'false')
OP_D0('STRING', 'true')
OP_D0('STRING', 'prologue01')
OP_CE('CreateMovieSG', 'ムービー', '9900', '0', '0', 'false', 'false', 'true', 'prologue01')
OP_8E()
OP_D0('STRING', 'ムービー')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('ムービー', '0', '1000', 'null', 'true')
OP_8E()
OP_D0('STRING', 'ムービー')
OP_D0('STRING', 'Play')
OP_23('ムービー', 'Play')
OP_8E()
OP_CE('MovieWaitSG')
OP_8E()
OP_D0('INT', '0728')
OP_B0('$LR_DATE')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('INT', '9000')
OP_D0('STRING', '#000000')
OP_D0('INT', '0')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_CE('ColorOut', '9000', '#000000', '0', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_24('BGBUF1')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_D0('INT', '100')
OP_D0('STRING', 'cg/bg/BG_WHITE.jpg')
OP_CE('BgLoad', 'BGBUF1', '100', 'cg/bg/BG_WHITE.jpg')
OP_8E()
OP_D0('STRING', 'OnColor*')
OP_D0('INT', '0')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_CE('FadeDelete', 'OnColor*', '0', 'null', 'true')
OP_8E()
OP_D0('STRING', '絵色黒')
OP_D0('INT', '10000')
OP_D0('STRING', '#000000')
OP_CE('CreateColorSP', '絵色黒', '10000', '#000000')
OP_8E()
OP_D0('STRING', 'ムービー')
OP_D0('INT', '9900')
OP_D0('INT', '0')
OP_D0('INT', '0')
OP_D0('STRING', 'false')
OP_D0('STRING', 'false')
OP_D0('STRING', 'true')
OP_D0('STRING', 'prologue02')
OP_CE('CreateMovieSG', 'ムービー', '9900', '0', '0', 'false', 'false', 'true', 'prologue02')
OP_8E()
OP_D0('STRING', 'ムービー')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('ムービー', '0', '1000', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BGBUFEX')
OP_D0('INT', '9890')
OP_D0('STRING', 'cg/bg/bg_white.jpg')
OP_CE('BgLoad', 'BGBUFEX', '9890', 'cg/bg/bg_white.jpg')
OP_8E()
OP_D0('STRING', 'BGBUFEX')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('BGBUFEX', '0', '1000', 'null', 'true')
OP_8E()
OP_D0('STRING', '絵色黒')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'false')
OP_CE('FadeDelete', '絵色黒', '1000', 'null', 'false')
OP_8E()
OP_D0('STRING', 'ムービー')
OP_D0('STRING', 'Play')
OP_23('ムービー', 'Play')
OP_8E()
OP_CE('MovieWaitSG')
OP_8E()
OP_D0('STRING', '@ムービー*')
OP_24('@ムービー*')
OP_8E()
OP_D0('STRING', '絵色黒')
OP_24('絵色黒')
OP_8E()
OP_D0('STRING', 'false')
OP_B0('$SYSTEM_menu_lock')
OP_8E()
OP_D0('INT', '9000')
OP_D0('STRING', '#FFFFFF')
OP_D0('INT', '0')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_CE('ColorOut', '9000', '#FFFFFF', '0', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_24('BGBUF1')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_D0('INT', '100')
OP_D0('STRING', 'cg/bg/BG13A1.jpg')
OP_CE('BgLoad', 'BGBUF1', '100', 'cg/bg/BG13A1.jpg')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('BGBUF1', '0', '1000', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BG13A1')
OP_CE('SetCharaColor', 'BG13A1')
OP_8E()
OP_D0('INT', '3000')
OP_B0('$SW_PHONE_PRI')
OP_8E()
OP_D0('INT', '0')
OP_CE('PhoneOperation', '0')
OP_8E()
OP_D0('STRING', 'PhoneMode_PowerOff')
OP_B0('$SW_PHONE_MODE')
OP_8E()
OP_D0('INT', '1')
OP_B0('$SF_Phone_Open')
OP_8E()
OP_D0('INT', '266')
OP_39('266')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_24('BGBUF2')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '2200')
OP_D0('STRING', 'cg/ibg/ibg001.png')
OP_CE('BgLoad', 'BGBUF2', '2200', 'cg/ibg/ibg001.png')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '0')
OP_D0('INT', '0')
OP_D0('INT', '0')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_20('BGBUF2', '0', '0', '0', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('BGBUF2', '0', '1000', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF3')
OP_24('BGBUF3')
OP_8E()
OP_D0('STRING', 'BGBUF3')
OP_D0('INT', '900')
OP_CE('CreatePlainSP', 'BGBUF3', '900')
OP_8E()
OP_D0('STRING', 'BGBUF3')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('BGBUF3', '0', '1000', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('STRING', 'AddRender')
OP_23('BGBUF2', 'AddRender')
OP_8E()
OP_D0('STRING', 'MASKBUF2')
OP_D0('INT', '4000')
OP_D0('STRING', '#ffffff')
OP_CE('CreateColorEX', 'MASKBUF2', '4000', '#ffffff')
OP_8E()
OP_D0('STRING', 'MASKBUF2')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('MASKBUF2', '0', '1000', 'null', 'true')
OP_8E()
OP_D0('STRING', 'SE01')
OP_D0('STRING', 'sgse004l')
OP_D0('INT', '2133')
OP_D0('INT', '1000')
OP_D0('STRING', 'true')
OP_CE('SeExPlay', 'SE01', 'sgse004l', '2133', '1000', 'true')
OP_8E()
OP_D0('STRING', 'SE02')
OP_D0('STRING', 'sgse007l')
OP_D0('INT', '2133')
OP_D0('INT', '1000')
OP_D0('STRING', 'true')
OP_CE('SeExPlay', 'SE02', 'sgse007l', '2133', '1000', 'true')
OP_8E()
OP_D0('INT', '800')
OP_3A('800')
OP_8E()
OP_D0('STRING', 'OnColor*')
OP_D0('INT', '0')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_CE('FadeDelete', 'OnColor*', '0', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BGBUFEX*')
OP_24('BGBUFEX*')
OP_8E()
OP_D0('STRING', 'MASKBUF2')
OP_D0('INT', '2133')
OP_D0('STRING', 'null')
OP_D0('STRING', 'false')
OP_CE('FadeDelete', 'MASKBUF2', '2133', 'null', 'false')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '2133')
OP_D0('INT', '0')
OP_D0('STRING', 'null')
OP_D0('STRING', 'false')
OP_25('BGBUF2', '2133', '0', 'null', 'false')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '2133')
OP_D0('INT', '0')
OP_91()
OP_D0('INT', '144')
OP_D2()
OP_91()
OP_D0('STRING', 'Dxl1')
OP_D0('STRING', 'true')
OP_20('BGBUF2', '2133', '@', '@', 'Dxl1', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_24('BGBUF2')
OP_8E()
OP_D0('STRING', 'BGBUF3')
OP_24('BGBUF3')
OP_8E()
OP_D0('INT', '0')
OP_B0('$SF_SYSTEMCHIP_HIDE')
OP_8E()
OP_D0('INT', '0')
OP_B0('$SYSTEM_menu_lock')
OP_8E()
OP_D0('INT', '0')
OP_B0('$SYSTEM_backlog_lock')
OP_8E()
OP_D0('INT', '0')
OP_B0('$SYSTEM_save_lock')
OP_8E()
OP_D0('INT', '4900')
OP_B0('$SW_PHONE_PRI')
OP_8E()
SetText(
    'text00010',
    '@box00',
    [[
<PRE @box00>[text00010]
<voice name="？？？" class="VID_MAY" src="voice/MAY_0000" mode="on">
「ねぇねぇ。なにブツブツ言ってるのー？」

右耳に当てているケータイ電話。通話口からはなにも聞こえてこない。ノイズすらない。完全に無音。

夏の強烈な日射しを受けて。

ぽたりと、俺の<RUBY text="あごさき">顎先</RUBY>から汗が<RUBY text="ひとしずく">一滴</RUBY>落ち、アスファルトに染みを作った。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '294')
OP_D0('INT', '0')
OP_91()
OP_CE('PosSt', 'STBUF5', '294', '@')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '1800')
OP_D0('INT', '0')
OP_91()
OP_D0('INT', '0')
OP_91()
OP_D0('STRING', 'MAY_AMA04')
OP_CE('St', 'STBUF5', '1800', '@', '@', 'MAY_AMA04')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '267')
OP_D0('STRING', 'true')
OP_CE('FadeSt', 'STBUF5', '267', 'true')
OP_8E()
SetText(
    'text00020',
    '@box00',
    [[
<PRE @box00>[text00020]
<voice name="？？？" class="VID_MAY" src="voice/MAY_0001" mode="on">
「オカリン？　ねぇってばー」

目の前には少女。

首を傾げながら俺に呼びかけてくる。

どう見ても中学生にしか見えないあどけなさの残る顔つきからは、今まさに敵地に潜入しようとしているにもかかわらず、緊張感が<RUBY text="みじん">微塵</RUBY>も感じられない。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_D0('INT', '0')
OP_B0('$SF_Phone_Open')
OP_8E()
OP_D0('INT', '1')
OP_CE('PhoneOperation', '1')
OP_8E()
SetText(
    'text00030',
    '@box00',
    [[
<PRE @box00>[text00030]
ケータイの通話口を手で押さえてから、俺は少女に向き直り人差し指を口に添えた。

ちょっと黙れ、のゼスチャー。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '1800')
OP_D0('INT', '0')
OP_91()
OP_D0('INT', '0')
OP_91()
OP_D0('STRING', 'MAY_AMB03')
OP_CE('St', 'STBUF5', '1800', '@', '@', 'MAY_AMB03')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '267')
OP_D0('STRING', 'true')
OP_CE('FadeSt', 'STBUF5', '267', 'true')
OP_8E()
SetText(
    'text00040',
    '@box00',
    [[
<PRE @box00>[text00040]
<voice name="？？？" class="VID_MAY" src="voice/MAY_0002" mode="on">
「誰かと電話中？」

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('STRING', '@BGM*')
OP_D0('INT', '533')
OP_D0('INT', '0')
OP_D0('STRING', 'null')
OP_43('@BGM*', '533', '0', 'null')
OP_8E()
OP_D0('INT', '267')
OP_D0('STRING', 'true')
OP_CE('DeleteAllSt', '267', 'true')
OP_8E()
OP_D0('INT', '0')
OP_CE('PhoneOperation', '0')
OP_8E()
OP_D0('STRING', 'PhoneMode_PowerOff')
OP_B0('$SW_PHONE_MODE')
OP_8E()
OP_D0('INT', '1')
OP_B0('$SF_Phone_Open')
OP_8E()
SetText(
    'text00050',
    '@box00',
    [[
<PRE @box00>[text00050]
うなずいてから、改めてケータイを右耳へ。

電話の向こうからはやはり一切の音が聞こえてこなかった。

聞かれてはまずい会話をしているのだから、向こうも気を利かせて黙ったのだろう。

<voice name="倫太郎" class="VID_OKA" src="voice/OKA_0027" mode="on">
「……いや、こちらの話だ。問題ない、これより会場に潜入する」

相変わらず相手は無言。

報告を聞くだけにしたらしい。

合理的な判断だ。

この場であれこれ雑談するのは危険すぎる。

<voice name="倫太郎" class="VID_OKA" src="voice/OKA_0028" mode="on">
「ああ、ドクター<RUBY text="なかばち">中鉢</RUBY>は抜け駆けをした。たっぷりとその考えについて聞かせてもらうつもりさ」

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_D0('STRING', 'TIPS_KIKAN')
OP_CE('TipsOn', 'TIPS_KIKAN')
OP_8E()
SetText(
    'text00060',
    '@box00',
    [[
<PRE @box00>[text00060]
<voice name="倫太郎" class="VID_OKA" src="voice/OKA_0029" mode="on">
「……なに！？　“<FONT incolor="#ff7080" outcolor="#000000">機関</FONT>”が動き出しているだと！？」

俺は目を見開き、驚いたような声をあげてみた。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '294')
OP_D0('INT', '0')
OP_91()
OP_CE('PosSt', 'STBUF5', '294', '@')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '1800')
OP_D0('INT', '0')
OP_91()
OP_D0('INT', '0')
OP_91()
OP_D0('STRING', 'MAY_AMB02')
OP_CE('St', 'STBUF5', '1800', '@', '@', 'MAY_AMB02')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '133')
OP_D0('STRING', 'true')
OP_CE('FadeSt', 'STBUF5', '133', 'true')
OP_8E()
OP_D0('STRING', '@STBUF5*')
OP_D0('INT', '150')
OP_D0('INT', '10')
OP_D0('INT', '6')
OP_D0('INT', '0')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_28('@STBUF5*', '150', '10', '6', '0', '0', '1000', 'null', 'true')
OP_8E()
SetText(
    'text00070',
    '@box00',
    [[
<PRE @box00>[text00070]
少女も、こちらに合わせてビクッと身をすくませている。

というか、こっちをじっと見てるんじゃない。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('INT', '267')
OP_D0('STRING', 'true')
OP_CE('DeleteAllSt', '267', 'true')
OP_8E()
SetText(
    'text00080',
    '@box00',
    [[
<PRE @box00>[text00080]
俺はすぐに深々とため息をつき、こめかみを指で押さえながら小さく首を振った。

<voice name="倫太郎" class="VID_OKA" src="voice/OKA_0030" mode="on">
「そうか、それが<RUBY text="シュタインズゲート">運命石の扉</RUBY>の選択か。エル・プサイ・コングルゥ」

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_D0('INT', '0')
OP_B0('$SF_Phone_Open')
OP_8E()
OP_D0('INT', '1')
OP_CE('PhoneOperation', '1')
OP_8E()
SetText(
    'text00090',
    '@box00',
    [[
<PRE @box00>[text00090]
別れの合い言葉を最後に、深刻な顔のままケータイを耳から離して、懐にしまった。

<RUBY text="シュタインズゲート">運命石の扉</RUBY>。

それはいわば“神々の意志”あるいは“運命”と同じ意味を表す。

その存在を知る者は、世界中でも数えるほどだろう。

さてと、それでは早速、潜入するとしよう。

俺は駅のすぐ隣にあるラジ館に向かって足を踏み出した。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('STRING', 'SE01')
OP_D0('INT', '1066')
OP_D0('INT', '0')
OP_D0('STRING', 'null')
OP_43('SE01', '1066', '0', 'null')
OP_8E()
OP_D0('STRING', 'SE02')
OP_D0('INT', '1066')
OP_D0('INT', '0')
OP_D0('STRING', 'null')
OP_43('SE02', '1066', '0', 'null')
OP_8E()
OP_D0('INT', '9000')
OP_D0('STRING', '#000000')
OP_D0('INT', '533')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_CE('ColorOut', '9000', '#000000', '533', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_24('BGBUF1')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_D0('INT', '100')
OP_D0('STRING', 'cg/bg/BG07A1.jpg')
OP_CE('BgLoad', 'BGBUF1', '100', 'cg/bg/BG07A1.jpg')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('BGBUF1', '0', '1000', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BG07A1')
OP_CE('SetCharaColor', 'BG07A1')
OP_8E()
OP_D0('INT', '266')
OP_39('266')
OP_8E()
OP_D0('INT', '800')
OP_3A('800')
OP_8E()
OP_D0('STRING', '@BGM07')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'true')
OP_CE('SoundPlay', '@BGM07', '0', '1000', 'true')
OP_8E()
OP_D0('STRING', 'OnColor*')
OP_D0('INT', '533')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_CE('FadeDelete', 'OnColor*', '533', 'null', 'true')
OP_8E()
SetText(
    'text00100',
    '@box00',
    [[
<PRE @box00>[text00100]
敵地への潜入だ、バカ正直に正面から突入するような愚を、俺は冒したりはしない。

エレベータやエスカレータは使わず、階段を上って最上階である８階に向かう。

だが７階まで来たところで力尽きた。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
SetText(
    'text00110',
    '@box00',
    [[
<PRE @box00>[text00110]
<voice name="まゆり" class="VID_MAY" src="voice/MAY_0003" mode="on">
「さっき、ケータイで誰と話してたのー？」

俺の後ろをついてくる少女――<RUBY text="しいな">椎名</RUBY>まゆりが、息を切らした様子もなくそう聞いてきた。

俺は階段を上り切ったところで膝に手を置き、一息つく。

階段を使うべきじゃなかったかもしれん……。キツすぎ……。

額に滲む汗を手で拭いつつ、まゆりへと向き直った。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '294')
OP_D0('INT', '0')
OP_91()
OP_CE('PosSt', 'STBUF5', '294', '@')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '1800')
OP_D0('INT', '0')
OP_91()
OP_D0('INT', '0')
OP_91()
OP_D0('STRING', 'MAY_ALA01')
OP_CE('St', 'STBUF5', '1800', '@', '@', 'MAY_ALA01')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '267')
OP_D0('STRING', 'true')
OP_CE('FadeSt', 'STBUF5', '267', 'true')
OP_8E()
SetText(
    'text00120',
    '@box00',
    [[
<PRE @box00>[text00120]
<voice name="倫太郎" class="VID_OKA" src="voice/OKA_0031" mode="on">
「聞くな。それがまゆりのためでもある」

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '1800')
OP_D0('INT', '0')
OP_91()
OP_D0('INT', '0')
OP_91()
OP_D0('STRING', 'MAY_ALA02')
OP_CE('St', 'STBUF5', '1800', '@', '@', 'MAY_ALA02')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '267')
OP_D0('STRING', 'true')
OP_CE('FadeSt', 'STBUF5', '267', 'true')
OP_8E()
SetText(
    'text00130',
    '@box00',
    [[
<PRE @box00>[text00130]
<voice name="まゆり" class="VID_MAY" src="voice/MAY_0004" mode="on">
「そうなんだー。オカリン、ありがとー」

まゆりは嬉しそうに微笑んだ。

こいつは実に物分かりがいい。

俺の立場もわきまえてくれていて、深く突っ込んでくることもない。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_24('BGBUF2')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '990')
OP_D0('STRING', 'cg/bg/BG_BLACK.jpg')
OP_CE('BgLoad', 'BGBUF2', '990', 'cg/bg/BG_BLACK.jpg')
OP_8E()
OP_D0('STRING', 'MASKBUF2')
OP_D0('INT', '910')
OP_D0('STRING', '#000000')
OP_CE('CreateColorEX', 'MASKBUF2', '910', '#000000')
OP_8E()
OP_D0('STRING', 'MASKBUF2')
OP_D0('INT', '0')
OP_D0('INT', '0')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('MASKBUF2', '0', '0', 'null', 'true')
OP_8E()
OP_D0('STRING', 'GRASHADE')
OP_24('GRASHADE')
OP_8E()
OP_D0('STRING', 'GRASHADE')
OP_D0('INT', '900')
OP_D0('STRING', 'SEMIHEAVY')
OP_CE('SetShadeSG', 'GRASHADE', '900', 'SEMIHEAVY')
OP_8E()
OP_D0('STRING', 'MASKBUF2')
OP_D0('INT', '1066')
OP_D0('INT', '500')
OP_D0('STRING', 'Axl2')
OP_D0('STRING', 'false')
OP_25('MASKBUF2', '1066', '500', 'Axl2', 'false')
OP_8E()
OP_D0('STRING', 'GRASHADE')
OP_D0('INT', '1066')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'false')
OP_25('GRASHADE', '1066', '1000', 'null', 'false')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('BGBUF2', '0', '1000', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '1066')
OP_D0('INT', '0')
OP_D0('INT', '250')
OP_D0('INT', '250')
OP_D0('STRING', 'DxlAuto')
OP_D0('STRING', 'mask17')
OP_D0('STRING', 'true')
OP_D0('STRING', 'true')
OP_CE('DrawTransitionSG', 'BGBUF2', '1066', '0', '250', '250', 'DxlAuto', 'mask17', 'true', 'true')
OP_8E()
SetText(
    'text00140',
    '@box00',
    [[
<PRE @box00>[text00140]
彼女は俺の幼なじみである。

年齢は俺より２つ下――１６歳の女子高生なので、幼なじみと言うより妹のような立場に近い。

家が近所なので昔からよく世話をしてやっていた。

まゆりには、<RUBY text="シュタインズゲート">運命石の扉</RUBY>の鍵という過酷な宿命を背負うことのできる素質があるのではないか。以前の俺はそんなことを考えたりもしたが、今はそれを改めている。

彼女にはいつまでも普通でいてほしい。

それが、今の俺のささやかな願いだ。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('STRING', 'MASKBUF2')
OP_D0('INT', '1066')
OP_D0('STRING', 'null')
OP_D0('STRING', 'false')
OP_CE('FadeDelete', 'MASKBUF2', '1066', 'null', 'false')
OP_8E()
OP_D0('STRING', 'GRASHADE')
OP_D0('INT', '1066')
OP_D0('STRING', 'null')
OP_D0('STRING', 'false')
OP_CE('FadeDelete', 'GRASHADE', '1066', 'null', 'false')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '1066')
OP_D0('INT', '250')
OP_D0('INT', '0')
OP_D0('INT', '250')
OP_D0('STRING', 'null')
OP_D0('STRING', 'mask17')
OP_D0('STRING', 'true')
OP_D0('STRING', 'true')
OP_CE('DrawTransitionSG', 'BGBUF2', '1066', '250', '0', '250', 'null', 'mask17', 'true', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_24('BGBUF2')
OP_8E()
OP_D0('STRING', 'GRASHADE')
OP_24('GRASHADE')
OP_8E()
OP_D0('INT', '267')
OP_D0('STRING', 'true')
OP_CE('DeleteAllSt', '267', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_D0('INT', '1066')
OP_D0('INT', '2000')
OP_D0('INT', '2000')
OP_D0('STRING', 'AxlDxl')
OP_D0('STRING', 'true')
OP_D0('STRING', 'Smoothing')
OP_CE('ZoomSG', 'BGBUF1', '1066', '2000', '2000', 'AxlDxl', 'true', 'Smoothing')
OP_8E()
OP_D0('INT', '266')
OP_3A('266')
OP_8E()
OP_D0('STRING', 'MASKBUF2')
OP_D0('INT', '5100')
OP_D0('STRING', '#000000')
OP_CE('CreateColorEX', 'MASKBUF2', '5100', '#000000')
OP_8E()
OP_D0('STRING', 'MASKBUF2')
OP_D0('INT', '1066')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'false')
OP_25('MASKBUF2', '1066', '1000', 'null', 'false')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_D0('INT', '1066')
OP_D0('INT', '512')
OP_91()
OP_D0('INT', '288')
OP_91()
OP_D0('STRING', 'AxlDxl')
OP_D0('STRING', 'true')
OP_20('BGBUF1', '1066', '@', '@', 'AxlDxl', 'true')
OP_8E()
OP_D0('INT', '9000')
OP_D0('STRING', '#000000')
OP_D0('INT', '0')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_CE('ColorOut', '9000', '#000000', '0', 'null', 'true')
OP_8E()
OP_D0('STRING', 'MASKBUF2')
OP_D0('INT', '5100')
OP_D0('STRING', '#000000')
OP_CE('CreateColorEX', 'MASKBUF2', '5100', '#000000')
OP_8E()
OP_D0('STRING', 'MASKBUF2')
OP_D0('INT', '0')
OP_D0('INT', '0')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('MASKBUF2', '0', '0', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_24('BGBUF1')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_D0('INT', '100')
OP_D0('STRING', 'cg/bg/BG06A4.jpg')
OP_CE('BgLoad', 'BGBUF1', '100', 'cg/bg/BG06A4.jpg')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('BGBUF1', '0', '1000', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BG06A4')
OP_CE('SetCharaColor', 'BG06A4')
OP_8E()
OP_D0('INT', '533')
OP_3A('533')
OP_8E()
OP_D0('STRING', 'OnColor*')
OP_D0('INT', '533')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_CE('FadeDelete', 'OnColor*', '533', 'null', 'true')
OP_8E()
SetText(
    'text00150',
    '@box00',
    [[
<PRE @box00>[text00150]
８階まで上がって会場に入ると、安っぽいセットが作られていた。

ドクター中鉢タイムマシン発明成功記念会見と銘打たれている。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '294')
OP_D0('INT', '0')
OP_91()
OP_CE('PosSt', 'STBUF5', '294', '@')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '1800')
OP_D0('INT', '0')
OP_91()
OP_D0('INT', '0')
OP_91()
OP_D0('STRING', 'MAY_ALA01')
OP_CE('St', 'STBUF5', '1800', '@', '@', 'MAY_ALA01')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '267')
OP_D0('STRING', 'true')
OP_CE('FadeSt', 'STBUF5', '267', 'true')
OP_8E()
SetText(
    'text00160',
    '@box00',
    [[
<PRE @box00>[text00160]
<voice name="まゆり" class="VID_MAY" src="voice/MAY_0005" mode="on">
「それよりオカリンオカリン」

オカリンとさっきからやたら連呼されているが、それは別に俺の本名でもなければコードネームでもない。俺自身があまり気に入っていないあだ名というヤツだ。

<voice name="倫太郎" class="VID_OKA" src="voice/OKA_0032" mode="on">
「まゆりよ、いつも言っているだろう。俺のことをオカリンと呼ぶなと」

<voice name="まゆり" class="VID_MAY" src="voice/MAY_0006" mode="on">
「えー？　でも昔からそう呼んでたよ？」

<voice name="倫太郎" class="VID_OKA" src="voice/OKA_0033" mode="on">
「それは昔の話だ。今の俺は“<RUBY text="ほうおういん">鳳凰院</RUBY><RUBY text="きょうま">凶真</RUBY>”。世界中の秘密組織から狙われる、狂気のマッドサイエンティストだ。フゥーハハハ！」

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '1800')
OP_D0('INT', '0')
OP_91()
OP_D0('INT', '0')
OP_91()
OP_D0('STRING', 'MAY_ALA04')
OP_CE('St', 'STBUF5', '1800', '@', '@', 'MAY_ALA04')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '267')
OP_D0('STRING', 'true')
OP_CE('FadeSt', 'STBUF5', '267', 'true')
OP_8E()
SetText(
    'text00170',
    '@box00',
    [[
<PRE @box00>[text00170]
<voice name="まゆり" class="VID_MAY" src="voice/MAY_0007" mode="on">
「だって、難しくて覚えられないし」

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_D0('STRING', 'TIPS_MANA')
OP_CE('TipsOn', 'TIPS_MANA')
OP_8E()
SetText(
    'text00180',
    '@box00',
    [[
<PRE @box00>[text00180]
とにかく鳳凰院凶真は俺の<FONT incolor="#ff7080" outcolor="#000000"><RUBY text="まな">真名</RUBY></FONT>なのだ。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '1800')
OP_D0('INT', '0')
OP_91()
OP_D0('INT', '0')
OP_91()
OP_D0('STRING', 'MAY_ALA02')
OP_CE('St', 'STBUF5', '1800', '@', '@', 'MAY_ALA02')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '267')
OP_D0('STRING', 'true')
OP_CE('FadeSt', 'STBUF5', '267', 'true')
OP_8E()
SetText(
    'text00190',
    '@box00',
    [[
<PRE @box00>[text00190]
<voice name="まゆり" class="VID_MAY" src="voice/MAY_0008" mode="on">
「それに、<RUBY text="おかべ">岡部</RUBY><RUBY text="りんたろう">倫太郎</RUBY>と１文字も合ってないよー？　おかしいね、えっへへー」

うーむ、実に幸せそうに笑っていらっしゃいやがる。

ちなみに岡部倫太郎という俺の本名は、間抜けな感じがして好きではない。

なのでそこから取ったあだ名である“オカリン”も同じく嫌いなのだ。

というかオカリンって。

銭湯に置いてある黄色い桶みたいじゃないか。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '1800')
OP_D0('INT', '0')
OP_91()
OP_D0('INT', '0')
OP_91()
OP_D0('STRING', 'MAY_ALB01')
OP_CE('St', 'STBUF5', '1800', '@', '@', 'MAY_ALB01')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '267')
OP_D0('STRING', 'true')
OP_CE('FadeSt', 'STBUF5', '267', 'true')
OP_8E()
SetText(
    'text00200',
    '@box00',
    [[
<PRE @box00>[text00200]
<voice name="まゆり" class="VID_MAY" src="voice/MAY_0009" mode="on">
「でね、オカリン。えっと、教えてほしいんだけど」

どうやらまゆりには言っても通じないようだった。

かれこれ５年は言い続けてきてこれだから、半ば諦めてはいるが。

<voice name="まゆり" class="VID_MAY" src="voice/MAY_0010" mode="on">
「これからここで、なにが始まるのー？」

<voice name="倫太郎" class="VID_OKA" src="voice/OKA_0034" mode="on">
「お前は、それも知らずここまで俺についてきたというのか」

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '1800')
OP_D0('INT', '0')
OP_91()
OP_D0('INT', '0')
OP_91()
OP_D0('STRING', 'MAY_ALA02')
OP_CE('St', 'STBUF5', '1800', '@', '@', 'MAY_ALA02')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '267')
OP_D0('STRING', 'true')
OP_CE('FadeSt', 'STBUF5', '267', 'true')
OP_8E()
SetText(
    'text00210',
    '@box00',
    [[
<PRE @box00>[text00210]
<voice name="まゆり" class="VID_MAY" src="voice/MAY_0011" mode="on">
「うん」

にこやかにうなずいている。

ここは東京、秋葉原にあるラジ館。

その８階は、イベントスペースになっている。

<voice name="倫太郎" class="VID_OKA" src="voice/OKA_0035" mode="on">
「これからここで始まるのは、ドクター中鉢の記者会見だ」

ドクター中鉢というのは発明家である。テレビなどにもよく登場する有名な人物で、特許数もそれなりに持っている。とはいえ世間一般の目からは所詮“色モノ”としか見られていないが。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '1800')
OP_D0('INT', '0')
OP_91()
OP_D0('INT', '0')
OP_91()
OP_D0('STRING', 'MAY_ALB03')
OP_CE('St', 'STBUF5', '1800', '@', '@', 'MAY_ALB03')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '267')
OP_D0('STRING', 'true')
OP_CE('FadeSt', 'STBUF5', '267', 'true')
OP_8E()
SetText(
    'text00220',
    '@box00',
    [[
<PRE @box00>[text00220]
<voice name="まゆり" class="VID_MAY" src="voice/MAY_0012" mode="on">
「記者会見？　でもー、記者さんなんて見当たらない気がするよ？」

まゆりの言う通りだった。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('INT', '267')
OP_D0('STRING', 'true')
OP_CE('DeleteAllSt', '267', 'true')
OP_8E()
SetText(
    'text00230',
    '@box00',
    [[
<PRE @box00>[text00230]
試しに奥にある会場をのぞいてみたが、記者らしい人間もカメラマンらしき人間も、１人としてここにはいない。その時点で記者会見ではなくただの発表会と化してしまっている。

会場にいるのは、俺も含めて手持ちぶさたで突っ立っている１０人程度の男たち。

そう、たったの１０人。

中鉢の知名度はそれなりのはずだし、タイムマシン開発に成功したという触れ込みなら、もっと集まってもいいはずだが。

<voice name="倫太郎" class="VID_OKA" src="voice/OKA_0036" mode="on">
「あるいは、“機関”によるなんらかの妨害を受けたのかもしれないな」

俺は自嘲気味につぶやき、わざとらしく唇を歪めた。

中鉢は元々――面識はないが――俺と同じ側にいる人間だったはずだ。

しかしそれを放棄して野に下った。

このタイミングを“機関”が見逃すはずがない。

<voice name="倫太郎" class="VID_OKA" src="voice/OKA_0037" mode="on">
「巻き込まれるのは、勘弁だがな」

とはいえ、ヤツがなにを語るのかには興味がある。

だからこそ俺はわざわざ夏休みの昼下がりという貴重な時間を割いて、ここに来たのだ。

俺がつぶやいた独り言に、まゆりはしばらく考え込んだ後、かなり間を置いてまた首を傾げた。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('STRING', 'STBUF8')
OP_D0('INT', '294')
OP_D0('INT', '0')
OP_91()
OP_CE('PosSt', 'STBUF8', '294', '@')
OP_8E()
OP_D0('STRING', 'STBUF8')
OP_D0('INT', '1200')
OP_D0('INT', '0')
OP_91()
OP_D0('INT', '0')
OP_91()
OP_D0('STRING', 'MAY_ALB03')
OP_CE('St', 'STBUF8', '1200', '@', '@', 'MAY_ALB03')
OP_8E()
OP_D0('STRING', 'STBUF8')
OP_D0('INT', '267')
OP_D0('STRING', 'true')
OP_CE('FadeSt', 'STBUF8', '267', 'true')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('STRING', '座標')
OP_D0('STRING', 'xx')
OP_DE('$StA', '3')
OP_D0('STRING', 'STBUF8')
OP_D0('STRING', '座標')
OP_D0('STRING', 'xx')
OP_DE('$StA', '3')
OP_B0('__array_variable__')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('STRING', '座標')
OP_D0('STRING', 'xx')
OP_DE('$StA', '3')
OP_B0('$SgMoveX')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D1('$SgMoveX')
OP_D0('INT', '0')
OP_91()
OP_CE('PosSt', 'STBUF5', '$SgMoveX', '@')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '1800')
OP_D0('INT', '0')
OP_91()
OP_D0('INT', '0')
OP_91()
OP_D0('STRING', 'MAY_ALA02')
OP_CE('St', 'STBUF5', '1800', '@', '@', 'MAY_ALA02')
OP_8E()
OP_D0('STRING', 'ProFaceChange')
OP_D0('STRING', 'sg00_01_Thd_IM_MAY_01')
OP_CE('CreateProcessSG', 'ProFaceChange', 'sg00_01_Thd_IM_MAY_01')
OP_8E()
OP_D0('STRING', 'ProFaceChange')
OP_D0('STRING', 'Start')
OP_23('ProFaceChange', 'Start')
OP_8E()
SetText(
    'text00240',
    '@box00',
    [[
<PRE @box00>[text00240]
<voice name="まゆり" class="VID_MAY" src="voice/MAY_0013" mode="on">
「巻き巻きトカゲ？　あ、それを言うならエリ巻きトカゲだねー。えっへへー」

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_D0('STRING', 'ProFaceChange')
OP_D0('INT', '5000')
OP_CE('ProcessRequest', 'ProFaceChange', '5000')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '1800')
OP_D0('INT', '0')
OP_91()
OP_D0('INT', '0')
OP_91()
OP_D0('STRING', 'MAY_ALA02')
OP_CE('St', 'STBUF5', '1800', '@', '@', 'MAY_ALA02')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '0')
OP_D0('STRING', 'true')
OP_CE('FadeSt', 'STBUF5', '0', 'true')
OP_8E()
OP_CE('ProcessRequestDelete')
OP_8E()
SetText(
    'text00250',
    '@box00',
    [[
<PRE @box00>[text00250]
俺はため息をついてしまう。

１人ボケツッコミ笑いとは実に脳天気なことだ。

まあ、まゆりは昔からこんな感じだが。

<voice name="倫太郎" class="VID_OKA" src="voice/OKA_0038" mode="on">
「まゆり、気を付けろ。おそらくこの記者会見、なんらかの事件が起き――」

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('STRING', '@BGM*')
OP_D0('INT', '1')
OP_D0('INT', '0')
OP_D0('STRING', 'null')
OP_43('@BGM*', '1', '0', 'null')
OP_8E()
OP_D0('INT', '267')
OP_D0('STRING', 'true')
OP_CE('DeleteAllSt', '267', 'true')
OP_8E()
OP_D0('STRING', 'SE01')
OP_D0('STRING', 'SGSE002')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'false')
OP_CE('SePlay', 'SE01', 'SGSE002', '0', '1000', 'false')
OP_8E()
OP_D0('INT', '1066')
OP_3A('1066')
OP_8E()
OP_D0('STRING', 'SE02')
OP_D0('STRING', 'SGSE115')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'false')
OP_CE('SePlay', 'SE02', 'SGSE115', '0', '1000', 'false')
OP_8E()
OP_D0('INT', '2133')
OP_3A('2133')
OP_8E()
SetText(
    'text00260',
    '@box00',
    [[
<PRE @box00>[text00260]
言っているそばから来た！

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_D0('STRING', 'TIPS_EMR')
OP_CE('TipsOn', 'TIPS_EMR')
OP_8E()
SetText(
    'text00270',
    '@box00',
    [[
<PRE @box00>[text00270]
こ、この音はなんだ！？　<FONT incolor="#ff7080" outcolor="#000000">電磁波</FONT>攻撃か！？

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('STRING', 'SE01')
OP_D0('STRING', 'SGSE003')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'false')
OP_CE('SePlay', 'SE01', 'SGSE003', '0', '1000', 'false')
OP_8E()
OP_D0('INT', '5000')
OP_D0('INT', '19')
OP_D0('INT', '6')
OP_D0('STRING', 'DxlAuto')
OP_D0('STRING', 'true')
OP_CE('AllShake', '5000', '19', '6', 'DxlAuto', 'true')
OP_8E()
OP_D0('STRING', 'SE01')
OP_CE('WaitPlayHalfSG', 'SE01')
OP_8E()
OP_D0('STRING', '@BGM08')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'true')
OP_CE('SoundPlay', '@BGM08', '0', '1000', 'true')
OP_8E()
SetText(
    'text00280',
    '@box00',
    [[
<PRE @box00>[text00280]
わずかに足下が揺れた。

確かな衝撃。

上からだ。

だが俺たちがいる８階は最上階。

ここより上となると、屋上しかない。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '294')
OP_D0('INT', '0')
OP_91()
OP_CE('PosSt', 'STBUF5', '294', '@')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '1800')
OP_D0('INT', '0')
OP_91()
OP_D0('INT', '0')
OP_91()
OP_D0('STRING', 'MAY_ALB03')
OP_CE('St', 'STBUF5', '1800', '@', '@', 'MAY_ALB03')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '267')
OP_D0('STRING', 'true')
OP_CE('FadeSt', 'STBUF5', '267', 'true')
OP_8E()
SetText(
    'text00290',
    '@box00',
    [[
<PRE @box00>[text00290]
<voice name="まゆり" class="VID_MAY" src="voice/MAY_0014" mode="on">
「地震かなぁ？　震度２？　マグニチュード２？　震度とマグニチュードってどう違うんだっけー……」

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('INT', '267')
OP_D0('STRING', 'true')
OP_CE('DeleteAllSt', '267', 'true')
OP_8E()
SetText(
    'text00300',
    '@box00',
    [[
<PRE @box00>[text00300]
悩み多き少女のことは放っておく。

胸騒ぎを覚え、俺は会場を飛び出した。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('INT', '9000')
OP_D0('STRING', '#000000')
OP_D0('INT', '533')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_CE('ColorOut', '9000', '#000000', '533', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_24('BGBUF1')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_D0('INT', '100')
OP_D0('STRING', 'cg/bg/BG_BLACK.jpg')
OP_CE('BgLoad', 'BGBUF1', '100', 'cg/bg/BG_BLACK.jpg')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('BGBUF1', '0', '1000', 'null', 'true')
OP_8E()
OP_D0('STRING', 'OnColor*')
OP_D0('INT', '0')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_CE('FadeDelete', 'OnColor*', '0', 'null', 'true')
OP_8E()
SetText(
    'text00310',
    '@box00',
    [[
<PRE @box00>[text00310]
立ち入り禁止なのを無視して、屋上への階段を駆け上がる。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('INT', '9000')
OP_D0('STRING', '#000000')
OP_D0('INT', '0')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_CE('ColorOut', '9000', '#000000', '0', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_24('BGBUF1')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_D0('INT', '100')
OP_D0('STRING', 'cg/bgef/bg11a2_ove.jpg')
OP_CE('BgLoad', 'BGBUF1', '100', 'cg/bgef/bg11a2_ove.jpg')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('BGBUF1', '0', '1000', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BG11A2')
OP_CE('SetCharaColor', 'BG11A2')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_24('BGBUF2')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '2010')
OP_D0('STRING', 'cg/bg/BG_BLACK.jpg')
OP_CE('BgLoad', 'BGBUF2', '2010', 'cg/bg/BG_BLACK.jpg')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('BGBUF2', '0', '1000', 'null', 'true')
OP_8E()
OP_D0('STRING', 'MASKBUF2')
OP_D0('INT', '2000')
OP_D0('STRING', '#ffffff')
OP_CE('CreateColorEX', 'MASKBUF2', '2000', '#ffffff')
OP_8E()
OP_D0('STRING', 'MASKBUF2')
OP_D0('INT', '0')
OP_D0('INT', '0')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('MASKBUF2', '0', '0', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('INT', '700')
OP_D0('INT', '250')
OP_D0('STRING', 'null')
OP_D0('STRING', 'mask02')
OP_D0('STRING', 'true')
OP_D0('STRING', 'true')
OP_CE('DrawTransitionSG', 'BGBUF2', '0', '1000', '700', '250', 'null', 'mask02', 'true', 'true')
OP_8E()
OP_D0('STRING', 'ムービー')
OP_D0('INT', '1900')
OP_D0('INT', '0')
OP_D0('INT', '0')
OP_D0('STRING', 'true')
OP_D0('STRING', 'true')
OP_D0('STRING', 'false')
OP_D0('STRING', 'imv038')
OP_CE('CreateBGMovieSG', 'ムービー', '1900', '0', '0', 'true', 'true', 'false', 'imv038')
OP_8E()
OP_D0('STRING', 'ムービー')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('ムービー', '0', '1000', 'null', 'true')
OP_8E()
OP_D0('STRING', 'ムービー')
OP_D0('STRING', 'Play')
OP_23('ムービー', 'Play')
OP_8E()
OP_D0('STRING', 'SE01')
OP_D0('STRING', 'SGSE084')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'false')
OP_CE('SePlay', 'SE01', 'SGSE084', '0', '1000', 'false')
OP_8E()
OP_D0('STRING', 'OnColor*')
OP_D0('INT', '533')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_CE('FadeDelete', 'OnColor*', '533', 'null', 'true')
OP_8E()
SetText(
    'text00320',
    '@box00',
    [[
<PRE @box00>[text00320]
屋上の扉はなぜか開いていた。というか、鍵が壊されていた。

扉を開けると、見渡さなくても黒い煙が立ちのぼっているのが見えた。

それに、なぜか虹色の燐光のようなものがキラキラと空中を舞っている。

<voice name="倫太郎" class="VID_OKA" src="voice/OKA_0039" mode="on">
「爆発……だと！？」

カッコつけて驚いてみたけど、え、ウソ、マジで爆発？

まずい、胸が高鳴ってきた。

ドキドキする。

ええと、ど、どうするべきだろう。

逃げた方がいい？

というかなんで爆発？　テロ？

いや、そんなものではないような気がする。

なぜなら、俺の目の前――屋上のガランとしたスペースのど真ん中に、奇妙な物体が鎮座していたからだ。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '533')
OP_D0('INT', '700')
OP_D0('INT', '0')
OP_D0('INT', '250')
OP_D0('STRING', 'null')
OP_D0('STRING', 'mask02')
OP_D0('STRING', 'true')
OP_D0('STRING', 'false')
OP_CE('DrawTransitionSG', 'BGBUF2', '533', '700', '0', '250', 'null', 'mask02', 'true', 'false')
OP_8E()
OP_D0('INT', '2000')
OP_D0('STRING', '#FFFFFF')
OP_D0('INT', '533')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_CE('ColorOut', '2000', '#FFFFFF', '533', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_24('BGBUF2')
OP_8E()
OP_D0('STRING', 'BGBUF3')
OP_24('BGBUF3')
OP_8E()
OP_D0('STRING', 'MASKBUF2')
OP_24('MASKBUF2')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_24('BGBUF1')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_D0('INT', '100')
OP_D0('STRING', 'cg/bg/BG11A2.jpg')
OP_CE('BgLoad', 'BGBUF1', '100', 'cg/bg/BG11A2.jpg')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('BGBUF1', '0', '1000', 'null', 'true')
OP_8E()
OP_D0('INT', '200')
OP_3A('200')
OP_8E()
OP_D0('STRING', 'OnColor*')
OP_D0('INT', '533')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_CE('FadeDelete', 'OnColor*', '533', 'null', 'true')
OP_8E()
SetText(
    'text00330',
    '@box00',
    [[
<PRE @box00>[text00330]
<voice name="倫太郎" class="VID_OKA" src="voice/OKA_0040" mode="on">
「なんだ……これは？」

そこには謎の機器が鎮座していた。

かなり大きい。高さは３メートル以上あるのではないだろうか。

これは……人工衛星？

煙や燐光、それにさっきの揺れの原因は、これなのか？

こんな物、誰がここに置いたんだろう？

それとも、中鉢が用意したものだとでもいうのか？　今日の会見と関係があったりする？

だが、もし仮にそうだとして、いったいここまでどうやって持ってきたんだ？

ここは８階建てビルの屋上だぞ？

頭の中は疑問だらけだった。

そしてその自問には、当然ながら答えは出ない。

謎の機器に近付くべきかどうか<RUBY text="ちゅうちょ">躊躇</RUBY>していると、俺に続くようにして、何人かが――おそらくラジ館の関係者か、記者会見の係員か――階段を上がってきた。

そして誰もが、俺と同じように困惑した顔をする。

<voice name="女" class="VID_SUZ" src="voice/SUZ_0000" mode="on">
「近寄らないでくださーい！」

と、係員のうちの１人と思われる女が両手を大きく振りながら、俺たちの前へと歩み出てきた。

<voice name="女" class="VID_SUZ" src="voice/SUZ_0001" mode="on">
「記者会見は予定通り始めますので、もうしばらくお待ちくださーい！」

なにかを隠そうとしている？

対応がやけに素早い。俺を人工衛星らしき物体から遠ざけたいらしい。

<voice name="倫太郎" class="VID_OKA" src="voice/OKA_0041" mode="on">
「これは匂う。陰謀の匂いだ。なにを隠したいんだ？　さっきの爆発はなんだ？」

ブツブツと声に出して考えを巡らせてみる。

気になる……。

気になるが、これ以上近付く危険は避けた方がいい。

決してビビったわけではないぞ。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('INT', '9000')
OP_D0('STRING', '#000000')
OP_D0('INT', '533')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_CE('ColorOut', '9000', '#000000', '533', 'null', 'true')
OP_8E()
OP_D0('STRING', '@ムービー*')
OP_24('@ムービー*')
OP_8E()
OP_D0('STRING', 'ムービー')
OP_D0('INT', '0')
OP_D0('INT', '0')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('ムービー', '0', '0', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_24('BGBUF1')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_D0('INT', '100')
OP_D0('STRING', 'cg/bg/BG_BLACK.jpg')
OP_CE('BgLoad', 'BGBUF1', '100', 'cg/bg/BG_BLACK.jpg')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('BGBUF1', '0', '1000', 'null', 'true')
OP_8E()
OP_D0('STRING', 'OnColor*')
OP_D0('INT', '0')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_CE('FadeDelete', 'OnColor*', '0', 'null', 'true')
OP_8E()
SetText(
    'text00340',
    '@box00',
    [[
<PRE @box00>[text00340]
係員に誘導されるままに８階に戻る。

まゆりの姿がなかった。イベント会場にもいない。

探してみると、７階の踊り場にいた。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('INT', '9000')
OP_D0('STRING', '#000000')
OP_D0('INT', '0')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_CE('ColorOut', '9000', '#000000', '0', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_24('BGBUF1')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_D0('INT', '100')
OP_D0('STRING', 'cg/bg/BG07A1.jpg')
OP_CE('BgLoad', 'BGBUF1', '100', 'cg/bg/BG07A1.jpg')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('BGBUF1', '0', '1000', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BG07A1')
OP_CE('SetCharaColor', 'BG07A1')
OP_8E()
OP_D0('STRING', 'OnColor*')
OP_D0('INT', '533')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_CE('FadeDelete', 'OnColor*', '533', 'null', 'true')
OP_8E()
OP_D0('STRING', 'TIPS_GACHA')
OP_CE('TipsOn', 'TIPS_GACHA')
OP_8E()
SetText(
    'text00350',
    '@box00',
    [[
<PRE @box00>[text00350]
日本におけるＰＣ発祥の地を示すプレートがあるその横に、<FONT incolor="#ff7080" outcolor="#000000">カプセルトイ</FONT>がずらっと並んでいる。

それを物欲しそうな顔で眺めていた。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_D0('INT', '0')
OP_CE('PhoneOperation', '0')
OP_8E()
OP_D0('STRING', 'PhoneMode_PowerOff')
OP_B0('$SW_PHONE_MODE')
OP_8E()
OP_D0('INT', '1')
OP_B0('$SF_Phone_Open')
OP_8E()
SetText(
    'text00360',
    '@box00',
    [[
<PRE @box00>[text00360]
ひとまずホッと一安心してから、俺はケータイを取り出した。

<voice name="倫太郎" class="VID_OKA" src="voice/OKA_0042" mode="on">
「俺だ。どうもイヤな予感がする。俺たちが知らないところでなにかが起こっているようだ」

<voice name="倫太郎" class="VID_OKA" src="voice/OKA_0043" mode="on">
「……ああ、分かってる。無茶はしないさ。俺も命は惜しいからな。エル・プサイ・コングルゥ」

改めて別れの合い言葉で締めた後、額に滲んだ汗を手の甲で拭った。

やっべ。かなり冷や汗かいてる。

本当になにか起こったらどうしよう。

期待半分、不安半分というところだ。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_D0('INT', '0')
OP_B0('$SF_Phone_Open')
OP_8E()
OP_D0('INT', '1')
OP_CE('PhoneOperation', '1')
OP_8E()
SetText(
    'text00370',
    '@box00',
    [[
<PRE @box00>[text00370]
ケータイをしまい、改めてまゆりを見る。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_24('BGBUF2')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '0')
OP_CE('BgCopy', 'BGBUF1', 'BGBUF2', '0')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '0')
OP_D0('INT', '0')
OP_D0('INT', '0')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_20('BGBUF2', '0', '0', '0', 'null', 'true')
OP_8E()
OP_D0('STRING', 'GRAOW')
OP_D0('INT', '5000')
OP_CE('CreatePlainSP', 'GRAOW', '5000')
OP_8E()
OP_D0('INT', '0')
OP_D0('STRING', 'true')
OP_CE('DeleteAllSt', '0', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_D0('INT', '100')
OP_D0('STRING', 'cg/bg/BG07A1.jpg')
OP_CE('BgLoad', 'BGBUF1', '100', 'cg/bg/BG07A1.jpg')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('BGBUF1', '0', '1000', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_D0('INT', '0')
OP_D0('INT', '2000')
OP_D0('INT', '2000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_D0('STRING', 'Smoothing')
OP_CE('ZoomSG', 'BGBUF1', '0', '2000', '2000', 'null', 'true', 'Smoothing')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_24('BGBUF2')
OP_8E()
OP_D0('STRING', 'GRAOW')
OP_D0('INT', '533')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_CE('FadeDelete', 'GRAOW', '533', 'null', 'true')
OP_8E()
SetText(
    'text00380',
    '@box00',
    [[
<PRE @box00>[text00380]
こいつはなにをしているんだ？

もしかしてカプセルトイに夢中なのか？

爆発騒ぎにもまったく動じていないとは。

とんでもない大物か、とんでもないバカかのどちらかだな。

<voice name="倫太郎" class="VID_OKA" src="voice/OKA_0044" mode="on">
「まゆり、なにをしている？」

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '512')
OP_D0('INT', '0')
OP_91()
OP_CE('PosSt', 'STBUF5', '512', '@')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '1800')
OP_D0('INT', '0')
OP_91()
OP_D0('INT', '0')
OP_91()
OP_D0('STRING', 'MAY_AMB03')
OP_CE('St', 'STBUF5', '1800', '@', '@', 'MAY_AMB03')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '267')
OP_D0('STRING', 'true')
OP_CE('FadeSt', 'STBUF5', '267', 'true')
OP_8E()
OP_D0('STRING', '@BGM*')
OP_D0('INT', '534')
OP_D0('INT', '0')
OP_D0('STRING', 'null')
OP_43('@BGM*', '534', '0', 'null')
OP_8E()
OP_D0('STRING', '@BGM13')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'true')
OP_CE('SoundPlay', '@BGM13', '0', '1000', 'true')
OP_8E()
SetText(
    'text00390',
    '@box00',
    [[
<PRE @box00>[text00390]
<voice name="まゆり" class="VID_MAY" src="voice/MAY_0015" mode="on">
「んー？」

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '1800')
OP_D0('INT', '0')
OP_91()
OP_D0('INT', '0')
OP_91()
OP_D0('STRING', 'MAY_AMB01')
OP_CE('St', 'STBUF5', '1800', '@', '@', 'MAY_AMB01')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '267')
OP_D0('STRING', 'true')
OP_CE('FadeSt', 'STBUF5', '267', 'true')
OP_8E()
SetText(
    'text00400',
    '@box00',
    [[
<PRE @box00>[text00400]
<voice name="まゆり" class="VID_MAY" src="voice/MAY_0016" mode="on">
「あのね、『うーぱ』がほしいなあって」

予想通りか……。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_24('BGBUF2')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '2200')
OP_D0('STRING', 'cg/ibg/ibg003.png')
OP_CE('BgLoad', 'BGBUF2', '2200', 'cg/ibg/ibg003.png')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '0')
OP_D0('INT', '128')
OP_91()
OP_D0('INT', '0')
OP_91()
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_20('BGBUF2', '0', '@', '@', 'null', 'true')
OP_8E()
OP_D0('STRING', '@STBUF5*')
OP_D0('INT', '1066')
OP_D0('INT', '285')
OP_D2()
OP_91()
OP_D0('INT', '0')
OP_91()
OP_D0('STRING', 'AxlDxl')
OP_D0('STRING', 'false')
OP_20('@STBUF5*', '1066', '@', '@', 'AxlDxl', 'false')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '1066')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('BGBUF2', '1066', '1000', 'null', 'true')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_CE('PosSetSt', 'STBUF5')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '227')
OP_D0('INT', '0')
OP_91()
OP_CE('PosSt', 'STBUF5', '227', '@')
OP_8E()
SetText(
    'text00410',
    '@box00',
    [[
<PRE @box00>[text00410]
まゆりが指差したカプセルトイのマシンには、『<RUBY text="らい">雷</RUBY>ネット<RUBY text="かける">翔</RUBY>　立体キャラクタードールシリーズ』というチープなディスプレイが施されていた。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_D0('STRING', 'TIPS_SHOW')
OP_CE('TipsOn', 'TIPS_SHOW')
OP_8E()
SetText(
    'text00420',
    '@box00',
    [[
<PRE @box00>[text00420]
今や子供から大人まで知らない者はいないアニメ『<FONT incolor="#ff7080" outcolor="#000000">雷ネット翔</FONT>』。

スピンアウトしたカードゲーム『雷ネット・アクセスバトラーズ』は海外にまで人気が飛び火し、世界規模の大会が開かれるほどだ。

ちなみにまゆりが言う『うーぱ』とは、その『雷ネット翔』の中で最も人気がある、マスコット的キャラクターである。

見た目としては、卵のような楕円形でそこに手足が生えた犬っぽい生き物、と言えばいいだろうか。

いわゆる、ゆるキャラというものに分類されると思われる。

女子高生に人気が出てもおかしくない。そう言えば去年も、キモいカエルのキャラクターが流行っていたな。名前は忘れたが。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '533')
OP_D0('INT', '0')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('BGBUF2', '533', '0', 'null', 'true')
OP_8E()
SetText(
    'text00430',
    '@box00',
    [[
<PRE @box00>[text00430]
<voice name="倫太郎" class="VID_OKA" src="voice/OKA_0045" mode="on">
「やればいい。『うーぱ』が当たるかどうかは保証できないがな」

だがまゆりは困ったような笑みを浮かべたままだ。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '1800')
OP_D0('INT', '0')
OP_91()
OP_D0('INT', '0')
OP_91()
OP_D0('STRING', 'MAY_AMA03')
OP_CE('St', 'STBUF5', '1800', '@', '@', 'MAY_AMA03')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '267')
OP_D0('STRING', 'true')
OP_CE('FadeSt', 'STBUF5', '267', 'true')
OP_8E()
SetText(
    'text00440',
    '@box00',
    [[
<PRE @box00>[text00440]
<voice name="まゆり" class="VID_MAY" src="voice/MAY_0017" mode="on">
「でもね、まゆしぃは今、１００円玉を切らしちゃっているのです」

まゆりは自分のことを“まゆしぃ”と呼ぶ。

もっと厳密に言うなら“まゆしぃ”の後には☆が付くらしい。

すなわち“まゆしぃ☆”。

まさにどうでもいいことだが。

<voice name="まゆり" class="VID_MAY" src="voice/MAY_0018" mode="on">
「だから、オカリンオカリン、１００円貸してー？」

ねだるように、俺に向けて手の平を見せてくる。

どうやら最初からそれを期待していたらしい。

“ちょうだい”と言ってこないだけまだマシだが。

<voice name="倫太郎" class="VID_OKA" src="voice/OKA_0046" mode="on">
「甘ったれるなまゆり。金は貸さん。俺がお前に人生の厳しさを教えてやる」

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '267')
OP_D0('STRING', 'true')
OP_CE('DeleteSt', 'STBUF5', '267', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '533')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('BGBUF2', '533', '1000', 'null', 'true')
OP_8E()
SetText(
    'text00450',
    '@box00',
    [[
<PRE @box00>[text00450]
俺は言い放つと、サイフから１００円玉を取り出してコイン挿入口にセットした。勢いよくレバーを回す。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('STRING', 'SE01')
OP_D0('STRING', 'SGSE188')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'false')
OP_CE('SePlay', 'SE01', 'SGSE188', '0', '1000', 'false')
OP_8E()
OP_D0('STRING', 'SE01')
OP_CE('WaitPlayHalfSG', 'SE01')
OP_8E()
SetText(
    'text00460',
    '@box00',
    [[
<PRE @box00>[text00460]
<voice name="まゆり" class="VID_MAY" src="voice/MAY_0019" mode="on">
「あ、ああー……」

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('BGBUF1', '0', '1000', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '533')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_CE('FadeDelete', 'BGBUF2', '533', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_24('BGBUF2')
OP_8E()
SetText(
    'text00470',
    '@box00',
    [[
<PRE @box00>[text00470]
出てきたカプセルを割って中身を取り出した。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '512')
OP_D0('INT', '0')
OP_91()
OP_CE('PosSt', 'STBUF5', '512', '@')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '1800')
OP_D0('INT', '0')
OP_91()
OP_D0('INT', '0')
OP_91()
OP_D0('STRING', 'MAY_ALA04')
OP_CE('St', 'STBUF5', '1800', '@', '@', 'MAY_ALA04')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '133')
OP_D0('STRING', 'true')
OP_CE('FadeSt', 'STBUF5', '133', 'true')
OP_8E()
SetText(
    'text00480',
    '@box00',
    [[
<PRE @box00>[text00480]
まゆりもなにが出たか気になるようで、俺の手元をのぞき込んでくる。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '1800')
OP_D0('INT', '0')
OP_91()
OP_D0('INT', '0')
OP_91()
OP_D0('STRING', 'MAY_ALB02')
OP_CE('St', 'STBUF5', '1800', '@', '@', 'MAY_ALB02')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '267')
OP_D0('STRING', 'true')
OP_CE('FadeSt', 'STBUF5', '267', 'true')
OP_8E()
SetText(
    'text00490',
    '@box00',
    [[
<PRE @box00>[text00490]
<voice name="まゆり" class="VID_MAY" src="voice/MAY_0020" mode="on">
「あっ、『うーぱ』だよ。しかもメタル。『メタルうーぱ』」

<voice name="倫太郎" class="VID_OKA" src="voice/OKA_0047" mode="on">
「それはレアなのか？」

<voice name="まゆり" class="VID_MAY" src="voice/MAY_0021" mode="on">
「すごく！」

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('STRING', 'GRAOW')
OP_D0('INT', '5000')
OP_CE('CreatePlainSP', 'GRAOW', '5000')
OP_8E()
OP_D0('INT', '0')
OP_D0('STRING', 'true')
OP_CE('DeleteAllSt', '0', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_24('BGBUF2')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '2000')
OP_CE('BgCopy', 'BGBUF1', 'BGBUF2', '2000')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_D0('STRING', 'Smoothing')
OP_CE('ZoomSG', 'BGBUF2', '0', '1000', '1000', 'null', 'true', 'Smoothing')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '0')
OP_D0('INT', '0')
OP_91()
OP_D0('INT', '0')
OP_91()
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_20('BGBUF2', '0', '@', '@', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '0')
OP_D0('INT', '0')
OP_91()
OP_D0('INT', '0')
OP_91()
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_20('BGBUF2', '0', '@', '@', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('BGBUF2', '0', '1000', 'null', 'true')
OP_8E()
OP_D0('STRING', 'GRAOW')
OP_D0('INT', '533')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_CE('FadeDelete', 'GRAOW', '533', 'null', 'true')
OP_8E()
SetText(
    'text00500',
    '@box00',
    [[
<PRE @box00>[text00500]
その『メタルうーぱ』をしげしげと眺めながら、カプセルトイの前から離れた。

俺たちの後ろで見ていた小学生ぐらいの男の子が、続いて同じ『雷ネット翔』のカプセルトイに挑戦している。

<voice name="男の子" class="VID_ETC" src="voice/BOY_0000" mode="on">
「あー、普通の『うーぱ』だ……」

俺の当てた『メタルうーぱ』を恨めしげに見つめてくる。

俺の横ではまゆりが目を輝かせている。

おい女子高生。小学生男児と同レベルだぞ……。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('STRING', 'EV_M01A')
OP_CE('ChkAchieveEVRead', 'EV_M01A')
OP_8E()
OP_D0('STRING', '絵板写')
OP_D0('INT', '5000')
OP_CE('CreatePlainSP', '絵板写', '5000')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_24('BGBUF2')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '3200')
OP_D0('STRING', 'cg/ev/EV_M01A.jpg')
OP_CE('BgLoad', 'BGBUF2', '3200', 'cg/ev/EV_M01A.jpg')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('BGBUF2', '0', '1000', 'null', 'true')
OP_8E()
OP_D0('STRING', '絵板写')
OP_D0('INT', '533')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_CE('FadeDelete', '絵板写', '533', 'null', 'true')
OP_8E()
SetText(
    'text00510',
    '@box00',
    [[
<PRE @box00>[text00510]
<voice name="倫太郎" class="VID_OKA" src="voice/OKA_0048" mode="on">
「フン、ではまゆりにくれてやろう」

はっきり言って全然興味がなかった。

まゆりの手に『メタルうーぱ』を握らせてやる。

<voice name="まゆり" class="VID_MAY" src="voice/MAY_0022" mode="on">
「ホントー？　いいの？　オカリン」

<voice name="倫太郎" class="VID_OKA" src="voice/OKA_0049" mode="on">
「鳳凰院凶真だ」

<voice name="まゆり" class="VID_MAY" src="voice/MAY_0023" mode="on">
「えっへへー、ありがとーオカリン♪」

<voice name="倫太郎" class="VID_OKA" src="voice/OKA_0050" mode="on">
「…………」

もしかしてわざとそこだけ無視してないか？

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('STRING', '@BGM*')
OP_D0('INT', '533')
OP_D0('INT', '0')
OP_D0('STRING', 'null')
OP_43('@BGM*', '533', '0', 'null')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_D0('INT', '100')
OP_D0('STRING', 'cg/bg/BG07A1.jpg')
OP_CE('BgLoad', 'BGBUF1', '100', 'cg/bg/BG07A1.jpg')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('BGBUF1', '0', '1000', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '533')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_CE('FadeDelete', 'BGBUF2', '533', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_24('BGBUF2')
OP_8E()
SetText(
    'text00520',
    '@box00',
    [[
<PRE @box00>[text00520]
<voice name="司会者" class="VID_ETC" src="voice/MCA_0000" mode="on">
「――本日は、ドクター中鉢によるタイムマシン発明成功記念会見にお集まりいただき、まことにありがとうございます」

上の階から、かすかにそんなマイクの声が聞こえてきた。

<voice name="倫太郎" class="VID_OKA" src="voice/OKA_0051" mode="on">
「どうやら始まるようだな」

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_D0('STRING', 'Smoothing')
OP_CE('ZoomSG', 'BGBUF1', '0', '1000', '1000', 'null', 'true', 'Smoothing')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_D0('INT', '0')
OP_D0('INT', '0')
OP_D0('INT', '0')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_20('BGBUF1', '0', '0', '0', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_D0('INT', '1066')
OP_D0('INT', '2000')
OP_D0('INT', '2000')
OP_D0('STRING', 'AxlDxl')
OP_D0('STRING', 'true')
OP_D0('STRING', 'Smoothing')
OP_CE('ZoomSG', 'BGBUF1', '1066', '2000', '2000', 'AxlDxl', 'true', 'Smoothing')
OP_8E()
OP_D0('INT', '266')
OP_3A('266')
OP_8E()
OP_D0('STRING', 'MASKBUF2')
OP_D0('INT', '5100')
OP_D0('STRING', '#000000')
OP_CE('CreateColorEX', 'MASKBUF2', '5100', '#000000')
OP_8E()
OP_D0('STRING', 'MASKBUF2')
OP_D0('INT', '1066')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'false')
OP_25('MASKBUF2', '1066', '1000', 'null', 'false')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_D0('INT', '1066')
OP_D0('INT', '512')
OP_91()
OP_D0('INT', '288')
OP_91()
OP_D0('STRING', 'AxlDxl')
OP_D0('STRING', 'true')
OP_20('BGBUF1', '1066', '@', '@', 'AxlDxl', 'true')
OP_8E()
SetText(
    'text00530',
    '@box00',
    [[
<PRE @box00>[text00530]
８階へと向かう。

だがまゆりがついてこない。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('STRING', 'MASKBUF2')
OP_D0('INT', '1066')
OP_D0('STRING', 'null')
OP_D0('STRING', 'false')
OP_CE('FadeDelete', 'MASKBUF2', '1066', 'null', 'false')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_D0('INT', '1066')
OP_D0('INT', '0')
OP_D0('INT', '0')
OP_D0('STRING', 'AxlDxl')
OP_D0('STRING', 'true')
OP_20('BGBUF1', '1066', '0', '0', 'AxlDxl', 'true')
OP_8E()
SetText(
    'text00540',
    '@box00',
    [[
<PRE @box00>[text00540]
<voice name="倫太郎" class="VID_OKA" src="voice/OKA_0052" mode="on">
「行くぞまゆり」

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '512')
OP_D0('INT', '0')
OP_91()
OP_CE('PosSt', 'STBUF5', '512', '@')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '1800')
OP_D0('INT', '0')
OP_91()
OP_D0('INT', '0')
OP_91()
OP_D0('STRING', 'MAY_ALA04')
OP_CE('St', 'STBUF5', '1800', '@', '@', 'MAY_ALA04')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '267')
OP_D0('STRING', 'true')
OP_CE('FadeSt', 'STBUF5', '267', 'true')
OP_8E()
SetText(
    'text00550',
    '@box00',
    [[
<PRE @box00>[text00550]
<voice name="まゆり" class="VID_MAY" src="voice/MAY_0024" mode="on">
「んー、待って待って。名前書かなくちゃ」

どうやら『メタルうーぱ』に夢中らしい。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('INT', '9000')
OP_D0('STRING', '#000000')
OP_D0('INT', '533')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_CE('ColorOut', '9000', '#000000', '533', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_24('BGBUF1')
OP_8E()
OP_D0('INT', '0')
OP_D0('STRING', 'true')
OP_CE('DeleteAllSt', '0', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_D0('INT', '100')
OP_D0('STRING', 'cg/bg/BG06A3.jpg')
OP_CE('BgLoad', 'BGBUF1', '100', 'cg/bg/BG06A3.jpg')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('BGBUF1', '0', '1000', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BG06A3')
OP_CE('SetCharaColor', 'BG06A3')
OP_8E()
OP_D0('INT', '533')
OP_3A('533')
OP_8E()
OP_D0('STRING', 'OnColor*')
OP_D0('INT', '533')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_CE('FadeDelete', 'OnColor*', '533', 'null', 'true')
OP_8E()
SetText(
    'text00560',
    '@box00',
    [[
<PRE @box00>[text00560]
<voice name="司会者" class="VID_ETC" src="voice/MCA_0001" mode="on">
「それでは、早速登場していただきましょう。発明家、ドクター中鉢さんです！　皆さん、盛大な拍手でお迎えください！」

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('STRING', 'SE01')
OP_D0('STRING', 'SGSE001')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'false')
OP_CE('SePlay', 'SE01', 'SGSE001', '0', '1000', 'false')
OP_8E()
OP_D0('STRING', 'SE01')
OP_CE('WaitPlayHalfSG', 'SE01')
OP_8E()
SetText(
    'text00570',
    '@box00',
    [[
<PRE @box00>[text00570]
まばら――どころかほんの数人だけの拍手に迎えられて、中鉢が現れた。

会見場の奥に設置された壇に向かう。

早くもかなりの仏頂面だ。不機嫌さが全身から溢れ出している。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_24('BGBUF2')
OP_8E()
OP_D0('STRING', '絵板写')
OP_D0('INT', '5000')
OP_CE('CreatePlainSP', '絵板写', '5000')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '1000')
OP_CE('BgCopy', 'BGBUF1', 'BGBUF2', '1000')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '0')
OP_D0('INT', '2000')
OP_D0('INT', '2000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_D0('STRING', 'Smoothing')
OP_CE('ZoomSG', 'BGBUF2', '0', '2000', '2000', 'null', 'true', 'Smoothing')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('BGBUF2', '0', '1000', 'null', 'true')
OP_8E()
OP_D0('STRING', 'STBUF6')
OP_D0('INT', '512')
OP_D0('INT', '0')
OP_91()
OP_CE('PosSt', 'STBUF6', '512', '@')
OP_8E()
OP_D0('STRING', 'STBUF6')
OP_D0('INT', '1600')
OP_D0('INT', '0')
OP_91()
OP_D0('INT', '0')
OP_91()
OP_D0('STRING', 'NAK_ASA02')
OP_CE('St', 'STBUF6', '1600', '@', '@', 'NAK_ASA02')
OP_8E()
OP_D0('STRING', 'STBUF6')
OP_D0('INT', '0')
OP_D0('STRING', 'true')
OP_CE('FadeSt', 'STBUF6', '0', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('BGBUF1', '0', '1000', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_D0('INT', '0')
OP_D0('INT', '2000')
OP_D0('INT', '2000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_D0('STRING', 'Smoothing')
OP_CE('ZoomSG', 'BGBUF1', '0', '2000', '2000', 'null', 'true', 'Smoothing')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_24('BGBUF2')
OP_8E()
OP_D0('STRING', '絵板写')
OP_D0('INT', '533')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_CE('FadeDelete', '絵板写', '533', 'null', 'true')
OP_8E()
SetText(
    'text00580',
    '@box00',
    [[
<PRE @box00>[text00580]
<voice name="中鉢" class="VID_NAK" src="voice/NAK_0000" mode="on">
「ドクター中鉢だ。どうぞよろしく」

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_D0('STRING', 'STBUF6')
OP_D0('INT', '1600')
OP_D0('INT', '0')
OP_91()
OP_D0('INT', '0')
OP_91()
OP_D0('STRING', 'NAK_ASA01')
OP_CE('St', 'STBUF6', '1600', '@', '@', 'NAK_ASA01')
OP_8E()
OP_D0('STRING', 'STBUF6')
OP_D0('INT', '267')
OP_D0('STRING', 'true')
OP_CE('FadeSt', 'STBUF6', '267', 'true')
OP_8E()
SetText(
    'text00590',
    '@box00',
    [[
<PRE @box00>[text00590]
<voice name="中鉢" class="VID_NAK" src="voice/NAK_0001" mode="on">
「それでは、ここに集まってもらった諸君だけに、人類史に残る世紀の大発明、タイムマシンについての理論をお教えしよう」

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('STRING', 'BGBUF4')
OP_24('BGBUF4')
OP_8E()
OP_D0('STRING', 'BGBUF4')
OP_D0('INT', '5000')
OP_CE('CreatePlainSP', 'BGBUF4', '5000')
OP_8E()
OP_D0('STRING', 'BGBUF4')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('BGBUF4', '0', '1000', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_24('BGBUF2')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '0')
OP_CE('BgCopy', 'BGBUF1', 'BGBUF2', '0')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('BGBUF2', '0', '1000', 'null', 'true')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '294')
OP_D0('INT', '0')
OP_91()
OP_CE('PosSt', 'STBUF5', '294', '@')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '1800')
OP_D0('INT', '0')
OP_91()
OP_D0('INT', '0')
OP_91()
OP_D0('STRING', 'MAY_ALC02')
OP_CE('St', 'STBUF5', '1800', '@', '@', 'MAY_ALC02')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '0')
OP_D0('STRING', 'true')
OP_CE('FadeSt', 'STBUF5', '0', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_24('BGBUF1')
OP_8E()
OP_D0('STRING', 'STBUF6')
OP_D0('INT', '0')
OP_D0('STRING', 'true')
OP_CE('DeleteSt', 'STBUF6', '0', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '0')
OP_CE('BgSwap', 'BGBUF1', 'BGBUF2', '0')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('BGBUF1', '0', '1000', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_24('BGBUF2')
OP_8E()
OP_D0('INT', '5')
OP_D0('INT', '6')
OP_D0('INT', '7')
OP_D0('INT', '8')
OP_CE('CharaPrio4', '5', '6', '7', '8')
OP_8E()
OP_D0('STRING', 'BGBUF4')
OP_D0('INT', '533')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_CE('FadeDelete', 'BGBUF4', '533', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF4')
OP_24('BGBUF4')
OP_8E()
SetText(
    'text00600',
    '@box00',
    [[
<PRE @box00>[text00600]
<voice name="まゆり" class="VID_MAY" src="voice/MAY_0025" mode="on">
「タイムマシン？　あの人が作ったのー？」

『メタルうーぱ』に名前を書き終わったらしいまゆりがやって来て、今さらながらなことを言っている。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('INT', '267')
OP_D0('STRING', 'true')
OP_CE('DeleteAllSt', '267', 'true')
OP_8E()
SetText(
    'text00610',
    '@box00',
    [[
<PRE @box00>[text00610]
中鉢は、マイクを片手に、自信満々という態度をみなぎらせて話し始めた。

聴衆は俺を入れてせいぜい２０人ほどだ。さっきより少しだけ増えた。

だがやはり、記者やカメラマンらしき人物は見当たらない。

これが世間のドクター中鉢への注目度かと理解した。

色モノ発明家が“タイムマシンを発明した”と発表したところで、世間は“なにを言ってるんだか”という失笑で返すだけ。

俺も、この男が語ることに興味はあったが、それほど期待していたわけではない。

そしてそれは、ドクター中鉢がいざタイムマシンの理論について語り出したときに失望となり、時間が経つにつれて怒りへと変わった。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_24('BGBUF2')
OP_8E()
OP_D0('STRING', '絵板写')
OP_D0('INT', '5000')
OP_CE('CreatePlainSP', '絵板写', '5000')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '0')
OP_CE('BgCopy', 'BGBUF1', 'BGBUF2', '0')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '0')
OP_D0('INT', '2000')
OP_D0('INT', '2000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_D0('STRING', 'Smoothing')
OP_CE('ZoomSG', 'BGBUF2', '0', '2000', '2000', 'null', 'true', 'Smoothing')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('BGBUF2', '0', '1000', 'null', 'true')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '512')
OP_D0('INT', '0')
OP_91()
OP_CE('PosSt', 'STBUF5', '512', '@')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '1800')
OP_D0('INT', '0')
OP_91()
OP_D0('INT', '0')
OP_91()
OP_D0('STRING', 'NAK_ASA01')
OP_CE('St', 'STBUF5', '1800', '@', '@', 'NAK_ASA01')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '0')
OP_D0('STRING', 'true')
OP_CE('FadeSt', 'STBUF5', '0', 'true')
OP_8E()
OP_D0('STRING', '@BGM08')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'true')
OP_CE('SoundPlay', '@BGM08', '0', '1000', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_D0('INT', '0')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_CE('FadeDelete', 'BGBUF1', '0', 'null', 'true')
OP_8E()
OP_D0('STRING', '絵板写')
OP_D0('INT', '133')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_CE('FadeDelete', '絵板写', '133', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '0')
OP_CE('BgSwap', 'BGBUF1', 'BGBUF2', '0')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_D0('INT', '0')
OP_D0('INT', '2000')
OP_D0('INT', '2000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_D0('STRING', 'Smoothing')
OP_CE('ZoomSG', 'BGBUF1', '0', '2000', '2000', 'null', 'true', 'Smoothing')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('BGBUF1', '0', '1000', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_24('BGBUF2')
OP_8E()
SetText(
    'text00620',
    '@box00',
    [[
<PRE @box00>[text00620]
<voice name="倫太郎" class="VID_OKA" src="voice/OKA_0053" mode="on">
「ドぉぉぉクぅぅぅターぁぁぁっ！」

記者会見中にもかかわらず、俺は叫んでしまっていた。

<voice name="倫太郎" class="VID_OKA" src="voice/OKA_0054" mode="on">
「バカにするにもほどがあるぞ！」

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '1800')
OP_D0('INT', '0')
OP_91()
OP_D0('INT', '0')
OP_91()
OP_D0('STRING', 'NAK_ASA02')
OP_CE('St', 'STBUF5', '1800', '@', '@', 'NAK_ASA02')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '267')
OP_D0('STRING', 'true')
OP_CE('FadeSt', 'STBUF5', '267', 'true')
OP_8E()
SetText(
    'text00630',
    '@box00',
    [[
<PRE @box00>[text00630]
<voice name="中鉢" class="VID_NAK" src="voice/NAK_0002" mode="on">
「なんだね君は！？」

<voice name="倫太郎" class="VID_OKA" src="voice/OKA_0055" mode="on">
「俺が誰なのかはどうでもいい！　それより、今貴方が語ったタイムマシンの理論はいったいなんだ！？」

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_D0('STRING', 'TIPS_TITOR')
OP_CE('TipsOn', 'TIPS_TITOR')
OP_8E()
SetText(
    'text00640',
    '@box00',
    [[
<PRE @box00>[text00640]
<voice name="倫太郎" class="VID_OKA" src="voice/OKA_0056" mode="on">
「<FONT incolor="#ff7080" outcolor="#000000">ジョン・タイター</FONT>のパクリではないか！　貴方はそれでも発明家かっ！」

<voice name="中鉢" class="VID_NAK" src="voice/NAK_0003" mode="on">
「だ、誰か、その男をつまみ出せ」

<voice name="倫太郎" class="VID_OKA" src="voice/OKA_0057" mode="on">
「出ていくのは貴方だ、ドクター！　恥を知れ！　<RUBY text="こんりんざい">金輪際</RUBY>、貴方には発明家を名乗る資格はないぞっ！」

<voice name="中鉢" class="VID_NAK" src="voice/NAK_0004" mode="on">
「うるさい、黙れっ！　生意気な若造めっ！」

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('INT', '900')
OP_D0('INT', '13')
OP_D0('INT', '6')
OP_D0('STRING', 'DxlAuto')
OP_D0('STRING', 'true')
OP_CE('AllShake', '900', '13', '6', 'DxlAuto', 'true')
OP_8E()
SetText(
    'text00650',
    '@box00',
    [[
<PRE @box00>[text00650]
と、背後から俺の手を何者かがつかんだ。

てっきり俺をつまみ出そうとする係員かと思い、にらみつける勢いで振り返る。

<voice name="倫太郎" class="VID_OKA" src="voice/OKA_0058" mode="on">
「は、な、せっ……んん？」

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('STRING', '@BGM*')
OP_D0('INT', '533')
OP_D0('INT', '0')
OP_D0('STRING', 'null')
OP_43('@BGM*', '533', '0', 'null')
OP_8E()
OP_D0('STRING', '上背景')
OP_D0('INT', '10000')
OP_CE('PrintGO', '上背景', '10000')
OP_8E()
OP_D0('STRING', 'EV_C01A')
OP_CE('ChkAchieveEVRead', 'EV_C01A')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_24('BGBUF2')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '3200')
OP_D0('STRING', 'cg/ev/EV_C01A.jpg')
OP_CE('BgLoad', 'BGBUF2', '3200', 'cg/ev/EV_C01A.jpg')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('BGBUF2', '0', '1000', 'null', 'true')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '0')
OP_D0('STRING', 'true')
OP_CE('DeleteSt', 'STBUF5', '0', 'true')
OP_8E()
OP_D0('STRING', '上背景')
OP_D0('INT', '133')
OP_D0('INT', '100')
OP_D0('STRING', 'null')
OP_D0('STRING', 'mask18')
OP_D0('STRING', 'true')
OP_D0('STRING', 'true')
OP_CE('DrawDeleteSG', '上背景', '133', '100', 'null', 'mask18', 'true', 'true')
OP_8E()
SetText(
    'text00660',
    '@box00',
    [[
<PRE @box00>[text00660]
<voice name="？？？" class="VID_CRS" src="voice/CRS_0000" mode="on">
「…………」

俺と同い年ぐらいの女だった。

挑みかかってくるかのような、きつい眼差し。

真正面から物怖じせずに向けてくるその視線に、俺はたじろぐ。

この顔には見覚えがあった。前に、どこかで……？

<voice name="倫太郎" class="VID_OKA" src="voice/OKA_0059" mode="on">
「あ……」

<RUBY text="まきせ">牧瀬</RUBY><RUBY text="くりす">紅莉栖</RUBY>だ。

会ったことはないが顔は知っている。

数日前、俺の友人であるダル――<RUBY text="はしだ">橋田</RUBY><RUBY text="いたる">至</RUBY>が雑誌を見せてくれた。

その中の記事に“天才少女が秋葉原で講演”という内容があった。

なんでも、今年の春にわずか１７歳でアメリカの大学を飛び級で卒業し、研究論文がアメリカの学術雑誌『サイエンス』に載ったとか。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('STRING', 'BGBUF3')
OP_24('BGBUF3')
OP_8E()
OP_D0('STRING', 'BGBUF3')
OP_D0('INT', '2300')
OP_D0('STRING', 'cg/ibg/ibg004.jpg')
OP_CE('BgLoad', 'BGBUF3', '2300', 'cg/ibg/ibg004.jpg')
OP_8E()
OP_D0('STRING', '@BGM19')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'true')
OP_CE('SoundPlay', '@BGM19', '0', '1000', 'true')
OP_8E()
OP_D0('STRING', 'GRAOW')
OP_D0('INT', '5000')
OP_CE('CreatePlainSP', 'GRAOW', '5000')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '3200')
OP_D0('STRING', 'cg/ibg/ibg004.jpg')
OP_CE('BgLoad', 'BGBUF2', '3200', 'cg/ibg/ibg004.jpg')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('BGBUF2', '0', '1000', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF3')
OP_24('BGBUF3')
OP_8E()
OP_D0('STRING', 'GRAOW')
OP_D0('INT', '533')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_CE('FadeDelete', 'GRAOW', '533', 'null', 'true')
OP_8E()
SetText(
    'text00670',
    '@box00',
    [[
<PRE @box00>[text00670]
記事で牧瀬紅莉栖と紹介されていた天才少女。

掲載されていた写真に写っていたのが、今目の前にいるこの生意気そうな女だった。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('STRING', 'BGBUF4')
OP_24('BGBUF4')
OP_8E()
OP_D0('STRING', 'BGBUF4')
OP_D0('INT', '5000')
OP_CE('CreatePlainSP', 'BGBUF4', '5000')
OP_8E()
OP_D0('STRING', 'BGBUF4')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('BGBUF4', '0', '1000', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF3')
OP_24('BGBUF3')
OP_8E()
OP_D0('STRING', 'BGBUF3')
OP_D0('INT', '4000')
OP_D0('STRING', 'cg/bg/BG_BLACK.jpg')
OP_CE('BgLoad', 'BGBUF3', '4000', 'cg/bg/BG_BLACK.jpg')
OP_8E()
OP_D0('STRING', 'BGBUF3')
OP_D0('INT', '0')
OP_D0('INT', '0')
OP_D0('INT', '500')
OP_D0('INT', '250')
OP_D0('STRING', 'null')
OP_D0('STRING', 'mask12')
OP_D0('STRING', 'true')
OP_D0('STRING', 'false')
OP_CE('DrawTransitionSG', 'BGBUF3', '0', '0', '500', '250', 'null', 'mask12', 'true', 'false')
OP_8E()
OP_D0('STRING', 'BGBUF3')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('BGBUF3', '0', '1000', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF5')
OP_24('BGBUF5')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('STRING', 'BGBUF5')
OP_D0('INT', '0')
OP_CE('BgCopy', 'BGBUF2', 'BGBUF5', '0')
OP_8E()
OP_D0('STRING', 'BGBUF5')
OP_D0('INT', '0')
OP_D0('INT', '2000')
OP_D0('INT', '2000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_D0('STRING', 'Smoothing')
OP_CE('ZoomSG', 'BGBUF5', '0', '2000', '2000', 'null', 'true', 'Smoothing')
OP_8E()
OP_D0('STRING', 'BGBUF5')
OP_D0('INT', '0')
OP_D0('INT', '656')
OP_D2()
OP_D0('INT', '0')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_20('BGBUF5', '0', '0', '0', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF5')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('BGBUF5', '0', '1000', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF4')
OP_D0('INT', '533')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_CE('FadeDelete', 'BGBUF4', '533', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF4')
OP_24('BGBUF4')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_24('BGBUF2')
OP_8E()
SetText(
    'text00680',
    '@box00',
    [[
<PRE @box00>[text00680]
その写真でも、今と同じように不機嫌さ丸出しの顔だったのが印象に残っている。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('STRING', 'BGBUF4')
OP_24('BGBUF4')
OP_8E()
OP_D0('STRING', 'BGBUF4')
OP_D0('INT', '5000')
OP_CE('CreatePlainSP', 'BGBUF4', '5000')
OP_8E()
OP_D0('STRING', 'BGBUF4')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('BGBUF4', '0', '1000', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_24('BGBUF2')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '0')
OP_CE('BgCopy', 'BGBUF1', 'BGBUF2', '0')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('BGBUF2', '0', '1000', 'null', 'true')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '640')
OP_D0('INT', '0')
OP_91()
OP_CE('PosSt', 'STBUF5', '640', '@')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '1800')
OP_D0('INT', '0')
OP_91()
OP_D0('INT', '0')
OP_91()
OP_D0('STRING', 'CRS_ALB04')
OP_CE('St', 'STBUF5', '1800', '@', '@', 'CRS_ALB04')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '0')
OP_D0('STRING', 'true')
OP_CE('FadeSt', 'STBUF5', '0', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF3')
OP_24('BGBUF3')
OP_8E()
OP_D0('STRING', 'BGBUF5')
OP_24('BGBUF5')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '0')
OP_CE('BgSwap', 'BGBUF1', 'BGBUF2', '0')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('BGBUF1', '0', '1000', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_24('BGBUF2')
OP_8E()
OP_D0('INT', '5')
OP_D0('INT', '6')
OP_D0('INT', '7')
OP_D0('INT', '8')
OP_CE('CharaPrio4', '5', '6', '7', '8')
OP_8E()
OP_D0('STRING', 'BGBUF4')
OP_D0('INT', '533')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_CE('FadeDelete', 'BGBUF4', '533', 'null', 'true')
OP_8E()
SetText(
    'text00690',
    '@box00',
    [[
<PRE @box00>[text00690]
そんな天才が、なぜ俺に声をかけてきた？

<voice name="紅莉栖" class="VID_CRS" src="voice/CRS_0001" mode="on">
「ちょっと来てくれませんか」

険しい表情のまま周囲に素早く視線を走らせ、小声で耳打ちしてきた。

なんだ、この態度は。

牧瀬紅莉栖が会場の係員だとは思えない。

かといってドクター中鉢の関係者であるはずもない。

となると……まさか……！

<voice name="倫太郎" class="VID_OKA" src="voice/OKA_0060" mode="on">
「き、貴様、“機関”の人間か！？」

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '1800')
OP_D0('INT', '0')
OP_91()
OP_D0('INT', '0')
OP_91()
OP_D0('STRING', 'CRS_ALC05')
OP_CE('St', 'STBUF5', '1800', '@', '@', 'CRS_ALC05')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '267')
OP_D0('STRING', 'true')
OP_CE('FadeSt', 'STBUF5', '267', 'true')
OP_8E()
SetText(
    'text00700',
    '@box00',
    [[
<PRE @box00>[text00700]
<voice name="紅莉栖" class="VID_CRS" src="voice/CRS_0002" mode="on">
「はあ？」

<voice name="倫太郎" class="VID_OKA" src="voice/OKA_0061" mode="on">
「くっ、まさかここまで手が回っているとは……。俺としたことが」

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_D0('STRING', '@BGM*')
OP_D0('INT', '533')
OP_D0('INT', '0')
OP_D0('STRING', 'null')
OP_43('@BGM*', '533', '0', 'null')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '1800')
OP_D0('INT', '0')
OP_91()
OP_D0('INT', '0')
OP_91()
OP_D0('STRING', 'CRS_ALB03')
OP_CE('St', 'STBUF5', '1800', '@', '@', 'CRS_ALB03')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '267')
OP_D0('STRING', 'true')
OP_CE('FadeSt', 'STBUF5', '267', 'true')
OP_8E()
SetText(
    'text00710',
    '@box00',
    [[
<PRE @box00>[text00710]
<voice name="紅莉栖" class="VID_CRS" src="voice/CRS_0003" mode="on">
「ふざけてないで、ちょっと来てください」

<voice name="倫太郎" class="VID_OKA" src="voice/OKA_0062" mode="on">
「…………」

ここは黙って従うことにした。

今の俺は、ドクター中鉢にケンカを売ったことで明らかに注目を浴びてしまっている。

というか中鉢が俺をすさまじい勢いでにらみつけてきているわけだが。

俺のような若造に図星を指され、さぞ悔しいのだろう。

とにかくこれ以上注目されるわけにはいかない。

俺は狂気のマッドサイエンティスト。“機関”から追われている身なのだ。

このままだと危険な事態になりそうな予感がする。

まゆりや周囲の聴衆を、そんな事態に巻き込むわけにはいかなかった。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('INT', '267')
OP_D0('STRING', 'true')
OP_CE('DeleteAllSt', '267', 'true')
OP_8E()
SetText(
    'text00720',
    '@box00',
    [[
<PRE @box00>[text00720]
牧瀬紅莉栖は、おとなしくなった俺の手を引いて、会場の外に出た。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('STRING', '上背景')
OP_D0('INT', '10000')
OP_CE('PrintGO', '上背景', '10000')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_24('BGBUF2')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '200')
OP_D0('STRING', 'cg/bg/BG_BLACK.jpg')
OP_CE('BgLoad', 'BGBUF2', '200', 'cg/bg/BG_BLACK.jpg')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('BGBUF2', '0', '1000', 'null', 'true')
OP_8E()
OP_D0('STRING', '上背景')
OP_D0('INT', '533')
OP_D0('INT', '100')
OP_D0('STRING', 'null')
OP_D0('STRING', 'mask02')
OP_D0('STRING', 'true')
OP_D0('STRING', 'true')
OP_CE('DrawDeleteSG', '上背景', '533', '100', 'null', 'mask02', 'true', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF*')
OP_24('BGBUF*')
OP_8E()
OP_D0('INT', '0')
OP_D0('STRING', 'true')
OP_CE('DeleteAllSt', '0', 'true')
OP_8E()
OP_D0('INT', '9000')
OP_D0('STRING', '#000000')
OP_D0('INT', '0')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_CE('ColorOut', '9000', '#000000', '0', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_24('BGBUF1')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_D0('INT', '100')
OP_D0('STRING', 'cg/bg/BG07A1.jpg')
OP_CE('BgLoad', 'BGBUF1', '100', 'cg/bg/BG07A1.jpg')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('BGBUF1', '0', '1000', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BG07A1')
OP_CE('SetCharaColor', 'BG07A1')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '512')
OP_D0('INT', '0')
OP_91()
OP_CE('PosSt', 'STBUF5', '512', '@')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '1800')
OP_D0('INT', '0')
OP_91()
OP_D0('INT', '0')
OP_91()
OP_D0('STRING', 'CRS_AMA04')
OP_CE('St', 'STBUF5', '1800', '@', '@', 'CRS_AMA04')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '0')
OP_D0('STRING', 'true')
OP_CE('FadeSt', 'STBUF5', '0', 'true')
OP_8E()
OP_D0('INT', '533')
OP_3A('533')
OP_8E()
OP_D0('STRING', '@BGM07')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'true')
OP_CE('SoundPlay', '@BGM07', '0', '1000', 'true')
OP_8E()
OP_D0('STRING', 'OnColor*')
OP_D0('INT', '533')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_CE('FadeDelete', 'OnColor*', '533', 'null', 'true')
OP_8E()
SetText(
    'text00730',
    '@box00',
    [[
<PRE @box00>[text00730]
<voice name="倫太郎" class="VID_OKA" src="voice/OKA_0063" mode="on">
「ここで俺になにかすれば人目に付くぞ。そうなれば貴様も色々まずいだろう」

<voice name="紅莉栖" class="VID_CRS" src="voice/CRS_0004" mode="on">
「なにかってなんですか、人聞きの悪い」

にらまれた。なかなかの迫力。

端整な顔立ちをしてるのに、かわいげの欠片もない。

冷酷無比の美少女エージェントか……。

波乱の予感だが、なぜか心が浮き立っている自分がいた。

やはり俺は、混沌に身を置くことが好きらしい、ククク。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '1800')
OP_D0('INT', '0')
OP_91()
OP_D0('INT', '0')
OP_91()
OP_D0('STRING', 'CRS_AMA01')
OP_CE('St', 'STBUF5', '1800', '@', '@', 'CRS_AMA01')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '267')
OP_D0('STRING', 'true')
OP_CE('FadeSt', 'STBUF5', '267', 'true')
OP_8E()
SetText(
    'text00740',
    '@box00',
    [[
<PRE @box00>[text00740]
<voice name="紅莉栖" class="VID_CRS" src="voice/CRS_0005" mode="on">
「私は、あなたに聞きたいことがあるだけです」

<voice name="倫太郎" class="VID_OKA" src="voice/OKA_0064" mode="on">
「それに答える義理はない。“機関”のやり方は分かっている」

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '1800')
OP_D0('INT', '0')
OP_91()
OP_D0('INT', '0')
OP_91()
OP_D0('STRING', 'CRS_AMC05')
OP_CE('St', 'STBUF5', '1800', '@', '@', 'CRS_AMC05')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '267')
OP_D0('STRING', 'true')
OP_CE('FadeSt', 'STBUF5', '267', 'true')
OP_8E()
SetText(
    'text00750',
    '@box00',
    [[
<PRE @box00>[text00750]
<voice name="紅莉栖" class="VID_CRS" src="voice/CRS_0006" mode="on">
「だから“機関”って？」

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_D0('INT', '0')
OP_CE('PhoneOperation', '0')
OP_8E()
OP_D0('STRING', 'PhoneMode_PowerOff')
OP_B0('$SW_PHONE_MODE')
OP_8E()
OP_D0('INT', '1')
OP_B0('$SF_Phone_Open')
OP_8E()
SetText(
    'text00760',
    '@box00',
    [[
<PRE @box00>[text00760]
その問いは無視してすかさずケータイを取り出し、耳に添えた。

<voice name="倫太郎" class="VID_OKA" src="voice/OKA_0065" mode="on">
「俺だ。“機関”のエージェントに捕まった。……ああ、牧瀬紅莉栖だ、あの女には気を付けろ……いや問題ない、ここはなんとか切り抜け――」

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '512')
OP_D0('INT', '0')
OP_91()
OP_CE('PosSt', 'STBUF5', '512', '@')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '1800')
OP_D0('INT', '0')
OP_91()
OP_D0('INT', '0')
OP_91()
OP_D0('STRING', 'CRS_AMA03')
OP_CE('St', 'STBUF5', '1800', '@', '@', 'CRS_AMA03')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '267')
OP_D0('STRING', 'true')
OP_CE('FadeSt', 'STBUF5', '267', 'true')
OP_8E()
SetText(
    'text00770',
    '@box00',
    [[
<PRE @box00>[text00770]
<voice name="紅莉栖" class="VID_CRS" src="voice/CRS_0007" mode="on">
「…………っ」

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '267')
OP_D0('STRING', 'true')
OP_CE('DeleteSt', 'STBUF5', '267', 'true')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '512')
OP_D0('INT', '0')
OP_91()
OP_CE('PosSt', 'STBUF5', '512', '@')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '1800')
OP_D0('INT', '0')
OP_91()
OP_D0('INT', '0')
OP_91()
OP_D0('STRING', 'CRS_ALA03')
OP_CE('St', 'STBUF5', '1800', '@', '@', 'CRS_ALA03')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '133')
OP_D0('STRING', 'true')
OP_CE('FadeSt', 'STBUF5', '133', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF4')
OP_24('BGBUF4')
OP_8E()
OP_D0('STRING', 'BGBUF4')
OP_D0('INT', '5000')
OP_CE('CreatePlainSP', 'BGBUF4', '5000')
OP_8E()
OP_D0('INT', '32')
OP_39('32')
OP_8E()
OP_D0('INT', '0')
OP_D0('STRING', 'true')
OP_CE('DeleteAllSt', '0', 'true')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '0')
OP_D0('STRING', 'true')
OP_CE('DeleteSt', 'STBUF5', '0', 'true')
OP_8E()
OP_D0('INT', '10')
OP_B0('$SW_PHONE_PRI')
OP_8E()
OP_D0('INT', '0')
OP_B0('$SF_Phone_Open')
OP_8E()
OP_D0('INT', '1')
OP_CE('PhoneOperation', '1')
OP_8E()
OP_D0('STRING', 'BGBUF4')
OP_D0('INT', '266')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_CE('FadeDelete', 'BGBUF4', '266', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF4')
OP_24('BGBUF4')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '512')
OP_D0('INT', '0')
OP_91()
OP_CE('PosSt', 'STBUF5', '512', '@')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '1800')
OP_D0('INT', '0')
OP_91()
OP_D0('INT', '0')
OP_91()
OP_D0('STRING', 'CRS_AMA03')
OP_CE('St', 'STBUF5', '1800', '@', '@', 'CRS_AMA03')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '267')
OP_D0('STRING', 'true')
OP_CE('FadeSt', 'STBUF5', '267', 'true')
OP_8E()
SetText(
    'text00780',
    '@box00',
    [[
<PRE @box00>[text00780]
いきなり紅莉栖は俺のケータイを取り上げてしまった。

なんという早業。あまりに華麗な奇襲攻撃だったため、俺は抵抗することすらできなかった。

<voice name="倫太郎" class="VID_OKA" src="voice/OKA_0066" mode="on">
「くっ、なにをする！」

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_D0('STRING', '@BGM*')
OP_D0('INT', '533')
OP_D0('INT', '0')
OP_D0('STRING', 'null')
OP_43('@BGM*', '533', '0', 'null')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '1800')
OP_D0('INT', '0')
OP_91()
OP_D0('INT', '0')
OP_91()
OP_D0('STRING', 'CRS_AMC04')
OP_CE('St', 'STBUF5', '1800', '@', '@', 'CRS_AMC04')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '267')
OP_D0('STRING', 'true')
OP_CE('FadeSt', 'STBUF5', '267', 'true')
OP_8E()
SetText(
    'text00790',
    '@box00',
    [[
<PRE @box00>[text00790]
<voice name="紅莉栖" class="VID_CRS" src="voice/CRS_0008" mode="on">
「あれ？　このケータイ、電源切れてる」

<voice name="倫太郎" class="VID_OKA" src="voice/OKA_0067" mode="on">
「…………」

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '1800')
OP_D0('INT', '0')
OP_91()
OP_D0('INT', '0')
OP_91()
OP_D0('STRING', 'CRS_AMB04')
OP_CE('St', 'STBUF5', '1800', '@', '@', 'CRS_AMB04')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '267')
OP_D0('STRING', 'true')
OP_CE('FadeSt', 'STBUF5', '267', 'true')
OP_8E()
SetText(
    'text00800',
    '@box00',
    [[
<PRE @box00>[text00800]
<voice name="紅莉栖" class="VID_CRS" src="voice/CRS_0009" mode="on">
「……誰と話していたんですか？」

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('INT', '267')
OP_D0('STRING', 'true')
OP_CE('DeleteAllSt', '267', 'true')
OP_8E()
SetText(
    'text00810',
    '@box00',
    [[
<PRE @box00>[text00810]
探るような視線を向けられ、俺は慌てて目を逸らした。

こいつ……できる。俺のアイデンティティを混乱させ精神崩壊を誘う気か。

立て直せ。俺はこの程度で揺らぎはしないぞ！

<voice name="倫太郎" class="VID_OKA" src="voice/OKA_0068" mode="on">
「き、貴様に答える義理はないが一応教えてやろう。それは俺以外が触ると自動的に電源がオフになる、特別製のケータイなのだっ。フゥーハハハ！」

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '512')
OP_D0('INT', '0')
OP_91()
OP_CE('PosSt', 'STBUF5', '512', '@')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '1800')
OP_D0('INT', '0')
OP_91()
OP_D0('INT', '0')
OP_91()
OP_D0('STRING', 'CRS_AMB04')
OP_CE('St', 'STBUF5', '1800', '@', '@', 'CRS_AMB04')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '267')
OP_D0('STRING', 'true')
OP_CE('FadeSt', 'STBUF5', '267', 'true')
OP_8E()
SetText(
    'text00820',
    '@box00',
    [[
<PRE @box00>[text00820]
そんな特別製を持っているのもすべて機密保持のため。

引ったくるようにケータイを取り戻すと、俺は額に滲んだ冷や汗をそっと拭った。

ふう、焦ったぜ。

<voice name="紅莉栖" class="VID_CRS" src="voice/CRS_0010" mode="on">
「……そう。独り言だったのね」

<voice name="倫太郎" class="VID_OKA" src="voice/OKA_0069" mode="on">
「……っ」

まずい。牧瀬紅莉栖は天才少女と呼ばれるだけあって一筋縄ではいかない。

それどころか俺に精神的揺さぶりをかけてきている！

くっ、ここはひとまず戦略的撤退をした方がよさそうだ。

なんとか隙を突かなければ……！

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '267')
OP_D0('STRING', 'true')
OP_CE('DeleteSt', 'STBUF5', '267', 'true')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '512')
OP_D0('INT', '0')
OP_91()
OP_CE('PosSt', 'STBUF5', '512', '@')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '1800')
OP_D0('INT', '0')
OP_91()
OP_D0('INT', '0')
OP_91()
OP_D0('STRING', 'CRS_ALA01')
OP_CE('St', 'STBUF5', '1800', '@', '@', 'CRS_ALA01')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '267')
OP_D0('STRING', 'true')
OP_CE('FadeSt', 'STBUF5', '267', 'true')
OP_8E()
SetText(
    'text00830',
    '@box00',
    [[
<PRE @box00>[text00830]
と、表情を引き締めた紅莉栖が、いきなり俺に詰め寄ってきた。

至近距離から、その爛々とたぎる大きな瞳でまっすぐに見据えてくる。

なんと強い意志に満ち溢れた眼の輝きなんだ。

俺は思わず見惚れてしまった。

これほどのまっすぐで純粋な瞳の持ち主が、本当に“機関”のエージェントなのか……？

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_D0('STRING', '@BGM11')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'true')
OP_CE('SoundPlay', '@BGM11', '0', '1000', 'true')
OP_8E()
SetText(
    'text00840',
    '@box00',
    [[
<PRE @box00>[text00840]
<voice name="紅莉栖" class="VID_CRS" src="voice/CRS_0011" mode="on">
「さっき、私になにを言おうとしたんですか？」

……さっき？

<voice name="倫太郎" class="VID_OKA" src="voice/OKA_0070" mode="on">
「さっきとはいつのことだ？」

<voice name="紅莉栖" class="VID_CRS" src="voice/CRS_0012" mode="on">
「ほんの１５分くらい前。会見が始まる前に」

なにをバカな。俺がこいつと会ったのは今が初めてだぞ。

１５分前にはまゆりと『うーぱ』のカプセルトイで盛り上がっていたのだ。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '1800')
OP_D0('INT', '0')
OP_91()
OP_D0('INT', '0')
OP_91()
OP_D0('STRING', 'CRS_ALC06')
OP_CE('St', 'STBUF5', '1800', '@', '@', 'CRS_ALC06')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '267')
OP_D0('STRING', 'true')
OP_CE('FadeSt', 'STBUF5', '267', 'true')
OP_8E()
SetText(
    'text00850',
    '@box00',
    [[
<PRE @box00>[text00850]
<voice name="紅莉栖" class="VID_CRS" src="voice/CRS_0013" mode="on">
「私に、なにか言おうとしましたよね？　すごく悲しそうな顔をして」

罠か？　いかにも薄汚い“機関”のやりそうなことだが。

しかしこの少女が、そんな手を使うだろうか。

<voice name="紅莉栖" class="VID_CRS" src="voice/CRS_0014" mode="on">
「まるで、今にも泣き出しそうで、それにすごく辛そうでした」

<voice name="紅莉栖" class="VID_CRS" src="voice/CRS_0015" mode="on">
「……どうして？　私、前にあなたと会ったことありますか？」

牧瀬紅莉栖は冗談を言っているようには見えない。

だからこそ、俺にとってこの女は、得体が知れない。

そうだ、顔に騙されるな！

こいつは冷酷無比なエージェント。

少しでも隙を見せれば負ける……！

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '1800')
OP_D0('INT', '0')
OP_91()
OP_D0('INT', '0')
OP_91()
OP_D0('STRING', 'CRS_ALC05')
OP_CE('St', 'STBUF5', '1800', '@', '@', 'CRS_ALC05')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '267')
OP_D0('STRING', 'true')
OP_CE('FadeSt', 'STBUF5', '267', 'true')
OP_8E()
SetText(
    'text00860',
    '@box00',
    [[
<PRE @box00>[text00860]
<voice name="紅莉栖" class="VID_CRS" src="voice/CRS_0016" mode="on">
「そう言えばなんで私の名前、知ってるんです？」

<voice name="倫太郎" class="VID_OKA" src="voice/OKA_0071" mode="on">
「俺はすべてお見通しなのだ」

なにしろマッドサイエンティストだからな。

<voice name="倫太郎" class="VID_OKA" src="voice/OKA_0072" mode="on">
「天才少女よ、次会うときは敵同士だな！」

<voice name="紅莉栖" class="VID_CRS" src="voice/CRS_0017" mode="on">
「はあ……？」

<voice name="倫太郎" class="VID_OKA" src="voice/OKA_0073" mode="on">
「さらばだ、フゥーハハハ！」

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('STRING', '@BGM*')
OP_D0('INT', '533')
OP_D0('INT', '0')
OP_D0('STRING', 'null')
OP_43('@BGM*', '533', '0', 'null')
OP_8E()
OP_D0('INT', '267')
OP_D0('STRING', 'true')
OP_CE('DeleteAllSt', '267', 'true')
OP_8E()
SetText(
    'text00870',
    '@box00',
    [[
<PRE @box00>[text00870]
俺はその場で１８０度Ｕターンすると、颯爽とした足取りで階段を駆け下りた。

牧瀬紅莉栖の呼び止める声が背後から追ってきたが、敵の言うことを聞くわけにはいかない。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('INT', '9000')
OP_D0('STRING', '#000000')
OP_D0('INT', '533')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_CE('ColorOut', '9000', '#000000', '533', 'null', 'true')
OP_8E()
OP_D0('INT', '4900')
OP_B0('$SW_PHONE_PRI')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_24('BGBUF1')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_D0('INT', '100')
OP_D0('STRING', 'cg/bg/BG07A3.jpg')
OP_CE('BgLoad', 'BGBUF1', '100', 'cg/bg/BG07A3.jpg')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('BGBUF1', '0', '1000', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BG07A3')
OP_CE('SetCharaColor', 'BG07A3')
OP_8E()
OP_D0('INT', '266')
OP_39('266')
OP_8E()
OP_D0('INT', '800')
OP_3A('800')
OP_8E()
OP_D0('STRING', 'OnColor*')
OP_D0('INT', '533')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_CE('FadeDelete', 'OnColor*', '533', 'null', 'true')
OP_8E()
SetText(
    'text00880',
    '@box00',
    [[
<PRE @box00>[text00880]
<voice name="倫太郎" class="VID_OKA" src="voice/OKA_0074" mode="on">
「き、“機関”め、あれほどのエージェントを送り込んでくるとは、ついに本気になったようだな……！」

一気に４階まで駆け下りたところで後ろを振り返り、牧瀬紅莉栖が追いかけてこないという確信を得たところで、俺はこめかみを指で押さえ、深々と息をついた。

<voice name="倫太郎" class="VID_OKA" src="voice/OKA_0075" mode="on">
「だ、だが、俺はまだヤツらに捕まるわけにはいかんのだ……」

さてと、これからどうすべきか。

当初の目的であったドクター中鉢の会見内容については、単なるパクリだと分かった。だから俺があの会場へ戻る意味はもうない。

さっさと帰ろう。

それが最も妥当な選択だ。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('STRING', '上背景')
OP_D0('INT', '10000')
OP_CE('PrintGO', '上背景', '10000')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_24('BGBUF2')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '200')
OP_D0('STRING', 'cg/bg/BG_BLACK.jpg')
OP_CE('BgLoad', 'BGBUF2', '200', 'cg/bg/BG_BLACK.jpg')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('BGBUF2', '0', '1000', 'null', 'true')
OP_8E()
OP_D0('STRING', '上背景')
OP_D0('INT', '1066')
OP_D0('INT', '100')
OP_D0('STRING', 'null')
OP_D0('STRING', 'mask02')
OP_D0('STRING', 'true')
OP_D0('STRING', 'true')
OP_CE('DrawDeleteSG', '上背景', '1066', '100', 'null', 'mask02', 'true', 'true')
OP_8E()
SetText(
    'text00890',
    '@box00',
    [[
<PRE @box00>[text00890]
そこでふと、重大ななにかを忘れていることに気付いた。

はて、なんだっただろうと考えてみる。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('STRING', '上背景')
OP_D0('INT', '10000')
OP_CE('PrintGO', '上背景', '10000')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_24('BGBUF2')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_D0('INT', '100')
OP_D0('STRING', 'cg/bg/BG07A3.jpg')
OP_CE('BgLoad', 'BGBUF1', '100', 'cg/bg/BG07A3.jpg')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('BGBUF1', '0', '1000', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '200')
OP_D0('STRING', 'cg/bg/BG_BLACK.jpg')
OP_CE('BgLoad', 'BGBUF2', '200', 'cg/bg/BG_BLACK.jpg')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '0')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_CE('FadeDelete', 'BGBUF2', '0', 'null', 'true')
OP_8E()
OP_D0('STRING', '上背景')
OP_D0('INT', '1066')
OP_D0('INT', '100')
OP_D0('STRING', 'null')
OP_D0('STRING', 'mask02')
OP_D0('STRING', 'false')
OP_D0('STRING', 'true')
OP_CE('DrawDeleteSG', '上背景', '1066', '100', 'null', 'mask02', 'false', 'true')
OP_8E()
SetText(
    'text00900',
    '@box00',
    [[
<PRE @box00>[text00900]
<voice name="倫太郎" class="VID_OKA" src="voice/OKA_0076" mode="on">
「チィッ！　まゆりを置いてきた……！」

あの足手まといめ。

連れてくるべきではなかった。

あいつの安全を一番に考えていたつもりなのに、俺は油断していたようだ。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
SetText(
    'text00910',
    '@box00',
    [[
<PRE @box00>[text00910]
ひとまずケータイに電話してみよう。場合によってはここに呼びつければいい。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_D0('INT', '0')
OP_CE('PhoneOperation', '0')
OP_8E()
OP_D0('STRING', 'PhoneMode_PowerOff')
OP_B0('$SW_PHONE_MODE')
OP_8E()
OP_D0('INT', '1')
OP_B0('$SF_Phone_Open')
OP_8E()
OP_D0('INT', '533')
OP_39('533')
OP_8E()
OP_D0('STRING', 'PhoneMode_Default')
OP_B0('$SW_PHONE_MODE')
OP_8E()
OP_D0('INT', '1')
OP_B0('$SF_PhoneSD_Disp')
OP_8E()
SetText(
    'text00920',
    '@box00',
    [[
<PRE @box00>[text00920]
そう思って自分のケータイを取り出した。電源を入れる。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_D0('STRING', 'PhoneMode_ReceivingMail')
OP_B0('$SW_PHONE_MODE')
OP_8E()
OP_D0('INT', '16')
OP_39('16')
OP_8E()
OP_D0('INT', '1000')
OP_3A('1000')
OP_8E()
SetText(
    'text00930',
    '@box00',
    [[
<PRE @box00>[text00930]
途端に着信音が鳴った。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_D0('STRING', 'FM_From_XXX0001')
OP_B0('$LR_TARGET_MAILNO')
OP_8E()
OP_CE('macrosys2_RECEIVE_NEW_MAIL')
OP_8E()
SetText(
    'text00940',
    '@box00',
    [[
<PRE @box00>[text00940]
<voice name="倫太郎" class="VID_OKA" src="voice/OKA_0077" mode="on">
「ん……？　メールか？」

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_E4()
OP_8E()
OP_D0('STRING', 'SE03')
OP_D0('INT', '133')
OP_D0('INT', '0')
OP_D0('STRING', 'null')
OP_43('SE03', '133', '0', 'null')
OP_8E()
OP_CE('macrosys2_DISP_RECEIVEBOX')
OP_8E()
OP_D0('INT', '16')
OP_39('16')
OP_8E()
OP_D0('INT', '1000')
OP_3A('1000')
OP_8E()
OP_CE('macrosys2_DISP_RECEIVED_MAIL_DIRECT')
OP_8E()
OP_D0('INT', '16')
OP_39('16')
OP_8E()
OP_D0('INT', '1000')
OP_3A('1000')
OP_8E()
SetText(
    'text00950',
    '@box00',
    [[
<PRE @box00>[text00950]
これは普通のメールではなく、動画付きのムービーメールだ。

送信者は、見覚えのないアドレス。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_D0('STRING', 'PhoneMode_MailSubMenu')
OP_B0('$SW_PHONE_MODE')
OP_8E()
OP_D0('INT', '16')
OP_39('16')
OP_8E()
OP_D0('INT', '500')
OP_3A('500')
OP_8E()
SetText(
    'text00960',
    '@box00',
    [[
<PRE @box00>[text00960]
不審に思いつつ、ムービーを再生してみる。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('STRING', '@BGM*')
OP_D0('INT', '533')
OP_D0('INT', '0')
OP_D0('STRING', 'null')
OP_43('@BGM*', '533', '0', 'null')
OP_8E()
OP_D0('STRING', 'SE01')
OP_D0('INT', '133')
OP_D0('INT', '0')
OP_D0('STRING', 'null')
OP_43('SE01', '133', '0', 'null')
OP_8E()
OP_D0('STRING', 'SE02')
OP_D0('INT', '133')
OP_D0('INT', '0')
OP_D0('STRING', 'null')
OP_43('SE02', '133', '0', 'null')
OP_8E()
OP_D0('STRING', '絵板写')
OP_D0('INT', '20000')
OP_CE('CreatePlainSP', '絵板写', '20000')
OP_8E()
OP_D0('STRING', '絵背景')
OP_D0('INT', '10010')
OP_D0('STRING', 'Center')
OP_D0('STRING', 'Middle')
OP_D0('STRING', 'cg/ibg/ibg778.jpg')
OP_CE('CreateTextureSP', '絵背景', '10010', 'Center', 'Middle', 'cg/ibg/ibg778.jpg')
OP_8E()
OP_D0('STRING', 'ムービーウィンドウ')
OP_D0('INT', '0')
OP_D0('INT', '290')
OP_D0('INT', '38')
OP_D0('INT', '442')
OP_D0('INT', '501')
OP_D0('STRING', 'false')
OP_14('ムービーウィンドウ', '0', '290', '38', '442', '501', 'false')
OP_8E()
OP_D0('STRING', 'ムービーウィンドウ')
OP_D0('STRING', 'ムービーウィンドウ')
OP_2B('ムービーウィンドウ', 'ムービーウィンドウ')
OP_8E()
OP_D0('STRING', 'ムービーウィンドウ/ムービー')
OP_D0('INT', '10100')
OP_D0('INT', '0')
OP_D0('INT', '0')
OP_D0('STRING', 'true')
OP_D0('STRING', 'false')
OP_D0('STRING', 'dx/imv001.ngs')
OP_D0('STRING', 'false')
OP_12('ムービーウィンドウ/ムービー', '10100', '0', '0', 'true', 'false', 'dx/imv001.ngs', 'false')
OP_8E()
OP_D0('STRING', 'ムービーウィンドウ/ムービー')
OP_D0('STRING', 'ムービーウィンドウ/ムービー')
OP_2B('ムービーウィンドウ/ムービー', 'ムービーウィンドウ/ムービー')
OP_8E()
OP_D0('STRING', 'ムービーウィンドウ/ムービー')
OP_D0('STRING', 'Play')
OP_23('ムービーウィンドウ/ムービー', 'Play')
OP_8E()
OP_D0('STRING', 'SE01')
OP_D0('STRING', 'SGSE005L')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'true')
OP_CE('SePlay', 'SE01', 'SGSE005L', '0', '1000', 'true')
OP_8E()
OP_D0('STRING', '絵板写')
OP_D0('INT', '266')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_CE('FadeDelete', '絵板写', '266', 'null', 'true')
OP_8E()
OP_D0('INT', '16')
OP_39('16')
OP_8E()
OP_D0('INT', '3000')
OP_3A('3000')
OP_8E()
SetText(
    'text00970',
    '@box00',
    [[
<PRE @box00>[text00970]
<voice name="倫太郎" class="VID_OKA" src="voice/OKA_0078" mode="on">
「……？」

ノイズのような音と映像が延々と垂れ流されるだけだった。

もしかしてイタズラか？　あるいは牧瀬紅莉栖によるなんらかの攻撃か？　このノイズは実は人をおかしくさせる怪音波だったりするとか。

……いや、あの女にアドレスを教えた覚えはないので、それはさすがに考えすぎだろう。

素直に再生してしまった間抜けっぷりに、俺は小さく舌打ちした。

そもそも今はこんなものに構っている場合ではない。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_D0('STRING', 'FM_From_XXX0001')
OP_B0('$SW_PHONE_MAILCURMNO')
OP_8E()
OP_D0('STRING', 'PhoneMode_ReceivedMail')
OP_B0('$SW_PHONE_MODE')
OP_8E()
OP_D0('STRING', '@ムービーウィンドウ/ムービー')
OP_24('@ムービーウィンドウ/ムービー')
OP_8E()
OP_D0('STRING', 'SE01')
OP_D0('INT', '1')
OP_D0('INT', '0')
OP_D0('STRING', 'null')
OP_43('SE01', '1', '0', 'null')
OP_8E()
OP_D0('INT', '16')
OP_39('16')
OP_8E()
OP_D0('STRING', '絵板写')
OP_D0('INT', '11000')
OP_CE('CreatePlainSP', '絵板写', '11000')
OP_8E()
OP_D0('STRING', 'ムービーウィンドウ')
OP_24('ムービーウィンドウ')
OP_8E()
OP_D0('STRING', '絵背景')
OP_24('絵背景')
OP_8E()
OP_D0('STRING', '絵板写')
OP_D0('INT', '267')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_CE('FadeDelete', '絵板写', '267', 'null', 'true')
OP_8E()
OP_D0('INT', '500')
OP_3A('500')
OP_8E()
OP_CE('macrosys2_RETURN_RECEIVEBOX_FUN')
OP_8E()
OP_D0('INT', '16')
OP_39('16')
OP_8E()
OP_D0('INT', '500')
OP_3A('500')
OP_8E()
OP_D0('INT', '0')
OP_B0('$SW_PHONE_MAILMENUCUR')
OP_8E()
OP_D0('STRING', 'PhoneMode_MailMenu')
OP_B0('$SW_PHONE_MODE')
OP_8E()
OP_D0('INT', '16')
OP_39('16')
OP_8E()
OP_D0('INT', '500')
OP_3A('500')
OP_8E()
OP_D0('INT', '0')
OP_B0('$SW_PHONE_SUBWIN_ALPHA')
OP_8E()
OP_D0('INT', '0')
OP_B0('$SW_PHONE_MENUCUR')
OP_8E()
OP_D0('STRING', 'PhoneMode_DefaultOperatable')
OP_B0('$SW_PHONE_MODE')
OP_8E()
OP_D0('INT', '16')
OP_39('16')
OP_8E()
OP_D0('INT', '500')
OP_3A('500')
OP_8E()
OP_D0('INT', '1')
OP_B0('$SW_PHONE_MENUCUR')
OP_8E()
OP_D0('INT', '16')
OP_39('16')
OP_8E()
OP_D0('INT', '500')
OP_3A('500')
OP_8E()
OP_CE('macrosys2_SELECT_ADDRESSBOOK')
OP_8E()
OP_D0('INT', '16')
OP_39('16')
OP_8E()
OP_D0('INT', '500')
OP_3A('500')
OP_8E()
OP_D0('STRING', 'PhID_MAY')
OP_B0('$LR_TARGET_PhID')
OP_8E()
OP_CE('macrosys2_SELECT_PhID')
OP_8E()
OP_D0('INT', '16')
OP_39('16')
OP_8E()
OP_D0('INT', '500')
OP_3A('500')
OP_8E()
OP_CE('macrosys2_PHONE_ADRSUBMENU_CALL')
OP_8E()
SetText(
    'text00980',
    '@box00',
    [[
<PRE @box00>[text00980]
ムービーメールの再生を途中で止め、アドレス帳からまゆりのケータイを呼び出す。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('macrosys2_PHONE_CALL_EXEC')
OP_8E()
OP_D0('INT', '16')
OP_39('16')
OP_8E()
OP_D0('INT', '2000')
OP_3A('2000')
OP_8E()
SetText(
    'text00990',
    '@box00',
    [[
<PRE @box00>[text00990]
<voice name="倫太郎" class="VID_OKA" src="voice/OKA_0079" mode="on">
「くっ、まゆり。なぜ出ない」

こうなると、会場に戻らざるを得ない。

だがそこでまた牧瀬紅莉栖と鉢合わせしたら、面倒なことになる。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_D0('STRING', '@BGM12')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'true')
OP_CE('SoundPlay', '@BGM12', '0', '1000', 'true')
OP_8E()
SetText(
    'text01000',
    '@box00',
    [[
<PRE @box00>[text01000]
<voice name="倫太郎" class="VID_OKA" src="voice/OKA_0080" mode="on">
「ハッ、まさか牧瀬紅莉栖め、まゆりをさらったな……！」

<voice name="倫太郎" class="VID_OKA" src="voice/OKA_0081" mode="on">
「おのれぇぇ。それが“機関”のやり方か……！」

まゆりを置いていくという選択肢は、俺にはなかった。

過保護とは思いつつも、どうしても目が離せないのだ。あの妹的存在は、放っておくと勝手にフラフラとどこかへ行ってしまいそうな危うさがある。

どこかとはすなわち、ここではないどこか。

昔から、まゆりにはそういうところがあった。

……俺が鳳凰院凶真となったのも、そんなまゆりの“危うさ”が原因だったりする。

<voice name="倫太郎" class="VID_OKA" src="voice/OKA_0082" mode="on">
「戻るしかないか……」

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_D0('INT', '3000')
OP_B0('$SW_PHONE_PRI')
OP_8E()
OP_CE('macrosys2_CANCEL_PHONE_CALL')
OP_8E()
OP_D0('INT', '16')
OP_39('16')
OP_8E()
OP_D0('INT', '1000')
OP_3A('1000')
OP_8E()
OP_CE('macrosys2_CLOSE_PHONE_WINDOW')
OP_8E()
SetText(
    'text01010',
    '@box00',
    [[
<PRE @box00>[text01010]
また８階まで階段を上るかと思うと、げんなりした。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('INT', '9000')
OP_D0('STRING', '#000000')
OP_D0('INT', '533')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_CE('ColorOut', '9000', '#000000', '533', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_24('BGBUF1')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_D0('INT', '100')
OP_D0('STRING', 'cg/bg/BG06A3.jpg')
OP_CE('BgLoad', 'BGBUF1', '100', 'cg/bg/BG06A3.jpg')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('BGBUF1', '0', '1000', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BG06A3')
OP_CE('SetCharaColor', 'BG06A3')
OP_8E()
OP_D0('INT', '266')
OP_39('266')
OP_8E()
OP_D0('INT', '800')
OP_3A('800')
OP_8E()
OP_D0('STRING', 'OnColor*')
OP_D0('INT', '533')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_CE('FadeDelete', 'OnColor*', '533', 'null', 'true')
OP_8E()
OP_D0('INT', '4900')
OP_B0('$SW_PHONE_PRI')
OP_8E()
SetText(
    'text01020',
    '@box00',
    [[
<PRE @box00>[text01020]
会場へと戻ると、ドクター中鉢の会見がちょうど終わったところだった。

壇上は無人で、すでにエセ発明家は退席した後だった。

２０人ほどの聴衆も、おのおの帰り支度を始めようとしている。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_D0('STRING', '@BGM*')
OP_D0('INT', '533')
OP_D0('INT', '0')
OP_D0('STRING', 'null')
OP_43('@BGM*', '533', '0', 'null')
OP_8E()
SetText(
    'text01030',
    '@box00',
    [[
<PRE @box00>[text01030]
まゆりはすぐに見つかった。

会場の隅で、１人でキョロキョロと周囲を見回している。

どうやら拉致されたわけではなかったらしい。

近くに牧瀬紅莉栖の姿は見当たらない。

これは俺にとって好都合だった。

<voice name="倫太郎" class="VID_OKA" src="voice/OKA_0083" mode="on">
「くくく、あの女、俺に怖じ気づいたか」

<voice name="倫太郎" class="VID_OKA" src="voice/OKA_0084" mode="on">
「よかろう。今日のところは見逃してやるとしよう」

というわけで周囲を警戒しつつ、まゆりの元へ駆け寄った。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '512')
OP_D0('INT', '0')
OP_91()
OP_CE('PosSt', 'STBUF5', '512', '@')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '1800')
OP_D0('INT', '0')
OP_91()
OP_D0('INT', '0')
OP_91()
OP_D0('STRING', 'MAY_ALC04')
OP_CE('St', 'STBUF5', '1800', '@', '@', 'MAY_ALC04')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '267')
OP_D0('STRING', 'true')
OP_CE('FadeSt', 'STBUF5', '267', 'true')
OP_8E()
OP_D0('STRING', '@BGM13')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'true')
OP_CE('SoundPlay', '@BGM13', '0', '1000', 'true')
OP_8E()
SetText(
    'text01040',
    '@box00',
    [[
<PRE @box00>[text01040]
<voice name="倫太郎" class="VID_OKA" src="voice/OKA_0085" mode="on">
「まゆり、なぜ電話に出ない。そろそろ帰るぞ」

<voice name="まゆり" class="VID_MAY" src="voice/MAY_0026" mode="on">
「あ、オカリン。『メタルうーぱ』がいなくなっちゃった」

しょんぼり顔で俺に訴えてくる。

<voice name="倫太郎" class="VID_OKA" src="voice/OKA_0086" mode="on">
「いなくなった？　勝手に動き出したのか。それは実にファンタジーだな」

<voice name="まゆり" class="VID_MAY" src="voice/MAY_0027" mode="on">
「落としたみたい……」

なるほど、それで探していたのか。

実にどうでもいいことだ。

<voice name="倫太郎" class="VID_OKA" src="voice/OKA_0087" mode="on">
「見つからないなら諦めろ。また当てればいい」

<voice name="まゆり" class="VID_MAY" src="voice/MAY_0028" mode="on">
「当たりっこないよ。だってね、『メタルうーぱ』はネットオークションで、１万円近いプレミアが付いてるんだよ？」

<voice name="倫太郎" class="VID_OKA" src="voice/OKA_0088" mode="on">
「な……に……？」

そ、そんな値があの小さなオモチャに……？

<voice name="倫太郎" class="VID_OKA" src="voice/OKA_0089" mode="on">
「まゆりよ、いったいどこで落としたのだ！？」

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '1800')
OP_D0('INT', '0')
OP_91()
OP_D0('INT', '0')
OP_91()
OP_D0('STRING', 'MAY_ALA03')
OP_CE('St', 'STBUF5', '1800', '@', '@', 'MAY_ALA03')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '267')
OP_D0('STRING', 'true')
OP_CE('FadeSt', 'STBUF5', '267', 'true')
OP_8E()
SetText(
    'text01050',
    '@box00',
    [[
<PRE @box00>[text01050]
<voice name="まゆり" class="VID_MAY" src="voice/MAY_0029" mode="on">
「分かんないから探してるんだよぅ……。あと、見つけても、売らないからねー？」

<voice name="倫太郎" class="VID_OKA" src="voice/OKA_0090" mode="on">
「フハハ、その１万円、この俺の研究資金にしてやる」

<voice name="まゆり" class="VID_MAY" src="voice/MAY_0030" mode="on">
「だから、売らないってばー。まゆしぃの名前書いちゃったし」

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('INT', '267')
OP_D0('STRING', 'true')
OP_CE('DeleteAllSt', '267', 'true')
OP_8E()
SetText(
    'text01060',
    '@box00',
    [[
<PRE @box00>[text01060]
というわけで、目を皿のようにして『メタルうーぱ』を探すことにした。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
SetText(
    'text01070',
    '@box00',
    [[
<PRE @box00>[text01070]
<voice name="まゆり" class="VID_MAY" src="voice/MAY_0031" mode="on">
「トゥットゥルー♪　うーぱさんうーぱさん、出ておいでー」

まゆりがそんな風に呼びかけているが、出てくるわけがない。

ちなみに“トゥットゥルー♪”とはまゆりの好きなフレーズで、色々な場面で口にする。

意味は……聞いたことはない。

『メタルうーぱ』は、なかなか見つからなかった。

ということは落としたのは会場内ではなく、カプセルトイが置いてある７階の踊り場の方なのだろうか。

あるいは、落ちている『メタルうーぱ』を拾った人物が、プレミア価格に目がくらみ持ち帰った可能性がある。

それを想像すると俺は悔しさに身悶えるしかなかった。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
SetText(
    'text01080',
    '@box00',
    [[
<PRE @box00>[text01080]
<voice name="倫太郎" class="VID_OKA" src="voice/OKA_0091" mode="on">
「おのれ、金にしか興味のない下劣なヤツめ、恥を知れ……！」

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '896')
OP_D0('INT', '0')
OP_91()
OP_CE('PosSt', 'STBUF5', '896', '@')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '1800')
OP_D0('INT', '0')
OP_91()
OP_D0('INT', '0')
OP_91()
OP_D0('STRING', 'MAY_ASA02')
OP_CE('St', 'STBUF5', '1800', '@', '@', 'MAY_ASA02')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '267')
OP_D0('STRING', 'true')
OP_CE('FadeSt', 'STBUF5', '267', 'true')
OP_8E()
SetText(
    'text01090',
    '@box00',
    [[
<PRE @box00>[text01090]
<voice name="まゆり" class="VID_MAY" src="voice/MAY_0032" mode="on">
「オカリンもねー」

くっ、まゆりにツッコミを入れられるとは。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('INT', '9000')
OP_D0('STRING', '#000000')
OP_D0('INT', '533')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_CE('ColorOut', '9000', '#000000', '533', 'null', 'true')
OP_8E()
OP_D0('INT', '0')
OP_D0('STRING', 'true')
OP_CE('DeleteAllSt', '0', 'true')
OP_8E()
OP_D0('INT', '2133')
OP_3A('2133')
OP_8E()
OP_D0('STRING', 'OnColor*')
OP_D0('INT', '533')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_CE('FadeDelete', 'OnColor*', '533', 'null', 'true')
OP_8E()
OP_D0('STRING', '@BGM*')
OP_D0('INT', '533')
OP_D0('INT', '0')
OP_D0('STRING', 'null')
OP_43('@BGM*', '533', '0', 'null')
OP_8E()
SetText(
    'text01100',
    '@box00',
    [[
<PRE @box00>[text01100]
<voice name="？？？" class="VID_OKA" src="voice/OKA_0092" mode="on">
「ああああああああああああ――――！」

<voice name="倫太郎" class="VID_OKA" src="voice/OKA_0093" mode="on">
「！？」

な、なんだ、今の声は？

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '384')
OP_D0('INT', '0')
OP_91()
OP_CE('PosSt', 'STBUF5', '384', '@')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '1800')
OP_D0('INT', '0')
OP_91()
OP_D0('INT', '0')
OP_91()
OP_D0('STRING', 'MAY_AMA03')
OP_CE('St', 'STBUF5', '1800', '@', '@', 'MAY_AMA03')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '267')
OP_D0('STRING', 'true')
OP_CE('FadeSt', 'STBUF5', '267', 'true')
OP_8E()
SetText(
    'text01110',
    '@box00',
    [[
<PRE @box00>[text01110]
<voice name="まゆり" class="VID_MAY" src="voice/MAY_0033" mode="on">
「悲鳴……かな？」

普通じゃない。

すでに会場に残っているのは、司会者や数人の係員など数えるほどだ。

会見を見に来ていた連中はそのほとんどが帰ってしまっていて、俺とまゆりを含め半分ほどしかいない。

全員が、今の悲鳴を聞いて身をすくませていた。

不安げに、お互いの顔を見合わせている。

かくいう俺も、あまりに常軌を逸した悲鳴を聞いて、全身が総毛立っていた。

またなのか……？　さっきの爆発騒ぎに続いて、またなにか起きたのか？

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '267')
OP_D0('STRING', 'true')
OP_CE('DeleteSt', 'STBUF5', '267', 'true')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '512')
OP_D0('INT', '0')
OP_91()
OP_CE('PosSt', 'STBUF5', '512', '@')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '1800')
OP_D0('INT', '0')
OP_91()
OP_D0('INT', '0')
OP_91()
OP_D0('STRING', 'MAY_ALA03')
OP_CE('St', 'STBUF5', '1800', '@', '@', 'MAY_ALA03')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '267')
OP_D0('STRING', 'true')
OP_CE('FadeSt', 'STBUF5', '267', 'true')
OP_8E()
SetText(
    'text01120',
    '@box00',
    [[
<PRE @box00>[text01120]
まゆりが、ギュッと俺の手を握りしめてくる。

<voice name="倫太郎" class="VID_OKA" src="voice/OKA_0094" mode="on">
「まゆり、ここにいろ」

俺は一度ゴクリと息を呑むと、覚悟を決めて声のした方へと向かった。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('STRING', '上背景')
OP_D0('INT', '10000')
OP_CE('PrintGO', '上背景', '10000')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_24('BGBUF2')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '2000')
OP_D0('STRING', 'cg/bg/BG_BLACK.jpg')
OP_CE('BgLoad', 'BGBUF2', '2000', 'cg/bg/BG_BLACK.jpg')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('BGBUF2', '0', '1000', 'null', 'true')
OP_8E()
OP_D0('STRING', '上背景')
OP_D0('INT', '533')
OP_D0('INT', '100')
OP_D0('STRING', 'null')
OP_D0('STRING', 'mask02')
OP_D0('STRING', 'true')
OP_D0('STRING', 'true')
OP_CE('DrawDeleteSG', '上背景', '533', '100', 'null', 'mask02', 'true', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF*')
OP_24('BGBUF*')
OP_8E()
OP_D0('INT', '0')
OP_D0('STRING', 'true')
OP_CE('DeleteAllSt', '0', 'true')
OP_8E()
OP_D0('INT', '9000')
OP_D0('STRING', '#000000')
OP_D0('INT', '0')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_CE('ColorOut', '9000', '#000000', '0', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_24('BGBUF1')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_D0('INT', '100')
OP_D0('STRING', 'cg/bg/BG09A.jpg')
OP_CE('BgLoad', 'BGBUF1', '100', 'cg/bg/BG09A.jpg')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('BGBUF1', '0', '1000', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BG09A')
OP_CE('SetCharaColor', 'BG09A')
OP_8E()
OP_D0('STRING', 'OnColor*')
OP_D0('INT', '533')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_CE('FadeDelete', 'OnColor*', '533', 'null', 'true')
OP_8E()
SetText(
    'text01130',
    '@box00',
    [[
<PRE @box00>[text01130]
階段の方ではなく、さらに奥の方へと続く通路。電気は消され、薄暗い。

そちらの方から声は聞こえた気がした。

腰を低くし、周囲を警戒しながら慎重に歩を進める。

角を曲がってすぐに、“それ”が目に入った。

通路の奥。

なにかが、うつ伏せに倒れている。

誰かが、うつ伏せに倒れている。

ピクリとも動かない。

服装には見覚えがあった。

それがなんなのか。

それが誰なのか。

すぐに理解した。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_D0('INT', '0')
OP_B0('$SF_PhoneSD_Disp')
OP_8E()
OP_D0('INT', '1')
OP_CE('PhoneOperation', '1')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('STRING', '@BGM23')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'true')
OP_CE('SoundPlay', '@BGM23', '0', '1000', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF8')
OP_24('BGBUF8')
OP_8E()
OP_D0('STRING', '絵板写')
OP_24('絵板写')
OP_8E()
OP_D0('STRING', 'BGBUF8')
OP_D0('INT', '4000')
OP_D0('STRING', 'cg/bg/BG_CHI.jpg')
OP_CE('BgLoad', 'BGBUF8', '4000', 'cg/bg/BG_CHI.jpg')
OP_8E()
OP_D0('STRING', 'BGBUF8')
OP_D0('INT', '533')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('BGBUF8', '533', '1000', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_24('BGBUF2')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '3200')
OP_D0('STRING', 'cg/ev/EV_C02C.jpg')
OP_CE('BgLoad', 'BGBUF2', '3200', 'cg/ev/EV_C02C.jpg')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('BGBUF2', '0', '1000', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF3')
OP_24('BGBUF3')
OP_8E()
OP_D0('STRING', 'BGBUF3')
OP_D0('INT', '3300')
OP_D0('STRING', 'cg/ev/EV_C02B2.png')
OP_CE('BgLoad', 'BGBUF3', '3300', 'cg/ev/EV_C02B2.png')
OP_8E()
OP_D0('STRING', 'BGBUF3')
OP_D0('INT', '0')
OP_D0('INT', '96')
OP_D2()
OP_D0('INT', '11')
OP_91()
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_20('BGBUF3', '0', '0', '@', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF3')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('BGBUF3', '0', '1000', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF7')
OP_24('BGBUF7')
OP_8E()
OP_D0('STRING', 'BGBUF7')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('BGBUF7', '0', '1000', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF4')
OP_24('BGBUF4')
OP_8E()
OP_D0('STRING', 'BGBUF4')
OP_D0('INT', '3210')
OP_D0('STRING', 'cg/ev/EV_C02C.jpg')
OP_CE('BgLoad', 'BGBUF4', '3210', 'cg/ev/EV_C02C.jpg')
OP_8E()
OP_D0('STRING', 'BGBUF4')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('BGBUF4', '0', '1000', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF4EX')
OP_D0('INT', '3211')
OP_D0('STRING', 'cg/ev/EV_C02C.jpg')
OP_CE('BgLoad', 'BGBUF4EX', '3211', 'cg/ev/EV_C02C.jpg')
OP_8E()
OP_D0('STRING', 'BGBUF4EX')
OP_D0('STRING', 'SEMIHEAVY')
OP_2D('BGBUF4EX', 'SEMIHEAVY')
OP_8E()
OP_D0('STRING', 'BGBUF4EX')
OP_D0('STRING', 'Passive')
OP_23('BGBUF4EX', 'Passive')
OP_8E()
OP_D0('STRING', 'BGBUF5')
OP_24('BGBUF5')
OP_8E()
OP_D0('STRING', 'BGBUF5')
OP_D0('INT', '3500')
OP_D0('STRING', 'cg/ev/EV_C02B1.png')
OP_CE('BgLoad', 'BGBUF5', '3500', 'cg/ev/EV_C02B1.png')
OP_8E()
OP_D0('STRING', 'BGBUF5')
OP_D0('INT', '0')
OP_D0('INT', '96')
OP_D2()
OP_D0('INT', '11')
OP_91()
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_20('BGBUF5', '0', '0', '@', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF5')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('BGBUF5', '0', '1000', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF6')
OP_24('BGBUF6')
OP_8E()
OP_D0('STRING', 'BGBUF6')
OP_D0('INT', '3600')
OP_D0('STRING', 'cg/ev/EV_C02D.jpg')
OP_CE('BgLoad', 'BGBUF6', '3600', 'cg/ev/EV_C02D.jpg')
OP_8E()
OP_D0('STRING', 'BGBUF6')
OP_D0('INT', '0')
OP_D0('INT', '0')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('BGBUF6', '0', '0', 'null', 'true')
OP_8E()
OP_D0('STRING', 'プロセス')
OP_D0('STRING', 'sg00_01_Thd_NEGAPOSI')
OP_CE('CreateProcessSG', 'プロセス', 'sg00_01_Thd_NEGAPOSI')
OP_8E()
OP_D0('STRING', 'BGBUF8')
OP_D0('INT', '534')
OP_D0('INT', '100')
OP_D0('STRING', 'null')
OP_D0('STRING', 'mask01')
OP_D0('STRING', 'false')
OP_D0('STRING', 'true')
OP_CE('DrawDeleteSG', 'BGBUF8', '534', '100', 'null', 'mask01', 'false', 'true')
OP_8E()
OP_D0('STRING', 'プロセス')
OP_D0('STRING', 'Start')
OP_23('プロセス', 'Start')
OP_8E()
OP_D0('STRING', 'BGBUF4*')
OP_D0('INT', '4264')
OP_D0('INT', '96')
OP_D2()
OP_D0('INT', '0')
OP_91()
OP_D0('STRING', 'DxlAuto')
OP_D0('STRING', 'false')
OP_20('BGBUF4*', '4264', '4264', '@', 'DxlAuto', 'false')
OP_8E()
OP_D0('STRING', 'BGBUF4EX')
OP_D0('INT', '4264')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'false')
OP_25('BGBUF4EX', '4264', '1000', 'null', 'false')
OP_8E()
OP_D0('STRING', 'BGBUF5')
OP_D0('INT', '4264')
OP_D0('INT', '0')
OP_D0('STRING', 'null')
OP_D0('STRING', 'false')
OP_25('BGBUF5', '4264', '0', 'null', 'false')
OP_8E()
OP_D0('STRING', 'BGBUF5')
OP_D0('INT', '4264')
OP_D0('INT', '0')
OP_D0('INT', '0')
OP_91()
OP_D0('STRING', 'DxlAuto')
OP_D0('STRING', 'false')
OP_20('BGBUF5', '4264', '0', '@', 'DxlAuto', 'false')
OP_8E()
OP_D0('STRING', 'BGBUF3')
OP_D0('INT', '4264')
OP_D0('INT', '0')
OP_D0('INT', '0')
OP_91()
OP_D0('STRING', 'DxlAuto')
OP_D0('STRING', 'true')
OP_20('BGBUF3', '4264', '0', '@', 'DxlAuto', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF8')
OP_24('BGBUF8')
OP_8E()
OP_D0('STRING', '絵板写')
OP_24('絵板写')
OP_8E()
OP_D0('STRING', 'BGBUF7')
OP_24('BGBUF7')
OP_8E()
OP_D0('STRING', 'BGBUF4')
OP_24('BGBUF4')
OP_8E()
OP_D0('STRING', 'BGBUF5')
OP_24('BGBUF5')
OP_8E()
OP_D0('STRING', 'プロセス')
OP_24('プロセス')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '0')
OP_D0('INT', '0')
OP_91()
OP_D0('INT', '0')
OP_91()
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_20('BGBUF2', '0', '@', '@', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '0')
OP_D0('INT', '96')
OP_D2()
OP_D0('INT', '0')
OP_91()
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_20('BGBUF2', '0', '0', '@', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF3')
OP_D0('INT', '0')
OP_D0('INT', '0')
OP_91()
OP_D0('INT', '0')
OP_91()
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_20('BGBUF3', '0', '@', '@', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF3')
OP_D0('INT', '0')
OP_D0('INT', '0')
OP_91()
OP_D0('INT', '0')
OP_91()
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_20('BGBUF3', '0', '@', '@', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF6')
OP_24('BGBUF6')
OP_8E()
OP_D0('STRING', 'EV_C02A')
OP_CE('ChkAchieveEVRead', 'EV_C02A')
OP_8E()
SetText(
    'text01140',
    '@box00',
    [[
<PRE @box00>[text01140]
<voice name="倫太郎" class="VID_OKA" src="voice/OKA_0095" mode="on">
「ひっ……」

牧瀬紅莉栖……。

顔ははっきり見えないが。

間違いない。

つい１０分ほど前に、俺に絡んできた、あの生意気な天才少女が。

鮮やかなほどの紅い血溜まりの中に、倒れていた。

死んでいる……。

<voice name="倫太郎" class="VID_OKA" src="voice/OKA_0096" mode="on">
「え、な、なんで……？」

気が付けば俺は身を震わせていた。

どうしよう。逃げたい。逃げ出したい。

わざわざ見に来たりするんじゃなかった。

これは、明らかに異常だ。

普通じゃない。

牧瀬紅莉栖は、誰かに殺されたようにしか見えない。

誰に――？

他には、人の姿はない――

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_D0('STRING', '@BGM*')
OP_D0('INT', '533')
OP_D0('INT', '0')
OP_D0('STRING', 'null')
OP_43('@BGM*', '533', '0', 'null')
OP_8E()
SetText(
    'text01150',
    '@box00',
    [[
<PRE @box00>[text01150]
<voice name="司会者" class="VID_ETC" src="voice/MCA_0002" mode="on">
「う、うわああ……！」

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('STRING', 'BGBUF4')
OP_24('BGBUF4')
OP_8E()
OP_D0('STRING', 'BGBUF4')
OP_D0('INT', '5000')
OP_CE('CreatePlainSP', 'BGBUF4', '5000')
OP_8E()
OP_D0('INT', '32')
OP_39('32')
OP_8E()
OP_D0('INT', '0')
OP_D0('STRING', 'true')
OP_CE('DeleteAllSt', '0', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF4')
OP_D0('INT', '5000')
OP_CE('CreatePlainSP', 'BGBUF4', '5000')
OP_8E()
OP_D0('STRING', 'BGBUF4')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('BGBUF4', '0', '1000', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_24('BGBUF2')
OP_8E()
OP_D0('STRING', 'BGBUF3')
OP_24('BGBUF3')
OP_8E()
OP_D0('STRING', 'BGBUF4EX')
OP_24('BGBUF4EX')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('BGBUF1', '0', '1000', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF4')
OP_D0('INT', '533')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_CE('FadeDelete', 'BGBUF4', '533', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF4')
OP_24('BGBUF4')
OP_8E()
SetText(
    'text01160',
    '@box00',
    [[
<PRE @box00>[text01160]
ギクリとして振り返った。

俺だけでなく、数人の男たちが俺についてきていた。

みんな顔面を蒼白にして、紅莉栖の死体を見ている。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_D0('STRING', '@BGM09')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'true')
OP_CE('SoundPlay', '@BGM09', '0', '1000', 'true')
OP_8E()
SetText(
    'text01170',
    '@box00',
    [[
<PRE @box00>[text01170]
<voice name="司会者" class="VID_ETC" src="voice/MCA_0003" mode="on">
「警察を呼べ！」

震える声で叫んだのは、さっきの会見で司会をしていた男だった。

その声を皮切りに、みんな悲鳴を上げ、一斉に逃げ出していく。

もちろん俺も彼らに続いた。この場に残る理由など、なにもなかった。

牧瀬紅莉栖に同情するより、“逃げ出したい”“怖い”という感情の方が勝っていた。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('STRING', 'GRAOW')
OP_D0('INT', '5000')
OP_CE('CreatePlainSP', 'GRAOW', '5000')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_24('BGBUF2')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '200')
OP_D0('STRING', 'cg/bg/BG06A4.jpg')
OP_CE('BgLoad', 'BGBUF2', '200', 'cg/bg/BG06A4.jpg')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_D0('INT', '100')
OP_D0('STRING', 'cg/bg/BG06A4.jpg')
OP_CE('BgLoad', 'BGBUF1', '100', 'cg/bg/BG06A4.jpg')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('BGBUF1', '0', '1000', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_24('BGBUF2')
OP_8E()
OP_D0('STRING', 'GRAOW')
OP_D0('INT', '533')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_CE('FadeDelete', 'GRAOW', '533', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BG06A4')
OP_CE('SetCharaColor', 'BG06A4')
OP_8E()
OP_D0('INT', '1')
OP_B0('$SF_PhoneSD_Disp')
OP_8E()
OP_D0('INT', '0')
OP_CE('PhoneOperation', '0')
OP_8E()
SetText(
    'text01180',
    '@box00',
    [[
<PRE @box00>[text01180]
会場に戻ると、まゆりが泣きそうな顔で待っていた。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '294')
OP_D0('INT', '0')
OP_91()
OP_CE('PosSt', 'STBUF5', '294', '@')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '1800')
OP_D0('INT', '0')
OP_91()
OP_D0('INT', '0')
OP_91()
OP_D0('STRING', 'MAY_AMC04')
OP_CE('St', 'STBUF5', '1800', '@', '@', 'MAY_AMC04')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '267')
OP_D0('STRING', 'true')
OP_CE('FadeSt', 'STBUF5', '267', 'true')
OP_8E()
SetText(
    'text01190',
    '@box00',
    [[
<PRE @box00>[text01190]
<voice name="まゆり" class="VID_MAY" src="voice/MAY_0034" mode="on">
「オカリン、どうしたの……？」

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '267')
OP_D0('STRING', 'true')
OP_CE('DeleteSt', 'STBUF5', '267', 'true')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '512')
OP_D0('INT', '0')
OP_91()
OP_CE('PosSt', 'STBUF5', '512', '@')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '1800')
OP_D0('INT', '0')
OP_91()
OP_D0('INT', '0')
OP_91()
OP_D0('STRING', 'MAY_ALC04')
OP_CE('St', 'STBUF5', '1800', '@', '@', 'MAY_ALC04')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '267')
OP_D0('STRING', 'true')
OP_CE('FadeSt', 'STBUF5', '267', 'true')
OP_8E()
SetText(
    'text01200',
    '@box00',
    [[
<PRE @box00>[text01200]
<voice name="倫太郎" class="VID_OKA" src="voice/OKA_0097" mode="on">
「で、出るぞっ」

まゆりの手を引いて、一刻も早くこの場から離れることにした。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_D0('INT', '1')
OP_CE('PhoneOperation', '1')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_24('BGBUF2')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '2000')
OP_D0('STRING', 'cg/bg/BG_BLACK.jpg')
OP_CE('BgLoad', 'BGBUF2', '2000', 'cg/bg/BG_BLACK.jpg')
OP_8E()
OP_D0('STRING', '上背景')
OP_D0('INT', '10000')
OP_CE('PrintGO', '上背景', '10000')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('BGBUF2', '0', '1000', 'null', 'true')
OP_8E()
OP_D0('STRING', '上背景')
OP_D0('INT', '533')
OP_D0('INT', '100')
OP_D0('STRING', 'null')
OP_D0('STRING', 'mask02')
OP_D0('STRING', 'true')
OP_D0('STRING', 'true')
OP_CE('DrawDeleteSG', '上背景', '533', '100', 'null', 'mask02', 'true', 'true')
OP_8E()
OP_D0('INT', '0')
OP_D0('STRING', 'true')
OP_CE('DeleteAllSt', '0', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF*')
OP_24('BGBUF*')
OP_8E()
OP_D0('INT', '9000')
OP_D0('STRING', '#000000')
OP_D0('INT', '0')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_CE('ColorOut', '9000', '#000000', '0', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_24('BGBUF1')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_D0('INT', '100')
OP_D0('STRING', 'cg/bg/BG_BLACK.jpg')
OP_CE('BgLoad', 'BGBUF1', '100', 'cg/bg/BG_BLACK.jpg')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('BGBUF1', '0', '1000', 'null', 'true')
OP_8E()
OP_D0('STRING', 'OnColor*')
OP_D0('INT', '0')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_CE('FadeDelete', 'OnColor*', '0', 'null', 'true')
OP_8E()
SetText(
    'text01210',
    '@box00',
    [[
<PRE @box00>[text01210]
階段を駆け下りながら、必死で先ほど見た紅莉栖の遺体の映像を脳裏から追い払おうとした。

でも、ダメだ。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_24('BGBUF2')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '2000')
OP_D0('STRING', 'cg/bg/BG_CHI.jpg')
OP_CE('BgLoad', 'BGBUF2', '2000', 'cg/bg/BG_CHI.jpg')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '133')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('BGBUF2', '133', '1000', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_24('BGBUF1')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_D0('INT', '3100')
OP_D0('STRING', 'cg/ev/EV_C02A.jpg')
OP_CE('BgLoad', 'BGBUF1', '3100', 'cg/ev/EV_C02A.jpg')
OP_8E()
OP_D0('STRING', 'EV_C02A')
OP_CE('ChkAchieveEVRead', 'EV_C02A')
OP_8E()
SetText(
    'text01220',
    '@box00',
    [[
<PRE @box00>[text01220]
死体と言うより、彼女の身体の下に広がっていた血溜まりの鮮烈な紅が、目に焼き付いて離れない。

人の死体というものを、初めて見た。

幸い、俺はこれまで肉親の死には立ち会ったことがなかったから。

誰かの葬式に出たこともなかったから。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('INT', '9000')
OP_D0('STRING', '#FFFFFF')
OP_D0('INT', '133')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_CE('ColorOut', '9000', '#FFFFFF', '133', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('BGBUF1', '0', '1000', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '4000')
OP_D0('STRING', 'cg/bg/BG_WHITE.jpg')
OP_CE('BgLoad', 'BGBUF2', '4000', 'cg/bg/BG_WHITE.jpg')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('BGBUF2', '0', '1000', 'null', 'true')
OP_8E()
OP_D0('STRING', 'OnColor*')
OP_D0('INT', '0')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_CE('FadeDelete', 'OnColor*', '0', 'null', 'true')
OP_8E()
OP_D0('STRING', '上背景')
OP_D0('INT', '10000')
OP_CE('PrintGO', '上背景', '10000')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '0')
OP_D0('INT', '0')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('BGBUF2', '0', '0', 'null', 'true')
OP_8E()
OP_D0('STRING', '上背景')
OP_D0('INT', '133')
OP_D0('INT', '1000')
OP_D0('INT', '0')
OP_D0('INT', '250')
OP_D0('STRING', 'null')
OP_D0('STRING', 'mask06')
OP_D0('STRING', 'false')
OP_D0('STRING', 'true')
OP_CE('DrawTransitionSG', '上背景', '133', '1000', '0', '250', 'null', 'mask06', 'false', 'true')
OP_8E()
OP_D0('STRING', '上背景')
OP_D0('INT', '10000')
OP_CE('PrintGO', '上背景', '10000')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('BGBUF2', '0', '1000', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_D0('INT', '0')
OP_D0('INT', '0')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('BGBUF1', '0', '0', 'null', 'true')
OP_8E()
OP_D0('STRING', '上背景')
OP_D0('INT', '133')
OP_D0('INT', '1000')
OP_D0('INT', '0')
OP_D0('INT', '250')
OP_D0('STRING', 'null')
OP_D0('STRING', 'mask06')
OP_D0('STRING', 'false')
OP_D0('STRING', 'true')
OP_CE('DrawTransitionSG', '上背景', '133', '1000', '0', '250', 'null', 'mask06', 'false', 'true')
OP_8E()
OP_D0('INT', '9000')
OP_D0('STRING', '#FFFFFF')
OP_D0('INT', '0')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_CE('ColorOut', '9000', '#FFFFFF', '0', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '200')
OP_D0('STRING', 'cg/bg/BG_CHI.jpg')
OP_CE('BgLoad', 'BGBUF2', '200', 'cg/bg/BG_CHI.jpg')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('BGBUF2', '0', '1000', 'null', 'true')
OP_8E()
OP_D0('STRING', 'OnColor*')
OP_D0('INT', '533')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_CE('FadeDelete', 'OnColor*', '533', 'null', 'true')
OP_8E()
SetText(
    'text01230',
    '@box00',
    [[
<PRE @box00>[text01230]
死体を見たのは、初めてで。

恐怖――と言うよりは気持ち悪さを覚えて、ゾクリと背筋を悪寒が走ったけれど。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('INT', '9000')
OP_D0('STRING', '#000000')
OP_D0('INT', '533')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_CE('ColorOut', '9000', '#000000', '533', 'null', 'true')
OP_8E()
OP_D0('INT', '0')
OP_D0('STRING', 'true')
OP_CE('DeleteAllSt', '0', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF*')
OP_24('BGBUF*')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_D0('INT', '100')
OP_D0('STRING', 'cg/bg/BG_BLACK.jpg')
OP_CE('BgLoad', 'BGBUF1', '100', 'cg/bg/BG_BLACK.jpg')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('BGBUF1', '0', '1000', 'null', 'true')
OP_8E()
OP_D0('STRING', 'OnColor*')
OP_D0('INT', '0')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_CE('FadeDelete', 'OnColor*', '0', 'null', 'true')
OP_8E()
SetText(
    'text01240',
    '@box00',
    [[
<PRE @box00>[text01240]
その程度の感想しか、抱けなかった。

それ以上の感想は、浮かばなかった。

俺と牧瀬紅莉栖の関係は、所詮その程度のものでしかない――

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('STRING', '@BGM*')
OP_D0('INT', '533')
OP_D0('INT', '0')
OP_D0('STRING', 'null')
OP_43('@BGM*', '533', '0', 'null')
OP_8E()
OP_D0('INT', '533')
OP_3A('533')
OP_8E()
OP_D0('INT', '9000')
OP_D0('STRING', '#000000')
OP_D0('INT', '0')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_CE('ColorOut', '9000', '#000000', '0', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_24('BGBUF1')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_D0('INT', '100')
OP_D0('STRING', 'cg/bg/BG40A.jpg')
OP_CE('BgLoad', 'BGBUF1', '100', 'cg/bg/BG40A.jpg')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('BGBUF1', '0', '1000', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BG40A')
OP_CE('SetCharaColor', 'BG40A')
OP_8E()
OP_D0('INT', '1066')
OP_3A('1066')
OP_8E()
OP_D0('STRING', 'OnColor*')
OP_D0('INT', '533')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_CE('FadeDelete', 'OnColor*', '533', 'null', 'true')
OP_8E()
OP_D0('STRING', 'SE01')
OP_D0('STRING', 'SGSE008')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'false')
OP_CE('SePlay', 'SE01', 'SGSE008', '0', '1000', 'false')
OP_8E()
OP_D0('STRING', 'SE01')
OP_CE('WaitPlayHalfSG', 'SE01')
OP_8E()
OP_D0('INT', '0')
OP_CE('PhoneOperation', '0')
OP_8E()
SetText(
    'text01250',
    '@box00',
    [[
<PRE @box00>[text01250]
<voice name="倫太郎" class="VID_OKA" src="voice/OKA_0098" mode="on">
「はあ、はあ……」

中央通りまで出て、やっと俺は立ち止まった。

全速力で階段を駆け下りてきたこともあり、息が切れて苦しい。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '512')
OP_D0('INT', '0')
OP_91()
OP_CE('PosSt', 'STBUF5', '512', '@')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '1800')
OP_D0('INT', '0')
OP_91()
OP_D0('INT', '0')
OP_91()
OP_D0('STRING', 'MAY_ALA03')
OP_CE('St', 'STBUF5', '1800', '@', '@', 'MAY_ALA03')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '267')
OP_D0('STRING', 'true')
OP_CE('FadeSt', 'STBUF5', '267', 'true')
OP_8E()
SetText(
    'text01260',
    '@box00',
    [[
<PRE @box00>[text01260]
<voice name="まゆり" class="VID_MAY" src="voice/MAY_0035" mode="on">
「ねぇねぇ、なにがあったのー？　顔色、すごく悪いけど……」

まゆりはケロッとしている。

あの現場を見ていないからだろう。

それにしても息すら切れていないとは。

こいつって、鈍くさそうに見えて実は運動神経はいいんだよな。

<voice name="倫太郎" class="VID_OKA" src="voice/OKA_0099" mode="on">
「人が……死んでた」

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '1800')
OP_D0('INT', '0')
OP_91()
OP_D0('INT', '0')
OP_91()
OP_D0('STRING', 'MAY_ALA04')
OP_CE('St', 'STBUF5', '1800', '@', '@', 'MAY_ALA04')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '267')
OP_D0('STRING', 'true')
OP_CE('FadeSt', 'STBUF5', '267', 'true')
OP_8E()
SetText(
    'text01270',
    '@box00',
    [[
<PRE @box00>[text01270]
<voice name="まゆり" class="VID_MAY" src="voice/MAY_0036" mode="on">
「え……」

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('INT', '267')
OP_D0('STRING', 'true')
OP_CE('DeleteAllSt', '267', 'true')
OP_8E()
SetText(
    'text01280',
    '@box00',
    [[
<PRE @box00>[text01280]
何度か、深呼吸。

まだ脳裏にあの血の色は残っているが。

それでも、だいぶ落ち着いてきた。

牧瀬紅莉栖は殺された。

誰が犯人かは分からない。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('STRING', 'GRAOW')
OP_D0('INT', '5000')
OP_CE('CreatePlainSP', 'GRAOW', '5000')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_24('BGBUF2')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '200')
OP_D0('STRING', 'cg/bg/BG13A1.jpg')
OP_CE('BgLoad', 'BGBUF2', '200', 'cg/bg/BG13A1.jpg')
OP_8E()
OP_D0('INT', '0')
OP_D0('STRING', 'true')
OP_CE('DeleteAllSt', '0', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_D0('INT', '100')
OP_D0('STRING', 'cg/bg/BG13A1.jpg')
OP_CE('BgLoad', 'BGBUF1', '100', 'cg/bg/BG13A1.jpg')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('BGBUF1', '0', '1000', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_24('BGBUF2')
OP_8E()
OP_D0('STRING', 'GRAOW')
OP_D0('INT', '533')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_CE('FadeDelete', 'GRAOW', '533', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BG13A1')
OP_CE('SetCharaColor', 'BG13A1')
OP_8E()
SetText(
    'text01290',
    '@box00',
    [[
<PRE @box00>[text01290]
サイレンが遠くで聞こえるから、もうすぐ救急車が来るだろう。

その後、警察も押しかけてきて、ここは大騒ぎになる。

でも今はまだ、夏休みの秋葉原を歩く多くの人たちが、この事件に気付いていない。

みんな、いつもと同じように歩いている。

家電や、萌えや、エロを求めて、歩いている。

いつもの、秋葉原だ。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('macrosys2_OPEN_PHONE_WINDOW')
OP_8E()
SetText(
    'text01300',
    '@box00',
    [[
<PRE @box00>[text01300]
俺は、なんとなく、ポケットの中からケータイを取り出していた。

特に目的があったわけじゃなかった。

あ、そうだ、牧瀬紅莉栖のことを教えてくれたダルに、さっき俺が見た驚くべき事件を伝えてやろう。そう思った。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_E4()
OP_8E()
OP_CE('macrosys2_SELECT_ADDRESSBOOK')
OP_8E()
OP_D0('INT', '16')
OP_39('16')
OP_8E()
OP_D0('INT', '500')
OP_3A('500')
OP_8E()
OP_D0('STRING', 'PhID_DAR')
OP_B0('$LR_TARGET_PhID')
OP_8E()
OP_CE('macrosys2_SELECT_PhID')
OP_8E()
OP_D0('INT', '16')
OP_39('16')
OP_8E()
OP_D0('INT', '500')
OP_3A('500')
OP_8E()
OP_CE('macrosys2_PHONE_ADRSUBMENU_MAIL')
OP_8E()
OP_D0('INT', '16')
OP_39('16')
OP_8E()
OP_D0('INT', '500')
OP_3A('500')
OP_8E()
OP_D0('STRING', 'FM_To_DAR0001_0')
OP_B0('$SW_PHONE_SENDMAILNO')
OP_8E()
OP_D0('STRING', 'NO_TARGET')
OP_B0('$SW_PHONE_MAILCURMNO')
OP_8E()
OP_CE('macrosys2_START_SendMailEdit')
OP_8E()
OP_D0('INT', '0')
OP_B0('$SF_PhoneSendMail')
OP_8E()
SetText(
    'text01310',
    '@box00',
    [[
<PRE @box00>[text01310]
不謹慎と言えば、不謹慎だ。

俺は興奮していた。頭に血が上っていたのかも。

あんな出来事をこの目で見てしまった後じゃ、冷静な判断などできない。

人間なんて、所詮そんなもの。

それほど高尚な存在じゃない。

そう、分かっているさ、結局のところ――

ヘドロにも似た穢れた肉から成り立ち。

子宮の中で腐り落ちる精液のごとき膿んだ精神を宿す。

それが人間なんだ。

などとちょっぴり感傷に浸りつつ、ケータイで文章を入力していく。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_D0('STRING', 'FM_To_DAR0001')
OP_B0('$LR_TARGET_MAILNO')
OP_8E()
OP_CE('macrosys2_SendMailEdit_NEXT')
OP_8E()
SetText(
    'text01320',
    '@box00',
    [[
<PRE @box00>[text01320]
『牧瀬紅莉栖が男に刺されたみたいだ。男が誰かは知らないけどさ。ヤバいかも。大丈夫かな』

犯人が男かどうかは分からない。ただなんとなく、女よりは男の方が現実的だな、という気がしただけで、俺の単なる憶測だ。

ついでに言うと、刺殺かどうかも想像。

銃声はしなかったし、あれだけの血溜まりができていたからそう思っただけ。

一方で、明確に『殺された』と書くのはやめた。

なぜなのか、理由は自分でもはっきりしたものはなかった。

あえて言えば、書くことでそれが“確定”してしまいそうな気がしたから、だろうか。

とても後ろめたい気分になりそうだったのだ。

別に、俺が殺したわけじゃないのに。そんな自分の奇妙な心理状態を考えて、苦笑した。

ついさっき、１人の人間の死を目の当たりにしていながら、ほんの数分後には、笑っていられる。

こんな俺は、残酷で冷たい人間なのだろうか。

悪魔的な狂気のマッドサイエンティストとしてはお似合いだ。

親指を、ケータイの送信ボタンに添える。

俺は、

その指に、

軽く力を込めて、

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_D0('STRING', 'PhoneMode_Sending')
OP_B0('$SW_PHONE_MODE')
OP_8E()
SetText(
    'text01330',
    '@box00',
    [[
<PRE @box00>[text01330]
メールを送信した――

その、直後――

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_D0('INT', '0')
OP_B0('$SF_PhoneSD_Disp')
OP_8E()
OP_D0('INT', '1')
OP_B0('$SYSTEM_menu_lock')
OP_8E()
OP_D0('INT', '1')
OP_B0('$SYSTEM_backlog_lock')
OP_8E()
OP_D0('INT', '1')
OP_B0('$SYSTEM_save_lock')
OP_8E()
OP_D0('INT', '1')
OP_B0('$SF_SYSTEMCHIP_HIDE')
OP_8E()
OP_D0('INT', '4000')
OP_B0('$SW_PHONE_PRI')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_24('BGBUF2')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '200')
OP_D0('STRING', 'cg/bg/BG13A3.jpg')
OP_CE('BgLoad', 'BGBUF2', '200', 'cg/bg/BG13A3.jpg')
OP_8E()
OP_D0('STRING', 'SE01')
OP_D0('INT', '266')
OP_D0('INT', '0')
OP_D0('STRING', 'null')
OP_43('SE01', '266', '0', 'null')
OP_8E()
OP_D0('STRING', 'SE02')
OP_D0('INT', '266')
OP_D0('INT', '0')
OP_D0('STRING', 'null')
OP_43('SE02', '266', '0', 'null')
OP_8E()
OP_D0('STRING', '@BGM*')
OP_D0('INT', '266')
OP_D0('INT', '0')
OP_D0('STRING', 'null')
OP_43('@BGM*', '266', '0', 'null')
OP_8E()
OP_D0('STRING', 'ムービー')
OP_D0('INT', '20000')
OP_D0('INT', '0')
OP_D0('INT', '0')
OP_D0('STRING', 'false')
OP_D0('STRING', 'false')
OP_D0('STRING', 'true')
OP_D0('STRING', 'imv005')
OP_CE('CreateMovieSG', 'ムービー', '20000', '0', '0', 'false', 'false', 'true', 'imv005')
OP_8E()
OP_D0('STRING', 'ムービー')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('ムービー', '0', '1000', 'null', 'true')
OP_8E()
OP_D0('STRING', 'ムービー')
OP_D0('STRING', 'Play')
OP_23('ムービー', 'Play')
OP_8E()
OP_D0('INT', '0')
OP_B0('$SF_Phone_Open')
OP_8E()
OP_D0('INT', '1')
OP_CE('PhoneOperation', '1')
OP_8E()
OP_D0('INT', '16')
OP_39('16')
OP_8E()
OP_CE('MovieWaitSG')
OP_8E()
OP_D0('INT', '4900')
OP_B0('$SW_PHONE_PRI')
OP_8E()
OP_D0('INT', '0')
OP_D0('STRING', 'true')
OP_CE('StDeleteAll', '0', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_24('BGBUF1')
OP_8E()
OP_CE('MovieMain')
OP_8E()
OP_D0('INT', '16')
OP_39('16')
OP_8E()
OP_D0('STRING', '@ムービー*')
OP_24('@ムービー*')
OP_8E()
OP_D0('STRING', 'false')
OP_B0('$SYSTEM_menu_lock')
OP_8E()
OP_D0('STRING', 'ムービー')
OP_D0('INT', '20000')
OP_D0('INT', '0')
OP_D0('INT', '0')
OP_D0('STRING', 'false')
OP_D0('STRING', 'false')
OP_D0('STRING', 'true')
OP_D0('STRING', 'imv002')
OP_CE('CreateMovieSG', 'ムービー', '20000', '0', '0', 'false', 'false', 'true', 'imv002')
OP_8E()
OP_D0('STRING', 'WDCOV')
OP_D0('INT', '19990')
OP_D0('STRING', '#000000')
OP_CE('CreateColorSP', 'WDCOV', '19990', '#000000')
OP_8E()
OP_D0('STRING', 'ムービー')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('ムービー', '0', '1000', 'null', 'true')
OP_8E()
OP_D0('STRING', 'ムービー')
OP_D0('STRING', 'Play')
OP_23('ムービー', 'Play')
OP_8E()
OP_CE('macrosys2_Init_Phone')
OP_8E()
OP_D0('STRING', 'WDCOV')
OP_24('WDCOV')
OP_8E()
OP_CE('MovieWaitSG')
OP_8E()
OP_CE('macrosys2_DELETE_MAIL_SG00_01')
OP_8E()
OP_D0('STRING', '０．５７１０２４')
OP_B0('$DGMP')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('STRING', 'BGBUF1')
OP_D0('INT', '0')
OP_CE('BgCopy', 'BGBUF2', 'BGBUF1', '0')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('BGBUF2', '0', '1000', 'null', 'true')
OP_8E()
OP_D0('INT', '0')
OP_B0('$SYSTEM_menu_lock')
OP_8E()
OP_D0('INT', '0')
OP_B0('$SYSTEM_backlog_lock')
OP_8E()
OP_D0('INT', '0')
OP_B0('$SYSTEM_save_lock')
OP_8E()
OP_D0('INT', '0')
OP_B0('$SF_SYSTEMCHIP_HIDE')
OP_8E()
OP_D0('STRING', '@ムービー*')
OP_24('@ムービー*')
OP_8E()
OP_D0('STRING', 'false')
OP_B0('$SYSTEM_menu_lock')
OP_8E()
SetText(
    'text01340',
    '@box00',
    [[
<PRE @box00>[text01340]
<voice name="倫太郎" class="VID_OKA" src="voice/OKA_0100" mode="on">
「――っ」

なんだ、今の、感覚は……？

いや、そんなことよりも……！

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_D0('INT', '0')
OP_B0('$SF_PhoneSD_Disp')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('STRING', '上背景')
OP_D0('INT', '10000')
OP_CE('PrintGO', '上背景', '10000')
OP_8E()
OP_D0('STRING', 'EV_Z01A')
OP_CE('ChkAchieveEVRead', 'EV_Z01A')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '3200')
OP_D0('STRING', 'cg/ev/EV_Z01A.jpg')
OP_CE('BgLoad', 'BGBUF2', '3200', 'cg/ev/EV_Z01A.jpg')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '0')
OP_D0('INT', '210')
OP_D0('INT', '70')
OP_D2()
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_20('BGBUF2', '0', '210', '210', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '306')
OP_D0('INT', '404')
OP_2C('BGBUF2', '306', '404')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '0')
OP_D0('INT', '5000')
OP_D0('INT', '5000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_D0('STRING', 'Smoothing')
OP_CE('ZoomSG', 'BGBUF2', '0', '5000', '5000', 'null', 'true', 'Smoothing')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('BGBUF2', '0', '1000', 'null', 'true')
OP_8E()
OP_D0('STRING', 'GRASHADE')
OP_D0('INT', '3210')
OP_D0('STRING', 'SEMIHEAVY')
OP_CE('SetShadeSG', 'GRASHADE', '3210', 'SEMIHEAVY')
OP_8E()
OP_D0('STRING', 'GRASHADE')
OP_D0('STRING', 'Passive')
OP_23('GRASHADE', 'Passive')
OP_8E()
OP_D0('STRING', 'BGBUF3')
OP_24('BGBUF3')
OP_8E()
OP_D0('STRING', 'BGBUF3')
OP_D0('INT', '4000')
OP_D0('STRING', 'cg/bg/BG_WHITE.jpg')
OP_CE('BgLoad', 'BGBUF3', '4000', 'cg/bg/BG_WHITE.jpg')
OP_8E()
OP_D0('STRING', 'BGBUF3')
OP_D0('STRING', 'AddRender')
OP_23('BGBUF3', 'AddRender')
OP_8E()
OP_D0('STRING', 'BGBUF3')
OP_D0('INT', '0')
OP_D0('INT', '500')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('BGBUF3', '0', '500', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF7')
OP_24('BGBUF7')
OP_8E()
OP_D0('STRING', 'BGBUF7')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('BGBUF7', '0', '1000', 'null', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF7')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('BGBUF7', '0', '1000', 'null', 'true')
OP_8E()
OP_D0('STRING', '上背景')
OP_D0('INT', '133')
OP_D0('INT', '100')
OP_D0('STRING', 'null')
OP_D0('STRING', 'mask18')
OP_D0('STRING', 'false')
OP_D0('STRING', 'true')
OP_CE('DrawDeleteSG', '上背景', '133', '100', 'null', 'mask18', 'false', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '133')
OP_D0('INT', '0')
OP_D0('INT', '0')
OP_D0('STRING', 'Axl2')
OP_D0('STRING', 'false')
OP_20('BGBUF2', '133', '0', '0', 'Axl2', 'false')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '133')
OP_D0('INT', '1050')
OP_D0('INT', '1050')
OP_D0('STRING', 'Axl2')
OP_D0('STRING', 'false')
OP_D0('STRING', 'Smoothing')
OP_CE('ZoomSG', 'BGBUF2', '133', '1050', '1050', 'Axl2', 'false', 'Smoothing')
OP_8E()
OP_D0('STRING', 'BGBUF3')
OP_D0('INT', '133')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_CE('FadeDelete', 'BGBUF3', '133', 'null', 'true')
OP_8E()
OP_D0('STRING', 'GRASHADE')
OP_D0('INT', '1066')
OP_D0('STRING', 'null')
OP_D0('STRING', 'false')
OP_CE('FadeDelete', 'GRASHADE', '1066', 'null', 'false')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '1066')
OP_D0('INT', '1000')
OP_D0('INT', '1000')
OP_D0('STRING', 'Dxl2')
OP_D0('STRING', 'true')
OP_D0('STRING', 'Smoothing')
OP_CE('ZoomSG', 'BGBUF2', '1066', '1000', '1000', 'Dxl2', 'true', 'Smoothing')
OP_8E()
OP_D0('STRING', 'GRASHADE')
OP_24('GRASHADE')
OP_8E()
OP_D0('STRING', 'BGBUF3')
OP_24('BGBUF3')
OP_8E()
OP_D0('STRING', 'BGBUF7')
OP_24('BGBUF7')
OP_8E()
SetText(
    'text01350',
    '@box00',
    [[
<PRE @box00>[text01350]
<voice name="倫太郎" class="VID_OKA" src="voice/OKA_0101" mode="on">
「消えた……」

夏休み。

正午。

秋葉原。

駅から徒歩１分の、中央通り。

そこから――

一瞬にして――

何千人という通行人が――

俺の視界から――

一斉に――

消失した。

これは、夢か？　幻覚でも見ているのか？

分からない。

でも、消えたんだ。

その瞬間を、確かに見たんだ。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('STRING', 'BGBUF1')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('BGBUF1', '0', '1000', 'null', 'true')
OP_8E()
OP_D0('INT', '1')
OP_B0('$SF_PhoneSD_Disp')
OP_8E()
OP_D0('INT', '0')
OP_CE('PhoneOperation', '0')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '1066')
OP_D0('INT', '1000')
OP_D0('INT', '0')
OP_D0('INT', '250')
OP_D0('STRING', 'null')
OP_D0('STRING', 'mask02')
OP_D0('STRING', 'false')
OP_D0('STRING', 'true')
OP_CE('DrawTransitionSG', 'BGBUF2', '1066', '1000', '0', '250', 'null', 'mask02', 'false', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_24('BGBUF2')
OP_8E()
SetText(
    'text01360',
    '@box00',
    [[
<PRE @box00>[text01360]
俺はただ、言葉も出ず、愕然となって、

無人と化した秋葉原に、

ただ１人、

立ち尽くしていて。

混乱し、ふと見上げれば、

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_D0('INT', '1')
OP_CE('PhoneOperation', '1')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('STRING', 'GRABGLINK')
OP_D0('INT', '1024')
OP_D0('INT', '1310')
OP_D0('STRING', '#FF00FF')
OP_1B('GRABGLINK', '1024', '1310', '#FF00FF')
OP_8E()
OP_D0('STRING', 'GRABGLINK')
OP_D0('INT', '0')
OP_D0('INT', '0')
OP_D0('STRING', 'cg/bg/BG10A2U.jpg')
OP_30('GRABGLINK', '0', '0', 'cg/bg/BG10A2U.jpg')
OP_8E()
OP_D0('STRING', 'GRABGLINK')
OP_D0('INT', '0')
OP_D0('INT', '655')
OP_D0('STRING', 'cg/bg/BG10A2D.jpg')
OP_30('GRABGLINK', '0', '655', 'cg/bg/BG10A2D.jpg')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '200')
OP_D0('INT', '0')
OP_D0('INT', '0')
OP_D0('STRING', 'GRABGLINK')
OP_CE('CreateTextureEX', 'BGBUF2', '200', '0', '0', 'GRABGLINK')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '0')
OP_D0('INT', '0')
OP_91()
OP_D0('INT', '732')
OP_D2()
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_20('BGBUF2', '0', '@', '0', 'null', 'true')
OP_8E()
OP_D0('STRING', '@BGM25')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'true')
OP_CE('SoundPlay', '@BGM25', '0', '1000', 'true')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '533')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('BGBUF2', '533', '1000', 'null', 'true')
OP_8E()
SetText(
    'text01370',
    '@box00',
    [[
<PRE @box00>[text01370]
ラジ館のビルに――

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('INT', '2133')
OP_B0('$MTime')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D1('$MTime')
OP_D0('INT', '0')
OP_91()
OP_D0('INT', '489')
OP_D2()
OP_D0('STRING', 'AxlDxl')
OP_D0('STRING', 'false')
OP_20('BGBUF2', '$MTime', '@', '0', 'AxlDxl', 'false')
OP_8E()
OP_D1('$MTime')
OP_3A('$MTime')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '0')
OP_D0('INT', '0')
OP_91()
OP_D0('INT', '489')
OP_D2()
OP_D0('STRING', 'AxlDxl')
OP_D0('STRING', 'true')
OP_20('BGBUF2', '0', '@', '0', 'AxlDxl', 'true')
OP_8E()
SetText(
    'text01380',
    '@box00',
    [[
<PRE @box00>[text01380]
俺たちがついさっきまでいた、８階あたりに――

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('INT', '2133')
OP_B0('$MTime')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D1('$MTime')
OP_D0('INT', '0')
OP_91()
OP_D0('INT', '64')
OP_D2()
OP_D0('STRING', 'AxlDxl')
OP_D0('STRING', 'true')
OP_20('BGBUF2', '$MTime', '@', '0', 'AxlDxl', 'true')
OP_8E()
OP_D1('$MTime')
OP_3A('$MTime')
OP_8E()
OP_D0('STRING', 'BGBUF2')
OP_D0('INT', '0')
OP_D0('INT', '0')
OP_91()
OP_D0('INT', '64')
OP_D2()
OP_D0('STRING', 'DxlAuto')
OP_D0('STRING', 'true')
OP_20('BGBUF2', '0', '@', '0', 'DxlAuto', 'true')
OP_8E()
OP_D0('INT', '1')
OP_CE('PhoneAutoOperation', '1')
OP_8E()
SetText(
    'text01390',
    '@box00',
    [[
<PRE @box00>[text01390]
人工衛星が、突き刺さっていた。

</PRE>]]
)
OP_CE('SetText')
OP_8E()
OP_CE('TypeBegin')
OP_8E()
OP_D0('INT', '0')
OP_B0('$SF_PhoneSD_Disp')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('STRING', '上背景')
OP_D0('INT', '10000')
OP_CE('PrintGO', '上背景', '10000')
OP_8E()
OP_D0('STRING', 'BGBUF4')
OP_24('BGBUF4')
OP_8E()
OP_D0('STRING', 'BGBUF4')
OP_D0('INT', '400')
OP_D0('STRING', 'cg/bg/BG_WHITE.jpg')
OP_CE('BgLoad', 'BGBUF4', '400', 'cg/bg/BG_WHITE.jpg')
OP_8E()
OP_D0('STRING', 'BGBUF4')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('BGBUF4', '0', '1000', 'null', 'true')
OP_8E()
OP_D0('STRING', '上背景')
OP_D0('INT', '1066')
OP_D0('INT', '250')
OP_D0('STRING', 'null')
OP_D0('STRING', 'mask10')
OP_D0('STRING', 'false')
OP_D0('STRING', 'true')
OP_CE('DrawDeleteSG', '上背景', '1066', '250', 'null', 'mask10', 'false', 'true')
OP_8E()
OP_D0('INT', '9000')
OP_D0('STRING', '#FFFFFF')
OP_D0('INT', '0')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_CE('ColorOut', '9000', '#FFFFFF', '0', 'null', 'true')
OP_8E()
OP_D0('INT', '0')
OP_D0('INT', '0')
OP_D0('STRING', 'BG_LINK_OFF')
OP_CE('BGsetLink', '0', '0', 'BG_LINK_OFF')
OP_8E()
OP_D0('INT', '266')
OP_39('266')
OP_8E()
OP_D0('STRING', 'BGBUF*')
OP_24('BGBUF*')
OP_8E()
OP_D0('STRING', '@BGM*')
OP_D0('INT', '533')
OP_D0('INT', '0')
OP_D0('STRING', 'null')
OP_43('@BGM*', '533', '0', 'null')
OP_8E()
OP_D0('STRING', 'OnColor*')
OP_D0('INT', '533')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_CE('FadeDelete', 'OnColor*', '533', 'null', 'true')
OP_8E()
OP_CE('SetPlayModeNormal')
OP_8E()
OP_D1('#CLEAR_CRS')
OP_D1('#CLEAR_MAY')
OP_C7()
OP_D1('#CLEAR_OKA')
OP_D0('STRING', 'true')
OP_C0()
OP_C7()
OP_98('label.if.311')
OP_C8()
OP_D1('#OPChoice')
OP_D0('STRING', 'demo')
OP_C0()
OP_98('label.if.421')
OP_C8()
OP_D0('STRING', 'ムービー')
OP_D0('INT', '9900')
OP_D0('INT', '0')
OP_D0('INT', '0')
OP_D0('STRING', 'false')
OP_D0('STRING', 'false')
OP_D0('STRING', 'true')
OP_D0('STRING', 'op')
OP_CE('CreateMovieSG', 'ムービー', '9900', '0', '0', 'false', 'false', 'true', 'op')
OP_8E()
OP_D0('STRING', 'op')
OP_B0('#OPChoice')
OP_8E()
OP_C9()
OP_CF('label.if.end42')
label('if.421')
OP_C8()
OP_D0('STRING', 'ムービー')
OP_D0('INT', '9900')
OP_D0('INT', '0')
OP_D0('INT', '0')
OP_D0('STRING', 'false')
OP_D0('STRING', 'false')
OP_D0('STRING', 'true')
OP_D0('STRING', 'demo')
OP_CE('CreateMovieSG', 'ムービー', '9900', '0', '0', 'false', 'false', 'true', 'demo')
OP_8E()
OP_D0('STRING', 'demo')
OP_B0('#OPChoice')
OP_8E()
OP_C9()
label('if.end42')
OP_C9()
OP_CF('label.if.end31')
label('if.311')
OP_C8()
OP_D0('STRING', 'ムービー')
OP_D0('INT', '9900')
OP_D0('INT', '0')
OP_D0('INT', '0')
OP_D0('STRING', 'false')
OP_D0('STRING', 'false')
OP_D0('STRING', 'true')
OP_D0('STRING', 'op')
OP_CE('CreateMovieSG', 'ムービー', '9900', '0', '0', 'false', 'false', 'true', 'op')
OP_8E()
OP_D0('STRING', 'op')
OP_B0('#OPChoice')
OP_8E()
OP_C9()
label('if.end31')
OP_D0('STRING', 'ムービー')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('ムービー', '0', '1000', 'null', 'true')
OP_8E()
OP_D0('STRING', 'ムービー')
OP_D0('STRING', 'Play')
OP_23('ムービー', 'Play')
OP_8E()
OP_CE('MovieWaitSG')
OP_8E()
OP_D0('STRING', '@ムービー*')
OP_24('@ムービー*')
OP_8E()
OP_D0('STRING', 'END_SG00')
OP_CE('AchievementOn', 'END_SG00')
OP_8E()
OP_D0('STRING', 'false')
OP_B0('$SYSTEM_menu_lock')
OP_8E()
OP_CE('TextBoxDelete')
OP_8E()
OP_D0('STRING', 'SE01')
OP_D0('INT', '1066')
OP_D0('INT', '0')
OP_D0('STRING', 'null')
OP_43('SE01', '1066', '0', 'null')
OP_8E()
OP_D0('STRING', 'SE02')
OP_D0('INT', '1066')
OP_D0('INT', '0')
OP_D0('STRING', 'null')
OP_43('SE02', '1066', '0', 'null')
OP_8E()
OP_D0('STRING', '@BGM*')
OP_D0('INT', '1066')
OP_D0('INT', '0')
OP_D0('STRING', 'null')
OP_43('@BGM*', '1066', '0', 'null')
OP_8E()
OP_D0('INT', '9000')
OP_D0('STRING', '#000000')
OP_D0('INT', '2133')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_CE('ColorOut', '9000', '#000000', '2133', 'null', 'true')
OP_8E()
OP_D0('STRING', 'SE01')
OP_D0('INT', '266')
OP_D0('INT', '0')
OP_D0('STRING', 'null')
OP_43('SE01', '266', '0', 'null')
OP_8E()
OP_D0('STRING', 'SE02')
OP_D0('INT', '266')
OP_D0('INT', '0')
OP_D0('STRING', 'null')
OP_43('SE02', '266', '0', 'null')
OP_8E()
OP_D0('STRING', '@BGM*')
OP_D0('INT', '266')
OP_D0('INT', '0')
OP_D0('STRING', 'null')
OP_43('@BGM*', '266', '0', 'null')
OP_8E()
OP_D0('STRING', 'OnColor*')
OP_D0('INT', '0')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_CE('FadeDelete', 'OnColor*', '0', 'null', 'true')
OP_8E()
OP_C9()
OP_D5('scene.sg00_01.nss')

BeginFunction('sg00_01_Thd_IM_MAY_01')
OP_97('function.sg00_01_Thd_IM_MAY_01')
OP_C8()
OP_D0('INT', '4000')
OP_39('4000')
OP_8E()
OP_D0('STRING', 'STBUF8')
OP_D0('INT', '267')
OP_D0('STRING', 'false')
OP_CE('DeleteSt', 'STBUF8', '267', 'false')
OP_8E()
OP_D0('STRING', 'STBUF5')
OP_D0('INT', '267')
OP_D0('STRING', 'true')
OP_CE('FadeSt', 'STBUF5', '267', 'true')
OP_8E()
OP_C9()
OP_D7()

BeginFunction('sg00_01_Thd_NEGAPOSI')
OP_97('function.sg00_01_Thd_NEGAPOSI')
OP_C8()
OP_D0('STRING', '@BGBUF6')
OP_D0('INT', '0')
OP_D0('INT', '0')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('@BGBUF6', '0', '0', 'null', 'true')
OP_8E()
OP_D0('INT', '1266')
OP_39('1266')
OP_8E()
OP_D0('STRING', '@BGBUF6')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('@BGBUF6', '0', '1000', 'null', 'true')
OP_8E()
OP_D0('INT', '100')
OP_39('100')
OP_8E()
OP_D0('STRING', '@BGBUF6')
OP_D0('INT', '0')
OP_D0('INT', '0')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('@BGBUF6', '0', '0', 'null', 'true')
OP_8E()
OP_D0('INT', '100')
OP_39('100')
OP_8E()
OP_D0('STRING', '@BGBUF6')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('@BGBUF6', '0', '1000', 'null', 'true')
OP_8E()
OP_D0('INT', '100')
OP_39('100')
OP_8E()
OP_D0('STRING', '@BGBUF6')
OP_D0('INT', '0')
OP_D0('INT', '0')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('@BGBUF6', '0', '0', 'null', 'true')
OP_8E()
OP_D0('INT', '666')
OP_39('666')
OP_8E()
OP_D0('STRING', '@BGBUF6')
OP_D0('INT', '0')
OP_D0('INT', '1000')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('@BGBUF6', '0', '1000', 'null', 'true')
OP_8E()
OP_D0('INT', '100')
OP_39('100')
OP_8E()
OP_D0('STRING', '@BGBUF6')
OP_D0('INT', '0')
OP_D0('INT', '0')
OP_D0('STRING', 'null')
OP_D0('STRING', 'true')
OP_25('@BGBUF6', '0', '0', 'null', 'true')
OP_8E()
OP_C9()
OP_D7()
UpdateFunctionMap()
