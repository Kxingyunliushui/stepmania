#ifndef NOTES_H
#define NOTES_H
/*
-----------------------------------------------------------------------------
 Class: Notes

 Desc: Holds note information for a Song.  A Song may have one or more Notess.
	A Notes can be played by one or more Styles.  See StyleDef.h for more info on
	Styles.

 Copyright (c) 2001-2002 by the person(s) listed below.  All rights reserved.
	Chris Danford
-----------------------------------------------------------------------------
*/

#include "GameConstantsAndTypes.h"
#include "Grade.h"
class NoteData;

struct Notes
{
public:
	Notes();
	~Notes();

	void Decompress() const;

public:
	void Compress() const;

	CString GetDescription() const { return Real()->m_sDescription; }
	Difficulty GetDifficulty() const { return Real()->m_Difficulty; }
	int GetMeter() const { return Real()->m_iMeter; }
	const float *GetRadarValues() const { return Real()->m_fRadarValues; }

	void SetDescription(CString desc);
	void SetDifficulty(Difficulty d);
	void SetMeter(int meter);
	void SetRadarValue(int r, float val);
	bool IsAutogen() const;	// Was created by autogen?

	NotesType		m_NotesType;

	void			GetNoteData( NoteData* pNoteDataOut ) const;
	void			SetNoteData( NoteData* pNewNoteData );
	void			SetSMNoteData( const CString &out );
	CString 		GetSMNoteData() const;
	RageColor		GetColor() const;	// a function of difficulty

	// initializers
	void AutogenFrom( Notes *parent, NotesType ntTo );
	void BakeAutoGen();		// makes into an AutoGen Notes into a regular Notes
	void CopyFrom( Notes* pSource, NotesType ntTo );
	void CreateBlank( NotesType ntTo );


	// High scores;
	int m_iNumTimesPlayed;

	struct MemCardScore
	{
		Grade grade;
		float fScore;
	} m_MemCardScores[NUM_PLAYERS];

	bool AddMemCardRecord( PlayerNumber pn, Grade grade, float fScore );	// return true if new high score


	void TidyUpData();

protected:
	/* If this Notes is autogenerated, this will point to the autogen
	 * source.  If this is true, notes_comp will always be NULL. */
	const Notes *parent;

	/* We can have one or both of these; if we have both, they're always identical.
	 * Call Compress() to force us to only have notes_comp; otherwise, creation of 
	 * these is transparent. */
	mutable NoteData *notes;
	mutable CString *notes_comp;

	const Notes *Real() const;

	/* These values are pulled from the autogen source first, if there is one. */
	CString			m_sDescription;		// This text is displayed next to the number of feet when a song is selected
	Difficulty		m_Difficulty;		// difficulty classification
	int				m_iMeter;			// difficulty rating from 1-10
	float			m_fRadarValues[NUM_RADAR_CATEGORIES];	// between 0.0-1.2 starting from 12-o'clock rotating clockwise

	/* If this Notes is autogenerated, make it a real Notes. */
	void DeAutogen();
};

bool CompareNotesPointersByRadarValues(const Notes* pNotes1, const Notes* pNotes2);
bool CompareNotesPointersByMeter(const Notes *pNotes1, const Notes* pNotes2);
bool CompareNotesPointersByDifficulty(const Notes *pNotes1, const Notes *pNotes2);
void SortNotesArrayByDifficulty( vector<Notes*> &arrayNotess );

#endif
