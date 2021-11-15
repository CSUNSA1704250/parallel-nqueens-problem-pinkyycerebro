#include <fstream>

void generar_tablero(int queens[], int queenSize) {
  std::ofstream file("graph.dot");
  file << "digraph G { \n";
  file << "node [shape=plaintext]\n";
  file << "a [fontsize=30\n";
  file << "label=<\n";
  file << "<TABLE border='5' cellspacing='0' cellpadding='7' style='rounded' "
          ">\n";
  int pos_color = 0;
  for (int i = 0; i < queenSize; i++) {
    file << "<TR>\n";
    for (int j = 0; j < queenSize; j++) {
      if (j == queens[i] - 1)
        file << "<TD border='1' bgcolor='chartreuse1'>♚</TD>\n";
      else {
        if (pos_color % 2 == 0)
          file << "<TD border='1'>   </TD>\n";
        else
          file << "<TD border='1' bgcolor='black'>   </TD>\n";
      }
      pos_color++;
    }
    pos_color++;
    file << "</TR>\n\n";
  }
  file << "</TABLE>\n>];\n}";
  file.close();
}