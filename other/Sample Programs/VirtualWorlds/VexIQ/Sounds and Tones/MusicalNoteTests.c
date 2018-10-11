task main()
{
	int nNote;
	clearDebugStream();

	while (true)
	{
		int nOctave;
		int nNoteInOctave;
		char *pzNote;
		char cNoteName[4];
		nVolume = 4;

		for (nOctave = 0; nOctave < 7; ++nOctave)
		{
			for (nNoteInOctave = 0; nNoteInOctave <= 11; ++nNoteInOctave)
			{
				switch (nNoteInOctave)
				{
				case  0:	pzNote = "Cn ";			break;
				case  1:	pzNote = "Cn#";			break;
				case  2:	pzNote = "Dn ";			break;
				case  3:	pzNote = "Dn#";			break;
				case  4:	pzNote = "En ";			break;
				case  5:	pzNote = "Fn ";			break;
				case  6:	pzNote = "Fn#";			break;
				case  7:	pzNote = "Gn ";			break;
				case  8:	pzNote = "Gn#";			break;
				case  9:	pzNote = "An ";			break;
				case  10:	pzNote = "An#";			break;
				case  11:	pzNote = "Bn ";			break;
				}
				nNote = (nOctave << 4) + nNoteInOctave;

				cNoteName[0] = pzNote[0];
				cNoteName[1] = '1' + nOctave;
				cNoteName[2] = pzNote[2];
				cNoteName[3] = 0;
				drawUserTextLine(2, "Note: %3s", &cNoteName[0]);
				playNote((TMusicalNotes) nNote,  15);
				while (bSoundActive)
				{}
			}
		}
	}

}
