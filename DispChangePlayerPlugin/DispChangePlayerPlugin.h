#pragma once
#pragma comment( lib, "bakkesmod.lib" )
#include "bakkesmod/plugin/bakkesmodplugin.h"

class DispChangePlayerPlugin : public BakkesMod::Plugin::BakkesModPlugin
{
private:
	bool enable_disp_change_player_plugin;

	/* ---- InputStatus(Start) ---- */
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

	void UiRender(CanvasWrapper canvas);
	void PlayerNameRender(CanvasWrapper canvas);
	void EndGame(std::string eventName);
	void SetInputStaus();
	void SetPlayerStatsList(ServerWrapper sw);
	void SetDispChangePlayersCount();
	void* CreateRandomNoList(int count, int random_no_list[]);
};
