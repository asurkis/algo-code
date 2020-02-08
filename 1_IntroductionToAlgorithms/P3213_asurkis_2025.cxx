#include <iostream>

using namespace std;

int main() {
  int T;
  cin >> T;
  for (int i = 0; i < T; ++i) {
    int participants_count;
    int team_count;
    cin >> participants_count >> team_count;
    int team_size = participants_count / team_count;
    int increased_teams = participants_count % team_count;

    int match_count = 0;
    int prev_teams = 0;
    for (int j = 0; j < team_count; j++) {
      int current_team = team_size + (j < increased_teams ? 1 : 0);
      match_count += current_team * prev_teams;
      prev_teams += current_team;
    }
    cout << match_count << endl;
  }
  return 0;
}
