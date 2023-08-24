#include "stdafx.h"
#include "SwapSaveCheat.h"

SwapSaveCheat::SwapSaveCheat()
{
	//Initialise member variables
	hasSwapped = false;
	App::AddUpdateFunction(this);
	timer = 0;
}


SwapSaveCheat::~SwapSaveCheat()
{
}


void SwapSaveCheat::ParseLine(const ArgScript::Line& line)
{
	//This is where the cheat does stuff.

	auto arguments = line.GetArguments(1); //Get the argument the player passed to the cheat...
	int ID = mpFormatParser->ParseInt(arguments[0]); //...and parse it as an integer, simply to ensure the player doesn't input a non-integer value.

	directory.assign_convert(to_string(ID)); 
	directory = u"Games/Game" + directory; //Now we create a new GameX folder, where X is the integer specified by the player
	if (GameModeManager.GetActiveModeID() == GameModeIDs::kGGEMode) //If we're in the main menu...
	{
		hasSwapped = true; //Tell the program we're doing the swap
		timer = 5; //set a small timer
		GameModeManager.SetActiveMode(GameModeIDs::kGameCell); //and go to cell stage.
	}
	else
	{
		App::ConsolePrintF("Must be in main menu to use cheat."); //Not in main menu, so we give an error to the user.
	}
}

DatabaseDirectoryFilesPtr SwapSaveCheat::saveDatabase;

void SwapSaveCheat::Update()
{
	if (hasSwapped) //Every frame, check if the player's swapped or not. if they have...
	{
		timer -= 1/GameTimeManager.GetSpeed(); //first, decrement the timer by 1 over the game's current speed, so that it always goes down by the same amount in a given time.
		if (timer == 0) //when it reaches 0...
		{
			//first, create a new save database for save files, and set the saveDatabase variable to be a pointer to it.
			//The detour in dllmain.cpp will handle the rest.
			Resource::Paths::CreateSaveAreaDirectoryDatabase(Resource::PathID::AppData, directory.c_str(), saveDatabase, Resource::SaveAreaID::GamesGame0);
			
			hasSwapped = false; //now, tell the game not to check the frame thingy anymore.
			GameModeManager.SetActiveMode(GameModeIDs::kGGEMode); //And finally, set the active mode to the main menu again.
		}
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

