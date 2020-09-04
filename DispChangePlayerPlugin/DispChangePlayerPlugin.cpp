// DispChangePlayerPlugin.cpp : Defines the expoted function for the DLL aplication.
//

// ì˙ñ{åÍê›íË
#include <codecvt>

// ÉtÉ@ÉCÉãèoóÕ
#include <direct.h>
#include <fstream>

// BakkesModä÷òA
#include "utils/parser.h"
#include "bakkesmod/wrappers/GameEvent/ServerWrapper.h"
#include "DispChangePlayerPlugin.h"
BAKKESMOD_PLUGIN(DispChangePlayerPlugin, "DispChangePlayerPlugin", "1.0", PLUGINTYPE_FREEPLAY)

// èàóù
void DispChangePlayerPlugin::onLoad()
{
	cvarManager->log("DispChangePlayerPlugin : onLoad");

	cvarManager->registerCvar("enable_disp_change_player_plugin", "0", "Enable", true, true, 0, true, 1, true);

	cvarManager->registerCvar("output_change_players_to_file", "0", "OutPut Change Players to File", true, true, 0, true, 1, true);

	cvarManager->registerCvar("enable_random_change_players", "0", "Random Change Players", true, true, 0, true, 1, true);
	cvarManager->registerCvar("random_change_players_num", "1", "Players Num", true, true, 1, true, 8, true);

	cvarManager->registerCvar("enable_random_change_players_on_team", "0", "Random Change Players on Team (Prioritize Random Change Players)", true, true, 0, true, 1, true);
	cvarManager->registerCvar("random_change_players_num_on_team_blue", "0", "Players Num on Team Blue", true, true, 0, true, 4, true);
	cvarManager->registerCvar("random_change_players_num_on_team_orange", "0", "Players Num on Team Orange", true, true, 0, true, 4, true);

	cvarManager->registerCvar("enable_change_players_rank_on_team", "0", "Change Players on Team (Prioritize Random Change Players, Random Change Players on Team)", true, true, 0, true, 1, true);
	cvarManager->registerCvar("change_player_rank_on_team_blue", "0", "Players Rank on Team Blue", true, true, 0, true, 4, true);
	cvarManager->registerCvar("change_player_rank_on_team_orange", "0", "Players Rank on Team Orange", true, true, 0, true, 4, true);

	cvarManager->registerCvar("enable_change_low_score_players_num_on_lose_team", "0", "Change Low Score Players on Lose Team (Prioritize Random Change Players, Random Change Players on Team, and Change Players on Team)", true, true, 0, true, 1, true);
	cvarManager->registerCvar("change_low_score_player_num_on_lose_team", "1", "Low Score Players Num on Lose Team", true, true, 1, true, 4, true);

	cvarManager->registerCvar("fill_box_color_r", "0", "Fill Box Color R", true, true, 0, true, 255, true);
	cvarManager->registerCvar("fill_box_color_g", "16", "Fill Box Color G", true, true, 0, true, 255, true);
	cvarManager->registerCvar("fill_box_color_b", "25", "Fill Box Color B", true, true, 0, true, 255, true);
	cvarManager->registerCvar("fill_box_color_a", "230", "Fill Box Color A", true, true, 0, true, 255, true);

	cvarManager->registerCvar("draw_box_color_r", "37", "Draw Box Color R", true, true, 0, true, 255, true);
	cvarManager->registerCvar("draw_box_color_g", "149", "Draw Box Color G", true, true, 0, true, 255, true);
	cvarManager->registerCvar("draw_box_color_b", "199", "Draw Box Color B", true, true, 0, true, 255, true);
	cvarManager->registerCvar("draw_box_color_a", "110", "Draw Box Color A", true, true, 0, true, 255, true);

	cvarManager->registerCvar("x_position", "0", "X Position", true, true, 0, true, 100, true);
	cvarManager->registerCvar("y_position", "0", "Y Position", true, true, 0, true, 100, true);
	cvarManager->registerCvar("box_scale", "1", "Box Scale", true, true, 1, true, 3, true);

	gameWrapper->RegisterDrawable(std::bind(&DispChangePlayerPlugin::UiRender, this, std::placeholders::_1));

	gameWrapper->HookEvent("Function TAGame.GameEvent_Soccar_TA.OnMatchEnded", bind(&DispChangePlayerPlugin::EndGame, this, std::placeholders::_1));
}

void DispChangePlayerPlugin::onUnLoad()
{
	cvarManager->log("DispChangePlayerPlugin : onUnLoad");
	gameWrapper->UnregisterDrawables();
	gameWrapper->UnhookEvent("Function TAGame.GameEvent_Soccar_TA.OnMatchEnded");
}

void DispChangePlayerPlugin::UiRender(CanvasWrapper canvas)
{
	SetInputStaus();

	if (!enable_disp_change_player_plugin || output_change_players_to_file) {
		return;
	}

	// BOXîwåi
	FillBoxCanvasRender(canvas);

	// BOXògê¸
	DrawBoxCanvasRender(canvas);

	padding = 0;

	// Plugin Change Mode
	std::string str = "[ Mode ] ";
	if (enable_random_change_players) {
		str = str + "Random change players";
	} else if (enable_random_change_players_on_team) {
		str = str + "Random change players on team";
	} else if (enable_change_players_rank_on_team) {
		str = str + "Change players rank on team";
	} else if (enable_change_low_score_players_num_on_lose_team) {
		str = str + "Change low score players on lose team";
	} else {
		str = str + "None";
	}
	CommonStringColorCanvasRender(canvas, str);

	// Change Num
	if (enable_random_change_players) {
		str = "[ Change players num ] " + std::to_string(random_change_players_num);
		CommonStringColorCanvasRender(canvas, str);
	} else if (enable_random_change_players_on_team) {
		str = "[ Change players num on Team Blue ] " + std::to_string(random_change_players_num_on_team_blue);
		TeamBlueStringColorCanvasRender(canvas, str);
		str = "[ Change players num on Team Orange ] " + std::to_string(random_change_players_num_on_team_orange);
		TeamOrangeStringColorCanvasRender(canvas, str);
	} else if (enable_change_players_rank_on_team) {
		str = "[ Change players rank on Team Blue ] " + std::to_string(change_player_rank_on_team_blue);
		TeamBlueStringColorCanvasRender(canvas, str);
		str = "[ Change players rank on Team Orange ] " + std::to_string(change_player_rank_on_team_orange);
		TeamOrangeStringColorCanvasRender(canvas, str);
	} else if (enable_change_low_score_players_num_on_lose_team) {
		str = "[ Change low score players num ] " + std::to_string(change_low_score_player_num_on_lose_team);
		CommonStringColorCanvasRender(canvas, str);
	}

	// Winner Team
	if (lose_team == 1) {
		str = "[ Winning Team ] Blue";
		TeamBlueStringColorCanvasRender(canvas, str);
	} else {
		str = "[ Winning Team ] Orange";
		TeamOrangeStringColorCanvasRender(canvas, str);
	}

	// Label
	if (enable_random_change_players || enable_random_change_players_on_team || enable_change_players_rank_on_team || enable_change_low_score_players_num_on_lose_team) {
		str = "[ Change players list ]";
		CommonStringColorCanvasRender(canvas, str);
	}

	// Change Player Name List
	if (enable_random_change_players) {
		for (int i = 0; i < disp_change_players_count; i++) {
			int index = random_players_no_list[i];
			str = "Player " + std::to_string(i + 1) + " : " + player_stats_list[index].name;
			CommonStringColorCanvasRender(canvas, str);
		}
	} else if (enable_random_change_players_on_team) {
		for (int i = 0; i < disp_change_players_count_on_team_blue; i++) {
			int index = random_players_no_list_on_team_blue[i];
			str = "Player " + std::to_string(i + 1) + " : " + player_stats_list_on_team_blue[index].name;
			TeamBlueStringColorCanvasRender(canvas, str);
		}
		if (disp_change_players_count_on_team_blue > 0 && disp_change_players_count_on_team_orange > 0) {
			str = "";
			CommonStringColorCanvasRender(canvas, str);
		}
		for (int i = 0; i < disp_change_players_count_on_team_orange; i++) {
			int index = random_players_no_list_on_team_orange[i];
			str = "Player " + std::to_string(i + 1) + " : " + player_stats_list_on_team_orange[index].name;
			TeamOrangeStringColorCanvasRender(canvas, str);
		}
	} else if (enable_change_players_rank_on_team) {
		if (disp_change_players_rank_on_team_blue > 0) {
			str = "Player : " + player_stats_list_on_team_blue[disp_change_players_rank_on_team_blue - 1].name;
			TeamBlueStringColorCanvasRender(canvas, str);
		}
		if (disp_change_players_rank_on_team_blue > 0 && disp_change_players_rank_on_team_orange > 0) {
			str = "";
			CommonStringColorCanvasRender(canvas, str);
		}
		if (disp_change_players_rank_on_team_orange > 0) {
			str = "Player : " + player_stats_list_on_team_orange[disp_change_players_rank_on_team_orange - 1].name;
			TeamOrangeStringColorCanvasRender(canvas, str);
		}
	} else if (enable_change_low_score_players_num_on_lose_team) {
		if (lose_team == 0 && disp_change_low_score_players_num_on_team_blue > 0) {
			for (int i = disp_change_low_score_players_num_on_team_blue - 1; i < players_count_on_team_blue; i++) {
				str = "Player " + std::to_string(i + 1) + " : " + player_stats_list_on_team_blue[i].name;
				TeamBlueStringColorCanvasRender(canvas, str);
			}
		} else if (lose_team == 1 && disp_change_low_score_players_num_on_team_orange > 0) {
			for (int i = disp_change_low_score_players_num_on_team_orange - 1; i < players_count_on_team_orange; i++) {
				str = "Player " + std::to_string(i + 1) + " : " + player_stats_list_on_team_orange[i].name;
				TeamOrangeStringColorCanvasRender(canvas, str);
			}
		}
	}
}

void DispChangePlayerPlugin::EndGame(std::string eventName)
{
	cvarManager->log("DispChangePlayerPlugin : EndGame");

	if (!enable_disp_change_player_plugin) {
		return;
	}

	ServerWrapper sw = gameWrapper->GetOnlineGame();
	if (sw.IsNull()) {
		return;
	}

	SetPlayerStatsList(sw);

	SetDispChangePlayersCount();

	if (team_count != 2) {
		return;
	}

	if (players_count == 0) {
		return;
	}

	delete[] random_players_no_list;
	random_players_no_list = new int[players_count];
	CreateRandomNoList(players_count, random_players_no_list);

	delete[] random_players_no_list_on_team_blue;
	delete[] random_players_no_list_on_team_orange;
	random_players_no_list_on_team_blue = new int[players_count_on_team_blue];
	random_players_no_list_on_team_orange = new int[players_count_on_team_orange];
	CreateRandomNoList(players_count_on_team_blue, random_players_no_list_on_team_blue);
	CreateRandomNoList(players_count_on_team_orange, random_players_no_list_on_team_orange);

	CreateOutputDirectory();
	WinnerTeamOutputToFile();
	RandomChangePlayersOutputToFile();
	RandomChangePlayersOnTeamOutputToFile();
	ChangePlayersRankOnTeamOutputToFile();
	ChangeLowScorePlayersOnLoseTeamOutputToFile();
}

void DispChangePlayerPlugin::SetInputStaus()
{
	enable_disp_change_player_plugin = cvarManager->getCvar("enable_disp_change_player_plugin").getBoolValue();

	output_change_players_to_file = cvarManager->getCvar("output_change_players_to_file").getBoolValue();

	enable_random_change_players = cvarManager->getCvar("enable_random_change_players").getBoolValue();
	random_change_players_num = cvarManager->getCvar("random_change_players_num").getIntValue();

	enable_random_change_players_on_team = cvarManager->getCvar("enable_random_change_players_on_team").getBoolValue();
	random_change_players_num_on_team_blue = cvarManager->getCvar("random_change_players_num_on_team_blue").getIntValue();
	random_change_players_num_on_team_orange = cvarManager->getCvar("random_change_players_num_on_team_orange").getIntValue();

	enable_change_players_rank_on_team = cvarManager->getCvar("enable_change_players_rank_on_team").getBoolValue();
	change_player_rank_on_team_blue = cvarManager->getCvar("change_player_rank_on_team_blue").getIntValue();
	change_player_rank_on_team_orange = cvarManager->getCvar("change_player_rank_on_team_orange").getIntValue();

	enable_change_low_score_players_num_on_lose_team = cvarManager->getCvar("enable_change_low_score_players_num_on_lose_team").getBoolValue();
	change_low_score_player_num_on_lose_team = cvarManager->getCvar("change_low_score_player_num_on_lose_team").getIntValue();

	fill_box_color_r = cvarManager->getCvar("fill_box_color_r").getIntValue();
	fill_box_color_g = cvarManager->getCvar("fill_box_color_g").getIntValue();
	fill_box_color_b = cvarManager->getCvar("fill_box_color_b").getIntValue();
	fill_box_color_a = cvarManager->getCvar("fill_box_color_a").getIntValue();

	draw_box_color_r = cvarManager->getCvar("draw_box_color_r").getIntValue();
	draw_box_color_g = cvarManager->getCvar("draw_box_color_g").getIntValue();
	draw_box_color_b = cvarManager->getCvar("draw_box_color_b").getIntValue();
	draw_box_color_a = cvarManager->getCvar("draw_box_color_a").getIntValue();

	x_position = cvarManager->getCvar("x_position").getIntValue();
	y_position = cvarManager->getCvar("y_position").getIntValue();
	box_scale = cvarManager->getCvar("box_scale").getFloatValue();
}

void DispChangePlayerPlugin::SetPlayerStatsList(ServerWrapper sw)
{
	cvarManager->log("DispChangePlayerPlugin : SetPlayerStatsList");

	ArrayWrapper<TeamWrapper> team = sw.GetTeams();
	ArrayWrapper<PriWrapper> players = sw.GetPRIs();
	team_count = team.Count();
	players_count = 0;
	players_count_on_team_blue = 0;
	players_count_on_team_orange = 0;
	player_stats_list.clear();
	player_stats_list_on_team_blue.clear();
	player_stats_list_on_team_orange.clear();

	int team_blue_goal_count = 0;
	int team_orange_goal_count = 0;
	for (int i = 0; i < players.Count(); i++) {
		PriWrapper player = players.Get(i);
		int team_num = player.GetTeamNum();
		if (team_num != 255) {
			player_stats_list.push_back(player_stats{
				player.GetTeamNum(),
				WStringToString(player.GetPlayerName().ToWideString()),
				player.GetMatchScore(),
				player.GetMatchGoals(),
				player.GetMatchAssists(),
				player.GetMatchSaves(),
				player.GetMatchShots()
				});

			if (team_num == 0) {
				player_stats_list_on_team_blue.push_back(player_stats_list[players_count]);
				players_count_on_team_blue += 1;
				team_blue_goal_count += player.GetMatchGoals();
			}
			else if (team_num == 1) {
				player_stats_list_on_team_orange.push_back(player_stats_list[players_count]);
				players_count_on_team_orange += 1;
				team_orange_goal_count += player.GetMatchGoals();
			}

			players_count += 1;
		}
	}

	if (team_blue_goal_count > team_orange_goal_count) {
		lose_team = 1;
	}
	else {
		lose_team = 0;
	}

	sort(player_stats_list.begin(), player_stats_list.end());
	sort(player_stats_list_on_team_blue.begin(), player_stats_list_on_team_blue.end());
	sort(player_stats_list_on_team_orange.begin(), player_stats_list_on_team_orange.end());

/*
	for (int i = 0; i < players_count; i++) {
		cvarManager->log("DispChangePlayerPlugin : player_stats_list : TeamNum : " + std::to_string(player_stats_list[i].team));
		cvarManager->log("DispChangePlayerPlugin : player_stats_list : PlayerName : " + player_stats_list[i].name);
		cvarManager->log("DispChangePlayerPlugin : player_stats_list : MatchScore : " + std::to_string(player_stats_list[i].score));
		cvarManager->log("DispChangePlayerPlugin : player_stats_list : MatchGoals : " + std::to_string(player_stats_list[i].goals));
		cvarManager->log("DispChangePlayerPlugin : player_stats_list : MatchAssists : " + std::to_string(player_stats_list[i].assists));
		cvarManager->log("DispChangePlayerPlugin : player_stats_list : MatchSaves : " + std::to_string(player_stats_list[i].saves));
		cvarManager->log("DispChangePlayerPlugin : player_stats_list : MatchShots : " + std::to_string(player_stats_list[i].shots));
	}
	for (int i = 0; i < players_count_on_team_blue; i++) {
		cvarManager->log("DispChangePlayerPlugin : player_stats_list_on_team_blue : TeamNum : " + std::to_string(player_stats_list_on_team_blue[i].team));
		cvarManager->log("DispChangePlayerPlugin : player_stats_list_on_team_blue : PlayerName : " + player_stats_list_on_team_blue[i].name);
		cvarManager->log("DispChangePlayerPlugin : player_stats_list_on_team_blue : MatchScore : " + std::to_string(player_stats_list_on_team_blue[i].score));
		cvarManager->log("DispChangePlayerPlugin : player_stats_list_on_team_blue : MatchGoals : " + std::to_string(player_stats_list_on_team_blue[i].goals));
		cvarManager->log("DispChangePlayerPlugin : player_stats_list_on_team_blue : MatchAssists : " + std::to_string(player_stats_list_on_team_blue[i].assists));
		cvarManager->log("DispChangePlayerPlugin : player_stats_list_on_team_blue : MatchSaves : " + std::to_string(player_stats_list_on_team_blue[i].saves));
		cvarManager->log("DispChangePlayerPlugin : player_stats_list_on_team_blue : MatchShots : " + std::to_string(player_stats_list_on_team_blue[i].shots));
	}
	for (int i = 0; i < players_count_on_team_orange; i++) {
		cvarManager->log("DispChangePlayerPlugin : player_stats_list_on_team_orange : TeamNum : " + std::to_string(player_stats_list_on_team_orange[i].team));
		cvarManager->log("DispChangePlayerPlugin : player_stats_list_on_team_orange : PlayerName : " + player_stats_list_on_team_orange[i].name);
		cvarManager->log("DispChangePlayerPlugin : player_stats_list_on_team_orange : MatchScore : " + std::to_string(player_stats_list_on_team_orange[i].score));
		cvarManager->log("DispChangePlayerPlugin : player_stats_list_on_team_orange : MatchGoals : " + std::to_string(player_stats_list_on_team_orange[i].goals));
		cvarManager->log("DispChangePlayerPlugin : player_stats_list_on_team_orange : MatchAssists : " + std::to_string(player_stats_list_on_team_orange[i].assists));
		cvarManager->log("DispChangePlayerPlugin : player_stats_list_on_team_orange : MatchSaves : " + std::to_string(player_stats_list_on_team_orange[i].saves));
		cvarManager->log("DispChangePlayerPlugin : player_stats_list_on_team_orange : MatchShots : " + std::to_string(player_stats_list_on_team_orange[i].shots));
	}
*/
}

void DispChangePlayerPlugin::SetDispChangePlayersCount()
{
	cvarManager->log("DispChangePlayerPlugin : SetDispChangePlayersCount");

	disp_change_players_count = (players_count < random_change_players_num) ? players_count : random_change_players_num;

	disp_change_players_count_on_team_blue = (players_count_on_team_blue < random_change_players_num_on_team_blue) ? players_count_on_team_blue : random_change_players_num_on_team_blue;
	disp_change_players_count_on_team_orange = (players_count_on_team_orange < random_change_players_num_on_team_orange) ? players_count_on_team_orange : random_change_players_num_on_team_orange;

	disp_change_players_rank_on_team_blue = (players_count_on_team_blue < change_player_rank_on_team_blue) ? players_count_on_team_blue : change_player_rank_on_team_blue;
	disp_change_players_rank_on_team_orange = (players_count_on_team_orange < change_player_rank_on_team_orange) ? players_count_on_team_orange : change_player_rank_on_team_orange;

	disp_change_low_score_players_num_on_team_blue = (players_count_on_team_blue < change_low_score_player_num_on_lose_team) ? players_count_on_team_blue : change_low_score_player_num_on_lose_team;
	disp_change_low_score_players_num_on_team_orange = (players_count_on_team_orange < change_low_score_player_num_on_lose_team) ? players_count_on_team_orange : change_low_score_player_num_on_lose_team;
}

void* DispChangePlayerPlugin::CreateRandomNoList(int count, int random_no_list[])
{
	cvarManager->log("DispChangePlayerPlugin : CreateRandomNoList");

	int random_no;
	for (int i = 0; i < count; i++) {
		do {
			random_no = rand() % count;
			exists_no = false;
			for (int j = 0; j < i; j++) {
				if (random_no_list[j] == random_no) {
					exists_no = true;
				}
			}
		} while (exists_no);
		random_no_list[i] = random_no;
	}
	return random_no_list;
}

void DispChangePlayerPlugin::WinnerTeamOutputToFile()
{
	if (lose_team == 1) {
		ClearOutputStringstream();
		std::string str = "Team Blue";
		output_stringstream << str;
		OutputToFile(output_filename_win_team_blue);

		ClearOutputStringstream();
		output_stringstream << "";
		OutputToFile(output_filename_win_team_orange);
	} else {
		ClearOutputStringstream();
		std::string str = "Team Orange";
		output_stringstream << str;
		OutputToFile(output_filename_win_team_orange);

		ClearOutputStringstream();
		output_stringstream << "";
		OutputToFile(output_filename_win_team_blue);
	}
}

void DispChangePlayerPlugin::RandomChangePlayersOutputToFile()
{
	ClearOutputStringstream();
	for (int i = 0; i < disp_change_players_count; i++) {
		int index = random_players_no_list[i];
		std::string player_name = player_stats_list[index].name;
		output_stringstream << player_name + "\n";
	}
	OutputToFile(output_filename_random_chagen_player_name);
}

void DispChangePlayerPlugin::RandomChangePlayersOnTeamOutputToFile()
{
	ClearOutputStringstream();
	for (int i = 0; i < disp_change_players_count_on_team_blue; i++) {
		int index = random_players_no_list_on_team_blue[i];
		std::string player_name = player_stats_list_on_team_blue[index].name;
		output_stringstream << player_name + "\n";
	}
	OutputToFile(output_filename_random_chagen_player_name_on_team_blue);

	ClearOutputStringstream();
	for (int i = 0; i < disp_change_players_count_on_team_orange; i++) {
		int index = random_players_no_list_on_team_orange[i];
		std::string player_name = player_stats_list_on_team_orange[index].name;
		output_stringstream << player_name + "\n";
	}
	OutputToFile(output_filename_random_chagen_player_name_on_team_orange);
}

void DispChangePlayerPlugin::ChangePlayersRankOnTeamOutputToFile()
{
	ClearOutputStringstream();
	if (disp_change_players_rank_on_team_blue > 0) {
		std::string player_name = player_stats_list_on_team_blue[disp_change_players_rank_on_team_blue - 1].name;
		output_stringstream << player_name + "\n";
	}
	OutputToFile(output_filename_rank_chagen_player_name_on_team_blue);

	ClearOutputStringstream();
	if (disp_change_players_rank_on_team_orange > 0) {
		std::string player_name = player_stats_list_on_team_orange[disp_change_players_rank_on_team_orange - 1].name;
		output_stringstream << player_name + "\n";
	}
	OutputToFile(output_filename_rank_chagen_player_name_on_team_orange);
}

void DispChangePlayerPlugin::ChangeLowScorePlayersOnLoseTeamOutputToFile()
{
	ClearOutputStringstream();
	if (lose_team == 0 && disp_change_low_score_players_num_on_team_blue > 0) {
		for (int i = disp_change_low_score_players_num_on_team_blue - 1; i < players_count_on_team_blue; i++) {
			std::string player_name = player_stats_list_on_team_blue[i].name;
			output_stringstream << player_name + "\n";
		}
	} else if (lose_team == 1 && disp_change_low_score_players_num_on_team_orange > 0) {
		for (int i = disp_change_low_score_players_num_on_team_orange - 1; i < players_count_on_team_orange; i++) {
			std::string player_name = player_stats_list_on_team_orange[i].name;
			output_stringstream << player_name + "\n";
		}
	}
	OutputToFile(output_filename_change_low_score_player_name_on_lose_team);
}

void DispChangePlayerPlugin::FillBoxCanvasRender(CanvasWrapper canvas)
{
	Vector2 monitor_size = canvas.GetSize();
	canvas.SetColor(fill_box_color_r, fill_box_color_g, fill_box_color_b, fill_box_color_a);
	canvas.SetPosition(Vector2{ (monitor_size.X * x_position) / 100 - 15, ((monitor_size.Y * y_position) / 100) - 15 });
	canvas.FillBox(Vector2{ 350, 200 });
}

void DispChangePlayerPlugin::DrawBoxCanvasRender(CanvasWrapper canvas)
{
	Vector2 monitor_size = canvas.GetSize();
	canvas.SetColor(draw_box_color_r, draw_box_color_g, draw_box_color_b, draw_box_color_a);
	canvas.SetPosition(Vector2{ (monitor_size.X * x_position) / 100 - 15, ((monitor_size.Y * y_position) / 100) - 15 });
	canvas.DrawBox(Vector2{ 350, 200 });
}

void DispChangePlayerPlugin::CommonStringColorCanvasRender(CanvasWrapper canvas, std::string str)
{
	Vector2 monitor_size = canvas.GetSize();
	canvas.SetColor(common_string_color_r, common_string_color_g, common_string_color_b, common_string_color_a);
	canvas.SetPosition(Vector2{ (monitor_size.X * x_position) / 100, (monitor_size.Y * y_position) / 100 + padding });
	canvas.DrawString(str, box_scale, box_scale);
	padding += 15;
}

void DispChangePlayerPlugin::TeamBlueStringColorCanvasRender(CanvasWrapper canvas, std::string str)
{
	Vector2 monitor_size = canvas.GetSize();
	canvas.SetColor(team_blue_string_color_r, team_blue_string_color_g, team_blue_string_color_b, team_blue_string_color_a);
	canvas.SetPosition(Vector2{ (monitor_size.X * x_position) / 100, (monitor_size.Y * y_position) / 100 + padding });
	canvas.DrawString(str, box_scale, box_scale);
	padding += 15;
}

void DispChangePlayerPlugin::TeamOrangeStringColorCanvasRender(CanvasWrapper canvas, std::string str)
{
	Vector2 monitor_size = canvas.GetSize();
	canvas.SetColor(team_orange_string_color_r, team_orange_string_color_g, team_orange_string_color_b, team_orange_string_color_a);
	canvas.SetPosition(Vector2{ (monitor_size.X * x_position) / 100, (monitor_size.Y * y_position) / 100 + padding });
	canvas.DrawString(str, box_scale, box_scale);
	padding += 15;
}

void DispChangePlayerPlugin::OutputToFile(std::string output_filename)
{
	std::ofstream f(output_directory + output_filename);
	f << output_stringstream.str();
	f.close();
}

void DispChangePlayerPlugin::CreateOutputDirectory()
{
	if (_mkdir(output_directory.c_str()) == 0) {
		cvarManager->log(output_directory + "directory created");
	}
}

void DispChangePlayerPlugin::ClearOutputStringstream()
{
	output_stringstream.str("");
	output_stringstream.clear(std::stringstream::goodbit);
}

std::string DispChangePlayerPlugin::WStringToString(std::wstring string)
{
/*
	size_t length = string.size();
	size_t convLength;
	char* c = (char*)malloc(sizeof(char) * length * 2);
	wcstombs_s(&convLength, c, sizeof(char) * length * 2, string.c_str(), length * 2);
	std::string result(c);
	free(c);
	return result;
*/
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> cv;
	return cv.to_bytes(string);
}
