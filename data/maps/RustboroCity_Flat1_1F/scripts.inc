RustboroCity_Flat1_1F_MapScripts::
	.byte 0

RustboroCity_Flat1_1F_EventScript_Man::
	msgbox RustboroCity_Flat1_1F_Text_Man, MSGBOX_NPC
	end

RustboroCity_Flat1_1F_EventScript_Woman::
	lock
	faceplayer
	msgbox RustboroCity_Flat1_1F_Text_Woman, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, RustboroCity_Flat1_1F_EventScript_GiveLeftovers
	msgbox RustboroCity_Flat1_1F_Text_Woman2, MSGBOX_DEFAULT
	release
	end

RustboroCity_Flat1_1F_EventScript_GiveLeftovers::
	giveitem ITEM_LEFTOVERS, 1
	release
	end

RustboroCity_Flat1_1F_Text_Man:
	.string "Sometimes her eyes are bigger than\n"
	.string "her stomach.$"

RustboroCity_Flat1_1F_Text_Woman:
	.string "I've eaten so much and it looks like\n"
	.string "I haven't even made a dent\l"
	.string "in these nachos!\p"
	.string "Would you like some?$"

RustboroCity_Flat1_1F_Text_Woman2:
	.string "Okay. I'll just have my boyfriend\n"
	.string "finish them.$"
