/*
 *  Copyright 2007 Victor Hugo Borja <vic@rubyforge.org>
 *            2006-2007 Adrian Thurston <thurston@cs.queensu.ca>
 */

/*  This file is part of Ragel.
 *
 *  Ragel is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 * 
 *  Ragel is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 * 
 *  You should have received a copy of the GNU General Public License
 *  along with Ragel; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA 
 */

#ifndef _RUBYCODEGEN_H
#define _RUBYCODEGEN_H

#include <iostream>
#include <string>
#include <stdio.h>
#include "common.h"
#include "gendata.h"

using std::string;
using std::ostream;

/*
 * RubyCodeGen
 */
struct RubyCodeGen : public CodeGenData
{
	RubyCodeGen( ostream &out ) : 
		CodeGenData(out),
		indent_level(1) { }

public:
	void BREAK( ostream &ret, int targState );
	void GOTO( ostream &ret, int gotoDest, bool inFinish );
	void GOTO_EXPR( ostream &ret, InlineItem *ilItem, bool inFinish );
	void CALL( ostream &ret, int callDest, int targState, bool inFinish );
	void CALL_EXPR( ostream &ret, InlineItem *ilItem, int targState, bool inFinish );
	void RET( ostream &ret, bool inFinish );

	void COND_TRANSLATE();
	void LOCATE_TRANS();

	virtual void writeExec();
	virtual void writeEOF();
	virtual void writeInit();
	virtual void writeData();
	virtual void writeExports();
	virtual void finishRagelDef();

 protected:
	std::ostream &TO_STATE_ACTION_SWITCH();
	std::ostream &FROM_STATE_ACTION_SWITCH();
	std::ostream &EOF_ACTION_SWITCH();
	std::ostream &ACTION_SWITCH();

	std::ostream &COND_KEYS();
	std::ostream &COND_SPACES();
	std::ostream &KEYS();
	std::ostream &INDICIES();
	std::ostream &COND_OFFSETS();
	std::ostream &KEY_OFFSETS();
	std::ostream &INDEX_OFFSETS();
	std::ostream &COND_LENS();
	std::ostream &SINGLE_LENS();
	std::ostream &RANGE_LENS();
	std::ostream &TO_STATE_ACTIONS();
	std::ostream &FROM_STATE_ACTIONS();
	std::ostream &EOF_ACTIONS();
	std::ostream &TRANS_TARGS();
	std::ostream &TRANS_ACTIONS();
	std::ostream &TRANS_TARGS_WI();
	std::ostream &TRANS_ACTIONS_WI();


	void NEXT( ostream &ret, int nextDest, bool inFinish );
	void NEXT_EXPR( ostream &ret, InlineItem *ilItem, bool inFinish );

	int TO_STATE_ACTION( RedStateAp *state );
	int FROM_STATE_ACTION( RedStateAp *state );
	int EOF_ACTION( RedStateAp *state );
	int TRANS_ACTION( RedTransAp *trans );

	/* Determine if we should use indicies. */
	void calcIndexSize();

private:
	string array_type;
	string array_name;

public:

	ostream &START_ARRAY_LINE();
	ostream &ARRAY_ITEM( string item, int count, bool last );
	ostream &END_ARRAY_LINE();

	string FSM_NAME();
	string START_STATE_ID();
	ostream &ACTIONS_ARRAY();
	string GET_WIDE_KEY();
	string GET_WIDE_KEY( RedStateAp *state );
	string TABS( int level );
	string KEY( Key key );
	string INT( int i );
	void CONDITION( ostream &ret, Action *condition );
	string ALPH_TYPE();
	string WIDE_ALPH_TYPE();
	string ARRAY_TYPE( unsigned long maxVal );

	string ACCESS();
	string P();
	string PE();
	string CS();
	string TOP();
	string STACK();
	string ACT();
	string TOKSTART();
	string TOKEND();
	string DATA();

	string DATA_PREFIX();
	string PM() { return "_" + DATA_PREFIX() + "partition_map"; }
	string C() { return "_" + DATA_PREFIX() + "cond_spaces"; }
	string CK() { return "_" + DATA_PREFIX() + "cond_keys"; }
	string K() { return "_" + DATA_PREFIX() + "trans_keys"; }
	string I() { return "_" + DATA_PREFIX() + "indicies"; }
	string CO() { return "_" + DATA_PREFIX() + "cond_offsets"; }
	string KO() { return "_" + DATA_PREFIX() + "key_offsets"; }
	string IO() { return "_" + DATA_PREFIX() + "index_offsets"; }
	string CL() { return "_" + DATA_PREFIX() + "cond_lengths"; }
	string SL() { return "_" + DATA_PREFIX() + "single_lengths"; }
	string RL() { return "_" + DATA_PREFIX() + "range_lengths"; }
	string A() { return "_" + DATA_PREFIX() + "actions"; }
	string TA() { return "_" + DATA_PREFIX() + "trans_actions_wi"; }
	string TT() { return "_" + DATA_PREFIX() + "trans_targs_wi"; }
	string TSA() { return "_" + DATA_PREFIX() + "to_state_actions"; }
	string FSA() { return "_" + DATA_PREFIX() + "from_state_actions"; }
	string EA() { return "_" + DATA_PREFIX() + "eof_actions"; }
	string SP() { return "_" + DATA_PREFIX() + "key_spans"; }
	string CSP() { return "_" + DATA_PREFIX() + "cond_key_spans"; }
	string START() { return DATA_PREFIX() + "start"; }
	string ERROR() { return DATA_PREFIX() + "error"; }
	string FIRST_FINAL() { return DATA_PREFIX() + "first_final"; }
	string CTXDATA() { return DATA_PREFIX() + "ctxdata"; }

	void INLINE_LIST( ostream &ret, InlineList *inlineList, int targState, bool inFinish );
	void EXEC( ostream &ret, InlineItem *item, int targState, int inFinish );
	void EXECTE( ostream &ret, InlineItem *item, int targState, int inFinish );
	void LM_SWITCH( ostream &ret, InlineItem *item, int targState, int inFinish );
	void SET_ACT( ostream &ret, InlineItem *item );
	void INIT_TOKSTART( ostream &ret, InlineItem *item );
	void INIT_ACT( ostream &ret, InlineItem *item );
	void SET_TOKSTART( ostream &ret, InlineItem *item );
	void SET_TOKEND( ostream &ret, InlineItem *item );
	void GET_TOKEND( ostream &ret, InlineItem *item );
	void SUB_ACTION( ostream &ret, InlineItem *item, 
			int targState, bool inFinish );

	string ERROR_STATE();
	string FIRST_FINAL_STATE();

	ostream &source_warning(const InputLoc &loc);
	ostream &source_error(const InputLoc &loc);

	unsigned int arrayTypeSize( unsigned long maxVal );

	bool outLabelUsed;
	bool againLabelUsed;

	bool useIndicies;

public:
	string NULL_ITEM();
	ostream &OPEN_ARRAY( string type, string name );
	ostream &CLOSE_ARRAY();
	ostream &STATIC_VAR( string type, string name );
	string ARR_OFF( string ptr, string offset );
	string GET_KEY();
	void ACTION( ostream &ret, Action *action, int targState, bool inFinish );

protected:
	string INDENT_S() { return INDENT(indent_level); }
	string INDENT_U() { return INDENT(++indent_level); }
	string INDENT_D() { return INDENT(--indent_level); }
	string INDENT_O() { return INDENT(indent_level--); }

private:
	string INDENT(int level);
	int indent_level;
};


#endif
