// DispChangePlayerPlugin.cpp : Defines the expoted function for the DLL aplication.
//

// ì˙ñ{åÍê›íË
#include <locale.h>

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

	if (!enable_disp_change_player_plugin) {
		return;
	}

	Vector2 sz = canvas.GetSize();

	canvas.SetColor(fill_box_color_r, fill_box_color_g, fill_box_color_b, fill_box_color_a);
	canvas.SetPosition(Vector2{ (sz.X * x_position) / 100 - 15, ((sz.Y * y_position) / 100) - 15 });
	canvas.FillBox(Vector2{ 350, 200 });

	canvas.SetColor(draw_box_color_r, draw_box_color_g, draw_box_color_b, draw_box_color_a);
	canvas.SetPosition(Vector2{ (sz.X * x_position) / 100 - 15, ((sz.Y * y_position) / 100) - 15 });
	canvas.DrawBox(Vector2{ 350, 200 });

	canvas.SetColor(240, 240, 240, 255);
	canvas.SetPosition(Vector2{ (sz.X * x_position) / 100, (sz.Y * y_position) / 100 });
	if (enable_random_change_players) {
		canvas.DrawString("[ Mode ] Random change players", box_scale, box_scale);
	}
	else if (enable_random_change_players_on_team) {
		canvas.DrawString("[ Mode ] Random change players on team", box_scale, box_scale);
	}
	else if (enable_change_players_rank_on_team) {
		canvas.DrawString("[ Mode ] Change players rank on team", box_scale, box_scale);
	}
	else if (enable_change_low_score_players_num_on_lose_team) {
		canvas.DrawString("[ Mode ] Change low score players on lose team", box_scale, box_scale);
	}
	else {
		canvas.DrawString("[ Mode ] None", box_scale, box_scale);
	}

	PlayerNameRender(canvas);
}

void DispChangePlayerPlugin::PlayerNameRender(CanvasWrapper canvas)
{
	int padding = 15;
	Vector2 sz = canvas.GetSize();

	if (enable_random_change_players) {
		canvas.SetColor(240, 240, 240, 255);
		canvas.SetPosition(Vector2{ (sz.X * x_position) / 100, (sz.Y * y_position) / 100 + padding });
		canvas.DrawString("[ Change players num ] " + std::to_string(random_change_players_num), box_scale, box_scale);
		padding += 15;
	}
	else if (enable_random_change_players_on_team) {
		canvas.SetColor(30, 144, 255, 255);
		canvas.SetPosition(Vector2{ (sz.X * x_position) / 100, (sz.Y * y_position) / 100 + padding });
		canvas.DrawString("[ Change players num on Team Blue ] " + std::to_string(random_change_players_num_on_team_blue), box_scale, box_scale);
		padding += 15;

		canvas.SetColor(255, 143, 34, 255);
		canvas.SetPosition(Vector2{ (sz.X * x_position) / 100, (sz.Y * y_position) / 100 + padding });
		canvas.DrawString("[ Change players num on Team Orange ] " + std::to_string(random_change_players_num_on_team_orange), box_scale, box_scale);
		padding += 15;
	}
	else if (enable_change_players_rank_on_team) {
		canvas.SetColor(30, 144, 255, 255);
		canvas.SetPosition(Vector2{ (sz.X * x_position) / 100, (sz.Y * y_position) / 100 + padding });
		canvas.DrawString("[ Change players rank on Team Blue ] " + std::to_string(change_player_rank_on_team_blue), box_scale, box_scale);
		padding += 15;

		canvas.SetColor(255, 143, 34, 255);
		canvas.SetPosition(Vector2{ (sz.X * x_position) / 100, (sz.Y * y_position) / 100 + padding });
		canvas.DrawString("[ Change players rank on Team Orange ] " + std::to_string(change_player_rank_on_team_orange), box_scale, box_scale);
		padding += 15;
	}
	else if (enable_change_low_score_players_num_on_lose_team) {
		canvas.SetColor(240, 240, 240, 255);
		canvas.SetPosition(Vector2{ (sz.X * x_position) / 100, (sz.Y * y_position) / 100 + padding });
		canvas.DrawString("[ Change low score players num ] " + std::to_string(change_low_score_player_num_on_lose_team), box_scale, box_scale);
		padding += 15;
	}


	if (enable_random_change_players || enable_random_change_players_on_team || enable_change_players_rank_on_team || enable_change_low_score_players_num_on_lose_team) {
		canvas.SetColor(240, 240, 240, 255);
		canvas.SetPosition(Vector2{ (sz.X * x_position) / 100, (sz.Y * y_position) / 100 + padding });
		canvas.DrawString("[ Change players list ]", box_scale, box_scale);
		padding += 15;
	}

	if (enable_random_change_players) {
		for (int i = 0; i < disp_change_players_count; i++) {
			int index = random_players_no_list[i];
			canvas.SetColor(240, 240, 240, 255);
			canvas.SetPosition(Vector2{ (sz.X * x_position) / 100, (sz.Y * y_position) / 100 + padding });
			canvas.DrawString("Player " + std::to_string(i + 1) + " : " + player_stats_list[index].name, box_scale, box_scale);
			padding += 15;
		}
	}
	else if (enable_random_change_players_on_team) {
		for (int i = 0; i < disp_change_players_count_on_team_blue; i++) {
			int index = random_players_no_list_on_team_blue[i];
			canvas.SetColor(30, 144, 255, 255);
			canvas.SetPosition(Vector2{ (sz.X * x_position) / 100, (sz.Y * y_position) / 100 + padding });
			canvas.DrawString("Player " + std::to_string(i + 1) + " : " + player_stats_list_on_team_blue[index].name, box_scale, box_scale);
			padding += 15;
		}

		if (disp_change_players_count_on_team_blue > 0 && disp_change_players_count_on_team_orange > 0) {
			canvas.SetColor(240, 240, 240, 255);
			canvas.SetPosition(Vector2{ (sz.X * x_position) / 100, (sz.Y * y_position) / 100 + padding });
			canvas.DrawString("", box_scale, box_scale);
			padding += 15;
		}

		for (int i = 0; i < disp_change_players_count_on_team_orange; i++) {
			int index = random_players_no_list_on_team_orange[i];
			canvas.SetColor(255, 143, 34, 255);
			canvas.SetPosition(Vector2{ (sz.X * x_position) / 100, (sz.Y * y_position) / 100 + padding });
			canvas.DrawString("Player " + std::to_string(i + 1) + " : " + player_stats_list_on_team_orange[index].name, box_scale, box_scale);
			padding += 15;
		}
	}
	else if (enable_change_players_rank_on_team) {
		if (disp_change_players_rank_on_team_blue > 0) {
			canvas.SetColor(30, 144, 255, 255);
			canvas.SetPosition(Vector2{ (sz.X * x_position) / 100, (sz.Y * y_position) / 100 + padding });
			canvas.DrawString("Player : " + player_stats_list_on_team_blue[disp_change_players_rank_on_team_blue - 1].name, box_scale, box_scale);
			padding += 15;
		}

		if (disp_change_players_rank_on_team_blue > 0 && disp_change_players_rank_on_team_orange > 0) {
			canvas.SetColor(240, 240, 240, 255);
			canvas.SetPosition(Vector2{ (sz.X * x_position) / 100, (sz.Y * y_position) / 100 + padding });
			canvas.DrawString("", box_scale, box_scale);
			padding += 15;
		}

		if (disp_change_players_rank_on_team_orange > 0) {
			canvas.SetColor(255, 143, 34, 255);
			canvas.SetPosition(Vector2{ (sz.X * x_position) / 100, (sz.Y * y_position) / 100 + padding });
			canvas.DrawString("Player : " + player_stats_list_on_team_orange[disp_change_players_rank_on_team_orange - 1].name, box_scale, box_scale);
			padding += 15;
		}
	}
	else if (enable_change_low_score_players_num_on_lose_team) {
		if (lose_team == 0 && disp_change_low_score_players_num_on_team_blue > 0) {
			for (int i = 0; i < disp_change_low_score_players_num_on_team_blue; i++) {
				canvas.SetColor(30, 144, 255, 255);
				canvas.SetPosition(Vector2{ (sz.X * x_position) / 100, (sz.Y * y_position) / 100 + padding });
				canvas.DrawString("Player " + std::to_string(i + 1) + " : " + player_stats_list_on_team_blue[players_count_on_team_blue - (1 + i)].name, box_scale, box_scale);
				padding += 15;
			}
		}
		else if (lose_team == 1 && disp_change_low_score_players_num_on_team_orange > 0) {
			for (int i = 0; i < disp_change_low_score_players_num_on_team_orange; i++) {
				canvas.SetColor(255, 143, 34, 255);
				canvas.SetPosition(Vector2{ (sz.X * x_position) / 100, (sz.Y * y_position) / 100 + padding });
				canvas.DrawString("Player " + std::to_string(i + 1) + " : " + player_stats_list_on_team_orange[players_count_on_team_orange - (1 + i)].name, box_scale, box_scale);
				padding += 15;
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
}

void DispChangePlayerPlugin::SetInputStaus()
{
	enable_disp_change_player_plugin = cvarManager->getCvar("enable_disp_change_player_plugin").getBoolValue();

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
				player.GetPlayerName().ToString(),
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
