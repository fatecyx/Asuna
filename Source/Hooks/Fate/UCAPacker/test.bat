Set File=^
Realta Nua VOICE.XP3

Set Dir=J:\Fate\

IF NOT EXIST "%Dir%xp3bak\%File%" Move "%Dir%%File%" "%Dir%xp3bak"

UCAPacker.exe "J:\Fate£¯Stay Night\Fate\UCA" "%Dir%%File%"

@Pause