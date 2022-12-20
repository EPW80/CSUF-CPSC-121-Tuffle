#include "tuffle.h"

void TuffleGame::NewGame() {
  game_state_ = GameState(dictionary_.GetRandomTuffle());
}
std::string BoardColorCheck(std::string guessed_words, std::string answer) {
  std::string _board_color_check = "BBBBB";
  for (int i = 0; i < answer.size(); i++) {
    if (guessed_words[i] == answer[i]) {
      _board_color_check[i] = 'G';
      answer[i] = '$';
    }
  }
  for (int i = 0; i < answer.size(); i++) {
    if (answer.find(guessed_words.at(i)) != std::string::npos) {
      int index = answer.find(guessed_words.at(i));
      if (_board_color_check[i] != 'G') {
        _board_color_check[i] = 'Y';
        answer[index] = '$';
      }
    }
  }
  return _board_color_check;
}
void TuffleGame::LetterKeyPressed(char key) {
  if (game_state_.GameStatus() != "active") {
    return;
  }
  game_state_.SetErrorMessage("");
  std::vector<std::string> guessed_words = game_state_.GuessedWords();

  if (guessed_words.size() == 0) {
    guessed_words.push_back("");
  }
  int index = guessed_words.size() - 1;
  std::string _word = guessed_words.at(index);
  if (_word.size() != 5) {
    guessed_words[index] = _word + key;
    game_state_.SetGuessedWords(guessed_words);
  }
}
void TuffleGame::EnterKeyPressed() {
  std::vector<std::string> guessed_words = game_state_.GuessedWords();
  if (game_state_.GameStatus() != "active") {
    return;
  }
  game_state_.SetErrorMessage("");
  int index = guessed_words.size() - 1;
  std::string _word = guessed_words.at(index);
  if (_word.length() != 5) {
    game_state_.SetErrorMessage("Please enter at least 5 characters. ");
    return;
  } else if (!dictionary_.IsValidGuess(_word)) {
    game_state_.SetErrorMessage("Invalid guess. Try again! ");
    return;
  }
  std::string _board_colors = BoardColorCheck(_word, game_state_.Answer());
  std::vector<std::string> Board_Colors = game_state_.BoardColors();
  Board_Colors.push_back(_board_colors);
  game_state_.SetBoardColors(Board_Colors);
  std::string _answer = game_state_.Answer();
  if (_board_colors == "GGGGG") {
    game_state_.SetGameStatus("win");
  } else if (guessed_words.size() == 6) {
    game_state_.SetGameStatus("lose");
  } else {
    guessed_words.push_back("");
    game_state_.SetGuessedWords(guessed_words);
  }
}
void TuffleGame::DeleteKeyPressed() {
  std::vector<std::string> _current_guess = game_state_.GuessedWords();
  if (_current_guess.size() == 0 || (game_state_.GameStatus() != "active")) {
    return;
  }
  int index = _current_guess.size() - 1;
  std::string _word = _current_guess.at(index);
  if (_word.length() == 0) {
    return;
  }
  _word.pop_back();
  _current_guess.at(index) = _word;
  game_state_.SetGuessedWords(_current_guess);
}
crow::json::wvalue TuffleGame::GameStateInJson() {
  // The JSON object to return to the Tuffle Frontend.
  crow::json::wvalue game_state_json({});

  game_state_json["answer"] = game_state_.Answer();
  game_state_json["boardColors"] = game_state_.BoardColors();
  game_state_json["guessedWords"] = game_state_.GuessedWords();
  game_state_json["gameStatus"] = game_state_.GameStatus();
  game_state_json["errorMessage"] = game_state_.ErrorMessage();
  game_state_json["letterColors"] = game_state_.LetterColors();
  return game_state_json;
};