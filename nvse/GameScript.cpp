#include "nvse/GameScript.h"

void Script::RefVariable::Resolve(ScriptEventList *eventList)
{
	if (varIdx && eventList)
	{
		ScriptVar *var = eventList->GetVariable(varIdx);
		if (var) form = LookupFormByRefID(var->data.refID);
	}
}

bool Script::Compile()
{
	ScriptBuffer scrBuffer;
	scrBuffer.scriptText = text;
	scrBuffer.runtimeMode = 1;
	scrBuffer.scriptName.Set((const char*)0x1044CB4);
	scrBuffer.partialScript = true;
	scrBuffer.currScript = this;
	return StdCall<bool>(0x5AEB90, this, &scrBuffer);
}

void Script::Init(char *scrText)
{
	Constructor();
	MarkAsTemporary();
	text = scrText;
	Compile();
	text = nullptr;
}

Script *Script::Create(char *scrText)
{
	Script *pScript = (Script*)GameHeapAlloc(sizeof(Script));
	pScript->Init(scrText);
	return pScript;
}

class ScriptVarFinder
{
	const char	*m_varName;

public:
	ScriptVarFinder(const char *varName) : m_varName(varName) {}

	bool Accept(VariableInfo *varInfo)
	{
		return !StrCompare(varInfo->name.m_data, m_varName);
	}
};

VariableInfo *Script::GetVariableByName(const char *varName)
{
	ListNode<VariableInfo> *varIter = varList.Head();
	VariableInfo *varInfo;
	do
	{
		varInfo = varIter->data;
		if (varInfo && !StrCompare(varName, varInfo->name.m_data))
			return varInfo;
	}
	while (varIter = varIter->next);
	return NULL;
}

Script::RefVariable	*Script::GetVariable(UInt32 reqIdx)
{
	UInt32 idx = 1;	// yes, really starts at 1
	if (reqIdx)
	{
		ListNode<RefVariable> *varIter = refList.Head();
		do
		{
			if (idx == reqIdx)
				return varIter->data;
			idx++;
		}
		while (varIter = varIter->next);
	}
	return NULL;
}

VariableInfo *Script::GetVariableInfo(UInt32 idx)
{
	ListNode<VariableInfo> *varIter = varList.Head();
	VariableInfo *varInfo;
	do
	{
		varInfo = varIter->data;
		if (varInfo && (varInfo->idx == idx))
			return varInfo;
	}
	while (varIter = varIter->next);
	return NULL;
}

UInt32 Script::AddVariable(TESForm *form)
{
	RefVariable	*refVar = (RefVariable*)GameHeapAlloc(sizeof(RefVariable));
	refVar->name.Set("");
	refVar->form = form;
	refVar->varIdx = 0;

	UInt32 resultIdx = refList.Append(refVar) + 1;
	info.numRefs = resultIdx + 1;
	return resultIdx;
}

UInt32 Script::RefVarList::GetIndex(RefVariable *refVar)
{
	UInt32 idx = 0;
	ListNode<RefVariable> *varIter = Head();
	do
	{
		idx++;
		if (varIter->data == refVar)
			return idx;
	}
	while (varIter = varIter->next);
	return 0;
}

UInt32 Script::GetDataLength()
{
	UInt8 *dataPtr = data;
	if (*(UInt32*)dataPtr != 0x1D) return 0;
	dataPtr += 4;
	while (*(UInt16*)dataPtr == 0x10)
	{
		dataPtr += *(UInt16*)(dataPtr + 2) + *(UInt16*)(dataPtr + 6);
		if (*(UInt32*)dataPtr != 0x11) return 0;
		dataPtr += 4;
	}
	return dataPtr - data;
}