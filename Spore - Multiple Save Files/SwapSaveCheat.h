#pragma once

#include <Spore\BasicIncludes.h>

class SwapSaveCheat
	: public ArgScript::ICommand
	, public App::IUpdatable
{
public:
	SwapSaveCheat();
	~SwapSaveCheat();

	// Called when the cheat is invoked
	void ParseLine(const ArgScript::Line& line) override;
	bool hasSwapped;
	int timer;

	static DatabaseDirectoryFilesPtr saveDatabase;

	void Update() override;

	virtual int AddRef() override;
	virtual int Release() override;
	
	// Returns a string containing the description. If mode != DescriptionMode::Basic, return a more elaborated description
	const char* GetDescription(ArgScript::DescriptionMode mode) const override;
};

