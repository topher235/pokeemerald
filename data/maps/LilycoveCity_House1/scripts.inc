LilycoveCity_House1_MapScripts::
	.byte 0

LilycoveCity_House1_EventScript_Woman::
	lock
	faceplayer
	goto_if_set FLAG_GIVE_INCENSE, LilycoveCity_House1_EventScript_IncenseGiven
	goto_if_unset FLAG_GIVE_INCENSE, LilycoveCity_House1_EventScript_OfferIncense
	release
	end

LilycoveCity_House1_EventScript_OfferIncense::
	msgbox LilycoveCity_House1_Text_OfferIncense, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, LilycoveCity_House1_EventScript_GiveIncense
	msgbox LilycoveCity_House1_Text_IncenseRefused, MSGBOX_NPC
	release
	end

LilycoveCity_House1_EventScript_GiveIncense::
	giveitem ITEM_LAX_INCENSE, 1
	giveitem ITEM_SEA_INCENSE, 1
	setflag FLAG_GIVE_INCENSE
	release
	end

LilycoveCity_House1_EventScript_IncenseGiven::
	msgbox LilycoveCity_House1_Text_IncenseGiven, MSGBOX_NPC
	release
	end

LilycoveCity_House1_EventScript_Charmander::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_CHARMANDER, CRY_MODE_NORMAL
	msgbox LilycoveCity_House1_Text_Charmander, MSGBOX_NPC
	waitmoncry
	release
	end

LilycoveCity_House1_Text_OfferIncense:
	.string "I love burning incense in my home. It's\n"
	.string "a great way to clear up the stuffy air\l"
	.string "and give the home some renewed energy!\p"
	.string "Not to mention! I hear there are some\n"
	.string "POKéMON who can benefit from smelling\l"
	.string "incense.\p"
	.string "My CHARMANDER always loves to help light\n"
	.string "the incense!\p"
	.string "Would you like some incense to take with\n"
	.string "you?$"

LilycoveCity_House1_Text_IncenseRefused:
	.string "Aw, too bad! Well... if you decide you'd\n"
	.string "like some, you know where to find me!$"

LilycoveCity_House1_Text_IncenseGiven:
	.string "I hope you and your POKéMON are enjoying\n"
	.string "the incense I gave you!$"

LilycoveCity_House1_Text_Charmander:
	.string "CHARMANDER: Ruroro?$"

