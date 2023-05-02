LetterMsgScript::
	lock
	msgbox LetterText, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

LetterText:
	.string "Here is a letter that is really really long\n"
	.string "and here is a new line.\p"
	.string "But wait! There's more!\p"
	.string "Just kidding :)$"
