.set LOCALID_ITEM_LETTER_2_ENCODED, 2

LilycoveCity_House4_MapScripts::
	.byte 0

LilycoveCity_House4_EventScript_Man1::
	lock
	faceplayer
	goto_if_set FLAG_LETTER_1_GIVEN_TO_BE_DECODED, EventScript_Letter1Given
	checkitem ITEM_LETTER_1_ENCODED, 1
	goto_if_eq VAR_RESULT, 1, EventScript_LetterDecoder
	msgbox Text_Greeting, MSGBOX_DEFAULT
	release
	end

EventScript_LetterDecoder::
	goto_if_unset FLAG_LETTER_1_GIVEN_TO_BE_DECODED, EventScript_GiveLetterToBeDecoded
	goto_if_set FLAG_LETTER_1_GIVEN_TO_BE_DECODED, EventScript_Letter1Given
	end

EventScript_GiveLetterToBeDecoded::
	msgbox Text_GiveLetter, MSGBOX_DEFAULT
	removeitem ITEM_LETTER_1_ENCODED
	setflag FLAG_LETTER_1_GIVEN_TO_BE_DECODED
	release
	end

EventScript_Letter1Given::
	goto_if_unset FLAG_LETTER_1_DECODED, EventScript_LetterNotReady
	goto_if_set FLAG_LETTER_1_DECODED, EventScript_Letter1Decoded
	end

EventScript_LetterNotReady::
	msgbox Text_LetterNotReady, MSGBOX_DEFAULT
	release
	end

EventScript_Letter1Decoded::
	checkitem ITEM_LETTER_1_DECODED, 1
	goto_if_eq VAR_RESULT, 1, EventScript_LetterAlreadyGiven
	msgbox Text_ExplainLetter, MSGBOX_DEFAULT
	giveitem ITEM_LETTER_1_DECODED, 1
	checkplayergender
	call_if_eq VAR_RESULT, MALE, EventScript_SetMysticTicketStateBrendanOne
	call_if_eq VAR_RESULT, FEMALE, EventScript_SetMysticTicketStateMayOne
	release
	end

EventScript_SetMysticTicketStateBrendanOne::
	setvar VAR_MYSTIC_TICKET_STATE_BRENDAN, 1
	return

EventScript_SetMysticTicketStateMayOne::
	setvar VAR_MYSTIC_TICKET_STATE_MAY, 1
	return

EventScript_LetterAlreadyGiven::
	msgbox Text_LetterAlreadyGiven, MSGBOX_DEFAULT
	release
	end

EventScript_PickUpLetter2::
	lock
	removeobject LOCALID_ITEM_LETTER_2_ENCODED
	setflag FLAG_LILYCOVE_HOUSE4_LETTER_HIDE
	bufferitemname STR_VAR_1, ITEM_LETTER_2_ENCODED
	msgbox Text_ReceivedLetter2, MSGBOX_DEFAULT
	giveitem ITEM_LETTER_2_ENCODED, 1
	release
	end

Text_LetterNotReady:
	.string "Sorry, the letter isn't ready yet.\n"
	.string "He really knows how to make these\l"
	.string "things incomprehensible.\p"
	.string "I'll call you when it's ready.$"

Text_Greeting:
	.string "My friend can be very cryptic...$"

Text_GiveLetter:
	.string "My friend can be very cryptic...\p"
	.string "Hey! Is that a letter that needs\n"
	.string "decyphering?\l"
	.string "Oh, you must be {PLAYER}!\p"
	.string "My name is LEON. Nice to meet you!\p"
	.string "Agh! He was waiting for you and you\l"
	.string "just missed him.\p"
	.string "If you want, I can take that\n"
	.string "letter and decypher it for you.\p"
	.string "I'll give you a call when it's ready.$"


Text_LetterAlreadyGiven:
	.string "Hopefully you can figure out what\n"
	.string "that letter is supposed to mean.$"

Text_ExplainLetter:
	.string "It took a while, but I finally\n"
	.string "decoded the letter!\p"
	.string "Sorry to say, but this version is\n"
	.string "still not very clear to me.\l"
	.string "Hopefully you can make sense of it.$"

Text_ReceivedLetter2:
	.string "Picked up {STR_VAR_1}.$"
