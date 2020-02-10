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

    int doubled_match_count = participants_count * participants_count;
    for (int j = 0; j < team_count; j++) {
      int current_team = team_size + (j < increased_teams ? 1 : 0);
      doubled_match_count -= current_team * current_team;
    }
    cout << (doubled_match_count / 2) << endl;
  }
  return 0;
}
