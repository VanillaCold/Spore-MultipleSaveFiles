#pragma once

#include <Spore\BasicIncludes.h>

class SwapSaveCheat
	: public ArgScript::ICommand
{
public:
	SwapSaveCheat();
	~SwapSaveCheat();

	// Called when the cheat is invoked
	void ParseLine(const ArgScript::Line& line) override;
	bool hasSwapped;

	static DatabaseDirectoryFilesPtr saveDatabase;
	
	// Returns a string containing the description. If mode != DescriptionMode::Basic, return a more elaborated description
	const char* GetDescription(ArgScript::DescriptionMode mode) const override;
};

