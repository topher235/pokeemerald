MagmaHideout_2F_2R_MapScripts::
	.byte 0

MagmaHideout_2F_2R_EventScript_Grunt15::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_15, MagmaHideout_2F_2R_Text_Grunt15Intro, MagmaHideout_2F_2R_Text_Grunt15Defeat
	msgbox MagmaHideout_2F_2R_Text_Grunt15PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_2F_2R_EventScript_Grunt6::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_6, MagmaHideout_2F_2R_Text_Grunt6Intro, MagmaHideout_2F_2R_Text_Grunt6Defeat
	msgbox MagmaHideout_2F_2R_Text_Grunt6PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_2F_2R_EventScript_Grunt7::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_7, MagmaHideout_2F_2R_Text_Grunt7Intro, MagmaHideout_2F_2R_Text_Grunt7Defeat
	msgbox MagmaHideout_2F_2R_Text_Grunt7PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_2F_2R_EventScript_Grunt8::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_8, MagmaHideout_2F_2R_Text_Grunt8Intro, MagmaHideout_2F_2R_Text_Grunt8Defeat
	msgbox MagmaHideout_2F_2R_Text_Grunt8PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_2F_2F_EventScript_SpecialEncounter::
	lock
	faceplayer
	goto_if_set FLAG_SPECIAL_ENCOUNTER_MAGMA_HIDEOUT_COMPLETE, MagmaHideout_2F_2F_EventScript_SpecialEncounterCompleted
	goto_if_unset FLAG_SPECIAL_ENCOUNTER_MAGMA_HIDEOUT_COMPLETE, MagmaHideout_2F_2F_EventScript_SpecialEncounterGreeting
	end

MagmaHideout_2F_2F_EventScript_SpecialEncounterCompleted::
	msgbox MagmaHideout_2F_2F_Text_SpecialEncounterCompleted, MSGBOX_DEFAULT
	release
	end

MagmaHideout_2F_2F_EventScript_SpecialEncounterGreeting::
	msgbox MagmaHideout_2F_2F_Text_SpecialEncounterGreeting, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, MagmaHideout_2F_2F_EventScript_SpecialEncounterBattle
	msgbox MagmaHideout_2F_2F_Text_SpecialEncounterComeBackWhenReady, MSGBOX_DEFAULT
	release
	end

MagmaHideout_2F_2F_EventScript_SpecialEncounterBattle::
	trainerbattle_single TRAINER_SPECIAL_ENCOUNTER_MAGMA_HIDEOUT, MagmaHideout_2F_2F_Text_SpecialEncounterBattleIntro, MagmaHideout_2F_2F_Text_SpecialEncounterBattleDefeat, MagmaHideout_2F_2F_EventScript_SpecialEncounterVictory
	end

MagmaHideout_2F_2F_EventScript_SpecialEncounterVictory::
	msgbox MagmaHideout_2F_2F_Text_SpecialEncounterPostBattle, MSGBOX_DEFAULT
	setflag FLAG_SPECIAL_ENCOUNTER_MAGMA_HIDEOUT_COMPLETE
	bufferspeciesname STR_VAR_1, SPECIES_MEWTWO
	givemon SPECIES_MEWTWO, 35
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, MagmaHideout_2F_2F_EventScript_SendMonToParty
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, MagmaHideout_2F_2F_EventScript_SendMonToPC
	goto Common_EventScript_NoMoreRoomForPokemon
	release
	end

MagmaHideout_2F_2F_EventScript_SendMonToParty::
	call MagmaHideout_2F_2F_EventScript_ReceivedMonFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MagmaHideout_2F_2F_EventScript_ReceivedMon
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto MagmaHideout_2F_2F_EventScript_ReceivedMon
	end

MagmaHideout_2F_2F_EventScript_SendMonToPC::
	call MagmaHideout_2F_2F_EventScript_ReceivedMonFanfare
	setvar VAR_TEMP_1, SPECIES_MEWTWO
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MagmaHideout_2F_2F_EventScript_MonTransferredToPC
	call Common_EventScript_NameReceivedBoxMon
	goto MagmaHideout_2F_2F_EventScript_MonTransferredToPC
	end

MagmaHideout_2F_2F_EventScript_ReceivedMonFanfare::
	bufferspeciesname STR_VAR_2, SPECIES_MEWTWO
	playfanfare MUS_OBTAIN_ITEM
	message MagmaHideout_2F_2F_Text_MonReceived
	waitmessage
	waitfanfare
	bufferspeciesname STR_VAR_1, SPECIES_MEWTWO
	return

MagmaHideout_2F_2F_EventScript_MonTransferredToPC::
	call Common_EventScript_TransferredToPC
	goto MagmaHideout_2F_2F_EventScript_ReceivedMon
	end

MagmaHideout_2F_2F_EventScript_ReceivedMon::
	release
	end

MagmaHideout_2F_2R_Text_Grunt15Intro:
	.string "I don't have a bone to pick with you.\n"
	.string "I'm just following orders!$"

MagmaHideout_2F_2R_Text_Grunt15Defeat:
	.string "I may have lost, but…$"

MagmaHideout_2F_2R_Text_Grunt15PostBattle:
	.string "We dug up something beyond belief!\n"
	.string "And, we got the BLUE ORB!\p"
	.string "All that's left is for our leader to…\n"
	.string "Fufufu… Fwahahaha!$"

MagmaHideout_2F_2R_Text_Grunt6Intro:
	.string "I can't stand heat. Maybe I should've\n"
	.string "joined TEAM AQUA instead…$"

MagmaHideout_2F_2R_Text_Grunt6Defeat:
	.string "Yeah, I really may not be right for\n"
	.string "TEAM MAGMA…$"

MagmaHideout_2F_2R_Text_Grunt6PostBattle:
	.string "Don't you get lonely for the sea\n"
	.string "being in a place like this?$"

MagmaHideout_2F_2R_Text_Grunt7Intro:
	.string "You can hear tremors here sometimes.\p"
	.string "Could it be the volcano rattling?\n"
	.string "Or is it GROU…\p"
	.string "Whoops!\n"
	.string "No, no, never mind!$"

MagmaHideout_2F_2R_Text_Grunt7Defeat:
	.string "You're a fiery battler.\n"
	.string "Just like a volcano!$"

MagmaHideout_2F_2R_Text_Grunt7PostBattle:
	.string "You just happened to win this time,\n"
	.string "but that doesn't matter.\p"
	.string "TEAM MAGMA's goal is about to be\n"
	.string "reached!$"

MagmaHideout_2F_2R_Text_Grunt8Intro:
	.string "One of our guys was freaking out that\n"
	.string "he lost his MAGMA EMBLEM…\p"
	.string "Wait a minute!\n"
	.string "Was it you who found it?$"

MagmaHideout_2F_2R_Text_Grunt8Defeat:
	.string "I'm having trouble believing this…$"

MagmaHideout_2F_2R_Text_Grunt8PostBattle:
	.string "I'm getting this feeling that our plan\n"
	.string "is going to end in failure…$"

MagmaHideout_2F_2F_Text_SpecialEncounterCompleted:
	.string "I may know a lot about these POKéMON,\n"
	.string "but I have much more to learn as a\l"
	.string "trainer.$"

MagmaHideout_2F_2F_Text_SpecialEncounterGreeting:
	.string "My area of research is POKéMON in\n"
	.string "other regions.\p"
	.string "I'm very interested in seeing how\n"
	.string "they stack up against the POKéMON of\l"
	.string "the HOENN region.\p"
	.string "Would you like to test it out?$"

MagmaHideout_2F_2F_Text_SpecialEncounterComeBackWhenReady:
	.string "Come back when you're ready to test\n"
	.string "your POKéMON against my research\l"
	.string "subjects.$"

MagmaHideout_2F_2F_Text_SpecialEncounterBattleIntro:
	.string "Show me what you've learned about\n"
	.string "your POKéMON!$"

MagmaHideout_2F_2F_Text_SpecialEncounterBattleDefeat:
	.string "I have so much research to do!$"

MagmaHideout_2F_2F_Text_SpecialEncounterPostBattle:
	.string "Wow! What an incredible learning\n"
	.string "experience! You and your POKéMON\l"
	.string "make a great team. I have much\l"
	.string "more research to do and MUCH\l"
	.string "more practice I need as a trainer.\p"
	.string "As a thank you for showing me\n"
	.string "just how much I still have to\l"
	.string "learn, please take my newest\l"
	.string "research specimen. I will have my\l"
	.string "hands full with my current POKéMON.$"

MagmaHideout_2F_2F_Text_MonReceived:
	.string "Received MEWTWO from ASDEF.$"
