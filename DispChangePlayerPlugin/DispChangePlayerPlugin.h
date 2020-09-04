#pragma once
#pragma comment( lib, "bakkesmod.lib" )
#include "bakkesmod/plugin/bakkesmodplugin.h"
#include "bakkesmod/wrappers/canvaswrapper.h"

class DispChangePlayerPlugin : public BakkesMod::Plugin::BakkesModPlugin
{
private:
	/* ---- PluginParam(Start) ---- */
	std::string output_directory = "bakkesmod/data/dispchangeplayer/";
	std::string output_filename_win_team_blue = "win_team_blue.txt";
	std::string output_filename_win_team_orange = "win_team_orange.txt";
	std::string output_filename_random_chagen_player_name = "random_change_player_name.txt";
	std::string output_filename_random_chagen_player_name_on_team_blue = "random_chagen_player_name_on_team_blue.txt";
	std::string output_filename_random_chagen_player_name_on_team_orange = "random_chagen_player_name_on_team_orange.txt";
	std::string output_filename_rank_chagen_player_name_on_team_blue = "rank_chagen_player_name_on_team_blue.txt";
	std::string output_filename_rank_chagen_player_name_on_team_orange = "rank_chagen_player_name_on_team_orange.txt";
	std::string output_filename_change_low_score_player_name_on_lose_team = "change_low_score_player_name_on_lose_team.txt";
	/* ---- PluginParam(End) ---- */

	/* ---- InputStatus(Start) ---- */
	bool enable_disp_change_player_plugin;

	bool output_change_players_to_file;

	bool enable_random_change_players;
	int random_change_players_num;

	bool enable_random_change_players_on_team;
	int random_change_players_num_on_team_blue;
	int random_change_players_num_on_team_orange;

	bool enable_change_players_rank_on_team;
	int change_player_rank_on_team_blue;
	int change_player_rank_on_team_orange;

	bool enable_change_low_score_players_num_on_lose_team;
	int change_low_score_player_num_on_lose_team;
	/* ---- InputStatus(End) ---- */

	/* ---- RenderStatus(Start) ---- */
	int common_string_color_r = 240;
	int common_string_color_g = 240;
	int common_string_color_b = 240;
	int common_string_color_a = 255;

	int team_blue_string_color_r = 30;
	int team_blue_string_color_g = 144;
	int team_blue_string_color_b = 255;
	int team_blue_string_color_a = 255;

	int team_orange_string_color_r = 255;
	int team_orange_string_color_g = 143;
	int team_orange_string_color_b = 34;
	int team_orange_string_color_a = 255;

	int fill_box_color_r;
	int fill_box_color_g;
	int fill_box_color_b;
	int fill_box_color_a;

	int draw_box_color_r;
	int draw_box_color_g;
	int draw_box_color_b;
	int draw_box_color_a;

	int x_position;
	int y_position;
	float box_scale;

	int padding = 0;
	std::stringstream output_stringstream;
	/* ---- RenderStatus(End) ---- */

	/* ---- PlayerStatsList(Start) ---- */
	int team_count = 0;
	int lose_team = 0;
	int players_count = 0;
	int players_count_on_team_blue = 0;
	int players_count_on_team_orange = 0;
	struct player_stats {
		int team;
		std::string name;
		int score;
		int goals;
		int assists;
		int saves;
		int shots;

		bool operator<(const player_stats& ps) const {
			if (score > ps.score) {
				return true;
			}
			else if (score == ps.score && goals > ps.goals) {
				return true;
			}
			else if (score == ps.score && goals == ps.goals && assists > ps.assists) {
				return true;
			}
			else if (score == ps.score && goals == ps.goals && assists == ps.assists && saves > ps.saves) {
				return true;
			}
			else if (score == ps.score && goals == ps.goals && assists == ps.assists && saves == ps.saves && shots > ps.shots) {
				return true;
			}
			return false;
		}
	};
	std::vector<player_stats> player_stats_list;
	std::vector<player_stats> player_stats_list_on_team_blue;
	std::vector<player_stats> player_stats_list_on_team_orange;
	/* ---- PlayerStatsList(End) ---- */

	/* ---- RandomPlayersNoList(Start) ---- */
	bool exists_no;
	int* random_players_no_list;
	int* random_players_no_list_on_team_blue;
	int* random_players_no_list_on_team_orange;
	/* ---- RandomPlayersNoList(End) ---- */

	/* ---- DispChangePlayersCount(Start) ---- */
	int disp_change_players_count = 0;
	int disp_change_players_count_on_team_blue = 0;
	int disp_change_players_count_on_team_orange = 0;
	int disp_change_players_rank_on_team_blue;
	int disp_change_players_rank_on_team_orange;
	int disp_change_low_score_players_num_on_team_blue;
	int disp_change_low_score_players_num_on_team_orange;
	/* ---- DispChangePlayersCount(End) ---- */

public:
	virtual void onLoad();
	virtual void onUnLoad();

	void EndGame(std::string eventName);

	void SetInputStaus();
	void SetPlayerStatsList(ServerWrapper sw);
	void SetDispChangePlayersCount();
	void* CreateRandomNoList(int count, int random_no_list[]);

	void CreateOutputDirectory();
	void ClearOutputStringstream();
	void OutputToFile(std::string output_filename);
	void WinnerTeamOutputToFile();
	void RandomChangePlayersOutputToFile();
	void RandomChangePlayersOnTeamOutputToFile();
	void ChangePlayersRankOnTeamOutputToFile();
	void ChangeLowScorePlayersOnLoseTeamOutputToFile();

	void UiRender(CanvasWrapper canvas);
	void FillBoxCanvasRender(CanvasWrapper canvas);
	void DrawBoxCanvasRender(CanvasWrapper canvas);
	void CommonStringColorCanvasRender(CanvasWrapper canvas, std::string str);
	void TeamBlueStringColorCanvasRender(CanvasWrapper canvas, std::string str);
	void TeamOrangeStringColorCanvasRender(CanvasWrapper canvas, std::string str);

	std::string WStringToString(std::wstring string);
};
