#include <fstream>
#include <iostream>
#include <string>

#include "Board.hpp"

int main()
{
    std::string filename = "rectangulos.in";
    std::ifstream in(filename);

    if (!in)
    {
        std::cerr << "Can't read file \"" << filename << "\"." << std::endl;
        return 1;
    }

    size_t n_rectangles;
    size_t board_rows;
    size_t board_cols;

    in >> n_rectangles >> board_rows >> board_cols;

    Board bd(board_rows, board_cols);
    for (; n_rectangles != 0; n_rectangles--)
    {
        std::string temp;
        size_t pos_x;
        size_t pos_y;
        size_t rows;
        size_t cols;
        in >> temp >> pos_x >> pos_y >> rows >> cols;

        //  Because it starts counting at 1, we substract one of the x- and
        // y-positions. This is easier than implementing something in `Board`.
        bd.insert({pos_x - 1, pos_y - 1, rows, cols});
    }

    for (auto const& r : bd.get_rectangles())
    {
        std::cout << "A" << " " << r.pos_x + 1 << " " << r.pos_y + 1 << " "
            << r.rows << " " << r.cols << std::endl;
    }

    return 0;
}
