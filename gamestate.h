#pragma once

#include <string>
#include <vector>

#ifndef GAMESTATE_H
#define GAMESTATE_H

class GameState {
 public:
  GameState(const std::string& answer)
      : answer_(answer), game_status_("active"), error_message_("") {}
  std::string Answer() { return answer_; }
  std::string GameStatus() { return game_status_; }
  std::string ErrorMessage() { return error_message_; }
  std::vector<std::string> BoardColors() { return board_colors_; }
  std::vector<std::string> GuessedWords() { return guessed_words_; }
  std::vector<std::string> LetterColors() { return letter_colors_; }
  void SetAnswer(const std::string& answer) { answer_ = answer; }
  void SetErrorMessage(const std::string& error_message) {
    error_message_ = error_message;
  }
  void SetGameStatus(const std::string& game_status) {
    game_status_ = game_status;
  }
  void SetBoardColors(std::vector<std::string>& board_colors) {
    board_colors_ = board_colors;
  }
  void SetGuessedWords(const std::vector<std::string>& guessed_words) {
    guessed_words_ = guessed_words;
  }
  void SetLetterColors(const std::vector<std::string>& letter_colors) {
    letter_colors_ = letter_colors;
  }
  bool GameStatusCheck() {
    if (game_status_ == "active") {
      return true;
    }
    return false;
  }

 private:
  std::string answer_;
  std::string game_status_;
  std::string error_message_;
  std::vector<std::string> board_colors_;
  std::vector<std::string> guessed_words_;
  std::vector<std::string> letter_colors_;
};

#endif  // GAMESTATE_H