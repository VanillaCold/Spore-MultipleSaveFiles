#include "stdafx.h"
#include "SwapSaveCheat.h"

SwapSaveCheat::SwapSaveCheat()
{
	hasSwapped = false;
	App::AddUpdateFunction(this);
	timer = 0;
}


SwapSaveCheat::~SwapSaveCheat()
{
}


void SwapSaveCheat::ParseLine(const ArgScript::Line& line)
{

	auto arguments = line.GetArguments(1);
	int ID = mpFormatParser->ParseInt(arguments[0]);

	string16 directory;

	directory.assign_convert(to_string(ID));
	directory = u"Games/Game" + directory;
	if (GameModeManager.GetActiveModeID() == GameModeIDs::kGGEMode)
	{
		Resource::Paths::CreateSaveAreaDirectoryDatabase(Resource::PathID::AppData, directory.c_str(), saveDatabase, Resource::SaveAreaID::GamesGame0);
		hasSwapped = true;
		timer = 5;
		GameModeManager.SetActiveMode(GameModeIDs::kGameCell);
	}
	else
	{
		App::ConsolePrintF("Must be in main menu to use cheat.");
	}
	// This method is called when your cheat is invoked.
	// Put your cheat code here.
}

DatabaseDirectoryFilesPtr SwapSaveCheat::saveDatabase;

void SwapSaveCheat::Update()
{
	if (!hasSwapped)
	{
		timer = 0;
		return;
	}
	timer--;
	if (timer == 0)
	{
		hasSwapped = false;
		GameModeManager.SetActiveMode(GameModeIDs::kGGEMode);
	}
}

const char* SwapSaveCheat::GetDescription(ArgScript::DescriptionMode mode) const
{
	if (mode == ArgScript::DescriptionMode::Basic) {
		return "Cheat to swap the main galaxy save.";
	}
	else {
		return "SwapSaveCheat: This cheat swaps the master 'galaxy' save of the game.\nUsage: swapSaveCheat [save_number]\nThe default save number is 0.";
	}
}


int SwapSaveCheat::AddRef()
{
	return IParser::AddRef();
}

int SwapSaveCheat::Release()
{
	return IParser::Release();
}

