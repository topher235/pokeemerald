RustboroCity_Flat1_1F_MapScripts::
	.byte 0

RustboroCity_Flat1_1F_EventScript_Man::
	msgbox RustboroCity_Flat1_1F_Text_Man, MSGBOX_NPC
	end

RustboroCity_Flat1_1F_EventScript_Woman::
	msgbox RustboroCity_Flat1_1F_Text_Woman, MSGBOX_NPC
	end

RustboroCity_Flat1_1F_Text_Man:
	.string "Sometimes her eyes are bigger than\n"
	.string "her stomach.$"

RustboroCity_Flat1_1F_Text_Woman:
	.string "I've eaten so much and it looks like\n"
	.string "I haven't even made a dent in these\l"
	.string "nachos!$"
